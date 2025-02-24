#!/usr/bin/python2

import os
import sys
import argparse
import gzip
import re
import time
from multiprocessing import Process

def localEmbossFile(sequenceFile, referenceFile):
    """Emboss files"""
    outFileName = outputFilesPath + '/' + os.path.basename(referenceFile) + '-' + os.path.basename(sequenceFile) + '-emboss_stretcher'
    stretcherCommand = 'stretcher -asequence ' + sequenceFile + ' -bsequence ' + referenceFile + ' -outFile ' + outFileName
    os.system(stretcherCommand)
    if not checkOutFile(outFileName):
        os.remove(outFileName)
        return 0.0
    else:
        return os.path.getsize(sequenceFile) - 100

def checkOutFile(outFileName):
    """Checks if result file is useful"""
    resultFile = open(outFileName, 'rb')
    result = resultFile.read()
    resultFile.close()
    if "::::::::::::::::::::::::::::::::::::::::::::::::::" not in result:
        return False
    indexes = findAll(result, 'NN')
    for index in indexes:
        if result.find("::::::::::::::::::::::::::::::::::::::::::::::::::", index) != -1 and result.find("::::::::::::::::::::::::::::::::::::::::::::::::::", 0, index) != -1:
            return True
    return False

def findAll(a_str, sub):
    """Finds all occurences of sub in a_str"""
    start = 0
    while True:
        start = a_str.find(sub, start)
        if start == -1: return
        yield start
        start += 1

def findPreviousFullLine(filename, actualLine):
    """Finds previous line without any 'N' sign."""
    previousLine = ''
    for line in open(filename):
        if line == actualLine:
            if not 'N' in previousLine:
                return previousLine
            else:
                return findPreviousFullLine(filename, previousLine)
        previousLine = line
    return previousLine

def findNextFullLine(filename, actualLine):
    """Finds next line without any 'N' sign."""
    previousLine = ''
    for line in open(filename):
        if previousLine == actualLine:
            if not 'N' in line:
                return line
            else:
                return findNextFullLine(filename, line)
        previousLine = line
    return line

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


def listdir_fullpath(d, suffix, substring=None):
    """Return list of files with sequences with full path appended."""
    old_path = os.getcwd()
    os.chdir(d)
    if substring is None:
        listdir = [os.path.join(d, f) for f in os.listdir(d)
                   if os.path.isfile(f) and f.endswith(suffix)]
    else:
        listdir = [os.path.join(d, f) for f in os.listdir(d)
               if os.path.isfile(f) and f.endswith(suffix) and f.find(substring) != -1]
    os.chdir(old_path)
    return listdir

def wait():
    while True:
        time.sleep(20)
        if len(browser.find_by_id('alnFile')) > 0:
            return

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--sequence_files_path', default='seq',
        help='path to directory with input files (default: %(default)s)')
    parser.add_argument(
        '--reference_files_path', default='ref',
        help='path to directory with input files (default: %(default)s)')
    parser.add_argument(
        '--output_files_path', default='out',
        help='path to directory with output files (default: %(default)s)')
    args = parser.parse_args()

    # set input directories
    seqDir = args.sequence_files_path
    seqDir = os.path.abspath(seqDir)
    refDir = args.reference_files_path
    refDir = os.path.abspath(refDir)
    count = 1.0
    numOfLines = 1.0

    print 'Counting number of lines to estimate progress...'
    for referenceFile in listdir_fullpath(refDir, '.fa', 'scaffold'):
        numOfLines += sum(1 for line in open(referenceFile))

    # create output directory
    if not os.path.exists(args.output_files_path):
        os.makedirs(args.output_files_path)
    outputFilesPath = args.output_files_path

    for referenceFile in listdir_fullpath(refDir, '.fa', 'scaffold'):
        for line in open(referenceFile):
            update_progress(count / numOfLines, referenceFile)
            count += 1.0

            if not 'N' in line:
                continue
            prevLine = findPreviousFullLine(referenceFile, line)
            #nextLine = findPreviousFullLine(referenceFile, line)

            for sequenceFile in listdir_fullpath(seqDir, '.fa'):
                file = open(sequenceFile, 'r')
                sequence = file.read()
                sequence = sequence.replace('\n', '')
                file.close()
                outFileName = outputFilesPath + '/' + os.path.basename(referenceFile) + '-' + os.path.basename(sequenceFile) + '-emboss_stretcher'
                if len(prevLine) > 10 and not os.path.isfile(os.path.abspath(outFileName)) and prevLine[:len(prevLine)-1] in sequence:
                    localEmbossFile(sequenceFile, referenceFile)
                #if len(nextLine) > 10 and not os.path.isfile(os.path.abspath(outFileName)) and nextLine[:len(nextLine)-1] in sequence:
                #    localEmbossFile(sequenceFile, referenceFile)
