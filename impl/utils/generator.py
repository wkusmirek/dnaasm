#! /usr/bin/python

import sys, getopt, random
file = open('seq', 'w')

def print_usage(argv):
    """print user help in script mode"""
    print 'generate sequence (random or repetitive)'
    print "  -l, --length\tlength of output sequence"
    print "  -m, --motif\t\trepetitive motif, if not set the random sequence is generated"

    print 'use: python ' + argv[0] + ' -l 50'
    print 'e.g. python ' + argv[0] + ' -l 50 -mAC'

def generate(length, motif):
    """generate motif or random string"""
    if len(motif) > 0:
        motif_len = len(motif)
        for i in range(length):
            sys.stdout.write(motif[ i % motif_len])
    else:
        for i in range(length):
            sys.stdout.write(random.choice('ACGT'))
            file.write(random.choice('ACGT'))
    sys.stdout.write('\n')
    sys.stdout.flush()

if __name__ == "__main__":

    if len(sys.argv) not in [2, 3]:
        print_usage(sys.argv)
        sys.exit(2)

    try:
        opts, args = getopt.getopt(sys.argv[1:], "l:m:", ["length=", "motif="])
    except getopt.GetoptError:
        print_usage(sys.argv)
        sys.exit(2)

    length = 40
    motif = ""

    for opt, arg in opts:
        if opt in ("-l", "--length"):
            length = int(arg)
        elif opt in ("-m", "--motif"):
            motif = arg

    generate(length, motif)

