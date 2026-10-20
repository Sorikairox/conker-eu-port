#!/bin/bash
# rdiff.sh func draft.c [n]  (s75) refdiff.py with relocation noise removed (%lo offsets on at/gp-relative lines, lui immediates), changed lines only
python3 ${CONKER_ROOT:-$HOME/conker}/docs/sessions/s65_drafts/refdiff.py "$1" "$2" 2>&1 | grep "^[-+]" | grep -v "^---\|^+++" |
 sed -E 's/^([-+]lui(at|v0|t[0-9])),.*/\1,K/; s/,-?[0-9]+\((at|v0|t[0-9])\)$/,K(\1)/; s/,0\((at|v0|t[0-9])\)$/,K(\1)/' |
 awk '{c[$0]++; l[NR]=$0} END{for(i=1;i<=NR;i++){s=l[i]; o=(substr(s,1,1)=="-"?"+":"-") substr(s,2); if(c[o]>0){c[o]--; continue} print s}}' | head -${3:-40}
