#!/bin/bash
# usage: tools/port/difftest.sh FUNC [cand.c] [--self] [--trials N] [--seed S] [--max-insns N] [-v] [--json]
# Host wrapper: runs tools/port/difftest/difftest.py in $CONKERDEV (paths under $CONKER_ROOT are
# translated to /conker/...). DIFFTEST_TIMEOUT (default 600 s, 0 = none) bounds the run inside the
# container with `timeout -s KILL` (macOS has no timeout; P15). Prints EQUIV / DIFFER / UNSURE / ERROR <func>: ...; exit 0 only on EQUIV.
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
exec docker exec -e DIFFTEST_TMP="${DIFFTEST_TMP:-build/difftest}" -e DIFFTEST_BUDGET="${DIFFTEST_BUDGET:-30}" -e DIFFTEST_OUTPARAMS="${DIFFTEST_OUTPARAMS:-}" -e DIFFTEST_STEP="${DIFFTEST_STEP:-}" -e DIFFTEST_POKE="${DIFFTEST_POKE:-}" -e DIFFTEST_RET="${DIFFTEST_RET:-}" -e DIFFTEST_ARG="${DIFFTEST_ARG:-}" -e DIFFTEST_ARGMEM="${DIFFTEST_ARGMEM:-}" -e DIFFTEST_OUTW="${DIFFTEST_OUTW:-}" -e DIFFTEST_OUTA="${DIFFTEST_OUTA:-}" -e DIFFTEST_OUTB="${DIFFTEST_OUTB:-}" -e DIFFTEST_EXACT="${DIFFTEST_EXACT:-}" -w /conker/conker ${CONKERDEV:-conkerdev} "${tmo[@]}" python3 ../tools/port/difftest/difftest.py "${args[@]}"
