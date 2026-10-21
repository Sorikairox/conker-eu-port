#!/bin/bash
# P14: headless-Chrome check that browser audio is really consumed. Serves the build (read-only
# mounts, as shot.sh), opens the page with &audprobe=1 (main.js installAudioProbe: wraps every
# ScriptProcessorNode's onaudioprocess and counts what the Web Audio graph pulls), lets the audio
# test start without a click (--autoplay-policy=no-user-gesture-required) and polls the probe once a second.
#   port/web/audprobe.sh "app=game&audtest=26390" [seconds]      or "app=game&voicetest=3"
# Chrome runs in real time under the DevTools protocol (port/web/audprobe.js): with
# --virtual-time-budget a running AudioContext keeps the page from ever going idle.
set -euo pipefail
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
Q=$1; SECS=${2:-12}
NAME=conker-web-probe-$$; PORT=$((8100 + $$ % 800))
docker run -d --rm --name "$NAME" -p 127.0.0.1:$PORT:8000 -v "$ROOT/port/build/web":/www/app:ro \
  -v "$ROOT/baserom.eu.z64":/www/dev/rom.z64:ro -w /www conker-emsdk python3 -m http.server 8000 >/dev/null
trap 'docker rm -f "$NAME" >/dev/null 2>&1 || true' EXIT
sleep 1.5
URL="http://localhost:$PORT/app/index.html?$Q&audprobe=1&romurl=../dev/rom.z64"
node "$ROOT/port/web/audprobe.js" "$URL" "$SECS"
