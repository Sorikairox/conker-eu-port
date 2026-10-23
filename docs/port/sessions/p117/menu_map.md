# P117: game mode 3 (title / main menu, level 0x1D) - map

Entry: LogoScreen scene 1 event 5/0x67 -> func_151DECB4 -> func_151DED3C (C): level 0x1D (func_1501C710(6, 0x1D, ..)),
D_800E0B94 = 3, D_80090120 = 1 (start scene 1 of the level on the next mode-3 frame), D_80090144 = 0 (setup frame
counter), menu record: menu 0 (title), x2B = x2C = 5.
Per frame: func_151E5928 (C) -> D_8009018C[3] = **func_151DEDD0** (menu_mode_update, C now). Render: func_151E8C60 ->
D_800903A4[3] = func_151ECB98 (C).

## The menu record D_80090174 (-> D_800E0F20, set once by func_151E582C, zeroed by func_151E5798)

| off | field (P117 name) | written by | read by |
|---|---|---|---|
| 0x08 | fade (f32): page fade-in, >= 0.5 shows the page | **func_151E73C8 (asm, 1129, carousel object)** | handler, func_151E5AB8 |
| 0x20 | input (u16): controller 1 menu bits this frame | handler | pages, prompt fade |
| 0x22 | padInput[4] (u16): 1 up, 2 down, 4 left, 8 right (stick edges), 0x10 A/Start, 0x20 B, 0x40 C-left?, 0x80 C-right? | handler | func_151E1EDC etc. |
| 0x2A / 0x2B | carousel target / step | func_151E73C8 | func_151E73C8, func_151E5AB8 |
| 0x2C | titlePage (s8) | func_151DED3C (5), func_151E73C8 (x2B at the fade midpoint), func_151E582C | handler (dispatch), func_151ECB98 |
| 0x2E / 0x32 | stickX[4] / stickY[4]: last stick (0 = re-arm the edge) | handler | handler |
| 0x36 / 0x3A | repeatX[4] / repeatY[4]: auto-repeat counters (0x33 then 0x28 -> every 11 ticks) | handler | handler |
| 0x3E | menu (s8): 0 title, 1 main | func_151DED3C, func_151E73C8 (toggle 1 - x) | handler, func_1000E7A0(4, menu) = menu music, render |
| 0x3F | mainPage (s8), 0x40 prevMainPage, 0x41 | pages, func_151E73C8 | handler |
| 0x70 + 12n | per-entry s16 (game_eu_B7840) | | |

## func_151DEDD0 state machine (one call per frame)

1. Setup frames (D_80090144 < 5): frame 0 = func_151EE704 (menu sprites, C now), func_15007778 (save slots reset, C now),
   func_151E856C, func_151E8998 (C); frames 0..3 func_150076BC(frame), frame 4 func_15007684; counter++.
   Later frames: func_1500764C unless D_800901D0.
2. D_80090120: D_800DBFF0->0x2C = 0x80000, func_1501D348(level, 1, 0, 0, 0) (scene start; port-b / web C), clear, return.
3. D_80090110 = n: drop queue entries (D_800901E4 / D_800E1030, copies i + n -> i for i in n .. 15 - n, as the asm).
4. frame >= 5: func_151E5AB8 (C; screen fade from rec->fade).
5. 4 controllers -> padInput (stick +-50 edges, buttons from D_800BED50[i]: 0x1000 / 0x8000 accept, 0x4000 back,
   2 / 1); stick auto-repeat; D_800E0FC6 (screen fade) != 0 zeroes the sticks. rec->input = padInput[0].
6. Attract (D_800C35EA == 1): D_800901C4 = 0; a button before t = 0x546 sets D_80090124 (stop the demo); return.
7. Prompt fade D_800902AC (blinking text 0x23C of D_800E1008 at 0x94, 0xC0, red), accept skips to 0x64.
8. D_800DBFF0->0x2C = 0x80000, func_1000E7A0(4, menu) (menu music, C).
9. After frame 5: D_800E0EC4 = page alpha from rec->fade; fade >= 0.5 -> page handler (A/Start masked until 1.0);
   fade < 0.5 -> reset the menu input state (D_800E0EC6 = -1, D_800E0EC5 = 0xFF, mainPage 0, queues).

## Pages

| menu | key | handler | insns | status | what |
|---|---|---|---|---|---|
| 0 | titlePage 1 | func_151DF6A4 | 410 | **C (P117)** title_press_start_page | Conker (object 9) on the title, title drawing func_151E3AE4 (asm, 953), item 9 = language (voice bank), 0x15 -> info screen (text 0x10, pak flags), 0x19 -> screen position (D_800E1010[0x17/0x18/0x1A/0x1B]), back = func_15007668 |
| 0 | titlePage 2 | func_151DFD0C | 625 | asm | code / cheat entry page (func_1509D338 / D464 / D49C, D_800902D4..E0) - not converted |
| 0 | titlePage 3..5 | func_151E06D0 | 315 | **C (P117)** title_slot_page | save slot 0..2: score / time, continue / erase / start, erase confirm; start = mode 7 fade + callback func_151E3A1C |
| 0 | titlePage 6, other | - | | | nothing |
| 1 | mainPage 0 | func_151E0BBC | 366 | asm | main menu pages (chapter select, options, multiplayer ...): not converted |
| 1 | mainPage 1 | func_151E1EDC | 720 | asm | |
| 1 | mainPage 2 | func_151E1174 | 101 | asm | |
| 1 | mainPage 3 | func_151E2A1C | C | C | func_151E4B40 (asm, 511) with D_80090120 = 3 |
| 1 | mainPage 4 | func_151E1308 | 425 | asm | |
| 1 | mainPage 5 | func_151E19AC | 332 | asm | |

## Stubs still reached (what the menu still needs)

1. **func_151E73C8 (game_eu_20B730, 1129 insns)**: the menu carousel object behaviour (called through func_1512A8D0
   for the menu objects). It is the producer of rec->fade, x2A / x2B, titlePage and the menu toggle. While it is a
   stub rec->fade stays 0, so the handler always takes the "page not shown" branch: **no page handler runs** and
   D_800E0EC4 stays 0. This is the next blocker for anything visible on the menu.
2. func_1501D348 (scene start, game_eu_4A070 = port-b; C on port-b / web).
3. func_151E3AE4 (game_eu_20B730, 953): title drawing of page 1.
4. func_151DFD0C (title page 2) and the main-menu pages func_151E0BBC / func_151E1EDC / func_151E1174 / func_151E1308 /
   func_151E19AC / func_151E4B40 (asm, game_eu_20B730): reached only after func_151E73C8 moves the carousel.
5. func_1507BB28 (game_A28B0 = port-b; page 1 info screen animation), func_1506160C (game_83300; event 0xC8 cmd 0x54).

## Event 0xC8 (level 0x1D) native-6 calls

The 21 calls whose id comes from func_15097D20 (`push entity 0x20xx; native 3` then `push 2, 2, cmd, id; native 6`)
all go to D_80088874[2] = func_15097E9C (object command handler). Both func_15097D20 and func_15097E9C are C on port-b
(P111, game_eu_C5530). Commands used: 0x3D (12x: object +0x94 flags), 0x54 (7x: fade via func_1506160C, asm in
game_83300), 0x14 (func_1507BB28, asm in port-b's game_A28B0).
