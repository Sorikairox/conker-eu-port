#!/bin/bash
# P190 (from port-b p186 mut55.sh): mutants through a whole-function harness: sed on SRC, NM build, harness N trials.
# usage: mutnm.sh SRC(conker/src_eu/x.c) HARNESS(tools/port/difftest/x.py) muts.txt [N]
# Restores SRC from port_work/p200/<base>.good.c after each mutant (and at the end).
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
S=$1; H=$2; M=$3; N=${4:-120}; G=port_work/p200/$(basename $S .c | sed 's/game_eu_//').good.c
[ -f $G ] || { echo "no $G"; exit 1; }
trap "cp $G $S" EXIT
grep -vE '^\s*(#|$)' "$M" | while IFS= read -r e; do
  sed "$e" $G > $S || { echo "SED ERROR [$e]"; continue; }
  cmp -s $G $S && { echo "NOT APPLIED [$e]"; continue; }
  if ! docker exec -w /conker/conker $CONKERDEV make VERSION=eu NON_MATCHING=1 -j4 > port_work/p200/mutnm.build.log 2>&1; then echo "BUILD FAIL [$e]"; continue; fi
  o=$(docker exec -w /conker/conker $CONKERDEV timeout 900 python3 ../$H $N 1 2>&1 | tail -1)
  case "$o" in EQUIV*) echo "SURVIVED [$e]";; DIFFER*) echo "KILLED [$e]";; *) echo "INVALID ($o) [$e]";; esac
done
cp $G $S
docker exec -w /conker/conker $CONKERDEV make VERSION=eu NON_MATCHING=1 -j4 > port_work/p200/mutnm.build.log 2>&1; echo "rebuilt good: rc $?"
