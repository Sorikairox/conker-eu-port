#!/bin/bash
# Headless boot run in node (read-only mounts of port/ and the ROM), compact summary.
#   port/web/boot.sh [SECONDS=10] [LOG]   env: GFXDEMO=1 etc. are passed through
set -uo pipefail
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
SEC=${1:-10}; LOG=${2:-$ROOT/port/build/boot.log}
envs=(); for v in GFXDEMO; do [ -n "${!v:-}" ] && envs+=(-e "$v=${!v}"); done
docker run --rm ${envs[@]+"${envs[@]}"} -v "$ROOT/port":/src/port:ro -v "$ROOT/conker":/src/conker:ro \
  -v "$ROOT/baserom.eu.z64":/rom/baserom.eu.z64:ro -w /src conker-emsdk \
  timeout $((SEC + 110)) node port/tools/node_run.js port/build/web/conker.js createConker "$SEC" /rom/baserom.eu.z64 > "$LOG" 2>&1
echo "rc=$? log=$LOG"
grep -E "PASS|FAIL|main loop|distinct asm stubs|null zone|\[sp\] tasks|\[gfx|\[seg|abort|RuntimeError|Aborted" "$LOG" | head -30
