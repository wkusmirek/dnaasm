# @file assembly/views.py
#  @brief database interface to client for assembly task table

"""
database interface to client
"""

import datetime
import os
from user.views import get_username
from assembly.models import AssemblyTask
from file.models import Document
from django.conf import settings
from django.db.models import Q
from production.views import get

def break_assembly_task(params, user):
    """break assembly task"""
    from user.views import get_user_id
    from dnaasmpy.views import break_command
    if not user.is_authenticated:
        return False
    id = str(params['id'])
    task = AssemblyTask.objects.filter(id=id)
    if len(task) == 0 or (task.values('user_id')[0]['user_id'] != get_user_id(user) and not user.is_superuser):
        return False
    break_command({'task_id' : id, 'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
    return True

def insert(params, user):
    """insert sth into a database"""
    from user.views import get_user_id
    from dnaasmpy.views import start_assembly_command
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
    i1_1_file_name = str(params['i1_1_file_name'])
    i1_2_file_name = str(params['i1_2_file_name'])
    i1_1_id = ''
    i1_2_id = ''
    i1_1_path = ''
    i1_2_path = ''
    o1_1_file_name = str(params['o1_1_file_name'])
    o1_2_file_name = str(params['o1_2_file_name'])
    o1_1_id = ''
    o1_2_id = ''
    o1_1_path = ''
    o1_2_path = ''
    k = str(params['k'])
    genome_length = str(params['genome_length'])
    insert_size_mean_inward = str(params['insert_size_mean_inward'])
    insert_size_std_dev_inward = str(params['insert_size_std_dev_inward'])
    insert_size_mean_outward = str(params['insert_size_mean_outward'])
    insert_size_std_dev_outward = str(params['insert_size_std_dev_outward'])
    paired_reads_algorithm = str(params['paired_reads_algorithm'])
    quality_threshold = str(params['quality_threshold'])
    bfcounter_threshold = str(params['bfcounter_threshold'])
    single_edge_counter_threshold = str(params['single_edge_counter_threshold'])
    paired_reads_pet_threshold_from = str(params['paired_reads_pet_threshold_from'])
    paired_reads_pet_threshold_to = str(params['paired_reads_pet_threshold_to'])
    paired_reads_mp_threshold_from = str(params['paired_reads_mp_threshold_from'])
    paired_reads_mp_threshold_to = str(params['paired_reads_mp_threshold_to'])
    correct = str(params['correct'])
    result_notification = str(params['result_notification'])
    mail_address = str(params['mail_address'])
    input_time = str(datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"))
    i1_1 = Document.objects.filter(file_name=i1_1_file_name, user_id=user_id)
    if len(i1_1) != 0:
        doc_i1_1 = i1_1.values('docfile')[0]['docfile']
        i1_1_id = i1_1.values('id')[0]['id']
        i1_1_path = settings.MEDIA_ROOT + '/' + doc_i1_1
    i1_2 = Document.objects.filter(file_name=i1_2_file_name, user_id=user_id)
    if len(i1_2) != 0:
        doc_i1_2 = i1_2.values('docfile')[0]['docfile']
        i1_2_id = i1_2.values('id')[0]['id']
        i1_2_path = settings.MEDIA_ROOT + '/' + doc_i1_2
    o1_1 = Document.objects.filter(file_name=o1_1_file_name, user_id=user_id)
    if len(o1_1) != 0:
        doc_o1_1 = o1_1.values('docfile')[0]['docfile']
        o1_1_id = o1_1.values('id')[0]['id']
        o1_1_path = settings.MEDIA_ROOT + '/' + doc_o1_1
    o1_2 = Document.objects.filter(file_name=o1_2_file_name, user_id=user_id)
    if len(o1_2) != 0:
        doc_o1_2 = o1_2.values('docfile')[0]['docfile']
        o1_2_id = o1_2.values('id')[0]['id']
        o1_2_path = settings.MEDIA_ROOT + '/' + doc_o1_2
    new_assembly_task = AssemblyTask.objects.create(
            user_id=user_id,
            name=name,
            i1_1_id=i1_1_id,
            i1_2_id=i1_2_id,
            o1_1_id=o1_1_id,
            o1_2_id=o1_2_id,
            output_file_id=newdoc.id,
            k=k,
            genome_length=genome_length,
            insert_size_mean_inward=insert_size_mean_inward,
            insert_size_std_dev_inward=insert_size_std_dev_inward,
            insert_size_mean_outward=insert_size_mean_outward,
            insert_size_std_dev_outward=insert_size_std_dev_outward,
            quality_threshold=quality_threshold,
            bfcounter_threshold=bfcounter_threshold,
            single_edge_counter_threshold=single_edge_counter_threshold,
            paired_reads_pet_threshold_from=paired_reads_pet_threshold_from,
            paired_reads_pet_threshold_to=paired_reads_pet_threshold_to,
            paired_reads_mp_threshold_from=paired_reads_mp_threshold_from,
            paired_reads_mp_threshold_to=paired_reads_mp_threshold_to,
            paired_reads_algorithm=paired_reads_algorithm,
            correct=(correct == 'true'),
            result_notification=(result_notification == 'true'),
            mail_address=mail_address,
            input_time=input_time,
            output_time=''
    )
    start_assembly_command({
        'task_id': new_assembly_task.id,
        'k':k,
        'genome_length':genome_length,
        'insert_size_mean_inward':insert_size_mean_inward,
        'insert_size_std_dev_inward':insert_size_std_dev_inward,
        'insert_size_mean_outward':insert_size_mean_outward,
        'insert_size_std_dev_outward':insert_size_std_dev_outward,
        'quality_threshold':quality_threshold,
        'bfcounter_threshold':bfcounter_threshold,
        'single_edge_counter_threshold':single_edge_counter_threshold,
        'paired_reads_pet_threshold_from':paired_reads_pet_threshold_from,
        'paired_reads_pet_threshold_to':paired_reads_pet_threshold_to,
        'paired_reads_mp_threshold_from':paired_reads_mp_threshold_from,
        'paired_reads_mp_threshold_to':paired_reads_mp_threshold_to,
        'i1_1':i1_1_path,
        'i1_2':i1_2_path,
        'o1_1':o1_1_path,
        'o1_2':o1_2_path,
        'paired_reads_algorithm':paired_reads_algorithm,
        'correct':correct,
        'output_file_name':name
    })  #from dnaasmpy.views
    result_url = get({})['production_string'] + '/' + result_docfile

    return {
        'status' : 'success',
        'msg' : 'New short-read assembly task was added successfully.',
        'result_url' : result_url,
        'task_id' : new_assembly_task.id
    }

def delete(params, user):
    """remove sth from a database"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return False
    id = str(params['id'])
    task = AssemblyTask.objects.filter(id=id)
    if len(task) == 0 or (task.values('user_id')[0]['user_id'] != get_user_id(user) and not user.is_superuser):
        return False
    task.delete()
    return True

def is_file_used(file_id):
    """check if file with id equal to file_id is used in any assembly task"""
    tasks = AssemblyTask.objects.filter(Q(i1_1_id=file_id) | Q(i1_2_id=file_id) | Q(o1_1_id=file_id) | Q(o1_2_id=file_id))
    if len(tasks) == 0:
        return False
    else:
        return True

def delete_user_assembly_tasks(user_id):
    """remove all tasks for user with user_id from a database"""
    AssemblyTask.objects.filter(user_id=user_id).delete()
    return True

def update(params, user):
    """update sth in a database"""
    from user.views import get_user_id
    from dnaasmpy.views import start_assembly_command
    if not user.is_authenticated:
        return
    user_id = get_user_id(user)
    id = str(params['id'])
    task = AssemblyTask.objects.filter(id=id)
    if len(task) == 0:
        return False
    from file.views import save_content_to_file
    save_content_to_file(task.values('output_file_id')[0]['output_file_id'], '')
    task_name = task.values('name')[0]['name']
    if not os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username):
        os.makedirs(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username)
    output_file = open(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + user.username + '/' + task_name, 'w+')
    output_file.close()
    result_docfile = settings.PUBLIC_USERS_PREFIX + '/' + user.username + '/' + task_name
    document = Document.objects.filter(user_id=user_id, docfile=result_docfile, file_name=task_name)
    k = str(params['k'])
    genome_length = str(params['genome_length'])
    insert_size_mean_inward = str(params['insert_size_mean_inward'])
    insert_size_std_dev_inward = str(params['insert_size_std_dev_inward'])
    insert_size_mean_outward = str(params['insert_size_mean_outward'])
    insert_size_std_dev_outward = str(params['insert_size_std_dev_outward'])
    quality_threshold = str(params['quality_threshold'])
    bfcounter_threshold = str(params['bfcounter_threshold'])
    single_edge_counter_threshold = str(params['single_edge_counter_threshold'])
    paired_reads_pet_threshold_from = str(params['paired_reads_pet_threshold_from'])
    paired_reads_pet_threshold_to = str(params['paired_reads_pet_threshold_to'])
    paired_reads_mp_threshold_from = str(params['paired_reads_mp_threshold_from'])
    paired_reads_mp_threshold_to = str(params['paired_reads_mp_threshold_to'])
    paired_reads_algorithm = str(params['paired_reads_algorithm'])
    correct = int(str(params['correct']) == 'true')
    result_notification = int(str(params['result_notification']) == 'true')
    mail_address = str(params['mail_address'])
    input_time = str(datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"))
    i1_1_file_name = str(params['i1_1_file_name'])
    i1_2_file_name = str(params['i1_2_file_name'])
    i1_1_id = ''
    i1_2_id = ''
    i1_1_path = ''
    i1_2_path = ''
    o1_1_file_name = str(params['o1_1_file_name'])
    o1_2_file_name = str(params['o1_2_file_name'])
    o1_1_id = ''
    o1_2_id = ''
    o1_1_path = ''
    o1_2_path = ''
    i1_1 = Document.objects.filter(file_name=i1_1_file_name, user_id=user_id)
    if len(i1_1) != 0:
        doc_i1_1 = i1_1.values('docfile')[0]['docfile']
        i1_1_id = i1_1.values('id')[0]['id']
        i1_1_path = settings.MEDIA_ROOT + '/' + doc_i1_1
    i1_2 = Document.objects.filter(file_name=i1_2_file_name, user_id=user_id)
    if len(i1_2) != 0:
        doc_i1_2 = i1_2.values('docfile')[0]['docfile']
        i1_2_id = i1_2.values('id')[0]['id']
        i1_2_path = settings.MEDIA_ROOT + '/' + doc_i1_2
    o1_1 = Document.objects.filter(file_name=o1_1_file_name, user_id=user_id)
    if len(o1_1) != 0:
        doc_o1_1 = o1_1.values('docfile')[0]['docfile']
        o1_1_id = o1_1.values('id')[0]['id']
        o1_1_path = settings.MEDIA_ROOT + '/' + doc_o1_1
    o1_2 = Document.objects.filter(file_name=o1_2_file_name, user_id=user_id)
    if len(o1_2) != 0:
        doc_o1_2 = o1_2.values('docfile')[0]['docfile']
        o1_2_id = o1_2.values('id')[0]['id']
        o1_2_path = settings.MEDIA_ROOT + '/' + doc_o1_2
    if int(k) != task.values('k')[0]['k'] or int(genome_length) != task.values('genome_length')[0]['genome_length'] or float(insert_size_mean_inward) != task.values('insert_size_mean_inward')[0]['insert_size_mean_inward'] or float(insert_size_std_dev_inward) != task.values('insert_size_std_dev_inward')[0]['insert_size_std_dev_inward'] or float(insert_size_mean_outward) != task.values('insert_size_mean_outward')[0]['insert_size_mean_outward'] or float(insert_size_std_dev_outward) != task.values('insert_size_std_dev_outward')[0]['insert_size_std_dev_outward'] or int(quality_threshold) != task.values('quality_threshold')[0]['quality_threshold'] or int(bfcounter_threshold) != task.values('bfcounter_threshold')[0]['bfcounter_threshold'] or int(single_edge_counter_threshold) != task.values('single_edge_counter_threshold')[0]['single_edge_counter_threshold'] or int(paired_reads_pet_threshold_from) != task.values('paired_reads_pet_threshold_from')[0]['paired_reads_pet_threshold_from'] or int(paired_reads_pet_threshold_to) != task.values('paired_reads_pet_threshold_to')[0]['paired_reads_pet_threshold_to'] or int(paired_reads_mp_threshold_from) != task.values('paired_reads_mp_threshold_from')[0]['paired_reads_mp_threshold_from'] or int(paired_reads_mp_threshold_to) != task.values('paired_reads_mp_threshold_to')[0]['paired_reads_mp_threshold_to'] or paired_reads_algorithm != task.values('paired_reads_algorithm')[0]['paired_reads_algorithm'] or correct != task.values('correct')[0]['correct'] or i1_1_id != task.values('i1_1_id')[0]['i1_1_id'] or i1_2_id != task.values('i1_2_id')[0]['i1_2_id'] or o1_1_id != task.values('o1_1_id')[0]['o1_1_id'] or o1_2_id != task.values('o1_2_id')[0]['o1_2_id']:
        AssemblyTask.objects.filter(id=id).update(i1_1_id=i1_1_id, i1_2_id=i1_2_id, o1_1_id=o1_1_id, o1_2_id=o1_2_id, output_file_id=document.values('id')[0]['id'], k=k, genome_length=genome_length, insert_size_mean_inward=insert_size_mean_inward, insert_size_std_dev_inward=insert_size_std_dev_inward, insert_size_mean_outward=insert_size_mean_outward, insert_size_std_dev_outward=insert_size_std_dev_outward, quality_threshold=quality_threshold, bfcounter_threshold=bfcounter_threshold, single_edge_counter_threshold=single_edge_counter_threshold, paired_reads_pet_threshold_from=paired_reads_pet_threshold_from, paired_reads_pet_threshold_to=paired_reads_pet_threshold_to, paired_reads_mp_threshold_from=paired_reads_mp_threshold_from, paired_reads_mp_threshold_to=paired_reads_mp_threshold_to, paired_reads_algorithm=paired_reads_algorithm, input_time=input_time, output_time='', correct=correct, result_notification=result_notification, mail_address=mail_address)
        start_assembly_command({'task_id': int(id), 'k':k, 'genome_length':genome_length, 'insert_size_mean_inward':insert_size_mean_inward, 'insert_size_std_dev_inward':insert_size_std_dev_inward, 'insert_size_mean_outward':insert_size_mean_outward, 'insert_size_std_dev_outward':insert_size_std_dev_outward, 'quality_threshold':quality_threshold, 'bfcounter_threshold':bfcounter_threshold, 'single_edge_counter_threshold':single_edge_counter_threshold, 'paired_reads_pet_threshold_from':paired_reads_pet_threshold_from, 'paired_reads_pet_threshold_to':paired_reads_pet_threshold_to, 'paired_reads_mp_threshold_from':paired_reads_mp_threshold_from, 'paired_reads_mp_threshold_to':paired_reads_mp_threshold_to, 'paired_reads_algorithm':paired_reads_algorithm, 'i1_1':i1_1_path, 'i1_2':i1_2_path, 'o1_1':o1_1_path, 'o1_2':o1_2_path, 'correct':str(params['correct']), 'output_file_name':task_name})
    result_url = get({})['production_string'] + '/' + result_docfile
    return {'status' : 'success', 'msg' : 'New task was added successfully.', 'result_url' : result_url}


def get_user_assembly_tasks(params, user):
    """return all assembly tasks for specified user"""
    from user.views import get_user_id
    from dnaasmpy.views import get_commands
    if not user.is_authenticated:
        return
    user_id = get_user_id(user)
    commands_info = get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
    tasks = AssemblyTask.objects.all().order_by("id").values()
    out_dict = dict()
    i = 0
    for task in tasks:
        if task['user_id'] == user_id:
            out_dict[i] = make_dict_from_task(task)
            i = i + 1
    for m in commands_info:
        for k in out_dict:
            if out_dict[int(k)]['id'] == commands_info[int(m)]['id']:
                out_dict[int(k)]['progress'] = commands_info[int(m)]['progress']
                out_dict[int(k)]['state'] = commands_info[int(m)]['state']
    return out_dict

def get_all_assembly_tasks(params, user):
    """return all assembly tasks for all users"""
    from dnaasmpy.views import get_commands
    out_dict = dict()
    if user.is_superuser:
        commands_info = get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        tasks = AssemblyTask.objects.all().order_by("id").values()
        i = 0
        for task in tasks:
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
    i1_1 = Document.objects.filter(id=task['i1_1_id']).values()
    if len(i1_1) != 0:
        i1_1_file_name = i1_1[0]['file_name']
    else:
        i1_1_file_name = ''
    i1_2 = Document.objects.filter(id=task['i1_2_id']).values()
    if len(i1_2) != 0:
        i1_2_file_name = i1_2[0]['file_name']
    else:
        i1_2_file_name = ''
    o1_1 = Document.objects.filter(id=task['o1_1_id']).values()
    if len(o1_1) != 0:
        o1_1_file_name = o1_1[0]['file_name']
    else:
        o1_1_file_name = ''
    o1_2 = Document.objects.filter(id=task['o1_2_id']).values()
    if len(o1_2) != 0:
        o1_2_file_name = o1_2[0]['file_name']
    else:
        o1_2_file_name = ''
    return {"id" : task['id'], "name": task['name'], "i1_1_file_name": i1_1_file_name, "i1_2_file_name": i1_2_file_name, "o1_1_file_name": o1_1_file_name, "o1_2_file_name": o1_2_file_name, "k": task['k'], "genome_length": task['genome_length'], "insert_size_mean_inward": task['insert_size_mean_inward'], "insert_size_std_dev_inward": task['insert_size_std_dev_inward'], "insert_size_mean_outward": task['insert_size_mean_outward'], "insert_size_std_dev_outward": task['insert_size_std_dev_outward'], "quality_threshold": task['quality_threshold'], "bfcounter_threshold": task['bfcounter_threshold'], "single_edge_counter_threshold": task['single_edge_counter_threshold'], "paired_reads_pet_threshold_from": task['paired_reads_pet_threshold_from'], "paired_reads_pet_threshold_to": task['paired_reads_pet_threshold_to'], "paired_reads_mp_threshold_from": task['paired_reads_mp_threshold_from'], "paired_reads_mp_threshold_to": task['paired_reads_mp_threshold_to'], "paired_reads_algorithm": task['paired_reads_algorithm'], "input_time": task['input_time'], "output_time": task['output_time'], "correct": task['correct'], "progress": 1}

def get_assembly_task_docfile(params, user):
    """get output docfile and file name for assembly task"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return {}
    id = str(params['id'])
    if user.is_superuser:
        assembly_task = AssemblyTask.objects.filter(id=id).values()
    else:
        assembly_task = AssemblyTask.objects.filter(user_id=get_user_id(user), id=id).values()
    if len(assembly_task) == 0:
        return {}
    file = Document.objects.filter(user_id=assembly_task[0]['user_id'], id=assembly_task[0]['output_file_id']).values()
    if len(file) == 0:
        return {}
    return {'docfile' : file[0]['docfile'], 'file_name': file[0]['file_name']}
