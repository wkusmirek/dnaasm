## @file mail/views.py
#  @brief sending mails interface to client

import logging
import re
from django.core.mail import send_mail
from production.views import get

def send_job_notification_mail(submit_task_time, to_mail_list, docfile):
    """send mail with notification, that task is finished"""
    submit_task_time = submit_task_time.replace("T", " ")
    formatted_submit_task_time = re.sub("[^0-9|:| |-]", "", submit_task_time)
    result_url = get({})['production_string'] + '/' + docfile
    try:
        if formatted_submit_task_time == '':
            send_mail('dnaasm task has finished', 'The job you submitted to dnaasm has finished.\n\nYou can download the output from ' + result_url, 'dnaasm@gmail.com', to_mail_list, fail_silently=False)
        else:
            send_mail('dnaasm task has finished', 'The job you submitted to dnaasm on ' + formatted_submit_task_time + ' GMT has finished.\n\nYou can download the output from ' + result_url, 'dnaasm@gmail.com', to_mail_list, fail_silently=False)
        return True
    except:
        logger = logging.getLogger('dnaasm.mail.views')
        logger.error('Error while sending email.')
        return False





