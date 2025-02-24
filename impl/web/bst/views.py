from django.core.exceptions import ObjectDoesNotExist
from datetime import datetime
import os

from dnaasmpy.views import start_bst_assembly_command, get_commands
from .models import BstAssemblyTask
from file.models import Document
from user.views import get_user_id
from django.conf import settings
from production.views import get

def get_user_assembly_tasks(params, user):
    """get task's progress and state"""
    if not user.is_authenticated:
        return {}

    commands_info = get_commands({'command_type' : 'BST_COMMAND_TYPE'})
    tasks = BstAssemblyTask.objects.filter(user=user).order_by('id')
    out_dict = {task.id: {} for task in tasks}

    for command in commands_info:
        for task in out_dict:
            if task['id'] == command['id']:
                task['progress'] = command['progress']
                task['state'] = command['state']
    return out_dict

def insert(params, user):
    """add assembly task"""
    if not user.is_authenticated:
        return {}

    try:
        if Document.objects.filter(file_name=params['task_name'], user=user).count() != 0:
            return {'status': 'error'}

        input_doc = Document.objects.get(file_name=params['input_file'], user=user)
        result_path = os.path.join(settings.PUBLIC_USERS_PREFIX, user.username, params['task_name'])
        result_doc = Document.objects.create(user=user, docfile=result_path, file_name=params['task_name'], input_time='')
        input_time = str(datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ"))

        new_task = BstAssemblyTask.objects.create(
                user=user,
                task_name=params['task_name'],
                input_file=input_doc,
                output_file=result_doc,
                word_length=params['word_length'],
                min_word_count=params['min_word_count'],
                max_word_count=params['max_word_count'],
                min_association=params['min_association'],
                path_width=params['path_width'], 
                min_similarity=params['min_similarity']
        )

        start_bst_assembly_command({
            'task_id': new_task.id,
            'word_length': params['word_length'],
            'min_word_count': params['min_word_count'],
            'max_word_count': params['max_word_count'],
            'min_association': params['min_association'],
            'path_width': params['path_width'],
            'input_file_path': input_doc.docfile.path,
            'output_file_name': params['task_name']
        })

    except ObjectDoesNotExist:
        return {'status': 'error'}
    except KeyError:
        return {}

    folder_path = os.path.dirname(result_doc.docfile.path)
    if not os.path.exists(folder_path):
        os.makedirs(folder_path)
    open(result_doc.docfile.path, 'w+').close()

    result_url = os.path.join(get({})['production_string'], result_path)
    return {'status': 'success',
            'task_id': new_task.id,
            'result_url': result_url}

def get_assembly_task_docfile(params, user):
    """get output docfile and file name for assembly task"""
    if not user.is_authenticated:
        return {}

    try:
        task = BstAssemblyTask.objects.get(id=params['id'], user=user)
        doc = Document.objects.get(bst_output=task)
    except:
        return {}

    return {'docfile': str(doc.docfile), 'file_name': str(doc.file_name)}
