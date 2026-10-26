#!/bin/bash
# Play the browser build yourself, on a frozen copy that agent sessions can't change under you.
#   tools/eu_port/play.sh          snapshot the latest web build, serve it, open the browser
#   tools/eu_port/play.sh again    serve the last snapshot again (no new copy)
#   tools/eu_port/play.sh stop     stop the play server
# Serves http://localhost:8070/ from container "conker-play" (agents use 8064 / conker-web-serve).
set -euo pipefail
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
WEB=${CONKER_WEB_WT:-$HOME/conker-wt/web}
PLAY=${CONKER_PLAY_DIR:-$HOME/conker-play}
PORT=${CONKER_PLAY_PORT:-8070}
NAME=conker-play
IMG=conker-emsdk

if [ "${1:-}" = stop ]; then docker rm -f "$NAME" >/dev/null 2>&1 && echo stopped || echo "not running"; exit 0; fi

if ! docker info >/dev/null 2>&1; then
  echo "starting Docker Desktop..."; open -a Docker
  for _ in $(seq 60); do docker info >/dev/null 2>&1 && break; sleep 2; done
  docker info >/dev/null 2>&1 || { echo "Docker did not start"; exit 1; }
fi
docker image inspect "$IMG" >/dev/null 2>&1 || { echo "image $IMG missing: run $WEB/port/web/run.sh image"; exit 1; }

if [ "${1:-}" = again ]; then
  DEST=$(ls -1d "$PLAY"/build-* 2>/dev/null | tail -1)
  [ -n "$DEST" ] || { echo "no snapshot yet: run without 'again'"; exit 1; }
else
  SRC=$WEB/port/build/web
  [ -f "$SRC/conker.wasm" ] || { echo "no build at $SRC: run $WEB/port/web/run.sh build"; exit 1; }
  DEST=$PLAY/build-$(date +%Y%m%d-%H%M%S)
  mkdir -p "$DEST"
  cp -R "$SRC"/. "$DEST"/
  rev=$(git -C "$WEB" log -1 --format='%h %ad %s' --date=format:'%Y-%m-%d %H:%M' 2>/dev/null || echo unknown)
  echo "$rev" > "$DEST/BUILD.txt"
  echo "snapshot: $DEST"
  echo "port-web: $rev"
fi

docker rm -f "$NAME" >/dev/null 2>&1 || true
docker run -d --name "$NAME" -p 127.0.0.1:"$PORT":8000 -v "$DEST":/www:ro -w /www "$IMG" \
  python3 -m http.server 8000 >/dev/null
echo "playing at http://localhost:$PORT/   (stop: tools/eu_port/play.sh stop)"
[ -n "${NOOPEN:-}" ] || open "http://localhost:$PORT/" 2>/dev/null || true
