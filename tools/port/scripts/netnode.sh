#!/bin/bash
# P337: the determinism harness in node (second runtime: no WebGL, one retrace per main-loop tick, own pacing), same
# session as netrun.sh: forced online determinism, 4 controllers, netmp_pads.py scripts, per-retrace [nethash] lines.
#   [STOP=N] tools/port/scripts/netnode.sh NAME SECS  (STOP: pause after retrace N, dump to port_work/p337/NAME.mem.bin)
#       (log port_work/p337/NAME.node.log; run node jobs one at a time)
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1   # P353: the worktree this script lives in
eval "$(python3 tools/port/scripts/netmp_pads.py)"
mkdir -p port_work/p337
[ -n "${STOP:-}" ] && export PORT_NETHASHSTOP=$STOP NETDUMP=/out/$1.mem.bin
PORT_NETDET=1 PORT_PADMASK=F PORT_NETHASH=1 PORT_P103BOOT=1 PORT_PADF="$PADF0" PORT_PADF1="$PADF1" PORT_PADF2="$PADF2" \
  PORT_PADF3="$PADF3" port/web/boot.sh "${2:-400}" "$PWD/port_work/p337/$1.node.log" | head -3
L=port_work/p337/$1.node.log
echo "nethash lines: $(grep -c '^\[nethash\] [0-9]' $L)  last: $(grep '^\[nethash\] [0-9]' $L | tail -1)"
echo "modes: $(grep -oE 'frame [0-9]+: mode [0-9]+ \(prev [0-9]+\) level [0-9A-F]+' $L | awk '{print $2 "m" $4 "L" $8}' | tr '\n' ' ' | cut -c1-300)"
