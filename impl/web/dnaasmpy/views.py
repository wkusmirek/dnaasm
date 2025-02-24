## @file dnaasmpy/views.py
#  @brief calculation library interface to client

"""
calc library interface to client

export calculation results to client
"""

import datetime
from user.views import get_user_mail
from assembly.models import AssemblyTask
from align.models import AlignTask
from scaffold.models import ScaffoldTask
from bst.models import BstAssemblyTask
from mail.views import send_job_notification_mail
from file.views import get_docfile
from . import dnaasmpy

def break_command(params):
    """break command"""
    task_id = str(params['task_id'])
    command_type = str(params['command_type'])
    cmdmgr = dnaasmpy.CommandManager()
    command_ids = cmdmgr.getIds()
    for command_id in command_ids:
        if str(cmdmgr.getState(command_id)) != 'DONE' \
            and str(cmdmgr.getCommandType(command_id)) == command_type \
            and str(cmdmgr.getTaskId(command_id)) == task_id:
            cmdmgr.breakCmd(command_id)
            return True
    return False

def start_align_command(params):
    """start new align command"""
    task_id = params['task_id']
    cmdmgr = dnaasmpy.CommandManager()
    cmd_id = cmdmgr.startAlign(task_id, params)
    return cmd_id

def start_assembly_command(params):
    """start new assembly command"""
    task_id = params.pop('task_id')
    cmdmgr = dnaasmpy.CommandManager()
    cmd_id = cmdmgr.startAssembly(task_id, params)
    return cmd_id

def start_olc_assembly_command(params):
    """start new olc assembly command"""
    task_id = params.pop('task_id')
    cmdmgr = dnaasmpy.CommandManager()
    cmd_id = cmdmgr.startOlcAssembly(task_id, params)
    return cmd_id

def start_scaffold_command(params):
    """start new scaffold command"""
    task_id = params.pop('task_id')
    cmdmgr = dnaasmpy.CommandManager()
    cmd_id = cmdmgr.startScaffold(task_id, params)
    return cmd_id

def start_bst_assembly_command(params):
    """start new bst command"""
    task_id = params.pop('task_id')
    cmdmgr = dnaasmpy.CommandManager()
    cmd_id = cmdmgr.startBstAssembly(task_id, params)
    return cmd_id

def get_commands(params):
    """return the commands descriptors"""
    cmdmgr = dnaasmpy.CommandManager()
    command_type = str(params['command_type'])
    ids = cmdmgr.getIds()
    out_dict = dict()
    k = 0
    for i in ids:
        if str(cmdmgr.getState(i)) != 'DONE':
            if str(cmdmgr.getCommandType(i)) == command_type:
                out_dict[k] = {
                    "progress": float(cmdmgr.getProgress(i)),
                    "id": cmdmgr.getTaskId(i),
                    "state": str(cmdmgr.getState(i))
                }
                k = k+1
    serve_finished_commands()
    return out_dict

def serve_finished_commands():
    """serves (send mail, save result to file etc.) finished commands"""
    from file.views import save_content_to_file
    cmdmgr = dnaasmpy.CommandManager()
    ids = cmdmgr.getIds()
    for i in ids:
        if str(cmdmgr.getState(i)) == 'DONE' and not cmdmgr.getIsSavedInDatabase(i):
            task_id = cmdmgr.getTaskId(i)
            output = cmdmgr.getResult(i)
            if str(cmdmgr.getCommandType(i)) == 'ASSEMBLY_COMMAND_TYPE':
                # FIXME:
                # Ugly workaround here
                task = AssemblyTask.objects.filter(id=task_id)
                if len(task):
                # find and start related ScaffoldTask if such exists
                    related_scaffold_task = ScaffoldTask.objects.all().filter(assembly_task=task[0])
                    if len(related_scaffold_task) != 0:
                        s_task = related_scaffold_task[0]
                        start_scaffold_command({
                            'task_id': s_task.id,
                            'kmer_size':str(s_task.kmer_size),
                            'distance':str(s_task.distance),
                            'step':str(s_task.step),
                            'min_links':str(s_task.min_links),
                            'max_ratio':str(s_task.max_ratio),
                            'min_contig_length':str(s_task.min_contig_length),
                            'contigs_file_path':s_task.contigs_file.docfile.path,
                            'long_reads_file_path':s_task.long_reads_file.docfile.path,
                            'output_file_name':s_task.name
                        })
            elif str(cmdmgr.getCommandType(i)) == 'ALIGN_COMMAND_TYPE':
                task = AlignTask.objects.filter(id=task_id)
            elif str(cmdmgr.getCommandType(i)) == 'SCAFFOLD_COMMAND_TYPE':
                task = ScaffoldTask.objects.filter(id=task_id)
            elif str(cmdmgr.getCommandType(i)) == 'BST_COMMAND_TYPE':
                task = BstAssemblyTask.objects.filter(id=task_id)
            else:
                return
            task.update(output_time=str(datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ")))
            if len(task.values()) > 0:
                output_file_id = (task.values())[0]['output_file_id']
                save_content_to_file(output_file_id, output)
                result_notification = (task.values())[0].get('result_notification', None)
                if result_notification is True:
                    #send_job_notification_mail((task.values())[0]['input_time'], [get_user_mail((task.values())[0]['user_id'])], get_docfile(output_file_id))
                    send_job_notification_mail((task.values())[0]['input_time'],
                                               [(task.values())[0]['mail_address']],
                                               get_docfile(output_file_id))
            cmdmgr.setIsSavedInDatabase(i, True)
    return
