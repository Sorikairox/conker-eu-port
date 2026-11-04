#!/bin/bash
# P378: end-to-end test of the retrowser build's standard 1.1 features in the real retrowser host (rtw_e2e.mjs, one muted
# headless Chrome at a time, retrowser's built dist served in-process, nothing left running).
#   tools/port/scripts/rtw_v11_e2e.sh OUTDIR [ROM] [RUN ...]     (ROM default baserom.eu.z64, read only by the host's file
#                                                                input; RUN default: all runs below)
#   rstick  the right analog stick (rtw_rstick, option 113) from a fake standard gamepad: with Free camera on, the camera
#           stick the glue writes = main.js gamepadPad's (radial dead zone 0.2, rescaled, 80 counts): axis 0.6 -> 40,
#           full up (axis -1) -> cy 80 (y up), a diagonal -0.3 / 0.3 -> -16 / -16; option 113 off: the host's C bit -> 80 (v1);
#           Free camera off: no camera stick.
set -uo pipefail
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:?usage: rtw_v11_e2e.sh OUTDIR [ROM] [RUN ...]}; ROM=${2:-baserom.eu.z64}; shift; shift 2>/dev/null || true
RUNS=${*:-rstick}
PORT=${RTW_SERVE:-8788}
run() {   # NAME OPTIONS ACTIONS
  rm -rf "$OUT/profile"
  RTW_OPTIONS=$2 RTW_SERVE=$PORT RTW_PROFILE=$PWD/$OUT/profile RTW_TIMEOUT=${RTW_TIMEOUT:-600000} \
    node tools/port/scripts/rtw_e2e.mjs "$OUT/$1" - "$ROM" "$3" > "$OUT/$1.log" 2>&1
  local rc=$?
  grep -E "expect|waitfor|fetched|ERROR|failure|done|saved files|log /" "$OUT/$1.log" | cut -c1-220
  echo "[$1] $([ $rc = 0 ] && echo PASS || echo "FAIL (rc $rc, $OUT/$1.log)")"
  return $rc
}
mkdir -p "$OUT"
RSTICK="open,frame:300,pad:0.6:0,wait:400,expect:cam.0:40,expect:cam.1:0,pad:0:-1,wait:400,expect:cam.1:80,\
pad:-0.3:0.3,wait:400,expect:cam.0:-16,expect:cam.1:-16,hostopt:113:0,pad:0.6:0,wait:400,expect:cam.0:80,expect:opts.113:0,\
hostopt:113:1,hostopt:15:0,wait:300,pad:0.6:0,wait:400,expect:cam.0:0,pad:off"
fails=0
for r in $RUNS; do
  case $r in
    rstick) run rstick '{"1":1,"15":1}' "$RSTICK" || fails=$((fails + 1)) ;;
    *) echo "unknown run $r"; fails=$((fails + 1)) ;;
  esac
done
rm -rf "$OUT/profile"
[ $fails = 0 ] && echo "RTW 1.1 ALL PASS ($RUNS)" || { echo "RTW 1.1: $fails run(s) failed"; exit 1; }
