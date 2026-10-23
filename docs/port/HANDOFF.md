# Port hand-off (branch `port`, worktree `~/conker-wt/port`)

Read `docs/port/PLAN.md` first: the phases, the browser-first target (wasm32/Emscripten) and the
risks. The decomp rules in `tools/eu_port/AGENT_BRIEF.md` and `HANDOFF.md` still apply: worktree
env, `verify_all.sh` before every commit, background jobs, the commit trailer.

```sh
cd ~/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"   # CONKER_ROOT, CONKERDEV=conkerdev-port
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
docker exec conkerdev-port python3 -c 'import unicorn'            # if missing: pip3 install --break-system-packages unicorn
```

## State (session P103, 2026-10-23, port-web). Details: `docs/port/sessions/P103.md`

- **Boot path (from the code):**
  1. func_151E582C sets mode 11 and loads level 0x25: the boot screen func_151DEBB4 / func_151EC300 (NTSC
     osTvType freezes it: region lock).
  2. At timer 0x2C7 the game goes to **mode 1 / level 0x21 = "LogoScreen"**. This is correct and matches the N64.
  3. Then the menu: mode 3 / level 0x1D (func_151DEDD0, asm), reached through event / scene actions (scene opcode
     0x67 -> func_151DECB4).
  4. Then a game: func_151E3864 / func_151E3A1C -> mode 0 (func_151DE100, asm).
  - Mode table D_8009018C and render table D_80090370: P103.md section 1.
- **Why the port stays on level 0x21: the level event system is asm.**
  - Level 0x21 has one level event, **0xC9 "LogoScreen"**, with no prerequisites.
  - The prerequisite check **func_1509CBD4** (stub, so 0) blocks it. Past that check, **func_1509B5AC** (start
    event) is a stub too, and so is the event VM **func_150ADFD0**.
  - Evidence: `?p103boot=1` / `?p103ev=1` logs in P103.md section 2.
- **World objects are 0 on every level because func_150039E0 (world-object loader, 741 insns) is a stub.** This
  corrects P101's "0 objects = level data".
- **D_8009018C[0] = raw 0x151DE100:**
  - Cause: func_151E86A4's code checksum uses func_151DE100 as data, so n64mem skips that word (the only `F-data`
    word).
  - It is not reached before the menu. When it is, it traps (`table index out of bounds`).
  - Fix it together with converting func_151DE100: guard the checksum under PORT, then remove the data stub.
- Port: DIAGNOSTICS `?p103boot=1`, `?p103ev=1` (port/gfx/p103_boot.c, 4 wraps, hook in p84_checks.c). No fix.

## Next steps (from P103)

1. Level events, as one unit:
   - func_1509CBD4 (48 insns);
   - func_1509B950 (45), together with the dropped-return fix: **func_1509B8FC must return func_1509B950(...)**;
   - func_1509B5AC (86);
   - func_150ADFD0 (485), with func_150ADA20 / func_150AE760.
2. Re-run `?p103boot=1` and the census on level 0x21 for the LogoScreen script's action handlers (func_1509FD30 & co.).
3. func_150039E0 (world objects). Then func_151DEDD0 (menu, mode 3).
4. func_151DE100 (mode 0), with the PORT guard of func_151E86A4 and the D_8009018C[0] relocation.
5. P101's list (func_150000B0 music etc.) still stands.

## State (session P101, 2026-10-23, port-web). Details: `docs/port/sessions/P101.md`

- **The fall near (-179, 301) is not a collision bug.**
  - Level 0x21's only collision is model 0: 288 triangles in a flat 480 x 480 grid at y 0 (x / z -240..240).
    Areas 1-3 are empty, D_800B0E00[1..3] are NULL, there are 0 world objects and no wall triangles.
  - The pad script walks Conker past |z| = 240 (at about (-142..-154, 249..268); frame 773-917, depending on run
    speed). The C floor query then correctly returns -10000, and an independent float reference over every
    triangle agrees.
  - The data reads cleanly (a perfect 40-unit grid), so endianness and relocation are fine. No port or game-C fix.
  - Idle, he stands at (27, 0, 27).
  - Open: whether the real game gives stick control on level 0x21 (mode 1, entered by the boot-screen timer
    func_151DEBB4). That needs an N64 reference.
- **Music: the blocker is func_150000B0** (game_2D4B0.c, still asm).
  - It is the level-start music function, called by func_15007B3C at every level load. It reads song ids from the
    level header D_800B0DF0 +0x2C / +0x32 and requests them through func_1000D96C.
  - From func_1000D96C on, everything is C: func_1000B3D4 queues the song, then func_1000D758 -> func_1000D2F8 ->
    func_10008CE8 (n_alCSeqNew / play).
  - The header asks for song 0x35 on level 0x2C (volume 0x7FFF) and song 0x60 on the scene level 0. Level 0x21 has
    song 0.
  - func_10010154 / func_1000F568 are sound-effect emitters, not music.
- Census at HEAD (node 50 s): 52 distinct stubs. One death, scene, 0x2C warp, heap 0, null zone 0. List in P101.md
  section 3.
- Port: DIAGNOSTICS `?p101col=N` (collision dump at floor -> void) and `?p101mus=1` (func_150000B0 wrap, level header
  music fields), in p49_walk.c, plus a Makefile wrap.

## Next steps (from P101)

1. Convert func_150000B0 to readable C (asm/nonmatchings/game_2D4B0/func_150000B0.s, jump table jtbl_80091A30).
   - Its inputs and callees are all C or data. Then check in Chrome that song 0x35 plays on level 0x2C.
2. func_15020920 / func_15020090 / func_15020430 (scene producers; the P97 guard still fires).
3. Camera eye height: func_15126378 / func_1512EE50.
4. The per-frame stubs (P101.md section 3), then the player-state stubs hit from the spawn: func_1507E9A8,
   func_15141C0C, func_15146EE0, func_151DA6F8.
5. If an N64 reference becomes available: does level 0x21 (mode 1) really let the stick move Conker?

## State (session P99, 2026-10-23, port-web). Details: `docs/port/sessions/P99.md`

- **Bisect lesson:** game .c changes are not rebuilt unless `port/build/vbe.stamp` is removed (the stamp does not
  depend on the sources). P97's bisect builds were no-ops. `port_work/p99/bis.sh` removes the stamp.
- Camera at 30-36 s ("straight down") and the higher 41 s scene camera: **func_15124C38** (P92 C, game_14FF90.c),
  found with a real rebuild and a node camera metric.
  - The old asm stub never moved the target height (+0x2C0): it stayed at y 1 / 0.
  - The C eases it to player y + 67.5 and follows Conker down when he falls before the death. The eye height stays
    at 400 (still stubbed), so the view tilts to -77 deg.
  - Checked against the asm: correct. **No fix.** The real problems are the fall itself (it predates P93 / P95) and
    the stubbed eye height.
- Audio: no regression.
  - The only sound any run ever starts is the floor-material ambient loop 0x15 (func_1508000C). P91 stood on that
    floor by chance, and P91 walk3 was silent too.
  - `?p99snd=F` forces that start: Chrome rms 0.026, peak 0.25, PASS at HEAD.
  - No music is ever started (older gap).
- Port: the `?camwatch` pointer guard (it trapped at the death) and the `?p99snd` diagnostic, in gfx_f3dex2.c.

## Next steps (from P99)

1. Why the player falls below the ground near (-179, 301) at about node frame 805 (collision / floor producers).
2. The camera eye-height producer (cam +0x2FC fixed at 400): func_15126378 / func_1512EE50 (asm stubs).
3. The music start path (no sequence ever starts); the init_EB00 asm stubs func_10010154 / func_1000F568.
4. Then P97's list (func_15020920 & co., the per-frame stubs).

## State (session P97, 2026-10-23, port-web). Details: `docs/port/sessions/P97.md`

- Merged port b3219c2 (P90 / P93 / P95) and port-b 99d4923 (P92). Both had only HANDOFF conflicts (merge_union).
  - One semantic clash: func_151BF8F0 (game_eu_1EC610.c, port-b C) still declared func_15157580 arg2 `s32` and passed
    0x3F800000; P95 made it `f32`. Fixed in its NM block. **port-b needs the same change.**
  - verify_all OK, NM links, protocheck 984 / 0, float-int scan 0, clean port rebuild.
- **P92 scene path + stub producer = corrupted player.** With the stub func_15020920, func_1501FD34 writes a garbage
  player position (-1.4e29...) at the scene start. Then more deaths and a call_indirect trap in func_1504A730.
  - TEMPORARY guard (`p84_checks.c`): func_1501FD34 / func_1501FF10 skip; `?p97path=1` runs the real C.
  - With it: one death, scene, 0x2C warp, heap 0, null zone 0 (node + 3 Chrome runs).
- The 30-36 s camera now looks straight down. Bisected to merge 1, not P92 and not func_150268BC: it is in the
  P93 / P95 changes. Open.
- func_15124C38 is never called; its per-frame caller func_15126378 is still asm.
- Sound: 0 samples since P94 (before and after); open.
- Sky t range = the game's own math (pitch x 81 / 32, base 237..612); not a port bug.
- Arity 113 / 57 (unchanged).

## Next steps (from P97)

1. Convert func_15020920 / func_15020090 / func_15020430 (port-b), then drop the P97 guard and check the paths.
2. Bisect the top-down camera inside P93 / P95: the float-int fix files vs func_15083E0C / func_150ADA68 /
   func_15167010 / func_1517FCCC.
3. func_15126378 (camera height caller), then the per-frame stub list in P97.md section 5.
4. Audio silence since P94 (P91 had rms 0.024): bisect P91..P94.

## State (session P94, 2026-10-23). Details: `docs/port/sessions/P94.md`

- **The green hoodie in the respawn cutscene was a renderer bug.** Two bugs in character lighting
  (`port/gfx/gfx_f3dex2.c`), both fixed:
  1. G_LOAD_UCODE text and data were swapped, so DMEM was seeded from the RSP code. The "ambient" record 2 read the
     instructions 4B6B58F2 as the green-grey colour 4B6B58.
  2. The F3DEX.NoN lighting overlay was disassembled (`sessions/p94/f3dex_light.dis`). It shows:
     - start = record M (the ambient);
     - record M-1 = directional (n.d);
     - records M-2..0 = point lights.
     P35's model instead used the ambient as a sun (its direction was its own colour bytes) and ignored the white key
     light.
- The game's lights are fine and are the same in the scene and in play: white directional + ambient 7380B1 from
  func_1515EAB4 (C). No game C change.
- Before/after: `sessions/p94/P94_before_after_{36,41,45}000ms.png`, `P94_walk2_before_after_{50,58}000ms.png`.
  Rollback flags: `?p94oldseed=1&p94oldlight=1`.
- Green quad: the sky texture (4x256 RGBA32) is a blue -> white -> green gradient, and rows 222-255 are flat green.
  cmt clamp to lrt shows that row below about 58 % of the quad, which is correct RDP behaviour. The game's t range was
  not traced.

## Next steps (from P94)

1. Check character point lights (M >= 2) at runtime when a level sends them (new `[p94light]` lines under `?p78tex`).
2. Sky: trace the game's sky quad t range (292..667) and find out what draws the black area above it in the
   table-view camera.
## State (session P95, 2026-10-23). Details: `docs/port/sessions/P95.md`

- **Float bit patterns as ints** (`docs/port/sessions/p95/floatint_scan.py [--all] [--protos]`, NM-selected text of all
  src_eu C): 28 literal call rows (incl. the P93 suspects func_151D58E4 / func_15116A8C / func_151AD010; func_1514CBE8
  was already right in NM) and 17 TU-prototype-vs-definition float/int rows (`*(s32 *)` float fields / out-params
  passed to f32 parameters) fixed in 28 files, 0 left. Matching lines are duplicated under `#ifdef NON_MATCHING`, so
  the default build is unchanged. No row in port-b files. 4 REVIEW rows are packed s32 constants, not floats.
- **func_15035220** (game_eu_62360.c, reflection matrices + entry alpha) in hand C (NM): 30 setups EQUIV, mutants 23/23.
- **difftest hole 3**: arguments 16+ of the function under test were never set (and `DIFFTEST_ARG` >= 16 ignored); now
  generated up to sp+0xFC when needed. Selftest 43/43.
- Frame-path stubs in hand C (NM): func_1517FCCC (timers), func_15167010 (per-frame hooks), func_150ADA68 (random
  float; MIPS III, model-checked `p95/ada68/check.py`), func_15083E0C (setup entry by id).
- Default build byte-identical (full verify_all), NM links, protocheck 0 (931 bodies), progress_nm 4925/5915 (83.3%),
  bytes 58.0%, 990 asm-only.

## Next steps (from P95)

1. Frame-path stubs still asm (P91 list, by size): func_15044D18 (71E70), func_15097BA8 (C4590), func_15185360,
   func_1512D900, func_1517E3CC, func_151DA6F8, func_1510CE28, func_1510D090, func_1508F9F4, func_15113798,
   func_15184298, func_15178004, func_15113000, func_15188630, func_15181A6C, func_1517B270, func_1509093C,
   func_15129220, func_1512EE50. func_150ADA20 (random int, same LFSR as func_150ADA68) is still asm too.
2. Browser: water / mirror reflections (func_15035220 modes 0-2), func_15167010 hooks, random floats.
3. Scan gap: TU prototypes of asm-only callees are only checked where a literal is passed; a float/int check of TU
   prototypes against the callee asm (mtc1 / lwc1 of each argument) would close it.
4. Mutant harness: stubbed matrix callees hide the contents of stack matrices passed by pointer (func_15035220 flip /
   rotation); an option to run real C callees (func_150A7A48 / func_150A8050) would test them.

## State (session P93, 2026-10-23). Details: `docs/port/sessions/P93.md`

- Re-check of every NM body calling a >16-argument function (`p93/wide_scan.py`): 11 bodies + func_150268BC; 9 EQUIV with
  wide-argument mutants DIFFER (new window) / EQUIV (old); **2 real DIFFERs fixed**: func_150E6060 (func_150E2030 call
  in m2c's wrong 30-arg order; now the asm's 28) and func_150FD554 (0xC61C4000 passed as int to an f32: -10000.0f).
  6 hand-asm shared-frame rows N/A. No DIFFER in port-b files.
- difftest: callees declared only in include/functions.h with >16 args now get that arity (stack args 16+ of e.g.
  func_1513D594 were never compared); result-line notes `[POKE unread: ...]`, `[POKE in ROM data ...]`,
  `[knob callee never called: ...]`. Selftest 41/41 (5 new cases).
- P90 "POKE on per-track records": the setups used the US address 800C395C of D_800C3958 (EU 0x800C3D78). With
  800C3D7C: 26 record setups EQUIV, 12 record mutants killed incl. the 0x33 `rec + 0x18 -> 0x1C` survivor.
- func_15035AF8 (object draw queue, game_eu_62360.c) in hand C (NM): 38 setups EQUIV, mutants 22/23.
- Default build byte-identical, NM links, protocheck 0 (926 bodies), progress_nm 4920/5915 (83.2%), bytes 57.9%, 995 asm-only.

## Next steps (from P93)

1. func_15035220 (game_eu_62360.c, 526 asm lines, 19 args; prototype in the func_15035AF8 NM block).
2. Knob setups: read the result-line notes; `POKE unread` can list byte-loaded words falsely (Unicorn read hook), the
   callee note is reliable. Always take global addresses from the EU ELF (`mips-linux-gnu-nm build/conker.eu.elf`).
3. Browser: func_15035AF8 draws (fade, attachments); the 31 asm callees of func_150268BC (P90 list).
4. Possibly wrong hex-float int arguments (func_151D58E4, func_1514CBE8, func_15116A8C, func_151AD010 calls): check the
   callee parameter types.

## State (session P90, 2026-10-23). Details: `docs/port/sessions/P90.md`

- **func_150268BC** (script event interpreter, 3594 asm lines, game_eu_51190.c) is readable hand C under NON_MATCHING:
  270 knob setups (every type / sub-type / b4 / b5 variant, ARGMEM on all structs) EQUIV except 0x5F/4 (UNSURE, harness
  fault after the call); mutants 115 killed / 6 survived (explained in P90.md). 0x60 passes 0 as func_150CE660's 4th arg.
- Prototypes: func_150EA560 / func_150EAA80 / func_150F6E10 arg2 `f32` -> `u8` (byte-identical); func_1516DF0C kept at its
  49-arg C prototype (pointer halves in a0 / a1, as on N64); 31 asm callees declared in the NM block from the call sites.
- Harness: stack arguments 16+ were never compared (only sp+0x10..0x3C captured); now up to arg 63,
  `DIFFTEST_STKW_OLD=1` = old window. Selftest 36/36 (new case func_150268BC).
- Default build byte-identical, NM links, protocheck 0, progress_nm 4919/5915 (83.2%), bytes 57.8%, 996 asm-only.
- UNVERIFIED: 0x5F/4; b5 < 0 paths of 0x11 / 0x34 / 0x5F/10 (N64 reads uninitialised / out-of-range stack, C is
  defined); u8 args are narrowed where the asm passes full words; browser runtime of the cutscene effects.

## Next steps (from P90)

1. Browser: run a cutscene with scripted effects (func_1502AB94 -> func_150268BC) and log stub hits of the 31 asm callees
   now reachable from C (list in P90.md) - they become the next blockers.
2. difftest: check why the rec pokes (D_800C3958[1] = 0x80490000 -> 0x80490088) did not reach the 0x33 reference
   (rec->0x18 read 0.0); then re-run the 0x33 mutant (`docs/port/sessions/p90/muts_r.txt`).
3. func_15035AF8, func_15035220 (game_eu_62360.c), remaining game_981E0 asm.

## State (session P89, 2026-10-23). Details: `docs/port/sessions/P89.md`

- The default build is byte-identical (full `verify_all.sh`, `port_work/p89/verify.log`). `NON_MATCHING=1` links.
  protocheck: 0 problems (924 bodies). difftest selftest 33/33.
- progress_nm (P86: 4916, 83.1%, 999 asm-only): **4918/5915 (83.1%)**, bytes **57.2%**, **997 asm-only**.
- **difftest fix**: only addresses in the stack the function used (>= min(lowest sp, SP_ENTRY - 0x1000)) compare as
  'STK'; other 0x806xxxxx values (stub returns, pokes) compare exactly. `DIFFTEST_STK_OLD=1` = old rule. Selftest case
  func_1502AB94 (+0x14 -> +0x10 mutant on a 0x80660000 object now DIFFERs).
- Hand C (NM): **func_15073118** (game_981E0, child object spawn: the browser P88 NULL-stub blocker for func_1507342C),
  func_15036600 (game_eu_63E10, joint look-at); game_eu_61AE0 declares func_15036600 `void`.
- **func_150268BC still asm**: structure map + partial draft in `docs/port/sessions/p89/` (func_150268BC_map.md,
  draft_268bc.c).

## Next steps (from P89)

1. Browser: runtime-check func_15073118 / func_1507342C (spawned child objects) and func_15036600.
2. func_150268BC: resolve the callee prototype conflicts listed in the map (func_150EA560 / func_150EAA80 /
   func_150F6E10 f32 arg2; asm callees without prototypes), then finish the draft's TODO sub-types and test per sub-type.
3. func_15035AF8 / func_15035220 (game_eu_62360), remaining game_981E0 asm.

## State (session P86, 2026-10-23). Details: `docs/port/sessions/P86.md`

- The default build is byte-identical (full `verify_all.sh`, `port_work/p86/verify.log`). `NON_MATCHING=1` links.
  protocheck: 0 problems (922 bodies).
- progress_nm (P85: 4909, 83.0%, 1006 asm-only): **4916/5915 (83.1%)**, bytes **57.1%**, **999 asm-only**.
- Hand C (NM), knob setups EQUIV + mutants (P86.md table): **func_151552F0** (sprite drawer, game_eu_182A10, 318
  calls/run), **func_1502AB94** (dispatcher, 51190, 1590 calls), **func_1509BFB0** (variadic dispatch, C8950, 573),
  **func_150A067C** (slot timers, CDDE0), **func_151143D4** (record / group update, 13DC30), **func_10011624**
  (sound entry update, init_EB00), func_150CE960 (frame-buffer zoom, FBE70).
- Prototype: game_45B80.c NM `void func_150A067C(void)`. No caller drops arguments to the new functions.
- Harness gotcha: stub return pointers in 0x80600000..0x8067FFFF are the harness stack and compare equal as 'STK';
  keep fake objects in 0x804xxxxx / 0x805xxxxx. New helpers `docs/port/sessions/p86/jals.sh` (decoded jal targets) and
  `draft.sh` (extract a function's NM block).

## Next steps (from P86)

1. Browser: runtime-check HUD sprites (func_151552F0), sounds (func_10011624: Doppler, voice end), the P84 frame-path
   functions now in C (func_1502AB94, func_1509BFB0, func_150A067C, func_151143D4).
2. func_150268BC (51190, ~3590 asm lines: split over sessions; pass 0 as func_150CE660's 4th argument).
3. Remaining owned asm: func_15036600 (63E10), func_15035AF8, func_15035220, game_981E0 smalls.

## State (session P85, 2026-10-23). Details: `docs/port/sessions/P85.md`

- The default build is byte-identical (full `verify_all.sh`, `port_work/p85/verify.log`). `NON_MATCHING=1` links.
  protocheck: 0 problems (915 bodies). difftest selftest 30/30.
- progress_nm (P80: 4903, 82.9%, 1012 asm-only): **4909/5915 (83.0%)**, bytes **56.9%**, **1006 asm-only**.
- Hand C (NM), all knob setups EQUIV + mutants (P85.md table): **func_15041A9C** (text drawer, game_eu_6EDC0),
  **func_15180AF0** (sniper scope, game_eu_1ACBC0), **func_151DDF6C** (settings clamp, game_eu_20B730: the browser's
  TEMPORARY PC copy can go), func_1506E2CC / func_1506E0EC (game_981E0 script commands 11 / 8), func_150156F4 (40490).
- Arity / prototypes: func_151DDF6C is `void (void)` (NM callers func_151E2A54, func_15007440 fixed); func_1517FF64
  takes s32 corners; func_1506E0EC / func_1506E2CC `void (void)`.
- Gotcha: some callee names differ from their EU jal address (func_151ACBD4 = 151AD184, func_150A8050 = 150A8530):
  decode the jal word for RET / OUTW / ARGMEM keys.

## Next steps (from P85)

1. Browser: drop the func_151DDF6C TEMPORARY copy; runtime-check text drawing (control codes, icons), the scope.
2. func_151552F0 (318 calls/run, DL path).
3. Remaining asm in owned files (P85.md "Not done").

## State (session P80, 2026-10-23). Details: `docs/port/sessions/P80.md`

- The default build is byte-identical (full `verify_all.sh`, `port_work/p80/verify2.log`). `NON_MATCHING=1` links.
  protocheck: 0 problems (909 bodies).
- progress_nm (P76: 4897, 82.8%, 1018 asm-only): C coverage including NON_MATCHING **4903/5915 (82.9%)**, bytes **56.4%**; **1012 asm-only**. 6 new hand-C functions, 5 arity sites resolved, one difftest harness fix.
- **func_150322B8 is C (NM)** (game_eu_5D910.c, attachment callback 5 on the browser frame path): the seven jump tables
  are generated from the ROM image by `docs/port/sessions/p80/gen_150322B8.py` (static const u8 tables + case lines);
  1246/1246 knob setups EQUIV (every key of every table), mutants 37/39 (2 equivalent).
- Also C (NM): func_15004FE0 (look point loader, game_32490.c: fills D_800C6A70 / D_800C6A74), func_15013778
  (game_40490.c), func_1506C32C / func_1506EF5C / func_1507488C (game_981E0.c script commands). All EQUIV + mutants.
- **Arity**: func_15074C00 -> func_1504715C(&tmp, arg1); func_15084000 is now 1-argument (callee reads only a0);
  func_150CE660 (NM) takes and passes arg3 to func_151604E4 (its asm caller func_150268BC passes 0: keep that when it
  becomes C); func_160012B0 -> func_1600160C(arg0); func_15194858 needs nothing (ignores arg2).
- **difftest fix**: a note line between `#else` and the pragma made build_tu drop the candidate (old NM C tested, all
  mutants LIVE); now accepted, and a dropped candidate raises. Selftest case func_1506EF5C. RET/OUTW addresses are EU
  (func_1000F568 = 1000F858).

## Next steps (from P80)

1. Browser: runtime-check func_150322B8 (callback-5 prop now freed / animated), func_15004FE0 (look points ->
   head turning), the arity fixes.
2. func_15041A9C (1098, game_eu_6EDC0, 915 calls/run), func_15180AF0 (991, game_eu_1ACBC0, 601): display-list path.
3. Remaining asm in owned files (P80.md "Not done").

## State (session P76, 2026-10-22). Details: `docs/port/sessions/P76.md`

- The default build is byte-identical (full `verify_all.sh`). `NON_MATCHING=1` links. protocheck: 0 problems (903 bodies).
- progress_nm: C coverage including NON_MATCHING **4897/5915 (82.8%)**, bytes **56.2%**; init 490/538, game 4368/5334, debugger 39/43; **1018 asm-only** (148 under 60 insns).
- **Look target is C (NM)**: func_15037CCC (target search: fixed targets, objects, look points D_800C6A70, node
  lists) and func_15038910 (joint turn, LookTrack state +0x324), plus func_15037224 (per-kind look config, C switch
  for jtbl_80098714). Also func_1502F780 (carry a point with a carrier triangle) and func_150314B4 (attachment
  draw, browser frame path). Knob setups 64 / 120 / 210 / 60 / 72 all EQUIV, mutants 19/20, 33/34, 19/20, 18/18,
  22/23 (P76.md table; live ones explained there).
- **Arity fixes** (browser P75 / P78 / P79 lists), all byte-identical: func_1503BCAC(arg0) in func_1503482C, 15 more
  call sites and the D_80082ECC / D_80082BFC / D_80082D60 / D_800863B4 handler calls (P76.md table).
- Tools: `docs/port/sessions/p76/` (gen*.py -> s*.txt, knobs.sh / mutfast.sh / mut_*.sh, logs);
  `port_work/p76/jalobj.sh CALLEE TU` = asm before each jal from the built .o.

## Next steps (from P76)

1. func_150322B8 (1148, game_eu_5D910.c, browser frame path): five .late_rodata jump tables (model id -> values),
   callees func_1503F8A8 / func_1505E060 only.
2. Remaining arity sites (need the callee's use): game_981E0 func_1504715C x3 / func_15194858, game_CB1C0
   func_15084000 x2 (a1 == 0 at the jals), game_eu_FBE70 func_151604E4, debugger func_1600160C; game_34F20
   func_15007B3C -> func_1501B640 belongs to port-b's file.
3. Browser: runtime-check the look target (P76.md UNVERIFIED), the attachment draw and the arity fixes.

## State (session P74, 2026-10-22). Details: `docs/port/sessions/P74.md`

- The default build is byte-identical (full `verify_all.sh`). `NON_MATCHING=1` links. protocheck: 0 problems (898 bodies).
- progress_nm: C coverage including NON_MATCHING **4892/5915 (82.7%)**, bytes **55.6%**; init 490/538,
  game 4363/5334, debugger 39/43; **1023 asm-only** (148 under 60 insns).
- **func_15000AD0 is hand C (NM)**, game_2DF70.c: mode 4 / mode 2 / mode 1 fully written (mode 2 = 256-row sky gradient
  texture from 4 colour sets keyed by level, Mtx buffer D_800DC2E0, per-player quads in D_800DC2B8). D_800DC2E0 /
  D_800DC2B8 / D_800DC2B0 are now allocated under NM: **the browser can drop its TEMPORARY func_150D1D20 guard**.
  118/118 knob setups EQUIV, 22/22 mutants killed.
- game_eu_6B970.c has no asm-only function left: func_1503E238, E6B4, E5F8, EB1C, ED44, EF90, F45C (breakable pieces)
  in hand C, knob setups + mutants in `docs/port/sessions/p74/` (P74.md table).
- Tools: `docs/port/sessions/p74/knobs.sh` (= p71), `mutfast.sh` (mutants, stops at the first DIFFER), `nmcheck.sh`.
  **DIFFTEST_POKE does not reach ROM-mapped rodata / odd-trial `.data`** (P74.md gotchas).

## Next steps (from P74)

1. Browser: drop the func_150D1D20 guard, runtime-check func_15000AD0 (sky texture / quads) and the breakables.
2. Remaining asm in the owned files, smallest first: func_1502F780 (302, 595D0), func_15037CCC (441), func_15037224
   (473), func_150314B4 (474), then func_150322B8 / func_15038910.

## State (session P71, 2026-10-22). Details: `docs/port/sessions/P71.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (890 bodies).
- progress_nm: C coverage including NON_MATCHING **4884/5915 (82.6%)**, bytes **55.4%**; init 490/538,
  game 4355/5334, debugger 39/43; **1031 asm-only** (148 under 60 insns).
- **difftest fix:** callee arity now comes from declarations first, argument lists split at top-level commas (a call
  `f((s32 *) M(a, b), 4)` was read as a 3-argument prototype). Selftest case func_15030448: 28 ok.
- Hand C + knobs + mutants (P71.md table): func_15030448, func_15030100, func_150302C8, func_15031F04, func_15033ECC
  (attachments, game_eu_5D910.c), func_15037988, func_15039D68, func_150383B0 (look target, 64770), func_1502C6F8
  (shadow), func_1502D920 (fog alpha), func_1502EF24 (tint) (595D0), func_1503F23C, func_1503DE70 (6B970).
- Tools: `docs/port/sessions/p71/knobs.sh` (p67 8-field format for this worktree), `mut.sh`, `mut_small.sh`, `nmcheck.sh`.
  DIFFTEST_ARG `A|B` choices follow the per-trial rng (same in every setup): fix them per setup in the generator.

## Next steps (from P71)

1. **func_15000AD0** (coordinator / P72 browser, HIGH PRIORITY: D_800DC2E0 / D_800DC2B8 stay NULL while it is asm,
   func_150D1D20 then writes to address 0). Not started beyond reading; structure + buffer sizes in P71.md "Not done".
2. Remaining asm in the model / object files (P71.md list), smallest first: 6B970 func_1503ED44 / F45C / EF90 ...

## State (session P70, 2026-10-22). Details: `docs/port/sessions/P70.md`

- Merged `port-b` (P64, P67; RETF fix) into `port`. The default build is byte-identical (full `verify_all.sh` OK).
  `NON_MATCHING=1` links. protocheck: 0 problems (877 bodies).
- progress_nm: C coverage including NON_MATCHING **4871/5915 (82.3%)**, bytes **55.1%**; init 490/538,
  game 4342/5334, debugger 39/43; **1044 asm-only** (150 under 60 insns).
- **Conker's tail is C:** func_1503BCAC (1143, chain simulation; knobs per branch 138/138, mutants 17/19) and
  func_1503CE88 (joint matrices). Model-path stubs done: func_1503B840, func_15039CC8. Breadth: func_1503A968,
  func_1503216C, func_1502FED8. All hand C, knob setups + mutants in `docs/port/sessions/p70/`.
- **Knob setups need EU data addresses** (`conker/undefined_syms_auto.txt`; D_800CC2D0 = 0x800CC6F0 etc., P70.md).
  Callee prototypes must be in the candidate text for difftest to ignore stray arg registers.

## Next steps (from P70)

1. func_15030448 (written, `docs/port/sessions/p70/draft_0448.c`, difftest a2 issue on func_100043B4), func_150302C8,
   func_15030100, then the other small asm-only functions of 5D910 / 595D0 / 64770 (P70.md list).
2. Browser: tail runtime check (P70.md UNVERIFIED); P65 items (PC overrides, D_80084550 callbacks).

## State (session P65, 2026-10-22). Details: `docs/port/sessions/P65.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (858 bodies).
- progress_nm: C coverage including NON_MATCHING **4852/5915 (82.0%)**, bytes **53.9%**; init 490/538,
  game 4323/5334, debugger 39/43; **1063 asm-only** (151 under 60 insns).
- Coordinator items first (browser P63 TEMPORARY PC versions can go): **func_1502AF04** (animation header lookup),
  **func_1510E908** (slope solver), **func_150A69E0** (func_150A6A48 wrapper; plain C in game_eu_D3880.c).
- Model path: **func_15036FD8**, **func_15030758** (attachments; D_80084550 = .data table of code pointers),
  **func_150028BC** (model vertex ranges / triangles from the DL), **func_1503AB20** (head / eye aim). All hand C,
  knob setups + mutants (P65.md table; setups in `docs/port/sessions/p65/`).
- difftest: known prototypes now fix the compared stack / register argument slots; `DIFFTEST_RET` / `ARGMEM` keys
  must be **EU** callee addresses (from the jal word), not the US-style names.

## Next steps (from P65)

1. **func_1503BCAC** (1143, game_eu_692C0.c): split by branch, knobs + mutants per branch (as func_1503AB20).
2. Browser: drop the PC overrides of func_1502AF04, func_1510E908, func_150A69E0; map D_80084550's callback
   addresses (func_15030758). Runtime checks: P65.md UNVERIFIED.

## State (session P62, 2026-10-22). Details: `docs/port/sessions/P62.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (851 bodies).
- progress_nm: C coverage including NON_MATCHING **4845/5915 (81.9%)**, bytes **53.6%**; init 490/538,
  game 4316/5334, debugger 39/43; **1070 asm-only** (152 under 60 insns); plus the nm_asm func_150A86B0,
  func_150A9B0C, func_150A9E64.
- New hand-written C (no asm2c): **func_150A9B0C** (root rotation x scale) and **func_150A9E64** (f32 -> Mtx) in the new
  `src_eu/nm_asm/D5E90_mtx.c` (harness `tools/port/difftest/nmasm_mtx.py`); **func_1000480C** (blocking cartridge
  read; new Unicorn harness with PI / ROM emulation `tools/port/difftest/pi480C.py`); **func_1502C9D8** (model LOD),
  **func_150F20C8** (type 0x7B adjustments), **func_150844AC** (vertex-block words +0x28C / +0x290). All EQUIV,
  mutants killed (P62.md table; knob setups in `docs/port/sessions/p62/`).
- **Walls literal-address bug fixed** in the generator: `asm2c_hand.py` relocates raw-word `lui 0x80xx` + offset pairs
  to `(u32) &D_X` (`D5E90_walls.inc` now reads `&D_8009FAB0`); regenerated, walls harness 0 diffs.
- The browser can drop its PC overrides of func_150A9B0C, func_150A9E64 and func_150844AC.

## Next steps (from P62)

1. Still asm on the model / draw path: **func_15036FD8** (147, twice per frame, callback-table entry; convert CERR),
   func_15030758 (464), func_150028BC (453; obj[0xAC] & 1 or rec +0x18 & 0x4000), func_1503AB20 (950),
   func_1503BCAC (1143). All need hand C (user policy). Drafts in `port_work/p62*/gen/`, `port_work/p57/gen/`.
2. func_1000480C in the browser: map `CART_WORD` (KSEG1 0xB0000000 | addr) to the ROM image and PI_STATUS to idle.
3. After changing `NM_ASM_C_FUNCS_D5E90`, delete `build_nm/asm/D5E90.s.o` before the NM build.
Code-segment tables: none in P62's C. Runtime checks: P62.md UNVERIFIED.
## P92 (port-b) (session P92, 2026-10-23). Details: `docs/port/sessions/P92.md`

Branch `port-b` (from P87 431730a); the orchestrator merges it into `port`.

- Default build byte-identical (full `verify_all.sh`, `port_work/p92/verify.log`). `NON_MATCHING=1` links. protocheck: 0 problems (912 bodies).
- **progress_nm (NM figure)**: total **4906/5915 (82.9%)**, game 4378/5334 (82.1%), C bytes 56.4%, 1009 asm-only.
- New hand-written NM C (no asm2c), setups EQUIV + mutants: the scene-path producers in game_eu_4A070.c,
  func_1501FD34 (20/20), func_1501FF10 (18/18), their producer func_1501F7D4 (26/26), func_1502330C (17/17),
  func_1501EA84 (29/29), func_1501E5AC (12/12), func_15023684 (23/23); game_14FF90.c func_15124C38 (31/39: 5 open
  survivors, 3 unrun, P92.md section 2).
- No arity fixes needed (callers / callees checked, P92.md section 3).

## Next steps (from P92)

1. Browser: cutscene paths / camera pick / scene end / camera height (P92.md UNVERIFIED).
2. func_15124C38 open mutants (`p92/4c38c_mut.txt` ready); func_15020920 (segment cubic, producer of func_1501F7D4).
3. func_15126378 (game_14FF90.c, 1130 lines) not started.

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
  (P66: it is the C body in the wasm build too; P61's note came from an old log. Jump / idle checked at runtime, P66.md.)
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
## State (session P65, 2026-10-22). Details: `docs/port/sessions/P65.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (858 bodies).
- progress_nm: C coverage including NON_MATCHING **4852/5915 (82.0%)**, bytes **53.9%**; init 490/538,
  game 4323/5334, debugger 39/43; **1063 asm-only** (151 under 60 insns).
- Coordinator items first (browser P63 TEMPORARY PC versions can go): **func_1502AF04** (animation header lookup),
  **func_1510E908** (slope solver), **func_150A69E0** (func_150A6A48 wrapper; plain C in game_eu_D3880.c).
- Model path: **func_15036FD8**, **func_15030758** (attachments; D_80084550 = .data table of code pointers),
  **func_150028BC** (model vertex ranges / triangles from the DL), **func_1503AB20** (head / eye aim). All hand C,
  knob setups + mutants (P65.md table; setups in `docs/port/sessions/p65/`).
- difftest: known prototypes now fix the compared stack / register argument slots; `DIFFTEST_RET` / `ARGMEM` keys
  must be **EU** callee addresses (from the jal word), not the US-style names.

## Next steps (from P65)

1. **func_1503BCAC** (1143, game_eu_692C0.c): split by branch, knobs + mutants per branch (as func_1503AB20).
2. Browser: drop the PC overrides of func_1502AF04, func_1510E908, func_150A69E0; map D_80084550's callback
   addresses (func_15030758). Runtime checks: P65.md UNVERIFIED.

## State (session P62, 2026-10-22). Details: `docs/port/sessions/P62.md`

- The default build is byte-identical (full `verify_all.sh` OK). `NON_MATCHING=1` links. protocheck: 0 problems (851 bodies).
- progress_nm: C coverage including NON_MATCHING **4845/5915 (81.9%)**, bytes **53.6%**; init 490/538,
  game 4316/5334, debugger 39/43; **1070 asm-only** (152 under 60 insns); plus the nm_asm func_150A86B0,
  func_150A9B0C, func_150A9E64.
- New hand-written C (no asm2c): **func_150A9B0C** (root rotation x scale) and **func_150A9E64** (f32 -> Mtx) in the new
  `src_eu/nm_asm/D5E90_mtx.c` (harness `tools/port/difftest/nmasm_mtx.py`); **func_1000480C** (blocking cartridge
  read; new Unicorn harness with PI / ROM emulation `tools/port/difftest/pi480C.py`); **func_1502C9D8** (model LOD),
  **func_150F20C8** (type 0x7B adjustments), **func_150844AC** (vertex-block words +0x28C / +0x290). All EQUIV,
  mutants killed (P62.md table; knob setups in `docs/port/sessions/p62/`).
- **Walls literal-address bug fixed** in the generator: `asm2c_hand.py` relocates raw-word `lui 0x80xx` + offset pairs
  to `(u32) &D_X` (`D5E90_walls.inc` now reads `&D_8009FAB0`); regenerated, walls harness 0 diffs.
- The browser can drop its PC overrides of func_150A9B0C, func_150A9E64 and func_150844AC.

## Next steps (from P62)

1. Still asm on the model / draw path: **func_15036FD8** (147, twice per frame, callback-table entry; convert CERR),
   func_15030758 (464), func_150028BC (453; obj[0xAC] & 1 or rec +0x18 & 0x4000), func_1503AB20 (950),
   func_1503BCAC (1143). All need hand C (user policy). Drafts in `port_work/p62*/gen/`, `port_work/p57/gen/`.
2. func_1000480C in the browser: map `CART_WORD` (KSEG1 0xB0000000 | addr) to the ROM image and PI_STATUS to idle.
3. After changing `NM_ASM_C_FUNCS_D5E90`, delete `build_nm/asm/D5E90.s.o` before the NM build.
Code-segment tables: none in P62's C. Runtime checks: P62.md UNVERIFIED.

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


## Browser build (sessions P3, P4, P6, P8, P9, P11, P14, P19, P21, P23, P25, P26, P27, P29, P31, P33, P35, P37, P39, P42, P44, P46, P49, P52, P55, P58, P61, P63, P66, P69, P72, P75, P78, P81; branch `port-web`)

Full notes: `docs/port/sessions/P3.md` (platform skeleton), `docs/port/sessions/P4.md` (memory
model, boot, priority list), `docs/port/sessions/P6.md` (indirect calls, renderer, microcode) and
`docs/port/sessions/P8.md` (address space, PC overrides, texture ids, re-rank) and
`docs/port/sessions/P9.md` (ROM-offset symbols, KSEG0 tests, audio HLE) and
`docs/port/sessions/P11.md` (runtime check of the C scheduler/allocator/asset walker, live-frame path, SDL2) and
`docs/port/sessions/P14.md` (MP3 voice audio, Conker lighting, skeleton bind pose, browser audio fix) and
`docs/port/sessions/P19.md` (real game frames, RCP/PIF model, level-loader stubs, real-time freeze guard) and
`docs/port/sessions/P21.md` (browser heap corruption = fiber stack alignment, real-time Chrome, debug flags) and
`docs/port/sessions/P23.md` (merge P20, srcfix, frame DL end to end, DL-path stub list) and
`docs/port/sessions/P25.md` (libultra/libgu/libc PC layer complete, `[gutest]`, licenses) and
`docs/port/sessions/P26.md` (merge port P24, sqrtf hang, runtime checks, **camera path**) and
`docs/port/sessions/P27.md` (input, EEPROM saves in IndexedDB, page UX, audio resume) and
`docs/port/sessions/P29.md` (merge port P28, a2-position DL stubs, camera runtime, camera callback check) and
`docs/port/sessions/P31.md` (merge port P30, valid projection + view, why the frame has no triangles) and
`docs/port/sessions/P33.md` (inflater = the level-load heap break, level geometry on screen, freecam, renderer gap list) and
`docs/port/sessions/P35.md` (F3DEXBG lighting checked in the RSP code, CULLDL/BRANCH_Z, RDP blender, 3-point filter, per-tile wrap, LOD) and
`docs/port/sessions/P37.md` (merge port P36, PC stand-ins removed, inflater / camera-target runtime checks, visibility-walk inputs) and
`docs/port/sessions/P39.md` (merge port P38, camera eye/at writer and its stubbed inputs, runtime checks of the P38 C) and
`docs/port/sessions/P42.md` (merge port P40, KSEG0 pointer tests and computed IO_READ, the real visibility walk on level data) and
`docs/port/sessions/P44.md` (runtime check of P41's camera chain, the game's own view, what blocks player movement) and
`docs/port/sessions/P46.md` (runtime check of P43 / P45, srcfix array initializers, the first lit and framed game-camera frame) and
`docs/port/sessions/P49.md` (merge port-b P47, the player walks and the camera follows, the movement-path stub order) and
`docs/port/sessions/P52.md` (P50 / P48 movement and model C at runtime, P49 overrides removed, why the view goes black) and
`docs/port/sessions/P55.md` (P53 / P54 floor and landing C at runtime: stand, walk off, land; G_DL 0 crash) and
`docs/port/sessions/P58.md` (P51 model load + skeleton evaluator at runtime, four port-side blockers, posed preview) and
`docs/port/sessions/P61.md` (Conker drawn by the game's func_1502CFEC, two TEMPORARY PC functions, walls K0-literal crash, P59 checks) and
`docs/port/sessions/P63.md` (Conker animated by the game: func_1502AF04 / func_1510E908 / func_150A69E0 TEMPORARY PC,
false slide and garbage-count crash, end callback verified, walk GIF) and
`docs/port/sessions/P66.md` (P62 / P64 overrides dropped, osRomBase for the C func_1000480C, func_15085710 is C,
jump / running jump / Z long jump and idle variations at runtime, jump GIF) and
`docs/port/sessions/P69.md` (last PC versions dropped, D_80084550 mapped, P65 / P67 C at runtime, the walk-after-respawn
hang) and `docs/port/sessions/P72.md` (the hang bisected to P64's func_150D1D20 writing through NULL buffers of the
stubbed func_15000AD0; TEMPORARY guard; 0x2C warp reached again) and `docs/port/sessions/P75.md` (merge P70 / P71 / P74,
guard dropped, sky / tail / breakable runtime checks, missing-argument call sites, blocker list)) and `docs/port/sessions/P78.md` (per-material DL dump,
LOD fixes in the renderer, the null-zone writer = func_1501396C's argument-less icall, the func_150D1D20 gate) and `docs/port/sessions/P81.md` (merge P76, arity rescan, look target / attachment / null-zone / tail runtime checks,
blocker list). The memory-model design is in **`docs/port/MEMORY.md`**. Everything is
under `port/`; nothing shared was changed, so the matching build is unaffected.

```sh
port/web/run.sh image     # once: conker-emsdk image (emscripten/emsdk:4.0.15-arm64, pinned)
port/web/run.sh build     # census + vbe IR build of the game TUs + memory tables + link + page (~2-3 min clean)
port/web/run.sh serve     # http://localhost:8064/?app=demo   (stop: port/web/run.sh stop)
port/web/boot.sh 10       # node boot, read-only mounts, compact summary; log in port/build/boot.log (GFXDEMO=1 for the viewer)
port/web/rebuild.sh 10 [clean]   # P11: build + boot in one step (clean = after a merge / C change)
python3 port/tools/priority.py port/build/boot.log 50   # conversion priority list (measured stubs + next wave)
AUDTEST=26390 port/web/boot.sh 8   # P9: C n_audio synth + audio HLE on a ROM sound -> port/build/audio/audtest.wav (page: &audtest=26390, click)
VOICETEST=3 port/web/boot.sh 8      # P14: voice clip via func_151F2E88 + MP3 decoder + MP3 ABI -> port/build/audio/voice.wav
port/web/audprobe.sh "app=game&audonly=1&audtest=26390" 10   # P14: real headless-Chrome Web Audio consumption check
port/web/shot.sh OUT.png 'app=game&gfxdemo=1' 2500           # viewer screenshot (P14: keep the budget short)
PADTEST=1 EEPTEST=77 port/web/boot.sh 10   # P27: scripted pad input -> [pad] lines; EEPROM write/read [eeptest] PASS
PROBE_NOAUDIO=1 PROBE_STEPS="6000:keydown:Space; 7500:keyup:Space" port/web/audprobe.sh "app=game" 10   # P27: real key events
PROBE_NOAUTOPLAY=1 PROBE_STEPS="6000:click" port/web/audprobe.sh "app=game&audonly=1&audtest=26390" 12  # P27: audio starts on the gesture
PORT_P49WALK=3 PORT_P49EVERY=16 PADSCRIPT="15000:0:0:80; 22000:0:0:0" port/web/boot.sh 30   # P49: scripted stick (ms:buttons:x:y) + walk-handler log
# P49: PROBE_STEPS also takes MS:shot:/abs/path.png (real-time screenshots during a run; frame sequences)
# P52: ?p49walk also logs [p52] gravity (dt D_800D1550[0]) and func_1502C1D4 (record 0 +0x1D4 / model) lines;
#      ?p52void=1 makes the floor query answer "no floor" (diagnostic); audprobe needs PROBE_LOG=/abs/file for the console
# P55: ?p49walk also logs [p55] floor (record 0's floor query + float reference) and [p55] landing lines;
#      ?p55synth=1 sloped synthetic floor check (PASS/FAIL); ?p55drop=Y drops the player from height Y; ?gdlzero=N
#      finds a "G_DL 0" writer; ?p52void is now an opt-in diagnostic only
# P58: ?p58model=N (model load + evaluator checks), ?p58dump=K, ?p58noterm=1, ?p58anim=K (+ p58speed: drive a ROM
#      animation, the driver func_1505E0C4 is asm), ?p58pose=1 (+ p58ang: posed ROM Conker drawn after each frame)
# P61: ?p61model=N (the game's model DL: commands / vertices / triangles / bone G_MTX per frame; first frame dumped),
#      ?p61check=N (P59 C: func_1507D4F8 + func_1501C710, func_1505D6F0, the sound calls of func_1508000C, func_1507C170)
# P63: ?p63anim=N (record 0's animation per func_1507C170 call + every func_1505E650 start + floor / slide state),
#      ?p63stack=1 (JS stack per new id), ?p63cb=N (end-callback probe, diagnostic); port/web/p63shots.sh (Chrome
#      stand / walk / idle frame sequence); python3 port/tools/png2gif.py (stdlib GIF / crop zoom from screenshots)
# P66: ?p66jump=N (record 0 per func_1505F298 call: buttons, anim id, y / vy / +0x28, water, + idle-chooser state),
#      ?p66lowg=1 (DIAGNOSTIC: D_800CC69C = 1 on A presses), ?p66hud=N (func_15085710 calls); port/web/p66shots.sh
#      (Chrome jump frame sequence, Space held 400 ms)
# P69: ?p69attach=N (D_80084550 check + attachment list), ?p69look=N (func_1503AB20), ?p69tri=N, ?p69att=N (attack /
#      debris / object anim start), ?p69floor=N, ?p69free=1|2|FRAME (double free + object-list scan), ?p69watch=N,
#      ?p69stub=MASK / ?p69pc=MASK (DIAGNOSTIC bisect wraps); port/web/p69shots.sh (Chrome stand / B / walk / jump / idle)
# P72: port/web/p72shots.sh [OUTDIR] [WALK_MS] [HOLD_MS] [EXTRA_QUERY] (Chrome walk
#      through the respawn to the 0x2C warp; DENSE="FROM TO" adds 200 ms shots)
#      (P75: ?p72quad / ?p72skip are gone with the TEMPORARY func_150D1D20 guard)
# P75: ?p75sky=1 (func_15000AD0 buffers / gradient / quads, null-zone first dirty frame), ?p75tail=N (func_1503BCAC),
#      ?p75brk=N (func_1503E238), ?p75break=FRAME&p75bslot=S&p75bkind=K (DIAGNOSTIC break request); one node boot at a time
# P78: ?p78tex=TASK (per-material dump: othermode / combiner / tiles / decoded texels / raw Vtx / texel density;
#      python3 port/tools/p78tex.py LOG OUTDIR -> PNGs), ?p78null=1 (first null-zone write: last stubs + JS stack),
#      ?p78sky=N (func_15110420 backdrop gate inputs), DIAGNOSTIC ?p78split=1 (left half old LOD, right half new),
#      ?p78lodviz=1 (tint by LOD tile), ?p78oldlod=1 (old LOD scale)
# P81: ?p81look=N (look slot / target / aim / LookTrack / joint 7, 12, 0 matrices after func_15036FD8), ?p81att=N (attachment
#      passes func_150310F8 / func_15031284: commands, part DLs, seg 3 Mtx, list on change), DIAGNOSTIC ?p81noatt=1
# after merging port: rm port/build/census/files.tsv port/build/vbe.stamp, then build (make doesn't track src_eu)
```

- **Memory model (P4):** N64 data stays at its N64 offsets in two mirror arrays (`n64_rdram`
  8 MB, `n64_seg16`). Data symbols are labels there (`port/stubs/n64mem_labels.s`).
  `port_mem_load()` copies `init_data`, `game_data` (rzip, inflated) and `debugger_data` from the
  user's ROM and relocates 5354 pointer words: 3244 become wasm function-table entries, 2110 data
  pointers. The pointer list comes from a scan of the blobs with range and function-start rules
  (`port/tools/n64mem.py`). Only 14 zero-filled data stubs remain (ROM offsets used as `&sym`).
- **Endianness (P4): game memory is virtual big-endian.**
  - Storage is word-swapped; byte accesses use `A^3`, halfword accesses `A^2`, 64-bit accesses swap
    halves.
  - `port/tools/vbe.py` applies this to every game TU at the LLVM IR level before optimization.
  - Game C code needs **no** swaps, and mixed-width access works.
  - ROM data and assets need no per-format swappers: DMA is a bswap32 copy.
  - Bitfields and the PC layer's sub-word accesses (`vbe_*` in `port/ultra/pc_mem.h`) are the
    exceptions. See MEMORY.md, "What this implies for the C code".
- **Signatures (P4):** `port/tools/sigs.py` gives every function one wasm signature (definition, or
  majority call site for stubs) and rewrites 791 mismatching call sites. Link signature warnings
  went from 288 to 1. Indirect calls: see P6 below.
- **Endianness test:** `port_memtest` checks real converted functions (`func_1509CE20/40/60/88`,
  `func_15041770`) against BE values decoded from the ROM in Python. 45/45 pass in node and in
  headless Chrome.
- **Boot:**
  - PC `func_15007830` (`port/boot/game_entry.c`) → full init sequence → main loop. The state
    machine is read from the ROM's jump table; one pass per frame.
  - P4: 23 distinct asm stubs were hit (P8: 15, see the priority list below). The top ones per frame were: `func_100061F8`, `func_10001420`,
    `func_10005BE0`, `func_1501878C`, `func_1501BBB8`; during init: `func_1502AC88` (×201) and the
    allocator `func_10003C6C`.
  - Next wave: `func_10004074`, `func_1515DC40`, `func_151674F8`, and the `func_1501878C` callees.
    The full 50-entry list is in P4.md.
- **Scheduler (P3):** libultra threads as emscripten fibers (ASYNCIFY). Priority scheduling, one VI
  retrace per frame, priority-0 idle threads park. `port_wait_frame()` paces PC-written loops.
- **Census (P3):** 7 of 719 TUs fail under clang and are left out (`port/build/census/summary.txt`).
- **Indirect calls (P6):** every indirect call in game code goes through a site-typed
  trampoline (`port/tools/icall.py`). Matching signatures take a plain `call_indirect`. Mismatches
  are converted with o32-like rules through `__port_icall_slow`, so they no longer trap.
  - 5270 functions are registered, with 218 target signatures.
  - The registry check over 5 ROM function tables passes, 654/654.
  - `[icalltest] PASS` in node and in headless Chrome.
  - Design: MEMORY.md, "Indirect calls (session P6)".
- **Renderer (P6):** `port/gfx/` is an F3DEX2 interpreter on WebGL2, written fresh.
  - It covers TMEM, all common texture formats, the two-cycle combiner, and Conker's Rare `TRI4`
    opcodes 0x10–0x1F.
  - `osSpTaskStartGo(M_GFXTASK)` → `gfx_run_task`. This path is ready, but **no task arrives
    yet**: the scheduler `func_100049E0` and the frame builders are asm stubs.
  - Proof: `?app=game&gfxdemo=1` draws six real model display lists inflated from ROM assets.
    Screenshot: `docs/port/sessions/P6_screenshot.png`. Tool: `port/web/shot.sh OUT.png 'app=game&gfxdemo=1'`.
  - The ROM has 8 microcodes: F3DEX / BS / BG / BGBS, each also as .NoN, all "fifo 2.08". The
    data block is 0x6C0 per ucode, and `G_LOAD_UCODE` switches between them per frame. Details in
    P6.md §2.
- **Address space (P8):** the game is linked with `-sGLOBAL_BASE=256MB`, so every wasm data address
  is `>= 0x10000000`. Display-list values `0x01000000..0x0FFFFFFF` are always RSP segment addresses,
  and the renderer needs no heuristic. The cost is virtual only (node maxRSS +8 MB, noise). The
  risk is 32-bit browser processes and an untested iOS device. MEMORY.md, "Address space and RSP
  segments".
- **PC overrides (P8):** `port/boot/pc_overrides.c` defines:
  - `func_100061F8`: a TLB-invalidate loop, a no-op on the PC;
  - `func_150ADA20`: `u64` guRandom (`[overrides] guRandom PASS`).

  Game `.c` files are untouched.
- **Texture ids (P8):** the engine resolves G_SETTIMG ids in place at model load:
  - `func_1510D3E0` (asm) walks the DL;
  - `func_1510D66C` (asm) is the cache;
  - the bank is ROM `0x1A3B40 + sum D_800920D0[0..id)`, rzip files;
  - `0x0040xxxx` / `0x0080xxxx` = the 256- / 16-colour TLUT at the end of the texture.

  The viewer has a PC copy (`tex_patch_dl`) and draws real textures (`P8_screenshot.png`).
- **ROM-offset symbols (P9):** `vbe.py` turns `&D_1A3B40`, `&D_AB2240`, `&D_2D810`, `&D_11AF` into
  constants and declares the four `extern s32 func_X` callbacks as functions (data stubs 14 → 6).
  `[romsym] PASS`: the C `func_1510D8F4(0xED0)` = 0x6F1618, and a DMA from there gives the ROM bytes.
  The boot's C `func_15003570` now builds the right texture size table.
- **KSEG0 tests (P9):** `vbe.py` `k0_checks` rewrites `(p & 0xFF000003) == 0x80000000` and
  `K0_TO_PHYS(p) > 0x800000` (4 sites, all audio) for wasm pointers.
- **Audio (P9):** `port/audio/` holds:
  - an n_audio ABI interpreter (Conker/MP3 table, all commands but MP3);
  - SDL output (Emscripten's built-in SDL audio; SDL2 needs an image change);
  - M_AUDTASK / `osAiSetNextBuffer` hooks.

  Test path `aud_test.c`: the game's C `n_alInit`/`n_alSynNew`/`n_alAudioFrame` with a sound from
  the ROM bank. The WAV is exactly the independently decoded sample (correlation 1.0000). The sound
  bank layout (asset table walk, ctl, on-demand records, sample table) is in P9.md. No game audio
  task yet: audio init `func_10008180`/`func_10008F90` and the scheduler are asm.
- **Priority list (P8, after merging port fa5daf8, 10 s boot; full 50 in P8.md):**
  15 distinct stubs are hit.
  - Measured: func_1501878C (540), func_1501BBB8 (540), func_1502AC88 (201), func_150159E8 (95),
    func_10003C6C (13), func_15085710 (3). Once each: func_100052A0, func_1000709C (missing),
    func_10005B04, func_100049E0 (scheduler), func_10008180, func_15043384, func_1509BA04,
    func_150A00F0, func_15007B3C.
  - Next wave: func_1515DC40, func_151674F8, func_151412BC, func_151E5928, func_1510BA9C,
    func_15019130, func_15019464, func_1501A490, func_150195A0, func_15019CC8, func_15084E80,
    func_1510D984 (texture cache), func_15114F9C, func_eu_1501C860, func_1501C55C.
  - Texture path, for a later session: func_1510D66C, func_1510D3E0, func_10004514, func_10006530.
- **Runtime check of converted C (P11, after merging port 17aafdb):**
  - **No bug found** in `func_100049E0` (scheduler), `func_10003C6C` (allocator) or
    `func_1502AC88` (asset walker).
  - Boot self-tests: `[schedtest] PASS` (retrace client, gfx and audio tasks reach `gfx_run_task`
    and `aud_run_alist`, done messages are right), `[heap]` walk with 0 errors, `[assettest] PASS`
    (8 keys, the game's walk equals a direct DMA walk).
  - Fixed on the PC side:
    - the PC `func_10001194` lacked the scheduler queue and VI event;
    - the heap bounds were K0 constants (`port_fix_heap_bounds`);
    - the mirrors are now 4 KB aligned.
  - Rule: gfx tasks go to `D_8003B1E8`, audio tasks to `D_8003B200`.
  - Symbol trap: asm names listed in `undefined_syms.eu.txt` are US names. `D_800BE9C0` in asm
    is address 0x800BEDE0, so PC code must use the mapped address.
- **Live frames (P11):** the game steps every frame (70 stubs). Still missing, so no game DL renders:
  - A game gfx task is never submitted, because the DL buffers `D_800BEDE8` are NULL. Only the
    asm level loader **`func_15007B3C`** calls `func_15015E30`, which allocates them. It also
    starts the first pad read; the PC `osContInit` posts one SI message as a shim until then.
  - The TEMPORARY PC overrides `func_15019130` (world update) and `func_eu_1501C860` (frame
    submit) are in `pc_overrides.c`. Remove them when the port branch converts these functions.
  - DL stubs called as `x = f(x, …)` return `a0` (23 pass-through stubs).
  - The first DL (written at NULL) is G_DL 0x8002CC90, G_SETZIMG z-buffer, G_MOVEMEM viewport;
    see P11.md §2.
- **Audio (P11):** the output is SDL2 (`-sUSE_SDL=2`; the image runs `embuilder build sdl2`).
  `[audtest]` passes unchanged. **P14: that SDL2 output never played anything** (see below).
- **MP3 voice audio (P14):** commands 7 (MP3) and 8 (MP3ADDY) are implemented in `aud_abi.c`.
  - Command 7 is the polyphase synthesis filterbank. The window is read from the ROM at 0x2CFD0.
    The FIFO is per state address and resets when the game zeroes the state.
  - The MP3 decoder's hand-written asm (bits, Huffman, IMDCT) has **TEMPORARY** PC versions in
    `port/audio/mp3_pc.c`. Remove them when the port branch converts `game_eu_226870.c` /
    `game_eu_227BF0.c`.
  - `VOICETEST=3` drives the real `func_151F2960`/`func_151F2E88` and gives speech: a syllabic
    envelope, energy below 4 kHz, diff/energy 0.24.
  - Voice clips are asset (0x16, id), MPEG-2 L3 at 22050 Hz mono. The handler's state word
    `D_800E1224` = `&D_800E0D80 + 0x74`; `D_800E0D80` is 0x800E11B0 in the EU ROM.
- **Browser audio (P14):**
  - `port/web/audprobe.sh` (CDP + `&audprobe=1` probe) showed that the SDL2 build never created an
    AudioContext: no Emscripten audio driver is linked, so SDL used a dummy device.
  - `aud_out.c` now has a direct Web Audio ScriptProcessor sink. It reads the ring from the heap,
    with no wasm call in the callback.
  - Measured: audtest 203864 non-zero samples pulled and voicetest 69618. Both PASS.
  - Rule: EM_JS functions must be named `__port_*`. `gen_stubs.py` stubs any other undefined name
    as "missing", silently.
  - `&audonly=1` loads the game data without starting the game threads.
  - **Open (P19: cause found, fix not yet confirmed):** the game page blocked its main thread in
    real-time headless Chrome. Timers fire only at retrace, so a NOBLOCK-polling or clock-spinning thread
    never yielded. `port_spin_check` (`pc_sched.c`) now yields after 4096 empty polls.
- **Renderer (P14):**
  - Conker lighting: normals are s8 x,y at `G_MOVEMEM 0x0E base + 2 * slot`, and z is the Vtx flag
    low byte. The vertex colour is multiplied by ambient plus directional lights (48-byte Light
    records). The ucode's exact formula is not checked against the RSP code.
  - Viewer skeleton: bone table at header +0x10/+0x14, entries `{parent, idx, idx, 0, f32 xyz}`.
    The bind pose is the joint offsets x the model matrix. Conker now stands assembled:
    `docs/port/sessions/P14_viewer.png`.
- **Merge of `port` P13 (b0fa85d): NOT done in P14** (the permission system denied `git merge`).
  The steps are in P14.md "Next": merge, drop the `func_15019130` / `func_eu_1501C860` overrides and
  the `osContInit` shim (P13: the override's ucode choice was reversed), `rebuild.sh 10 clean`, look
  for real gfx tasks, and runtime-check `func_15007B3C` / `func_15043384`.
- **P19 (after merging port P17, 506 NM): real game gfx tasks reach `gfx_run_task`.**
  - The P11 overrides `func_15019130` / `func_eu_1501C860` and the `osContInit` SI shim are gone.
  - Node 10 s: 143 gfx frames plus 286 audio tasks (the C audio thread runs). Each frame is 12 commands,
    0 triangles, 0 unknown: segment, init DL, z-image, viewport, fullsync. The scene, colour image and
    clear are still asm stubs.
  - New PC pieces:
    - `vbe.py rcp_io` turns constant `IO_READ`/`IO_WRITE` into `__port_io_read/write` (`pc_os.c`);
    - a PIF model (pad 0, 16K EEPROM, SI event);
    - `osPiRawReadIo`;
    - `port_spin_check` (§ freeze below).
  - TEMPORARY overrides in `pc_overrides.c`: `func_1502B350` (asset load), `func_1502B4A8` (sub-file
    relocation), `func_15002248` (quadtree helper; its garbage `*out` made free() spin).
  - **For the port branch:**
    - `func_15049260` is declared `void`, but `func_15002248` uses its v0 (from `func_150AB278`);
    - `struct_eu_bytes24` is 36 bytes;
    - no bug found in `func_15007B3C`, `func_10004074`, `func_15019130` or `func_eu_1501C860`;
    - `func_15043384`, `func_1510BC10`, `func_1501E46C`, `func_15084E80` and `func_150802A8` were not
      checked (none traps in 10 s).
  - Top stubs: func_1000CEAC, func_1000D2F8, func_150A7A48, func_150A4ED4, func_1501B22C,
    func_15113B44, func_1502BDC0, func_1517D7B0, func_1000A03C, func_15173954. Top 30 in P19.md §9.
  - Open items: both were closed in P21 (see below).
  - Screenshot (real-time CDP, `PROBE_SHOT=` in `audprobe.sh`): `docs/port/sessions/P19_screenshot.png`
    shows a black canvas plus the crash that P21 fixed.
- **P21: the game runs in real-time Chrome as far as in node.**
  - **Heap corruption fixed.** The fiber C stacks came from `malloc`, which is only 8-byte aligned.
    - wasm assumes a 16-aligned stack pointer, so clang folded the game's own
      `((u32)buf + 15) & ~15` to `buf`.
    - In the browser, WebGL's mallocs left the stacks at 8 mod 16, and `func_1502AC88` read its ROM
      record 8 bytes off. Wrong assets were loaded and the heap broke.
    - Now `aligned_alloc(16, …)`.
    - **Rule: every C stack must be 16-byte aligned.**
    - `mallocpad=8/16` in node, which reproduced the crash, now runs clean.
  - **Real time:**
    - Chrome stays responsive: evaluate answers throughout; slowest about 4 s at startup with
      SwiftShader, where `getContext` alone takes 1.7 s.
    - Metal: more than 480 gfx frames in 35 s.
    - A spinning thread is now parked until the next frame.
    - `port_sched_run` has a 40 ms wall-time budget, and frames slower than 250 ms are logged.
  - **Tools:**
    - `shot.sh OUT.png 'app=game' MS` uses the real-time CDP path. Screenshot:
      `docs/port/sessions/P21_screenshot.png`.
    - `[schedtest] PASS` again: it counts runs of its own task by `data_ptr`.
  - **Debug flags:** set them as `?flag=N` on the page or `PORT_FLAG=N` for `boot.sh`.
    - `det`: deterministic clock;
    - `nogl`, `noselftest`;
    - `heapwatch`: heap walk after every switch and `osSetIntMask`;
    - `stubstack`;
    - `dmalog` and `dmamin`;
    - `mallocpad`.

    `audprobe.js` adds `PROBE_LOG` (streamed console), `PROBE_EVAL_TIMEOUT`, `PROBE_PROFILE`,
    `PROBE_ANGLE=metal` and `PROBE_SAMPLES`. Details: P21.md §5.
  - **For the port branch:** `func_151E8620` calls the asm stub `func_151EC11C` (`v:` called as
    `Gfx*(Gfx*)`) through `D_80090370`. It returns NULL, so every frame DL ends after the viewport.
    Convert that table's functions next. `__osRunningThread` is never set (0).
  - Rule: after changing `port_prefix.h`, the `.ll` cache now rebuilds by itself.
- **P23 (after merging port P20, 366af85): the frame DL runs end to end.**
  - **Merge:**
    - The P19 overrides `func_1502B350` / `func_1502B4A8` / `func_15002248` were removed.
    - `func_150ADC50` was added to `vbe.py FUNC_AS_DATA`: `debugger.c` declares it as data.
    - **`port/tools/srcfix.py`** builds patched copies of TUs that clang rejects (lvalue casts, K&R arity).
      Five P20 TUs had dropped out of the build.
  - **Checks:**
    - Node: all self-tests PASS and the heap has 0 errors, also with `heapwatch`.
    - Real-time Chrome, Metal, 45 s: past gfx frame 600 with 0 heap breaks.
  - **Why the frames were empty:** `func_eu_1501C860` throws away any frame whose DL pointer is outside
    the buffer, and asm DL builders returned 0.
  - **Fixed in three ways:**
    - `x = fp(x)` indirect sites return `a0` when the target is a stub (`__port_is_stub`);
    - stubs declared `Gfx *f(Gfx *, ...)` return `a0`;
    - every int stub returns `a0` when `a0` points into the frame DL buffers (`port_stub_dlret`).
  - **Result:** each frame is about 120 commands, 0 triangles and 0 unknown opcodes. The screenshot
    `P23_screenshot.png` shows only the clear colour.
  - **For the port branch:**
    - **Frame-DL-path stubs, which block the scene:** func_15113B44, func_1502BDC0, func_15110420,
      func_1510BF50, func_15186D04, func_150362D8, func_1517E7FC, func_15182450, func_1517FAD4,
      func_1508FD38, func_151EC300 (`D_80090370[11]`; not func_151EC11C), func_1517F910, func_15180AF0.
    - **Top measured stubs:** func_1000CEAC, func_1000D2F8, func_150A4ED4, func_1517D7B0, func_1000A03C,
      func_15173954, func_1509BE40, func_1501B300, then about 26 at one call per frame.
      `guMtxF2L` is an asm stub (P25: now PC). Full list in P23.md §3.
    - **clang errors in converted C (fix when convenient):**
      - `game_eu_113D60.c:131`, `game_eu_1C3530.c:1069`, `game_eu_1F4F60.c:93`: lvalue casts;
      - `game_eu_1D1150.c:435`: `func_151A3AB4` called with 3 arguments, defined with 2;
      - `game_eu_B37F0.c:282`: `func_150889D8()` called with 0 arguments, defined with 1;
      - `debugger.c`: `extern s32 func_150ADC50`.
    - **`func_15002248` (P20)** was not reached in 10 s, so it is not checked at runtime. No bug found.
  - **Flags:** `dltrace=N`, `dlstat=N` (opcode histogram, segments, `[probe]`) and `gdltrack=N`.
- **P25: the libultra/libgu/libc PC layer is complete.** `asm_stubs.c` has no libultra, libgu or libc
  name left (stubs 1168 → 1160; the only non-`func_` stub is the PC tool `port_icall_check`).
  - **New `port/ultra/pc_gu.c`:**
    - `guMtxF2L` (Rare's asm: `cvt.w.s`, round to nearest even; written as whole Mtx words);
    - `func_150A7B80` (guMtxIdent);
    - `vbe.cosf` (the libultra polynomial);
    - Rare's fast sin/cos `func_150AD78C` / `func_150AD780` (D5E90.s; constants from .rodata).
  - **New `port/ultra/pc_libc.c`:** `vbe.bcopy` / `vbe.bzero` on the vbe helpers.
  - **Found:** `bcopy`, `bzero` and `cosf` were asm-only and had been bound **silently to musl**. musl's
    bcopy/bzero use host bytes, which is wrong on vbe memory at mismatched alignment.
    `vbe.py LIBC_VBE` renames them like `LIBC_CLASH`, with sigdb aliases for those names only.
  - **`pc_os.c`:**
    - interrupt state is tracked (`__osDisableInt` / `__osRestoreInt` / `osSetIntMask` return the
      previous state);
    - `__osProbeTLB`, `__osSetCompare`, `__osCleanupThread`;
    - `func_10024190` (osWritebackDCache) is a no-op.
  - **Licenses:** ultralib has **no license**, and its C keeps SGI's proprietary header. Nothing was
    copied from it; everything was written from the game's asm and the decomp. See
    `port/ultra/LICENSES.md`.
  - **`[gutest] PASS`:** F2L edge values, L2F→F2L round trip, guPerspective (game C) and a guLookAtF
    matrix, bit-exact against `port/tools/gu_expect.py`; cosf bit-exact; fast sin/cos; bcopy/bzero on
    vbe memory.
  - **Matrices:**
    - The one game `guMtxF2L` call in 10 s, the level-load `guPerspective` (`func_15017640` → 0x105D87F0),
      now writes a valid projection.
    - **No frame-DL `G_MTX` changed.** The frame loads a static identity, and zero projections
      (0x10622690 / 0x106226D0 / address 0) that still-asm camera code fills.
    - Flags: `mtxdump=1` (with `dltrace`) and `gulog=N`.
  - **For the port branch:**
    - the same 13 DL-path stubs as P23;
    - top stubs `func_1000CEAC` / `func_1000D2F8` (426 each);
    - `func_150A4ED4` (296 calls) is **not an EU function**: it is inside `func_150A49D0`, so the call in
      `game_eu_13C400.c:173` uses an unmapped name;
    - `func_150A8050` (RPY rotate) is still asm.
- **P27: input, saves, page UX, audio resume** (screenshots `P27_screenshot.png`, `P27_dropzone.png`).
  - **`port/ultra/pc_pif.c`** now holds the PIF model, the controllers and the EEPROM (moved from `pc_os.c`).
    - `osContStartReadData` runs libultra's read block through the PIF and keeps the replies in
      `cont_ram` (`__osContPifRam`). `osContGetReadData` unpacks them.
    - Unpacking PIF RAM directly read garbage, because the game's pak writes reuse PIF RAM in between.
  - **Input:**
    - The page writes `port_pads[4][4]` (present, N64 buttons, stick x/y) through `HEAP32`, with no wasm calls.
    - Keyboard defaults: WASD stick, Space A, F B, Q Z, R L, E R, Enter Start, IJKL C, arrows D-pad, Ctrl half tilt.
    - Gamepads use the Standard mapping; the right stick drives the C-buttons.
    - The stick reaches 80 on the axes and (70, 70) on the diagonals of the octagon.
    - The remap panel is stored in localStorage.
    - **Verified:** a real CDP key press reaches the now-C `func_1501BBB8`. `D_800BED38[0]` buttons 8000, stick
      70,70 → 63,63 after its dead zone; `D_800BED50` new-press mask 8000. `[pad]` lines; `?padlog=N`.
  - **Saves:**
    - The 2048-byte EEPROM goes to IndexedDB (`conker-port` v2, store `saves`, key
      `<rom sha1>/eeprom/<slot>`, `?slot=N`).
    - It is loaded before `callMain` and saved with a 400 ms debounce after each changing PIF write
      (`Module.portEepDirty`).
    - Export and import as `.eep`.
    - If IndexedDB does not answer in 3 s, saving is turned off for the session (never overwrite with a blank).
    - **Verified:** write → reload → read PASS, and another slot fails as expected (`&eeptest=w:SEED` / `r:SEED`).
    - The game's own save path is not reached yet.
  - **Page:**
    - The ROM drop zone has a "never leaves this browser" note and the SHA-1 status.
    - The 4:3 screen scales, and fullscreen keeps the aspect.
    - Pause on tab hide: `port_set_paused` stops frames and the game clock, and suspends audio
      (`?nohidepause=1`).
    - The volume is a GainNode.
    - The debug console sits behind the Debug toggle (`?debug=1`). All dev flags are unchanged.
  - **Audio:** `main.js` resumes the AudioContext on the first pointer or key gesture. With the default
    autoplay policy, audprobe shows it suspended until a CDP click, then running: PASS with 203864 non-zero
    samples.
  - **Tools:**
    - `audprobe.js PROBE_STEPS` (click, keydown, keyup, nav, eval), `PROBE_NOAUTOPLAY`, `PROBE_NOAUDIO`;
    - `boot.sh PADTEST` / `EEPTEST`.
  - **Not tested:** a real gamepad, because headless Chrome has none.
- **P26 (after merging port P24, b742b0d): the camera path is located.** Full notes: P26.md.
  - **Merge:**
    - `src_eu/nm_asm/D5E90.c` is compiled by the census glob as is, and its strong definitions beat the
      weak stubs.
    - P25's PC fast sin/cos (`pc_gu.c`) are removed; the game C `func_150AD78C` / `func_150AD780` wins.
    - `vbe.py FUNC_AS_DATA` += `func_1000EC24` (now C in init_EB00.c, but declared `extern s32` in two
      TUs: a link type clash), `func_15103AA0`, `func_15103910`, `func_150DE8AC` and `func_160036F0`.
    - srcfix is now used by 0 TUs.
  - **Hang fixed:**
    - The NON_MATCHING `sqrtf` (`init_eu_26860.c`: `return sqrtf(value);`, IDO intrinsic) is an endless
      loop under clang, and the newly merged C calls it. node hung after 5 frames; V8 `--prof` put 97.5 %
      of ticks in `vbe.sqrtf`.
    - `vbe.py self_intrinsic` turns the self-call into `llvm.sqrt.f32`.
  - **Renderer:** `G_SETCONVERT` (EC) is a no-op.
  - **Results:**
    - Node: all self-tests PASS, heap 0 errors.
    - Real-time Chrome, Metal, 45 s, heapwatch: past frame 600 with 0 heap breaks.
    - The frame DL is 175 commands, 0 triangles, 0 unknown.
    - DL-path stubs went 13 → 7: func_15110420, func_1510BF50, func_15186D04, func_15182450, func_1508FD38,
      func_15180AF0 and the new func_151EDBE8.
    - Top stub: func_15042ECC (869 calls, vsprintf-like).
  - **Probe:** `?dlstat=N` now also prints `[cam]` (D_800DC6D0, D_800DBFF0, camera record, projection and
    view words, request queue) and `[chk]` (music players, D_800DE1BB/BC, D_800DDD64).
  - **P24 / P22 runtime checks, no bug found:**
    - CEAC / D2F8 are not exercised: the music players `D_800417B0[]` stay NULL, because the music init
      is asm.
    - The D2F8 callback goes through an `i:iiffi` site. The slow path bitcasts slot by slot, which is
      o32-correct for all 9 song-table callbacks (listed in P26.md).
    - FAD4's blend-0 path runs every frame (`D_800DE1BC = 0`, alpha 0).
    - E7FC is not exercised: its node list is empty.
    - func_15088BFC is verified statically: its only caller, func_150538CC, passes its own object.
    - func_151EB81C (counter screen) is not reached.
    - func_1517D7B0 runs with no trap.
  - **For the port branch:**
    - the sqrtf body;
    - the `extern s32 func_1000EC24` declarations in game_eu_12A7C0.c / game_eu_142E40.c;
    - **the camera list below.**
  - **Camera:**
    - The projection is `D_800BE628 + p*0x180 + buf*0x40 + 0x100`, written only by the C func_1510BB78
      (guPerspectiveF + guMtxF2L).
    - The view is `D_800DC6D0[buf] + p*0x40`, written only by the asm func_1512C490.
    - `D_800DC6D0[]` and `D_800DBFF0` are **NULL** because their allocator is a stub.
  - **Camera path, ordered (asm unless marked):**
    1. **func_15005290** (level init in func_15007B3C; allocates D_800DBFF0, D_800DC6E0, D_800DC6D0[0..1],
       D_800BE6D0[], D_800DC440) with **func_150054C4** and **func_1512B168**;
    2. **func_150006E0** (D_800D9F18 projection requests and D_800D9F38);
    3. per frame, C func_15122AE0 (gated by **func_150859AC**):
       - front end: **func_15122C5C** → **func_1510B6A8** → C func_1510BB78;
       - gameplay: **func_1512C490** (C func_15047E70 look-at, then guMtxCatL with **func_150A82D0**);
    4. **func_1510B9D8** (← func_15024910), the other request source.

    Also writing the projection: func_15126378 and func_15129220 (via func_1510B6A8), and func_1501B0A0
    (NM-C).
  - **Frame G_MTX:**
    - 23× MV identity 0x1058F810;
    - 2× MV identity by segment-0 address 0x00089810 (static DL 0x800844F0; resolved correctly);
    - 2× projection 0x10622690 (zero);
    - 1× view multiply at address 0.

    Screenshot `P26_screenshot.png`: the clear colour.
- **P29 (after merging port P28, 1fbb219): the camera buffers are allocated, but the projection is still zero.**
  Full notes: P29.md.
  - **Merge:**
    - The merge was clean.
    - `func_1000EC24` is dropped from `vbe.py FUNC_AS_DATA`; port P28 declares it as a function.
    - `self_intrinsic` now makes 0 rewrites (`NM_SQRTF` = `__builtin_sqrtf`). The pass is kept as a harmless
      safety net.
    - `src_eu/nm_asm/func_150A49D0_tail.s` is never built: the census only globs `.c`, and clang ignores
      `GLOBAL_ASM`. **func_150A3F50 stays a weak stub** (not hit).
  - **Regression fixed:** the now-C func_1510BF50 calls the asm `func_150A5858(D_800B0E00[0], gdl, …)`, whose
    DL pointer is **a1**. The stub returned 0, the frame overran, and it was dropped (12 commands).
    - `gen_stubs.py`: `Gfx *f(T, Gfx *, …)` stubs now return the first `Gfx *` argument (tag `:passthruK`).
    - Frame DL is now 212 to 230 commands, 0 triangles.
  - **Checks:**
    - Node: all self-tests PASS, heap 0 errors.
    - Real-time Chrome, Metal, 45 s, heapwatch: past frame 600 with 0 heap breaks.
    - Screenshot `P29_screenshot.png`: the clear colour.
  - **Camera:**
    - `D_800DC6D0[0..1]` and `D_800DBFF0` are allocated (the C func_15005290).
    - func_15122AE0 runs for player 0 and takes the front-end branch → the asm func_15122C5C (136 per 10 s).
      The gate func_150859AC is C; there is one player, and i = 0 always passes.
    - The asm camera functions hit are func_150006E0 (2), func_150045C4, func_150054C4, func_1512B168 (1 each)
      and func_15122C5C. Never hit: func_1510B6A8, func_1512C490, func_150A82D0 and func_1510B9D8.
    - **The projection 0x10622690 is still zero.** Its only writer, the C func_1510BB78, is reached only through
      the asm func_1510B6A8 or the request queue that the asm func_150006E0 sets up.
    - The view `D_800DC6D0[0]` is non-NULL but **uninitialised heap**; only the asm func_1512C490 writes it.
    - A new valid `DA380007 105D87F0` (the level-load perspective) comes through the C func_1510BF50.
  - **func_15110420's callback (P28 UNVERIFIED): no bug.**
    - The C `i:iffffffi` site matches the asm o32 layout: x/y/z in a1..a3 as bits, yaw/pitch/roll/handle at
      sp+0x10..0x1C.
    - `D_80089578` = {func_15110948, func_150FA030, func_150D1D20, func_15110B80, func_15112074}. At runtime
      `unk8 = 0`, which calls the stub func_15110948; the DL pointer stays valid.
    - New `[icalltest]` cases: an exact `Gfx *(Gfx *, f32 ×6, s32)` callee, and an `s32 ×8` callee through the
      slow path, which receives the f32 bit patterns. Both ok.
    - **Note for the port branch:** the C `func_15110B80(Gfx *, s32, s32, s32)` receives x/y/z as float bits.
      It does not use them; type them `f32` if it ever does.
  - **For the port branch:**
    - **Camera, asm, in call order:**
      1. func_150006E0 (request queue: the shortest route to a non-zero projection);
      2. func_150045C4;
      3. func_150054C4 / func_1512B168;
      4. func_15122C5C → func_1510B6A8;
      5. not reached yet: func_1512C490 + func_150A82D0, then func_1510B9D8.
    - **Frame-DL-path stubs (11):** func_151EDBE8, func_15110948, func_1515DE84 (world), func_150A5858,
      func_1517485C, func_15186D04, func_15182450, func_150911F4, func_15090630, func_15180AF0, func_150900F0.
    - **Top 15 stubs:**
      - func_15042ECC (869);
      - func_1000A03C (270);
      - func_151EDBE8 (212);
      - func_1509BE40 (138);
      - func_1501B300 (137);
      - at 136 each: func_151E7110, func_150A067C, func_10011624, func_151143D4, func_15044D18, func_1504A730,
        func_1501ECA4, func_15020F6C, func_15122C5C, func_1504ADD0.
- **P31 (after merging port P30, 2c94c13): valid projection and view; the frame has no triangles because level
  0x25 is the 2D boot screen.** Full notes: P31.md.
  - **Merge regression fixed:** `[memtest]` failed with every `want` = 0. `sigs.py` keys signatures by name, statics
    included, and P29's `static check()` in game_icalltest.c (3 args) rewrote game_entry.c's `check()` (4 args).
    It is renamed `ict_check`. **Rule: no static PC function name may be reused with another signature.**
  - **Checks:** node: 7/7 self-tests PASS, heap 0 errors. Chrome (Metal, 45 s, heapwatch): past frame 600, 0 heap
    breaks. Screenshot `P31_screenshot.png`: the clear colour.
  - **Projection:** it was saturated (NaN), because the camera record was zero. The **TEMPORARY PC func_1501A8C0**
    (camera record init, from the asm) fixes it. 0x10622690 is now `1.7113 / 2.1445 / -1.0101 / -1 / -100.50`:
    fov 60.6 x 50 degrees, near 50, far 10000, viewport 292 x 216.
  - **View:** it was zero, because func_1512C490 → func_15047E70 → the asm stub **func_150479F0** (guLookAtReflectF
    variant). The **TEMPORARY PC func_150479F0** gives a valid rotation. Eye = at = 0, because the camera target
    object `D_800CC2D0[0]+0x31C` is NULL: no object is spawned yet.
  - **Geometry:**
    - Level 0x25 (VI frames 0 to about 720, then level 0x21) is the boot screen func_151EC300. It shows text through
      the asm func_15042ECC + func_15041A9C and sprites through the asm func_151EDBE8. It has no 3D model: asset
      (2, 0x25) is not found.
    - For the world, the stubs in order are **func_150031EC** (level model loader, sets D_800B0E00) and then
      **func_150A5858** (hand asm visibility walk).
    - PC func_150031EC + func_15003120 are behind `?lvlload=1`. **That breaks the heap at the switch to level
      0x21** (not diagnosed).
    - `?dlapprox=1` makes func_150A5858 emit the whole level DL. It is a diagnostic only.
  - **For the port branch:**
    - **bug**: `game_14FF90.c` func_15127EB8 calls `func_1510B8AC(…, 0, 0, 0x3F800000)` with no prototype. The
      asm passes 1.0f, so it must be `1.0f` with a prototype `void (s32, f32, f32, f32)`.
    - Convert: func_1501A8C0, func_150479F0, func_150031EC/func_15003120, func_15042ECC, func_151EDBE8/func_151EDA54,
      and the object spawners func_15082E44 / func_1506C460.
    - P30's UNVERIFIED items:
      - func_150006E0 is OK (it receives the level, 37);
      - the func_1512C490 `obj == NULL` reads run every frame with no trap; the 0x8000 case is not exercised;
      - the func_150A82D0 constant is π/180 (static check);
      - func_150045C4 and func_1517485C are not exercised.
- **P33: the level-load heap break is fixed, and real level geometry is on screen.** Full notes: P33.md.
  Screenshot `P33_screenshot.png` (`shot.sh OUT 'app=game&dlapprox=1&freecam=1' 45000`): level 0x21's wooden floor,
  288 textured, lit triangles.
  - **Root cause of P31's break:** Rare's inflater **func_1000654C** (init_eu_5DA0.s, hand asm, state in $f16..$f18)
    was a weak stub, so every compressed asset loaded as zeros.
    - The C func_1502B4A8 then searched the zero model list (asset (4, level), not (2, level)) for a bit-31
      terminator. It found one 0xF34 entries further on and "relocated" the next heap headers.
    - The PC func_150031EC and allocate_memory were correct.
  - **TEMPORARY PC func_1000654C** (`pc_mem.c`, from the asm entry; the raw-DEFLATE decoder now has a vbe mode):
    - the stream starts at src+4, or src+2 after a 0x1172 halfword;
    - the limit is min(src−dst if src>dst, limit−dst);
    - it returns the bytes written.

    All rzip assets now load. Node 60 s and Chrome 45 s with heapwatch: no break, 7/7 PASS.
  - **The PC level loader func_150031EC is now the default** (`?nolvlload=1` restores the stub). Level 37 gets a model
    too (4 entries). Without `dlapprox` the frame still has 0 triangles: func_150A5858 is a stub.
  - **Screenshots since P21 showed the animated "alive" colour, not the game frame.** pc_video.c cleared on every
    VI frame without a gfx task. It now clears only until the first game frame.
  - **`?freecam=1`** (diagnostic) replaces the world view, i.e. the `G_MTX` P-multiply after the projection load,
    with a fly camera on pad 0:
    - WASD moves, IJKL looks, E/Q go up/down, Ctrl gives half speed;
    - `fcx/fcy/fcz/fcyaw/fcpitch` set the start pose; otherwise it frames the previous frame's bounds;
    - verified with CDP key events.
  - **`?drawlog=N`:** per-draw state, NDC box and a 5x5 `glReadPixels` grid for gfx task N.
  - **Renderer: still wrong or unverified (precise list in P33.md §3):**
    1. no level visibility culling (func_150A5858 stub; dlapprox draws everything; LOD parts 1..3 unused);
    2. `G_CULLDL` is ignored and `G_BRANCH_Z` always takes the near branch;
    3. the Conker light formula is unchecked, and the `G_MOVEMEM 0x0A` records at offsets 0x00/0x30 are dropped
       (n < 0);
    4. the Rare `G_MOVEWORD` index 0x10 block (12 words per frame) is ignored;
    5. GL bilinear instead of 3-point; no mip/LOD/detail; mask+clamp is approximated;
    6. the CI-as-RGBA heuristic is not exercised;
    7. blender: only FORCE_BL alpha; P/A/M/B, coverage and dither are not decoded; decals use polygon offset;
    8. depth: no prim depth / `G_ZS_PRIM`; the z clear is recognised only as cimg == zimg;
    9. fog is not exercised (no G_FOG in level 0x21);
    10. no guard band or clip ratio (`G_MW_CLIP` ignored);
    11. `G_MW_PERSPNORM` is ignored (harmless);
    12. viewport overscan and aspect: Vp 302x226 on a 292-wide cimg, H = cimg × 0.75;
    13. the second-pass combiner `FFB3FF/FF64FE7F` and K4/K5/noise are not handled;
    14. the texture cache re-decodes on every TMEM load (performance);
    15. no N64 reference frame to compare colours.
  - **For the port branch:**
    - convert func_1000654C + func_1000661C..func_100070F0 (inflater);
    - func_150A5858;
    - func_150031EC / func_15003120;
    - the object spawners (the camera target).
- **P35 (+P35b): renderer accuracy on level geometry.** Full notes: P35.md. Screenshots `P35_screenshot.png`
  (level 0x21) and `P35_*.png` (0x21 from three views, plus point filter; 0x25 boot level).
  - **The level ucode is F3DEXBG**: it is the task ucode, and the rest of the frame switches ucode with
    `G_LOAD_UCODE`. Its light overlay was disassembled (IMEM 0x12D8..0x15EC, `?udump=1` + rabbitizer RSP).
    - The colour is `vtx rgb × min(1, col[record M] + Σ point lights col × min(1, att))`, with M = NUMLIGHT/48.
    - There are no normals and no directional light. Point-light distances use Rare's `G_MOVEWORD 0x10` block as an
      inverse projection.
    - The level sends M = 0 and record 0 = white, so it keeps its prelit vertex colours.
    - The other ucode (characters, `0x0E` normals) uses P35's model: record M = directional sun (n·d), record
      M + 1 = ambient. That model is **unverified**.
  - DMEM light records, the Rare block and normals are seeded from the ucode data image at task start and on
    `G_LOAD_UCODE`.
  - **`G_CULLDL`** (all vertices outside one clip plane) and **`G_BRANCH_Z`** (screen z ≤ w1) are implemented. Levels
    0x21 and 0x25 do not use them, so they are not exercised yet.
  - **Blender:** the P/A/M/B selectors are decoded per cycle into shader blend or `glBlendFunc`, with alpha
    compare/dither, coverage from alpha and prim depth.
    - Fog: the fog factor goes into shade alpha and the blender reads it.
    - Fill rects in 1/2-cycle mode now go through the combiner and blender. The boot level's end-of-frame fade quad
      is black, so the boot screen is black; `?nofillrect=1` shows the level under it.
    - `G_SETSCISSOR` → `glScissor`.
  - **Textures:**
    - exact `texelFetch` addressing per tile (clamp, then mirror, then mask; per-tile shift);
    - the **3-point filter** is the default (`?filter4=1` gives bilinear, `?filter0=1` point);
    - `G_TL_LOD` tile selection with `LOD_FRACTION` (unexercised).
  - **Renderer gaps still open:**
    1. no level visibility culling: `func_150A5858` is a stub, `dlapprox` draws all of D_800B0E00[0], and the LOD
       parts 1..3 are unused;
    2. the light model of the second ucode (F3DEX/BS, characters) is not checked against its RSP code, and neither
       is BG's exact point-light attenuation scale (32768·K/d²) — no point lights exercised;
    3. `G_CULLDL`, `G_BRANCH_Z`, fog, LOD/mip and detail/sharpen are implemented but no tested frame uses them;
    4. the coverage model is approximate: no real 8-sample coverage, `CVG_DST`, `CLR_ON_CVG`, or memory alpha
       (taken as 1), and decals use polygon offset instead of the z-delta compare;
    5. level 0x25 from above: the −z half of the ±10000 plane is missing (not investigated; maybe near-plane or
       w ≤ 0 handling);
    6. a fill rect in 1/2-cycle mode uses shade 0 and s = t = 0 (RDP behaviour as understood; the boot fade quad is
       opaque, so check it against the real boot sequence);
    7. no guard band or clip ratio, and `G_MW_PERSPNORM` is ignored (harmless);
    8. viewport overscan and aspect (H = cimg × 0.75);
    9. combiner K4/K5 are passed in but unverified; the second-pass combiner `FFB3FF/FF64FE7F` is not checked;
    10. the texture cache re-decodes on every TMEM load (performance);
    11. no N64 reference frame to compare against.
- **P37 (after merging port P36, c93ba87): the game's own C replaces every PC stand-in.** Full notes: P37.md.
  - **Removed:** func_1501A8C0, func_150031EC / func_15003120, func_150479F0, the func_150A5858 diagnostic
    (`pc_overrides.c`) and func_1000654C (`pc_mem.c`). The `nolvlload` flag is gone.
  - **Diagnostics are now link-time wrappers** (`-Wl,--wrap=`, `port/Makefile`), each with the callee's exact wasm
    signature:
    - `dlapprox`, and `?vislog=N` (tri counts, `[vis]`), in `gfx_f3dex2.c`;
    - `?infcheck=1|2` (inflater against an independent decoder, `[texid]`, level-loader brackets), in `pc_mem.c`.
  - **Port-side bugs fixed** (each crashed node):
    1. The PC main thread called the US name `func_1000709C`, so the inflater's fixed tables (EU **func_1000738C**) were
       never built.
    2. `vbe.py ROM_ABS` += `D_D11`, `D_A4A`, `D_89C`, `D_85D` (texture ids), `D_1A3750` and `D_1A3840` (the
       func_15016950 setup-table ROM range), and `D_2C1` / `D_1C0`.
       - As wasm addresses, the texture ids pushed func_1510D66C's dirty range past its tables, and func_1510D984
         inflated garbage.
       - **Rule:** every `D_<hex>` in `undefined_syms_auto.txt` with a value below 0x80000000 that game C uses as a number
         must be in ROM_ABS.
    3. func_150A5858 with an empty visibility range: its clear loop (a do-while, as in the asm) runs off memory. The
       wrapper skips the call when the inputs are missing.
  - **Checks:**
    - Node 60 s with heapwatch: 7/7 PASS, heap 0 errors.
    - Chrome (Metal, 45 s, heapwatch): no break, heap 0 errors.
    - Inflater: 64/64 calls match, including the level 0x21 model list (14904 bytes) and texture 0xED0 (768 bytes).
  - **Camera target present:** `D_800CC2D0[0]+0x31C` ≠ NULL after the level 0x21 load (mask 0x0001, char 0, entry 0
    spawned). Its eye/at (+0x13C..+0x150) are still 0, so the game view looks from the origin.
    `P37_screenshot.png` (game view, no freecam) is black, because the frame has 0 triangles.
  - **Visibility walk:** not run on real data. Its range and tree come from the asm **func_15001460** (level-DL triangle
    walk, counts D_800DBE38, writes D_800DC26C/270/274), **func_15001A08** (node pool) and **func_15002008** (leaf
    lists).
    - Without `dlapprox` the frame has 0 level triangles; with it, 288.
    - The P34 `$gp` / previous-index item is still open.
  - **Stubs:** 82 distinct, 19023 calls in 30 s. Top: func_15041A9C (869), func_1512C6C0 (684), func_1509BE40,
    func_151283B8 (345).
    - Frame-DL-path stubs: func_15041A9C, func_15196560, func_15186D04, func_1502CC64, func_15182450, func_15180AF0, plus
      func_15001460 and func_15017B20 at level load.
  - **For the port branch:**
    - convert func_15001460, func_15001A08 (a JUSTREG draft is in game_eu_2F180.c) and func_15002008;
    - `init_1050.c`'s commented func_10001194 calls `func_1000709C`, which must be `func_1000738C` (asm 0x10001278);
    - no transcription bug was found in the P34 / P36 C that ran: the inflater, the level loader, the camera record,
      lookat and the spawn chain.
- **P39 (after merging port P38, 8e17fd1): the camera eye/at writer is found; its inputs are asm stubs.** Full notes: P39.md.
  - **Merge:**
    - The merge was clean.
    - `nm_asm/func_150A6840_tail.s` needs nothing: `.s` files are not built, and func_150A6A48 stays a weak stub (not
      hit).
    - func_1504A730, func_15186D04, func_15182450 and func_1505E650 now run as C. There are 83 distinct stubs.
    - Node: 8/8 PASS, heap 0 errors. Real-time Chrome (Metal, 45 s, heapwatch, twice): 0 RuntimeError, heap 0 errors,
      past frame 600.
  - **Writer:** the target's eye/at/dir (`D_800CC2D0[0]+0x31C` +0x130..0x150) is written every frame by the **C**
    func_1512C490, through func_15122AE0 → func_15122C5C → func_151284C4.
    - It writes zeros. The followed record `D_800CC2D0[0]` (EU 0x800CC6F0) is at (0, 0, 0), and the controller's at
      (0x2A4 / 0x2BC) and eye (0x2F8) are 0.
    - `?camwatch=N` is a write watch: it compares at every stub entry and around func_1512C490, logs with JS stacks, and
      logs first hits of the camera stubs.
  - **For the port branch, camera, in order:**
    1. func_150858A0 + func_150851E0 (game_eu_B2980): place the player record at the level start;
    2. func_15005818 (game_32740): the initial eye;
    3. func_151247C0 (game_14FF90, 213 lines): at follows the record;
    4. func_15123A54 (game_14FF90, 917 lines): the eye orbit;
    5. func_151283B8 → func_15122EF0 (mode 1);
    6. later, func_1504CB98 (5006 lines, the per-object player callback of func_1504A730).
  - **Runtime checks (`?p38check=N`):**
    - func_15186D04 emits 0 commands. Object 0 fails the filter on `+0x1D4 == NULL`, which is set only by the asm chain
      func_1502C1D4 → func_1502C074 → func_1502E228. The strip splitter therefore stays **UNVERIFIED**.
    - The func_1504A730 stack-buffer branch is unreachable with D_8008FD8C = 1 slot. D_800CC6A4 is never left in a dead
      frame (0 of 512 calls). No bug.
    - func_150A6840 is not called; its wrapper checks it against a float reference once it is.
    - No bug was found in the P38 C.
  - **Screenshot:** `P39_screenshot.png` is the freecam + `dlapprox` level geometry (288 triangles). No objects or
    shadows draw yet.
- **P42 (after merging port P40, 005e00a): the real visibility walk draws level 0x21.** Full notes: P42.md.
  - **Merge:** it was clean. The first boot trapped in func_15001A08: `IO_READ(osRomBase | 0xB0000D24)` has a computed
    address, so it was a wasm load at 0xB0000D24.
    - `vbe.py rcp_io` now also turns `or x, 0xA0000000` → inttoptr → volatile load into `__port_io_read(x)`.
    - `__port_io_read` answers 0xB0000000.. with the big-endian ROM word: `[io] cart read 0xB0000D24 = 0x98CCE31A`,
      the asm's compare value, so the node pool is not doubled.
    - PI_STATUS was already idle.
  - **KSEG0 pointer tests:** the new `vbe.py k0_ptr_sites` rewrites, scoped by function, with an expected count:
    - func_15002008 and func_15002248: `(u32)p < 0x80000001` → `< 0x10000000`. Without this, every real vertex reads
      as (0, 0, 0) in the quadtree box tests.
    - func_15004CE0: `< 0x80000000` → `< 0x10000000` (not run yet; its caller func_150039E0 is asm).
    - func_15001460's `>= 0x100001` is correct as is.

    **All sites (P9 and P42) are listed in MEMORY.md, "Pointer-range tests in game C".**
  - **Walk:** without `dlapprox`, func_150A5858 gets its range and tree.
    - Level 0x21: **172 of 288 triangle slots**, 168/288 visibility bytes.
    - The pool counters are 103 nodes and 77 leaves, equal to P40's harness. The leaf lists hold 388 entries, at most
      97 per leaf.
    - Boot level 0x25: 24 of 36.
    - **P34 `$gp` item closed:** no leaf starts with a relative index, because func_15002008 always writes the first
      entry as a halfword | 0x8000.
    - `?vislog=N` now logs per (dl, tree) pair; with N ≥ 3 it dumps the output.
  - **The level is black without `?lvlwhite=1`. This is stub-dependent, not a C bug.** The C func_1515DE84 sends
    NUMLIGHT 0x30, and record 1 = `arg8` = its local `col`. The still-asm **func_1515E7E8** should fill `col`; with the
    stub it is uninitialised stack (P39: dim green; now 0). `?lvlwhite=1` (diagnostic) makes a black BG start colour
    white.
  - **Checks:**
    - Node 30 s, clean build: 8/8 PASS, heap 0 errors.
    - Real-time Chrome (Metal, 45 s, heapwatch): 0 RuntimeError, heap 0 errors, frame 600 at 172 triangles.
    - Stubs: 81 distinct (from 83), 22980 calls in 30 s. Frame-DL-path stubs: func_15041A9C, func_15196560,
      func_1502CC64, func_15180AF0, func_15017B20.
  - **Screenshot:** `P42_screenshot.png`, freecam + real walk + `lvlwhite`: the wooden floor. The far part is culled,
    because the walk culls for the game camera, which is still at the origin.
  - **For the port branch:**
    - convert func_1515E7E8 (+ func_1515E9AC): the level light colour;
    - then P39's camera list.
    - No bug was found in the P40 C.
- **P44 (after merging port-b P41, 52baa69): the game's own camera view.** Full notes: P44.md.
  - Clean rebuild. Node 30 s: 8/8 PASS, heap 0 errors. Real-time Chrome (Metal, 45 s, three runs): 0 RuntimeError,
    heap 0 errors, frame 600 at 340 commands and **288 triangles**: the whole floor is in the game's view.
  - **P41's camera chain is correct at runtime (`?camwatch`). No C bug was found.**
    - D_800CC2D0[0] is placed at the level start: (27, 1, 27) on level 0x21, (-245, 14, 9464) on boot level 0x25.
    - at follows it, and eye = at + (sin, cos)(yaw) * 530.
    - obj+0x130..0x150 are non-zero.
    - The lookat and perspective matrices check out (`mtxdump` + `dltrace`).
  - **Screenshot** `P44_screenshot.png`: no freecam, the real walk, `?lvlwhite=2` (new: forces white for any BG start
    colour; the func_1515E7E8 stack garbage is dim green again). It shows the floor at a grazing angle.
    - **eye.y stays at the start table's 40:** the eye height writers func_1512E6B0 (0x2FC = 0x354 + offset) and
      func_1512A390 (clamp 0x354 + 30) are asm stubs.
  - **Moving:** scripted W / C-right reach `D_800BED38[0]`, but the record, at, eye and yaw never change. The state
    handler **func_1504CB98** (5006 lines; 12 of its 61 callees are stubs, func_15056B08 1752 lines the largest) and
    func_150A16A4 (799 lines, before it in func_1504A730) are stubs. So "does the camera follow" waits on them.
  - **func_150ACEA0** (ray cast) is in the unsplit `asm/D5E90.s` (kind `missing`). On level 0x21 (open floor), its
    "no hit" stub breaks nothing visible.
  - Frame-DL-path stubs are unchanged. 82 distinct stubs; 16 camera-helper stubs run per frame (table in P44 §5).
    func_1512C6C0 (48 lines) is the top stub.
  - New flag `?camevery=N`: the camwatch summary every N calls.
  - **For the port branch:**
    - func_1512E6B0, then func_1512A390: the eye height;
    - func_1504CB98 + func_150A16A4: the player moves;
    - func_1515E7E8: the level colour.
- **P46 (after merging port P43 + P45, bb80ab1): the first lit, framed game-camera frame.** Full notes: P46.md.
  - Clean rebuild. Node 40 s: 8/8 PASS, heap 0 errors, 74 distinct stubs (P44: 82). Real-time Chrome (Metal, three
    runs): 0 RuntimeError, heap 0 errors, frame 600 at 347 commands and 288 triangles.
  - **Screenshot** `P46_screenshot.png`: no freecam, no `lvlwhite`. Level 0x21's floor seen from above (about 37°
    down), lit by the game's own lights.
  - **Level colour:** still black after P43. The cause was a dropped TU, not P43's C. `game_36680.c` (the level light
    init **func_150091D0**: `func_1515D4D4(255, 255, 255, 0)`) failed under clang on `u8 sp1C[4] = D_80095B70;`.
    **`srcfix.py` kind `arrinit`** now copies such arrays element by element. It fixes game_36680.c and game_2062D0.c.
    BG start colour: 000000 → 262626 with 3 point lights (`?lvlcol=N`).
  - **Eye height correct:** eye.y = base 0x354 (1) + dy 0x344 (400 = h 0x348). No bug in func_1512E6B0 /
    func_1512A390. Their floor query, the asm **func_1510EED0** (932 lines), is now the #2 stub; the floor stays at the
    -10000 default.
  - **TEMPORARY `sigs.py A0_KEEP`:** game_14FF90.c func_15127FEC calls `func_1512A390();` with no argument. sigs.py
    padded it with NULL (no trap, a null-zone write if reached). Now it passes the caller's arg0, as a0 does in the
    asm. Remove it when port-b fixes the source. func_15127FEC was not reached in 40 s.
  - **func_1509BE40 → D_80088838:** mismatches (asm-stub `v:` entries, func_1509CBD8 `v:iii`) go through
    `__port_icall_slow` with no trap. Entry 1 **func_1509A024** (1655 lines) is the stub that runs every frame.
  - **Objects do not draw:** func_1502CC64 (C) returns early because the player record's model +0x1D4 is 0. It is set
    by func_1502E228 through the C func_1502C074, whose only caller is the **asm func_1502C1D4** (198 lines, per-object
    update; not a "shadow chain"). `?p46check=N` (wraps of func_1502BDC0 / func_15196560).
  - **func_15196560:** runs every frame, but its list D_800E0D18 is empty on both levels. Not exercised.
  - **func_150A16A4 kind 8:** not reached. The PI model is right: ROM 0x454 = 0x0109082B, + 0x400 = the tested
    0x01090C2B. `[pi] raw read` logs the first 8.
  - Movement: unchanged; func_1504CB98 is still a stub. func_1507E690 (76 lines, under func_1507EB1C) is a new stub.
  - **For the port branch:** fix `func_1512A390(arg0)` in func_15127FEC; **func_1502C1D4**, func_1502E228,
    func_1502E7B4 (Conker's model); func_1504CB98 + func_1507E690 (movement); func_1510EED0 / func_150A44A4 (floor);
    func_1509A024. game_36680.c and game_2062D0.c build on the PC only through srcfix; write explicit copies if they
    get NON_MATCHING bodies.
- **P49 (after merging port-b P47, cd88fdd): the player walks and the camera follows.** Full notes: P49.md.
  - Clean rebuild. The P46 `A0_KEEP` entry is gone (`A0_KEEP = set()`). Node 40 s: 8/8 PASS, heap 0 errors, no
    heapwatch break, 83 distinct stubs. Real-time Chrome (Metal, `heapwatch=1`, W / D / S keys): 8/8 PASS, heap 0
    errors, no RuntimeError.
  - **The C walk handler func_1504CB98 works:** the stick sets the target speed +0x44 = 35, the camera-relative
    heading +0x76 and the speed +0x3C. **x / z did not change because the integrator func_15059C84 (asm) was a
    stub.** TEMPORARY PC version (full, step by step from the asm) in `port/boot/pc_overrides.c`.
  - Second blocker: **func_1504C0E8** (stub) never set +0x80, so func_150599C8 never turned the body yaw +0x7A.
    The handler then cut the speed whenever +0x3C > 12 (it saw-toothed 7..14). TEMPORARY **partial** PC version
    (prefix only: the unk31C+0x12 easing and `+0x80 = 1` on the ground path; no animation choice). Speed now 35,
    +0x7A follows.
  - Camera: `at` = the record every frame; the eye trails 530 to 680 behind at height 401 and swings behind on turns.
    The stick is camera-relative. Screenshot `P49_screenshot.png`; frame sequence `docs/port/sessions/p49/walk_*.png`.
  - No floor or wall collision yet: at about 600 units/s the player leaves level 0x21's floor in about a second (a long
    W hold turns the view black about 2 s in).
  - **UNVERIFIED branches of func_1504CB98:** the C-button steering (needs D_800BE616 or unk31C+0x78 in 9 / 0x16 /
    0x3B), unk31C+0x4E == 2 and the in-water turn rate are not reachable on level 0x21. All three were read against
    the asm instruction by instruction: **no bug found**.
  - **For the port branch, the movement path in order:**
    1. **func_15059C84** (341 lines, integrator);
    2. **func_1504C0E8** (531, animation choice + +0x80);
    3. **func_1505A770** (163, gravity: y / y_velocity);
    4. func_1510EED0 (932) / func_150A44A4 (282): floor, +0x118 stays -10000;
    5. walls: func_15044950 (169), then **func_150AB6D0 / func_150AC8C4**, which are in the unsplit `asm/D5E90.s`;
    6. func_15021834 (423, x2: +0x28, old position);
    7. then func_1505F298 (1281, jump / attack), func_1505A9AC (893, landing), func_15051558 (824), func_1505D6F0,
       func_1508000C.

    Drop both P49 overrides when 1 and 2 are converted.
  - Tools: `?p49walk=N` / `?p49every=N` (`port/gfx/p49_walk.c`, wrap of func_1504CB98; logs the record and the stubs
    reached inside the call through `port_stub_trace_hook`), node `PADSCRIPT`, audprobe `MS:shot:PATH`.
- **P52 (after merging port-b P50 + port P48, f123763): the movement and model C at runtime.** Full notes: P52.md.
  - **P49's TEMPORARY func_15059C84 / func_1504C0E8 overrides are removed**; the P50 C runs. Clean rebuild. Node 40 s
    and real-time Chrome (Metal, `heapwatch=1`, W / D / S): 8/8 PASS, heap 0 errors, no heapwatch break, 91 stubs.
  - **Walking with the real C equals P49's PC version:** speed 35, 42 units per call, +0x7A follows +0x76, camera
    `at` follows. Gravity func_1505A770 (C) is right; **D_800D1550[0] = 1.2 then 2.4** (sane).
  - **The player does not fall off the edge:** func_1510EE3C (C) forwards to the asm stub func_1510EED0, so the walk
    handler's floor height `spC4` is never written (reads 0, uninitialised) and line 2569 snaps y to spC4 - 1 = -1
    every call; vy sits at -500 (func_1505A9AC, landing, is a stub). With the diagnostic `?p52void=1` the player
    falls under the C gravity. Not a bug in converted C.
  - **+0x1D4 is still 0:** the C func_1502C1D4 runs every frame and reaches func_1502DE74, but D_800D19A0[0] is 0 and
    the model loader **func_1503D210 is an asm stub**, so DE74 returns before +0x1D4 (func_150A86B0 is never reached).
  - **Black screen = correct culling:** the camera follows the player off the floor; the floor ends up behind it and the
    C visibility walk emits 0 / 288 triangle slots (288 → 252 → 172 → 114 → 0). No NaN. Screenshot
    `P52_screenshot.png`, sequence `docs/port/sessions/p52/walk_00..05_*.png`.
  - **For the port branch:** no bug found in func_15059C84 / func_1504C0E8 / func_1505A770 / func_1502C1D4 at
    runtime. Next: func_1510EED0 (floor), func_150A44A4, func_15021834, func_1505A9AC; for the model func_1503D210,
    then func_150A86B0, func_150342D0 / func_1502DB14, func_1502CFEC.
- **P55 (after merging port-b P53 + P54, 6bc3909): standing, walking off and landing with the real floor C.** Full
  notes: P55.md.
  - Clean rebuild; none of the P53 / P54 functions is a stub any more. The P54 nm_asm tails do not matter for wasm
    (`.s` is never built; all four collectors are C). Node 40 s and real-time Chrome (Metal, `heapwatch=1`, W holds):
    8/8 PASS, heap 0 errors, no heapwatch break, no RuntimeError. 91 distinct stubs.
  - **The walk handler gets a real floor height:** spC4 = 0 on level 0x21 (288 floor triangles, all y = 0, x / z in
    -240..240; area 0, func_150A3F50 BSP path). A float barycentric reference over the same triangles agrees.
  - **Stand / walk / fall / land work:** standing y = 0 with vy reset to -4 by the landing C every call; walking keeps
    y = 0; past the edge (z ≈ 267) the query gives -10000 and the player falls; a diagnostic drop from y = 300
    (`?p55drop=300`) lands: y → 0, vy -88 → -4, +0x28 → 0. The 10000-unit fall takes the fall-death branch
    (health = 0, stubs func_1513783C / func_1507CD64), game-consistent.
  - **Slopes:** level 0x21 is flat, so `?p55synth=1` runs the C query on a synthetic sloped quad + overlapping shelf
    through vbe memory: 4356 points, 0 misses / extras, |C − float| max 0.92, mean 0.41. PASS.
  - **P54 `$gp` tag item closed:** no reader of D_800D3720 +0xC uses area-0/1 entries (func_1510EED0 reads it for
    areas 2 / 3 only; the game_eu_71E70 readers use func_150A48C0 entries; func_15104BB4's `lw 0xC` is a stack index
    list).
  - **Crash fixed (port side):** after the fall the C func_150900F0 (game_BC510.c) emits `G_DL D_800D29A8` with
    `D_800D29A8 = func_1518C900(0xB8)`, an asm stub that returns 0; the renderer ran RDRAM 0 as a DL and hit
    `memory access out of bounds`. The renderer now skips a G_DL to address 0 (logged once). New `?gdlzero=N`.
  - Camera: `at` follows x / z, but at.y stays 1 and eye.y 400 while the player falls (its own floor height).
  - **No bug found in the converted C** (func_1510EED0, func_150A3F50, func_150A44A4, func_1505A9AC, func_15021834).
  - Screenshot `P55_screenshot.png`; sequence `docs/port/sessions/p55/walk_00_stand.png .. walk_06_4000ms.png`.
  - **Stubs, movement path** (per walk-handler call): func_150AB6D0 x4 / func_150AC8C4 x3 (wall engine, body
    func_150AB708, converting on port-b), func_1507C7C0, func_1508000C, func_1505F298 (jump), func_1505D6F0,
    func_15051558, func_1507F640, moving: func_1505E0C4, func_1506E46C, func_1507D4F8; also func_1507C170; ray cast
    **func_150ACEA0** (one per frame, converting on port-b). **Model path** (P51 on port, not merged here):
    func_1503D210, func_1502F17C (top stub), func_1502F554, func_1503A37C, func_15030758, func_150A9B0C, func_1507E7A0,
    then func_150A86B0, func_150342D0 / func_1502DB14, func_1502CFEC. **New for the port branch:** func_1518C900
    (+ func_1518CF74), the DL getter behind the G_DL 0.
- **P58 (after merging port P51, 8f18a3f): the model load and the skeleton evaluator at runtime.** Full notes: P58.md.
  - Clean rebuild; `nm_asm/D5E90_anim.c` compiles in the census glob. Node 40 s (W hold, `heapwatch=1`) and real-time
    Chrome (Metal, `heapwatch=1`): 8/8 PASS + `[tables] PASS`, heap 0 errors, no heapwatch break, no RuntimeError.
    97 distinct stubs.
  - **Model loads:** the C func_1503D210 returns 0 for id 0 (frames 2 and 723); `D_800D19A0[0]` set; **+0x1D4 non-zero**
    every frame; func_150A86B0 runs once per frame for record 0.
  - **Four port-side blockers fixed** (no bug in the converted C):
    1. **`D_150AA11C`** (evaluator sine table, code segment) was a zero 0x100-byte weak data stub → every joint 3x3 was 0.
       Now real data in `port/ultra/pc_tables.c` (sin rounded to 6 decimals + 12 ROM corrections), bit-exact,
       `[tables] PASS`. **Rule:** tables in the code segment are not loaded on the PC; a C function that reads one gets
       a zero stub from `data_stubs.c`.
    2. **TEMPORARY PC func_150A9B0C** (`pc_overrides.c`; EU code at 0x150A9FEC in the unsplit D5E90.s, 76 insns): the stub
       left func_1502E228's root matrix as stack garbage (NaN joints on level 0x21).
    3. **TEMPORARY PC func_1000480C** (`pc_mem.c`; small blocking PI read): func_1502DB14's key-frame copies were empty.
    4. **TEMPORARY wrap of func_150342D0** (`p58_model.c`) writes the 0x1000 terminator first: with the stub the
       evaluator applied ~200 garbage angle and ~110 scale edits per call (`?p58noterm=1` shows it).
  - **Evaluator verified under vbe:** header / key-frame bytes equal the ROM; on three ROM animations (`?p58anim`) every
    matrix is finite and orthonormal, all 27 bone lengths equal the skeleton, the pose moves smoothly and loops.
    **Callback table:** jtbl_8008891C_game[1..5] are relocated by P4 to the right wasm functions; Conker's slots 7 / 12
    call entry 1 (func_15036FD8, asm stub) through the icall layer with no trap.
  - **In the game Conker stays in the bind pose:** the animation driver **func_1505E0C4** (asm) never fills the state.
  - **Preview `?p58pose=1`:** the closest ROM viewer Conker (0xAFA400) drawn after each frame with the evaluated joints.
    `P58_screenshot.png` (`p58anim=1`: his stride), `p58/anim0_a.png` (bind pose, assembled).
  - **For the port branch** (in order): func_1505E0C4 (animation driver); func_150A9B0C (**EU 0x150A9FEC**, see
    pc_overrides.c); func_1000480C; func_150342D0 + func_15034B50 (P57); the draw: func_150A9E64 (`missing`, D5E90.s,
    arena f32 → Mtx), func_1502CFEC, func_1502C9D8, func_1503AB20, func_1503BCAC, func_1503DD8C, func_1502F17C,
    func_1502F554, func_1503A37C, func_15030758, func_1507E7A0, callbacks func_15036FD8 / func_15037224 / func_1503A968.
    Drop the three P58 TEMPORARY pieces when their functions are C (the func_150342D0 wrap can stay: it calls the C).
- **P61 (after merging port 5d0322c: P51-P59): Conker drawn by the game's own code.** Full notes: P61.md.
  - Clean rebuild (nm_asm D5E90.c / D5E90_anim.c + .inc compile). Node and real-time Chrome (Metal, `heapwatch=1`,
    walking): 9 PASS, heap 0 errors, no RuntimeError. The P58 func_150342D0 terminator is removed (P57 C writes it; the
    evaluator scan now finds 3 face entries). Kept: TEMPORARY func_150A9B0C, func_1000480C.
  - **Drawn without p58pose** via func_1502C1D4 → func_1502BDC0 → func_1502CC64 → func_1502CFEC: 831 commands, 913
    vertices, **811 triangles**, 84 bone G_MTX (segment 3), 0 bad addresses. Needed two more **TEMPORARY PC** functions
    (`pc_overrides.c`): **func_150844AC** (vertex block words +0x28C/+0x290; the stub left them 0 and CFEC returned
    early) and **func_150A9E64** (arena f32 → Mtx in place; the stub left float bits). `P61_screenshot.png` (standing,
    bind pose), `p61/walk_30000ms.png` (walking), `p61/after_33000ms.png` (after a fall: checkpoint restart).
  - **Physical G_MTX address works:** `&D_800C42B8 & 0x1FFFFFFF` keeps the wasm mirror address (< 0x20000000) and
    resolves to the label; true physical (< 8 MB) values map to the RDRAM mirror as before.
  - **Bug in P56 converted C (crash, fixed port-side):** `D5E90_walls.inc` line 230 loads from the **literal 0x8009FAB0**
    (`at = 0x800A0000; LW(at + -1360)`, = D_8009FAB0) → *memory access out of bounds* in nmw_walls when the player
    moves. Port fix: `srcfix.py` STATIC (patched include copy). Port branch: use `HI/LO((u32) &D_8009FAB0)`.
  - **P59 at runtime:** func_1507D4F8 runs on a fall (lives left → `func_1501C710(2, 0, 0, 0, 0)`, checkpoint restart,
    the player reappears at x 348 z -2284 and walks on); func_1505D6F0 runs (no second record, no push);
    func_1508000C's sounds never fire on level 0x21 (UNVERIFIED); func_1507C170 returns at once (anim +0x28 = 0 until
    func_1505E0C4). No bug found in P59's C.
  - **Stubs:** model path func_15036FD8 (x2), func_1503BCAC, func_1503AB20, func_15030758, func_1502C9D8, func_1505E0C4;
    movement func_1505F298, func_15051558, func_1507F640, func_15017FA4, after respawn func_150ADE40, func_150D1D20.
- **P63 (after merging port-b 71183d1: P60): Conker animated by the game's own code.** Full notes: P63.md.
  - Clean rebuild: 725 vbe TUs, 1 link warning; P61's walls srcfix still applies. Node (idle 40 s, walk 32 s) and
    real-time Chrome (Metal, `heapwatch=1`, W held): 9 PASS, heap 0 errors, no RuntimeError.
  - **func_1505E0C4 needed its header lookup func_1502AF04 (asm stub → TEMPORARY PC):** anim +0x28 was 0, so nothing
    advanced. Now func_1505E650 → func_1505E0C4 → func_1507C170 → func_150A86B0 → func_1502CFEC animate Conker: idle
    0x0F, walk 0x01 / run 0x02, skid 0x21, fall 0x38, land 0x36, death 0xCF; walk → idle works. The pose looks right
    (no blend / header / block copy / endianness bug found). Open: the tail looks pale with dark triangles while
    running away from the camera (UNVERIFIED, compare with an emulator).
  - **func_1510E908 (slope solver, asm stub → TEMPORARY PC):** the stub left func_1510FDA0's dx / dz as stack garbage,
    so P60's func_15051558 slid Conker (0x28E, D_800CC69C = 1) off the flat start floor every frame. That was P61's
    "walk off the edge", and it blocked the walk / idle choice (+0x83).
  - **func_150A69E0 (asm stub → TEMPORARY PC):** the uninitialised count gave func_150A49D0 a garbage id list, a *memory
    access out of bounds* that depended on the stack layout (latent in every earlier build).
  - **End-of-animation callback runs** (P59 UNVERIFIED): called from func_1507C170 with the anim block (`?p63cb`).
  - Not reached: real slope slides, the turn-around 0xA5, the ice wobble sound; no idle variant in 13 s (func_1507F834
    is a stub).
  - Screens: `P63_screenshot.png` (idle, facing the camera), `p63/` (150 ms frame sequence) and **`p63/walk.gif`**.
  - **For the port branch:** convert func_1502AF04, func_1510E908, func_150A69E0 (then drop the PC versions), then
    func_1507F834 / func_1507F3B0, func_1505F298, and the model-path stubs func_15036FD8, func_1503BCAC, func_1503AB20,
    func_15030758, func_1502C9D8. The P61 items are still open (walls literal, func_150844AC, func_150A9E64).
- **P66 (after merging port P62 + port-b P64, ca891e7): overrides dropped, Conker jumps.** Full notes: P66.md.
  - Removed the PC func_150A9B0C, func_150A9E64, func_150844AC (`pc_overrides.c`), func_1000480C (`pc_mem.c`) and
    P61's walls srcfix (`srcfix.STATIC`; the regenerated D5E90_walls.inc uses HI / LO(&D_8009FAB0), the pattern no
    longer matched). Kept the P63 PC func_1502AF04, func_1510E908, func_150A69E0 (P65 converts them).
  - **The C func_1000480C needed osRomBase:** its CART_WORD KSEG1 loads already become `__port_io_read` (vbe.py P42
    rule; the cart domain 0xB0000000.. answers the BE ROM word, PI_STATUS idle), but D_80000308 was 0, so it read
    RDRAM 0xA0xxxxxx and the skeleton decoder crashed (*memory access out of bounds* in nmAnimDecode).
    `game_main.c` now sets `D_80000308 = 0xB0000000` (IPL3 value).
  - Clean rebuild (722 census TUs, 719 ok; 1 link warning). Node and real-time Chrome: 9 PASS, heap 0 errors, no
    RuntimeError, no heapwatch break.
  - **func_15085710 is the C body in the wasm** (not in asm_stubs.o; `?p66hud` logs its calls). P61's "asm stub" came
    from an old GFXDEMO log, not a current build.
  - **Jump (P64 C) works:** A → 0x32, vy 59, +0x28 80, A held -9.6 / call, release cuts (-14.88), apex ~210, land 0x36.
    Running jump 0x37; Z crouch 0x16 / 0x1B, Z + A long jump 0xEB. Forced low gravity (`?p66lowg`): 0xEB with
    +0x81 = 0x81, vy x 1.4 (P64 UNVERIFIED, now seen). Water / hang / glide / rides not reached (in_water stayed 0:
    the sp+0x8C slot is still UNVERIFIED). No bug found in the converted C.
  - **Idle variations play** (func_1507F834 / F3B0 C): after ~260 idle frames set 14 → 0x55, 0x57, 0x56, back to
    0x0F, then 0x9A, 0x9B, 0x04; 0x47 seen in Chrome.
  - Captures: `P66_screenshot.png` (rising), **`p66/jump.gif`**, `p66/jump_*.png`, `p66/chrome_jump.log`.
  - **Stubs for the port branches** (node 44 s, 91 distinct): model path func_15036FD8 (1144), func_1503BCAC /
    func_1503AB20 / func_15030758 (572), func_1503B840 / func_15039CC8 (15); movement func_1506BF5C (18),
    func_1507E7E4 (9), func_150453BC, func_1501D348, func_151BF8F0, func_1507342C; per frame func_1509A024 (1598),
    func_151236D0, func_1501B300, func_1512C77C, func_1512C080, func_151E7110, func_150A067C, func_10011624, ...
    (~45 at once per frame). Full ranked list: P66.md §3 / `port/build/boot_p66_runjump.log`.
- **P69 (after merging port P65 + port-b P67, 5d3f149): no TEMPORARY PC functions left; a respawn hang.** Full notes: P69.md.
  - Removed the P63 PC func_1502AF04, func_1510E908 and func_150A69E0 (`pc_overrides.c` now holds only
    func_100061F8 and func_150ADA20). Clean rebuild, 1 link warning (the old one).
  - Node runs (30 s idle; P66's run-jump script, 44 s) and real-time Chrome (Metal, `heapwatch=1`; B, walk, fall,
    respawn, idle): 9 PASS, heap 0 errors, no break. Animation as in P66.
  - **D_80084550 is mapped:** its 24 entries are function starts (P4 class F → wasm table). The runtime check
    `[p69] D_80084550 callback table: PASS` compares each word with `port_n64_to_wasm(ROM word)`. Stub entries [3] [5]
    [19] [21] are converted by the icall layer. Callback 5 (func_150322B8, stub) runs for the B attachment.
  - **Head aim (func_1503AB20 C) works** (mode 0, step 8, clamps), but its target D_800C43F0 stays (0, 0, 0): its
    writers func_15037CCC / func_15038910 are stubs. Floor probe func_150453BC: flags 07, height 0 on the start floor.
    func_1507E7E4 sets +6F / +71 / +72 as asked. No bug found in the P65 / P67 C that ran.
  - **Not reached (UNVERIFIED):** attack func_1505C7D8 (B plays 0x171-0x173 and attaches model 1 at joint 9, but only
    anim event 7, func_1506BEDC, arms +0xD0, and no animation used it); debris func_150D5F7C / func_150D71D4;
    func_150028BC.
  - **NEW BUG (open): walking after a checkpoint respawn hangs the game.**
    - Repro (node): `PADSCRIPT="15000:0:0:80; 16800:0:0:0; 19500:0:0:80; 30000:0:0:0" port/web/boot.sh 42`, rc 124.
    - A garbage node 0x0000243C reaches `D_800DD280[1][0]`. func_151670C0 → func_15169824 frees it twice, the free
      list cycles, and func_10003C6C spins (V8 profile 91%).
    - All called P65 / P67 C was wrapped out and the hang stayed. P63 walked here fine (and reached the 0x2C warp).
    - Suspects: P64's func_15017FA4 (zone boxes, same-TU only), other P62 / P64 C, P66's osRomBase. Bisect tools:
      `?p69free`, `?p69watch`, `?p69stub`, `?p69pc`.
  - **After the respawn the level renders:** a textured, lit wooden platform between tree trunks
    (`P69_screenshot.png`). Textures look smeared / blurry and the doorway is black. The 0x2C warp was not reached
    (hang).
  - **Stubs for the port branches** (node 44 s, 90 distinct):
    - look target func_15037CCC / func_15038910, func_150220CC, func_1503BCAC;
    - attachment callbacks func_150322B8 / func_1503216C / func_150D88E8 / func_150F5FD4;
    - anim events func_1506BF5C (sound), func_1506C32C, func_1506CE6C, func_1506EF5C;
    - per frame func_1509A024 (1758), func_151236D0, func_1501B300, func_1512C77C / func_1512C080, func_151E7110,
      func_150A067C, func_10011624, func_151143D4, func_15044D18, func_150617BC / func_15061B4C / func_1506160C;
    - DL passthru func_15041A9C, func_15180AF0, func_150314B4, func_150954E4.
- **P72 (c899e0c): the P69 respawn hang is fixed (port-side TEMPORARY guard).** Full notes: P72.md.
  - **Bisect** (scratch worktree, read-only ROM / ELF mounts, `timeout` in the container): P66 tip dce8fee bad;
    P66 with the six P64 files reverted good; one file at a time → only `game_eu_FF530.c` hangs. The first bad
    merge is ca891e7 (port-b P64), the commit f0437f9, the function **func_150D1D20** (view quad). P62 and P66's
    osRomBase are clean.
  - **Cause:** func_150D1D20's C matches the asm (P72.md §2). But its buffers D_800DC2E0 (Mtx) and
    D_800DC2B8[p][fb] (Vtx) are allocated by **func_15000AD0** (game_2DF70.c, asm stub; `sw` at 0x15000C70 /
    0x150012DC). So both are NULL in the port.
    - guMtxF2L and the vertex t-coordinate stores land in the null zone at 0x00..0xFF.
    - Other stubs' NULL "objects" are read from there, so a garbage node (0x243C / 0x2450) reached
      D_800DD280[1][0] and was freed twice.
  - **For the port branch:** no bug in the converted C. Converting func_15000AD0 is what removes the guard.
  - **Workaround:** `port/gfx/p72_checks.c` wraps func_150D1D20. A call with a NULL buffer returns gdl unchanged,
    like the old stub (marked TEMPORARY, logs once).
  - **Confirmed:**
    - The repro gives rc 0 (2416 frames, heap 0 errors, also with heapwatch).
    - P63's walk reaches `func_1501C710(1, 0x2C)` at frame 1077 and comes back at 1157.
    - Real-time Chrome walks through the respawn and the 0x2C round trip (frames 1793 / 1873) with no break.
    - Screenshot: `P72_screenshot.png`.
- **P75 (merge port P70 / P71 / P74 + checks): P72's TEMPORARY func_150D1D20 guard is dropped.** Full notes: P75.md.
  - Merge 0149c7e: one docs conflict (HANDOFF, merge_union). verify_all OK, NM links, protocheck 0 (898), clean port
    rebuild (vbe 727 ok, 1 old link warning).
  - `p72_checks.c` and `--wrap=func_150D1D20` are removed; func_15000AD0 (P74 C) allocates the buffers.
    - Node P72 repro: rc 0, 2272 frames, heap 0 errors.
    - Node walk: warp 0x2C at 1077, back at 1157.
    - Real-time Chrome: respawn 1741, warp 1813 / 1893, 0 heapwatch breaks.
    - func_150D1D20 writes real t coordinates and the Mtx.
  - **Sky (mode 2, level 0):** gradient blue → pale blue → green, quads ±1750 / z -1000. The texture is never loaded,
    because **func_150954E4** (DL passthru stub) is the loader. After the 0x2C round trip, func_150D1D20 is not called
    any more (gate unknown).
  - **Tail (P70) works** (wave phase, sway, reset; visible in Chrome, `P75_screenshot.png`). **Latent bug:**
    func_1503482C calls `func_1503BCAC()` without arguments, so the port passes 0 (`call @func_1503BCAC(i32 0)`).
    Fix: pass arg0. `p75/missing_args.txt` lists 18 such C call sites with missing arguments.
  - **Breakables (P74)** are not requested in play. With the DIAGNOSTIC request (kind 2 on record 0):
    - pieces fly, fall and bounce (vy x -0.5);
    - **the `unkF` branch is reached:** the timer ends, func_1503E550 sets state 0 and frees the pieces, and ED44 / EB1C
      are skipped;
    - no heap error.
  - Attachments (func_150302C8 C) now load. That puts func_150322B8 (callback 5) and func_150314B4 (DL) on the frame path.
  - Null zone: `null+0x14 = 0x400` (pre-existing) is first dirty at frame 1084 in level 0x2C. Candidate NULL producers:
    func_151ACBD4, func_150156F4, func_15195AA8, func_151BEE00.
  - **Blockers, in order:**
    1. func_150954E4;
    2. the arity fixes;
    3. func_151462C8 / 1514306C / 1513C060;
    4. func_15041A9C, func_15180AF0;
    5. func_150314B4 / func_150322B8;
    6. the look target func_15037CCC / func_15038910;
    7. the per-frame group (func_1509A024, game_14FF90.c, ...).

    Details: P75.md §3.
- **P78 (no merge; renderer LOD fixes + three findings).** Full notes: P78.md.
  - **Second-area blur is in the data, not the sampler.** The per-material dump (`?p78tex`) shows level textures of
    32x32 / 64x32 CI8 / CI4 with planar UVs at ~9.4 world units per texel. The near ground is drawn at 0.07-0.43
    texels per N64 pixel (2-15 px per texel), and some lip / wall pieces have UVs stretched 4x along one axis. TMEM
    decode, odd-row xor, tile shifts / ul, masks, TLUT were checked against the dump. `?p78split=1` shows the field is
    mip 0 with the old and the new LOD.
  - **Fixed in gfx_f3dex2.c (LOD, RDP semantics):**
    - uPixScale was inverted, so lod was ~4.8x too small and far LOD surfaces sampled 2+ levels too fine;
    - lod is now the per-component max, not the vector length;
    - "distant" now takes both texels from tile base + max (it was the stale tile after it);
    - levels go up to 4 (6 tiles bound; was 2).

    Same-frame screenshot: `P78_screenshot.png` (left old, right new).
  - **Null-zone writer found.** func_1501396C (game_40490.c) calls `D_80082ECC[idx]()` with no argument; on N64 a0
    still holds arg0. The callee func_15013D38 then does `arg0->unk16 |= 4` with arg0 = 0, which is null+0x14 =
    0x400. **Port-branch fix:** `void (*)(struct16 *)` + `func(arg0)` (check byte identity / NON_MATCHING). The P75
    stub candidates are only neighbours. No guard: it does not crash.
  - **func_150D1D20 gate.** func_15110420 calls `D_80089578[header +8]` (mode 2 = func_150D1D20) only when
    func_15110E44 ≠ 0. For level 0, that is 0 when player y < 1600 and the camera angle > 26. After the 0x2C round
    trip the angle is 27-47 (before: 13-18), so this is game logic, not a stub effect (`?p78sky`).
- **P79 (tooling only; arity scanner).** Full notes: P79.md.
  - **`tools/port/arity_scan.py`** compares the C call sites (pre-sigs IR in `port/build/ll`) with the EU ELF asm
    (objdump in the container, cached in `port/build/arity/`). It looks at a0..a3 / stack-arg liveness at each `jal` /
    `jalr`, the asm live-in of the callees, and the function-pointer tables read from the ELF data. It writes
    `docs/port/arity_scan.tsv`. The method and the columns are in the docstring.
  - Results on port-web at a09d170 (D1 / D2 / D3 / I are defined in P79.md):

    | kind | rows | severity > 0 |
    |---|---|---|
    | D1 | 21 | 12 |
    | D2 | 6 | 6 |
    | D3 | 8 | 8 |
    | I | 106 | 54 |

    The rows are ranked by severity, then by browser-log / reachability tier.
  - It finds the three known cases:
    - func_1501396C `D_80082ECC[idx]()` (rank 2);
    - func_1503482C `func_1503BCAC()` (rank 4);
    - func_15059C84 → func_15049350 1 < 9 (rank 17).

    All 18 sites of P75's `missing_args.txt` are D1 rows.
  - It is a may-analysis: check each row's asm (`asm_regs` column: W = written, E = caller's entry value) before
    fixing. Rerun it after every merge.
- **P81 (merge port P76 + checks).** Full notes: P81.md.
  - Merge e4162f2 had no conflicts.
    - verify_all OK; NM links; protocheck 0 (903).
    - Clean port rebuild: vbe 727 ok.
  - **Arity rescan:** 123 rows / 69 with severity > 0 (P79: 141 / 80).
    - All 18 rows of the P76-fixed callers are gone and there are no new rows.
    - D1 rows still open: func_15049350 (port-b), func_15084000 x2, func_1504715C, func_1600160C.
  - **Null zone clean:** no `[p78]` dirty write in node or Chrome, and the end scan shows 0 dirty words. The null+0x14 write is
    gone.
  - **Look:**
    - The target and the aim point D_800C43F0 are -99999 ("none"), no longer (0,0,0). No target is ever found, because
      **func_15004FE0** (the look point loader, game_32490.c, asm stub) leaves D_800C6A74 = 0.
    - The no-target hold / fade path runs. The slerp blend keeps the row lengths (0.5), orthogonality and the translation,
      and the rotation is smooth.
    - Head-turning toward targets is UNVERIFIED. func_15021E60 (fixed angles) is a stub.
  - **Attachments are drawn:**
    - Conker's prop on joint 9 (callback 5): 14-16 commands, 1 part DL, segment 3 Mtx; a second prop (callback 2) appears
      later.
    - **func_150322B8 (callback 5) stubbed** means the prop is never freed and stays drawn for the rest of the run. Its
      per-model tables are missing too.
    - One of three post-merge Chrome runs showed a large dark translucent overlay after the 0x2C round trip (37-45 s). It
      is not in the before run, after2 or noatt. Suspect: the stale callback-5 prop (not proven).
  - **Tail:** func_1503BCAC(arg0) gets arg0 = 0 for Conker and works.
  - **Respawn + 0x2C:**
    - node repro: 997 / 1173 / 1253;
    - Chrome: 1713 / 1785 / 1865;
    - heap 0 errors.
  - Same-frame screenshots: `p81/P81_before_after_{36000,41000}ms.png` (left pre-merge, right post-merge).
  - **Blockers, in order:**
    1. func_150954E4;
    2. func_151462C8 / 1514306C / 1513C060;
    3. func_15041A9C / func_15180AF0;
    4. func_150322B8;
    5. func_15004FE0 + func_15021E60;
    6. arity rows (top: func_1507C170 icall, func_1512B670 -> func_1512B2C4, func_1504A730 D_800863B4[]);
    7. the per-frame group (func_1509A024, func_150ADA68, game_14FF90.c).
- **Next for the browser build:**
  1. (P11) Convert **`func_15007B3C`** (level loader: DL buffers, first pad read) on the port
     branch, then `func_15019130` and `func_eu_1501C860`, which replace the temporary PC
     overrides. After that, rerun `port/web/rebuild.sh 10` and look for `[gfx] task` lines with
     real DLs. Then convert `func_1502AB04` (the asset-cache insert, 217 calls).
     MP3 ABI 7/8 is done (P14).
  2. The texture cache (`func_1510D66C`, `func_1510D3E0`); ROM-offset symbols are done (P9).
     A PC override of the asset-table walker `func_1502AC88` (#3 stub, format in P9.md) unblocks
     the asset loader. Audio: `func_10008180`, `func_10008F90`, `func_10009CBC` as PC overrides, then
     game audio tasks play through `port/audio` (MP3 commands: P14).
  3. Test the 352 MB memory on 32-bit Android and iOS Safari. Add a `GLOBAL_BASE=16MB` fallback
     only if needed.
  4. Conker lighting and per-bone matrices are done (P14). Still open: the material DLs in segment 8
     and the texture-bank segments for the viewer. The BG (level) light formula was checked against the ucode in
     P35b; the character ucode's formula is still unchecked.
  5. Still open from P4.md, "Known gaps":
     - address constants and `K0_TO_PHYS` in C;
     - bitfields;
     - `va_arg` doubles;
     - review of the pointer scan.
- **P84 (merge port-b e7e2e1a and port 8d63a7d + checks).** Full notes: P84.md.
  - Merges 4c07f94 (P68 / P73 / P77 / P82) and 1fb63b3 (P80).
    - Code conflicts in game_981E0.c, game_eu_AF2A0.c and difftest.py: both sides kept.
    - verify_all OK, NM links, protocheck 933 / 0. The difftest selftest was not run (no unicorn in conkerdev-web).
  - Arity: 112 rows / 56 with severity > 0 (P81: 123 / 69).
  - **Two new blockers, both with TEMPORARY port measures:**
    - func_151DDF6C (settings clamp, stub): language 0xFF made func_151E7110 DMA out of ROM and scan the null zone every frame. A PC copy is in pc_overrides.c.
    - func_1501CE34 (scene length, stub): the C func_1501E364 loops forever at the level 0 load. `__wrap_func_1501E364` guard in p84_checks.c.
  - With both measures the game runs (heap 0 errors, null zone clean), but level 0 is entered at frame ~950 and the view then freezes: no Conker, no respawn / 0x2C warp.
  - The sky shows as a solid green quad. Look points = 8, but there is no head target. The dark overlay was not seen in 3 walks (inconclusive).
  - **Next:** port branch converts func_1501CE34 (+ func_1501ECA4 / func_15020F6C) and func_151DDF6C, then remove both P84 TEMPORARY measures. Then redo the respawn / 0x2C / callback-5 / overlay checks.
- **P88 (merge port-b e3312cf P83 and port 6484e09 P85 + checks).** Full notes: P88.md.
  - Merges f6887a5 (HANDOFF union only) and 077e609 (no conflicts).
    - verify_all OK, NM links, protocheck 951 / 0, clean port rebuild.
  - **P84 measures dropped:** the PC func_151DDF6C (language 0, no out-of-ROM DMA) and the func_1501E364 length guard (scene length is now 250).
  - **New TEMPORARY guards (p84_checks.c, Makefile wraps):**
    - func_1501E888 (scene end) is a stub, so func_1501E364 looped at the scene end. The wrap writes state 0 and D_800C3638 = 0 (`?p88noguard`).
    - func_1501ECA4 (scene step) is a stub, so the C func_150225D0 / func_15021834 copied uninitialised D_800C3958 blocks into the player (y = -7.69e11). That caused an endless respawn loop. The func_1501D348 wrap restores the records it moved (`?p88noactor`).
  - **Playable again:** respawn, then the 250-frame scene, then walk, the 0x2C warp and back. Node and 2 Chrome walks; heap 0 errors.
    - The callback-5 prop is now removed.
    - No dark overlay in 3 walks.
    - Head target still -99999.
    - The sky gradient shows; the green part is the clamped tile (t 290..665 vs tile 256..511), so no renderer fix.
  - Null-zone writes (+0xB8 / +0xF8) by C func_1507342C from the NULL returned by the stub func_15073118.
  - Arity: 111 rows / 56 with severity > 0.
  - **Next:** port-b converts func_1501ECA4 + func_15020F6C + func_1501E888 (with func_15022C4C / func_15020430 / func_1501DB18 / func_1501D044) together. Then remove both P88 guards and recheck the respawn / scene. Then func_15073118 and func_151552F0.
- **P91 (merge port-b 431730a P87 and port 7127974 P86 + P89 + checks).** Full notes: P91.md.
  - Merges:
    - b69b918: HANDOFF union only.
    - f290c6b: game_981E0.c conflict, both sides kept. func_1507342C's local `struct127 *func_15073118` prototype was removed; its two uses cast the NM `u8 *` result.
    - difftest.py / selftest.sh merged automatically, with both fixes.
    - verify_all OK, NM links, protocheck 960 / 0 and then 969 / 0, clean port rebuild.
  - **Both P88 TEMPORARY guards are dropped** (`__wrap_func_1501E364`, `__wrap_func_1501D348` and their Makefile wraps):
    - The respawn scene ends by itself: state 1 -> 0 and the cutscene flag D_800C3638 1 -> 0, 250 frames later.
    - There is one death only; the player position stays sane.
    - Conker walks and the 0x2C warp goes there and back.
    - Seen in node (50 s and 80 s) and in 3 Chrome runs. Heap 0 errors, null zone 0 words, no `[p78]` line.
  - The respawn scene now plays with its real cutscene camera (Conker steps out of the wooden passage). A HUD counter sprite is drawn.
  - In Chrome, the audio reaches Web Audio (rms 0.024, peak 0.17). It was 0 in P88. Not judged by ear.
  - Head target: real once, in Chrome walk2 (frame 3841). Otherwise still -99999.
  - Arity: 113 rows / 57 with severity > 0. New row: func_151143D4 -> D_800DBEF4 callbacks, severity 2 (C passes 1 argument, the asm leaves a0..a2).
  - **Next:**
    - Scene path: func_1501FD34 (320 calls, "place", feeds func_1501ECA4's records), then func_1501E0C8 (63) and func_1512DAD0 (57, camera event 7).
    - Then the per-frame stubs at about 668 calls: func_15129220, func_150ADA68, func_15097E9C, func_15044D18, func_15097BA8, game_14FF90 x2, ... (P91.md section 6).
    - Check the func_151143D4 callback arity.
- **P97 (merge port b3219c2 + port-b 99d4923, checks).** Full notes: P97.md. func_151BF8F0 prototype fix; TEMPORARY guard on func_1501FD34 / func_1501FF10 (stub producer func_15020920, `?p97path=1`); top-down camera at 30-36 s from P93 / P95 (open); sound 0 since P94; sky t range = game math; arity 113 / 57.
- **P101 (investigation, no merge).** Full notes: P101.md. Fall = walking off level 0x21's 480 x 480 floor (its only collision, correct C query, no fix). Music blocker = asm stub func_150000B0 (level-start music: header song 0x35 on 0x2C, 0x60 on scene level 0). Census 52 stubs. Diagnostics ?p101col / ?p101mus.
