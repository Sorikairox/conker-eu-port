#!/bin/bash
# P105 (copy of p99/cam.sh, prints eye.y too): node boot of a build dir with the camera watch; prints eye/at + pitch every N calls.
#   cam.sh NAME SECONDS [BUILD_DIR=port/build/web]   (env CAMEVERY=20, PADSCRIPT, PORT_*)
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
eval "$(tools/eu_port/wt.sh env web)"
N=$1; S=$2; B=${3:-port/build/web}; L=port_work/p105/cam_$N.log
: ${PADSCRIPT:="15000:0:0:80; 22000:0:0:0; 23500:0:0:80; 31000:0:0:0"}
envs=(-e "PADSCRIPT=$PADSCRIPT" -e PORT_CAMWATCH=1 -e PORT_CAMEVERY=${CAMEVERY:-20} -e PORT_P88POS=${P88POS:-40} -e PORT_P61CHECK=${P61:-40})
for v in $(compgen -e | grep "^PORT_" || true); do envs+=(-e "$v=${!v}"); done
docker run --rm --name p105-cam-$N "${envs[@]}" -v "$PWD/port":/src/port:ro -v "$PWD/$B":/bld:ro -v "$PWD/conker":/src/conker:ro \
  -v "$PWD/baserom.eu.z64":/rom/baserom.eu.z64:ro -w /src conker-emsdk \
  timeout $((S + 110)) node port/tools/node_run.js /bld/conker.js createConker "$S" /rom/baserom.eu.z64 > "$L" 2>&1
echo "rc=$? $L last $(grep -o 'frame [0-9]*' $L | sort -k2 -n | tail -1)"
python3 - "$L" <<'PY'
import re,sys,math
out=[]
for ln in open(sys.argv[1]):
    m=re.search(r'call (\d+) frame (\d+):.*?pos (\S+) (\S+) (\S+) \|.*? at (\S+) (\S+) (\S+) eye (\S+) (\S+) (\S+)',ln)
    if m and int(m.group(2))>=int(__import__('os').environ.get('FMIN','690')):
        px,py,pz,ax,ay,az,ex,ey,ez=map(float,m.groups()[2:])
        h=math.hypot(ax-ex,az-ez); out.append(f"f{m.group(2)} y{py:.0f} at.y {ay:.1f} eye.y {ey:.1f} pitch {math.degrees(math.atan2(ay-ey,h)):.1f}")
    elif 'sound start' in ln or 'RuntimeError' in ln: out.append(ln.strip()[:120])
print(' | '.join(out))
PY
