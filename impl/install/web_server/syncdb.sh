#!/bin/bash
export LD_LIBRARY_PATH=/var/srv/dnaasm/cpp:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=/var/srv/dnaasm/libs:${LD_LIBRARY_PATH}
python3 /var/srv/dnaasm/build_web/manage.py makemigrations --settings=config.settings.prod dnaasmpy version current assembly align scaffold user file olc bst
python3 /var/srv/dnaasm/build_web/manage.py migrate --settings=config.settings.prod
