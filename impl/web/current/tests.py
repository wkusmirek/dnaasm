## @file current/tests.py
#  @brief current server status unit testing

import datetime
import django.test
from . import views

class CurrentModelTestCase(django.test.TestCase):
    """test module model"""

    pass

class CurrentViewTestCase(django.test.TestCase):
    """test module interface"""

    def test_01_time(self):
        """check server current time"""
        self.assertEqual(views.time({}),
                          str(datetime.datetime.utcnow().strftime("%Y-%m-%d %H:%M:%S")))

    def test_02_get(self):
        """check if service return non-empty dict"""
        returned_dictionary = views.get({})
        self.assertEqual(len(returned_dictionary), 2)



