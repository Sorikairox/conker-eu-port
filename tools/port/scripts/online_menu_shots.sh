#!/bin/bash
# P365: screenshots of the game-style ONLINE pages before boot (port/web/gmenu.js), keys only:
# Enter on the Press Start screen boots the game once (so the page keeps font 0), the page reloads, Esc opens the menu on the Press Start screen,
# ArrowUp x5 + Enter = Online, Enter on Create room (no room server behind this test server: the error shows), Join
# room = the letter picker, typed on the keyboard (k 7 u, an O that room codes do not have, Backspace, 4 9), Esc x3
# back to the Press Start screen. The real 2-4 player sessions through these pages: netpair.sh ROOM=1 UI=gmenu.
#   tools/port/scripts/online_menu_shots.sh OUTDIR [720|1080|both]
#   720 = 1280x720; 1080 = 1920x1080 widescreen + full resolution + smooth font. Muted headless Chrome, one at a time
#   (PROBE_NOWAIT=1 on a shared machine). Log lines "mark {...}" = GMenu.state().
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/online_menu}; WHICH=${2:-both}
JK="window.JK = (c, k) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: k || c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: k || c })), 120))"
MARK="console.log('mark ' + JSON.stringify(GMenu.state()))"
run() {   # $1 = W,H  $2 = options  $3 = prefix
  local p=$3 t=31000 steps=() i
  steps+=("raw:6000:eval:$JK" "raw:7000:eval:JK('Enter')" "raw:20000:eval:$JK" "raw:21000:eval:JK('Escape')" "21800:${p}0_ingame_menu" "raw:22500:eval:JK('Escape')"
          "raw:23500:eval:location.reload()" "raw:30000:eval:$JK" "raw:30500:eval:JK('Escape')" "$t:${p}1_preboot_menu" "raw:$((t + 100)):eval:$MARK")
  for i in 1 2 3 4 5; do steps+=("raw:$((t + 300 * i)):eval:JK('ArrowUp')"); done
  t=$((t + 2000)); steps+=("raw:$t:eval:JK('Enter')" "$((t + 1000)):${p}2_online_page" "raw:$((t + 1100)):eval:$MARK")
  t=$((t + 1500)); steps+=("raw:$t:eval:JK('Enter')" "$((t + 2500)):${p}3_create_no_server" "raw:$((t + 2600)):eval:$MARK")
  t=$((t + 3000)); steps+=("raw:$t:eval:JK('ArrowDown')" "raw:$((t + 300)):eval:JK('Enter')" "$((t + 1300)):${p}4_picker" "raw:$((t + 1400)):eval:$MARK")
  t=$((t + 1800)); steps+=("raw:$t:eval:JK('KeyK', 'k')" "raw:$((t + 300)):eval:JK('Digit7', '7')" "raw:$((t + 600)):eval:JK('KeyU', 'u')" "raw:$((t + 900)):eval:JK('KeyO', 'o')" "$((t + 1800)):${p}5_typed_refused_O")
  t=$((t + 2200)); steps+=("raw:$t:eval:JK('Backspace')" "raw:$((t + 300)):eval:JK('Digit4', '4')" "raw:$((t + 600)):eval:JK('Digit9', '9')" "raw:$((t + 900)):eval:JK('Digit3', '3')" "$((t + 1800)):${p}6_typed_full" "raw:$((t + 1900)):eval:$MARK")
  t=$((t + 2300)); steps+=("raw:$t:eval:JK('Escape')" "raw:$((t + 400)):eval:JK('Escape')" "raw:$((t + 800)):eval:JK('Escape')" "$((t + 1800)):${p}7_back_on_press_start" "raw:$((t + 1900)):eval:$MARK")
  tools/port/scripts/pageshot.sh "$OUT" "$1" $(( t / 1000 + 6 )) "${2:+opt=${2#,}}" "${steps[@]}"
  mv "$OUT/pageshot_$1.log" "$OUT/$p.log"
  grep -E '^mark|\[gmenu\]' "$OUT/$p.log" | head -20
}
[ "$WHICH" = 1080 ] || run 1280,720 "" w
[ "$WHICH" = 720 ] || run 1920,1080 ",widescreen:1,fullres:1,smoothfont:1" f
