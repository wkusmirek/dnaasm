## @file logs/views.py
#  @brief log file interface to client

"""
log interface to client
"""

import os
import shutil
from . import models
#from django.conf import settings
#import logging

## Logger web localization
LOG_WEB_LOC = models.get_logs_location()
## Logger file name
LOG_FILE_NAME = models.get_logs_filename()

#two functions in order to have chance to test get_logs_local function without destroying actual logs on server
def get_logs(params, user):
    return get_logs_local(params, user, LOG_WEB_LOC, LOG_FILE_NAME)

def get_logs_local(params, user, log_web_loc, log_file_name):
    """get server logs"""
    if not user.is_authenticated:
        return ''
    number_of_lines = int(params['number_of_lines'])
    tmp_files = []
    for actual_file in os.listdir(log_web_loc):
        if actual_file.startswith(log_file_name):# and not actual_file.endswith(user.username):
            shutil.copyfile(log_web_loc + actual_file, log_web_loc + actual_file + '.' + user.username)
            tmp_files.append(log_web_loc + actual_file + '.' + user.username)
    tmp_files.sort()
    tmp_files.sort(key=len)

    logs = ''
    i = 0

    for tmp_file in tmp_files:
        for line in reversed(open(tmp_file).readlines()):
            logs = logs + line.rstrip() + "\n"
            i = i + 1
            if i == number_of_lines:
                break
        if i == number_of_lines:
            break

    for tmp_file in tmp_files:
        os.remove(tmp_file)

    return logs
