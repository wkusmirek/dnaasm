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
    outFileName = outputFilesPath + '/' + os.path.basename(sequenceFile) + '-' + os.path.basename(referenceFile) + '-emboss_stretcher'
    stretcherCommand = 'stretcher -asequence ' + sequenceFile + ' -bsequence ' + referenceFile + ' -outFile ' + outFileName
    os.system(stretcherCommand)
    resultFile = open(outFileName, 'rb')
    result = resultFile.read()
    resultFile.close()
    if "::::::::::::::::::::::::::::::::::::::::::::::::::" not in result:
        os.remove(outFileName)
        return 0.0
    else:
        return os.path.getsize(sequenceFile) - 100

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
    """Return list of files with contigs with full path appended."""
    old_path = os.getcwd()
    os.chdir(d)
    listdir = [os.path.join(d, f) for f in os.listdir(d)
               if os.path.isfile(f) and f.endswith(suffix)]
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
    for referenceFile in listdir_fullpath(refDir, '.fa'):
        numOfLines += sum(1 for line in open(referenceFile))

    # create output directory
    if not os.path.exists(args.output_files_path):
        os.makedirs(args.output_files_path)
    outputFilesPath = args.output_files_path

    processes = []
    sequenceSize = 0.0
    for referenceFile in listdir_fullpath(refDir, '.fa'):
        #usedSequenceFile = []
        for line in open(referenceFile):
            update_progress(count / numOfLines, referenceFile)
            count += 1.0
            if sequenceSize > 0.0:
                sequenceSize -= len(line)
                continue
            sequenceSize = 0.0
            for sequenceFile in listdir_fullpath(seqDir, '.fa'):
                #if sequenceFile in usedSequenceFile:
                #    continue
                file = open(sequenceFile, 'r')
                sequence = file.read()
                sequence = sequence.replace('\n', '')
                file.close()
                outFileName = outputFilesPath + '/' + os.path.basename(referenceFile) + '-' + os.path.basename(sequenceFile) + '-emboss_stretcher'
                if len(line) > 10 and not os.path.isfile(outFileName) and line[:len(line)-1] in sequence:
                    sequenceSize = localEmbossFile(sequenceFile, referenceFile)
                    #usedSequenceFile.append(sequenceFile)
#                p = Process(target=localEmbossFile, args=(sequenceFile, referenceFile))
#                p.start()
#                processes.append(p)
#                if len(processes) == 4:
#                    for p in processes:
#                        p.join()
#                    processes = []
        #os.remove(referenceFile)

    for p in processes:
        p.start()
    for p in processes:
        p.join()
