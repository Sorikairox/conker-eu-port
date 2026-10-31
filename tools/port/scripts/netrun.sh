#!/bin/bash
# P337 online-multiplayer phase 0: one muted headless-Chrome run of the determinism harness (port/ultra/pc_net.c,
# pc_nethash.c). Forced online determinism (?netdet=1), 4 controllers (?padmask=F), frame scripts for pads 1..4.
#   tools/port/scripts/netrun.sh NAME SECS [EXTRA_QUERY]
#   env: PADF0..PADF3  pad scripts (F:BTN:X:Y,...) for controllers 1..4 (default: tools/port/scripts/netmp_pads.py)
#        SHOTS         screenshot times in ms              THROTTLE=N  CDP CPU throttling (N x slower)
#        DUMP=1        dump the hashed memory at the ?nethashstop retrace (port_work/p337/NAME/mem.bin)
# Logs: port_work/p337/NAME/chrome.log ([nethash] lines: tools/port/nethash_diff.py A B). One Chrome at a time.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1   # P353: the worktree this script lives in
[ -n "${PROBE_NOWAIT:-}" ] || while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 10; done
D=port_work/p337/$1; rm -rf "$D"; mkdir -p "$D"
T=${2:-200}
if [ -z "${PADF0:-}" ]; then eval "$(python3 tools/port/scripts/netmp_pads.py)"; fi
S=""; for t in ${SHOTS:-}; do S="$S${S:+; }$t:shot:$D/s_${t}ms.png"; done
Q="app=game&netdet=1&padmask=${PADMASK:-F}&p103boot=1&padf=$PADF0&padf1=$PADF1&padf2=$PADF2&padf3=$PADF3${3:-}"
s=$(date +%s)
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" PROBE_THROTTLE=${THROTTLE:-} \
  PROBE_DUMP=${DUMP:+$D/mem.bin} port/web/audprobe.sh "$Q" "$T" > "$D.out" 2>&1
L=$D/chrome.log
echo "== $1 (${T}s run, $(( $(date +%s) - s ))s wall)"
echo "modes: $(grep -oE 'frame [0-9]+: mode [0-9]+ \(prev [0-9]+\) level [0-9A-F]+' $L | awk '{print $2 "m" $4 "L" $8}' | tr '\n' ' ' | cut -c1-300)"
echo "nethash lines: $(grep -c '^\[nethash\] [0-9]' $L)  last: $(grep '^\[nethash\] [0-9]' $L | tail -1)"
grep -E '^\[netprof\]|^\[netsnap\]' $L | tail -4
echo "traps/aborts: $(grep -iE 'Aborted|RuntimeError|trap' $L | grep -vc 'no trap')  last frame: $(grep -oE 'frame [0-9]+' $L | tail -1)  unaudited void icalls (P373): $(grep -c '^\[icall\] UNAUDITED' $L)"
