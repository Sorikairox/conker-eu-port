## Remaining work (in order)

1. ~~49 C functions that differ in EU~~: done. Findings:
   - 37 only lacked EU symbol definitions (the port marked them as differing because
     relocation targets were unresolved).
   - PAL changes: 300 -> 250, 2400 -> 2000, `/ 60` -> `/ 50`; debugger text width
     163 -> 19; `func_1509BE40(1, 0x4080, ...)`; `D_800BE5E0` is stored as s16 in EU
     (cast in `game_45B80.c`, the shared header still says u8).
   - Tables in `game_305D0.c` hold 7764 entries in EU (7762 in US).
   - `func_10005020` (`init_49E0.c`) blanks the VI once before the first swap
     (EU-only `D_eu_8002AFA8`, `D_eu_8002AE24`).
2. ~~14 US files not ported~~: done.
   - Shift-only: `game_A9D90`, `game_A28B0`, `libultra/audio/game_21FC90`,
     `libultra/io/ai`, `aigetstat`, `aisetfreq`.
   - `game_83300`: EU has a file boundary (16-byte padding) after `func_150627D4`, so
     `func_15062800`... live in `game_8FCB0.c` (named after its US rom offset).
   - `libultra/audio/n_cspgetstate`: EU builds it `-O2` (see the EU-only rule in
     `conker/Makefile`) and adds two empty functions, `ptstart` and `func_eu_10017D80`.
   - `init_1050`: `osInitialize()` is `__osInitialize_common()`, no `D_8002AC5C` check.
   - `init_39C0`: no VI mode setup; EU-only `func_10003C10` (0x210 bytes, PAL VI
     timing) is still asm.
   - `init_50A0`: no third message queue / `osViSetEvent`. Its `.bss` variable
     `D_8003B260` stays a tentative definition in the C file (needed for codegen) and
     gets its EU address from `undefined_syms.eu.txt`.
   - `init_214F0`, `game_D4C20`, `game_221290`: all GLOBAL_ASM; only placed.
3. ~~31 functions reverted in the salvage~~: all done (`func_151EF840` = `sqrtf` in
   session 5, own file `game_eu_21D050.c` built `-O2`).
4. **New decompilation** of the remaining ~3,350 asm functions (game is 38.7% by
   count but only 8.2% by bytes: the large functions are what's left). Use m2c
   (`tools/mips_to_c`), asm-differ, decomp-permuter, and decomp.me (IDO 5.3,
   `-O2 -g3 -mips2`; per-file flag overrides are in `conker/Makefile`).
   `check_funcs.py -v` is a quick per-function diff. Easy EU-only targets:
   `func_10003C10` (`init_39C0.c`).
   Next steps (session 15):
   - Hand-draft the callers of the fixed prototypes: `rescreen.py` lists them (375 asm functions call a
     changed function); m2c drafts of them are in no better shape, but the header is now right.
   - `func_150144B8` (DIFF4, `tools/decomp-permuter/drafts/func_150144B8c.c`): find why
     `tmp.unk1C *= D_80096A38` costs 8 bytes of frame (`stackfix.py --bisect`).
   - `func_100046E4` (DIFF2, frame 0x90 vs 0x80, `conker/build/stackfix` is wiped by verify_all; the
     permuter best is `nm/func_100046E4/best.c`): 16 bytes above `sp68`.
   - `func_150E0B78`: the permuter draft with the extern literals `D_800A13A0/A4` is DIFF14.
   - protocheck: report callers' argument counts (`callargs` is collected) and extra params
     (`func_150D03A8`); the 8 DEF leftovers need their C callers changed together with the prototype.
   - Session 14 next steps still apply (pass 4 rest, `sweep.sh gen 400`).
   Next steps (session 14):
   - Finish pass 4: the 68 unrun functions of `sweep/cand4.txt` (lines 91-158), 100 s each (~40 min).
   - Look at `func_150E0B78` (`nm/func_150E0B78/match.c`, REJECTed by apply.py).
   - Read the `PERMUTER CHANGED DECL` lines of the closest unsolved results first: a wrong callee
     prototype (`func_1515D4D4`) was the whole difference for a score-0 SIZE+1 result.
   - Pass-3 leftovers with best <= 50 (`sort -t= -k3 -n sweep/perm_cand3.txt`) by hand from `best.c`;
     5 of 7 tried this session matched within a few drafts.
   - `sweep.sh gen 400` (more drafts; native gen/screen are ~3.6x faster now).
   Next steps (session 13):
   - Hand-finish the score-0/score-1..5 permuter results listed in the session 13 section.
   - Test the `func_1000FA64` arg0 `int` prototype (permuter hint, 745 -> 160 for `func_150A28C4`).
   - Rerun `sweep.sh gen` with a larger max (200-400 instructions) or after naming structs; the
     <= 200 pool is now swept at 300 s. A longer pass (900 s+) over `improved.txt` entries with best
     score <= 300 not yet retried (ranks 55-75) is the cheap next permuter run.
   Next steps (session 12):
   - Write hand drafts for the session 11 near misses again (they were lost) and finish them with
     `permute.sh`; keep drafts in a persistent place (e.g. `tools/decomp-permuter/drafts/`, gitignored).
   - Run `permute.sh -l` over every SIZE±1/DIFF1-5 draft of a fresh `gen2.py` screen (session 6 noted
     ~250 SIZE±1 functions), 300 s each, 3 streams of `-j3`, overnight-style in the background.
   - Look at callee prototypes the permuter changes (`PERMUTER CHANGED DECL`): a wrong `void`/`int`
     return type in `functions.h` blocked 4 functions at once.
   Next steps (session 11):
   - Hand-write the remaining effect spawners (`spawngen.py` SKIP list, ~40): most are short,
     branchy and use the patterns above; the game_40490 ones (`func_15015354`, `func_15011D60`,
     `func_150124A0`) are larger.
   - Near misses of session 11 (list above), especially the DIFF1 operand-order cases.
   - Medium float/switch functions in owned files: drafts with `JT=1 ONLY=<list> gen2.py` (list:
     asm functions 30-300 instructions in owned files whose `.s` has a `rodata_inject` header; 224
     functions this session, 0 OK as generated), then natural C by hand; m2c only for structure.
   Next steps (session 10):
   - Spawners that call other functions first (~45, `spawngen.py` SKIP list): extend the
     interpreter (calls whose result is stored to a field, e.g. `func_15083E90`, function-pointer
     tables) or hand-write; add the `if (arg0 != NULL) { }` guard as a spawngen variant.
   - More .data ownership: list asm functions that copy from a game .data address (`addiu tX, tX,
     %lo(D_8008...)` followed by `lw $at, 0x0(tX)`; ~30 functions, see session 10) and own their
     files' .data. Files whose .data holds only data used by C can be written fully in C
     (`ptrtable.py` for pointer tables).
   - Solve the sp+0x24 local array slot in `game_36680` (`func_1500A6D8`, `func_1500A7E8`).
   - Medium float/switch functions by hand (session 9 advice still holds).
   Next steps (session 9):
   - Effect spawners with `m2c/spawn.py` (~40 left, see session 9), then other families that call
     the same helpers (`func_15160CDC`, `func_15169260`).
   - The 4 unresolved BOUNDARY files and the PADDING list of `rodata_bounds.py` (25 files; check
     with `rodata_inject.py --dry` whether a C function's late chunk runs over a data block).
   - Hand-write medium float/switch functions in owned files (list: asm functions whose `.s` has a
     `rodata_inject` header; `m2c/list.py` + filter by owned stems); write natural C first, m2c
     only for structure.
   Next steps (session 8):
   - **Rodata functions** (1299 asm game functions reference .rodata, ~300k instructions; the
     largest pool left): use the workflow in the session 8 section. Start with files that
     `rodata_bounds.py` does not flag; split flagged files first (US hints help). Hand-fix the
     lowest DIFFs from a fresh `JT=1 ONLY=<list> gen2.py` run (list: asm functions with a
     `%lo` of a game .rodata symbol, i.e. vram 0x80091DE0..0x800B11D0; see the near misses
     above). Functions over 400 instructions were not drafted yet.
   - **.data pieces**: everything before 0x237060 in `game_data` is now `databin`, so a game
     file can own its `.data` with `rodata_split.py <stem> <a> <b> --section .data` (ranges:
     `datarefs.py game --runs --hi 0x237060`). Not automated yet (no injection for .data of
     GLOBAL_ASM functions: only whole-C files or files whose .data is used only by C code).
     `init_data`/`debugger_data` still need their .data/.rodata boundary.
   - **Handlers**: ~200 functions with u8 params remain asm (`m2c/u8params.py`); the drafts in
     `conker/build/u` (regenerate with `m2c/u8run.sh`) are the starting point. Do the 1-case
     handlers with the patterns above; the 2-case ones wait for the unfilled-delay-slot puzzle
     (try: an empty statement/macro after the last store, a `do {} while (0)` wrapper, `register`
     locals, or splitting the file at different flags).
   - Finish `cosf` (session 7).
   - **Remaining libultra C**: `osPfsChecker` group (`init_eu_289A0` and `pfschecker2.c`),
     osLeoDiskInit (`func_10027B50`), the unidentified functions in `init_eu_26B30`.
     Handwritten asm (leave as is): `bzero`, `bcopy`, `__osGetSR/__osSetSR`,
     `__osSetFpcCsr`, `__osDisableInt/__osRestoreInt`, `osInvalICache/DCache`,
     `osWritebackDCache(All)`, `osGetCount`, `__osSetCompare`, `osMapTLB/osUnmapTLB`,
     `__osProbeTLB`, `osSetIntMask`, `sqrtf` (init copy), the `__ll_*` helpers (compiled
     with a different compiler), `func_10007D14` (`__osPopThread`, from exceptasm.s).
   - Game-side copies of libultra exist too (`game_eu_21D010`, `game_eu_21E320`); look
     for more `func_151E`/`func_151F` functions that call `__osDisableInt` or touch
     `0xA4xx` registers.
   - Near misses left (1-4 differing words): `func_150351A4 func_150C60D4 func_151A53E4
     func_1517A220 func_151CBAC0` (commutative operand order), `func_1511CAD0` (store/load
     order), `func_15144B68 func_150A7CB0` (instruction order), `func_151A547C` (flag
     spilled as a byte across a call), `func_150D03A8` (one stack slot),
     `func_1514EA78 func_1514EB28 func_1514EBD8 func_1514EC88` (`v1`/`v2` choice),
     `func_1509CEA8` (unrolled `for` loop, init order), `func_15142E24 func_15052260
     func_151C2600` (100+ instructions); session 7: `func_151597A0`, `func_151596F4`
     (multi-return float compares, SIZE-1), `func_151AEBF0` (delay slot only).
   - `func_151EF7B0` matches as C but is followed by 0x40 bytes of nop padding in its
     file (`game_eu_21CFC0`), more than the 16-byte object alignment; needs an asm
     padding block or a different file split.
   - `func_15173948` (`return arg0;` with an unused second arg) has its `jr ra` delay
     slot filled: its file (`game_eu_1A1060`) would need a split with `-O2`.
   - About 250 functions screen as `SIZE±1`; quick looks found single-instruction
     differences that resisted easy fixes (e.g. `func_150104F0`: `or v0, zero, zero`
     stored twice).
   - Naming structs (`struct127` objects, `struct_eu_node` lists, the message struct
     `{s32 old; s32 new; u8 b8, b9}`) would make m2c's drafts much closer.
5. Later: finish splitting EU data (started in session 7; game .rodata ownership works since
   session 8), document asset formats, then the PC port.
