##
# @file web/copy_example_files.py
# @brief copy files with example files to settings.EXAMPLE_FILES_MEDIA_ROOT

import os
import shutil
from django.conf import settings

def copy_example_files():
    """Copies files with example data to settings.EXAMPLE_FILES_MEDIA_ROOT"""
    if not os.path.exists(settings.EXAMPLE_FILES_MEDIA_ROOT):
        os.makedirs(settings.EXAMPLE_FILES_MEDIA_ROOT)
    if not os.path.exists(settings.EXAMPLE_FILES_ROOT):
        print(settings.EXAMPLE_FILES_ROOT + ' not exist')
        return False
    src_files = os.listdir(settings.EXAMPLE_FILES_ROOT)
    for file_name in src_files:
        full_file_name = os.path.join(settings.EXAMPLE_FILES_ROOT, file_name)
        if os.path.isfile(full_file_name):
            shutil.copy(full_file_name, settings.EXAMPLE_FILES_MEDIA_ROOT)


global COPY_EXAMPLE_FILES_DONE
## Boolean that specifies whether example files was already copied or not
COPY_EXAMPLE_FILES_DONE = False
if not COPY_EXAMPLE_FILES_DONE:
    copy_example_files()
