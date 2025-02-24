# from django.core.urlresolvers import reverse
from django.urls import reverse
from django.contrib.auth.models import User
from django.test import TestCase
from django.conf import settings
from file.models import Document
import os, shutil, time

from dnaasmpy.views import start_bst_assembly_command, serve_finished_commands
from .models import BstAssemblyTask
from . import views


# class BstAssemblyTest(TestCase):
    # user_ = 'user1'
    # doc_in = 'doc_in'
    # doc_out = 'doc_out'
    # path = os.path.join(settings.PRIVATE_MEDIA_ROOT, user_)

    # def setUp(self):
        # self.user1 = User.objects.create_user(username=self.user_, password='test')
        # self.client.login(username=self.user_, password='test')

    # def tearDown(self):
        # if os.path.exists(self.path):
            # shutil.rmtree(self.path)

    # def create_test_file(self, filename, is_input=False):
        # if not os.path.exists(self.path):
            # os.makedirs(self.path)
        # fpath = os.path.join(self.path, filename)
        # f = open(fpath , 'w+')
        # if is_input:
            # f.write('@read_0\nAAGG\n+\n@read_1\nGGCC\n+\n')
        # f.close()
        # return os.path.join(settings.PRIVATE_PREFIX, self.user_, filename)

    # def check_output_file(self, doc, string):
        # result_file = open(doc.docfile.path, 'r')
        # content = result_file.read()
        # result_file.close()
        # self.assertEqual(content, string)

    # def test_get_user_assembly_tasks(self):
        # path = self.create_test_file('Task 2', True)
        # Document.objects.create(user=self.user1, docfile=path, file_name='test_file')
        # res = self.client.post(reverse('ajax', args=['bst', 'insert']), data={'task_name': 'Task 2',
                                                                              # 'input_file': 'test_file',
                                                                              # 'word_length': '4',
                                                                              # 'min_word_count': '1',
                                                                              # 'max_word_count': '10',
                                                                              # 'path_width': '1'})
        # task_id = str(res.json()['task_id'])
        # res = self.client.get(reverse('ajax', args=['bst', 'get_user_assembly_tasks']))
        # self.assertEqual(res.json()[task_id], {})
        # doc_out = Document.objects.get(user=self.user1, file_name='Task 2')
        # self.check_output_file(doc_out, '@res_0\nAAGGCC\n')

    # def test_start_bst_assembly_command(self):
        # input_file = self.create_test_file(self.doc_in, True)
        # output_file = self.create_test_file('Task 1')
        # doc_in = Document.objects.create(user=self.user1, docfile=input_file, file_name=self.doc_in, input_time='01')
        # doc_out = Document.objects.create(user=self.user1, docfile=output_file, file_name='Task 1', input_time='01')
        # task = BstAssemblyTask.objects.create(user=self.user1, task_name='Task 1', input_file=doc_in, output_file=doc_out, word_length=4, min_word_count=1, max_word_count=10, path_width=1)

        # res = start_bst_assembly_command({'task_id': task.id, 'word_length': "4", 'min_word_count': "1", 'input_file_path': doc_in.docfile.path, 'output_file_name': 'Task 1', 'max_word_count': '10', 'path_width': '1'})
        # self.assertGreaterEqual(res, 1)
        # serve_finished_commands()
        # self.check_output_file(doc_out, '@res_0\nAAGGCC\n')

    # def test_insert_and_get_docfile(self):
        # Document.objects.create(user=self.user1, docfile=self.doc_in, file_name='test_file')
        # res = self.client.post(reverse('ajax', args=['bst', 'insert']), data={'task_name': 'Test task',
                                                                              # 'input_file': 'test_file',
                                                                              # 'word_length': '10',
                                                                              # 'min_word_count': '1',
                                                                              # 'max_word_count': '10',
                                                                              # 'path_width': '1'})
        # res = self.client.get(reverse('ajax', args=['bst', 'get_assembly_task_docfile']), data={'id': res.json()['task_id']})
        # self.assertEqual(res.json()['file_name'], 'Test task')

    # def test_insert_task_with_wrong_data(self):
        # res = self.client.post(reverse('ajax', args=['bst', 'insert']))
        # self.assertEqual(res.json(), {})
        # res = self.client.get(reverse('ajax', args=['bst', 'insert']))
        # self.assertEqual(res.status_code, 404)

    # def test_insert_when_file_name_exists(self):
        # Document.objects.create(user=self.user1, docfile=self.doc_in, file_name='Test', input_time='01')
        # res = self.client.post(reverse('ajax', args=['bst', 'insert']), data={'task_name': 'Test'})
        # self.assertEqual(res.json()['status'], 'error')

    # def test_insert_task_with_wrong_input_file(self):
        # res = self.client.post(reverse('ajax', args=['bst', 'insert']), data={'task_name': 'Test', 'input_file': 'some_made_up_test_file'})
        # self.assertEqual(res.json()['status'], 'error')

    # def test_insert_task(self):
        # Document.objects.create(user=self.user1, docfile=self.doc_in, file_name='test_file')
        # res = self.client.post(reverse('ajax', args=['bst', 'insert']), data={'task_name': 'Test task',
                                                                              # 'input_file': 'test_file',
                                                                              # 'word_length': '10',
                                                                              # 'min_word_count': '1',
                                                                              # 'max_word_count': '10',
                                                                              # 'path_width': '1'})
        # self.assertEqual(BstAssemblyTask.objects.filter(task_name='Test task').count(), 1)
        # self.assertEqual(res.json()['status'], 'success')
        # self.assertGreaterEqual(res.json()['task_id'], 1)
        # self.assertTrue(res.json()['result_url'].endswith(os.path.join(settings.PUBLIC_USERS_PREFIX, self.user_, 'Test task')))
        # self.assertTrue(os.path.isfile(os.path.join(settings.PUBLIC_USERS_MEDIA_ROOT, self.user_, 'Test task')))

    # def test_task_docfile_with_wrong_data(self):
        # res = self.client.get(reverse('ajax', args=['bst', 'get_assembly_task_docfile']))
        # self.assertEqual(res.json(), {})
        # res = self.client.get(reverse('ajax', args=['bst', 'get_assembly_task_docfile']), data={'id':-5})
        # self.assertEqual(res.json(), {})

    # def test_create_assembly_task(self):
        # docfile_out = Document.objects.create(user=self.user1, docfile=self.doc_in, file_name='file_name1', input_time='01')
        # docfile_in = Document.objects.create(user=self.user1, docfile=self.doc_out, file_name='file_name2', input_time='01')

        # BstAssemblyTask.objects.create(user=self.user1, task_name='Task 1', input_file=docfile_in, output_file=docfile_out, word_length=100, min_word_count=1, max_word_count=10, path_width=1)

        # self.assertEqual(BstAssemblyTask.objects.count(), 1)

    # def test_get_assembly_task_docfile(self):
        # file_ = self.create_test_file(self.doc_out)
        # docfile_out = Document.objects.create(user=self.user1, docfile=file_, file_name=self.doc_out, input_time='01')
        # task = BstAssemblyTask.objects.create(user=self.user1, task_name='Task 1', output_file=docfile_out, word_length=100, min_word_count=1, max_word_count=10, path_width=1)

        # res = self.client.get(reverse('ajax', args=['bst', 'get_assembly_task_docfile']), data={'id': task.id})
        # self.assertEqual(res.json()['file_name'], self.doc_out)
        # self.assertEqual(res.json()['docfile'], file_)
