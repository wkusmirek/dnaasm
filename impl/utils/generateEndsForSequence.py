#!/usr/bin/python2

import os, re, sys
import argparse
from Bio import SeqIO

def generateEndsForSequence(sequenceId, sequence, ends_length, outputFile):
    """Generates and saves ends for sequence."""
    if len(sequence) > 2 * ends_length:
        outputFile.write('>' + sequenceId + '_trimmed\n' + sequence[0:ends_length] + 'NNNNN' + sequence[-ends_length:] + '\n')

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
        '--ends_length', default=1000, type=check_integer_argument,
        help='length of DNA sequence ends, allowed values: '
             'integer values (default: %(default)s)')
    parser.add_argument(
        '--input_file_path', default='seq.fa',
        help='path to input file in FASTA format (default: %(default)s)')
    parser.add_argument(
        '--output_file_path', default='seqEnds.fa',
        help='path to output file in FASTA format with end of each contig (default: %(default)s)')
    args = parser.parse_args()

    # set paths to files
    inputFile = args.input_file_path
    inputFile = os.path.abspath(inputFile)
    outputFile = args.output_file_path
    outputFile = os.path.abspath(outputFile)

    # ends_length value
    ends_length = int(args.ends_length)

    # create output file
    outputFile = open(outputFile, 'w')

    # number of sequences in input file
    numOfSequences = len(list(SeqIO.parse(open(inputFile),'fasta')))

    fastaSequences = SeqIO.parse(open(inputFile),'fasta')
    count = 1.0
    for fasta in fastaSequences:
        name, sequence = fasta.id, str(fasta.seq)
        update_progress(count / numOfSequences, name)
        count += 1.0
        generateEndsForSequence(name, sequence, ends_length, outputFile)
    outputFile.close()
