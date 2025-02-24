##
# @file web/initDeleteGuestUsersThread.py
# @brief dnaasm init thread for deleting guest users

from threading import Thread
import time
from datetime import timedelta

class DeleteGuestUsersThread(Thread):
    def __init__(self, begin_wait, interval_wait, offset_time):
        Thread.__init__(self)
        self.begin_wait = begin_wait
        self.interval_wait = interval_wait
        self.offset_time = offset_time
    def run(self):
        time.sleep(self.begin_wait)    # sleeping before import delete_guest_users
                                       # (libcalc.so required) to make available fast commands
                                       # 'python manage.py ...' without adding libcalc.so path to LD
        from user.views import delete_guest_users
        while True:
            time.sleep(self.interval_wait)
            delete_guest_users(self.offset_time)


def init_delete_guest_users_thread():
    """Initializes thread for deleting guest users"""
    delete_guest_users_thread_ob = DeleteGuestUsersThread(300, 86400, timedelta(days=7))
    #delete_guest_users_thread_ob = DeleteGuestUsersThread(10, 30, timedelta(minutes=1))
    delete_guest_users_thread_ob.setDaemon(True)
    delete_guest_users_thread_ob.start()


global DELETE_GUEST_USERS_THREAD_INIT_DONE
## Boolean that specifies whether DeleteGuestUsersThread was already make or not
DELETE_GUEST_USERS_THREAD_INIT_DONE = False
if not DELETE_GUEST_USERS_THREAD_INIT_DONE:
    init_delete_guest_users_thread()
