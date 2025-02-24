#!/usr/bin/python2

import os
import sys
import argparse
import gzip
import re
import time
import splinter
from splinter import Browser

def embossFile(contigsFile):
    """Emboss file with contigs"""
    inFile = open(contigsFile, 'rb')
    browser.visit(needle_www_addr)
    browser.find_by_id('asequence').fill(inFile.read())
    inFile.close()
    browser.find_by_id('bsequence').fill(genomeReference)
    time.sleep(2)
    browser.find_by_value('Submit').click()
    time.sleep(2)
    wait()
    result = browser.find_by_id('alignmentContent').text
    time.sleep(5)
    outFile = open(outputFilesPath + '/' + os.path.basename(contigsFile) + '-emboss_needle', 'wb')
    outFile.write( result )
    outFile.close()

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
        '--input_files_path', default='../../../mitochondria/output',
        help='path to directory with input files (default: %(default)s)')
    parser.add_argument(
        '--output_files_path', default='../../../mitochondria/output/needle',
        help='path to directory with output files (default: %(default)s)')
    parser.add_argument(
        '--genome_reference_path', default='../../../mitochondria/rCRS',
        help='path to file with genome reference (default: %(default)s)')
    args = parser.parse_args()

    # set input directory
    inputDir = args.input_files_path
    inputDir = os.path.abspath(inputDir)
    numOfFiles = len(listdir_fullpath(inputDir, '.fastq-out'))
    count = 1.0

    # create output directory
    if not os.path.exists(args.output_files_path):
        os.makedirs(args.output_files_path)
    outputFilesPath = args.output_files_path

    # emboss needle
    www_browser = 'chrome'
    needle_www_addr = 'http://www.ebi.ac.uk/Tools/psa/emboss_needle/nucleotide.html'

    browser = Browser(www_browser)
    browser.driver.maximize_window()

    # genome reference
    genomeFile = open(args.genome_reference_path, 'rb')
    genomeReference = genomeFile.read()
    genomeFile.close()

    #i = 0
    for contigsFile in listdir_fullpath(inputDir, '.fastq-out'):
        update_progress(count / numOfFiles, contigsFile)
        count += 1.0
        #i = i + 1
        #if i < 109:
        #    continue
        embossFile(contigsFile)

    browser.quit()
