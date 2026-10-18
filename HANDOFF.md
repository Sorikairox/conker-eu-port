# Hand-off: Conker's Bad Fur Day (EU) decompilation

Last updated: 2026-10-19 (session 33). Update this file at the end of every work session.

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
- **3139 / 5913 functions in C (53.1%)**, code bytes 340,772 / 2,253,856 (15.1%) (end of session 32; updated at the end of this file's session notes below).
  init 361/540 (38.5% of bytes), game 2727/5330 (13.0%), debugger 31/43 (41.3%). Progress by session is in `docs/sessions/commit_table_and_state_history.md`.
- Every plain asm subsegment is a C file (`*_eu_<rom>.c`); new decompilation = replace a `#pragma GLOBAL_ASM` with C, no yaml edits. All 266 US C files are ported to `conker/src_eu/` (plus EU-only `game_30E60.c`, `game_8FCB0.c`).
- **From commit `b5aeddd` on, `src_eu/`, the EU yaml and symbol files are hand-edited. Never run `tools/eu_port/run.sh`.**
- Session 33 (this one): docs restructure, then repair loop on the session-32 pool; see "Session 33" at the end.
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

Verification / build
- `verify_all.sh [--quick]` full check (s-brief). `check_files.py [src_eu/X.c]` whole-object `.text` + owned `.rodata/.data` vs ROM (reliable; `check_funcs.py` skips functions already in C). `fdiff.py src_eu/X.c func` word diff of a C function. `rodiff.py` rodata word diff. `bindiff.py`.
- `needsyms.py [--apply] funcs` re-adds splat auto symbols that a newly matched function was the last user of (only the full verify catches it, s13). `revert_bad.py` reverts bad new C to GLOBAL_ASM (s03).

Drafting and screening (`m2c/` is host-side; paths in `m2c/` scripts assume `~/conker` and `conkerdev`; s04-s07)
- `m2c/list.py` all GLOBAL_ASM functions; `m2c/gen2.py outdir min max` m2c drafts + 8 variants; `m2c/screen.py` (OK/DIFFn/SIZE+-n/CERR; word diff with `SCREEN_V=1`); `m2c/try func [draft]`, `m2c/tryall func a.c b.c...` (8 parallel),
  `m2c/mine func draft.c` (my asm on one line; honours `SCREEN_OPT`), `m2c/keep`, `m2c/apply.py build/hand`, `m2c/screenall dir`, `m2c/merge.py`, `m2c/narrow.py`, `m2c/switchinline.py`, `m2c/compound.py`, `m2c/voidret.py`, `m2c/spawngen.py`/`spawn.py` (effect spawners, s09-s11), `m2c/flags src_eu/X.c` (build with each OPT_FLAGS).
- `gensome.sh <funcs>` drafts for a few functions into `repair/fresh/`; `gen40.sh [max]` bulk; `m2cfix.py list` declfix + bulk screen (s30); `fctx.sh <func>` / `sh.sh <func>` context + asm on one line (s18, s24).
- `shortpool.py [max]` candidate pool of unlogged short functions (s30, s32). `shapes.py [--list A|B|C|D N]` tags known shapes (s24). `gfxfind.py [--list|--untried|--hints F]` Gfx writers (s31).
  `clones.py [--draft] [--lax]`, `--near K`, `--asm-clusters` template clones (s25, s28); `declfix.py` called by it (s29).

Repair loop
- `repair_ctx.sh <f>` context + `draftcheck.py` HINT lines; `repair_try.sh <f> draft.c`; `rlog.sh` log row into `repair_log.tsv` (560 rows); `stackfix.py f draft.c` / `--scan` / `--bisect` (frame/slot puzzles, s15);
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

1. Continue the repair loop over `shortpool.py 70` (about 600 unlogged candidates after session 33). First read the first compile error of CERR drafts (many are prototype/forward-declaration fixes, `fwdproto.sh`); for SIZE+-1..3 drafts read the asm before restructuring; queue DIFF8-9 register-only leftovers for the permuter in the background.
2. Pool expansions: `shortpool.py 100`, `clones.py --refresh --draft --lax` and `--near 16` after each batch (new matched C = new siblings), shape lists `shapes.py --list A|B 150` (A 101-150: 18, B 33 untouched), Gfx writers 101-150 insns (`gfxfind.py --untried --hints`).
3. Open families worth a fresh idea: shape D unfilled delay slot (176 fns), the `func_150F1B78` family, `func_150AEDF8` family (8), the 43-insn u8 handler family (7), `mul.s` operand-order DIFF1s (`func_150EAA10`, `func_151AAFFC`), `func_151C2600` (DIFF2 frame), `func_150C572C` (DIFF2). All documented in IDO_SHAPES.md.
4. Float functions blocked by rodata are unblocked in owned files (`game_eu_142E40`, `1CCD10`, `12C5F0`, `18B1C0`, `13C400`...): `func_15095B70`, `func_151166FC`, `func_150FF1A8`, `func_1519F500` need real hand work.
5. Longer term: libultra leftovers (`osPfsChecker` ~730 insns in `init_eu_289A0`, `func_10027B50` osLeoDiskInit, unidentified `init_eu_26B30`), `-mips3` per-file build for `sd/ld` functions, naming structs (`struct127`, `struct_eu_node`) to improve m2c, finish splitting EU data, asset formats, then the PC port.

## Session notes

### Session 33
(filled in at the end of the session)
