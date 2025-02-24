#!/usr/bin/python2

import os, re, sys
import argparse
from Bio import SeqIO

def generateReads(sequence, k, readLength, outputFile):
    """Generates and saves reads from input sequence."""
    n = len(sequence)
    i = 0
    for i in range(0, ((n-readLength)/(readLength-k+1)+1)):
        outputFile.write('>test\n' + sequence[i*(readLength-k+1):(i+1)*(readLength-k+1)+k-1] + '\n')
    if (i+1)*(readLength-k+1)+k-1 < n:
        i += 1
        outputFile.write('>test\n' + sequence[i*(readLength-k+1):n] + '\n')

def check_integer_argument(val):
    """Check integer argument."""
    match = re.search("^-?\d+$", val)
    try: val = match.group(0)
    except AttributeError:
        raise argparse.ArgumentTypeError(
            "%s is not an integer value" % val)
    return val

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
        '--k', default=55, type=check_integer_argument,
        help='do Bruijn graph dimension, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--n', default=100, type=check_integer_argument,
        help='reads length, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--input_file_path', default='ref.fa',
        help='path to input file in FASTA or FASTQ format (default: %(default)s)')
    parser.add_argument(
        '--output_file_path', default='reads.fa',
        help='path to output file in FASTA format with reads (default: %(default)s)')
    args = parser.parse_args()

    # set paths to files
    inputFile = args.input_file_path
    inputFile = os.path.abspath(inputFile)
    outputFile = args.output_file_path
    outputFile = os.path.abspath(outputFile)

    # k and n values
    k = int(args.k)
    n = int(args.n)

    # create output file
    outputFile = open(outputFile, 'w')

    input = open(inputFile)
    firstSign = input.read(1)
    input.close()

    if firstSign == '@':
        numOfSequences = len(list(SeqIO.parse(open(inputFile),'fastq')))
        sequences = SeqIO.parse(open(inputFile),'fastq')
    elif firstSign == '>':
        numOfSequences = len(list(SeqIO.parse(open(inputFile),'fasta')))
        sequences = SeqIO.parse(open(inputFile),'fasta')
    else:
        print 'This file format is not supported.'

    count = 1.0
    for sequence in sequences:
        update_progress(count / numOfSequences, sequence.id)
        count += 1.0
        generateReads(str(sequence.seq), k, n, outputFile)
    outputFile.close()
