#!/usr/bin/python3

import os
import sys
import argparse
import re

def mergeSequences(sequenceFile, referenceFile):
    """Merge sequences"""
    outFileName = outputFilesPath + '/' + os.path.basename(referenceFile) + '-' + os.path.basename(sequenceFile) + '-emboss_merger_outFile'
    outSeqName = outputFilesPath + '/' + os.path.basename(referenceFile) + '-' + os.path.basename(sequenceFile) + '-emboss_merger_outSeq'
    mergerCommand = 'merger -asequence ' + sequenceFile + ' -bsequence ' + referenceFile + ' -outFile ' + outFileName + ' -outSeq ' + outSeqName
    os.system(mergerCommand)
    if not checkOutFile(outFileName):
        os.remove(outFileName)
        os.remove(outSeqName)
        return False
    else:
        return True

def checkOutFile(outFileName):
    """Checks if result file is useful"""
    resultFile = open(outFileName, 'rb')
    result = resultFile.read()
    resultFile.close()
    # below lines should be changed for another files (id of sequence in FASTA format)
    if "out_tasiemiec      1 --------------------------------------------------      0" in result:  # scaffold is earlier than out_tasiemiec in genome
        return False
    alignIndex = result.find("||||||||||||||||||||||||||||||||||||||||||||||||||")
    misAlignIndex = result.find("--------------------------------------------------")
    if alignIndex != -1 and misAlignIndex != -1 and result.find('|') > minOverlap and result.find("--------------------------------------------------", misAlignIndex+1, alignIndex) != -1:
        return True
    else:
        return False

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

def check_integer_argument(val):
    """Check rotation argument."""
    match = re.search("^\d+$", val)
    try: val = match.group(0)
    except AttributeError:
        raise argparse.ArgumentTypeError(
            "%s is not an integer value" % val)
    return val

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
    parser.add_argument(
        '--min_overlap', default=300, type=check_integer_argument,
        help='path to directory with output files (default: %(default)s)')
    args = parser.parse_args()

    # set input directories
    seqDir = args.sequence_files_path
    seqDir = os.path.abspath(seqDir)
    refDir = args.reference_files_path
    refDir = os.path.abspath(refDir)

    count = 1.0
    numOfFiles = len(listdir_fullpath(refDir, '.fa', 'scaffold'))
    minOverlap = args.min_overlap

    # create output directory
    if not os.path.exists(args.output_files_path):
        os.makedirs(args.output_files_path)
    outputFilesPath = args.output_files_path

    for referenceFile in listdir_fullpath(refDir, '.fa', 'scaffold'):
        update_progress(count / numOfFiles, referenceFile)
        count += 1.0
        lineIndex = 1.0
        for line in open(referenceFile):
            if lineIndex > 5.0:
                break
            lineIndex += 1.0

            for sequenceFile in listdir_fullpath(seqDir, '.fa'):
                file = open(sequenceFile, 'r')
                sequence = file.read()
                sequence = sequence.replace('\n', '')
                file.close()
                
                if line[:len(line)-1] in sequence and mergeSequences(sequenceFile, referenceFile):
                    lineIndex = 100.0
                    break



