#!/bin/bash
# P165 (from P152) (from p113): node boot of a build dir (default port/build/web); log port_work/p165/NAME.log.  nb.sh NAME SECONDS [BUILD_DIR]
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
N=$1; S=$2; B=${3:-port/build/web}; L=port_work/p165/$N.log
# P149: frame-based walk (PORT_PADF, retraces) replaces the wall-clock PADSCRIPT (15/22/23.5/31 s ~ retraces 775/1095/1160/1550)
: ${PORT_PADF:="775:0:0:80,1095:0:0:0,1160:0:0:80,1550:0:0:0"}; export PORT_PADF
envs=(); [ -n "${PADSCRIPT:-}" ] && envs=(-e "PADSCRIPT=$PADSCRIPT")
for v in $(compgen -e | grep "^PORT_" || true); do envs+=(-e "$v=${!v}"); done
docker run --rm --name p165-node-$N "${envs[@]}" -v "$PWD/port":/src/port:ro -v "$PWD/$B":/bld:ro -v "$PWD/conker":/src/conker:ro \
  -v "$PWD/baserom.eu.z64":/rom/baserom.eu.z64:ro -w /src conker-emsdk \
  timeout $((S + 110)) node port/tools/node_run.js /bld/conker.js createConker "$S" /rom/baserom.eu.z64 > "$L" 2>&1
echo "rc=$? $L last $(grep -o 'frame [0-9]*' $L | sort -k2 -n | tail -1) lines $(wc -l < $L)"
