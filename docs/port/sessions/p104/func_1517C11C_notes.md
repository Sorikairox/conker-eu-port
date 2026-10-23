# P104: func_1517C11C (game_eu_1A9280.c) - draft, NOT committed

Brief said ~320 instructions; it is **1286** (0x1517C11C..0x1517D530), 11 callees (allocate_memory, cosf, sinf,
func_10003C6C x2, func_10004074, func_100043B4, func_10004514, func_150AD9A0 x3, func_15170A70 x3, func_1517BE0C,
func_151EFDD0 x4) and one indirect callback (D_8008D25C[D_8008D2A0[...]].fn).

What it is: the ambient emitter system (fires / torches): 14-byte records *D_800DE148 (D_800DDD20 of them) sorted by
x or z; binary search for the near edge of (x, z) +- radius along the axis the camera angle picks; for each emitter in
range: nearest distance per voice (D_800DE070), voice load (D_800DD478 slot, 26 words) or mark heard
(D_800DDA90[voice].+0xC = 1 -> **the producer func_1517E3CC needs**), flare-up states (+0xB 0x21/0x22, func_15170A70),
one camera-facing 4-Vtx quad per emitter in D_800DDD10[D_800BE9C0] (allocate_memory), D_800DE188 = count; phase
animation per voice (D_800DE0C0, ping-pong / wrap, random flips); random spark; quads turned to cos/sin(angle).

Draft `draft_7c11c.c` (void return; the file's NM prototype was changed to void, uncommitted): difftest 100 random
trials EQUIV (81 ok / 19 inconclusive) but random inputs rarely enter the emitter loop (205 calls in 81 trials).
Needed before commit: knob setups (table at heap, D_800DDD20 / D_800DDD0C, RET allocate_memory=heap, RET
func_150ADE80 (= func_150AD9A0 jal key) sequences per emitter, voice slots, D_800DE0B0 / phases, D_800BEAC0=0 with
D_800DE000 periods, func_151EFDD0 sequences) and mutants.
EU addresses (all checked from symbol files): D_800DE188 800DE188, D_800DDD20 800DE150, D_8008D254 8008D254, D_800DE148
800DE148, D_800DE070 800DE070, D_800DDD0C 800DE13C, D_800BE9C0 800BEDE0, D_800DDD10 800DE140, D_800DD478 800DD8A8,
D_800DDA90 800DDEC0, D_800DDFF0 800DDFF0, D_800DE0C0 800DE0C0, D_800DD8A0 800DD8A0, D_800DE0B0 800DE0B0, D_800BEAC0
800BEEE0, D_800DE000 800DE000, D_800DDC04 800DE034, D_800DDC08 800DE038, D_800DE040 800DE040, D_800BE9E4 800BEE04.
jal keys: allocate_memory 10003E90, func_10003C6C 10003EBC, func_10004074 100042C4, func_100043B4 10004604,
func_10004514 10004764, cosf 15047EF0, sinf 15048050, func_150AD9A0 150ADE80, func_15170A70, func_1517BE0C,
func_151EFDD0 (same as names).
Producer chain: func_1517BE0C (asm, the sort) is called by it when the axis changes; *D_800DE148 itself comes from
the level loader (not checked). m2c raw: port_work/p104/raw_7c11c.c (needs pycparser 2.22: `pip3 install --target
/tmp/p104py pycparser==2.22` in the container, PYTHONPATH=/tmp/p104py).
