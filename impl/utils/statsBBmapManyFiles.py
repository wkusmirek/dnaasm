#!/usr/bin/python2

import os
import sys
import argparse

def generateStats(contigFile):
    """Makes stats for file with contigs in FASTA format."""
    os.system('echo ' + os.path.basename(contigFile) + ' >> ' + outFile.name)
    statCommand = statsPath + ' ' + contigFile + ' gcformat=0 format=7 >> ' + outFile.name
    os.system(statCommand)
    os.system('echo "**************************************************************\n\n" >> ' + outFile.name)
    logFile.write(statCommand + '\n')

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

def addToLD(path):
    if "LD_LIBRARY_PATH" in os.environ:
        os.environ["LD_LIBRARY_PATH"]= os.environ["LD_LIBRARY_PATH"] + ':' + os.path.abspath(path)
    else:
        os.environ["LD_LIBRARY_PATH"]= os.path.abspath(path)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--stats_sh_path', default='../../../assemblers/bbmap/stats.sh',
        help='path to stats.sh from bbmap (default: %(default)s)')
    parser.add_argument(
        '--input_files_path', default='../../../mitochondria/wyniki',
        help='path to directory with input files (default: %(default)s)')
    parser.add_argument(
        '--output_file_path', default='../../../mitochondria/stat',
        help='path to output file (default: %(default)s)')
    args = parser.parse_args()

    # set input directory
    inputDir = args.input_files_path
    inputDir = os.path.abspath(inputDir)
    numOfFiles = len([file for file in os.listdir(inputDir)])
    count = 1.0

    statsPath = args.stats_sh_path
    logFile = open('log', 'wb')
    outFile = open(args.output_file_path, 'wb')

    for contigFile in listdir_fullpath(inputDir, '-out'):
        update_progress(count / numOfFiles, contigFile)
        count += 1.0
        generateStats(contigFile)

    outFile.close()
    result = open(args.output_file_path, 'r').read()
    outFile.close()
    nomOfSamples = result.count('**************************************************************')
    numOfProperSamples = result.count('Main genome contig total:           	2\n')
    result = 'Files with two contigs: ' + str(numOfProperSamples) + '\n' + 'All files: ' + str(nomOfSamples) + '\n\n\n\n' + result
    outFile = open(args.output_file_path, 'wb')
    outFile.write(result)
    outFile.close()
