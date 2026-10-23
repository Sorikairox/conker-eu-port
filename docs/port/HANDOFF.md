# Port hand-off (branch `port`, worktree `~/conker-wt/port`)

Read `docs/port/PLAN.md` first: the phases, the browser-first target (wasm32/Emscripten) and the
risks. The decomp rules in `tools/eu_port/AGENT_BRIEF.md` and `HANDOFF.md` still apply: worktree
env, `verify_all.sh` before every commit, background jobs, the commit trailer.

```sh
cd ~/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"   # CONKER_ROOT, CONKERDEV=conkerdev-port
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
docker exec conkerdev-port python3 -c 'import unicorn'            # if missing: pip3 install --break-system-packages unicorn
```

## State (session P156, 2026-10-23). Details: `docs/port/sessions/P156.md`

- New hand C (NM): func_1507CD64 player_hit_reaction (func_1507D754 callee; 72 setups, mutants 55/55; returns s32 0
  because every prototype, also port-b's, says s32 and no caller reads it), func_150B8020 object_break_effects
  (func_1507D754 callee; 24 + 10 setups, mutants 57/58, 1 beyond the ARGMEM window, asm-checked), its callee
  func_150B87B0 debris_burst_spawn (6 parameters, mutants 18/18), coordinator item func_1510A98C
  vent_smoke_emitter_update (18 + 3 setups, mutants 40/42, 2 beyond the ARGMEM window, asm-checked).
- D_8008A3CC (func_151416E8 handler table): entries 10..17 are all C (list in P156.md); entries >= 18 are another table.
- difftest: opt-in `DIFFTEST_TUCMP_LEN=N` (bytes compared for a candidate TU-local object argument, default 32) and
  `DIFFTEST_OUTA_PERCALL=1` (OUTA words + k * 0x10000 on call k: different out-arrays per call); both forwarded by
  difftest.sh. New `docs/port/sessions/p156/isasm.py ROOT func...` (real C / ASM status; callees.py / romtab.py ASM
  marks come from the stale p98 asmonly list).
- Checks: verify_all OK (full ROM OK, after the last code edit), NM links, protocheck 0 (1151), selftest 62/62, progress_nm 5145/5915 (87.0%), C bytes 67.6%.

## Next steps (from P156)

1. func_1507D754 still blocked: this slot's func_151BAAC8 (715), func_150BC968 / func_150BC03C (461 / 587),
   func_150C04E0 (127), func_151C9740 (224), func_151CFFFC (374); port-b's func_15150D7C (via func_15136C3C ->
   func_1513A24C) and func_15154728 (via func_150E0DF0, func_151C9740); func_151D5AC4 / func_151D4684 (game_eu_201240).
2. func_15132BBC (game_eu_15FF50, 256): asm worker behind the C wrapper func_15132FBC (particle spawn used by
   func_150B8020 and many C callers).
3. Browser: hit reactions (func_1507CD64), vent smoke (func_1510A98C).
4. P138 / P141 leftovers (not started).

## State (session P154, 2026-10-23, port-web, runtime). Details: `docs/port/sessions/P154.md`

- **A new game reaches player control**: the Gregg cutscene (level 0x22 scene 2, 12441) ends at retrace **18485**.
  Conker is in the first room (dark round room, pillar, gargoyle, hanging squirrel tail). Node and Chrome agree to
  +-3 retraces. Runs: node 30101, Chrome 24401. No trap, heap 0, null zone only the known null+0x14.
- The cutscenes are timed: A / B / stick presses during them change nothing, so they need no input.
- Gameplay checks in Chrome:
  - Walking works, with the camera following.
  - Collision works: the round wall at radius ~470 and the pillar.
  - A jumps (held A hovers), and jumping collects the tail (starburst, lives "3").
  - The pause menu opens.
  - Audio runs.
- **B does nothing**: it calls the stub func_15064668 (B / context action), probably the first room's blocker.
- Fixed a `?p103boot` diagnostic trap: memok() in p103_boot.c accepted pointers beyond wasm memory. New knobs:
  `?p140len`, `?p88from` / `?p88to`; `?padf` takes up to 2048 entries.
- Scripts in docs/port/sessions/p154/: padgen.py (cutscene presses), padwalk.py (walk test), padtongue.py (tail
  pick-up + B / pause); newgame.sh takes env PADF / SHOTFROM / SHOTSTEP.

## Next steps (from P154)

1. Gameplay blockers, in order:
   - func_15064668 (game_eu_90F50, B action)
   - func_15064F50 (game_eu_90F50, called while walking, the stub returns 0)
   - func_10010154 / func_1000F568 / func_10010344 (init_EB00, sound-effect emitters)
   - func_1505528C (game_eu_78230, idle sit)
   - func_151EE0C4 (game_eu_216470, pause menu)
   - then the P152 list.
2. After func_15064668 is C: run padtongue.py (`NOSTART=1`) with B presses at the gargoyle / pillar to get past the
   first room. Also check the pause-menu text noise and the shadow streak / hatched floor patches (gfx).

## P153 (port-b) (session P153, 2026-10-23). Details: `docs/port/sessions/P153.md`

Branch `port-b` (from P150 53f4db6). Hand C (NM), difftest EQUIV + setups + mutants:
- func_15100B80 `object_burst_effect_spawn` (12E390, the effect of func_15102C3C; one frame struct keeps the
  original stack layout incl. the 0x68-byte emitter copy), func_150BA3B0 `water_splash_spawn` (E7BC0, port-b now
  owns game_eu_E7BC0.c; anti-tamper checksum left out), func_151A7240 `object_explosion_effects` (1D3420),
  func_151AE958 `path_ride_place` (1D9C00), func_150916B4 `hud_time_draw` (BC510), func_151B01B8
  `object_hit_flash_spawn` (1DDE10, returns 0 for int-declaring callers), func_151DC034 `glow_particle_spawn`
  (2062D0), func_151504B4 `path_particles_spawn` (17D3C0, returns 0).
- func_1513D4B8 returns its record under NM (game_169510.c + functions.h).
- func_151AC3F0 `debris_burst_spawn` verified (draft `p153/d_c3f0.c`) but not committed: game_eu_1EDA00.c:292
  declares it `s32` (protocheck); four other caller files say void. Fix that prototype, then insert.
- Checks: verify_all rc 0, NM build links, protocheck 0 (1170 bodies), selftest 62/62.
  progress_nm total 5164/5915 (87.3%), game 4633/5334, C bytes 68.1%, 751 asm-only.

## Next steps (from P153)

1. Coordinator additions (browser P152 stubs): func_151A9940 (game_eu_1D5710, 187 lines), func_1516AD20
   (game_eu_1984F0, 192), func_151506E8 (17D3C0, 178), func_1505528C (game_eu_78230, 529).
2. func_151AC3F0: after the 1EDA00 prototype fix, insert `p153/d_c3f0.c`.
3. Remaining asm-only with C callers in port-b files (asmlist); still-asm callees of func_151A7240: func_15154728
   (17D3C0), func_151A74B0, func_151D5AC4.
4. func_151AE694 hang: decide a port policy (see P153.md); level-data scan of trigger ids vs path objects open.

## State (session P152, 2026-10-23, port-web). Details: `docs/port/sessions/P152.md`

- Merged port-b 53f4db6 (P143 / P146 / P150, merge 7d3c2ff) and port d9785e0 (P148, merge 6d8dfff): only HANDOFF
  conflicted (merge_union, then section order fixed by hand). After each: verify OK, NM links, protocheck 0 (1167),
  float-int BUG 0, census 722 ok / 0 FAIL (clean), arity_scan 127 rows, m2c_sanity 226 rows (new width-high rows on
  hand C func_151018F8 / func_150EF90C: owners to check), stubcalls: the new frame-path C calls no stubs.
- **func_1513CFE4 list bounded**: ~1.6k calls per 250 retraces, flat (P149 stub: 2.9k -> 19.9k). Asm-stub calls in a
  new game 7.7k (P149 293k); no stub at all between ~4750 and 10721; 0 frame-DL stubs.
- **New game plays past the throne opening**: opening cutscene ends at 10728, next cutscenes at 10822 / 12448 (Conker
  wakes on the stone floor, Gregg the Reaper at 271 s). Particle sprite draw func_1513100C active there. Heap 0,
  traps 0, only the known null+0x14 (stub func_1514CFF0).
- Noev regressions clean: node 925 / 1249 / 1329; Chrome x2 1528 / 2304 / 2384. No water-drop splashes reached.
- New diagnostic `?p152hits=1` / PORT_P152HITS (p144_hits.c + 8 wraps).

## Next steps (from P152)

1. Blockers: func_1514CFF0 (port, in progress), func_151416E8 (end of opening), func_15058898 (title phase),
   func_100114D0, func_151A9940 / func_1516AD20 (post-opening cutscenes), func_eu_1501B640, func_1510A98C; level 0:
   func_1505528C, func_10010154 / func_1000F568.
2. Longer new-game run with `?padf` presses through the Gregg cutscene to first player control.
3. Check m2c_sanity width-high rows on func_151018F8 / func_150EF90C (port-b) and med rows on func_1517B270 (port).

## State (session P151, 2026-10-23). Details: `docs/port/sessions/P151.md`

- New hand C (NM): func_1514CFF0 character_handler_indices (new-game scene start; 192 setups, mutants 24/24),
  func_15058898 object_move_collide (49 setups, mutants 48/49 + 1 equivalent; calls port-b's func_150BA3B0 with its
  C signature `(u8 *, f32, f32, u8, s32)`), its callee func_1505DADC player_find_visible_target (mutants 26/28 + 2
  equivalent), func_1000A420 sound_pan_volume (492 setups, mutants 30/36 + 6 equivalent; init_A420 prototype now
  has f32 arg 3 and pointer outs), func_100114D0 sound_source_mix (mutants 14/14), func_1507D754 callees
  func_150AEB9C owner_spawn_children (anti-tamper checksum skipped under NM, as P127), func_1507515C
  player_find_owned_object, func_150E7F14 spawn_random_curve_object (func_1507CD64's asm callee), and coordinator
  P152 item func_151416E8 effect_message_dispatch. All EQUIV + mutants killed (equivalents listed in P151.md).
- game_83300 NM prototype of func_150ACEA0: args 7 / 8 are `void *`.
- Checks: verify_all OK (after the last code edit), NM links, protocheck 0 (1147), selftest 62/62, progress_nm
  5141/5915 (86.9%), C bytes 67.4%.

## Next steps (from P151)

1. Coordinator P152: func_1510A98C (game_eu_1379B0, 281 insns); func_1501B640 is in port-b's game_34F20 /
   game_eu_48B10 (port-b).
2. func_1507D754: remaining asm callees func_1507CD64 (now only C callees), func_151BAAC8, func_15136C3C (blocked by
   port-b's func_15150D7C via func_1513A24C), func_150B8020 (+ func_150B87B0), func_150BC968 / func_150BC03C,
   func_150E0DF0 (+ func_151D5AC4 / func_151D4684, port-b's func_15154728), port-b's func_151A7240.
3. Browser: check the null+0x14 = 0x400 write at the new-game scene start is gone (func_1514CFF0 now real).
4. P138 / P141 leftovers.
## P150 (port-b) (session P150, 2026-10-23). Details: `docs/port/sessions/P150.md`

Branch `port-b` (from P146 b8f1ce7); merged port 37085b5 (merge commit 1457344, only HANDOFF.md conflicted).

- func_1513D524 `_void_proto` hacks removed (game_169510.c, game_eu_1772D0.c).
- Hand C (NM), difftest EQUIV + mutants: func_1508154C `object_ray_hit_model` (AE930; func_15081A90 model hits now
  C), func_15153BA4 `particle_burst_spawn` (17D3C0, replaces the batch m2c body), func_15084814
  `object_model_refs_release` (AF2A0), func_15102C3C `object_effect_start` (12E390; callee func_15100B80 still asm),
  func_151AE694 `path_try_attach` (1D9C00), func_151B09BC `object_link_effect_spawn` (1DDE10); func_1510BA9C (138E00,
  C since P13) verified and now counted (dead nested `#ifndef NON_MATCHING` removed).
- Checks: verify_all rc 0, NM build links, protocheck 0 (1162 bodies), selftest 62/62.
  progress_nm total 5156/5915 (87.2%), game 4625/5334, C bytes 67.8%, 759 asm-only.
- Port-b asm lister: `docs/port/sessions/p150/asmlist.py` (port-b files; run progress_nm --list >
  port_work/p150/asmonly.txt first). 91 asm-only left in port-b files, 42 with C calls.

## Next steps (from P150)

1. Next smallest port-b asm with C callers (asmlist): func_151AE958 (122, 1D9C00), func_150916B4 (123, BC510),
   func_151B01B8 (128, 1DDE10), func_151DC034 (139, 2062D0), func_151504B4 (141, 17D3C0), func_151AC3F0 (142, 12 calls).
2. func_15100B80 (12E390, 706 lines) so func_15102C3C's effects show.
3. Browser: model ray hits, burst particles, path attach, linked effects (P150.md UNVERIFIED).

## State (session P149, 2026-10-23, port-web). Details: `docs/port/sessions/P149.md`

- Merged port 37085b5 (P141 / P145): code conflicts comment-only (functions.h, game_16DC80.c, game_eu_20B730.c), HANDOFF
  rebuilt (merge_union mixed blocks). verify OK, NM links, protocheck 0 (1140), float-int BUG 0, census 722 ok / 0 FAIL
  (clean), arity_scan 121 rows (new func_1513095C rows severity 0), m2c_sanity 214 rows.
- **Frame-based input**: `?padf=F:BTN:X:Y,...` / PORT_PADF (pc_pif.c) sets pad 0 from VI retrace F. New-game STARTs
  3386 / 4458 (p131 + p149 newgame.sh, env F1 / F2), Chrome noev walk 1380-1780 + 2230-2630 (p149/chrome.sh),
  p72shots.sh maps WALK_MS / HOLD_MS to retraces (WALLCLOCK=1 = old), node walk 775-1095 + 1160-1550 (p149/nb.sh).
  Runs are now reproducible in frames (scene start 4560 / 4559, fade-in 6242 / 6241).
- C particles (func_1513095C) bounded (120-426 calls per 250 retraces in the opening, then 0; P140 stub kept rising):
  they die now. Framebuffer pass func_15160310 runs every game frame, no handler called (empty list) -> no visual
  change. Handler 14 / 17 stubs not hit. Cards + throne fine at 50 Hz. Diagnostic `?p149hits=1`.
- Regressions clean: node noev 925 / 1249 / 1329; Chrome walks 1527 / 2303 / 2383 and 1530; heap 0, null 0, traps 0.

## Next steps (from P149)

1. Blockers: func_1513CFE4 + its asm handlers (281k calls, list grows), func_1513100C (frame DL in the throne scene),
   func_150A7EE0 / func_15058898 (mode 0), func_1517B270, func_1514CFF0, then func_151928C8 / func_151A2F10.
2. Use `?padf` for all new scripted runs (screenshot times are still wall clock: ~50 retraces/s after ~1.4 s boot).
3. Lens warp func_151CB6C0 still unexercised at runtime: find a level with a 0x34-list effect.
## State (session P148, 2026-10-23). Details: `docs/port/sessions/P148.md`

- New hand C (NM): func_151928C8 water_drop_splash_update (func_1513095C update handler 14; mutants 16/16),
  func_1513100C particle_draw_sprite (frame DL path, 37 setups, mutants 29/31 + 2 equivalent), func_1517B270
  player_morph_blend (27 setups, mutants 28/29 + 1 equivalent; game_eu_595D0 prototype now s32), func_150A7EE0
  matrix_transform_point_w (hand-asm trampoline; new whole harness `tools/port/difftest/nmasm_7ee0.py`, 2000 trials
  0 diffs), func_1501A764 world_to_screen (mutants 10/10).
- func_1513095C tables: only update handler 17 func_151A2F10 (port-b) is still asm; death table all C.
- New helpers `docs/port/sessions/p148/romtab.py` (EU table dump with ASM marks), `callees.py` (jal targets with
  decoded keys).
- Checks: verify_all OK, NM links, protocheck 0 (1138), selftest 62/62, progress_nm 5132/5915 (86.8%), bytes 67.1%.

## Next steps (from P148)

1. Coordinator P149 census items still open: func_1514CFF0 (game_eu_17A800, 583 lines, pointer producer),
   func_15058898 (game_83300; asm callees func_150BA3B0 port-b, func_1505DADC), func_100114D0 (init_EB00; asm callee
   func_1000A420 first).
2. func_1507D754 (game_A9D90): 10 asm callees listed in P148.md section 4 (func_151A7240 is port-b's).
3. P138 / P141 leftovers (func_151E3AE4 ARGMEM 0:52 lists, func_151DFD0C f1 setups, func_151E19AC, func_151E4B40 gaps).

## P146 (port-b) (session P146, 2026-10-23). Details: `docs/port/sessions/P146.md`

Branch `port-b` (from P143 3005439); the orchestrator merges it into `port`.

- func_1513CFE4 `effect3d_update` (game_169510.c, ~492k calls/run) inserted from the P143 draft; its last asm
  handlers are C: func_150FDA94 `bound_cloud_update` (12A7C0), func_151018F8 `laser_sight_update` (12E390),
  func_150EF90C `tether_beam_update` (11CB90) with func_15081A90 `ray_cast_world` + func_15082020
  `ray_hit_object_bounds` (AF2A0). Re-run of cfe4 setups after insertion: all EQUIV.
- Coordinator request: func_151A2F10 `particle_timed_event_update` (1CE7D0), handler 17 of P145's func_1513095C.
- All hand C (NM), difftest EQUIV + mutants (survivors equivalent or listed UNVERIFIED in P146.md).
- func_15081A90 keeps `s32` return (callers' NM prototypes; the asm returns nothing, C returns 0). It still calls
  asm func_1508154C (game_eu_AE930.c, not owned) when boundsOnly == 0 (callers 90F50, 1EFE10).
- Checks: verify_all rc 0, NM build links rc 0, protocheck 5 lines = 4 known pairs + game_eu_11A2B0.c:9.
  progress_nm total 5115/5915 (86.5%), game 4585/5334, C bytes 65.6%, 800 asm-only.
- Not done: func_15153BA4 (17D3C0), dropping the `func_1513D524 ..._void_proto` #define hack (169510, 1772D0).

## Next steps (from P146)

1. func_1508154C (AE930, model ray test) so func_15081A90 model hits work; then func_15153BA4 (17D3C0).
2. Drop the func_1513D524 #define hack if this worktree's functions.h returns the pointer under NON_MATCHING.
3. Browser: object-bound clouds, aim laser, beam tethers, timed-event particles, all func_1513CFE4 effects.

## State (session P145, 2026-10-23). Details: `docs/port/sessions/P145.md`

- Scans on this tree: protoasm_check 0 real rows (RETNONE 14 info), floatint_scan BUG 0 / REVIEW 4 (known);
  arity_scan / m2c_sanity need port-web's `port/build/ll` (run them there after the next merge).
- New lister `docs/port/sessions/p145/asmlist.py` (asm-only functions in this slot's files with C callers).
- New hand C (NM): func_15160310 framebuffer_effects_apply (= US func_1515FDA0; init_49E0 aliases the name under NM),
  func_151CB6C0 fb_lens_warp_draw, func_1513095C particle_update (frame path), its handlers func_151A4DEC
  spark_burst_update and func_150C1698 pool_slot_release. All EQUIV on setups + mutants killed (equivalents listed).
- func_1513095C update handlers 14 func_151928C8 (game_eu_1BF960, this slot) and 17 func_151A2F10 (game_eu_1CE7D0,
  port-b) are still asm: those particles die on their first tick in the port.
- Checks: verify_all OK, NM links, protocheck 0 (1133), selftest 62/62, progress_nm 5127/5915 (86.7%), bytes 66.8%.

## Next steps (from P145)

1. func_151928C8 (water splash handler, 137 lines); ask port-b for func_151A2F10.
2. func_1513100C (game_eu_15E000, frame DL, 568 lines), func_1517B270 (game_eu_1A8930, 512 lines).
3. func_1507D754 (game_A9D90) after its 13 asm callees; P138 / P141 leftovers.

## P143 (port-b) (session P143, 2026-10-23). Details: `docs/port/sessions/P143.md`

Branch `port-b` (from P142 a4cc21e); the orchestrator merges it into `port`.

- P142's func_1513CFE4 handler list was wrong: D_8008A1B0 has 3 slots, D_8008A1BC after it is the +0x73 draw
  table. Real asm handlers were 8; P143 converted 5 (func_150BA904, func_1518A604, func_151B173C, func_15191A90,
  func_151A6BB0) plus func_151DAB58 `splash_ring_spawn` (2062D0, asm callee of two of them) and the three draw-table
  quad builders func_1513E83C / func_1513EE14 / func_15140190 (169510). All hand C (NM), difftest EQUIV + mutants.
- func_1513CFE4: verified draft `docs/port/sessions/p143/d_cfe4.c` (EQUIV, mutants 28/28), not inserted: still
  asm handlers func_150EF90C (11CB90, + asm callee func_15081A90 in AF2A0), func_150FDA94 (12A7C0),
  func_151018F8 (12E390).
- Files taken: game_eu_E7BC0, game_eu_1B7D70, game_eu_1DDE10, game_eu_1BE5C0, game_eu_1D3420, game_2062D0.
- Checks: verify_all rc 0, NM build links rc 0, protocheck 5 lines = 4 known pairs + game_eu_11A2B0.c:9.
  progress_nm total 5108/5915 (86.4%), game 4578/5334, C bytes 65.3%, 807 asm-only.

## Next steps (from P143)

1. func_150FDA94, func_151018F8, func_150EF90C (+ func_15081A90), then insert `p143/d_cfe4.c` (+ its setups for a
   final re-run) into game_169510.c.
2. Browser: sprite quads, splash rings, falling debris / drops, bubble emitters, bone-attached effects.
3. func_15153BA4 (17D3C0) for func_151BF678's flash particle (not started).

## State (session P147, 2026-10-23, port-web). Details: `docs/port/sessions/P147.md`

- **Browser VI pacing is now 50 Hz for PAL** (pc_sched.c fixed-timestep accumulator on performance.now; present on
  rAF only after a retrace; caps: 250 ms per tick, 4 retraces / 33 ms per tick, backlog > 2 periods dropped; pause
  resets). Node / `?det=1` / `?vi60=1` keep one retrace per callback; `?det` clock 1/50 s per retrace.
- Audio: AI_LEN reports ring level minus 3072 frames (`?ailat`). 130 s Chrome run: **50.009 retraces per audio second**,
  ring 2.1k..5.3k frames (stable), 0 underrun, 0 dropped (old 60 Hz pacing: ring filled to 6 s and dropped samples).
  Diagnostic `?p147pace=1`.
- Presented rows follow the VI mode (`?p147vi=1` logs it): PAL rows 1..214.7 of the 292 x 216 fb (no more row-216 line);
  `?p147vifull=1` = old. Logo-end title image at y 226..278 is outside the scissor (0..216) on the N64 too.
- New game: 1682 frames black = ~34 s to the fade-in (was 28 s). At 50 Hz the menu STARTs need E1=69500 E2=91000.
- Regressions clean: node noev (death 925, 0x2C 1285, 0 1365), Chrome walk (1531 / 2303 / 2383), heap 0 / null 0 / traps 0.
- New knobs: `?dltracef=F` (trace first gfx task at/after retrace F), `?timer=N` (N ms setTimeout loop).

## Next steps (from P147)

1. Conversion blockers as P144 (func_1513CFE4 + handlers, func_1514CFF0, frame-DL stubs, func_15153BA4).
2. Logo-end title image: what sets its y 226 (scene event data D_80091BA8 or a stubbed producer).
3. Scripts driven by wall time (walks, newgame presses) now land on different frames: retime them for 50 Hz.

## State (session P144, 2026-10-23, port-web). Details: `docs/port/sessions/P144.md`

- Merged port-b a4cc21e (P136 / P139 / P142): only HANDOFF conflicted (merge_union); game_eu_11A2B0.c func_151432BC
  prototype -> s32. verify OK, NM links, protocheck 0 (1130), float-int BUG 0, census 722 ok / 0 FAIL (clean),
  m2c_sanity 236 rows / 41 high (+3 low/med port-b rows).
- **New-game title cards now draw** (P142 func_15169FB8 / func_150966AC): "Nintendo presents", "A Rareware game",
  "Starring Conker & Berri", then the fade-in to the throne cutscene.
- **Logo-end iris** (func_15180AF0 -> func_1518010C scope lens) was a black screen: renderer ignored CVG_X_ALPHA +
  CLR_ON_CVG without FORCE_BL; now low-alpha texels are discarded (`?p144nocvgx=1` = old). Scope lens verified.
- Browser runs ~60 VI frames/s; the EU ROM is PAL (50): game and cutscenes ~20 % fast. Not changed.
- New knob `?p144hits=1` / PORT_P144HITS: call counts of 17 P136-P142 functions (cross-TU --wrap).
- Regressions clean: node noev (death 953, 0x2C 1321, 0 1401), 2 Chrome walks, heap 0 / null 0 / traps 0.

## Next steps (from P144)

1. Runtime: pace VI retraces at 50 Hz for osTvType PAL (pc_sched / main loop) and check audio pacing with it.
2. Conversion: func_1513CFE4 (+ its asm handlers, producers first), func_1514CFF0 (null+0x14 write at new-game
   scene start); frame-DL stubs func_1513095C / func_1513100C, func_151408A4, func_1517B270, func_1515FDA0;
   func_15153BA4.
3. Check the logo-end title image (5/0x5C b5 0, drawn at y 226..278) and the y 216 row under the iris fills.

## State (session P140, 2026-10-23, port-web, diagnostic). Details: `docs/port/sessions/P140.md`

- Node noev "stall" (P137) is a log artefact: without PORT_P61CHECK no frame-bearing lines after the padscript ends;
  scheduler frames / gfx DLs match the P131-knob run (4482 / 1120 vs 4486 / 1121), same level switches. p140/sum.py
  now prints a `progress:` line. 40dc311 not implicated.
- Opening black (level 0x18 scene 1) is scene-scripted: fade-in event 5/1 at t 2040 (60ths) = frame 1700 PAL; the port
  starts it at 1682 + 17 fade frames, so timing is right. During the black part the N64 shows 3 title cards (5/0x5C ->
  func_150F59A0 -> image effect 0x5E) drawn by **asm stub func_15169FB8** (called every game frame only in that
  stretch, `?p140win`); it needs func_150966AC (asm) too.
- Renderer: offscreen images no longer square-only (FBO w x 256, rows from the scissor set while bound; shadow pass
  64x63); 8-bit images keep the red byte (RDP behaviour). Chrome noev walk clean, shadows unchanged.
- New knob `?p140win=F` / PORT_P140WIN: per-stub call counts in 250-frame windows from frame F.

## Next steps (from P140)

1. Conversion slot: func_15169FB8 + func_150966AC (image-effect draw; opening title cards, title screen).
2. Frame-DL stubs func_1513095C / func_1513100C, func_151432BC, func_151408A4, func_1518010C; func_1513CFE4.
3. After (1): check the cards draw above the fade (fade level 255 during the cards).

## State (session P137, 2026-10-23, port-web). Details: `docs/port/sessions/P137.md`

- Merged port-b 48f7258 (P130/P133), port caf7013 (P132), port 40dc311 (P134). Only HANDOFF conflicts; game_16DC80.c
  func_1513D524 hack removed; game_eu_20B730.c D_800E0FB8 unified to `u8 **` (P134's `s32 *` broke the NM build).
  verify OK, NM links, protocheck 0 (1102), float-int BUG 0, arity 118, census 722 ok / 0 FAIL, m2c_sanity 234 / 41 high.
- New game: no trap; level 0x18 opening is black (fade 255) for ~1680 frames, then the throne cutscene draws (5-8k tris).
- Shadows: renderer now supports offscreen colour images (FBO + RDRAM write-back); before that the P130 shadow pass
  painted the screen white. Conker has a shadow on level 0 / 0x2C. P113 guard removed (log-only STALE check).
- Open: node noev stops advancing game frames at ~1730 after the 40dc311 merge (Chrome fine).

## Next steps (from P137)

1. Node noev stall after 40dc311 (rerun with P131 knobs, bisect).
2. Check the opening's fade-in event time vs scene data; then mode-0 stubs func_151408A4, func_151432BC.
3. Frame-DL stubs func_1513100C / func_1513095C / func_15169FB8 / func_1518010C; func_1513CFE4.

## State (session P135, 2026-10-23, port-web, tooling). Details: `docs/port/sessions/P135.md`

- `port/tools/m2c_sanity.py` gains per-base kinds `pscale` / `pindex` (typed pointer LOADED from memory: pointer
  variable, pointer-table entry, argument, pointer field, `&SYM[i]` in an m2c temp local; IR GEP scale S*K vs the
  multipliers the asm `addu`s onto that same base) and a cheap `spaddr` (P124 scattered stack structs, low).
  Tracker fixes: jal delay slots run before the call, pointer spills to sp slots followed. `--stats`; `--func` no
  longer overwrites the TSV.
- Validation: func_15022440 `pscale high` at game_eu_4A070.c:2447 (P131's trap). New TRUE bug, frame path:
  **func_15036BB4 game_eu_64070.c:75** `temp_s0 + (arg2 * 4)` on struct127 * (scale 3248; asm `arg2*4 + s0`, lw 0x304).
- TSV 220 rows (213 before): pscale high 2 / low 1, pindex low 3, spaddr low 2; high functions 40 (+2).
  FP: high tier 0/2, low tier 6/6 FP (hand-asm bodies / separate out-params, downgraded on purpose).

## Next steps (from P135)

1. Port slot: fix game_eu_64070.c:75 (func_15036BB4) with game_eu_4A070.c:2447: `(u8 *) base + x * K`.
2. Tool: embedded arrays (`p->arr[i]`, multi-index GEPs) as candidates; spaddr needs the callee's read size.

## State (session P131, 2026-10-23, port-web). Details: `docs/port/sessions/P131.md`

- Merged port 40d3eaa (P127) as dc562bf and port-b c2778a9 (P125/P128/P129) as b03d7fa; only HANDOFF conflicts
  (merge_union.py, section order checked). Resolution: functions.h declares func_1513D524 `struct210 *` under
  NON_MATCHING (void in #else), the `_void_proto` hack in game_169510.c / game_eu_1772D0.c is gone; pc_gu.c's duplicate
  func_150A7B80 removed (link warning gone). verify_all OK, NM links, protocheck 0 (1081), float-int BUG 0, arity 117,
  m2c_sanity 213 rows / 38 high functions, census 722 ok / 0 FAIL.
- func_151DE100 is a plain function in the port (no data stub, n64mem F-data 0, D_8009018C[0] relocated): P126's mode-0
  trap at 4487 is gone (node: ~940 mode-0 frames, no trap).
- New game: menu -> START -> START reaches mode 0 / level 0x18 / scene 1 (cutscene). Chrome traps 6/6 on that frame in
  func_1510D3E0 via func_15022440 -> func_15082E44 -> func_15083568 (setup list 178 -> asset (9, 189) one-list model
  through the multi-list loader). Cause: **game_eu_4A070.c:2447** `(sp38 * 0x30) + D_800D20FC` on a `struct258 *`
  (size 0x10) = stride 0x300; asm uses bytes. Fix `(u8 *) D_800D20FC + sp38 * 0x30` (port slot). Node survives by
  luck but draws 0 triangles in mode 0 (opening cutscene black).
- Cartridge check (func_151DE100 quit -> no): osPiStartDma = rom_copy of real ROM bytes; ROM 0xF80 gives the expected
  0x3050A14A / 0xBCFCF506, so the random DMA path is not taken (not reached at runtime).
- P113 guard kept (mode 0 not observable yet; noguard run: only the harmless 2133 case). noev regression clean (node +
  2 Chrome walks, heap 0, traps 0).
- DIAGNOSTIC `?p131mdl=1|FRAME` (p103_boot.c wraps of func_1510D3E0 / func_1502B6BC / func_15082E44 / func_1502B8E0).

## Next steps (from P131)

1. Port slot: fix func_15022440's entry stride (game_eu_4A070.c:2447) and audit other struct258 / D_800D20FC
   arithmetic (game_eu_44010.c:46). Then re-run `docs/port/sessions/p131/newgame.sh DIR "&p131mdl=4300"`.
2. Opening cutscene draws nothing: stub func_150F1F80 (game_eu_11F790, mode-0 per-frame), then frame-DL stubs
   func_150A6D40 / func_1510E6A0 / func_15169FB8 / func_1517FF64 / func_1518010C.
3. func_151407D0 (game_16DC80, emitters of P127's func_150113E0), func_1515AEE4 (game_eu_186A80).
4. P113 guard: remove after a mode-0 run past the scene start without NO GUARD lines.
5. Node new-game runs: START timing is unreliable in node (2 of 3 runs never left the menu); prefer Chrome or add a
   third START.

## State (session P126, 2026-10-23, port-web). Details: `docs/port/sessions/P126.md`

- Merged port 9940126 (P124) as 7738b0a and port-b 422e5d3 (P119 + P122) as dd693f9. Code conflicts were in
  game_981E0.c (comments / redundant prototype), game_eu_AF2A0.c (port-b = port's file), difftest.py (comment) and
  selftest.sh (duplicate cases). After each merge: verify_all OK, NM link, protocheck 0 (1038 / 1060), float-int BUG 0,
  arity 117 rows unchanged, census 722 ok / 0 FAIL (clean). m2c_sanity 207 rows, high 44 / 38 functions (new high:
  func_15181A6C, func_1512EE50). HANDOFF union mis-nested port-b's sections into P123's: repaired by hand.
- **The title menu fades in the game's way** (handler C func_15029EA8 C, P124): 2140 `func_1517F3B0(41 frames, dir 0)`
  from func_15029EA8, fade 0 from 2285, 6626 triangles. **The `?p123fadeev` wrap is removed.**
- **START works**: the first press zooms the carousel to GAME1 / NEW GAME. The second press sets mode 7 (4393), then
  mode 0 (4485), then level 0x18 scene 1, then **traps at 4487**: `table index is out of bounds` in func_151E5928
  `D_8009018C[0]()`. That is the raw 0x151DE100 that P103 predicted.
- The frame-1985 trap is gone: 6 of 6 events-on node boots ran clean. `?p110noev=1`: node + 2 Chrome walks clean
  (heap 0, null 0). P122 shadows and waves are not visible: the shadow draw functions func_15186A9C / func_15187954 are
  still stubs.
- P113 guard: the 3053 condition no longer occurs, and 2133 is harmless without the guard. The guard is not needed in
  these runs. It is kept until a mode-0 run has been checked without it.

## Next steps (from P126)

1. Conversion slot, as one unit: **func_151DE100 (mode 0) to C** + a `#ifdef PORT` skip of the func_151E86A4
   checksum + drop the func_151DE100 data stub (data_stubs.c / vbe.py note) so that D_8009018C[0] is relocated.
2. Then the level 0x18 new-game stubs: func_150113E0 (game_3E890), func_1515AEE4 (game_eu_186A80), func_10024190
   (init_eu_23CC0, a mode-0 callee). Run the stub census again with `docs/port/sessions/p126/menu.sh`.
3. Shadow draw func_15186A9C / func_15187954 (game_eu_1B1ED0). Menu DL stubs func_1510E004 / func_1510E6A0.
4. port-web: after item 1, run the new game with `?p113noguard=1`, then drop the guard. Remove the pc_gu.c copy of
   func_150A7B80 (now game C).

## State (session P123, 2026-10-23, port-web). Details: `docs/port/sessions/P123.md`

- **Menu black = screen fade stuck at 0xFF.** The C menu handler (P117) now starts level 0x1D scene 1. Its scene start
  func_1501DB18 sets black (t = 0 event `5/0x01 w6 1`). The fade-in is the same event in **handler C func_15029EA8**
  (game_eu_51190.c, asm stub), so func_1517F51C(0) stays 1 and func_15019464 / func_150195A0 skip every world draw
  (114-command DLs, 0 triangles). The renderer is fine.
- TEST ONLY `?p123fadeev=1` (5/1 `b4 == 0` branch of func_15029EA8 from the asm): the menu room is drawn (3119
  triangles, Chrome shot). Other new flags: `?p123tri=N`, `?p123fade=1`, `?p123noscene=1`.
- Merged port 0c14e92 (P120, carousel func_151E73C8 C, func_151EE704 OR dropped) as b00bd2c on coordinator request:
  verify_all OK, NM link, protocheck 0 (1033), census 0 FAIL (clean). The carousel alone does not fix the black menu.
  `?p121spr` is now obsolete: don't pass it.
- Camera retarget (3053): no scene event retargets +0x3D4 (type 3 only switches the scene camera track; 1D/1's final
  3/0 is a no-op). +0x3D4 comes only from the camera init func_1512868C / func_150054C4 (slot D_800CC2D0[+0x23D]
  +0x31C). The removed object is slot 0 itself. P113 guard stays.

## Next steps (from P123)

1. Conversion slot: **func_15029EA8 to C** (handler C; type 5 id 1 = screen fade, types 6 / 0xA = sounds). Then drop the
   p123fadeev wrap. Also func_1510AEB0 (P121).
2. port-web: log func_1512868C / func_150054C4 / func_15097188 after 2133 and 3053 (no guard) to find the camera
   re-init that the port misses.
## State (session P145, 2026-10-23). Details: `docs/port/sessions/P145.md`

- Scans on this tree: protoasm_check 0 real rows (RETNONE 14 info), floatint_scan BUG 0 / REVIEW 4 (known);
  arity_scan / m2c_sanity need port-web's `port/build/ll` (run them there after the next merge).
- New lister `docs/port/sessions/p145/asmlist.py` (asm-only functions in this slot's files with C callers).
- New hand C (NM): func_15160310 framebuffer_effects_apply (= US func_1515FDA0; init_49E0 aliases the name under NM),
  func_151CB6C0 fb_lens_warp_draw, func_1513095C particle_update (frame path), its handlers func_151A4DEC
  spark_burst_update and func_150C1698 pool_slot_release. All EQUIV on setups + mutants killed (equivalents listed).
- func_1513095C update handlers 14 func_151928C8 (game_eu_1BF960, this slot) and 17 func_151A2F10 (game_eu_1CE7D0,
  port-b) are still asm: those particles die on their first tick in the port.
- Checks: verify_all OK, NM links, protocheck 0 (1133), selftest 62/62, progress_nm 5127/5915 (86.7%), bytes 66.8%.

## Next steps (from P145)

1. func_151928C8 (water splash handler, 137 lines); ask port-b for func_151A2F10.
2. func_1513100C (game_eu_15E000, frame DL, 568 lines), func_1517B270 (game_eu_1A8930, 512 lines).
3. func_1507D754 (game_A9D90) after its 13 asm callees; P138 / P141 leftovers.

## State (session P141, 2026-10-23). Details: `docs/port/sessions/P141.md`

- Merged port-b 9c9369d (P115-P139) as 904c686: HANDOFF conflict only (merge_union); functions.h func_1513D524
  `struct210 *` under NM (game_16DC80 hack removed), game_eu_11A2B0 func_151432BC s32, game_eu_20B730:460
  func_1501D348 void.
- New hand C (NM): func_151408A4 particle_glow_update (game_16DC80, 38 setups, mutants 62/62), func_151E4B40
  menu_level_start_page (67 setups, mutants 52/54 + 1 equivalent), func_151E1EDC menu_team_select_page (74 setups,
  mutants 51/59, 8 equivalent; random garbage layouts with > 4 teams diverge, unreachable).
- Checks: verify_all OK, NM links, protocheck 0 (1128), selftest 62/62, progress_nm 5122/5915 (86.6%) combined, bytes 66.7%.

## Next steps (from P141)

1. func_151E4B40: 2 coverage-gap mutants (fade exactly 0x100; state-1 queue loop with D_800E1030[i] != i).
2. P138 re-runs: func_151E3AE4 mutant lists, func_151DFD0C terminating f1 setups, func_151E19AC mutants.
3. arity_scan / m2c_sanity after the merge; port-b to drop the func_1513D524_void_proto defines (game_169510, game_eu_1772D0).

## State (session P138, 2026-10-23). Details: `docs/port/sessions/P138.md`

- func_151E3AE4 real bug fixed: in the asm frame y[] (sp+0x90) has only 14 slots and x[] follows it, so with 13+ items
  y[14..] overwrites x[0..]; now one `points[14 + 32]` buffer. 68 errored setups EQUIV with ARGMEM 15049AD0=0:52
  (old 20 DIFFER); aliasing mutant killed. Use ARGMEM 0:52, not 0:128 (unwritten slots = false DIFFER).
- m2c_sanity high rows (39 in this slot's files): 25 functions fixed NM-only; 11 with old DIFFER / new EQUIV, 14
  asm-checked but unobserved by difftest (UNVERIFIED list in P138.md); 8 rows false positives (reasons in P138.md).
- New hand C (NM): func_151E870C menu_spawn_character (mutants 23/23), func_151E1308 menu_player_join_page
  (27 setups, mutants 41/41). func_15060F28 (their object free) is still asm on `port` (C on port-b P83).
- game_eu_20B730.c D_800E0FB8 declared `u8 **` (coordinator item from browser P137).
- Checks: verify_all OK, NM links, protocheck 0 (981), selftest 60/60, progress_nm 4975/5915 (84.1%), bytes 60.5%.

## Next steps (from P138)

1. func_151408A4 (game_16DC80, emitter update, 3148 calls on the new-game mode-0 path; coordinator request).
2. func_151E1EDC, func_151E4B40 (menu pages).
3. func_151E3AE4: re-run P120 mutant lists (no ARGMEM) and the remaining 135 setups.
4. func_151DFD0C: ~12 surviving mutants need nav f1 setups with a terminating scene loop; func_151E19AC mutants
   (DIFFTEST_VARARGS_REF=1).
5. Targeted setups for the 14 unobserved scanner fixes (P138.md section 2), e.g. ARGMEM on the stack record callee.

## P142 (port-b) (session P142, 2026-10-23). Details: `docs/port/sessions/P142.md`

Branch `port-b` (from P139 9c9369d); the orchestrator merges it into `port`.

- Priority (P140): func_15169FB8 `image_effect_draw` (197680, the new-game title cards) + func_150966AC
  `image_draw_tiled` (C2B60) converted together; browser check pending.
- Also hand C (NM), difftest EQUIV + mutants: func_15096144 `sprite_draw_rect` (C2B60), func_15146078
  `plane_axes_from_normal` (170760), func_151BF678 `pickup_burst_spawn` (1EC610, now void(f32 *)), func_151BEE00
  `marker_sprite_spawn` (1EC610; LivesSprite typedef hoisted), func_15129EA4 `camera_follow_update` (156A30).
- func_1513CFE4 (169510, hot) skipped: its three handler tables still hold 16 asm handlers (list in P142.md).
- Checks: verify_all rc 0, NM build links rc 0, protocheck 5 lines = 4 known pairs + game_eu_11A2B0.c:9
  func_151432BC. progress_nm total 5099/5915 (86.2%), game 4569/5334, C bytes 65.1%, 816 asm-only.

## Next steps (from P142)

1. Browser: new-game title cards (func_15169FB8), sprites (func_15096144), pickup bursts, camera mode 0x40.
2. func_1513CFE4 after its handlers: port-b ones first (func_1513E83C, func_1513EE14, func_15140190 in 169510),
   the others in their owners' slots.
3. func_15153BA4 (17D3C0, not port-b) so func_151BF678's flash particle spawns.
4. Owned asm with C callers next (`python3 port_work/p142/asmlist.py`): func_150511E8, func_1510CA2C,
   func_15113D54, func_1514B8D4, func_1513FAB4, ...

## P139 (port-b) (session P139, 2026-10-23). Details: `docs/port/sessions/P139.md`

Branch `port-b` (from P136 b894dda); the orchestrator merges it into `port`.

- Hand C (NM), readable, with name comments, all difftest EQUIV + mutants: func_150B3394 `pipe_explode_spawn_chunk` +
  func_150B3668 `pipe_explode_spawn_debris` (E0430, D_8008ADA0 handlers 9 / 10), func_151432BC
  `spawn_region_random_point` (170760, P137 mode-0 stub), func_151277B0 `scope_zoom_sound_update` + func_15127520
  `scope_motion_sound_update` (14FF90), func_1514C9E0 `spawn_line_emit` + func_1514CDC8 `spawn_arc_emit` (1772D0),
  func_15095F18 `sprite_screen_rect` (C2B60, void), func_151BF490 `ring_particle_spawn` (1EC610), func_1517A550
  `drift_object_spawn` (1A7B30, void).
- D_8008B848 +0x1C handlers: all C. D_8008ADA0 asm handlers outside port-b: func_150C2334 (EF6D0), func_150C2558
  (EF410), func_150C1BC0 (EF370), func_151A11BC (1CE7D0), func_150B2A50 (E0170), func_150B40EC (E17A0),
  func_151AC628 / func_151ACBCC (1D9C00). func_1507D754 is game_A9D90 (not port-b).
- protocheck: new row game_eu_11A2B0.c:9 declares `void func_151432BC` (not port-b; must become s32 like the other
  three files). The func_15179008 -> func_15179A38 arity row is a false positive (callee reads no a0).
- Checks: verify_all rc 0 (default build byte-identical), NM build links rc 0, protocheck 5 lines = the 4 known pair lines + game_eu_11A2B0.c:9 func_151432BC (not port-b). progress_nm total 5092/5915 (86.1%), game 4562/5334, C bytes 64.8%, 823 asm-only.

## Next steps (from P139)

1. Fix game_eu_11A2B0.c:9 prototype (port slot) -> protocheck back to the known pairs.
2. Browser: new-game opening (func_151432BC), scope sounds, pipe explosions, sprite clipping.
3. Convert the remaining D_8008ADA0 asm handlers (list above) in their owners' slots.
4. Owned asm with C callers next (`python3 port_work/p139/asmlist.py`): func_15146078 (12 C calls), func_151BF678,
   func_151BEE00 ...

## State (session P138, 2026-10-23). Details: `docs/port/sessions/P138.md`

- func_151E3AE4 real bug fixed: in the asm frame y[] (sp+0x90) has only 14 slots and x[] follows it, so with 13+ items
  y[14..] overwrites x[0..]; now one `points[14 + 32]` buffer. 68 errored setups EQUIV with ARGMEM 15049AD0=0:52
  (old 20 DIFFER); aliasing mutant killed. Use ARGMEM 0:52, not 0:128 (unwritten slots = false DIFFER).
- m2c_sanity high rows (39 in this slot's files): 25 functions fixed NM-only; 11 with old DIFFER / new EQUIV, 14
  asm-checked but unobserved by difftest (UNVERIFIED list in P138.md); 8 rows false positives (reasons in P138.md).
- New hand C (NM): func_151E870C menu_spawn_character (mutants 23/23), func_151E1308 menu_player_join_page
  (27 setups, mutants 41/41). func_15060F28 (their object free) is still asm on `port` (C on port-b P83).
- game_eu_20B730.c D_800E0FB8 declared `u8 **` (coordinator item from browser P137).
- Checks: verify_all OK, NM links, protocheck 0 (981), selftest 60/60, progress_nm 4975/5915 (84.1%), bytes 60.5%.

## Next steps (from P138)

1. func_151408A4 (game_16DC80, emitter update, 3148 calls on the new-game mode-0 path; coordinator request).
2. func_151E1EDC, func_151E4B40 (menu pages).
3. func_151E3AE4: re-run P120 mutant lists (no ARGMEM) and the remaining 135 setups.
4. func_151DFD0C: ~12 surviving mutants need nav f1 setups with a terminating scene loop; func_151E19AC mutants
   (DIFFTEST_VARARGS_REF=1).
5. Targeted setups for the 14 unobserved scanner fixes (P138.md section 2), e.g. ARGMEM on the stack record callee.

## P136 (port-b) (session P136, 2026-10-23). Details: `docs/port/sessions/P136.md`

Branch `port-b` (from P133 48f7258); the orchestrator merges it into `port`.

- Hand C (NM), readable, with name comments, all difftest EQUIV + mutants: func_15111DD8 `star_field_generate` +
  func_151148C8 `world_object_rotate_point` + func_151152A4 `object_sound_play` (13DC30), func_1518010C
  `scope_lens_draw` (1ACBC0, P126 DL passthru: 4 mirrored scissored texrects), func_15169260 `node_lists_update_types`
  (1944C0, new-game path), func_1514C860 `spawn_ring_emit` (1772D0), func_1514948C `trail_spawn_directed` (175B20),
  func_15144CEC `world_to_screen` + func_1514654C `model_node_points_to_world` (170760), func_15159C2C
  `orbit_object_step` (186A80), func_15053430 `object_death_resolve` (78230).
- func_15111DD8 keeps Rare's float-upper-halfword star coordinates; its difftest needs DIFFTEST_STEP=1 + RETF
  (`port_work/p136/dd8.sh`), prefix-only (8000 iterations exceed the call cap).
- Stubs reached: guRotateF (libultra), func_150A7EE0 (D5650), func_1507D754, func_1000FA64; indirect handler tables
  D_8008B848 +0x1C / D_8008ADA0 not checked.
- P134's struct258 stride report (port line 774) = func_15022440, already fixed here in 4acf065 (port must merge it);
  no other D_800D20FC scaling in port-b's game_eu_4A070.c.
- Checks: verify_all rc 0, NM links, protocheck = known pairs (1088 bodies). progress_nm total 5082/5915 (85.9%),
  C bytes 64.5%, 833 asm-only.

## Next steps (from P136)

1. Browser: scope lens (func_1518010C), star-field overlay, new-game frames past func_15169260.
2. Owned asm with C callers next (`python3 port_work/p136/asmlist.py`): func_151277B0, func_1514C9E0, func_15095F18,
   func_151BF490, func_1514CDC8, func_1517A550, func_15146078, func_151BF678 ...
3. Remaining stubs from the new C: func_150A7EE0 (game_eu_D5650, not port-b), func_1507D754, func_1000FA64.

## State (session P134, 2026-10-23). Details: `docs/port/sessions/P134.md`

- Re-check after P132: 15 NM bodies with stack args stored before an IDO division trap check (`p134/trapscan.py`):
  all EQUIV with whole-block candidates (func_150E7104's known P104 sinf artefact aside); 40 setup files with pokes
  into ROM .data / .rodata (`p134/pokescan.py`) re-run: 0 DIFFER (func_1509CBD4 needs DIFFTEST_ROMDATA=1, func_151E19AC
  DIFFTEST_VARARGS_REF=1). `difftest.sh --self` drops prototypes declared in the same NM block (false DIFFER / CERR):
  use `p134/selfrun.sh` / `p132/cand.sh`. port-b files not run: func_15180AF0, func_151143D4.
- func_15036BB4 (game_eu_64070): three m2c stride bugs fixed (struct127 * + arg2 * 4, struct222 * + 0x10 twice),
  old DIFFER / new EQUIV, mutants 4/4; own commit. port-b: game_eu_4A070.c:774 `(sp38 * 0x30) + D_800D20FC` same bug.
- New hand C (NM): func_150F1F80 object_7B_pulse_scale (mode-0 frame path; mutants 16/16), func_151DFD0C
  title_chapter_select_page (378 setups 360 EQUIV / 18 UNSURE / 0 DIFFER; mutants 72 killed, 0 survived, 13 INVALID).
- difftest: header-only callees (cosf) take arity / float slots from the header (DIFFTEST_HDRSLOT_OLD=1 = old).
- Checks: verify_all OK, NM links, protocheck 0 (979), selftest 60/60, progress_nm 4973/5915 (84.1%), bytes 60.4%.

## Next steps (from P134)

1. func_151E3AE4: 20 of P120's 68 errored setups (the a1 ones) DIFFER on the ring array x[0] with
   DIFFTEST_ARGMEM=15049AD0=0:52 / 0:56 (ref 83.0, cand 74.0); EQUIV without ARGMEM. Probably a real bug: check
   the `x[0] = x[count - 1]` logic against the asm.
2. func_151DFD0C: re-run the 13 INVALID mutants with `p134/dfd0c_mutsetups.txt` minus the nav_*_f1_0 setups.
3. func_151E1308 with its producers func_151E870C (game_eu_20B730) and func_15060F28 (game_83300), then
   func_151E1EDC, func_151E4B40; func_151E19AC mutants (run with DIFFTEST_VARARGS_REF=1).
4. game_16DC80.c's #define hack for func_1513D524 stays until the browser merge changes functions.h.

## P133 (port-b) (session P133, 2026-10-23). Details: `docs/port/sessions/P133.md`

Branch `port-b` (from P130 54195bc); the orchestrator merges it into `port`.

- Hand C (NM), readable, each with a name comment: func_150A6D40 `sprite_billboard_draw` (game_eu_D4550.c, hand asm,
  P126 menu DL stub; whole-function harness `docs/port/sessions/p133/whole6d40.py`, 3300 EQUIV, NM mutants 28/28),
  func_1518403C `hud_model_load` (1B1010), func_15182BE0 `colour_fade_start` (1ACBC0), func_1514C390
  `camera_look_follow` (1772D0), func_15111CAC `overlay_mode_set` + func_15114CBC `world_object_timer_update` (13DC30),
  func_1515AEE4 `object_attach_effect_start` (186A80, P126 level-0x18 start stub). All difftest EQUIV + mutants.
- func_150A6D40 keeps Rare's quirks (hide test through `&D_800DBFF0`, upper-half D_800DD5E4/E8, 64-bit leftover
  compare); KSEG1 vertex address only `#ifndef PORT`; func_15095380's 9th argument (stale s0 in the asm) is 0x80000000.
- Stubs reached: func_15111DD8 (from func_15111CAC mode 1) and func_151148C8 (from func_15114CBC), both 13DC30 asm; their
  outputs are not read by the new C.
- Urgent P131 fix, own commit 4acf065: func_15022440 (game_eu_4A070.c NM) scaled D_800D20FC entries by
  sizeof(struct258) (now byte offset sp38 * 0x30) and divided the actor index twice (now byte difference / 812);
  difftest old DIFFER / new EQUIV on 5 setups, mutants 2/2.
- Checks: verify_all rc 0, NM links, protocheck = known pairs (1077 bodies). progress_nm total 5071/5915 (85.7%),
  game 4541/5334, C bytes 64.1%, 844 asm-only.

## Next steps (from P133)

1. Browser: menu sprites (func_150A6D40, 820 calls per menu run in P126) and the level-0x18 start (func_1515AEE4).
2. func_1518010C (game_eu_1ACBC0, 712 lines, scope range finder; P126 DL passthru) - not started.
3. Owned asm with C callers, smallest first: func_1514C860, func_1514948C, func_15144CEC, func_15159C2C, func_15053430,
   func_151152A4 (`python3 port_work/p133/asmlist.py`); func_15111DD8 / func_151148C8 are now reached from C.
4. game_eu_1BAF40.c calls func_1514C390 with 3 arguments through an implicit declaration (asm uses a0): arity row.
5. Whole-function harnesses on build_nm code cannot read `.nm_rodata` (NOBITS in the NM ELF: the switch jump tables
   are not in the file), so a `switch` compiled to a table jumps to 0 there; func_150A6D40 uses an if chain.

## State (session P132, 2026-10-23). Details: `docs/port/sessions/P132.md`

- difftest fixes (selftest 57 / 57): (1) varargs / unknown callees' stack arguments behind IDO division trap checks
  were never compared (the call-site scan stopped at `bnez; break 7`) - the real cause of P127's "ineffective poke"
  survivors; (2) DIFFTEST_POKE now wins over the ROM image in every trial (also with DIFFTEST_ROMDATA=1 and in
  rodata); precedence learned pointers > POKE > ROM image > random; (3) `[POKE unread]` from decoded loads (Unicorn's
  global read hook misses some loads). Old behaviour: DIFFTEST_TRAPSCAN_OLD / DIFFTEST_POKE_OLD / DIFFTEST_PREAD_OLD = 1.
- func_151DE100's 7 non-equivalent P127 survivors all killed (new gap setups, `p132/gende100.py`).
- New hand C (NM): func_151407D0 particle_emitter_spawn (game_16DC80; needs port-b's returning func_1513D524),
  func_1509D1EC / func_1509D338 / func_1509D49C (game_eu_CA630; load-game save-route producers of func_151DFD0C),
  func_151E0BBC menu_mode_select_page (main menu page 0).
- Checks: verify_all OK, NM links, protocheck 0 (977), selftest 57/57, progress_nm 4971/5915 (84.0%), bytes 60.2%.

## Next steps (from P132)

0. Web: merge together with port-b's P128 game_169510.c (func_1513D524 returns the record; func_151407D0 uses it).
   func_1515AEE4 (game_eu_186A80) on the new-game frame is port-b's.
1. func_151DFD0C (title page 2; its producers D338 / D464 / D49C are now C), then func_151E1308, func_151E4B40,
   func_151E1EDC (same alpha / pending-page head as func_151E0BBC).
2. func_151E19AC mutants; the 68 errored func_151E3AE4 setups.
3. Varargs printers verified before P132 had their stack args unchecked when a division preceded the call: re-run
   mutants of such functions if one matters.

## P130 (port-b) (session P130, 2026-10-23). Details: `docs/port/sessions/P130.md`

Branch `port-b` (from P129 c2778a9); the orchestrator merges it into `port`.

- Shadow pipeline in C (NM), producers + consumers together: func_15186A9C `shadow_level_vertices`, func_15187954
  `shadow_object_vertices`, func_15185514 `shadow_render_caster`, func_15186494 `shadow_clip_triangle`
  (game_eu_1B1ED0.c) and the hand-asm projectors func_150A6070 `shadow_level_triangles` / func_150A6324
  `shadow_object_triangles` with their private vertex transform func_150A661C (static `shadow_project_vertex`)
  (game_eu_D3880.c). All callees of func_15186D04's shadow chain have C now.
- Also: func_1510E6A0 `blob_shadow_draw` (game_eu_13B700.c, P126 menu DL stub), func_1517FF64 `view_fill_rect`
  (game_eu_1ACBC0.c, P126 DL passthru), func_1510DD2C `texture_cache_release` (game_eu_13A8A0.c).
- New whole-function harnesses (session dir, tools/port/difftest unchanged): `p130/nmasm_shadow.py` (hand asm vs C,
  interpreter + add/addi/mult/mflo) and `p130/whole6494.py` (Unicorn on both ELFs, real callees, NM function tables
  patched). `port_work/p130/mutnm.py` runs mutants against such harnesses (source edit + NM make + restore).
- verify_all rc 0 (default build byte-identical), NM build links (rc 0), protocheck 4 lines = the known pairs (A9D90 func_1517FD84, func_150A6C40 / 13C400). func_1510DD2C is `s32 (s32, s32, u16)` for game_eu_6AA20.c's
  prototype (verified as the void variant). progress_nm total 5064/5915 (85.6%), game 4534/5334, C bytes 64.0%, 851 asm-only.

## Next steps (from P130)

1. Browser: Conker's shadow on levels 0 / 0x2C (the whole func_15186D04 chain is C now), blob shadows, scope
   rectangles. If the shadow is wrong, start with func_15185514's texture pass and func_15186494's alpha / tex coords.
2. func_1510E6A0's dispatcher (descriptor slot 0x8008C78C): confirm it passes (Gfx *, rec, s16 idx).
3. func_1518010C (game_eu_1ACBC0, 712 lines, scope range finder; P126 DL passthru) is the next DL-path stub here.
4. Remaining asm with C callers in port-b files: `python3 port_work/p130/asmlist.py` (smallest: func_1518403C,
   func_15182BE0, func_1514C390, func_15111CAC).
5. Still from P129: drop the func_1513D524 `_void_proto` guards after the functions.h:772 fix merges; func_1505528C
   waits for func_15058898 / func_10010344.

## P129 (port-b) (session P129, 2026-10-23). Details: `docs/port/sessions/P129.md`

Branch `port-b` (from P128 9328f02); the orchestrator merges it into `port`.

- C (NM), all EQUIV + mutants: func_1515929C `watcher_state_update` (game_eu_186A80.c), func_1508F9F4
  `underwater_bubbles_update` + func_1509093C `underwater_air_meter_update` (game_BC510.c), func_15188630
  `light_fx_update` (game_eu_1B5C40.c, s32 for its caller, returns 0).
- func_1515929C's rule table D_800A65E0 and the s8 lists behind D_8008B3CC (its rodata_inject block) are referenced
  by symbol only: the browser's n64mem mirror holds the ROM game_data (rodata included) at N64 addresses and
  relocates D_8008B3CC's five words; NM link symbols are absolute. No build-file change. All 23 handlers were C.
- func_1508F9F4's uninitialised spawn flag: on the N64 the slot always holds func_1501878C's s1 (0x800BEDF0, saved
  there by func_1517ABB0's prologue) -> spawning enabled unless the asm clears it; C uses `spawn = (delay != 0)`.
  Verified with a test copy of difftest that presets the stack slot (`port_work/p129/difftest_stk.py`).
- Harness note: a static helper function in a candidate is run as a callee stub by difftest (write helpers inline).
- func_1513D524 `_void_proto` guards kept (functions.h:772 fix not in port-b yet).
- verify_all OK, NM links, protocheck = the two known pairs (A9D90 func_1517FD84, func_150A6C40 / 13C400:576).
  progress_nm total 5057/5915.

## Next steps (from P129)

1. After the functions.h:772 / game_eu_13C400.c:576 fixes merge: drop the `func_1513D524_void_proto` guards.
2. func_1505528C (game_eu_78230.c): blocked on func_15058898 (game_83300.c, asm, produces the object position) and
   func_10010344 (init_EB00.c, asm); convert together with / after them.
3. Browser: UNVERIFIED list in P129.md (watchers, underwater HUD, light effects).
4. Optional harness feature: DIFFTEST_STKFILL (P129 test copy) could go into tools/port/difftest (shared file, not
   changed here) for other uninitialised-stack reads.

## P128 (port-b) (session P128, 2026-10-23). Details: `docs/port/sessions/P128.md`

Branch `port-b` (from P125 e8fb8b9); the orchestrator merges it into `port`.

- C (NM), all EQUIV + mutants: func_15149AC0 `spark_spawn_from_desc` (game_eu_1772D0.c) with func_1513D524
  `record_spawn_default` now returning its record in NM builds (game_169510.c); func_150A6C40 `pvs_row_apply`
  (game_eu_D3880.c, void); func_15052F9C `object_catch_player` + func_1505327C `object_launch_player`
  (game_eu_78230.c, keep the callers' f32 / s32 return types, return 0); func_1510CE28 `tex_scroll_update`
  (game_eu_138E00.c, s32 for its caller).
- Temporary: game_169510.c / game_eu_1772D0.c hide functions.h:772's void func_1513D524 prototype with a
  `#define ... _void_proto` around the include (NM only). Remove once the port slot's functions.h fix merges.
- verify_all OK, NM links, protocheck = the known game_A9D90.c pair + func_150A6C40 vs game_eu_13C400.c:576 (port
  fixing). progress_nm total 5053/5915.

## Next steps (from P128)

1. After the functions.h:772 / game_eu_13C400.c:576 fixes merge: drop the `func_1513D524_void_proto` guards and
   re-run protocheck (should be the A9D90 pair only).
2. func_1515929C: its .data list table D_8008B3CC points into its own rodata_inject block (0x800A66C0..); decide how
   the NM / port builds keep those bytes at their addresses before converting; check the 23 D_8008B370 handlers.
3. func_1508F9F4: the spawn flag (sp+0x44) and level (s7) are uninitialised on some paths in the asm; decide the
   intended values (spawn = 1?) with the orchestrator, then convert.
4. Still open per-frame: func_15188630, func_1509093C, func_1505528C (its callee func_15058898 is a menu stub).
5. func_10010154 (init_EB00.c, not port-b) is func_15054F74's last asm callee.
6. Browser: UNVERIFIED list in P128.md.

## State (session P127, 2026-10-23). Details: `docs/port/sessions/P127.md`

- P124 gap closed: func_15029EA8 t6 / ta setups EQUIV with ARGMEM on the func_1000FA64 record (allocate_memory key
  10003E90 was right; the "never called" notes came from setups that return early), mutants 27 / 28 (1 equivalent).
  func_15023988 / func_1000FA64 / func_15188D80 setups + mutants done (only equivalent survivors).
- New hand C (NM): func_151E2B9C settings_save, func_151E2FCC menu_game_start, func_151DE100 game_pause_update
  (mode-0 handler, browser P126 blocker), func_150113E0 level_fire_emitters_create (game_3E890); func_151E86A4's
  NM body skips the anti-tamper code checksum (no null-zone write in the port).
- NM prototype fixes from P125: func_150A6C40 void, func_15179008 prototypes. func_1513D524 header change deferred
  to the merge with port-b (its definition is in game_169510.c).

## Next steps (from P127)

0. Web: merge; drop func_151DE100's data stub (port/ side). Watch the pause menu's "no" path (cartridge check DMA,
   P127.md) and func_151407D0 (game_16DC80, asm) on the new-game frame.
1. func_1513D524 `void *` in functions.h under NM together with port-b's game_169510.c change.
2. Menu pages still asm: func_151DFD0C, func_151E0BBC, func_151E1308, func_151E1EDC, func_151E4B40 (P120 drafts in
   port_work/p120/gen, raw); func_151E19AC mutants; 68 func_151E3AE4 setups.
3. func_10024190 (osWritebackDCache, hand asm cache loop): port no-op, keep as is.

## P125 (port-b) (session P125, 2026-10-23). Details: `docs/port/sessions/P125.md`

Branch `port-b` (from P122 422e5d3); the orchestrator merges it into `port`.

- C (NM), all EQUIV + mutants: menu stubs func_1516865C `sprite_quad_init` (game_1944C0.c, now `s32 (u8 *, s32 x4)`
  to match its callers), func_15054F74 `menu_object_update` (game_eu_78230.c, file prototype -> void),
  func_1510E004 `blob_shadow_update` (game_eu_13B700.c), func_15179008 `rain_update` + its asm callee func_1517A084
  `rain_spawn_splashes` (game_eu_1A6C30.c); func_15184298 `anim_meshes_update` (game_eu_1B1010.c) with its asm
  callees func_151661F0 `mesh_swing_update` (game_eu_193A00.c) and func_1517A320 `flag_wave_update`
  (game_eu_1A7B30.c).
- Not done: func_15149AC0 (needs func_1513D524 to return its record: functions.h:772 + game_169510.c),
  func_150A6C40 (caller game_eu_13C400.c:576 declares s32; asm is void), the rest of the per-frame group.
- verify_all OK, NM links, protocheck = only the known game_A9D90.c func_1517FD84 lines. progress_nm total
  5048/5915.

## Next steps (from P125)

1. func_15149AC0 (menu, 1451 hits): change `func_1513D524` to return `func_1513D2F0(...)` (game_169510.c, check
   byte-identical) and functions.h:772 to `struct210 *` (or `u8 *`), then convert (stack struct sp44..spDC, one
   struct: the record copy memcpy(rec + 0x110, &sp44, 0x50)).
2. func_150A6C40: decide the caller prototype (game_eu_13C400.c:576 `s32` -> void), then convert (reading in P125.md).
3. func_15179008 callers game_eu_1231B0.c:140 / game_eu_1387B0.c:10 have no prototype (implicit int): check the
   wasm link for a signature-mismatch stub.
4. Per-frame stubs still open: func_1510CE28, func_15188630, func_1508F9F4 + func_1509093C, func_1515929C,
   func_1505528C (its callee func_15058898 is also a menu stub).
5. Browser: menu sprites / shadows / rain / animated meshes (UNVERIFIED list in P125.md).

## State (session P124, 2026-10-23). Details: `docs/port/sessions/P124.md`

- **m2c scattered stack structs fixed (NM, commit 1efdab2)**: func_1510AEB0 (the P121 frame-1985 trap), func_150B7700,
  func_150B7DFC, func_1519961C, func_151ABE04, func_150D4FF0, func_15103310, func_1519E6BC: one struct / 2-element
  arrays; ARGMEM on the passed memory: old bodies DIFFER, new EQUIV, mutants. func_15169ED8 returns its record (NM).
  Scanner `p124/spaddr_scan.py` (+ triage tsv).
- **Scene handler C chain (NM)**: func_15029EA8 scene_event_run_c with func_15023988 (sound callback),
  func_15023EC4 (event lookup around now), func_1000FA64 (positional sound start), func_15188D80 (trail start).
  Setups: 29EA8 444 EQUIV, EC4 168 EQUIV (mutants 5/8); 23988 / FA64 / 188D80 random EQUIV only. **UNVERIFIED**: types
  6 / 0xA record path (wrong allocate_memory key in the setups) - see P124.md. Checks: verify_all OK, NM links,
  protocheck 0 (968), selftest 51/51, progress_nm 4962/5915 (83.9%), bytes 59.9%.
- Menu pages (task 2) and the 19AC / 3AE4 re-runs (task 3) NOT started (budget went to the coordinator's re-priority).

## Next steps (from P124)

0. Web: merge; the title menu should fade in (5/0x01 -> func_1517F3B0 from handler C); level 0x21 sounds start.
1. Menu pages: func_151DFD0C, func_151E0BBC, func_151E1308, func_151E1EDC, func_151E4B40, func_151E2B9C, func_151E2FCC,
   func_15042E3C (smallest / producers first). 19AC mutants, 68 3AE4 setups (P120 lists).
2. Remaining handler-C callee still asm: func_15060F28 (game_83300, C on port-b; replay path of 5/4 only).

## P122 (port-b) (session P122, 2026-10-23). Details: `docs/port/sessions/P122.md`

Branch `port-b` (from P119 3b9eea1); the orchestrator merges it into `port`.

- m2c_sanity: the 3 high rows in port-b files (func_15051558, func_1509A024, func_15180AF0; all pooled `O:` width
  rows) are false positives (reasons in P122.md); no change.
- C (NM): func_151848D8 `shadow_light_projection` (52/58, 4 equivalent, 2 boundary survivors), func_15178004
  `vtx_anims_update` (19/19) with its five hand-asm wave animators in game_eu_D4C90.c: func_150A7480
  `vtx_wave_y_per_vertex`, func_150A75A0 `vtx_wave_y`, func_150A76A8 `vtx_wave_y_colour`, func_150A7840
  `vtx_wave_y_colour_per_vertex`, func_150A79FC `vtx_wave_y_normal_colour` (func_150A7BD0 stays GLOBAL_ASM).
- verify_all OK, NM links, protocheck = only the known game_A9D90.c func_1517FD84 line. progress_nm total
  5040/5915 (85.2%), game 4510/5334, C bytes 63.1%, 875 asm-only.

## Next steps (from P122)

1. game_A9D90.c:19 `void func_1517FD84(...)` (port session).
2. func_15184298 (game_eu_1B1010.c) with func_151661F0 (game_eu_193A00.c) and func_1517A320 (game_eu_1A7B30.c):
   needs a session owning those files.
3. Boundary survivors: func_151848D8 `min_h < 10` / `m < 32767`; P119's 7 threshold gaps.
4. Browser: shadows, vertex wave animations (water), plus the P119 list.

## State (session P120, 2026-10-23). Details: `docs/port/sessions/P120.md`, map `docs/port/sessions/p120/carousel_map.md`

- **Menu camera / carousel func_151E73C8 (menu_camera_update) in hand C (NM)**: writes rec->fade / x2B / titlePage /
  menu, so the menu pages can now run. 620 / 626 setups EQUIV, mutants 51 killed (survivors equivalent).
- func_151E3AE4 settings_list_draw (553 setups EQUIV, 68 not run), main pages func_151E1174 main_settings_page and
  func_151E19AC main_players_page (mutants of 19AC not done).
- func_15042D94 varargs prototype under NM (game_eu_216470); func_151EE704 `| 0x80000000` dropped (P121);
  func_1517FD84 declared void (game_A9D90). difftest `DIFFTEST_VARARGS_REF=1`.
- Checks: verify_all OK, NM links, protocheck 0 (963), selftest 51/51, progress_nm 4957/5915 (83.8%), bytes 59.6%.

## Next steps (from P120)

0. Web: merge; mode 3 should now slide / zoom (left / right / accept / back) and show pages 1, 3..5, main pages 2, 3, 5.
1. **func_1510AEB0 (game_eu_1386C0, P121 request)**: rewrite with one struct (layout of S59A0 in game_eu_1231B0),
   difftest with ARGMEM on the passed struct. Not started.
2. Re-run the 19AC mutants (`p120/19ac_muts.txt`, DIFFTEST_VARARGS_REF=1) and the 68 ERROR setups of 3AE4.
3. Remaining menu: func_151DFD0C (title page 2, 625), func_151E0BBC (366), func_151E1308 (425), func_151E1EDC (720),
   func_151E4B40 (511); func_151E2B9C (settings save) and func_151E2FCC (start callback); func_15042E3C text printer.
4. P117 leftovers: func_151DEDD0 / page-1 mutants not run.

## P119 (port-b) (session P119, 2026-10-23). Details: `docs/port/sessions/P119.md`

Branch `port-b` (from P115 9f8e18a); the orchestrator merges it into `port`.

- **Merged port 28b8fa3** (275614d): CD540 = port's file; 83300 / 981E0 adjacent NM blocks kept; AF2A0 = port's
  one-argument func_15084000; difftest.py = P80 splice + P73 nmside; selftest 53/53. Fixes: func_15073118 `u8 *`
  declaration (NM build), duplicate func_1506BF5C prototype, game_eu_F5580.c one-argument func_151149AC.
- C (NM): func_1512DAD0 `camera_queue_event` (8/8), func_150A7B80 `mtx_set_identity` (5/5), func_15113000
  `world_records_build_visible` (30/35, 3 equivalent), func_1517FD84 `hud_lens_set_target` (12/13, 1 equivalent),
  func_15181A6C `hud_lens_update` (33/40, 2 equivalent), func_1510D090 `tint_channels_update` (16/18, 2 equivalent).
- verify_all OK, NM links. **protocheck 2 lines = 1 mismatch**: game_A9D90.c:19 declares `s32 func_1517FD84`, the
  function returns nothing: make it `void` (not a port-b file). **progress_nm** total 5033/5915 (85.1%), game
  4503/5334, C bytes 62.8%, 882 asm-only.

## Next steps (from P119)

1. game_A9D90.c:19: `void func_1517FD84(s32, f32, f32, f32, s32);` (protocheck back to 0).
2. Boundary survivors listed in P119.md (func_15113000 depth == far / near; func_15181A6C exact-threshold cases):
   targeted setups if wanted.
3. Shadow func_151848D8 (674 insns, game_eu_1B1ED0.c); func_15178004 / func_15184298 (asm callees, see P115).
4. Browser: camera requests, visible world records, HUD lens / zoom, tint channels.

## State (session P117, 2026-10-23). Details: `docs/port/sessions/P117.md`, map `docs/port/sessions/p117/menu_map.md`

- **P116 / P118 browser bugs fixed in P15 m2c NM bodies**: func_1502457C (scene event walker: track pointer stride x4,
  slot offset x4, the D_800C39D0 / 39D8 / 3A60 reads at 16-byte stride, D_800C39E0 word store -> `sb`; 48 setups EQUIV,
  old body DIFFERs), func_150337A8 (`lb` compares for 0xF2), func_150623F4 (byte loop, object step, 0x40-byte stride).
- **Mode 3 menu in hand C (NM)**: func_151DEDD0 menu_mode_update (225 setups EQUIV), func_151EE704 menu_sprites_load,
  func_15007778 save_slots_reset, title pages func_151E06D0 title_slot_page (slots 3..5) and func_151DF6A4
  title_press_start_page (page 1). MenuState typedef for the record D_80090174.
- **No page runs until func_151E73C8 (asm, 1129, menu carousel object, called via func_1512A8D0) is C**: it is the only
  writer of rec->fade (>= 0.5 gates the pages), the carousel index and titlePage / menu.
- Event 0xC8: all 21 native-6 calls -> func_15097E9C (C on port-b with func_15097D20), cmds 0x3D / 0x54 / 0x14.
- Checks: verify_all OK (rc 0), NM links, protocheck 0 (959), selftest 51/51, progress_nm 4953/5915 (83.7%), bytes 59.1%.

## Next steps (from P117)

0. Web: merge; LogoScreen to t = 1700 with the walker fix (track 13: camera switch + 5/0x67 -> mode 3); func_150337A8 no
   longer runs off memory. Mode 3: frame-0 setup (sprites, slots), menu music, input; pages wait for func_151E73C8.
1. func_151E73C8 (game_eu_20B730, 1129): carousel producer of rec->fade / x2B / titlePage / menu. Then title drawing
   func_151E3AE4 (953), title page 2 func_151DFD0C (625), main-menu pages func_151E0BBC / 1EDC / 1174 / 1308 / 19AC /
   func_151E4B40.
2. game_eu_216470.c line 20 declares varargs func_15042D94 with 4 fixed args (non-NM, C callers): wasm signature check.
3. Remaining m2c_sanity rows in my files (web `docs/port/m2c_sanity.tsv`; the `(x*3)+&D_800AB7F4` pattern in 7 functions).
4. func_15029EA8 + chain (P114 item 2): not started.
## P115 (port-b) (session P115, 2026-10-23). Details: `docs/port/sessions/P115.md`

Branch `port-b` (from P111 5a19134); the orchestrator merges it into `port`.

- **Camera** in C: func_15128D50 (`camera_lean_from_heading`, mutants 22/24, 2 equivalent), func_15129220
  (`camera_process_events`, the per-frame event pump; 87 setups, mutants 41/42, 1 equivalent), func_1512EB60
  (`camera_read_depth_row`, DL; mutants 18/20, 2 equivalent). func_15128D50 / func_15129220 return nothing: caller
  declarations in game_14FF90.c, game_eu_15C660.c, game_eu_4A070.c are now `void`.
- func_15113798 (`world_records_update_matrices`, per frame from func_15019130): mutants 20/20.
- func_151149AC (`world_record_find`, P114 draft) inserted in game_eu_13DC30.c on the coordinator's request.
- Default build byte-identical (verify_all, `port_work/p115/verify1.log`), NM links. protocheck: 3 problems = the
  known func_15157580 + func_151149AC declared with 3 args in game_eu_F5580.c:93 (not a port-b file; fix the
  declaration to `u8 *func_151149AC(u8)`). **progress_nm** total 4933/5915 (83.4%), game 4405/5334, C bytes 58.0%,
  982 asm-only.

## Next steps (from P115)

1. Remaining stubs on the new C paths: func_1512DAD0 (41 insns, game_eu_15B2E0.c; script request start in
   func_15129220) and func_150A7B80 (16 insns, game_D5030.c; Mtx of disabled records in func_15113798).
2. game_eu_F5580.c:93 / 118: one-argument func_151149AC (protocheck).
3. Per-frame handlers left: func_15113000 (448, callees C), func_15181A6C with its producer func_1517FD84 (same file),
   func_15178004 (asm callees in game_eu_D4C90.c), func_15184298 (asm callees func_151661F0, func_1517A320), shadow
   func_151848D8, func_1510D090.
4. Browser: camera events (cut scenes, save / restore of the game camera), depth row, attached world records.

## P111 (port-b) (session P111, 2026-10-23). Details: `docs/port/sessions/P111.md`

Branch `port-b` (from P108 7d59c9c); the orchestrator merges it into `port`.

- **func_1512EE50 in C** (`camera_apply_request`, game_eu_15C660.c): the per-frame camera request handler that
  writes the eye height cam +0x2FC (P105 camera bug). Map `p111/func_1512EE50_map.md`. 213 setups EQUIV, mutants
  78/78. Caller declaration in game_14FF90.c changed to `void`. Only stub callee: func_15128D50 (mode 2, not a
  port-b file).
- Free camera: func_1512B728 (`free_camera_scan_depth`, 16/16 mutants) and func_1512BCA0 (`free_camera_turn`,
  returns s32; 28/29 mutants, 1 equivalent). func_1512B2C4's three callees are all C now.
- func_150B3CA8 (`trail_hit_splash`, game_eu_E0430.c): the last asm trail hit handler; mutants 33/33.
- Default build byte-identical (verify_all rc 0), NM links, protocheck 1 known problem. **progress_nm** total
  4928/5915 (83.3%), game 4400/5334, C bytes 57.7%, 987 asm-only.

## Next steps (from P111)

1. Browser: re-run the P105 camera scenario. The pre-death view should no longer look straight down. Also check
   the free camera and the trail splashes (P111.md UNVERIFIED).
2. func_15128D50 (game_eu_156560.c), func_15129220 (game_eu_156A30.c) and func_1512EB60 (game_eu_15C370.c) are
   not in port-b files and need an owner.
3. Smallest asm-only left in port-b files (from P108): func_15144CEC (101), func_1505327C (109), func_15053430
   (113). func_15060D54 is now owned by port (game_83300.c moved).

## State (session P121, 2026-10-23, port-web). Details: `docs/port/sessions/P121.md`

- Merged port 4987bbc (P117) as 85aea50. NM build broke on a `func_1501D348` redeclaration in game_eu_20B730.c
  (P117 `s32` at line 188 vs port-web `void`); line 188 -> `void`. verify_all OK, NM link, protocheck 0 (1029),
  float-int BUG 0, m2c_sanity 199 rows / high 43 rows / 37 functions (P118 202 / 48 / 40; the 3 fixed functions gone),
  arity unchanged, census 722 ok / 0 FAIL (clean). Run m2c_sanity after the web rebuild (it reads port/build/ll).
- **Track 13 runs**: 3/0xD + 5/0x5C + 5/0x67 at frame 2133 -> func_151DECB4 -> mode 3 / level 0x1D at 2139.
  P116 +0x65 cycle guard never fires (kept, log only). `?p116walk` removed (redundant).
- **P113 camera guard kept**: at 2133 it still fires but is harmless now (`?p113noguard=1`: no trap); the menu level's
  916-frame scene ends at 3053 with the same stale camera target and without the guard node traps at 3057
  (func_1508F0D4).
- **New trap: P117 C func_151EE704** (game_eu_216470) `dl[1] | 0x80000000` -> OOB store at 2139. TEST-ONLY copy
  without the OR: `?p121spr=1`.
- Menu: rec->fade stays 0 (2139..4301), pages hidden; music func_1000E7A0(4, 0) from 3057. **No 3D is drawn on the menu**
  (black shots; triangle count frozen after the scene), unlike P116. Cause open.
- Frame-1985 trap explained: track 13's 5/0x5C -> func_1510AEB0 (game_eu_1386C0, P15 m2c) passes `&sp24` of scattered
  stack locals as a 0x3C-byte struct -> garbage table index in func_15169EF8.
- `?p110noev=1` regression clean: node + 2 Chrome walks (death, 0x2C and back, heap 0, null 0).

## Next steps (from P121)

1. Conversion slot: func_151EE704 drop the K0 OR (1 line); func_1510AEB0 as one stack struct (S59A0 layout);
   func_151E73C8 (menu carousel, producer of rec->fade).
2. port-web: why the menu draws no 3D after mode 3 (handler camera +0x2C = 0x80000, menu scene camera track, stubs
   func_1510E004 / func_15149AC0); then drop `?p121spr` once item 1 merges.
3. Scene-end camera retarget producer (func_15029EA8 chain, func_151149AC) so the P113 guard can go (3053 case).

## State (session P118, 2026-10-23, port-web, tooling). Details: `docs/port/sessions/P118.md`

- New `port/tools/m2c_sanity.py` (host, ~10 s): compares every NON_MATCHING body's clang IR (sroa+instcombine) with
  the EU asm for access width (lb/lh vs word), pointer stride (`p += 4` on `u8 **`), and the m2c byte idiom
  `(x * K) + &SYM` on a non-byte symbol. Output `docs/port/m2c_sanity.tsv` (202 rows; high 48 rows / 40 functions).
- Validation: flags func_1502457C (scaled + stride + a third bug: line 299 `*(&D_800C39E0 + arg1) = 1` on s32, asm `sb`)
  and func_150337A8 (`lb` vs `*(s32 *)`), all high.
- New real bugs confirmed by hand: func_150623F4 (frame path, `s32 *var_s1 += 0x40`, asm +64), func_15010110,
  func_150C6960 / func_1509EDE0 (scaled), func_1506045C, func_15070300, func_1508A040, func_1509DFCC, func_151E2C88,
  func_150DE9D8, func_16000B14. FP sample: 2/10 (pooled `O:` width rows are the weak tier).
- No src_eu edits (fixes are for conversion slots).

## Next steps (from P118)

1. Conversion slot: fix the high rows (P118.md section 6 list), frame path first: func_1502457C (3 lines) +
   func_150337A8, func_150623F4; then the scaled rows (7 functions share the `D_800AB7F4` x3 idiom).
2. Re-run `python3 port/tools/m2c_sanity.py` after each conversion merge; hand-check pooled `O:` rows before fixing.

## State (session P116, 2026-10-23, port-web). Details: `docs/port/sessions/P116.md`

- Merged port 28b8fa3 (P114) as 21cc7f0 (HANDOFF only). verify_all OK, NM link, protocheck 0 (1024), float-int BUG 0,
  census 722 ok / 0 FAIL.
- **Title menu reached**: Chrome, events on: scene 722..2133, then **mode 3 / level 0x1D at frame 2139**, event 0xC8
  starts, the menu room renders (GAME1 sign, Conker, sack character): `p116/P116_menu_60000ms.png`.
- **Bug in game C func_1502457C** (scene walker, game_eu_51190.c, P15 m2c): `var_s6 += 4` on a `u8 **` (and the slot
  offset `(arg1 * 0x78) + &D_800C3AA8` on an `s32 *`). Track i walks track 4i's events with track i's object, so
  LogoScreen attached Conker to himself (+0x65 = 1) and func_1502C1D4 hung; track 13 (t = 1700 camera switch, 5/0x67)
  is never walked. Fix = 2 lines (P116.md section 2); not applied (game C).
- With a fixed port-side copy (`?p116walk=1`, TEST ONLY) the next P15 m2c bug traps: func_150337A8 (game_eu_5D910.c)
  compares words where the asm uses `lb` (-0xE = 0xF2 opcode byte).
- Hang guard (always on): the func_1502C1D4 wrap logs a +0x65 cycle and skips that frame's update (LogoScreen 1461..1628).
- The P113 camera guard still fires at 2133 (track 13 unwalked) and stays.
- `?p110noev=1` regression clean: node + 2 Chrome walks (death, 0x2C and back, heap 0, null 0).

## Next steps (from P116)

1. Conversion slot: fix func_1502457C (2 lines) and func_150337A8 (`*(s8 *)` compares) in one commit; scan other P15
   m2c bodies for pointer-stride / load-width errors. Then port-web: boot without p116walk, check track 13 at t = 1700
   and drop the P113 guard (`?p113noguard=1` first).
2. Mode 3: func_151DEDD0 + 8 pages (game_eu_20B730), func_15149AC0, func_1000FA64, func_15058898, func_15054F74,
   func_15179008, func_1000BF60.
3. Node trap at frame 1985 in func_15169EF8 (table index), seen once; recheck after 1.

## State (session P113, 2026-10-23, port-web). Details: `docs/port/sessions/P113.md`

- Merged port 8ed5688 (P112) as 8e79558.
  - game_83300.c: both kept (func_15060D54 from port, func_15060F28 C from port-web).
  - game_eu_CD540.c: port's version taken whole (func_1509FD30 + the new func_150A02EC). The port-b P77
    func_150A02EC is dropped, so **port-b will get the same conflict**.
  - verify_all OK, NM link, protocheck 0 (1021), float-int BUG 0, census 722 ok / 0 FAIL.
- **LogoScreen scene end: the heap corruption was not the object removal.**
  - With func_150849C0 / func_15060D54 as C, the heap still broke at frame 2137.
  - Cause: camera D_800DBFF0[0].unk3D4 (target = the object's +0x31C record) still points at the record that
    func_15060F28 freed at frame 2133. func_15122AE0 -> func_15122C5C writes floats into it.
  - Producer: nothing retargets the camera. On N64 the scene VM func_15024910 (asm stub) should leave level 0x21
    by opcode 0x67 first.
  - TEMPORARY guard `--wrap=func_15060F28` (p103_boot.c) points such a camera at a zeroed parking record.
    `?p113noguard=1` turns it off.
- With the guard: node 150 s and Chrome run past the scene with heap 0 and no trap. The game then **stalls on level
  0x21, mode 1, black screen**, and no new stub is hit after frame 2133. func_151DECB4 / mode 3 are never reached.
- `?p110noev=1` regression: node and 2 Chrome walks clean (death, scene, 0x2C and back, heap 0).
- New diagnostics: `?p113watch=ADDR&p113wf=F` (16-byte write watch at osSetIntMask / thread switch / 19
  checkpoint wraps in func_15019130), `?p113wtrace=F`, `?p113free=F`, opt-in func_15084814 emulation
  `?p113g84=1`. The heap walk no longer traps on a garbage link.

## Next steps (from P113)

1. Conversion: the scene VM func_15024910 / func_15029EA8 (game_eu_51190). Check that opcode 0x67 reaches
   func_151DECB4, and find the camera retarget at scene end, so the P113 guard can be dropped.
2. Then mode 3 func_151DEDD0 and its pages (game_eu_20B730), func_151EE704, func_15007778, event 0xC8 natives
   (port-b C5530).
3. func_15084814 (small, last stub of the removal chain), then the LogoScreen stubs and the P110 per-frame list.

## State (session P110, 2026-10-23, port-web). Details: `docs/port/sessions/P110.md`

- Merged port a658cf8 (P104 music), port-b 7d59c9c (P102 / P108) and port 1888378 (P106 event system).
  - Only HANDOFF conflicts (merge_union).
  - After each merge: verify_all OK, NM link, protocheck 0, float-int BUG 0. Census 722 ok / 0 FAIL.
- port/boot/pc_overrides.c: func_150ADA20 removed (duplicate of the P106 game C).
- port/tools/n64mem.py: maps the 10 event-VM natives in D_80088A44 (VM_NATIVES).
- **P105 guard dropped.** The trail chain runs as C: spawns, then about 22000 draws, heap 0, null 0. func_150B3CA8
  is not reached.
- **Music plays.** Level 0 starts song 0x60 and level 0x2C starts song 0x35.
  - Node meter `?p110aud=1`: non-zero output from frame 1012.
  - Chrome: rms 0.0071, peak 0.135.
- **The LogoScreen event 0xC9 now starts on level 0x21** and runs a 1416-frame scene.
  - At its end, the object removal stubs func_150849C0 / func_15060D54 run, the heap is corrupted (block 43), and
    the run traps at frame 2137. This happens in node and Chrome, idle or walking.
  - `?p110noev=1` (TEST ONLY) skips event starts, so the old walk / death / 0x2C path can still be tested. With it:
    3 Chrome walks clean.
- Diagnostics: `?p110part=1` (particle counts), `?p110aud=1`. `?p101mus=1` now also logs the songs started inside
  func_150000B0.

## Next steps (from P110)

1. Conversion slots: func_150849C0 (game_eu_AF2A0) + func_15060D54 (game_83300) together.
   - These are the object removal chain under func_15060F28; run stubcalls on it first.
   - After that, re-run `p103boot` idle with no `p110noev`. Expect the scene end, then func_1509FD30.
2. Then the LogoScreen scene stubs: func_151149AC, func_150A4FE4, func_15083F30, func_1513095C / func_1513100C.
3. Camera func_1512EE50, the per-frame stubs under func_15019130, the free-camera callees, func_151848D8.
4. Remove `p110noev` once the event path survives the scene end.

## State (session P107, 2026-10-23, port-web). Details: `docs/port/sessions/P107.md`

- No src_eu change; the default build is unchanged.
- **game_A28B0.c (202 functions) had never been in the port.** It failed the census because of
  `((u8*)p->unk218) += 1;` at line 21 (upstream code). All its functions were weak `absolute` stubs. None was ever
  hit, so it is not on the frame path.
  - srcfix.py: new rule `((T)x) op= v` -> `*(T *)&x op= v`.
- init_2070.c and debugger_257350.c (printf `s - fmt`, char vs unsigned char pointers) fixed by a new srcfix
  `ptrsub` rule.
- game_eu_12A7C0.c removed from port/exclude.txt (stale since P28).
- Census: 0 FAIL. Function stubs 962 -> 762.
- Node boot clean: 1 death, scene, 0x2C warp and back, heap 0, null zone 0, no trap.
  - 47 -> 49 stubs. New: func_1515929C and func_1505528C (frame ~2130), reached through the 12A7C0 table handlers
    that now run as C.
- New **port/tools/stubcalls.py** (docstring = usage). For each C function it lists the stubs it calls:
  direct / table / addr / deep, with census hits.
  - Output: docs/port/stubcalls.tsv (NM) and stubcalls_all.tsv (all C).
  - Top: func_15019130 (5 per-frame stubs), func_1512B2C4 (free camera), func_15122C5C (func_1512EE50 camera),
    func_1510BF50, func_1509BFB0 (table D_80088874).

## Next steps (from P107)

1. Conversion slots: `python3 port/tools/stubcalls.py --func <funcs>` on a port build before committing a
   frame-path function.
2. The P105 list stands: particle handlers, then func_1512EE50, the free-camera callees, func_151848D8, the
   level-event unit.
3. Chrome check of the 12A7C0 handlers and the 2 new stubs. If they cause trouble, put the exclude line back.

## State (session P105, 2026-10-23, port-web). Details: `docs/port/sessions/P105.md`

- Merged port c35d31d (P98 / P100) and port-b 66dffbc (P96).
  - Conflicts: HANDOFF (merge_union) and game_eu_1EC610.c, where both sides made the same func_15157580 f32 change.
  - Checks after each merge: verify_all OK, NM links, protocheck 0 (997), float-int scan BUG 0 / REVIEW 4 / OK-INT 12.
  - Clean rebuild (census + vbe.stamp removed).
- **P97 path guard dropped** (func_15020920 is C). The scene path C now moves the player sanely:
  (346, -2078, -2266) -> (348, -2284, -2284).
- **New TEMPORARY guard `__wrap_func_151DA6F8`** (p84_checks.c + Makefile `--wrap`).
  - Why: P100's C particle spawn wrapper feeds the stub particle handlers func_15148428 / func_151485AC. After the
    scene that dirties null+0x10 and traps in func_100043B4 (memory out of bounds).
  - This happens on merge 1 alone, guard or not. `?p105part=1` / `PORT_P105PART=1` runs the real C.
  - With the guard: node and 3 Chrome walks each give one death, the scene ends, the 0x2C warp works there and back,
    heap 0, null zone 0, no trap.
- Camera: still straight down before the death (pitch -78 deg at node frame 885). func_15126378 (C) runs every frame
  but does not write the eye height. **func_1512EE50** (asm) writes +0x2FC: eye.y stays 400, 218 in the scene.
- Scans:
  - protoasm: INT 2 (game_83300, port-b), ARITY 0.
  - arity: 112 rows / 56 with severity > 0 (no new rows).
  - Census: 47 stubs (P101: 52). Newly reached: func_1512B728 / BAAC / BCA0, func_151848D8, func_1512EB60 (DL),
    func_1501A764.
- game_A28B0.c fails the census build (old lvalue cast at line 21) and has no vobj object: check it.

## Next steps (from P105)

1. Convert func_15148428 + func_151485AC (particle handlers, game_eu_175B20), then drop the P105 guard.
2. func_1512EE50 (camera coordinator, eye height +0x2FC; 1352 insns).
3. The free-camera callees func_1512B728 / func_1512BAAC / func_1512BCA0, func_1512EB60, func_151848D8 (shadow).
4. P103's level-event unit (func_1509CBD4, func_1509B950 + func_1509B8FC return, func_1509B5AC, func_150ADFD0), then
   func_150039E0, func_150000B0.
5. game_83300 INT rows; game_A28B0.c port build failure.

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
## State (session P134, 2026-10-23). Details: `docs/port/sessions/P134.md`

- Re-check after P132: 15 NM bodies with stack args stored before an IDO division trap check (`p134/trapscan.py`):
  all EQUIV with whole-block candidates (func_150E7104's known P104 sinf artefact aside); 40 setup files with pokes
  into ROM .data / .rodata (`p134/pokescan.py`) re-run: 0 DIFFER (func_1509CBD4 needs DIFFTEST_ROMDATA=1, func_151E19AC
  DIFFTEST_VARARGS_REF=1). `difftest.sh --self` drops prototypes declared in the same NM block (false DIFFER / CERR):
  use `p134/selfrun.sh` / `p132/cand.sh`. port-b files not run: func_15180AF0, func_151143D4.
- func_15036BB4 (game_eu_64070): three m2c stride bugs fixed (struct127 * + arg2 * 4, struct222 * + 0x10 twice),
  old DIFFER / new EQUIV, mutants 4/4; own commit. port-b: game_eu_4A070.c:774 `(sp38 * 0x30) + D_800D20FC` same bug.
- New hand C (NM): func_150F1F80 object_7B_pulse_scale (mode-0 frame path; mutants 16/16), func_151DFD0C
  title_chapter_select_page (378 setups 360 EQUIV / 18 UNSURE / 0 DIFFER; mutants 72 killed, 0 survived, 13 INVALID).
- difftest: header-only callees (cosf) take arity / float slots from the header (DIFFTEST_HDRSLOT_OLD=1 = old).
- Checks: verify_all OK, NM links, protocheck 0 (979), selftest 60/60, progress_nm 4973/5915 (84.1%), bytes 60.4%.

## Next steps (from P134)

1. func_151E3AE4: 20 of P120's 68 errored setups (the a1 ones) DIFFER on the ring array x[0] with
   DIFFTEST_ARGMEM=15049AD0=0:52 / 0:56 (ref 83.0, cand 74.0); EQUIV without ARGMEM. Probably a real bug: check
   the `x[0] = x[count - 1]` logic against the asm.
2. func_151DFD0C: re-run the 13 INVALID mutants with `p134/dfd0c_mutsetups.txt` minus the nav_*_f1_0 setups.
3. func_151E1308 with its producers func_151E870C (game_eu_20B730) and func_15060F28 (game_83300), then
   func_151E1EDC, func_151E4B40; func_151E19AC mutants (run with DIFFTEST_VARARGS_REF=1).
4. game_16DC80.c's #define hack for func_1513D524 stays until the browser merge changes functions.h.

## State (session P132, 2026-10-23). Details: `docs/port/sessions/P132.md`

- difftest fixes (selftest 57 / 57): (1) varargs / unknown callees' stack arguments behind IDO division trap checks
  were never compared (the call-site scan stopped at `bnez; break 7`) - the real cause of P127's "ineffective poke"
  survivors; (2) DIFFTEST_POKE now wins over the ROM image in every trial (also with DIFFTEST_ROMDATA=1 and in
  rodata); precedence learned pointers > POKE > ROM image > random; (3) `[POKE unread]` from decoded loads (Unicorn's
  global read hook misses some loads). Old behaviour: DIFFTEST_TRAPSCAN_OLD / DIFFTEST_POKE_OLD / DIFFTEST_PREAD_OLD = 1.
- func_151DE100's 7 non-equivalent P127 survivors all killed (new gap setups, `p132/gende100.py`).
- New hand C (NM): func_151407D0 particle_emitter_spawn (game_16DC80; needs port-b's returning func_1513D524),
  func_1509D1EC / func_1509D338 / func_1509D49C (game_eu_CA630; load-game save-route producers of func_151DFD0C),
  func_151E0BBC menu_mode_select_page (main menu page 0).
- Checks: verify_all OK, NM links, protocheck 0 (977), selftest 57/57, progress_nm 4971/5915 (84.0%), bytes 60.2%.

## Next steps (from P132)

0. Web: merge together with port-b's P128 game_169510.c (func_1513D524 returns the record; func_151407D0 uses it).
   func_1515AEE4 (game_eu_186A80) on the new-game frame is port-b's.
1. func_151DFD0C (title page 2; its producers D338 / D464 / D49C are now C), then func_151E1308, func_151E4B40,
   func_151E1EDC (same alpha / pending-page head as func_151E0BBC).
2. func_151E19AC mutants; the 68 errored func_151E3AE4 setups.
3. Varargs printers verified before P132 had their stack args unchecked when a division preceded the call: re-run
   mutants of such functions if one matters.

## State (session P127, 2026-10-23). Details: `docs/port/sessions/P127.md`

- P124 gap closed: func_15029EA8 t6 / ta setups EQUIV with ARGMEM on the func_1000FA64 record (allocate_memory key
  10003E90 was right; the "never called" notes came from setups that return early), mutants 27 / 28 (1 equivalent).
  func_15023988 / func_1000FA64 / func_15188D80 setups + mutants done (only equivalent survivors).
- New hand C (NM): func_151E2B9C settings_save, func_151E2FCC menu_game_start, func_151DE100 game_pause_update
  (mode-0 handler, browser P126 blocker), func_150113E0 level_fire_emitters_create (game_3E890); func_151E86A4's
  NM body skips the anti-tamper code checksum (no null-zone write in the port).
- NM prototype fixes from P125: func_150A6C40 void, func_15179008 prototypes. func_1513D524 header change deferred
  to the merge with port-b (its definition is in game_169510.c).

## Next steps (from P127)

0. Web: merge; drop func_151DE100's data stub (port/ side). Watch the pause menu's "no" path (cartridge check DMA,
   P127.md) and func_151407D0 (game_16DC80, asm) on the new-game frame.
1. func_1513D524 `void *` in functions.h under NM together with port-b's game_169510.c change.
2. Menu pages still asm: func_151DFD0C, func_151E0BBC, func_151E1308, func_151E1EDC, func_151E4B40 (P120 drafts in
   port_work/p120/gen, raw); func_151E19AC mutants; 68 func_151E3AE4 setups.
3. func_10024190 (osWritebackDCache, hand asm cache loop): port no-op, keep as is.

## State (session P124, 2026-10-23). Details: `docs/port/sessions/P124.md`

- **m2c scattered stack structs fixed (NM, commit 1efdab2)**: func_1510AEB0 (the P121 frame-1985 trap), func_150B7700,
  func_150B7DFC, func_1519961C, func_151ABE04, func_150D4FF0, func_15103310, func_1519E6BC: one struct / 2-element
  arrays; ARGMEM on the passed memory: old bodies DIFFER, new EQUIV, mutants. func_15169ED8 returns its record (NM).
  Scanner `p124/spaddr_scan.py` (+ triage tsv).
- **Scene handler C chain (NM)**: func_15029EA8 scene_event_run_c with func_15023988 (sound callback),
  func_15023EC4 (event lookup around now), func_1000FA64 (positional sound start), func_15188D80 (trail start).
  Setups: 29EA8 444 EQUIV, EC4 168 EQUIV (mutants 5/8); 23988 / FA64 / 188D80 random EQUIV only. **UNVERIFIED**: types
  6 / 0xA record path (wrong allocate_memory key in the setups) - see P124.md. Checks: verify_all OK, NM links,
  protocheck 0 (968), selftest 51/51, progress_nm 4962/5915 (83.9%), bytes 59.9%.
- Menu pages (task 2) and the 19AC / 3AE4 re-runs (task 3) NOT started (budget went to the coordinator's re-priority).

## Next steps (from P124)

0. Web: merge; the title menu should fade in (5/0x01 -> func_1517F3B0 from handler C); level 0x21 sounds start.
1. Menu pages: func_151DFD0C, func_151E0BBC, func_151E1308, func_151E1EDC, func_151E4B40, func_151E2B9C, func_151E2FCC,
   func_15042E3C (smallest / producers first). 19AC mutants, 68 3AE4 setups (P120 lists).
2. Remaining handler-C callee still asm: func_15060F28 (game_83300, C on port-b; replay path of 5/4 only).

## State (session P120, 2026-10-23). Details: `docs/port/sessions/P120.md`, map `docs/port/sessions/p120/carousel_map.md`

- **Menu camera / carousel func_151E73C8 (menu_camera_update) in hand C (NM)**: writes rec->fade / x2B / titlePage /
  menu, so the menu pages can now run. 620 / 626 setups EQUIV, mutants 51 killed (survivors equivalent).
- func_151E3AE4 settings_list_draw (553 setups EQUIV, 68 not run), main pages func_151E1174 main_settings_page and
  func_151E19AC main_players_page (mutants of 19AC not done).
- func_15042D94 varargs prototype under NM (game_eu_216470); func_151EE704 `| 0x80000000` dropped (P121);
  func_1517FD84 declared void (game_A9D90). difftest `DIFFTEST_VARARGS_REF=1`.
- Checks: verify_all OK, NM links, protocheck 0 (963), selftest 51/51, progress_nm 4957/5915 (83.8%), bytes 59.6%.

## Next steps (from P120)

0. Web: merge; mode 3 should now slide / zoom (left / right / accept / back) and show pages 1, 3..5, main pages 2, 3, 5.
1. **func_1510AEB0 (game_eu_1386C0, P121 request)**: rewrite with one struct (layout of S59A0 in game_eu_1231B0),
   difftest with ARGMEM on the passed struct. Not started.
2. Re-run the 19AC mutants (`p120/19ac_muts.txt`, DIFFTEST_VARARGS_REF=1) and the 68 ERROR setups of 3AE4.
3. Remaining menu: func_151DFD0C (title page 2, 625), func_151E0BBC (366), func_151E1308 (425), func_151E1EDC (720),
   func_151E4B40 (511); func_151E2B9C (settings save) and func_151E2FCC (start callback); func_15042E3C text printer.
4. P117 leftovers: func_151DEDD0 / page-1 mutants not run.

## State (session P117, 2026-10-23). Details: `docs/port/sessions/P117.md`, map `docs/port/sessions/p117/menu_map.md`

- **P116 / P118 browser bugs fixed in P15 m2c NM bodies**: func_1502457C (scene event walker: track pointer stride x4,
  slot offset x4, the D_800C39D0 / 39D8 / 3A60 reads at 16-byte stride, D_800C39E0 word store -> `sb`; 48 setups EQUIV,
  old body DIFFERs), func_150337A8 (`lb` compares for 0xF2), func_150623F4 (byte loop, object step, 0x40-byte stride).
- **Mode 3 menu in hand C (NM)**: func_151DEDD0 menu_mode_update (225 setups EQUIV), func_151EE704 menu_sprites_load,
  func_15007778 save_slots_reset, title pages func_151E06D0 title_slot_page (slots 3..5) and func_151DF6A4
  title_press_start_page (page 1). MenuState typedef for the record D_80090174.
- **No page runs until func_151E73C8 (asm, 1129, menu carousel object, called via func_1512A8D0) is C**: it is the only
  writer of rec->fade (>= 0.5 gates the pages), the carousel index and titlePage / menu.
- Event 0xC8: all 21 native-6 calls -> func_15097E9C (C on port-b with func_15097D20), cmds 0x3D / 0x54 / 0x14.
- Checks: verify_all OK (rc 0), NM links, protocheck 0 (959), selftest 51/51, progress_nm 4953/5915 (83.7%), bytes 59.1%.

## Next steps (from P117)

0. Web: merge; LogoScreen to t = 1700 with the walker fix (track 13: camera switch + 5/0x67 -> mode 3); func_150337A8 no
   longer runs off memory. Mode 3: frame-0 setup (sprites, slots), menu music, input; pages wait for func_151E73C8.
1. func_151E73C8 (game_eu_20B730, 1129): carousel producer of rec->fade / x2B / titlePage / menu. Then title drawing
   func_151E3AE4 (953), title page 2 func_151DFD0C (625), main-menu pages func_151E0BBC / 1EDC / 1174 / 1308 / 19AC /
   func_151E4B40.
2. game_eu_216470.c line 20 declares varargs func_15042D94 with 4 fixed args (non-NM, C callers): wasm signature check.
3. Remaining m2c_sanity rows in my files (web `docs/port/m2c_sanity.tsv`; the `(x*3)+&D_800AB7F4` pattern in 7 functions).
4. func_15029EA8 + chain (P114 item 2): not started.

## State (session P114, 2026-10-23). Details: `docs/port/sessions/P114.md`

- **func_15024910 (scene event handler A, scene_event_run_a) in hand C (NM)**: compiled C, not a VM: one 8-byte scene
  event per call (type switch, type-5 id switch). 293 synthetic + 154 real ROM event setups EQUIV, mutants 115/118
  (2 equivalent, 1 open). Fix from the setups: sub 0x3C uses w6 sign-extended.
- **Level 0x21 scene 1 reaches 5/0x67 at t = 1700 (= frame 1416, the scene end)** on track 13, together with
  `type 3 id 0xD` (camera track switch / retarget) and the 0x5C fade companions (`p114/scdis.py ROM 21 1`).
  Browser: the scene ended by its counter because A was a stub; re-run now.
- Producers for scene 1's type 0xD: func_15083F30 (object_spawn_attached, mutants 20/20) and func_150836CC
  (object_setup_undo, 9/9) in hand C (game_eu_AF2A0). func_151149AC verified but NOT committed (13DC30 -> port-b).
- Tools: `p114/scasset.py` (asset path loader), `p114/scdis.py` (scene disassembler, `--scan TYPE ID`).
- Checks: verify_all OK, NM links, protocheck 0 (954), selftest 51/51, progress_nm 4948/5915 (83.7%), bytes 58.9%.

## Next steps (from P114)

0. Web: merge; run LogoScreen to t = 1700: does 5/0x67 fire (func_151DECB4 -> mode 3, level 0x1D)? Does the type-3
   camera switch fix the stale camera target (P113 retarget guard)?
1. port-b: func_151149AC (28 insns, game_eu_13DC30) - candidate + setups + mutants ready in `p114/c/`, `9ac_*`.
2. func_15029EA8 (handler C, 827): map in `p114/scene_vm_map.md`; convert with func_1000FA64 (init_EB00),
   its callback func_15023988, func_15023EC4, func_15188D80 (producer / handler first).
3. func_150039E0 (P112 map), func_15084814 (AF2A0 removal chain): not started.

## State (session P112, 2026-10-23). Details: `docs/port/sessions/P112.md`

- **game_eu_CD540.c fully hand C (NM)**: func_1509FD30 (event_action_game_state, D_80088874[4]: 23 actions incl.
  the abort sites `func_150AE760(); return 0;`, attract idle check, mode 10) and func_150A02EC
  (event_query_game_state, D_80088838[4]: 20 queries). Random EQUIV + 65 / 45 knob setups EQUIV, mutants
  MUTFD30 / MUT02EC killed. Host whole-VM test (`p112/vmabort/`): stopping the running event ends the script after
  the native call, D_800D3858 cleared, result not stored; other events / pause go on.
- **difftest**: a `jalr` call of an unknown function now compares every arg register the reference wrote on its path
  since the previous call (P106's surviving a1 mutant in func_150AE5F8 / 60C now DIFFERs). `DIFFTEST_JALR_DYN=0`
  disables. Selftest 51/51 (new case func_150AE60C). DIFFTEST_REFLEN is in bytes.
- **Object removal producers** (coordinator re-order, browser P110 heap corruption at the logo scene end):
  func_150849C0 (object_release_models, game_eu_AF2A0) and func_15060D54 (object_forget_target, game_83300) in
  hand C (NM); setups EQUIV, mutants 8/10 (1 equivalent, 1 loop-bound gap) and 3/3. Their caller func_15060F28 is
  C on port-b / port-web only.
- **The real LogoScreen path**: event 0xC9 only does func_1509C850(1, 1) -> **func_1501D348(0x21, 1, 0, 0, 0)**
  (scene start; asm, 473 insns, game_eu_4A070 = port-b). None of the D_80088874 / D_800887C0 asm handlers is on it.
  The exit to the menu is the scene VM func_15024910 (asm, 2027, game_eu_51190) opcode 0x67 -> func_151DECB4.
- Checks: full verify_all OK (code build, check_files, full ROM byte-identical), NM links, protocheck 0 (951 bodies), selftest 51/51, progress_nm 4945/5915 (83.6%), bytes 58.5%.

## Next steps (from P112)

0. Web: merge, re-run the logo scene end (func_15060F28 -> the two new C functions); other still-asm callees of
   func_15060F28 were not re-listed here (stubcalls needs a port build; in the asm: func_1514D880, func_151695F0,
   func_150626EC, func_1504AF10, func_1503E550, func_10004074, func_1516972C, func_100043B4, func_10010AA8,
   func_150306D4, func_15189040, func_1505F188 - check them with stubcalls.py on port-web).
   Scene stubs in my files still asm: func_15083F30 (182, game_eu_AF2A0), func_15024910 / func_15029EA8
   (game_eu_51190), func_151149AC (28, game_eu_13DC30), func_150A4FE4 (295, game_eu_D1760), func_1513095C /
   func_1513100C (game_eu_15E000) - file owners to check.
1. **func_1501D348** (scene start; port-b's game_eu_4A070; runs on port-web already). Then the scene VM
   **func_15024910** (game_eu_51190, 2027 insns): check that level 0x21 scene 1 reaches opcode 0x67 (scene data
   reader still to write; evdis.py is for event blocks only).
2. Menu level 0x1D: event 0xC8 needs func_15097D20 (47) and func_15097E9C (2146), both in port-b's game_eu_C5530;
   mode 3 needs func_151DEDD0 + 8 page handlers in game_eu_20B730 (~3300 insns, map in P112.md), func_15007778
   (game_33990, 46), func_151EE704 (game_eu_216470, 142), and func_1501D348 again.
3. func_150039E0 (world objects, 741 insns, all callees C; map in P112.md).
4. Web: re-run level 0x21 after func_1501D348 is C; the event handlers 0x5xxx (func_1509FD30 / func_150A02EC) are C now.

## State (session P106, 2026-10-23). Details: `docs/port/sessions/P106.md`

- **Level event system committed as one unit** (NM hand C): func_1509CBD4 (prereqs), func_1509B950 (relocate),
  func_1509B5AC (start; `struct249 *`), func_1509B8FC returns func_1509B950(...), the event VM func_150ADFD0
  (hand-written asm -> readable C interpreter, now `void`), func_150AE760 (abort = flag EV_ABORTED in D_800D3858,
  checked after each native call) + func_150AE780 (ordinary function), the VM natives func_150AE5D8 / 5E8 / 5F8 / 60C /
  674 / 690 / 6A0 / 6BC / 6D4 / 714 (code inside the asm VM, separate C functions named by address), func_150ADA20.
  Verification: VM 258 synthetic + LogoScreen (0xC9) setups EQUIV, mutants 46/46; small functions setups + mutants;
  64-bit natives + func_150ADA20 model-checked (`p106/ada20/check.py`, mutants 11/12, 1 equivalent).
- difftest: `DIFFTEST_ROMDATA=1`, `DIFFTEST_MEMSTK=`, `DIFFTEST_SIGNORE=`; difftest.sh forwards DIFFTEST_REFLEN
  (it never did before). Selftest 49/49.
- Default build byte-identical (full verify_all), NM links, protocheck 0 (947 bodies), progress_nm 4941/5915 (83.5%),
  bytes 58.3%.

## Next steps (from P106)

0. Browser (web slot): D_80088A44 entries 3..12 point into the asm VM (0x150AE5D8 ...): check that n64mem.py's
   relocation maps them to the new C functions func_150AE5D8 ... (named by address). Then run level 0x21:
   LogoScreen entry 1 = push 1, push 0x1001, native 6 -> D_80088874[0] = func_1509C850(1, 1, args) (C).
   Asm-only handlers the VM can reach: D_800887C0 func_15097D20 / func_1509F4D0 / func_1509D590; D_800887FC
   func_15097DDC; D_80088838 func_1509A024 / func_150A09B8 / func_150A02EC; D_80088874 func_15097E9C,
   func_1509FD30 (port-b; must do `func_150AE760(); return 0;`), func_15097188, func_1509E3D4.
1. Open harness question: a1 of the unnamed indirect handler call in func_150AE5F8 / 60C is not compared (mutant
   survives; a1 is loaded in an earlier block). Fix difftest's argument count for jalr stubs + selftest case.
2. func_1517C11C (P104 draft), float re-check (P104 item 2; func_15075884 is now port-b), func_1512EE50 is port-b now.

## State (session P104, 2026-10-23). Details: `docs/port/sessions/P104.md`

- func_150000B0 (game_2D4B0, level music) in hand C (NM): random + 33 knob setups EQUIV, mutants 33/34 (1 equivalent). Music
  requests should now reach func_1000D96C in the browser.
- NOT committed (drafts only): the level event unit (func_1509CBD4 / func_1509B950 / func_1509B5AC random-EQUIV,
  func_150ADA20 not runnable in difftest, VM func_150ADFD0 + func_150AE760 mapped: hand-written asm with an
  sp-restoring abort), and func_1517C11C (1286 insns, random-EQUIV draft).
- Float re-check after P100's harness fix: 66 / 203 bodies run, 4 DIFFER + 2 UNSURE, not investigated.

## Next steps (from P104)

0. Level event system as one unit (browser P103 title-screen blocker): `docs/port/sessions/p104/event_vm_map.md`.
   Drafts in `p104/ev/` need knob setups + mutants; func_1509B8FC (NM) must return func_1509B950(...); the VM
   func_150ADFD0 needs a C interpreter design with a setjmp/longjmp (or flag) abort for func_150AE760's first 6
   instructions; func_150AE780 (the rest of AE760's asm) is an ordinary function.
1. func_1517C11C: `p104/draft_7c11c.c` + `p104/func_1517C11C_notes.md` (addresses, jal keys, setup plan). Commit with
   setups + mutants; make its NM prototype in game_eu_1A9280.c void. Producer func_1517BE0C (sort) is still asm.
2. Float re-check: finish the 137 bodies (`p104/hfrun.sh` on the unrun rows), investigate func_15075884
   (game_A28B0) and func_150E7104 (game_eu_114640); func_15123A54 / func_151247C0 are port-b (game_14FF90).
3. func_1512EE50 (camera eye, 1352 insns): not started.

## State (session P100, 2026-10-23). Details: `docs/port/sessions/P100.md`

- Frame-path stubs in hand C (NM): func_15141C0C (object type -> interaction category), func_15146EE0 (D_8008A084
  hook), func_1507E9A8 (apply animation entry), func_1512D900 (player tilt), func_1517E3CC (sound slot refresh),
  func_151DA6F8 (particle spawn wrapper). All EQUIV + knob setups; mutants 11/11, 12/12, 14/14, 15/15, 13/13, 24/24.
- Bug fixed in NM C: func_151D9B8C read the u8 table D_800AB710 as s32 at 4 * index (old body DIFFERs with ARGMEM).
- difftest: FP argument registers of callees with no TU declaration were never compared (the call statement was
  parsed as a prototype); now declarations only, falling back to include/**.h (sinf / cosf). New knob forms:
  OUTA / OUTB / OUTW `ADDR=@MEM:...` (absolute address), ARGMEM `ADDR=N+OFF:LEN`. Selftest 49/49.
- D_8008622C done hooks (func_15044D18): all four targets set a0 themselves; no argument needed (P98 item closed).
- protoasm_check: same 6 port-b rows. Default build byte-identical (full verify_all), NM links, protocheck 0.

## Next steps (from P100)

0. func_150000B0 (game_2D4B0, level music: the only blocker for music in the browser, P101): not started in P100.
   It is ~400 instructions, not small: level header D_800B0DF0 +0x2C..0x39 copied to a 14-byte block (or defaults
   when NULL), 5-case jump table on the mode byte, func_1000B548 fills 3 playing-song words (padded with -1), then
   up to two songs are matched / stopped / started via func_1000E46C / func_1000E40C / func_1000DF68 /
   func_1000DE1C / func_1000D96C and func_10017944(1, +0x6D). An old commented-out draft is in game_2D4B0.c line 27.
1. func_1512EE50 (camera eye height, 1352 instructions, 49 calls): dedicated session; m2c raw draft in
   `port_work/p100/raw/func_1512EE50.c` (700 lines, one goto) as a reading aid only.
2. func_1517C11C (asm-only, ~320 instructions): producer of the voice flags func_1517E3CC reads; until it is C every
   positional sound slot is switched off each frame.
3. Remaining P97 stubs (smallest first): func_1510CE28, func_1515929C, func_1510D090, func_1508F9F4, func_15113798,
   func_15184298, func_15178004, func_15113000, func_15188630, func_15181A6C, func_1517B270, func_1509093C,
   func_15129220. func_1505528C is in a port-b file (game_eu_78230).
4. Bodies verified before P100 that call header-only float functions may now show FPR diffs: re-run if touched.

## State (session P98, 2026-10-23). Details: `docs/port/sessions/P98.md`

- **Prototype vs. asm check** (`docs/port/sessions/p98/protoasm_check.py [--func F] [--why F] [--src D --inc D]`):
  every call from NM-selected C to an asm-only function, prototype in scope (o32 layout) vs. the callee's EU asm
  (f12/f14 vs a-registers, mtc1 / lwc1-reload = float bits, cvt.s.w = int, pass-through resolved, stack words,
  v0 / f0 at return). Rows FREG 4 / FLOAT 1 / INT 20 / ARITY 5 -> 0 / 0 / 3 / 3; the 6 left are port-b files
  (list in P98.md). RETNONE 17 is info. Output `docs/port/sessions/p98/protoasm.tsv`.
- Fixed (24 rows, 16 files, NM-only or `#ifdef NON_MATCHING`-wrapped): func_15152A90 (sp+0x20 block, u8),
  func_15133E04 (object, not f32), func_15086508 (7 args, z in a2), func_151BEE00 arg1 f32 (functions.h NM),
  func_150E6550 / func_151C64F4 / func_15081A90 / func_15142600 / func_15081120 / func_151848D8 float args,
  func_15185360 f32 out-params, func_15155B1C dropped a2/a3, func_10012560 callback forwards a1/a2 to func_15043BB8.
- Frame-path stubs in hand C (NM): func_15044D18 (timed effect list), func_15097BA8 (player push-back),
  func_15185360 (aim distance gate). EQUIV + knob setups; mutants 9/12, 9/9, 9/9.
- difftest selftest case func_150268BC.c updated for the func_151BEE00 f32 prototype (43/43).
- Default build byte-identical (full verify_all), NM links, protocheck 0 (934 bodies), progress_nm 4928/5915 (83.3%),
  bytes 58.0%, 987 asm-only.

## Next steps (from P98)

1. port-b: the 6 checker rows in its files (game_14FF90 func_151221F0 arg1 f32; game_83300 func_15064668 arg2 /
   func_15065E18 arg3 float bits; func_1512B2C4() / func_1501B300() / func_1501DF70() missing the a0 the asm reads).
2. Re-run `protoasm_check.py` after each merge (it needs `port_work/p98/asmonly.txt` = `progress_nm.py --list`;
   regenerate it first).
3. Frame-path stubs still asm (smallest first): func_1512D900, func_1517E3CC, func_151DA6F8, func_1510CE28,
   func_1510D090, func_1508F9F4, func_15113798, func_15184298, func_15178004, func_15113000, func_15188630,
   func_15181A6C, func_1517B270, func_1509093C, func_15129220, func_1512EE50; func_150ADA20.
4. Browser: func_15044D18 hooks (D_8008622C[] gets no a0), func_15097BA8 push-back, func_15185360 aim.

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
## P108 (port-b) (session P108, 2026-10-23). Details: `docs/port/sessions/P108.md`

Branch `port-b` (from P102 b2a5c1f); the orchestrator merges it into `port`.

- Default build byte-identical (verify_all rc 0, `port_work/p108/verify2.log`). `NON_MATCHING=1` links. protocheck:
  1 expected problem (func_15157580, gone after merging port; 930 bodies). **progress_nm**: total 4924/5915 (83.2%),
  game 4396/5334 (82.4%), C bytes 57.4%, 991 asm-only (142 under 60 insns).
- **Landed P102's pair** (commit 1b05b54): func_1507BB28 (game_A28B0.c, script producer) + func_15097E9C (object
  command handler). game_A28B0.c's census lvalue cast left alone (P107 fixed it port-side).
- **Trail particle chain in C** (game_eu_175B20.c): func_15148428 (step), func_151485AC (draw), and the sub-handlers
  they reach from func_151DA6F8 trails: func_15148E34 (grow), func_15149114 (fall + hit), func_15149350 (shrink).
  All setups EQUIV + mutants killed (P108.md section 2). **The P105 guard on func_151DA6F8 can be dropped.**
- func_1505D024 (game_83300.c, hit message, used by func_15097E9C) in C, 12/12.
- New rule applied: every converted function has a `// snake_case_name: ...` first comment line.

## Next steps (from P108)

1. Browser: drop the P105 guard; check trails (P108.md UNVERIFIED) and the object command scripts.
2. Particle type tables still have asm entries for other kinds (list in P108.md section 2, none in port-b files);
   trail hit handler func_150B3CA8 (game_eu_E0430.c) is asm.
3. Smallest asm-only left in port-b files: func_15144CEC (101), func_1505327C (109), func_15053430 (113),
   func_15060D54 (117).

## P102 (port-b) (session P102, 2026-10-23). Details: `docs/port/sessions/P102.md`

Branch `port-b` (from P96 66dffbc); the orchestrator merges it into `port`.

- Default build byte-identical (verify_all). `NON_MATCHING=1` links. protocheck: 1 expected problem
  (func_15157580, gone after merging port). **progress_nm**: total 4916/5915 (83.1%), game 4388/5334 (82.3%),
  C bytes 56.8%, 999 asm-only.
- P98 rows done: func_1506045C arg3 / func_15064668 arg2 / func_15065E18 arg3 are f32 (NM, all callers NM).
- **func_15097E9C (object command handler, 142 cases): verified but NOT committed.** Draft
  `sessions/p102/func_15097E9C.c`, map `func_15097E9C_map.md`, 1471 setups EQUIV, mutants 85/87 + 2 equivalent.
  Blocked by its producer **func_1507BB28** (game_A28B0.c, asm, stub returns 0 -> object +0x218 script pointer
  NULL for cmds 0x14 / 0x35 / 0x60). Verified draft `sessions/p102/func_1507BB28.c` (7/7). Commit both together.
- New hand-written NM C: func_1512BAAC (producer for func_1512B2C4), func_1512BBA0, func_1505D5D0, func_151406AC,
  func_1505DDA8, func_1501DF70 (all mutants killed).

## Next steps (from P102)

1. Whoever owns game_A28B0.c: `insert_nm.py func_1507BB28 docs/port/sessions/p102/func_1507BB28.c` and, in the
   same commit, `insert_nm.py func_15097E9C docs/port/sessions/p102/func_15097E9C.c` (port-b file
   game_eu_C5530.c); then browser check of script commands.
2. Browser: P102.md UNVERIFIED list.
3. Smallest asm-only left in port-b files: func_15144CEC (101), func_1505D024 (104, used by func_15097E9C),
   func_1505327C (109), func_15053430 (113), func_15060D54 (117).

## P96 (port-b) (session P96, 2026-10-23). Details: `docs/port/sessions/P96.md`

Branch `port-b` (from P92 99d4923); the orchestrator merges it into `port`.

- Default build byte-identical (verify_all). `NON_MATCHING=1` links. protocheck: 1 expected problem (func_15157580 f32 in
  game_eu_1EC610.c vs port-b's old s32 definition; gone after merging port). **progress_nm**: total 4910/5915 (83.0%),
  game 4382/5334 (82.2%), C bytes 56.7%, 1005 asm-only.
- **func_15124C38 "survivors" resolved: 39/39 killed.** `&0xF -> &7` was a harness race: two `p82/mut.sh` jobs of
  one function share `port_work/p82_mut_FUNC.c` / `build/difftest_p73m_FUNC`. Use **`docs/port/sessions/p96/mut.sh`**
  (per-run paths). The other 4 were setup holes (no setup reached the paths; `4c38c.txt` was a copy of 4c38b with
  out != NULL); `p96/gen4c38t.py` kills them.
- New hand-written NM C: **func_15020920** (segment cubic + length table, the producer the browser P97 needs;
  25/26 + 1 equivalent), func_1501E0C8 (cutscene skip, 16/16), func_1512B2C4 (free camera, 23/23 + 2 equivalent),
  **func_15126378** (aim mode, 1130 asm lines, 61/61 + 1 equivalent).
- func_15020090 / func_15020430 were already NM C here (P87); func_15157580 arg 3 f32 in game_eu_1EC610.c's NM
  block; func_151221F0 arg1 f32 (P98 protoasm).
- Harness hole for P95: callee FP args are compared only with a prototype in the TU text (sinf / cosf from
  libc/math.h were not); workaround: declare them in the TU.

## Next steps (from P96)

1. Browser: drop the FD34 / FF10 guard (func_15020920 is C); scene path, aim mode, free camera (P96.md UNVERIFIED).
2. P98 protoasm rows left: game_83300 func_15064668 arg2 / func_15065E18 arg3 (float bits as s32).
3. func_1512EE50 (eye height?) is in game_eu_15C660.c (not port-b). Frame-path stubs in port-b files: func_15097E9C (game_eu_C5530.c, 2146 lines, 678 calls/boot).

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
