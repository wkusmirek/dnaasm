## @file web/config/settings/base.py
#  @brief Django base settings file

"""
Django base settings file
"""

import os
BASE_DIR = os.path.dirname(os.path.dirname(__file__))

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = 'kw$@=pa)zdjmjx^6z65-+x3c5j+^ydyj1!t!@_q+z2qw06&1*i'

# SECURITY WARNING: don't run with debug turned on in production!
DEBUG = False
TEMPLATE_DEBUG = DEBUG

ALLOWED_HOSTS = ['*']

STATIC_URL = '/../media/'
STATIC_ROOT = os.path.join(BASE_DIR, '../media')

MEDIA_ROOT = '/var/tmp/dnaasm/media'
PRIVATE_PREFIX = 'private'
PUBLIC_PREFIX = 'public'
USERS_PREFIX = 'users'
PUBLIC_USERS_PREFIX = PUBLIC_PREFIX + '/' + USERS_PREFIX
PRIVATE_MEDIA_ROOT = MEDIA_ROOT + '/' + PRIVATE_PREFIX
PRIVATE_MEDIA_URL = MEDIA_ROOT + '/' + PRIVATE_PREFIX + '/'
PUBLIC_MEDIA_ROOT = MEDIA_ROOT + '/' + PUBLIC_PREFIX
PUBLIC_USERS_MEDIA_ROOT = MEDIA_ROOT + '/' + PUBLIC_USERS_PREFIX
EXAMPLE_FILES_MEDIA_ROOT = PUBLIC_MEDIA_ROOT + '/example_files'
EXAMPLE_FILES_ROOT = os.path.join(BASE_DIR, '../example_files/')

# Application definition
INSTALLED_APPS = (
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.sites',
    'django.contrib.messages',
    'django.contrib.staticfiles',
)

## Modules used within the project
PROJECT_APPS = (
    'version',
    'current',
    'dnaasmpy',
    'assembly',
    'user',
    'file',
    'align',
    'scaffold',
    'olc',
    'bst'
)

INSTALLED_APPS += PROJECT_APPS

MIDDLEWARE = (
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.common.CommonMiddleware',
#    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
)

ROOT_URLCONF = 'config.urls'

WSGI_APPLICATION = 'wsgi.application'

import version.models

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.postgresql_psycopg2',
        'NAME': version.models.get_db_name(),
        'HOST': '',
        'PORT': '5432',
        'USER': version.models.get_db_user(),
        'PASSWORD': version.models.get_db_password()
   }
}

# Internationalization
# https://docs.djangoproject.com/en/1.6/topics/i18n/

LANGUAGE_CODE = 'en-us'

TIME_ZONE = 'UTC'

USE_I18N = True

USE_L10N = True

USE_TZ = True

# Email settings

EMAIL_BACKEND = 'django.core.mail.backends.smtp.EmailBackend'

EMAIL_USE_TLS = True

EMAIL_HOST = 'smtp.gmail.com'

EMAIL_PORT = 587

EMAIL_HOST_USER = 'dnaasm@gmail.com'

EMAIL_HOST_PASSWORD = 'evarqdxmnbmdhloo'

DEFAULT_FROM_EMAIL = EMAIL_HOST_USER
