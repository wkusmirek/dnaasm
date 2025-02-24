#!/usr/bin/python3

import os
import sys
import argparse

def collectStatsFromStretcherFile(inputFilePath, statsFile, count):
    """Collect stats from stretcher output file"""
    inputFile = open(inputFilePath, 'r')
    stretcherFileLines = inputFile.readlines()
    statsFile.write(str(count) + ':\r\n')
    statsFile.write('      ' + stretcherFileLines[14][5:])
    statsFile.write('      ' + stretcherFileLines[15][5:] + '\r\n')
    inputFile.close()

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

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--stretcher_files_path', default='out_stretcher',
        help='path to directory with input files (default: %(default)s)')
    parser.add_argument(
        '--output_file_name', default='stretcher_stats.txt',
        help='output file name (default: %(default)s)')
    args = parser.parse_args()

    # set input directory
    inputDir = args.stretcher_files_path
    inputDir = os.path.abspath(inputDir)
    count = 1
    numOfFiles = 1

    print 'Counting number of files to estimate progress...'
    for inputFile in inputDir:
        numOfFiles += 1

    # create output file
    statsFile = open(args.output_file_name, 'w+')
    statsFile.write('Aligning these pairs of sequences could be useful:\r\n\r\n')
    
    for inputFile in os.listdir(inputDir):
        if 'stretcher' in inputFile:
            update_progress(count / numOfFiles, '')
            collectStatsFromStretcherFile(os.path.abspath(os.path.join(inputDir, inputFile)), statsFile, count)
            count += 1

    # close output file
    statsFile.close()



