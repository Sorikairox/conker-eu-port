# P120: func_151E73C8 - menu camera / carousel (game_eu_20B730, 1129 insns) - map

Called once per frame as the behaviour of the menu camera object (through func_1512A8D0), arg0 = camera index into
D_800DBFF0 (struct108, 0x9A0 bytes). Only writer of the menu record's carousel / zoom state (record D_80090174 =
D_800E0F20, `MenuState` in the func_151DEDD0 NM block; P120 added x42 / x43 / x44).

## Record fields (MenuState)

| off | field | meaning (P120) |
|---|---|---|
| 0x00 | x0 | slide progress between two stops (0..1); > 0.5 shows the next stop's page |
| 0x04 | x4 | slide speed (+0.05 right, -0.05 left; x0 runs 1 -> 0 when going left) |
| 0x08 | fade | zoom into the current stop (0..1); the handler shows the page from 0.5 |
| 0x0C | xC | zoom speed (+ D_800902F8 / D_80090340[stop] in, - out) |
| 0x10 | x10 | weight of the look-at offset (x14, x18, x1C); decays * 0.85, or -(0.25 - fade) * 4 in mode 3 |
| 0x2A | x2A | main-menu camera mode: 0 normal, 1 just entered (look back), 2 back pressed on a page 2..6, 3 jump to stop 4 |
| 0x2B | x2B | carousel stop (0..5 title, 0..7 main) |
| 0x2C | titlePage | page shown: x2B (+1 past the slide midpoint), main menu through D_800AB950 |
| 0x2D | x2D | the stop of titlePage before the D_800AB950 mapping |
| 0x3E | menu | 0 title, 1 main; toggled when fully zoomed into stop 0 (fade restarts at 0.99, zooming out) |
| 0x43 | x43 | request: slide right once (set when the main menu zoomed out at page 0 with x44) |
| 0x44 | x44 | arms x43 |

## Per frame

1. Stop table by menu: title 6 stops (points D_800902F0, speeds D_800902F8, sounds D_800ABD04 [accept, back]),
   main 8 stops (D_80090338, D_80090340, D_800ABD1C). Eye base point: path point func_150871B8(0 / 0x10).
2. State: sliding (x4 != 0) / zooming or zoomed (xC or fade != 0: back 0x20 zooms out except main stop 0, accept 0x10
   zooms in) / at rest (accept starts the zoom with its sound, left / right / x43 start a slide).
3. Eased values: slide = sin(x0 pi - pi/2) / 2 + 1/2, zoom likewise from fade (title: damped by D_eu_80090310[page] *
   D_80090170; main pages != 0: * 0.6).
4. Title: page world objects D_80090360[2][6] (func_151149AC ids) shown (+0x80 = 1) when zoom% > D_80090328[page]
   while zooming in, hidden below D_80090330[page] while zooming out.
5. Camera object +0x3D0: flag 0x200, y = 1000.
6. Zoom > 0: path from the base point to the stop's point and on through the point graph D_800D2778 (16-byte nodes,
   links at +9..+13, 0xFF = none, never back to the previous node; NB the compare is s8 vs u8, a link >= 0x80 back to
   its predecessor loops forever - same in the asm). 4+ points: Catmull-Rom (func_15049AD0) with mirrored ends, eye =
   segment, look-at = segment + 1; 2..3 points: linear. Zoom 0: look-at = spline over stops (x2B - 1 .. x2B + 2) at
   `slide`.
7. x2A != 0 mirrors the look-at through the eye; + x10 * (x14, x18, x1C).
8. Main menu: back at fade 0 (x10 < 0.01, not sliding) -> stop 0 (x2A = 2 on pages 2..6) and an offset jump; mode 1
   below fade 0.25 -> stop 4 then mode 3; mode 3 at fade 0 -> stop 4, mode 0.
9. Toggle at fade >= 1 on stop 0; titlePage / x2D; camera copies (+0x2BC = look-at, +0x390 = 0, +0x19C..0x1A8
   20 / 15); objects 0xF8 (+0x6E = 1), 0xF6 / 0xF7 visible for title / main.

## Callees

func_150871B8, func_1508712C (C), func_15049AD0 (C, NM), func_1000D96C (jal 1000DC5C, C), sinf, func_151149AC
(jal 15114F2C; C on port-b P114 / game_eu_13DC30, asm on `port`). No asm callee of this subsystem remains except
func_151149AC (port-b file).

## Verification (P120)

difftest random EQUIV; knob setups `p120/gen_73c8.py` (record / camera in one mapped page, menu .data tables poked
with their ROM values, func_1508712C out-params via OUTW, sinf via RETF, path graphs c2..c6 / negative id,
DIFFTEST_ARGMEM=15049AD0=0:64 compares the spline point arrays). Mutants `73c8_muts.txt`.
