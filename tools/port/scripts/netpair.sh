#!/bin/bash
# P338 online multiplayer phase 1: a 2-player online session in ONE muted headless Chrome (two windows), connected over
# WebRTC on this machine through the page's own copy-paste code flow (tools/port/scripts/netpair.js drives window.__online).
# Player 1 (host) and player 2 (guest) play the first two pads of tools/port/scripts/netmp_pads.py (P1 drives the
# menus into Total War, P2 presses Start on the join page, both move); each page sends only its own pad (?netscript=1).
#   tools/port/scripts/netpair.sh NAME SECS
#   env: NETSIM_HOST / NETSIM_GUEST   e.g. lat:60,jit:20,loss:5 (net.js ?netsim: delay / reorder / drop sent packets)
#        NETD=D                       input delay (host, default 3)       GUEST_LEAVE=1  the guest leaves at the end
#        PLAY_SECS=N                  seconds of free play in the pad scripts (default 20)
# Logs: port_work/p338/NAME/{host,guest}.log; [nethash] lines compared with tools/port/nethash_diff.py.
cd ~/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 10; done
D=port_work/p338/$1; rm -rf "$D"; mkdir -p "$D"
T=${2:-120}
eval "$(python3 tools/port/scripts/netmp_pads.py 7000 "${PLAY_SECS:-20}")"
NAME=conker-web-pair-$$; PORT=$((8100 + $$ % 800))
docker run -d --rm --name "$NAME" -p 127.0.0.1:$PORT:8000 -v "$PWD/port/build/web":/www/app:ro \
  -v "$PWD/baserom.eu.z64":/www/dev/rom.z64:ro -w /www conker-emsdk python3 -m http.server 8000 >/dev/null
trap 'docker rm -f "$NAME" >/dev/null 2>&1 || true' EXIT
sleep 1.5
B="http://localhost:$PORT/app/index.html?romurl=../dev/rom.z64&mute=1&p103boot=1&nethash=1&netscript=1&padf=$PADF0&padf1=$PADF1${NETD:+&netd=$NETD}"
s=$(date +%s)
node tools/port/scripts/netpair.js "$B${NETSIM_HOST:+&netsim=$NETSIM_HOST}" "$B${NETSIM_GUEST:+&netsim=$NETSIM_GUEST}" "$T" "$D" | tee "$D/driver.out" | tail -4
echo "== $1 (${T}s, $(( $(date +%s) - s ))s wall)"
for p in host guest; do
  L=$D/$p.log
  echo "$p: modes $(grep -oE 'frame [0-9]+: mode [0-9]+ \(prev [0-9]+\) level [0-9A-F]+' $L | awk '{print $2 "m" $4 "L" $8}' | tr '\n' ' ' | cut -c1-200)"
  echo "$p: nethash lines $(grep -c '^\[nethash\] [0-9]' $L), traps $(grep -iE 'Aborted|RuntimeError' $L | grep -vc 'no trap'), DESYNC $(grep -c DESYNC $L); $(grep -E '^\[net\] (ICE|playing|session)' $L | head -3 | tr '\n' ' ')"
done
python3 tools/port/nethash_diff.py $D/host.log $D/guest.log 2>&1 | tail -4
