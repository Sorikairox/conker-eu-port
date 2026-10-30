#!/bin/bash
# P360: screenshots of the whole page (layout, menu drawer, overlays) at a given window size, in headless Chrome
# (muted, one at a time). Each SHOT is MS:NAME[:EVAL]: at MS ms after load, optionally evaluate EVAL in the page, wait
# 600 ms, then save OUTDIR/NAME.png (Page.captureScreenshot = what the player sees, not just the canvas).
#   tools/port/scripts/pageshot.sh OUTDIR W,H SECS QUERY SHOT [SHOT ...]
# e.g. pageshot.sh port_work/p360 1280,720 40 'app=game&opt=skipintro:1' '25000:title' '27000:title_menu:drawerSet(true)'
# W,H = the page's viewport (CSS pixels). QUERY gets &mute=1&romurl=... from audprobe.sh. The page log goes to OUTDIR/pageshot_W,H.log.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
[ -n "${PROBE_NOWAIT:-}" ] || while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 10; done
OUT=$1; WIN=$2; T=$3; Q=$4; shift 4
case $OUT in /*) ;; *) OUT=$PWD/$OUT;; esac
mkdir -p "$OUT"
STEPS=""
for s in "$@"; do
  ms=${s%%:*}; rest=${s#*:}; name=${rest%%:*}; ev=""; [ "$rest" != "$name" ] && ev=${rest#*:}
  [ -n "$ev" ] && STEPS="$STEPS; $((ms - 600)):eval:$ev"
  STEPS="$STEPS; $ms:shot:$OUT/$name.png"
done
PROBE_WINDOW=$WIN PROBE_VIEWPORT=$WIN PROBE_LOG="$OUT/pageshot_$WIN.log" PROBE_ANGLE=${PROBE_ANGLE:-metal} PROBE_NOAUDIO=1 PROBE_SAMPLES=0 \
  PROBE_STEPS="${STEPS#; }" port/web/audprobe.sh "$Q" "$T" 2>&1 | grep -E 'screenshot|eval:|timeout|no DevTools' || true
grep -iE 'Aborted|RuntimeError' "$OUT/pageshot_$WIN.log" | head -3
