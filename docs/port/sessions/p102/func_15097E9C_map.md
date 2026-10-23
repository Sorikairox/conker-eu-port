# func_15097E9C map (P102)

`s32 func_15097E9C(s32 id, s32 cmd, s32 *args)` — game_eu_C5530.c, 2146 asm words (C56AC..C7830), frame
0x128. Object **command** handler of the script dispatcher func_1509BE40 (handler table D_80088838, ids 0x2xxx;
func_1509A024 next to it is the matching *query* handler). `args` = D_800D3380 = {id, cmd, x1, x2, ...},
`args[2]` = first extra word, D_800D3C60 = number of words.

## Blocks

| block | asm | what |
|---|---|---|
| entry | 7E9C..7EF4 | obj = func_1505EEF4(id) (jal 1505F2A0); NULL -> return 0; `cmd - 1 < 0x8E` -> jtbl_8009E320 (142 words, `jt1.txt`), else return 0 (A004) |
| cases | 7EF8..A000 | one block per case; nearly all end in `b A00C` (v0 = 1) or `b A010` with v0 = 1 |
| inner switch | 9A84..9C30 | cmd 0x78: `(u32)args[2] < 6` -> jtbl_8009E568 (6 words, `jt2.txt`), else return 1 |
| exits | A004 / A00C / A010 | return 0 / 1 / v0 |

Jump-table targets shared: 0x0C = 0x0D (xz speed), 0x52 = 0x5E = A00C (no-op, return 1). Every case 1..0x8E
exists (140 distinct targets).

## Cases (cmd: effect; "fix" = args / 65536.0f; rec = obj +0x31C)

- flags: 01 +0x25C |= / &= ~args[3] by args[2]; 02 |=8; 03 &=~8; 04 |=0x10; 05 |=1; 06 |=4 then &=~1; 0A &=~4;
  1B +0x9C (args[2]==1 set, else clear); 36 rec+0x20 (u8); 3D +0x94 (0: = ~(args[3]|1), 1: clear, else set);
  40 +0xF8; 50 +0x74 = args[2] | (+0x74 & ~args[3]); 6A +0x101 bit 0; 6B +0x101 (==1 set); 70 rec+0x128
  (args[3] selects); 75 +0x2F8 (u16); 1E +0x2FA bit 7; 1D +0x89/+0x8A/+0x83 = 0xFF or 0.
- position / motion: 08 x/y/z = (f32)args (0x7FFFFFFF keeps); 09 position = point args[2] (func_150871B8 ->
  func_1508712C into obj+0x14..0x1C); 0C/0D +0x3C, 0E +0x20, 0F +0x24, 15 +0xB8, 16 +0x48, 1C +0x154..0x15C (fix);
  5F +0x44 = min(+0x44, (f32)args[2]); 41 +0x1CC, 48 +0xD0 / +0x114, 8E +0x180 ((f32)args); 22 +0x2D8[i] fix
  (0x78000000 keeps), 23 +0x2E4[i] (0x7FFFFFFF keeps), i < D_800D3C60 - 2.
- angles: 10 +0x76 = +0x7A = u32(fix * 182.04445) - 0x4000 (IDO f32->u32: negative -> 0xFFFFFFFF);
  11 same from args/256 without the offset; 12 +0x78 = u32(args / 256).
- scripts: 14 / 60 / 35 set +0x232 (60: +0x211 = point args[2], +0x20F = 0xFF, +0x25C &= ~0x800), D_800D154C =
  obj, D_800C3E78 = object number, +0x218 = func_1507BB28(0, script), +0x21C = 0; 07 D_800D154C = obj,
  func_1504BAF0; 82 func_1507D1D8 with D_8009015C = 0 (saved / restored).
- 34: random spot 1800 in front of the camera D_800DBFF0 (+0x2F8 / +0x300, yaw +0x3A0, sinf / cosf,
  func_150ADA20 % 800 - 400), mirrored into the box args[2..5], floor height func_1510ED24(.., &y, .., x, y0, z,
  y0, 0, 0, -10000, 20000) + args[6].
- 71: random point around (args[2], args[3]): angle func_150ADA20 % func_15048AD0(lo, hi) + lo (degrees, args[6] /
  args[7] put in order in place), distance args[4] + rand % (args[5] - args[4]); x = c + sin * -d, z = c + cos * -d.
- paths (D_800D2104[obj +0x13F], 8-byte points): 43 point args[2]+1 = args[3..5]; 44 = position of point args[3].
- object table D_800CC2D0 (25 x 0x32C, end D_800D121C): 62 / 63 / 64 / 65 func_15085710(number, 10 / 9 / 2 / 3,
  ..) for numbers < D_8008FD8C (62 / 63 also D_800BE804 = func_150859AC(number, 6); 64: 0x33 when !D_800BE616 &&
  D_800E9D00 & 0x200); 55 numbers < 4: button bit 0x4000 in D_800BEB30[n] and *D_800BE728[0][n]; 85
  func_1507D4F8(number); 8B func_1517F3B0(args[2..6], number) when number <= D_80082FA0; 8D func_15060F28(o, 0)
  for live objects of kind 5 (+5) with +0x124 == number + 1; 4E / 7A grab entity args[2] (func_15083E90):
  +0x65 = its number + 1 (4E: +0x101 |= 4 unless args[4], +0x5C = args[3]) / +0x13C = its number + 100, speed 0,
  func_1505959C(it, number).
- record rec: 24 (0: func_1507EF0C, rec+8 = 0, +0x16 = 0; else rec+8 = 1, 1: func_1507EB4C(0x15), 2: (0x2A),
  +0x16 = 0xFF); 25 rec+8 = args[2], +0xE = 0xA6; 27 func_15080A20(id, 1, ..) and rec+0x78 = 0 with 3 words and
  args[2] == 0; 3B rec+0x32 |= args[2], 4 words: rec+0x34 = args[3]; 3C rec+0x1A = !!args[2]; 61 rec+0x8C
  (-1 -> 0x8000), +0x8F = 0, and for -1 / 4 / 0x2000 +0x8A, +0x8E = 2; 72 rec+0x129 (no rec: obj+0x222); 76 rec
  +0x1AE when rec; 79 rec+0x7D = !!args[2]; byte stores rec +0x76 (28), +0x7B (45), +0x1B (47), +0x4A (51),
  +0x31 (74), +0x1AF (7B), +0x7C (7E), +0x4E (84), +0x11A (8C).
- byte / half stores obj: 0B +0x13D, 13 +0x125, 18 +0x247, 1A +0x20A, 29 +0x251, 2D +0x21E, 30 +0x104, 31 +0x239,
  32 +0x10A, 37 +0x1E4, 38 +0x232, 39 +0x221, 3F +0x8A, 42 +0x246 = args >> 8 / +0x249, 46 +0x234/236/237, 49
  +0x1C9, 4F +0x3B, 53 +0x89, 56 +0x65, 57 +0x21C (h), 58 +0x140, 59 +0x20B + args[3], 5B / 5C / 5D +0x211 /
  +0x20F / +0x212 = point args[2] (0xFF if < 0), 68 +0x10 (h), 6E +0x6C + args[2] = args[3] + 10, 6F +0x68 +
  args[2], 73 +0 (word), 7C +0x23E, 7D +0x328 = args[2] + 1, 7F *(u16 *)(+0x144), 81 +0x275, 83 +0x238, 86 +0x23D,
  89 +0x22E (h), 8A +0xA4..A7 / +0xA0; 19 +0x222 = func_15084000(args[2] & 0xFFFF0FFF) (negative: as is, -1: none).
- globals: 20 +0x1CA, 4 words: D_800D2456 = D_800D2457 = args[2]; 2E D_800BEB30[args[2]] and *D_800BE728[0][args[2]]
  = args[3]; 33 D_800D1898[args[2]] = fix; 69 D_800D18C0 |= args[2]; 77 D_800C4414[0..2] = args[2..4].
- calls: 17 func_1518C000(obj, 0xFF, 0) / func_1518C164(obj); 1F func_15085880(obj, args[2] & 0xFFF); 21
  func_15085710((s16)id, (s16)args[2], args[3]); 26 func_15080A20(id, 0, args[2], 0); 2A / 2B func_1505D024(obj,
  args[2], (u16)args[3], -1 / args[4]); 2C func_1505D1C4(f args[3..5], args[2], args[6], args[7], 0, 0); 2F p =
  func_15072208(obj, args[2]): 0 func_15062BDC(obj, fix, fix), 1 func_1505E650(p, (u16)args[4], fix, fix, 0, 0, 0),
  2 p+0x218 = 0, p+0x232 = args[4]; 3A func_15062BDC(obj, f, f); 3E func_1503DE70(obj, args[2], args[3]); 4A
  func_1507EB4C; 4B func_15083568(obj, args[2], 0.0f, 0); 4C func_150836CC; 4D p = func_15031C4C(obj, a2, a3),
  p+0x38 = args[4]; 54 func_1506160C(obj, 1, a2, 0, 0) with 3 words, else (obj, 2, a2, a3, 0); 5A
  func_15173298(obj, -1); 66 func_150432CC(obj, a2); 67 func_15042D78(0), 2 / 3 player modes (D_80082FA0):
  func_150432FC((n & 1) * 150 + 10, (n >> 1) * 115); 6C 9: func_150637B4, 0x3B: func_15063920; 6D 9:
  func_15063894; 80 func_15063254(obj, a2, a3, args[4] * 0.01f); 87 / 88 func_1507CD64(obj, 0xF / 9).
- 78 inner switch on args[2]: 0 func_15083568(obj, 0x79, 0, 0), number < D_80090130: rec+0x4E = 2,
  func_1505E650(obj, 5, 1, 0, 0, 0, 0); 1 func_1514E404; 2 rec+0x17 = 1, +0x1C9 = 6; 3 func_1505EEF4(args[3] &
  0xFFFF0FFF): rec+0x4E = 1, func_15052F9C(it, 50, 0x17, 4, 0, 1, 0, 0, 1, 0); 4 func_15193660 / func_151937F4 /
  func_151D71AC(obj, 0xFF, 1); 5 func_1505E650(obj, 0x16, 1, 0, 0, 0, 0).

## State read / written

Read: args[0..11], D_800D3C60, the object (+0..+0x328) and its rec (+0x31C), D_800CC2D0 objects (8D), D_800DBFF0
camera (+0x2F8..0x300, +0x3A0), D_800D2104 path table, D_800BE728 pointer table, D_800BE616, D_800E9D00, ROM data
D_8008FD8C / D_80082FA0 / D_80090130 / D_8009015C. Written: obj / rec fields above, D_800D154C, D_800C3E78,
D_800BE804, D_800D2456 / 57, D_800BEB30, D_800D1898, D_800D18C0, D_800C4414, D_8009015C (restored), args[6] /
args[7] (cmd 0x71), path points.

## Producers before consumers

Values this function reads that a still-asm function produces (port: weak stub returning 0):
- **func_1507BB28** (game_A28B0.c, 59 words, asm-only): the script pointer stored in obj +0x218 by 14 / 35 / 60.
  With the stub, +0x218 = NULL and the script runner reads the null zone (P72 pattern). Draft
  `func_1507BB28.c` here (EQUIV). game_A28B0.c's NM code (func_1507B... line 423) already consumes it.
- func_150ADA20 (game_DAE50.c, asm): provided natively by port/boot/pc_overrides.c — not a stub.
- Return values not used: func_1505D024, func_150836CC, func_1507CD64, func_15083568 (all asm, called for effect).
- Caller / args producer func_1509BE40 (game_C8950.c) and func_1505EEF4 are C.
