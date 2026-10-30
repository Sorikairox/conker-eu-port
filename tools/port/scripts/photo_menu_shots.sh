#!/bin/bash
# P366: screenshots of photo mode in the game's style (option nativemenu: gmenu.js GPhoto), driven by keys like a player:
#   P starts photo mode (the HUD bottom left, the Pose & Outfit panel right, unfocused), O gives the panel the focus,
#   Enter on Animation opens the animation list (857 entries: Page Down, held Down speeds up), Enter picks one, Down /
#   Enter toggles Play, the Model list, Item 1's list, the Materials page with a tint, H hides every menu (and shows them
#   again), He carries (his own attachment) hidden, Esc goes back / unfocuses / leaves photo mode, then W walks (play goes
#   on where it was).
#   tools/port/scripts/photo_menu_shots.sh OUTDIR [720|1080|both|pad|mouse|off] [LEVEL] [EXTRA_OPTS]
#   720 = 1280x720; 1080 = 1920x1080 widescreen + full resolution + smooth font + hi-res 2D. Muted headless Chrome, one at
#   a time (PROBE_NOWAIT=1 on a shared machine). Log lines "mark {...}" = window.__gphoto.state(); "[p205obj]" = positions.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/photo_menu}; WHICH=${2:-both}; LEVEL=${3:-29}; EXTRA=${4:-}
# JS key helpers (comma expressions: pageshot steps split on ';'): JK = one press; JR(code, n) = a held key's n auto-repeats
JK="window.JK = (c) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: c })), 120)), window.JR = (c, n, i = 0, f = null) => (f = () => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: c, repeat: i > 0 })), ++i < n ? setTimeout(f, 33) : dispatchEvent(new KeyboardEvent('keyup', { code: c, key: c }))), f())"
MARK="console.log('mark ' + JSON.stringify(window.__gphoto.state()) + ' photo=' + photo.state)"
run() {   # $1 = W,H  $2 = options  $3 = prefix
  local p=$3 t=19000 S=()
  at() { t=$((t + $1)); }
  k() { S+=("raw:$t:eval:JK('$1')"); at "${2:-350}"; }
  shot() { S+=("$t:$p$1" "raw:$((t + 50)):eval:$MARK"); at 700; }
  S+=("raw:12000:eval:$JK")
  shot 00_play
  k KeyP 1500; shot 01_photo_hud
  k KeyO; shot 02_panel_focus
  k Enter; shot 03_anim_list
  k PageDown; k PageDown; S+=("raw:$t:eval:JR('ArrowDown', 60)"); at 2600; shot 04_anim_list_fast
  k Enter 1200; shot 05_anim_picked
  k ArrowDown; k Enter 2000; shot 06_playing
  k ArrowDown; k ArrowDown; k ArrowDown; k Enter; shot 07_model_list
  k PageDown; k ArrowDown; k Enter 2500; shot 08_model_changed
  k ArrowDown; k Enter; k ArrowDown; k ArrowDown; k ArrowDown; shot 09_item_list
  k Enter 2000; shot 10_item_on
  k ArrowDown; k ArrowDown; k ArrowDown; k ArrowDown; k Enter 2000; shot 10b_attachment_hidden
  k End; k ArrowUp; k ArrowUp; k ArrowUp; shot 11_lower_rows
  k Enter; shot 12_materials
  k Enter; k ArrowDown; k ArrowDown; S+=("raw:$t:eval:JR('ArrowRight', 40)"); at 1800; k ArrowDown; k ArrowRight; k ArrowRight 1500; shot 13_material_tint
  k KeyH 900; shot 14_hidden
  at 1500; shot 15_hidden_later
  k KeyH; shot 16_shown_again
  k KeyO; k Escape 500; shot 17_unfocused
  k Escape 1500; shot 18_left_photo
  S+=("raw:$t:keydown:KeyW"); at 2000; S+=("raw:$t:keyup:KeyW"); at 500; shot 19_walked; at 6000
  tools/port/scripts/pageshot.sh "$OUT" "$1" $((t / 1000 + 3)) "app=game&warp=$LEVEL&p205obj=50&opt=nativemenu:1,photomode:1$2" "${S[@]}"
  mv "$OUT/pageshot_$1.log" "$OUT/$p.log"
  grep -E '^mark|\[gphoto\]|\[photo\]' "$OUT/$p.log" | cut -c1-260 | head -60
  grep -E '\[p205obj\] frame|\[p205obj\]   rec  ?[0-9]+ ' "$OUT/$p.log" | awk '/frame/ {f=$3; p=$5; next} {r=$3+0; if (r==p) print "  player pos @" f ": " $11, $12, $13}' | tail -4
}
# pad: a fake standard gamepad (?gmenutest=1 queue: [button, frames held]) at 1280x720: RS click focuses the panel, D-pad
# / A / X (= N64 B) work it, RT hides / shows the menus, Start leaves photo mode
padrun() {
  local p=pad t=19000 S=()
  at() { t=$((t + $1)); }
  pb() { S+=("raw:$t:eval:__gmenuTest.press([[$1, 4]])"); at "${2:-400}"; }
  shot() { S+=("$t:$p$1" "raw:$((t + 50)):eval:$MARK"); at 700; }
  S+=("raw:12000:eval:$JK")
  S+=("raw:$t:eval:JK('KeyP')"); at 1500; shot 0_photo
  pb 11; pb 13; pb 0 1200; shot 1_rs_focus_play_on
  pb 12; pb 0; pb 15; pb 13; pb 13; pb 0 1500; shot 2_anim_list_page_picked
  pb 7 900; shot 3_rt_hidden
  pb 7; shot 4_rt_shown
  pb 2; shot 5_x_unfocused
  pb 9 1500; shot 6_start_left
  S+=("raw:$t:keydown:KeyW"); at 2000; S+=("raw:$t:keyup:KeyW"); at 500; shot 7_walked; at 6000
  tools/port/scripts/pageshot.sh "$OUT" 1280,720 $((t / 1000 + 3)) "app=game&warp=$LEVEL&p205obj=50&gmenutest=1&opt=nativemenu:1,photomode:1$EXTRA" "${S[@]}"
  mv "$OUT/pageshot_1280,720.log" "$OUT/$p.log"
}
# mouse: clicks at 1280x720 (4:3 picture at x 160..1120): the Model row (focus + its list), an entry (130 mech suit),
# (its Parts page by __gphoto.go, Enter hides part 0, Esc back), the footer's SAVE (PNG + message), Play's value, the
# footer's HIDE MENUS; H shows them again; the footer's EXIT leaves photo mode
mouserun() {
  local p=mouse t=19000 S=()
  at() { t=$((t + $1)); }
  ck() { S+=("raw:$t:click:$1"); at "${2:-600}"; }
  shot() { S+=("$t:$p$1" "raw:$((t + 50)):eval:$MARK"); at 700; }
  S+=("raw:12000:eval:$JK")
  S+=("raw:$t:eval:JK('KeyP')"); at 1500; shot 0_photo
  ck 800,272; shot 1_model_list
  ck 800,262 2500; shot 2_mech_suit
  S+=("raw:$t:eval:__gphoto.go('parts')"); at 600; shot 2b_parts_page
  S+=("raw:$t:eval:JK('Enter')"); at 1500; shot 2c_part0_hidden
  S+=("raw:$t:eval:JK('Escape')"); at 400
  ck 255,649 1300; shot 2d_saved_toast
  ck 1050,158 1200; shot 3_play_clicked
  ck 450,681 900; shot 4_hidden
  S+=("raw:$t:eval:JK('KeyH')"); at 600; shot 5_shown
  ck 520,649 1500; shot 6_exit_clicked
  tools/port/scripts/pageshot.sh "$OUT" 1280,720 $((t / 1000 + 3)) "app=game&warp=$LEVEL&opt=nativemenu:1,photomode:1$EXTRA" "${S[@]}"
  mv "$OUT/pageshot_1280,720.log" "$OUT/$p.log"
}
# off: the option off: photo mode exactly as before (the page's HUD box and Pose & Outfit panel, O = its focus)
offrun() {
  local p=off t=19000 S=()
  at() { t=$((t + $1)); }
  k() { S+=("raw:$t:eval:JK('$1')"); at "${2:-400}"; }
  shot() { S+=("$t:$p$1" "raw:$((t + 50)):eval:console.log('mark gphoto=' + JSON.stringify(window.__gphoto.state().active) + ' bodyclass=' + document.body.className + ' photoHidden=' + document.getElementById('photo').hidden + ' lookHidden=' + document.getElementById('photo-look').hidden)"); at 700; }
  S+=("raw:12000:eval:$JK")
  k KeyP 1500; shot 0_photo
  k KeyO; k ArrowDown; k ArrowRight 1500; shot 1_panel_nav
  k KeyH 600; shot 2_h_does_nothing
  k KeyP 1500; shot 3_left
  tools/port/scripts/pageshot.sh "$OUT" 1280,720 $((t / 1000 + 3)) "app=game&warp=$LEVEL&opt=nativemenu:0,photomode:1$EXTRA" "${S[@]}"
  mv "$OUT/pageshot_1280,720.log" "$OUT/$p.log"
}
case $WHICH in pad) padrun; exit;; mouse) mouserun; exit;; off) offrun; exit;; esac
if [ "$WHICH" = 720 ] || [ "$WHICH" = both ]; then run 1280,720 "$EXTRA" w; fi
if [ "$WHICH" = 1080 ] || [ "$WHICH" = both ]; then run 1920,1080 ",widescreen:1,fullres:1,smoothfont:1,hires2d:1$EXTRA" f; fi
