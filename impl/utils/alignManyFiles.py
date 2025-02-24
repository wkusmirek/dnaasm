#!/usr/bin/python2

import os
import sys
import argparse
import gzip
import re

def align(contigFile):
    """Align sequence command."""
#./dnaasm -align -d -1 -AA 1 -AC -1 -AG -1 -AT -1 -CA -1 -CC 1 -CG -1 -CT -1 -GA -1 -GC -1 -GG 1 -GT -1 -TA -1 -TC -1 -TG -1 -TT 1 -seq sequence.fasta -ref reference.fasta
    alignCommand = dnaasmPath + ' -align -d ' + str(d) + ' -AA ' + str(AA) + ' -AC ' + str(AC) + ' -AG ' + str(AG)  + ' -AT ' + str(AT) + ' -CA ' + str(CA) + ' -CC ' + str(CC) + ' -CG ' + str(CG)  + ' -CT ' + str(CT) + ' -GA ' + str(GA) + ' -GC ' + str(GC) + ' -GG ' + str(GG)  + ' -GT ' + str(GT) + ' -TA ' + str(TA) + ' -TC ' + str(TC) + ' -TG ' + str(TG)  + ' -TT ' + str(TT) + ' -seq ' + contigFile + ' -ref ' + referenceFilePath + ' -out ' + contigFile + '-align'
    logFile.write(alignCommand + '\n')
    os.system(alignCommand)

def update_progress(progress, status):
    """Update progressbar."""
    barLength = 30
    status += " "
    if isinstance(progress, int):
        progress = float(progress)
    if not isinstance(progress, float):
        progress = 0
    if progress >= 1:
        progress = 1
    block = int(round(barLength * progress))
    text = "\r[{0}] {1:.2f}% {2}".format(
        "#" * block + "-" * (barLength - block),
        progress * 100, os.path.basename(status))
    sys.stdout.write(text)
    sys.stdout.flush()

def listdir_fullpath(d, suffix):
    """Return list of archives with full path appended."""
    old_path = os.getcwd()
    os.chdir(d)
    listdir = [os.path.join(d, f) for f in os.listdir(d)
               if os.path.isfile(f) and f.endswith(suffix)]
    os.chdir(old_path)
    return listdir

def check_integer_argument(val):
    """Check rotation argument."""
    match = re.search("^-?\d+$", val)
    try: val = match.group(0)
    except AttributeError:
        raise argparse.ArgumentTypeError(
            "%s is not an integer value" % val)
    return val

def addToLD(path):
    if "LD_LIBRARY_PATH" in os.environ:
        os.environ["LD_LIBRARY_PATH"]= os.environ["LD_LIBRARY_PATH"] + ':' + os.path.abspath(path)
    else:
        os.environ["LD_LIBRARY_PATH"]= os.path.abspath(path)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--dnaasm_path', default='../cpp/dnaasm',
        help='path to dnaasm application (default: %(default)s)')
    parser.add_argument(
        '--libcalc_path', default='../cpp',
        help='path to libcalc.so from dnaasm application (default: %(default)s)')
    parser.add_argument(
        '--input_files_path', default='../../../dnaasm-dane/mitochondria/wyniki/wyniki-ass',
        help='path to directory with input files (default: %(default)s)')
    parser.add_argument(
        '--reference_file_path', default='../../../dnaasm-dane/mitochondria/ref.fa',
        help='path to file with reference (default: %(default)s)')
    parser.add_argument(
        '--d', default='-1', type=check_integer_argument,
        help='gap penalty, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--AA', default='1', type=check_integer_argument,
        help='cell AA in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--AC', default='-1', type=check_integer_argument,
        help='cell AC in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--AG', default='-1', type=check_integer_argument,
        help='cell AG in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--AT', default='-1', type=check_integer_argument,
        help='cell AT in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--CA', default='-1', type=check_integer_argument,
        help='cell CA in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--CC', default='1', type=check_integer_argument,
        help='cell CC in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--CG', default='-1', type=check_integer_argument,
        help='cell CG in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--CT', default='-1', type=check_integer_argument,
        help='cell CT in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--GA', default='-1', type=check_integer_argument,
        help='cell GA in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--GC', default='-1', type=check_integer_argument,
        help='cell GC in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--GG', default='1', type=check_integer_argument,
        help='cell GG in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--GT', default='-1', type=check_integer_argument,
        help='cell GT in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--TA', default='-1', type=check_integer_argument,
        help='cell TA in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--TC', default='-1', type=check_integer_argument,
        help='cell TC in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--TG', default='-1', type=check_integer_argument,
        help='cell TG in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--TT', default='1', type=check_integer_argument,
        help='cell TT in similarity matrix, allowed values: '
             'integer values (default: %(default)s)')
    args = parser.parse_args()

    # set input directory
    inputDir = args.input_files_path
    inputDir = os.path.abspath(inputDir)
    referenceFilePath = os.path.abspath(args.reference_file_path)
    numOfFiles = len([file for file in os.listdir(inputDir)])
    count = 1.0

    d = args.d
    AA = args.AA
    AC = args.AC
    AG = args.AG
    AT = args.AT
    CA = args.CA
    CC = args.CC
    CG = args.CG
    CT = args.CT
    GA = args.GA
    GC = args.GC
    GG = args.GG
    GT = args.GT
    TA = args.TA
    TC = args.TC
    TG = args.TG
    TT = args.TT

    dnaasmPath = args.dnaasm_path
    logFile = open('log', 'wb')

    # add libcalc.so to LD
    addToLD(args.libcalc_path)

    for contigFile in listdir_fullpath(inputDir, '.fastq-out'):
        update_progress(count / numOfFiles, contigFile)
        count += 1.0
        align(contigFile)
