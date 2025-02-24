## @file web/urls.py
#  @brief Django urls

import version.models
# from django.conf.urls import url
from django.urls import include, path

from . import views

WEB_SRV_PREFIX = version.models.get_web_srv_prefix()

urlpatterns = [
    path(WEB_SRV_PREFIX + '/ajax/<module>', views.ajax, name='ajax'),
    path(WEB_SRV_PREFIX + '/ajax/<module>/', views.ajax, name='ajax'),
    path(WEB_SRV_PREFIX + '/ajax/<module>/<function>', views.ajax, name='ajax'),
    path(WEB_SRV_PREFIX + '/ajax/<module>/<function>/', views.ajax, name='ajax'),
    path('', views.index, name='index')
]
