#!/bin/bash
# P93: re-run difftest on the NON_MATCHING bodies that call a >16-argument function (wide_scan.py rows),
# with the P90 stack window (args 4..63) and with the old one (DIFFTEST_STKW_OLD=1). usage: recheck.sh FUNC... (TR trials, default 64)
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=port_work/p93/rc; mkdir -p $D
for F in "$@"; do
  src=$(grep -l "nonmatchings/[^/]*/$F.s" conker/src_eu/*.c | head -1)
  bash docs/port/sessions/p90/draft.sh $F $src $D/$F.c >/dev/null
  for w in new old; do
    o=; [ $w = old ] && o=1
    r=$(DIFFTEST_TMP=build/difftest_p93_$F DIFFTEST_STKW_OLD=$o tools/port/difftest.sh $F $D/$F.c --trials ${TR:-64} 2>&1 | grep -E '^(EQUIV|DIFFER|UNSURE|ERROR)' | cut -c1-220)
    echo "$F [$w] ${src##*/}: $r"
  done
done
