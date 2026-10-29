#!/bin/bash
# P357: make a test recording with the page's input recorder in headless Chrome (tools/port/scripts/e2e_record.js: the
# Options / Record panel clicks and real-time key events of a player). Used to prove the recorder (docs/port/E2E.md).
#   tools/port/scripts/e2e_record.sh NAME 'STEPS' [EXTRA_QUERY]     e.g. EXTRA_QUERY='&opt=widescreen:1,hfr:1'
#   STEPS: see e2e_record.js ("RETRACE:down:Enter; RETRACE:up:Enter; ...; RETRACE:stop"); default: E2E_ROUTE below
#   Output: port_work/e2e_rec/NAME/ (chrome.log, the downloaded .ckrec)
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
[ -n "${PROBE_NOWAIT:-}" ] || while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 10; done
# the hold-L route (holdl.sh) by keyboard: Start at the title and the menu, L held over the opening, then a walk on level 0x29
E2E_ROUTE='3386:down:Enter; 3401:up:Enter; 4458:down:Enter; 4473:up:Enter; 5600:down:KeyR; 5800:up:KeyR;
 6000:down:KeyW; 6300:down:KeyD; 6420:up:KeyD; 6500:down:Space; 6512:up:Space; 6700:down:KeyA; 6800:up:KeyA; 6900:up:KeyW;
 6950:down:KeyS; 7100:up:KeyS; 7150:down:KeyF; 7160:up:KeyF; 7200:down:KeyW; 7400:down:Space; 7420:up:Space; 7600:up:KeyW; 7700:stop'
D=port_work/e2e_rec/$1; rm -rf "$D"; mkdir -p "$D"
WEB=$(cd "${WEB:-port/build/web}" && pwd)
NAME=conker-e2erec-$$; PORT=${PROBE_PORT:-$((8100 + $$ % 800))}
docker run -d --rm --name "$NAME" -p 127.0.0.1:$PORT:8000 -v "$WEB":/www/app:ro -v "$PWD/baserom.eu.z64":/www/dev/rom.z64:ro \
  -w /www conker-emsdk python3 -m http.server 8000 >/dev/null || exit 1
trap 'docker rm -f "$NAME" >/dev/null 2>&1 || true' EXIT
sleep 1.5
node tools/port/scripts/e2e_record.js "http://localhost:$PORT/app/index.html?romurl=../dev/rom.z64&mute=1${3:-}" "$D" "$1" "${2:-$E2E_ROUTE}" | tee "$D/driver.out"
