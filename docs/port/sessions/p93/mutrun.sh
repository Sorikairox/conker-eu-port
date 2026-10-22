#!/bin/bash
# P93: run difftest on FUNC with candidate files (new stack window, then DIFFTEST_STKW_OLD=1). usage: mutrun.sh FUNC cand.c...  (TR trials, default 64; knob env passes through)
cd "$(dirname "$0")/../../../.." && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
F=$1; shift
for c in "$@"; do for w in new old; do o=; [ $w = old ] && o=1
  r=$(DIFFTEST_TMP=build/difftest_p93_$F${KTAG:-} DIFFTEST_STKW_OLD=$o tools/port/difftest.sh $F $c --trials ${TR:-64} 2>&1 | grep -E '^(EQUIV|DIFFER|UNSURE|ERROR)' | cut -c1-200)
  echo "$(basename $c) [$w]: $r"; [ -n "${NEWONLY:-}" ] && break; done; done
