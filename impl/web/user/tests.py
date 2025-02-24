## @file user/tests.py
#  @brief web interface for user operations

import os
import re
import time
import django.test
from django.contrib.auth.models import User
from assembly.models import AssemblyTask
from file.models import Document
from django.conf import settings
from django.test.client import RequestFactory
from . import views

class UserModelTestCase(django.test.TestCase):
    """test module model"""
    pass

class UserViewTestCase(django.test.TestCase):
    """test module interface"""

    def setUp(self):
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT)
        self.username0 = u'username0'
        self.password0 = u'password0'
        self.mail0 = u'mail0'
        self.username1 = u'username1'
        self.password1 = u'password1'
        self.mail1 = u'mail1'
        self.username2 = u'username2'
        self.password2 = u'password2'
        self.mail2 = u'mail2'
        self.admin_username = u'admin_username'
        self.admin_password = u'admin_password'
        self.admin_mail = u'admin_mail'
        self.user0 = User.objects.create_user(self.username0, email=self.mail0)
        self.user0.set_password(self.password0)
        self.user0.save()
        self.user1 = User.objects.create_user(self.username1, email=self.mail1)
        self.user1.set_password(self.password1)
        self.user1.save()
        self.user2 = User.objects.create_user(self.username2, email=self.mail2)
        self.user2.set_password(self.password2)
        self.user2.save()
        self.admin_user = User.objects.create_user(self.admin_username, email=self.admin_mail)
        self.admin_user.set_password(self.admin_password)
        self.admin_user.is_superuser = True
        self.admin_user.save()
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1)
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2)
        self.i1_1_file_name = 'i1_1_file_name'
        self.i1_1_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.i1_1_file_name
        self.i1_1 = Document(user_id=self.user1.id, docfile=self.i1_1_docfile, file_name=self.i1_1_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.i1_1_docfile, 'w+').close()
        self.i1_1.save()
        self.i1_2_file_name = 'i1_2_file_name'
        self.i1_2_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.i1_2_file_name
        self.i1_2 = Document(user_id=self.user1.id, docfile=self.i1_2_docfile, file_name=self.i1_2_file_name, input_time='02')
        open(settings.MEDIA_ROOT + '/' + self.i1_2_docfile, 'w+').close()
        self.i1_2.save()
        self.o1_1_file_name = 'o1_1_file_name'
        self.o1_1_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.o1_1_file_name
        self.o1_1 = Document(user_id=self.user1.id, docfile=self.o1_1_docfile, file_name=self.o1_1_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.o1_1_docfile, 'w+').close()
        self.o1_1.save()
        self.o1_2_file_name = 'o1_2_file_name'
        self.o1_2_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.o1_2_file_name
        self.o1_2 = Document(user_id=self.user1.id, docfile=self.o1_2_docfile, file_name=self.o1_2_file_name, input_time='02')
        open(settings.MEDIA_ROOT + '/' + self.o1_2_docfile, 'w+').close()
        self.o1_2.save()
        self.out_file_name = 'out_file_name'
        self.out_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.out_file_name
        self.out_newdoc = Document(user_id=self.user1.id, docfile=self.out_docfile, file_name=self.out_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.out_docfile, 'w+').close()
        self.out_newdoc.save()

    def tearDown(self):
        User.objects.all().delete()

    def test_01_get_user_id(self):
        """get user id"""
        self.assertEqual(views.get_user_id('notExistUser'), -1)
        self.assertEqual(views.get_user_id(self.username0), self.user0.id)

    def test_02_get_username(self):
        """get username"""
        self.assertEqual(views.get_username(self.user0.id+500), '')
        self.assertEqual(views.get_username(self.user0.id), self.username0)

    def test_03_add_user(self):
        """add user test"""
        User.objects.all().delete()
        self.assertEqual(User.objects.all().count(), 0)
        out = views.add_user({'username':self.username1, 'password':self.password1, 'mail':self.mail1})
        self.assertEqual(out['status'], 'success')
        self.assertEqual(out['msg'], 'New user added.')
        self.assertEqual(User.objects.all().count(), 1)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username1)
        self.assertEqual(users[0]['email'], self.mail1)
        out = views.add_user({'username':self.username2, 'password':self.password2, 'mail':self.mail2})
        self.assertEqual(out['status'], 'success')
        self.assertEqual(out['msg'], 'New user added.')
        self.assertEqual(User.objects.all().count(), 2)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username1)
        self.assertEqual(users[0]['email'], self.mail1)
        self.assertEqual(users[1]['username'], self.username2)
        self.assertEqual(users[1]['email'], self.mail2)
        out = views.add_user({'username':self.username2, 'password':self.password2, 'mail':self.mail2})
        self.assertEqual(out['status'], 'error')
        self.assertEqual(out['msg'], 'Username in use, please change it.')
        self.assertEqual(User.objects.all().count(), 2)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username1)
        self.assertEqual(users[0]['email'], self.mail1)
        self.assertEqual(users[1]['username'], self.username2)
        self.assertEqual(users[1]['email'], self.mail2)
        out = views.add_user({'username':'AAAAAAAAAA1111111111aaaaaaaaaa', 'password':self.password2, 'mail':self.mail2})
        self.assertEqual(out['status'], 'error')
        self.assertEqual(out['msg'], 'Your username is a string pattern composed for guest users, please change it.')
        self.assertEqual(User.objects.all().count(), 2)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username1)
        self.assertEqual(users[0]['email'], self.mail1)
        self.assertEqual(users[1]['username'], self.username2)
        self.assertEqual(users[1]['email'], self.mail2)

    def test_04_delete_user(self):
        """delete user test"""
        from importlib import import_module
        from django.conf import settings
        settings.SESSION_ENGINE = 'django.contrib.sessions.backends.file'
        engine = import_module(settings.SESSION_ENGINE)
        store = engine.SessionStore()
        store.save()
        self.session = store
        self.client.cookies[settings.SESSION_COOKIE_NAME] = store.session_key
        session = self.session
        session.save()
        self.factory = RequestFactory()
        AssemblyTask.objects.create(user_id=self.user0.id, i1_1_id=self.i1_1.id, i1_2_id=self.i1_2.id, o1_1_id=self.o1_1.id, o1_2_id=self.o1_2.id, output_file_id=self.out_newdoc.id, name='name7', k=7, genome_length=1, insert_size_mean_inward=1.0, insert_size_std_dev_inward=0.0, insert_size_mean_outward=1.0, insert_size_std_dev_outward=0.0, quality_threshold='0', bfcounter_threshold='0', single_edge_counter_threshold='0', paired_reads_pet_threshold_from='0', paired_reads_pet_threshold_to='0', paired_reads_mp_threshold_from='0', paired_reads_mp_threshold_to='0', paired_reads_algorithm=AssemblyTask.NONE, input_time='7', output_time='7', correct=True, result_notification=True, mail_address='mail_address')
        AssemblyTask.objects.create(user_id=self.user1.id, i1_1_id=self.i1_1.id, i1_2_id=self.i1_2.id, o1_1_id=self.o1_1.id, o1_2_id=self.o1_2.id, output_file_id=self.out_newdoc.id, name='name7', k=7, genome_length=1, insert_size_mean_inward=1.0, insert_size_std_dev_inward=0.0, insert_size_mean_outward=1.0, insert_size_std_dev_outward=0.0, quality_threshold='0', bfcounter_threshold='0', single_edge_counter_threshold='0', paired_reads_pet_threshold_from='0', paired_reads_pet_threshold_to='0', paired_reads_mp_threshold_from='0', paired_reads_mp_threshold_to='0', paired_reads_algorithm=AssemblyTask.NONE, input_time='7', output_time='7', correct=True, result_notification=True, mail_address='mail_address')
        AssemblyTask.objects.create(user_id=self.user2.id, i1_1_id=self.i1_1.id, i1_2_id=self.i1_2.id, o1_1_id=self.o1_1.id, o1_2_id=self.o1_2.id, output_file_id=self.out_newdoc.id, name='name7', k=7, genome_length=1, insert_size_mean_inward=1.0, insert_size_std_dev_inward=0.0, insert_size_mean_outward=1.0, insert_size_std_dev_outward=0.0, quality_threshold='0', bfcounter_threshold='0', single_edge_counter_threshold='0', paired_reads_pet_threshold_from='0', paired_reads_pet_threshold_to='0', paired_reads_mp_threshold_from='0', paired_reads_mp_threshold_to='0', paired_reads_algorithm=AssemblyTask.NONE, input_time='7', output_time='7', correct=True, result_notification=True, mail_address='mail_address')
        self.assertEqual(len(AssemblyTask.objects.all()), 3)
        self.assertEqual(User.objects.all().count(), 4)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[3]['username'], self.admin_username)

        request = self.factory.post('/user/delete_user')
        #request objects are immuatable
        request.POST = request.POST.copy()
        request.POST['username'] = self.username1
        request.session = session
        request.user = self.user2
        out = views.delete_user(request)
        self.assertEqual(User.objects.all().count(), 4)
        self.assertEqual(out['status'], 'error')
        self.assertEqual(out['msg'], 'Invalid password.')
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[3]['username'], self.admin_username)

        request = self.factory.post('/user/delete_user')
        #request objects are immuatable
        request.POST = request.POST.copy()
        request.POST['username'] = 'notExist'
        request.session = session
        request.user = self.admin_user
        out = views.delete_user(request)
        self.assertEqual(User.objects.all().count(), 4)
        self.assertEqual(out['status'], 'error')
        self.assertEqual(out['msg'], "User doesn't exist.")
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[3]['username'], self.admin_username)

        request = self.factory.post('/user/delete_user')
        #request objects are immutable
        request.POST = request.POST.copy()
        request.POST['username'] = self.username1
        request.session = session
        request.user = self.admin_user
        out = views.delete_user(request)
        self.assertEqual(User.objects.all().count(), 3)
        self.assertEqual(out['status'], 'success')
        self.assertEqual(out['msg'], 'User deleted.')
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username2)
        self.assertEqual(users[2]['username'], self.admin_username)

        request = self.factory.post('/user/delete_user')
        #request objects are immutable
        request.POST = request.POST.copy()
        request.POST['username'] = self.username2
        request.session = session
        request.user = self.user2
        out = views.delete_user(request)
        self.assertEqual(User.objects.all().count(), 3)
        self.assertEqual(out['status'], 'error')
        self.assertEqual(out['msg'], 'Invalid password.')
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username2)
        self.assertEqual(users[2]['username'], self.admin_username)

        request = self.factory.post('/user/delete_user')
        #request objects are immutable
        request.POST = request.POST.copy()
        request.POST['username'] = self.username2
        request.POST['password'] = self.password1
        request.session = session
        request.user = self.user2
        out = views.delete_user(request)
        self.assertEqual(User.objects.all().count(), 3)
        self.assertEqual(out['status'], 'error')
        self.assertEqual(out['msg'], 'Invalid password.')
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username2)
        self.assertEqual(users[2]['username'], self.admin_username)

        request = self.factory.post('/user/delete_user')
        #request objects are immutable
        request.POST = request.POST.copy()
        request.POST['username'] = self.username2
        request.POST['password'] = self.password2
        request.session = session
        request.user = self.user2
        out = views.delete_user(request)
        self.assertEqual(User.objects.all().count(), 2)
        self.assertEqual(out['status'], 'success')
        self.assertEqual(out['msg'], 'User deleted.')
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.admin_username)



    def test_05_login_user(self):
        """login user test"""
        from importlib import import_module
        from django.conf import settings
        settings.SESSION_ENGINE = 'django.contrib.sessions.backends.file'
        engine = import_module(settings.SESSION_ENGINE)
        store = engine.SessionStore()
        store.save()
        self.session = store
        self.client.cookies[settings.SESSION_COOKIE_NAME] = store.session_key
        session = self.session
        session.save()
        self.factory = RequestFactory()
        request = self.factory.post('/assembly/insert')
        #request objects are immuatable
        request.POST = request.POST.copy()
        request.POST['username'] = self.username0
        request.POST['password'] = self.password0
        request.session = session
        out = views.login_user(request)
        self.assertEqual(out['status'], 'success')
        self.assertEqual(out['msg'], 'You have logged in successfully.')
        self.assertEqual(out['isSuperuser'], False)
        request = self.factory.post('/assembly/insert')
        #request objects are immutable
        request.POST = request.POST.copy()
        request.POST['username'] = self.admin_username
        request.POST['password'] = self.admin_password
        request.session = session
        out = views.login_user(request)
        self.assertEqual(out['status'], 'success')
        self.assertEqual(out['msg'], 'You have logged in successfully.')
        self.assertEqual(out['isSuperuser'], True)
        request = self.factory.post('/assembly/insert')
        #request objects are immutable
        request.POST = request.POST.copy()
        request.POST['username'] = self.username0
        request.POST['password'] = self.password1
        request.session = session
        out = views.login_user(request)
        self.assertEqual(out['status'], 'error')
        self.assertEqual(out['msg'], 'Invalid username or password.')
        self.assertEqual(out['isSuperuser'], '')

    def test_06_logout_user(self):
        """logout user test"""
        from importlib import import_module
        from django.conf import settings
        settings.SESSION_ENGINE = 'django.contrib.sessions.backends.file'
        engine = import_module(settings.SESSION_ENGINE)
        store = engine.SessionStore()
        store.save()
        self.session = store
        self.client.cookies[settings.SESSION_COOKIE_NAME] = store.session_key
        session = self.session
        session.save()
        self.factory = RequestFactory()
        request = self.factory.post('/assembly/insert')
        #request objects are immutable
        request.POST = request.POST.copy()
        request.POST['username'] = self.username0
        request.POST['password'] = self.password0
        request.session = session
        views.logout_user(request)
        #sprawdzic, czy uzytkownik jest nadal zalogowany tutaj!!!

    def test_07_get_users(self):
        """get all users"""
        users = views.get_users({}, self.user0)
        self.assertEqual(len(users), 0)
        users = views.get_users({}, self.admin_user)
        self.assertEqual(len(users), 4)
        self.assertEqual(users[0]['username'], self.admin_username)
        self.assertEqual(len(users[0]['lastLogin']) > 0, False)
        self.assertEqual(len(users[0]['joinedDate']) > 0, True)
        self.assertEqual(users[0]['isSuperuser'], True)
        self.assertEqual(users[1]['username'], self.username0)
        self.assertEqual(len(users[1]['lastLogin']) > 0, False)
        self.assertEqual(len(users[1]['joinedDate']) > 0, True)
        self.assertEqual(users[1]['isSuperuser'], False)
        self.assertEqual(users[2]['username'], self.username1)
        self.assertEqual(len(users[2]['lastLogin']) > 0, False)
        self.assertEqual(len(users[2]['joinedDate']) > 0, True)
        self.assertEqual(users[2]['isSuperuser'], False)
        self.assertEqual(users[3]['username'], self.username2)
        self.assertEqual(len(users[3]['lastLogin']) > 0, False)
        self.assertEqual(len(users[3]['joinedDate']) > 0, True)
        self.assertEqual(users[3]['isSuperuser'], False)

    def test_08_get_user_mail(self):
        """get user mail"""
        self.assertEqual(views.get_user_mail(self.admin_user.id+1), '')
        self.assertEqual(views.get_user_mail(self.user0.id), self.mail0)
        self.assertEqual(views.get_user_mail(158, self.user1), self.mail1)

    def test_09_set_user_mail(self):
        """set user mail"""
        new_mail = 'testMail@gmail.com'
        self.assertEqual(User.objects.all().count(), 4)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[0]['email'], self.mail0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[1]['email'], self.mail1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[2]['email'], self.mail2)
        self.assertEqual(views.set_user_mail({'new_mail':new_mail}, self.user1), {'status' : 'success', 'msg' : 'Email changed.'})
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[0]['email'], self.mail0)
        self.assertEqual(users[1]['username'], self.username2)
        self.assertEqual(users[1]['email'], self.mail2)
        self.assertEqual(users[2]['username'], self.admin_username)
        self.assertEqual(users[2]['email'], self.admin_mail)
        self.assertEqual(users[3]['username'], self.username1)
        self.assertEqual(users[3]['email'], new_mail)

    def test_10_set_user_mail(self):
        """set user password"""
        new_password = 'new_password'
        self.assertEqual(User.objects.all().count(), 4)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[0]['email'], self.mail0)
        password0 = users[0]['password']
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[1]['email'], self.mail1)
        password1 = users[1]['password']
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[2]['email'], self.mail2)
        password2 = users[2]['password']
        self.assertEqual(users[3]['username'], self.admin_username)
        self.assertEqual(users[3]['email'], self.admin_mail)
        admin_password = users[3]['password']
        self.assertEqual(views.set_user_password({'new_password':new_password}, self.user1), {'status' : 'success', 'msg' : 'Password changed.'})
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[0]['email'], self.mail0)
        self.assertEqual(users[0]['password'], password0)
        self.assertEqual(users[1]['username'], self.username2)
        self.assertEqual(users[1]['email'], self.mail2)
        self.assertEqual(users[1]['password'], password2)
        self.assertEqual(users[2]['username'], self.admin_username)
        self.assertEqual(users[2]['email'], self.admin_mail)
        self.assertEqual(users[2]['password'], admin_password)
        self.assertEqual(users[3]['username'], self.username1)
        self.assertEqual(users[3]['email'], self.mail1)
        self.assertNotEqual(users[3]['password'], password1)

    def test_11_add_and_login_guest_user(self):
        """add new guest user and log in"""
        from importlib import import_module
        from django.conf import settings
        settings.SESSION_ENGINE = 'django.contrib.sessions.backends.file'
        engine = import_module(settings.SESSION_ENGINE)
        store = engine.SessionStore()
        store.save()
        self.session = store
        self.client.cookies[settings.SESSION_COOKIE_NAME] = store.session_key
        session = self.session
        session.save()
        self.factory = RequestFactory()

        request = self.factory.post('/assembly/insert')
        request.session = session
        self.assertEqual(User.objects.all().count(), 4)
        out = views.add_and_login_guest_user(request)
        self.assertEqual(out['status'], 'success')
        self.assertEqual(out['msg'], 'You have logged in successfully to new guest user.')
        self.assertNotEqual(re.match('[A-Z]{10}\d{10}[a-z]{10}', out['username'], 0), None)
        self.assertEqual(User.objects.all().count(), 5)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[0]['email'], self.mail0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[1]['email'], self.mail1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[2]['email'], self.mail2)
        self.assertEqual(users[3]['username'], self.admin_username)
        self.assertEqual(users[3]['email'], self.admin_mail)
        self.assertEqual(users[4]['username'], out['username'])
        self.assertEqual(users[4]['email'], '')

        request = self.factory.post('/assembly/insert')
        request.session = session
        out2 = views.add_and_login_guest_user(request)
        self.assertEqual(out2['status'], 'success')
        self.assertEqual(out2['msg'], 'You have logged in successfully to new guest user.')
        self.assertNotEqual(re.match('[A-Z]{10}\d{10}[a-z]{10}', out2['username'], 0), None)
        self.assertEqual(User.objects.all().count(), 6)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[0]['email'], self.mail0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[1]['email'], self.mail1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[2]['email'], self.mail2)
        self.assertEqual(users[3]['username'], self.admin_username)
        self.assertEqual(users[3]['email'], self.admin_mail)
        self.assertEqual(users[4]['username'], out['username'])
        self.assertEqual(users[4]['email'], '')
        self.assertEqual(users[5]['username'], out2['username'])
        self.assertEqual(users[5]['email'], '')

    def test_12_delete_guest_users(self):
        """delete guest users test"""
        from datetime import timedelta
        guest_username_0 = 'AAAAAAAAAA0000000000aaaaaaaaaa'
        guest_password_0 = 'asdasdasdasdsadasdasdsadasdsad'
        guest_user_0 = User.objects.create_user(guest_username_0)
        guest_user_0.set_password(guest_password_0)
        guest_user_0.save()
        guest_username_1 = 'AAAAAAAAAA1111111111aaaaaaaaaa'
        guest_password_1 = 'asdasdasdasdsadasdasdsadasdsad'
        guest_user_1 = User.objects.create_user(guest_username_1)
        guest_user_1.set_password(guest_password_1)
        guest_user_1.save()
        AssemblyTask.objects.create(user_id=self.user0.id, i1_1_id=self.i1_1.id, i1_2_id=self.i1_2.id, o1_1_id=self.o1_1.id, o1_2_id=self.o1_2.id, output_file_id=self.out_newdoc.id, name='name7', k=7, genome_length=1, insert_size_mean_inward=1.0, insert_size_std_dev_inward=0.0, insert_size_mean_outward=1.0, insert_size_std_dev_outward=0.0, quality_threshold='0', bfcounter_threshold='0', single_edge_counter_threshold='0', paired_reads_pet_threshold_from='0', paired_reads_pet_threshold_to='0', paired_reads_mp_threshold_from='0', paired_reads_mp_threshold_to='0', paired_reads_algorithm=AssemblyTask.NONE, input_time='7', output_time='7', correct=True, result_notification=True, mail_address='mail_address')
        AssemblyTask.objects.create(user_id=guest_user_1.id, i1_1_id=self.i1_1.id, i1_2_id=self.i1_2.id, o1_1_id=self.o1_1.id, o1_2_id=self.o1_2.id, output_file_id=self.out_newdoc.id, name='name7', k=7, genome_length=1, insert_size_mean_inward=1.0, insert_size_std_dev_inward=0.0, insert_size_mean_outward=1.0, insert_size_std_dev_outward=0.0, quality_threshold='0', bfcounter_threshold='0', single_edge_counter_threshold='0', paired_reads_pet_threshold_from='0', paired_reads_pet_threshold_to='0', paired_reads_mp_threshold_from='0', paired_reads_mp_threshold_to='0', paired_reads_algorithm=AssemblyTask.NONE, input_time='7', output_time='7', correct=True, result_notification=True, mail_address='mail_address')
        self.assertEqual(AssemblyTask.objects.all().count(), 2)
        self.assertEqual(User.objects.all().count(), 6)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[3]['username'], self.admin_username)
        self.assertEqual(users[4]['username'], guest_username_0)
        self.assertEqual(users[5]['username'], guest_username_1)
        out = views.delete_guest_users(timedelta(minutes=5))
        self.assertEqual(out, 0)
        self.assertEqual(AssemblyTask.objects.all().count(), 2)
        self.assertEqual(User.objects.all().count(), 6)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[3]['username'], self.admin_username)
        self.assertEqual(users[4]['username'], guest_username_0)
        self.assertEqual(users[5]['username'], guest_username_1)
        out = views.delete_guest_users(timedelta(minutes=0))
        self.assertEqual(out, 2)
        self.assertEqual(AssemblyTask.objects.all().count(), 1)
        self.assertEqual(User.objects.all().count(), 4)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[3]['username'], self.admin_username)
        guest_username_0 = 'AAAAAAAAAA0000000000aaaaaaaaaa'
        guest_password_0 = 'asdasdasdasdsadasdasdsadasdsad'
        guest_user_0 = User.objects.create_user(guest_username_0)
        guest_user_0.set_password(guest_password_0)
        guest_user_0.save()
        time.sleep(1.0)
        guest_username_1 = 'AAAAAAAAAA1111111111aaaaaaaaaa'
        guest_password_1 = 'asdasdasdasdsadasdasdsadasdsad'
        guest_user_1 = User.objects.create_user(guest_username_1)
        guest_user_1.set_password(guest_password_1)
        guest_user_1.save()
        out = views.delete_guest_users(timedelta(seconds=1))
        self.assertEqual(out, 1)
        self.assertEqual(AssemblyTask.objects.all().count(), 1)
        self.assertEqual(User.objects.all().count(), 5)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[3]['username'], self.admin_username)
        self.assertEqual(users[4]['username'], guest_username_1)
        time.sleep(1.0)
        out = views.delete_guest_users(timedelta(seconds=1))
        self.assertEqual(out, 1)
        self.assertEqual(AssemblyTask.objects.all().count(), 1)
        self.assertEqual(User.objects.all().count(), 4)
        users = User.objects.all().values()
        self.assertEqual(users[0]['username'], self.username0)
        self.assertEqual(users[1]['username'], self.username1)
        self.assertEqual(users[2]['username'], self.username2)
        self.assertEqual(users[3]['username'], self.admin_username)
