## @file logs/tests.py
#  @brief log file interface unit testing

import os
import django.test
from django.contrib.auth.models import User
from . import views
from . import models

class LogsModelTestCase(django.test.TestCase):
    """test module model"""

    def test_01_get_logs_location(self):
        """test if get_logs_location return non-empty string"""
        self.assertTrue(len(models.get_logs_location()) > 0)

    def test_02_get_logs_filename(self):
        """test if get_logs_filename return non-empty string"""
        self.assertTrue(len(models.get_logs_filename()) > 0)

class LaogsViewTestCase(django.test.TestCase):
    """test module interface"""

    def test_01_get_logs_local(self):
        """get server logs"""
        log_dir_path = './'
        log_file_name_1 = 'web_test_log.log'
        log_file_name_2 = 'web_test_log.log.1'
        log_file_name_3 = 'web_test_log.log.2'
        username = u'username'
        password = u'password'
        user = User.objects.create_user(username)
        user.set_password(password)
        user.save()
        log_file_1 = open(log_dir_path + log_file_name_1, 'w+')
        log_file_2 = open(log_dir_path + log_file_name_2, 'w+')
        log_file_3 = open(log_dir_path + log_file_name_3, 'w+')
        log_file_1.close()
        log_file_2.close()
        log_file_3.close()
        self.assertEqual(views.get_logs_local({'number_of_lines' : 3}, user, log_dir_path, log_file_name_1), u'')
        log_file_1 = open(log_dir_path + log_file_name_1, 'r+')
        log_file_1.write('aaa\nbbb\n')
        log_file_1.close()
        self.assertEqual(views.get_logs_local({'number_of_lines' : 1}, user, log_dir_path, log_file_name_1), u'bbb\n')
        self.assertEqual(views.get_logs_local({'number_of_lines' : 3}, user, log_dir_path, log_file_name_1), u'bbb\naaa\n')
        log_file_2 = open(log_dir_path + log_file_name_2, 'r+')
        log_file_3 = open(log_dir_path + log_file_name_3, 'r+')
        log_file_2.write('ccc\nddd\n')
        log_file_3.write('eee\n')
        log_file_2.close()
        log_file_3.close()
        self.assertEqual(views.get_logs_local({'number_of_lines' : 7}, user, log_dir_path, log_file_name_1), u'bbb\naaa\nddd\nccc\neee\n')
        self.assertEqual(os.path.isfile(log_dir_path + log_file_name_1 + '.' + username), False)
        self.assertEqual(os.path.isfile(log_dir_path + log_file_name_2 + '.' + username), False)
        self.assertEqual(os.path.isfile(log_dir_path + log_file_name_3 + '.' + username), False)
        os.remove(log_dir_path + log_file_name_1)
        os.remove(log_dir_path + log_file_name_2)
        os.remove(log_dir_path + log_file_name_3)
        User.objects.all().delete()
