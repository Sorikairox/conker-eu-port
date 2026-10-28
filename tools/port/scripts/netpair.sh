#!/bin/bash
# P338 / P344 online multiplayer: an online session of PLAYERS (2..4, default 2) peers in ONE muted headless Chrome (one
# window each), connected over WebRTC on this machine through the page's own copy-paste code flow
# (tools/port/scripts/netgroup.js drives window.__online: host, invite, join, accept, start).
# Player 1 (host) .. player 4 (guest4) play the pads of tools/port/scripts/netmp_pads.py (P1 drives the menus into Total
# War, the others press Start on the join page, all move); each page sends only its own pad (?netscript=1).
#   tools/port/scripts/netpair.sh NAME SECS
#   env: PLAYERS=2..4                  pages host, guest (player 2), guest3, guest4
#        NETSIM_HOST / NETSIM_GUEST / NETSIM_GUEST3 / NETSIM_GUEST4   e.g. lat:60,jit:20,loss:5 (net.js ?netsim: delay /
#                                     reorder / drop that page's sent packets)
#        NETFAIL=A-B                  test: players A and B (2..4) never get a direct link (?netfailto): the host relays
#        NETD=D                       input delay (host, default 3; auto = from the pings)
#        LEAVE=NAME (GUEST_LEAVE=1 = guest)  that page leaves at the end, the others run on 15 s
#        ROOM=1  P345: connect with a room code through a LOCAL room server (tools/port/scripts/roomserver.mjs, the
#                function's core.mjs on a Map; never the production function), ROOMCHECK=1 also checks an unknown
#                code and a full room (ROOMMAX=N room size; netgroup.js)
#        UI=1  codes (or the room code) through the Online panel's buttons     SHOTS="60 150"  screenshots of every window
#        DESYNC_AT=N  test: the guest flips one byte of game memory at retrace N (?netdesync, desync report);
#                     DESYNC_OFF=decimal offset in n64_rdram (default 0x200000)
#        HIDE=AT:FOR  the guest's page is hidden from AT s for FOR s     REALBG=1  normal background throttling
#        PLAY_SECS=N                  seconds of free play in the pad scripts (default 20)
#        HOSTQ / GUESTQ  P346: extra query for the host's / player 2's page, e.g. HOSTQ='&preset=modern' GUESTQ='&panel=options'
#        PADS=FILE  sourced after netmp_pads.py to replace PADF0..PADF3 (netmp_bunker.sh: Bunker Deathmatch,
#                   NET_BUNKER_DEMO=1 player 2 takes a weapon, draws it and fires)
# Logs: port_work/${NETDIR:-p339}/NAME/{host,guest,guest3,guest4}.log; [nethash] lines of every guest compared with
# the host's by tools/port/nethash_diff.py.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1   # P353: the worktree this script lives in
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
[ -n "${PROBE_NOWAIT:-}" ] || while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 10; done
D=port_work/${NETDIR:-p339}/$1; rm -rf "$D"; mkdir -p "$D"
T=${2:-120}; P=${PLAYERS:-2}
eval "$(python3 tools/port/scripts/netmp_pads.py 7000 "${PLAY_SECS:-20}")"
[ -n "${PADS:-}" ] && source "$PADS"   # P341: another pad script, e.g. tools/port/scripts/netmp_bunker.sh (Bunker)
NAME=conker-web-pair-$$; PORT=${PROBE_PORT:-$((8100 + $$ % 800))}   # P353: PROBE_PORT pins the port
docker run -d --rm --name "$NAME" -p 127.0.0.1:$PORT:8000 -v "$PWD/port/build/web":/www/app:ro \
  -v "$PWD/baserom.eu.z64":/www/dev/rom.z64:ro -w /www conker-emsdk python3 -m http.server 8000 >/dev/null
RPID=
trap 'docker rm -f "$NAME" >/dev/null 2>&1 || true; [ -n "$RPID" ] && kill $RPID 2>/dev/null' EXIT
ROOMQ=
if [ -n "${ROOM:-}" ]; then   # P345: the local room server (killed by the trap)
  RPORT=$((8900 + $$ % 90)); node tools/port/scripts/roomserver.mjs $RPORT > "$D/roomserver.log" 2>&1 &
  RPID=$!; ROOMQ="&roomapi=http://127.0.0.1:$RPORT/api/room"
fi
sleep 1.5
B="http://localhost:$PORT/app/index.html?romurl=../dev/rom.z64&mute=1&p103boot=1&nethash=1&netscript=1&netpanel=1&padf=$PADF0&padf1=$PADF1&padf2=$PADF2&padf3=$PADF3${NETD:+&netd=$NETD}$ROOMQ"
FA=${NETFAIL%-*}; FB=${NETFAIL#*-}
fail() { [ -n "${NETFAIL:-}" ] && { [ "$1" = "$FA" ] && echo "&netfailto=$FB"; [ "$1" = "$FB" ] && echo "&netfailto=$FA"; }; }
URLS=("$B${NETSIM_HOST:+&netsim=$NETSIM_HOST}${HOSTQ:-}"
      "$B${NETSIM_GUEST:+&netsim=$NETSIM_GUEST}${GUESTQ:-}${DESYNC_AT:+&netdesync=$DESYNC_AT}${DESYNC_OFF:+&netdesyncoff=$DESYNC_OFF}$(fail 2)"
      "$B${NETSIM_GUEST3:+&netsim=$NETSIM_GUEST3}$(fail 3)"
      "$B${NETSIM_GUEST4:+&netsim=$NETSIM_GUEST4}$(fail 4)")
NAMES=(host guest guest3 guest4)
s=$(date +%s)
node tools/port/scripts/netgroup.js "$T" "$D" "${URLS[@]:0:$P}" | tee "$D/driver.out" | tail -$((P + 4))
echo "== $1 ($P players, ${T}s, $(( $(date +%s) - s ))s wall)"
for p in "${NAMES[@]:0:$P}"; do
  L=$D/$p.log
  echo "$p: modes $(grep -oE 'frame [0-9]+: mode [0-9]+ \(prev [0-9]+\) level [0-9A-F]+' $L | awk '{print $2 "m" $4 "L" $8}' | tr '\n' ' ' | cut -c1-200)"
  echo "$p: nethash lines $(grep -c '^\[nethash\] [0-9]' $L), traps $(grep -iE 'Aborted|RuntimeError' $L | grep -vc 'no trap'), DESYNC $(grep -c DESYNC $L); $(grep -E '^\[net\] (session|mesh)' $L | head -2 | tr '\n' ' ')"
done
for p in "${NAMES[@]:1:$((P - 1))}"; do echo "-- host vs $p"; python3 tools/port/nethash_diff.py $D/host.log $D/$p.log 2>&1 | tail -3; done
