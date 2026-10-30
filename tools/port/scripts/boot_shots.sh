#!/bin/bash
# P368: the last native-menus step (docs/design/NATIVE_MENUS.md), the developer drawer, the game-style
# touch controls (with real CDP touch taps) and the boot screens, at one window size per run.
#   tools/port/scripts/boot_shots.sh OUTDIR [720|1080|800|844|all]
#   720 = 1280x720; 1080 = 1920x1080 widescreen + full resolution + smooth font; 800 = 800x1000 portrait touch;
#   844 = 844x390 landscape phone touch. Muted headless Chrome, one at a time (PROBE_NOWAIT=1 on a shared machine).
# Per size, two page loads:
#   A (no ROM: ?romurl=none, the first visit): a_first_run, then a wrong file (right N64 magic, wrong SHA-1) through
#     main.js takeFile: b_error_wrong_file.
#   B (ROM, ?warp=29, a fresh browser profile = no game font kept yet): c_ready_nofont (Press Start, page style, dark),
#     Esc: d_drawer_fallback (the game-style menu cannot open without the font: the whole drawer), Enter boots;
#     e_play (touch sizes: the game-style touch faces), touch sizes: A tapped (f_touch_A_held, log "tb"), stick dragged
#     up 4 s (f2_touch_stick_held; "player pos" = record 0 of ?p205obj, every 250 retraces, around the hold), Start tapped (g_touch_start_pause = the game's pause) and again; Esc:
#     h_gmenu (the game-style menu; the font is kept), Developer tools: i_drawer_dev, "All page controls":
#     j_drawer_all; the option switched off at run time: k_off_play (page touch faces), l_off_drawer (the whole drawer);
#     back on, location.reload(): m_ready_font (Press Start in the game's font), Esc + Online: n_online_backdrop.
# Log lines: "mark {...}" = GMenu.state() + body classes; "tb ..." = main.js touch state.
cd "$(git -C "$(dirname "$0")" rev-parse --show-toplevel)" || exit 1
OUT=${1:-port_work/boot_shots}; WHICH=${2:-all}
JK="window.JK = (c, k) => (dispatchEvent(new KeyboardEvent('keydown', { code: c, key: k || c })), setTimeout(() => dispatchEvent(new KeyboardEvent('keyup', { code: c, key: k || c })), 120))"
MARK="console.log('mark ' + JSON.stringify(GMenu.state()) + ' body=' + document.body.className + ' drawer=' + drawerOpen() + ' running=' + running)"
TB="console.log('tb b=' + touch.b.toString(16) + ' x=' + touch.x + ' y=' + touch.y + ' gtouch=' + document.body.classList.contains('gtouch'))"
WRONG="takeFile(new File([new Uint8Array([0x80, 0x37, 0x12, 0x40]), new Uint8Array(65532)], 'not-conker.z64'))"
run() {   # $1 = W,H  $2 = extra options  $3 = prefix  $4 = touch (1 / 0)
  local W=${1%,*} H=${1#*,} p=$3 tc=$4 t steps=()
  # A: no ROM
  tools/port/scripts/pageshot.sh "$OUT" "$1" 9 "romurl=none${2:+&opt=${2#,}}&touch=$tc" \
    "4000:${p}a_first_run" "raw:4500:eval:$WRONG" "6500:${p}b_error_wrong_file"
  mv "$OUT/pageshot_$1.log" "$OUT/${p}A.log"
  # B: ROM
  steps=("raw:3000:eval:$JK" "4500:${p}c_ready_nofont" "raw:5000:eval:JK('Escape')" "6000:${p}d_drawer_fallback" "raw:6100:eval:$MARK"
         "raw:6600:eval:JK('Escape')" "raw:7200:eval:JK('Enter')" "27500:${p}e_play" "raw:27600:eval:$MARK")
  t=28000
  if [ "$tc" = 1 ]; then
    local ax=$((W - 151)) ay=$((H - 53)) sx=$((W - W / 2)) sy=$((H - 25)) kx=110 ky=$((H - 80))
    [ "$H" -gt "$W" ] && sy=$((H - 215))   # portrait: Start sits higher (index.html @media orientation)
    steps+=("raw:$t:touchdown:$ax,$ay,1" "raw:$((t + 150)):eval:$TB" "$((t + 700)):${p}f_touch_A_held" "raw:$((t + 800)):touchup:$ax,$ay,1" "raw:$((t + 1000)):eval:$TB")
    t=$((t + 1500))
    steps+=("raw:$t:eval:console.log('mark stick start')" "raw:$((t + 100)):touchdown:$kx,$ky,2" "raw:$((t + 200)):touchmove:$kx,$((ky - 25)),2" "raw:$((t + 300)):touchmove:$kx,$((ky - 55)),2"
            "raw:$((t + 600)):eval:$TB" "$((t + 2000)):${p}f2_touch_stick_held" "raw:$((t + 4300)):touchup:$kx,$((ky - 55)),2" "raw:$((t + 4500)):eval:console.log('mark stick end')" "raw:$((t + 4600)):eval:$TB")
    t=$((t + 5500))
    steps+=("raw:$t:touchdown:$sx,$sy,3" "raw:$((t + 200)):touchup:$sx,$sy,3" "$((t + 1800)):${p}g_touch_start_pause" "raw:$((t + 2000)):touchdown:$sx,$sy,3" "raw:$((t + 2200)):touchup:$sx,$sy,3")
    t=$((t + 3500))
  fi
  steps+=("raw:$t:eval:JK('Escape')" "$((t + 900)):${p}h_gmenu" "raw:$((t + 1000)):eval:$MARK"
          "raw:$((t + 1300)):eval:JK('ArrowUp')" "raw:$((t + 1600)):eval:JK('ArrowUp')" "raw:$((t + 1900)):eval:JK('Enter')" "$((t + 2900)):${p}i_drawer_dev" "raw:$((t + 3000)):eval:$MARK"
          "raw:$((t + 3200)):eval:\$('drawer-all').click()" "$((t + 3900)):${p}j_drawer_all" "raw:$((t + 4000)):eval:JK('Escape')"
          "raw:$((t + 8000)):eval:location.reload()"
          "raw:$((t + 13000)):eval:$JK" "$((t + 14000)):${p}m_ready_font" "raw:$((t + 14100)):eval:$MARK" "raw:$((t + 14500)):eval:JK('Escape')")
  t=$((t + 15000))
  for i in 1 2 3 4 5; do steps+=("raw:$((t + 300 * i)):eval:JK('ArrowUp')"); done
  t=$((t + 2000)); steps+=("raw:$t:eval:JK('Enter')" "$((t + 1200)):${p}n_online_backdrop" "raw:$((t + 1300)):eval:$MARK")
  tools/port/scripts/pageshot.sh "$OUT" "$1" $(( t / 1000 + 4 )) "warp=29&p205obj=50&touch=$tc${2:+&opt=${2#,}}" "${steps[@]}"
  mv "$OUT/pageshot_$1.log" "$OUT/${p}B.log"
  grep -E '^mark|^tb |\[gboot\]|\[gtouch\]|\[gmenu\] (open|close)|Aborted|Uncaught' "$OUT/${p}B.log" | cut -c1-260
  # Conker's position before / after the stick hold (p205obj: the player record's x y z)
  awk '/^mark stick/ {print; next} /\[p205obj\] frame/ {f=$3; next} /\[p205obj\]   rec  0 / {print "  player pos @" f ": " $11, $12, $13}' "$OUT/${p}B.log" | grep -B1 -A1 '^mark stick'
}
case $WHICH in 720|all) run 1280,720 "" w 0;; esac
case $WHICH in 1080|all) run 1920,1080 ",widescreen:1,fullres:1,smoothfont:1" f 0;; esac
case $WHICH in 800|all) run 800,1000 "" p 1;; esac
case $WHICH in 844|all) run 844,390 "" l 1;; esac
