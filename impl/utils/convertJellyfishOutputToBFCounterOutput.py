#!/usr/bin/python2

import os
import argparse

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--jellyfish_file_path', default='outJellyfish',
        help='path to output file from Jellyfish application (default: %(default)s)')
    parser.add_argument(
        '--bfcounter_file_path', default='outBFCounter',
        help='path to output file from BFCounter application (default: %(default)s)')
    args = parser.parse_args()

    # set paths to files
    jellyfishFile = args.jellyfish_file_path
    jellyfishFile = os.path.abspath(jellyfishFile)
    bfcounterFile = args.bfcounter_file_path
    bfcounterFile = os.path.abspath(bfcounterFile)

    # convert file
    bfcounterFile = open(bfcounterFile, 'w')
    previousLine = ''
    for line in open(jellyfishFile):
        if line[0] != '>':
            bfcounterFile.write(''.join(line.split('\n', 1)) + '\t' + previousLine[1:])
        previousLine = line

