#
#  FASTA formatter  -  a script for re-formatting a FASTA file
#
#  Version 0.1.2 (July 31, 2012)
#
#  Copyright (c) 2012 Kirill Kryukov
#
#  This software is provided 'as-is', without any express or implied
#  warranty. In no event will the authors be held liable for any damages
#  arising from the use of this software.
#
#  Permission is granted to anyone to use this software for any purpose,
#  including commercial applications, and to alter it and redistribute it
#  freely, subject to the following restrictions:
#
#  1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#  2. Altered source versions must be plainly marked as such, and must not be
#     misrepresented as being the original software.
#  3. This notice may not be removed or altered from any source distribution.
#

# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#perl fastaFormatter.pl -line-length 100 -in <seq.fa >seq100.fa
# !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

use strict;

my $eol = "\x0A";
my $line_length = 60;

my $argc = scalar(@ARGV);
for (my $i=0; $i<$argc; $i++)
{
    if ($i < $argc-1)
    {
        if ($ARGV[$i] eq '-line-length')
        {
            $i++;
            $line_length = int($ARGV[$i]);
            if ($line_length < 0) { die; }
            next;
        }
        if ($ARGV[$i] eq '-eol')
        {
            $i++;
            if (lc($ARGV[$i]) eq 'dos') { $eol = "\x0D\x0A"; }
            elsif (lc($ARGV[$i]) eq 'mac') { $eol = "\x0D"; }
            elsif (lc($ARGV[$i]) eq 'unix') { $eol = "\x0A"; }
            else { die "Error: Unknown -eol parameter\n"; }
            next;
        }
    }
}

my $n_seq = 0;
my $total_length = 0;
my $seq = '';

binmode STDOUT;

while (<STDIN>)
{
    #chomp;
    s/[\x13\x10\s]+$//;
    if (/^>.*$/)
    {
        if ($seq ne '') { print $seq, $eol; }
        $seq = '';
        print $_, $eol;
        $n_seq++;
        next;
    }

    $seq .= $_;
    $total_length += length($_);

    if ($line_length > 0)
    {
        while (length($seq) >= $line_length)
        {
            print substr($seq,0,$line_length), $eol;
            $seq = substr($seq,$line_length);
        }
    }
}
if ($seq ne '') { print $seq, $eol; }

print STDERR "Processed $total_length bp in $n_seq sequences\n";
