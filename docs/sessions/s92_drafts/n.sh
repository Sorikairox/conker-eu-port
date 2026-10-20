#!/bin/sh
# print the instructions of an asm function (no address columns)
f=$(grep -rl "glabel $1\$" ~/conker/conker/asm/nonmatchings | head -1)
perl -ne 'print "$1\n" if /^\s*\/\*\s*[0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*\/\s*(.*)$/ ' "$f" | sed 's/  */ /g'
