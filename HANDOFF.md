# Hand-off: Conker's Bad Fur Day (EU) decompilation

Last updated: 2026-10-20 (session 39, main checkout; slice below 0x130000). Update this file at the end of every work session.
Last updated: 2026-10-20 (session 44, worktree eu-wt-a; s43 = the stopped one, s42/40 before). Update this file at the end of every work session.
Last updated: 2026-10-20 (session 40, worktree eu-wt-a; session 41, main checkout, game < 0x130000). Update this file at the end of every work session.
Last updated: 2026-10-20 (session 42, worktree eu-wt-a; 40 = previous); session 45 (main, game < 0x130000). Update this file at the end of every work session.

Layout of the docs (read in this order):
- `tools/eu_port/AGENT_BRIEF.md`: the rules of a work session (short).
- **This file, in full.**
- `docs/IDO_SHAPES.md`: matching recipes and ruled-out hypotheses, grouped by topic. **Read before any matching work.**
- `docs/sessions/sNN.md`: per-session history (verbatim, reference only; `grep` it when a function or tool name comes up).
  `docs/sessions/remaining_work_history.md` (old "Remaining work" and next-step lists), `docs/sessions/commit_table_and_state_history.md`
  (commit table, progress history, the old "Current state" block). `docs/LAYOUT.md`: the porting pipeline and verification scripts.

## Goal

Full matching decompilation of the **European** ROM. Private fork of [mkst/conker](https://github.com/mkst/conker) (upstream is US-first); the long-term aim is a native
Mac/Windows port. Nothing is pushed, nothing goes upstream (remote `upstream` is mkst/conker; never touch it).
- Repo `~/conker`, branch `eu`. ROM `~/conker/baserom.eu.z64` (z64 order, SHA1 `ee7bc6656fd1e1d9ffb3d19add759f28b88df710`).
  The user's `~/Downloads/Conker's Bad Fur Day (Europe).n64` is byte-swapped; never modify it.

## Quick start

1. `tools/eu_port/verify_all.sh` (repo root, host; `--quick` skips the re-split): code build + `check_files.py` + full ROM + progress. Exit 0 only if everything matches. Authority before every commit.
2. Inner loop in the native arm64 container `conkerdev` (see Build environment) with the tools below.
3. Candidate pool for short functions: `tools/eu_port/shortpool.py 70` (names to stdout), drafts `tools/eu_port/gensome.sh ${=LIST}` (zsh: `${=...}` splits), read with `tools/eu_port/fctx.sh <func>` / `sh.sh <func>`.
4. Per function: `repair_ctx.sh <f>` (asm + draft + diff + HINTs), write a rewrite, `repair_try.sh <f> <draft.c>` (OK/DIFFn/SIZE+-n/CERR; OK drafts go to `conker/build/hand`), up to 3 reasoned rewrites;
   register-only leftovers (DIFF <= 9) go to `permute.sh <f> draft.c 150 4` in the background; log every function with `rlog.sh func start attempts end y|n perm y|n "note"` (quote everything; a bare `?` is a zsh glob).
5. Batch: `docker exec -w /conker/conker conkerdev python3 ../tools/eu_port/m2c/apply.py build/hand` (move applied drafts to `build/hand_done` and delete their `screen.txt` lines before the next run), `needsyms.py`, `verify_all.sh`, commit.

## Current state

- Full EU ROM rebuilds **byte-identical** (`build/conker.eu.z64: OK`).
- **3273 / 5913 functions in C (55.4%)**, code bytes 364,580 / 2,253,856 (16.2%) (merged state, from `verify_all.sh`). init 374/540 (40.3% of bytes), game 2867/5330 (14.1% of bytes), debugger 32/43 (42.6% of bytes).
  Sessions 35 (main), 36-38 (worktree eu-wt-a, merged) and 39 (main, game files below 0x130000; a parallel worktree session works above it) done. Session 36 recipes: IDO_SHAPES section 12, session 39: section 13. Progress by session is in `docs/sessions/commit_table_and_state_history.md`.
- Every plain asm subsegment is a C file (`*_eu_<rom>.c`); new decompilation = replace a `#pragma GLOBAL_ASM` with C, no yaml edits. All 266 US C files are ported to `conker/src_eu/` (plus EU-only `game_30E60.c`, `game_8FCB0.c`).
- **From commit `b5aeddd` on, `src_eu/`, the EU yaml and symbol files are hand-edited. Never run `tools/eu_port/run.sh`.**
- Session 35: permuter sweep over the repair leftovers, +8 (commits `3315bbc` and the next); see "Session 35" at the end. Session 34: 5 more from the pool (commit `350efff`), see "Session 34" at the end. Session 33: docs restructure (commit `7ef7e94`), then 14 functions from the session-32 pool (commit `d2cde39`); see "Session 33" at the end.
- Conventions: EU symbols keep their **US names** (address in the name is the US one); clashing ones are `func_eu_XXXXXXXX` / `D_eu_XXXXXXXX`. A US function whose EU code differs is a prototype + `GLOBAL_ASM`.
  Data segments are mostly `databin`/`rodatabin` blobs; files that own `.rodata`/`.data` are listed in `docs/sessions/s08.md` / `s10.md` and by `grep -n 'rodata' conker/conker.eu.yaml`. Data symbols C code uses live in `undefined_syms.eu.txt`.
  Label every unnatural construct `// fakematch: <why>` (`grep -rn fakematch conker/src_eu`). Commit trailer: your own `Co-Authored-By:` line (see AGENT_BRIEF).

## Build environment

Toolchain (IDO 5.3 recomp, mips-linux-gnu binutils) is Linux only: everything runs in Docker. `docker` is not on PATH:

```sh
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
docker build --platform linux/arm64 -f Dockerfile.arm -t conker-arm .     # fast native image (ido-static-recomp v1.2, IDO_DIR=/opt/ido5.3)
docker build --platform linux/amd64 -t conker .                           # x86 image, used by verify_all.sh
docker run -d --name conkerdev --platform linux/arm64 -v ~/conker:/conker -w /conker conker-arm sleep infinity   # if missing
docker exec conkerdev make -C conker VERSION=eu -j8                       # code build + verify (~20 s clean)
docker exec conkerdev bash -c 'make -C conker VERSION=eu replace && make VERSION=eu -j8'   # full ROM
```
- arm64 IDO gives byte-identical `.text/.rel.text/.data` (only `.mdebug` differs); it is 3.6x faster, so ~100 s/function in the permuter equals the old 300 s. `verify_all.sh` runs on the x86 image and also covers the bundled x86 `tools/gzip`.
- `conkerdev` is the persistent container (started before sessions; leave it running). Progress: `make -C conker VERSION=eu progress` -> `conker/progress.csv`; `python3 tools/eu_port/progress.py conker/progress.csv`.
- After a yaml / `symbol_addrs.eu.txt` change re-split: `rm -rf conker/asm conker/build; find conker -maxdepth 1 -name '*_auto.txt' -delete; docker exec conkerdev make -C conker VERSION=eu extract` (zsh: `rm *_auto.txt` aborts on no match, use `find -delete`).
- `SPIMDISASM_ASM_NM_LABEL=""` is set in the image (asm-processor rejects the `nonmatching` line). `pyelftools` in requirements. m2c needs `pycparser<3` (its own venv under `tools/eu_port/m2c/venv`).
- The decomp-permuter is cloned at `tools/decomp-permuter` (gitignored; `git clone https://github.com/simonlindholm/decomp-permuter` if missing); drafts/work dirs under it (`repair/`, `nm/`, `sweep/`, `drafts/`) are gitignored and survive `verify_all.sh`; `conker/build/` does not.
- Per-file `OPT_FLAGS` overrides are in `conker/Makefile` (libultra `-O1`, libc `-O2`, game copies of libultra `-O1`). Changing a file's flags does not rebuild its object: delete the `.o`.

## Tool index (`tools/eu_port/`, details in the session named)

Parallel worktrees (one agent per worktree; s35)
- `wt.sh new|env|merge|rm <name>`: git worktree `~/conker-wt/<name>` on branch `eu-wt-<name>` + container `conkerdev-<name>` (conker-arm, worktree mounted at /conker). `eval "$(tools/eu_port/wt.sh env <name>)"` exports `CONKER_ROOT` (default `$HOME/conker`) and `CONKERDEV` (default `conkerdev`), which every host-side script in `tools/eu_port` reads. `verify_all.sh` runs from its own checkout. `merge` merges the branch into `eu` in the main checkout (only when no agent is active there). Worktrees have their own m2c venv and gitignored data (`ctx/` regenerates, permuter `nm/`, `repair/`, `sweep/` start empty). Run `verify_all.sh` once in a new worktree to create `conker/asm` and `conker/build`.
- `remote_perm.sh f [draft.c] [secs] [jobs]` permuter search on the Mac mini worker (REMOTE, its own `conkerdev` container; local setup/screening use `CONKER_ROOT`/`CONKERDEV`; concurrent jobs fine, each has its own `nm/<func>`).

Verification / build
- `verify_all.sh [--quick]` full check (s-brief). `check_files.py [src_eu/X.c]` whole-object `.text` + owned `.rodata/.data` vs ROM (reliable; `check_funcs.py` skips functions already in C). `fdiff.py src_eu/X.c func` word diff of a C function. `rodiff.py` rodata word diff. `bindiff.py`.
- `needsyms.py [--apply] funcs` re-adds splat auto symbols that a newly matched function was the last user of (only the full verify catches it, s13). `revert_bad.py` reverts bad new C to GLOBAL_ASM (s03).

Drafting and screening (`m2c/` is host-side; paths in `m2c/` scripts come from `CONKER_ROOT` / `CONKERDEV`, defaults `~/conker` and `conkerdev`; s04-s07)
- `m2c/list.py` all GLOBAL_ASM functions; `m2c/gen2.py outdir min max` m2c drafts + 8 variants; `m2c/screen.py` (OK/DIFFn/SIZE+-n/CERR; word diff with `SCREEN_V=1`); `m2c/try func [draft]`, `m2c/tryall func a.c b.c...` (8 parallel),
  `m2c/mine func draft.c` (my asm on one line; honours `SCREEN_OPT`), `m2c/keep`, `m2c/apply.py build/hand`, `m2c/screenall dir`, `m2c/merge.py`, `m2c/narrow.py`, `m2c/switchinline.py`, `m2c/compound.py`, `m2c/voidret.py`, `m2c/spawngen.py`/`spawn.py` (effect spawners, s09-s11), `m2c/flags src_eu/X.c` (build with each OPT_FLAGS).
- `gensome.sh <funcs>` drafts for a few functions into `repair/fresh/`; `gen40.sh [max]` bulk; `m2cfix.py list` declfix + bulk screen (s30); `fctx.sh <func>` / `sh.sh <func>` context + asm on one line (s18, s24).
- `shortpool.py [max]` candidate pool of unlogged short functions (s30, s32). `shapes.py [--list A|B|C|D N]` tags known shapes (s24). `gfxfind.py [--list|--untried|--hints F]` Gfx writers (s31).
  `clones.py [--draft] [--lax]`, `--near K`, `--asm-clusters` template clones (s25, s28); `declfix.py` called by it (s29).

Repair loop
- `mydis.sh <f>` disassembles the "mine" column of `repair/<f>.diff` (s45); a `//HOIST <proto>;` first line in a draft hoists a forward prototype for screening.
- `repair_ctx.sh <f>` context + `draftcheck.py` HINT lines; `repair_try.sh <f> draft.c`; `rlog.sh` log row into `repair_log.tsv` (~590 rows); `stackfix.py f draft.c` / `--scan` / `--bisect` (frame/slot puzzles, s15);
  `protocheck.py [--sig f | --apply --skip-logged]` + `rescreen.py` prototype contradictions (s15); `fwdproto.sh file 'proto;'` forward prototype after the last `#include` (s32); `permute.sh f draft.c [secs] [jobs]` / `-l list` (decomp-permuter, `nm/<f>/best.c`, `match.c`, s12); `sweep.sh` older bulk permuter sweep (s13).

Data / rodata / file splitting (s07-s10)
- `rodata_split.py --own <stem> [--dry] --resplit` (a C file owns its `.rodata`; required for float literals, switch tables, strings), `rodata_split.py <stem> <a> <b> --section .data`, `rodata_inject.py <stem> [--dry]` (runs after splat), `rodata_literals.py`, `rodata_bounds.py` (multi-object rodata), `file_split.py <stem> [--at FUNC] [--dry]`,
  `datarefs.py`, `ptrtable.py`.

Porting pipeline (done; `docs/LAYOUT.md`): `run.sh` (never), `port.py`, `match.py`, `port_one.py`, `cmp_syms.py`, `add_syms.py`, `toggle_us.py`, `survey.py`.

## Pitfalls (deduplicated)

Environment / scripts
- `verify_all.sh` (full), `rodata_split.py --resplit`, `file_split.py --resplit` wipe `conker/build/` (`build/hand`, `hand_done`, `pc`, `stackfix`, m2c draft dirs): apply kept drafts first and keep wanted drafts under `tools/decomp-permuter/` or the session scratch dir. After a wipe, functions already in C have no `.s` to screen against.
- A failed compile leaves the previous object (check reports the old state): delete the `.o` first (`cf` / `repair_try.sh` do). `make` prints `conker.eu.bin: OK` only when it relinks (delete `conker/build/conker.eu.ok` to force).
- After changing which functions of an owned file are C, rerun `rodata_inject.py <stem>` (apply.py does). `--quick` does not catch missing splat auto symbols (`needsyms.py`) nor data bytes; the full verify does.
- `apply.py`: crashes on an already applied draft / a `screen.txt` line whose `.c` moved; REJECTs float literals in files that do not own `.rodata`, size-mismatching padding cases and rodata plan conflicts. Check `git diff --stat` for emptied files after any crash.
- BSD `sed -i` needs `sed -i ''`, and `sed -i -E` leaves `*.c-E` files in `src_eu/` that break the Makefile (`rm conker/src_eu/*-E`); prefer `perl -pi`.
- Never `git checkout` a source file to undo an experiment after `protocheck.py --apply` edited it (drops kept prototype fixes): edit the line back. `git checkout` of generated files gives generated output; use `tools/eu_port/baseline/`.
- `tools/n64splat` shows as modified in `git status`: pre-existing submodule noise, not part of commits.
- Adding a header prototype can change codegen in files that called the function implicitly: run `check_files.py` on everything. A US name added in `symbol_addrs.eu.txt` at an address with a `func_eu_`/`D_eu_` name makes splat stop ("Duplicate symbol"). splat auto names in `undefined_syms_auto.txt` win over same-spelled US names: give the EU address a `D_eu_` name in both symbol files.
- `ld_align_section_vram_end: False` is required in `conker/conker.eu.yaml`. splat links all `.data` subsegments of a segment before `.rodata` ones. `check_funcs.py` reports trailing nops as a DIFF (file padding; mid-file it means an EU file boundary: split it).
- Temp-draft hygiene: `repair_try.sh` overwrites `repair/<f>.c` with whatever file you pass; `permute.sh` removes `nm/<f>/` first. K&R and permuter do not mix. Running parallel screens: `tryall` caps at 8 (more got OOM-killed).
- REA / Ghidra are not useful here (MIPS-II ELF). zsh: quote `?`, use `${=var}`.

Matching (recipes in `docs/IDO_SHAPES.md`)
- Check call arities / prototypes and the first compile error before restructuring. Permuter first for register-only DIFF <= 9. Do not give float spills names. Do not copy `arg0` into a local for delay-slot/arg-copy shapes. Hand-written asm (`Handwritten function`), `sd/ld`, `lwr/swr` are not matchable as C at -mips2.

## Next steps (prioritized)

1. Slice below 0x130000 after session 45 (details `docs/sessions/s45.md`, recipes IDO_SHAPES section 16): +14. Open near misses with permuter bests in `conker/build_port/s45/bestfinal_*.c` and `tools/decomp-permuter/drafts/best_func_*.c`:
   `func_1508148C` DIFF2, `func_150FE08C` DIFF3 (0x2D/0 family, leaf), `func_15097DDC` DIFF6, `func_1509CBD4` DIFF6, `func_15013000` DIFF8, `func_1504BA38` DIFF10, `func_1502F6B8` DIFF11, `func_150B78D0` DIFF12, `func_150D2C00` DIFF14 (frame only),
   `func_15015E30` DIFF21, `func_1507BB28` DIFF22; blocked: `func_1505F188` (draft OK, needs `game_83300` to own `.rodata`, which breaks `func_1505D34C`), `func_150F2B20`/`func_150B9A40` (ref keeps `addiu v0,a0,K` pointer live), `func_15062D10`;
   family members not yet tried: `func_150EFE90`, `func_150D4ED0`, `func_150FCD98`. `shortpool.py 70` has ~100 unlogged `func_150*` left (screened batches in `conker/build_port/s45/gensome*.out`: SIZE+n drafts `func_150EFD30`, `func_150EFDE0`, `func_1502298C`, `func_1503E00C`, `func_150174C0` untried).
1b. (older) Slice below 0x130000 after session 41 (details `docs/sessions/s41.md`, recipes IDO_SHAPES section 15): 11 matched. Open near misses (all in `repair_log.tsv`; best permuter sources in `tools/decomp-permuter/drafts/best_func_*.c`):
   `func_1503D658` DIFF7, `func_150225D0` DIFF12, `func_150A3794` DIFF6 (store order), `func_1509B950` DIFF2, `func_1509D49C` DIFF15, `func_150337A8` DIFF16, `func_15003570` DIFF21, `func_150E3B5C`/`func_1509CBD4`/`func_1507488C`/`func_15022304` (SIZE-1/structural),
   `func_15007440` (goto loops, frame OK, DIFF52), `func_1503D950`, `func_1503FCE0`, `func_15088130`, `func_150802A8`. Untried CERR in the slice: `func_1507BB28`, `func_1505F188`, `func_150F2B20`, `func_15062D10`, `func_1502F6B8`.
   Old s39 list still open: `func_1503F23C`, `func_15084814`, `func_150B7B9C`, `func_15083E0C`, `func_15088B08`, `func_15088760`, `func_150952B0`, `func_1506C32C`, `func_1503DA64`, `func_150A00F0`.
   Tips from s41: an apply.py "padding" REJECT can be a neighbour's codegen (K&R forward decl); struct-array indexing stops strength reduction, goto loops stop unrolling; `rlog.sh` takes exactly 7 fields.
   `shortpool.py 70` still has ~190 unlogged functions in the slice.
0. (Session 40 worktree `a`, game >= 0x130000 + init/debugger slice) Unsolved leftovers with notes in `repair_log.tsv`: the **0x2D/0 handler family** with the `or a3,a0` entry copy (`func_151937A4`, `func_151BEB08`, `func_151BCB54`, `func_151BAA18`, `func_151D2E5C` DIFF1; IDO_SHAPES 13.2),
1. Slice below 0x130000 after session 39: of the 44 CERR drafts there only the near misses are left (all in `repair_log.tsv`, sorted by closeness): `func_1509B950` (DIFF2, permuter best in `tools/decomp-permuter/nm/func_1509B950/best.c`), `func_1503A8FC` (DIFF5, v0/v1 roles), `func_1503F23C`, `func_15084814`, `func_150B7B9C` (DIFF16/22 register-only, permuter runs unsolved or still unchecked),
   `func_150E3B5C` (SIZE-1, loop tail `bnel`), `func_1509CBD4` (SIZE-1), `func_15083E0C` (DIFF19), `func_15088B08`/`func_15088760` (frame/arg-copy), `func_150952B0`, `func_1506C32C`, `func_1503DA64`, `func_150A00F0` (frame/stack, see IDO_SHAPES 13.11). `func_150489B0` matches but `apply.py` REJECTs it (16 bytes of nop padding after `game_75E60`): split the padding or add a filler, draft in `docs/sessions/s39_func_150489B0.c.txt`.
   Fresh `gensome.sh` drafts: 30 shortest unlogged pool functions of the slice were screened (list in `docs/sessions/s39.md`); the untouched ones with SIZE+n/DIFF<=22 are `func_15022304`, `func_1503FC54`, `func_1503F8A8`, `func_150CCB48`, `func_1507488C`, `func_150A69E0`, `func_150A3794`, `func_15010600`. `shortpool.py 70` still has ~190 unlogged functions in the slice.
   Fresh short drafts matched at about 0.5 per attempt this session (tables as typed arrays, u64 bit tables, `s32 arg` instead of `u8`).
00. Session 44 leftovers (details in `docs/sessions/s44.md`): DIFF1 `func_15163FEC`/`func_15164134` (second `bnel t2,a2` operand order, drafts in `tools/decomp-permuter/drafts/`), `func_151B6804` DIFF17, `func_151D5714` DIFF16, `func_151D75B0` DIFF16, `func_1518403C`/`func_15191E2C`/`func_1518F8F4` SIZE-n, `func_1514DAD4` (arg-copy shape C). Apply the `new_var` loop-tail recipe to `func_150E3B5C` (slice below 0x130000). Use `tools/eu_port/myasm.sh f draft.c` to read your own asm.
0. (Session 42 solved 11 of the s40 CERR list and the rest of it is done; recipes in IDO_SHAPES-style notes in `docs/sessions/s42.md`. Still open: the `or a3,a0` key-swap family (`func_151937A4` DIFF10, `func_151BEB08`, `func_151BCB54`, `func_151BAA18` SIZE-1), DIFF1s `func_151D2E5C`, `func_1519E874`, `func_151D324C` DIFF12, `func_151A7E2C` DIFF13.) (Session 40 worktree `a`, game >= 0x130000 + init/debugger slice) Unsolved leftovers with notes in `repair_log.tsv`: the **0x2D/0 handler family** with the `or a3,a0` entry copy (`func_151937A4`, `func_151BEB08`, `func_151BCB54`, `func_151BAA18`, `func_151D2E5C` DIFF1; IDO_SHAPES 13.2),
   the `D_800DD280[j][idx]` node searches (`func_151CEBE4` SIZE+1, `func_151A7188`), `func_151C1B20` (shape C, ref frame 0x28 vs 0x20), `func_151A2F10` (frame 0x20 vs 0x28), `func_1514DA28` (DIFF2 spill slot 0x1C vs 0x18), `func_15159828` (SIZE-3),
   `func_10003BD0` (DIFF23 after the permuter). The next untried CERR/short candidates from `shortpool.py` in this slice (`conker/build_port/list3.txt` was screened: CERR `func_15114644`, `func_1511F8A4`, `func_15134908`, `func_151475B0`, `func_1517F3B0`, `func_15182388`, `func_1519E874`, `func_151ACB00`, `func_151BEC7C`, `func_151D324C`, `func_151E4A78`, `func_151E8620`; `func_151D75B0` DIFF16) are not logged.

1. Continue the repair loop over `shortpool.py 70` (about 575 unlogged candidates; ~125 CERR left in `cerr.err`, minus the 28 logged in s34; the ranked results of session 33's `gensome.sh` run are in `tools/decomp-permuter/repair/pool33.res`, 540 drafts: 167 CERR, 167 DIFF, 115 SIZE-, 91 SIZE+; the CERR first-errors are in `repair/cerr.err`, 153 CERR left). CERR with `Dereferenced a non-pointer`/`X undefined` (m2c vector locals `spXX`) and `redeclaration` (forward prototype) were the cheapest class in session 33 (12 of 14 matches); the remaining ones are listed in cerr.err. Queue DIFF<=9 register-only leftovers for the permuter in the background (`permute.sh f draft.c 150 5`).
2. Pool expansions: `shortpool.py 100`, `clones.py --refresh --draft --lax` and `--near 16` after each batch (new matched C = new siblings), shape lists `shapes.py --list A|B 150` (A 101-150: 18, B 33 untouched), Gfx writers 101-150 insns (`gfxfind.py --untried --hints`).
3. Open families worth a fresh idea: shape D unfilled delay slot (176 fns), the `func_150F1B78` family, `func_150AEDF8` family (8), the 43-insn u8 handler family (7), `mul.s` operand-order DIFF1s (`func_150EAA10`, `func_151AAFFC`), `func_151C2600` (DIFF2 frame), `func_150C572C` (DIFF2). All documented in IDO_SHAPES.md.
4. Float functions blocked by rodata are unblocked in owned files (`game_eu_142E40`, `1CCD10`, `12C5F0`, `18B1C0`, `13C400`...): `func_15095B70`, `func_151166FC`, `func_150FF1A8`, `func_1519F500` need real hand work.
5. Longer term: libultra leftovers (`osPfsChecker` ~730 insns in `init_eu_289A0`, `func_10027B50` osLeoDiskInit, unidentified `init_eu_26B30`), `-mips3` per-file build for `sd/ld` functions, naming structs (`struct127`, `struct_eu_node`) to improve m2c, finish splitting EU data, asset formats, then the PC port.

## Session notes

### Session 33
- Docs restructure (this file, `docs/IDO_SHAPES.md`, `docs/sessions/`), no code change.
- Repair loop on the `shortpool.py 70` pool: 621 candidates, `gensome.sh` (5 min) -> 540 drafts. Worked CERR drafts by reading the first compile error first: 21 functions logged, **14 matched (67%)**,
  40 attempts, permuter used on 7 (3 solved: `func_150FE290`, `func_151CB07C`, `func_1514D880`; 3 improved only: `func_1507C608` DIFF4, `func_15030600` SIZE+1; the rest not run).
  Matched: `func_150E3850`, `func_150E3788` (callee prototype moved to file head), `func_1515F4E4` (forward protos), `func_150D9304`, `func_1519C38C` (vertex struct-copy vector integrators),
  `func_15114E8C`, `func_15107FA0`, `func_151080F8` (m2c `spXX` vector locals -> `f32 spXX[3]` arrays passed by address), `func_151145D0`, `func_150FE290`, `func_150E3A94`, `func_151CB07C`, `func_15174F68`, `func_1514D880`.
- New recipes are in `docs/IDO_SHAPES.md` (sections 1.5, 2.3, 3.5, 4.1, 5.1): `fwdproto.sh` also for moving a file-local prototype to the head; `struct127 *` loops need `p = D_800CC2D0` inside the `if`; `s32 idx = *(u8 *)...; if (idx >= 0)` keeps a `bltz` on a byte; fn-pointer tables for `extern s32 D_x` called as function.
- Not solved (notes in `repair_log.tsv`): `func_150626EC`, `func_1502F6B8` (SIZE-1/-2: the ref materialises `D_800CC2D0` hi/lo twice, loop pointer and index base separately; mine CSEs), `func_15040CC8` (empty counting loop kept in `s0`), `func_150C1698` (s16 index free-list unlink, rotated registers),
  `func_150D8F44` (shape A arg copy in a3 as 4th pass-through arg), `func_151D441C` (DIFF25: `subu` hoisted above the `lw v0` in the ref), `func_15030600` (saved register numbering).
- `-O2` quirk worth knowing: `tools/eu_port/m2c/tryall` on a CERR-free list is the cheapest way to try 3-24 mechanical variants (declaration orders did nothing for register roles in `func_150C1698`).
- Pitfall: a stray `cat > /tmp/x` in a compound shell command blocks on stdin (the call hangs until the tool timeout).

### Session 34
- Repair loop, CERR-first, 29 functions logged, **5 matched**: `func_1507E1D0` (`f32 sp28[3]`/`sp1C[3]`, stackfix order, explicit else), `func_15044C54` (pass-through `allocate_memory(arg0,1,0,0)`), `func_15131D98` (u8 callee param: no `& 0xFF`, `f32 * call()`),
  `func_1517F54C` (file gets `s32 func_1517F470();` fwd proto), `func_151E856C` (`extern u8 D[][6]` stops strength reduction; permuter finished; uses `D_800ABE94` extern, file does not own rodata). Recipes are in IDO_SHAPES (1.12, 3.16, 4.17, 5.4). Details and token cost: `docs/sessions/s34.md`.
- Near misses worth a fresh look (all logged): `func_150D513C` (DIFF2, only frame 0x28 vs 0x30 from the unnamed spill of a function address), `func_151E856C`-style tables, `func_15003120` (DIFF36 roles), `func_15168E54` (DIFF14), `func_1509D274` (DIFF19, s0/s1 roles), `func_151733EC` (DIFF8, frame), `func_150D247C` (SIZE-1), `func_151481BC` (SIZE-1, ref presets v0 in the beqz delay slot).
- Pitfall: `repair_try.sh` overwrites `repair/<f>.c` with the draft you pass; use one distinct draft filename per function (I clobbered a shared `g.c`). In zsh, `set -- $var` does not split; use bash for loops over lists.

### Session 35
- Bulk permuter sweep (`sweep.sh perm`, 3 streams x -j3, 120 s) over 103 SIZE+-1 / DIFF<=12 leftovers from pool33.res + repair_log: 6 solved; pass 2 from best.c (240 s) on 13 improved: 2 solved; 1 more by hand (func_1517A028). 9 matches, 8 applied (func_150351A4 REJECTed by apply.py). ~2.5 h wall, few tokens. Details and unsolved DIFF1/2 list in `docs/sessions/s35.md`.
- Yield is about 8% per candidate; the remaining SIZE+-1 drafts are structural (permuter cannot fix). Next: the 90 candidates left unsolved are not worth repeating; go back to CERR-class drafts or new pools.
- Pitfall: a permuter that ignores `timeout -s INT` stalls a whole `sweep.sh perm` stream; kill it with `docker exec conkerdev pkill -9 -f 'permuter.py nm/<f>'`.

### Session 39
- Slice below 0x130000 (main checkout), CERR-class drafts first, then fresh drafts: about 40 functions tried, **19 matched in 2 commits** (`53a176e`, `845f5be`), 1 more matching but not applicable (`func_150489B0`, padding). Recipes: IDO_SHAPES section 13, per-function notes in `repair_log.tsv`, details `docs/sessions/s39.md`.
- Pitfalls: `fwdproto.sh` skips an existing identical line, so to move a file prototype to the head delete the old line first; `zsh` needs `${=LIST}` for `gensome.sh`; `rm -f v/*` is blocked by the harness safety check (use `mkdir -p` and overwrite).
- The Mac mini permuter is shared with the other agent (many concurrent jobs): a 400 s job took about 10 min wall.
