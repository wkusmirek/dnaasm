#!/bin/bash
pkill gunicorn
export LD_LIBRARY_PATH=/var/srv/dnaasm/cpp:${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=/var/srv/dnaasm/libs:${LD_LIBRARY_PATH}
chown www-data /tmp/dnaasm
chown www-data /tmp/dnaasm/dnaasm.log
chown -R www-data /var/tmp/dnaasm
sudo -u www-data sh -c "export LD_LIBRARY_PATH=/var/srv/dnaasm/cpp:${LD_LIBRARY_PATH};export LD_LIBRARY_PATH=/var/srv/dnaasm/libs:${LD_LIBRARY_PATH};gunicorn --env DJANGO_SETTINGS_MODULE=config.settings.prod --chdir /var/srv/dnaasm/build_web --timeout 0 --workers 1 --bind 127.0.0.1:50007 --daemon wsgi:application"
chmod 0774 /var/www/dnaasm/client/films/demo.mp4
