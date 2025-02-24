#!/usr/bin/python2

import os, re, sys
import argparse
from Bio import SeqIO

def makeRevCompl(sequence, outputFile):
    """Generates and saves reverse complement sequence for input sequence."""
    outputFile.write( '>' + sequence.id + '_rev_compl\n' + str(sequence.reverse_complement().seq) + '\n')

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
        '--input_file_path', default='seq.fa',
        help='path to input file in FASTA or FASTQ format (default: %(default)s)')
    parser.add_argument(
        '--output_file_path', default='rev_compl_seq.fa',
        help='path to output file in FASTA format with reads (default: %(default)s)')
    args = parser.parse_args()

    # set paths to files
    inputFile = args.input_file_path
    inputFile = os.path.abspath(inputFile)
    outputFile = args.output_file_path
    outputFile = os.path.abspath(outputFile)

    # create output file
    outputFile = open(outputFile, 'w')

    numOfSequences = len(list(SeqIO.parse(open(inputFile),'fasta')))
    sequences = SeqIO.parse(open(inputFile),'fasta')

    count = 1.0
    for sequence in sequences:
        update_progress(count / numOfSequences, sequence.id)
        count += 1.0
        makeRevCompl(sequence, outputFile)
    outputFile.close()
