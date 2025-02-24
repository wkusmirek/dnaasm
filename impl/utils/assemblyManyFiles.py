#!/usr/bin/python2

import os
import sys
import argparse
import gzip
import re

def assemblyGz(compressedFileNameR1):
    """Find proper _R2.fastq.gz file in the folder and assembly them( two files - _R1.fastq.gz and _R2.fastq.gz)."""
    compressedFileNameR2 = compressedFileNameR1.replace('_R1', '_R2')
    uncompressedFileNameR1 = outputFilesPath + '/' + os.path.basename(compressedFileNameR1[:-3])
    uncompressedFileNameR2 = outputFilesPath + '/' + os.path.basename(compressedFileNameR2[:-3])
    uncompressFile(compressedFileNameR1, uncompressedFileNameR1)
    uncompressFile(compressedFileNameR2, uncompressedFileNameR2)

    assemblyCommand = dnaasmPath + ' -a -k ' + str(k) + ' -GS ' + str(GS) + ' -correct ' + correct + ' -complSeq ' + complSeq + ' -paired ' + paired + ' -delta ' + str(delta) + ' -qualFile ' + str(qualFile) + ' -qualSingleEdge ' + str(qualSingleEdge) + ' -qualPairedEdge ' + str(qualPairedEdge) + ' -i1 ' + uncompressedFileNameR1 + ' -i2 ' + uncompressedFileNameR2 + ' -out ' + outputFilesPath + '/' + os.path.basename(compressedFileNameR1[:-3]) + '-out'
    logFile.write(assemblyCommand + '\n')
    os.system(assemblyCommand)
    os.remove(uncompressedFileNameR1)
    os.remove(uncompressedFileNameR2)

def uncompressFile(compressedFileName, uncompressedFileName):
    inF = gzip.open(compressedFileName, 'rb')
    outF = open(uncompressedFileName, 'wb')
    outF.write( inF.read() )
    inF.close()
    outF.close()

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
    match = re.search("^\d+$", val)
    try: val = match.group(0)
    except AttributeError:
        raise argparse.ArgumentTypeError(
            "%s is not an integer value" % val)
    return val

def check_01_argument(val):
    """Check 0/1 argument."""
    value = int(val)
    if value not in [0, 1]:
        raise argparse.ArgumentTypeError(
            "%s is an invalid value" % value)
    return str(value)

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
        '--input_files_path', default='../../../mitochondria',
        help='path to directory with input files (default: %(default)s)')
    parser.add_argument(
        '--output_files_path', default='../../../mitochondria/output',
        help='path to directory with output files (default: %(default)s)')
    parser.add_argument(
        '--correct', default='1', type=check_01_argument,
        help='correcting errors, allowed values: '
             '0 - not correcting errors, '
             '1 - correcting errors (default: %(default)s)')
    parser.add_argument(
        '--complSeq', default='1', type=check_01_argument,
        help='adding complementary sequences, allowed values: '
             '0 - not adding, '
             '1 - adding (default: %(default)s)')
    parser.add_argument(
        '--paired', default='0', type=check_01_argument,
        help='type of reads, allowed values: '
             '0 - single reads, '
             '1 - paired reads (default: %(default)s)')
    parser.add_argument(
        '--GS', default=16565, type=check_integer_argument,
        help='genome size, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--k', default=55, type=check_integer_argument,
        help='graph dimension, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--delta', default=0, type=check_integer_argument,
        help='delta value, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--qualFile', default=10, type=check_integer_argument,
        help='file quality value, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--qualSingleEdge', default=30, type=check_integer_argument,
        help='single edge counter threshold value, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--qualPairedEdge', default=0, type=check_integer_argument,
        help='paired edge counter threshold value, allowed values: '
             'integer values (default: %(default)s)')
    args = parser.parse_args()

    # set input directory
    inputDir = args.input_files_path
    inputDir = os.path.abspath(inputDir)
    numOfFiles = len([file for file in os.listdir(inputDir)]) / 2
    count = 1.0

    complSeq = args.complSeq
    correct = args.correct
    paired = args.paired
    delta = args.delta
    k = args.k
    GS = args.GS
    qualFile = args.qualFile
    qualSingleEdge = args.qualSingleEdge
    qualPairedEdge = args.qualPairedEdge
    dnaasmPath = args.dnaasm_path
    outputFilesPath = args.output_files_path
    logFile = open('log', 'wb')

    # create output directory
    if not os.path.exists(args.output_files_path):
        os.makedirs(args.output_files_path)

    # add libcalc.so to LD
    addToLD(args.libcalc_path)

    for fileR1 in listdir_fullpath(inputDir, '_R1.fastq.gz'):
        update_progress(count / numOfFiles, fileR1)
        count += 1.0
        assemblyGz(fileR1)
