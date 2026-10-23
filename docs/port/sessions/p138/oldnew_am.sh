#!/bin/bash
# P138: like oldnew.sh for one function with a DIFFTEST_ARGMEM spec. usage: oldnew_am.sh TRIALS func:file ARGMEM
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
T=$1; p=$2; f=${p%%:*}; s=${p#*:}
bash docs/port/sessions/p132/cand.sh $f conker/src_eu/$s.c port_work/p138/new/$f.c
r=""; for v in old new; do
  o=$(DIFFTEST_ARGMEM=$3 DIFFTEST_TMP=build/difftest_p138am_$f tools/port/difftest.sh $f port_work/p138/$v/$f.c --trials $T 2>&1 | grep -E '^(EQUIV|DIFFER|UNSURE|ERROR|CERR)' | head -1 | cut -c1-260)
  r="$r $v: $o |"; done
echo "$f [$3]$r"
