# Port hand-off (branch `port`, worktree `~/conker-wt/port`)

Read `docs/port/PLAN.md` first: the phases, the browser-first target (wasm32/Emscripten) and the
risks. The decomp rules in `tools/eu_port/AGENT_BRIEF.md` and `HANDOFF.md` still apply: worktree
env, `verify_all.sh` before every commit, background jobs, the commit trailer.

```sh
cd ~/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"   # CONKER_ROOT, CONKERDEV=conkerdev-port
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
docker exec conkerdev-port python3 -c 'import unicorn'            # if missing: pip3 install --break-system-packages unicorn
```

## P87 (port-b) (session P87, 2026-10-23). Details: `docs/port/sessions/P87.md`

Branch `port-b` (from P83 e3312cf); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p87/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (903 bodies).
- **progress_nm (NM figure)**: total **4897/5915 (82.8%)**, game 4369/5334 (81.9%), C bytes 56.1%, 1018 asm-only.
  (P83's 3994/5915 was the matched-only column.)
- New hand-written NM C (no asm2c), setups EQUIV, mutants: the P88 trio in one commit, **func_1501ECA4** (camera
  track pass, fills D_800C3958, 39/40, 1 equivalent), **func_15020F6C** (applies the records, 46/46),
  **func_1501E888** (scene end, 22/23, 1 equivalent); func_1501D044 (21/21), func_1501DB18 (20/20),
  func_15020430 (24/25, 1 equivalent), func_15022C4C (30/30), func_15022A8C (10/11, 1 invalid mutant),
  func_15095A4C (game_eu_C2B60.c, 11/11).
- Arity fix (NM): func_15020430 passes the key count to func_15020090 (4th argument read from a3).
- P83 survivors killed: func_1501CE34 `<` -> `<=` (camera ends 0), func_1512317C `& 0xF` -> `& 7` (+0x4E = 9).
- Harness: declarations for an NM body must sit in their own NM block (difftest replaces the function's block).

## Next steps (from P87)

1. Browser: level 0 / cutscenes without the P88 guards (P87.md UNVERIFIED).
2. Scene-path asm left in game_eu_4A070.c: func_1501FD34 / func_1501FF10 (place / roll, called by func_1501ECA4),
   func_1502330C, func_1501EA84, func_1501E5AC, func_15023684.
3. game_14FF90.c: func_15124C38 (385), func_15126378 (1130).

## P83 (port-b) (session P83, 2026-10-23). Details: `docs/port/sessions/P83.md`

Branch `port-b` (from P82 e7e2e1a); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p83/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (895 bodies). progress_nm: game 3502/5334 funcs (65.7%), total 3994/5915 (67.5%).
- New hand-written NM C (no asm2c), random 100 + setups EQUIV: **func_1501CE34** (cutscene length, P84 level-0
  freeze; 12/15, 1 boundary survivor UNVERIFIED), func_15060F28 (object removal, 23/23), func_1506160C (fade
  command, 22/22), func_15061B4C (object-kind texture / colour animation, 50/50), func_150626EC (4/4),
  func_15056A00 (12/12); camera func_15125DB4 (controls mask, 32/32), func_151256BC (shake, 18/18),
  func_1512317C (look toggle, 23/26), func_15128030 (transition, 18/20, 2 equivalent); cutscene func_1501DE84
  (8/8), func_150225D0 (8/8).
- Harness: DIFFTEST_ARG values are hex (a decimal `1=10` setup hid a path); stack arrays passed to callees need
  DIFFTEST_ARGMEM; INVALID under load is reported correctly (P83.md §2).
- No dropped-argument fixes needed (C callers all pass full lists).

## Next steps (from P83)

1. Browser: level 0 start without the P84 guard (func_1501CE34), object removal / fades, camera (P83.md UNVERIFIED).
2. Scene loader producers still asm in game_eu_4A070.c: **func_1501ECA4** (716 insns) and **func_15020F6C** (562),
   then func_1501D044, func_1501DB18, func_1501E888, func_15020430, func_15022C4C (P83.md §4).
3. game_14FF90.c: func_15124C38 (385, prototype now `(struct108 *, f32 *)`), func_15126378 (1130).
4. Setups for the two UNVERIFIED survivors (func_1501CE34 all-zero camera ends, func_1512317C +0x4E nibble 9).

## P82 (port-b) (session P82, 2026-10-22). Details: `docs/port/sessions/P82.md`

Branch `port-b` (from P77 3ef8b97); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p82/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems.
- New hand-written NM C (no asm2c), all EQUIV on random 100 + setups: the browser's top frame-path group
  **func_151462C8** (model-part lights, DL, 25/25), **func_1514306C** (material texture address, 11/11),
  **func_1513C060** (sprite effect update, 28/28); func_1513E2AC (sprite quad corners, 27/29, 2 equivalent);
  **func_15021E60** (look target / fixed look angles, 24/24), func_150220CC (look limits, 14/14);
  func_1504ADD0 (per-frame object pass, 12/12; stores a pointer to a stack local as the asm does, P82.md §2);
  func_150617BC (object fades, 17/21, 4 equivalent; prototype now `void`).
- Arity fixes (byte-identical, default build): handler tables D_80089EE8 / EF0 / EF8 / F2C now get arg0
  (game_169510.c, scan rows 34-37); func_1501DF70(arg0) (game_eu_4A070.c, row 52).
- `docs/port/sessions/p82/mut.sh`: sed errors and CERR / UNSURE setups no longer count as SURVIVED (selftest in
  `selftest_mut.txt`). POKE into `.game_data` (0x80096DC4) had no effect: use the ELF value (P82.md §3).

## Next steps (from P82)

1. Browser: the DL group (lit parts, material textures, sprite effects), head turning (func_15021E60 /
   func_150220CC), the corrected handler calls (P82.md UNVERIFIED).
2. Frame-path asm left in P82's files: func_15060F28 (game_83300.c, called by func_150617BC mode 5 / 6),
   func_1506160C (fade setter, 108 insns), func_15061B4C (601), game_14FF90.c group (func_15125DB4, 15128030,
   15126378, 15124C38, 1512317C, 151256BC, 601 each), func_1501ECA4 / func_15020F6C (game_eu_4A070.c, 601).
3. Remaining asm in game_eu_170760.c (func_151432BC, func_15144CEC, func_15146078, func_1514654C) and
   game_169510.c (func_1513CFE4, func_1513EE14, func_1513FAB4, func_15140190, func_151406AC, ...): not hit in P81's run.

## P77 (port-b) (session P77, 2026-10-22). Details: `docs/port/sessions/P77.md`

Branch `port-b` (from P73 4498419); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p77/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems.
- New hand-written NM C (no asm2c), all EQUIV with every mutant killed: **func_150A02EC** (query handler entry 4, 27/27),
  **func_150A09B8** (entry 3, 32/32), **func_150954E4** (sky / sprite texture loader, browser blocker, 34/34),
  func_1501CDA0 (5/5), func_150226E8 (7/7), func_15097D20 (8/8), func_15097DDC (8/8).
- Arity fixes (NM): func_15049350 gets its nine floats (game_83300.c), func_1512B2C4(arg0) (game_eu_158110.c),
  func_15053430(arg0) (game_eu_78230.c). Rows func_1512C6C0 / func_1512523C x3 / D_800863B4 handlers checked: no
  argument in the asm (P77.md §1).
- func_1512C080: the 4 P73 survivors are killed (31/31).
- `docs/port/sessions/p77/mut.sh`: refuses the random phase when the draft itself DIFFERs on random trials (P77.md §3).

## Next steps (from P77)

1. Browser: sky quad (func_150954E4), script queries 0x3xxx / 0x4xxx, the three corrected calls (P77.md UNVERIFIED).
2. Display-list producers func_151462C8 / func_1514306C (game_eu_170760.c), func_1513C060 (game_169510.c), once assigned.
3. Breadth in owned files: asm-only game_eu_4A070.c func_1501DE84 (59), func_150225D0 (70); game_83300.c func_150626EC (58),
   func_15056A00 (66); game_eu_78230.c func_1504ADD0 (73); game_eu_C2B60.c func_15095A4C (73).

## P73 (port-b) (session P73, 2026-10-22). Details: `docs/port/sessions/P73.md`

Branch `port-b` (from P68 2f9d323); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p73/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems.
- **difftest bug fixed**: for an NM block holding more than one function (func_1501B300 + func_1501B640) the candidate
  was put in the dropped `#else` side, so the src_eu body was tested instead (all mutants "survived"). `build_tu` now
  replaces the definition on the NM side and errors out if the candidate is missing from the TU. Selftest case added
  (28/28). func_1501B300's rate mutants are now killed (11/15 overall, survivors boundary / equivalent). Same layout: func_150183D0/184B0, func_1507F3B0/F834.
- P67 setups (func_1505C7D8, func_150D5F7C, func_1507E7E4, func_150453BC, func_150D71D4) already used EU addresses
  (`port_work/p73/knobcheck.py`); re-run: all EQUIV.
- func_1512C080 full mutant run: 27/31 killed; 4 survivors (+0x23E / +0x2B0 / mode 0x100 / floor boundary) UNVERIFIED.
- New hand-written NM C (no asm2c): **func_151BF8F0** (lives pop-up, 132 setups, mutants 20/21), **func_1501D348**
  (scene loader, `void`, 123 setups, 27/27), **func_1509A024** (object query handler, 99-case switch, 622 setups x2,
  44/46, survivors equivalent). func_15084000 has a one-argument NM body (wasm signature).
- Tools: `docs/port/sessions/p73/knobs.sh` (KTMP) / `mut.sh` (own tmp dir; random phase without DIFFTEST_ARGMEM).
  Never run a setup run and a mutant run of one function with the p68 scripts at the same time (shared tmp dir).

## Next steps (from P73)

1. func_1512C080 survivors: setups with +0x23E not in {2, 3}, +0x2B8 equal / +0x2B0 different, mode 0x100.
2. Other entries of func_1509BE40's table still asm: func_150A09B8 (3), func_150A02EC (4).
3. Browser: lives pop-up, cutscene start (func_1501D348), script queries (func_1509A024) -- P73.md UNVERIFIED.

## P68 (port-b) (session P68, 2026-10-22). Details: `docs/port/sessions/P68.md`

Branch `port-b` (from P67 8c057c9); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p68/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (865 bodies).
- New hand-written NM C (no asm2c), P66 browser stub list: per frame **func_151236D0** (camera state flags + inside /
  outside sound), **func_1512C77C** (camera cylinder push-out), **func_151E7110** (text bank loader), **func_1501B300**
  (smoothed view direction; func_1501B640 forwards the player index under NM), **func_1512C080** (camera eye
  collision probe); movement **func_1506BF5C** (script sound / footsteps), **func_1507342C** (projectile spawn).
  Random seeds + knob setups EQUIV for all; mutants in P68.md.
- **Knob addresses must be EU addresses** (US-style names: func_15048A70 is at 0x15048D60, D_800D154C at
  0x800D196C ...): `port_work/p68_sym.sh SYM...`. OUTW is word-sized (use OUTB for u16 out-params).
  `docs/port/sessions/p68/mut.sh` stops at the first DIFFER (random trials first).
- Open harness question: writes of func_1501B300 to D_800BEAE0 / D_800BEAF0 do not seem to be compared (rate
  mutants survive); its smoothing math is hand-checked only (UNVERIFIED).

## Next steps (from P68)

1. P66 stub list, still asm: func_151BF8F0 (311 lines, stack struct for func_15149130), func_1501D348 (473),
   func_1509A024 (1571, in sections).
2. Browser: camera collision / follow, menu and in-game text, footsteps, projectiles (P68.md UNVERIFIED).

## P67 (port-b) (session P67, 2026-10-22). Details: `docs/port/sessions/P67.md`

Branch `port-b` (from P64 f0437f9); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p67/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (859 bodies).
- New hand-written NM C (no asm2c): **func_1505C7D8** (attack hit test over all records, sphere / box, line-of-sight
  ray cast), **func_150D5F7C** (debris burst: ray cast for the surface, two particle bursts), **func_1507E7E4**
  (start an object animation + first sound), **func_150453BC** (floor probe), **func_150D71D4** (debris follows its
  owner; batch EQUIV rewritten by hand). Random seeds + knob setups EQUIV; mutants 54/55, 44/44, 17/17, 13/13, 6/7.
- `void` under NM: func_1507E7E4, func_150D5F7C (prototypes in game_981E0.c, game_eu_ABEA0.c, init_B1B0.c, game_eu_78230.c).
- **difftest.sh did not forward DIFFTEST_RETF since P50** (every float-return knob was ignored, stubs returned random
  floats). Fixed; P59 / P60 / P64 RETF setups re-run: all still EQUIV.
- Tools: `docs/port/sessions/p67/knobs.sh` / `mut.sh` (8th setup field = DIFFTEST_OUTB), `port_work/p67_dbg.sh`.
- Batch (17 small never-attempted functions): 1 EQUIV (func_150D71D4), results in `port_work/p67b/results.tsv`.

## Next steps (from P67)

1. P66 stub list, still asm: movement func_1506BF5C (244 lines), func_1501D348 (473), func_151BF8F0 (311),
   func_1507342C (303); per frame func_1509A024 (1571), func_151236D0 (153), func_1501B300 (200), func_1512C77C (156),
   func_1512C080 (342), func_151E7110 (166).
2. Browser: attacks hitting enemies (func_1505C7D8), debris on destruction, floor detection (P67.md §4 UNVERIFIED).

## P64 (port-b) (session P64, 2026-10-22). Details: `docs/port/sessions/P64.md`

Branch `port-b` (from P60 71183d1); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p64/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (854 bodies).
- New hand-written NM C (no asm2c): **func_1505F298** (jump / swim / hang / glide handler, 5 commented sections;
  stunned / dead and the hanging animation now return as the asm does), **func_1507F3B0** + **func_1507F834**
  (idle-set chooser / advance: the idle path is all C), **func_15017FA4** (zone bounding boxes at level load),
  **func_150D1D20** (scrolling view quad DL), **func_150ADE40** (approx. distance; raw hand .s as plain C).
  Random seeds + knob setups EQUIV; mutants 87/89, 30/30, 5/5, 11/15, 15/15, 2/3 killed (survivors in P64.md).
- func_15085710 has been C since P16: P61's "asm stub" report points at the browser build (game_eu_B2980.c TU?).
- Tools: difftest DIFFTEST_OUTW takes stack arguments (N >= 4); `docs/port/sessions/p64/knobs.sh` / `mut.sh`
  (7th setup field = DIFFTEST_OUTW, per-call out-params).

## Next steps (from P64)

1. Ray-cast callers of the walk handler: func_1505C7D8 (567, attack hit test; m2c draft's record loop is wrong)
   and func_150D5F7C (603). Drafts: `port_work/p59/gen/`, `port_work/p64/gen/`.
2. Browser: jumps / swimming / glide (func_1505F298), idle animations (func_1507F640 -> F834 / F3B0), and why
   func_15085710 shows as a stub. Runtime checks: P64.md §3 UNVERIFIED.

## P60 (port-b) (session P60, 2026-10-22). Details: `docs/port/sessions/P60.md`

Branch `port-b` (from P59 649a7fa, `port` merged in at the end); the orchestrator merges it into `port`.
- After `git merge port` (5d0322c): full `verify_all.sh` OK (`port_work/p60/verify_merge.log`), NM links, protocheck 0 problems (850 bodies).

- The default build is byte-identical (full `verify_all.sh`, `port_work/p60/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (830 bodies).
- New hand-written NM C (no asm2c): **func_1505E0C4** (animation driver: fills anim +0x40 / +0x28 / +0x18, the
  bind-pose cause; s32 kept, returns 0), **func_1507F640** (idle animation chooser, `void (void)`; game_981E0.c's
  one-argument call fixed under NM), **func_15051558** (floor push / slope slide / landing tilt, `void` under NM).
  Random seeds + knob setups EQUIV; mutants: 38/39, 28/29, 40/50 killed (survivors in P60.md §1-2).
- structs.h: struct_eu_anim unk0 / unk3A / unk3C; struct126 unk32 / unk5A / unk5C / unk5D / unk1B2 (layout unchanged
  except struct126 now extends to 0x1B3).
- Tools: `docs/port/sessions/p60/knobs.sh` / `mut.sh` (6th setup field = DIFFTEST_OUTA, out-params via stack args),
  `gen_*.py` setup generators.

## Next steps (from P60)

1. func_1505F298 (jump, 1281 lines), ray-cast callers func_1505C7D8 (567) and func_150D5F7C (603); also still asm
   on the idle path: func_1507F834, func_1507F3B0. m2c drafts: `port_work/p59/gen/`.
2. Browser: does Conker leave the bind pose with func_1505E0C4 in C (P60.md §3 UNVERIFIED)?
Runtime checks: P60.md UNVERIFIED.

## State (session P57, 2026-10-22). Details: `docs/port/sessions/P57.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (829 bodies).
- progress_nm: C coverage including NON_MATCHING **4823/5915 (81.5%)**, bytes **51.5%**; init 489/538,
  game 4295/5334, debugger 39/43; **1092 asm-only** (152 under 60 insns); plus the nm_asm func_150A86B0.
- **The model DL path is C:** func_1502CFEC (model display list) with func_1503DD8C (model ready check) and
  func_1502F30C (vertex-block segments); the adjustment buffer is initialised: func_150342D0 + func_15034B50
  (face blink / mouth entries, then the 0x1000 terminator). Also func_1502F17C, func_1502F554, func_1507E7A0 (now
  `void`), func_1503A37C (bounds box), func_1518C900 (asset 9 DL load; func_1518CF74 was already C).
  All difftested with knob scripts in `port_work/p57/` (k*.sh) plus mutants (P57.md table).
- **Browser check first:** func_1502CFEC's G_MTX stores a *physical* address (0x000C42B8, `& 0x1FFFFFFF` of
  D_800C42B8) as the asm does; the port's gfx path must map it.

## Next steps (from P57)

Coordinator order after P58's browser run (Conker loads and is posed correctly by func_150A86B0):
1. **func_150A9B0C** (root rotation / scale; US name, real EU code at **0x150A9FEC** in the unsplit D5E90.s):
   hand asm, goes into `src_eu/nm_asm/D5E90_anim.c` (or a new nm_asm file); asm2c_hand.py is allowed only for such
   raw hand-written .s code. **All GLOBAL_ASM functions get readable hand C** (user policy).
2. **func_1000480C** (init_4470, 129 lines, not started): blocking cartridge read. Decoded: sets D_8003A8D2 = 1,
   waits for D_8003A8D3 == 0 and PI status (0xA4600010) & 3 == 0, size rounded up to even, reads words from
   KSEG1 0xA0000000 | (devAddr | D_80000308) into dramAddr (two paths: devAddr & 2 -> halfword-shifted copy with
   head / tail halves; else word copy + a trailing halfword when size & 2), clears D_8003A8D2 and starts thread
   D_80035C70 when D_8003A8D5 != 0. Difftest needs PI / ROM emulation (busy loops); the browser needs a ROM read.
3. Draw path: func_150A9E64 (f32 arena -> Mtx), func_1502C9D8, func_1503AB20, func_1503BCAC, then
   func_15030758 (464, convert CERR). Done in P57: func_1502CFEC, func_1503DD8C, func_1502F17C, func_1502F554,
   func_1503A37C, func_1507E7A0.
4. Other asm still reached: func_150028BC (453; obj[0xAC] & 1 or +0x18 & 0x4000), func_150F20C8 (type 0x7B
   adjustments), func_150ADA20 (random).
Code-segment tables: none of P57's C reads one (all its tables are in data / bss); func_150A86B0's D_150AA11C is
the known one (the browser supplies it). Runtime checks: P57.md UNVERIFIED.

## State (session P51, 2026-10-22). Details: `docs/port/sessions/P51.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (819 bodies).
- progress_nm: C coverage including NON_MATCHING **4813/5915 (81.4%)**, bytes **51.1%**; init 489/538,
  game 4285/5334, debugger 39/43; **1102 asm-only** (153 under 60 insns); plus the nm_asm func_150A86B0 (not counted).
- **func_150A86B0** (skeleton / animation evaluator, D5E90.s hand asm) is C in the new **`src_eu/nm_asm/D5E90_anim.c`**
  (separate Makefile lines; delete build_nm/conker.ld after merging), verified whole on real ROM animations of Conker
  (model id 0) by **`tools/port/difftest/nmasm_anim86B0.py`** (VR4300 interpreter with 64-bit ops vs Unicorn C):
  EQUIV in 950 trials, mutants DIFFER. Input builder `tools/port/difftest/anim_inputs.py`.
- Also C: **func_1503D210** (model load; P52's blocker), func_1503DC74, **func_1502DB14** (key-frame DMA; NM `void`).
- **Not yet:** func_150342D0 needs func_15034B50 (479, asm) first, so sbuf still reaches the evaluator
  uninitialised (its adjustment loop scans until 0x1000); func_1502CFEC (model DL).

## Next steps (from P51)

1. func_15034B50 then func_150342D0 (decoded in P51.md §4), then func_1502CFEC (model DL, 571).
2. P52's other stubs on the path: func_1503A37C, func_1502F554, func_1502F17C, func_15030758, func_150A9B0C, func_150028BC.
Runtime checks: P51.md UNVERIFIED (animation header / stream read big-endian, skeleton floats typed, callback table
function addresses, func_1503D210 only partly difftested).

## State (session P48, 2026-10-22). Details: `docs/port/sessions/P48.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (816 bodies).
- progress_nm: C coverage including NON_MATCHING **4810/5915 (81.3%)**, bytes **51.0%**; init 489/538,
  game 4282/5334, debugger 39/43; **1105 asm-only** (154 under 60 insns).
- **The object model chain is C** (game_eu_595D0): func_1502C1D4 (update loop, parents before children),
  func_1502E228 (root matrix), func_1502DE74 (model instance, sets +0x1D4), func_1502DE10, func_1502E7B4 (visibility
  mask; convert's "EQUIV" draft had two byte-offset bugs), func_1502F6B8. Also func_1507E690 (eye blink), and an NM
  `s32` func_1503FBF4.
- **Still asm on the model path:** func_150A86B0, the hand-asm skeleton evaluator in the unsplit D5E90.s (64-bit
  ldl / ldr bitstream decode, own register conventions; it writes the joint matrices +0x1D4 points at), then
  func_1502CFEC (model DL, 571), func_150342D0, func_1502DB14, func_1503D210 (P48.md §4).

## Next steps (from P48)

1. func_150A86B0 with a whole-function harness (nmasm_vis5858-style VR4300 interpreter, real ROM animation data).
2. func_1502CFEC, func_150342D0, func_1502DB14, func_1503D210; then func_1510EED0 (floor), func_15180AF0, func_15041A9C.
Runtime checks: P48.md UNVERIFIED (+0x1D4 now non-zero but its matrices unwritten while func_150A86B0 is a stub).
## P59 (port-b) (session P59, 2026-10-22). Details: `docs/port/sessions/P59.md`

Branch `port-b` (from P56 155e9d9); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p59/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (827 bodies).
- game_eu_17D3C0.c: func_150ACEA0 arg 2 is `f32` under NM (`RAY_Z0` macro keeps the matching call text).
- New hand-written NM C (no asm2c): **func_1506E46C** (sound id resolver), **func_1508000C** (floor-material effects),
  **func_1507D4F8** (life lost / respawn, now `void`), **func_1505D6F0** (record contact pass, `void`),
  **func_1507C7C0** (collision cylinder; m2c's switch was wrong, rebuilt from the jump tables), **func_1507C170**
  (animation advance, `void`). Each: random seeds + knob setups EQUIV, mutants killed except those in P59.md §2.
- Tools: `docs/port/sessions/p59/knobs.sh` / `mut.sh` (setup / mutant files), `pk.py` (poke words from record field
  specs), `sym.sh` (EU addresses). difftest pokes into `.game_data` are ignored: use real table entries there.

## Next steps (from P59)

1. Still asm on the walk path: func_15051558 (824 lines), func_1505F298 (jump, 1281), func_1507F640 (417),
   func_1505E0C4 (401); ray-cast callers func_1505C7D8 (567) and func_150D5F7C (603). m2c drafts: `port_work/p59/gen/`.
2. func_1507C170: the two unexplained surviving mutants (P59.md §2), and what the end-of-animation callbacks expect in a0.
Runtime checks: P59.md UNVERIFIED.

## P56 (port-b) (session P56, 2026-10-22). Details: `docs/port/sessions/P56.md`

Branch `port-b` (from P54 1b2f577); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p56/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (821 bodies; the nm_asm functions are not counted).
- New NM C (hand asm, src_eu/nm_asm/D5E90.c): **func_150AB6D0 / func_150AC8C4** (wall engine func_150AB708, both
  entries) and **func_150ACEA0** (ray cast). They are a mechanical register-level translation (`tools/port/asm2c_hand.py`,
  regenerate with `tools/port/gen_d5e90_walls.sh`) into `D5E90_walls.inc` / `D5E90_ray.inc`, which D5E90.c includes;
  touch D5E90.c after regenerating. Walls are now all C under NON_MATCHING: func_15044670 -> func_15044950 -> engine.
- `tools/port/difftest/nmasm_walls.py` (VR4300 vs Unicorn): synthetic data (3 seeds x 400 per entry) + levels 0x21 /
  0x1 / 0x5 / 0xB: 0 diffs. Mutants: 4 killed, 6 survive (P56.md §2; the ray cast's dx-sign `s1` mutant is unexplained).
- nmasm_vr.py: `.nm_rodata` contents are now loaded (relink without NOLOAD; before, the candidate saw zeros for NM C
  literals / jump tables), `Ref.trace`. EU symbol names are not addresses (D_800DBE5C = 0x800DC28C): look them up.
  NM sinf / cosf / func_150484A0 return garbage in the candidate (NM data layout): `nmasm_walls.patch_libm()`.

## Next steps (from P56)

1. Browser: walls / steps on level 0x21 and camera ray casts against walls (P56.md §3 UNVERIFIED); fix the
   game_eu_17D3C0.c prototype of func_150ACEA0 (arg 2 is `s32` there, `f32` in the definition: wasm mismatch).
2. Engine area kinds 2 / 3 (world objects, records' models) are untested: synthetic setups for them.
3. Asm-only ray-cast callers on the movement path: func_1505C7D8 (567 lines, CB98 callee), func_150D5F7C (603).
   `asm2c_hand.py` can translate other hand asm (it needs an EXTERN entry per external callee).
Runtime checks: P56.md UNVERIFIED.

## P54 (port-b) (session P54, 2026-10-22). Details: `docs/port/sessions/P54.md`

Branch `port-b` (from P53 190fae7); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p54/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (821 bodies).
- New NM C (hand asm): **func_150A3F50** (level floors: all triangles or BSP leaf), **func_150A48C0** (world objects),
  **func_150A5480** (records), shared per-triangle test `floor_tri` (= asm label func_150A408C), all in game_eu_D1760.c;
  **func_150A6A48** (object box lists, game_eu_D3880.c). func_1510EED0's floor lookup is now all C under NON_MATCHING.
  The NM tails func_150A44A4_tail.s / func_150A49D0_tail.s / func_150A6840_tail.s are no longer included.
- New `tools/port/difftest/nmasm_floorsets.py`: VR4300 reference vs Unicorn, synthetic sets + real level data (0x21, 0x1,
  0x5, 0xB via nmasm_level's pipeline): 0 diffs; mutants killed except one equivalent.
- **func_1505A9AC** (landing) inserted: func_1513783C(rec, 0xFF, 1) x2, func_15055C88(rec); void everywhere; 18 knob setups
  x 2 seeds EQUIV (`p54/a9acknobs.sh`), 8/8 mutants DIFFER. difftest pokes at 0x806xxxxx are ignored: point test
  pointers into the record array.

## Next steps (from P54)

1. Browser: drop overrides for the floor callees / landing and check standing + landing on level 0x21 (P54.md UNVERIFIED).
2. Wall engine func_150AB708 + stubs func_150AB6D0 / func_150AC8C4 (P53.md §5 map; D5E90.s lines 3305-4935), then the
   ray cast func_150ACEA0 (lines 4935-5620). Use src_eu/nm_asm/D5E90.c and an `nmasm_vr.Ref` harness like nmasm_floorsets.py.
Runtime checks: P54.md UNVERIFIED.

## P53 (port-b) (session P53, 2026-10-22). Details: `docs/port/sessions/P53.md`

Branch `port-b` (from P50 346c2d9); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh`, `port_work/p53/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (818 bodies).
- New NM C: **func_1510EED0** (floor / ceiling lookup, game_eu_13C400.c; setups a-j EQUIV + mutants), **func_150A44A4**
  (hand asm, triangle floor height, game_eu_D1760.c + `nm_asm/func_150A44A4_tail.s`; whole-function VR4300 harness
  `nmasm_floor.py` 2100 trials 0 diffs + mutants), **func_15021834** (spawn marker placement, game_eu_4A070.c),
  **func_15044950** (wall cylinder, game_eu_71E70.c). func_15021834 / func_15044950 are `void` everywhere.
- New `tools/port/difftest/nmasm_vr.py`: reusable VR4300 interpreter (FR=0, FCSR, div0, ldl/ldr, ...) + Unicorn
  candidate with FPR prologue / epilogue (Unicorn FPR reg access is a no-op).
- func_1510EED0's callees func_150A3F50 / func_150A48C0 / func_150A5480 / func_150A6A48 are still asm.

## Next steps (from P53)

1. func_1505A9AC (landing): EQUIV-but-untested draft in `port_work/p53b/pass/`; fix the func_1513783C calls (P53.md §4b), knob setups.
2. Floor callees for the browser: func_150A3F50 (hand asm, 367 lines), func_150A48C0, func_150A5480, func_150A6A48, func_1507C7C0.
3. Wall engine func_150AB708 + stubs func_150AB6D0 / func_150AC8C4: structure map in P53.md §5; reference = `nmasm_vr.Ref`.
   Then the ray cast func_150ACEA0.
Runtime checks: P53.md UNVERIFIED (real floor tables, walking height).

## P50 (port-b) (session P50, 2026-10-22). Details: `docs/port/sessions/P50.md`

Branch `port-b` (from P47 c811a9e); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (814 bodies).
- New NM C: **func_15056B08** (remote pad copy; P47's DIFFER was m2c `struct127 *` arithmetic `+= 0x32C`, not
  rounding), and P49's movement path: **func_15059C84** (position integrator), **func_1505A770** (gravity),
  **func_1504C0E8** (animation choice, sets +0x80). All void; their NM prototypes everywhere are void.
- func_1504CB98: d-pad (34.0) and kind-2 floor branches now reached and mutant-killed (`p50/cbknobs.sh` m, o);
  the in-water `/ 4` is unreachable under difftest (needs func_1504BC38 side effects): matches the asm by hand.
- difftest: array parameters (`f32 mf[4][4]`) count as pointers in the float-slot logic; `DIFFTEST_RETF` (f0 of a stub).
- D_800D1550 is `f32[]` (the frame-time float), not a pointer.

## Next steps (from P50)

1. Movement: func_150A44A4 + func_15021834 (NODRAFT: raw m2c), func_15044950 (CERR), func_1510EED0 when P48 hands it over.
2. Walls func_150AB6D0 / func_150AC8C4 are 13-insn entry stubs into the hand-asm engine func_150AB708 (P50.md §3);
   func_150ACEA0 is ~600 insns (P50.md §3): nm_asm C + whole-function harness.
3. Browser: drop P49's PC overrides for func_15059C84 / func_1504C0E8 / func_1505A770 and recheck walking.
Runtime checks: P50.md UNVERIFIED.

## P47 (port-b) (session P47, 2026-10-22). Details: `docs/port/sessions/P47.md`

Branch `port-b` (fast-forwarded to `port` 1a26d1a during the session); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (821 bodies; the nm_asm functions are not counted).
- **func_1504CB98** (state-1 walk handler) is NM C: 12 knob setups x 3 seeds EQUIV (`docs/port/sessions/p47/cbknobs.sh`);
  3 of 4 mutants survive = d-pad steering, kind-2 floor and in-water turn branches UNVERIFIED.
- u64 re-check: 87 NM bodies with u64; only func_150A16A4 calls the 64-bit helpers; 85 EQUIV + func_15158838 EQUIV
  (budget); func_150A16A4 DIFFERs only for counts > 192 (out-of-range input), P45 setups EQUIV. No false EQUIV found.
- func_15127FEC calls `func_1512A390(arg0)` under NON_MATCHING (wasm signature fix). func_150A16A4: prev = 0 for non-players.
- difftest: float-slot prototype lookup prefers declarations over call statements; `DIFFTEST_WLOG` write log, `DIFFTEST_CALLS_FROM`.

## Next steps (from P47)

1. func_15056B08: draft `docs/port/sessions/p47/func_15056B08_draft.c` compiles, DIFFER at call #2 (func_1505A630 f12).
2. CB98 setups for the three unreached branches (P47.md §2), then P45 §5 stubs, then func_150ACEA0.
3. Per-frame stubs the browser hits (P46): func_1510EED0 (floor lookup), func_150A44A4 / func_150ACEA0 (ray casts),
   func_1507E690, func_1509A024. The object update loop (game_eu_595D0.c) belongs to a `port` session: do not edit it.

## P45 (port-b) (session P45, 2026-10-22). Details: `docs/port/sessions/P45.md`

Branch `port-b`, worktree `~/conker-wt/portb` (from P41 50cb17e); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (798 bodies).
- progress_nm: C coverage including NON_MATCHING **4792/5915 (81.0%)**, bytes **50.4%**; **1123 asm-only**.
- New C: **func_150A16A4** (trigger zones, before the state handler), **func_1507EB1C**, **func_1504AF10** (both
  after it; now `void`). Fixed NM C: **func_150A2AB4**'s last parameter is a `u64` on the stack (was read from a3).
- difftest: the libultra 64-bit helpers (`__ll_lshift`, `__ull_rshift`, ...) are **emulated** instead of returning
  random values; u64 code was only half exercised before. selftest 26/26.
- State table `D_800863B4` holds EU addresses: state 1 = 0x1504CE90 = **func_1504CB98** (one function, ~4700 insns).
  Its cleaned m2c draft compiles and agrees up to call #10: `docs/port/sessions/p45/func_1504CB98_draft.c` (+ the
  fixm2c.py / fixloop.sh used to make it). Not inserted.

## Next steps (from P45)

1. func_1504CB98: continue from the saved draft (P45.md §4: first DIFFER = memory before call #11, func_15021834).
   Check struct127 field widths against the asm (unk31C+8 was s16), then knob setups per branch + mutants.
2. Then its stubs on the walk path (P45.md §5), func_15056B08 first (called at the top of the handler).
3. Browser: func_150A16A4 now runs real trigger zones; watch kind 8 (PI read of 0xB0000054).

## P41 (port-b) (session P41, 2026-10-22). Details: `docs/port/sessions/P41.md`

Branch `port-b`, worktree `~/conker-wt/portb` (from `port` at 8e17fd1); the orchestrator merges it into `port`.

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (795 bodies).
- progress_nm: C coverage including NON_MATCHING **4789/5915 (81.0%)** (P38: 4781), bytes 49.9% → **50.3%**;
  init 489/538, game 4261/5334, debugger 39/43; **1126 asm-only**.
- **The camera's inputs are C (P39 §2 list):** func_150851E0 + func_150858A0 (place the player record at the level
  start), func_15005818 (initial eye), func_151247C0 (at follows the record), func_15123A54 (eye orbit + wall ray
  casts), func_151283B8 (mode dispatcher, now `void`), func_15122EF0 (mode 1). Shadow chain: only func_1502C074;
  func_1502C1D4 and func_1502E228 (+0x1D4 writer) are still asm.
- difftest: **`DIFFTEST_OUTB="ADDR=N:B0;B1;..."`** (byte out-params through argument N; N >= 4 = stack argument).
- Fresh-worktree setup: copy the untracked `conker/build_port/s54/` (m2c gen2.py needs `fi/params.json`).

## Next steps (from P41)

1. Browser: `?camwatch=8` after merging: D_800CC2D0[0] should sit at the level start, the controller's at (0x2A4 / 0x2BC)
   follow it, eye 0x2F8 / 0x300 orbit at 0x370, and `obj+0x13C..0x150` be non-zero. Then shoot the game's own view.
2. Shadow chain: func_1502C1D4 (198 lines; draft DIFFERs on a2 of the C074 call), func_1502E228 (367 lines; CERR).
3. Still-asm camera callees that matter at runtime: func_150ACEA0 (ray cast; stub = no wall shortening), func_1512DAD0
   (camera events), func_15123070, func_1512A390, func_1512E6B0.
Runtime checks: P41.md UNVERIFIED (second-ray branch of func_15123A54, multiplayer start choice, func_1502C074's
`+0x1D4 != 0` branch).

## State (session P30, 2026-10-22). Details: `docs/port/sessions/P30.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (753 bodies). difftest selftest 26/26.
- progress_nm: C coverage including NON_MATCHING **4746/5914 (80.3%)** (P28: 4735), bytes 48.1% → **48.5%**; init 479/538, game 4228/5333, debugger 39/43; **1168 asm-only**.
- **The camera path is C:** func_150054C4, func_1512B168, func_150006E0 (forwards the level in a0 to func_15000940),
  func_15122C5C, func_1510B6A8 (now `void (s32, f32 x4)`; the NM caller passed 1.0f as an int), func_1510B9D8,
  **func_1512C490** (gameplay view matrix), func_150A82D0 (hand-asm rotation Mtx), and func_150045C4 (P29's runtime list:
  world-object matrices). Frame DL: func_15110948 (default camera callback), func_1517485C (occlusion probes).
- difftest: `DIFFTEST_EXACT='*'` (known prototypes are exact); `proto_arity` ignores commented-out drafts.

## Next steps (from P43)

Port-b owns game_14FF90.c, game_eu_B2980.c, game_32740.c, the shadow chain, and the player movement files
game_eu_78230.c (func_1504CB98, func_1504ADD0), game_eu_CE6C0.c (func_150A16A4), game_83300.c (func_15056B08).
1. When port-b merges: game_14FF90.c's func_15127FEC calls `func_1512A390();` with no argument (wasm trap now that
   func_1512A390 is C); it must pass arg0.
2. func_15180AF0 (convert: NODRAFT this time; P38's m2c draft in `port_work/p38/m2c/`), func_15041A9C (boot text,
   raw draft `port_work/p38/m2c/raw/`), the rest of P32's list (all CERR in `port_work/p43e/`: func_151E7110,
   func_1501B300, func_151143D4, ...).
Runtime checks: P43.md UNVERIFIED (D_80088838 handler types for the now-variadic func_1509BE40, func_1509CBD8 is void).

## State (session P43, 2026-10-22). Details: `docs/port/sessions/P43.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (798 bodies).
- progress_nm: C coverage including NON_MATCHING **4792/5915 (81.0%)** (P40: 4784), bytes 50.0% → **50.3%**;
  init 489/538, game 4264/5334, debugger 39/43; **1123 asm-only** (157 under 60 insns).
- **Level lighting:** func_1515E7E8 (the start colour `col` of func_1515DE84; the level was black / stack-coloured
  without it). func_1515E9AC was already C; game_eu_18B1C0 is all C under NM.
- Frame DL: func_1502CC64 (object draw), func_15196560 (texture scroll). Level load: func_15017B20 (zone overlap masks).
- Camera: func_1512E6B0 (eye height), func_1512A390 (eye base / floor clamp), func_1512C6C0 (top stub by hits).
- func_1509BE40 is a real variadic function under NM; every caller's NM prototype is `s32 func_1509BE40(s32, s32, ...)`.
- difftest: `DIFFTEST_ARGMEM` accepts stack arguments (N >= 4).

## Next steps (from P40)

Browser priorities (P39, sent during P40): the camera chain (func_150858A0 / func_150851E0, func_15005818,
func_151247C0, func_15123A54, func_151283B8 → func_15122EF0) and the shadow chain (func_1502C1D4 → func_1502C074 →
func_1502E228) **belong to the parallel session on branch `port-b`** (worktree `~/conker-wt/portb`). Do not take them
here, and do not edit game_eu_B2980.c, game_32740.c, game_14FF90.c or the files of those shadow functions.
1. Here: func_15180AF0 (m2c raw draft, see P38.md §6), func_15041A9C (raw draft with 3 `unksp`), the P29 top-hit list.
Runtime checks: P40.md UNVERIFIED (**vertex-pointer range tests** `> 0x100000` / `> 0x80000000` in func_15001460 /
func_15002008 / func_15002248 vs wasm heap addresses; PI_STATUS + cart word reads in func_15001A08), P38's list.

## State (session P40, 2026-10-22). Details: `docs/port/sessions/P40.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (790 bodies).
- progress_nm: C coverage including NON_MATCHING **4784/5915 (80.9%)** (P38: 4781), bytes 49.9% → **50.0%**;
  init 489/538, game 4256/5334, debugger 39/43; **1131 asm-only** (158 under 60 insns).
- **The level-load visibility build is all C:** func_15001460 (triangle scan), func_15001A08 (node pool), func_15002008
  (leaf lists), and the PVS row index func_150183D0 + func_150184B0 (hand asm). func_150A5858 now gets a range
  (D_800D3668..D_800D3A8C) and a tree (D_800DC278).
- **New whole-pipeline harness `tools/port/difftest/nmasm_level.py`:** real level assets from the ROM (zlib), func_15003668
  + func_150038A0 through asm and C in Unicorn, all RDRAM compared: **EQUIV on all 59 levels with a model list**
  (PVS on 19 of them), plus `--synth` random DLs through func_15001460; func_150A5858 (C) smoke on the C tree (asm agrees).
  Masked: area-2 (object) triangle bounds, which the asm fills from stale stack slots (P40.md §1).

## Next steps (from P38)

Browser priorities (P37, sent during P38). The player spawns and the camera target is non-NULL. Two blockers remain:
1. **Visibility-walk inputs** (still asm stubs, so func_150A5858 gets an empty range and a NULL tree): **func_15001460**
   (game_2DF70, 324 lines: walks the level DL, counts triangles into D_800DBE38, writes the triangle tables),
   **func_15001A08** (66 lines, node pool; a JUSTREG draft is in game_eu_2F180.c), **func_15002008** (144 lines, leaf
   index lists).
2. **Camera eye/at:** the target record's +0x13C..+0x150 stay 0. Candidates: func_150617BC, func_1512C6C0 (#2 stub by
   hits), func_1512C77C, func_1512C080 (func_1504A730 is C since P38 and does not write them). A P38 grep found **no
   direct swc1 / addiu at 0x13C..0x150** in those four, so the writer is a callee (func_15048A70 / func_15048758 /
   func_15048F90 / func_15048FC8, called by func_1512C6C0 / func_1512C77C) or works through a base pointer + offset.
   Trace it in the browser with a write watch on the record.
3. Done in P38: init_1050.c comment now says func_1000738C.
4. Then: func_15180AF0 (m2c drafts it now; see P38.md §6), func_15041A9C (raw draft with 3 `unksp`), the P29 top-hit list
   (P32 drafts in `port_work/p32/gen/`, mostly same-file redeclaration CERRs).
Runtime checks: P38.md UNVERIFIED (shadow strip splitter, func_1504A730's stack D_800CC6A4).

## State (session P38, 2026-10-22). Details: `docs/port/sessions/P38.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (787 bodies).
- progress_nm: C coverage including NON_MATCHING **4781/5915 (80.8%)** (P36: 4775/5914), bytes 49.6% → **49.9%**;
  init 489/538, game 4253/5334, debugger 39/43; **1134 asm-only** (158 under 60 insns). The function total is +1 because the
  8-byte `func_150A6840_tail` asm fragment counts as a function (as P28's tail did).
- New C: **func_150A6840** (FR=1 hand-asm view test; whole-function harness `tools/port/difftest/nmasm_view6840.py`, 4000
  trials incl. exact boundaries EQUIV) + func_150A69A8; **func_1505E650**; **func_1504A730** (per-frame object update);
  **func_15186D04** (shadows, strip splitter UNVERIFIED); **func_15182450** (fade overlay).
- Tools: difftest `DIFFTEST_OUTA="ADDR=N:W0;W1;..."` (array out-param, N >= 4 = stack argument). The vis5858 VR4300
  interpreter takes `entry=` and has c.olt / c.ult / c.ule / cvt.w.s. m2c: the generated contexts for game_eu_1ACBC0 were
  patched (K&R func_1517F470); a context regeneration undoes that.

## Next steps (from P36)

1. Browser: **drop the TEMPORARY PC inflater** (`web/port/ultra/pc_mem.c` func_1000654C): the whole inflater is NON_MATCHING C
   (P36). Note the work area (3rd argument, D_8003809C) receives the huft tables and must start >= 1 byte past the output.
2. Browser runtime check: camera target D_800CC2D0[0] + 0x31C after the level 0x21 load. The level-setup chain is now C:
   func_15016950 → func_15082D5C → func_150829C0 → func_15082E44 (+ func_15083C3C, func_1505F188, func_15083568).
3. func_150A6840 (view test, FR=1 hand asm, shares its .s with func_150A69A8; needs an nmasm-style harness),
   func_1504A730 (per-frame update, 426), func_1505E650; then func_15041A9C (boot text), func_15186D04, func_15182450,
   func_15180AF0, func_1506C460 (projectile spawner, not on the camera path). convert.py gives no usable draft for these.
Runtime checks: P36.md UNVERIFIED (inflater under the vbe layout, camera target, func_15030DE4 s8 argument).

## State (session P36, 2026-10-22). Details: `docs/port/sessions/P36.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (782 bodies).
- progress_nm: C coverage including NON_MATCHING **4775/5914 (80.7%)** (P34: 4761), bytes 49.2% → **49.6%**;
  init 489/538, game 4247/5333, debugger 39/43; **1139 asm-only** (158 under 60 insns).
- New C: **Rare's inflater** func_1000654C + func_1000661C / 10006670 / 10006714 / 10006B18 / 10006C1C / 10006C5C /
  100070F0 + func_1000738C (fixed tables), verified whole by **`tools/port/difftest/nmasm_inflate.py`** on real ROM assets
  (`scan_assets.py`: 5869 packed records; 2 x 1012 trials incl. 0x1172 header, limit / error paths, corrupted streams:
  0 differences; 6 mutants DIFFER). Level-setup spawn chain: **func_15016950** (level setup load), **func_150829C0**
  (spawn gate), func_15083C3C, func_1505F188, func_15083568, func_15022304 (difftest EQUIV with knobs, mutants DIFFER).

## Next steps (from P34)

1. **Rare's inflater func_1000654C + helpers** (init_eu_5DA0, GLOBAL_ASM; the browser has a TEMPORARY PC inflater since
   P33): NON_MATCHING C, verified whole by inflating real ROM assets through asm and C (plan in P34.md).
2. func_1506C460 (thrown-object spawner; m2c draft broken, see P34.md §4).
3. func_15041A9C (boot text, 1202 lines), func_15186D04, func_15182450, func_15180AF0; P29 top-15 list.
Runtime checks: P34.md UNVERIFIED ($gp at func_150A5858 entry, real level data, spawned object/camera target).
Browser can now drop its TEMPORARY func_150031EC / func_15003120 / func_1501A8C0 / func_150479F0 and the dlapprox
diagnostic: all are NON_MATCHING C (P34). Level asset key is (4, level).

## State (session P34, 2026-10-22). Details: `docs/port/sessions/P34.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (767 bodies).
- progress_nm: C coverage including NON_MATCHING **4761/5914 (80.5%)** (P32: 4754), bytes 48.9% → **49.2%**;
  init 480/538, game 4241/5333, debugger 39/43; **1153 asm-only** (163 under 60 insns).
- New C: level loader func_150031EC + func_15003120 (exact allocation sizes: count * 4 and count, both bzero'd with
  count bytes); **the func_150A5858 hand-asm blob** (also replaces func_150A5BE8 / func_150A5D08 / func_150A5F98:
  visibility walk + level-DL filter), checked whole by `tools/port/difftest/nmasm_vis5858.py` (VR4300 interpreter for
  the 64-bit asm vs Unicorn for the C; 1000 random scenes EQUIV); func_1501A8C0 (camera record); func_150479F0
  (guLookAtReflectF variant); **func_15082E44** (level-setup object spawner).
- difftest: `DIFFTEST_OUTW="ADDR=N:V;.../M:W"` writes words through a stub's pointer args (out-params).

## Next steps (from P32)

Browser priority order (P31, sent during P32):
1. Boot screen (level 0x25): func_15041A9C (text, 1202 lines). func_15042ECC, func_151EDBE8, func_151EDA54 are done.
2. Level 0x21 world: func_150031EC (level model loader, sets D_800B0E00; the browser's temporary C loader breaks the
   heap at the level switch, check allocation sizes) + func_15003120; func_150A5858 (**raw hand asm** visibility walk,
   gp/t-register calling convention, DL pointer = 2nd arg): faithful C via a whole-function nmasm harness.
3. Replace the browser's temporary C: func_1501A8C0 (camera record FOV/scale), func_150479F0 (guLookAtReflectF).
4. Object spawners: func_15082E44, func_1506C460.
5. Then: func_15186D04 (shadows; draft `port_work/p32/gen/v0/`), func_15182450, func_15180AF0; P29 top-15 list.
Runtime checks: P32.md UNVERIFIED list and P30's.

## State (session P32, 2026-10-22). Details: `docs/port/sessions/P32.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (761 bodies).
- progress_nm: C coverage including NON_MATCHING **4754/5914 (80.4%)** (P30: 4746), bytes 48.5% → **48.9%**;
  init 480/538, game 4235/5333, debugger 39/43; **1160 asm-only** (164 under 60 insns).
- New C (hand, difftest EQUIV with knobs + mutants): frame-DL func_151EDBE8 (HUD tiles), func_150911F4, func_15090630,
  func_150900F0, func_1515DE84 (lights), func_151EDA54; **func_15042ECC** (text-queue printf, top stub by hits); func_1000A03C (audio bank DMA).
- Fix: game_eu_C2B60's void wrappers func_15095380 / func_150953F8 / func_15095E58 / func_1509611C return the
  display-list pointer under NM (callers relied on IDO's leftover v0; the wasm build got garbage).
- func_15127EB8 (NM): func_1510B8AC now prototyped `(s32, f32, f32, f32)`, called with 0.0f, 0.0f, 1.0f.
- Reminder: source names are US names; POKE/RET/ARGMEM take EU addresses (`port_work/p28h/euaddr.sh`).

## Next steps (from P30)

1. Frame-DL stubs (P29 runtime list): func_151EDBE8 (212 hits), func_1515DE84, func_150A5858 (DL pointer = 2nd arg),
   func_150911F4, func_15090630, func_150900F0, func_15186D04, func_15182450, func_15180AF0; func_15042ECC (vsprintf-like, top hits).
2. Runtime checks: the P30.md UNVERIFIED list (func_150006E0's a0 pass-through, func_1512C490's uninitialised Mtx at 0x2C == 0x8000).
3. func_1000A03C, D5E90.s raw asm.

## State (session P28, 2026-10-22). Details: `docs/port/sessions/P28.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (743 bodies).
- progress_nm: C coverage including NON_MATCHING **4735/5913 (80.1%)** (P24: 4728), bytes 47.8% → **48.1%**; init 479/538, game 4217/5332, debugger 39/43; **1178 asm-only** (164 under 60 insns).
- New C (hand, difftest/harness EQUIV with knobs + mutants): frame path func_15110420 (func_15110E44 takes 4 floats),
  func_1510BF50, func_1508FD38, func_15173954; **the func_150A49D0.s blob** (entries func_150A49D0 + func_150A4ED4; the
  inner glabels are loop labels; the tail fragment is func_150A3F50's and stays asm in `src_eu/nm_asm/func_150A49D0_tail.s`;
  harness `tools/port/difftest/nmasm_blob49D0.py`). This also fixes a latent NM bug: the asm blob relied on sin/cos
  preserving f1-f13, which the P24 C sin/cos does not.
- P26 camera path: **func_15005290** (allocates D_800DBFF0 / D_800DC6D0 / D_800DC6E0 / D_800BE6D0 / D_800DC440) and
  func_150859AC are C. NM `sqrtf` no longer recurses outside IDO (`NM_SQRTF`); func_1000EC24 declared as a function under NM.
- Tools: difftest `DIFFTEST_ARGMEM="ADDR=N:LEN"` (compare memory passed by address); `difftest.sh` now forwards
  `DIFFTEST_ARG` (it silently didn't) and `DIFFTEST_ARGMEM`; `port_work/p28h/euaddr.sh` (EU addresses from the map).

## Next steps (from P28)

1. P26 camera list still asm: func_150054C4 (213), func_1512B168 (87), func_150006E0 (152), func_15122C5C (261),
   func_1510B6A8 (129), func_1512C490 (760) + func_150A82D0 (152), func_1510B9D8 (49). convert output in `port_work/p28cam/`.
2. Frame-path stubs: func_15182450 (484), func_15186D04 (711), func_15180AF0 (991) (`port_work/p28c/`).
3. func_1000A03C (asm decoded in P28.md, C not written); D5E90.s raw asm (P22.md §3).
4. Runtime: func_15110420 callback signature, P24's list.

## State (session P24, 2026-10-22). Details: `docs/port/sessions/P24.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (736 bodies). difftest selftest 26/26.
- progress_nm: C coverage including NON_MATCHING **4728/5913 (80.0%)** (P22: 4721, 79.8%), bytes 47.6% → **47.8%**; init 479/538, game 4210/5332, debugger 39/43; **1185 asm-only** (164 under 60 insns).
- New C (hand, difftest/harness EQUIV): func_1000CEAC + func_1000D2F8 (**music player per-slot update, not camera code**:
  the projection buffers are filled elsewhere), func_150A8050 (rotation matrix from degrees), **sinf/cosf
  func_150AD78C/func_150AD780 in `src_eu/nm_asm/D5E90.c`** (harness `tools/port/difftest/nmasm_sincos.py`, 0 differences),
  frame-path func_150362D8, func_1517F910, func_1517FAD4, func_1517E7FC. UNVERIFIED notes for the browser in P24.md.
- Clang-only errors fixed under NM: the 3 lvalue casts, func_151A3AB4 arity, func_15088BFC/func_150889D8 pass-through,
  debugger.c's func_150ADC50 (function, compared by address).
- Tools: `DIFFTEST_RET="ADDR=V1;V2;..."` sequences; known short prototypes have no stack args; both nmasm harnesses
  run the candidate on the reference `.game_data` (the NM build's data is not address-stable).

## Next steps (from P24)

1. Frame-path stubs still asm: func_15110420 (draft calls func_15110E44 with the wrong arity: it is `(f32 x4)`),
   func_1510BF50, func_1508FD38, func_15182450, func_15186D04, func_15180AF0.
2. func_150A49D0.s blob (6 functions; func_150A4ED4 is a glabel inside it, used by game_eu_13C400.c:173), then
   func_1000A03C, func_15173954.
3. Find the real producer of the projection buffers at D_800DC6D0 (browser: 0x10622690/0x106226D0): not init_B1B0.
4. Runtime checks (P24.md): func_1000CEAC beat length, func_1000D2F8 song callback signature, func_1517FAD4 lerp
   factor, func_15088BFC argument.

## State (session P22, 2026-10-22). Details: `docs/port/sessions/P22.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems (821 bodies; the nm_asm functions are not counted).
- **729 NON_MATCHING bodies** (+42). progress_nm: C coverage including NON_MATCHING **4721/5913 (79.8%)**, bytes 47.6%:
  init 477/538, game 4205/5332, debugger 39/43; **1192 asm-only** (165 under 60 insns).
- HUD tables D_80090370 / D_800903A4 are all C under NM: func_151EB81C, func_151ECB98, **func_151EC300** (the frame-path
  entry, D_80090370[11]), func_151EC9A0, func_151EC11C (D_800903A4[8]); func_151ED854 returns `Gfx *` under NM.
- Stub hits now C: func_15113B44, func_1502BDC0 (EQUIV), func_1517D7B0 (EQUIV, thin coverage).
- **Raw asm C:** `src_eu/nm_asm/D5E90.c` + Makefile `NM_ASM_C_FUNCS_D5E90` (NM-only; asm symbol weakened). func_150AB278
  (triangle/box test) is the first: `tools/port/difftest/nmasm_tri_box.py` 4000 trials, 0 differences. Plan in P22.md §3.
- Breadth p22b (185, 301–450 insns): 46 EQUIV, 35 inserted (4 reverted, 7 lint-flagged left out).

## Next steps (from P22)

1. **Browser frame-path stubs (P23 list):** func_15110420, func_1510BF50, func_15186D04, func_150362D8, func_1517E7FC,
   func_15182450, func_1517FAD4, func_1508FD38, func_1517F910, func_15180AF0 (func_15113B44, func_1502BDC0 and
   func_151EC300 from that list are done in P22).
2. **guMtxF2L is still an asm stub** (garbage matrices in the browser): libultra, port the ultralib source directly.
3. **Clang-only errors in converted C** (IDO accepts them): lvalue casts at game_eu_113D60.c:131, game_eu_1C3530.c:1069,
   game_eu_1F4F60.c:93; game_eu_1D1150.c:435 calls func_151A3AB4 with 3 args (defined with 2); game_eu_B37F0.c:282 calls
   func_150889D8() with 0 args (defined with 1).
4. Rest of the old stub-hit list: func_1000CEAC, func_1000A03C, func_15173954 (CERR), func_1000D2F8 (NODRAFT), the
   func_150A49D0.s blob (entry func_150A4ED4). Runtime checks: func_151EB81C counter screen, func_1517D7B0, func_15113B44.
5. D5E90.s: the other C-called functions (P22.md §3 plan), each with a whole-function Unicorn harness.
6. p22b leftovers (4 reverts, 7 lint EQUIVs, 51 DIFFER, 58 CERR); CERR classes (deref 40, functions.h self-redecl 38, subscript 36).

## State (session P20, 2026-10-22). Details: `docs/port/sessions/P20.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems. difftest selftest 26/26.
- **687 NON_MATCHING bodies** (+71). progress_nm: C coverage including NON_MATCHING **4679/5913 (79.1%)**, bytes 45.1%:
  init 477/538, game 4163/5332, debugger 39/43; **1234 asm-only** (165 under 60 insns).
- `fix_selfproto` now works (implproto oscillation fixed; `//DROP` + `//HOIST` fallback for same-file prototypes): p17c/p17d 11 EQUIV.
- P18's 11 reverts are in (helper `port_work/p20/fixproto.py FUNC...` syncs every prototype with the C definition).
- New CERR fixes (spframe trailing-comment decls, implicit-int vs later file prototype, `//HOIST` redecl): CERR re-run p20c
  of 335 → 50 EQUIV, 45 inserted.
- Browser asks: func_15049260 returns s32 under NM (func_150AB278 too); hand bodies func_1502B350, func_1502B4A8,
  func_15002248, func_150A7A48 (EQUIV); func_1501B22C EQUIV. difftest knob `DIFFTEST_ARG="N=V1|V2"`.

## Next steps (from P20)

1. Browser stub hits still asm: func_1000CEAC, func_15113B44, func_1000A03C, func_15173954 (CERR), func_1502BDC0 (DIFFER),
   func_1000D2F8 (NODRAFT), func_1517D7B0 (untried, 427), func_150A4ED4 (entry inside the `func_150A49D0.s` blob). Rest of P19.md §9.
2. Breadth 301–450 insns: 185 untried (`port_work/p20/p20b.txt`), `convert.py --tag p20b --jobs 4 -l ...`.
3. CERR: 38 self-redeclarations against functions.h (needs a header variant of the DROP fallback); deref / subscript / `-` operand classes.
4. Open from P18: func_1505A3A8 (1-ulp), func_150A6834 (asm f20/f21 setter), difftest stack memory passed by address.

## State (session P18, 2026-10-22). Details: `docs/port/sessions/P18.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems. difftest selftest 26/26.
- **616 NON_MATCHING bodies** (+110). progress_nm: C coverage including NON_MATCHING **4608/5913 (77.9%)**, bytes 42.9%:
  init 477/538, game 4092/5332, debugger 39/43; **1305 asm-only** (175 under 60 insns).
- **difftest root causes:** (1) Unicorn 2.0.1 ignores FPR `reg_read`/`reg_write`: float args, stub f0 returns, f0 return /
  FP-arg / f20-f31 compares never worked. FPRs now go through memory (prologue / stub helper / epilogue, base k0).
  (2) The P17 "literal reads as 0": a Unicorn TLB bug between virtual page 0 and kseg0 pages with TLB index 0; TU_BASE moved
  to 0x80705000, heap pointers skip those pages. `fix_litsym` is no longer needed (kept, harmless).
- Re-check of all 506 old bodies with the fixed difftest found 2 wrong math bodies (func_150488C8, func_15048C30, fixed);
  the new table/width lint (`lint:table`) found 2 more (func_15008BF0, func_15007440, fixed).
- Trial children have a wall limit (`DIFFTEST_TRIAL_WALL`) and die with their parent (PR_SET_PDEATHSIG; convert.py too).
- Batch p18b (303 untried, 201–300 insns): 106 lint-clean EQUIV (35%); re-eval p18r of 301 old DIFFER/UNSURE: 15. 110 inserted.

## Next steps (from P18)

1. p17c (`cfix.fix_selfproto` registration + `convert.py --tag p17c`): relayed approval, but the auto-mode classifier denied
   registering it. Needs the user to allow it directly.
2. 11 reverted P18 bodies (prototype wraps / NM redeclarations, list in P18.md); func_1505A3A8 (1-ulp), func_150A6834 (asm f20/f21).
3. Near misses: p18b 56 DIFFER / 96 CERR / 40 NODRAFT; p18r 263 DIFFER. Next breadth range 301–400 insns.
4. difftest: compare stack memory passed to callees by address (the func_15008BF0 blind spot).

## State (session P17, 2026-10-22). Details: `docs/port/sessions/P17.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems (821 bodies; the nm_asm functions are not counted).
- **506 NON_MATCHING bodies** (+175). progress_nm: C coverage including NON_MATCHING **4498/5913 (76.1%)**, bytes 38.6%:
  init 477/538, game 3983/5332, debugger 38/43; **1415 asm-only** (176 under 60 insns).
- The 7 reverted P16 EQUIVs are in (NM prototype wraps; float-as-`s32` call sites rewritten under NM; func_1516295C's tables
  are the real 5-entry ROM tables in `.rodata`).
- Re-evaluating 227 old non-EQUIV drafts with the P16 tooling (`port_work/p17r/`): **22 flipped to EQUIV** (13 DIFFER, 6 UNSURE,
  2 HANG, 1 CERR); 23 inserted. The segfault class was real but small.
- **difftest false DIFFER found:** some candidate float literals read as 0. Workaround `cfix.fix_litsym` (literal → the
  `D_X` rodata word the asm loads), now first in convert.py's DFIXES: +19 from old DIFFERs, 20 of the batch EQUIVs.
- Batch p17b (406 untried asm-only, 121–200 insns): 132 lint-clean EQUIV (33%), 124 inserted (8 reverted: list in P17.md).

## Next steps (from P17)

1. Fix the float-literal bug in difftest itself (P17.md §3), then re-run all DIFFER rows; put literals back in litsym bodies.
2. Add a per-trial wall limit to difftest's forked trials (orphaned hung grandchildren after a convert HANG).
3. User decision: `convert.py --tag p17c` (33 self-redeclaration CERRs with `cfix.fix_selfproto` registered) was denied by
   the auto-mode classifier; `fix_selfproto` exists but is unregistered/untested.
4. p17b near misses: 96 DIFFER, 110 CERR, 58 NODRAFT; the 8 reverted bodies; next breadth range 201–300 insns.

## State (session P16, 2026-10-22). Details: `docs/port/sessions/P16.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems. difftest selftest 20/20.
- **331 NON_MATCHING bodies** (+88). progress_nm: C coverage including NON_MATCHING **4323/5913 (73.1%)**, bytes 34.4%:
  init 474/538, game 3811/5332, debugger 38/43; 1590 asm-only (197 under 60 insns).
- **Unicorn segfaults fixed at the root:** any `uc_close` (unicorn's GC finalizer) made a later emulator segfault. difftest now
  runs each trial in a forked child that never closes its emulators (`DIFFTEST_NOFORK=1` = old way). convert.py no longer
  uses a Pool (the deadlock): one forked child per function, file results, wall-clock kill, seed retry on crash, `CRASH` rows.
- Batch p16 (284: 12 P15 leftovers + all untried 80–120 insns): 86 lint-clean EQUIV (31%), 78 inserted, 7 reverted for prototype
  conflicts / NM link (list in P16.md). Hand bodies: func_150D0420, func_1509BA04, func_1501C55C, func_15114708, func_1000D758,
  func_15085710, func_15019F20, func_1509BBA0, func_1501C1B0, func_1507C8FC.

## Next steps (from P16)

1. Re-insert the 7 reverted p16 EQUIVs after prototype fixes; then p16 DIFFER (101) / CERR (55) near misses.
2. Re-run older DIFFER/UNSURE rows whose cause was a segfault (they may pass now).
3. Stub-hit still asm: func_1504A730, func_10011624, func_151143D4 (draft in `port_work/p16h/`), func_15044D18.

## State (session P15, 2026-10-22). Details: `docs/port/sessions/P15.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems. difftest selftest 20/20.
- **243 NON_MATCHING bodies** (+67). C coverage including NON_MATCHING is **4235/5913 (71.6%)**, bytes 32.7%: init 472/538, game 3725/5332, debugger 38/43; 1678 asm-only (196 under 60 insns).
- Breadth batch (`port_work/p15/`): 145 untried asm-only functions of 60–79 insns, 54 EQUIV by convert.py + 7 hand-repaired
  (42%); 60–69 insns 44%, 70–79 insns 33% (convert only). 12 functions never ran (the convert.py pool deadlocked; list in P15.md).
- Stub-hit callees now C: func_15084E80, func_15114F9C, func_1510BC10, func_1501E46C, func_150619A8, func_1501A490,
  func_1502457C, func_150A09D0. `func_1506D584` is void under NON_MATCHING (functions.h wrap).
- Tools: `DIFFTEST_TIMEOUT` (default 600 s) in difftest.sh; difftest compiles with `-DNON_MATCHING`; protocheck reads headers
  through the NM view.

## Next steps (from P15)

1. Re-run the 12 unevaluated batch functions (P15.md) with a new tag; look at the convert.py pool deadlock.
2. Near misses in `port_work/p15/results.tsv` (32 DIFFER, 18 CERR) and the rest of the stub-hit list (P15.md "Next").
3. Browser runtime checks: func_1510BC10, func_1501E46C, func_15084E80, func_150802A8, plus the P13 list.

## State (session P13, 2026-10-22). Details: `docs/port/sessions/P13.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems. difftest selftest 20/20.
- **176 NON_MATCHING bodies.** C coverage including NON_MATCHING is **4168/5913 (70.5%)**, bytes 31.8%: init 471/538, game 3661/5332,
  debugger 36/43; 1745 asm-only (196 under 60 insns).
- **The browser's live-frame blockers are C:** `func_15007B3C` (level loader: DL buffers, pad timer), `func_15019130` (world
  update), `func_eu_1501C860` (frame submit), `func_1502AB04` (asset cache insert), `func_1510BA9C`, and the frame-builder
  callees `func_150195A0`, `func_15019CC8`, `func_151412BC`, all EQUIV. `func_15043384` (text/icon flush) is EQUIV on random
  inputs only: the icon path needs a runtime check.
- Browser: drop the P11 overrides and the `osContInit` SI shim after merging. The P11 `func_eu_1501C860` override has the ucode
  choice on `D_800BEFC0` inverted.
- difftest: the call-site scan stops at an earlier delay slot, unnamed callees use the `func_<ADDR>` prototype, and leading float
  params skip a0/a1. New knob: `DIFFTEST_RET="ADDR=VAL"`. asm `D_80082FA0` is EU 0x80083330 (POKE that address).

## Next steps (from P13)

1. Browser runtime check of the P13 bodies (first frame should now render), especially `func_15043384` icons and `func_15007B3C`.
2. Remaining callees: func_15084E80 (DIFFER), func_15114F9C (UNSURE); then the P8 stub-hit list and the breadth batch.
3. Add a container-side `DIFFTEST_TIMEOUT` to `tools/port/difftest.sh` (macOS has no `timeout`; P13 used `docker exec ... timeout`).

## State (session P12, 2026-10-22). Details: `docs/port/sessions/P12.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems (821 bodies; the nm_asm functions are not counted).
- **167 NON_MATCHING bodies.** C coverage including NON_MATCHING is **4159/5913 (70.3%)**, bytes 31.5%: init 471/538, game 3652/5332,
  debugger 36/43; 1754 asm-only (197 under 60 insns).
- **Audio start-up is all C:** `func_10008180` (audio init) EQUIV, `func_10009CBC` (sound loader / DMA callback) EQUIV
  (the eviction path via `DIFFTEST_POKE="80040A48=0"`). Runtime check owed: the browser should now get audio tasks
  (this also checks `func_10008F90`, UNVERIFIED past n_alInit).
- Frame-builder callees: `func_151E5928`, `func_15019464` EQUIV. `func_1517F51C` has a one-arg signature under NON_MATCHING.
- **Needs a user decision:** a difftest I started for `func_1510BA9C` (container PID 41060, host task `b1m0geqzn`) hung.
  The auto-mode classifier denied killing it and denied setting up a bounded re-run, so it may still be running.
  The draft `port_work/p12/func_1510BA9C.c` is unverified and not inserted.

## Next steps (from P12)

1. After the stuck difftest is dealt with: verify `func_1510BA9C` (POKE the player count `D_80082FA0` small), insert it.
2. Remaining frame-builder callees in call order: func_15019130 (convert.py EQUIV in `port_work/p12_cal/pass/`, but
   lint:proto with 39 guessed prototypes: clean it before inserting), func_150195A0, func_15019CC8, func_15043384,
   func_15084E80, func_15114F9C (UNSURE), func_eu_1501C860, func_151412BC. NODRAFT for 195A0/19CC8/43384/412BC: hand drafts.
3. Then the P8 stub-hit list, then the breadth batch (convert.py `--jobs 4` over ~200 small asm-only functions).
4. r7 rerun: still in p2A at P12; collect `port_work/r7_*/pass/` for later tags when they appear.

## State (session P10, 2026-10-22). Details: `docs/port/sessions/P10.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems (821 bodies; the nm_asm functions are not counted).
- **163 NON_MATCHING bodies.** C coverage including NON_MATCHING is **4155/5913 (70.3%)**, bytes 31.4%: init 469/538, game 3650/5332, debugger 36/43; 1758 asm-only (197 under 60 insns).
- **Browser blockers done:** `func_1501BBB8` (controller read) EQUIV, `func_1501878C` (frame step / DL builder,
  G_LOAD_UCODE) EQUIV over 512 OUTPARAMS trials. `func_15019E60`/`func_150198FC` now return `Gfx *` (their value was used).
- Texture pipeline: `func_1510D66C` EQUIV on both paths (miss path via `DIFFTEST_POKE`), `func_1510D984` EQUIV,
  `func_1510D3E0` **UNVERIFIED for ids >= 0x1E54** (the original overruns its stack bitmap there; the C bounds-checks).
- `func_150159E8`, `func_1515DC40` EQUIV; `func_151674F8` EQUIV except a test artifact (layer pointer into its own code).
- Audio: `func_10008F90` (amCreateAudioMgr, s125 draft + u32 frame-size fix) **UNVERIFIED past n_alInit** (stack-address
  field differs by frame layout): needs a runtime check.
- r7 p2A EQUIVs inserted (`func_15007440`, `func_150416EC`, `func_1507DFE4`).
- New: `DIFFTEST_POKE="ADDR=VAL[*N],..."` fixed input words; protocheck knows macros / fn-pointer calls.
- **The r7 rerun is still running** in conkerdev-port (`RERUN_PREFIX=r7 tools/port/rerun_p5.sh ...`, at hand-off
  still on p2A's last function, then p2B, b_rest_00..03, b_boot2). Do not kill it. Collect `port_work/r7_*/pass/`
  for the later tags (check lint in `results.tsv`), `insert_nm.py`, protocheck, verify_all.

## Next steps (from P10)

1. **Audio (browser P9 asks):** `func_10008180` (audio init, 214 insns), `func_10009CBC` (on-demand sound loader, 208),
   then runtime-check `func_10008F90`.
2. `func_1501878C`'s asm callees: func_15019130, func_15019464, func_150195A0, func_15019CC8, func_151E5928, func_151412BC,
   func_1510BA9C, func_15043384, func_15084E80, func_15114F9C, func_eu_1501C860, func_15096D44. Then P8's ranked list
   (`~/conker-wt/web/docs/port/sessions/P8.md`).
3. difftest gaps seen in P10: an explicit `(void)` callee whose call site loads a0 for other reasons is a false DIFFER
   (the opt-in to trust `(void)` was denied by the auto-mode classifier; needs a user decision). Stack addresses stored in
   memory compare raw (func_10008F90). Unicorn segfaults (exit 139) on long loops (func_1510D984: 4/7 seeds).

## State (session P7, 2026-10-22). Details: `docs/port/sessions/P7.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems (821 bodies; the nm_asm functions are not counted).
- **151 NON_MATCHING bodies.** C coverage including NON_MATCHING is **4143/5913 (70.1%)**, bytes 31.0%:
  init 468/538, game 3639/5332, debugger 36/43. There are 1770 asm-only functions.
- **Guard:** every tools/port script exits 3 unless `CONKER_ROOT` is set, equals the script's checkout, and equals the cwd's git
  toplevel (`tools/port/portguard.{py,sh}`). The `eval "$(tools/eu_port/wt.sh env port)"` is now enforced.
- New bodies:
  - `func_100049E0` (scheduler thread) is **UNVERIFIED-difftest, needs runtime check**. It is an infinite loop, so
    difftest can only return UNSURE. No difference was seen in 10 trials.
  - `func_10003C6C` (allocator) is EQUIV for valid `arg2` (0–4). It needs a runtime check.
  - `func_1502AC88` (ROM record MRU cache) is EQUIV, but only the miss path was exercised.
- difftest: trailing-padding fix (a matched `--self` false DIFFER), libultra/reference-only arity, and opt-in
  `DIFFTEST_OUTPARAMS=1` (stubs write through stack out-params). There is an open Unicorn mis-run on IDO jump tables in long
  loops, plus random segfaults (exit 139). See P7.md.

## Next steps (from P7)

1. Browser-critical, still asm: **func_1501BBB8** (controller pad read per frame: OSContPad[4] at sp38, b_boot2 draft
   has one CERR `sp.u38 = 0`) and **func_1501878C** (412 insns, no draft).
   Then P8's list: **func_1510D66C** (texture cache), **func_1510D3E0** (patches texture-id 0xFD commands in model DLs),
   **func_1510D984** (per-frame cache ageing), **func_150159E8** (95 calls per 10 s of boot).
   Do not convert `func_100061F8`/`func_150ADA20`: the browser branch has PC overrides for them.
2. The re-run `RERUN_PREFIX=r7 tools/port/rerun_p5.sh p2A p2B b_rest_00 b_rest_01 b_rest_02 b_rest_03 b_boot2` was started in the
   background in P7 (log `port_work/r7_all.log`, results `port_work/r7_<tag>/`). It is slow: p2A alone took about 40 min. If it was
   killed, restart it for the unfinished tags. p2A gave 3 lint-clean EQUIVs that are **not inserted yet**: `func_150416EC`,
   `func_1507DFE4`, `func_15007440` (`port_work/r7_p2A/pass/`). Insert them with `insert_nm.py`, then run protocheck and verify_all.
3. Consider making `DIFFTEST_OUTPARAMS=1` the default (run selftest first). Also re-check the earlier EQUIVs whose code depends on out-params.

## State (session P5, 2026-10-22). Details: `docs/port/sessions/P5.md`

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `make VERSION=eu NON_MATCHING=1` links.
- **148 NON_MATCHING bodies** (P2: 127). C coverage including NON_MATCHING is **4140/5913 (70.0%)**, bytes 30.9%:
  init 466/538, game 3638/5332, debugger 36/43. There are 1773 asm-only functions (198 under 60 insns). The boot path (`boot_depth3.txt`) has 84 asm-only left.
- **difftest needs Unicorn 2.0.1** (2.1.x mis-runs calls whose delay slot is an FPU instruction). Install it once per worktree:
  `docker exec $CONKERDEV pip3 install --target /conker/port_work/pyuc201 unicorn==2.0.1.post1`. difftest picks it up automatically.
  Stubs are now real `jr ra` code, ld/sd/daddiu are emulated, and an overlapping candidate runs at an alternate base. selftest passes 20/20.
- protocheck reads files as the NON_MATCHING build sees them and reports 0 problems. The convention for a matching-code prototype that disagrees with a body:
  wrap it in `#ifdef NON_MATCHING <body's signature> #else <old> #endif`. Inside an NM body, change it directly; never nest.
- **ALWAYS** `eval "$(tools/eu_port/wt.sh env port)"` in the same shell call as insert_nm.py / protocheck.py / progress_nm.py
  (they default to ~/conker). P5 wrote 17 bodies into ~/conker by mistake. That still needs a user revert (see P5.md "Incident").

## Next steps (from P5)

1. Finish the re-run: `tools/port/rerun_p5.sh b_boot2 p2A p2B b_rest_00 b_rest_01 b_rest_02 b_rest_03` (background, about 1 h).
   Insert the lint-clean EQUIVs, then run protocheck and verify_all.
2. P4 priority list (`~/conker-wt/web/docs/port/sessions/P4.md`). Done: 10005BE0, 10001420, 15015FBC, 15003570, 15006234,
   150158D0, 15172C50, 10004074. **Open, in order:** 1501878C (412 insns), 1501BBB8 (278), 1502AC88 (159), **10003C6C
   (allocator, 258; returns 0 in wasm)**, 15085710, 100052A0, 10005B04 (56), 100049E0, 10008180, 15043384, 1509BA04,
   150A00F0 (43), 15007B3C, then 1515DC40, 151674F8, 151412BC, 151E5928, 1510BA9C, 15019130/19464/195A0/19CC8.
   PC replacements needed: `func_100061F8` (TLB writes, no-op), `func_150ADA20` (guRandom, u64 C given in P5.md).
3. difftest gaps: callee out-params are never written (code behind `if (*out)` is untested). Doubleword ALU ops are not emulated.
   Random function-pointer tables are slow (`func_15013000`; a draft in `port_work/p5/`).
4. Earlier items: P2 steps 3–4 below (near-miss fan-out, NODRAFT hand drafts).

## State (session P2, 2026-10-21) — read `docs/port/sessions/P2.md` for details

- The default build is byte-identical: full `verify_all.sh` OK, 3992/5913 matched (unchanged).
- **127 NON_MATCHING bodies** (P1: 9). C coverage including NON_MATCHING: **4119/5913 (69.7%)**;
  init 461/538, game 3622/5332, debugger 36/43; 1794 asm-only (208 under 60 insns).
  Run `python3 tools/port/progress_nm.py` (after verify_all regenerates `conker/progress.csv`).
- Pass rates with the P2 pipeline: pilot A 13/30 (43%, was 30%), pilot B 7/30 (23%, was 10%);
  batch: boot path 22/121, small (<60 insns) 86/261 (33%).
- `make VERSION=eu NON_MATCHING=1` links again (NM-only `.nm_rodata` NOLOAD section for C literals).
- New tools: `tools/port/{cfix.py, nmrepair.sh, nmrepair.py, progress_nm.py, protocheck.py}`.
  convert.py has the new fix chain (spframe, u8arith, cmp2, deref, rostr, passthru2, proto);
  difftest learns pointer inputs when the reference faults, and `-v` explains a DIFFER.
- **One prototype per function (P3/wasm):** run `python3 tools/port/protocheck.py` before every
  commit that inserts bodies. convert.py flags `lint:proto` and repairs it with `cfix.fix_proto`. Open:
  `func_150AD9A0` (callers disagree: 3 vs 4 args), `func_150A2280`; `func_10004074`/`func_10007D14`
  not inserted (void vs s32 callers in matching code).

## Next steps (from P2)

1. difftest: the Unicorn `UC_ERR_EXCEPTION at 0x00000000` after a stubbed call returning into a branch
   (UNSURE `func_150B0574`, `func_151DAE28`; many `fault only in cand` DIFFERs). This is likely a false
   negative and the biggest single win. Also `sd`/`ld` (MIPS III) need UC_MODE_MIPS64 or emulating them in a hook.
2. Boot path for P3: 99 boot asm-only functions remain (list `tools/port/pilot/boot_depth3.txt`, BFS depth 3 from `func_15007830`, see
   P2.md). Hand repair with `tools/port/nmrepair.sh f` from `port_work/b_boot2/best/`; re-run
   `func_150158D0`, `func_15084E80`.
3. Fan-out hand repair of the batch near misses (`port_work/b_*/results.tsv`: 96 DIFFER, 68 CERR).
   86 NODRAFT need hand drafts (gen2 rejects the m2c output).
4. Caller-side prototype fixes for NON_MATCHING (wrap conflicting prototypes in matching files in
   `#ifdef NON_MATCHING`), coordinated with P3's list of 262 mismatched calls.

## P1 notes (still valid)

## State (session P1, 2026-10-21)

- The default build is byte-identical: full `verify_all.sh` OK, 3992/5913 matched functions (unchanged).
- NON_MATCHING bodies so far: 9 functions (the pilot EQUIVs). List them with
  `grep -c '^#ifdef NON_MATCHING$' -r conker/src_eu`.
- Tools added: `tools/port/{difftest.sh, difftest/difftest.py, difftest/selftest.sh, convert.py, insert_nm.py, nm_layout.py}`.
  The Makefile now has `NON_MATCHING=1`.

## Convention

```c
#ifdef NON_MATCHING
s32 func_150FB708(u8 *arg0) { ... }        /* functionally equivalent C (difftest EQUIV) */
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_127840/func_150FB708.s")
#endif
```

- `//HOIST` declarations go into one `#ifdef NON_MATCHING // hoisted ...` block after the last
  `#include`. `//DROP` lines are wrapped in `#ifndef NON_MATCHING`. Both only take effect in
  NON_MATCHING mode, so they can never change the matching build.
- `make -C conker VERSION=eu NON_MATCHING=1 -j8` (inside the container) adds `-DNON_MATCHING`,
  builds into `conker/build_nm/` (the ld script is rewritten with sed `build/` → `build_nm/`) and
  skips the sha1 verify. The matching `build/` is not touched.

## difftest (`tools/port/difftest.sh FUNC [draft.c] [--self] [--trials N] [-v] [--json]`)

- Reference: the words of `asm/nonmatchings/.../FUNC.s`, or `conker.eu.bin` at the function's EU
  address for C functions with `--self`.
- Candidate: the draft compiled by IDO with the file's exact flags, in a standalone TU built like
  `m2c/screen.py` (other pragmas dropped, other NON_MATCHING blocks resolved to C). It is relocated so
  every symbol gets its EU address from the symbol files, and the TU's `.rodata/.data/.bss` go to 0x80700000.
- Unicorn MIPS32 BE. Memory pages are created lazily with deterministic pseudo-random words: zero,
  small ints, packed small halfwords/bytes, heap pointers (0x80400000–0x80600000), floats
  (including 0/±1/0.5/2/100), noise. Code and rodata are mapped from the ROM image. Odd trials also
  use the ROM's initial `.data`; even trials use random globals.
- Arguments follow the candidate's parameter types (pointer → heap, int → small/-1/16-bit/noise,
  float/double → f12/f14 under the o32 rules) plus 12 random stack-arg words.
- Callees outside the function body are stubs. Each logs (address, a0–a3 up to the arity, stack args
  in the contiguous run from sp+0x10, f12–f15 if set, and a hash of the non-stack memory written so far).
  It returns deterministic random v0/v1/f0/f2 and clobbers the caller-saved registers. Arity comes
  from the TU prototype, or else from which a-registers the call site writes (`call_site_writes`).
- Compared: the call trace, memory at each call, the final memory writes outside the stack, the
  return value (from the candidate's declared return type), and sp, s0–s8, f20–f30. Pointers into
  the stack compare equal. A candidate TU-local object (a string or table literal) compares equal
  to the reference address if the first 32 bytes match.
- Verdicts:
  - `EQUIV`: no difference, and at least `max(4, trials/8)` trials ran to completion.
  - `DIFFER <reason>`: the first difference.
  - `UNSURE`: too many trials ended in a fault or timeout. A fault in the reference only makes the trial
    inconclusive (the input was invalid). A fault in the candidate only is DIFFER.
  - `CERR`: compile error, with the offending lines after `@@`.
  - `ERROR`: setup problem.
- Speed: about 0.3–2 s per function at 64 trials. `DIFFTEST_BUDGET` (30 s) caps the time per check.
- `tools/port/difftest/selftest.sh`: 5 matched functions → EQUIV, 7 mutants → DIFFER, and one mutant
  that is semantically equivalent (`>` → `>=` where both branches give 0) → EQUIV. All 13 pass.

**Limits (read before trusting an EQUIV):**
- **Pointers passed to callees are not dereferenced.** A stub never reads or writes through its
  arguments. So `&sp1C` with scalar neighbours `sp20, sp24...` (an m2c vector split into scalars) passes
  if IDO happens to keep the layout, but it is wrong for clang/wasm. convert.py flags this as
  `lint:stackaddr`. Fix those drafts with `tools/eu_port/vecfix.py` / `spstruct.py` (make it an array
  or struct) before they go to Phase 3.
- Out-params: callee writes are not modelled, so code that reads a value back from a callee-filled
  buffer sees zeros/random in both runs and is only compared for consistency.
- FP: results are compared bit-exactly, and the operands are random. NaN payloads and exact rounding
  corner cases are covered only by chance. Reassociated FP expressions report DIFFER, which is
  correct.
- Big loops / large memory: capped at 100k instructions per run (`--max-insns`). Loops that are
  bounded by random data time out in both runs (inconclusive). The coverage of long paths is poor.
- TLB addresses 0x15xxxxxx/0x16xxxxxx: kuseg is mapped identity (no TLB). Code that computes code
  addresses or reads its own code works on the ROM image, but self-modifying or DMA'd code is not
  modelled. kseg2 (0xC0000000+) accesses fault (inconclusive).
- rand / time: callees such as `rand` are stubs with deterministic returns. That is fine as long as
  both versions call them the same number of times in the same order.
- Indirect calls through random function pointers land in stubs keyed by the random address.
  They are consistent, but nothing checks that the pointer came from the right table entry beyond
  the address itself.
- Hardware access (`0xA4xxxxxx`) is random RAM: no side effects are modelled.
- Callee arity is inferred. A wrong K&R/implicit prototype in the TU plus an a-register that the
  candidate does not write can hide a missing argument when the reference doesn't write it either
  (a pass-through), but then the values are equal anyway.

## convert.py (`tools/port/convert.py --tag T (-l list | FUNC...) [--insert] [--no-gen] [--trials N] [--jobs J]`)

1. gen2.py (`JT=1 LAX=1`) with typed contexts (`TYPED=1` → `gen/v0..7`) and untyped ones (`gen/u0..7`),
   `narrow.py` variants (`nv*`, `nu*`), and `argfix.py --tail` variants (`av*`, `au*`). That is up to
   48 drafts per function. Typed needs `python3 tools/eu_port/fieldinfer.py --report` once per worktree
   (already done here).
2. In the container, with 8 processes: each distinct draft goes through difftest. On CERR, autofixes
   run in a chain: `implproto` (hoist the prototype of a function that is used before its prototyped
   definition), `cmpcast`, `fnptr` (fnptrfix.py), `redecl`, `qtypes`, `undecl`, `argc`. On DIFFER the
   `passthru` fix runs: when the callee needs `aN` that m2c dropped, the caller's own `argN` is inserted.
   Up to 6 rounds per draft and `CONVERT_BUDGET` (150 s) per function.
3. Output in `port_work/T/` (gitignored): `results.tsv` (func, verdict, variant, fixes+lints, reason),
   `attempts.tsv` (every attempt), `pass/<f>.c`. With `--insert`, the EQUIV ones are inserted.
   Re-run `verify_all.sh` afterwards.

## Pilot results

Two pilots, chosen at random with a fixed seed, one function per file (`tools/port/pilot/pilot30*.txt`;
results in `tools/port/pilot/pilot30*_results.tsv`):

| pilot | size (insns) | EQUIV | DIFFER | CERR | NODRAFT | UNSURE | HANG |
|---|---|---|---|---|---|---|---|
| A `pilot30` | 8–80 | **9 (30%)** | 9 | 7 | 3 | 1 | 1 |
| B `pilot30b` | 81–200 | **3 (10%)** | 11 | 11 | 2 | 3 | 0 |

- Of the 12 EQUIVs, 4 are flagged `lint:stackaddr` (`&spXX` of a scalar local passed to a callee).
  They are fine on IDO but must become arrays or structs before the wasm build.
- The 9 pilot-A EQUIVs are inserted as NON_MATCHING bodies; verify_all is OK. The pilot-B EQUIVs
  (`func_15060BE0`, `func_150BE7E8`, `func_151BCD44`) are in `port_work/pilot30b/pass/` but not
  inserted yet.
- About 20 s per function of wall time (8 workers), dominated by the m2c generation and the up to 48 drafts.

Failure reasons, both pilots (60 functions):

| count | reason | what it means / next fix |
|---|---|---|
| 8 | DIFFER: wrong call argument | m2c arity/pass-through mistakes, typed `struct127 *` pointer arithmetic scaling byte offsets (`p += 0x32C`), `""` emitted for an unnamed rodata symbol, float args in GPRs. The `passthru` autofix sometimes fixes them; sometimes it inserts the wrong param (an `&local` was expected). |
| 5 | CERR `'spXX' undefined` | m2c stack locals it could not type. Autofix idea: declare `u8 spXX[N]` sized from the frame. |
| 5 | NODRAFT | gen2 rejects m2c output (M2C_ERROR etc.); needs a hand draft |
| 4 | DIFFER call count | control flow mis-decompiled (conditions, loop exits) |
| 4 | UNSURE | every trial faults in the reference: these functions need valid pointer graphs (nested struct pointers). Idea: a per-function "input template" option in difftest. |
| 3+3+1+1 | CERR operand type errors (`==` pointer vs int, deref of non-pointer, `&` on non-lvalue, non-lvalue) | typing errors in drafts. `cmpcast` handles only simple cases; an expression-level retyping pass (everything `s32`/`u8 *`) would help. |
| 3 | DIFFER memory state before a call | a missing or extra store |
| 2 | CERR redeclaration | conflicting prototypes in the headers vs the draft |
| 2 | DIFFER timeout/fault only in cand | loops that never end (wrong loop variable) or extra loads |
| 1 each | fn-pointer tables, sinf argument, unaligned-fault mismatch, syntax error, missing array size, hang | |

**Planning consequence:** expect about 20–30% automatic conversion on small functions and about 10% on
mid-size ones. The remaining ~1890 functions are 75% above 50 instructions. So Phase 1 is mostly
**hand repair against difftest**, with convert.py as the first pass that also gives each
function a ready reason (`attempts.tsv`).

### Hand-repair loop (what fan-out sessions do)

1. `python3 tools/port/convert.py --tag <range> -l <list>` (in the background) for a file range.
   Use `pilot/all_asm.tsv` for name/size/file.
2. `--insert` (or `insert_nm.py f port_work/<tag>/pass/f.c`) for the EQUIVs. Then run `verify_all.sh`
   and commit.
3. For each failure: read the best draft (`port_work/<tag>/gen/<variant>/f.c`, plus the fixes listed
   in `attempts.tsv`), the asm (`tools/eu_port/sh.sh f`) and the difftest reason. Edit, then run
   `tools/port/difftest.sh f draft.c -v` until EQUIV. Use a struct/array for any stack object whose
   address is taken (no `lint:stackaddr`). Code quality matters more than matching: this C becomes
   the PC source.
4. Matching is not required: drop permuter-style tricks; prefer readable, typed code.


## NON_MATCHING build: status and blockers

- `make VERSION=eu NON_MATCHING=1` **compiles and links** with the 9 bodies (`build_nm/conker.eu.elf`).
- `tools/port/nm_layout.py` (container, from `conker/`) compares the two ELFs. With the 9 bodies
  `.game` is 16 bytes smaller, and **2771 functions moved** (the first is `func_150851E0`, +20). The data
  did not move this time; it will once C rodata sizes differ.
- Blockers for a ROM that boots:
  1. **The data is not shiftable.** The game/init data are incbin'd blobs (`assets/*.databin.bin`,
     `*.rodatabin.bin`). They hold raw addresses of functions, jump-table targets of every GLOBAL_ASM
     function, and data pointers. The 9,557 `D_` symbols are absolute linker assignments. Any move
     breaks them. Fix: PLAN Phase 2A (trampolines, address-stable) or 2B (symbolize the data).
  2. **rzip packing** (`build_nm/conker.eu.game.rzip.bin`): `compress_dir.py` needs the bundled
     x86 `tools/gzip`, which fails in the arm64 container (`ERROR calling gzip`, then a NameError in
     the script). Run it in the x86 image `conker` (as `verify_all.sh` does). `TEXT_SECTION_LENGTH`,
     `DATA_SECTION_LENGTH` and the code padding are fixed in the Makefile and must be recomputed if
     the code grows.
  3. `make replace` copies the built segments into `../assets/` (shared with the matching build).
     A NON_MATCHING ROM needs its own outer build target (e.g. `assets_nm/`). This has not been written.

## Next steps

1. **P2: conversion throughput (one session).** Improve convert.py on the measured failure
   classes before fanning out:
   - an `'spXX' undefined` autofix;
   - an expression-level type relaxation for the CERR operand errors;
   - stop TYPED drafts scaling byte offsets (`struct127 *` + const), or fall back to untyped;
   - an m2c `""`-string fix (pass the rodata symbol names);
   - a smarter `passthru` (prefer an `&local` when the reference passes a stack address);
   - per-function input templates for the UNSURE class.
   Add `tools/port/nmrepair.sh f` (asm + best draft + difftest -v reason in one view). Re-run both
   pilots to measure, then convert the ~210 functions under 50 insns in batches with
   `--insert` + `verify_all.sh`.
2. **P3 (can run in parallel, different worktree): Phase 3 skeleton.** Add `Dockerfile.emsdk` (emsdk
   in a container, no host installs), a CMake build that compiles the matched C plus the
   NON_MATCHING bodies for wasm32 with libultra stubs (`src/pc/ultra`), and a "hello frame"
   page. This finds the wasm compile errors in the existing C early (IDO-isms, K&R calls,
   `GLOBAL_ASM` leftovers need stubs). Also prototype the ASYNCIFY fiber scheduler for
   `osCreateThread`/`osRecvMesg` (PLAN 3.8), the biggest design risk.
3. Then: fan-out hand-repair sessions over disjoint file ranges (2–3 at a time). In parallel, Phase 2b
   data symbolization (datarefs.py → `.word sym` data files), which unblocks a shiftable
   NON_MATCHING ROM and the wasm data layout.

Known tool issues:
- `func_150416EC` hung a worker before the SIGALRM guard was added (convert.py now records `HANG`).
  It was not re-run.
- Docker Desktop's file sync can lag: a file edited on the host may be seen half-written in the
  container for a second. Wait for the sync to settle before re-running a tool that was just edited.
- Never run two convert.py jobs on the same `--tag`: they share `results.tsv`.

