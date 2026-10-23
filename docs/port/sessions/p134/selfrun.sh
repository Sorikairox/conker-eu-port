#!/bin/bash
# P134: difftest of each function's current NM block (p132/cand.sh: the whole #ifdef NON_MATCHING block, so the
# prototypes declared in the block stay; --self keeps only the function body and drops them), one after the other.
# usage: selfrun.sh TRIALS func...   (env passes through: DIFFTEST_TRAPSCAN_OLD etc.)
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
T=$1; shift; mkdir -p port_work/p134/cand
for f in "$@"; do
  src=$(grep -l "GLOBAL_ASM(\"asm/nonmatchings/[^/]*/$f.s\")" conker/src_eu/*.c conker/src_eu/*/*.c 2>/dev/null | head -1)
  c=port_work/p134/cand/$f.c; bash docs/port/sessions/p132/cand.sh $f $src $c || { echo "ERROR $f: no candidate"; continue; }
  DIFFTEST_TMP=build/difftest_p134_$f tools/port/difftest.sh $f $c --trials $T 2>&1 | grep -E '^(EQUIV|DIFFER|UNSURE|ERROR|CERR)|\[POKE|\[knob' | cut -c1-300
done
