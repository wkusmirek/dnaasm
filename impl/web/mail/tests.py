## @file mail/tests.py
#  @brief sending mails unit testing

import django.test
from django.core import mail
from . import views

class MailViewTestCase(django.test.TestCase):
    """module view test"""

    def test_send_email(self):
        """check if service send proper mail when job is finished"""
        self.assertEquals(len(mail.outbox), 0)
        views.send_job_notification_mail('2016-01-31T14:18:10Z', [], 'docfile')
        self.assertEquals(len(mail.outbox), 0)

        views.send_job_notification_mail('', ['test1@server.com, test2@server.com'], 'docfile')
        self.assertEquals(len(mail.outbox), 1)
        self.assertEquals(len(mail.outbox[0].subject) > 0, True)
        self.assertEquals(len(mail.outbox[0].body) > 0, True)
        self.assertEquals(mail.outbox[0].from_email, 'dnaasm@gmail.com')
        self.assertEquals(mail.outbox[0].to, ['test1@server.com, test2@server.com'])

        views.send_job_notification_mail('2016-01-31T14:18:10Z', ['test3@server.com, test4@server.com'], 'docfile')
        self.assertEquals(len(mail.outbox), 2)
        self.assertEquals(len(mail.outbox[0].subject) > 0, True)
        self.assertEquals(len(mail.outbox[0].body) > 0, True)
        self.assertEquals(mail.outbox[0].from_email, 'dnaasm@gmail.com')
        self.assertEquals(mail.outbox[0].to, ['test1@server.com, test2@server.com'])
        self.assertEquals(len(mail.outbox[1].subject) > 0, True)
        self.assertEquals(len(mail.outbox[1].body) > 0, True)
        self.assertEquals(mail.outbox[1].from_email, 'dnaasm@gmail.com')
        self.assertEquals(mail.outbox[1].to, ['test3@server.com, test4@server.com'])
