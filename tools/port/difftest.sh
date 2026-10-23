#!/bin/bash
# usage: tools/port/difftest.sh FUNC [cand.c] [--self] [--trials N] [--seed S] [--max-insns N] [-v] [--json]
# Host wrapper: runs tools/port/difftest/difftest.py in $CONKERDEV (paths under $CONKER_ROOT are
# translated to /conker/...). P67: DIFFTEST_RETF is now forwarded (it was dropped since P50). DIFFTEST_TIMEOUT (default 600 s, 0 = none) bounds the run inside the
# container with `timeout -s KILL` (macOS has no timeout; P15). P89: DIFFTEST_STK_OLD forwarded. P90: DIFFTEST_STKW_OLD forwarded. Prints EQUIV / DIFFER / UNSURE / ERROR <func>: ...; exit 0 only on EQUIV.
. "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"  # wrong-checkout guard (P7)
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
R=${CONKER_ROOT:-$HOME/conker}
args=()
for a in "$@"; do
  if [ -f "$a" ]; then a=$(cd "$(dirname "$a")" && pwd)/$(basename "$a"); a=${a/#$R//conker}
    case $a in /conker/*) ;; *) echo "ERROR: $a is outside $R" >&2; exit 2;; esac
  fi
  args+=("$a")
done
T=${DIFFTEST_TIMEOUT:-600}; tmo=(); [ "$T" != 0 ] && tmo=(timeout -s KILL "$T")
exec docker exec -e DIFFTEST_TMP="${DIFFTEST_TMP:-build/difftest}" -e DIFFTEST_BUDGET="${DIFFTEST_BUDGET:-30}" -e DIFFTEST_OUTPARAMS="${DIFFTEST_OUTPARAMS:-}" -e DIFFTEST_STEP="${DIFFTEST_STEP:-}" -e DIFFTEST_POKE="${DIFFTEST_POKE:-}" -e DIFFTEST_RET="${DIFFTEST_RET:-}" -e DIFFTEST_RETF="${DIFFTEST_RETF:-}" -e DIFFTEST_ARG="${DIFFTEST_ARG:-}" -e DIFFTEST_ARGMEM="${DIFFTEST_ARGMEM:-}" -e DIFFTEST_OUTW="${DIFFTEST_OUTW:-}" -e DIFFTEST_OUTA="${DIFFTEST_OUTA:-}" -e DIFFTEST_OUTB="${DIFFTEST_OUTB:-}" -e DIFFTEST_CALLS_FROM="${DIFFTEST_CALLS_FROM:-}" -e DIFFTEST_WLOG="${DIFFTEST_WLOG:-}" -e DIFFTEST_WLOG_T="${DIFFTEST_WLOG_T:-}" -e DIFFTEST_EXACT="${DIFFTEST_EXACT:-}" -e DIFFTEST_STK_OLD="${DIFFTEST_STK_OLD:-}" -e DIFFTEST_STKW_OLD="${DIFFTEST_STKW_OLD:-}" -e DIFFTEST_ROMDATA="${DIFFTEST_ROMDATA:-}" -e DIFFTEST_MEMSTK="${DIFFTEST_MEMSTK:-}" -e DIFFTEST_SIGNORE="${DIFFTEST_SIGNORE:-}" -e DIFFTEST_REFLEN="${DIFFTEST_REFLEN:-}" -e DIFFTEST_JALR_DYN="${DIFFTEST_JALR_DYN:-}" -w /conker/conker ${CONKERDEV:-conkerdev} "${tmo[@]}" python3 ../tools/port/difftest/difftest.py "${args[@]}"
