#!/bin/bash
# P376 retrowser.app build of the port (spec: ~/Code/retrowser spec/retrowser-v1.md). Separate from the page build:
# `make -C port rtw` (in the conker-emsdk container) writes port/build/rtw/dist and never touches port/build/web.
#   tools/eu_port/build_rtw.sh [--rom FILE]
#     builds port/build/rtw/dist (conker.js, conker.wasm, conker_netx.txt, retrowser.json), writes the sha256 / size of
#     every file into retrowser.json (retrowser tools/rtw-hash.ts) and checks the directory (tools/rtw-check.ts; with
#     --rom also the local scan for runs of that ROM's bytes in every build file; nothing is copied or sent).
# Env: RETROWSER_DIR (default ~/Code/retrowser). Publishing the output: tools/eu_port/rtw_dist_commit.sh.
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
RTW_REPO=${RETROWSER_DIR:-$HOME/Code/retrowser}
DIST=$ROOT/port/build/rtw/dist
rom=""
if [ "${1:-}" = --rom ]; then rom=${2:?--rom needs a file}; fi
"$ROOT/port/web/run.sh" build rtw 2>&1 | grep -E "error|warning: .*rtw|rtw link|conker\.(wasm|js)|Error" || true
[ -s "$DIST/conker.wasm" ] && [ "$DIST/conker.wasm" -nt "$ROOT/port/ultra/pc_rtw.c" ] || { echo "build_rtw: no fresh $DIST/conker.wasm"; exit 1; }
node "$RTW_REPO/tools/rtw-hash.ts" "$DIST"
if [ -n "$rom" ]; then node "$RTW_REPO/tools/rtw-check.ts" "$DIST" --rom "$rom"; else node "$RTW_REPO/tools/rtw-check.ts" "$DIST"; fi
(cd "$DIST" && shasum -a 256 retrowser.json conker.js conker.wasm conker_netx.txt)
