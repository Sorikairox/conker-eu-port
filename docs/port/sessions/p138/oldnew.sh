#!/bin/bash
# P138: difftest the saved old NM block (port_work/p138/old/FUNC.c) and the current one (new/FUNC.c), random trials.
# usage: oldnew.sh TRIALS func:file ...   prints "FUNC old: ... | new: ..."
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
T=$1; shift
for p in "$@"; do f=${p%%:*}; s=${p#*:}
  bash docs/port/sessions/p132/cand.sh $f $(ls conker/src_eu/$s.c conker/src_eu/*/$s.c 2>/dev/null | head -1) port_work/p138/new/$f.c
  r=""; for v in old new; do
    o=$(DIFFTEST_TMP=build/difftest_p138_$f tools/port/difftest.sh $f port_work/p138/$v/$f.c --trials $T 2>&1 | grep -E '^(EQUIV|DIFFER|UNSURE|ERROR|CERR)' | head -1 | cut -c1-230)
    r="$r $v: $o |"; done
  echo "$f$r"
done
