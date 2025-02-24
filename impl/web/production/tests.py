## @file production/tests.py
#  @brief production module unit testing

import django.test
from . import models
from . import views

class ProductionModelTestCase(django.test.TestCase):
    """test production model"""

    def test_01_get_production_host(self):
        """test if get_production_host return non-empty string"""
        self.assertTrue(len(models.get_production_host()) > 0)

    def test_02_get_production_port(self):
        """test if get_production_port return non-empty string"""
        self.assertTrue(len(models.get_production_port()) > 0)

    def test_03_get_production_string(self):
        """test if get_production_string return any output"""
        v = models.get_production_string()
        self.assertTrue(len(v) > 0)
        self.assertNotEqual(str(v), 'unknown')

class ProductionViewTestCase(django.test.TestCase):
    """test production interface"""

    def test_01_get_productions_params(self):
        """check if getProductionParams service return non-empty dict"""
        returned_dictionary = views.get({})
        self.assertEqual(len(returned_dictionary), 3)



