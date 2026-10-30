#!/bin/bash
# P354 trailer: a real 4-player online session (4 windows in one muted headless Chrome, WebRTC on this machine) through
# the Online panel with a room code (local room server tools/port/scripts/roomserver.mjs, never the production function),
# Bunker Deathmatch with the netmp_bunker.sh pads + NET_BUNKER_PLAY random play. Same flow as tools/port/scripts/netpair.sh
# (PLAYERS=4 ROOM=1 UI=1 PADS=netmp_bunker.sh) but served by node (cdp.mjs) and without netpair's wait for other
# sessions' Chrome runs; pages get the trailer's display options (widescreen / hi-res 2D / high frame rate: page-side,
# each player's own choice). Screenshots of every window at SHOTS seconds after the start.
#   tools/port/trailer/net4.sh OUTDIR SECS        env NETUI=gmenu (P370: the game-style ONLINE pages), SHOTS="10 60 ..." (default below), PLAY (s of random play, 40)
# Then tools/port/nethash_diff.py OUTDIR/host.log OUTDIR/guestN.log; capture.mjs shot 'mp4' replays the same pads
# under ?netdet=1 frame by frame (pictures) and its ?nethash lines can be compared with the host's.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1   # P353: the worktree this script lives in
D=${1:?outdir}; T=${2:-200}; mkdir -p "$D"
export NET_BUNKER_PLAY=${PLAY:-40}
eval "$(python3 tools/port/scripts/netmp_pads.py 7000 20)"
source tools/port/scripts/netmp_bunker.sh
printf 'PADF0=%s\nPADF1=%s\nPADF2=%s\nPADF3=%s\n' "$PADF0" "$PADF1" "$PADF2" "$PADF3" > "$D/pads.env"
SPORT=$((8560 + $$ % 20)); RPORT=$((8580 + $$ % 10))
node -e "import('./tools/port/trailer/cdp.mjs').then(m => m.serve({ '/app/': 'port/build/web', '/dev/rom.z64': 'baserom.eu.z64' }, $SPORT))" > "$D/server.log" 2>&1 &
SPID=$!
node tools/port/scripts/roomserver.mjs $RPORT > "$D/roomserver.log" 2>&1 &
RPID=$!
trap 'kill $SPID $RPID 2>/dev/null' EXIT
sleep 1.5
OPTQ='&opt=hires2d:1,widescreen:1,hfr:1,smoothfont:1'
# P370 NETUI=gmenu: through the game-style ONLINE pages (netgroup.js UI=gmenu, ?gmenutest fake pads) with screenshots of
# every step (GSHOTS) at VIEWPORT (default 1920x1080) on every page; default: the page's Online panel (P354, UI=1)
GQ=; NUI=1
if [ "${NETUI:-}" = gmenu ]; then GQ='&gmenutest=1'; NUI=gmenu; V=${VIEWPORT:-1920x1080}; export GSHOTS=1 VIEWPORTS="$V,$V,$V,$V"; fi
B="http://127.0.0.1:$SPORT/app/index.html?romurl=../dev/rom.z64&mute=1&p103boot=1&nethash=1&netscript=1&netpanel=1&padf=$PADF0&padf1=$PADF1&padf2=$PADF2&padf3=$PADF3&roomapi=http://127.0.0.1:$RPORT/api/room$OPTQ$GQ"
ROOM=1 UI=$NUI JOINSHOTS=1 SHOTS="${SHOTS:-10 100 160 200}" node tools/port/scripts/netgroup.js "$T" "$D" "$B" "$B" "$B" "$B" | tee "$D/driver.out" | grep -v '^netgroup [0-9]* s:' | tail -8
for p in host guest guest3 guest4; do
  echo "$p: nethash lines $(grep -c '^\[nethash\] [0-9]' $D/$p.log), traps $(grep -iE 'Aborted|RuntimeError' $D/$p.log | grep -vc 'no trap'), DESYNC $(grep -c DESYNC $D/$p.log)"
done
for p in guest guest3 guest4; do echo "-- host vs $p"; python3 tools/port/nethash_diff.py $D/host.log $D/$p.log 2>&1 | tail -2; done
