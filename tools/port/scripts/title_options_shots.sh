#!/bin/bash
# P364: screenshots of the title menu's "OPTIONS" rows (option nativemenu; title_slot_page / menu_mode_select_page in
# conker/src_eu/game_eu_20B730.c, gameRows() in port/web/gmenu.js), driven by keys like a player (Skip intro on):
#   slot  the save slot page GAME1 (empty): Space zooms in (NEW GAME + OPTIONS), S selects OPTIONS (NEW GAME faded),
#         Space opens the game-style menu over the running title, ArrowDown / Enter open Picture, Esc / Esc close it
#         (back on the slot page, OPTIONS still selected), W back to NEW GAME, Space starts a new game as usual.
#   multi a used slot (test aid: the three slot summaries are poked in the N64 memory mirror, nothing is saved): GAME1
#         shows PLAY / ERASE + OPTIONS, S selects it; F zooms out, D / Space go to MULTI (main menu), D / Space open the
#         next mode group's page, D selects SET-UP, S selects OPTIONS under it, Space opens the menu, Esc closes it, W
#         back on SET-UP.
#   settings (P367) the game's own OPTIONS page (D, D, Space from GAME1): S x3 reaches its fourth row SETTINGS (the game's
#         cursor slides to it), Space opens the game-style menu, Esc closes it (back on SETTINGS), W back to the
#         screen-position item, S S wraps to the first item, W from there reaches SETTINGS again, F leaves the page.
#   tools/port/scripts/title_options_shots.sh OUTDIR [720|1080|both] [slot|multi|settings|all]
#   720 = 1280x720; 1080 = 1920x1080 widescreen + full resolution + smooth font + hi-res 2D. Muted headless Chrome, one at
#   a time (PROBE_NOWAIT=1 on a shared machine). Log lines "mark {...}" = GMenu state (open / from / page) + page pause.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/title_options}; WHICH=${2:-both}; FLOWS=${3:-all}; EXTRA=${4:-}
JK="window.JK = (c) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: c })), 120))"
MARK="console.log('mark ' + JSON.stringify(GMenu.state()) + ' paused=' + userPaused)"
# slot summaries (g_save_slot_summaries, N64 0x800BE818, 16 bytes each; the mirror is at wasm 0x10800000 and keeps
# big-endian words, so whole words are written as numbers): play time 1:02:03, score 1234, stamp 5, resume level 0x29
POKE="window.PK = () => [0, 1, 2].forEach((i) => (M.HEAP32[(0x10800000 + 0xBE818 + 16 * i) >> 2] = 3723, M.HEAP32[(0x10800000 + 0xBE81C + 16 * i) >> 2] = 1234, M.HEAP32[(0x10800000 + 0xBE820 + 16 * i) >> 2] = 5, M.HEAP32[(0x10800000 + 0xBE824 + 16 * i) >> 2] = 0x29050100))"
key() { echo "raw:$1:keydown:$2" "raw:$(($1 + 150)):keyup:$2"; }
slot() {   # $1 = W,H  $2 = options  $3 = prefix
  local p=$3
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" "$1" 44 "app=game&opt=skipintro:1,nativemenu:1$2" \
    "raw:20000:eval:$JK" '23000:'"$p"'0_title' \
    $(key 23300 Space) '25800:'"$p"'1_slot_with_options' "raw:25900:eval:$MARK" \
    $(key 26200 KeyS) '27200:'"$p"'2_options_selected' \
    $(key 27500 Space) '28700:'"$p"'3_menu_over_title' "raw:28800:eval:$MARK" \
    $(key 29100 ArrowDown) $(key 29400 Enter) '30400:'"$p"'4_menu_picture_page' \
    "raw:30600:eval:JK('Escape')" "raw:31000:eval:JK('Escape')" '32000:'"$p"'5_back_to_title' "raw:32100:eval:$MARK" \
    $(key 32400 KeyW) '33400:'"$p"'6_new_game_selected' \
    $(key 33700 Space) '36500:'"$p"'7_new_game_started' '43000:'"$p"'8_opening'
  mv "$OUT/pageshot_$1.log" "$OUT/$p.log"
  grep -E '^mark|\[gmenu\]' "$OUT/$p.log" | head -12
}
multi() {
  local p=$3
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" "$1" 46 "app=game&opt=skipintro:1,nativemenu:1$2" \
    "raw:12000:eval:$JK" "raw:12100:eval:$POKE" "raw:21000:eval:PK()" "raw:23000:eval:PK()" \
    $(key 23300 Space) "raw:24500:eval:PK()" '25800:'"$p"'0_used_slot_with_options' \
    $(key 26100 KeyS) '27100:'"$p"'1_used_slot_options_selected' \
    $(key 27400 KeyF) $(key 29400 KeyD) $(key 31100 Space) $(key 35100 KeyD) $(key 37100 Space) \
    '39600:'"$p"'2_modes_with_options' $(key 39900 KeyD) '40900:'"$p"'3_setup_selected' \
    $(key 41200 KeyS) '42200:'"$p"'4_options_selected' \
    $(key 42500 Space) '43600:'"$p"'5_menu_over_modes' "raw:43700:eval:$MARK" \
    "raw:43900:eval:JK('Escape')" '44800:'"$p"'6_closed' "raw:44900:eval:$MARK" \
    $(key 45100 KeyW) '45800:'"$p"'7_setup_again'
  mv "$OUT/pageshot_$1.log" "$OUT/$p.log"
  grep -E '^mark|\[gmenu\]' "$OUT/$p.log" | head -12
}
settings() {   # P367: the game's own title OPTIONS page (title_press_start_page) with its fourth row SETTINGS
  local p=$3
  # shellcheck disable=SC2046
  tools/port/scripts/pageshot.sh "$OUT" "$1" 46 "app=game&opt=skipintro:1,nativemenu:1$2" \
    "raw:20000:eval:$JK" $(key 23300 KeyD) $(key 25300 KeyD) '27000:'"$p"'0_options_place' \
    $(key 27300 Space) '30000:'"$p"'1_options_page_with_settings' $(key 30300 KeyS) $(key 31300 KeyS) \
    '32300:'"$p"'2_screen_position_selected' $(key 32600 KeyS) '33000:'"$p"'3_cursor_sliding' '34000:'"$p"'4_settings_selected' \
    $(key 34300 Space) '35500:'"$p"'5_menu_over_options' "raw:35600:eval:$MARK" \
    "raw:36000:eval:JK('Escape')" '37000:'"$p"'6_closed_back_on_settings' "raw:37100:eval:$MARK" \
    $(key 37300 KeyW) '38500:'"$p"'7_up_screen_position' $(key 38800 KeyS) $(key 39800 KeyS) '41000:'"$p"'8_down_wraps_to_first' \
    $(key 41300 KeyW) '42500:'"$p"'9_up_from_first_to_settings' $(key 42800 KeyF) '44500:'"$p"'10_left_the_page'
  mv "$OUT/pageshot_$1.log" "$OUT/$p.log"
  grep -E '^mark|\[gmenu\]' "$OUT/$p.log" | head -12
}
for r in 720 1080; do
  [ "$WHICH" = "$r" ] || [ "$WHICH" = both ] || continue
  if [ $r = 720 ]; then W=1280,720; O="$EXTRA"; P=w; else W=1920,1080; O=",widescreen:1,fullres:1,smoothfont:1,hires2d:1$EXTRA"; P=f; fi
  if [ "$FLOWS" = slot ] || [ "$FLOWS" = all ]; then slot "$W" "$O" ${P}s; fi
  if [ "$FLOWS" = multi ] || [ "$FLOWS" = all ]; then multi "$W" "$O" ${P}m; fi
  if [ "$FLOWS" = settings ] || [ "$FLOWS" = all ]; then settings "$W" "$O" ${P}o; fi
done
