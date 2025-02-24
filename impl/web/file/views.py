## @file file/views.py
#  @brief database interface to client for document table

"""
database interface to client
"""

import datetime
import mimetypes
import ntpath
import os
from user.views import get_user_id
from user.views import get_username
from wsgiref.util import FileWrapper
from file.models import Document
from django.http import HttpResponse
from django.conf import settings
from django.http import StreamingHttpResponse
from django.core.files.base import File as DjangoFile


def get_file_contents(params, user):
    """get file contents"""
    if not user.is_authenticated:
        return {'status' : 'error', 'msg' : 'User is not authenticated.'}
    user_id = get_user_id(user)
    docfile = str(params['docfile'])
    file = Document.objects.filter(user_id=user_id, docfile=docfile).values()
    if user.is_superuser:
        file = Document.objects.filter(docfile=docfile).values()
    if len(file) == 0:
        return {'status' : 'error', 'msg' : 'File does not exist.'}
    else:
        file_path = settings.MEDIA_ROOT + '/' + docfile
        if os.path.getsize(file_path) > 5000000:
            return {'status' : 'error', 'msg' : 'File is oversized.'}
        else:
            with open(file_path, 'r') as content_file:
                content = content_file.read()
            return {'status' : 'success', 'msg' : content}

def download_file(params, user):
    """download file"""
    from django.utils.encoding import smart_str
    if not user.is_authenticated:
        return False
    user_id = get_user_id(user)
    docfile = str(params['docfile'])
    file = Document.objects.filter(user_id=user_id, docfile=docfile).values()
    if user.is_superuser:
        file = Document.objects.filter(docfile=docfile).values()
    if len(file) == 0:
        return HttpResponse("No such file.", content_type="text/plain")
    file_name = file[0]['file_name']
    file_path = settings.MEDIA_ROOT + '/' + docfile
    chunk_size = 8192
    response = StreamingHttpResponse(FileWrapper(open(file_path), chunk_size), content_type=mimetypes.guess_type(file_path)[0])
    file_size_without_new_lines = 0
    for line in open(file_path):
        file_size_without_new_lines = file_size_without_new_lines + len(line) - 1
    response['Content-Length'] = file_size_without_new_lines
    response['Content-Disposition'] = "attachment; filename=%s" % smart_str(file_name)
    return response

def save_content_to_file(file_id, content):
    """save content to file"""
    document = Document.objects.filter(id=file_id)
    if len(document) == 0:
        return False
    document.update(input_time=str(datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ")))
    docfile = (document.values())[0]['docfile']
    file = open(settings.MEDIA_ROOT + '/' + docfile, 'w+')
    file.write(content)
    file.close()
    # below two lines added in order to send post_save signal, which will trigger determine_file_format function from file.models
    doc = Document.objects.get(id=file_id)
    doc.save()
    return True

def upload_file(docfile, user):
    """upload input file"""
    if not user.is_authenticated:
        return {'status' : 'error', 'msg' : 'You have to be logged in to upload a new file.'}
    user_id = get_user_id(user)
    input_time = str(datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"))
    newdoc = Document(user_id=user_id, docfile=docfile, file_name=ntpath.basename(docfile.name), input_time=input_time)
    newdoc.save()

def get_user_files(params, user):
    """return all files for specified user"""
    if not user.is_authenticated:
        return
    if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + user.username)
    user_id = get_user_id(user)
    files = Document.objects.filter(user_id=user_id).values()
    files_dict = dict()
    i = 0
    for file in files:
        files_dict[i] = {"file_name": file['file_name'], "input_time": file['input_time'], "docfile": file['docfile'], "file_format": file['file_format']}
        i = i + 1
    return files_dict

def get_all_files(params, user):
    """return all files for all users"""
    if not user.is_authenticated or not user.is_superuser:
        return {}
    if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + user.username)
    files = Document.objects.values()
    files_dict = dict()
    i = 0
    for file in files:
        files_dict[i] = {"file_name": file['file_name'], "input_time": file['input_time'], "docfile": file['docfile'], "file_format": file['file_format'], "owner": get_username(file['user_id'])}
        i = i + 1
    return files_dict

def delete_file(params, user):
    """remove file from a Document database"""
    import assembly.views
    import align.views
    import scaffold.views
    import olc.views
    if not user.is_authenticated:
        return {'status' : 'error', 'msg' : 'User is not authenticated.'}
    user_id = get_user_id(user)
    docfile = str(params['docfile'])
    file = Document.objects.filter(user_id=user_id, docfile=docfile).values()
    if user.is_superuser:
        file = Document.objects.filter(docfile=docfile).values()
    if len(file) == 0:
        return {'status' : 'error', 'msg' : 'File does not exist.'}
    elif align.views.is_file_used(file[0]['id']) or assembly.views.is_file_used(file[0]['id'])\
            or scaffold.views.is_file_used(file[0]['id']) or olc.views.is_file_used(file[0]['id']):
        return {'status' : 'error', 'msg' : 'File is used.'}
    else:
        Document.objects.filter(docfile=docfile).delete()
        return {'status' : 'success', 'msg' : 'File is deleted.'}

def delete_user_files(user_id, username):
    """remove all files for user with user_id"""
    Document.objects.filter(user_id=user_id).delete()
    user_private_media_path = settings.PRIVATE_MEDIA_ROOT + '/' + username
    user_public_media_path = settings.PUBLIC_USERS_MEDIA_ROOT + '/' + username
    if os.path.exists(user_private_media_path):
        os.rmdir(user_private_media_path)
    if os.path.exists(user_public_media_path):
        os.rmdir(user_public_media_path)
    return True

def upload_example_files(params, user):
    """upload example files"""
    if not user.is_authenticated:
        return {'status' : 'error', 'msg' : 'You have to be logged in to upload a new file.'}
    if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + user.username)
    if not os.path.exists(settings.EXAMPLE_FILES_MEDIA_ROOT):
        return {'status' : 'error', 'msg' : 'Directory for example files does not exist.'}
    src_files = os.listdir(settings.EXAMPLE_FILES_MEDIA_ROOT)
    for file_name in src_files:
        full_file_name = os.path.join(settings.EXAMPLE_FILES_MEDIA_ROOT, file_name)
        if (os.path.isfile(full_file_name)):
            docfile = DjangoFile(open(full_file_name))
            upload_file(docfile, user)

def get_docfile(id):
    """return docfile for wile with specified id"""
    file = Document.objects.filter(id=id).values()
    if len(file) != 1:
        return ''
    else:
        return file[0]['docfile']
