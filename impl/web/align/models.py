## @file align/models.py
#  @brief table for align tasks

from django.db import models
from django.contrib.auth.models import User
from file.models import Document

class AlignTask(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    sequence_file = models.ForeignKey(Document, related_name="sequence_file", null=True, blank=True, on_delete=models.CASCADE)
    reference_file = models.ForeignKey(Document, related_name="reference_file", null=True, blank=True, on_delete=models.CASCADE)
    output_file = models.ForeignKey(Document, related_name="align_task_output_file", null=False, blank=True, on_delete=models.CASCADE)
    name = models.CharField(max_length=30)
    HIRSCHBERG = 'H'
    NEEDLEMAN_WUNSCH = 'NW'
    UNKNOWN = '?'
    ALIGN_ALGORITHM_CHOICES = (
        (HIRSCHBERG, 'hirschberg'),
        (NEEDLEMAN_WUNSCH, 'needleman_wunsch'),
        (UNKNOWN, 'unknown'),
   )
    align_algorithm = models.CharField(max_length=2,
                                      choices=ALIGN_ALGORITHM_CHOICES,
                                      default=UNKNOWN)
    circular = models.BooleanField()
    gap_penalty = models.IntegerField()
    AA = models.IntegerField()
    AC = models.IntegerField()
    AG = models.IntegerField()
    AT = models.IntegerField()
    CA = models.IntegerField()
    CC = models.IntegerField()
    CG = models.IntegerField()
    CT = models.IntegerField()
    GA = models.IntegerField()
    GC = models.IntegerField()
    GG = models.IntegerField()
    GT = models.IntegerField()
    TA = models.IntegerField()
    TC = models.IntegerField()
    TG = models.IntegerField()
    TT = models.IntegerField()
    result_notification = models.BooleanField()
    mail_address = models.CharField(max_length=40)
    input_time = models.CharField(max_length=30)
    output_time = models.CharField(max_length=30)
