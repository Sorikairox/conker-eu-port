#!/bin/bash
# P161 node run with an alternative web dir: nrun.sh NAME WEBDIR SECONDS LOG   (PORT_* env passed through)
set -uo pipefail
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
ROOT=$HOME/conker-wt/web; NAME=$1; WEB=$2; SEC=$3; LOG=$4
envs=(); for v in PADSCRIPT $(compgen -e | grep "^PORT_" || true); do [ -n "${!v:-}" ] && envs+=(-e "$v=${!v}"); done
docker run --rm --name "$NAME" ${envs[@]+"${envs[@]}"} -v "$ROOT/port":/src/port:ro -v "$WEB":/src/port/build/web:ro -v "$ROOT/conker":/src/conker:ro \
  -v "$ROOT/baserom.eu.z64":/rom/baserom.eu.z64:ro -w /src conker-emsdk \
  timeout $((SEC + 110)) node --stack-trace-limit=60 port/tools/node_run.js port/build/web/conker.js createConker "$SEC" /rom/baserom.eu.z64 > "$LOG" 2>&1
echo "rc=$? log=$LOG"
