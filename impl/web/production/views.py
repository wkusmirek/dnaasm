## @file production/views.py
#  @brief server production interface to client

"""
production interface module. Return production host and production port
"""

from . import models

def get(params):
    """gets production parameters"""
    return {
        "host": models.get_production_host(),
        "port": models.get_production_port(),
        "production_string": models.get_production_string(),
   }
