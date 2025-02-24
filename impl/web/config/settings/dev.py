## @file web/config/settings/dev.py
#  @brief Django dev settings file

"""
Django dev settings file
"""

from .base import *

DEBUG = True

INSTALLED_APPS += (
    'django_jenkins',
)

JENKINS_TASKS = (
    'django_jenkins.tasks.run_pyflakes',
)

import init_log
import copy_example_files
import init_command_thread
import init_delete_guest_users_thread
