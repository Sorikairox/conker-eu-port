#!/bin/bash
# usage: tools/port/difftest.sh FUNC [cand.c] [--self] [--trials N] [--seed S] [--max-insns N] [-v] [--json]
# Host wrapper: runs tools/port/difftest/difftest.py in $CONKERDEV (paths under $CONKER_ROOT are
# translated to /conker/...). P67: DIFFTEST_RETF is now forwarded (it was dropped since P50). DIFFTEST_TIMEOUT (default 600 s, 0 = none) bounds the run inside the
# container with `timeout -s KILL` (macOS has no timeout; P15). P89: DIFFTEST_STK_OLD forwarded. P90: DIFFTEST_STKW_OLD forwarded. Prints EQUIV / DIFFER / UNSURE / ERROR <func>: ...; exit 0 only on EQUIV. P176: DIFFTEST_PAGESTUB_OLD forwarded. P198: DIFFTEST_STUBW_OLD forwarded. P200: DIFFTEST_ARGF_OLD forwarded. P211: DIFFTEST_JALRARG_OLD / DIFFTEST_STKFILL forwarded. P214: DIFFTEST_JALARG_OLD / DIFFTEST_JALARG_WIDE / DIFFTEST_DECLKW_OLD / DIFFTEST_NOPROTO forwarded. P215: DIFFTEST_JALRTGT_OLD / DIFFTEST_JALRSKIP / DIFFTEST_TUPEEK_OLD forwarded. P221: DIFFTEST_BADJALR_OLD forwarded. P234: DIFFTEST_INCHDR_OLD forwarded. P225: DIFFTEST_NMNEST_OLD forwarded. P235: DIFFTEST_SLOTS / DIFFTEST_SLOTDIR / DIFFTEST_SLOT_MAXWAIT forwarded.
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
# P235 job limiter: at most DIFFTEST_SLOTS (default 2, 0 = off) difftest jobs per container (Docker memory is shared
# with the browser slot). A slot is a dir <DIFFTEST_SLOTDIR>/slotN holding the in-container PID of the job's bash; taking
# and cleaning slots happens under flock. A slot whose PID is dead inside the container is stale and removed. A job with
# no free slot waits (one notice on stderr); DIFFTEST_SLOT_MAXWAIT=S gives up after S s (ERROR, exit 3). Test: slots_test.sh.
SLOTSH='N=${DIFFTEST_SLOTS:-2}; [ "$N" = 0 ] && exec "$@"
S=${DIFFTEST_SLOTDIR:-/tmp/difftest_slots}; mkdir -p "$S"; t0=$(date +%s); got=; said=
while :; do
  exec 9>"$S/.lock"; flock 9
  for i in $(seq 1 $N); do d=$S/slot$i
    if [ -d $d ]; then p=$(cat $d/pid 2>/dev/null); if [ -n "$p" ] && kill -0 $p 2>/dev/null; then continue; fi; rm -rf $d; fi
    mkdir $d && echo $$ > $d/pid && { got=$d; break; }
  done
  flock -u 9; exec 9>&-
  [ -n "$got" ] && break
  [ -z "$said" ] && { echo "difftest.sh: all $N job slots busy ($S), waiting" >&2; said=1; }
  [ -n "$DIFFTEST_SLOT_MAXWAIT" ] && [ $(( $(date +%s) - t0 )) -ge "$DIFFTEST_SLOT_MAXWAIT" ] && { echo "ERROR difftest.sh: no job slot after ${DIFFTEST_SLOT_MAXWAIT}s"; exit 3; }
  sleep 2
done
[ -n "$said" ] && echo "difftest.sh: got $got after $(( $(date +%s) - t0 ))s" >&2
trap "rm -rf $got" EXIT; "$@"; exit $?'
exec docker exec -e DIFFTEST_TMP="${DIFFTEST_TMP:-build/difftest}" -e DIFFTEST_BUDGET="${DIFFTEST_BUDGET:-30}" -e DIFFTEST_OUTPARAMS="${DIFFTEST_OUTPARAMS:-}" -e DIFFTEST_STEP="${DIFFTEST_STEP:-}" -e DIFFTEST_POKE="${DIFFTEST_POKE:-}" -e DIFFTEST_POKE_OLD="${DIFFTEST_POKE_OLD:-}" -e DIFFTEST_TRAPSCAN_OLD="${DIFFTEST_TRAPSCAN_OLD:-}" -e DIFFTEST_PREAD_OLD="${DIFFTEST_PREAD_OLD:-}" -e DIFFTEST_HDRSLOT_OLD="${DIFFTEST_HDRSLOT_OLD:-}" -e DIFFTEST_RET="${DIFFTEST_RET:-}" -e DIFFTEST_RETF="${DIFFTEST_RETF:-}" -e DIFFTEST_ARG="${DIFFTEST_ARG:-}" -e DIFFTEST_ARGMEM="${DIFFTEST_ARGMEM:-}" -e DIFFTEST_OUTW="${DIFFTEST_OUTW:-}" -e DIFFTEST_OUTA="${DIFFTEST_OUTA:-}" -e DIFFTEST_OUTB="${DIFFTEST_OUTB:-}" -e DIFFTEST_OUTP="${DIFFTEST_OUTP:-}" -e DIFFTEST_CALLS_FROM="${DIFFTEST_CALLS_FROM:-}" -e DIFFTEST_WLOG="${DIFFTEST_WLOG:-}" -e DIFFTEST_WLOG_T="${DIFFTEST_WLOG_T:-}" -e DIFFTEST_EXACT="${DIFFTEST_EXACT:-}" -e DIFFTEST_STK_OLD="${DIFFTEST_STK_OLD:-}" -e DIFFTEST_STKW_OLD="${DIFFTEST_STKW_OLD:-}" -e DIFFTEST_ROMDATA="${DIFFTEST_ROMDATA:-}" -e DIFFTEST_MEMSTK="${DIFFTEST_MEMSTK:-}" -e DIFFTEST_SIGNORE="${DIFFTEST_SIGNORE:-}" -e DIFFTEST_REFLEN="${DIFFTEST_REFLEN:-}" -e DIFFTEST_JALR_DYN="${DIFFTEST_JALR_DYN:-}" -e DIFFTEST_VARARGS_REF="${DIFFTEST_VARARGS_REF:-}" -e DIFFTEST_TUCMP_LEN="${DIFFTEST_TUCMP_LEN:-}" -e DIFFTEST_OUTA_PERCALL="${DIFFTEST_OUTA_PERCALL:-}" -e DIFFTEST_PAGESTUB_OLD="${DIFFTEST_PAGESTUB_OLD:-}" -e DIFFTEST_STUBW_OLD="${DIFFTEST_STUBW_OLD:-}" -e DIFFTEST_ARGF_OLD="${DIFFTEST_ARGF_OLD:-}" -e DIFFTEST_JALRARG_OLD="${DIFFTEST_JALRARG_OLD:-}" -e DIFFTEST_JALRTGT_OLD="${DIFFTEST_JALRTGT_OLD:-}" -e DIFFTEST_JALRSKIP="${DIFFTEST_JALRSKIP:-}" -e DIFFTEST_TUPEEK_OLD="${DIFFTEST_TUPEEK_OLD:-}" -e DIFFTEST_JALARG_OLD="${DIFFTEST_JALARG_OLD:-}" -e DIFFTEST_JALARG_WIDE="${DIFFTEST_JALARG_WIDE:-}" -e DIFFTEST_NOPROTO="${DIFFTEST_NOPROTO:-}" -e DIFFTEST_DECLKW_OLD="${DIFFTEST_DECLKW_OLD:-}" -e DIFFTEST_STKFILL="${DIFFTEST_STKFILL:-}" -e DIFFTEST_BADJALR_OLD="${DIFFTEST_BADJALR_OLD:-}" -e DIFFTEST_INCHDR_OLD="${DIFFTEST_INCHDR_OLD:-}" -e DIFFTEST_NMNEST_OLD="${DIFFTEST_NMNEST_OLD:-}" -e DIFFTEST_SLOTS="${DIFFTEST_SLOTS:-}" -e DIFFTEST_SLOTDIR="${DIFFTEST_SLOTDIR:-}" -e DIFFTEST_SLOT_MAXWAIT="${DIFFTEST_SLOT_MAXWAIT:-}" -w /conker/conker ${CONKERDEV:-conkerdev} bash -c "$SLOTSH" difftest_slot "${tmo[@]}" python3 ../tools/port/difftest/difftest.py "${args[@]}"
