#!/bin/bash
# P367: evidence that the game-style menus play the game's menu sounds (gmenu.js GSound, port/ultra/pc_sfx.c) locally
# and nothing when muted. Muted headless Chrome (--mute-audio: nothing reaches the host's speakers) on level 0x29 with
# option nativemenu, driven by JS key events (no user activation: Fullscreen refuses = the error sound):
#   GMenu: Esc opens (choose), Right on Preset (change), Down x7 (move) to Fullscreen, Right (error: needs a key press),
#          Up x6 to Picture, Enter (choose), Esc (back), Esc (back: closes);
#   GPhoto: P starts photo mode, O focuses the panel (choose), Down x2 (move) to Frame, Right (error: no animation
#          chosen, the frame cannot move), Down x2 (move) to Model, Right (change: the next model), Esc (back:
#          unfocus), Esc leaves photo mode (no sound: the game's own sound comes back).
#   tools/port/scripts/menu_sound_probe.sh OUTDIR [local|muted|both]
# local = PROBE_PAGEVOL=1 (the page's volume 80 %, Chrome still muted): every sound logs "[gsound] play KIND 0xID (...
# roughness R)" and "[gsound] heard KIND: output peak P" (an AnalyserNode after the master gain, ?audprobe). muted = the
# page's ?mute=1: no "play" line, GSound.stats() counts them as muted. Online / replay silence: netpair.sh / e2e_replay.sh
# logs ("[gsound] silent (online session|replay)").
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/menu_sounds}; WHICH=${2:-both}
JK="window.JK = (c) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: c })), 120))"
STATS="console.log('stats ' + JSON.stringify(GSound.stats()))"
run() {   # $1 = local | muted
  local t=12000 S=()
  at() { t=$((t + $1)); }
  k() { S+=("raw:$t:eval:JK('$1')"); at "${2:-500}"; }
  S+=("raw:9000:eval:$JK")
  k Escape 900; S+=("$t:${1}_0_menu"); at 600
  k ArrowRight
  for _ in 1 2 3 4 5 6 7; do k ArrowDown; done
  k ArrowRight 700; S+=("$t:${1}_1_fullscreen_refused"); at 600
  for _ in 1 2 3 4 5 6; do k ArrowUp; done
  k Enter 900; S+=("$t:${1}_2_page"); at 600
  k Escape; k Escape 900
  k KeyP 2000; k KeyO 700; S+=("$t:${1}_3_photo_focus"); at 600
  k ArrowDown; k ArrowDown; k ArrowRight; k ArrowDown; k ArrowDown; k ArrowRight 1500; S+=("$t:${1}_4_photo_changed"); at 600
  k Escape; k Escape 1500
  S+=("raw:$t:eval:$STATS"); at 1500
  S+=("$t:${1}_5_end")
  local env=(); [ "$1" = local ] && env=(PROBE_PAGEVOL=1)
  env "${env[@]}" tools/port/scripts/pageshot.sh "$OUT" 1280,720 $((t / 1000 + 4)) "app=game&warp=29&opt=nativemenu:1,photomode:1" "${S[@]}" >/dev/null
  mv "$OUT/pageshot_1280,720.log" "$OUT/$1.log"
  echo "== $1: $(grep -c '\[gsound\] play' "$OUT/$1.log") sounds played, $(grep -c '\[gsound\] heard' "$OUT/$1.log") measured"
  grep -E '\[gsound\]|^stats|\[gmenu\] (open|close)|\[gphoto\] (panel|game-style)|\[photo\] (start|off|leave)' "$OUT/$1.log" | cut -c1-200
}
[ "$WHICH" = local ] || [ "$WHICH" = both ] && run local
[ "$WHICH" = muted ] || [ "$WHICH" = both ] && run muted
exit 0
