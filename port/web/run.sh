#!/bin/bash
# Browser build helper. Everything runs in the conker-emsdk container; nothing is installed on the host.
#   port/web/run.sh image          build the toolchain image (pinned emsdk)
#   port/web/run.sh build [target] make -C port [target]   (default: all = demo + game)
#   port/web/run.sh census         clang/wasm32 compile census of conker/src_eu (port/build/census/)
#   port/web/run.sh serve [port]   serve port/build/web on http://localhost:PORT (default 8064), detached
#   port/web/run.sh stop           stop the server container
#   port/web/run.sh sh             interactive shell in the toolchain container
set -euo pipefail
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
IMG=${CONKER_EMSDK_IMAGE:-conker-emsdk}
SRV=${CONKER_WEB_SERVER:-conker-web-serve}
run() { docker run --rm -v "$ROOT":/src -w /src "$IMG" "$@"; }
case ${1:-} in
image) docker build -t "$IMG" "$ROOT/port/web";;
build) shift; run make -C port -j"$(sysctl -n hw.ncpu 2>/dev/null || nproc)" "$@";;
census) run python3 port/tools/census.py;;
serve)
  p=${2:-8064}
  docker rm -f "$SRV" >/dev/null 2>&1 || true
  docker run -d --name "$SRV" -p 127.0.0.1:"$p":8000 -v "$ROOT/port/build/web":/www:ro -w /www "$IMG" \
    python3 -m http.server 8000 >/dev/null
  echo "serving port/build/web at http://localhost:$p/  (stop: port/web/run.sh stop)";;
stop) docker rm -f "$SRV" >/dev/null && echo stopped;;
sh) docker run --rm -it -v "$ROOT":/src -w /src "$IMG" bash;;
*) sed -n '2,8p' "$0"; exit 2;;
esac
