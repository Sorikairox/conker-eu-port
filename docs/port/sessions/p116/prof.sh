#!/bin/bash
# P116: node boot under `node --prof` (v8 tick log written as it runs), to locate a hang. prof.sh NAME SECONDS
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
N=$1; S=$2; B=port/build/web; O=port_work/p116/prof_$N; mkdir -p $O; rm -f $O/*
: ${PADSCRIPT:="1000:0:0:0"}
envs=(-e "PADSCRIPT=$PADSCRIPT")
for v in $(compgen -e | grep "^PORT_" || true); do envs+=(-e "$v=${!v}"); done
docker run --rm --name p116-prof-$N "${envs[@]}" -v "$PWD/port":/src/port:ro -v "$PWD/$B":/bld:ro \
  -v "$PWD/baserom.eu.z64":/rom/baserom.eu.z64:ro -v "$PWD/$O":/out -w /out conker-emsdk \
  bash -c "timeout -s INT $S node --prof /src/port/tools/node_run.js /bld/conker.js createConker 600 /rom/baserom.eu.z64 > /out/run.log 2>&1; node --prof-process /out/isolate*.log > /out/prof.txt 2>/dev/null; echo done"
echo "rc=$?"; grep -A25 'Bottom up' $O/prof.txt | head -40
