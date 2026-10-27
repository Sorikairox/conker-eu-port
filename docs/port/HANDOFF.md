# Port hand-off (branch `port-web`, worktree `~/conker-wt/web`)

Current-state summary. The per-session history (docs/port/sessions, docs/sessions, the old long hand-off) was deleted
in P329; it is in git history (e.g. `git show b274100a:docs/port/HANDOFF.md`) and on branch `exact-byte-decomp-wip`.
Session notes now go into this file (section "Sessions"), one short entry per session, plus a row in
`docs/progress/sessions.tsv`.

```sh
cd ~/conker-wt/web && eval "$(tools/eu_port/wt.sh env web)"    # CONKER_ROOT, CONKERDEV=conkerdev-web
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
```

## What the repo is now
- The EU game as readable C (`conker/src_eu`, 722 TUs; every function is C except 31 platform-replaced asm-only
  functions listed in `port/symbols/global_asm.tsv` / `tools/port/platform_replaced.tsv`) + headers (`conker/include`,
  libultra internals in `conker/include/libultra/{os,audio,io}`), built for the browser (wasm32, Emscripten) by `port/`.
  No `#pragma GLOBAL_ASM`, no `#ifdef NON_MATCHING` (stripped in P329); `#ifdef PORT` marks deliberate port changes.
- The byte-matching decomp build (IDO + splat + asm + US/debug/ects configs) is gone from port-web. It lives on branch
  `exact-byte-decomp-wip` (pushed by backup_push.sh; never merge it back).
- Names / addresses: frozen `port/symbols/symbols.tsv` (+ segments.tsv, global_asm.tsv, ido_cc.tsv). Game code and
  data are read from the user's ROM at run time (and by the build / difftest: `port/symbols/romimage.py`). Never commit
  ROM bytes.

## Daily commands
- Build: `port/web/run.sh build` (incremental by content; `build clean` for a clean one). Output port/build/web.
- Checks before every commit: `tools/eu_port/check.sh` (~150 s: implicit_scan 0 NM+float, romabs_check 0 FAIL,
  difftest selftest 152/152, census 722 TUs 0 FAIL, web build). Never commit on RED.
- Gameplay test (fast): `tools/port/scripts/warp.sh NAME SECS LEVEL [EXTRA_QUERY]` (?warp: level 0x29 at retrace 38).
- New-game route: `tools/port/scripts/newgame.sh DIR SECS [EXTRA_QUERY]` / `newgame_summary.sh NAME SECS PADF`;
  hold-L regression: `tools/port/scripts/holdl.sh` (opening ends at retrace 5789, level 0x29 at 5795, no traps).
  All browser runs: muted, det=2, one headless Chrome at a time, kill only your own PIDs.
- difftest (IDO 5.3 in the container compiles the candidate, reference = ROM): `tools/port/difftest.sh FUNC [FILE]`,
  registry re-runs `tools/port/reverify.sh FUNC` / `reverify_all.sh` (setups / mutants in `tools/port/testdata/`).
  The 21 registry rows with a HARNESS knob needed the matching build's ELFs and are reported as skipped.
- Renames: docs/RENAMING.md (`tools/eu_port/rename.py`, `apply_names.sh`).
- Deploy after a green check + browser test: `tools/eu_port/deploy_web.sh`; backup: `~/conker/tools/eu_port/backup_push.sh`.

## Reference docs
`docs/port/PLAN.md` (original port plan), `docs/port/MEMORY.md` (wasm memory model), `docs/port/design/P4..P9.md`
(browser harness, PC replacements, gfx interpreter, texture ids, audio HLE; cited by port code comments),
`docs/names/` (naming tables and proposals), `docs/progress/` (session log), `PLAYING.md` (what works).

## Open items
- Globals not renamed: 562 D_ symbols only declared in conker/include/variables.h (no C use), D_ names that appear
  only in tables / comments, ROM-offset symbols < 0x10000000, and D_ names inside log strings (kept so the wasm stayed
  identical). Some descriptions note wrong declaration comments or US/EU alias pairs (`_alias`) worth merging later.
- port_cdata name strings (n64mem_tab.c) still print the original D_ names (n64mem.py, RENAMED_FROM).
- ?warp is tested on level 0x29 only; other levels may need event state the real route sets.
- Frame-blend "ghost" effect (fb_ghost_render) looks wrong in the port: in the hangover wake-up scene after the opening
  the picture shows one pixelated frame that stays frozen for seconds (two shots 3 s apart identical) instead of a
  blend of live frames. Its copy of the new frame into g_fb_ghost_image (SETCIMG into RDRAM) probably never lands.
  Option "No motion blur / drunk sway" hides it; the default (off) still shows it (P331).
- Route tests `p261 r5g / pan8` (new game -> later levels) were not re-tuned after P319; their pad scripts are in git
  history (docs/port/sessions/p261).
- port-b P317 leftovers (memcpy re-run of 19 registry rows, v0use candidates, random DIFFERs of func_1510E004 /
  func_15141A7C): their lists are in git history (docs/port/sessions/p317); the v0use / arity tools were deleted with
  the matching build.
- Analysis tools that read the matching ELF / asm were deleted in P329 (stubcalls, m2c_sanity, bootpath, priority,
  arity_scan, stride_scan, tablesig, v0use, protocheck, the nmasm harnesses). Rebuild them on port/symbols + the ROM if
  needed. romabs_check's source scan still skips `#ifndef NON_MATCHING` blocks (none left).

## Sessions
### P331 (port-web, 2026-10-27): features #7 and #8
- 2023e2ed option "No motion blur / drunk sway" ('nodrunk', PORT_OPT_NO_DRUNK_FX 6): fb_ghost_set_mode turns every
  frame-blend request off; camera_update_shake and camera_wobble_apply ignore their drunk triggers (camera mode
  0x80000 = title menu, +0x5F0 bit 3 = drunk state); the under-water wobble and cutscene camera-path roll stay.
  Measured on the new game route: menu wobble 0.003 -> 0, menu roll +-2.9 -> 0, wake-up ghost 210/1 -> 0/0.
- 42be5836 option "Conker always full detail" ('conkerlod', PORT_OPT_CONKER_FULL_LOD 7): obj_select_lod gives
  level 0 to the object whose level-0 model is 0 (Conker, models 0..4). Off: level 1 at 529..627 units while
  running; on: level 0 always.
- Both: check.sh GREEN, hold-L 5789 / 0x29 at 5795, deployed. Found the ghost-effect render problem (Open items).
### P330 (port-web, 2026-10-27): global variable names, cash counter images
- Tooling 666e0ef9 (+ fixes 2 later commits): rename.py / apply_names.sh handle `D_` rows (`/* was D_X */` on each
  declaration line, string literals kept, wasm byte-identity enforced; tools/eu_port/wasm_sig.py,
  tools/eu_port/globals_chunks.py -> docs/names/globals.tsv). docs/RENAMING.md "Globals".
- 3920 globals renamed in 4 batches (ebb2912c, be9ad98b, d6348054, 004c464f) from 15 proposal files
  (docs/names/proposals/globals01..15.tsv, written by naming sessions); object-table fields unified to
  `g_objects_<field>` (cf93e1fd). conker.wasm md5 f73eb4a2... unchanged throughout.
- Cash counter 3478fd22: option "Always show cash" draws the pause screen's $ + digit images, half size, top right
  (hud_cash_counter_draw in game_eu_216470.c); the P325 text version is gone. Browser-tested, hold-L OK, deployed.
### P329 (port-web, 2026-10-27): cleanup part 2 of 2
- Step 1 (3771055a): gen_stubs `asm_only()` and difftest `find_file` read `port/symbols/global_asm.tsv` (1892 former
  GLOBAL_ASM functions, 31 asm-only) instead of the pragmas. Same results for all names; md5 unchanged.
- Step 2 (166c8afa): `tools/port/strip_nm.py` stripped 2270 NON_MATCHING blocks and 1892 GLOBAL_ASM pragmas (461
  src_eu files + functions.h / variables.h); -DNON_MATCHING dropped from the port build. difftest splices a candidate
  by top-level items (replaces same-name typedefs / prototypes / data near the function, like the old whole-block
  splice); one selftest case got `//DROP` lines. md5 unchanged, selftest 152/152.
- Step 3 (7cf600ba): deleted the matching build (generated output, configs, vendored splat / asm-processor / IDO
  recomp, conversion-era tools, conker/src US tree; libultra headers moved to conker/include/libultra). check.sh,
  rename.py, apply_names.sh: port mode only. Clean rebuild md5 unchanged, selftest 152/152.
- Step 4: live test inputs moved to `tools/port/testdata/` (1068 registry setups / mutants) and
  `tools/port/scripts/` (newgame.sh, newgame_summary.sh, warp.sh, new holdl.sh); docs/port/sessions, docs/sessions,
  root HANDOFF.md and matching-only docs deleted; P4..P9 design docs kept in docs/port/design.
- conker.wasm md5 f73eb4a25467dc5aa21b8a12cab69699 at every step (same as before P328).
- Step 5: orchestrator.md section 2 rewritten for the port-only layout (matching-build / verify_all / convert rules
  removed, port rules kept), README "how to build" + layout, PLAN.md marked historical. Final: check.sh GREEN;
  holdl.sh: opening ends at 5789, 0x29 at 5795, 0 traps to retrace 9965; warp.sh 29: 0x29 at 38, 0 traps. Deployed.
- Size: tracked files 8450 -> 2103, tracked bytes 325.9 MB -> 21.2 MB; worktree on disk 3.7 GB -> 2.4 GB (of which
  2.1 GB is the gitignored port_work scratch).
- backup_push.sh fast-forwarded `eu` (main checkout ~/conker) to port-web, so ~/conker now has this layout too:
  root HANDOFF.md is gone there (the eu decomp hand-off is in history / on exact-byte-decomp-wip) and the old
  untracked dirs (tools/asm-differ, asm-processor, mips_to_c, n64splat, tools/eu_port/m2c) are left on disk there.
- Follow-ups: rebuild analysis tools on port/symbols if needed (Open items).
