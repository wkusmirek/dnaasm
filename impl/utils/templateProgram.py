#!/usr/bin/python3

"""

Exampe use:

python templateProgram.py align --align_algorithm needleman_wunsch --circular false --gap_penalty -1 ../web/example_files/seq.fa ../web/example_files/ref.fa result_file_name

python templateProgram.py assembly --k 55 --genome_length 4000000 --correct false --complementary_seq_add true --paired_reads_algorithm velvet --insert_size_mean 400.0 --insert_size_std_dev 20.0 --paired_reads_threshold 5 --quality_threshold 0 --single_edge_counter_threshold 0 --i1 ../cpp/coli1.fq --i2 ../cpp/coli2.fq result_file_name

"""

import os
import re
import sys
import argparse
import requests
import json
import shutil
import time
import ntpath

def log_in(session, new_mail):
    """log in"""
    add_and_login_guest_user_url = client_server_prefix + '/ajax/user/add_and_login_guest_user/'    
    add_and_login_guest_user_response = session.post(add_and_login_guest_user_url)
    if add_and_login_guest_user_response.status_code != 200:
        print("Failed to log in as a guest user.")
        sys.exit(-1)
    set_user_mail_url = client_server_prefix + '/ajax/user/set_user_mail/'
    set_user_mail_data = {
        'new_mail': new_mail
    }    
    set_user_mail_response = session.post(set_user_mail_url, data=set_user_mail_data)
    if set_user_mail_response.status_code != 200:
        print("Failed to set email for guest user.")
        sys.exit(-1)
    return add_and_login_guest_user_response.json()['username']

def log_out(session, guest_username):
    """log out"""
    logout_user_url = client_server_prefix + '/ajax/user/logout_user/'
    logout_user_data = {
        'username': guest_username
    }
    logout_user_response = session.post(logout_user_url, data=logout_user_data)
    if logout_user_response.status_code != 200:
        print("Failed to logout guest user.")
        sys.exit(-1)

def upload_file(session, guest_username, input_file):
    """upload input file"""
    if input_file == '':
        return
    upload_file_url = client_server_prefix + '/ajax/file/upload_file/'
    upload_file_data = {
        'username': guest_username,
    }
    upload_file_files = {'file':open(input_file, 'rb')}
    upload_file_response = session.post(upload_file_url, data=upload_file_data, files=upload_file_files)
    if upload_file_response.status_code != 200:
        print("Failed to upload %s file." % input_file)
        sys.exit(-1)

def download_file(session, guest_username, outputDir, result_file_name):
    """download output file"""
    download_file_url = client_server_prefix + '/ajax/file/download_file/'
    download_file_data = {
        'username': guest_username,
        'docfile': 'public/users/%s/%s' % (guest_username, result_file_name),
    }
    download_file_response = session.post(download_file_url, data=download_file_data, stream=True)
    if download_file_response.status_code != 200:
        print("Failed to download result.")
        sys.exit(-1)
    if not os.path.exists(outputDir):
        os.makedirs(outputDir)
    with open(outputDir + '/' + result_file_name, 'wb') as f:
        shutil.copyfileobj(download_file_response.raw, f)

def wait_for_assembly_task(session, guest_username, task_name):
    """wait until assembly task has been finished"""
    get_user_assembly_tasks_url = client_server_prefix + '/ajax/assembly/get_user_assembly_tasks/'
    while True:
        time.sleep(0.1)
        get_user_assembly_tasks_response = session.get(get_user_assembly_tasks_url)
        progress = get_user_assembly_tasks_response.json()['0']['progress']    # for another user than guest user it has to be changed, fot guest user it is ok
        update_progress(progress, task_name)
        if progress == 1:
            print('')
            time.sleep(3.0)    # wait until dnaasm save result to file, for large genomes it should be larger value
            get_user_assembly_tasks_response = session.get(get_user_assembly_tasks_url)
            break

def wait_for_align_task(session, guest_username, task_name):
    """wait until align task has been finished"""
    get_user_align_tasks_url = client_server_prefix + '/ajax/align/get_user_align_tasks/'
    while True:
        time.sleep(0.1)
        get_user_align_tasks_response = session.get(get_user_align_tasks_url)
        progress = get_user_align_tasks_response.json()['0']['progress']    # for another user than guest user it has to be changed, fot guest user it is ok
        update_progress(progress, task_name)
        if progress == 1:
            print('')
            time.sleep(3.0)    # wait until dnaasm save result to file, for large genomes it should be larger value
            get_user_align_tasks_response = session.get(get_user_align_tasks_url)
            break

def assembly(session, guest_username, input_file_1, input_file_2, k, genome_length, correct, complementary_seq_add, paired_reads_algorithm, insert_size_mean, insert_size_std_dev, paired_reads_threshold, quality_threshold, single_edge_counter_threshold, result_file_name, result_notification):
    """assembly task"""
    insert_url = client_server_prefix + '/ajax/assembly/insert/'
    insert_data = {
        'username': guest_username,
        'name': result_file_name,
        'file_name1': ntpath.basename(input_file_1),
        'file_name2': ntpath.basename(input_file_2),
        'k': k,
        'genome_length': genome_length,
        'insert_size_mean': insert_size_mean,
        'insert_size_std_dev': insert_size_std_dev,
        'paired_reads_threshold': paired_reads_threshold,
        'paired_reads_algorithm': paired_reads_algorithm,
        'quality_threshold': quality_threshold,
        'single_edge_counter_threshold': single_edge_counter_threshold,
        'complementary_seq_add': complementary_seq_add,
        'correct': correct,
        'result_notification': result_notification,
    }
    insert_response = session.post(insert_url, data=insert_data)
    if insert_response.status_code != 200:
        print("Failed to start new assembly task.")
        sys.exit(-1)

def align(session, guest_username, seq, ref, gap_penalty, AA, AC, AG, AT, CA, CC, CG, CT, GA, GC, GG, GT, TA, TC, TG, TT, result_file_name, circular, align_algorithm, result_notification):
    """align task"""
    insert_url = client_server_prefix + '/ajax/align/insert/'
    insert_data = {
        'username': guest_username,
        'name': result_file_name,
        'circular': circular,
        'align_algorithm': align_algorithm,
        'seq_file_name': ntpath.basename(seq),
        'ref_file_name': ntpath.basename(ref),
        'gap_penalty': gap_penalty,
        'AA': AA,
        'AC': AC,
        'AG': AG,
        'AT': AT,
        'CA': CA,
        'CC': CC,
        'CG': CG,
        'CT': CT,
        'GA': GA,
        'GC': GC,
        'GG': GG,
        'GT': GT,
        'TA': TA,
        'TC': TC,
        'TG': TG,
        'TT': TT,
        'result_notification': result_notification,
    }
    insert_response = session.post(insert_url, data=insert_data)
    if insert_response.status_code != 200:
        print("Failed to start new align task.")
        sys.exit(-1)

def update_progress(progress, status):
    """Update progressbar."""
    barlength = 30
    status += " "
    if isinstance(progress, int):
        progress = float(progress)
    if not isinstance(progress, float):
        progress = 0
    if progress >= 1:
        progress = 1
    block = int(round(barlength * progress))
    text = "\r[{0}] {1:.2f}% {2}".format(
        "#" * block + "-" * (barlength - block),
        progress * 100, os.path.basename(status))
    sys.stdout.write(text)
    sys.stdout.flush()

def check_file_existence(input_file):
    """Check if input_file exists."""
    if input_file == '':    # second input file for assembly task
        return True
    if not os.path.exists(input_file):
        print('File %s does not exist.' % input_file)
        return False
    return True

def check_align_algorithm_argument(val):
    """Check align algorithm argument."""
    value = str(val)
    if value not in ['needleman_wunsch', 'hirschberg']:
        raise argparse.ArgumentTypeError(
            "%s is an invalid value" % value)
    return str(value)

def check_false_true_argument(val):
    """Check false/true argument."""
    value = str(val).lower()
    if value not in ["true", "false"]:
        raise argparse.ArgumentTypeError(
            "%s is an invalid value" % value)
    return value

def check_paired_reads_algorithm_argument(val):
    """Check paired reads algorithm argument."""
    value = str(val).lower()
    if value not in ["none", "velvet"]:
        raise argparse.ArgumentTypeError(
            "%s is an invalid value" % value)
    return value

def check_integer_argument(val):
    """Check integer argument."""
    match = re.search("^-?\d+$", val)
    try: val = match.group(0)
    except AttributeError:
        raise argparse.ArgumentTypeError(
            "%s is not an integer value" % val)
    return val

def check_float_argument(val):
    """Check float argument."""
    match = re.search("^-?\d+\.\d+$", val)
    try: val = match.group(0)
    except AttributeError:
        raise argparse.ArgumentTypeError(
            "%s is not a float value" % val)
    return val
    
    
if __name__ == "__main__":
    # parse arguments
    main_parser=argparse.ArgumentParser()
    main_parser.add_argument(
        '-u', '--url', default='http://127.0.0.1',
        help='url of the dnaasm service (default: %(default)s)')
    main_parser.add_argument(
        '-p', '--port', default='9000',
        help='port of the dnaasm service (default: %(default)s)')
    main_parser.add_argument(
        '--output_dir', default='output_dir',
        help='path to directory for result files (default: %(default)s)')
    main_parser.add_argument(
        '--result_notif', default='false', type=check_false_true_argument,
        help='result notification, allowed values: '
             'false - not sending e-mail, '
             'true - sending e-mail (default: %(default)s)')
    main_parser.add_argument(
        '--email', default='',
        help='e-mail address')
    subparsers = main_parser.add_subparsers(dest='subparser_name')

    assembly_parser = subparsers.add_parser('assembly', help = "make graph for input file (set of reads) and write contigs to the file")
    assembly_parser.add_argument(
        '--k', default=55, type=check_integer_argument,
        help='do Bruijn graph dimension, allowed values: '
             'integer values (default: %(default)s)')
    assembly_parser.add_argument(
        '--genome_length', default=4000000, type=check_integer_argument,
        help='genome size, allowed values: '
             'integer values (default: %(default)s)')
    assembly_parser.add_argument(
        '--correct', default='false', type=check_false_true_argument,
        help='correcting errors, allowed values: '
             'false - not correcting errors, '
             'true - correcting errors (default: %(default)s)')
    assembly_parser.add_argument(
        '--complementary_seq_add', default='false', type=check_false_true_argument,
        help='adding complementary sequences, allowed values: '
             'false - not adding, '
             'true - adding (default: %(default)s)')
    assembly_parser.add_argument(
        '--paired_reads_algorithm', default='none', type=check_paired_reads_algorithm_argument,
        help='type of paired reads algorithm, allowed values: '
             'none - reads are unpaired, '
             'velvet - for using algorithm from Velvet assembler (--insert_size_mean, --insert_size_std_dev and --paired_reads_threshold arguments required (default: %(default)s)')
    assembly_parser.add_argument(
        '--insert_size_mean', default=400.0, type=check_float_argument,
        help="the value associated with paired read sequencing, required only when '-paired_reads_algorithm' is set to 'velvet', allowed values: "
             'float values (default: %(default)s)')
    assembly_parser.add_argument(
        '--insert_size_std_dev', default=20.0, type=check_float_argument,
        help="the value associated with paired read sequencing, required only when '-paired_reads_algorithm' is set to 'velvet', allowed values: "
             'float values (default: %(default)s)')
    assembly_parser.add_argument(
        '--paired_reads_threshold', default=0, type=check_integer_argument,
        help="the threshold of edge counter (each paired-end tag adds new edge or increment specified counter) for contigs graph, required only when '-paired_reads_algorithm' is set to 'velvet', allowed values: "
             'integer values (default: %(default)s)')            
    assembly_parser.add_argument(
        '--quality_threshold', default=0, type=check_integer_argument,
        help='file quality value, allowed values: '
             'integer values (default: %(default)s)')
    assembly_parser.add_argument(
        '--single_edge_counter_threshold', default=0, type=check_integer_argument,
        help='single edge (edge from de Bruijn graph) counter threshold value, allowed values: '
             'integer values (default: %(default)s)')
    assembly_parser.add_argument(
        '--i1', default='',
        help='file with reads for first end (if reads are paired and each end is stored in separate file) or file with all reads (if reads are not paired or if reads are paired and stored interleaved in one file), allowed values: '
             'string values (default: %(default)s)')
    assembly_parser.add_argument(
        '--i2', default='',
        help='file with reads for second end (if reads are paired and each end is stored in separete file), allowed values: '
             'string values (default: %(default)s)')
    assembly_parser.add_argument(
        'result_file_name',
        help="result file name")


    align_parser = subparsers.add_parser('align', help = "align sequence to reference genome")
    align_parser.add_argument(
        '--circular', default='true', type=check_false_true_argument,
        help='circular or linear genome, allowed values: '
             'false - genome is linear, '
             'true - genome is circular (default: %(default)s)')
    align_parser.add_argument(
        '--align_algorithm', default='needleman_wunsch', type=check_align_algorithm_argument,
        help='align algorithm, allowed values: '
             'needleman_wunsch - for Needleman-Wunsch algorithm, '
             "hirschberg - for Hirschberg's algorithm, "
             '(default: %(default)s)')
    align_parser.add_argument(
        '--gap_penalty', default='-1', type=check_integer_argument,
        help='gap penalty, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--AA', default='1', type=check_integer_argument,
        help='cell AA in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--AC', default='-1', type=check_integer_argument,
        help='cell AC in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--AG', default='-1', type=check_integer_argument,
        help='cell AG in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--AT', default='-1', type=check_integer_argument,
        help='cell AT in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--CA', default='-1', type=check_integer_argument,
        help='cell CA in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--CC', default='1', type=check_integer_argument,
        help='cell CC in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--CG', default='-1', type=check_integer_argument,
        help='cell CG in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--CT', default='-1', type=check_integer_argument,
        help='cell CT in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--GA', default='-1', type=check_integer_argument,
        help='cell GA in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--GC', default='-1', type=check_integer_argument,
        help='cell GC in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--GG', default='1', type=check_integer_argument,
        help='cell GG in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--GT', default='-1', type=check_integer_argument,
        help='cell GT in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--TA', default='-1', type=check_integer_argument,
        help='cell TA in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--TC', default='-1', type=check_integer_argument,
        help='cell TC in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--TG', default='-1', type=check_integer_argument,
        help='cell TG in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        '--TT', default='1', type=check_integer_argument,
        help='cell TT in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    align_parser.add_argument(
        'seq',
        help='path to file with sequence')
    align_parser.add_argument(
        'ref',
        help='path to file with reference genome')
    align_parser.add_argument(
        'result_file_name',
        help="result file name")



    args = main_parser.parse_args()
    address = "%s:%s/" % (args.url, args.port)
    client_server_prefix = address + 'srvmyapp'
    if args.subparser_name == 'align':
        if check_file_existence(args.seq) and check_file_existence(args.ref):
            with requests.Session() as session:
                guest_username = log_in(session, args.email)
                upload_file(session, guest_username, args.seq)
                upload_file(session, guest_username, args.ref)
                align(session, guest_username, args.seq, args.ref, args.gap_penalty, args.AA, args.AC, args.AG, args.AT, args.CA, args.CC, args.CG, args.CT, args.GA, args.GC, args.GG, args.GT, args.TA, args.TC, args.TG, args.TT, args.result_file_name, args.circular, args.align_algorithm, args.result_notif)
                wait_for_align_task(session, guest_username, args.result_file_name)
                download_file(session, guest_username, args.output_dir, args.result_file_name)
                log_out(session, guest_username)
    elif args.subparser_name == 'assembly':
        if check_file_existence(args.i1) and check_file_existence(args.i2):
            with requests.Session() as session:
                guest_username = log_in(session, args.email)
                upload_file(session, guest_username, args.i1)
                upload_file(session, guest_username, args.i2)
                assembly(session, guest_username, args.i1, args.i2, args.k, args.genome_length, args.correct, args.complementary_seq_add, args.paired_reads_algorithm, args.insert_size_mean, args.insert_size_std_dev, args.paired_reads_threshold, args.quality_threshold, args.single_edge_counter_threshold, args.result_file_name, args.result_notif)
                wait_for_assembly_task(session, guest_username, args.result_file_name)
                download_file(session, guest_username, args.output_dir, args.result_file_name)
                log_out(session, guest_username)
