# Port hand-off (branch `port`, worktree `~/conker-wt/port`)

Read `docs/port/PLAN.md` first: the phases, the browser-first target (wasm32/Emscripten) and the
risks. The decomp rules in `tools/eu_port/AGENT_BRIEF.md` and `HANDOFF.md` still apply: worktree
env, `verify_all.sh` before every commit, background jobs, the commit trailer.

```sh
cd ~/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"   # CONKER_ROOT, CONKERDEV=conkerdev-port
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
docker exec conkerdev-port python3 -c 'import unicorn'            # if missing: pip3 install --break-system-packages unicorn
```

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

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems.
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

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems.
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

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems.
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

- The default build is byte-identical (full `verify_all.sh` OK, 3992/5913). `NON_MATCHING=1` links. protocheck: 0 problems.
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


## Browser build (sessions P3, P4, P6, P8, P9, P11, P14, P19, P21, P23, P25, P27; branch `port-web`)

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
`docs/port/sessions/P27.md` (input, EEPROM saves in IndexedDB, page UX, audio resume). The memory-model design is in **`docs/port/MEMORY.md`**. Everything is
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
     and the texture-bank segments for the viewer, and checking the light formula against the ucode.
  5. Still open from P4.md, "Known gaps":
     - address constants and `K0_TO_PHYS` in C;
     - bitfields;
     - `va_arg` doubles;
     - review of the pointer scan.
