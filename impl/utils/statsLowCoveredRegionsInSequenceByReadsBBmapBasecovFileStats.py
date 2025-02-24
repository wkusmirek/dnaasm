#!/usr/bin/python2

import os
import sys
import argparse

def check_integer_argument(val):
    """Check rotation argument."""
    match = re.search("^-?\d+$", val)
    try: val = match.group(0)
    except AttributeError:
        raise argparse.ArgumentTypeError(
            "%s is not an integer value" % val)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--basecov_file_path', default='basecov_file.txt',
        help='path to basecov file from BBmap (default: %(default)s)')
    parser.add_argument(
        '--output_file_path', default='out',
        help='path to output file (default: %(default)s)')
    args = parser.parse_args()
    parser.add_argument(
        '--coverageThreshold', default='5', type=check_integer_argument,
        help='reference genome coverage thredhold, allowed values: '
             'integer values (default: %(default)s)')

    coverageThreshold = 5

    # set input directories
    basecovFilePath = args.basecov_file_path
    basecovFilePath = os.path.abspath(basecovFilePath)
    basecovFile = open(basecovFilePath, 'r')

    # create filtered basecov file
    filteredBasecovFilePath = args.basecov_file_path + ".tmp"
    filteredBasecovFilePath = os.path.abspath(filteredBasecovFilePath)
    filteredBasecovFile = open(filteredBasecovFilePath, 'w')

    # create output file
    outputFilePath = args.output_file_path
    outputFilePath = os.path.abspath(outputFilePath)
    outputFile = open(outputFilePath, 'w')

    print "Filtering original basecov file..."

    for line in basecovFile:
        if line[0] == "#":
            continue
        words = line.split("\t")
        words[2].replace("\n", "")
        if int(words[2]) > coverageThreshold:
            continue
        else:
            filteredBasecovFile.write(words[0] + "\t" + words[1] + "\t" + words[2])

    basecovFile.close()
    filteredBasecovFile.close()
    filteredBasecovFile = open(filteredBasecovFilePath, 'r')

    print "Filtering original basecov file done"
    print "Merging regions..."

    actualSequenceId = ''
    actualSequenceMin = ''
    actualSequenceMax = ''
    for line in filteredBasecovFile:
        words = line.split("\t")
        if actualSequenceId == '':    # first line
            actualSequenceId = words[0]
            actualSequenceMin = int(words[1])
            actualSequenceMax = int(words[1])
        elif words[0] == actualSequenceId and int(words[1]) == actualSequenceMax+1:
            actualSequenceMax += 1
        elif words[0] == actualSequenceId and int(words[1]) != actualSequenceMax+1:
            outputFile.write(actualSequenceId + "\t" + str(actualSequenceMin) + "\t" + str(actualSequenceMax) + "\n")
            actualSequenceId = words[0]
            actualSequenceMin = int(words[1])
            actualSequenceMax = int(words[1])
        elif words[0] != actualSequenceId:
            outputFile.write(actualSequenceId + "\t" + str(actualSequenceMin) + "\t" + str(actualSequenceMax) + "\n")
            actualSequenceId = words[0]
            actualSequenceMin = int(words[1])
            actualSequenceMax = int(words[1])

    print "Merging regions done"

    filteredBasecovFile.close()
    outputFile.close()
            
