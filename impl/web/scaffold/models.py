## @file scaffold/models.py
#  @brief table for scaffolding tasks

from django.db import models
from django.contrib.auth.models import User
from file.models import Document
from assembly.models import AssemblyTask

class ScaffoldTask(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    assembly_task = models.ForeignKey(AssemblyTask, related_name="assembly_task", null=True, blank=True, on_delete=models.CASCADE)
    contigs_file = models.ForeignKey(Document, related_name="contigs_file", null=True, blank=True, on_delete=models.CASCADE)
    long_reads_file = models.ForeignKey(Document, related_name="long_reads_file", null=True, blank=True, on_delete=models.CASCADE)
    output_file = models.ForeignKey(Document, related_name="scaffold_task_output_file", null=False, blank=True, on_delete=models.CASCADE)
    name = models.CharField(max_length=30)
    kmer_size = models.IntegerField()
    distance = models.IntegerField()
    step = models.IntegerField()
    min_links = models.IntegerField()
    max_ratio = models.FloatField()
    min_contig_length = models.IntegerField()
    input_time = models.CharField(max_length=30)
    output_time = models.CharField(max_length=30)
