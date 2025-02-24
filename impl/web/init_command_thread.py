##
# @file web/init_command_thread.py
# @brief dnaasm init thread for c++ commands

import time
from threading import Thread

class CommandThread(Thread):
    def __init__(self, begin_wait, interval_wait):
        Thread.__init__(self)
        self.begin_wait = begin_wait
        self.interval_wait = interval_wait
    def run(self):
        time.sleep(self.begin_wait)   # sleeping before import delete_guest_users
                                      # (libcalc.so required) to make available fast commands
                                      # 'python manage.py ...' without adding libcalc.so path to LD
        from dnaasmpy.views import serve_finished_commands
        while True:
            time.sleep(self.interval_wait)
            serve_finished_commands()


def init_command_thread():
    """Initializes thread for saving CommandManager results"""
    command_thread_object = CommandThread(30, 60)
    command_thread_object.setDaemon(True)
    command_thread_object.start()


global COMMAND_THREAD_INIT_DONE
## Boolean that specifies whether CommandThread was already make or not
COMMAND_THREAD_INIT_DONE = False
if not COMMAND_THREAD_INIT_DONE:
    init_command_thread()
