#!/bin/bash
# P358: photo mode pose / outfit shots. Warps to LEVEL, enters photo mode after retrace AT (?photoat) and, for each
# LOOK (JavaScript run in the page, e.g. 'P({anim:0x42})' = __photo.lookPage: the panel's own look), resets the look, applies it,
# saves the photo PNG at twice the canvas (DIR/NN.png, NN = 01, 02, ...). Look 0 (DIR/00.png) is the game's own look.
# Before the first look it prints the game's reports (window.__photo.lookDump()).
#   tools/port/scripts/photolook.sh NAME LEVEL AT 'LOOK1' 'LOOK2' ...      (env EXTRA: more query, e.g. '&photomove=..')
# Helpers in the page: P(patch) = __photo.lookPage, I(w, i) = __photo.lookInfo, L(k, i, v) = __photo.lookSet (raw; the panel
# overrides it at its next push). Output: port_work/p358/NAME/
# (NN.png, chrome.log); the evals' results are in port_work/p327/p358_NAME.out. One headless Chrome at a time.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
NAME=$1; LEVEL=$2; AT=$3; shift 3
D=$PWD/port_work/p358/$NAME; rm -rf "$D"; mkdir -p "$D"
T0=$(( 9000 + AT * 30 ))   # ?warp boots in ~7 s, then about 33 ms per retrace at det=2
H="(window.L=(k,i,v)=>__photo.lookSet(k,i,v), window.I=(w,i)=>__photo.lookInfo(w,i), window.P=(o)=>__photo.lookPage(o), 'helpers')"   # no ';' (it separates steps)
# env CAM: JavaScript run once before the first picture to place the photo camera, e.g. 'C(900,0,0,0,0)' then
# 'C(0,0,0,180,-10,0.6)' (__photo.move: forward, right, up, yaw, pitch, zoom factor); comma-separated, no ';'
S="$((T0 - 400)):eval:$H; $((T0 - 300)):eval:__photo.lookDump(); $T0:eval:(window.C=(a,b,c,d,e,f)=>__photo.move(a,b,c,d,e,f), ${CAM:-0}); $((T0 + 300)):eval:__photo.capture(); $((T0 + 1000)):png:$D/00.png"
t=$((T0 + 1200)); n=0
for look in "$@"; do
  n=$((n + 1)); f=$(printf %02d $n)
  S="$S; $t:eval:(P(null), $look, 'look $f'); $((t + 450)):eval:__photo.capture(); $((t + 1150)):png:$D/$f.png; $((t + 1200)):eval:__photo.lookState()"
  t=$((t + 1400))
done
SECS=$(( t / 1000 + 2 ))
STEPS="$S" SHOTS=$((T0 - 600)) tools/port/scripts/warp.sh "p358_$NAME" "$SECS" "$LEVEL" "&opt=photomode:1&photoat=$AT${EXTRA:-}" | tail -2
cp port_work/p327/p358_$NAME/chrome.log "$D/chrome.log"
grep -a '^eval: ' port_work/p327/p358_$NAME.out | grep -v '^eval: {}$\|^eval: undefined$' | cut -c1-2000
grep -a -c 'RuntimeError\|Aborted' "$D/chrome.log" | sed 's/^/traps: /'
ls "$D" | grep -c png | sed 's/^/pngs: /'
