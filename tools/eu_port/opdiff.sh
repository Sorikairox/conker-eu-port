#!/bin/bash
# opdiff.sh func draft.c  (s96) ndiff with sp offsets normalised (N(sp), sp,N), then a diff of only the changed lines:
# shows structural differences when the frame / struct offsets are still shifted.
R=${CONKER_ROOT:-$HOME/conker}
$R/tools/eu_port/ndiff.sh "$1" "$2" 1 2000 | sed -E 's/-?[0-9]+\(sp\)/N(sp)/; s/sp,[0-9]+$/sp,N/' | grep -v '^@@' | python3 -c '
import sys,difflib
L=sys.stdin.read().split("\n")
r=[l[1:] for l in L if l.startswith("-")]; m=[l[1:] for l in L if l.startswith("+")]
for l in list(difflib.unified_diff(r,m,lineterm="",n=1))[2:]: print(l)'
