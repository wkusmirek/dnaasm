## @file version/models.py
#  @brief server version model

"""
version state module. Return database version, database connecting strings and application build version
"""

import logging
import platform
import django
from django.db import connection
from . import version_gen

def get_web_srv_prefix():
    return str(version_gen.WEB_SRV_PREFIX)

def get_version_string():
    """version string, for displaying in client"""
    return str(version_gen.DNAASM_VER_MAJOR) + "." + str(version_gen.DNAASM_VER_MINOR) + "." + str(version_gen.DNAASM_VER_COMPILATION) + "; Python: " + str(platform.python_version()) + "; Arch: " + str(platform.processor()) + "; Os: " + str(platform.system()) + " " + str(platform.version()) + "; Django: " + str(django.get_version())


def get_db_name():
    """database name"""
    return version_gen.DB_NAME

def get_db_user():
    """database user"""
    return version_gen.DB_USER

def get_db_password():
    """database password"""
    return version_gen.DB_PASSWORD

def version_from_row(row):
    """helping function - parse row to return the correct version"""
    ver = 'unknown'
    try:
        ver = str(row[0].split(',')[0])
    except:
        logger = logging.getLogger('dnaasm.version.models')
        logger.error('Unknown version')
        pass
    return ver

def get_db_version_string():
    """database version"""
    cursor = connection.cursor()
    cursor.execute("select version();")
    row = cursor.fetchone()
    return version_from_row(row)
