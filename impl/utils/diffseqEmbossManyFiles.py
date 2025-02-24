#!/usr/bin/python2

import os
import sys
import argparse
import gzip
import re
import time
import splinter
from splinter import Browser

def diffseqFile(contigsFile):
    """Emboss file with contigs"""
    inFile = open(contigsFile, 'rb')
    browser.visit(diffseq_www_addr)
    browser.find_by_name('asequence.text').fill(inFile.read())
    inFile.close()
    browser.find_by_name('bsequence.text').fill(genomeReference)
    browser.find_by_name('wordsize').fill(wordSize)
    time.sleep(2)
    browser.find_by_name('_run').click()
    time.sleep(2)
    wait()
    result = browser.find_by_css("dd.inline").text
    time.sleep(5)
    outFile = open(outputFilesPath + '/' + os.path.basename(contigsFile) + '-emboss_diffseq', 'wb')
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
        if len(browser.find_by_id('output')) > 0:
            return

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--input_files_path', default='../../../mitochondria/output',
        help='path to directory with input files (default: %(default)s)')
    parser.add_argument(
        '--output_files_path', default='../../../mitochondria/output/diffseq',
        help='path to directory with output files (default: %(default)s)')
    parser.add_argument(
        '--genome_reference_path', default='../../../mitochondria/rCRS',
        help='path to file with genome reference (default: %(default)s)')
    parser.add_argument(
        '--word_size', default=15,
        help='word size (default: %(default)s)')
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
    diffseq_www_addr = 'http://www.bioinformatics.nl/cgi-bin/emboss/diffseq'

    browser = Browser(www_browser)
    browser.driver.maximize_window()

    # genome reference
    genomeFile = open(args.genome_reference_path, 'rb')
    genomeReference = genomeFile.read()
    genomeFile.close()

    wordSize = args.word_size

    #i = 0
    for contigsFile in listdir_fullpath(inputDir, '.fastq-out'):
        update_progress(count / numOfFiles, contigsFile)
        count += 1.0
        #i = i + 1
        #if i < 101:
        #    continue
        diffseqFile(contigsFile)

    browser.quit()
