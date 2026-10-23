# P104: level event system (browser P103 blocker) - drafts and map, NOT committed

Unit (producers before consumers, commit together): func_1509CBD4, func_1509B950 (+ func_1509B8FC returns it),
func_1509B5AC, func_150ADFD0 (VM), func_150ADA20, func_150AE760. P104 stopped at the VM, so none is in src_eu.

## Drafts in `ev/` (difftest, 100 random trials, current harness)

| function | file | draft | result |
|---|---|---|---|
| func_1509CBD4 | game_eu_CA630.c | ev/func_1509CBD4.c | EQUIV (15 ok / 24 inconclusive, recursive; needs knob setups: D_800877D0 rec +0xC list, D_800D2E4C bits) |
| func_1509B950 | game_C8950.c | ev/func_1509B950.c | EQUIV (63 ok) - the commented P-old draft, uncommented |
| func_1509B5AC | game_C8950.c | ev/func_1509B5AC.c | EQUIV (69 ok). Draft returns `int` and calls func_1509B8FC through a cast only because the TU has an implicit declaration (func_1509B4A0 calls it first) and a `void` func_1509B8FC. Commit as `struct249 *func_1509B5AC(s32, s32)` with a prototype above func_1509B4A0, and func_1509B8FC (NM only) as `struct249 *func_1509B8FC(s16)` returning `func_1509B950(temp_v0)` |
| func_150ADA20 | game_DAE50.c | ev/func_150ADA20.c | UNVERIFIABLE in difftest: the reference uses ld/sd/dsll32 (64-bit), every trial faults in Unicorn MIPS32. Check by hand / native test against a few known states (P95's random-float helper in game_DAE50.c uses the same step) |

Still missing knob setups + mutants for all four (P104 ran out of budget).

## func_150ADFD0 (game_eu_DB7E0.c, 485 insns): hand-written assembly, not compiled C

- Prologue saves ra, s0-s7, **gp, fp**, f20-f30 and stores **sp in D_800D3858** (`sw $sp, D_800D3858`).
- a0 = event block (struct_eu_C8950_blk: +8 offset of ?, +0xA offset of variables -> s2 = blk + unkA, s3 = blk + unk8),
  a1 = entry kind (0..4): `jtbl_80088960_game[a1]` picks the start pc: kind 0 -> blk + 0x20, others blk + u16 at
  +0xE / +0x10 / ... (s1 = pc).
- Clears D_800D3C60 and D_800D3C64 (D_800D3C64 = native handler pointer called via `jalr $v1`, 2 sites).
- s4 = s5 = D_800D3C80 + 0x17FC (an operand stack growing down?).
- 5 jump tables (jtbl_80088960 / 74 / 90 / AC / C8) = opcode dispatch, 5 `jr $v1`, 13 `jr $ra`.
- Data: D_800876F8, D_800887C0, D_800887FC, D_80088838, D_80088874, D_80088A44 (opcode tables?), D_800BE9A0,
  D_800D3C68 / 6C. One call: func_150ADA20 (random opcode).
- **func_150AE760 is not a function**: its first 6 instructions (E760..E774) load sp from D_800D3858, clear it, and
  branch to .L150AE58C inside func_150ADFD0 (the VM's exit path). It is an abort / longjmp out of the VM, called by
  native handlers. E780.. is a separate C function (func_150AE780: unk178 / unk17C += rate * D_800BE9A4,
  func_15144B68 wrap, unk20 / unk28 = sinf(...) * const, returns 1).
- Port design needed: the VM as a C interpreter loop (state in a struct, pc / operand stack / variable base), and the
  abort as setjmp/longjmp (or a flag checked after each native call). The rule on mechanical translation (asm2c_hand)
  allows it only for hand-written asm - this qualifies, but a readable interpreter is preferred.
- jump tables are not in tools/eu_port/m2c/rod (m2c fails); read them from conker.eu.bin at 0x80088960.. (EU = US
  names here? check the lui/addiu words).
