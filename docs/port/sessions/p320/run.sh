#!/bin/bash
# P320 (copy of p273/run.sh): det=2 muted new game with an overridable pad script.  run.sh DIR SECS [EXTRA_QUERY]
# PADF=... overrides the pad script (frame:buttons hex:sx:sy,...); default = p273 (Start at 3386 and 4458).
# Waits for any other headless Chrome (P272 etc.) before starting: one Chrome run at a time.
R=$(cd "$(dirname "$0")/../../../.." && pwd); cd "$R" || exit 1
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
while [ "$(ps -axo command | grep -v grep | grep -c 'headless=new')" -gt 0 ]; do sleep 20; done
D=$1; T=${2:-260}; mkdir -p "$D"
PADF=${PADF:-'3386:1000:0:0,3401:0:0:0,4458:1000:0:0,4473:0:0:0'}
SHOTS="${SHOTS:-200000 220000 240000 250000}"
S=""; for t in $SHOTS; do S="$S${S:+; }$t:shot:$D/s_${t}ms.png"; done
PROBE_LOG=$D/chrome.log PROBE_ANGLE=metal PROBE_NOAUDIO=1 PROBE_SAMPLES=0 PROBE_STEPS="$S" \
  port/web/audprobe.sh "app=game&heapwatch=1&p78null=1&p103boot=1&p88scene=8&p123fade=1&padf=$PADF&det=2&p174ev=1${3:-}" $T
