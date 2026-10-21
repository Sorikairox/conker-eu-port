#!/bin/bash
f=$1; s=$(ls /Users/sorikairo/conker-wt/a/conker/asm/nonmatchings/*/$f.s | head -1)
perl -ne 's{^\s*/\* [0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*/\s*}{}; s/\s+/ /g; next if /^\s*$|^glabel|^\.size|endlabel|rodata_inject|^\.(section|text|word)/; print "$_;"' $s; echo
