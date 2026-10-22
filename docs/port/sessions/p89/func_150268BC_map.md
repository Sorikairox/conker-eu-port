# func_150268BC structure map (P89)

`game_eu_51190.c`, EU 0x150268BC..0x15029EA4 (ROM 0x540CC), 3594 asm lines, frame 0x750, 183 jal, 4 jump tables
(jtbl_80096F94 / 80096FB0 / 80097040 / 8009709C). Still GLOBAL_ASM. Draft: `draft_268bc.c` (not compiled, not tested).
Reading aid: `port_work/p89/m2c_268bc.c` (raw m2c, only for reading; never paste it).

## Role

Middle handler of the cutscene / script-event dispatcher func_1502AB94 (P86): `s32 func_150268BC(s32 ev, u8 track,
u16 value, s32 now, s32 player, struct127 *obj, u8 *rec, u8 *data, s32 flag)`. `ev` points at one 8-byte script event:

| off | type | meaning |
|---|---|---|
| 0 | s8  | event type (0x0B sound, 0x11 table byte, 0x05 effect; anything else -> return 0) |
| 1 | u8  | delta (used by func_15023C60) |
| 2 | s16 | id: sound id (0x0B), table index (0x11), effect sub-type (0x05) |
| 4 | s8  | b4: 0 = start; other values = stop / variant (most effects only run when b4 == 0) |
| 5 | s8  | b5: variant / colour set / bone index |
| 6 | s16 | w6: volume / duration / parameter |

`span = func_15023C60(ev, ev->type, track, &next, 1, ev->id, 0, 0, 0, 0, player) - now` = frames until the next
event with the same type and id (the effect's duration). Every sub-type computes it with its own out slot (sp740,
sp738, ..., sp10C); the out pointer is never read back. Variants: type 0x0B uses `(1, id, 1, 2, 0, 0)`, sub 0x65 uses
`(1, id, 1, 1, 1, b5)`, sub 0x48 uses `(1, id, 0, 0, 1, b5)`.

`rec` in the effects below means `&D_800C3958[player][track]` (struct233, 0x44 bytes: pos 0/4/8, angles 0xC/0x10,
0x18, 0x1C, 0x20, 0x30, 0x38 height). `data` (arg7) is a position (f32 x, y, z) = rec or obj + 0x14. `flag` (arg8) is
passed on as `(u8) flag` almost everywhere.

Return: 1 for every handled event (shared exit .L15029E94), 0 for an unknown type or sub-type (sub 0x05 chain falls
out at the end -> `return 0` at .L15029E90).

## Top level

1. type 0x0B (sound): b4 0: func_1001263C(id, w6 ? (w6 << 16) / 255 : 0x10000, 0x40); b4 1: span (variant 1,2),
   func_151F2D6C(w6 ? (w6 << 16) / 255 : 0x10000, span * 0x5604 / 50); b4 3/4/5: func_151F2BA8 / BE8 / C4C (void
   in their C; m2c shows (ev, 0x40) left in a0/a1). Return 1.
2. type 0x11: `D_800C3D80[player][track][id] = b4 ? (u8) value : 0xFF` (u8 *table[4][30], byte offsets 0x78 / 4).
3. type 0x05: if-chain on `id` (compiled order below); every branch returns 1 except the final fall-through (0).

## Type 0x05 sub-types (compiled order)

| id | condition | does |
|---|---|---|
| 0x11 | b4 == 0 | colour set D_800844D8[min(b5,<3)] (3 x 6 bytes, copied to sp6FC), size w6 (0 -> 0x1000, <= 200 -> 200); func_1516DF0C(49 args: a0/a1 = (s16)(data >> 16) / (s16) data = the *pointer halves*, as on N64) |
| 0x0A / 0x0B | b4 == 0 | func_151BA1A0(3,3,0,0,0,800,1200,400,200,0x66,0x1C7,2,span,data,flag,0) / (0x2F,1,0,0,0,2000,1000,400,200,0x400,0x400,6,...) |
| 0x0C | - | local struct {D_8008CDF0, (s16)x, (s16)(y + b4), (s16)z, 0, 0x100, 1500, 1500, -10, 0} -> func_15167AD8(&s, flag, 1) |
| 0x19 | b4 == 0 | func_15177F90(b5 ? b5 : 12, data, 0xFF, (s32)x, (s32)y, (s32)z, 0, span, flag, 0, w6) |
| 0x1A | b4 == 1: func_150B0574(&{D_eu_800C3C88[p][t] s16 x3 as f32}, &{rec x, rec y + rec->0x38, rec z}, flag, 1); else func_150E2030(0, those 6 floats, 40, 0, 8, 60, 600, 35, 0 x10, 0.0 x6) |
| 0x1C | obj | b4 0 -> 3, b4 1 -> 2: func_150E3334(obj, obj->0x3B, n, -1, 0, 0, 156, 0, 0, 636, 3, 10, 0xF0, 0); other b4: nothing |
| 0x1B | b4 == 0 | switch (u16) w6: 0 func_1516ECE8(data, span, b5, flag, 0); 1 func_150BF47C(span); 2 two func_1516FAB8 (obj pos + 20/475 and -24/476, sin/cos of obj->0x7A >> 8 via func_15048A40 / func_150489B0); 3 / 4 func_151DCE6C(data, (s16) span, 1,1 / 0,0, flag, 0) |
| 0x1F | obj | func_150BA4C0(obj, flag, 1) |
| 0x00 | obj | func_151A3940(obj, flag) |
| 0x20 | - | func_151664F0(-1, (s32)x, (s32)y, (s32)z, 20, 20, 1, flag, 1) |
| 0x06 | - | nothing (return 1) |
| 0x07 | - | func_150B2974(obj, 9, -1) |
| 0x21 | b4 == 0 | func_15136A50(data, data + 4, data + 8, (s16) span, flag, 0) |
| 0x60 | b4 == 0 | func_150CE660(obj, (s16) span, (u8) flag, **0**) (4th argument 0, P80) |
| 0x65 | | b4 == 2: b5 0x11/0x12/0x15 -> func_151494E0(&(s8) w6, 0x51); 0x13 -> func_150D0148(w6 * 0.01 * 300 - 150, ...). b4 == 0: span (variant 1,1,1,b5), switch b5 1..26 (jtbl_80096FB0, table below) |
| 0x5B | b4 == 0 | func_151B57F0((s16) span, flag, 0) |
| 0x5D | b4 == 0 | func_151932B8(obj, (s16) span, flag, 0) |
| 0x5E | | b5 == 1: func_151B09BC(obj, 0, 1000, flag, 0); else b4 == 0: same with (s16) span |
| 0x4C | b4 == 0 | obj kind (obj->4) 0x49 / 0x58: list = func_151905AC(obj, &n); if list && w6 < n: func_1518FA8C(obj, list[w6] (byte), (s16) span, -1, -1, -1, 0, 0, flag, 1); other kinds: func_1518D1C0(obj, b5, span, 0, flag, 1, "Cutscene 2") |
| 0x53 | b4 == 0 | local {data, data + 4, data + 8, (s16) span, 1, 2, 2.0f, 1.0f} -> func_15134908(&s, 0, flag, 0) |
| 0x50 / 0x51 | b4 == 0 | func_150EA560 / func_150EAA80(obj, (s16) span, flag, 0) (PROTO CONFLICT: callees declare arg2 f32) |
| 0x48 | b4 == 0 | span (variant 0,0,1,b5); random offsets (func_150ADA68 x5, func_150ADA20 x2) -> func_151356D4(12 args) |
| 0x0F | b4 == 0 | func_150C7520(obj, span, flag, 1) |
| 0x3E / 0x3F | - | nothing |
| 0x32 | b4 == 0 | func_150DBA98(data, rec + 0x10, rec + 0x18, rec + 0x1C, rec + 0x20, span, flag, 0) |
| 0x34 | b4 == 0 | idx = 13 when b5 >= 0 (uninitialised stack byte when b5 < 0); walk obj->0x2F4 list (next +0x14): node->0x1C == idx or func_1514DA28(D_8008AF88[idx]->4, node->0x1C) -> node->0x10->0x30 = func_1519EEE0((s16) span, node->0x10, 0, rec + 0x30, rec + 0x20, flag, 0) |
| 0x23 / 0x22 | obj, b4 == 0 | func_1516F868(obj index, span, span, 0, flag, 0) / func_1516F730(obj index, span, flag, 0); obj index = (obj - D_800CC2D0) / 812 |
| 0x52 | obj | func_15136404(obj, 90.0f, flag, 1) |
| 0x5F | (u8) b4 < 23 | switch (u8) b4 (jtbl_80097040, table below) |
| 0x40 | - | func_151A0A10(obj, 0x28, flag, 1) |
| 0x4D / 0x4E | - | particle struct on the stack (random count func_150ADA20 % 5 + 5 / % 6 + 6, data pos, constants) -> func_151A74B0(&s, 1, flag, 1) |
| 0x4F | - | struct -> func_15154488(&s, &pos, 0, flag, 1) |
| 0x24 | - | func_151DBAA8(&pos, b4 ? b4 : 10, (u8) b5 < 13 ? b5 : 0, flag, 0) |
| 0x10 | - | func_151AFA80(obj, (u8) b4 < 27 ? b4 : 0, flag, 0) |
| 0x47 | - | func_151925C4(obj, 0x32, flag, 0) |
| 0x2E | - | func_150C1F60((u8) flag) (asm; a1/a2 leftovers), func_150C2290(flag & 0xFF), func_150C2424(flag & 0xFF) |
| 0x31 | - | func_150DB3F0(obj, 0, flag, 0) |
| 0x33 | - | func_1514948C(rec->0x1C * 0.1, 0.7111111, min(b4, 15), x, y, z, (s32)(rec->0x20 * 0.05), (s32)((rec->0x10 + 180) * 0.7111111), (s32)(rec->0xC * 0.7111111), rec->0x38 * 0.1 + 0.5, b5 ? b5 : 100, rec->0x18 * 0.1 + 1, same as arg0, flag) |
| 0x35 | - | func_150DBF60(obj, b4 >= 2 ? 1 : b4, flag) |
| 0x26 | obj, b4 == 0 | obj->0x276 = 1; obj->0x282 = span |
| 0x27 | - | func_1518B7D4(data, w6 >= 0 ? w6 : 30.0, b5 ? b5 * 0.1 : 1.0, b4 ? b4 : 1, flag) |
| 0x02 | - | func_1518B818(data, same floats, b4 ? b4 : 1, 30, 100, flag) |
| 0x28 | - | rec ? func_15171B70(rec, flag, 0) : obj ? func_15172164(obj, flag) |
| 0x29 | - | rec ? func_15171434(rec, flag, 0) : obj ? func_15171734(obj) |
| 0x2A | - | nothing |
| 0x2B | - | func_1518BC20(x, y, z, flag, 0) (m2c misreads the float in a2) |
| 0x2C | - | span only (result unused) |
| 0x2F | obj, b4 == 0 | func_1516F2D8(obj index, span, flag, 0) |
| 0x39 | b4 == 0 | func_150C2804(data, data + 4, data + 8, (s16) span, flag, 0) |
| 0x3A | - | func_151DBAA8(&pos, b4 ? b4 : 10, 6, flag, 0) |
| other | | return 0 |

### sub 0x65, b4 == 0, switch b5 (span = s16 below)

1 func_15109990(obj, span, -1, 0, 0.00071f, 0, flag, 1); 2 same with (1, 0.006125f); 3 / 4 func_1510A454(rec, span, -1, 0 / 1,
0.006125f, 0, flag, 1); 5 func_1510A8C4(obj, span, flag, 1); 6 func_151619A0(track, span, flag, 1); 7 func_1510957C(track,
span32, flag); 8 func_151A9940(5, 1, NULL, &pos(rec), -10000, 100, span, flag, 1); 9 struct {obj, (s16) span, obj->0x3B, 1, 0,
kind (obj->4: 0x57 / 0x71 -> 1, 0x96 -> 3, else 0)} -> func_15190770(&s, 0, flag, 1); 10 func_150F85AC(rec, span, flag, 1);
11 func_150AFC18(span, flag, 1) then r = func_15149130(span, -1, 0x4B, -1, 1, 0, (struct37 *) 4, flag, 1), if r: 4 zero bytes
at r + 0x28; 12 func_150F6188(obj, span, flag, 1); 13 func_1519F0FC(rec, (u16) w6 < 0xE9 ? w6 : 0, span, flag, 1); 15 obj &&
span32 > 0: obj->0x2EC = 1, obj->0x2D8 = span * 0.5f, obj->0x2DC = 1 / that, func_150C4620(obj, span, flag, 1); 16 obj &&
span32 > 0: func_150F6E10(obj, span, flag, 1) (PROTO CONFLICT f32 arg2); 17 / 18 / 21 func_150D0644 / 07C4 / 09D4(w6 & 0xFF,
D_800C3A00[player][w6], span, flag, 1); 19 func_150CFB90(span, flag, 1); 20 func_151925C4(obj, span, flag, 1); 22
func_1519F2F4(rec, (u16) w6 < 0xCF ? w6 : 0, span, flag, 1); 23 func_150FB398(span, flag, 1); 24 floor probe from rec + 100
down to rec y - 1000 (func_15046F70); hit and surface byte (+0x1D of the out struct) != 3 -> func_15136698(random sizes,
random alpha 0x9B..0xFF, 0xFF, span32, &out + 4, &pos, w6 == 0, 1, flag, 1); 25 func_150E38C0(&{s16 x3 of D_eu_800C3C88 as
f32}, &{rec pos as s32}, rec, span); 26 struct {1, span, 8, 1, -1} -> func_151D8E18(&s, 0, flag, 1). 14: no case (default).

### sub 0x5F, switch (u8) b4 (0..22)

0 obj: func_1504715C(&tmp, obj), floor probe from obj pos + 100 to obj y - 300, hit -> func_150CAE30(&{x, floor, z});
1 func_1510965C() (void); 2 obj by kind obj->4: 0x4A func_150E0C58(obj, b5, flag, 1); 0x5A / 0x74 / 0x75 / 0x7A
attachment 0x46 (func_15031C4C) -> func_1514654C(obj, att, 0, &D_800AAE70 ptr, &buf ptr, 1) -> func_151C5B38(obj, buf, 0x46,
flag, 1), func_151C5C54(buf, flag, 1); 0x86 func_150FB8A4; 0x97 func_150F9D6C; 0x98 func_150F9ED0 (each (obj, flag, 1));
3 func_151BEE00(&pos(rec), rec->0x10, 1, 0, 2, flag, 1); 4 func_151CFFFC(obj, flag, 1); 5 obj: att = w6 ? func_15031C4C(obj,
b5 ? 0xA4 : 0xA5, 0, 0) : 0; func_151C62D0(obj, b5, 1, att, b5 ? 0xA4 : 0xA5, flag, 1); 6 func_150BAEF4(obj, 9, -1);
7 func_150E0DF0(obj, flag, 1); 8 func_151D5BF8(&pos(data), flag, 1); 9 func_15136C3C(obj, 1, 1, 1, 1, 0, flag, 1); 10 obj->0x1D4:
offset tables D_80096DF8 (3), D_80096E1C (4), D_80096E4C (6) x 12 bytes, pick random entry by b5 (0: %3, 1: &3, 2: %6), bone
D_80096E94[b5] = {0x15, 0x20, 3}: func_15143134(entry, &out, obj->0x1D4 + bone * 64), func_151C384C(&out, flag, 1); 11 for i in
D_80096EA0 = {6, 7, 8, 9}: func_151C9CBC(1, D_800D34B8 + i * 0x34); 12 func_151080F8(obj, rand & 0xFF, (rand & 0x7F) - 0x40, flag,
1); 13 func_151CC840(D_800DBFF0); 14 func_1519EFE8(&pos(data), (u16) b5 < 0xE9 ? b5 : 0, w6 ? w6 * 0.01 : 1.0, flag, 1); 15 colour
{0xAE, 0xD2, 0xFF, rand % 61 + 150}, size rand*20+25 (x 0.35 when b5) -> func_15107C80(obj, rand & 0xFF, rand % 129 - 63,
rand % 21 + 10, 4, 40.0, size, 0, 2, colour, flag, 1); 16 func_150F1C5C(obj, b5, (u8) w6 low byte (ev + 7), flag, 1); 17
struct {1, 0x32, 8, 1, -1} -> func_151D8E18; 18 obj->0x1D4: D_80096EB0 (2 x 12) by b5 -> func_15143134(entry, &out, obj->0x1D4) (no bone offset), func_15132454(&out, 0.6460f (0x3F256042), flag, 0); 19 obj->0x1D4: D_80096EC8 (8 x 12, ROM) by b5, bone
D_80096F28[b5] (u8 {7,8,9,10,13,14,15,16}) -> func_15143134, func_15132454(&out, 6.990f (0x40DFAE15), flag, 0); 20 struct
{s16 rec x, y + 50, z} -> func_15171100(&s, 1, 1, 2, flag, 0); 21 obj: func_1507DE4C(obj), func_15138C80(obj, flag, 0);
22 obj: func_15193660(obj, flag, 0).

## Callee prototype conflicts (fix before converting)

The port calls through the callee's C prototype; a mismatch is a wasm signature trap. N64 behaviour per register:
- func_150EA560, func_150EAA80, func_150F6E10: C prototypes take `f32 arg2` but the caller puts `(u8) flag` in a2 and
  0 / 1 in a3. Check the callees' bodies: either their prototype is wrong (likely: `u8 arg2, s32 arg3`) or the float is the
  flag's bit pattern. Resolve in the callee's file first (protocheck).
- func_1510965C (void), func_1507DE4C (obj), func_15171734 (obj), func_151CC840 (s32), func_151C9CBC (2 args),
  func_15172164 (2 args), func_1504715C (2 args), func_151F2BA8 / BE8 / C4C (void): m2c shows leftover a1 / a2 values
  (0x34 = the multiply constant of case 0x5F/11, the type, ...); pass only what the prototypes take.
- func_1518BC20(f32, f32, f32, s32, s32): z goes in a2 as float bits (m2c shows `arg7`).
- func_1516DF0C: a0 / a1 are the two halves of the `data` pointer (sra / sll of arg7), a2 = 0. In the port this is
  garbage either way; keep it, mark it.
- asm callees without a C prototype: func_151356D4, func_150DBA98, func_1514DA28, func_150F9D6C, func_151CFFFC,
  func_151C62D0, func_150E0DF0, func_150F1C5C, func_15171100, func_150C1F60, func_150DB3F0, func_1514948C, func_150DBF60,
  func_150B0574, func_15177F90, func_1516FAB8, func_15109990, func_150F85AC, func_1519F0FC, func_150CFB90, func_151925C4,
  func_150FB398, func_150E38C0: declare from the call sites (arity from the asm), add to functions.h.

## Tests to write (next session)

Setups: one ev per (type, id) pair, poke the 8 bytes at a fake heap address (0x8048xxxx), RET func_15023C60 = now + k so
span is known, obj / rec / data in the heap (never 0x806xxxxx, P86; the harness now compares those exactly, P89). Cover
b4 0 / non-0 for each, every b5 of sub 0x65 and every b4 of sub 0x5F, obj NULL vs non-NULL, the 0x34 list walk (2 nodes),
the 0x4C list path. RET for func_150ADA20 / func_150ADA68 fixed values. ARGMEM on every struct passed by address (0x0C,
0x53, 0x4D/4E/4F, 0x65/9, 0x65/26, 0x5F/14/17/20, 0x5F/10/18/19 offsets).
