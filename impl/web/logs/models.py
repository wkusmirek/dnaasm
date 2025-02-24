## @file logs/models.py
#  @brief server logs model

"""
logs state module. Return logs location and file name
"""

from . import logs_gen

def get_logs_location():
    """logs location"""
    return logs_gen.LOG_WEB_LOC

def get_logs_filename():
    """logs file name"""
    return logs_gen.LOG_FILE_NAME
