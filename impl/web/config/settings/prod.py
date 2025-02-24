## @file web/config/settings/prod.py
#  @brief Django prod settings file

"""
Django prod settings file
"""

from .base import *

DEBUG = False

import init_log
import copy_example_files
import init_command_thread
import init_delete_guest_users_thread
