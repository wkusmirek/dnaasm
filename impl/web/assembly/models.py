## @file assembly/models.py
#  @brief table for assembly tasks

from django.db import models
from django.contrib.auth.models import User
from file.models import Document

class AssemblyTask(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    i1_1 = models.ForeignKey(Document, related_name="i1_1", null=True, blank=True, on_delete=models.CASCADE)
    i1_2 = models.ForeignKey(Document, related_name="i1_2", null=True, blank=True, on_delete=models.CASCADE)
    o1_1 = models.ForeignKey(Document, related_name="o1_1", null=True, blank=True, on_delete=models.CASCADE)
    o1_2 = models.ForeignKey(Document, related_name="o1_2", null=True, blank=True, on_delete=models.CASCADE)
    output_file = models.ForeignKey(Document, related_name="assembly_task_output_file", null=False, blank=True, on_delete=models.CASCADE)
    name = models.CharField(max_length=30)
    k = models.IntegerField()
    genome_length = models.IntegerField()
    insert_size_mean_inward = models.FloatField()
    insert_size_std_dev_inward = models.FloatField()
    insert_size_mean_outward = models.FloatField()
    insert_size_std_dev_outward = models.FloatField()
    quality_threshold = models.IntegerField()
    bfcounter_threshold = models.IntegerField()
    single_edge_counter_threshold = models.IntegerField()
    paired_reads_pet_threshold_from = models.IntegerField()
    paired_reads_pet_threshold_to = models.IntegerField()
    paired_reads_mp_threshold_from = models.IntegerField()
    paired_reads_mp_threshold_to = models.IntegerField()
    NONE = '0'
    VELVET_PAIRED_READS_ALGORITHM = '1'
    PAIRED_READS_ALGORITHM_CHOICES = (
        (NONE, 'none'),
        (VELVET_PAIRED_READS_ALGORITHM, 'velvet_paired_graph_algorithm'),
   )
    paired_reads_algorithm = models.CharField(max_length=1,
                                      choices=PAIRED_READS_ALGORITHM_CHOICES,
                                      default=NONE)
    correct = models.BooleanField()
    result_notification = models.BooleanField()
    mail_address = models.CharField(max_length=40)
    input_time = models.CharField(max_length=30)
    output_time = models.CharField(max_length=30)
