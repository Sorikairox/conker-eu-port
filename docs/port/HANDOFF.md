# Port hand-off (branch `port`, worktree `~/conker-wt/port`)

Read `docs/port/PLAN.md` first: the phases, the browser-first target (wasm32/Emscripten) and the
risks. The decomp rules in `tools/eu_port/AGENT_BRIEF.md` and `HANDOFF.md` still apply: worktree
env, `verify_all.sh` before every commit, background jobs, the commit trailer.

```sh
cd ~/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"   # CONKER_ROOT, CONKERDEV=conkerdev-port
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
docker exec conkerdev-port python3 -c 'import unicorn'            # if missing: pip3 install --break-system-packages unicorn
```

## State (session P240, 2026-10-24, port-web). Details: `docs/port/sessions/P240.md`

- Merged port a64ed49e and port-b b798adaf. Checks after each: verify_all OK, NM build OK, protocheck 0 (1517),
  floatint 0, implicit NM+float 0, romabs 0 FAIL, arity / m2c ran; clean rebuild census 722 TUs 0 FAIL; selftest
  108 / 0. HANDOFF: 59 exact duplicate blocks from older merge_union runs removed (`docs/port/sessions/p240/hodedup.py`).
- Total War: null zone clean, store watch on [0x24, 0x28) silent for 7269 frames (func_151603FC fix holds); stubs:
  2 boot only.
- Story route chR3: level 0x29 scene 5 at 33659 as P236; func_15175900 gone; stubs 2 boot + func_151D8280 (204F70).
- Save / load: route EEPROM (`?eepdump=1`) booted with `?eephex=`: save select shows GAME1 0:09:52, PLAY loads level
  0x29 (func_15006BEC pack and func_15006590 unpack agree). New stub func_151EF3A0 (216470) on that screen.
- Race A: `?p240steer=8100[:LOOK[:PCT]]` (with `&p205rec=1`) drives 3 full laps (HUD LAP 2/3, 3/3 shots); the CPU
  (C func_1508CF34) still finishes first, so STATS shows the player's total as --:--:--. Ripples (func_151B61A0) not
  reached in any route (`?p240rip` counter).

## Next steps (from P240)
1. port: stub func_151EF3A0 (game_eu_216470, save-select slot draw); stub func_151D8280 (204F70, level 6 entry).
2. port-b: func_15196438 D_8008FC30 arity row.
3. port-web: Race A win (avoid the node 14 / 15 lava; tune PCT), then STATS with a total time; ripple route
   (object break over water); river crossing on level 0x29.

## State (session P237, 2026-10-24). Details: `docs/port/sessions/P237.md`
- Hand C (NM, one block each, all in the registry with setups + mutants): Total War stubs func_1508C600
  `rail_pair_sight` (B7840; racer line-of-sight masks rail +0x16C0, 18 setups, 32 / 32) and func_151EA4C8
  `mp_team_score_draw` (216470; two-team score panel, returns the DL end, 13 setups, 30 / 30); D_8008B0F0 light
  handlers func_15160E30 `light_beam_update` (18D770, 16 setups, 29 / 29) and func_151B99B8 `searchlight_light_update`
  (1E6B70, 5 setups, 17 / 17; the beam pointer is re-read per store as in the asm); func_15109390 was already C.
  Breadth: func_150C7E68 `obj_shade_from_level` (F5580), func_151600E0 `effect_noop_check` (18D5D0),
  func_150F1B78 `fx_hit_handler` (11CB90).
- Checks: NM build rc 0, protocheck `1470 NON_MATCHING bodies checked, 0 problems`, implicit_scan `663 TUs, 852
  implicit call sites (159 in NM code, 1 float-related, 0 NM+float)`, progress_nm `total 5915 3994 1488 433 5482
  92.7% 1827484/2253856 (81.1%)`, verify_all rc 0 (3994 / 5915 matched), selftest 100 / 100.

## Next steps (from P237)
1. port-web: Total War (func_1508C600 / func_151EA4C8), beam lights and the searchlight (func_15160E30 /
   func_151B99B8); frame-19116 freeze review of the P232 functions is still not done here (no message received).
2. Breadth in port's files (P237.md section 6): func_150C1B60 (asm caller only), func_150A7BD0, func_150FD49C,
   func_151016C8 / func_15101610.
3. D_8008FFE8 one-argument table (P234 item 2, port-b's entries) still open.

## State (session P236, 2026-10-24, port-web). Details: `docs/port/sessions/P236.md`

- **Frame-19116 freeze fixed (port-side, not game C):** the port's own `osContInit` (port/ultra/pc_pif.c) skipped
  libultra's `osCreateMesgQueue(&__osEepromTimerQ = D_80042E08, &D_80042E20, 1)`. The zeroed queue dropped the
  osEepromLongWrite timer messages, so the first long write (P232's C func_15006BEC save_slot_pack at the level-6 entry)
  never progressed, and the next save blocked for good in func_151DD4A0's `while (func_151DD588(1))` (OS_MESG_BLOCK
  on the empty queue). osContInit now creates the queue once. Not a workaround; func_15006BEC is fine.
- chR3 route (Chrome 730 s): saves progress (2 .. 30 block writes), level 0x29 scene 5 at 33659, 5002 started; item 4
  pickup -> q 0xAA = 4 (32091 / 33659) -> 0 after scene 5. Traps 0, heap 0, null zone 0. Stubs: 2 boot +
  func_151D8280 (204F70, port) + func_15175900 (1A2970, port-b).
- Race A: `?p205goto` followed the CPU's record (D_800C3E78 = 1 in the look callback); new `?p205rec=N` picks record
  N - 1. Lap counter works at record level (`?p236race=1`: player record node count 36 / 68 -> lap 1 / 2 of 33-node
  laps), HUD LAP 2/3 not yet in a shot; the walking autopilot can't steer the board well (stuck near the start).
- Diagnostics: `?p236race=1` (rail records + nodes), `?p236rw=F` (player rail tracking per update),
  `--wrap=func_150877C0` (call counter, calls through).

## Next steps (from P236)
1. port: game_18D770.c func_151603FC arg0 (P233); stub func_151D8280 (204F70, now reached from C func_151D7EDC);
   Total War stubs func_1508C600, func_151EA4C8.
2. port-b: stub func_15175900 (1A2970, story route 19112); func_15196438 arity row.
3. port-web: hoverboard steering controller (stick x from heading error) for a full Race A with LAP 2/3 / 3/3 on the
   HUD; save / load check of the route's EEPROM (continue game); river crossing (P228 recorder).

## P235 (port-b) (session P235, 2026-10-24). Details: `docs/port/sessions/P235.md`

Branch `port-b`. **difftest job limiter** in `tools/port/difftest.sh` (port and web get it via merges): at most 2
difftest jobs per container (`DIFFTEST_SLOTS`, default 2, 0 = off); slots are lock dirs in the container's
`/tmp/difftest_slots` with the job's in-container PID, taken under flock; dead-PID slots are cleaned inside the
container; a third job waits (stderr notice; `DIFFTEST_SLOT_MAXWAIT=S` gives up with ERROR). Test
`tools/port/difftest/slots_test.sh` 5 / 5; difftest.py untouched. Hand C (NM) + setups + mutants + registry rows:
**func_150FA520 object_point_burst_spawn**, **func_150F9BB0 object_aura_spawn** (127840), **func_151356D4
sprite_splash_spawn** (161520), **func_151BDDD8 object_aura_burst_spawn** (1E7CC0). **reverify fix**: line-numbered
mutants were applied one line off (nmblock dropped the `#ifdef NON_MATCHING` line); nmblock `NMBLOCK_WHOLE=1`, used by
reverify by default; matching-C functions without .s (func_151D52B4) re-check fine. Coordinator item: D_8008FC30's only
entry func_151991D0 sets a0..a3 itself - the 0-argument call in func_15196438 is right (comment added). Checks:
verify_all rc 0 (byte-identical), NM build rc 0, protocheck 0 (1484), selftest 103 / 103. progress_nm: game 4942 / 5334,
total 5478 / 5915 (92.6%), C bytes 82.1%, 437 asm-only.

## Next steps (from P235)

1. **D_8008FFE8 (game_1FFF60, now port-b's; coordinator / port P234)**: entries [0] func_151901F4, [1] func_1518FD34
   s32(s32), [2] func_1518FE0C void(s32), [3] func_151D33B8 (EU 151D3968) void(struct224 *), [4] func_1518FDC8 void(u8 *);
   dispatchers func_151D2C40 / func_151D3130 (matched C) pass two arguments through `void (*)(child *, void *)`.
   func_151901F4 does read its second argument (the target position, P231: its NM body aims at it), so the table
   can't be one-argument for all entries: give it the wasm-safe common signature under NON_MATCHING (e.g.
   `s32 (*)(void *, void *)`), NM wrappers / adjusted prototypes for the one-argument entries, and decide
   func_1518FD34's return with v0use over the dispatchers first. Not started (budget).
2. Browser: func_150FA520 / func_150F9BB0 (game_981E0 menu effect handlers), func_151356D4 (51190 event sprite
   splash), func_151BDDD8 (5D910 aura burst).
3. port (game_981E0, functions.h): func_150FA520 / func_150F9BB0 are called with no prototype (implicit int) but are
   now `void (u8 *, u8, u8, s32)` / `void (u8 *, u8, s32)`: a wasm signature mismatch unless declared; add prototypes.
4. C-caller candidates left: func_15135DD0 (397, 161520), func_15139768 (387, 161520), func_150D3870 (450, 101080),
   func_151F94E0 (960, 226870); the 4 Rare hand-asm functions of game_eu_226870 (not started).
5. difftest (port's difftest.py): ARGMEM has one length per callee, so memcpy blocks of different sizes in one function
   can't all be compared; a per-call length (or `N+OFF:LEN@callindex`) would help.

## State (session P234, 2026-10-24). Details: `docs/port/sessions/P234.md`
- Harness: difftest now takes callee prototypes from the headers the TU includes (recursive, Makefile include dirs)
  when the TU text has no declaration: a callee declared only in functions.h (func_150ADA20) no longer has IDO's
  scratch f12 compared as an argument. `DIFFTEST_INCHDR_OLD=1` = old (forwarded by difftest.sh). Selftest 95 / 95
  before, 100 / 100 after (new func_15109DC8 cases; the P134 func_150F1F80 case now needs HDRSLOT_OLD + INCHDR_OLD).
- progress_nm: conditional-stack block detection (`--old` = old regex). 18 functions with C in the NM build were
  counted asm-only (func_150E394C, D2DB0 / D3880 / D1760 / AC770 / 45B90 / 48B10 / init_EB00 / 1FB080 pieces; list in
  P234.md). Corrected before this session's conversions: `total 5915 3994 1479 442 5473 92.5% 1819332/2253856 (80.7%)`.
- Hand C (NM, one block each), in the registry: func_1508CF34 `rail_racer_steer` (B7840 rail cmd 9 / AI steering,
  862 insns; exact v0 = yaw error beyond 45 degrees; 60 setups, 90 / 90), func_151B61A0 `ripple_spawn_flat` (1E39B0,
  coordinator item: the ripple model func_1513783C picks half the time; anti-tamper code sum skipped in NM; 39 / 39).
- Checks: verify_all rc 0 (code build / check_files / full ROM OK, 3994 / 5915 matched), NM build rc 0, protocheck
  `1463 NON_MATCHING bodies checked, 0 problems`, selftest 100 / 100, implicit_scan `663 TUs, 852 implicit call sites
  (159 in NM code, 1 float-related, 0 NM+float)`, progress_nm `total 5915 3994 1481 440 5475 92.6% 1823456/2253856 (80.9%)`.
- Urgent port fix (coordinator, Total War null+0x24): D_8008B0F0 (EU D_8008B490) handlers now get the effect: NM
  table type `s32 (*[])(struct225 *)` in variables.h, NM block of func_151603FC passes arg0, NM func_15161F2C returns
  func_15163F50's s32 (the dispatcher tests it). Both difftest EQUIV, NULL / return-0 mutants DIFFER (P234.md section 8).
- zsh note: `env $K cmd` does not split $K in the agent shell; use `${=K}` (or bash) for hand-run knob strings.

## Next steps (from P234)
1. port-web: Total War null+0x24 should be gone (D_8008B0F0 handlers get the effect); AI racers on rail levels
   (func_1508CF34), water ripples (func_151B61A0).
1b. Not done: NM C for Total War stubs func_1508C600 (B7840), func_151EA4C8 (216470); review P232 functions
   (func_15006BEC, func_151D7EDC -> stub func_151D8280, func_15109DC8, func_1510A538) for the frame-19116 freeze.
2. D_8008FFE8 (game_1FFF60) table: all 5 EU entries take one argument ([0] func_151901F4 asm, [1] func_1518FD34
   `s32 (s32)`, [2] func_1518FE0C, [3] func_151D33B8, [4] func_1518FDC8), the declaration and the two matched C
   dispatchers pass two. Entries 0/1/2/4 are port-b's (1BAF40): coordinate an NM one-argument table type + NM copies of
   func_151D2C40 / func_151D3130, and func_1518FD34's return type (v0use first).
3. Breadth from `progress_nm.py --list` (not started in P234).
4. port-b: func_151D52B4 float argument (same fix as func_150AFBC4).

## State (session P233, 2026-10-24, port-web). Details: `docs/port/sessions/P233.md`

- Merged port 690c3153 (P227 / P230), port-b 2428c7cb (P225 / P229), port 05b91168 (P232). After each: verify_all OK,
  NM link OK, protocheck 0 (1501 at the end), float-int 0, implicit_scan NM+float 0, romabs_check 0 FAIL; census 722 ok /
  0 FAIL (clean rebuilds); arity_scan 142 rows (+3 port-b func_15196438), m2c_sanity 299. Selftest 103 / 103.
- **`port/tools/romabs_check.py`** (standing check; run by port/Makefile after vbe_build.py and by checks.sh): every
  `D_<hex>` link symbol < 0x10000000 used by NM C must be in vbe.py `ROM_ABS` (a number) or the new **`RAM_ALIAS`**
  (physical address of RAM data). Found D_89810 -> fixed: `RAM_ALIAS = {'D_89810': 'D_80089810'}` (shadow pass
  identity view matrix in game_eu_1B1ED0.c, was a zero data stub). D_2D810 is a reviewed ROM offset (REVIEWED_ABS).
- **Difftest in a new worktree needs `port_work/pyuc201`** (pinned Unicorn 2.0.1, gitignored): without it the
  container's 2.1.4 runs silently and calls next to FPU delay slots fault at pc 0 (that was the web 44 / 95). Installed
  for web; selftest.sh now refuses to run without it.
  `docker exec $CONKERDEV pip3 install --target /conker/port_work/pyuc201 unicorn==2.0.1.post1`.
- **Race A**: CPU racer drives (rail AI C), HUD complete; match end -> STATS (RESTART / QUIT) -> back to the RACE barrel
  menu; only the 2 boot stubs. Laps still UNVERIFIED (frame script dies in the lava, LAP 1/3).
- **Total War null+0x24 writer**: store watch (p233/watch.sh) -> func_15163DEC / func_15160954 called through
  `D_8008B0F0[arg0->unkF]()` in **game_18D770.c:106 func_151603FC with arg0 dropped** (asm keeps a0 = arg0; variables.h:444
  declares the table `(void)`). Game-C fix for port. Total War stubs: func_1508C600 (B7840), func_151EA4C8 (216470).
- **Level 0x29 route REGRESSION**: chR3 run freezes at frame 19116 (`func_1501D348(level 18, scene 2)`, no more
  retraces, no trap) after the 05b91168 merge; P228 went on from the same point. Suspects: P232's func_15006BEC
  save_slot_pack (new EEPROM save at level 6 entry), func_151D7EDC (+ stub func_151D8280), func_15109DC8 / func_1510A538.

## Next steps (from P233)
0. port / port-web: bisect the frame-19116 freeze (build 690c3153+2428c7cb vs 05b91168; chR3 frame script to ~19300).
1. port: game_18D770.c func_151603FC pass arg0 to D_8008B0F0 handlers (+ variables.h:444 prototype); then Total War
   stubs func_1508C600, func_151EA4C8.
2. port-b: func_15196438's D_8008FC30 call (arity row, a0..a3 live in the asm).
3. port-web: re-run the store watch after fix 1 (`SW_EXCL= p233/watch.sh inst; p233/watch.sh run war 200 LOG`);
   Race A laps with a steering frame script; river crossing from a human recording (P228 record.sh).
## State (session P232, 2026-10-24). Details: `docs/port/sessions/P232.md`
- Hand C (NM, one block each), all in the registry: func_151E533C `mp_match_end_continue` (20B730; coordinator
  priority: the D_800E0EB8 fade callback after a multiplayer match: next level / replay / back to the menu; 32/32),
  func_15073FA0 `event_spawn_helper_object` (981E0; last asm callee of the B-pad function; 74/74),
  func_151D7EDC `trail_points_update` (204F70, level 6; 22/22), func_15109DC8 `spark_burst_spawn` (1371A0, D_80089004
  handler 0; 58/58), func_1510A538 `segment_effect_update` (1379B0, effect 0x1B; 21/21), func_151922C4
  `obj_dust_effect_update` (1BF960, effect 0x1D; 34/34), func_15006BEC `save_slot_pack` (33990, EEPROM save writer;
  now `void (s32)`; 46/46).
- No `D_<small hex>` link symbols in the new C (nothing for port-web's ROM_ABS table).
- difftest tip: a callee declared only in a header has no TU prototype, so IDO's scratch f12 before a `void`-arg call
  (func_150ADA20) is compared as an argument: declare such callees in the NM block.
- Checks: verify_all rc 0 (3994 / 5915 matched), NM build rc 0, protocheck `1461 NON_MATCHING bodies checked, 0
  problems`, selftest 95 / 95, implicit_scan 852 sites / 159 NM / 1 float / 0 NM+float, progress_nm
  `total 5915 3994 1461 460 5455 92.2% 1811392/2253856 (80.4%)`.

## Next steps (from P232)
1. port-web: Race A end of match (func_151E533C: black screen after the wipe should be gone), save writing
   (func_15006BEC vs func_15006590), level 6 trail (func_151D7EDC), object dust / segment sparks.
2. func_1508CF34 (B7840 rail cmd 9, 862 insns, exact v0 for func_1508AB7C): not started.
3. Breadth from `progress_nm.py --list` (func_150E394C is listed as asm-only although game_eu_110DB0 has its NM body:
   check the block detection).
4. port-b: func_151D52B4 float argument (same fix as func_150AFBC4).

## P231 (port-b) (session P231, 2026-10-24). Details: `docs/port/sessions/P231.md`

Branch `port-b`. Hand C (NM) + setups + mutants, registry rows with full knobs: **func_1519AF14 trail_update**
(1C3530; the "stale a1" quirk was a table mix-up: its D_8008FC48 is at 0x8008FC48 with three one-argument handlers
func_1519CEB8 / CEE0 / CF08; JALRSKIP=1,2,3), **func_15175900 leaf_field_spawn** (1A2970), **func_1513783C
object_break_effects** (161520; ripple via asm func_151B61A0 or C func_151B65C0 at random). Coordinator request:
**func_151D52B4** (201240) NM variant with the real `func_15131EC8(f32 *, f32)` prototype (P230 implicit_scan float
site). func_151901F4 (1BAF40): P219's PORT-only "aim at the node" fallback removed - D_8008FFE8's real callers
(game_1FFF60 C) pass the position. Checks: verify_all rc 0 (byte-identical), NM build rc 0, protocheck 0 (1480), selftest 103 / 103. progress_nm: game 4938 / 5334, total 5474 / 5915 (92.5%), C bytes 81.8%, 441 asm-only.

## Next steps (from P231)

1. Browser: trails (func_1519AF14), leaf fields (func_15175900), break debris / splash (func_1513783C), effect node
   launch target (func_151901F4 PORT change).
2. port-b C-caller candidates left: func_150FA520, func_151356D4, func_151BDDD8, func_150F9BB0, func_15135DD0,
   func_15139768, func_150D3870, func_151F94E0; the 4 Rare hand-asm functions of game_eu_226870 (not started).
3. port: game_1FFF60's D_8008FFE8 declared `void (*)(child *, void *)` but holds s32-returning / one-argument
   handlers (wasm call_indirect signature); func_151B61A0 (1E39B0) is an asm ripple handler behind func_1513783C.

## State (session P230, 2026-10-24). Details: `docs/port/sessions/P230.md`
- **Standing check: `tools/port/implicit_scan.py`** (`[--all] [--tsv OUT]`, ~9 s): host clang pass over src_eu with
  -DNON_MATCHING and only -Wimplicit-function-declaration (IDO is silent about implicit declarations). Lists
  implicit call sites, NM-only vs both builds, FLOAT flag (libm, by-value f32 prototype elsewhere, or asm callee
  reading $f12/$f14 / returning $f0). Run it after every conversion session; NM+float must stay 0.
  Now: 852 sites, 159 in NM code, 1 float (port-b 201240:588 func_151D52B4 -> func_15131EC8(f32 *, f32)).
- Fixed: func_150AFBC4 (DCEF0) NM variant passes the f32 to func_15131EC8 with a prototype; game_981E0 NM
  prototype `u8 *func_15196438(u8 *, s32, u8, s32)` (port-b P229 item). port-b list: `docs/port/sessions/p230/implicit_portb.tsv`.
- Hand C (NM, one block each), all in the registry: func_150130B4 `record_particle_emitter_start` (40490, 61/61),
  func_1508C07C `rail_lane_shuffle` (B7840, 18/18; void (void): func_1508A040's NM prototype / call fixed),
  func_1508CA14 `rail_pair_rivals` (B7840, 51/51; returns the +0x16C0 mask: func_1508BE18's NM prototype fixed),
  func_1508B854 `rail_events_assign_nodes` (B7840, 44/44), func_1000C530 `channel_effect_update` (init_B1B0, 47/47).
- Checks: verify_all rc 0 (3994 / 5915 matched), NM build rc 0, protocheck `1454 NON_MATCHING bodies checked, 0
  problems`, selftest 95 / 95, progress_nm `total 5915 3994 1454 467 5448 92.1% 1805128/2253856 (80.1%)`.
## Next steps (from P230)
1. port-web: MP / race rail AI (lanes, rival pairing, event nodes), record particle emitters, channel audio effects.
2. func_15073FA0 (981E0): sketched in P230.md section 5, not written. Then func_1508CF34 (B7840 cmd 9, 862 insns).
3. Pre-0x29 leftovers: func_151D7EDC (204F70), func_15109DC8 (1371A0), func_1510A538 (1379B0), func_151922C4
   (1BF960), func_15006BEC (33990).
4. port-b: func_151D52B4 float argument (same fix as func_150AFBC4).
## P229 (port-b) (session P229, 2026-10-24). Details: `docs/port/sessions/P229.md`

Branch `port-b`. Harness: a malformed `DIFFTEST_ARG` item (e.g. `A=7`) is an ERROR line instead of a traceback with
empty result lines (selftest cases `A=7` ERROR / `0=7` EQUIV, 103 / 103). `tools/eu_port/hoorder.py` added (copy of
p208's). Hand C (NM) + setups + mutants, registry rows with full knobs: **func_15196438 object_emitter_spawn**
(1C3530; returns the emitter; JALRSKIP=1,2,3 for the one-argument handler tables), **func_1516FAB8 spray_pair_spawn**
(19B180), **func_15170648 quad_edge_sparks_spawn** (19B180; constant 836.0), **func_150FB398 score_banner_spawn**
(127840; ARGMEM found two spec layout bugs that random trials missed), **func_15175160 leaf_burst_spawn** and
**func_15175514 leaf_drop_spawn** (1A2970; Row20 / D_800DE2B8 declarations moved to the file top). Checks: verify_all
rc 0, NM links, protocheck 0 (1477), selftest 103/103. progress_nm total 5471 / 5915 (92.5%), C bytes 81.6%, 444 asm-only.

## Next steps (from P229)

1. Browser: emitters (func_15196438, flame thrower kinds 5 / 6), scene-event sprays (func_1516FAB8), banner
   (func_150FB398), leaves (func_15175160 / func_15175514), quad edge sparks (func_15170648).
2. port-b's new files: C-caller candidates left: func_15175900 (370), func_1513783C, func_150FA520, func_151356D4,
   func_151BDDD8, func_150F9BB0, func_15135DD0, func_15139768, func_150D3870, func_1519AF14 (D_8008FC48 dispatcher),
   func_151F94E0; the 4 Rare hand-asm functions of game_eu_226870 (nmasm harness) are not started.
3. port: game_981E0 calls func_15196438 without a prototype (implicit int); `u8 *func_15196438(u8 *, s32, u8, s32)`.

## State (session P228, 2026-10-24, port-web). Details: `docs/port/sessions/P228.md`

- Merged port 956b59ed (P214 .. P226), then port-b 5ac75d1c (P220 / P222). After the first merge alone the NM build
  failed (game_eu_90F50.c local prototypes of func_150FC438 / func_150DC2F0 vs port's new C); port-b's P222 alignment
  fixes it. After both: verify_all OK, NM link OK, protocheck 0 (1474), float-int 0 bugs, census 0 FAIL (722 TUs, clean
  rebuild), arity_scan 137 rows unchanged, m2c_sanity 286 rows.
- **Barrel-menu trap fixed** (port/tools/vbe.py ROM_ABS += D_88C 0x88C, D_87B 0x87B): the new C barrel_menu_draw
  func_151ECE00 passes these link-symbol texture ids; as zero data stubs they were wasm addresses -> func_1510D66C range
  -> fatal func_150ADC50 + OOB trap in func_1510D984 at frame 4442. Rule: new C using `D_<small hex>` link symbols needs
  a ROM_ABS entry. Still open: `D_89810` (shadow view matrix in game_eu_1B1ED0.c) is a zero data stub; it should alias
  D_80089810 (identity matrix).
- **Race A**: Conker drives (about one lap), camera follows, deaths respawn with a fade (9 respawns, no black screen),
  lives 6 -> 4 -> out; match end at 12524 -> stub **func_151E533C** (20B730, port) -> black for good. Laps / rail camera
  still UNVERIFIED (LAP 1/3 only).
- **Total War**: player model visible, camera follows, player moves; null+0x24 write still at 6514 .. 6518 before stub
  func_1511E4F4 (142E40, port).
- **Level 0x29 regression OK**: chR3 route scenes 2 / 3 / 4 / 5 at the P223 retraces, 5002 at 33914, 0 stubs on 0x29.
- **?padrec=1 / ?padf F:P** (port/ultra/pc_pif.c): records a human route as a frame script; `p228/record.sh`.
- Difftest selftest in conkerdev-web: 51 ok / 44 failed (unicorn 2.1.4 installed this session; failing cases fault at
  pc 0 on the first callee, e.g. func_151B97C4): an environment problem of this container, not investigated; run
  selftests in the port / port-b containers.

### How to record the river crossing (for the user)
1. Make sure `conker-web-serve` runs (it serves `~/conker-wt/web/port/build/web` on http://localhost:8064). Use a
   fresh profile / private window (no saves: the script assumes a new game), keep the tab in front (a hidden tab pauses).
2. `docs/port/sessions/p228/record.sh url` prints the URL (add `&romurl=...` or load the ROM as usual). The autopilot
   plays the new game to scene 5 on level 0x29 (~11 minutes, retrace ~34000). At retrace 34200 (~685 s after boot)
   the pad is yours: keyboard WASD stick, Space A, F B, Q Z, Ctrl half tilt (or a gamepad).
3. Walk to the river and cross it (event 4 "Training - Jumping", zone 0x0F near (622, -142, -2674); P223 found the
   fence at z ~548 solid; the crossing is somewhere else: a gap, a log, a platform?). Go on as far as you like (the
   Baddie, event 6, is past the jumping area).
4. Open DevTools (Cmd-Opt-J) and run `copy(__padrec.join(','))`; paste into a file, e.g.
   `docs/port/sessions/p228/river_human.txt`.
5. Replay headless: `docs/port/sessions/p228/record.sh replay docs/port/sessions/p228/river_human.txt 1200`.
   Format: `F:BTN:X:Y` comma-separated, F = VI retrace, BTN = N64 button bits in hex (A 8000, B 4000, Z 2000,
   START 1000), X / Y stick -80..80 (y up). Only entries after 34200 are kept; the prefix is replayed by the autopilot.

## Next steps (from P228)
1. port: func_151E533C (MP match end / results), func_1511E4F4 (null+0x24 in Total War), func_151E9150,
   func_1509D590, func_150130B4, rail AI func_1508B854 / func_1508C07C / func_1508CA14, func_1000C530.
2. port-web: D_89810 alias (shadow view matrix); the river crossing from a human recording (above) or nav data;
   then events 4 / 6 / 1 on level 0x29; Race A lap counting once a lap completes (needs a frame script that stays on
   the track: steer, don't hold the stick straight up).
3. Check why difftest selftest fails in conkerdev-web (fault at pc 0 on the first callee).
## State (session P227, 2026-10-24). Details: `docs/port/sessions/P227.md`
- Tooling: `tools/port/reverify.sh` no longer cuts the mutant line (knob `MUTCUT=N`; P226's rvw.sh is obsolete).
- Hand C (NM, one block each), all in the registry: func_151E9150 `mp_hud_draw` (216470), func_151EA90C
  `mp_scoreboard_draw` (216470; barrel menu mode 3 bar / in-match score table), func_1509D590
  `event_effect_command` (CA630, D_800887C0 entry 14, EvHandlerA), func_1511E4F4 `pickup_update` (142E40,
  world-object type 0x28 callback D_80089030[0x28][0]; declares `f32 cosf(f32)` in its block: 142E40 had none).
- Verification: setups + mutants all killed (69/69, 68/68, 57/57, 53/53); random 100 EQUIV for all four.
- Total War null+0x24 = 7.58f (browser P223): func_1511E4F4 has no +0x24 store and returns nothing used, so its
  stub is only where the check fired; the write happened earlier in that frame. Its conversion is NOT expected to fix
  the write (pickups now scale in / animate / can be taken). Re-check in the browser after the merge; look at the
  code that runs before the world-object callbacks in that frame.
- Checks: verify_all rc 0 (code build / check_files / full ROM OK, 3994 / 5915 matched), NM build rc 0, protocheck
  `1449 NON_MATCHING bodies checked, 0 problems`, selftest 95 / 95, progress_nm
  `total 5915 3994 1449 472 5443 92.0% 1799532/2253856 (79.8%)`.

## Next steps (from P227)
1. port-web: Race A / Total War HUD and score table, pickups, null+0x24 re-check.
2. func_150130B4 (40490): analysed in P227.md section 6 (spawn / emitter blocks, 19-case jump table), not written.
3. Rail AI func_1508B854 / func_1508C07C / func_1508CA14 (B7840), func_1000C530 (init_B1B0), func_15073FA0 (981E0),
   func_1508CF34 (B7840 cmd 9). m2c drafts: `port_work/p226/gen/`.

## State (session P226, 2026-10-24). Details: `docs/port/sessions/P226.md`
- Hand C (NM, one block each), all in the registry: func_151E5E08 `mp_match_rules_update` (20B730; the match now
  ends: D_800E1050, placings D_800E0EF0), func_151ECE00 `barrel_menu_draw` (216470; returns the DL end),
  func_1509F4D0 `event_sound_command` (CC5F0, D_800887C0 entry 7), func_15086268 `rail_node_nearest` (B37F0).
  func_1509F9C8 (CC5F0, matching C `void`) has an NM variant returning func_10010F88's handle (func_1509F4D0
  kind 0x4000 returns it to the VM).
- Verification: setups + mutants all killed (50/50, 76/76, 31/31, 25/25); func_1509F4D0 random DIFFERs only at the
  u16-truncated argument of func_1509FBC8 (callee reads `lhu`, harness artefact).
- `port_work/p226/rvw.sh` = reverify.sh printing all survivors (reverify cuts at 600 characters); consider making
  the cut an env knob in tools/port/reverify.sh.
- Checks: verify_all rc 0, NM build rc 0, protocheck 0 (1445 bodies), selftest 95/95, progress_nm total 5439/5915 C (92.0%), C bytes 79.4%.

## Next steps (from P226)
1. func_151E9150 (216470 MP HUD, 819 insns), func_1509D590 (CA630), func_150130B4 (40490), func_1511E4F4 (142E40).
2. Rail AI group func_1508B854 / func_1508C07C / func_1508CA14 (B7840) - func_15086268 is done; func_1000C530
   (init_B1B0); then func_15073FA0 (981E0) and func_1508CF34 (B7840 cmd 9). m2c reading drafts: `port_work/p226/gen/`.
3. func_151EA90C (216470, barrel menu mode 3) is still asm.

## P225 (port-b) (session P225, 2026-10-24). Details: `docs/port/sessions/P225.md`

Branch `port-b`. **Ownership (new from P225): port-b also owns game_161520 (src and src_eu), game_eu_1C3530,
game_eu_19B180, game_eu_1FB080, game_eu_127840, game_eu_226870, game_eu_1E7CC0, game_eu_1A2970, game_eu_133A70,
game_eu_101080 and D5E90 (Rare hand asm).** Merged port d5b5126a (verify registry, BADJALR fix); 35 registry rows
added for port-b's P197-P222 conversions (DIFFTEST_ROMDATA=1 + the recorded ARGMEM / STKFILL; rows whose ARGMEM list
was never written down have ROMDATA only, listed in P225.md section 1). Port-b uses the registry from now on.
Harness: `nm_resolve` handles `#if` nested inside an NM block (DIFFTEST_NMNEST_OLD=1 = old; selftest case
func_15103828); a non-hex DIFFTEST_STKFILL is an ERROR line instead of empty output. Hand C (NM) + setups + mutants:
**func_15138120 object_hit_kind_effect_spawn** (161520; now s32 = the asm's leftover v0, as 1C1A20 declares it),
**func_15106260 bolt_arc_spawn**, **func_15107C80 object_arc_to_surface_spawn**, **func_1510819C
object_arc_from_point_spawn** (133A70), **func_15177360 prop_model_draw** (1A2970). Checks: verify_all rc 0, NM links,
protocheck 0 (1471), selftest 101/101. progress_nm total 5465 / 5915 (92.4%), C bytes 81.3%, 450 asm-only.

## Next steps (from P225)

1. Browser: hit effects (func_15138120), lightning arcs (func_15106260 / func_15107C80 / func_1510819C), prop models
   with fade (func_15177360).
2. New files: 68 compiled asm-only functions left (C-caller candidates listed in P225.md section 6), 4 Rare hand-asm
   functions in game_eu_226870 (func_151F9060 / 911C / 9184 / 933C: nmasm harness) and 29 in D5E90.
3. Fill in the missing ARGMEM knobs of the older registry rows when re-checking them (P225.md section 1).
4. difftest: a non-decimal DIFFTEST_ARG index (e.g. `A=7`) also gives empty result lines (seen in P225); make it an
   ERROR like STKFILL.

## State (session P224, 2026-10-24). Details: `docs/port/sessions/P224.md`

Branch `port` (P221 d5b5126a + P224 commit).
- Hand C (NM), multiplayer: func_1507D1D8 mp_player_respawn (A9D90; the respawn after a lost life), func_150528C8
  obj_hover_height_update (78230; board height / movement handler, state table D_800863B8: the likely cause of
  "Conker can't move in Race A"), func_151221F0 camera_follow_update (14FA00; the stub skipped the camera follow steps),
  func_15164E0C object_wobble_update (192500). Random + setups EQUIV, mutants 39/39, 46/46, 37/37, 30/30 (func_150528C8
  random DIFFERs only on an lh-vs-u16 argument the callee masks: artefact, see the session doc).
- D_8008A1BC draw-table entries (port-b P222 item) return their callee's v0 in NM (7 wrappers; NM-only prototypes
  in functions.h for func_1513EDB4 / func_1513F4B0).
- Triage of the MP start stubs in P224.md section 1. Ownership move to port-b (game_161520, 1C3530, 19B180, 1FB080,
  127840, 226870, 1E7CC0, 1A2970, 133A70, 101080, D5E90): no edits there in P224.
- Checks: verify_all rc 0 (code build / check_files / full ROM OK, 3994 / 5915 matched), NM build rc 0, protocheck `1441 NON_MATCHING bodies checked, 0 problems`, selftest 95 / 95, progress_nm `total 5915 3994 1441 480 5435 91.9% 1783192/2253856 (79.1%)`.

## Next steps (from P224)
1. port-web: browser re-run of Race A / Total War (movement, camera, first death / respawn).
2. func_151E5E08 (match rules, D_800E1050), func_151ECE00 (216470 DL passthru, 661 insns), func_151E9150,
   func_1509D590; then func_15073FA0, func_1508CF34.

## State (session P223, 2026-10-24, port-web). Details: `docs/port/sessions/P223.md`

- No merges, no game C. Level 0x29 script mapped from ROM (evdis / evtab): event 0 Scarecrow (ev 1128), 1 (ev 1090:
  zone 9 pad + item 0x28), 2 / 3 (ev 1074: held item 4 off zone 8 -> scene 5 / 14), 4 Jumping (zone 0x0F, across the
  river), 6 The Baddie (the only enemy, across the river).
- **Scene 5 reached**: after scene 4, B again on the pad -> item 4 -> event 2 fires: scene 5 33362 .. 33911, 5002 (event done),
  item consumed (hangover cure). No stub / trap / null-zone write on level 0x29 to 56000.
- Then stuck on the map: the river fence (z ~548) is solid even when jumping, and the autopilot gets stuck on the field
  fence going back west. The river crossing (platform, door on the hill) was not found.
- `?p223hit` (wrap of func_1505C1E4): B on Birdy lands every swing; rule `00 FF 86 08` -> D_8009A6D8[8] (xz 0, y 0,
  mask 0): no knock-back is what the ROM data asks for. Knock-back with speed still UNVERIFIED (enemy across the river).
- `docs/port/sessions/p223/mp.sh race|war`: one command into Race A (0x33 at 7447) / Total War (0x2D at 6546). Total
  War writes null+0x24 (7.58f) at 6526 .. 6530, before stub func_1511E4F4 (142E40).
- Never run two Chrome runs at once (the hidden tab pauses).

## Next steps (from P223)
1. port: func_1507D1D8 (MP respawn), MP start stubs (func_1511E4F4 first: null+0x24 write), func_15164E0C, func_151ECE00.
2. port-web: level 0x29 river crossing: better autopilot (steer by collision / nav data, or a recorded human frame script),
   then events 4 / 6 (enemy knock-back), event 1 (zone 9, item 0x28: carried object).
3. Open: does item 4 survive scene 4 on N64 (port needs a second B press)? Needs an N64 reference.

## P222 (port-b) (session P222, 2026-10-24). Details: `docs/port/sessions/P222.md`

Branch `port-b`. Hand C (NM), difftest setups (ARGMEM / STKFILL / RET sequences) + mutants, exact commands per
function in P222.md section 2: **func_1506401C object_find_held** (90F50, 145; mutants 14/14), **func_150C92B8
ring_effect_draw** (F6060, 767; render layer 0x31 draw, `Gfx *(Gfx *, u8 *, s16)`; 1 boundary survivor),
**func_1518F080 line_quad_build** (1BAF40, 273; 1 equivalent survivor), **func_151D4D44 object_trail_smoke_update**
(201240, 297; 1 equivalent survivor), **func_15083E90 object_find_by_id** (AF2A0, 72; readable rewrite of the m2c
goto body; port P221 follow-up (a)), **func_15063AA0 object_pending_actions_run** (90F50, 179; jump table, all cases;
mutants 47/47). func_15065E18: func_150FC438 / func_150DC2F0 prototypes now match port's C (`(.., u8, u8)`,
`u8 *(u8, s32)`, calls pass arg1 = 0; a3 at 0x15069F80 is carryAnim, already passed). 1BAF40: func_151901F4's
nested `#ifdef PORT` moved into a macro (it broke difftest for the whole TU). Port-b's files have no asm-only
functions left (D3880's are C since P130). Checks: verify_all rc 0, NM links, protocheck 0 (1461), selftest 91/91. progress_nm total 5455 / 5915 (92.2%),
C bytes 80.9%, 460 asm-only.

## Next steps (from P222)

1. Browser: B-pad case 0x3C (func_15065E18 -> func_15083E90 / func_150FC438), shockwave rings (func_150C8F68 /
   func_150C92B8), line effects (func_1518F080), trail smoke (func_151D4D44), pending actions (func_15063AA0).
2. Readable rewrites of remaining m2c-style NM bodies in port-b's files.
3. Port's files (func_15065E18 still-asm callees): func_15073FA0 (981E0), func_1507EE9C (ABEA0), func_150D9098 (106830).

## State (session P221, 2026-10-24). Details: `docs/port/sessions/P221.md`

Branch `port` (P218 85e5d8c6 + P221 commit).
- **Verification registry**: `tools/port/verify_registry.tsv` (func, file, setup_file, knobs, mutant_file, session;
  57 rows: P198-P218 conversions seeded by `tools/port/seed_registry.py`, P218 re-check rows, P221). Re-run with
  `tools/port/reverify.sh FUNC...` (TR=4, NR=100 random, MUT=1 mutants, NOSETUP=1); candidate = current NM block
  (`tools/port/nmblock.py`). Add a row for every new conversion; blank knobs = not recorded (check the session doc).
- difftest: a jalr / jr to an unaligned or unstubbable target ends the run as a fault `jalr to bad target` (same
  target both sides = inconclusive; `DIFFTEST_BADJALR_OLD=1` = old). Selftest case func_151416E8: 95 / 95.
- Hand C (NM), B-pad callees of port-b's func_15065E18: func_150FC438 effect27_spawn_with_screen_effect (129650; NM-only
  prototype in functions.h), func_150D9098 obj_spawn_effect50_with_sound (106830), func_150DC2F0 item_effect_spawn
  (109770; `(u8 kind, s32 arg1)`). Random + setups EQUIV, mutants 22/22, 27/27, 37/37.
- Lesson: random trials compare stack records passed to stubs (memcpy sources, spec structs) only by pointer class:
  func_150D9098's first draft swapped two record floats and was random-EQUIV. Use ARGMEM (+ STKFILL) setups.
- Checks: verify_all OK, NM build links, protocheck 0 (1437), selftest 95 / 95, progress_nm 5431 / 5915 (91.8%), C bytes 78.9%.

## Next steps (from P221)
1. func_15073FA0 (game_981E0, 458 lines; last port-file callee of func_15065E18), func_1508CF34 (B7840 cmd 9, exact v0).
2. port-b: func_15065E18's `jal func_150FC438` (15069F80): a3 not visibly set; func_150DC2F0 takes 2 args in NM C.
3. Re-checks: use `tools/port/reverify.sh`; fill blank knobs in the registry as functions are re-checked.
4. Breadth: `p218/asmlist.py`.
## P220 (port-b) (session P220, 2026-10-24). Details: `docs/port/sessions/P220.md`

Branch `port-b`. **func_15065E18 player_item_action** (90F50): 40 targeted setups (RET on func_15064240 /
func_150810F4 / func_151F2CDC (key 151F349C) / func_1506401C / func_15083568, pad pokes via D_800CC6A4 / D_800CC6B0 /
D_800CC6AC, ctl +0x8 for case 3, noAnim = 0 for the `done` cases 0x1A / 0x2A) all EQUIV; mutants 33/34 killed, the one
survivor (`D_800D1940 & 7` -> `& 3` inside `== 0x42`) is equivalent. Fix: case 0x1B's voice id is u16 (the asm masks it).
Hand C (NM): **func_151C0698 projectile_fire** (1EDA00, 669): ARGMEM setups found two draft bugs (inexact float
literals 0.047 / 1.009, missing payload +0xCC = trace hit), fixed; 18/20 setups EQUIV (2 differ only on the asm's
leftover v0), mutants 33/33. **func_150C8F68 ring_effect_update** (F6060, 212): 13/14 setups EQUIV (h3d: a1 the
target never reads), mutants 26/26; handlers func_150C9EB4 / func_150CA2C4 now take (.., f32, f32) (wasm type).
func_150A6070 / func_150A6324 were already C (P130). Checks: verify_all rc 0, NM links, protocheck 0 (1455), selftest
91/91. progress_nm total 5449 / 5915 (92.1%), C bytes 80.6%, 466 asm-only.

## Next steps (from P220)

1. func_1506401C (90F50, func_15065E18 case 0x3A's item lookup).
2. Breadth: func_150C92B8 (F6060, ring effect draw), func_1518F080 (1BAF40), func_151D4D44 (201240).
3. Browser: level 0x29 B-pad (func_15065E18 case 0x3C), gun shots (func_151C0698), shockwave rings (func_150C8F68).
4. Port's files (func_15065E18 still-asm callees): func_15073FA0 (981E0), func_1507EE9C (ABEA0), func_150D9098
   (106830), func_150DC2F0 (109770), func_150FC438 (129650).

## P219 (port-b) (session P219, 2026-10-24). Details: `docs/port/sessions/P219.md`

Branch `port-b`. Merged port 18edc1c6 (difftest P211/P214/P215 fixes, func_151B8EB8 s32); after the merge verify_all
rc 0, NM links, protocheck 0, selftest 91/91. Hand C (NM): **func_15065E18 player_item_action** (90F50, 4838 words,
the level 0x29 B-pad blocker): every case written (P216 draft fixed: cases 3 / 9 / 0x15 / 0x37 / 0x38 / 0x39 / 0x3C
had dropped calls; new 0x24 0x3B 0x12 0x23 0x17 0x1A 0x2A 0x1B 0x26 0x3A 0x3E), 617 setups EQUIV, mutants 29/61
killed, 27 survivors = setup gaps (list in P219.md section 2), 5 invalid (0x3A k3A_s faults at TR=4).
**func_151901F4 effect_node_launch** (1BAF40): setups EQUIV, mutants 11/11; a1 is the dispatcher's stale register:
N64 build reads it, `#ifdef PORT` aims at the node itself (velocity 0). func_150768DC x-swap mutant now KILLED
(random) with the merged harness. Checks: verify_all rc 0, NM links, protocheck 0 (1453), selftest 91/91. progress_nm total 5447 / 5915 (92.1%), 468
asm-only.

## Next steps (from P219)

1. func_15065E18 survivors (RET knobs on func_150810F4 / func_151F2CDC / func_15064240, pad pokes via D_800CC6A4 /
   D_800CC6B0 / D_800CC6AC, ctl +0x8 for case 3, a non-faulting 0x3A stunned setup); browser-check level 0x29 B-pad
   (case 0x3C).
2. func_151C0698 (1EDA00, 669; RET on the func_151B8EB8 stub; analysis P213.md section 3).
3. Breadth: func_150A6070, func_150A6324 (D3880), func_150C8F68, func_1518F080, func_151D4D44, func_150C92B8.

## State (session P218, 2026-10-24). Details: `docs/port/sessions/P218.md`

Branch `port` (P215 18edc1c6 + P218 commit). No harness change.
- func_1514D3B0: event values a2 / a3 are s32 in the NM build (functions.h `#ifdef NON_MATCHING`; the default keeps u8
  because the s32 prototype changes a C caller's default codegen). Setups wide / wideneg / wide32 EQUIV, 17 / 17 mutants.
- Random DIFFERs are harness artefacts: func_1504A730 (D_800CC6A4 holds &sp5C: MEMSTK=800CC6A4 -> EQUIV x3 seeds),
  func_151416E8 / func_151D9014 (random table entries -> unaligned jalr targets, no stub: ROMDATA / valid kind -> EQUIV).
- UNSURE setups: 15169260 / 15160310 just need DIFFTEST_ROMDATA=1 (EQUIV); func_15013000's "setups" were func_15113000's
  (p119/3000.txt): new `p218/15013000_setups.txt` EQUIV + mutants; func_1509D274 setups EQUIV TR=16 (random stays UNSURE).
- Hand C (NM): func_1508E080 rail_weapons_update (cmd 11, B7840), func_15173090 sprite_place_on_floor (19FA20).
- Checks: verify_all OK, NM build links, protocheck 0 (1434), selftest 91 / 91, progress_nm 5428 / 5915 (91.8%), C bytes 78.8%.

## Next steps (from P218)
1. B7840: func_1508CF34 (cmd 9; its result is used by func_1508AB7C: exact v0).
2. Harness idea (needs a selftest case): a jalr to an unaligned target could end the trial as inconclusive on both
   sides instead of running garbage (P218 section 2).
3. Re-check runs must use each function's own setup file and knobs (P214 / P215 ran 9260 / 0310 without ROMDATA and
   func_15013000 with another function's setups).
4. port-b: re-run A28B0 mutants (DECLKW fix, P214) - and any port-b mutant run made on a merge of P214 (jalr compare off).

## State (session P217, 2026-10-24, port-web). Details: `docs/port/sessions/P217.md`

- Merged port-b 427c2d4a (P210 + P213) and, on coordinator request, port-b bcdca37c (P219 func_15065E18, contains port
  18edc1c6): HANDOFF conflicts only. After each: verify_all OK, NM link OK, protocheck 0 (1445 / 1453), float-int 0,
  census 0 FAIL (722, clean rebuild), arity 139 / 137 lines (tool changed in bcdca37c), m2c 285 / 287.
- **B pad works**: B on the pad -> q 0x2000 cmd 0xAA = 4 (item held), scene 4 31803 .. 33263, then ev 1074 waits on
  q 0x4036 / 0x4008. Level-0x29 stub census 0 (scarecrow, hit, bpad routes; Chrome first-hit lists).
- B attack on Birdy: C hit path, no trap / stub / null-zone write; no visible knock-back (Birdy is a scripted NPC).
- **Multiplayer reached** (menu path in P217.md 4): Race A (level 0x33) and Total War (0x2D) start; HUD (lap, place,
  map, timer; radar with dot, ammo squares, countdown) draws. Conker cannot move; in Race the first death goes black
  for good: stub func_1507D1D8 (MP respawn, A9D90).
- Node census runs fail when other slots use the Docker VM (rc 137 / swapping at 5.3 GiB): run them only when the VM is idle.

## Next steps (from P217)
1. port: func_1507D1D8 (A9D90, MP respawn); then the MP control / start stubs (B7840 func_1508C07C / B854 / CA14 /
   E080, B37F0 func_15086268, 40490 func_150130B4, 142E40 func_1511E4F4, 78230 func_150528C8, 20B730 func_151E5E08,
   CC5F0 func_1509F4D0, 14FA00 func_151221F0, init_B1B0 func_1000C530, 216470 func_151E9150, CA630 func_1509D590),
   func_15164E0C (192500), func_151ECE00 (216470 menu DL).
2. port-web: level 0x29 after scene 4 (zone 0x36 / river); MP rails / laps once Conker can move.
3. port-b reviews: arity D_80086A34 rows (func_1505B9C4 / func_1505C1E4, a3), func_15167E0C; m2c func_15167C58.

## P216 (port-b) (session P216, 2026-10-24). Details: `docs/port/sessions/P216.md`

Branch `port-b`. Hand C (NM), difftest EQUIV + 10 setups + mutants 20/20: func_151D5DA8 mouth_aim_ray (201240, void;
caller func_15063AA0 ignores v0). **Ownership: game_eu_90F50.c moved to port-b** (coordinator, mid-session).
func_15065E18 (90F50, the level 0x29 B-pad item-action blocker) is **4838 words** (0x42-case switch), not ~1280:
WIP draft `docs/port/sessions/p216/d_5e18.c` (compiles in difftest, not verified, not in the source) covers the
prologue, the tail and all cases except the rest of 0x24 and 0x3B 0x12 0x23 0x17 0x1A 0x2A 0x1B 0x26 0x3A 0x3E
(asm 15068ED0..1506A898). Signature s32 (obj, buttons, held, f32 height, recurse, kind, stunned, timeout, noAnim),
v0 used by func_1506045C. Checks: verify_all rc 0, NM links, protocheck 0 (1446), selftest 71/71. progress_nm total
5440 / 5915 (92.0%), 475 asm-only.

## Next steps (from P216)

1. Finish func_15065E18 from the P216 draft (P217), then setups for every branch + mutants (P218 if needed).
2. Merge port (P215 18edc1c6+: func_151B8EB8 s32, difftest jalr fix) into port-b; re-run the func_150768DC x-swap
   mutant; convert func_151C0698 (RET on the func_151B8EB8 stub) and func_151901F4 (a1 is stale at the dispatcher
   jalr: convert faithfully, port-safe C must not dereference it; document).
3. Breadth: func_150A6070, func_150A6324 (D3880; compiled or hand asm?), func_150C8F68, func_1518F080,
   func_151D4D44, func_150C92B8.
## State (session P215, 2026-10-24). Details: `docs/port/sessions/P215.md`

Branch `port` (P214 2f944d3c + P215 commit).
- Selftest regression root cause: P214's compare() edit deleted the P211 line `cnt = max(cnt, max(indw)+1)` (jalr GPR
  compare silently off; JALRARG_OLD a no-op). Restored. All difftest runs after that P214 edit with a jalr are suspect;
  P214's dispatcher re-check redone (P215.md section 4).
- difftest: jalr target register not compared (JALRTGT_OLD=1 = old); `DIFFTEST_JALRSKIP=N,..` drops scratch arg GPRs at
  jalrs (check every table entry first); TU-literal compare reads unmapped reference pages' initial content
  (TUPEEK_OLD=1 = old). Selftest cases func_1506B04C (5), func_1508AB7C (3): 91 / 91.
- func_1506B04C: C was right (handler(obj, arg)); the DIFFER was a2 = jump target + a3 scratch copy. Verified.
- Natives func_150AE5D8 / 5E8 / 5F8 / 60C: EQUIV, all mutants killed (new setup idhi8).
- func_151B8EB8 (1E61C0): NM C now `s32`, returns func_151307F0's particle (port-b func_151C0698 stores it at +0x84).
- port-b question: func_1519AF14 does NOT set a1 at the D_8008FC48 jalr: a1 is stale (loop index on the early exits
  after func_15144528, memcpy / func_1513D2F0 leftovers on the loop path), never a vec3 pointer (P215.md section 5).
- Hand C (NM, B7840): func_1508AB7C rail_racers_update (cmd 6, returns the started-racer mask).
- Checks: verify_all OK, NM build links, protocheck 0 (1432), selftest 91 / 91, progress_nm 5426 / 5915 (91.7%), C bytes 78.6%.

## Next steps (from P215)
1. func_1514D3B0 (17A800): a2 / a3 are u8 in functions.h but the asm passes them unmasked (random DIFFER a2 0x141A vs
   0x1A). Change to s32 (prototype + NM def) and check the default build of the C callers (A28B0 is port-b's).
2. Random DIFFERs still open (not new-compare artefacts): func_1504A730, func_151416E8, func_151D9014; check with WLOG
   whether lazily filled pages / random tables explain them.
3. Setup files of func_15169260 / func_15160310 / func_15013000 / func_151D9014 / func_1514D3B0 give UNSURE at TR=4
   (faults): rerun with more trials or fix the setups.
4. B7840: func_1508E080, func_1508CF34. Breadth: `p215/asmlist.py`.
5. port-b: re-run A28B0 mutants (DECLKW fix, P214) - and any port-b mutant run made on a merge of P214 (jalr compare off).

## State (session P214, 2026-10-24). Details: `docs/port/sessions/P214.md`

Branch `port` (P211 b635f45 + P214 commit).
- difftest: `return func_X(...)` lines were taken as func_X's prototype (type `return`): FP args of such callees were
  never compared (port-b P210 func_150768DC x-swap of func_1505A630). Fixed (DECLKW_OLD=1 = old); K&R `f();` = unknown.
  Unknown-prototype jal: FPRs either side sets right before the call (JALARG_OLD=1 = old); the wide "since previous
  call" compare is opt-in (JALARG_WIDE=1: false DIFFERs as default). Selftest hook DIFFTEST_NOPROTO. New selftest
  case func_150768DC (6 checks).
- func_15074C80 (981E0): NM-only 3-parameter signature (table D_80086A34 all void/3; default build keeps 2 params).
- Hand C (NM, B7840): func_1508ECF8 rail_racer_take_over (cmd 15), func_1508A63C rail_rank_rivals (cmd 5).
- Re-check table in P214.md section 2: func_1506B04C (981C0) p184 setups DIFFER with old and new compare (object in
  a2 vs a3 at the jalr): likely real bug, not fixed.
- Checks: verify_all OK, NM build links, protocheck 0 (1431), progress_nm 5425 / 5915 (91.7%), C bytes 78.5%.
  **Selftest 82 / 83** (func_1513472C `arg0 = 0` case EQUIV, was 83 / 83 mid-session): open, see P214.md section 6.

## Next steps (from P214)
1. Selftest func_1513472C case (P214.md section 6), before trusting new difftest results.
2. func_1506B04C jalr argument slot (P214.md section 2).
3. port-b: re-run A28B0 mutants touching func_1505A630 / directly returned float-arg callees (DECLKW fix).
4. Re-check left: natives func_150AE5D8 / 5E8 / 5F8 (p106 REFLEN / SIGNORE=7 candidates), func_150FD49C,
   func_15196438, func_15199A28, func_151DA6F8, func_1509D274.
5. B7840: func_1508AB7C (cmd 6, exact v0), func_1508E080, func_1508CF34. Breadth: `p214/asmlist.py`.

## P213 (port-b) (session P213, 2026-10-24). Details: `docs/port/sessions/P213.md`

Branch `port-b`. Hand C (NM), difftest EQUIV + setups + mutants: func_150562FC object_carried_update, func_1505E874
hit_reaction_advance (83300, void since P209), func_15190A2C effect_node_release (1BAF40, D_8008FC60 handler),
func_150CA0DC shockwave_hit_objects (F6060, D_80088C00 handler, s32 leftover v0 kept). P210 setup gaps closed: 602c
t == 12, 68dc self2, 7e0c boundaries + both `%` mutants (rewritten with `.` and groups), 85f0 unk28 0.2f - all killed;
remaining: 68dc func_1505A630 x-swap (waiting for port P211's harness check), 7e0c life `<= 0` (equivalent).
Blocked: func_151C0698 (needs port's func_151B8EB8 to return the func_151307F0 result; payload +0x84 is dereferenced
by func_151C1730), func_151901F4 (dispatcher func_1519AF14 leaves a1). Checks: verify_all rc 0, NM links, protocheck 0 (1445), selftest 71/71. progress_nm total 5439 / 5915 (92.0%), 476 asm-only.

## Next steps (from P213)

1. port: func_151B8EB8 (1E61C0) -> `s32`, returning func_151307F0's result; then port-b converts func_151C0698
   (analysis in P213.md section 3).
2. func_151901F4 after the a1 of func_1519AF14's D_8008FC48 jalr is known (port's file).
3. Breadth in port-b files: func_151D5DA8, func_150A6070, func_150A6324, func_150C8F68, func_1518F080,
   func_151D4D44, func_150C92B8.
4. Re-run the func_150768DC x-swap mutant after P211's harness answer.

## State (session P212, 2026-10-24, port-web). Details: `docs/port/sessions/P212.md`

- Merged port d93bdcd (P204 / P207 / P209 + port-b P203 / P206) and port-b 33387f8 (P208): HANDOFF.md conflicts only
  (merge_union + hoorder 150). After each: verify_all OK, NM link OK, protocheck 0 (1426 / 1429 bodies), float-int 0
  bugs, census 0 FAIL (722 TUs, clean rebuild), arity 134 -> 135 (+func_151D7814), m2c_sanity 279 -> 284 (P212.md 1).
- `tools/eu_port/hoorder.py` (copy of p185/hoorder.py): `python3 tools/eu_port/hoorder.py docs/port/HANDOFF.md 150`.
- gen_stubs `DL_INDIRECT` emptied (func_151A03DC is C). Pond / level-0 water: wake trails drawn, null zone 0 everywhere.
- **Level 0x29 stub census ~0**: only func_15065E18 (port) on the B pad and func_1505C1E4 (port-b) when B hits an NPC.
- Fire imp flames visible on frontend 0x1D; level 6 night sky and the logo spotlight (sky dome UVs) fine.
- **After Birdy**: the B pad is zone 0x24 at (894, 970) (the board north of Birdy, not the disc). Stepping on it starts
  scene 3 ("OKAY, I'LL PRESS B", 29921 .. 31469); then the script waits for q 0x2000 cmd 0xAA (player held object +0x78)
  but B on the pad does nothing while the stub func_15065E18 (game_eu_90F50, ~1280 insns) runs every frame.
- New diagnostics: `[p212zone]` event-zone dump with ?p205obj; ?p174ev logs each action pair once (no cap overflow).

## Next steps (from P212)
1. port: **func_15065E18** (game_eu_90F50; caller port-b's C func_1506045C, 9 args) - blocks the B-pad action on 0x29.
2. port-b: func_1505C1E4 (game_83300, attack hit apply; 8 calls on 0x29).
3. port-web: after the merge, padwalk212 `bpad2` (P212 route) -> B on the pad -> follow q 0x2000 cmd 0xAA, then the
   river crossing / door north (fence at z ~548).
4. Reviews: m2c func_150F5FD4 width high (port), func_150867D4 (port), func_150F8EAC (port-b); arity func_151D7814 (port).
## State (session P211, 2026-10-24). Details: `docs/port/sessions/P211.md`

Branch `port` (P209 d93bdcd + P211 commit).
- difftest: at a jalr every arg register a0-a3 / f12-f15 that EITHER side wrote since entry is compared, whatever the
  target's prototype (before: only the reference's writes since the previous call, unknown targets only).
  `DIFFTEST_JALRARG_OLD=1` = old. New knob `DIFFTEST_STKFILL=WORD` (stack starts filled with WORD instead of zeros).
  Both forwarded by difftest.sh; selftest cases func_1513472C (jalr) and func_151C384C (stack fill); selftest 77 / 77.
  P200's "handler(0) survives" was a mutant file identical to the draft (sed did not apply).
- func_151C384C's `req.angle[1]` survivor killed with STKFILL=5A5A5A5A (setup r0).
- func_1513BA10 / BA44 (game_168A90): NM blocks pass the object to the D_80089C44 / C54 handlers (asm keeps a0).
- **Rail command result rule** (P211.md section 3): func_1509E3D4's return goes to the event VM result register
  (or back to func_1509BFB0's C caller, none of which uses a 0xFxxx word). ROM script scan: only commands 3, 6, 22,
  25 have their result read. Those must return the asm's exact value; the others return the asm's value where
  defined and 0 where the asm leaves a callee's scratch v0 (pin that callee with DIFFTEST_RET).
- Hand C (NM): func_1508DCAC rail_rival_pace (cmd 14), func_1508BE18 rail_pick_chase_target (cmd 13),
  func_1508C370 rail_assign_targets (cmd 7); all random + setups EQUIV, mutants all killed.
- Checks: verify_all OK (port_work/p211/verify.log), NM build links, protocheck 0 (1429), selftest 77 / 77,
  progress_nm 5423 / 5915 (91.7%), C bytes 78.4%.

## Next steps (from P211)
1. Re-run the setups of the dispatchers in the P211.md section 1 re-check list with the new jalr compare.
2. B7840 commands: func_1508ECF8 (cmd 15), func_1508A63C, func_1508AB7C (cmd 6: result read by scripts, exact v0),
   func_1508E080, func_1508CF34, func_1508C5F0.
3. Coordinator items not reached: (a) port-b func_150768DC mutant swapping the f12 / f14 x arguments of jal stub
   func_1505A630 survived - check that jal-stub FPR args are compared (unknown prototype: only FPRs BOTH sides
   write right before the call count; a known prototype uses FREGS) and float stack args; (b) game_981E0
   func_15074C80 is declared with 2 params but sits in hit handler table D_80086A34 (others void, 3 args): check
   the asm and align the NM prototype.
4. Browser: P211.md section 8. Breadth: `p211/asmlist.py`.

## P210 (port-b) (session P210, 2026-10-24). Details: `docs/port/sessions/P210.md`

Branch `port-b`. Merge of `port` d93bdcd (30e140a7; func_15142600 now void, 126330 func_150FFC60 declaration =
P209's) + hand C (NM), difftest EQUIV + setups + mutants: func_1505B9C4 object_apply_hit, func_1505C1E4
object_receive_hit, func_150585F0 object_stun_update (83300); func_15076D3C object_set_scale, func_15079FBC
follow_player_speed, func_1507602C path_jump_to_point, func_150768DC find_visible_target, func_15078544
path_point_from_object, func_1507AA48 set_heading_cmd, func_15079B30 object_var_cmd (A28B0, script command handlers
of D_80086730); func_15167C58 sprite_quad_draw, func_15167E0C sprite_node_update (1944C0, render layer callbacks of
D_8008B848). Checks: verify_all rc 0, NM links, protocheck 0 (1441), selftest 71/71. progress_nm total 5435 / 5915
(91.9%), 480 asm-only.

## Next steps (from P210)

1. func_150562FC (400), func_1505E874 (304) in 83300 (void prototypes since P209).
2. func_151C0698 (1EDA00, 669 words), callee func_151B8EB8 is C now.
3. Setup gaps listed in P210.md section 1 notes (602c, 68dc, 7e0c, 85f0).
4. Other owner: func_15074C80 (981E0) has 2 parameters in the void/3 hit handler table D_80086A34.
## State (session P209, 2026-10-24). Details: `docs/port/sessions/P209.md`

Branch `port` (P207 2672b13 + merge of port-b 4c59938 = a447641).
- Merged port-b 4c59938 (C5530 `s32 func_150867D4`, port-b P201-P206); HANDOFF via merge_union + hoorder 150.
- Hand C (NM): func_150867D4 rail_route_next inserted (P207 draft; 6 of 9 survivors killed by gen_67d4b.py setups,
  3 proven equivalent), func_151C384C fire_embers_spawn (embers for port-b's fire_burn_update; 151530A8 + 151307F0
  + 151602C0 requests, ARGMEM on all), func_15087040 rail_node_distance, func_1508DE78 rail_state_reset,
  func_15133E04 particle_fall_update, func_150FFC60 model_points_find, func_15062E24 type_texture_scroll_apply,
  func_151009E4 sky_segments_set, func_151722BC sprite_spawn_at. All random + setups EQUIV, all mutants killed
  (except listed equivalents).
- **NM-only prototype changes for port-b**: func_150585F0 and func_150562FC are `void (struct127 *)` under NM
  (game_eu_78230, game_eu_10E600; the matched func_15052590's call is wrapped in `#ifdef NON_MATCHING`);
  functions.h `void func_1505E874(u8, struct127*)` under NM (asm ignores a0, no v0); func_15142600 void in
  game_eu_E66D0's NM prototype. func_150FFC60 is `s32 (f32 *, f32 *, f32 *, f32 *, f32 *, u8 *, s32)` now
  (game_eu_126330's prototype still says s32 * - port-b may align it).
- Checks: verify_all OK (port_work/p209/verify.log), NM build links, protocheck 0 (1426), selftest 71 / 71,
  progress_nm 5420 / 5915 (91.6%), C bytes 78.3%.

## Next steps (from P209)
1. func_1508DCAC (B7840, rail script command 9): decide what the script runner does with a command's v0 (its
   `*cnt == 0` path returns func_150ADA68's leftover v0), then convert; the other B7840 commands have the same issue.
2. Browser: P209.md section 6 (rail races, fire embers, sprites, landing particles, sky segments).
3. Breadth: `p209/asmlist.py` (next: func_151F9184 is hand asm; func_15138120, func_1519D320, func_15117858,
   func_150B0344, func_150FC438 ...).
4. Harness: compare pass-through arguments of jalr calls (still open).

## P208 (port-b) (session P208, 2026-10-24). Details: `docs/port/sessions/P208.md`

Branch `port-b`. Merge of `port` (4c59938, checks green) + hand C (NM), difftest EQUIV + setups + mutants:
- **Ownership**: port-b now also owns `game_16EE20.c`, `game_83300.c`, `game_A28B0.c`, `game_1944C0.c` (moved from
  port in P208). `game_eu_78230.c` is port's (P207 edited func_150538CC); older notes calling it port-b's are stale.
- func_150918EC `mp_hud_draw` (BC510, 1995): the multiplayer HUD overlay (placing digit, score / team text, state and
  vehicle icons, lives and ammo bars, fire counter, race laps, overview map, radar). 64 setups EQUIV, mutants 126/128
  + 2 equivalent. With it func_15091534 `hud_icon_sheet_load` (BC510, 96; producer of the `ready` byte and of the DL
  pointer), 5 setups, mutants 14/14.
- func_15142600 `mtx_look_along_scaled` (16EE20, 142): look-along matrix for func_150BA1F4 (E66D0); keeps the
  caller's s32 prototype, returns 0 (unused). 7 setups, mutants 25/25.
- port P207 follow-up (b): func_150611E8 m2c_sanity rows O:20 / O:28 are loop artefacts (unrolled by 4, pointer +0x20);
  C is right.
- Checks: verify_all rc 0, NM links, protocheck 0 (1416 bodies), selftest 71/71. progress_nm total 5410 / 5915
  (91.5%), game 4874 / 5334, C bytes 78.2%, 505 asm-only.

## Next steps (from P208)

1. func_151C0698 (1EDA00): unblocked, callee func_151B8EB8 is C on port (2672b13); merge port first.
2. New files: func_1505C1E4 (381, 83300, result used by func_1505C7D8), func_1505B9C4 (490). func_150585F0 (callers in
   port's 78230 / 10E600 declare `s32 (struct127 *, s32)`; the asm takes one argument, no result), func_150562FC (s32
   in port's 78230) and func_1505E874 (functions.h `f32 (u8, struct127 *)`, the asm ignores a0 and has no result)
   need void prototypes in the callers' files first (other owners / shared header).
3. Other owner: func_151C384C (game_eu_1EFE10) asm-only, called by func_150F8EAC.
4. Browser: multiplayer HUD (func_150918EC), radar, fire scene; E66D0 objects using func_15142600.

## State (session P207, 2026-10-24). Details: `docs/port/sessions/P207.md`

Branch `port` (from P204 0226d7d).
- Hand C (NM): rail callers func_1509E3D4 rail_script_command (CBB40) and func_150538CC thrown_object_fly_update
  (78230, 1027 insns; D_800863B4 handler) - func_150877C0 rail_track_update now has C callers; func_151B8EB8
  smoke_puff_spawn (1E61C0; **port-b can convert func_151C0698** now); func_150B1200 wake_spray_update (DE750).
  All difftest EQUIV (random + setups) and every mutant killed.
- func_150867D4 rail_route_next (B37F0, 539): **draft only** in `docs/port/sessions/p207/150867D4_cand.c` (s32;
  40 setups EQUIV, 29 / 38 mutants, 9 survivors listed in P207.md 3.). Inserting it makes protocheck fail (2) until
  port-b 4f8756f's game_eu_C5530.c prototype (`s32 func_150867D4`) is merged into `port`; then insert with
  `p207/insert.py` and strengthen the setups (near-tie graph with a penalised short cut, first hop > 32767).
- Ownership change (coordinator, mid-session): game_16EE20.c, game_83300.c, game_A28B0.c, game_1944C0.c are port-b's
  now; no edits there in P207. func_150611E8 (83300) m2c_sanity O:20 / O:28 rows handed to port-b unresolved.
- Merge note: game_eu_78230.c was edited here (func_150538CC NM block); port-b has older edits in it - expect a
  clean merge (different function).
- Harness notes: declare no-arg callees (`s32 func_150ADA20(void);`) in the NM block or difftest compares their a0;
  mut.sh cuts a mutant line at the first `%` (use `.` + `\(..\)` groups); a stub's pointer arguments are only
  compared with DIFFTEST_ARGMEM.
- Checks: verify_all OK (port_work/p207/verify.log), NM build links, protocheck 0 (1369), selftest 71 / 71,
  progress_nm 5363 / 5915 (90.7%), C bytes 75.1%.

## Next steps (from P207)
1. After merging port-b 4f8756f: insert func_150867D4 (above), strengthen its setups, re-run the survivors.
2. func_151C384C (game_eu_1EFE10, ~300 insns, two func_151307F0 requests + func_151530A8): called by port-b's new
   fire_burn_update for embers (coordinator item, not started).
3. Browser: P207.md UNVERIFIED (rail races / camera, thrown objects, wake spray, smoke puffs).
4. Harness: compare pass-through arguments of jalr calls (still open).
## P206 (port-b) (session P206, 2026-10-24). Details: `docs/port/sessions/P206.md`

Branch `port-b` (from P203 4f8756f). Tooling commit + hand C (NM), difftest EQUIV + setups + mutants:
- Tooling: `docs/port/sessions/p179/voidret_scan.py --files` silently matched nothing for paths / `.c` names ("0
  void C functions scanned"); now accepts base names, `.c` names and paths, errors on unknown names, refuses a missing
  `port_work/p179/dis.txt` and warns when it is older than the ELF; `#pragma GLOBAL_ASM` lines no longer count as
  table references. Re-run on the P197..P203 files: 88 void functions, no suspect. `tools/port/v0use.py` copied from
  port (p204).
- func_15093B58 `radar_draw` (BC510, 857): multiplayer radar (disc + team dots + height marks); callers
  func_1508FD38 (C) and func_150918EC (asm), both read v0. 35 setups EQUIV, mutants 65/67 + 2 equivalent.
- func_150F8EAC `fire_burn_update` (126330, 893): burning-object update (stages, crackle, embers / flames / smoke /
  sparks); caller func_150F8DFC (matched C, void). 21 setups EQUIV, mutants 89/91 + 1 equivalent + 1 1-ulp literal.
  Callee func_151C384C (game_eu_1EFE10, not port-b's) is asm-only: embers missing until converted.
- Checks: verify_all rc 0, NM links, protocheck 0 (1318 bodies), selftest 65/65. progress_nm 5312 / 5915 (89.8%),
  game 4778 / 5334, C bytes 75.2%, 603 asm-only (P203's "5353 / 562" in its notes did not match progress_nm; the
  P162 list from 11:37 had 5307 before P203).

## Next steps (from P206)

1. func_150918EC (1995, BC510): last owned asm-only function with a C caller; split into readable parts, verify by
   branch setups.
2. Other owner: func_151C384C (game_eu_1EFE10) asm-only, called by func_150F8EAC.
3. Browser: radar (multiplayer), the fire scene (message 0x3F to func_150F8DFC).

## State (session P205, 2026-10-24, port-web). Details: `docs/port/sessions/P205.md`

- Merged port 47ca032 (P200) and port-b ce8da0d (P201): HANDOFF.md conflicts only. After each: verify_all OK, NM link OK,
  protocheck 0 (1402 bodies), float-int 0 bugs, census 0 FAIL (clean rebuild), arity 136 -> 134 (func_1513472C / 477C
  rows gone), m2c_sanity 278 -> 279 (+func_150CA150 stride low, review only).
- **P199 wrap removed** (pc_overrides.c + Makefile): level 0 swim (node noev + Chrome chN) and the level 0x29 pond swim
  run without a trap (no func_15168A9C trap), heap 0, null zone 0.
- **Level 0x29: Birdy (the scarecrow) dialogue reached** with a new pad autopilot (`?p205goto`, port/gfx/p205_obj.c;
  routes in `docs/port/sessions/p205/padwalk205.py`): route around the fence, dialogue at 26812 (16-line box, then a
  4-line box to 29360), text boxes / camera cuts / Birdy's animation correct, gameplay resumes after. Only stub on the
  route: func_1518354C. Node and Chrome are retrace-identical.
- func_150CA150 (landing dust): 0 calls on all routes (event-script command func_15070014 only); UNVERIFIED.
- New diagnostics: `?p205obj=F` (D_800CC2D0 record dump), `?p205dust=N` (func_150CA150 wrap).

## Next steps (from P205)

1. port: func_1518354C (only stub on the 0x29 route); P204's func_151A03DC -> then drop gen_stubs' DL_INDIRECT entry.
2. port-web: after Birdy, find the next trigger (the disc in front of him: B taps did nothing; run `?p174ev` on
   padwalk205 `bpad`), then the river crossing / door to the north; extend padwalk205.
3. Check arity rows func_1513BA10 / func_1513BA44 (game_168A90, port): same dropped-argument shape as func_1513472C.

## State (session P204, 2026-10-24). Details: `docs/port/sessions/P204.md`

Branch `port` (from P200 47ca032).
- Coordinator priorities done (hand C, NM): func_151A03DC foot_trail_draw (game_eu_1CCD10; D_8008A644 draw handler,
  returns its DL argument), func_1518354C water_wave_push (game_eu_1B0550; the 1.1 M-call level-0x29 stub), and the
  level-0x29 frame-path stubs func_151D7814 effect_follow_update (204F70), func_150F5FD4 model_tile_fade_cb (1231B0),
  func_151096A0 sky_dome_project_uv (1365E0), func_1000BF60 ambient_voice_update_3d (init_B1B0).
  func_150B1200 (DE750, 244, particle spawner with many stub callees) NOT done (budget).
- game_981E0.c: `s32 func_150CA150(u8 *);` added to the NM prototype block (call cast, default build identical);
  func_151AABC4's prototype was already there (P192).
- **port-web can remove** the `DL_INDIRECT` entry for func_151A03DC in port/tools/gen_stubs.py after merging this.
- Merge note: game_eu_1CCD10.c is also edited on port-b (P191 func_1519FD60 NM block, one line above
  func_151A03DC's GLOBAL_ASM line, a blank line between): expect a clean merge, check it.
- Harness lesson: a plain-C callee is a stub in difftest too (func_15143E64 returned random f0): give such callees
  RET / RETF and ARGMEM, or their branches are random.
- Task 5: arity rows func_1509D274 / func_1506B04C / func_1514D3B0 and m2c_sanity func_150DE8AC are false positives
  (P204.md section 2); func_150A55A0 is port-b's; func_150611E8 O:20 / O:28 not resolved.
- Checks: verify_all OK (port_work/p204/verify.log), NM build links, protocheck 0 (1365), selftest 71 / 71,
  progress_nm 5359 / 5915 (90.6%), C bytes 74.8%.

## Next steps (from P204)
1. Coordinator extras (arrived late, not started): (a) func_150867D4 (game_eu_B37F0, 539 insns, rail choice) with an
   s32 return (asm ends `or v0, s5, zero`) - after merging port-b 4f8756f (its C5530 prototype becomes s32);
   (b) rail camera callers func_150538CC (game_eu_78230) and func_1509E3D4 (game_eu_CBB40) are still asm (browser
   P202: that is why func_150877C0 never runs on the route); (c) func_151B8EB8 (game_eu_1E61C0.c) blocks port-b's
   func_151C0698.
2. func_150B1200 (game_eu_DE750, 244): level-0x29 frame-path stub; list its stub callees first (func_150B0F40,
   func_15143794, func_151D9014, func_1515C668).
3. Browser: P204.md UNVERIFIED (pond ripples / trails, wave push, sky dome UVs, level 0x1D ambient voice).
4. func_150611E8 m2c_sanity rows (O:20 / O:28) still to explain.
5. Harness: compare pass-through arguments of jalr calls (P200 item, still open).

## P203 (port-b) (session P203, 2026-10-24). Details: `docs/port/sessions/P203.md`

Branch `port-b` (from P201 ce8da0d). Hand C (NM), difftest EQUIV + setups + mutants:
- func_1518ECAC `particle_quad_velocity_build` (1BAF40, 245; coordinator priority from browser P202): entry 5 of
  the particle draw table D_8008A1BC, `u8 *(u8 *, s16)` like func_1514A540; returns the view's vertex block (the stub
  returned 0: no character-effect particle drawn). 14 setups, mutants 32/33 + 1 equivalent.
- func_1511127C `sky_box_face_build` (13DC30, 652, level-0x29 stub): returns the DL (C caller func_15112074 uses
  it); w / h / steps u32; SkyFace / SkyLoad typedefs moved above it. 39 setups, mutants 80/84 (3 equivalent, 1
  untestable upper-case axis = port decision, start at 0).
- func_151D3A30 `impact_effect_spawn` (201240, 564): s32 returning 0 (981C0 prototype, nobody reads v0). 32 setups,
  mutants 88/88. IDO reads `5.86f` as 0x40BB851F: the C writes 5.85999966f (rodata 0x40BB851E).
- Coordinator: game_eu_C5530.c NM prototype of func_150867D4 is now s32 (asm returns s5; func_15086508 and game_A28B0
  read it): port can convert func_150867D4.
- P199 stub census: no other listed stub is in a port-b file.
- Checks: verify_all rc 0, NM links, protocheck 0 (1359), selftest 65/65. progress_nm 5353/5915 (90.5%), C bytes
  74.5%, 562 asm-only.

## Next steps (from P203)

1. Browser: func_1518ECAC (frontend 0x1D fire imp flames), func_1511127C (level 0x29 sky), func_151D3A30 impacts.
2. func_151C0698 (1EDA00) waits for func_151B8EB8 (game_eu_1E61C0, other owner, asm-only).
3. Owned breadth: func_15093B58 (857, BC510), func_150F8EAC (893, 126330), func_150918EC (1995, BC510).

## State (session P202, 2026-10-24, port-web). Details: `docs/port/sessions/P202.md`

- Merged port 6f2d2ca (P198) and port-b b693dac (P197): HANDOFF.md conflicts only. After each: verify_all OK, NM link OK,
  protocheck 0 (1393 bodies), float-int 0 bugs, census 0 FAIL (clean rebuild), arity 136 rows (no change),
  m2c_sanity 273 -> 278 (func_150877C0 width high, func_1510783C width med x3, func_1518DC50 width low).
- func_1518DC50: 0 stub calls now. `?p202fx=N` (port/gfx/p202_fx.c): only 2 character-effect attaches in a 57 k-frame
  walk, both the frontend 0x1D fire imp (type 5); none on level 0x29, and no continuous particle spawns there.
  `?p202stubfrom=F` (stub census counts from frame F): on 0x29 only func_1518354C / func_151A03DC / func_151473F4 are hit
  -> the 0x29 torches are not blocked by a stub on the current path (agrees with port-b P201).
- **New blocker func_1518ECAC** (game_eu_1BAF40): particle draw table D_8008A1BC[5], stub returns 0 -> the fire imp's
  flames (all character-effect particles) are spawned but not drawn.
- Backdrop quad (draw 0) 00C700 is correct: the 4x256 texture is a sky gradient whose last rows are 00C700 (ground
  below the horizon); t clamps there.
- Regressions none: level 0 swim (node + Chrome), level 0x29 pond swim, ?p103boot runs past 17820 (to 39488).
  Rail func_150877C0 unreachable (callers func_150538CC / func_1509E3D4 still asm, never hit).

## Next steps (from P202)

1. port-b: convert func_1518ECAC (then re-shoot the fire imp, chB shots 50-65 s); func_1518354C.
2. Level 0x29: route to the scarecrow / B pads (text boxes); check on an emulator whether the torch posts are lit there.
3. Drop the P199 port workarounds once port P200's game C lands.
## P201 (port-b) (session P201, 2026-10-24). Details: `docs/port/sessions/P201.md`

Branch `port-b` (from P197 b693dac). Hand C (NM) + tests:
- func_1518DC50 `character_effect_update` mutants complete: 72 = 71 killed + 1 equivalent on ROM data (hidden-row
  yoff is 0 in every D_8008D980 row); 19 new setups (vis 7, model id >= 0x100, release velocities at the clamps,
  live == max, effects 8 / 9). Seed-1 trial-57 random DIFFER proved a harness artefact (kuseg pointer 0x02000000,
  lazily mapped page reads 0; WLOG + POKE evidence in P201.md 1).
- **Character effect types 5..9 (func_1518D1C0)**: attached by the D_8008AE10 character handlers 4..8 / 0x2C
  (game_eu_17A800 func_1514EA78 / EB28 / EBD8 / EC88 type 5, func_1514ED38 type 7, func_1514F9BC type 5 "frontend
  fire imp"), run from func_1514D6CC; func_1514CFF0 picks them only on levels 0x02 (sub 0xD -> type 7), 0x0A (subs
  8..0xF -> type 5) and 0x1D (sub 9 -> fire imp). **Level 0x29 is not in that switch**: no static path gives a
  level-0x29 character a type 5..9 effect (only a cutscene script event 0x4C with b5 5..9 could). Types 6 / 8 / 9
  have no static caller. So the level-0x29 torches are probably not character effects. Table in P201.md 2.
- func_150CA150 `landing_dust_burst` (F6060, 504): 22 setups EQUIV, mutants 55/56 + 1 equivalent; s32 returning 0
  (implicit-int caller in game_981E0); anti-tamper code checksum skipped in NM.
- func_150CA2C4 (F6060) fixed: called func_150CD2A0 without a prototype with a pointer as its f32 argument (wrong
  wasm signature; N64 used a leftover f12). Now passes the position's z. Port decision, UNVERIFIED.
- Checks: verify_all rc 0, NM links, protocheck 0 (1313), selftest 65/65; voidret no suspect. progress_nm 5307/5915
  (89.7%), C bytes 74.6%, 608 asm-only.

## Next steps (from P201)

1. Browser: func_1518D1C0 calls on level 0x29 (torches need another source than character effects); character
   fire on level 0x0A / frontend 0x1D; func_150CA150 on player landing.
2. func_1511127C (13DC30, 652; asm read halfway, not started), func_151D3A30, func_151C0698 (asm callees first).
3. game_981E0 owner: add `s32 func_150CA150(u8 *);` (called without a prototype).

## State (session P200, 2026-10-24). Details: `docs/port/sessions/P200.md`

Branch `port` (from P198 6f2d2ca).
- Harness fix: `DIFFTEST_ARG` on a leading float parameter now also sets f12 / f14 (before, setups for
  `f(f32 x, f32 y, ...)` ran on random x / y). `DIFFTEST_ARGF_OLD=1` = old. Selftest case func_15087204.
  Known remaining hole: a pass-through argument of an indirect call (a0 never written before the jalr) is not compared.
- Restore re-check (P198 stub-write fix): func_15006590's unexplained P176 survivor (`D_800BE7FC >= 0` -> `> 0`) is now
  killed; committed body unchanged and EQUIV (no bug). Other old survivors near OUT knobs are logic / type equivalences.
- Priority 1 from the coordinator (P199 blocker) done: func_1513472C / func_1513477C (game_161520.c) under NM call the
  D_80089AAC / D_80089AD4 handler with the object and return its result (all 20 entries are s32 (*)(obj)).
  **port-web can remove** the func_1513472C / 477C `--wrap` in port/boot/pc_overrides.c after merging this.
- Hand C (NM): func_15088E84 rail_param_step, func_1508882C rail_find_ahead, func_15087204 rail_wall_hit,
  func_15086508 rail_point_pick, func_1517F01C world_to_screen, func_15155B1C effect_overlap_find,
  func_150CFB90 screen_bar_spawn, func_15195160 obj_hit_retire (void; NM prototype in 1C1A20 void).
- Checks: verify_all OK (port_work/p200/verify.log), NM build links, protocheck 0 (1359), selftest 71 / 71,
  progress_nm 5353 / 5915 (90.5%), C bytes 74.5%.

## Next steps (from P200)
1. Coordinator priorities not started (budget): func_151A03DC (game_eu_1CCD10.c, ripple / foot-trail DL draw, data
   table; must return its DL argument) - then port-web's DL_INDIRECT entry in port/tools/gen_stubs.py can go;
   func_1518354C (game_eu_1B0550.c, 1.1M stub calls per walk on level 0x29); then func_150F5FD4 (1231B0),
   func_151096A0 (1365E0), func_150B1200 (DE750), func_151D7814 (204F70), func_1000BF60 (init_B1B0).
2. func_150867D4 (539, rail choice): port-b must first make game_eu_C5530.c's prototype
   `s32 func_150867D4(s32, s32, s32, u8 *, s8 *)` (now void; func_15086508 / game_A28B0 use the result).
3. Harness: compare pass-through arguments of jalr calls (func_1513472C `handler(0)` mutant is EQUIV today).
4. Browser: P200.md UNVERIFIED (rail race levels, swimming, effects).
5. Coordinator low-priority item (budget): game_981E0.c needs prototypes `s32 func_150CA150(u8 *);` (port-b P201: s32
   returning 0) and `s32 func_151AABC4(struct127 *, s32);` (both called without one today); keep byte identity.
6. Breadth: `p200/asmlist.py` next: func_15103AA0 (93, refs only), func_15103910 (100), func_150D2C9C (102),
   func_15062E24 (103), func_151009E4 (103).

## State (session P199, 2026-10-24, port-web). Details: `docs/port/sessions/P199.md`

- Merged port 4793d9c (P184-P196) and port-b a4dd67d (P183-P194, swim update func_1504B0FC): HANDOFF.md conflicts only.
  After each: verify_all OK, NM link OK, protocheck 0 (1381 bodies), float-int 0 bugs, census 0 FAIL (clean rebuild).
  arity +3 rows (func_1506B04C, func_1509D274, func_1514D3B0), m2c_sanity 260 -> 273 (func_150A55A0, func_150DE8AC, func_150611E8).
- Port fixes: duplicate func_151F9150 (mp3_pc.c copy removed); p103_boot memok overflow (?p103boot crash at 17820);
  **wraps for func_1513472C / func_1513477C** (pc_overrides.c: dropped object argument trapped func_15168A9C at noev 1501
  once Conker swims; `?p199nowrap=1` = old); **gen_stubs DL_INDIRECT func_151A03DC** returns its a1 DL (stub returned 0:
  frame DL built at address 0, black screen in water, 1338 null-zone words).
- Level-0 rise gone (node + Chrome): Conker floats, swims to the bank, walks out; death / 0x2C / level 0 as before; heap 0.
- New game, no flags: real route to 0x29 (22765); at 25889 Conker falls in the pond, floats, swims, leaves it by 27768
  and walks on (control kept, to 34936). Torches still unlit (func_1518DC50 stub); text boxes / NPCs not reached.

## Next steps (from P199)

1. Convert func_151A03DC (ripple / foot-trail draw) and fix the func_1513472C / func_1513477C game C (pass arg0); drop the port workarounds.
2. func_1518DC50 (torches), func_1518354C (1.1 M calls on 0x29), func_150F5FD4, func_151096A0, func_150B1200, func_151D7814.
3. Walk further on 0x29 with A presses (text boxes, NPCs); backdrop quad draw 0 check; re-run ?p103boot past 17820.
## State (session P198, 2026-10-24). Details: `docs/port/sessions/P198.md`

Branch `port` (from P196 4793d9c).
- Harness fix (tools/port/difftest/difftest.py): memory written by stub knobs (DIFFTEST_OUTW / OUTA / OUTB, incl.
  `@ADDR`) is now part of the compared memory (`Run.stub_write`); before, only the function's own stores were logged,
  so dropping the restore of a stub-clobbered word compared equal. `DIFFTEST_STUBW_OLD=1` = old behaviour (forwarded by
  difftest.sh). Selftest case func_15063254 (68 / 68 ok). func_15063254's 3 P196 survivors are now killed (16 / 16).
- Hand C (NM), difftest EQUIV + setups + mutants (table in P198.md): func_1510783C `bolt_record_update` (43 / 43),
  func_15107518 `bolt_spawn` (P196 candidate, re-run 14 / 14), func_150877C0 `rail_track_update` (604; 76 / 77 + 1
  equivalent; sets D_800D27C9), func_150893AC `rail_spline_points`, func_15088D24 `rail_link_pick`, func_15087540
  `rail_records_init` (34 / 34), func_1518C000 `obj_effect1F_attach` (void: the only caller's prototype is void).
- game_eu_133A70: NM prototypes of func_15143794 are void (its definition is void; protocheck).
- Checks: verify_all OK, NM links, protocheck 0 (1351), selftest 68 / 68, progress_nm 5345 / 5915 (90.4%), C bytes 74.3%.

## Next steps (from P198)
1. Browser: race level with the rail family (func_15087540 / func_150877C0 + P196 cameras): rank +0x29, camera point,
   D_800D27C9 gating func_15088130; bolts (func_15107518 / func_1510783C).
2. Rail still asm: func_15088E84 (212, parameter step used by func_150877C0), func_1508882C (107), func_150867D4 (539),
   func_15087204, func_15086508; callers of func_150877C0 are asm (func_150538CC in port-b's 78230, func_1509E3D4).
3. Re-check older functions verified with OUTW / OUTA / OUTB clobbers on words the function restores: their
   "survived as equivalent" restore mutants may now die (harness fix above).
4. func_15133E04: fix the D_80089CD4 handler signatures first (P196).
5. Breadth (`p198/asmlist.py` after `progress_nm.py --list > port_work/p198/asmonly.txt`): next game entries
   func_1517F01C (92), func_15103AA0 (93, refs only), func_15155B1C (96), func_150CFB90 (96), func_15103910 (100).
## P197 (port-b) (session P197, 2026-10-24). Details: `docs/port/sessions/P197.md`

Branch `port-b` (from P194 a4dd67d). Hand C (NM):
- func_1518DC50 `character_effect_update` (1BAF40, 750): the handler of every func_1518D1C0 character effect
  (burning / smoke / impacts; endless point flames = types 5..9, effects 2..6, attach 2) - the torch-flame candidate:
  as asm stub no character effect ever spawned. 207 setups EQUIV, mutants partial (18/20 run, 52 not run).
- func_15082278 `shot_hit_apply` (AF2A0) inserted (41/42 + 1 equivalent); game_eu_12D5D0 prototype s32.
- func_150B2C20 `pipe_explode_effects` (E0430; s32 for port's caller), mutants 41/41.
- func_150C8DD0 `ring_effect_create` (F6060), mutants 13/13. func_150A66F0 `view_sphere_depth` (D3880, hand asm):
  whole-function harness `p197/nmasm_66f0.py` 10000 trials EQUIV.
- Checks: verify_all rc 0, NM links, protocheck 0 (1312). progress_nm 5306/5915 (89.7%), C bytes 74.5%.

## Next steps (from P197)

1. Browser: level 0x29 torches / character effects with func_1518DC50 in C.
2. Finish func_1518DC50 mutants (P197.md 4.); func_150CA150, func_1511127C (their asm callees are C now).
3. Breadth (`p168/asmlist.py`), smallest first.

## State (session P196, 2026-10-24). Details: `docs/port/sessions/P196.md`

Branch `port` (from P195 7964ca6). Hand C (NM), difftest EQUIV + setups + mutants (table in P196.md):
- func_151184BC `gate_swing_update` mutants done: 66 run, 64 killed, 2 equivalent (new setups for the 4 P195 gaps).
- Rail cameras (game_eu_B37F0): func_150894F8 `rail_node_next`, func_15089664 `rail_camera_follow`, func_15089B68
  `rail_camera_spline`, func_15088130 `rail_cameras_update`, func_150882C4 `obj_yaw_clamp_to_track`. Dormant in the
  port until the producer func_150877C0 (604, asm) sets D_800D27C9.
- Breadth: func_150D7B6C `anim_segments_set` (105140), func_150E7B20 `particle_spawn_simple` (114640), func_15131F34
  `surface_hit_dispatch` (15E000, passes cfg as the handler's arg3), func_15063254 `obj_model_swap_keep_pose` (8FCB0),
  func_150DE8AC `trigger_zones_check` (10C0B0; game_3DC30 now declares it as a function), func_15107678
  `bolt_subdivide` (133A70). func_15107518 `bolt_spawn` verified but not committed (handler func_1510783C is asm).
- Checks: verify_all OK, NM links, protocheck 0 (1344), selftest ok, progress_nm 5338/5915 (90.2%), C bytes 74.1%.

## Next steps (from P196)
1. port-b: func_1518DC50 (torch-flame candidate, P195), then browser-check level 0x29.
2. Harness: func_15063254 mutants dropping restores of stub-clobbered words (OUTW `@ADDR` on func_15060F28) survive;
   check whether difftest compares memory written by stubs (P196.md section 2 notes); add a selftest case if fixed.
3. Rail producers (B37F0): func_150877C0 (604), func_15087540 (160), func_1508882C (107), func_150867D4 (539), then
   func_150893AC (83) / func_15088D24 (88) / func_15088E84 (212). Bolt: func_1510783C (210), then commit
   `p196/15107518_cand.c` (verified).
4. func_15133E04: fix the D_80089CD4 handler signatures (func_151A79EC has `f32 arg1`) before converting.
5. Breadth (`p196/asmlist.py` after `progress_nm.py --list > port_work/p196/asmonly.txt`): next game entries
   func_1518C000 (89), func_1517F01C (92), func_15103AA0 (93), func_15155B1C (96).

## State (session P195, 2026-10-24). Details: `docs/port/sessions/P195.md`

Branch `port` (from P192 cc3d667). Hand C (NM), difftest EQUIV + setups + mutants (table in P195.md):
- Level 0x29 world-mesh handlers (D_80089140 table, func_151143D4): func_151184BC `gate_swing_update` (652; mutants
  partial, see P195.md), func_15118F2C `mover_swing_step` (350), func_1511ED08 `mover_slide_step` (308),
  func_15119974 `mover_bob_y_update` (port-b P194 draft), func_1511A540 `pickup_spin_update` (278).
- Other level 0x29 stubs: func_1513B5E0 `mesh_effect_spawn` (game_168A90), func_151630F4 `lightning_flash_update`
  (game_18D770). Breadth: func_15080900 `context_action_set` (AE110), func_150DBA98 `anim_event_effect_spawn` (108C00).
- Torch flames: not in game_eu_142E40. Best candidate is port-b's func_1518DC50 (game_eu_1BAF40, 750 insns): object-type
  handler at D_8008BEFC that spawns particle records (func_1513D524 + 0x58-byte emitter block at rec + 0x110).
- Checks: verify_all OK, NM links, protocheck 0 (1333), selftest 65/65, progress_nm 5327/5915 (90.1%), C bytes 73.9%.

## Next steps (from P195)
1. port-b: convert func_1518DC50 (torch-flame candidate), then browser-check the level 0x29 torches.
2. Finish func_151184BC mutants: `TR=4 docs/port/sessions/p195/mut.sh func_151184BC docs/port/sessions/p195/151184BC_cand.c
   docs/port/sessions/p195/151184BC_setups.txt docs/port/sessions/p195/151184BC_muts.txt` (68 setups now).
3. Breadth (`p195/asmlist.py` after `progress_nm.py --list > port_work/p195/asmonly.txt`): func_15088130 needs
   func_15089664 (321) / func_15089B68 (306) first (all game_eu_B37F0).
4. Browser: level 0x29 gate / doors / scenery / pickups / lightning (P195.md section 4).
5. Setup tip: sinf / cosf are harness stubs (random returns); pin them with RETF (cosf jal 15047EF0, sinf jal 15048050).
## P194 (port-b) (session P194, 2026-10-24). Details: `docs/port/sessions/P194.md`

Branch `port-b` (from P191 5d6bdf7). Docs / drafts only, no src_eu change.
- Torch flames: none of func_151184BC (per-level door mover), func_15116F34 / func_1511712C (linear movers with
  sounds), func_151831CC (wave mesh vertices) draws or spawns flames. Those files are port's (P192 converted
  func_15116F34 / func_151831CC); P194 drafts kept in `p194/` for reference only.
- func_15082278 shot_hit_apply (AF2A0, 466 words): draft `p194/d_2278.c`, 312 setups EQUIV, mutants 38/42
  (1 coverage survivor, 3 not re-run on the full set). Not inserted.

## Next steps (from P194)

1. func_1518DC50 (game_eu_1BAF40, 750 insns): torch-flame candidate from port P195 (P195.md); callees first.
2. Finish func_15082278 (survivor run on all setups, insert, `s32` prototype in game_eu_12D5D0.c, full checks).
3. Breadth: func_150B2C20, func_150CA150, func_151D3A30, func_1511127C, func_151C0698.

## State (session P193, 2026-10-24, port-web). Details: `docs/port/sessions/P193.md`

- **Level 0x29 green patch fixed (renderer)**: the texture cache was direct-mapped and mip tiles 1 and 3 of a standard
  chain always shared a slot, so binding tile 3 re-uploaded the GL texture bound to unit 1; LOD level 1 sampled out of
  range (alpha 0) and the ALPHA_CVG_SEL CI4 ground (draw 48, cc 26A004/151092FF) was cut away, showing the backdrop quad.
  Fix in `tex_for`: mixed hash, 8-way probing, entries bound for the pending draw never evicted (`?p193oldtc=1` = old).
- The CI8 leaf cut-out (cc 15FC92F8) blamed by P189 is fine: the `[draw]` log printed the NEXT draw's state. Fixed
  (apply_state saves the drawn state; lines carry `#index`).
- New DIAGNOSTIC flags: `?p193dbg`, `?p193idx`, `?p193bucket`, `?p193pick` (+`p193d`), per-unit binding log in p158 dumps.
- Before/after: no regressions (logo, menu, throne room, intro scenes, level 0x29); level 0 not re-shot.

## Next steps (from P193)

1. Convert func_1504B0FC (P189 #1). 2. Torches on level 0x29. 3. Backdrop quad (draw 0) texture / colour check.

## State (session P192, 2026-10-24). Details: `docs/port/sessions/P192.md`

- Level 0x29 stubs (browser P185 census) now hand C (NM), difftest EQUIV + setups + mutants: **func_15080628**
  text_queue_tempo_events (3083 stub hits), **func_15116F34** mover_step + its callee **func_1511712C** mover_step_sfx,
  **func_1511AA1C** obj_texture_anim_step (real D_800896C4 table via DIFFTEST_ROMDATA), **func_151831CC**
  water_mesh_wave_update.
- Breadth (hand C, NM): func_1509D274, func_151AF820, func_1507E8E0 (void under NM, ADE10 prototype), func_15088760,
  func_15088360, func_150F58C0, func_150637B4, func_15007558, func_150B7B9C, func_15088B08 (table in P192.md).
- game_981E0.c: `s32 func_151AABC4(struct127 *, s32);` under NON_MATCHING (coordinator request).
- Checks: verify_all OK (code build, check_files, full ROM OK) after the last code edit, NM links (rc 0), protocheck 0
  (1324 NM bodies), selftest 65/65, progress_nm 5318/5915 (89.9%), C bytes 73.5%. No difftest processes left.

## Next steps (from P192)

1. Browser: P192.md section 3 (level 0x29 moving scenery / animated textures / water, text queue 'L' records).
2. Remaining level 0x29 stubs in port files: func_1511ED08 (308), func_15118F2C (350), func_151184BC (652) (game_eu_142E40).
3. Breadth: p192/asmlist.py smallest first (next: func_15088130 67, func_150DBA98 70, func_15080900 72, func_150DE8AC 75,
   func_150E7B20 76, func_150D7B6C 77); P138 / P141 leftovers.
4. func_1505D1C4 (game_83300) return: coordinate with port-b (unchanged).

## P191 (port-b) (session P191, 2026-10-24). Details: `docs/port/sessions/P191.md`

Branch `port-b` (from P188 a1667be). Hand C (NM), all difftest EQUIV + setups + mutants:
- func_1504B0FC `player_swim_update` (78230, 591 words): **the level-0 rise / level-0x29 control loss (P189)**: clamps
  y at the surface line (+0x118 - 60, +14, 0.65 of the excess), zeroes gravity / y_velocity when the buoyancy
  pushes up, bob, buoyancy rise, air timer / drowning, swim pitch, bottom exit. 75 setups, mutants 92/95 (2
  equivalent, 1 harness-blind). Callees all C.
- func_151AC628 `debris_chunk_emit` / func_151ACBCC `debris_dust_emit` (1D9C00; D_8008ADA0 handlers 0xB / 0xC,
  return 1): mutants 46/47 (1 equivalent) and 29/29.
- func_1519FD60 `foot_trail_update` (1CCD10, D_8008A5DC handler 5): mutants 71/71.
- func_151AABC4 `footstep_splash` (1D7790): s32 returning 0 because game_981E0 calls it without a prototype
  (implicit int); tested as a void variant; mutants 40/40.
- Checks: verify_all rc 0, NM links, protocheck 0 (1307), selftest 65/65; voidret_scan no new suspect.
  progress_nm total 5301/5915 (89.6%), game 4767/5334, C bytes 74.2%, 614 asm-only.

## Next steps (from P191)

1. Browser (port-web): func_1504B0FC on level 0 noev (no rise) and level 0x29 25889 (control kept); then the P191.md
   UNVERIFIED list (debris, foot trails, footstep splashes).
2. game_981E0 owner: add `s32 func_151AABC4(struct127 *, s32);` (no prototype today).
3. port-b breadth (`p168/asmlist.py`): func_15082278 (466, AF2A0), func_150B2C20 (477, E0430), func_150CA150 (504,
   F6060), func_151D3A30 (564, 201240), func_151C0698 (669, 1EDA00).

## State (session P190, 2026-10-24). Details: `docs/port/sessions/P190.md`

- **func_150A4FE4** obj_floor_mesh_update (game_eu_D1760, 295, Rare hand asm): readable hand C (NM) verified with the
  new whole-function harness `tools/port/difftest/nmasm_objmesh4FE4.py` (VR4300 ref vs NM ELF, allocate_memory / free
  as a shared MIPS stub with a log in RDRAM): 860 trials EQUIV, NM mutants 24 killed + 1 crash + 1 equivalent
  (`docs/port/sessions/p190/mutnm.sh` runs mutants through a harness).
- **func_15189F70** area_drift_emitter_update (game_eu_1B7680, 303; D_8008B848 type 0x1A update): EQUIV random + 17
  setups, mutants 32 / 32.
- Breadth (hand C, NM, EQUIV + setups + mutants): func_151F9150 mp3util_get_bits (hand asm), func_150E394C,
  func_151A4B40 (prototype now void), func_15063920, func_151CC784, func_1508CE28 (table in P190.md).
- Checks: verify_all OK (code build, check_files, full ROM OK) after the last code edit, NM links (rc 0), protocheck 0
  (1309 NM bodies), selftest 65/65, progress_nm 5303/5915 (89.7%), C bytes 73.3%. No difftest processes left.
- game_eu_1CCD10.c / game_eu_1D7790.c moved to port-b (not touched; added to p190/asmlist.py's forbid list).

## Next steps (from P190)

1. Browser: P190.md section 4 (area 3 floors on moving objects, drifting particles, mp3 music / speech).
2. Breadth: p190/asmlist.py smallest first (next: func_1509D274 49, func_151AF820 50, func_1507E8E0 50, func_15088760 /
   func_15088360 (B37F0), func_150F58C0, func_150637B4, func_15007558, func_150B7B9C); P138 / P141 leftovers.
3. func_1505D1C4 (game_83300) return: coordinate with port-b (unchanged from P182).
4. Other hand-asm functions with C callers can follow the nmasm_objmesh4FE4.py + mutnm.sh pattern.

## State (session P189, 2026-10-24, port-web). Details: `docs/port/sessions/P189.md`

- Diagnostic only (no merges, no src_eu edits). New flags: `?p189y=F` (Conker y / vy / gravity / water log),
  `?p189swim=1` (TEST: stand-in for func_1504B0FC), `?p189nopush=1` (TEST: `--wrap=func_150511E8` no-op), p158 dumps log
  LOADTLUT and the CI8 palette (`[p189pal]`) and get their own texel budget.
- **Level-0 rise (noev) = the asm stub func_1504B0FC** (swim update, called each frame by the C func_1504CB98 while
  in_water != 0): Conker walks into water at 1481, gravity -3 (buoyancy) and nothing clamps at the surface. `?p189swim=1`
  removes the rise. func_151AC628 / func_151ACBCC are only the water-entry splash particles (func_151AA250 ->
  func_151AC3F0 -> func_1514CBE8 -> D_8008ADA0 0xB / 0xC). The new part from the merges: the post-death respawn now lands
  in water (func_1504B0FC first hit 933, +80 frames to 0x2C); not bisected; not func_150511E8.
- **Level 0x29 at 25889 = the same**: Conker falls into the pond (surface -79), in_water 1, rises to y ~1550 (rock wall).
  func_1519FD60 (ripple particle, D_8008A5A0 / 5DC table via func_15147CB0) and func_151AABC4 (swim-stroke splash, anim
  callbacks in game_981E0.c) are cosmetic.
- **Green decal = port renderer**: one draw, CI8 32x32 mip chain, 2-cycle LOD, ALPHA_CVG_SEL; TLUT (256, resolved),
  palette and texels are right (leaf cut-out, 62 % alpha 0), screen shows uniform 00C700 without cut-out. Not fixed.
- Torches: unresolved (candidates func_15189F70, func_151184BC, func_151831CC, func_15116F34).

## Next steps (from P189)

1. Convert func_1504B0FC (game_eu_78230) — fixes both rises. Then re-run noev and padwalk29.
2. Renderer: the 2-cycle CI8 mip / ALPHA_CVG_SEL material (cc 26A004/15FC92F8) renders uniform green: check tiles 1-4
   upload, uTexOn bits, `?p78lodviz=1`.
3. Bisect why the noev respawn after the death at 925 now lands in water (merged P169-P182).
4. Torch flames on level 0x29: log emitter creations (func_151407D0 / func_151DA6F8) on level 0x29.

## P188 (port-b) (session P188, 2026-10-24). Details: `docs/port/sessions/P188.md`

Branch `port-b` (from P186 791adfb). Hand C (NM), all difftest EQUIV + setups + mutants:
- func_15190E08 `drip_emitter_update` (1BE5C0, level 0x29 stub): P186 draft finished; the a3 DIFFER was an unknown
  callee arity (difftest's call regex vs nested parentheses): the draft re-declares func_15143134's 3-argument
  prototype. Rng14 / D_800AA120 moved above it; func_1513F680 declared void (its definition). Mutants 50/50.
- func_15112074 `sky_box_draw` (13DC30, level 0x29 stub, D_80089578 camera callback): mutants 67/69 (2 equivalent).
- func_15177410 `model_light_create` (1A5190; game_3DC30 callers, 16 args): mutants 45/46 (1 equivalent).
- func_151C62D0 `object_gun_fire` (1F4090; void like game_eu_51190's prototype, nobody reads the asm's v0):
  mutants 45/46 (1 harness-blind: dst array order).
- Checks: verify_all rc 0, NM links, protocheck 0 (1302), selftest 65/65; voidret_scan no SUSPECT. progress_nm total
  5296/5915 (89.5%), game 4762/5334, C bytes 73.9%, 619 asm-only.

## Next steps (from P188)

0. COORDINATOR RE-PRIORITY (received end of P188, browser P185, see ~/conker-wt/web/docs/port/sessions/P185.md):
   (a) level 0: player rises forever after func_151AC628 (213 insns) / func_151ACBCC (125) (game_eu_1D9C00, D_8008ADA0
   particle handlers) first run at frame 1473; (b) level 0x29 frame 25889: control lost when func_1504B0FC
   (78230, called by C func_1504CB98), func_151AC628 / func_151ACBCC, func_1519FD60 (1CCD10) and func_151AABC4
   (1D7790, 126) run. Order: func_151AC628 + func_151ACBCC (check what they write that the C caller reads), then
   func_1504B0FC, then func_1519FD60 / func_151AABC4. Note: 1504B0FC and 1519FD60 already show an `#else` before
   their pragma (check whether an NM body exists / whether the files are port's in-flight before taking them).
1. Browser (port-web): P188.md UNVERIFIED list (drips, sky box, model lights, gun fire bone-path vectors).
2. port-b breadth (`p168/asmlist.py`): func_15082278 (466, AF2A0), func_150B2C20 (477, E0430), func_150CA150 (504,
   F6060), func_151D3A30 (564, 201240), func_1504B0FC (591, 78230), func_151C0698 (669, 1EDA00).
3. Other slots' level 0x29 stubs (P186 list): func_150D0C40 (FE450), func_15008E10 (362B0), func_1514D3B0 (17A800),
   func_150A4FE4 (D1760), func_151925C4 (1BF960), func_1000A750 (init_A420), func_15189F70 (1B7680).

## State (session P187, 2026-10-24). Details: `docs/port/sessions/P187.md`

- Hand C (NM), difftest EQUIV + setups + mutants (table in P187.md): the three port stubs behind func_1506B04C's
  handlers **func_151B78D8** obj_attached_glow_spawn (game_eu_1E40E0; D_8008FF30 = 2 C handlers with matching
  `s32 (u8 *, void *)`), **func_151BBBCC** shot_impact_effects (game_eu_1E7CC0; keyframe tables as `static const`),
  **func_151043C0** ground_explosion (game_eu_131BD0); level 0x29 breadth **func_1514D3B0** obj_state_event_dispatch
  (game_eu_17A800), **func_15192150** obj_dust_effect_spawn + **func_151925C4** obj_dust_effect (game_eu_1BF960,
  producer with its caller), **func_1000A750** path_sound_pan_volume (init_A420).
- Stubs still reached through func_1506B04C: func_151D3A30 (port-b), func_151522DC (port-b, from func_151BBBCC).
- Checks: verify_all OK (code build, check_files, full ROM OK) after the last code edit, NM links (rc 0), protocheck 0
  (1302 NM bodies), selftest 65/65, progress_nm 5296/5915 (89.5%), C bytes 73.1%. No difftest processes left.

## Next steps (from P187)

1. Browser: P187.md section 5 (effect handlers 2 / 11 / 12 / 14, level 0x29 state events, dust, path sounds).
2. func_15189F70 (game_eu_1B7680, 303; level 0x29 list, no C caller so asmlist.py skips it).
3. func_150A4FE4 (game_eu_D1760, 295) is hand-written asm: needs an nmasm whole-function harness (or the asm2c
   stopgap by user decision), not hand C.
4. func_1505D1C4 (game_83300) return: coordinate with port-b (unchanged from P182).
5. Breadth: p187/asmlist.py (smallest first); P138 / P141 leftovers.

## P186 (port-b) (session P186, 2026-10-24). Details: `docs/port/sessions/P186.md`

Branch `port-b` (from P183 6d46bb1). Hand C (NM):
- func_15178CC0 (game_eu_1A5D10, now port-b's): NM branch passes (arg0, arg1, arg2) to func_15168118 (dropped args).
- func_15168118 `billboard_sprite_draw` (1944C0): difftest EQUIV + 15 setups + mutants.
- func_150A55A0 `mesh_dl_cull_copy` (game_eu_D2DB0, taken by port-b): Rare hand asm (+ loop func_150A563C, now
  `#ifndef NON_MATCHING`); whole-function harness `docs/port/sessions/p186/nmasm_mesh55a0.py` EQUIV + mutants.
- func_15183800 `weather_effect_start` (1B1010): difftest EQUIV + 17 setups + mutants 29/29.
- Checks: verify_all rc 0, NM links, protocheck 0 (1298), selftest 65/65; voidret_scan no SUSPECT. progress_nm total
  5292/5915 (89.5%), game 4758/5334, C bytes 73.6%, 623 asm-only.

## Next steps (from P186)

1. Browser (port-web): P186.md UNVERIFIED list (sprites, culled world meshes, weather effect starts).
2. func_15190E08 (449, game_eu_1BE5C0, level 0x29 stub): draft `p186/d_0e08.c`; DIFFER only on the leftover a3 of
   the func_15143134 call (harness arity); hoist Rng14 / D_800AA120 above it, then setups (P186.md section 2).
3. port-b breadth (`p168/asmlist.py`): func_15177410 (417, 1A5190, 6 calls), func_151C62D0 (425, 1F4090),
   func_15082278 (466, AF2A0), func_150B2C20 (477, E0430); func_15112074 (651, 13DC30, level 0x29 stub).
4. Other slots' level 0x29 stubs: func_150D0C40 (FE450), func_15008E10 (362B0), func_1514D3B0 (17A800),
   func_150A4FE4 (D1760), func_151925C4 (1BF960), func_1000A750 (init_A420), func_15189F70 (1B7680).

## State (session P185, 2026-10-24, port-web). Details: `docs/port/sessions/P185.md`

- Merged port f9c552b (P169-P182) and port-b 4c2d5a5 (P170-P181): HANDOFF.md conflicts only. After each: verify_all OK,
  NM link OK, protocheck 0 (1309 NM bodies), float-int 0 bugs, census 0 FAIL (clean rebuild). arity +2 rows
  (func_150F0448, func_1515C388), m2c_sanity +21 (func_1510C4E0 width high x3).
- **vbe.py aligns stack slots like IDO** (`Pass.do_alloca`: align >= 4, sizes padded to words; 3852 allocas): event
  structs keep their ids (P178 bug in func_1509B8FC gone), BF finishes and stops, level 0x29 loads once. wasm -0.9 %.
- New vbe.py site **k0_add_sites** (func_151F3C4C mixer read callback: `+ 0x80000000` dropped; the C func_15016170 from
  P172 made it run and it trapped at boot).
- Test wraps removed: `?p171fix`, `?p174fix` (p174ev logging kept), `?p178fix` (p178_path.c deleted; its s32 wrap of the
  now-void func_150170C4 broke wasm-emscripten-finalize), `?p178evid`.
- **New game with no flags follows the real route** to level 0x29 scene 1 (22771) and gameplay (23937); walking works
  (fence, slope, camera, sfx) until 25889, where stubs func_1504B0FC / func_151AC628 / func_151ACBCC / func_1519FD60 /
  func_151AABC4 take over and player control is lost.
- **Regression: noev level 0, the player rises forever** from ~1550 (node + Chrome; after the merges, not the alignment).

## Next steps (from P185)

1. Bisect the level-0 rise (P185 6.1) over the P169-P182 merged files (scratch worktree, node noevL with p81look).
2. Convert func_1504B0FC (game_eu_78230, called by C func_1504CB98) and the D_8008ADA0 handlers func_151AC628 /
   func_151ACBCC (1D9C00), func_1519FD60, func_151AABC4 (level 0x29 at 25889).
3. func_15078A60 (path follow), func_15116F34, func_151184BC, func_150D0C40, func_15008E10, func_151831CC.
4. Green ground decal / unlit torches on level 0x29; DL stubs func_15113D54 / func_15112074.
## State (session P184, 2026-10-24). Details: `docs/port/sessions/P184.md`

- Hand C (NM), difftest EQUIV + setups + mutants (table in P184.md): **func_15170A70** spark_particle_spawn
  (game_eu_19B180; the only stub the P182 ambient emitters reached), **func_1506B04C** obj_effect_dispatch
  (game_eu_981C0; table D_800864B0 = 15 C handlers; func_1506AEA0 now takes the dispatch arguments `(u8 *, void *)`),
  **func_150D0C40** level_ambient_cue_update (game_eu_FE450, level table D_8008D0A4[14]), **func_15008E10**
  area_points_alloc (game_362B0), **func_150611E8** path_face_nearest_segment (game_83300; browser P178 level 0x29 path
  reader; NM hoisted prototype added), **func_151B76F4** obj_smoke_puff_spawn (game_eu_1E40E0, effect handler 8).
- Stubs still reached through func_1506B04C's C handlers: func_151BBBCC, func_151D3A30 (port-b), func_151B78D8,
  func_151043C0.
- Checks: verify_all OK (code build, check_files, full ROM OK) after the last code edit, NM links (rc 0),
  protocheck 0 (1295 NM bodies), selftest 65/65, progress_nm 5289/5915 (89.4%), C bytes 72.9%. No difftest processes left.

## Next steps (from P184)

1. Browser: P184.md section 5 (sparks / flare-ups, object effects, level 0x29 cue sounds and path turning).
2. func_151B78D8 (game_eu_1E40E0, 212): check its D_8008FF30 handler table first, then convert; func_151BBBCC
   (1E7CC0, 288), func_151043C0 (131BD0, 204): the other stubs behind func_1506B04C (func_151D3A30 is port-b's).
3. func_1505D1C4 (game_83300) return: coordinate with port-b (unchanged from P182).
4. Breadth: p184/asmlist.py (skipped: func_150882C4 port-b caller prototype; libultra / hand-written asm).
5. P138 / P141 leftovers.

## P183 (port-b) (session P183, 2026-10-24). Details: `docs/port/sessions/P183.md`

Branch `port-b` (from P181 4c2d5a5).
- **Debug hooks** func_1511FC2C / func_1511FC44 (coordinator decision): NM-only real signatures
  `Gfx *(Gfx *, f32, f32, f32, f32, s32)` / `Gfx *(Gfx *, f32, f32, f32, s32)` in `include/functions.h` and, because
  that file includes functions.h, in their definitions in `src_eu/game/done/game_14D0D0.c` (outside the brief's file
  list; NM-only, default build unchanged). The asm passes three f32 in a1..a3 by mfc1 (first argument is a pointer).
- Hand C (NM), difftest EQUIV + setups + mutants: func_15113D54 `world_mesh_draw` (13DC30), func_1514B8D4
  `lava_splash_effect` (1772D0; game_A28B0 prototype `void` -> `s32` under NM), func_151279A0 `player_aim_look`
  (14FF90), func_151ACBD4 `light_column_create` (1D9C00), func_15078A60 `script_test_object_value` (A28B0).
- Skipped func_15168118 (game_1944C0): its C caller func_15178CC0 (game_eu_1A5D10.c, not port-b's) drops a1 / a2.
- Checks: verify_all rc 0 (default build byte-identical), NM build links, protocheck 0 (1295 bodies), selftest 65/65.
  voidret_scan on the caller files: no SUSPECT. progress_nm total 5289/5915 (89.4%), game 4755/5334, C bytes 73.4%,
  626 asm-only. No difftest / mut.sh processes left.

## Next steps (from P183)

1. Browser (port-web): P183.md UNVERIFIED list (world meshes, lava splash, aim look, light columns, script tests).
2. Owner of game_eu_1A5D10.c: func_15178CC0 must pass (arg0, arg1, arg2) to func_15168118 under NM; then port-b can
   convert func_15168118 (337, game_1944C0).
3. port-b breadth (`python3 docs/port/sessions/p168/asmlist.py` after `progress_nm.py --list > port_work/p162/asmonly.txt`,
   drop game_eu_1C3530 rows): func_15183800 (392, 1B1010), func_15177410 (417, 1A5190, 6 calls), func_151C62D0 (425,
   1F4090), func_15082278 (466, AF2A0), func_150B2C20 (477, E0430).
4. func_150A55A0 (game_eu_D2DB0, not port-b's) is still asm and is called by world_mesh_draw and game_eu_138E00.

## State (session P182, 2026-10-24). Details: `docs/port/sessions/P182.md`

- **func_1517C11C ambient_emitters_update** (game_eu_1A9280, 1286 insns) hand C (NM), from the P104 draft re-checked
  against the asm: random EQUIV, 51 setups x 2 seeds EQUIV (ROMDATA: real updaters / rows / sound info; ARGMEM on
  every updater call), mutants 67 / 68 + 1 equivalent. The level ambient emitter system is now C end to end
  (func_1500BEC0 unit + sort + this consumer). Stub reached: func_15170A70 (particle, asm). Caller func_1517E3CC's NM
  prototype now `void`.
- Dropped-return suspects: func_100126E8 real -> returns func_15043CA4's length (matching C, byte-identical);
  func_15060F28 / func_1506160C / func_1506E5FC not defects (details P182.md section 2).
- Breadth (hand C, NM, EQUIV + setups + mutants all killed): func_15043BB8 text_queue_put, func_15043CA4
  text_queue_get (game_70200), func_150F7890 / func_151007B0 / func_151D7AE8 linked-object event handlers,
  func_15104A0C obj_fog_alpha_gfx, func_1506AEA0 players_effect_at_point, func_150B7170 hud_box_reset (file prototype
  now void).
- Checks: verify_all OK (code build, check_files, full ROM OK) after the last code edit, NM links (rc 0), protocheck 0
  (1289 NM bodies), selftest 65/65, progress_nm 5283/5915 (89.3%), C bytes 72.7%. No difftest processes left.

## Next steps (from P182)

1. Browser: P182.md section 5 (ambient emitters with sounds, debug text queue, func_150B7170).
2. func_15170A70 (game_eu_19B180, asm): spark / flare particle spawner the emitters now call.
3. func_1505D1C4 (game_83300) return: coordinate with port-b (prototypes in game_eu_201240 / 110DB0 / 12D5D0).
4. Breadth: p182/asmlist.py; skipped func_150882C4 (port-b caller prototype), func_1506B04C (check the D_800864B0
   handlers first).
5. P138 / P141 leftovers.
## P181 (port-b) (session P181, 2026-10-24). Details: `docs/port/sessions/P181.md`

Branch `port-b` (from P179 9ddc1a9).
- **Merge** of `port` at b8b9829 (P165-P176) -> d6105ff. Conflict only in HANDOFF.md (merge_union.py, P176 section
  reordered by hand); no code conflicts. verify_all rc 0, NM links, protocheck 0 (1285), selftest 65 ok.
- Hand C (NM), difftest EQUIV + setups + mutants: func_1510C4E0 `dl_find_texture_vertices` + func_1510CA2C
  `tex_scroll_create` (138E00, producer + consumer together), func_15150970 `spark_burst_spawn` (17D3C0),
  func_150F0448 `smoke_emitter_spawn` + func_150EF500 `fire_effect_start` (11CB90; file prototype of func_150EF500
  `void` -> `u8 *`, default build byte-identical).
- Harness notes: DIFFTEST_RET entries are comma-separated (a space silently breaks the knob line); per-call
  out-param values need OUTW (OUTA writes the same array on every call); stale-v0 functions kept `s32` for the
  callers' prototype can be verified with a `void` copy of the draft (the harness then skips v0).
- Checks: verify_all rc 0 (default build byte-identical), NM build links, protocheck 0 (1290 bodies), selftest 65/65.
  progress_nm total 5284/5915 (89.3%), game 4750/5334, C bytes 73.1%, 631 asm-only. No difftest processes left.

## Next steps (from P181)

1. Browser (port-web): P181.md UNVERIFIED list (texture scroller at level load; fire / smoke / spark effects).
2. func_15113D54 (301, game_eu_13DC30): decide how to call the debug hooks func_1511FC2C / FC44 (float bits in
   a1..a3 + 2 stack args, functions.h has 4 s32 args) before converting (P181.md section 3).
3. port-b breadth (`python3 docs/port/sessions/p168/asmlist.py` after `progress_nm.py --list > port_work/p162/asmonly.txt`):
   func_1514B8D4 (312, 1772D0), func_151279A0 (326, 14FF90), func_15168118 (337, 1944C0), func_151ACBD4 (360, 7 calls),
   func_15078A60 (363, A28B0).

## State (session P180, 2026-10-24). Details: `docs/port/sessions/P180.md`

- **func_1500BEC0 unit done** (one commit): hand C (NM) for func_1500BEC0 ambient_emitters_build, func_1500AD84
  ambient_slot_setup, func_1500AF08 ambient_emitter_add, the six D_8008D258 placers func_1500B1F4 / B714 / B8F4 / BAB8 /
  B3B0 / BC7C (func_1500AF08 is not in the table) and func_1517BE0C ambient_emitters_sort. difftest EQUIV (random +
  setups, ROMDATA), mutants 107 / 109 (2 equivalent). No stubs reached. game_3B920 NM prototype `void func_1500BEC0(void)`.
- Dropped-return fixes (port-b P179 scan): 12 functions now return their tail call's value (func_1516387C, func_150408CC,
  func_150ED7B4, func_150FF808, func_1513092C, func_1515DB1C, func_151B8C18, func_1500F240, func_150870E0,
  func_1509FA88 / FB90 / FBC8); default build byte-identical. func_1505D1C4 real but its prototypes are in port-b files.
- P90 func_150268BC setup s5F_4 (UNSURE) is EQUIV after the P176 page-end stub fix.
- Checks: verify_all OK (code build, check_files, full ROM OK) after the last code edit, NM links (rc 0), protocheck 0 (1280 NM
  bodies), selftest 65/65, progress_nm 5274/5915 (89.2%), C bytes 72.4%. No difftest processes left in conkerdev-port.

## Next steps (from P180)

1. func_1505D1C4 (game_83300) should return func_1505C7D8's s32: coordinate with port-b (prototypes in game_eu_201240.c,
   game_eu_110DB0.c, game_eu_12D5D0.c). func_100126E8 (inner asm func_15043CA4), func_15060F28 / func_1506160C /
   func_1506E5FC (SUSPECT2): check.
2. func_1517C11C (game_eu_1A9280, 1286 insns): per-frame consumer of the sorted emitters (P104 draft).
3. Browser: level ambient emitters (P180.md section 6), the 12 return fixes.
4. Breadth (p180/asmlist.py, forbid list now includes port-b P179 names game_40490 / game_39750 / game_1897A0 / game_eu_126330).
5. P138 / P141 leftovers.

## P179 (port-b) (session P179, 2026-10-24). Details: `docs/port/sessions/P179.md`

Branch `port-b` (from P177 fc67ce4).
- **Dropped-return audit**: `docs/port/sessions/p179/voidret_scan.py` (default-ELF asm: callee v0 / f0 at `jr ra`,
  caller reads after each `jal`, transitive through `return g()` callers). port-b files: 890 void C functions,
  **1 real dropped return, fixed**: func_15079A98 `path_point_angle` (game_A28B0, matching C) now returns the u16
  angle its asm caller func_15079B30 stores (default build byte-identical). Other files: 16 SUSPECT + 3 SUSPECT2 for
  port / coordinator (list in P179.md section 1, `p179/scan_others.tsv`). tablesig re-run: nothing in port-b files.
- Hand C (NM), difftest EQUIV + setups + mutants: func_150FD140 `view_sparkle_burst` (12A7C0; prototype now
  `void (u8)`), func_15081120 `object_reach_hit` (AE930; NM prototype kind s32), func_150511E8 `swim_push_update`
  (78230), func_15152700 `particle_burst_spawn` (17D3C0), func_151D535C `object_take_hit` (201240),
  func_15100304 `gun_shot_sparks` (12D5D0).
- Harness notes: `difftest.sh F draft --self` ignores the draft (use no `--self` for matching-C drafts); OUTA with
  several out-params of one callee uses `ADDR=5:W/6:W` (a second `ADDR=` entry replaces the first).
- Checks: verify_all rc 0 (default build byte-identical), NM build links, protocheck 0 (1232 bodies), selftest 62/62. progress_nm total 5226/5915 (88.4%), game 4695/5334, C bytes 70.7%, 689 asm-only. No difftest processes left.

## Next steps (from P179)

1. Port / coordinator: the 16 SUSPECT rows of `p179/scan_others.tsv` (other slots' files), e.g. func_10010F88,
   func_1505D1C4, func_15195FB0 (1C3530), func_1509FBC8 / func_1500F240 (NM bodies).
2. Browser (port-web): P179.md UNVERIFIED list.
3. port-b breadth (`python3 docs/port/sessions/p168/asmlist.py` after `progress_nm.py --list > port_work/p162/asmonly.txt`,
   drop game_eu_1C3530): func_1510CA2C (255, 138E00), func_150EF500 (259, 11CB90), func_15150970 (259, 17D3C0),
   func_15113D54 (301), func_1514B8D4 (312).

## State (session P178, 2026-10-24, port-web, diagnostic). Details: `docs/port/sessions/P178.md`

- **Producer of D_800D2104 / D_800D2528 (EU 0x800D2524 / 0x800D2528) = asm stub func_150170C4** (game_eu_44010.c,
  called only by the C level loader func_15016950). `docs/port/sessions/p178/stscan.py` (constant propagation over all
  asm) finds no other store to either word. It allocates the per-spawn-record path tables (player records: 0x10-byte
  path, count 2; level records from asset (2, 0x10, level) = {offset, count} entries). Convert it (spec in P178 1; test
  body `port/gfx/p178_path.c`, `?p178fix=1`).
- With `?p174fix=1&p171fix=1&p178fix=1` the scene-3 trap is gone: the intro plays scene 3 / 4 / 2 on level 0x1D,
  scene 0x14 on level 6, scenes 2 / 4 on level 0x18, then BF changes to **level 0x29**, which then reloads every 4
  retraces until the heap breaks (24343).
- Cause: **every event struct has id 0** (func_1509B8FC, game_C8950.c: the s16 parameter copy at (sp+14)^2 = sp+12 is
  overwritten by func_1502B5C8's 32-bit out-param store into the 2-aligned `s16 sp18[2]` at sp+10, a vbe stack-layout
  bug). func_1509B704 never finds an event, so finish / stop actions fail and starts load duplicates (two BF copies).
  Test `?p178evid=1` puts the id back.
- With `?p178evid=1` too (node fixF, Chrome chB, without ?p103boot): level 0x29 loads once, its scene 1 (Conker hung
  over) plays 22771-23937, then gameplay on level 0x29 (Conker by the fence), no trap / heap error to 28337 / 27966.
- `?p103boot` Chrome run trapped at 19183 inside the P116 / P121 logger in `__wrap_func_1502457C` (diagnostic only).
- Regression node noev: death 925, 0x2C 1249, level 0 1329, heap 0 errors, null zone clean, no trap (= P174).

## Next steps (from P178)

1. Convert **func_150170C4** (game_eu_44010.c) from the asm (P178 1).
2. **vbe.py: align every alloca to 4** (fixes func_1509B8FC's lost event id and any other sub-word stack slot next to a
   2-aligned array used as a word); full port rebuild (delete vbe.stamp) + noev / new-game regressions. Alternative,
   local: `s32 sp18` in func_1509B8FC (src_eu).
3. P174 blockers 1 / 2 (func_1509CBD8 s32 return, func_1509DFCC case 0x19) still needed.
4. Level 0x29 stubs: func_15078A60 (game_A28B0.c path follow, jump table; reads D_800D2104), func_1513FAB4,
   func_150D0C40, func_15008E10; then walk on level 0x29 with pad input.
## P177 (port-b) (session P177, 2026-10-24). Details: `docs/port/sessions/P177.md`

Branch `port-b` (from P175 dd78307). Hand C (NM), difftest EQUIV + setups + mutants (table in P177.md):
- **Beam break unit** (game_eu_1F4F60.c): func_151C8D90 `beam_hits_object` and func_151C8F4C `beam_hit_effects`.
  **Not dead** (P175 next step 3): both are called by the beam message handler func_151C8C5C (C; message 0x20 hit test
  then effects, 0x3A case 2 effects with obj NULL). Its forward declarations are now `(u8 *, u8 *)`.
  The scorch-mark positions are the beam end points (the asm stores v0 = rec + 0x34 / + 0x40 in the delay slots of
  the func_1515016C calls).
- func_1516547C `screen_effect_preset` (game_eu_192500.c; the only asm callee of beam_hit_effects): 8 presets of a
  15-float block for func_15165B98; kind >= 8 returns NULL (asm: stale v0). Mutants 32/32.
- func_1518D1C0 `character_effect_attach` (game_eu_1BAF40.c, browser P171 boot / title stub): effect types 1..18
  -> kind-0x21 effect record (func_1518E934), optional clear of obj's existing ones. The in-file prototype (2 copies,
  s32 / s32 * args) is one `u8 *(u8 *, s16, s16, u8, u8, s32, char *)`; its two matching callers func_1518EBDC /
  func_1518EC44 now pass typed args (default build byte-identical).
- tablesig v2 on port-b HEAD: flagged 47 -> 43, no new flagged table, nothing to fix in port-b files.
- Checks: verify_all rc 0, NM build links, protocheck 0 (1226 bodies), selftest 62/62. progress_nm total
  5220/5915 (88.3%), game 4689/5334, C bytes 70.5%, 695 asm-only. No difftest processes left.

## Next steps (from P177)

1. Browser (port-web): P177.md UNVERIFIED list (beam break effects, screen effect presets, character effects).
2. port-b breadth (`python3 docs/port/sessions/p168/asmlist.py`, drop game_eu_1C3530 rows): next smallest owned asm
   with C callers: func_150FD140 (215, game_eu_12A7C0, 3 C calls: per-view effect with func_15154728 + a spark loop),
   func_15081120 (219, AE930), func_150511E8 (220, 78230), func_15152700 (228, 17D3C0, 15 C calls), func_151D535C (231).
3. mut.sh: mutant lines are split at `%` (sed expressions with `% 9U` become SED ERROR); mutate the constants instead.

## State (session P176, 2026-10-24). Details: `docs/port/sessions/P176.md`

- Merged port-b b235977 (P168 + P170) (b5b4e02): HANDOFF.md only conflict; merge fix: game_eu_1F4F60.c NM prototype of
  func_10010F88 returns u16 (port P167 definition).
- Browser P174 fixes: func_1509CBD8 event_query_scene returns s32 per case (was void: every scene query 0, intro BF
  never started scene 3), func_1509DFCC case 0x19 tests every node (527ead2); func_1509C850 / func_1509DD0C return
  s32 with the asm's defined values (a028320).
- New hand C (NM): func_1507D754 object_destroy_effects (P169 draft), func_150039E0 world_objects_load (741),
  func_15006590 save_slot_unpack (407). difftest EQUIV + mutants (P176.md).
- difftest harness: stubs on the last word of a page (func_151CFFFC) no longer fault (delay-slot block was taken for a
  second call); DIFFTEST_PAGESTUB_OLD=1 = old; selftest 65/65.
- Checks: verify_all OK, NM links, protocheck 0 (1270 NM bodies), progress_nm 5264/5915 (89.0%), C bytes 72.2%.

## Next steps (from P176)

1. func_1500BEC0 unit (func_1500AD84 + D_8008D258 handlers + func_1517BE0C, ~1270 insns) - not started.
2. Browser: intro scene 3 (BF) now starts; func_150623F4 trap / D_800D2104 / D_800D2528 producer is P178's.
3. Browser checks: level world objects (func_150039E0), save load (func_15006590), break effects (func_1507D754).
4. Earlier UNSURE results with "both sides fault at 0x00000000" next to a page-end callee may be re-run now.
5. P138 / P141 leftovers.

## P175 (port-b) (session P175, 2026-10-24). Details: `docs/port/sessions/P175.md`

Branch `port-b` (from P170 b235977). Hand C (NM), difftest EQUIV + setups + mutants (table in P175.md):
- **Kind-8 streak particle** (commit a6d93bd, game_1897A0.c): func_1515C388 `particle_streak_step` and
  func_1515C6F4 `particle_streak_draw`; the draw now **returns the advanced Gfx pointer** (browser P171 null-zone DL
  writes from 6257). The step's motion handler D_8008B420[block +0x38] gets (rec, block) (asm a1 = block).
  Mutants 16/16, 38/38.
- **Beam unit** (game_eu_1F4F60.c): func_151C7B1C `beam_create` (now `u8 *` with u8 / s16 args; the prototype in
  func_151C7750's NM block updated, one line for protocheck), func_151C9748 `beam_end_pieces_spawn`, func_151C957C
  `beam_glow_spawn`. Piece pointers NULL-initialised before func_151C9748 (N64 leaves garbage when func_15144E80 fails).
- Reviews (no change): m2c_sanity func_1500D8C8 width high = false positive (asm word copy of the u16 table to the
  stack, then lhu); the 3 arity rows on func_1516AFE0's callback = false positives (a3 is a temp; the only callback,
  func_15080BF4, is `void (s32, s32, s32)` and uses a2).
- Checks: verify_all rc 0, NM build links, protocheck 0 (1222 bodies), selftest 62/62. progress_nm total 5216/5915
  (88.2%), game 4685/5334, C bytes 70.2%, 699 asm-only. No difftest processes left.

## Next steps (from P175)

1. Browser (port-web): kind-8 streak particles render, null zone clean after 6257; beams from record_beam_start
   (D_80082EA0 entry 8) if a level has one. P175.md UNVERIFIED list.
2. port-b breadth: `python3 docs/port/sessions/p168/asmlist.py` (owned asm with C callers), smallest first.
3. game_eu_1F4F60.c still has asm func_151C8D90 / func_151C8F4C (no references found in .data / C).
## State (session P174, 2026-10-24, port-web, diagnostic). Details: `docs/port/sessions/P174.md`

- Level 0x22 (the "first room") is the **death tutorial**: one level event 0xCA "First Death". After Gregg's scenes it
  waits for the scene to end (`0x1001(1)`, func_1509CBD8), then for **the squirrel tail to be collected** (`0xE019(4)`,
  func_1509DFCC: no node of lists 0x36 / 0x4C / 0x5B with +0x48 == 2; the tail hangs under the gargoyle at
  (-421, 170, -21)), prints "LIFE COLLECTED", plays scene 4, then returns to the saved level (0x18).
- Blockers (both batch m2c NON_MATCHING bodies): **func_1509CBD8** (game_eu_CA060.c) is `void`, every scene query
  answers 0; **func_1509DFCC** (game_eu_CA630.c) case 0x19 reads +0x48 of node->next (skips the tail, reads NULL+0x48).
  func_1509CBD8 also causes the detour itself: the intro event BF never starts scene 3 at 10725, Conker falls
  (y -4759) and dies at 10813 -> level 0x22.
- Test `?p174fix=3` (asm answers inside event CA only) + padpull.py (walk forward + jump at the pillar): tail collected
  at 18613, scene 4, **level 0x22 left at 19113** (node evJ and Chrome chJ), back to level 0x18 (intro restarts). No B /
  context action needed.
- With the fix everywhere (`?p174fix=1`) the real route runs scene 3 of level 0x18 and traps at 10733 in func_150623F4
  (game_83300.c): D_800D2104 / D_800D2528 (EU 0x800D2524 / 0x800D2528) are NULL; producer unknown.
- New diagnostic port/gfx/p174_ev.c (`?p174ev`, `?p174fix=1|2|3`, 4 wraps). noev regression = P171.

## Next steps (from P174)

1. Conversion slot: real C for func_1509CBD8 (s32, 6 cases) and the func_1509DFCC case-0x19 loop fix, together.
2. Then the scene-3 trap: find the producer of D_800D2104 / D_800D2528 for level 0x18 (path tables), check
   func_150623F4's C against the asm.
3. Still open from P171: func_15147F50 / func_15147FA0 record argument, func_1515C388 / func_1515C6F4.

## State (session P173, 2026-10-24). Details: `docs/port/sessions/P173.md`

- **Browser P171 new-game trap fixed (7cdb22a, own commit)**: func_15147F50 / func_15147FA0 (game_eu_1754C0, matching
  C) pass the record to the D_8008A690 / D_8008A6E0 handlers under NON_MATCHING (all 40 entries C, void, 1 arg);
  EQUIV on 6 setups, NULL-argument mutant killed. Default build unchanged.
- New hand C (NM), difftest EQUIV + mutants: func_150A00F0 slots_reset, func_15086058 point_bands_build,
  func_eu_1501B640 model_vertex_colours_blend (title / opening stub, 89 calls), the level-load vertex colour backup
  func_15012760 level_vertex_colours_backup + func_15012C34 vertex_colours_store + func_15012E88 dl_env_colours_list
  (P165 scene-start stubs). No stubs reached. game_3B920 NM `void func_15012760(void)`.
- libultra / init with C callers: the port provides the libultra ones natively (list in P173.md section 5); remaining
  game-specific init stubs: func_1000C530, func_10001550, func_1000A750; func_10005B04 is hand asm (TLB page pool).
- Checks: verify_all OK (code build, check_files, full ROM OK) after the last code edit, NM links (rc 0), protocheck 0
  (1259 NM bodies), selftest 62/62, progress_nm 5253/5915 (88.8%), C bytes 71.3%. No processes left in conkerdev-port.

## Next steps (from P173)

1. func_1500BEC0 as one unit with func_1500AD84, the D_8008D258 handlers (func_1500AF08 / B1F4 / B3B0 / B714 / B8F4 /
   BAB8 / BC7C) and func_1517BE0C (~1270 insns; level-load sound emitters).
2. func_150039E0 (30E90, 741), func_15006590 (33990, 407, save unpack with __ll_lshift / __ull_rshift).
3. port-b: func_1515C388 / func_1515C6F4 (game_1897A0, browser P171 item 2) are in port-b's next steps; not touched.
4. Browser: new game past 6241, level vertex colours, title model colour blend (P173.md section 7).
5. func_1507D754 (P169 draft) once port-b's func_151C9740 / func_151CFFFC are merged (port-b P170 has them in C).
6. P138 / P141 leftovers (not started).

## State (session P172, 2026-10-24). Details: `docs/port/sessions/P172.md`

- func_15195FB0 (game_eu_1C3530) now returns func_15196344's handle (`s32`, both builds; asm callers func_15116690 /
  func_1511D0CC / func_150BFC60 store v0). Default build unchanged.
- New hand C (NM), all difftest EQUIV + mutants: func_15116690 object_start_pending_anim, the texture-scroll
  registration cluster func_15195DD8 dl_find_scroll_texture / func_15195AA8 level_dl_add_texture_scroll (P165 level-load
  stub) / func_15196344 dl_add_texture_scroll, func_15109990 event_object_effect_spawn, func_15016170
  audio_mixer_init (boot stub), func_15007168 save_data_reset (boot stub), func_1500AC14 ambient_sounds_load and
  func_150170C4 level_entry_data_load (scene-start stubs), func_15116854 object_bob_update, func_1517E6A4
  object_node_remove. No stubs reached.
- NM-only prototype fixes in game_eu_51190 / game_3B920 / game_eu_44010 / game_33990 (func_1500727C no longer passes
  two unused arguments); game_eu_142E40 `void func_15116854(u8 *)`.
- New tools: `docs/port/sessions/p172/asmlist.py` (this slot's asm-only functions with C calls), `mkdraft.py`.
- Checks: verify_all OK (code build, check_files, full ROM OK) after the last code edit, NM links (rc 0), protocheck 0 (1253 NM bodies), selftest 62/62, progress_nm 5247/5915 (88.7%), C bytes 71.1%. No processes left in conkerdev-port.

## Next steps (from P172)

1. func_1507D754: insert the P169 draft once port-b converts func_151C9740 / func_151CFFFC (unchanged).
2. port-b: game_eu_78230.c declares func_150882C4 `s32` (asm returns nothing): fix, then convert it (39 insns).
3. Remaining P165 scene-start / boot stubs in this slot: func_1500BEC0 (38360, 200), func_15012760 (3FF70, 309),
   func_150039E0 (30E90, 741), func_15006590 (33990, 407), func_100052A0 (init_50A0, 195), func_1000BF60
   (init_B1B0, 252), func_eu_1501B640 (48E50, 304).
4. Browser: texture scrolling at level loads, ambient sounds, P172.md section 6.
5. P138 / P141 leftovers (not started).

## State (session P171, 2026-10-24, port-web). Details: `docs/port/sessions/P171.md`

- Merged port-b 6dcbf88 (P164, P168) and port 7b18642 (P166, P167): HANDOFF.md conflicts only. After each: verify_all OK,
  NM link OK, protocheck 0 (1242 NM bodies), float-int 0 bugs, census 0 FAIL after a clean rebuild. arity_scan: the
  func_1501370C row is gone, +3 func_1516AFE0 callback rows; m2c_sanity +3 (func_1500D8C8 width **high**, port-b check).
- **New-game trap at retrace 6241 after the merges**: func_15147F50 (game_eu_1754C0.c, matching C) calls
  `D_8008A690[idx]()` without the record (asm keeps a0); func_15147E64 frees garbage at rec + 0x84. Reached now because
  P164's func_151530A8 creates kind-8 particle records. Port test `?p171fix=1` (p171_tb.c) passes the record: run OK.
  Same shape func_15147FA0 / D_8008A6E0.
- **null+0x14 = 0x400 gone** (P164); the P161 `?p161fix` wrap is removed. New null-zone writer from 6257: the kind-8
  particle draw func_1515C6F4 (asm stub) returns gdl 0, the caller writes its DL at NULL (671 words); its update
  func_1515C388 is a stub too (both game_1897A0.c).
- **Text boxes advance and close** (C func_1516AFE0): the Gregg cutscene's 10 boxes run their states and close by
  script requests (0x100); A / B are ignored by these caller-owned boxes (by design). Boxes invisible (draw asm).
  Control at 18485 as before; after it no box opens, ctx+0x7B stays 0 (now read via vbe_ld8), jumps at the pillar reach
  y 190 by the gargoyle's tongue but nothing triggers: the first room is still closed.
- Regression: node noev 925 / 1249 / 1329, Chrome noev 1530 / 2302 / 2382, heap 0, null zone clean, traps 0.

## Next steps (from P171)

1. Conversion slot: func_15147F50 / func_15147FA0 pass the record under NON_MATCHING (blocker: default new game traps).
2. Conversion slot: func_1515C388 + func_1515C6F4 (game_1897A0.c, kind-8 particle update / draw; the draw returns gdl).
3. func_1516BC2C + func_1516CEA4 (text box draw), then func_1513FAB4, func_151D9014.
4. port-web: first-room puzzle (gargoyle tongue): find the grab / pull trigger in the event script or player code and
   test it with `?p171tb=1&p171fix=1&p165hits=1` (padpull.py); drop `?p171fix` once (1) is merged.
## P170 (port-b) (session P170, 2026-10-24). Details: `docs/port/sessions/P170.md`

Branch `port-b` (from P168 6dcbf88). Hand C (NM), difftest EQUIV + setups + mutants (table in P170.md):
- **Text box draw unit** (commit 851e6f3, game_eu_1984F0.c): func_1516BC2C `text_box_draw` (shadow pass + colour
  pass: box / pointer / thought dots sprites via func_15095380 + func_15095E58, box corner +0x48 / +0x4C, text colour
  D_800D31C8..CA) and func_1516CEA4 `text_box_draw_text` (`Gfx *(Gfx *, box, u8 r, g, b, a)`). Mutants 44/44, 27/27.
- func_1513FAB4 `beam_quad_build` (game_169510; prototype + `(u8 *)` casts in its callers func_1513FA2C / FA70),
  func_151C9740 `object_explode` (game_eu_1F4F60), func_151CFFFC `object_shatter_effects` (game_eu_1FB080),
  func_151D9014 `particle_spawn` (game_2062D0, Gregg cutscene; D_80090070 = no-argument u8 texture getters).
- NM-build pitfall: a local array initializer (`s32 k[7] = {...}`) in game_eu_1FB080 emits a `.data` section the NM
  link discards (link error); read the ROM table (D_800AB320) instead.
- Not touched: game_eu_1C3530.c (moved to port per coordinator).
- Checks: verify_all rc 0, NM build links, protocheck 0 (1217 bodies), selftest 62/62. progress_nm total 5211/5915
  (88.1%), game 4680/5334, C bytes 70.0%, 704 asm-only. No difftest processes left.

## Next steps (from P170)

0. **PRIORITY (coordinator, browser P171), not started in P170 (budget):** func_1515C388 (update) and func_1515C6F4
   (draw) in game_1897A0.c, the kind-8 particle record handlers created by P164's func_151530A8, are asm stubs; the
   draw stub returns 0 as the Gfx pointer and the caller writes its DL at NULL (null-zone writes from retrace 6257).
   Convert both in one commit; the draw must return the advanced Gfx pointer. Also check m2c_sanity "width high" on
   func_1500D8C8 (P164, game_39750): asm word read vs IR halfword.
1. Browser (port-web): text boxes should now be visible (first-room gargoyle); check the shadow / pointer / text
   colour and the thought-dot variant. P170.md UNVERIFIED list.
2. port-b: beam unit func_151C7B1C (24 args) + func_151C9748 (draft `p168/d_9748.c`) + func_151C957C (P168 notes below).
3. Next port-b asm with C callers: `python3 docs/port/sessions/p168/asmlist.py`.

## State (session P169, 2026-10-24). Details: `docs/port/sessions/P169.md`

- Merged port-b 9eebdac (P150-P164) as 53b9728: only HANDOFF.md conflicted (union + sections sorted by session).
  Merge checks: verify_all OK, NM links, protocheck 0 (1240), selftest 62/62.
- D_80089E10 handlers now all `void (f32 x, f32 y, f32 z, f32 dx, f32 dy, f32 dz, u8 *obj)`: func_151348F0,
  func_151AA8BC, func_150C65D8, func_150C6F08, func_150EAB4C (changed parameters unused; default build unchanged).
- New hand C (NM): func_151342BC trail_emitter_update (list-0x28 update, dispatches D_80089E10 / D_80089E40;
  32/32 mutants), func_150E0DF0 object_explode (30/31 + 1 equivalent). Both EQUIV on random + setups; no stubs.
- func_1507D754: verified draft `docs/port/sessions/p169/d754_draft.c` (35/35 mutants), not inserted: func_151C9740 /
  func_151CFFFC still asm here and on port-b 9eebdac.
- Checks: verify_all OK (full ROM), NM links, protocheck 0 (1242), selftest 62/62, progress_nm 5236/5915 (88.5%),
  C bytes 70.9%.

## Next steps (from P169)

1. func_1507D754: insert the P169 draft (game_A9D90.c, NM) once port-b converts func_151C9740 / func_151CFFFC.
2. func_15116690 (game_eu_142E40) needs func_15195FB0 (game_eu_1C3530) to return func_15196344's v0 under NM.
3. Browser: trails / emitters (func_151342BC), explosions (func_150E0DF0), P167's list.
4. Don't `git stash` during an unfinished merge (P169.md section 1).
5. P138 / P141 leftovers (not started).

## P168 (port-b) (session P168, 2026-10-24). Details: `docs/port/sessions/P168.md`

Branch `port-b` (from P164 9eebdac). Re-prioritised by the coordinator (browser P165: first room blocked by text
boxes that open but never advance).
- **func_1516AFE0** `text_box_update` and its every-frame callee **func_1516D1C8** `text_box_place`
  (game_eu_1984F0.c) hand C (NM), one unit: the +0x15 state machine (open / grow / wait / dots / line fade-in /
  shown (A / B on D_800BEB30[0]) / fade-out + next line / close with callbacks 0x2000 / 0x4000 / 0x1000), and the
  box / pointer placement. AFE0: 36 setups EQUIV, mutants 26/26; D1C8: 10 setups EQUIV, mutants 18/20 + 2 equivalent.
- **Not done (budget): the draw func_1516BC2C (1127 words) + its callee func_1516CEA4 (201)** — still asm, so boxes
  now advance / close but are invisible. Structure notes in P168.md.
- m2c_sanity "high" rows func_151A9940 / func_151AC3F0: both false positives (same offset on different bases).
- Checks: verify_all rc 0, NM build links, protocheck 0 (1211 bodies), selftest 62/62. progress_nm total 5205/5915
  (88.0%), game 4674/5334, C bytes 69.5%, 710 asm-only. No difftest processes left.

## Next steps (from P168)

1. Browser (port-web): first room with the C text box update: does the gargoyle dialogue advance with B / close,
   and does the room open? Expect no visible boxes (draw still asm).
2. port-b: func_1516BC2C text box draw + func_1516CEA4 (one unit; P168.md has the layout of the stack sprite block
   and the callees func_15095380 / func_15095E58).
3. port-b (coordinator order): func_1513FAB4 (game_169510, every frame), then func_151C9740 (game_eu_1F4F60) and
   func_151CFFFC (game_eu_1FB080) (last port-b asm callees of port's item switch func_1507D754), then func_151D9014
   (game_2062D0, Gregg cutscene).
4. port-b: beam unit func_151C7B1C (24 args) + producers func_151C9748 (writes the 3 piece pointers it reads back;
   draft `p168/d_9748.c`, not difftested) + func_151C957C (glow records via func_151407D0). Layout of the 0xA0-byte
   emitter block (copied to rec +0x110, read by func_151C8880 / func_151C8448): +0x00..+0x24 random sizes / phases
   (8 func_150ADA68 calls), +0x28 rec, +0x2C sound (func_1516284C, only with arg9), +0x30..+0x3B never written,
   +0x3C / +0x48 piece pointers [3], +0x54 0.0f, +0x58 0, +0x5A / +0x6C the two 0x12-byte hit triangles, +0x7E..+0x84
   s16 args 10..12 and 10+11, +0x86 option bits, +0x88 rec, +0x8C / +0x90 ground ids, +0x94 arg17, +0x98 / +0x9C
   arg19 / arg20. If func_15144E80 fails, func_151C9748 leaves out[] unwritten (N64 frees stack garbage then).

## State (session P167, 2026-10-24). Details: `docs/port/sessions/P167.md`

- New hand C (NM): func_151BAAC8 object_model_shatter (func_1507D754 callee, 715 insns: smoke burst + model pieces
  0x27..0x2C), func_15136C3C object_hit_effects (hit kind effects; returns s32 0) and its callee func_1513A24C
  object_debris_burst (calls port-b's func_15150D7C: stub here until the sync). All EQUIV with setups + ARGMEM;
  mutants 43/44 + 1 equivalent, 19/19, 25/26 + 1 equivalent.
- func_10010F88 (init_EB00): NM returns func_10010E78's u16 (asm callers keep it as a sound handle); functions.h
  u16 under NM. func_151AB954 (D_80089E10 entry 3): NM C lacked a parameter (read dy / dz instead of dz / obj): fixed.
- func_1507D754: not written: func_151C9740 / func_151CFFFC are asm in port-b files on port-b HEAD 9eebdac too;
  func_150E0DF0 (this slot, asm) depends on port-b's func_151D5AC4 / func_151D4684 / func_15154728.
- func_151342BC: decoded, not converted: 5 D_80089E10 handlers have NM signatures other than
  `void (f32 x6, u8 *)` (list in P167.md section 3; wasm call_indirect would trap).
- Checks: verify_all OK (code build, check_files, full ROM OK; after the last code edit), NM links (rc 0), protocheck 0 (1164), selftest 62/62, progress_nm 5158/5915 (87.2%), C bytes 68.4%.

## Next steps (from P167)

1. Unify the D_80089E10 handler NM signatures (func_151348F0, func_151AA8BC, func_150C65D8, func_150C6F08,
   func_150EAB4C -> `void (f32, f32, f32, f32, f32, f32, u8 *)`), then convert func_151342BC (decoding in P167.md).
2. func_150E0DF0 (game_eu_10E600, 220 insns) after the port-b sync (its port-b callees are C there).
3. func_1507D754 once port-b converts func_151C9740 / func_151CFFFC.
4. Browser: hit / break effects (func_15136C3C), sound handles from func_10010F88, P166's list.
5. P138 / P141 leftovers (not started).

## State (session P166, 2026-10-24). Details: `docs/port/sessions/P166.md`

- New hand C (NM): pause / money screen HUD model func_151EE0C4 hud_model_load (display list copies: 0xEF -> render
  mode 0x5041C8, 0xFC -> no-op) and func_151EE394 hud_model_draw (per frame; head blink textures 0x507 / 0x508);
  func_1507D754 callees func_150BC968 object_impact_debris_hard, func_150BC03C object_impact_debris (both void),
  func_150C04E0 object_land_puff. All difftest EQUIV with setups / ARGMEM + mutants (24/24, 30/31 + 1 equivalent,
  50/50, 52/52, 15/15).
- D_80089E40 (func_151342BC per-type table, 23 entries) confirmed real (result 0 -> func_1516972C(obj)). NM return
  types fixed: func_151346EC returns obj[1] (asm: func_15168A4C's lbu), func_1513470C returns 1 (free's nonzero v0),
  wrappers func_151ABD38 / 151ABD88 / 150C6910 / 150C6938 / 150C7240 / 150C7268 return the tail call (matching
  bodies in #else). func_151342BC itself still asm.
- func_1507D754: not written. Left: func_151BAAC8 (this slot, 715 insns, all callees C), func_15136C3C (this slot,
  blocked by port-b's func_15150D7C), func_151CFFFC / func_151C9740 / func_150E0DF0 chain (port-b files).
- New `docs/port/sessions/p166/dis.sh func...`: objdump of matching-build functions (return-value checks of C code).
- Checks: verify_all OK (full ROM OK, after the last code edit), NM links, protocheck 0 (1161), selftest 62/62,
  progress_nm 5155/5915 (87.2%), C bytes 68.2%.

## Next steps (from P166)

1. func_151BAAC8 (game_eu_1E7CC0, 715 insns): last func_1507D754 callee in this slot with only C callees.
2. func_151342BC (game_161520, D_80089E40 dispatcher) now that its table entries have s32 NM signatures.
3. Browser: pause / money screen head model (func_151EE0C4 / func_151EE394), plus P157's list.
4. P138 / P141 leftovers (not started).

## State (session P165, 2026-10-24, port-web). Details: `docs/port/sessions/P165.md`

- Merged port 902871d (P157) and port-b 8bd88bc (P155-P163): HANDOFF.md conflicts only. After each: verify_all OK,
  NM link OK, protocheck 0 (1225 NM bodies), float-int 0 bugs (REVIEW 4), census 0 FAIL after a clean rebuild.
  arity_scan 128 -> 130 (func_151D611C / func_151D469C table rows, game_eu_201240), m2c_sanity 228 -> 236 (port-b new C;
  "high": func_151A9940 game_eu_1D5710, func_151AC3F0 game_eu_1D9C00).
- First room (Chrome chR + node ngR, `padroom.py`, new `?p165hits=1`): **B swings the frying pan**; func_15064F50
  returns walk / run animation ids on every call; the object sound emitters start voices (footstep ids 577-582,
  run 299 / 300, pan swing 90); audio rms does not separate idle / walk (music dominates). Pause shows the frozen
  frame. Heap 0, traps 0, null zone only the known null+0x14 (port-b P164).
- **Conker still cannot leave the room**: no context action (ctx+0x7B stays 0 at 14 B presses around the room), no new
  event / scene. Text box handlers func_1516AFE0 (update) / func_1516BC2C (draw, DL stub) of the C text_box_open
  func_1516AD20 are asm stubs hit every frame since 12157: the box opens and never advances / closes / draws, so the
  gargoyle's dialogue cannot run (likely blocker).
- Regression: node noev 925 / 1249 / 1329, Chrome noev 1530 / 2302 / 2382, heap 0, null zone clean.

## Next steps (from P165)

1. Conversion: func_1516AFE0 + func_1516BC2C (game_eu_1984F0.c, text box update / draw, together), then
   func_1513FAB4 (game_169510.c, every frame), func_151EE0C4 (pause menu), func_151D9014 (game_2062D0.c).
2. Browser after (1): padroom.py again; look for the gargoyle's text and a ctx+0x7B / event change (`?p165hits=1`).
3. port-b: review the m2c_sanity high rows and the two new arity rows (section 1 of P165.md).
## P164 (port-b) (session P164, 2026-10-24). Details: `docs/port/sessions/P164.md`

Branch `port-b` (from P163 8bd88bc). Took game_40490.c, game_eu_1F4F60.c, game_39750.c; prototype-only edits in
game_1897A0.c / game_eu_126330.c (func_151530A8).
- **P161 fix**: func_1501370C (NM) calls the D_80082EA0 (EU 0x80083230) start handler with the record. Same commit:
  producer func_151530A8 `particle_burst_from_spec` (3 arguments; all prototypes `s32 (s32 *, u8, s32)`, 4-arg calls
  dropped under NM in 1CE7D0 / 11CB90) and the three still-asm entries func_151C7750 `record_beam_start` (idx 8),
  func_1500C2F0 `record_debris_spawn` (0x22), func_1500D8C8 `record_debris_spawn_b` (0x26). All D_80082EA0 entries
  are C now. 0x22 / 0x26 take `(rec, f32 scale)`; from the dispatcher a1 is func_15013000's jalr register (the
  dispatcher's own address, ~3e-26 as f32) so they spawn nothing there, in the port too (missing argument = 0).
- func_15150D7C `debris_burst_spawn` (17D3C0, coordinator request: port's func_1507D754 item path), func_150F79F0
  `light_effect_spawn` (125200, muzzle-fire light) and func_15152A90 `particle_burst_from_spec_b`
  (17D3C0) hand C. func_150F79F0 calls func_10010E78 directly: the C func_10010F88 (init_EB00) is void but the asm
  callers use its v0 (sound handle).
- All EQUIV + setups + mutants (P164.md); old func_1501370C is EQUIV on MIPS too (a0 survives), the NULL-argument
  mutant (wasm behaviour) DIFFERs.
- Checks: verify_all rc 0, NM build links, protocheck 0 (1209 bodies), selftest 62/62. progress_nm total 5203/5915
  (88.0%), game 4672/5334, C bytes 69.3%, 712 asm-only. No difftest processes left.

## Next steps (from P164)

1. Browser (port-web): re-run the P161 null-zone check without `?p161fix` (null+0x14 should stay clean); level-start
   records now run func_151530A8 / func_151C7750 (beam) for real. UNVERIFIED list in P164.md.
2. Owner of init_EB00.c: func_10010F88 should return func_10010E78's u16 under NM (asm callers read v0: P164
   func_150F79F0; check the other C callers with `arity_scan` / tablesig-style v0 use).
3. Next port-b asm with C callers (`p163/asmlist.py`): func_150FD140 (215, 12A7C0), func_15081120 (219, AE930),
   func_150511E8 (220, 78230), func_15152700 (228, 15 calls). func_151C7B1C (1F4F60, 24 args, beam builder) is now
   reached from C (func_151C7750).
4. Owner of game_161520.c: D_80089E40 (P163 next step 1, unchanged).

## P163 (port-b) (session P163, 2026-10-24). Details: `docs/port/sessions/P163.md`

Branch `port-b` (from P162 720e4c3). Took game_eu_1C3530.c.
- Table signatures: D_8008FC30 / D_8008FC58 are one-entry start-sound tables (FC34.. / FC5C.. are separate update /
  stop tables with their own index bytes); the asm dispatchers store v0 as the u16 voice handle. NM variants
  `u16 func_151991D0` / `u16 func_1519C4FC` return func_10010F30's handle (EQUIV + mutants).
- The 11 tablesig "maybe" rows: port-b ones (B730, FC10, 90070, 900D0, BA4) are false positives (next named address
  is a separately indexed table). Possibly real, not port-b: D_80089E40 (func_151342BC, game_161520) looks like one
  23-entry table whose default entries func_151346EC / func_1513470C are void wrappers; the dispatcher tests v0.
- m2c_sanity (port-web tsv): 12 high/medium rows in port-b files, all checked, 0 real (reasons in P163.md).
- func_151C6A28 `object_muzzle_fire` (1F4090) hand C (NM): 200 random + 9 setups + ARGMEM, mutants 18/20 + 2/2;
  returns 0 for game_981E0's undeclared call. func_15142A5C is 1-argument under NM in 1F4090 (was 2: wasm mismatch).
- Checks: verify_all rc 0, NM build links, protocheck 0 (1202 bodies), selftest 62/62. progress_nm total 5196/5915 (87.8%), game 4665/5334, C bytes 69.0%, 719 asm-only. No difftest processes left.

## Next steps (from P163)

0. **PRIORITY (coordinator, browser P161), not done in P163 (budget):** func_1501370C (game_40490.c:64, now port-b)
   calls `D_80082EA0[arg0->unk17]()` without the record; the asm (EU 150136BC) keeps a0 = arg0 at the jalr, so every
   level-start record handler gets NULL (the null+0x14 writer). Fix under NM like func_1501396C:
   `void (*func)(struct16 *) = (void (*)(struct16 *)) D_80082EA0[idx]; if (func) func(arg0);` — **in the same commit
   as func_151530A8** (game_eu_17D3C0, asm, 102 calls from frame 4773; 287 asm lines; callees func_150ADA20 x14,
   func_150ADA68 x3, func_15143794 (jal 15143D04), func_1515C2F0 (jal 1515C860); its C prototypes disagree:
   1897A0 `(s32 *, u8, u8)`, 11CB90 `(s32 *, s32, s32, u8 *)`, 126330 `(s32 *, s32, s32)` — check the asm's real
   arity). D_80082EA0 = EU 0x80083230, entries 0..0x2F (see P163.md); still asm besides 151530A8's path:
   func_151C7750 (idx 8, 1F4F60), func_1500C2F0 (idx 0x22) and func_1500D8C8 (idx 0x26) (game_39750).
1. Owner of game_161520.c: D_80089E40 (func_151342BC) index obj+0x3C may reach func_151346EC / func_1513470C (void
   C, v0 = func_15169804 / func_15169824's result, tested by `bnez v0`) and the void 1D7790 / F3AD0 / F4400 entries.
2. func_150F79F0 (125200, asm, port-b): consumer of func_151C6A28 / func_150FF604; 20-argument prototype in P163.md.
3. Next port-b asm with C callers (`p163/asmlist.py`): func_15152A90 (213, 17D3C0), func_150FD140 (215, 12A7C0),
   func_15081120 (219, AE930), func_150511E8 (220, 78230), func_15152700 (228, 15 calls).
4. Browser: P163.md / P162.md UNVERIFIED.

## P162 (port-b) (session P162, 2026-10-24). Details: `docs/port/sessions/P162.md`

Branch `port-b` (from P160 9151c20). Took game_eu_F6060.c, game_eu_192500.c, game_eu_1BAF40.c, game_eu_1FB080.c.
- Table signatures (P160 list), each jalr traced to its table: real and fixed under NM: D_8008B734 (func_151660F0
  returns f32: func_15164E0C stores f0), D_8008FFD0 (func_151D1654 / 1674 return func_151D1694's s32; func_151D1694
  `object_offset_point` converted). False positives: D_80088BF8, D_8008D9C0, D_80089E9C (the v0 test after
  func_151349D0's first jalr belongs to D_80089EB8; func_151A7BC0 needs nothing), D_80082FA4 (US name for EU
  0x80083334; the real table is C-dispatched D_80082BFC in game_36680, result unused).
- New real cases in game_eu_1C3530.c (not port-b): D_8008FC30 (func_151991D0 ..) and D_8008FC58 (func_1519C4FC ..),
  results stored with `sh v0`.
- `p162/tablesig.py` v2 (EU symbol resolution, per-jalr table trace, f0 results, single named entries, "maybe" rows);
  `p162/asmlist.py` skips functions defined in multi-function NM blocks.
- Hand C (NM), EQUIV + setups + mutants: func_151CEBE4 `node_find_kind11_by_id`, func_151CDA70 `splash_effect_spawn`
  (1FB080), func_150C8850 `wobblers_update` (F6060), func_1518FE50 `bone_sparks_emit` (1BAF40), func_150F1C5C
  `limb_burst_spawn` (11CB90), func_150FF840 `gun_fire_effects` (12D5D0, returns 0 for 981E0's undeclared calls).
- Bug fix: func_150F03F8 (11CB90 NM m2c body) pointer stride on `&D_800A1A10 / 1A28 / 1A40` (wrong for arg1 = 1).
- Checks: verify_all rc 0, NM build links, protocheck 0 (1201 bodies), selftest 62/62. progress_nm total 5195/5915 (87.8%), game 4664/5334, C bytes 68.9% (P160: 5189, 68.8%), 720 asm-only. No difftest processes left.

## Next steps (from P162)

1. Owner of game_eu_1C3530.c: D_8008FC30 / D_8008FC58 entries must return s16/s32 (P162.md). Check the "maybe"
   rows of `p162/tablesig.py` (dispatcher index ranges).
2. Next port-b asm with C callers (`p162/asmlist.py`): func_151C6A28 (210, 1F4090), func_15152A90 (213, 17D3C0),
   func_150FD140 (215, 12A7C0), func_15081120 (219, AE930), func_150511E8 (220, 78230), func_15152700 (228, 15 calls).
3. Run port-web `port/tools/m2c_sanity.py` over port-b files: func_150F03F8's stride bug was still in an NM body.
4. Browser: P162.md UNVERIFIED.

## State (session P161, 2026-10-24, port-web). Details: `docs/port/sessions/P161.md`

- **null+0x14 = 0x400 writer found**: func_1501374C (game_40490.c) `arg0->unk16 |= 4` with arg0 = NULL, because
  **func_1501370C (game_40490.c:64) calls `D_80082EA0[idx]()` without the record** (asm keeps a0 = record at the jalr;
  same as func_1501396C / P76; arity_scan row 22). Not a stubbed producer. Not harmless: every D_80082EA0 level-start
  record handler gets NULL (func_1515D088 spawns an effect with a NULL owner, func_15013778 spawns nothing).
  Found with a whole-wasm store watch (`docs/port/sessions/p161/storewatch_inst.py` + `nrun.sh`, wasm-dis / wasm-as).
  Port test `?p161fix=1`: null zone stays clean; exposes stub **func_151530A8** (game_eu_17D3C0.c, 102 calls from 4773).
- **Pause background fixed** (gfx_f3dex2.c): the pause copies the previous screen image into the **z-buffer image**
  (SETCIMG = zimg) and textures it from there. Now: per-screen-image GPU copies of the canvas, written back to RDRAM
  only when a SETTIMG reads that image; SETCIMG of the z image is an offscreen image (own FBO, written back only after
  draws; its z-clear rects still clear the canvas depth); canvas restore per image. Flags `?p161nofb`, `?p161nozc`,
  `?p161norestore`, `?p161log=F`.
- Regression: node new game to control (heap 0), Chrome pause in the first room (frozen frame shown, heap 0), noev
  walk 1527 / 2303 / 2383 (= P158), heap 0, traps 0.

## Next steps (from P161)

1. Game C (conversion slot): fix func_1501370C's dropped argument (pass arg0, as func_1501396C) **together with**
   func_151530A8 (game_eu_17D3C0.c), which the real record handlers then reach; check with stubcalls.py.
2. The P158 list stays: func_15064668, func_15064F50, init_EB00 sound emitters, func_1505528C, func_151EE0C4 (pause).
3. Other arity_scan rows of the same shape (handler tables called with no argument) deserve the same check; the store
   watch finds any null-zone writer in one run (change the range in storewatch_inst.py).

## P160 (port-b) (session P160, 2026-10-24). Details: `docs/port/sessions/P160.md`

Branch `port-b` (from P159 4bb281f). Took game_eu_1F4090.c.
Hand C (NM), difftest EQUIV + setups + mutants: func_151C6F7C `object_bone_point` (1F4090; its matching callers
func_151C6F24 / func_151C6F50 get typed 3-argument NM variants), func_151D469C `object_point_effect_spawn` (201240;
returns 0 for 981E0's undeclared calls; func_151D5308 NM casts), func_151C230C `ray_cast_through_passable` (1EDA00;
NM prototype + func_151C1F1C casts), func_151A2C9C `particle_puff_spawn` (1CE7D0), func_151DA08C `smoke_puff_spawn`
(2062D0), func_151A31D4 `particle_burst_spawn` (1CE7D0).
- func_1513D668 (169510 + functions.h) returns func_1513D594's record under NM (func_151DA08C uses it).
- func_151A3134 NM signature = func_151A3180's (both called through one pointer in func_151A31D4).
- func_150A6070 (D3880) was already C (P130); asmlist.py misses multi-function NM blocks.
- New `docs/port/sessions/p160/tablesig.py`: function-pointer tables vs NM C signatures / asm v0 use after jalr.
  Real P159-class cases (void C entries, asm dispatcher reads v0): D_80089E9C (func_151349D0 frees the object when
  v0 == 0; includes port-b's func_151A7BC0), D_80089E40, D_80089ED8, D_80089E10 (game_161520 dispatchers),
  D_80088BF8, D_8008B734, D_8008D9C0, D_8008FFD0, D_80082FA4 — listed in P160.md, none fixed.
- Harness: DIFFTEST_OUTW `@ADDR` faults on a page not touched yet (workaround in P160.md).
- Checks: verify_all rc 0, NM build links, protocheck 0 (1195 bodies), selftest 62/62. progress_nm total 5189/5915 (87.7%), game 4658/5334, C bytes 68.8% (P159: 5183, 68.6%), 726 asm-only. No difftest processes left.

## Next steps (from P160)

1. Table-scan cases: work out what v0 the void entries leave (D_80089E9C / func_151349D0 first: it decides whether
   objects are freed) and give the entries s32 NM returns; needs the game_161520 / other slots' files.
2. Next port-b asm with C callers (`p160/asmlist.py`): func_1501B300 (200, 48B10), func_150F1C5C (201, 11CB90),
   func_150FF840 (203, 12D5D0), func_151C6A28 (210, 1F4090), func_15152A90 (213, 17D3C0), func_150FD140 (215, 12A7C0).
3. Browser: P160.md UNVERIFIED (object point effects, see-through ray casts, particle puffs / bursts, smoke puffs).

## P159 (port-b) (session P159, 2026-10-24). Details: `docs/port/sessions/P159.md`

Branch `port-b` (from P155 d2c5c53). Took game_eu_125200.c, 12C0B0.c, 12BB30.c, 12D5D0.c.
Hand C (NM), difftest EQUIV + setups + mutants: func_15154728 `spark_shower_spawn` (17D3C0; NM prototypes now s32 in
125200 / 201240 / 1EDA00 / 1D3420), func_151D441C `object_sound_between` (201240; void, 12D5D0 prototype void),
func_151D611C `objects_hit_by_segment` (201240), func_150F85AC `record_particle_spawn` (125200), func_151C0434
`impact_effects_spawn` (1EDA00), func_1514FE68 `spray_particles_spawn` (17D3C0; its spray chain is now all C),
func_150F0BEC `object_glow_spawn` (11CB90).
- func_151C1EF0 (D_80087030 filter 3, matching C `void`) returns func_151C0894's result under NM (the table callers
  func_151D611C / func_15081A90 test it; a void function through an s32 table pointer traps on wasm).
- func_151D469C held: D_80090010 handlers 0 / 1 (func_151C6F24 / func_151C6F50) call func_151C6F7C, asm-only in
  game_eu_1F4090.c (not port-b); func_151D5308 uses kinds 0 and 1.
- Checks: verify_all rc 0, NM build links, protocheck 0 (1189 bodies), selftest 62/62.
  progress_nm total 5183/5915 (87.6%), game 4652/5334, C bytes 68.6%, 732 asm-only.

## Next steps (from P159)

1. func_151D469C after func_151C6F7C (game_eu_1F4090) is C — give 1F4090 to port-b or convert it in the port slot.
2. Next port-b asm with C callers (`p159/asmlist.py`): func_151C230C (151, 1EDA00), func_151A2C9C (157, 1CE7D0),
   func_150A6070 (173, D3880), func_151DA08C (183, 2062D0), func_151A31D4 (186, 1CE7D0).
3. Browser: P159.md UNVERIFIED (spark showers, impact sprays, segment hit masks, filter-3 ray casts).

## State (session P158, 2026-10-24, port-web). Details: `docs/port/sessions/P158.md`

- Merged port 92789cc (P151 + P156) and port-b d394089 (P153): HANDOFF.md conflicts only (merge_union.py + section
  order by hand), no code conflicts; func_15058898's func_150BA3B0 prototype matches the P153 definition.
  After each merge: verify_all OK, NM link OK, protocheck 0, float-int 0 bugs (REVIEW 4), arity_scan 128,
  m2c_sanity 228 (+1 func_1507CD64 width med, probably false positive), census 0 FAIL after a clean rebuild,
  stubcalls: the new C calls no hit stubs.
- New game: player control at **18485** again (node ng1 to 33101, Chrome x3); heap 0, traps 0; stub calls over the
  whole new game 9233 -> 1758. **null+0x14 = 0x400 is still written**, at frame 4560, right after the scene-start
  stub set (last stub func_15086058, game_eu_B37F0) and not by func_1514D6CC / func_1514CFF0 (checked with a wrap).
- Renderer fixes (port/gfx/gfx_f3dex2.c): **32-bit textures' odd rows** were never swapped (pause-menu letters and
  the HUD digit are RGBA32 loaded with dxt 0: noisy / interlaced text, now clean); **projected shadows z-fought**
  with the floor (hatched patches): z-compare-without-update draws now get the decal polygon offset
  (`?p158nozofs=1` = old). The long shadow streak is game behaviour: level 0x22's two shadow lights are 91 units
  high, ~500 away, and func_15187820 disables the minimum-height rule for this level.
- Pause background is black: the game reads the frozen frame from RDRAM, the port never writes its GL frame back.
- Noev Chrome regression unchanged (1528 / 2304 / 2384). New diagnostics: `?p158f` / `?p158f2` (texture / draw dump
  of the first task at retrace F), `?p158light`, `?p158null`.

## Next steps (from P158)

1. Gameplay blockers, in order: func_15064668 (game_eu_90F50, B action), func_15064F50 (game_eu_90F50, walking),
   func_10010154 / func_1000F568 / func_10010344 (init_EB00, sound emitters), func_1505528C (game_eu_78230, idle sit),
   func_151EE0C4 (game_eu_216470, pause menu); then the scene-start stub set and the P152 list (P158.md section 5).
2. Find the null+0x14 writer: wrap the level-load functions that run after func_15085FE0 at the new-game level
   load (frame 4559-4560) with before / after checks, as `__wrap_func_1514D6CC` does.
3. Gfx: write the frozen frame back to the colour image for the pause screen (read back on the pause transition).
   Compare the level 0x22 shadows with real hardware if possible.
4. After func_15064668 is C: padtongue.py with `NOSTART=1` B presses at the pillar, to get past the first room.
## State (session P157, 2026-10-23). Details: `docs/port/sessions/P157.md`

- New hand C (NM): func_15132BBC particle_spawn (worker of the C wrapper func_15132FBC: every particle spawn now runs C)
  + its asm callee func_15133C18 particle_model_load; coordinator priorities from browser P154: func_15064668
  player_context_action (B button; game_83300's prototype now `void`), func_15064F50 player_move_animation (walk /
  run / carry animation, 946 insns); sound emitters func_10010154 object_sound_play, func_10010344
  object_sound_play2, func_1000F568 sound_pick_variant. All difftest EQUIV with setups + mutants (P157.md table).
- A setup batch found a real draft bug in func_15064668 (D_800E9D00 0x800 bit picks 0x1DC, else 0x354): fixed,
  re-verified (79 setups).
- func_1507D754: still blocked (port-b HEAD d394089: func_15150D7C / func_15154728 asm; func_151D5AC4 / func_151D4684
  now port-b's). Its asm callees in this branch were not started (re-prioritised).
- Checks: verify_all OK (full ROM OK, after the last code edit), NM links, protocheck 0 (1156), selftest 62/62,
  progress_nm 5150/5915 (87.1%), C bytes 67.9%.

## Next steps (from P157)

1. Pause menu func_151EE0C4 (game_eu_216470.c), queued by the coordinator.
2. func_1507D754 callees in this branch: func_151BAAC8 (715), func_150BC968 / func_150BC03C (461 / 587),
   func_150C04E0 (127), func_151CFFFC (374), func_151C9740 (224, needs port-b's func_15154728).
3. Browser: B button / context actions, walk animations, object sounds, particles (func_15132BBC).
4. P138 / P141 leftovers (not started).
5. (Coordinator note, retracted by port-b P162: the game_161520 table-signature flags D_80089E9C / E40 / ED8 / E10
   are false positives; no action.)

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

## P155 (port-b) (session P155, 2026-10-23). Details: `docs/port/sessions/P155.md`

Branch `port-b` (from P153 d394089). Coordinator decisions: func_151AC3F0 inserted (1EDA00:292 prototype `void`);
func_151AE694 returns instead of spinning forever when no path exists (NM only, documented port divergence; no log
hook in the NM build). Took game_eu_1D4CC0.c and game_eu_201240.c (not on the port slot's list).
Hand C (NM), difftest EQUIV + setups + mutants: func_151A9940 `kind_effect_spawn` (1D5710), func_1516AD20
`text_box_open` (1984F0), func_1505528C `thrown_object_update` (78230), func_151506E8 `particle_spray_spawn` (17D3C0),
func_151D5AC4 `smoke_cloud_spawn`, func_151A74B0 `debris_spray_spawn` (1D4CC0), func_151D5714 `bone_beam_spawn`,
func_151D4898 `object_sound_at`, func_151A7F00 `path_record_create` (1D5710), func_151D5FC8 `object_mouth_point`,
func_151D4684 `object_sounds_at` (201240). func_15081974 (AE930) takes `f32` for its second parameter.
- func_15154728 `spark_shower_spawn` verified (draft `p155/d_4728.c`) but NOT committed: game_eu_125200.c:36 (not
  port-b) declares it `void`; 1191C0 needs `s32`. Fix that prototype (+ port-b NM prototypes 201240:398, 1EDA00:12,
  1D3420:743 -> s32), then insert.
- Checks: verify_all rc 0, NM build links, protocheck 0 (1182 bodies), selftest 62/62.
  progress_nm total 5176/5915 (87.5%), game 4645/5334, C bytes 68.5%, 739 asm-only.

## Next steps (from P155)

1. func_15154728: after the 125200 prototype fix, insert `p155/d_4728.c`.
2. func_151D441C: prototypes in 12C0B0 / 12BB30 (void) vs 12D5D0 (s32) must agree first.
3. func_151D469C / func_151D611C (201240): check the D_80090010 / D_80087030 handler tables (C or stubs) first.
4. Next port-b asm with C callers (`p155/asmlist.py`): func_151C0434 (133, 1EDA00), func_150F0BEC (151, 11CB90),
   func_151C230C (151, 1EDA00), func_151A2C9C (157, 1CE7D0), func_1514FE68 (168, 17D3C0).
5. Browser: P155.md UNVERIFIED (post-opening cutscene text boxes, level-0 thrown objects).

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
## P77 (port-b) (session P77, 2026-10-22). Details: `docs/port/sessions/P77.md`
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

## State (session P71, 2026-10-22). Details: `docs/port/sessions/P71.md`

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
