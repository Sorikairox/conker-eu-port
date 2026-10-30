#!/bin/bash
# P363: screenshots of the game's own pause menu with the port's "OPTIONS" row (option nativemenu; game_pause_update in
# conker/src_eu/game_eu_20B730.c, gameRows() in port/web/gmenu.js), driven by keys like a player:
#   Start (Enter) pauses, stick down (S) selects OPTIONS, A (Space) opens the game-style menu over the game's pause,
#   arrows / Enter move in it, Esc goes back and closes it (back on the pause menu, OPTIONS still selected), stick up
#   (W) back to CONT.., Start resumes, W walks.
#   tools/port/scripts/pause_options_shots.sh OUTDIR [720|1080|both] [EXTRA_OPTS]
#   720 = 1280x720; 1080 = 1920x1080 widescreen + full resolution + smooth font + hi-res 2D. Muted headless Chrome, one at
#   a time (PROBE_NOWAIT=1 on a shared machine). Log lines "mark {...}" = GMenu state, page pause, row switch.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/pause_options}; WHICH=${2:-both}; EXTRA=${3:-}
JK="window.JK = (c) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: c })), 120))"
MARK="console.log('mark ' + JSON.stringify(GMenu.state()) + ' paused=' + userPaused)"
key() { echo "raw:$1:keydown:$2" "raw:$(($1 + 150)):keyup:$2"; }
run() {   # $1 = W,H  $2 = options  $3 = prefix
  local p=$3
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" "$1" 36 "app=game&warp=29&p205obj=50&opt=nativemenu:1$2" \
    "raw:12000:eval:$JK" '19500:'"$p"'0_play' \
    $(key 20000 Enter) '21800:'"$p"'1_pause_with_options' "raw:21900:eval:$MARK" \
    $(key 22200 KeyS) '23200:'"$p"'2_options_selected' \
    $(key 23500 Space) '24600:'"$p"'3_menu_over_pause' "raw:24700:eval:$MARK" \
    $(key 25000 ArrowDown) $(key 25300 Enter) '26300:'"$p"'4_menu_picture_page' \
    "raw:26500:eval:JK('Escape')" "raw:26900:eval:JK('Escape')" '27800:'"$p"'5_back_to_pause' "raw:27900:eval:$MARK" \
    $(key 28200 KeyW) '29000:'"$p"'6_cont_selected' \
    $(key 29300 Enter) "raw:30200:eval:$MARK" "raw:30400:keydown:KeyW" "raw:32400:keyup:KeyW" '33000:'"$p"'7_resumed_walked' "raw:33100:eval:$MARK"
  mv "$OUT/pageshot_$1.log" "$OUT/$p.log"
  grep -E '^mark|\[gmenu\]' "$OUT/$p.log" | head -20
  grep -E '\[p205obj\] frame|\[p205obj\]   rec  ?[0-9]+ ' "$OUT/$p.log" | awk '/frame/ {f=$3; p=$5; next} {r=$3+0; if (r==p) print "  player pos @" f ": " $11, $12, $13}' | tail -4
}
if [ "$WHICH" = 720 ] || [ "$WHICH" = both ]; then run 1280,720 "$EXTRA" w; fi
if [ "$WHICH" = 1080 ] || [ "$WHICH" = both ]; then run 1920,1080 ",widescreen:1,fullres:1,smoothfont:1,hires2d:1$EXTRA" f; fi
