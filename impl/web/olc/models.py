## @file scaffold/models.py
#  @brief table for scaffolding tasks

from django.db import models
from django.contrib.auth.models import User
from file.models import Document


class OlcAssemblyTask(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    long_reads_file = models.ForeignKey(Document,
                                            related_name="olc_long_reads_file",
                                            null=True,
                                            blank=True,
                                            on_delete=models.CASCADE)

    output_file = models.ForeignKey(Document,
                                    related_name="olc_task_output_file",
                                    null=False,
                                    blank=True,
                                    on_delete=models.CASCADE)
    name = models.CharField(max_length=30)
    kmer_length = models.IntegerField()
    sketch_num = models.IntegerField()
    min_jaccard_sim = models.FloatField()
    match_score = models.IntegerField()
    mismatch_score = models.IntegerField()
    gap_penalty = models.IntegerField()
    min_edge = models.IntegerField()
    min_contig_length = models.IntegerField()
    path_width = models.IntegerField()
    input_time = models.CharField(max_length=30)
    output_time = models.CharField(max_length=30)
