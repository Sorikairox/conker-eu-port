#!/bin/bash
# P375 offline play test (tools/port/scripts/offline_test.js): muted headless Chrome, Android phone emulation, one at a time.
#   tools/port/scripts/offline_test.sh local     a copy of port/build/web served locally: install, ROM picked, network
#                                               off (CDP offline + the server stopped), reload, boot, touch; then the
#                                               update A -> B (notice, Reload, A's cache deleted)
#   tools/port/scripts/offline_test.sh live      the same against https://conker-web-port.netlify.app (CDP offline only)
# Output: port_work/p375/<mode>/ (chrome.log, screenshots). The ROM is only read (the page's file input).
set -euo pipefail
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)"
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
MODE=${1:-local}; OUT=port_work/p375/$MODE; rm -rf "$OUT"; mkdir -p "$OUT"
ROM=$PWD/baserom.eu.z64
if [ "$MODE" = live ]; then
  exec node tools/port/scripts/offline_test.js https://conker-web-port.netlify.app/ "$ROM" "$OUT"
fi
SITE=$PWD/$OUT/site; mkdir -p "$SITE"
for f in index.html main.js net.js gmenu.js conker.js conker.wasm conker_netx.txt conker_netsyms.txt manifest.webmanifest icon.svg icon-192.png icon-512.png sw.js; do
  cp port/build/web/$f "$SITE/"; done
echo "local test build A" > "$SITE/BUILD.txt"
NAME=conker-offline-test-$$; PORT=$((8100 + $$ % 800))
docker run -d --name "$NAME" -p 127.0.0.1:$PORT:8000 -v "$SITE":/www/app:ro -w /www conker-emsdk python3 -m http.server 8000 >/dev/null
trap 'docker rm -f "$NAME" >/dev/null 2>&1 || true' EXIT
sleep 1.5
OFFLINE_CMD="docker stop -t 0 $NAME >/dev/null" ONLINE_CMD="docker start $NAME >/dev/null && sleep 1.5" \
UPDATE_CMD="echo '<!-- offline-test-build-B -->' >> '$SITE/index.html' && python3 port/tools/sw_stamp.py port/web/sw.js '$SITE'" \
  node tools/port/scripts/offline_test.js "http://localhost:$PORT/app/" "$ROM" "$OUT" update
