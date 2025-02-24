from django.db import models
from django.contrib.auth.models import User
from file.models import Document

class BstAssemblyTask(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    task_name = models.CharField(max_length=30)
    word_length = models.IntegerField()
    min_word_count = models.IntegerField()
    max_word_count = models.IntegerField()
    min_association = models.IntegerField()
    path_width = models.IntegerField()
    input_file = models.ForeignKey(Document,
                                   related_name="bst_input",
                                   null=True,
                                   blank=True,
                                   on_delete=models.CASCADE)
    output_file = models.ForeignKey(Document,
                                    related_name="bst_output",
                                    null=True,
                                    blank=True,
                                    on_delete=models.CASCADE)
    output_time = models.CharField(max_length=30)
