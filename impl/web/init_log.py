##
# @file web/initlog.py
# @brief dnaasm init logger

import logging
import os
import logging.handlers
from logs import models

## Logger web localization
LOG_WEB_LOC = models.get_logs_location()
## Logger file name
LOG_FILE_NAME = models.get_logs_filename()

def init_logging():
    """Initializes main logger""" 
    logger = logging.getLogger('dnaasm')
    logger.setLevel(logging.INFO)
    if not os.path.exists(LOG_WEB_LOC):
        os.makedirs(LOG_WEB_LOC)
    handler_file = logging.handlers.RotatingFileHandler(LOG_WEB_LOC + LOG_FILE_NAME,
                                                        "a", 1024 * 1024, 5)
    handler_file.setLevel(logging.DEBUG)
    handler_file.setFormatter(logging.Formatter('%(asctime)s %(levelname)s %(name)s '
                                                '[%(lineno)s] - %(message)s'))
    logger.addHandler(handler_file)

global LOGGING_INIT_DONE
## Boolean that specifies whether logging was already initialized or not
LOGGING_INIT_DONE = False
if not LOGGING_INIT_DONE:
    init_logging()
    ## Main application logger
    logger = logging.getLogger('dnaasm.initlog')
    logger.info('Server started')
    LOGGING_INIT_DONE = True
