#!/bin/bash
# P255: mutants for a whole-function harness: apply each sed mutant to a source file, rebuild NM, run the harness
# (tools/port/nmharness.sh), restore the source. Generalises port-b P251's port_work/p251/mhuff.sh.
# usage: tools/port/nmharness_mut.sh SRC MUTFILE SCRIPT [ARGS...]   (after eval "$(tools/eu_port/wt.sh env <name>)")
#   SRC      source file relative to the worktree root (e.g. conker/src_eu/game_eu_D1760.c); edited in place and
#            always restored (copy in port_work/nmharness/, restored on exit / interrupt too). Never run it while
#            verify_all.sh, a convert batch or another mutant run on the same worktree is running.
#   MUTFILE  one sed expression per line (`#` comments; a `% ...` tail is ignored, so reverify mutant files work;
#            the expression is applied to the whole SRC, so use patterns that hit one place, or `1,/re/` ranges)
#   SCRIPT ARGS  as for nmharness.sh (keep the trial count modest: every mutant rebuilds NM + runs the harness)
# Env: FROM=N starts at mutant N (1-based). Output: one line per mutant (KILLED / SURVIVED / NOAPPLY / INVALID /
#      ERROR k: expr), then `done: killed K survived S other O` (O = no-apply + invalid + error), the format
#      reverify.sh's HMUT= knob reads. The NM build is redone with the original source at the end.
. "$(dirname "${BASH_SOURCE[0]}")/portguard.sh"
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
R=${CONKER_ROOT:-$HOME/conker}; cd "$R" || exit 2
SRC=$1 M=$2; shift 2; [ -f "$SRC" ] && [ -f "$M" ] || { echo "ERROR nmharness_mut: need SRC and MUTFILE"; exit 2; }
W=port_work/nmharness; mkdir -p $W; O=$W/orig_$$_$(basename $SRC); cp "$SRC" $O
restore() { cmp -s $O "$SRC" || { cp $O "$SRC"; touch "$SRC"; }; }  # no cp -p: make must see the restore as newer than the mutant .o
trap 'restore; rm -f $O; exit 130' INT TERM
k=0; s=0; o=0; i=0
while IFS= read -r line; do
  e=$(echo "${line%%%*}" | sed 's/ *$//'); i=$((i+1)); [ $i -lt ${FROM:-1} ] && continue
  restore; sed "$e" $O > "$SRC" 2>/dev/null || { echo "INVALID $i: $e (sed)"; o=$((o+1)); continue; }
  if cmp -s $O "$SRC"; then echo "NOAPPLY $i: $e"; o=$((o+1)); continue; fi
  r=$(tools/port/nmharness.sh "$@" 2>&1 | tail -1)
  case "$r" in DIFFER*) echo "KILLED $i: $e"; k=$((k+1));; EQUIV*) echo "SURVIVED $i: $e"; s=$((s+1));;
    *"NM build failed"*) echo "INVALID $i: $e (build)"; o=$((o+1));; *) echo "ERROR $i: $e :: $r"; o=$((o+1));; esac
done < <(grep -vE '^\s*(#|$)' "$M")
restore; rm -f $O; trap - INT TERM
docker exec -w /conker ${CONKERDEV:?} make -C conker VERSION=eu NON_MATCHING=1 -j4 > $W/final_build_$$.log 2>&1 || echo "WARNING: final NM rebuild failed ($W/final_build_$$.log)"
echo "done: killed $k survived $s other $o"
