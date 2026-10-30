#!/bin/bash
# P369: the touch controls on an emulated phone (port/web/audprobe.js PROBE_MOBILE: mobile metrics, DPR 3, touch
# emulation = pointer: coarse / ontouchstart / maxTouchPoints, the phone's user agent; the page's first load already
# sees the phone, so the touch controls come up by themselves as on a real one: no ?touch=1). Every input is a real CDP
# touch event on the on-screen controls, except the boot (Enter).
#   tools/port/scripts/phone_shots.sh OUTDIR ios|android W,H PREFIX [TURN_TO_W,H]
# Flow: boot (?warp=29), a_play; tap the corner button: b_menu (the customisation settings with the touch controls);
# stick down one step + A: c_menu_page (Picture); B: back on the main page; B: d_closed (the controls are still there);
# stick up 2 s in the game: e_walk (Conker walks: "player pos" lines). With TURN_TO: tap the corner button again, turn
# the phone (f_menu_turned), B closes: g_closed_turned (the controls must be complete and in place), stick up 2 s:
# h_walk_turned. Log lines: "mark {...}" = GMenu state, touch state, pad 1 as the game reads it (port_pad_state: while
# the menu is open the game must see no buttons and no stick), body classes, the A face's canvas width.
# Muted headless Chrome, one at a time (PROBE_NOWAIT=1 on a shared machine).
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/phone_shots}; UA=${2:-ios}; WH=${3:-390,844}; p=${4:-p}; TURN=${5:-}
JK="window.JK = (c, k) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: k || c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: k || c })), 120))"
MARK="console.log('mark ' + JSON.stringify(Object.assign(GMenu.state(), { touch: [touch.b.toString(16), touch.x, touch.y], game: Array.from(M.HEAP32.subarray((M._port_pad_state() >> 2) + 1, (M._port_pad_state() >> 2) + 4)), w: innerWidth + 'x' + innerHeight, gtA: (\$('tk-A').querySelector('canvas.gt') || {}).width, disp: getComputedStyle(\$('touch')).display })) + ' body=' + document.body.className)"
# control centres (CSS px) from index.html's #touch rules: A / B / START / the resting stick (zone left + 90, bottom - 80)
pos() {   # $1 = W,H  $2 = menu (1: the menu's layout) -> sets AX AY BX BY SX SY KX KY
  local W=${1%,*} H=${1#*,}
  AX=$((W - 151)); AY=$((H - 53)); BX=$((W - 204)); BY=$((H - 124)); KX=90; KY=$((H - 80))
  SX=$((W / 2)); SY=$((H - 25)); [ "$H" -gt "$W" ] && SY=$((H - 215))
  # landscape with the menu open: A / B / START in the right margin (index.html body.gmenu rules)
  if [ "${2:-0}" = 1 ] && [ "$W" -gt "$H" ]; then AX=$((W - 53)); AY=$((H - 65)); BX=$((W - 124)); BY=$((H - 128)); SX=$((W - 52)); SY=$((H - 205)); fi
}
t=0; S=()
at() { t=$((t + $1)); }
tap() { S+=("raw:$t:touchdown:$1,$2,$3" "raw:$((t + 120)):touchup:$1,$2,$3"); at "${4:-700}"; }
mark() { S+=("raw:$t:eval:$MARK"); at 100; }
shot() { S+=("$t:$p$1"); at 700; }
stick() {   # $1 = dy (CSS px, + = down)  $2 = hold ms; marks while held (the game's pad must stay idle in the menu)
  S+=("raw:$t:touchdown:$KX,$KY,9" "raw:$((t + 80)):touchmove:$KX,$((KY + $1 / 2)),9" "raw:$((t + 160)):touchmove:$KX,$((KY + $1)),9" "raw:$((t + 260)):eval:$MARK")
  S+=("raw:$((t + $2)):touchup:$KX,$((KY + $1)),9"); at $(($2 + 600))
}
pos "$WH" 1
S+=("raw:2500:eval:$JK" "raw:4500:eval:JK('Enter')"); t=26000
shot a_play; mark
tap 30 30 0 1200; shot b_menu; mark
stick 50 400; tap "$AX" "$AY" 1 900; shot c_menu_page; mark
tap "$SX" "$SY" 3 900; mark   # START in the menu chooses (Widescreen toggles)
tap "$SX" "$SY" 3 900; mark   # and back
S+=("raw:$t:touchdown:$AX,$AY,1" "raw:$((t + 200)):eval:$MARK" "raw:$((t + 400)):touchup:$AX,$AY,1"); at 900   # A held in the menu: not the game's
tap "$BX" "$BY" 2 900; mark
tap "$BX" "$BY" 2 1200; shot d_closed; mark
pos "$WH"
S+=("raw:$t:eval:console.log('mark stick start')"); at 100; stick -55 2000; S+=("raw:$t:eval:console.log('mark stick end')"); at 100; shot e_walk; mark
if [ -n "$TURN" ]; then
  tap 30 30 0 1200; mark
  S+=("raw:$t:orient:$TURN"); at 2500; shot f_menu_turned; mark
  pos "$TURN" 1
  tap "$BX" "$BY" 2 1500; shot g_closed_turned; mark
  pos "$TURN"
  S+=("raw:$t:eval:console.log('mark stick start')"); at 100; stick -55 2000; S+=("raw:$t:eval:console.log('mark stick end')"); at 100; shot h_walk_turned; mark
fi
PROBE_MOBILE=$UA PROBE_NOWAIT=${PROBE_NOWAIT:-} tools/port/scripts/pageshot.sh "$OUT" "$WH" $((t / 1000 + 4)) "warp=29&p205obj=50" "${S[@]}" >/dev/null
mv "$OUT/pageshot_$WH.log" "$OUT/$p.log"
grep -E '^mark|\[gtouch\]|\[gmenu\] (open|close)|Aborted|Uncaught' "$OUT/$p.log" | cut -c1-330
awk '/^mark stick/ {print; next} /\[p205obj\] frame/ {f=$3; next} /\[p205obj\]   rec  0 / {print "  player pos @" f ": " $11, $12, $13}' "$OUT/$p.log" | grep -B1 -A1 '^mark stick'
