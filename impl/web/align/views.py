## @file align/views.py
#  @brief database interface to client for align task table

"""
database interface to client
"""

import datetime
import os
from user.views import get_username
from align.models import AlignTask
from file.models import Document
from django.conf import settings
from django.db.models import Q
from production.views import get

def break_align_task(params, user):
    """break align task"""
    from user.views import get_user_id
    from dnaasmpy.views import break_command
    if not user.is_authenticated:
        return False
    id = str(params['id'])
    task = AlignTask.objects.filter(id=id)
    if len(task) == 0 or (task.values('user_id')[0]['user_id'] != get_user_id(user) and not user.is_superuser):
        return False
    break_command({'task_id' : id, 'command_type' : 'ALIGN_COMMAND_TYPE'})
    return True

def insert(params, user):
    """insert align task into a database"""
    from user.views import get_user_id
    from dnaasmpy.views import start_align_command
    if not user.is_authenticated:
        return {'status' : 'error', 'msg' : 'You have to be logged in to add a new task.'}
    user_id = get_user_id(user)
    name = str(params['name'])
    if str(params['align_algorithm']) == 'h':
        align_algorithm = AlignTask.HIRSCHBERG
    elif str(params['align_algorithm']) == 'nw':
        align_algorithm = AlignTask.NEEDLEMAN_WUNSCH
    else:
        align_algorithm = AlignTask.UNKNOWN
    circular = str(params['circular'])
    result_notification = str(params['result_notification'])
    mail_address = str(params['mail_address'])
    if len(Document.objects.filter(file_name=name, user_id=user_id)) > 0:
        return {'status' : 'error', 'msg' : 'Task name error.'}
    seq_file_name = str(params['seq_file_name'])
    ref_file_name = str(params['ref_file_name'])
    sequence_file = Document.objects.filter(file_name=seq_file_name, user_id=user_id)
    if len(sequence_file) != 0:
        docfile = sequence_file.values('docfile')[0]['docfile']
        sequence_file_id = sequence_file.values('id')[0]['id']
        #to do zmiany!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        with open(settings.MEDIA_ROOT + '/' + docfile, 'r') as content_file:
            sequence = content_file.read()
            content_file.close()
    else:
        return False
    reference_file = Document.objects.filter(file_name=ref_file_name, user_id=user_id)
    if len(reference_file) != 0:
        docfile = reference_file.values('docfile')[0]['docfile']
        reference_file_id = reference_file.values('id')[0]['id']
        #to do zmiany!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        with open(settings.MEDIA_ROOT + '/' + docfile, 'r') as content_file:
            reference = content_file.read()
            content_file.close()
    else:
        return False
    if not os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username)
    output_file = open(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username + '/' + name, 'w+')
    output_file.close()
    result_docfile = settings.PUBLIC_USERS_PREFIX + '/' + user.username + '/' + name
    output_document = Document(user_id=user_id, docfile=result_docfile, file_name=name, input_time='')
    output_document.save()
    gap_penalty = str(params['gap_penalty'])
    AA = str(params['AA'])
    AC = str(params['AC'])
    AG = str(params['AG'])
    AT = str(params['AT'])
    CA = str(params['CA'])
    CC = str(params['CC'])
    CG = str(params['CG'])
    CT = str(params['CT'])
    GA = str(params['GA'])
    GC = str(params['GC'])
    GG = str(params['GG'])
    GT = str(params['GT'])
    TA = str(params['TA'])
    TC = str(params['TC'])
    TG = str(params['TG'])
    TT = str(params['TT'])
    input_time = str(datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"))
    new_align_task = AlignTask.objects.create(user_id=user_id, name=name, sequence_file_id=sequence_file_id, reference_file_id=reference_file_id, output_file_id=output_document.id, align_algorithm=align_algorithm, circular=(circular == 'true'), gap_penalty=gap_penalty, AA=AA, AC=AC, AG=AG, AT=AT, CA=CA, CC=CC, CG=CG, CT=CT, GA=GA, GC=GC, GG=GG, GT=GT, TA=TA, TC=TC, TG=TG, TT=TT, result_notification=(result_notification == 'true'), mail_address=mail_address, input_time=input_time, output_time='')
    start_align_command({'task_id': new_align_task.id, 'gap_penalty':gap_penalty, 'sequence':sequence, 'reference':reference, 'align_algorithm':align_algorithm, 'circular':circular, 'AA':AA, 'AC':AC, 'AG':AG, 'AT':AT, 'CA':CA, 'CC':CC, 'CG':CG, 'CT':CT, 'GA':GA, 'GC':GC, 'GG':GG, 'GT':GT, 'TA':TA, 'TC':TC, 'TG':TG, 'TT':TT})  #from dnaasmpy.views
    result_url = get({})['production_string'] + '/' + result_docfile
    return {'status' : 'success', 'msg' : 'New task was added successfully.', 'result_url' : result_url}

def delete(params, user):
    """remove align task from a database"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return False
    id = str(params['id'])
    task = AlignTask.objects.filter(id=id)
    if len(task) == 0 or (task.values('user_id')[0]['user_id'] != get_user_id(user) and not user.is_superuser):
        return False
    task.delete()
    return True

def delete_user_align_tasks(user_id):
    """remove all align tasks for user with user_id from a database"""
    AlignTask.objects.filter(user_id=user_id).delete()
    return True

def is_file_used(file_id):
    """check if file with id equal to file_id is used in any align task"""
    align_tasks = AlignTask.objects.filter(Q(sequence_file_id=file_id) | Q(reference_file_id=file_id))
    if len(align_tasks) == 0:
        return False
    else:
        return True

def get_user_align_tasks(params, user):
    """return all align tasks for specified user"""
    from user.views import get_user_id
    from dnaasmpy.views import get_commands
    if not user.is_authenticated:
        return {}
    user_id = get_user_id(user)
    commands_info = get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
    align_tasks = AlignTask.objects.all().order_by("id").values()
    out_dict = dict()
    i = 0
    for task in align_tasks:
        if task['user_id'] == user_id:
            out_dict[i] = make_dict_from_task(task)
            i = i + 1
    for m in commands_info:
        for k in out_dict:
            if out_dict[int(k)]['id'] == commands_info[int(m)]['id']:
                out_dict[int(k)]['progress'] = commands_info[int(m)]['progress']
                out_dict[int(k)]['state'] = commands_info[int(m)]['state']
    return out_dict

def get_all_align_tasks(params, user):
    """return all align tasks for all users"""
    from dnaasmpy.views import get_commands
    if not user.is_authenticated or not user.is_superuser:
        return {}
    commands_info = get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
    align_tasks = AlignTask.objects.all().order_by("id").values()
    out_dict = dict()
    i = 0
    for task in align_tasks:
        out_dict[i] = make_dict_from_task(task)
        out_dict[i]['owner'] = get_username(task['user_id'])
        i = i + 1
    for m in commands_info:
        for k in out_dict:
            if out_dict[int(k)]['id'] == commands_info[int(m)]['id']:
                out_dict[int(k)]['progress'] = commands_info[int(m)]['progress']
                out_dict[int(k)]['state'] = commands_info[int(m)]['state']
    return out_dict

def make_dict_from_task(task):
    """return dictionary with data for input task"""
    seq_file = Document.objects.filter(id=task['sequence_file_id']).values()
    if len(seq_file) != 0:
        seq_file_name = seq_file[0]['file_name']
    else:
        seq_file_name = ''
    ref_file = Document.objects.filter(id=task['reference_file_id']).values()
    if len(ref_file) != 0:
        ref_file_name = ref_file[0]['file_name']
    else:
        ref_file_name = ''
    return {"id" : task['id'], "name": task['name'], "sequence_file_name": seq_file_name, "reference_file_name": ref_file_name, "align_algorithm": task['align_algorithm'], "circular": task['circular'], "gap_penalty": task['gap_penalty'], "AA": task['AA'], "AC": task['AC'], "AG": task['AG'], "AT": task['AT'], "CA": task['CA'], "CC": task['CC'], "CG": task['CG'], "CT": task['CT'], "GA": task['GA'], "GC": task['GC'], "GG": task['GG'], "GT": task['GT'], "TA": task['TA'], "TC": task['TC'], "TG": task['TG'], "TT": task['TT'], "input_time": task['input_time'], "output_time": task['output_time'], "progress": 1}

def get_align_task_docfile(params, user):
    """get output docfile and file name for align task"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return {}
    id = str(params['id'])
    if user.is_superuser:
        align_task = AlignTask.objects.filter(id=id).values()
    else:
        align_task = AlignTask.objects.filter(user_id=get_user_id(user), id=id).values()
    if len(align_task) == 0:
        return {}
    file = Document.objects.filter(user_id=align_task[0]['user_id'], id=align_task[0]['output_file_id']).values()
    if len(file) == 0:
        return {}
    return {'docfile' : file[0]['docfile'], 'file_name': file[0]['file_name']}
