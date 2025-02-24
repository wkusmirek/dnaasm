## @file production/models.py
#  @brief server production model

"""
production state module. Return production host and production port
"""

from . import production_gen

def get_production_host():
    """production host"""
    return production_gen.PRODUCTION_HOST

def get_production_port():
    """production port"""
    return production_gen.PRODUCTION_PORT

def get_production_string():
    """production string"""
    if production_gen.PRODUCTION_PORT.isdigit():
        return 'http://' + production_gen.PRODUCTION_HOST + ':' +production_gen.PRODUCTION_PORT
    else:
        return 'http://' + production_gen.PRODUCTION_HOST



