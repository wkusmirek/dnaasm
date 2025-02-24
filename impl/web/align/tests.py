## @file align/tests.py
#  @brief database interface unit testing

import os
import shutil
import time
import django.test
from dnaasmpy import dnaasmpy    # c++ module with CommandManager - to test break_align_task function
from file.models import Document
from django.contrib.auth.models import User
from django.conf import settings
from .models import AlignTask
from . import views

class AlignModelTestCase(django.test.TestCase):
    """test module model"""
    pass

class AlignViewTestCase(django.test.TestCase):
    """test module interface"""

    def setUp(self):
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT)
        self.username1 = u'username1'
        self.password1 = u'password1'
        self.user1 = User.objects.create_user(self.username1)
        self.user1.set_password(self.password1)
        self.user1.save()
        self.username2 = u'username2'
        self.password2 = u'password2'
        self.user2 = User.objects.create_user(self.username2)
        self.user2.set_password(self.password2)
        self.user2.save()
        self.admin_username = u'admin_username'
        self.admin_password = u'admin_password'
        self.admin_user = User.objects.create_user(self.admin_username)
        self.admin_user.set_password(self.admin_password)
        self.admin_user.is_superuser = True
        self.admin_user.save()
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1)
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2)
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.admin_username):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + self.admin_username)
        if not os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.username1):
            os.makedirs(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.username1)
        if not os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.username2):
            os.makedirs(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.username2)
        if not os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.admin_username):
            os.makedirs(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.admin_username)
        self.seq_file_name = 'seq_file_name'
        self.seq_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.seq_file_name
        self.seq_newdoc = Document(user_id=self.user1.id, docfile=self.seq_docfile, file_name=self.seq_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.seq_docfile, 'w+').close()
        self.seq_newdoc.save()
        self.ref_file_name = 'ref_file_name'
        self.ref_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.ref_file_name
        self.ref_newdoc = Document(user_id=self.user1.id, docfile=self.ref_docfile, file_name=self.ref_file_name, input_time='02')
        open(settings.MEDIA_ROOT + '/' + self.ref_docfile, 'w+').close()
        self.ref_newdoc.save()
        self.out_file_name = 'out_file_name'
        self.out_docfile = settings.PUBLIC_USERS_PREFIX + '/' + self.username1 + '/' + self.out_file_name
        self.out_newdoc = Document(user_id=self.user1.id, docfile=self.out_docfile, file_name=self.out_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.out_docfile, 'w+').close()
        self.out_newdoc.save()

    def tearDown(self):
        if os.path.exists(settings.MEDIA_ROOT + '/' + self.seq_docfile):
            os.remove(settings.MEDIA_ROOT + '/' + self.seq_docfile)
        if os.path.exists(settings.MEDIA_ROOT + '/' + self.ref_docfile):
            os.remove(settings.MEDIA_ROOT + '/' + self.ref_docfile)
        if os.path.exists(settings.MEDIA_ROOT + '/' + self.out_docfile):
            os.remove(settings.MEDIA_ROOT + '/' + self.out_docfile)
        if os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1):
            shutil.rmtree(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1)
        if os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2):
            shutil.rmtree(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2)
        if os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.admin_username):
            shutil.rmtree(settings.PRIVATE_MEDIA_ROOT + '/' + self.admin_username)
        if os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.username1):
            shutil.rmtree(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.username1)
        if os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.username2):
            shutil.rmtree(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.username2)
        if os.path.exists(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.admin_username):
            shutil.rmtree(settings.PUBLIC_USERS_MEDIA_ROOT + '/' + self.admin_username)
        Document.objects.all().delete()
        AlignTask.objects.all().delete()
        User.objects.all().delete()

    def test_01_insert(self):
        """insert sth into a AlignTask table"""
        views.insert({'name':'name', 'seq_file_name':'noSuchFile', 'ref_file_name':self.ref_file_name, 'align_algorithm':'h', 'circular':'false', 'gap_penalty':'0', 'AA':'1', 'AC':'2', 'AG':'3', 'AT':'4', 'CA':'5', 'CC':'6', 'CG':'7', 'CT':'8', 'GA':'9', 'GC':'10', 'GG':'11', 'GT':'12', 'TA':'13', 'TC':'14', 'TG':'15', 'TT':'16', 'result_notification':'false', 'mail_address':'user1_mail_address'}, self.user1)
        self.assertEqual(AlignTask.objects.all().count(), 0)
        views.insert({'name':'name', 'seq_file_name':self.seq_file_name, 'ref_file_name':'noSuchFile', 'align_algorithm':'nw', 'circular':'true', 'gap_penalty':'0', 'AA':'1', 'AC':'2', 'AG':'3', 'AT':'4', 'CA':'5', 'CC':'6', 'CG':'7', 'CT':'8', 'GA':'9', 'GC':'10', 'GG':'11', 'GT':'12', 'TA':'13', 'TC':'14', 'TG':'15', 'TT':'16', 'result_notification':'true', 'mail_address':'user1_mail_address'}, self.user1)
        self.assertEqual(AlignTask.objects.all().count(), 0)
        views.insert({'name':'name', 'seq_file_name':self.seq_file_name, 'ref_file_name':self.ref_file_name, 'align_algorithm':'unknown', 'circular':'false', 'gap_penalty':'0', 'AA':'1', 'AC':'2', 'AG':'3', 'AT':'4', 'CA':'5', 'CC':'6', 'CG':'7', 'CT':'8', 'GA':'9', 'GC':'10', 'GG':'11', 'GT':'12', 'TA':'13', 'TC':'14', 'TG':'15', 'TT':'16', 'result_notification':'false', 'mail_address':'user1_mail_address'}, self.user1)
        self.assertEqual(AlignTask.objects.all().count(), 1)
        actual_align_task = AlignTask.objects.filter(name='name').values()
        align_task = AlignTask.objects.all().values()
        self.assertEqual(align_task[0]['id'], actual_align_task[0]['id'])
        self.assertEqual(align_task[0]['user_id'], self.user1.id)
        self.assertEqual(align_task[0]['name'], 'name')
        self.assertEqual(align_task[0]['sequence_file_id'], self.seq_newdoc.id)
        self.assertEqual(align_task[0]['reference_file_id'], self.ref_newdoc.id)
        self.assertEqual(align_task[0]['output_file_id'], self.out_newdoc.id + 1)
        self.assertEqual(align_task[0]['align_algorithm'], AlignTask.UNKNOWN)
        self.assertEqual(align_task[0]['circular'], False)
        self.assertEqual(align_task[0]['gap_penalty'], 0)
        self.assertEqual(align_task[0]['AA'], 1)
        self.assertEqual(align_task[0]['AC'], 2)
        self.assertEqual(align_task[0]['AG'], 3)
        self.assertEqual(align_task[0]['AT'], 4)
        self.assertEqual(align_task[0]['CA'], 5)
        self.assertEqual(align_task[0]['CC'], 6)
        self.assertEqual(align_task[0]['CG'], 7)
        self.assertEqual(align_task[0]['CT'], 8)
        self.assertEqual(align_task[0]['GA'], 9)
        self.assertEqual(align_task[0]['GC'], 10)
        self.assertEqual(align_task[0]['GG'], 11)
        self.assertEqual(align_task[0]['GT'], 12)
        self.assertEqual(align_task[0]['TA'], 13)
        self.assertEqual(align_task[0]['TC'], 14)
        self.assertEqual(align_task[0]['TG'], 15)
        self.assertEqual(align_task[0]['TT'], 16)
        self.assertEqual(align_task[0]['result_notification'], False)
        self.assertEqual(align_task[0]['mail_address'], 'user1_mail_address')
        self.assertEqual(len(align_task[0]['input_time']) > 0, True)
        self.assertEqual(align_task[0]['output_time'], '')
        self.assertEqual(Document.objects.all().count(), 4)
        file = Document.objects.all().values()
        self.assertEqual(file[0]['id'], self.seq_newdoc.id)
        self.assertEqual(file[0]['docfile'], self.seq_docfile)
        self.assertEqual(file[0]['file_name'], self.seq_file_name)
        self.assertEqual(file[0]['input_time'], '01')
        self.assertEqual(file[1]['id'], self.ref_newdoc.id)
        self.assertEqual(file[1]['docfile'], self.ref_docfile)
        self.assertEqual(file[1]['file_name'], self.ref_file_name)
        self.assertEqual(file[1]['input_time'], '02')
        self.assertEqual(file[2]['id'], self.out_newdoc.id)
        self.assertEqual(file[2]['docfile'], self.out_docfile)
        self.assertEqual(file[2]['file_name'], self.out_file_name)
        self.assertEqual(file[2]['input_time'], '01')
        self.assertEqual(file[3]['id'], self.out_newdoc.id + 1)
        self.assertEqual(file[3]['docfile'], settings.PUBLIC_USERS_PREFIX + '/' + self.username1 + '/name')
        self.assertEqual(file[3]['file_name'], 'name')
        self.assertEqual(file[3]['input_time'], '')
        # below the same task name - can not add a new task
        views.insert({'name':'name', 'seq_file_name':self.seq_file_name, 'ref_file_name':self.ref_file_name, 'align_algorithm':'h', 'circular':'false', 'gap_penalty':'0', 'AA':'1', 'AC':'2', 'AG':'3', 'AT':'4', 'CA':'5', 'CC':'6', 'CG':'7', 'CT':'8', 'GA':'9', 'GC':'10', 'GG':'11', 'GT':'12', 'TA':'13', 'TC':'14', 'TG':'15', 'TT':'16', 'result_notification':'false', 'mail_address':'user1_mail_address'}, self.user1)
        self.assertEqual(AlignTask.objects.all().count(), 1)
        actual_align_task = AlignTask.objects.filter(name='name').values()
        align_tasks = AlignTask.objects.all().values()
        self.assertEqual(align_tasks[0]['id'], actual_align_task[0]['id'])
        self.assertEqual(align_tasks[0]['user_id'], self.user1.id)
        self.assertEqual(align_tasks[0]['name'], 'name')
        self.assertEqual(align_tasks[0]['sequence_file_id'], self.seq_newdoc.id)
        self.assertEqual(align_tasks[0]['reference_file_id'], self.ref_newdoc.id)
        self.assertEqual(align_tasks[0]['output_file_id'], self.out_newdoc.id + 1)
        self.assertEqual(align_tasks[0]['align_algorithm'], AlignTask.UNKNOWN)
        self.assertEqual(align_tasks[0]['circular'], False)
        self.assertEqual(align_tasks[0]['gap_penalty'], 0)
        self.assertEqual(align_tasks[0]['AA'], 1)
        self.assertEqual(align_tasks[0]['AC'], 2)
        self.assertEqual(align_tasks[0]['AG'], 3)
        self.assertEqual(align_tasks[0]['AT'], 4)
        self.assertEqual(align_tasks[0]['CA'], 5)
        self.assertEqual(align_tasks[0]['CC'], 6)
        self.assertEqual(align_tasks[0]['CG'], 7)
        self.assertEqual(align_tasks[0]['CT'], 8)
        self.assertEqual(align_tasks[0]['GA'], 9)
        self.assertEqual(align_tasks[0]['GC'], 10)
        self.assertEqual(align_tasks[0]['GG'], 11)
        self.assertEqual(align_tasks[0]['GT'], 12)
        self.assertEqual(align_tasks[0]['TA'], 13)
        self.assertEqual(align_tasks[0]['TC'], 14)
        self.assertEqual(align_tasks[0]['TG'], 15)
        self.assertEqual(align_tasks[0]['TT'], 16)
        self.assertEqual(align_tasks[0]['result_notification'], False)
        self.assertEqual(align_task[0]['mail_address'], 'user1_mail_address')
        self.assertEqual(len(align_tasks[0]['input_time']) > 0, True)
        self.assertEqual(align_tasks[0]['output_time'], '')
        self.assertEqual(Document.objects.all().count(), 4)
        file = Document.objects.all().values()
        self.assertEqual(file[0]['id'], self.seq_newdoc.id)
        self.assertEqual(file[0]['docfile'], self.seq_docfile)
        self.assertEqual(file[0]['file_name'], self.seq_file_name)
        self.assertEqual(file[0]['input_time'], '01')
        self.assertEqual(file[1]['id'], self.ref_newdoc.id)
        self.assertEqual(file[1]['docfile'], self.ref_docfile)
        self.assertEqual(file[1]['file_name'], self.ref_file_name)
        self.assertEqual(file[1]['input_time'], '02')
        self.assertEqual(file[2]['id'], self.out_newdoc.id)
        self.assertEqual(file[2]['docfile'], self.out_docfile)
        self.assertEqual(file[2]['file_name'], self.out_file_name)
        self.assertEqual(file[2]['input_time'], '01')
        self.assertEqual(file[3]['id'], self.out_newdoc.id + 1)
        self.assertEqual(file[3]['docfile'], settings.PUBLIC_USERS_PREFIX + '/' + self.username1 + '/name')
        self.assertEqual(file[3]['file_name'], 'name')
        self.assertEqual(file[3]['input_time'], '')
        views.insert({'name':'name2', 'seq_file_name':self.seq_file_name, 'ref_file_name':self.ref_file_name, 'align_algorithm':'h', 'circular':'true', 'gap_penalty':'02', 'AA':12, 'AC':22, 'AG':32, 'AT':42, 'CA':52, 'CC':62, 'CG':72, 'CT':82, 'GA':92, 'GC':102, 'GG':112, 'GT':122, 'TA':132, 'TC':142, 'TG':152, 'TT':162, 'result_notification':'true', 'mail_address':'user1_mail_address'}, self.user1)
        self.assertEqual(AlignTask.objects.all().count(), 2)
        actual_align_task2 = AlignTask.objects.filter(name='name2').values()
        align_tasks = AlignTask.objects.all().values()
        self.assertEqual(align_tasks[0]['id'], actual_align_task[0]['id'])
        self.assertEqual(align_tasks[0]['user_id'], self.user1.id)
        self.assertEqual(align_tasks[0]['name'], 'name')
        self.assertEqual(align_tasks[0]['sequence_file_id'], self.seq_newdoc.id)
        self.assertEqual(align_tasks[0]['reference_file_id'], self.ref_newdoc.id)
        self.assertEqual(align_tasks[0]['output_file_id'], self.out_newdoc.id + 1)
        self.assertEqual(align_tasks[0]['align_algorithm'], AlignTask.UNKNOWN)
        self.assertEqual(align_tasks[0]['circular'], False)
        self.assertEqual(align_tasks[0]['gap_penalty'], 0)
        self.assertEqual(align_tasks[0]['AA'], 1)
        self.assertEqual(align_tasks[0]['AC'], 2)
        self.assertEqual(align_tasks[0]['AG'], 3)
        self.assertEqual(align_tasks[0]['AT'], 4)
        self.assertEqual(align_tasks[0]['CA'], 5)
        self.assertEqual(align_tasks[0]['CC'], 6)
        self.assertEqual(align_tasks[0]['CG'], 7)
        self.assertEqual(align_tasks[0]['CT'], 8)
        self.assertEqual(align_tasks[0]['GA'], 9)
        self.assertEqual(align_tasks[0]['GC'], 10)
        self.assertEqual(align_tasks[0]['GG'], 11)
        self.assertEqual(align_tasks[0]['GT'], 12)
        self.assertEqual(align_tasks[0]['TA'], 13)
        self.assertEqual(align_tasks[0]['TC'], 14)
        self.assertEqual(align_tasks[0]['TG'], 15)
        self.assertEqual(align_tasks[0]['TT'], 16)
        self.assertEqual(align_tasks[0]['result_notification'], False)
        self.assertEqual(align_task[0]['mail_address'], 'user1_mail_address')
        self.assertEqual(len(align_tasks[0]['input_time']) > 0, True)
        self.assertEqual(align_tasks[0]['output_time'], '')
        self.assertEqual(align_tasks[1]['id'], actual_align_task2[0]['id'])
        self.assertEqual(align_tasks[1]['user_id'], self.user1.id)
        self.assertEqual(align_tasks[1]['name'], 'name2')
        self.assertEqual(align_tasks[1]['sequence_file_id'], self.seq_newdoc.id)
        self.assertEqual(align_tasks[1]['reference_file_id'], self.ref_newdoc.id)
        self.assertEqual(align_tasks[1]['output_file_id'], self.out_newdoc.id + 2)
        self.assertEqual(align_tasks[1]['align_algorithm'], AlignTask.HIRSCHBERG)
        self.assertEqual(align_tasks[1]['circular'], True)
        self.assertEqual(align_tasks[1]['gap_penalty'], 2)
        self.assertEqual(align_tasks[1]['AA'], 12)
        self.assertEqual(align_tasks[1]['AC'], 22)
        self.assertEqual(align_tasks[1]['AG'], 32)
        self.assertEqual(align_tasks[1]['AT'], 42)
        self.assertEqual(align_tasks[1]['CA'], 52)
        self.assertEqual(align_tasks[1]['CC'], 62)
        self.assertEqual(align_tasks[1]['CG'], 72)
        self.assertEqual(align_tasks[1]['CT'], 82)
        self.assertEqual(align_tasks[1]['GA'], 92)
        self.assertEqual(align_tasks[1]['GC'], 102)
        self.assertEqual(align_tasks[1]['GG'], 112)
        self.assertEqual(align_tasks[1]['GT'], 122)
        self.assertEqual(align_tasks[1]['TA'], 132)
        self.assertEqual(align_tasks[1]['TC'], 142)
        self.assertEqual(align_tasks[1]['TG'], 152)
        self.assertEqual(align_tasks[1]['TT'], 162)
        self.assertEqual(align_tasks[1]['result_notification'], True)
        self.assertEqual(align_task[1]['mail_address'], 'user1_mail_address')
        self.assertEqual(len(align_tasks[1]['input_time']) > 0, True)
        self.assertEqual(align_tasks[1]['output_time'], '')
        self.assertEqual(Document.objects.all().count(), 5)
        file = Document.objects.all().values()
        self.assertEqual(file[0]['id'], self.seq_newdoc.id)
        self.assertEqual(file[0]['docfile'], self.seq_docfile)
        self.assertEqual(file[0]['file_name'], self.seq_file_name)
        self.assertEqual(file[0]['input_time'], '01')
        self.assertEqual(file[1]['id'], self.ref_newdoc.id)
        self.assertEqual(file[1]['docfile'], self.ref_docfile)
        self.assertEqual(file[1]['file_name'], self.ref_file_name)
        self.assertEqual(file[1]['input_time'], '02')
        self.assertEqual(file[2]['id'], self.out_newdoc.id)
        self.assertEqual(file[2]['docfile'], self.out_docfile)
        self.assertEqual(file[2]['file_name'], self.out_file_name)
        self.assertEqual(file[2]['input_time'], '01')
        self.assertEqual(file[3]['id'], self.out_newdoc.id + 1)
        self.assertEqual(file[3]['docfile'], settings.PUBLIC_USERS_PREFIX + '/' + self.username1 + '/name')
        self.assertEqual(file[3]['file_name'], 'name')
        self.assertEqual(file[3]['input_time'], '')
        self.assertEqual(file[4]['id'], self.out_newdoc.id + 2)
        self.assertEqual(file[4]['docfile'], settings.PUBLIC_USERS_PREFIX + '/' + self.username1 + '/name2')
        self.assertEqual(file[4]['file_name'], 'name2')
        self.assertEqual(file[4]['input_time'], '')

    def test_02_delete(self):
        """delete align task from a AlignTask table"""
        self.assertEqual(AlignTask.objects.all().count(), 0)
        views.delete({'id':0}, self.user1)
        self.assertEqual(AlignTask.objects.all().count(), 0)
        align_task_1 = AlignTask.objects.create(user_id=self.user1.id, name='name', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty=0, AA=1, AC=2, AG=3, AT=4, CA=5, CC=6, CG=7, CT=8, GA=9, GC=10, GG=11, GT=12, TA=13, TC=14, TG=15, TT=16, result_notification=False, mail_address='user1_mail_address', input_time='1', output_time='2')
        self.assertEqual(AlignTask.objects.all().count(), 1)
        align_task_2 = AlignTask.objects.create(user_id=self.user1.id, name='name2', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty='02', AA=12, AC=22, AG=32, AT=42, CA=52, CC=62, CG=72, CT=82, GA=92, GC=102, GG=112, GT=122, TA=132, TC=142, TG=152, TT=162, result_notification=False, mail_address='user1_mail_address', input_time='12', output_time='22')
        self.assertEqual(AlignTask.objects.all().count(), 2)
        align_tasks = AlignTask.objects.all().values()
        self.assertEqual(align_tasks[0]['id'], align_task_1.id)
        self.assertEqual(align_tasks[1]['id'], align_task_2.id)
        views.delete({'id':7}, self.user1)
        self.assertEqual(AlignTask.objects.all().count(), 2)
        views.delete({'id':align_task_1.id}, self.user2)
        self.assertEqual(AlignTask.objects.all().count(), 2)
        views.delete({'id':align_task_1.id}, self.user1)
        self.assertEqual(AlignTask.objects.all().count(), 1)
        align_tasks = AlignTask.objects.all().values()
        self.assertEqual(align_tasks[0]['id'], align_task_2.id)
        views.delete({'id':align_task_2.id}, self.admin_user)
        self.assertEqual(AlignTask.objects.all().count(), 0)

    def test_03_get_user_align_tasks(self):
        """get all align tasks for specified user from a database"""
        AlignTask.objects.create(user_id=self.user1.id, name='nameGet', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty=0, AA=1, AC=2, AG=3, AT=4, CA=5, CC=6, CG=7, CT=8, GA=9, GC=10, GG=11, GT=12, TA=13, TC=14, TG=15, TT=16, result_notification=False,  mail_address='user1_mail_address', input_time='1', output_time='2')
        task = AlignTask.objects.filter(name='nameGet')
        align_task = views.get_user_align_tasks({}, self.user1)
        self.assertEqual(len(align_task), 1)
        self.assertEqual(align_task[0]['id'], task.values('id')[0]['id'])
        self.assertEqual(align_task[0]['name'], 'nameGet')
        self.assertEqual(align_task[0]['sequence_file_name'], self.seq_file_name)
        self.assertEqual(align_task[0]['reference_file_name'], self.ref_file_name)
        self.assertEqual(align_task[0]['align_algorithm'], AlignTask.HIRSCHBERG)
        self.assertEqual(align_task[0]['circular'], False)
        self.assertEqual(align_task[0]['gap_penalty'], 0)
        self.assertEqual(align_task[0]['AA'], 1)
        self.assertEqual(align_task[0]['AC'], 2)
        self.assertEqual(align_task[0]['AG'], 3)
        self.assertEqual(align_task[0]['AT'], 4)
        self.assertEqual(align_task[0]['CA'], 5)
        self.assertEqual(align_task[0]['CC'], 6)
        self.assertEqual(align_task[0]['CG'], 7)
        self.assertEqual(align_task[0]['CT'], 8)
        self.assertEqual(align_task[0]['GA'], 9)
        self.assertEqual(align_task[0]['GC'], 10)
        self.assertEqual(align_task[0]['GG'], 11)
        self.assertEqual(align_task[0]['GT'], 12)
        self.assertEqual(align_task[0]['TA'], 13)
        self.assertEqual(align_task[0]['TC'], 14)
        self.assertEqual(align_task[0]['TG'], 15)
        self.assertEqual(align_task[0]['TT'], 16)
        self.assertEqual(align_task[0]['input_time'], '1')
        self.assertEqual(align_task[0]['output_time'], '2')

    def test_04_get_all_align_tasks(self):
        """get all align tasks for all users from a database"""
        align_task = views.get_all_align_tasks({}, self.user1)
        self.assertEqual(len(align_task), 0)
        align_task = views.get_all_align_tasks({}, self.admin_user)
        self.assertEqual(len(align_task), 0)
        AlignTask.objects.create(user_id=self.user1.id, name='nameGet', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty=0, AA=1, AC=2, AG=3, AT=4, CA=5, CC=6, CG=7, CT=8, GA=9, GC=10, GG=11, GT=12, TA=13, TC=14, TG=15, TT=16, result_notification=False,  mail_address='user1_mail_address', input_time='1', output_time='2')
        task = AlignTask.objects.filter(name='nameGet')
        align_task = views.get_all_align_tasks({}, self.user1)
        self.assertEqual(len(align_task), 0)
        align_task = views.get_all_align_tasks({}, self.admin_user)
        self.assertEqual(len(align_task), 1)
        self.assertEqual(align_task[0]['id'], task.values('id')[0]['id'])
        self.assertEqual(align_task[0]['name'], 'nameGet')
        self.assertEqual(align_task[0]['sequence_file_name'], self.seq_file_name)
        self.assertEqual(align_task[0]['reference_file_name'], self.ref_file_name)
        self.assertEqual(align_task[0]['align_algorithm'], AlignTask.HIRSCHBERG)
        self.assertEqual(align_task[0]['circular'], False)
        self.assertEqual(align_task[0]['gap_penalty'], 0)
        self.assertEqual(align_task[0]['AA'], 1)
        self.assertEqual(align_task[0]['AC'], 2)
        self.assertEqual(align_task[0]['AG'], 3)
        self.assertEqual(align_task[0]['AT'], 4)
        self.assertEqual(align_task[0]['CA'], 5)
        self.assertEqual(align_task[0]['CC'], 6)
        self.assertEqual(align_task[0]['CG'], 7)
        self.assertEqual(align_task[0]['CT'], 8)
        self.assertEqual(align_task[0]['GA'], 9)
        self.assertEqual(align_task[0]['GC'], 10)
        self.assertEqual(align_task[0]['GG'], 11)
        self.assertEqual(align_task[0]['GT'], 12)
        self.assertEqual(align_task[0]['TA'], 13)
        self.assertEqual(align_task[0]['TC'], 14)
        self.assertEqual(align_task[0]['TG'], 15)
        self.assertEqual(align_task[0]['TT'], 16)
        self.assertEqual(align_task[0]['input_time'], '1')
        self.assertEqual(align_task[0]['output_time'], '2')
        self.assertEqual(align_task[0]['owner'], self.username1)

    def test_05_is_file_used(self):
        """check if file is used"""
        AlignTask.objects.create(user_id=self.user2.id, name='name', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=True, gap_penalty=0, AA=1, AC=2, AG=3, AT=4, CA=5, CC=6, CG=7, CT=8, GA=9, GC=10, GG=11, GT=12, TA=13, TC=14, TG=15, TT=16, result_notification=False, mail_address='user2_mail_address', input_time='1', output_time='2')
        self.assertEqual(AlignTask.objects.all().count(), 1)
        self.assertEqual(views.is_file_used(self.seq_newdoc.id), True)
        self.assertEqual(views.is_file_used(self.ref_newdoc.id), True)
        self.assertEqual(views.is_file_used(self.out_newdoc.id), False)

    def test_06_delete_user_align_tasks(self):
        """delete user align tasks"""
        AlignTask.objects.create(user_id=self.user2.id, name='name', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty=0, AA=1, AC=2, AG=3, AT=4, CA=5, CC=6, CG=7, CT=8, GA=9, GC=10, GG=11, GT=12, TA=13, TC=14, TG=15, TT=16, result_notification=False, mail_address='user2_mail_address', input_time='1', output_time='2')
        AlignTask.objects.create(user_id=self.user1.id, name='name2', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty='02', AA=12, AC=22, AG=32, AT=42, CA=52, CC=62, CG=72, CT=82, GA=92, GC=102, GG=112, GT=122, TA=132, TC=142, TG=152, TT=162, result_notification=False, mail_address='user1_mail_address', input_time='12', output_time='22')
        AlignTask.objects.create(user_id=self.user1.id, name='name3', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty='03', AA=13, AC=23, AG=33, AT=43, CA=53, CC=63, CG=73, CT=83, GA=93, GC=103, GG=113, GT=123, TA=133, TC=143, TG=153, TT=163, result_notification=False, mail_address='user1_mail_address', input_time='13', output_time='23')
        self.assertEqual(AlignTask.objects.all().count(), 3)
        views.delete_user_align_tasks(self.user1.id)
        self.assertEqual(AlignTask.objects.all().count(), 1)
        align_tasks = AlignTask.objects.all().values()
        align_task = AlignTask.objects.filter(name='name').values()
        self.assertEqual(align_tasks[0]['id'], align_task[0]['id'])
        self.assertEqual(align_tasks[0]['user_id'], self.user2.id)
        self.assertEqual(align_tasks[0]['name'], 'name')
        self.assertEqual(align_tasks[0]['sequence_file_id'], self.seq_newdoc.id)
        self.assertEqual(align_tasks[0]['reference_file_id'], self.ref_newdoc.id)
        self.assertEqual(align_tasks[0]['output_file_id'], self.out_newdoc.id)
        self.assertEqual(align_tasks[0]['align_algorithm'], AlignTask.HIRSCHBERG)
        self.assertEqual(align_tasks[0]['circular'], False)
        self.assertEqual(align_tasks[0]['gap_penalty'], 0)
        self.assertEqual(align_tasks[0]['AA'], 1)
        self.assertEqual(align_tasks[0]['AC'], 2)
        self.assertEqual(align_tasks[0]['AG'], 3)
        self.assertEqual(align_tasks[0]['AT'], 4)
        self.assertEqual(align_tasks[0]['CA'], 5)
        self.assertEqual(align_tasks[0]['CC'], 6)
        self.assertEqual(align_tasks[0]['CG'], 7)
        self.assertEqual(align_tasks[0]['CT'], 8)
        self.assertEqual(align_tasks[0]['GA'], 9)
        self.assertEqual(align_tasks[0]['GC'], 10)
        self.assertEqual(align_tasks[0]['GG'], 11)
        self.assertEqual(align_tasks[0]['GT'], 12)
        self.assertEqual(align_tasks[0]['TA'], 13)
        self.assertEqual(align_tasks[0]['TC'], 14)
        self.assertEqual(align_tasks[0]['TG'], 15)
        self.assertEqual(align_tasks[0]['TT'], 16)
        self.assertEqual(align_tasks[0]['result_notification'], False)
        self.assertEqual(align_tasks[0]['mail_address'], 'user2_mail_address')
        self.assertEqual(align_tasks[0]['input_time'], '1')
        self.assertEqual(align_tasks[0]['output_time'], '2')

    def test_07_get_align_task_docfile(self):
        """get output docfile and file name for align task"""
        align_task = AlignTask.objects.create(user_id=self.user1.id, name='name3', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=True, gap_penalty='03', AA=13, AC=23, AG=33, AT=43, CA=53, CC=63, CG=73, CT=83, GA=93, GC=103, GG=113, GT=123, TA=133, TC=143, TG=153, TT=163, result_notification=True, mail_address='user1_mail_address', input_time='13', output_time='23')
        self.assertEqual(AlignTask.objects.all().count(), 1)
        result = views.get_align_task_docfile({'id' : str(align_task.id)}, self.user1)
        self.assertEqual(result['docfile'], self.out_docfile)
        self.assertEqual(result['file_name'], self.out_file_name)
        result = views.get_align_task_docfile({'id' : str(align_task.id)}, self.admin_user)
        self.assertEqual(result['docfile'], self.out_docfile)
        self.assertEqual(result['file_name'], self.out_file_name)
        result = views.get_align_task_docfile({'id' : str(align_task.id + 10)}, self.user1)
        self.assertEqual(len(result), 0)
        Document.objects.all().delete()
        result = views.get_align_task_docfile({'id' : str(align_task.id)}, self.user1)
        self.assertEqual(len(result), 0)

    def test_08_break_align_task(self):
        """break align task"""
        input_seq = '>seq\nAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAA\n'
        align_task = AlignTask.objects.create(user_id=self.user1.id, name='name3', sequence_file_id=self.seq_newdoc.id, reference_file_id=self.ref_newdoc.id, output_file_id=self.out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty='03', AA=13, AC=23, AG=33, AT=43, CA=53, CC=63, CG=73, CT=83, GA=93, GC=103, GG=113, GT=123, TA=133, TC=143, TG=153, TT=163, result_notification=False, mail_address='user1_mail_address', input_time='13', output_time='23')
        cmdmgr = dnaasmpy.CommandManager()
        cmdmgr.clearHistory()
        params1 = {'sequence': input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq, 
                   'reference': input_seq, 
                   'similarity_matrix_string': '1 -1 -1 -1 -1 1 -1 -1 -1 -1 1 -1 -1 -1 -1 1',
                   'AA': '1',
                   'AC': '-1',
                   'AG': '-1',
                   'AT': '-1',
                   'CA': '-1',
                   'CC': '1',
                   'CG': '-1',
                   'CT': '-1',
                   'GA': '-1',
                   'GC': '-1',
                   'GG': '1',
                   'GT': '-1',
                   'TA': '-1',
                   'TC': '-1',
                   'TG': '-1',
                   'TT': '1',
                   'align_algorithm': 'h', 
                   'circular': 'false', 
                   'gap_penalty': '-1'}
        align_cmd_id = cmdmgr.startAlign(align_task.id, params1)
        views.break_align_task({'id' : align_task.id}, self.user1)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(align_cmd_id) == dnaasmpy.INTERRUPTED:
                break
        self.assertEqual(cmdmgr.getState(align_cmd_id), dnaasmpy.INTERRUPTED)
        self.assertEqual(AlignTask.objects.all().count(), 1)
        params2 = {'sequence': input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq, 
                   'reference': input_seq, 
                   'similarity_matrix_string': '1 -1 -1 -1 -1 1 -1 -1 -1 -1 1 -1 -1 -1 -1 1',
                   'AA': '1',
                   'AC': '-1',
                   'AG': '-1',
                   'AT': '-1',
                   'CA': '-1',
                   'CC': '1',
                   'CG': '-1',
                   'CT': '-1',
                   'GA': '-1',
                   'GC': '-1',
                   'GG': '1',
                   'GT': '-1',
                   'TA': '-1',
                   'TC': '-1',
                   'TG': '-1',
                   'TT': '1',
                   'align_algorithm': 'h', 
                   'circular': 'false', 
                   'gap_penalty': '-1'}
        align_cmd_id_2 = cmdmgr.startAlign(align_task.id, params2)
        views.break_align_task({'id' : align_task.id,}, self.user2)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(align_cmd_id_2) == dnaasmpy.DONE:
                break
        self.assertEqual(cmdmgr.getState(align_cmd_id), dnaasmpy.INTERRUPTED)
        self.assertEqual(cmdmgr.getState(align_cmd_id_2), dnaasmpy.DONE)
        self.assertEqual(AlignTask.objects.all().count(), 1)
