## @file file/models.py
#  @brief table for documents

import logging
import ntpath
import os
import re
from django.contrib.auth.models import User
from django.db import models
from django.dispatch import receiver
from django.utils.translation import ugettext_lazy as _
from django.conf import settings

def content_file_name(instance, filename):
    return '/'.join([settings.PRIVATE_PREFIX, instance.user.username, ntpath.basename(str(filename))])

class Document(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    docfile = models.FileField(_("docfile"), upload_to=content_file_name)
    file_name = models.CharField(max_length=100)
    input_time = models.CharField(max_length=50)
    FASTA = 'FA'
    FASTQ = 'FQ'
    VCF = 'VCF'
    UNKNOWN = '??'
    FILE_FORMAT_CHOICES = (
        (FASTA, 'fasta'),
        (FASTQ, 'fastq'),
        (VCF, 'vcf'),
        (UNKNOWN, 'unknown'),
    )
    file_format = models.CharField(max_length=3,
                                      choices=FILE_FORMAT_CHOICES,
                                      default=UNKNOWN)

@receiver(models.signals.post_save, sender=Document)
def determine_file_format(sender, instance, **kwargs):
    """Determines file format (estimation based on first line) when `Document` object is changed."""
    #file_path = '/'.join([settings.PRIVATE_MEDIA_ROOT, instance.user.username, ntpath.basename(instance.docfile.path)])
    file_path = instance.docfile.path
    if os.path.isfile(file_path):
        with open(file_path, 'r') as f:
            first_line = f.readline()
            if re.match('>+.*', first_line, 0) != None:
                Document.objects.filter(id=instance.id).update(file_format=Document.FASTA)
            elif re.match('@+.*', first_line, 0) != None:
                Document.objects.filter(id=instance.id).update(file_format=Document.FASTQ)
            elif re.match('##+.*', first_line, 0) != None:
                Document.objects.filter(id=instance.id).update(file_format=Document.VCF)
            else:
                Document.objects.filter(id=instance.id).update(file_format=Document.UNKNOWN)
            f.close()
        return True
    return False

@receiver(models.signals.post_delete, sender=Document)
def auto_delete_file_on_delete(sender, instance, **kwargs):
    """Deletes file from filesystem when corresponding `Document` object is deleted."""
    if instance.docfile:
        if os.path.isfile(instance.docfile.path):
            os.remove(instance.docfile.path)
            return True
    return False

@receiver(models.signals.pre_save, sender=Document)
def auto_delete_file_on_change(sender, instance, **kwargs):
    """Deletes file from filesystem when corresponding `Document` object is changed."""
    if not instance.pk:
        return False
    try:
        old_file = Document.objects.get(pk=instance.pk).docfile
    except Document.DoesNotExist:
        logger = logging.getLogger('dnaasm.file.models')
        logger.error('Document does not exist.')
        return False

    new_file = instance.docfile
    if not old_file == new_file:
        if os.path.isfile(old_file.path):
            os.remove(old_file.path)
    return True
