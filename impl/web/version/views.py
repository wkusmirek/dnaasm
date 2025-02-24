## @file version/views.py
#  @brief server version interface to client

"""
version interface module. Return database version, database connecting strings and application build version
"""

from . import models

def get(params):
    """versions"""
    return {
        "paramsVer" : 1,
        "server": models.get_version_string(),
        "database": models.get_db_version_string(),
   }
