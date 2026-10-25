#!/bin/bash
# Headless-Chrome screenshot of the browser build (dev/test aid). The ROM is mounted read-only into
# the server container and fetched by the page with &romurl= (never copied).
#   port/web/shot.sh OUT.png 'QUERY' [budget_ms] [log.html]
#   e.g. port/web/shot.sh /tmp/x.png 'app=game&gfxdemo=1' 15000
set -euo pipefail
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
OUT=$1; Q=$2; BUDGET=${3:-15000}; DOM=${4:-}
NAME=conker-web-shot-$$; PORT=$((8100 + $$ % 800))
docker run -d --rm --name "$NAME" -p 127.0.0.1:$PORT:8000 -v "$ROOT/port/build/web":/www/app:ro \
  -v "$ROOT/baserom.eu.z64":/www/dev/rom.z64:ro -w /www conker-emsdk python3 -m http.server 8000 >/dev/null
trap 'docker rm -f "$NAME" >/dev/null 2>&1 || true' EXIT
sleep 1.5
# P21: the running game (app=game without gfxdemo) never lets virtual time run out (rAF main loop and
# AudioContext), so it is shot in real time over the DevTools protocol (audprobe.js PROBE_SHOT) after
# BUDGET ms instead. PROBE_ANGLE=metal uses the real GPU (default SwiftShader).
if [[ "$Q" == *app=game* && "$Q" != *gfxdemo* ]]; then
  case $OUT in /*) ;; *) OUT=$PWD/$OUT;; esac
  PROBE_SHOT=$OUT PROBE_EVAL_TIMEOUT=${PROBE_EVAL_TIMEOUT:-30000} PROBE_SAMPLES=0 \
    node "$ROOT/port/web/audprobe.js" "http://localhost:$PORT/app/index.html?$Q&romurl=../dev/rom.z64" $(( (BUDGET + 999) / 1000 )) \
    | grep -E "screenshot|evaluate|respond" || true
  exit 0
fi
TMP=$(mktemp -d)
CH="/Applications/Google Chrome.app/Contents/MacOS/Google Chrome"
URL="http://localhost:$PORT/app/index.html?$Q&romurl=../dev/rom.z64"
perl -e 'alarm shift; exec @ARGV' $((BUDGET / 1000 + 60)) "$CH" --headless=new --mute-audio --user-data-dir="$TMP" --use-angle=swiftshader --enable-unsafe-swiftshader \
  --window-size=1000,900 --virtual-time-budget="$BUDGET" --screenshot="$OUT" "$URL" >/dev/null 2>&1 || true
if [ -n "$DOM" ]; then
  perl -e 'alarm shift; exec @ARGV' $((BUDGET / 1000 + 60)) "$CH" --headless=new --mute-audio --user-data-dir="$TMP" --use-angle=swiftshader --enable-unsafe-swiftshader \
    --window-size=1000,900 --virtual-time-budget="$BUDGET" --dump-dom "$URL" > "$DOM" 2>/dev/null || true
fi
rm -rf "$TMP"
echo "screenshot: $OUT"
