## @file file/tests.py
#  @brief database interface unit testing

import os
import shutil
import django.test
from assembly.models import AssemblyTask
from align.models import AlignTask
from file.models import Document
from django.contrib.auth.models import User
from django.conf import settings
from . import views

class FileModelTestCase(django.test.TestCase):
    """test module model"""
    pass

class FileViewTestCase(django.test.TestCase):
    """test module interface"""

    def setUp(self):
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT)
        self.username1 = u'username1'
        self.password1 = u'password1'
        self.username2 = u'username2'
        self.password2 = u'password2'
        self.admin_username = u'username'
        self.admin_password = u'password'
        self.docfile1 = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + 'docfile1'
        self.docfile2 = settings.PRIVATE_PREFIX + '/' + self.username2 + '/' + 'docfile2'
        self.file_name1 = 'file_name1'
        self.file_name2 = 'file_name2'
        self.newdoc1_path = settings.MEDIA_ROOT + '/' + self.docfile1
        self.newdoc2_path = settings.MEDIA_ROOT + '/' + self.docfile2
        self.user1 = User.objects.create_user(self.username1)
        self.user1.set_password(self.password1)
        self.user1.save()
        self.user2 = User.objects.create_user(self.username2)
        self.user2.set_password(self.password2)
        self.user2.save()
        self.admin_user = User.objects.create_user(self.admin_username)
        self.admin_user.set_password(self.admin_password)
        self.admin_user.is_superuser = True
        self.admin_user.save()
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1)
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2)

    def tearDown(self):
        if os.path.exists(self.newdoc1_path):
            os.remove(self.newdoc1_path)
        if os.path.exists(self.newdoc2_path):
            os.remove(self.newdoc2_path)
        if os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1):
            shutil.rmtree(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1)
        if os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2):
            shutil.rmtree(settings.PRIVATE_MEDIA_ROOT + '/' + self.username2)
        AlignTask.objects.all().delete()
        AssemblyTask.objects.all().delete()
        Document.objects.all().delete()
        User.objects.all().delete()

    def test_01_get_user_files(self):
        """get all files for specified user"""
        self.assertEqual(Document.objects.all().count(), 0)
        newdoc1 = Document(user_id=self.user1.id, docfile=self.docfile1, file_name=self.file_name1, input_time='01', file_format=Document.FASTA)
        f = open(self.newdoc1_path, 'w+')
        f.write('>test\nAAA')
        f.close()
        newdoc1.save()
        newdoc2 = Document(user_id=self.user2.id, docfile=self.docfile2, file_name=self.file_name2, input_time='02', file_format=Document.FASTQ)
        f = open(self.newdoc2_path, 'w+')
        f.write('@test\nAAA\n+\nQQQ')
        f.close()
        newdoc2.save()
        files_user1 = views.get_user_files({}, self.user1)
        files_user2 = views.get_user_files({}, self.user2)
        self.assertEqual(len(files_user1), 1)
        self.assertEqual(files_user1[0]['docfile'], self.docfile1)
        self.assertEqual(files_user1[0]['file_name'], self.file_name1)
        self.assertEqual(files_user1[0]['input_time'], '01')
        self.assertEqual(files_user1[0]['file_format'], Document.FASTA)
        self.assertEqual(len(files_user2), 1)
        self.assertEqual(files_user2[0]['docfile'], self.docfile2)
        self.assertEqual(files_user2[0]['file_name'], self.file_name2)
        self.assertEqual(files_user2[0]['input_time'], '02')
        self.assertEqual(files_user2[0]['file_format'], Document.FASTQ)

    def test_02_get_all_files(self):
        """get all files for all users"""
        self.assertEqual(Document.objects.all().count(), 0)
        newdoc1 = Document(user_id=self.user1.id, docfile=self.docfile1, file_name=self.file_name1, input_time='01', file_format=Document.FASTA)
        f = open(self.newdoc1_path, 'w+')
        f.write('>test\nAAA')
        f.close()
        newdoc1.save()
        newdoc2 = Document(user_id=self.user2.id, docfile=self.docfile2, file_name=self.file_name2, input_time='02', file_format=Document.FASTQ)
        f = open(self.newdoc2_path, 'w+')
        f.write('@test\nAAA\n+\nQQQ')
        f.close()
        newdoc2.save()
        all_files = views.get_all_files({}, self.user1)
        self.assertEqual(len(all_files), 0)
        all_files = views.get_all_files({}, self.admin_user)
        self.assertEqual(len(all_files), 2)
        self.assertEqual(all_files[0]['docfile'], self.docfile1)
        self.assertEqual(all_files[0]['file_name'], self.file_name1)
        self.assertEqual(all_files[0]['input_time'], '01')
        self.assertEqual(all_files[0]['file_format'], Document.FASTA)
        self.assertEqual(all_files[0]['owner'], self.username1)
        self.assertEqual(all_files[1]['docfile'], self.docfile2)
        self.assertEqual(all_files[1]['file_name'], self.file_name2)
        self.assertEqual(all_files[1]['input_time'], '02')
        self.assertEqual(all_files[1]['file_format'], Document.FASTQ)
        self.assertEqual(all_files[1]['owner'], self.username2)

    def test_03_delete_user_files(self):
        """delete all user files"""
        self.assertEqual(Document.objects.all().count(), 0)
        newdoc1 = Document(user_id=self.user1.id, docfile=self.docfile1, file_name=self.file_name1, input_time='01', file_format=Document.UNKNOWN)
        open(self.newdoc1_path, 'a').close()
        newdoc1.save()
        newdoc2 = Document(user_id=self.user2.id, docfile=self.docfile2, file_name=self.file_name2, input_time='02', file_format=Document.UNKNOWN)
        open(self.newdoc2_path, 'a').close()
        newdoc2.save()
        files = Document.objects.all().values()
        self.assertEqual(len(files), 2)
        self.assertEqual(files[0]['user_id'], self.user1.id)
        self.assertEqual(files[0]['docfile'], self.docfile1)
        self.assertEqual(files[0]['file_name'], self.file_name1)
        self.assertEqual(files[0]['input_time'], '01')
        self.assertEqual(files[1]['user_id'], self.user2.id)
        self.assertEqual(files[1]['docfile'], self.docfile2)
        self.assertEqual(files[1]['file_name'], self.file_name2)
        self.assertEqual(files[1]['input_time'], '02')
        views.delete_user_files(self.user1.id, self.user1.username)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 1)
        self.assertEqual(files[0]['user_id'], self.user2.id)
        self.assertEqual(files[0]['docfile'], self.docfile2)
        self.assertEqual(files[0]['file_name'], self.file_name2)
        self.assertEqual(files[0]['input_time'], '02')
        self.assertEqual(os.path.isfile(self.newdoc1_path), False)
        self.assertEqual(os.path.isfile(self.newdoc2_path), True)
        views.delete_user_files(self.user2.id, self.user2.username)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 0)
        self.assertEqual(os.path.isfile(self.newdoc1_path), False)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)

    def test_04_delete_file(self):
        """delete single file"""
        self.assertEqual(Document.objects.all().count(), 0)
        newdoc1 = Document(user_id=self.user1.id, docfile=self.docfile1, file_name=self.file_name1, input_time='01', file_format=Document.UNKNOWN)
        open(self.newdoc1_path, 'a').close()
        newdoc1.save()
        newdoc2 = Document(user_id=self.user1.id, docfile=self.docfile2, file_name=self.file_name2, input_time='02', file_format=Document.UNKNOWN)
        open(self.newdoc2_path, 'a').close()
        newdoc2.save()
        file1 = Document.objects.filter(docfile=self.docfile1).values()
        file2 = Document.objects.filter(docfile=self.docfile2).values()
        self.assertEqual(Document.objects.all().count(), 2)
        AssemblyTask.objects.create(user_id=self.user1.id, i1_1_id=file1[0]['id'], i1_2_id=file1[0]['id'], o1_1_id=file1[0]['id'], o1_2_id=file1[0]['id'], output_file_id=file1[0]['id'], name='name7', k=7, genome_length=1, insert_size_mean_inward=1.0, insert_size_std_dev_inward=1.0, insert_size_mean_outward=1.0, insert_size_std_dev_outward=1.0, quality_threshold='0', bfcounter_threshold='0', single_edge_counter_threshold='0', paired_reads_pet_threshold_from='0', paired_reads_pet_threshold_to='0', paired_reads_mp_threshold_from='0', paired_reads_mp_threshold_to='0', paired_reads_algorithm=AssemblyTask.NONE, input_time='7', output_time='7', correct=True, result_notification=True, mail_address='mail_address')
        AlignTask.objects.create(user_id=self.user1.id, name='name', sequence_file_id=file2[0]['id'], reference_file_id=file2[0]['id'], output_file_id=file2[0]['id'], align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty=0, AA=1, AC=2, AG=3, AT=4, CA=5, CC=6, CG=7, CT=8, GA=9, GC=10, GG=11, GT=12, TA=13, TC=14, TG=15, TT=16, result_notification=False, mail_address='mail_address', input_time='1', output_time='2')
        views.delete_file({'docfile' : self.docfile1}, self.user1)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 2)
        self.assertEqual(files[0]['user_id'], self.user1.id)
        self.assertEqual(files[0]['docfile'], self.docfile1)
        self.assertEqual(files[0]['file_name'], self.file_name1)
        self.assertEqual(files[0]['input_time'], '01')
        self.assertEqual(files[1]['user_id'], self.user1.id)
        self.assertEqual(files[1]['docfile'], self.docfile2)
        self.assertEqual(files[1]['file_name'], self.file_name2)
        self.assertEqual(files[1]['input_time'], '02')
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), True)

        views.delete_file({'docfile' : self.docfile2}, self.user1)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 2)
        self.assertEqual(files[0]['user_id'], self.user1.id)
        self.assertEqual(files[0]['docfile'], self.docfile1)
        self.assertEqual(files[0]['file_name'], self.file_name1)
        self.assertEqual(files[0]['input_time'], '01')
        self.assertEqual(files[1]['user_id'], self.user1.id)
        self.assertEqual(files[1]['docfile'], self.docfile2)
        self.assertEqual(files[1]['file_name'], self.file_name2)
        self.assertEqual(files[1]['input_time'], '02')
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), True)

        AlignTask.objects.all().delete()

        views.delete_file({'docfile' : self.docfile2}, self.user1)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 1)
        self.assertEqual(files[0]['id'], file1[0]['id'])
        self.assertEqual(files[0]['docfile'], self.docfile1)
        self.assertEqual(files[0]['file_name'], self.file_name1)
        self.assertEqual(files[0]['input_time'], '01')
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)

        views.delete_file({'docfile' : self.docfile2}, self.user1)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 1)
        self.assertEqual(files[0]['id'], file1[0]['id'])
        self.assertEqual(files[0]['docfile'], self.docfile1)
        self.assertEqual(files[0]['file_name'], self.file_name1)
        self.assertEqual(files[0]['input_time'], '01')
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)

        views.delete_file({'docfile' : self.docfile1}, self.user1)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 1)
        self.assertEqual(files[0]['id'], file1[0]['id'])
        self.assertEqual(files[0]['docfile'], self.docfile1)
        self.assertEqual(files[0]['file_name'], self.file_name1)
        self.assertEqual(files[0]['input_time'], '01')
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)

        views.delete_file({'docfile' : self.docfile1}, self.admin_user)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 1)
        self.assertEqual(files[0]['id'], file1[0]['id'])
        self.assertEqual(files[0]['docfile'], self.docfile1)
        self.assertEqual(files[0]['file_name'], self.file_name1)
        self.assertEqual(files[0]['input_time'], '01')
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)

        AssemblyTask.objects.all().delete()

        views.delete_file({'docfile' : self.docfile1}, self.admin_user)
        files = Document.objects.all().values()
        self.assertEqual(len(files), 0)

    def test_05_save_content_to_file(self):
        """save content to file"""
        self.assertEqual(Document.objects.all().count(), 0)
        newdoc1 = Document(user_id=self.user1.id, docfile=self.docfile1, file_name=self.file_name1, input_time='01', file_format=Document.UNKNOWN)
        open(self.newdoc1_path, 'a').close()
        newdoc1.save()
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), '')
        file.close()
        self.assertEqual(Document.objects.filter(id=newdoc1.id).values('file_format')[0]['file_format'], Document.UNKNOWN)
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)
        views.save_content_to_file(newdoc1.id + 8, 'aaa')
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), '')
        file.close()
        self.assertEqual(Document.objects.filter(id=newdoc1.id).values('file_format')[0]['file_format'], Document.UNKNOWN)
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)
        views.save_content_to_file(newdoc1.id, 'aaa')
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), 'aaa')
        file.close()
        self.assertEqual(Document.objects.filter(id=newdoc1.id).values('file_format')[0]['file_format'], Document.UNKNOWN)
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)
        views.save_content_to_file(newdoc1.id, 'bbb')
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), 'bbb')
        file.close()
        self.assertEqual(Document.objects.filter(id=newdoc1.id).values('file_format')[0]['file_format'], Document.UNKNOWN)
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)
        views.save_content_to_file(newdoc1.id, '>test 01\nAACTG')
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), '>test 01\nAACTG')
        file.close()
        self.assertEqual(Document.objects.filter(id=newdoc1.id).values('file_format')[0]['file_format'], Document.FASTA)
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)
        views.save_content_to_file(newdoc1.id, '@test 02\nAACTG\n+\nBBBBB')
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), '@test 02\nAACTG\n+\nBBBBB')
        file.close()
        self.assertEqual(Document.objects.filter(id=newdoc1.id).values('file_format')[0]['file_format'], Document.FASTQ)
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)
        views.save_content_to_file(newdoc1.id, '##fileformat=VCFv4.0\n#CHROM	POS	ID	REF	ALT	QUAL	FILTER	INFO\n.	73	.	A	G	.	.	.')
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), '##fileformat=VCFv4.0\n#CHROM	POS	ID	REF	ALT	QUAL	FILTER	INFO\n.	73	.	A	G	.	.	.')
        file.close()
        self.assertEqual(Document.objects.filter(id=newdoc1.id).values('file_format')[0]['file_format'], Document.VCF)
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)
        views.save_content_to_file(newdoc1.id, '')
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), '')
        file.close()
        self.assertEqual(Document.objects.filter(id=newdoc1.id).values('file_format')[0]['file_format'], Document.UNKNOWN)
        self.assertEqual(os.path.isfile(self.newdoc1_path), True)
        self.assertEqual(os.path.isfile(self.newdoc2_path), False)

    def test_06_upload_file(self):
        """upload user file"""
        files = Document.objects.all().values()
        self.assertEqual(len(files), 0)
        from django.core.files.uploadedfile import SimpleUploadedFile
        test_file_field_name = u'test_file_field_name'
        test_file_field_content = u'test_file_field_content'
        test_file_field = SimpleUploadedFile(test_file_field_name, test_file_field_content.encode())
        views.upload_file(test_file_field, self.user1)
        files = Document.objects.all().values()
        self.assertEqual(files[0]['user_id'], self.user1.id)
        self.assertEqual(files[0]['docfile'], settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + str(test_file_field_name))
        self.assertEqual(files[0]['file_name'], test_file_field_name)
        self.assertEqual(len(files[0]['input_time']) > 0, True)
        self.assertEqual(os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1 + '/' + test_file_field_name), True)
        test_file = open(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1 + '/' + test_file_field_name, 'r')
        self.assertEqual(test_file.read(), test_file_field_content)
        test_file.close()

    def test_07_download_file(self):
        """download user file"""
        test_file_content = 'test_file_content'
        self.assertEqual(Document.objects.all().count(), 0)
        newdoc1 = Document(user_id=self.user1.id, docfile=self.docfile1, file_name=self.file_name1, input_time='01', file_format=Document.UNKNOWN)
        test_file = open(self.newdoc1_path, 'w+')
        test_file.write(test_file_content)
        test_file.close()
        newdoc1.save()
        file = open(self.newdoc1_path, 'r')
        self.assertEqual(file.read(), test_file_content)
        file.close()
        response = views.download_file({'docfile' : self.docfile1}, self.user1)
        self.assertEqual(response['Content-Length'], str(len(test_file_content)-1))
        self.assertEqual(response['Content-Disposition'], 'attachment; filename=' + self.file_name1)
        self.assertEqual(response['Content-Type'], 'text/html; charset=utf-8')
        response = views.download_file({'docfile' : self.docfile1}, self.admin_user)
        self.assertEqual(response['Content-Length'], str(len(test_file_content)-1))
        self.assertEqual(response['Content-Disposition'], 'attachment; filename=' + self.file_name1)
        self.assertEqual(response['Content-Type'], 'text/html; charset=utf-8')
        response = views.download_file({'docfile' : self.docfile1}, self.user2)
        self.assertEqual(response['Content-Type'], 'text/plain')
        self.assertEqual(response.content, b'No such file.')

    def test_08_get_file_contents(self):
        """get contents of file"""
        test_file_content = 'test_file_content'
        self.assertEqual(Document.objects.all().count(), 0)
        newdoc1 = Document(user_id=self.user1.id, docfile=self.docfile1, file_name=self.file_name1, input_time='01', file_format=Document.UNKNOWN)
        test_file = open(self.newdoc1_path, 'w+')
        test_file.write(test_file_content)
        test_file.close()
        newdoc1.save()
        newdoc2 = Document(user_id=self.user2.id, docfile=self.docfile2, file_name=self.file_name2, input_time='02', file_format=Document.UNKNOWN)
        test_file = open(self.newdoc2_path, 'w+')
        for _ in range(0, 500000):
            test_file.write(test_file_content)
        test_file.close()
        newdoc2.save()
        files = Document.objects.all().values()
        self.assertEqual(len(files), 2)
        self.assertEqual(files[0]['user_id'], self.user1.id)
        self.assertEqual(files[0]['docfile'], self.docfile1)
        self.assertEqual(files[0]['file_name'], self.file_name1)
        self.assertEqual(files[0]['input_time'], '01')
        self.assertEqual(files[1]['user_id'], self.user2.id)
        self.assertEqual(files[1]['docfile'], self.docfile2)
        self.assertEqual(files[1]['file_name'], self.file_name2)
        self.assertEqual(files[1]['input_time'], '02')
        return_data = views.get_file_contents({'docfile' : self.docfile2}, self.user1)
        self.assertEqual(return_data['status'], 'error')
        self.assertEqual(return_data['msg'], 'File does not exist.')
        return_data = views.get_file_contents({'docfile' : self.docfile2}, self.user2)
        self.assertEqual(return_data['status'], 'error')
        self.assertEqual(return_data['msg'], 'File is oversized.')
        return_data = views.get_file_contents({'docfile' : self.docfile1}, self.user1)
        self.assertEqual(return_data['status'], 'success')
        self.assertEqual(return_data['msg'], test_file_content)
        return_data = views.get_file_contents({'docfile' : self.docfile1}, self.admin_user)
        self.assertEqual(return_data['status'], 'success')
        self.assertEqual(return_data['msg'], test_file_content)

    def test_09_upload_example_files(self):
        """upload example files"""
        self.assertEqual(Document.objects.all().count(), 0)
        self.assertEqual(os.path.exists(settings.EXAMPLE_FILES_MEDIA_ROOT), True)
        _, _, example_files = next(os.walk(settings.EXAMPLE_FILES_MEDIA_ROOT))
        num_of_example_files = len(example_files)
        views.upload_example_files({}, self.user1)
        self.assertEqual(Document.objects.all().count(), num_of_example_files)
        _, _, example_files_in_user_dir = next(os.walk(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1))
        self.assertEqual(len(example_files_in_user_dir), num_of_example_files)
        files = Document.objects.all().values()
        actual_index = 0
        for file in example_files:
            self.assertEqual(files[actual_index]['user_id'], self.user1.id)
            self.assertEqual(files[actual_index]['docfile'], settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + file)
            self.assertEqual(files[actual_index]['file_name'], file)
            self.assertEqual(len(files[actual_index]['input_time']) > 0, True)
            actual_index = actual_index + 1
