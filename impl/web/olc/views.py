## @file olc/views.py
#  @brief database interface to client for olc assembly task table

"""
database interface to client
"""

from datetime import datetime
import datetime
import os
from user.views import get_username
from olc.models import OlcAssemblyTask
from file.models import Document
from django.conf import settings
from django.db.models import Q
from production.views import get


def break_olc_task(params, user):
    """break olc task"""
    from user.views import get_user_id
    from dnaasmpy.views import break_command
    if not user.is_authenticated:
        return False
    id = str(params['id'])
    task = OlcAssemblyTask.objects.filter(id=id)
    if len(task) == 0 or (
            task.values('user_id')[0]['user_id'] != get_user_id(user) and not user.is_superuser):
        return False
    break_command({'task_id': id, 'command_type': 'OLC_COMMAND_TYPE'})
    return True


def insert(params, user):
    """insert olc task into a database"""
    from user.views import get_user_id
    from dnaasmpy.views import start_olc_assembly_command
    if not user.is_authenticated:
        return {'status': 'error', 'msg': 'You have to be logged in to add a new task.'}
    user_id = get_user_id(user)
    name = str(params['name'])
    if len(Document.objects.filter(file_name=name, user_id=user_id)) > 0:
        return {'status': 'error', 'msg': 'Task name error.'}
    if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + user.username)
    if not os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username)
    output_file = open(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username + '/' + name, 'w+')
    output_file.close()
    result_docfile = settings.PUBLIC_USERS_PREFIX + '/' + user.username + '/' + name
    newdoc = Document(user_id=user_id, docfile=result_docfile, file_name=name, input_time='')
    newdoc.save()

    long_reads_file_name = str(params['long_reads_file_name'])
    long_reads_file_id = ''
    kmer_length = str(params['kmer_length'])
    sketch_num = str(params['sketch_num'])
    min_jaccard_sim = str(params['min_jaccard_sim'])
    match_score = str(params['match_score'])
    mismatch_score = str(params['mismatch_score'])
    gap_penalty = str(params['gap_penalty'])
    min_edge = str(params['min_edge'])
    min_contig_length = str(params['min_contig_length'])
    path_width = str(params['path_width'])
    input_time = str(datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"))

    long_reads_file = Document.objects.filter(file_name=long_reads_file_name, user_id=user_id)
    if len(long_reads_file) != 0:
        long_reads_file_id = long_reads_file.values('id')[0]['id']

    new_olc_task = OlcAssemblyTask.objects.create(
        user_id=user_id,
        name=name,
        olc_long_reads_file_id=long_reads_file_id,
        output_file_id=newdoc.id,
        kmer_length=kmer_length,
        sketch_num=sketch_num,
        min_jaccard_sim=min_jaccard_sim,
        match_score=match_score,
        mismatch_score=mismatch_score,
        gap_penalty=gap_penalty,
        min_edge=min_edge,
        min_contig_length=min_contig_length,
        path_width=path_width,
        input_time=input_time,
        output_time=''
    )

    start_olc_assembly_command({
        'task_id': new_olc_task.id,
        'kmer_length': kmer_length,
        'sketch_num': sketch_num,
        'min_jaccard_sim': min_jaccard_sim,
        'match_score': match_score,
        'mismatch_score': mismatch_score,
        'gap_penalty': gap_penalty,
        'min_edge': min_edge,
        'min_contig_length': min_contig_length,
        'path_width': path_width,
        'input_file_name': long_reads_file[0].docfile.path if long_reads_file else '',
        'output_file_name': name
    })  # from dnaasmpy.views

    result_url = get({})['production_string'] + '/' + result_docfile

    return {
        'status': 'success',
        'msg': 'New task was added successfully.',
        'result_url': result_url,
        'task_id': new_olc_task.id
    }


def delete(params, user):
    """remove sth from a database"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return False
    id = str(params['id'])
    task = OlcAssemblyTask.objects.filter(id=id)
    if len(task) == 0 or (
            task.values('user_id')[0]['user_id'] != get_user_id(user) and not user.is_superuser):
        return False
    task.delete()
    return True


def delete_user_olc_tasks(user_id):
    """remove all tasks for user with user_id from a database"""
    OlcAssemblyTask.objects.filter(user_id=user_id).delete()
    return True


def is_file_used(file_id):
    """check if file with id equal to file_id is used in any scaffold task"""
    tasks = OlcAssemblyTask.objects.filter(Q(long_reads_file_id=file_id))
    if len(tasks) == 0:
        return False
    else:
        return True


def get_user_olc_tasks(params, user):
    """return all olc assembly tasks for specified user"""
    from user.views import get_user_id
    from dnaasmpy.views import get_commands
    if not user.is_authenticated:
        return
    user_id = get_user_id(user)
    commands_info = get_commands({'command_type': 'OLC_COMMAND_TYPE'})
    olc_tasks = OlcAssemblyTask.objects.all().order_by("id").values()
    out_dict = dict()
    i = 0
    for task in olc_tasks:
        if task['user_id'] == user_id:
            out_dict[i] = make_dict_from_task(task)
            i = i + 1
    for m in commands_info:
        for k in out_dict:
            if out_dict[int(k)]['id'] == commands_info[int(m)]['id']:
                out_dict[int(k)]['progress'] = commands_info[int(m)]['progress']
                out_dict[int(k)]['state'] = commands_info[int(m)]['state']
    return out_dict


def get_all_olc_tasks(params, user):
    """return all olc tasks for all users"""
    from dnaasmpy.views import get_commands
    out_dict = dict()
    if user.is_superuser:
        commands_info = get_commands({'command_type': 'OLC_COMMAND_TYPE'})
        olc_tasks = OlcAssemblyTask.objects.all().order_by("id").values()
        i = 0
        for task in olc_tasks:
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
    long_reads_file = Document.objects.filter(id=task['olc_long_reads_file_id']).values()
    if len(long_reads_file) != 0:
        long_reads_file_name = long_reads_file[0]['file_name']
    else:
        long_reads_file_name = ''
    return {
        "id": task['id'],
        "name": task['name'],
        "long_reads_file_name": long_reads_file_name,
        "kmer_length": task['kmer_length'],
        "sketch_num": task['sketch_num'],
        "min_jaccard_sim": task['min_jaccard_sim'],
        "match_score": task['match_score'],
        "mismatch_score": task['mismatch_score'],
        "gap_penalty": task['gap_penalty'],
        "min_edge": task['min_edge'],
        "min_contig_length": task['min_contig_length'],
        "path_width": task['path_width'],
        "input_time": task['input_time'],
        "output_time": task['output_time'],
        "progress": 1
    }


def get_olc_task_docfile(params, user):
    """get output docfile and file name for scaffold task"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return {}
    id = str(params['id'])
    if user.is_superuser:
        olc_task = OlcAssemblyTask.objects.filter(id=id).values()
    else:
        olc_task = OlcAssemblyTask.objects.filter(user_id=get_user_id(user), id=id).values()
    if len(olc_task) == 0:
        return {}
    file = Document.objects.filter(user_id=olc_task[0]['user_id'],
                                   id=olc_task[0]['output_file_id']).values()
    if len(file) == 0:
        return {}
    return {'docfile': file[0]['docfile'], 'file_name': file[0]['file_name']}
