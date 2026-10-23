#!/bin/bash
# P113 (from p110): node boot of a build dir (default port/build/web); log port_work/p113/NAME.log.  nb.sh NAME SECONDS [BUILD_DIR]
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
N=$1; S=$2; B=${3:-port/build/web}; L=port_work/p113/$N.log
: ${PADSCRIPT:="15000:0:0:80; 22000:0:0:0; 23500:0:0:80; 31000:0:0:0"}
envs=(-e "PADSCRIPT=$PADSCRIPT")
for v in $(compgen -e | grep "^PORT_" || true); do envs+=(-e "$v=${!v}"); done
docker run --rm --name p113-node-$N "${envs[@]}" -v "$PWD/port":/src/port:ro -v "$PWD/$B":/bld:ro -v "$PWD/conker":/src/conker:ro \
  -v "$PWD/baserom.eu.z64":/rom/baserom.eu.z64:ro -w /src conker-emsdk \
  timeout $((S + 110)) node port/tools/node_run.js /bld/conker.js createConker "$S" /rom/baserom.eu.z64 > "$L" 2>&1
echo "rc=$? $L last $(grep -o 'frame [0-9]*' $L | sort -k2 -n | tail -1) lines $(wc -l < $L)"
