import os, shutil, time
from django.contrib.auth.models import User
from django.test import TestCase
from django.conf import settings
from file.models import Document
from unittest.mock import patch
from assembly.models import AssemblyTask
from .models import ScaffoldTask
from . import views


class ScaffoldTest(TestCase):

    def setUp(self):
        self.username1 = 'username1'
        self.username2 = 'username2'
        self.admin_username = 'admin_username'
        self.user1 = User.objects.create_user(username=self.username1, password='test1')
        self.user2 = User.objects.create_user(username=self.username2, password='test2')
        self.admin_user = User.objects.create_user(username=self.admin_username, password='admin', is_superuser=True)

        self.path1 = os.path.join(settings.PRIVATE_MEDIA_ROOT, self.username1)
        self.path2 = os.path.join(settings.PRIVATE_MEDIA_ROOT, self.username2)
        if not os.path.exists(self.path1):
            os.makedirs(self.path1)
        if not os.path.exists(self.path2):
            os.makedirs(self.path2)
        self.contigs_file_name = 'contigs_test_file'
        self.contigs_docfile = settings.PRIVATE_PREFIX + '/'\
                               + self.username1 + '/' + self.contigs_file_name
        self.contigs_newdoc = Document(user_id=self.user1.id, docfile=self.contigs_docfile,
                                       file_name=self.contigs_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.contigs_docfile, 'w+').close()
        self.contigs_newdoc.save()
        self.reads_file_name = 'reads_test_file'
        self.reads_docfile = settings.PRIVATE_PREFIX + '/' \
                               + self.username1 + '/' + self.reads_file_name
        self.reads_newdoc = Document(user_id=self.user1.id, docfile=self.reads_docfile,
                                     file_name=self.reads_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.reads_docfile, 'w+').close()
        self.reads_newdoc.save()
        self.out_file_name = 'out_file_name'
        self.out_docfile = settings.PRIVATE_PREFIX + '/' \
                               + self.username1 + '/' + self.out_file_name
        self.out_newdoc = Document(user_id=self.user1.id, docfile=self.out_docfile,
                                   file_name=self.out_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.out_docfile, 'w+').close()
        self.out_newdoc.save()


    def tearDown(self):
        if os.path.exists(self.path1):
            shutil.rmtree(self.path1)
        if os.path.exists(self.path2):
            shutil.rmtree(self.path2)
        Document.objects.all().delete()
        ScaffoldTask.objects.all().delete()
        AssemblyTask.objects.all().delete()
        User.objects.all().delete()

    def test_insert_task_standalone(self):
        """insert standalone task and check if saved correctly"""
        self.assertEqual(ScaffoldTask.objects.all().count(), 0)
        task_data = {
            'name': 'name',
            'contigs_file_name': self.contigs_file_name,
            'long_reads_file_name': self.reads_file_name,
            'kmer_size': '15',
            'distance': '1000',
            'step': '1',
            'min_links': '4',
            'max_ratio': '0.3',
            'min_contig_length': '500'
        }

        with patch('dnaasmpy.views.start_scaffold_command') as mock_scaffold_start:
            res = views.insert(task_data, self.user1)
            self.assertEqual(len(mock_scaffold_start.mock_calls), 1)
        self.assertEqual(ScaffoldTask.objects.all().count(), 1)
        self.assertEqual(Document.objects.all().count(), 4)
        self.assertEqual(res['status'], 'success')
        self.assertTrue(res['task_id'] > 0)
        self.assertTrue(len(res['result_url']) > 0)
        tasks = ScaffoldTask.objects.all().values()
        self.assertEqual(tasks[0]['id'], res['task_id'])
        self.assertEqual(tasks[0]['name'], 'name')
        self.assertEqual(tasks[0]['contigs_file_id'], self.contigs_newdoc.id)
        self.assertEqual(tasks[0]['long_reads_file_id'], self.reads_newdoc.id)
        self.assertEqual(tasks[0]['output_file_id'], self.out_newdoc.id + 1)
        self.assertEqual(tasks[0]['kmer_size'], 15)
        self.assertEqual(tasks[0]['distance'], 1000)
        self.assertEqual(tasks[0]['step'], 1)
        self.assertEqual(tasks[0]['min_links'], 4)
        self.assertEqual(tasks[0]['max_ratio'], 0.3)
        self.assertEqual(tasks[0]['min_contig_length'], 500)
        self.assertEqual(len(tasks[0]['input_time']) > 0, True)
        self.assertEqual(tasks[0]['output_time'], '')
        file = Document.objects.all().values()
        self.assertEqual(file[0]['id'], self.contigs_newdoc.id)
        self.assertEqual(file[0]['docfile'], self.contigs_docfile)
        self.assertEqual(file[0]['file_name'], self.contigs_file_name)
        self.assertEqual(file[0]['input_time'], '01')
        self.assertEqual(file[1]['id'], self.reads_newdoc.id)
        self.assertEqual(file[1]['docfile'], self.reads_docfile)
        self.assertEqual(file[1]['file_name'], self.reads_file_name)
        self.assertEqual(file[1]['input_time'], '01')
        self.assertEqual(file[2]['id'], self.out_newdoc.id)
        self.assertEqual(file[2]['docfile'], self.out_docfile)
        self.assertEqual(file[2]['file_name'], self.out_file_name)
        self.assertEqual(file[2]['input_time'], '01')
        self.assertEqual(file[3]['id'], self.out_newdoc.id+1)
        self.assertEqual(file[3]['docfile'], settings.PUBLIC_USERS_PREFIX + '/' + self.username1 + '/name')
        self.assertEqual(file[3]['file_name'], 'name')
        self.assertEqual(file[3]['input_time'], '')
        
        # try add new task with same name - not allowed
        with patch('dnaasmpy.views.start_scaffold_command') as mock_scaffold_start:
            res = views.insert(task_data, self.user1)
            self.assertEqual(len(mock_scaffold_start.mock_calls), 0)
        self.assertEqual(ScaffoldTask.objects.all().count(), 1)
        self.assertEqual(Document.objects.all().count(), 4)
        self.assertEqual(res['status'], 'error')
        
        # add another task
        task_data['name'] = 'name2'
        res = views.insert(task_data, self.user1)
        self.assertEqual(ScaffoldTask.objects.all().count(), 2)
        self.assertEqual(Document.objects.all().count(), 5)
        self.assertEqual(res['status'], 'success')
        self.assertTrue(res['task_id'] > 0)
        self.assertTrue(len(res['result_url']) > 0)
        first_task = ScaffoldTask.objects.filter(name='name').values()
        second_task = ScaffoldTask.objects.filter(name='name2').values()
        tasks = ScaffoldTask.objects.all().values()
        self.assertEqual(tasks[0]['id'], first_task[0]['id'])
        self.assertEqual(tasks[0]['name'], 'name')
        self.assertEqual(tasks[0]['contigs_file_id'], self.contigs_newdoc.id)
        self.assertEqual(tasks[0]['long_reads_file_id'], self.reads_newdoc.id)
        self.assertEqual(tasks[0]['output_file_id'], self.out_newdoc.id + 1)
        self.assertEqual(tasks[0]['kmer_size'], 15)
        self.assertEqual(tasks[0]['distance'], 1000)
        self.assertEqual(tasks[0]['step'], 1)
        self.assertEqual(tasks[0]['min_links'], 4)
        self.assertEqual(tasks[0]['max_ratio'], 0.3)
        self.assertEqual(tasks[0]['min_contig_length'], 500)
        self.assertEqual(len(tasks[0]['input_time']) > 0, True)
        self.assertEqual(tasks[0]['output_time'], '')
        self.assertEqual(tasks[1]['id'], res['task_id'])
        self.assertEqual(tasks[1]['id'], second_task[0]['id'])
        self.assertEqual(tasks[1]['name'], 'name2')
        self.assertEqual(tasks[1]['contigs_file_id'], self.contigs_newdoc.id)
        self.assertEqual(tasks[1]['long_reads_file_id'], self.reads_newdoc.id)
        self.assertEqual(tasks[1]['output_file_id'], self.out_newdoc.id + 2)
        self.assertEqual(tasks[1]['kmer_size'], 15)
        self.assertEqual(tasks[1]['distance'], 1000)
        self.assertEqual(tasks[1]['step'], 1)
        self.assertEqual(tasks[1]['min_links'], 4)
        self.assertEqual(tasks[1]['max_ratio'], 0.3)
        self.assertEqual(tasks[1]['min_contig_length'], 500)
        self.assertEqual(len(tasks[1]['input_time']) > 0, True)
        self.assertEqual(tasks[1]['output_time'], '')
        file = Document.objects.all().values()
        self.assertEqual(file[3]['id'], self.out_newdoc.id + 1)
        self.assertEqual(file[3]['docfile'], settings.PUBLIC_USERS_PREFIX + '/' + self.username1 + '/name')
        self.assertEqual(file[3]['file_name'], 'name')
        self.assertEqual(file[3]['input_time'], '')
        self.assertEqual(file[4]['id'], self.out_newdoc.id + 2)
        self.assertEqual(file[4]['docfile'], settings.PUBLIC_USERS_PREFIX + '/' + self.username1 + '/name2')
        self.assertEqual(file[4]['file_name'], 'name2')
        self.assertEqual(file[4]['input_time'], '')

    def test_insert_with_related_assemblytask(self):
        """insert scaffold task that is linked with assemlby task"""
        self.assertEqual(ScaffoldTask.objects.all().count(), 0)
        self.assertEqual(AssemblyTask.objects.all().count(), 0)
        assembly_task = AssemblyTask.objects.create(
            user_id=self.user1.id,
            name='some_assembly',
            output_file_id=self.out_newdoc.id,
            k=3,
            genome_length=0,
            insert_size_mean_inward=0.0,
            insert_size_std_dev_inward=0.0,
            insert_size_mean_outward=0.0,
            insert_size_std_dev_outward=0.0,
            quality_threshold=0,
            bfcounter_threshold=0,
            single_edge_counter_threshold=0,
            paired_reads_pet_threshold_from=0,
            paired_reads_pet_threshold_to=0,
            paired_reads_mp_threshold_from=0,
            paired_reads_mp_threshold_to=0,
            paired_reads_algorithm='0',
            correct=False,
            result_notification=False,
            mail_address='user1_mail_address',
            input_time='1',
            output_time=''
        )
        self.assertEqual(AssemblyTask.objects.all().count(), 1)

        task_data = {
            'name': 'name',
            'assembly_task': 'some_assembly',
            'contigs_file_name': self.contigs_file_name,
            'long_reads_file_name': self.reads_file_name,
            'kmer_size': '15',
            'distance': '1000',
            'step': '1',
            'min_links': '4',
            'max_ratio': '0.3',
            'min_contig_length': '500'
        }

        # scaffold task should not be started because related assembly task
        # did not finish yet
        with patch('dnaasmpy.views.start_scaffold_command') as mock_scaffold_start:
            res = views.insert(task_data, self.user1)
            self.assertEqual(len(mock_scaffold_start.mock_calls), 0)
        self.assertEqual(ScaffoldTask.objects.all().count(), 1)
        self.assertEqual(Document.objects.all().count(), 4)

        # mock finished assembly task
        assembly_task.output_time = '1'
        assembly_task.save()

        # create new scaffold task related to finished assembly task - it should now start
        task_data['name'] = 'name2'
        with patch('dnaasmpy.views.start_scaffold_command') as mock_scaffold_start:
            res = views.insert(task_data, self.user1)
            self.assertEqual(len(mock_scaffold_start.mock_calls), 1)
        self.assertEqual(ScaffoldTask.objects.all().count(), 2)
        self.assertEqual(Document.objects.all().count(), 5)

    def test_break_scaffold_task(self):
        """break running scaffold task"""
        task = ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name',
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=100,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )

        with patch('dnaasmpy.views.break_command') as mock_break_command:
            self.assertTrue(views.break_scaffold_task({'id': task.id}, self.user1))
            self.assertEqual(len(mock_break_command.mock_calls), 1)

        # cannot break task of another user
        with patch('dnaasmpy.views.break_command') as mock_break_command:
            self.assertFalse(views.break_scaffold_task({'id': task.id}, self.user2))
            self.assertEqual(len(mock_break_command.mock_calls), 0)

    def test_delete_scaffold_task(self):
        """delete task from a database"""
        self.assertEqual(ScaffoldTask.objects.all().count(), 0)
        views.delete({'id':0}, self.user1)
        self.assertEqual(ScaffoldTask.objects.all().count(), 0)
        task1 = ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name1',
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=100,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        self.assertEqual(ScaffoldTask.objects.all().count(), 1)
        task2 = ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name2',
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=100,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        self.assertEqual(ScaffoldTask.objects.all().count(), 2)
        tasks = ScaffoldTask.objects.all().values()
        self.assertEqual(tasks[0]['id'], task1.id)
        self.assertEqual(tasks[1]['id'], task2.id)

        # try delete non-existing task - fail
        self.assertFalse(views.delete({'id':7}, self.user1))
        self.assertEqual(ScaffoldTask.objects.all().count(), 2)

        # try delete task of another user - fail
        self.assertFalse(views.delete({'id':task1.id}, self.user2))
        self.assertEqual(ScaffoldTask.objects.all().count(), 2)

        # delete own task - pass
        self.assertTrue(views.delete({'id':task1.id}, self.user1))
        self.assertEqual(ScaffoldTask.objects.all().count(), 1)
        tasks = ScaffoldTask.objects.all().values()
        self.assertEqual(tasks[0]['id'], task2.id)

        # delete task as superuser - pass
        self.assertTrue(views.delete({'id':task2.id}, self.admin_user))
        self.assertEqual(ScaffoldTask.objects.all().count(), 0)

    def test_delete_user_scaffold_tasks(self):
        """delete all user's task from database"""
        ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name1',
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=100,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name2',
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=100,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        ScaffoldTask.objects.create(
            user_id=self.user2.id,
            name='name3',
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=100,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        self.assertEqual(ScaffoldTask.objects.all().count(), 3)
        views.delete_user_scaffold_tasks(self.user1.id)
        self.assertEqual(ScaffoldTask.objects.all().count(), 1)
        views.delete_user_scaffold_tasks(self.user2.id)
        self.assertEqual(ScaffoldTask.objects.all().count(), 0)

    def test_is_file_used(self):
        """check if file is used by any task"""
        ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name',
            contigs_file=self.contigs_newdoc,
            long_reads_file=self.reads_newdoc,
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=100,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        self.assertEqual(ScaffoldTask.objects.all().count(), 1)
        self.assertEqual(views.is_file_used(self.contigs_newdoc.id), True)
        self.assertEqual(views.is_file_used(self.reads_newdoc.id), True)
        self.assertEqual(views.is_file_used(self.out_newdoc.id), False)

    def test_get_user_scaffold_tasks(self):
        """get all scaffold tasks for specified user from a database"""
        tasks = views.get_user_scaffold_tasks({}, self.user1)
        self.assertEqual(len(tasks), 0)
        ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name',
            contigs_file=self.contigs_newdoc,
            long_reads_file=self.reads_newdoc,
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=1000,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        task = ScaffoldTask.objects.filter(name='name')
        tasks = views.get_user_scaffold_tasks({}, self.user1)
        self.assertEqual(len(tasks), 1)
        self.assertEqual(tasks[0]['id'], task.values('id')[0]['id'])
        self.assertEqual(tasks[0]['name'], 'name')
        self.assertEqual(tasks[0]['contigs_file_name'], self.contigs_file_name)
        self.assertEqual(tasks[0]['long_reads_file_name'], self.reads_file_name)
        self.assertEqual(tasks[0]['kmer_size'], 15)
        self.assertEqual(tasks[0]['distance'], 1000)
        self.assertEqual(tasks[0]['step'], 1)
        self.assertEqual(tasks[0]['min_links'], 4)
        self.assertEqual(tasks[0]['max_ratio'], 0.3)
        self.assertEqual(tasks[0]['min_contig_length'], 500)
        self.assertEqual(len(tasks[0]['input_time']) > 0, True)
        self.assertEqual(tasks[0]['output_time'], '')
        self.assertEqual(tasks[0]['progress'], 1.0)

    def test_get_all_scaffold_tasks(self):
        """get all scaffold tasks for all users from a database"""
        tasks = views.get_all_scaffold_tasks({}, self.user1)
        self.assertEqual(len(tasks), 0)
        tasks = views.get_all_scaffold_tasks({}, self.admin_user)
        self.assertEqual(len(tasks), 0)

        ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name',
            contigs_file=self.contigs_newdoc,
            long_reads_file=self.reads_newdoc,
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=1000,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        task = ScaffoldTask.objects.filter(name='name')

        # regular user cannot get all tasks
        tasks = views.get_all_scaffold_tasks({}, self.user1)
        self.assertEqual(len(tasks), 0)

        # only admin can do it
        tasks = views.get_all_scaffold_tasks({}, self.admin_user)
        self.assertEqual(len(tasks), 1)
        self.assertEqual(tasks[0]['id'], task.values('id')[0]['id'])
        self.assertEqual(tasks[0]['name'], 'name')
        self.assertEqual(tasks[0]['contigs_file_name'], self.contigs_file_name)
        self.assertEqual(tasks[0]['long_reads_file_name'], self.reads_file_name)
        self.assertEqual(tasks[0]['kmer_size'], 15)
        self.assertEqual(tasks[0]['distance'], 1000)
        self.assertEqual(tasks[0]['step'], 1)
        self.assertEqual(tasks[0]['min_links'], 4)
        self.assertEqual(tasks[0]['max_ratio'], 0.3)
        self.assertEqual(tasks[0]['min_contig_length'], 500)
        self.assertEqual(len(tasks[0]['input_time']) > 0, True)
        self.assertEqual(tasks[0]['output_time'], '')
        self.assertEqual(tasks[0]['progress'], 1.0)
        self.assertEqual(tasks[0]['owner'], self.username1)

    def test_get_scaffold_task_docfile(self):
        """get output docfile and file name for scaffold task"""
        task = ScaffoldTask.objects.create(
            user_id=self.user1.id,
            name='name',
            contigs_file=self.contigs_newdoc,
            long_reads_file=self.reads_newdoc,
            output_file=self.out_newdoc,
            kmer_size=15,
            distance=1000,
            step=1,
            min_links=4,
            max_ratio=0.3,
            min_contig_length=500,
            input_time='1',
            output_time=''
        )
        self.assertEqual(ScaffoldTask.objects.all().count(), 1)

        result = views.get_scaffold_task_docfile({'id' : str(task.id)}, self.user1)
        self.assertEqual(result['docfile'], self.out_docfile)
        self.assertEqual(result['file_name'], self.out_file_name)

        result = views.get_scaffold_task_docfile({'id' : str(task.id)}, self.admin_user)
        self.assertEqual(result['docfile'], self.out_docfile)
        self.assertEqual(result['file_name'], self.out_file_name)

        result = views.get_scaffold_task_docfile({'id' : str(task.id + 10)}, self.user1)
        self.assertEqual(len(result), 0)

        Document.objects.all().delete()
        result = views.get_scaffold_task_docfile({'id' : str(task.id)}, self.user1)
        self.assertEqual(len(result), 0)
