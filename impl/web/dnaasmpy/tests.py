## @file dnaasmpy/tests.py
#  @brief c++ calculation library Python API unit testing - basic tests

import os
import shutil
import time
import django.test
from align.models import AlignTask
from assembly.models import AssemblyTask
from file.models import Document
from django.contrib.auth.models import User
from django.conf import settings
from . import dnaasmpy
from . import views

class DnaasmPyLibraryTestCase(django.test.TestCase):
    """integration test, call C++ library interface from Python"""

    def setUp(self):
        cmdmgr = dnaasmpy.CommandManager()
        cmdmgr.clearHistory()

    def tearDown(self):
        pass

    def test_01_assembly_command(self):
        """assembly command test"""
        input_seq = '>seq\nAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAA\n'
        cmdmgr = dnaasmpy.CommandManager()
        params_assembly = {'paired_reads_algorithm': '1',
                           'i1_1': input_seq + input_seq,
                           'i1_2': input_seq + input_seq,
                           'o1_1': '',
                           'o1_2': '',
                           'k': '3',
                           'genome_length': '7',
                           'insert_size_mean_inward': '40',
                           'insert_size_std_dev_inward': '0',
                           'insert_size_mean_outward': '0',
                           'insert_size_std_dev_outward': '0',
                           'quality_threshold': '0',
                           'bfcounter_threshold': '0',
                           'single_edge_counter_threshold': '0',
                           'paired_reads_pet_threshold_from': '0',
                           'paired_reads_pet_threshold_to': '0',
                           'paired_reads_mp_threshold_from': '0',
                           'paired_reads_mp_threshold_to': '0',
                           'correct': 'false',
                           'output_file_name': 'test'}
        cmd_id = cmdmgr.startAssembly(1, params_assembly)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(cmd_id) == dnaasmpy.DONE:
                break
        self.assertEqual(cmdmgr.getState(cmd_id), dnaasmpy.DONE)
        self.assertEqual(len(cmdmgr.getIds()), 1)
        self.assertEqual(cmdmgr.getTaskId(cmd_id), 1)
        self.assertEqual(cmdmgr.getProgress(cmd_id), 1.0)
        #self.assertEqual(cmdmgr.getResult(cmd_id), ">test_0_5\r\nAATGA\r\n>test_1_4\r\nTAAT\r\n>test_2_4\r\nGAAT\r\n>test_3_4\r\nCAAT\r\n>test_4_4\r\nACCA\r\n>test_5_3\r\nTTA\r\n>test_6_3\r\nATT\r\n>test_7_3\r\nATA\r\n>test_8_3\r\nTAC\r\n>test_9_3\r\nACA\r\n>test_10_3\r\nCAG\r\n>test_11_3\r\nAGA\r\n>test_12_3\r\nGAC\r\n>test_13_3\r\nAAA\r\n>test_14_3\r\nAAC\r\n>test_15_3\r\nTAG\r\n")
        self.assertNotEqual(cmdmgr.getResult(cmd_id), "")  # without BFCounter (output file) application returns empty string
        self.assertEqual(cmdmgr.getIsSavedInDatabase(cmd_id), False)
        cmdmgr.setIsSavedInDatabase(cmd_id, True)
        self.assertEqual(cmdmgr.getIsSavedInDatabase(cmd_id), True)

    def test_02_align_command(self):
        """align command test"""
        input_ref = '>ref\nAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCA\n'
        input_seq = '>seq\nAATAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCA\n'
        cmdmgr = dnaasmpy.CommandManager()
        params_align = {'sequence': input_seq, 
                        'reference': input_ref, 
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
                        'gap_penalty': '-5'}
        cmd_id = cmdmgr.startAlign(1, params_align)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(cmd_id) == dnaasmpy.DONE:
                break
        self.assertEqual(cmdmgr.getState(cmd_id), dnaasmpy.DONE)
        self.assertEqual(len(cmdmgr.getIds()), 1)
        self.assertEqual(cmdmgr.getTaskId(cmd_id), 1)
        self.assertEqual(cmdmgr.getProgress(cmd_id), 1.0)
        self.assertEqual(cmdmgr.getResult(cmd_id), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n.\t3\tseq\tA\tT\t.\t.\t.\r\n")
        self.assertEqual(cmdmgr.getIsSavedInDatabase(cmd_id), False)
        cmdmgr.setIsSavedInDatabase(cmd_id, True)
        self.assertEqual(cmdmgr.getIsSavedInDatabase(cmd_id), True)

class DnaasmPyViewTestCase(django.test.TestCase):
    """module view test"""

    def setUp(self):
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT)
        self.username1 = u'username1'
        self.password1 = u'password1'
        self.mail1 = u'mail1'
        self.user1 = User.objects.create_user(self.username1, email=self.mail1)
        self.user1.set_password(self.password1)
        self.user1.save()
        if not os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1):
            os.makedirs(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1)
        self.sequence_file_name = 'sequence_file_name'
        self.sequence_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.sequence_file_name
        self.sequence_newdoc = Document(user_id=self.user1.id, docfile=self.sequence_docfile, file_name=self.sequence_file_name, input_time='01')
        open(settings.MEDIA_ROOT + '/' + self.sequence_docfile, 'w+').close()
        self.sequence_newdoc.save()
        self.reference_file_name = 'reference_file_name'
        self.reference_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.reference_file_name
        self.reference_newdoc = Document(user_id=self.user1.id, docfile=self.reference_docfile, file_name=self.reference_file_name, input_time='02')
        open(settings.MEDIA_ROOT + '/' + self.reference_docfile, 'w+').close()
        self.reference_newdoc.save()
        self.assembly_out_file_name = 'assembly_out_file_name'
        self.assembly_out_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.assembly_out_file_name
        self.assembly_out_newdoc = Document(user_id=self.user1.id, docfile=self.assembly_out_docfile, file_name=self.assembly_out_file_name, input_time='01')
        self.assembly_out_newdoc_path = settings.MEDIA_ROOT + '/' + self.assembly_out_docfile
        open(self.assembly_out_newdoc_path, 'w+').close()
        self.assembly_out_newdoc.save()
        self.align_out_file_name = 'align_out_file_name'
        self.align_out_docfile = settings.PRIVATE_PREFIX + '/' + self.username1 + '/' + self.align_out_file_name
        self.align_out_newdoc = Document(user_id=self.user1.id, docfile=self.align_out_docfile, file_name=self.align_out_file_name, input_time='01')
        self.align_out_newdoc_path = settings.MEDIA_ROOT + '/' + self.align_out_docfile
        open(self.align_out_newdoc_path, 'w+').close()
        self.align_out_newdoc.save()
        cmdmgr = dnaasmpy.CommandManager()
        cmdmgr.clearHistory()

    def tearDown(self):
        if os.path.exists(settings.MEDIA_ROOT + '/' + self.sequence_docfile):
            os.remove(settings.MEDIA_ROOT + '/' + self.sequence_docfile)
        if os.path.exists(settings.MEDIA_ROOT + '/' + self.reference_docfile):
            os.remove(settings.MEDIA_ROOT + '/' + self.reference_docfile)
        if os.path.exists(settings.MEDIA_ROOT + '/' + self.assembly_out_docfile):
            os.remove(settings.MEDIA_ROOT + '/' + self.assembly_out_docfile)
        if os.path.exists(settings.MEDIA_ROOT + '/' + self.align_out_docfile):
            os.remove(settings.MEDIA_ROOT + '/' + self.align_out_docfile)
        if os.path.exists(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1):
            shutil.rmtree(settings.PRIVATE_MEDIA_ROOT + '/' + self.username1)
        Document.objects.all().delete()
        AlignTask.objects.all().delete()
        AssemblyTask.objects.all().delete()
        User.objects.all().delete()

    def test_01_get_commands(self):
        """check if service return proper dict for align and assembly commands"""
        cmdmgr = dnaasmpy.CommandManager()
        align_task_id = 1
        assembly_task_id = 1
        input_seq = 'AATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAA'
        input_ref = '>ref\nAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAA\n'
        dict_assembly = views.get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        dict_align = views.get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
        self.assertEqual(len(dict_assembly), 0)
        self.assertEqual(len(dict_align), 0)
        self.assertEqual(dict_assembly, {})
        self.assertEqual(dict_align, {})
        params_align = {'sequence': '>seq\n' + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq, 
                        'reference': input_ref, 
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
        align_cmd_id = cmdmgr.startAlign(align_task_id, params_align)
        dict_align = views.get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
        dict_assembly = views.get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        self.assertEqual(len(dict_assembly), 0)
        self.assertEqual(len(dict_align), 1)
        self.assertEqual(dict_assembly, {})
        self.assertEqual(dict_align[0]['id'], align_task_id)
        self.assertEqual(dict_align[0]['state'] != 'DONE', True)
        self.assertEqual(dict_align[0]['progress'] >= 0.0, True)
        self.assertEqual(dict_align[0]['progress'] <= 1.0, True)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(align_cmd_id) == dnaasmpy.DONE:
                break
        dict_assembly = views.get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        dict_align = views.get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
        self.assertEqual(len(dict_assembly), 0)
        self.assertEqual(len(dict_align), 0)
        self.assertEqual(dict_assembly, {})
        self.assertEqual(dict_align, {})

        params_assembly = {'paired_reads_algorithm': '1',
                           'i1_1': '>seq\n' + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq,
                           'i1_2': '>seq\n' + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq,
                           'o1_1': '',
                           'o1_2': '',
                           'k': '3',
                           'genome_length': '7',
                           'insert_size_mean_inward': '40',
                           'insert_size_std_dev_inward': '0',
                           'insert_size_mean_outward': '0',
                           'insert_size_std_dev_outward': '0',
                           'quality_threshold': '0',
                           'bfcounter_threshold': '0',
                           'single_edge_counter_threshold': '0',
                           'paired_reads_pet_threshold_from': '0',
                           'paired_reads_pet_threshold_to': '0',
                           'paired_reads_mp_threshold_from': '0',
                           'paired_reads_mp_threshold_to': '0',
                           'correct': 'false',
                           'output_file_name': 'test'}
        assembly_cmd_id = cmdmgr.startAssembly(assembly_task_id, params_assembly)
        dict_assembly = views.get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        dict_align = views.get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
        self.assertEqual(len(dict_assembly), 1)
        self.assertEqual(len(dict_align), 0)
        self.assertEqual(dict_align, {})
        self.assertEqual(dict_assembly[0]['id'], assembly_task_id)
        self.assertEqual(dict_assembly[0]['state'] != 'DONE', True)
        self.assertEqual(dict_assembly[0]['progress'] >= 0.0, True)
        self.assertEqual(dict_assembly[0]['progress'] <= 1.0, True)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(assembly_cmd_id) == dnaasmpy.DONE:
                break
        dict_assembly = views.get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        dict_align = views.get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
        self.assertEqual(len(dict_assembly), 0)
        self.assertEqual(len(dict_align), 0)
        self.assertEqual(dict_assembly, {})
        self.assertEqual(dict_align, {})

        assembly_cmd_id = cmdmgr.startAssembly(assembly_task_id, params_assembly)
        align_cmd_id = cmdmgr.startAlign(align_task_id, params_align)
        dict_assembly = views.get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        dict_align = views.get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
        self.assertEqual(len(dict_assembly), 1)
        self.assertEqual(len(dict_align), 1)
        self.assertEqual(dict_align[0]['id'], align_task_id)
        self.assertEqual(dict_align[0]['state'] != 'DONE', True)
        self.assertEqual(dict_align[0]['progress'] >= 0.0, True)
        self.assertEqual(dict_align[0]['progress'] <= 1.0, True)
        self.assertEqual(dict_assembly[0]['id'], assembly_task_id)
        self.assertEqual(dict_assembly[0]['state'] != 'DONE', True)
        self.assertEqual(dict_assembly[0]['progress'] >= 0.0, True)
        self.assertEqual(dict_assembly[0]['progress'] <= 1.0, True)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(align_cmd_id) == dnaasmpy.DONE and cmdmgr.getState(assembly_cmd_id) == dnaasmpy.DONE:
                break
        dict_assembly = views.get_commands({'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        dict_align = views.get_commands({'command_type' : 'ALIGN_COMMAND_TYPE'})
        self.assertEqual(len(dict_assembly), 0)
        self.assertEqual(len(dict_align), 0)
        self.assertEqual(dict_assembly, {})
        self.assertEqual(dict_align, {})

    def test_02_break_command(self):
        """break command test"""
        input_seq = 'AATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAA'
        input_ref = '>seq\nACTACTTTACGCTACGACCATCTACGCGCATCATACATCTACGCGACTACTCATCATCATCAGCGGGGCATCATCGCAGCATCTCTCATCGCGCGACTCATCGACGACGACTACTCTCTACGCAGCAGCATCTACTACTTTCATCAGCGGGA\n'
        align_task_id = 1
        assembly_task_id = 1
        cmdmgr = dnaasmpy.CommandManager()
        params_align = {'sequence': '>seq\n' + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq, 
                        'reference': input_ref, 
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
        align_cmd_id = cmdmgr.startAlign(align_task_id, params_align)
        views.break_command({'task_id' : align_task_id, 'command_type' : 'ALIGN_COMMAND_TYPE'})
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(align_cmd_id) == dnaasmpy.INTERRUPTED:
                break
        self.assertEqual(cmdmgr.getState(align_cmd_id), dnaasmpy.INTERRUPTED)
        params_assembly = {'paired_reads_algorithm': '1',
                           'i1_1': '>seq\n' + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq,
                           'i1_2': '>seq\n' + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq + input_seq,
                           'o1_1': '',
                           'o1_2': '',
                           'k': '3',
                           'genome_length': '7',
                           'insert_size_mean_inward': '40',
                           'insert_size_std_dev_inward': '0',
                           'insert_size_mean_outward': '0',
                           'insert_size_std_dev_outward': '0',
                           'quality_threshold': '0',
                           'bfcounter_threshold': '0',
                           'single_edge_counter_threshold': '0',
                           'paired_reads_pet_threshold_from': '0',
                           'paired_reads_pet_threshold_to': '0',
                           'paired_reads_mp_threshold_from': '0',
                           'paired_reads_mp_threshold_to': '0',
                           'correct': 'false',
                           'output_file_name': 'test'}
        assembly_cmd_id = cmdmgr.startAssembly(assembly_task_id, params_assembly)
        views.break_command({'task_id' : assembly_task_id, 'command_type' : 'ASSEMBLY_COMMAND_TYPE'})
        assembly_cmd_id_2 = cmdmgr.startAssembly(assembly_task_id, params_assembly)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(assembly_cmd_id) == dnaasmpy.INTERRUPTED and cmdmgr.getState(assembly_cmd_id_2) == dnaasmpy.DONE:
                break
        self.assertEqual(cmdmgr.getState(assembly_cmd_id), dnaasmpy.INTERRUPTED)
        self.assertEqual(cmdmgr.getState(assembly_cmd_id_2), dnaasmpy.DONE)
        self.assertEqual(cmdmgr.getState(align_cmd_id), dnaasmpy.INTERRUPTED)

    def test_03_serve_finished_commands(self):
        """serve finished commands test"""
        from django.core import mail
        input_seq = '>seq\nAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAAAATTAAAACAGAAAAATACCAAAAAAATAAAAATGAAAAACCAAAAAAAAATGAAAAATAGACCAAATAAAAAAAA\n'
        cmdmgr = dnaasmpy.CommandManager()
        assembly_task = AssemblyTask.objects.create(user_id=self.user1.id, name='name', i1_1_id=self.sequence_newdoc.id, i1_2_id=self.sequence_newdoc.id, o1_1_id=self.sequence_newdoc.id, o1_2_id=self.sequence_newdoc.id, output_file_id=self.assembly_out_newdoc.id, k=5, genome_length=1, insert_size_mean_inward=1.0, insert_size_std_dev_inward=0.0, insert_size_mean_outward=1.0, insert_size_std_dev_outward=0.0, quality_threshold='0', bfcounter_threshold='0', single_edge_counter_threshold='0', paired_reads_pet_threshold_from='0', paired_reads_pet_threshold_to='0', paired_reads_mp_threshold_from='0', paired_reads_mp_threshold_to='0', paired_reads_algorithm='0', input_time='1', output_time='', correct=True, result_notification=True, mail_address='mail_address')
        align_task = AlignTask.objects.create(user_id=self.user1.id, name='name', sequence_file_id=self.sequence_newdoc.id, reference_file_id=self.sequence_newdoc.id, output_file_id=self.align_out_newdoc.id, align_algorithm=AlignTask.HIRSCHBERG, circular=False, gap_penalty=0, AA=1, AC=2, AG=3, AT=4, CA=5, CC=6, CG=7, CT=8, GA=9, GC=10, GG=11, GT=12, TA=13, TC=14, TG=15, TT=16, result_notification=False, mail_address='mail_address', input_time='1', output_time='')
        params_assembly = {'paired_reads_algorithm': '1',
                           'i1_1': input_seq,
                           'i1_2': input_seq,
                           'o1_1': '',
                           'o1_2': '',
                           'k': '3',
                           'genome_length': '180',
                           'insert_size_mean_inward': '40',
                           'insert_size_std_dev_inward': '0',
                           'insert_size_mean_outward': '0',
                           'insert_size_std_dev_outward': '0',
                           'quality_threshold': '0',
                           'bfcounter_threshold': '0',
                           'single_edge_counter_threshold': '0',
                           'paired_reads_pet_threshold_from': '0',
                           'paired_reads_pet_threshold_to': '0',
                           'paired_reads_mp_threshold_from': '0',
                           'paired_reads_mp_threshold_to': '0',
                           'correct': 'false',
                           'output_file_name': 'test'}
        assembly_cmd_id = cmdmgr.startAssembly(assembly_task.id, params_assembly)
        params_align = {'sequence': input_seq, 
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
        align_cmd_id = cmdmgr.startAlign(align_task.id, params_align)
        for _ in range(100):
            time.sleep(0.1)
            if cmdmgr.getState(align_cmd_id) == dnaasmpy.DONE and cmdmgr.getState(assembly_cmd_id) == dnaasmpy.DONE:
                break
        self.assertEqual(cmdmgr.getState(assembly_cmd_id), dnaasmpy.DONE)
        self.assertEqual(cmdmgr.getState(align_cmd_id), dnaasmpy.DONE)
        self.assertEqual(cmdmgr.getProgress(assembly_cmd_id), 1.0)
        self.assertEqual(cmdmgr.getProgress(align_cmd_id), 1.0)
        self.assertEqual(cmdmgr.getTaskId(assembly_cmd_id), assembly_task.id)
        self.assertEqual(cmdmgr.getTaskId(align_cmd_id), align_task.id)
        self.assertEqual(cmdmgr.getIsSavedInDatabase(assembly_cmd_id), False)
        self.assertEqual(cmdmgr.getIsSavedInDatabase(align_cmd_id), False)
        #self.assertEqual(cmdmgr.getResult(assembly_cmd_id), u'>test_0_4\r\nTAAT\r\n>test_1_4\r\nGAAT\r\n>test_2_4\r\nCAAT\r\n>test_3_4\r\nATTA\r\n>test_4_4\r\nACCA\r\n>test_5_4\r\nATGA\r\n>test_6_3\r\nAAA\r\n>test_7_3\r\nAAC\r\n>test_8_3\r\nACA\r\n>test_9_3\r\nCAG\r\n>test_10_3\r\nAGA\r\n>test_11_3\r\nATA\r\n>test_12_3\r\nTAC\r\n>test_13_3\r\nGAC\r\n>test_14_3\r\nTAG\r\n')
        self.assertNotEqual(cmdmgr.getResult(assembly_cmd_id), "")
        self.assertEqual(cmdmgr.getResult(align_cmd_id), u'##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n')
        align_task = AlignTask.objects.filter(name='name').values()
        assembly_task = AssemblyTask.objects.filter(name='name').values()
        self.assertEqual(align_task[0]['output_time'], '')
        self.assertEqual(assembly_task[0]['output_time'], '')
        file = open(self.assembly_out_newdoc_path, 'r')
        self.assertEqual(file.read().replace('\r', ''), '')
        file.close()
        file = open(self.align_out_newdoc_path, 'r')
        self.assertEqual(file.read().replace('\r', ''), '')
        file.close()
        self.max_diff = None
        views.serve_finished_commands()
        self.assertEqual(cmdmgr.getState(assembly_cmd_id), dnaasmpy.DONE)
        self.assertEqual(cmdmgr.getState(align_cmd_id), dnaasmpy.DONE)
        self.assertEqual(cmdmgr.getProgress(assembly_cmd_id), 1.0)
        self.assertEqual(cmdmgr.getProgress(align_cmd_id), 1.0)
        self.assertEqual(cmdmgr.getTaskId(assembly_cmd_id), assembly_task[0]['id'])
        self.assertEqual(cmdmgr.getTaskId(align_cmd_id), align_task[0]['id'])
        self.assertEqual(cmdmgr.getIsSavedInDatabase(assembly_cmd_id), True)
        self.assertEqual(cmdmgr.getIsSavedInDatabase(align_cmd_id), True)
        #self.assertEqual(cmdmgr.getResult(assembly_cmd_id), u'>test_0_4\r\nTAAT\r\n>test_1_4\r\nGAAT\r\n>test_2_4\r\nCAAT\r\n>test_3_4\r\nATTA\r\n>test_4_4\r\nACCA\r\n>test_5_4\r\nATGA\r\n>test_6_3\r\nAAA\r\n>test_7_3\r\nAAC\r\n>test_8_3\r\nACA\r\n>test_9_3\r\nCAG\r\n>test_10_3\r\nAGA\r\n>test_11_3\r\nATA\r\n>test_12_3\r\nTAC\r\n>test_13_3\r\nGAC\r\n>test_14_3\r\nTAG\r\n')
        self.assertNotEqual(cmdmgr.getResult(assembly_cmd_id), "")
        self.assertEqual(cmdmgr.getResult(align_cmd_id), u'##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n')
        align_task = AlignTask.objects.filter(name='name').values()
        assembly_task = AssemblyTask.objects.filter(name='name').values()
        self.assertEqual(len(align_task[0]['output_time']) > 0, True)
        self.assertEqual(len(assembly_task[0]['output_time']) > 0, True)
        file = open(self.assembly_out_newdoc_path, 'r')
        #self.assertEqual(file.read().replace('\r', ''), u'>test_0_4\nTAAT\n>test_1_4\nGAAT\n>test_2_4\nCAAT\n>test_3_4\nATTA\n>test_4_4\nACCA\n>test_5_4\nATGA\n>test_6_3\nAAA\n>test_7_3\nAAC\n>test_8_3\nACA\n>test_9_3\nCAG\n>test_10_3\nAGA\n>test_11_3\nATA\n>test_12_3\nTAC\n>test_13_3\nGAC\n>test_14_3\nTAG\n')
        self.assertNotEqual(file.read().replace('\r', ''), "")
        file.close()
        file = open(self.align_out_newdoc_path, 'r')
        self.assertEqual(file.read().replace('\r', ''), u'##fileformat=VCFv4.0\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\n')
        file.close()

        self.assertEquals(len(mail.outbox), 1)
        self.assertEquals(len(mail.outbox[0].subject) > 0, True)
        self.assertEquals(len(mail.outbox[0].body) > 0, True)
        self.assertEquals(mail.outbox[0].from_email, 'dnaasm@gmail.com')
        self.assertEquals(mail.outbox[0].to, ['mail_address'])
