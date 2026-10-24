#!/bin/bash
# P255: run a whole-function harness (tools/port/difftest/nmasm_*.py or a session copy) against the NON_MATCHING build.
# usage: tools/port/nmharness.sh SCRIPT [ARGS...]   (after eval "$(tools/eu_port/wt.sh env <name>)")
#   SCRIPT is a path relative to the worktree root; it runs in $CONKERDEV from /conker/conker as
#   `python3 ../SCRIPT ARGS...` (the convention of every nmasm_*.py; ROM paths in ARGS are relative to conker/,
#   e.g. ../baserom.eu.z64).
# Env: NOBUILD=1 skips the NM build (make VERSION=eu NON_MATCHING=1; default: build first, so the harness sees the
#      current source; reference = build/conker.eu.elf, which verify_all.sh keeps current). HLOG=file keeps the output.
# Output: the harness's verdict line (first line that starts with EQUIV / DIFFER / UNSURE / ERROR, or `RESULT X`)
#      prefixed with that word, e.g. `EQUIV nmasm_floor.py: EQUIV: 0 differences in 400 trials, ...`; a failed build or
#      a harness without a verdict prints `ERROR ...`. Exit 0 only on EQUIV. Used by reverify.sh's HARNESS= knob.
. "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
R=${CONKER_ROOT:-$HOME/conker}; cd "$R" || exit 2
S=$1; shift; [ -f "$S" ] || { echo "ERROR nmharness: no script $S"; exit 2; }
C=${CONKERDEV:?CONKERDEV not set}; mkdir -p port_work/nmharness
L=${HLOG:-port_work/nmharness/$(basename $S .py)_$$.log}
if [ -z "$NOBUILD" ]; then
  docker exec -w /conker $C make -C conker VERSION=eu NON_MATCHING=1 -j4 > $L.build 2>&1 || { echo "ERROR nmharness: NM build failed (see $L.build)"; exit 2; }
fi
docker exec -w /conker/conker $C python3 ../$S "$@" > $L 2>&1
v=$(grep -E '^(RESULT )?(EQUIV|DIFFER|UNSURE|ERROR)' $L | head -1); w=${v#RESULT }; w=${w%%[: ]*}
# harnesses without a verdict word (nmasm_floor.py: `... trials N diffs D ...`): the last line with `diffs D` or
# `D differences` decides (0 = EQUIV); a Python traceback is an ERROR
if [ -z "$v" ] && ! grep -q '^Traceback' $L; then v=$(grep -E '(diffs|differences?)[ :]+[0-9]+|[0-9]+ differences' $L | tail -1)
  n=$(echo "$v" | sed -nE 's/.*(diffs|differences?)[ :]+([0-9]+).*/\2/p' | head -1)
  [ -z "$n" ] && n=$(echo " $v" | sed -nE 's/.*[^0-9]([0-9]+) differences.*/\1/p' | head -1)
  if [ -n "$n" ]; then [ "$n" = 0 ] && w=EQUIV || w=DIFFER; else v=""; fi; fi
t=$(tail -1 $L 2>/dev/null | cut -c1-100); [ -z "$HLOG" ] && rm -f $L $L.build
if [ -z "$v" ]; then echo "ERROR $(basename $S): no verdict line ($t)"; exit 2; fi
echo "$w $(basename $S): $v" | cut -c1-${CUT:-200}
[ "$w" = EQUIV ]
