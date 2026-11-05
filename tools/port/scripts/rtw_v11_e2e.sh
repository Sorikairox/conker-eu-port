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
#   replay  files to the game (fileInputs 1 .ckrec, rtw_file_buffer / rtw_file_ready, rtw_request_file, option 115): with
#           the Input recorder on, NEW GAME + hold L to the level's autosave, "Save recording" (.ckrec in Saved files,
#           fetched); the customisation settings' Tools -> "Replay a recording" opens the host's file prompt -> the
#           recording is kept; reload: it replays from power-on at 50 Hz, every checkpoint / digest IDENTICAL (same
#           build: H / S too), paused at its end; the replayed saves never reach the host (save generation 0, the
#           module's EEPROM written). Then Saved files -> "Open in game" keeps it again; option 115 off: refused.
#   optsync rtw_option_changed (P382: always; options rule): the customisation settings (Menu button on the title) turn
#           Full-resolution on (each player's own, not declared: the settings record keeps it, the host is not told),
#           Widescreen on (P383: inGame, 1 call) and the music to 90 % (inGame: 2 calls, the host stores both but its menu
#           does not show them; the record keeps nothing of them); the host's menu shows only 1 108 117 118 119; after a
#           reload all are back (music and Widescreen from the host). Skip intro (a start-up option) turned off in-game:
#           told, the host's menu shows it off, kept after a reload.
#   (P382: options 113 / 114 / 115 are no longer in the host's menu: the runs set them as a settings row does, gameopt.)
set -uo pipefail
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:?usage: rtw_v11_e2e.sh OUTDIR [ROM] [RUN ...]}; ROM=${2:-baserom.eu.z64}; shift; shift 2>/dev/null || true
RUNS=${*:-rstick wheel replay optsync}
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
pad:-0.3:0.3,wait:400,expect:cam.0:-16,expect:cam.1:-16,gameopt:113:0,pad:0.6:0,wait:400,expect:cam.0:80,expect:opts.113:0,\
gameopt:113:1,gameopt:15:0,wait:300,pad:0.6:0,wait:400,expect:cam.0:0,pad:off"
WHEELMENU="open,frame:900,press:Enter,wait:3000,press:Enter,wait:4000,press:Digit6,waitfor:menu.open:true,expect:menu.sel:0,\
wheel:100,wait:300,expect:menu.sel:1,wheel:250,wait:300,expect:menu.sel:3,wheel:-150,wait:300,expect:menu.sel:2,press:KeyC,waitfor:menu.open:false"
# (no profile: headless Chrome with a persistent profile refused the host's pointer lock)
WHEELPHOTO="open,frame:900,press:Enter,wait:3000,press:Enter,wait:4000,press:KeyX,wait:16000,down:KeyA,wait:4500,up:KeyA,\
waitfor:saveicon.showing:true:40000,dismiss,wait:6000,press:Digit1,waitfor:photoinfo.state:2,wait:800,expect:photoinfo.fov:60.6,\
click,wheel:300,wait:500,expect:photoinfo.fov:80.659,shot:zoomed,wheel:-600,wait:500,expect:photoinfo.fov:45.53,\
unlock,gameopt:114:0,click,wheel:300,wait:500,expect:photoinfo.fov:45.53,expect:opts.114:0"
REPLAY="open,frame:300,press:Enter,wait:3000,press:Enter,wait:4000,press:KeyX,wait:16000,down:KeyA,wait:4500,up:KeyA,\
waitfor:saveicon.showing:true:40000,dismiss,wait:3000,press:Digit5,wait:2500,fetchfile:conker-rec,hostsave,\
press:Digit6,waitfor:menu.open:true,press:ArrowUp,press:ArrowUp,expect:menu.item:Tools,press:KeyX,expect:menu.item:Replay a recording,\
press:KeyX,askfile:last,waitfor:replay.pending:retrowser,shot:pending,press:KeyC,press:KeyC,\
reload,open,frame:100,expect:replay.state:running,expect:replay.sameBuild:true,shot:replaying,waitfor:replay.ended:true:150000,\
expect:replay.state:identical,expect:replay.mismatches:0,expect:replay.saveGeneration:0,expect:replay.eepromNonzero:>0,shot:ended,hostsave,\
openingame:conker-rec,waitfor:replay.pending:retrowser,gameopt:115:0,openingame:conker-rec,waitfor:replay.refused:1,grep:replay"
OPTSYNC="open,frame:900,press:Enter,wait:3000,press:Enter,wait:4000,press:Digit6,waitfor:menu.open:true,\
press:ArrowDown,press:KeyX,expect:menu.page:picture,press:KeyX,wait:800,expect:opts.102:1,press:ArrowDown,press:KeyX,wait:800,expect:opts.103:1,press:KeyC,\
press:ArrowDown:4,press:KeyX,expect:menu.page:sound,press:ArrowDown,press:ArrowLeft:2,expect:opts.9:90,press:KeyC,press:KeyC,waitfor:menu.open:false,\
expect:optsync.told:3,expect:optsync.refused:0,expect:hoststored.102:1,expect:hoststored.103:undefined,expect:hoststored.9:90,expect:menu.settings.chosen.102:undefined,\
expect:menu.settings.chosen.103:1,expect:menu.settings.chosen.9:undefined,expect:hostmenu.ids:1-108-117-118-119,expect:hostmenu.9:undefined,expect:hostmenu.102:undefined,\
reload,open,frame:300,expect:opts.102:1,expect:opts.103:1,expect:opts.9:90,expect:optsync.told:0,expect:menu.settings.chosen.9:undefined,\
press:Digit6,waitfor:menu.open:true,press:ArrowDown:3,expect:menu.page:main,expect:menu.item:Gameplay,press:KeyX,press:ArrowDown,expect:menu.item:Skip intro,\
press:KeyX,wait:500,expect:opts.1:0,press:KeyC,press:KeyC,waitfor:menu.open:false,expect:optsync.told:1,expect:hoststored.1:0,expect:hostmenu.1:0,\
reload,open,frame:300,expect:opts.1:0,expect:opts.9:90,expect:opts.102:1,expect:opts.103:1"
fails=0
for r in $RUNS; do
  case $r in
    rstick) run rstick '{"1":1,"15":1}' "$RSTICK" || fails=$((fails + 1)) ;;
    wheel) run wheel_menu '{"1":1,"16":1}' "$WHEELMENU" || fails=$((fails + 1))
           run wheel_photo '{"1":1,"16":1}' "$WHEELPHOTO" noprofile || fails=$((fails + 1)) ;;
    optsync) run optsync '{"1":1,"16":1}' "$OPTSYNC" || fails=$((fails + 1)) ;;
    replay) run replay '{"1":1,"108":1}' "$REPLAY" || fails=$((fails + 1)) ;;
    *) echo "unknown run $r"; fails=$((fails + 1)) ;;
  esac
done
rm -rf "$OUT/profile"
[ $fails = 0 ] && echo "RTW 1.1 ALL PASS ($RUNS)" || { echo "RTW 1.1: $fails run(s) failed"; exit 1; }
