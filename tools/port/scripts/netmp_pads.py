#!/usr/bin/env python3
"""P337: frame scripts (?padf syntax, F:BTN:X:Y) for 4 controllers: Player 1 drives the title and the MULTI menus into
Total War (the P217 / P223 route, retraces at det=2 from power-on with the default options), every pad presses A on the
mode / character pages to join, then all 4 move for SECS seconds of retraces with sticks, jumps (A), attacks (B), Z.
Prints shell assignments PADF0..PADF3 (netrun.sh evals them).   netmp_pads.py [PLAY_FROM] [PLAY_SECS] [SEED]"""
import sys
play_from = int(sys.argv[1]) if len(sys.argv) > 1 else 7000
play_secs = int(sys.argv[2]) if len(sys.argv) > 2 else 60
seed = int(sys.argv[3]) if len(sys.argv) > 3 else 337
# title Start, MULTI menu (B, right, Start, Start, B, right, Start): P223 war.env
p1_menu = "3386:1000:0:0,3401:0:0:0,3700:4000:0:0,3708:0:0:0,4000:0:80:0,4008:0:0:0,4300:1000:0:0,4315:0:0:0," \
          "4700:1000:0:0,4715:0:0:0,5000:4000:0:0,5008:0:0:0,5120:0:80:0,5128:0:0:0,5300:1000:0:0,5315:0:0:0"
joins = [5900, 6200, 6500, 6800]   # A on the character / setup pages (all pads)
join_start = 5750                   # pads 2..4: Start on the "press START" join page (shown ~5650 .. 5900)
rng = seed
def rand(n):
    global rng
    rng = (rng * 1103515245 + 12345) & 0x7FFFFFFF
    return (rng >> 8) % n
out = []
for ch in range(4):
    ev = [f"{join_start + ch}:1000:0:0,{join_start + ch + 15}:0:0:0"] if ch else [p1_menu, "5600:8000:0:0,5610:0:0:0"]
    for f in joins: ev.append(f"{f + ch}:8000:0:0,{f + ch + 10}:0:0:0")
    f = play_from + 7 * ch
    end = play_from + play_secs * 50
    while f < end:
        x, y = rand(161) - 80, rand(161) - 80
        dur = 20 + rand(80)
        btn = [0, 0, 0, 0x8000, 0x4000, 0x2000][rand(6)]   # mostly move, sometimes jump / attack / Z
        ev.append(f"{f}:{btn:X}:{x}:{y}")
        if btn: ev.append(f"{f + 6}:0:{x}:{y}")
        f += dur
    ev.append(f"{end}:0:0:0")
    out.append(",".join(ev))
for ch, s in enumerate(out): print(f"PADF{ch}='{s}'")
