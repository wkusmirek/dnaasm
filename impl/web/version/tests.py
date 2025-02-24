## @file version/tests.py
#  @brief version module unit testing

import django.test
from . import models
from . import views

class VersionModelTestCase(django.test.TestCase):
    """test version model"""

    def test_01_get_version_string(self):
        """test if getVersion return non-empty string"""
        self.assertTrue(len(models.get_version_string()) > 0)

    def test_02_get_db_name(self):
        """test if get_db_name return non-empty string"""
        self.assertTrue(len(models.get_db_name()) > 0)

    def test_03_get_db_user(self):
        """test if get_db_user return non-empty string"""
        self.assertTrue(len(models.get_db_user()) > 0)

    def test_04_get_db_password(self):
        """test if get_db_password return non-empty string"""
        self.assertTrue(len(models.get_db_password()) > 0)

    def test_05_get_db_version_string(self):
        """test if get_db_password return any output"""
        v = models.get_db_version_string()
        self.assertTrue(len(v) > 0)
        self.assertNotEqual(str(v), 'unknown')

    def test_06version_from_row(self):
        """check if database version string has 'ver'"""
        self.assertEqual(models.version_from_row(''), 'unknown')
        t = ('ver,xxx',)
        self.assertEqual(models.version_from_row(t), 'ver')

class VersionViewTestCase(django.test.TestCase):
    """test version interface"""

    def test_01_get(self):
        """check if get service return non-empty dict"""
        returned_dictionary = views.get({})
        self.assertEqual(len(returned_dictionary), 3)
