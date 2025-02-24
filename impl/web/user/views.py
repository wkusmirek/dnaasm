## @file user/views.py
#  @brief web interface for user operations

"""
web interface for user operations
"""

import logging
import random
import re
import string
from datetime import datetime
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.models import User

def add_and_login_guest_user(request):
    """add new guest user and log in"""
    out_dict = dict()
    username = ''.join(random.SystemRandom().choice(string.ascii_uppercase) for _ in range(10)) + ''.join(random.SystemRandom().choice(string.digits) for _ in range(10)) + ''.join(random.SystemRandom().choice(string.ascii_lowercase) for _ in range(10))
    password = ''.join(random.SystemRandom().choice(string.ascii_uppercase + string.digits) for _ in range(30))
    try:
        user = User.objects.get(username__exact=username)
    except User.DoesNotExist:
        logger = logging.getLogger('dnaasm.user.views')
        logger.error('User ' + username + 'does not exist')
        user = None
    if user is not None:
        return add_and_login_guest_user(request)
    else:
        user = User.objects.create_user(username)
        user.set_password(password)
        user.save()
        user = authenticate(username=username, password=password)
        if user is not None:
            login(request, user)
            out_dict = {'status' : 'success', 'msg' : 'You have logged in successfully to new guest user.', 'username' : username}
        else:
            out_dict = {'status' : 'error', 'msg' : 'Invalid username or password.', 'username' : ''}
    return out_dict

def add_user(params):
    """add new user"""
    out_dict = dict()
    username = str(params['username'])
    password = str(params['password'])
    mail = str(params['mail'])
    if re.match('[A-Z]{10}\d{10}[a-z]{10}', username, 0) is not None:
        out_dict = {'status' : 'error', 'msg' : 'Your username is a string pattern composed for guest users, please change it.'}
    else:
        try:
            user = User.objects.get(username__exact=username)
        except User.DoesNotExist:
            logger = logging.getLogger('dnaasm.user.views')
            logger.error('User ' + username + ' does not exist')
            user = None
        if user is not None:
            out_dict = {'status' : 'error', 'msg' : 'Username in use, please change it.'}
        else:
            user = User.objects.create_user(username, email=mail)
            user.set_password(password)
            user.save()
            out_dict = {'status' : 'success', 'msg' : 'New user added.'}
    return out_dict

def delete_user(request):
    """delete user"""
    from assembly.views import delete_user_assembly_tasks
    from align.views import delete_user_align_tasks
    from file.views import delete_user_files
    username = request.POST['username']
    password = ''
    if 'password' in request.POST:
        password = request.POST['password']
    auth_user = authenticate(username=username, password=password)
    if request.user.is_authenticated and (request.user.is_superuser or auth_user is not None):
        try:
            user = User.objects.get(username__exact=username)
        except User.DoesNotExist:
            logger = logging.getLogger('dnaasm.user.views')
            logger.error('User ' + username + ' does not exist')
            return {'status' : 'error', 'msg' : "User doesn't exist."}
        user_id = get_user_id(username)
        delete_user_align_tasks(user_id)
        delete_user_assembly_tasks(user_id)
        delete_user_files(user_id, username)
        user.delete()
        if request.user.username == username:
            logout(request)
        return {'status' : 'success', 'msg' : 'User deleted.'}
    else:
        return {'status' : 'error', 'msg' : "Invalid password."}

def delete_guest_users(offset_time):
    """delete guest user"""
    from assembly.views import delete_user_assembly_tasks
    from align.views import delete_user_align_tasks
    from file.views import delete_user_files
    users = User.objects.all().values()
    num_deleted = 0
    for user in users:
        username = user['username']
        user_id = user['id']
        if re.match('[A-Z]{10}\d{10}[a-z]{10}', username, 0) is not None:
            if user['date_joined'] is not None and datetime.now().replace(tzinfo=None) > user['date_joined'].replace(tzinfo=None) + offset_time:
                try:
                    user = User.objects.get(username__exact=username)
                except User.DoesNotExist:
                    logger = logging.getLogger('dnaasm.user.views')
                    logger.error('User ' + username + ' does not exist')
                    continue
                delete_user_align_tasks(user_id)
                delete_user_assembly_tasks(user_id)
                delete_user_files(user_id, username)
                user.delete()
                num_deleted += 1
    return num_deleted

def logout_user(request):
    """logout user"""
    logout(request)

def login_user(request):
    """login user"""
    username = request.POST['username']
    password = request.POST['password']
    user = authenticate(username=username, password=password)
    if user is not None:
        login(request, user)
        out_dict = {'status' : 'success', 'msg' : 'You have logged in successfully.', 'isSuperuser' : user.is_superuser}
    else:
        out_dict = {'status' : 'error', 'msg' : "Invalid username or password.", 'isSuperuser' : ''}
    return out_dict

def get_users(params, user):
    """get all users (only for admin users)"""
    users_dict = dict()
    if user.is_superuser and user.is_authenticated:
        users = User.objects.all().order_by("username").values()
        i = 0
        for user in users:
            users_dict[i] = {"username" : user['username'], "lastLogin" : parse_date(str(user['last_login'])), "joinedDate" : parse_date(str(user['date_joined'])), "isSuperuser" : user['is_superuser']}
            i = i + 1
    return users_dict

def parse_date(date):
    """parse date to another format"""
    if date == 'None':
        return ''
    else:
        return date.split(' ')[0] + 'T' + date.split(' ')[1].split('.')[0] + 'Z'

def get_user_id(username):
    """get user id"""
    user = User.objects.filter(username=username).values()
    if len(user) != 1:
        return -1
    return user[0]['id']

def get_username(user_id):
    """get username"""
    user = User.objects.filter(id=user_id).values()
    if len(user) != 1:
        return ''
    return user[0]['username']

def get_user_mail(user_id, user=None):
    """get user mail"""
    if user is not None:
        from user.views import get_user_id
        if not user.is_authenticated:
            return ''
        user_id = get_user_id(user)
    user = User.objects.filter(id=user_id).values()
    if len(user) != 1:
        return ''
    return user[0]['email']

def set_user_mail(params, user):
    """set user mail"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return {'status' : 'error', 'msg' : 'User not logged in.'}
    new_mail = str(params['new_mail'])
    user_id = get_user_id(user)
    user = User.objects.filter(id=user_id).values()
    if len(user) != 1:
        return {'status' : 'error', 'msg' : 'Internal error.'}
    user.update(email=new_mail)
    return {'status' : 'success', 'msg' : 'Email changed.'}

def set_user_password(params, user):
    """set user password"""
    from user.views import get_user_id
    if not user.is_authenticated:
        return {'status' : 'error', 'msg' : 'User not logged in.'}
    new_password = str(params['new_password'])
    user_id = get_user_id(user)
    user = User.objects.get(id__exact=user_id)
    if user is None:
        return {'status' : 'error', 'msg' : 'Internal error.'}
    user.set_password(new_password)
    user.save()
    return {'status' : 'success', 'msg' : 'Password changed.'}

