#!/bin/bash
# P353: does the game depend on where the n64_rdram mirror lands in wasm memory? (docs/port/MEMORY.md "Layout
# independence"). Builds the game with the mirror moved by RDRAM_SHIFT (port/Makefile; nothing else moves), runs the
# same scripted route on each build with ?layhash (pc_nethash.c: per-retrace hash of the game state with mirror
# pointers taken as N64 addresses) and compares the hashes and a 640x480 canvas shot of the last retrace.
#   layout_cmp.sh build SHIFT...         build each shift into port_work/layout/s_<SHIFT> (then rebuild the normal build)
#   layout_cmp.sh run ROUTE SHIFT...     run ROUTE on each built shift and compare everything with the first shift
#   layout_cmp.sh check                  the short regression: build 0x0 and 0x123000, run route "menu", exit 1 on a
#                                        difference (~4 min; tools/eu_port/check.sh runs it with --layout)
# Routes: menu (title menu after skipintro, retrace 450), run29 (?warp=29, a walk with camera turns, retrace 800),
#         mp (4-player Bunker from the title menu, tools/port/scripts/netmp_pads.py, retrace 7250, ~5 min per shift)
#         short (title menu at retrace 300, for `check`)
# Env: OUT=DIR (default port_work/layout/<route>), STOPAT=N stop at retrace N instead, DUMP=1 also dumps the hashed memory at the stop
#      (tools/port/layout_diff.py compares two dumps), PROBE_NOWAIT / PROBE_PORT as for cshot.sh / audprobe.sh.
# Outputs: OUT/<route>_s<SHIFT>.{png,log,out}; prints the first differing retrace (R = mirrors, G = other globals,
# S = thread stacks) and the pixel diff for each shift.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
eval "$(tools/eu_port/wt.sh env "$(basename "$PWD")")"
L=port_work/layout
cmd=${1:-}; shift || true
build_shifts() {
  for s in "$@"; do
    port/web/run.sh build RDRAM_SHIFT="$s" > $L/build_s$s.log 2>&1 || { echo "build RDRAM_SHIFT=$s failed: $L/build_s$s.log"; return 1; }
    rm -rf $L/s_$s; cp -R port/build/web $L/s_$s; cp port/build/conker.map $L/s_$s/conker.map
    echo "built s_$s: n64_rdram $(grep -m1 ' n64_rdram$' port/build/conker.map | awk '{print $1}')"
  done
  port/web/run.sh build > $L/build_normal.log 2>&1 || { echo "normal rebuild failed: $L/build_normal.log"; return 1; }
}
route() {  # route NAME -> sets STOP SECS PADF Q
  case $1 in
  menu)  STOP=450; SECS=70; PADF='200:1000:0:0,215:0:0:0'; Q='&opt=skipintro:1';;
  short) STOP=300; SECS=50; PADF='200:1000:0:0,215:0:0:0'; Q='&opt=skipintro:1';;
  run29) STOP=800; SECS=50; PADF='150:0:0:70,400:0002:40:60,700:0:-50:50'; Q='&warp=29';;
  mp)    STOP=7250; SECS=300; eval "$(python3 tools/port/scripts/netmp_pads.py 7000 20)"
         PADF=$PADF0; Q="&padf1=$PADF1&padf2=$PADF2&padf3=$PADF3";;
  *) echo "unknown route $1"; return 1;;
  esac
  [ -n "${STOPAT:-}" ] && SECS=$(( SECS * STOPAT / STOP + 25 )) && STOP=$STOPAT
  return 0
}
run_route() {
  local r=$1; shift; route "$r" || return 1
  local O=${OUT:-$L/$r}; mkdir -p "$O"
  for s in "$@"; do
    [ -d $L/s_$s ] || { echo "no build $L/s_$s (layout_cmp.sh build $s)"; return 1; }
    env WEB=$PWD/$L/s_$s CANVAS=640x480 PADF=$PADF ${DUMP:+PROBE_DUMP=$PWD/$O/${r}_s$s.dump} \
      tools/port/scripts/cshot.sh "$O/${r}_s$s.png" $STOP $SECS "$Q&layhash=1"
  done
  local a=$1 bad=0; shift
  for s in "$@"; do
    local line
    line=$(python3 - "$O/${r}_s$a.log" "$O/${r}_s$s.log" <<'EOF'
import re, sys
def rd(p):
    h = {}
    for l in open(p, errors='replace'):
        m = re.match(r'^\[layhash\] (\d+) (\S+) (\S+) (\S+)', l)
        if m: h[int(m[1])] = m.groups()[1:]
    return h
A, B = rd(sys.argv[1]), rd(sys.argv[2]); c = sorted(set(A) & set(B))
d = [f for f in c if A[f] != B[f]]
if not c: print('NO HASHES'); sys.exit()
what = lambda f: ''.join(k for k, x, y in zip('RGS', A[f], B[f]) if x != y)
print(f"retraces {c[0]}..{c[-1]}: " + ('IDENTICAL' if not d else f"{len(d)} differ, first {d[0]} ({what(d[0])})"))
EOF
)
    local px; px=$(python3 tools/port/scripts/pngtool.py diff "$O/${r}_s$a.png" "$O/${r}_s$s.png" | sed 's/.*: 640x480, //')
    echo "$r s_$a vs s_$s: hash $line; picture $px"
    case "$line$px" in *IDENTICAL*identical*) ;; *) bad=1;; esac
  done
  return $bad
}
case $cmd in
build) mkdir -p $L; build_shifts "$@";;
run) r=$1; shift; run_route "$r" "$@";;
check) mkdir -p $L; build_shifts 0x0 0x123000 && run_route short 0x0 0x123000 && echo "LAYOUT OK" || { echo "LAYOUT CHANGED"; exit 1; };;
*) sed -n '2,17p' "$0"; exit 2;;
esac
