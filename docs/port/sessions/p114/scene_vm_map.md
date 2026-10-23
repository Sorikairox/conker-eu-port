# Scene event handler A (func_15024910) - map (P114)

`game_eu_51190.c`, EU 0x15024910, 2027 instructions, frame 0x158, 61 jal, one jump table (jtbl_80096F30, sub 0x6C).
**Compiled C (IDO), not hand-written asm** - and **not a VM**: no loop, no program counter. It handles one 8-byte scene
event and returns 1 (handled) or 0 (not mine). The "opcode 0x67" of the P103 / P112 notes is the type-5 event with
id 0x67.

## Where it sits

- Scene data = asset (6, level, scene), loaded by func_1501D240 -> func_1502B6BC(&q, 0, &n, 3, 6, level, scene), a
  chunk table relocated by func_1502B4A8. func_1501D348 (scene start, port-b's game_eu_4A070) distributes the chunks:
  chunk 0 = header u16 n0 n1 n2 n3; then n0 track position chunks (D_eu_800C3C88[p][t]), n0 8-byte track refs
  (D_800C3A10[p] = first ref; {u16 kind, u8 id}: 1 camera, 2 object, 3 world record), n1 key chunks (D_800C3B98),
  n2 event tracks (D_800C3AA8[p][t], count = size / 8 into D_800C39F8), n3 words.
- Event track: 0x20-byte header (+2 s16 start time) then events {s8 type, u8 delta, s16 id, s8 b4, s8 b5, s16 w6};
  time += delta, type 0 / delta 0 sets the time to id (func_15023C60 walks the same way and returns the frames to the
  next matching event = "span").
- Per frame the due events go through func_15024438 -> func_150243AC -> func_1502AB94(ev, track, value, now, player),
  which resolves the track's ref (kind 2: obj = func_15083E90(id), data = obj + 0x14; kind 3: wrec = func_151149AC(id))
  and calls **func_15024910**, then func_150268BC (P90, C), then func_15029EA8 (asm, 1550 insns) until one returns non-zero.

## Arguments

`s32 func_15024910(s32 ev, u8 track, u16 value, s32 now, s32 player, struct127 *obj, u8 *wrec, u8 *data, s32 flag)`
(`data` unused here; `flag` = D_800C3A08[player]).

## Cases (C draft order = switch order; the asm is an if-chain)

| type / id | does | callees (asm-only marked *) |
|---|---|---|
| 7, 0xE, 0xF, 0x10, 0x12 (only while D_800E1024) | cutscene text light; needs D_800BEECB = 0 / 4 / 2 / 3 / 1, else nothing; light = func_1502354C(track, b4 == 0): b4 0 builds it (text D_800C3A00[p][id], 0xBE / 0xBF prefix -> flags 0x8013 / 0x8019, colour D_800844A8[b5], track record pointers +0xC/+0x10/+0x14), b4 1 func_150234E8, else func_1516D8E8 / func_1516D934 + colour w6 - 1. Always returns 1 | func_1502354C, func_1516D850, func_1516AD20*, func_150234E8, func_1516D8E8, func_1516D934 |
| 0xC | object animation id: w6 -> func_1507EB4C(obj, id); else func_1507E7E4(obj, id, 3, b5 ? 0xFFFF : span, b4) | func_15023C60, func_1507EB4C, func_1507E7E4 |
| 0xD | setup list id + 1: b4 0 run func_15083568, b4 1 undo func_150836CC, b4 2 / 3 set att +0x18 / +0x1A = D_800905C4[b5] | func_15083568 (-> func_15083F30), func_150836CC, func_15031C4C |
| 4 | obj +0x134 = id, +0x135 = clamp(span / 2, 1, 255) when b4 == 0 | func_15023C60 |
| 3 | camera track switch: id < D_800C3A5A[p], ref kind 1, id != D_800C3A18 -> D_800C3A18 = id, D_800DBFF4 = 4, D_800DBFF0->0x5F0 \|= 4 | - |
| 9 / 1 | obj +0x6C + b4 = id + 10 / obj +0x1C9 = id or 0xFF | - |
| 5 | sub-type switch on id (below); unknown id -> 0 | |
| other | return 0 | |

Type 5 ids: 0x3B (D_800DDE18 = record + 0x28), 8 / 9 / 0xD / 0x12 / 0x15 / 0x7C / 0x84 / 0x85 / 0x6D (flags = b4 == 0),
0x13 (D_800C3A80[p] = b4), 0x14 (b4 0 func_15053430*(obj), else func_15060F28*(obj, 0)), 0x41 (obj colour light
+0xA0..A7 from D_800844B4[b5]), 0x44 (level change func_1501C710), 0x17 / 0x16 (obj +0x1FF / +0x206 (+ b5) and
+0x201 / +0x208 = w6), 0x18 / 0x66 / 0x6B (nothing, 1), 0x1D (wrec +0x6E when ref kind 3), 0x1E (D_800C39E2 = b4 + 1,
D_800C39E3 = level), 3 (world record func_151149AC(w6) +0x73 bits), 0x6C (24-way switch on b4: func_151BEE00*,
func_151A9940*, func_151494E0, func_1515F170, func_151645C4, func_151616D0, func_151CD90C, func_150B696C*,
func_151C9CBC x4, func_151CA398, func_151CA484, func_150E0880, func_150FB2A8, func_150F58C0*, func_150FAFC0,
func_15169040, func_151CD944, func_15190A88 + func_1518F9CC, func_151937F4, func_151920FC), 0x6E (func_151905AC list
-> func_1518FA8C), 5 (func_1518D1C0*(obj, D_800844BC[min(b5,3)][1], span or 999, 0, flag, 0, "Cutscene 1")),
0x36 (func_1519D5A0 / func_151482D4), 0x30 (func_1514D3B0*(obj, 0xD, 12/4/7/10, 0)), 0x46 (func_150C6174 /
func_150C619C), 0x25 / 0x58 (D_800C3A70 / D_800C3A74 + func_1510B9D8), 0x3C (obj +0x94 bits), 0x3D (target
func_15083FB0(w6) -> +0x65 / +0x101 / +0x5C), 0x42 (D_800D9CB0 table), 0x43 (func_150B7700), 0x45 (func_151A5580),
0x49 / 0x4B (obj words), 0x4A (func_10011FB0), 0x54 (D_800C3A84[p] = ~b4), 0x55 (func_150C851C), 0x59 / 0x70 / 0x78
/ 0x7F (flags), 0x5A (obj kind 0x53 / 0x28 / 0x21 -> func_15052F9C*), 0x71 (release player slot 0), 0x37 / 0x38
(func_1517F9F8 / func_1517FC90 fades), **0x5C** (fade in / hold / out from the b4 1 / 2 / 3 companion events: level
0x18 func_150F59A0, level 0x21 func_1510AEB0), 0x62, 0x63, 0x64 (D_800DDE40 + record pointers), **0x67
(func_151DECB4(): leave the logo scene)**, 0x73 (func_151E5B94(0)), 0x69 (7 obj actions incl. func_1505959C /
func_15073F1C), 0x6A / 0x7A (D_800C3A94 / 98 / 9C), 0x74, 0x6F, 0x72, 0x79, 0x7B, 0x7D, 0x7E, 0x80, 0x81
(func_15093818), 0x82, 0x83.

Asm-only callees (progress_nm --list at P114 start): func_15052F9C, func_15053430 (port-b game_eu_78230),
func_15060F28 (game_83300; C on port-b / port-web), func_150836CC (converted in P114), func_150B696C, func_150F58C0,
func_151149AC (converted in P114), func_1514D3B0, func_1516AD20, func_1518D1C0, func_151A9940, func_151BEE00 (port-b).
None of the outputs the C reads come from them except func_151149AC (now C) and func_1516AD20 (light handle, stored
only).

## Level 0x21 scene 1 (LogoScreen) - `scdis.py ROM 21 1`

15 tracks, 151 events. Track 13 (ref kind 1) has **type 5 id 0x67 at t = 1700**: the exit to the title menu goes
through this function. Events of scene 1 this function handles: type 3 (ids 0, 3, 0xB, 0xC, 0xD), 4 (ids 0, 2, 4,
0xC), 9 (ids 0x19, 0x1E, 0x21; b4 0 / 1), 0xD (ids 0x3F, 0x40, 0x55; b4 0 / 1 -> func_15083568 -> func_15083F30 and
func_150836CC), type 5: 0x14 (b4 0: func_15053430, port-b asm), 0x25, 0x3C, 0x3D, 0x41, 0x5C (b4 0..3: level 0x21 ->
func_1510AEB0), 0x64, 0x67. Track 9 is ref kind 3 (world record id 253 via func_151149AC).

# Scene event handler C (func_15029EA8) - map only (P114)

`game_eu_51190.c`, EU 0x15029EA8, 827 instructions, compiled C. Third handler of func_1502AB94; extra argument
`replay` (arg9: 1 when D_800C3C88 == 2, i.e. the scene is being skipped / fast-forwarded: most cases then only
restore end states). Reading aid: `port_work/p114/m2c_29ea8.c` (raw m2c, never paste).

| type / id | does |
|---|---|
| 6 / 0xA | positional sound: volume w6 (0 -> 0xFF), span to the b4 1 event (0xFFFF for type 6 or none); type 0xA also fade-in to the b4 2 and fade-out from the b4 3 events; a 0x10-byte record (player, track, spans, volume * 0x7FFF >> 8, looped flag, D_800C3A08 byte) is allocated and passed with **callback func_15023988** to **func_1000FA64**(id, x, y, z of data, vol, 0x7D00, 0x7918, cb, rec, 0, 0x400 / 0x800 / 0, b5 * 50). Skipped in replay unless type 0xA with no end event |
| 8 | music: b4 0 func_1000D96C (not in replay when func_1000E134 says playing), 1 func_1000E588, 2 func_1000DF68, 4 span -> func_1000E588 (replay) / func_1000E46C, 6 func_1000DF68 with span >= 1, 8 func_1000E654, 9 func_1000DE1C |
| 2 | object animation by id with blend (obj +0x2D0 anim state; func_1505E650 twice; skip-blend when D_800C40AE >= now or replay) |
| 5 / 1 | screen fade colour D_800844A0[b5] -> func_1517F3B0 (+ D_800C40AA); in replay the last fade event (func_15023EC4) |
| 5 / 4 | obj kind 0x4B: func_1503DE70(obj, 2, b4 - 1 or -1); replay: func_15060F28(obj, 1) |
| 5 / 0x5C | func_150F59A0 fade (never reached: handler A returns 1 for 0x5C first) |
| 5 / 0x56, 0x76, 0x2D, 0x57 | func_1517946C, func_151D6CA0, func_15188EBC / func_15188D80 / func_15189040, func_15155D6C / func_15156500 |

Still-asm callees (producer-first blockers): **func_1000FA64** (init_EB00, 109), **func_15023988** (the sound callback,
51190, 182), **func_15023EC4** (51190, 314), func_15188D80 (game_eu_1B6590, 79), func_15060F28 (game_83300; C on
port-b). Level 0x21 scene 1 uses types 6 (ids 0x105, 0x1A2, 0x3A2, 0x447), 0xA, 2, 8 and 5 / 1 here, so the sound
callback chain should be converted together with this function.
