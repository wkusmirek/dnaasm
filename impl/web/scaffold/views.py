## @file scaffold/views.py
#  @brief database interface to client for scaffold task table

"""
database interface to client
"""

import datetime
import os
from user.views import get_username
from scaffold.models import ScaffoldTask
from assembly.models import AssemblyTask
from file.models import Document
from django.conf import settings
from django.db.models import Q
from production.views import get

def break_scaffold_task(params, user):
    """break scaffold task"""
    from user.views import get_user_id
    from dnaasmpy.views import break_command
    if not user.is_authenticated:
        return False
    id = str(params['id'])
    task = ScaffoldTask.objects.filter(id=id)
    if len(task) == 0 or (task.values('user_id')[0]['user_id'] != get_user_id(user) and not user.is_superuser):
        return False
    break_command({'task_id' : id, 'command_type' : 'SCAFFOLD_COMMAND_TYPE'})
    return True

def insert(params, user):
    """insert scaffold task into a database"""
    from user.views import get_user_id
    from dnaasmpy.views import start_scaffold_command
    if not user.is_authenticated:
        return {'status' : 'error', 'msg' : 'You have to be logged in to add a new task.'}
    user_id = get_user_id(user)
    name = str(params['name'])
    if len(Document.objects.filter(file_name=name, user_id=user_id)) > 0:
        return {'status' : 'error', 'msg' : 'Task name error.'}
    if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + user.username)
    if not os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username)
    output_file = open(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username + '/' + name, 'w+')
    output_file.close()
    result_docfile = settings.PUBLIC_USERS_PREFIX + '/' + user.username + '/' + name
    newdoc = Document(user_id=user_id, docfile=result_docfile, file_name=name, input_time='')
    newdoc.save()
    assembly_task_name = str(params.get('assembly_task', ''))
    assembly_task = None
    if assembly_task_name != '':
        try:
            assembly_task = AssemblyTask.objects.get(name=assembly_task_name, user_id=user_id)
        except:
            pass

    contigs_file_name = str(params['contigs_file_name'])
    long_reads_file_name = str(params['long_reads_file_name'])
    long_reads_file_id = ''
    contigs_file_id = ''
    kmer_size = str(params['kmer_size'])
    distance = str(params['distance'])
    step = str(params['step'])
    min_links = str(params['min_links'])
    max_ratio = str(params['max_ratio'])
    min_contig_length = str(params['min_contig_length'])
    input_time = str(datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"))

    if contigs_file_name == '':
        # use output file from related assembly task
        contigs_file_name = assembly_task_name

    contigs_file = Document.objects.filter(file_name=contigs_file_name, user_id=user_id)
    if len(contigs_file) != 0:
        contigs_file_id = contigs_file.values('id')[0]['id']

    long_reads_file = Document.objects.filter(file_name=long_reads_file_name, user_id=user_id)
    if len(long_reads_file) != 0:
        long_reads_file_id = long_reads_file.values('id')[0]['id']

    new_scaffold_task = ScaffoldTask.objects.create(
        user_id=user_id,
        name=name,
        contigs_file_id=contigs_file_id,
        long_reads_file_id=long_reads_file_id,
        output_file_id=newdoc.id,
        kmer_size=kmer_size,
        distance=distance,
        step=step,
        min_links=min_links,
        max_ratio=max_ratio,
        min_contig_length=min_contig_length,
        input_time=input_time,
        output_time=''
    )

    if assembly_task is not None:
        new_scaffold_task.assembly_task = assembly_task
        new_scaffold_task.save()
        if assembly_task.output_time == '':
            return {
                'status' : 'success',
                'msg' : '''New scaffold task was added successfully. \
                        It will be started when related assembly task will finish''',
                'task_id' : new_scaffold_task.id
            }
        else:
            # scaffold task will be started when related assembly task will finish
            # (see dnaasmpy.views.serve_finished_commands)
            pass

    # start if standalone scaffold task OR related assembly task already finished
    start_scaffold_command({
        'task_id': new_scaffold_task.id,
        'kmer_size':kmer_size,
        'distance':distance,
        'step':step,
        'min_links':min_links,
        'max_ratio':max_ratio,
        'min_contig_length':min_contig_length,
        'contigs_file_path':contigs_file[0].docfile.path if contigs_file else '',
        'long_reads_file_path':long_reads_file[0].docfile.path if long_reads_file else '',
        'output_file_name':name
    })  #from dnaasmpy.views
    result_url = get({})['production_string'] + '/' + result_docfile

    return {
        'status' : 'success',
        'msg' : 'New task was added successfully.',
        'result_url' : result_url,
        'task_id' : new_scaffold_task.id
    }

def delete(params, user):
    """remove sth from a database"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return False
    id = str(params['id'])
    task = ScaffoldTask.objects.filter(id=id)
    if len(task) == 0 or (task.values('user_id')[0]['user_id'] != get_user_id(user) and not user.is_superuser):
        return False
    task.delete()
    return True

def delete_user_scaffold_tasks(user_id):
    """remove all tasks for user with user_id from a database"""
    ScaffoldTask.objects.filter(user_id=user_id).delete()
    return True

def is_file_used(file_id):
    """check if file with id equal to file_id is used in any scaffold task"""
    tasks = ScaffoldTask.objects.filter(Q(contigs_file_id=file_id) | Q(long_reads_file_id=file_id))
    if len(tasks) == 0:
        return False
    else:
        return True

def get_user_scaffold_tasks(params, user):
    """return all scaffold tasks for specified user"""
    from user.views import get_user_id
    from dnaasmpy.views import get_commands
    if not user.is_authenticated:
        return
    user_id = get_user_id(user)
    commands_info = get_commands({'command_type' : 'SCAFFOLD_COMMAND_TYPE'})
    scaffold_tasks = ScaffoldTask.objects.all().order_by("id").values()
    out_dict = dict()
    i = 0
    for task in scaffold_tasks:
        if task['user_id'] == user_id:
            out_dict[i] = make_dict_from_task(task)
            i = i + 1
    for m in commands_info:
        for k in out_dict:
            if out_dict[int(k)]['id'] == commands_info[int(m)]['id']:
                out_dict[int(k)]['progress'] = commands_info[int(m)]['progress']
                out_dict[int(k)]['state'] = commands_info[int(m)]['state']
    return out_dict

def get_all_scaffold_tasks(params, user):
    """return all scaffold tasks for all users"""
    from dnaasmpy.views import get_commands
    out_dict = dict()
    if user.is_superuser:
        commands_info = get_commands({'command_type' : 'SCAFFOLD_COMMAND_TYPE'})
        scaffold_tasks = ScaffoldTask.objects.all().order_by("id").values()
        i = 0
        for task in scaffold_tasks:
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
    contigs_file = Document.objects.filter(id=task['contigs_file_id']).values()
    if len(contigs_file) != 0:
        contigs_file_name = contigs_file[0]['file_name']
    else:
        contigs_file_name = ''
    long_reads_file = Document.objects.filter(id=task['long_reads_file_id']).values()
    if len(long_reads_file) != 0:
        long_reads_file_name = long_reads_file[0]['file_name']
    else:
        long_reads_file_name = ''
    return {
        "id" : task['id'],
        "name": task['name'],
        "contigs_file_name": contigs_file_name,
        "long_reads_file_name": long_reads_file_name,
        "kmer_size": task['kmer_size'],
        "distance": task['distance'],
        "step": task['step'],
        "min_links": task['min_links'],
        "max_ratio": task['max_ratio'],
        "min_contig_length": task['min_contig_length'],
        "input_time": task['input_time'],
        "output_time": task['output_time'],
        "progress": 1
    }

def get_scaffold_task_docfile(params, user):
    """get output docfile and file name for scaffold task"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return {}
    id = str(params['id'])
    if user.is_superuser:
        scaffold_task = ScaffoldTask.objects.filter(id=id).values()
    else:
        scaffold_task = ScaffoldTask.objects.filter(user_id=get_user_id(user), id=id).values()
    if len(scaffold_task) == 0:
        return {}
    file = Document.objects.filter(user_id=scaffold_task[0]['user_id'], id=scaffold_task[0]['output_file_id']).values()
    if len(file) == 0:
        return {}
    return {'docfile' : file[0]['docfile'], 'file_name': file[0]['file_name']}
