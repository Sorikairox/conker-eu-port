#!/bin/bash
# usage: repair_ctx.sh <func>   -> compact repair context: target asm, current draft, aligned diff region
# Draft = tools/decomp-permuter/repair/<f>.c (latest attempt), else permuter best.c, else sweep draft.
# Diff = columns "ref mine asm" from repair_try.sh (run it first; this runs it if there is no diff yet).
P=~/conker/tools/decomp-permuter; R=$P/repair; f=$1
d=$R/$f.c
if [ ! -f $d ]; then
  for c in $R/fresh/$f.c $P/nm/$f/best.c $P/sweep/drafts4/$f.c $P/sweep/drafts3/$f.c $P/sweep/drafts2/$f.c $P/sweep/drafts/$f.c $P/drafts/$f.c $P/drafts_pc/$f.c; do
    [ -f $c ] && { mkdir -p $R; grep -v 'PERMUTER CHANGED' $c > $d; break; }; done
fi
s=$(find ~/conker/conker/asm/nonmatchings -name $f.s | head -1)
n=$(grep -c '^ *\/\*' $s)
echo "=== TARGET $f ($n insns)"
[ "$n" -gt "${MAXT:-60}" ] && echo "(listing skipped: > ${MAXT:-60} insns; see DIFF, or MAXT=999 for all)" || grep -E '^\s*(/\*|\.L|glabel)' $s | sed -E 's/\/\* [0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*\/ *//' | grep -v '^glabel'
if [ -f $d ]; then echo "=== DRAFT ($d)"; head -90 $d | grep -v "^$"; else echo "=== no draft: m2c needed"; fi
[ -f $R/$f.diff ] || ~/conker/tools/eu_port/repair_try.sh $f $d >/dev/null
echo "=== DIFF (ref  mine  asm)"
awk '{l[NR]=$0; if ($1=="**" && $0 !~ /%hi|%lo|jal /) {if(!first) first=NR; last=NR}} END{
  if(!first){print "(no differing words; size/other)"; exit}
  a=first-3; if(a<1)a=1; b=first+14; if(b>NR)b=NR
  for(i=a;i<=b;i++) print l[i]; if(last>b) print "... last diff at line " last " of " NR}' $R/$f.diff | sed '/^$/d'
h=$(python3 ~/conker/tools/eu_port/draftcheck.py $f $d 2>/dev/null | grep -v "no .s found"); [ -n "$h" ] && { echo "=== HINTS (draftcheck.py: call patterns / double scaling)"; echo "$h"; }
