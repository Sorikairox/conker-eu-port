#!/bin/bash
# P377: end-to-end test of the retrowser build's overlays (customisation settings, autosave icon, hold-L ring, photo mode
# menus) in the real retrowser host, buttons only (the host's default keys: arrows = stick, X = A, C = B, Enter = Start,
# A = L, T / G / F / H = D-pad, 1 = Photo mode, 6 = Menu), one muted headless Chrome at a time (rtw_e2e.mjs).
#   tools/port/scripts/rtw_overlay_e2e.sh OUTDIR [ROM]      (ROM default baserom.eu.z64, read only by the host's file input)
# Needs a built dist (tools/eu_port/build_rtw.sh) and ~/Code/retrowser's built dist (served in-process: RTW_SERVE, nothing
# is left running). Both runs start from a fresh browser profile (OUTDIR/profile): skip intro and photo mode on.
#   1 menus: the title's save slot page -> its CUSTOMISATION row -> every page (Picture: Widescreen on, Sound: music 90 %,
#     Saves: export), back to the title; reload: both kept. P382 (options rule): Widescreen is each player's own (not in
#     the manifest): the settings record keeps it; music is inGame: the host stores it (rtw_option_changed) and hands it
#     back at the start, the record keeps nothing; the host's menu shows only the start-up options (1 108 117 118 119)
#     and still changes them (Skip intro off).
#   2 play: holding Photo opens the menu (paused), a Photo tap closes it; NEW GAME, hold L over the opening (ring), the
#     autosave icon when the level saves; photo mode: Menu = the Pose & Outfit panel, D-pad / A / B change the animation
#     (list page) and the model, hold Menu hides / shows the menus, holding Photo focuses the panel, A saves the PNG
#     (fetched: no menus in it); the pause menu's CUSTOMISATION row opens the menu over the pause menu.
set -uo pipefail
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:?usage: rtw_overlay_e2e.sh OUTDIR [ROM]}; ROM=${2:-baserom.eu.z64}
PORT=${RTW_SERVE:-8788}
run() {   # NAME ACTIONS
  rm -rf "$OUT/profile"
  local opts='{"1":1,"16":1}'
  [ -n "${RTW_OFF:-}" ] && opts='{"1":1,"16":1,"109":0,"110":0,"111":0,"112":0,"116":0}'   # P382: no longer declared: ignored
  RTW_OPTIONS=$opts RTW_SERVE=$PORT RTW_PROFILE=$PWD/$OUT/profile RTW_TIMEOUT=600000 \
    node tools/port/scripts/rtw_e2e.mjs "$OUT/$1" - "$ROM" "$2" > "$OUT/$1.log" 2>&1
  local rc=$?
  grep -E "expect|waitfor|fetched|ERROR|failure|done|saved files" "$OUT/$1.log" | cut -c1-200
  echo "[$1] $([ $rc = 0 ] && echo PASS || echo "FAIL (rc $rc, $OUT/$1.log)")"
  return $rc
}
mkdir -p "$OUT"
TITLE='open,frame:900,press:Enter,wait:3000,press:Enter,wait:4000'
MENUS="$TITLE,shot:slot_row,key:ArrowDown:250,wait:600,press:KeyX,waitfor:menu.open:true,expect:menu.from:title,wait:400,shot:menu_from_title,\
press:ArrowDown,press:KeyX,expect:menu.page:picture,press:KeyX,wait:800,expect:opts.102:1,shot:pg_picture_ws,press:KeyC,\
press:ArrowDown,press:KeyX,expect:menu.page:hud,shot:pg_hud,press:KeyC,\
press:ArrowDown,press:KeyX,expect:menu.page:gameplay,shot:pg_gameplay,press:KeyC,\
press:ArrowDown,press:KeyX,expect:menu.page:controls,shot:pg_controls,press:KeyC,\
press:ArrowDown,press:KeyX,expect:menu.page:sound,press:ArrowDown,press:ArrowLeft:2,expect:opts.9:90,shot:pg_sound,press:KeyC,\
press:ArrowDown,press:KeyX,expect:menu.page:saves,press:KeyX,wait:300,shot:pg_saves,press:KeyC,\
press:ArrowDown,press:KeyX,expect:menu.page:online,shot:pg_online,press:KeyC,\
press:ArrowDown,press:ArrowDown,press:KeyX,expect:menu.page:tools,shot:pg_tools,press:KeyC,\
press:ArrowDown,expect:menu.item:Back to title,press:KeyX,wait:2000,expect:menu.open:false,shot:closed,files,\
reload,open,frame:300,expect:opts.102:1,expect:opts.9:90,shot:reload_kept,expect:menu.settings.chosen.102:1,expect:menu.settings.chosen.9:undefined,\
expect:hoststored.9:90,expect:hoststored.102:undefined,expect:hostmenu.ids:1-108-117-118-119,hostopt:1:0,wait:500,expect:opts.1:0,expect:hoststored.1:0,ov"
PLAY="open,frame:900,key:Digit1:800,waitfor:menu.open:true,expect:menu.paused:true,shot:menu_by_hold,press:Digit1,waitfor:menu.open:false,\
press:Enter,wait:3000,press:Enter,wait:4000,press:KeyX,wait:16000,down:KeyA,wait:1500,shot:ring,expect:ring.progress:>0.2,wait:3000,up:KeyA,\
waitfor:saveicon.showing:true:40000,dismiss,shot:saveicon,wait:6000,shot:level,\
press:Digit1,waitfor:photo.shown:true,wait:800,shot:photo_hud,press:Digit6,wait:300,expect:photo.focus:true,shot:panel_focus,\
press:KeyH,wait:600,expect:photo.look.anim:0,shot:pose_next_anim,press:KeyX,wait:400,expect:photo.page:anims,press:KeyG:3,wait:300,shot:pose_list,press:KeyX,wait:800,expect:photo.look.anim:3,shot:pose_list_pick,\
press:KeyG:4,wait:200,expect:photo.item:Model,press:KeyH,wait:1500,expect:photo.look.model:1,shot:outfit_model,\
key:Digit6:800,wait:300,expect:photo.hidden:true,shot:menus_hidden,key:Digit6:800,wait:300,expect:photo.hidden:false,\
press:KeyC,wait:300,expect:photo.focus:false,key:Digit1:800,wait:300,expect:photo.focus:true,press:KeyC,wait:300,press:KeyX,wait:2500,shot:photo_saved,\
press:Enter,waitfor:photo.shown:false,wait:1000,press:Enter,wait:2500,key:ArrowDown:250,wait:500,shot:pause_row,press:KeyX,waitfor:menu.open:true,\
expect:menu.from:pause,wait:500,shot:menu_from_pause,press:KeyC,wait:800,expect:menu.open:false,press:Enter,wait:1000,fetchfile:conker-photo,ov,state"
#   3 rows (P382): stored host values for the removed options 110 / 116 / 109 / 111 / 112 change nothing (the menu opens,
#     the features stay on); this build's own rows: HUD -> Hold-L skip ring off, Controls -> Analog right stick off, Tools
#     -> Photo mode menus off; the host stores 113 (inGame) only, the record 111 / 112; reload: all three kept.
ROWS="$TITLE,expect:menu.rows:1,expect:opts.109:1,expect:opts.111:1,expect:opts.112:1,press:Digit6,waitfor:menu.open:true,\
press:ArrowDown:2,expect:menu.item:HUD and information,press:KeyX,press:ArrowDown:5,expect:menu.item:Hold-L skip ring,press:KeyX,wait:300,expect:opts.111:0,press:KeyC,\
press:ArrowDown:2,expect:menu.item:Controls,press:KeyX,press:ArrowDown:7,expect:menu.item:Analog right stick (camera),press:KeyX,wait:300,expect:opts.113:0,shot:pg_controls_rows,press:KeyC,\
press:ArrowDown:5,expect:menu.item:Tools,press:KeyX,press:ArrowDown:3,expect:menu.item:Photo mode menus (Pose & Outfit),press:KeyX,wait:300,expect:opts.112:0,shot:pg_tools_rows,press:KeyC,\
press:KeyC,waitfor:menu.open:false,wait:800,expect:hoststored.113:0,expect:optsync.told:1,expect:menu.settings.chosen.111:0,\
expect:menu.settings.chosen.112:0,expect:menu.settings.chosen.113:undefined,\
reload,open,frame:300,expect:opts.111:0,expect:opts.112:0,expect:opts.113:0,expect:opts.110:undefined,expect:opts.116:undefined,ov"
fails=0
run menus "$MENUS" || fails=$((fails + 1))
run play "$PLAY" || fails=$((fails + 1))
RTW_OFF=1 run rows "$ROWS" || fails=$((fails + 1))
rm -rf "$OUT/profile"
[ $fails = 0 ] && echo "RTW OVERLAYS ALL PASS" || { echo "RTW OVERLAYS: $fails run(s) failed"; exit 1; }
