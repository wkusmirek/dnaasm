## @file web/views.py
#  @brief main server interface to client

"""
main interface to server
"""

import json
import traceback
import logging
import django.http

#all modules should be imported here
import align
import align.views
import assembly
import assembly.views
import scaffold
import scaffold.views
import olc
import olc.views
import bst
import bst.views
import current
import current.views
import file
import file.views
import logs
import logs.views
import user
import user.views
import version
import version.views

## for test working server
def index(request):
    """for test working server"""
    return django.http.HttpResponse("DnaAsm server")

def ajax(request, module, function):
    """dispatch ajax requests"""
    logger = logging.getLogger('dnaasm.config.views')
    try:
        fun = getattr(getattr(globals()[str(module)], 'views'), str(function))
        logger.info('Request: ' + module + '/' + str(function))
        if request.method == 'GET':
            if module in ['logs', 'file', 'align'] or \
               module == 'bst'      and str(function) in ['get_user_assembly_tasks', 'get_assembly_task_docfile'] or \
               module == 'assembly' and str(function) in ['get_user_assembly_tasks', 'get_all_assembly_tasks', 'get_assembly_task_docfile'] or \
               module == 'olc'      and str(function) in ['get_user_olc_tasks', 'get_all_olc_tasks', 'get_olc_task_docfile'] or \
               module == 'scaffold' and str(function) in ['get_user_scaffold_tasks', 'get_all_scaffold_tasks', 'get_scaffold_task_docfile'] or \
               module == 'user'     and str(function) in ['get_user_mail', 'get_users', 'add_and_login_guest_user']:
                data = json.dumps(fun(request.GET, request.user))
            else:
                data = json.dumps(fun(request.GET))
        elif request.method == 'POST':
            if module == 'user' and str(function) in ['login_user', 'logout_user', 'add_and_login_guest_user', 'delete_user']:
                data = json.dumps(fun(request))
            elif module == 'user' and str(function) in ['set_user_mail', 'set_user_password']:
                data = json.dumps(fun(request.POST, request.user))
            elif module == 'assembly' and str(function) in ['break_assembly_task', 'insert', 'update', 'delete', 'delete_user_assembly_tasks']:
                data = json.dumps(fun(request.POST, request.user))
            elif module == 'olc' and str(function) in ['insert', 'delete']:
                data = json.dumps(fun(request.POST, request.user))
            elif module == 'bst' and str(function) in ['insert']:
                data = json.dumps(fun(request.POST, request.user))
            elif module == 'align' and str(function) in ['insert', 'delete', 'delete_user_align_tasks']:
                data = json.dumps(fun(request.POST, request.user))
            elif module == 'scaffold' and str(function) in ['break_scaffold_task', 'insert', 'delete', 'delete_user_scaffold_tasks']:
                data = json.dumps(fun(request.POST, request.user))
            elif module == 'file' and (str(function) == 'upload_file'):
                data = json.dumps(fun(request.FILES['file'], request.user))
            elif module == 'file' and str(function) in ['upload_example_files', 'delete_file', 'get_user_files', 'get_all_files', 'get_file_contents']:
                data = json.dumps(fun(request.POST, request.user))
            elif module == 'file' and str(function) in ['download_file']:
                response = fun(request.POST, request.user)
                logger.info('Response: ' + module + '/' + str(function))
                return response
            else:
                data = json.dumps(fun(request.POST))
        elif request.method == 'PUT':
            data = json.dumps(fun(request))
        logger.info('Response: ' + module + '/' + str(function))
        return django.http.HttpResponse(data, content_type='application/json')
    except Exception as e:
        logger.error("dnaasm ajax error: " + str(traceback.format_exc()))
        return django.http.HttpResponseNotFound("dnaasm ajax error: " + str(traceback.format_exc()))
    except:
        logger.error('dnaasm ajax system error')
        return django.http.HttpResponseNotFound("dnaasm ajax system error")
