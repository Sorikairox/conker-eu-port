#!/bin/bash
# P378: end-to-end test of the retrowser build's standard 1.1 features in the real retrowser host (rtw_e2e.mjs, one muted
# headless Chrome at a time, retrowser's built dist served in-process, nothing left running).
#   tools/port/scripts/rtw_v11_e2e.sh OUTDIR [ROM] [RUN ...]     (ROM default baserom.eu.z64, read only by the host's file
#                                                                input; RUN default: all runs below)
#   rstick  the right analog stick (rtw_rstick, option 113) from a fake standard gamepad: with Free camera on, the camera
#           stick the glue writes = main.js gamepadPad's (radial dead zone 0.2, rescaled, 80 counts): axis 0.6 -> 40,
#           full up (axis -1) -> cy 80 (y up), a diagonal -0.3 / 0.3 -> -16 / -16; option 113 off: the host's C bit -> 80 (v1);
#           Free camera off: no camera stick.
#   wheel   the mouse wheel (rtw_wheel, option 114): the customisation settings (Menu button on the title) move one row
#           per notch (100, 250 -> rows 1, 3; -150 -> 2: the half notch is kept); in a level, photo mode's field of view
#           60.6 -> x 1.1^3 = 80.659 -> x 1.1^-6 = 45.53 (main.js's canvas wheel formula; the wheel reaches the game only
#           once the host captured the mouse: its "Click to use the mouse" cover swallows it before); option 114 off:
#           no zoom.
set -uo pipefail
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:?usage: rtw_v11_e2e.sh OUTDIR [ROM] [RUN ...]}; ROM=${2:-baserom.eu.z64}; shift; shift 2>/dev/null || true
RUNS=${*:-rstick wheel}
PORT=${RTW_SERVE:-8788}
run() {   # NAME OPTIONS ACTIONS [noprofile]
  rm -rf "$OUT/profile"
  local profile=$PWD/$OUT/profile
  [ "${4:-}" = noprofile ] && profile=   # a fresh incognito context (headless Chrome refused the pointer lock with a profile)
  RTW_OPTIONS=$2 RTW_SERVE=$PORT RTW_PROFILE=$profile RTW_TIMEOUT=${RTW_TIMEOUT:-600000} \
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
WHEELMENU="open,frame:900,press:Enter,wait:3000,press:Enter,wait:4000,press:Digit6,waitfor:menu.open:true,expect:menu.sel:0,\
wheel:100,wait:300,expect:menu.sel:1,wheel:250,wait:300,expect:menu.sel:3,wheel:-150,wait:300,expect:menu.sel:2,press:KeyC,waitfor:menu.open:false"
# (no profile: headless Chrome with a persistent profile refused the host's pointer lock)
WHEELPHOTO="open,frame:900,press:Enter,wait:3000,press:Enter,wait:4000,press:KeyX,wait:16000,down:KeyA,wait:4500,up:KeyA,\
waitfor:saveicon.showing:true:40000,dismiss,wait:6000,press:Digit1,waitfor:photoinfo.state:2,wait:800,expect:photoinfo.fov:60.6,\
click,wheel:300,wait:500,expect:photoinfo.fov:80.659,shot:zoomed,wheel:-600,wait:500,expect:photoinfo.fov:45.53,\
unlock,hostopt:114:0,click,wheel:300,wait:500,expect:photoinfo.fov:45.53,expect:opts.114:0"
fails=0
for r in $RUNS; do
  case $r in
    rstick) run rstick '{"1":1,"15":1}' "$RSTICK" || fails=$((fails + 1)) ;;
    wheel) run wheel_menu '{"1":1,"16":1}' "$WHEELMENU" || fails=$((fails + 1))
           run wheel_photo '{"1":1,"16":1}' "$WHEELPHOTO" noprofile || fails=$((fails + 1)) ;;
    *) echo "unknown run $r"; fails=$((fails + 1)) ;;
  esac
done
rm -rf "$OUT/profile"
[ $fails = 0 ] && echo "RTW 1.1 ALL PASS ($RUNS)" || { echo "RTW 1.1: $fails run(s) failed"; exit 1; }
