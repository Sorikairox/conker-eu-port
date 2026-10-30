#!/bin/bash
# P361: screenshots of the game-style menu (option nativemenu, port/web/gmenu.js) driven like a player would:
#   title  1280x720: Esc (JS key event: a CDP Escape hides the headless tab, P357) opens it over the title menu, real CDP
#          arrow / Enter keys move, open a section and change an option, Esc goes back and closes.
#   play   1920x1080 widescreen + smooth font, ?warp=29 gameplay: a fake gamepad (navigator.getGamepads) opens it with
#          Home, D-pad down / A / B navigate.
#   tools/port/scripts/gmenu_shots.sh OUTDIR [title|play|all]      (muted headless Chrome, one at a time: PROBE_NOWAIT=1 on a shared machine)
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/gmenu}; WHICH=${2:-all}
JK="window.JK = (c) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: c })), 120))"
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
fi
if [ "$WHICH" = play ] || [ "$WHICH" = all ]; then
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" 1920,1080 36 'app=game&warp=29&opt=nativemenu:1,widescreen:1,fullres:1,smoothfont:1,hires2d:1' \
    "raw:12000:eval:$FP" '24000:p0_play' "raw:24200:eval:PB(16)" '25000:p1_open_pad' \
    "raw:25200:eval:PB(13)" "raw:25600:eval:PB(0)" '26400:p2_picture_page' "raw:26500:eval:$ST" \
    "raw:26700:eval:PB(13)" "raw:27100:eval:PB(13)" "raw:27500:eval:PB(13)" "raw:27900:eval:PB(13)" '28800:p3_smoothfont_row' \
    "raw:29000:eval:PB(0)" '29800:p4_pixel_font' "raw:29900:eval:$ST" "raw:30000:eval:PB(0)" "raw:30400:eval:PB(2)" '31200:p5_back_main' \
    "raw:31400:eval:PB(16)" '32200:p6_closed' "raw:32300:eval:$ST" "raw:32400:eval:console.log('opts smoothfont=' + opt('smoothfont') + ' paused=' + userPaused)"
fi
grep -hE 'gmstate|opts |\[gmenu\]|\[options\]' "$OUT"/pageshot_*.log 2>/dev/null | tail -30
