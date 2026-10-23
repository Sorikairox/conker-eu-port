# func_1512EE50 map (P111)

`camera_apply_request` (game_eu_15C660.c, 1352 insns, frame 0xD8). Called by func_15122C5C (game_14FF90.c) with
one argument (the camera); that file declared it `s32`, the asm leaves no return value -> declared `void` now.

## Layout used

- Camera `p` (struct108). Request record `req = p + 0x6FC`: mode s32 +0, id s16 +4, argument s32 +8, point s16
  +0x10/+0x12/+0x14, values A u32 +0x1C (low byte +0x1F = object id for modes 0xA/0xE) and B u32 +0x20 (converted
  as unsigned: cvt + 2^32 when negative), saved s16 +0x34.
- State `st = p + 0x6CC`: active s16 +0 (= p+0x6CC), last id +2, applied mode +4, pending +6, easing +8, blend f32
  +0x10, push rate +0x14, point x +0x18 / z +0x20, values +0x24/+0x28/+0x2C.
- Eye p+0x2F8/2FC/300 (0x2FC = eye height, the P105 camera bug), target p+0x2A4/2A8/2AC, look-at p+0x618..620,
  distances +0x374/+0x348/+0x34C, smoothing velocities +0x8F4/+0x8FC/+0x904, rates +0x908/+0x90C (targets
  +0x910/+0x914, velocities +0x918/+0x91C), flags +0x920 (u16), +0x92C / +0x948 bytes.

## Flow (asm addresses)

| asm | what |
|---|---|
| 1512EE64..EEA0 | return if +0x2C & 0x100, +0x73C, (after func_151239CC(p, 0xD)) +0x2C & 0x40000 |
| EEA4..EEFC | new request id: clear +0x92C, st+6, copy id, func_151239CC C/D/2/7 |
| EF00..EF54 | pending if mode != 4 and (+0x3D4)->0x120 and !+0x92C; pending -> func_151239CC(C) |
| EF58..EF98 | active && !pending && !easing: st+4 = mode, func_15130370(p, arg) unless mode 0xA |
| EFB0 | mode 4 hold |
| EFD4..F588 | mode 7 node graph (D_800D2778, func_15086268 node, links +9..+13, closest point by func_15048F90 / 150491EC / 150ADDE0 / 15049148 / 15048F20); func_15123934(.., 0xC); eye eased by func_150498A0; **0x2FC stored at F4DC** (snap) or through func_150498A0 at F500 |
| F58C..F7A0 | mode 5 fixed position record D_800DC450 + A*0x18 (D_800DC454) |
| F7A4..F81C | mode 0xB |
| F824..FAC8 | mode 0xA / 0xE look at object (func_15083E0C, func_1505EEF4, func_151254F4, sinf / cosf) |
| FAD0..FB20 | mode 0xF func_1512DD50 |
| FB28..FC28 | mode 3 |
| FC2C..FDB4 | mode 2 (func_1512E6B0, func_150AD78C / 780, **func_15128D50** stub) |
| FDB8..300A0 | modes 1 / 0 (func_15124C38) |
| 300A4..300CC | mode 0xD |
| 300D4..30358 | settle + reset to mode 0xD (func_151239CC 1/C/D/2/7) |

Rodata: D_800A3B20 1e14, B24/B28 0.017453292, B2C/B30/B38/B40 0.04, B34 0.005, B3C 0.0025, B44 0.01, B48 0.015
(read from the ELF, equal to the literals in the C).

## Callees and port status (port-web asm_stubs.c, c9daf10)

All C (or hand asm handled by the port) except **func_15128D50** (game_eu_156560.c, not a port-b file): called only
in mode 2, after all the camera writes; it is already a hit stub from func_15122C5C / func_15128030 per frame
(596). func_15123934 / func_151239CC / func_151254F4 / func_1505EEF4 are still asm in port-b's tree but C on
`port`. No table dispatch. func_15130370 (same file) is C.

## Verification

- 100 random EQUIV; 120 setups `ee50.txt` (genee50.py: all modes, random flags, node graph, records, objects;
  OUTA / OUTW on the closest-point callee) EQUIV x4 trials; mutants: `ee50_mut.txt` (results in P111.md).
