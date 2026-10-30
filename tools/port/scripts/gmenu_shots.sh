#!/bin/bash
# P361: screenshots of the game-style menu (option nativemenu, port/web/gmenu.js) driven like a player would:
#   title  1280x720: Esc (JS key event: a CDP Escape hides the headless tab, P357) opens it over the title menu, real CDP
#          arrow / Enter keys move, open a section and change an option, Esc goes back and closes.
#   play   1920x1080 widescreen + smooth font, ?warp=29 gameplay: a fake gamepad (navigator.getGamepads) opens it with
#          Home, D-pad down / A / B navigate.
#   keys   (P362) 1280x720, ?warp=29: by keys to the new pages (Controls, Keyboard keys, a capture that binds Stick up
#          to T, Sound, Saves, the main page's lower rows), then holds W (now unbound: Conker stays) and T (he walks);
#          ?p205obj logs Conker's position every 250 retraces ("player pos" lines).
#   pad    (P362) 1920x1080 widescreen + smooth, ?warp=29, fake pad: holding Back (button 8) opens the menu, Controls >
#          Gamepad buttons, a capture that binds A to Y (button 3), Sound, Saves, the lower rows, a Back press closes it,
#          a short Back tap starts photo mode, Start leaves it.
#   tools/port/scripts/gmenu_shots.sh OUTDIR [title|play|keys|pad|all]      (muted headless Chrome, one at a time: PROBE_NOWAIT=1 on a shared machine)
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/gmenu}; WHICH=${2:-all}
JK="window.JK = (c) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: c })), 120)), window.JKD = (c) => dispatchEvent(new KeyboardEvent('keydown', { code: c, key: c })), window.JKU = (c) => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: c }))"
# fake pad: PB(i) queues a press of button i, held for 6 animation frames with 6 idle frames after it (frame-based, so
# timer jitter in the driver cannot merge or drop presses)
# (no ";" in these expressions: pageshot.sh splits its steps on it)
FP="window.FP = { id: 'fake pad', index: 0, connected: true, mapping: 'standard', axes: [0, 0, 0, 0], buttons: Array.from({ length: 17 }, () => ({ pressed: false, value: 0 })) }, navigator.getGamepads = () => [window.FP], window.PQ = [], window.PB = (i) => PQ.push(i), window.PUMP = (n, b = PQ[0]) => (FP.buttons.forEach((x, j) => (x.pressed = b !== undefined && n < 6 && j === b, x.value = x.pressed ? 1 : 0)), b !== undefined && n >= 11 ? (PQ.shift(), n = -1) : 0, requestAnimationFrame(() => PUMP(b === undefined ? 0 : n + 1))), PUMP(0)"
ST="console.log('gmstate ' + JSON.stringify(GMenu.state()))"
key() { echo "raw:$1:keydown:$2" "raw:$(($1 + 120)):keyup:$2"; }
if [ "$WHICH" = title ] || [ "$WHICH" = all ]; then
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" 1280,720 40 'app=game&opt=skipintro:1,nativemenu:1' \
    "raw:20000:eval:$JK" '23000:t0_title' "23700:t1_open:JK('Escape')" \
    $(key 24200 ArrowDown) $(key 24500 ArrowDown) '25400:t2_sel_hud' \
    $(key 25700 Enter) '26600:t3_hud_page' $(key 26900 ArrowDown) $(key 27200 ArrowRight) "raw:27500:eval:$ST" '28200:t4_hud_health_on' \
    "raw:28400:eval:JK('Escape')" '29200:t5_back_main' $(key 29400 ArrowUp) $(key 29700 ArrowUp) $(key 30000 ArrowRight) '30800:t6_preset_classic' \
    "raw:31000:click" '31800:t7_click_gameplay' "raw:31900:eval:$ST" \
    "raw:32000:eval:JK('Escape')" "raw:32400:eval:JK('Escape')" '33200:t8_closed' "raw:33300:eval:$ST" \
    "raw:33400:eval:console.log('opts ' + ['healthhud', 'skipintro'].map((k) => k + '=' + opt(k)).join(' ') + ' preset=' + presetShown() + ' paused=' + userPaused)"
  mv "$OUT/pageshot_1280,720.log" "$OUT/title.log"
fi
if [ "$WHICH" = play ] || [ "$WHICH" = all ]; then
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" 1920,1080 36 'app=game&warp=29&opt=nativemenu:1,widescreen:1,fullres:1,smoothfont:1,hires2d:1' \
    "raw:12000:eval:$FP" '24000:p0_play' "raw:24200:eval:PB(16)" '25000:p1_open_pad' \
    "raw:25200:eval:PB(13)" "raw:25600:eval:PB(0)" '26400:p2_picture_page' "raw:26500:eval:$ST" \
    "raw:26700:eval:PB(13)" "raw:27100:eval:PB(13)" "raw:27500:eval:PB(13)" "raw:27900:eval:PB(13)" '28800:p3_smoothfont_row' \
    "raw:29000:eval:PB(0)" '29800:p4_pixel_font' "raw:29900:eval:$ST" "raw:30000:eval:PB(0)" "raw:30400:eval:PB(2)" '31200:p5_back_main' \
    "raw:31400:eval:PB(16)" '32200:p6_closed' "raw:32300:eval:$ST" "raw:32400:eval:console.log('opts smoothfont=' + opt('smoothfont') + ' paused=' + userPaused)"
  mv "$OUT/pageshot_1920,1080.log" "$OUT/play.log"
fi
# P362 fake pad with holds: PH(i, n) queues a press of button i held for n animation frames (then 6 idle frames)
FH="window.FP = { id: 'fake pad', index: 0, connected: true, mapping: 'standard', axes: [0, 0, 0, 0], buttons: Array.from({ length: 17 }, () => ({ pressed: false, value: 0 })) }, navigator.getGamepads = () => [window.FP], window.PQ = [], window.PH = (i, n = 6) => PQ.push([i, n]), window.PUMP = (f, q = PQ[0]) => (FP.buttons.forEach((x, j) => (x.pressed = !!q && f < q[1] && j === q[0], x.value = x.pressed ? 1 : 0)), q && f >= q[1] + 6 ? (PQ.shift(), f = -1) : 0, requestAnimationFrame(() => PUMP(q ? f + 1 : 0))), PUMP(0)"
MARK="console.log('mark ' + JSON.stringify(GMenu.state()) + ' UP=' + keyMap.UP + ' padA=' + padMap.A + ' photo=' + photo.state)"
if [ "$WHICH" = keys ] || [ "$WHICH" = all ]; then
  t=23500; steps=()
  k() { steps+=($(key $t "$1")); t=$((t + ${2:-300})); }
  s() { t=$((t + 500)); steps+=("$t:$1"); t=$((t + 300)); }
  for i in 1 2 3 4; do k ArrowDown; done; k Enter; s k2_controls_page
  k Enter; s k3_keys_page
  k Enter; s k4_capture_prompt
  k KeyT; s k5_stick_up_is_T; steps+=("raw:$t:eval:$MARK")
  k Backspace; k Backspace; k ArrowDown; k Enter; s k6_sound_page
  k Backspace; k ArrowDown; k Enter; s k7_saves_page
  k Backspace; for i in 1 2 3 4 5; do k ArrowDown; done; s k8_main_lower_rows
  k ArrowDown; k ArrowDown; s k8b_main_last_row
  k Backspace; s k9_closed; steps+=("raw:$t:eval:$MARK")
  # W (unbound now) for 6 s, then T (Stick up now) for 6 s; JS key events (a CDP key held for seconds hid the headless
  # tab: the page paused itself)
  w0=$((t + 1000)); t0=$((w0 + 7000))
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" 1280,720 $(((t0 + 9000) / 1000)) 'app=game&warp=29&p205obj=50&opt=nativemenu:1' \
    "raw:12000:eval:$JK" '22000:k0_play' "raw:22500:eval:JK('Escape')" '23300:k1_open_main' "${steps[@]}" \
    "raw:$((w0 - 100)):eval:console.log('mark hold W')" "raw:$w0:eval:JKD('KeyW')" "raw:$((w0 + 6000)):eval:JKU('KeyW')" "$((w0 + 6500)):k10_after_W" \
    "raw:$((t0 - 100)):eval:console.log('mark hold T')" "raw:$t0:eval:JKD('KeyT')" "raw:$((t0 + 6000)):eval:JKU('KeyT')" "$((t0 + 6500)):k11_after_T" \
    "raw:$((t0 + 6600)):eval:console.log('mark end')"
  L="$OUT/keys.log"; mv "$OUT/pageshot_1280,720.log" "$L"
  grep -E '^mark|\[p205obj\] frame|\[p205obj\]   rec  ?[0-9]+ ' "$L" | awk '/^mark/ {print; next} /frame/ {f=$3; p=$5; next} {r=$3+0; if (r==p) print "  player pos @" f ": " $11, $12, $13}' | grep -A3 -E '^mark' | tail -40
fi
if [ "$WHICH" = pad ] || [ "$WHICH" = all ]; then
  t=23800; steps=()
  b() { steps+=("raw:$t:eval:PH($1${2:+, $2})"); t=$((t + ${3:-400})); }
  s() { t=$((t + 500)); steps+=("$t:$1"); t=$((t + 300)); }
  for i in 1 2 3 4; do b 13; done; b 0; s s2_controls_page
  b 13; b 0; s s3_pad_page
  for i in 1 2 3 4 5 6; do b 13; done; s s4_pad_row_A   # P368: row 0 is Connected gamepads
  b 0; s s5_capture_prompt
  b 3 "" 600; s s6_A_is_Y; steps+=("raw:$t:eval:$MARK")
  b 1; b 1; b 13; b 0; s s7_sound_page
  b 1; b 13; b 0; s s8_saves_page
  b 1; for i in 1 2 3 4 5; do b 13; done; s s9_main_lower_rows
  b 8 "" 600; s s10_closed_by_back; steps+=("raw:$t:eval:$MARK")
  b 8 6 2500; s s11_photo_by_tap; steps+=("raw:$t:eval:$MARK")
  b 9 "" 1500; s s12_photo_left; steps+=("raw:$t:eval:$MARK")
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" 1920,1080 $(((t + 3000) / 1000)) 'app=game&warp=29&opt=nativemenu:1,photomode:1,widescreen:1,fullres:1,smoothfont:1,hires2d:1' \
    "raw:12000:eval:$FH" '22000:s0_play' "raw:22200:eval:PH(8, 40)" "raw:22500:eval:$MARK" '23500:s1_open_by_hold' "raw:23600:eval:$MARK" "${steps[@]}"
  mv "$OUT/pageshot_1920,1080.log" "$OUT/pad.log"
fi
grep -hE 'gmstate|opts |mark |\\[gmenu\\]|\\[options\\]|\\[binds\\]|\\[photo\\]' "$OUT"/*.log 2>/dev/null | tail -40
