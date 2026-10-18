# Hand-off: Conker's Bad Fur Day (EU) decompilation

Last updated: 2026-10-19 (twenty-eighth session). Update this file at the end of every work session.

## Goal

Full matching decompilation of the **European** ROM. This is a private fork of
[mkst/conker](https://github.com/mkst/conker); upstream is US-first. The long-term aim
is a native Mac and Windows port. The user decided on a separate fork: nothing is
pushed, and nothing goes upstream.

- Repo: `~/conker`, branch `eu`. Remote `upstream` is mkst/conker.
- ROM: `~/conker/baserom.eu.z64`, z64 byte order, SHA1 `ee7bc6656fd1e1d9ffb3d19add759f28b88df710`.
  The user's original `~/Downloads/Conker's Bad Fur Day (Europe).n64` is byte-swapped
  and must not be modified.

## Current state

- The full EU ROM rebuilds **byte-identical** (`build/conker.eu.z64: OK`).
- **3071 / 5913 functions in C (51.9%)**; code bytes 332,360 / 2,253,856 (14.7%)
  (end of session 28, from `verify_all.sh`).
  - init: 361/540 functions (38.5% of bytes)
  - game: 2679/5330 (12.7%)
  - debugger: 31/43 (41.3%)
  - History: 1094 (18.5%) after the automated port, 1363 (23.1%) after the hand port,
    2374 after the first round of new decompilation (session 3), 2563 after session 4,
    2622 (253,312 bytes) after session 5, 2664 (265,996 bytes) after session 6, 2682
    (268,452 bytes) after session 7, 2706 (273,596 bytes) after session 8, 2735 (277,860 bytes)
    after session 9, 2757 (281,452 bytes) after session 10, 2772 (286,048 bytes) after session 11,
    2780 (287,492 bytes) after session 12, 2799 (290,016 bytes) after session 13, 2820 (292,952 bytes) after session 14, 2823 (293,688 bytes) after session 15, 2842 (296,208 bytes) after session 16, 2877 (300,256 bytes) after session 17, 2899 (302,528 bytes) after session 18, 2922 (305,776 bytes) after session 19, 2948 (307,808 bytes) after session 20, 2959 after session 21, 2963 (310,916 bytes) after session 22, 2971 (312,680 bytes) after session 23, 2991 (316,280 bytes) after session 24, 3026 (326,668 bytes) after session 25, 3039 (328,116 bytes) after session 26, 3059 (330,824 bytes) after session 27.
- Every former plain `asm` subsegment is now a C file (`*_eu_<rom>.c`, initially all
  GLOBAL_ASM stubs; commit `c3f2d8f`), so new decompilation never needs yaml edits:
  replace a pragma with C.
- All 266 US C files are ported to `conker/src_eu/`, plus two EU-only files that
  come from EU file boundaries: `game_30E60.c` (tail of `game_305D0`) and
  `game_8FCB0.c` (tail of `game_83300`).
- No `#if 0 // US version; EU code differs` blocks are left.

Commits on `eu`:

| Commit | What |
|---|---|
| `fff8a37` | EU configs moved to splat 0.34; asm-only matching build (baseline) |
| `585ee67` | First automated US→EU port (232 files) |
| `c2cf2b3` | Anchor-based placement; baseline inputs pinned |
| `8eb7484` | Looser anchor outlier filter (245 files) |
| `e448d65` | `.rodata` of ported C files placed in data blobs (252 files) |
| `b5aeddd` | This hand-off document |
| `d6c0494` | 37 "differing" functions were only missing EU symbols; restored as C |
| `d59c123` | 8 more: PAL constants, debugger text width, s16 store, padding stubs |
| `b57f948` | Last 4 differing functions; new EU file `game_30E60.c` |
| `af90530` | Hand-port of 11 of the 14 unported files (+ `game_8FCB0.c`) |
| `2142e35` | The 3 asm-only unported files get their own subsegments |
| `b5aa354` | Hand-off update after the hand port |
| `fac015a`…`cfe5861` | New decompilation, ~283 functions in 10 commits (object lists, object script interpreter in `game_A28B0`, n_seqplayer/event queue/sound handles in init, EEPROM save, ring buffer, display-list relocation and state cache, matrix/vector helpers, stream decoder in `game_221290`, guNormalize, pfsisplug2) |
| `c3f2d8f` | The 413 plain asm subsegments become C files (GLOBAL_ASM stubs) |
| `c67d78d` | Salvage of an interrupted parallel round: 728 more functions (see below) |
| `8d3f205`…`fc0e53a` | Session 4: 189 functions (near-misses, m2c pipeline, hand fixes); tools in `tools/eu_port/m2c/` |
| `8430db4`…`3d5a326` | Session 5: 59 functions (variant screening, near misses, sqrtf split, 40 libultra functions at -O1) |
| `3df102d`…`204343f` | Session 6: 42 functions (libultra controller/pfs/SI/PI/VI/thread at -O1, libc ldiv/_Litob at -O2, `narrow.py`) |
| `4b80d37`…`4086ef1` | Session 7: u8 handler prototypes, 16 handlers, `__sinf`/`sinf` with their own .rodata/.data (first data-blob splits) |
| `624bf92`…`3c2d62f` | Session 8: real game .data/.rodata boundary, C files own their .rodata (`rodata_split.py --own`), 24 rodata functions, 2 EU file splits |
| `9fddd60`…`dcf890a` | Session 9: 26 EU file splits (`file_split.py`), 83 files own .rodata, 29 functions (const local arrays, effect spawners) |
| `18c0449`…`ba052c8` | Session 10: `spawngen.py` (spawners from asm), C files own `.data` (`rodata_inject.py`), 22 functions |
| `c6ae2b4`…`fce108a` | Session 11: `spawngen.py` calls/arg stores, 15 hand-written spawner and float/switch functions |
| `4df1653`…`364d883` | Session 12: decomp-permuter (`tools/eu_port/permute.sh`), 8 near misses solved by it |
| `2b846db`…`3a88cab` | Session 13: scripted near-miss sweep (`tools/eu_port/sweep.sh`), 19 functions |
| `2f1f805`…`c896fcf` | Session 14: native arm64 toolchain, sweep passes 3/4, hand-finished near misses, 21 functions |
| `63f199e`…`ae35e92` | Session 15: `protocheck.py` (152 prototype fixes), `stackfix.py`, `rescreen.py`, 3 functions |
| `c5c5784`…`f68cfe6` | Session 16: structured repair loop (`repair_ctx.sh`, `repair_try.sh`, `repair_log.tsv`), 19 functions |
| `f300d27`, `75e7386`, `3b05e9d` | Session 17: `draftcheck.py` hints in `repair_ctx.sh`, fresh m2c drafts of short functions (`gen40.sh`), `game_eu_13C400` owns .rodata; 35 functions (+9, +11, +14 in the three batches) |
| `028cb85` | Session 20: permuter on hand drafts, dead-addiu trick, table-call family; 26 functions |
| `2ad4fa9`, next | Session 21: `// fakematch:` labels on sessions 19-20 constructs, own rodata for `game_eu_1C3530`; 11 functions |
| `8fdd85e`, next | Session 22: 70-150 insn functions experiment; 4 functions, +1,536 bytes |
| `e5241d4`, `270f3d8`, next | Session 23: recurring blocked shapes; "Known IDO shapes" section; 8 functions, +1,764 bytes |
| `27e612a`, next | Session 24: `shapes.py`, recipes A/B applied family-wide; 20 functions, +3,600 bytes |
| `b59b0cc`, next | Session 25: `clones.py`, template clones; 35 functions, +10,388 bytes |

**From `b5aeddd` on, `src_eu/`, the EU yaml and the symbol files are hand-edited.
Do not run `tools/eu_port/run.sh`: it would regenerate them from the baseline and
throw all of that away.**

## Quick start for a new session

- Standard brief and rules: `tools/eu_port/AGENT_BRIEF.md`.
- One-command verification: `tools/eu_port/verify_all.sh` (`--quick` skips the
  re-split). It prints code build / check_files / full ROM status and progress.
- Progress summary only: `python3 tools/eu_port/progress.py conker/progress.csv`.
- A function that needs float literals, a switch or strings: `rodata_split.py --own <stem>
  --resplit` first (session 8 section, "Workflow").
- A C file that is several EU objects: `tools/eu_port/file_split.py <stem> [--dry]` (session 9).
- A function that copies a non-const local array from `.data`: own the file's `.data` (session 10).
- A near miss (C draft a few words off): `tools/eu_port/permute.sh <func> <draft.c> [secs] [jobs]`
  (decomp-permuter, session 12). Run it with run_in_background; batch with `-l list`.
- The whole near-miss sweep (m2c drafts -> screen -> permuter -> apply): `tools/eu_port/sweep.sh`
  (session 13).
- Prototype problems (wrong void/int return, u8/s16 params, float args, arg counts):
  `tools/eu_port/protocheck.py` (report), `--apply --skip-logged` (fix, verified), then
  `tools/eu_port/rescreen.py` (session 15).
- Pre-checks of a draft's calls/tables against the asm (session 17): `tools/eu_port/draftcheck.py <func> [draft.c]`; `repair_ctx.sh` prints its `HINT` lines. Fresh m2c drafts of short asm functions: `tools/eu_port/gen40.sh [max=40]` (-> `repair/fresh/`, ranking in `repair/fresh.txt`). Log rows: `tools/eu_port/rlog.sh func start attempts end y|n perm y|n "note"` (never pass a bare `?`, zsh globs it).
- Budgeted LLM repair of near misses (session 16): `tools/eu_port/repair_ctx.sh <func>` (target asm + draft + diff region), write a reasoned rewrite, `tools/eu_port/repair_try.sh <func> <draft.c>` (one line OK/DIFFn/SIZE±n; OK drafts go to `conker/build/hand` for `apply.py build/hand`). Log in `tools/eu_port/repair_log.tsv`.
- A draft whose stack slots or frame size are off: `tools/eu_port/stackfix.py <func> <draft.c>`;
  `--scan list` / `--bisect func draft.c` (session 15).

## Fast native toolchain (session 14 restart)

The inner loops run in a **native arm64 image** (`Dockerfile.arm`, image `conker-arm`).
It has the native linux-arm build of ido-static-recomp v1.2 at `/opt/ido5.3`, selected
through `IDO_DIR` (the Makefile and compile_us.py honour it), so there's no x86
emulation. The `.text`, `.rel.text` and `.data` output is byte-identical to the x86 IDO;
only `.mdebug` (debug info, discarded at link) differs.
- A clean code build takes 20 s instead of 81 s, and one compile is about 3.6× faster.
- The permuter and screening get the speed-up automatically, because they take the
  compile line from `make -n`.
- Build the image with
  `docker build --platform linux/arm64 -f Dockerfile.arm -t conker-arm .`, then start
  `conkerdev` from it (command below).
- `verify_all.sh` still runs on the x86 image `conker` and stays the authority before
  every commit. It also covers the bundled x86 `tools/gzip` used for ROM recompression.
- Permuter time budget: a function now gets ~3.6× more iterations per second, so about
  100 s per function in a sweep matches the old 300 s. Put the closest candidates
  (DIFF1–5, SIZE±1) first.

## Build environment

The toolchain (IDO 5.3 recomp, mips-linux-gnu binutils) is Linux x86-64 only, so
everything runs in Docker. Docker Desktop is installed, but `docker` is **not on PATH**:
`/usr/local/bin/docker` points into a missing OrbStack install. Use:

```sh
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
docker build --platform linux/amd64 -t conker .     # after Dockerfile/requirements changes
```

Full build and verify, from the repo root:

```sh
docker run --rm --platform linux/amd64 -v ~/conker:/conker conker bash -c '
  make VERSION=eu extract && make -C conker VERSION=eu extract &&
  make -C conker VERSION=eu -j8 && make -C conker VERSION=eu replace && make VERSION=eu -j8'
```

Expected output:
- `conker/build/conker.eu.bin: OK` (code sub-project)
- `build/conker.eu.z64: OK` (whole ROM)

Progress: `make -C conker VERSION=eu progress` writes `conker/progress.csv`.

Faster iteration: keep one container running and `docker exec` into it.

```sh
docker run -d --name conkerdev --platform linux/arm64 -v ~/conker:/conker -w /conker conker-arm sleep infinity
docker exec conkerdev make -C conker VERSION=eu -j8          # code build + verify
docker exec conkerdev bash -c 'make -C conker VERSION=eu replace && make VERSION=eu -j8'  # full ROM
```

After a yaml or `symbol_addrs.eu.txt` change, re-split (the root `make VERSION=eu
extract` only needs to run once per checkout):

```sh
rm -rf conker/asm conker/build; find conker -maxdepth 1 -name '*_auto.txt' -delete
docker exec conkerdev make -C conker VERSION=eu extract
```

(In zsh, `rm conker/*_auto.txt` fails when no file matches and aborts an `&&` chain;
use `find -delete`.)

Notes:
- The image sets `SPIMDISASM_ASM_NM_LABEL=""`. asm-processor rejects the `nonmatching`
  line that current spimdisasm emits before `glabel`.
- `pyelftools` is in `requirements.txt`; the porting tools use it.
- Splitting from scratch needs `rm -rf conker/asm conker/build conker/*_auto.txt` first.
  Stale asm files get assembled otherwise.

## Session 3 incident: interrupted parallel round

The decompilation agent fanned out into parallel helpers ("round 2") that hit a usage
limit mid-run and left uncommitted edits in 192 files. The tree compiled but did not
match (built binary 0x40 bytes long). Recovery, which is the template if it happens
again:

1. `git diff > backup.patch`.
2. `check_files.py` (inside the container, after building) compares every src_eu
   object with the original bytes at its rom range. 25 files were bad.
3. A HEAD worktree split supplies the `.s` files for reverted functions (copy the
   submodules `tools/n64splat asm-processor asm-differ mips_to_c` into the worktree,
   they are not checked out there). `revert_bad.py <head conker dir> src_eu/X.c ...`
   then reverts, file by file, the first differing function back to GLOBAL_ASM until
   the file matches: 31 functions reverted, everything else kept.
4. One untouched file (`game_A28B0`) broke because round 2 added a prototype
   `func_1505D024(struct127 *, s32, s32, s32)` to `functions.h`; removed it.
5. Clean re-split, full ROM verify, commit.

Lesson for parallel work: have each worker commit (or at least verify with
`check_files.py`) per small batch, so an interruption loses little.

## Session 4: m2c pipeline and hand fixes

Work was sequential (no agents). +189 functions (2374 -> 2563), +24,424 bytes of code
in C (9.8% -> 10.9%): 30 of the 31 salvage near-misses, ~120 functions straight from
m2c drafts, the rest m2c drafts fixed by hand. Commits `8d3f205`..`fc0e53a`.

The pipeline scripts are in `tools/eu_port/m2c/` (paths inside assume the repo at
`~/conker` and the container `conkerdev`):

| Script | Where | Use |
|---|---|---|
| `list.py` | host | `python3 list.py > all.txt` (in that dir): every GLOBAL_ASM function with its instruction count, file, jump-table flag |
| `gen2.py` | host | `gen2.py <outdir> <min> <max>`: m2c drafts and variants into `<outdir>/v0..v7/<func>.c` (8 processes). Needs `venv/` next to it: `python3 -m venv venv && venv/bin/pip install 'pycparser<3'`. Caches per-file contexts in `ctx/`. Use an outdir under `conker/build/` so the container sees it |
| `screen.py` | container | `docker exec -w /conker/conker conkerdev python3 <path>/screen.py build/<dir>/vN 8` -> `screen.txt` (OK / DIFFn / SIZE±n / SYM / CERR, errors in `errs/`). Copy the script under `conker/` (e.g. `conker/build/`) first: the container only mounts the repo |
| `apply.py` | container | `apply.py build/<dir>/final`: inserts the `OK` lines of `final/screen.txt` into `src_eu`, checks whole files, falls back to one function at a time; prints ACCEPT/REJECT |
| `autotry.py` | container | older, slower (make + whole-file check per function); superseded by screen + apply |
| `verify` | host | full code build + `check_files.py`; prints VERIFY-OK / VERIFY-FAILED (exit status). Use it before every commit |
| `cf` | host | `cf src_eu/X.c func [-v]`: rebuild one object, per-function diff and whole-file check (removes the stale .o first; a failed compile used to leave the old object and look OK) |
| `rep.py` / `revert.py` / `strip.py` | host | `rep.py func < draft.c` replaces a pragma with C between `//BEGIN`/`//END` markers; `revert.py func` puts the pragma back; `strip.py` removes the markers before committing |
| `tidy.py` | host | cosmetic clean-up of `M2C_FIELD` expansions in changed files |
| `best` | host | `D=<dir> best func`: the variant draft with the fewest differing words |

Merging variants: for each function take the first `OK` across `v0..v7` into
`final/` (copy the draft and append `OK func file` to `final/screen.txt`), then run
`apply.py`. A full set of drafts for functions up to 200 instructions with all 8
variants was generated at the end of the session into `conker/build/k/` but not
screened; it is gitignored and may be gone, regenerate with `gen2.py`.

How the pieces work:

- **Draft generation** (host, needs `pycparser<3`; the system Python and the image both
  have pycparser 3.x, which m2c cannot import, so use a throwaway venv):
  `m2c.py --valid-syntax --context <per-file ctx>`, where the per-file context is
  `gcc -E` of the `src_eu` file (headers plus the file's own prototypes) with `#pragma`
  lines dropped. Post-processing: `M2C_FIELD(x, T *, off)` -> `(*(T *)((u8 *)x + off))`,
  `M2C_UNK*` -> sized ints, `void *` -> `u8 *` (so byte arithmetic works), `?` types ->
  `s32`, and `*(&D + (i * k))` -> `*(T *)((u8 *)&D + (i * k))` (m2c's byte offsets
  otherwise get scaled). Drafts containing `M2C_ERROR`, bitwise casts, struct copies,
  unaligned access or jump tables are dropped.
- **Variants per function**: base; `s8 *` -> `u8 *`; `--no-andor`; reversed local
  declaration order; `s32 pad;` as first local; `--no-stack-spill` (+ pad, + reversed).
- **Screening** (in the container, 8 worker processes, grouped by C file): each draft
  goes into a standalone TU (the C file with every GLOBAL_ASM pragma removed and the
  draft in place of its own pragma), compiled directly with the file's `cc` line from
  `make -n -B` (so per-file OPT_FLAGS apply). The function's words are compared with
  its `.s` (relocations masked, relocated symbol names must appear on the asm line, no
  relocations against section symbols, i.e. no new .rodata/.data). ~1500 drafts take
  about a minute.
- **Apply**: insert every screened draft, rebuild the touched objects, compare each
  whole object with the ROM (`check_files.py` logic, plus "no data section grew");
  files that fail are redone one function at a time.
- Yield: about 10% of functions up to 40 instructions match as generated, ~3% of
  41-100, under 1% of 101-200. The rest of the session was hand-fixing near misses.

Recurring fixes for near misses (IDO 5.3 -O2 -g3):
- Byte constants >= 0x80 stored through `s8 *` assemble as `-1`/`0xFFC8`: use `u8 *`.
- m2c misses stack arguments it never reads; count them from the caller's stack slot
  offsets (`arg4` at `0x10($sp)` etc.).
- Stack slot off by 4: add an unused `s32 pad;` as the first local (moves spills down)
  or delete m2c's `spXX = temp;` spill copies (moves them up); declaration order of
  locals also moves slots (`func_151AA72C`, `func_150E8854`).
- A pointer kept in a register across both branches (`addiu vX, a0, 0x28` in two delay
  slots) comes from a pointer local initialised before the `if`, not from a field
  access in each branch.
- A value reloaded instead of CSE'd: the source read it with a different type/cast.
- Same register for two unrelated values: reuse one variable (`func_1519EF74`).
- `var = 0; if (c) var = f(); return var;` from m2c often wants early returns.
- Index arithmetic `base + i * size` vs `&((T *)base)[i]` changes `addu` operand
  order; `(u8 *)p + i * k` vs `i * k + (u8 *)p` too (`func_150243AC`, `func_15157DD0`).
- Operand order of commutative float ops sometimes follows the source and sometimes
  not; try both, then give up.
- Unsolved patterns worth a fresh look: a global loaded into `v0` then moved to `a0`
  for a call (`if (D) { f(D); D = 0; }`, `func_1509D464`, `func_15080FE8`), and an
  argument stored to its home slot in a call's delay slot although never reloaded
  (`func_151AD110`).

## Session 5: variant screening saturated, libultra at -O1

Sequential, 6 work commits (`8430db4`..`3d5a326`), +59 functions (2563 -> 2622).

- **Variant screening** of all asm functions up to 200 instructions (`conker/build/k`,
  regenerated with `gen2.py`, ~2500 functions): only 9 new OK drafts across the 8 old
  variants plus the new ones below. Further variant sets tried, all with 0-3 hits:
  `compound.py` (`X = (T)(X op Y)` -> `X op= Y`), `voidret.py` (unused `s32` call
  results -> `void` prototypes), `genx.py ... --void`, `genx.py ... --reg-vars saved`,
  and `voidret` applied to every other variant. Automated variants are exhausted for
  this size range; what remains needs hand work (or real struct types).
- **Near misses fixed by hand** (session-4 list): `func_1509D464`, `func_15080FE8`
  (global in `v0`: `if (D) { r = D; f(r); D = 0; }`), `func_151AD110` (arg home store:
  an `if (arg0) {}` after the call keeps `arg0` live), `func_1001091C` (early returns
  instead of `&&`), `func_15195418` (`volatile` + `s32 pad`), `func_150ED7B4` (m2c
  invented a third argument), `func_15166774` (`+=` fixes operand order),
  `func_1509FAD4` (plain nested ifs), `func_1503F5A0` (callee is `void`, see below),
  `func_150D2564` (`u8` loop counter).
- **`sqrtf` split done**: `game_eu_21D010` is split at 0x21D050; `game_eu_21D050.c`
  (`func_151EF840`, `return sqrtf(x);` with the intrinsic) builds `-O2`.
- **libultra is -O1** (EU): every libultra C function tried matched at `-O1` (stack
  homes for args, `register u32 saveMask`), except libc `string.c` (memcpy/strlen/
  strchr) at `-O2` with `unsigned char`. Files now built with overrides (see the EU-only
  block in `conker/Makefile`): `game_eu_21D010` (osPiReadIo), `game_eu_21E320`
  (__osSiCreateAccessQueue/__osSiGetAccess/__osSiRawStartDma), `init_eu_22D70`,
  `init_eu_22FE0`, `init_eu_23050`, `init_eu_232A0`, `init_eu_23360` (new subsegment,
  string.c), `init_eu_23860`, `init_eu_238E0`, `init_eu_23A20`, `init_eu_23B70`,
  `init_eu_24210`, `init_eu_24220`, `init_eu_24260`, `init_eu_242F0`, `init_eu_24320`
  (timers), `init_eu_24870`, `init_eu_24BF0`, `init_eu_24DF0`, `init_eu_24ED0`,
  `init_eu_251D0`, `init_eu_252D0`, `init_eu_25360`, `init_eu_265F0`, `init_eu_26AD0`.
  Libultra internals are referenced by their EU names with a comment
  (`D_8002C134` = `__osViNext`, `D_8002C130` = `__osViCurr`, `D_8002C148` =
  `__osRunQueue`, `D_8002C140` = `__osThreadTail`, `D_8002C0C0` = `__osTimerList`,
  `D_80042D40..50` = current time / base counter / VI intr count / timer counter,
  `D_8002AE90` = `__osPiDevMgr`, `func_10007BA4/CC8/D14/D28` = `__osEnqueueAndYield`,
  `__osEnqueueThread`, `__osPopThread`, `__osDispatchThread`, `func_10023BC0/C04` =
  `__osPiGetAccess/RelAccess`, `func_10024190` = `osWritebackDCache`).
  The function the port calls `__osGetActiveQueue` (`init_eu_24870`) is really
  `__osViGetCurrentContext` (it returns `__osViCurr`).

New tools in `tools/eu_port/m2c/` (host side, same conventions as session 4):

| Script | Use |
|---|---|
| `try func [draft.c]` | screen one draft (stdin if no file); `V=1 try ...` prints a word diff (ref, mine, asm line), also for SIZE results |
| `flags src_eu/X.c [flagset ...]` | build the file with each `OPT_FLAGS` override (default `-O1 -O2 -g "-O2 -g3"`) and print check results; the **last** flagset stays in the Makefile |
| `compound.py in out` / `voidret.py in out` | derive a variant set from another (only changed drafts are written) |
| `genx.py out min max <m2c flags>` | one draft per function with extra m2c flags |
| `merge.py out vdir...` | collect the first OK draft per function into `out/` for `apply.py` |

`screen.py` now counts a relocation whose symbol is not on the asm line as one
differing word instead of stopping with `SYM:` (gives real DIFF counts), and writes
`<func>.diff` when `SCREEN_V=1`. `conker/build/best.txt` (gitignored, may be gone) lists
the lowest DIFF per function across all variant sets.

Lessons:
- m2c gives unused call results the type `s32`; a non-void prototype makes IDO avoid
  `v0` and shifts register allocation (`func_1503F5A0`). Use `void` prototypes.
- m2c can invent arguments from registers that merely hold a value at the call
  (`func_150ED7B4`'s callee takes two floats, not three args).
- `x += y` and `x = x + y` can differ in `addu` operand order.
- A loop over `u8 i` shows up as `andi $t, $s, 0xFF` before the compare.

## Session 6: libultra almost done, `narrow.py`

Sequential, 4 work commits (`3df102d`..`204343f`), +42 functions (2622 -> 2664),
+12,684 bytes. Everything written from libultra/libc source knowledge, built with `m2c/flags`.

- **-O1** (added to the EU-only block in `conker/Makefile`): `init_eu_277D0` (osJamMesg,
  osPiGetCmdQueue), `init_eu_27960` (__osSiDeviceBusy), `init_eu_27950` (__osSpGetStatus),
  `init_eu_26870` (__osSpRawReadIo/WriteIo; `__sinf` stays asm in the same file),
  `init_eu_26370` (__osContAddressCrc/DataCrc, osDestroyThread), `init_eu_24ED0`
  (osContStartReadData, osContGetReadData, __osPackReadData = `contreaddata_text_017C`),
  `init_eu_256E0` (osContInit, __osContGetInitData, __osPackRequestData), `init_eu_25AA0`
  (__osSiGetAccess, __osSiRawStartDma = `func_10025B60`), `init_eu_25FC0`/`init_eu_25C10`
  (__osContRamRead/Write + pack helpers `func_10026204`/`func_10025E40`), `init_eu_25370`
  (osPfsIsPlug group, same code as `pfsisplug2.c`), `init_eu_27990` (osPfsInit =
  `func_10027990`, __osPfsGetStatus), `init_eu_27C40` (all of contpfs.c: __osSumcalc,
  __osIdCheckSum, __osRepairPackId, __osCheckPackId, __osGetId, __osCheckId,
  __osPfsRWInode, __osPfsSelectBank), `init_eu_23CC0` (osPiRawStartDma,
  osEPiRawStartDma = `func_10023DA0`; bcopy/osWritebackDCache stay asm),
  `init_eu_24320` (__osViInit = `func_10024720`), `init_eu_24880` (__osViSwapContext).
- **-O2** (libc): `init_eu_23400` (lldiv, ldiv), `init_eu_23590` (_Litob; `unsigned char`
  for `type`, the buffer and the digit tables, like string.c).
- This libultra is an old revision: OSPifRam loops clear 16 words (`i < 16`, the
  pifstatus word included), retry loops are `while (ret == PFS_ERR_CONTRFAIL && retry-- >= 0)`,
  osDestroyThread walks `tlnext` with pred/succ, osPiRawStartDma has no domain handling,
  `OS_USEC_TO_CYCLES` must be spelled `((u64)n * osClockRate) / 1000000LL`
  (`osContInit`), `__osContDataCrc` needs `temp |= 0;` (not `&= 0xFF`) in the `i == 32` branch.
- New names in `undefined_syms.eu.txt`: `__osContPifRam` 0x80042DA0,
  `__osContinitialized` 0x8002C160, `osClockRate` 0x8002C060, `__osEepromTimerQ/Msg`
  0x80042E08/0x80042E20, `osTvType` 0x80000300, `osViModePalLan1/MpalLan1/NtscLan1`
  0x8002C180/1D0/220, `osRomBase` 0x80000308. The `D_8002C220` spelling is taken by a US
  `f32` in `variables.h`, hence real names. A missing name only shows at link time (check_files
  masks relocations), so run `verify_all.sh --quick` after adding externs.
- **`m2c/narrow.py indir outdir`** (new variant set): a parameter that m2c masks as
  `(argN & 0xFF)` / `& 0xFFFF` gets type `u8`/`u16` and the masks are removed. This is the
  `(obj, msg, u8 event)` handler signature; IDO homes the arg and re-truncates it
  (`sw a2, 8(sp); andi t6, a2, 0xFF; move a2, t6`), which is the most common single
  pattern among the `SIZE-1` drafts. ~190 drafts change; 2 matched outright
  (`func_150FA9E8`, `func_15179154`); most of the rest are now off by register choice only
  (e.g. `func_15190C50`: DIFF3, a temp lands in `a0` instead of the dead `a2`). Many narrowed
  drafts fail with CERR because `functions.h` or the C file already prototypes the function
  with `s32` params; fixing those prototypes (check codegen of callers!) would unlock more.
  Workflow used: `gen2.py ~/conker/conker/build/k 1 150` (~6.5 min, 1889 functions), then
  `for v in 0..7: narrow.py build/k/v$v build/k/n$v`, `screen.py build/k/n$v 8` in the
  container (~1.5 min per full set), `merge.py build/k/final build/k/n*`, `apply.py`.
  `verify_all.sh` (full) wipes `conker/build/`, drafts included.
- SIZE±1 classification (instruction multiset of ref vs draft, script not kept): besides the
  u8 parameter case, recurring groups are `bnel`-loops of the form
  `while (!found && i < N) { if (x == tbl[i]) found = 1; else i++; }`
  (`func_15199954`, `func_151999BC`, `func_1519C428`, `func_1519C490`: control flow right,
  but the reference keeps `i/found/x` in `a1/a2/a3`; declaration-order permutations did not
  help), and extra `lw`/`addiu` pairs where the reference reloads a pointer through a
  struct (`func_150F1B78`, `func_151BE65C`, `func_151D7AE8`, `func_151007B0`).

Skipped libultra (still asm):
- `func_10027B50` (osLeoDiskInit, `init_eu_27990`): matches except instruction scheduling of
  the handle field stores (`pageSize`/`relDuration` share one `lui $at` in the ROM); all
  orders of the six field assignments tried; -O2/-g worse. Maybe its own object with
  different flags/source shape; left as asm at the end of the file.
- `osPfsChecker`, `corrupted_init`, `corrupted` (`init_eu_289A0`, ~730 instructions, old
  pfschecker.c) and its game/US twin `libultra/io/pfschecker2.c`: not attempted.
- `__sinf` (`init_eu_26870`) and `sinf` (`libultra/gu/sinf.c`): need their double constants,
  which live in the EU data blobs (no `.rodata` in C files yet).
- `init_eu_26B30` (`__osSetHWIntrRoutine`, `func_10026C00`, `func_10026E40`,
  `func_10027524`, `func_1002760C` next to the `__ll_*` helpers): not identified.
- `MusPtrBankGetCurrent` (0x10027938) is really the tail of `osPiGetCmdQueue`; its symbol is
  harmless and left in `symbol_addrs.eu.txt`.

## Session 7: u8 handler prototypes, first data-blob splits

Sequential, 4 work commits (`4b80d37`..`4086ef1`), +18 functions (2664 -> 2682), +2,456 bytes.

### u8/u16 parameters (`(obj, msg, u8 event)` handlers)

- `m2c/u8params.py` lists every asm function whose prologue re-truncates an argument register
  (`andi $tX, $aN, 0xFF|0xFFFF` then `or $aN, $tX, $zero`, before any other write to `$aN`):
  239 params in 218 functions. Output `func file argN u8|u16`.
- `m2c/fixprotos.py list [--apply]` retypes those params in every one-line prototype in
  `include/*.h` and `src_eu` (FIX/OK/ODD report). Only 20 prototypes needed changes (most
  handlers have none). After `--apply`, touch all C files and run `m2c/verify`: two callers
  changed codegen and were fixed (`game_A28B0` `func_150771F0`: `u8 var_a1`; `game_eu_CC5F0`:
  drop a now-redundant `& 0xFF`).
- `m2c/u8run.sh [build/u]`: the whole pipeline (list, fresh contexts, `gen2.py` with the new
  `ONLY=<list>` filter, `narrow.py` forced by the list, screen n0..n7, merge). Result: **0 OK**.
  The narrowed m2c drafts are mostly 3-30 words off; the u8 type alone was not the blocker.
  `m2c/protofix.py` (prototypes for called u8 functions) gave 1 more.
- So the 16 handlers came from hand work with the helpers below. Patterns that matched:
  - "object deleted" (event 0): `id = msg[0]; if (id == obj->ref || obj->b4 == msg->b4) func_1516972C(obj);`
    -- the `id` local is required (puts the value in `v0`).
  - "swap ids" (event 0x2D, msg = {s32 old, s32 new, u8 b8, u8 b9}):
    `if (msg[0] == *p) { *p = msg[1]; p[4] = msg->b9; return; } if (msg[1] == *p) { *p = msg[0]; p[4] = msg->b8; }`
    with `p` a pointer local set before the event test (no `cur` local; plain `else if` also works
    when no case follows).
  - Dispatch: `f = D_xxx[obj->b4D]; if (f != NULL) f(obj, msg, event);` with
    `extern void (*D_xxx[])(u8 *, u8 *, u8);` -- pass all three args through (m2c drops them).
  - Pass-through wrappers need the callee prototyped with its u8 params, else IDO re-truncates.
  - An intermediate pointer kept in `v0` (`lw v0, 0x98(a0); lw v1, 4(v0)`) needs its own local.
  - `sw a0, home; lw t7, home` (arg0 reloaded from its home slot): take its address,
    `p = (*(u8 **)&arg0) + 0x28` (`func_150D380C`).
  - Multiple `return X;` compile to `b end; li v1, X` + `move v0, v1` at -O2 -g3.
  - u16 params do not always show the `or`: `andi a3, a1, 0xFFFF` alone when `a1` is reused
    (`func_1508220C`: `u16` param + callee prototype `(u8 *, s32, u8)`).
- **Unsolved handler shape** (blocks most 2-case handlers, e.g. `func_151AEBF0`,
  `func_150FE08C`, `func_151590AC`, and the US note in `game_18D770.c` `func_15163FEC`): the
  last branch of an if-chain ends `sw/sb; jr ra; nop` (delay slot not filled) where IDO fills it
  for every source shape tried (if/else-if, switch with/without default, returns, goto, `-O2`,
  `-O2 -g`, `-O3`). Everything else in those functions matches.
- New helpers in `m2c/` (host side): `tryall func a.c b.c ...` (screens several drafts in
  parallel, one line each; `SCREEN_OPT="-O2"` overrides the file's -O/-g flags, also honoured by
  `screen.py`), `keep func draft.c` (collects a matched draft in `conker/build/hand/` for
  `apply.py build/hand`; move the dir away after applying), `asm func...` (compact listing).
  `screen.py` takes `SCREEN_TMP` so parallel runs don't collide.

### Data blobs: first real .rodata/.data pieces

- Mechanism: a C file gets its own section by splitting the containing blob in
  `conker/conker.eu.yaml`: `[a, rodatabin] -> [a, rodatabin], [x, .rodata, <stem>], [y, rodatabin]`.
  `tools/eu_port/rodata_split.py <stem> <rom start> <rom end> [--section .data]` does the edit.
  Then define the constants in the C file with the exact bytes (object sections are 16-byte
  aligned/padded), re-split (`rm -rf conker/asm conker/build`, `*_auto.txt`, `make extract`) and run
  the full `verify_all.sh` (only the full ROM check covers data bytes; `check_files` is .text only).
- **splat links all `.data`-type subsegments of a segment before all `.rodata` ones** (see the
  generated `conker/conker.ld`). A `.data` piece is therefore only possible where everything
  before it is data-typed: `game_data` now starts with `databin` pieces (linked as `.data`) up to
  a provisional boundary at rom 0x22D990, then `rodatabin` (superseded in session 8: the real
  boundary is 0x237060).
  `init_data` is still all rodatabin (fine while only .rodata pieces are carved there).
- Done: `__sinf` (`init_eu_26870.c`, now only `__sinf`, -O2 -g3; the SpRaw functions moved to the
  new `init_eu_26A30.c`, -O1) with .rodata 0x2CC30-0x2CC80 (P[5], rpi, pihi, pilo, zero as `du`/`fu`
  unions); `__libm_qnan_f = 0x8002CC80` in `undefined_syms.eu.txt`. Game `sinf` (float version,
  `libultra/gu/sinf.c`): .data 0x22B4D0 (`static fu rpi, pihi, pilo, zero`), .rodata 0x23E3C0
  (`static const fu P[]`). Both matched first try.
- `cosf` (game, same layout: .data 0x22B4C0, .rodata 0x23E3A0) is a C draft in a comment in
  `libultra/gu/cosf.c`: all but `dn`/`dx` register choice (f12/f2) matches. Needs
  `ABS(d) ((d) > 0 ? ...)` (int 0) with `ROUND` against `0.0f`, else the zero constant is CSE'd.

## Session 8: C files own their .rodata

Sequential, 3 work commits (`624bf92`..`3c2d62f`), +24 functions (2682 -> 2706), +5,144 bytes.

### The game_data layout

- **.data ends at rom 0x237048** (the last write from code is to 0x236FA0; 0x236FC0-0x237048
  is a pointer table into .bss), then 16 zero bytes, and **.rodata starts at 0x237060** with
  game_2D4B0's jump table (file 0, as expected: all .rodata of the segment is linked in file
  order after all .data). `conker.eu.yaml` now has `[0x22B4E0, databin]` up to 0x237060.
  Session 7's "provisional boundary" at 0x22D990 was based on `jtbl_8008891C`, which is
  spimdisasm's misreading of a data word (it is loaded with `lw`, never jumped through).
- `tools/eu_port/datarefs.py [game|init] [--runs] [--lo/--hi] [--file stem]`: scans the code of a
  segment for %hi/%lo pairs (register state carried into branch targets, `addu` chains for
  indexed loads) and prints who references which data address. Kinds: `lw`, `lwc1`, `ldc1`,
  `addiu`, ..., `jtbl` (indexed `lw` followed by `jr`), an `x` suffix for indexed access
  (an array). `--runs` shows the file index sequence; a drop marks the .data/.rodata switch.
  `owners()` assigns each .rodata address to one referencing file (longest non-decreasing
  chain of file indices), so shared const tables do not distort the per-file ranges.

### Workflow: a function that needs .rodata (float literals, switch, strings, const tables)

1. `python3 tools/eu_port/rodata_split.py --own <stem> --dry` prints the file's .rodata range
   (16-byte aligned, from the references) and warnings. It refuses (without `--force`) files
   whose rodata shows a second object (see below).
2. `python3 tools/eu_port/rodata_split.py --own <stem> --resplit` does it:
   - splits the blob in `conker/conker.eu.yaml`: `[a, .rodata, <stem>]`;
   - runs `rodata_literals.py <stem> --apply`: ported C that read the file's float constants
     through externs (`D_800A56A8` = `0x800A5A88` in `undefined_syms.eu.txt`) gets literals
     (`3.1415927f`); same codegen, but now the compiler emits them in place;
   - re-splits in `conkerdev` (wipes `conker/asm` and `conker/build`: keep drafts elsewhere).
     `make VERSION=eu extract` now runs `tools/eu_port/rodata_inject.py` after splat.
3. Write the function with literals/switch/strings. Screen it with `m2c/try` / `m2c/tryall`:
   `screen.py` now accepts relocations to the TU's own `.rodata` and compares what they point
   at with the ROM (literal value, jump table entries relative to the function, string bytes).
4. Insert with `m2c/apply.py` (it re-runs `rodata_inject.py` for owned files before building
   and checks owned sections) or by hand followed by
   `docker exec -w /conker/conker conkerdev python3 ../tools/eu_port/rodata_inject.py <stem>`
   (objects depend only on the .c, so delete the .o).
5. `verify_all.sh`. `check_files.py` now also compares each owned `.rodata`/`.data` with its
   ROM range (DATA lines); `tools/eu_port/rodiff.py src_eu/X.c [.rodata]` (container) prints the
   word diff. `conker.eu.bin: OK` covers the data segments too.

How `rodata_inject.py` works (one plan per owned file that still has GLOBAL_ASM pragmas):
items = addresses the file's code references; each belongs to the first function (file order)
that uses it; items from the first float/double/jump-table item on are the late region (IDO
emits literals and jump tables after all strings/const data of the object). GLOBAL_ASM
functions get their items prepended to their `.s` as raw `.word`s in `.section .rodata` /
`.section .late_rodata` (plus `glabel` for the symbols the asm uses, which splat leaves
undefined once the range is owned); asm-processor reserves the space at the right spot.
Items of C functions are left to the compiler, except ones the C names (externs) or nobody
references, which go to a neighbouring GLOBAL_ASM function. Strings/const data that are not
C-owned are placed as one block in any GLOBAL_ASM function between their C neighbours (file-
scope tables do not follow function order). `--dry` prints the plan; it fails (and so does
`make extract`) when a layout cannot be expressed, e.g. a late item named by C code with no
GLOBAL_ASM neighbour (write it as a literal) or a data block between two C functions with no
GLOBAL_ASM function in between (define it in C, e.g. `static const f32 v[3] = {...};`).

Owned so far: game_433F0, game_eu_64770, game_eu_6EDC0, game_981E0, game_eu_B7840,
game_eu_14F750, game_eu_14F980, game_16EE20, game_eu_170760, game_eu_1CC6F0, game_eu_1C1A20,
game_14FF90, game_eu_133A70, game_eu_1387B0, game_eu_AF2A0, game_eu_120060, game_eu_61AE0,
game_eu_49F20 (plus session 7's sinf/__sinf and the ported files).

### Files that are really several EU objects

One IDO object's .rodata is [strings/const data][literals/jump tables]; data after late items,
or zero padding up to a 16-byte boundary between late items, means a second object.
`tools/eu_port/rodata_bounds.py [stem...]` lists them for all game files: 28 BOUNDARY (certain),
25 PADDING (possible; can also be double alignment), and US hints (the US yaml's rodata
subsegment starts, mapped to EU, fall on such boundaries: game_77AD0 0x23E6F0, game_16EE20
0x24AAE0). Split done this session:
- `game_eu_14F750` | `game_eu_14F980` (func_15122170..; rodata 0x248A70 | 0x248A80).
- `game_16EE20` | `game_eu_170760` (from func_151429E0 at 0x15142F50). The second object's
  .data starts at 0x22F780 (zero padding before it) and its .rodata at 0x24AAE0; the text
  boundary is the 16-byte aligned function between the last user of the first .rodata and the
  first user of the second's .data/.rodata. Move the functions into `src_eu/game_eu_<rom>.c`
  (fix the pragma paths), add the c subsegment, `--own` both.
Byte-wise, owning a multi-object file still matches while the affected items stay in
GLOBAL_ASM functions, but C functions whose items are on the wrong side will not.

### m2c with rodata

- `m2c/rodasm.py <func.s>`: the function's .rodata items as labelled asm (`.word`, jump tables
  as `.word .L...`, strings as `.asciz`); `gen2.py` passes it to m2c as a second input (and adds
  labels for jump-table targets inside delay slots), so drafts get literals, `switch` and
  strings. `JT=1` includes jump-table functions; cache in `m2c/rod/` (gitignored).
- All 1114 asm game functions up to 400 instructions that use .rodata were run through
  v0..v7, narrowed (n0..n7), `compound.py` and the new `switchinline.py` (`temp = x; switch
  (temp)` -> `switch (x)`, which keeps the switch value in its own register): 11 + 3 OK. The
  rest came from hand work on the lowest DIFFs (list: `screen.txt` of all sets, best per
  function).
- Patterns that fixed near misses: write the switch on the expression; `+=`/`-=`/`&=`/`|=`
  instead of m2c's `x = (f32)(x + y)` and temps (`func_1510B34C`, `func_15082DD8`); plain
  `f32 *` indexing (`func_15108060`); an explicit empty `case 0:` when the table starts at 0
  (`func_1501C710`); missing stack args (`func_151441A4`); local arrays of the right size
  (`s32 sp2C[9]`, frame size tells); `const` local aggregates are initialised from .rodata
  (non-const ones from .data); IDO does not merge equal float literals in a function.
- Drafts that declare a prototype already declared differently in the file fail when a second
  draft lands in the same file; use one prototype at the top (`game_eu_1C1A20`).

Near misses left (rodata functions): `func_15007168` (DIFF2: only the order of the two `lui`s of
the first loop; tried do/while/for, end pointer locals, operand order), `func_151E2B9C` (a0/v1
swapped), `func_15146EE0` (const struct copy matches; return value lands in v1, not v0),
`func_151D5FC8` (delay slot filled from the branch target), `func_150EB610`/`func_151472D0`
(twins; every argument homed and reloaded from the stack), `func_1511CAD0` (store/reload order
at the end), `func_151D343C`/`func_1518F9CC`/`func_151343AC` (copy of a const local array:
`const s32 a[1] = {..}` gets the data right, the call setup order differs).

## Session 9: file splits in one command, hand-written rodata functions

Sequential, 3 work commits (`9fddd60`..`dcf890a`), +29 functions (2706 -> 2735), +4,264 bytes.

### `tools/eu_port/file_split.py <stem> [--at FUNC] [--rodata ROM] [--dry] [--no-own] [--resplit]`

Splits a C file at an EU object boundary: finds the .rodata boundary (16-byte aligned end of the
late item before the first data item that follows late items; an indexed byte table accessed with a
negative offset, e.g. `lbux` at 0x245E5F, is mapped to the next 16-byte boundary), the text split
(a 16-byte aligned function such that all functions before it reference only .rodata below the
boundary and all after only above; ties broken by .data reference order, US file starts and nop
padding; candidates are printed), moves the functions (pragmas, C, a comment block directly above)
into `src_eu/game_eu_<rom>.c` with the original preamble, adds the c subsegment and runs
`rodata_split.py --own` on both halves (an owned file is un-owned first). `--rodata ROM` forces the
boundary. Needs `conker/build/conker.eu.map` (addresses only, so several splits in a row are fine
before one re-split). Then `verify_all.sh`.

Split this session (all byte-matching, all halves own .rodata): game_2DF70 | game_eu_2F180,
game_36680 | game_eu_38360, game_eu_48B10 | game_eu_48E50, game_77AD0 | game_eu_78230,
game_eu_C24E0 | game_eu_C2B60, game_eu_DE3A0 | game_eu_DE750, game_eu_E48B0 | game_eu_E5830,
game_eu_E9450 | game_eu_EB430, game_eu_EBBA0 | game_eu_EBF20, game_eu_FBE70 | game_eu_FC460
(own range set by hand: 0x245E60-0x245E80), game_eu_FCE60 | game_eu_FDEC0, game_eu_111F50 |
game_eu_1122E0, game_eu_11CB90 | game_eu_11F790, game_eu_125200 | game_eu_126330, game_eu_12CAC0 |
game_eu_12D5D0, game_eu_17D3C0 | game_eu_182A10, game_eu_183F10 | game_eu_185050, game_eu_185E30 |
game_eu_186A80, game_eu_1BAAA0 | game_eu_1BAF40 | game_eu_1BE5C0, game_eu_1D1150 | game_eu_1D2F30,
game_eu_1D9C00 | game_eu_1DC470 | game_eu_1DD290 (`--rodata 0x24E900`: found because a C
function's late chunk in `rodata_inject.py --dry` ran over an unreferenced data block),
game_eu_1E7CC0 | game_eu_1EC610, game_eu_1F4F60 | game_eu_1F7960, game_eu_1FB080 | game_eu_200070.
Also owned (no split needed): game_1FFF60, game_eu_1365E0, game_eu_18DB20, game_eu_15E000,
game_16DC80, game_eu_114640.

Not split (rodata_bounds.py BOUNDARY, judged false positives or unresolved):
- game_eu_1371A0: the "late" item 0x247B6C is one `lwc1` into a const float table in the data region.
- game_eu_15FF50, game_18D770: `lwc1` (non-indexed) reads of const float tables/structs look like
  literals; the item order contradicts a split.
- game_eu_17A800: byte tables at 0x24B520 after its jump tables are read by early functions of the
  file; maybe an object between it and game_eu_17D3C0 (unreferenced bytes 0x24B540-0x24B640).
- game_eu_1DC470 still shows zero padding 0x24F3D4-0x24F3E0 (maybe one more boundary).
- Known limitation of rodata_bounds/rodata_split: `lw` of a .rodata word counts as data, but it can
  be a const local array copy (`sp1C = D_800A83F0`), which is data, or a float stored via an
  integer register.

### Matching findings

- **Const local arrays passed to `func_15169260`** (5 matched, pattern of ~10 handlers):
  `const s32 sp1C[1] = {0x5A}; func_15169260(sp1C, 1, arg0, arg1);` with `(s32 arg0, u8 arg1)`.
  The `(s32)` cast that m2c and the old prototype needed makes IDO compute the address into `v0`
  first; with a `void *` parameter (now in `functions.h`, also `func_15155C9C(void *, u8)`) and no
  cast it matches. Same idea likely helps any `(s32) &local` argument. Copies from `.data`
  (`func_1510965C`, `func_151417C4`, `func_1510957C`: non-const arrays) need .data ownership.
- **Effect spawners** (~40 left, list: `grep -rlE "jal +func_1514(9130|91F4)" conker/asm/nonmatchings
  | xargs grep -l "jal  *memcpy"`): `tools/eu_port/m2c/spawn.py` writes them from a spec, e.g.
  `spawn.py func_1514F93C A "u8 *arg0" "u8 *unk0=arg0;u8 unk4=arg0[0x3B];f32 unk8=0.0f"
  "300, -1, 0x3A, -1, 0, 0x2B, 0xC, 255, 1" 0xC`. Read the struct fields from the stores between
  the memcpy source (`addiu a1, sp, X`) and X + size, the args from a0..a3 and the stack slots
  from 0x10. Declare `temp_v0` after the struct (A) or before it with the early-return guard (B,
  `VFIRST=1 ... g`); try both. u8/s8/s16 params show up as `lbu/lb/lh` from the arg home.
- Hand-written C beats m2c drafts for float code: `f32 *v = (f32 *)(arg0 + 0x70); v[1] += ...`
  (`func_150D0170`), plain `*(f32 *)(arg0 + 0x44) *= k` offsets (`func_150BD498`), `+=` lerps
  without temps (`func_15052260`), one product temp (`func_151CC190`), `u8` locals for masks
  (`func_151423D8`), `% 5U` when the asm has `divu` (`func_1515302C`).
- `rodata_literals.py` turned `game_eu_1E7CC0` `func_151BDD00`'s externs into literals and that
  changed its codegen; it keeps the externs now. Check `check_files` after every `--own`.

Near misses left (session 9): `func_151AFA80` (DIFF1: `addu a2, v1, t2` operand order; tried
base/offset orders, Mtx array, int base), `func_15034710` (DIFF6, temp register numbering),
`func_15034790` (register numbering), `func_1519E6BC` (SIZE-1: `&D_800E0D50` kept in `t0`),
`func_151CC190` (matches in screening but `apply.py` rejects it: the file's rodata plan gives its
late chunk an extra word D_800AB29C; needs a `rodata_inject.py` look), `func_1518F9CC` (matches,
rejected: its const array sits between strings and a table in one data block of game_eu_1BAF40),
`func_151A5BCC`-style arrays in unowned game_eu_15FF50 (`func_151343AC`).

## Session 10: spawners from the asm, C files own .data

Sequential, 3 work commits (`18c0449`..`ba052c8`), +22 functions (2735 -> 2757), +3,592 bytes.

### `tools/eu_port/m2c/spawngen.py <outdir> [func ...]` (effect spawners in bulk)

A small symbolic interpreter of the asm of every remaining `func_15149130`/`func_151491F4` +
`memcpy` function (only other calls allowed: the random helpers `func_150ADA20`/`func_150ADA68`).
It recovers the struct (stores into the memcpy source range; `lw/sw` word runs through an `sp+X`
register become a block copy `typedef struct { s32 w[N]; } BlkN;`), the call args (a0-a3, stack
slots 0x10..), param types (lbu/lb/lh/lhu/lw/lwc1 of arg homes, `sll/sra`, `andi`, loads through an
arg -> `u8 *`, `mtc1 aN` -> f32), the `if (arg0 == NULL) return [NULL];` guard, `return temp_v0;`,
`% NU` for `divu`, float literals (owned files) or externs. 12 variants per function (temp_v0
declared before/after the struct, struct vs asm store order, 0/4/8 bytes of tail padding).
Workflow: `spawngen.py ~/conker/conker/build/sg`, then `m2c/screenall build/sg` (screens every
`v*/`, merges the first OK into `final/`, prints the best result per function), then
`apply.py build/sg/final` in the container. First run: 9 of 14 drafted functions OK.
Helpers: `m2c/permassign.py draft.c outdir [fixed] [max]` (every order of the `tmp.X = ...`
assignment block, for `tryall`), `tryall` now runs at most 8 screens at once (720 parallel
screens got OOM-killed).

Hand-written spawners and what mattered: store order follows the source (`func_150D2620`:
`D_800D9D20++` first, then the asm store order), `+` operand order of floats (`func_151D0058`),
`if (arg0 != NULL) { ... }` instead of an early return (`func_151B2610`), aligned array fields
(`f32 unk10[3]`, not `u8[0xC]`), two `if (temp_v0 != NULL)` blocks (`func_150FAFC0`), call-time
ternaries `(arg1 == -1) ? 300 : arg1` / `? 0 : 1` with temp_v0 declared first (`func_150B58B0`),
a function-pointer table call writing into a struct field (`func_151D1510`).
Left: `func_1510A454`, `func_15109990`, `func_150E892C`, `func_150ECFE8` (the same ternaries, but
the struct stores come after the branches: SIZE+1 or DIFF30+ for every shape tried),
`func_151D469C` (DIFF2: `sh -1` / `sb 0` store order; all 720 assignment orders tried),
`func_15182BE0` (struct 4 bytes lower and `arg4` reloaded for the `div`), `func_1515AFF4`
(struct copy loop), `func_151C4BF4`, `func_150E6E30`, and ~45 spawners that call other functions
first (list: `spawngen.py` prints `SKIP ... calls ...`).

### C files own .data

- `rodata_inject.py` now also plans owned `[addr, .data, stem]` ranges (one region, no late items):
  local array initialisers of C functions and data the C file defines at file scope (a
  `name[] = ...` line) are the compiler's, everything else goes as raw words in `.section .data`
  into a GLOBAL_ASM function between its C neighbours; data symbols the C code names get a glabel.
  All sections of a file are emitted in one `# rodata_inject` block per function.
- Done: `game_eu_1365E0` (0x22E270-0x22E280, `func_1510957C`, `func_1510965C`),
  `game_16DC80` (0x22F5B0-0x22F6A0; its function-pointer tables stay in GLOBAL_ASM functions;
  `func_151417C4`), `game_36680` (0x2281F0-0x228390; `D_80082BFC`/`D_80082D60` are now C tables
  at the end of the file, written with `tools/eu_port/ptrtable.py <rom a> <rom b>`; the two
  `= D_80082BE0`-style initialisers became literal `{...}`).
- Steps: find the file's .data range with `datarefs.py game --lo/--hi` (references are in file
  order; take 16-byte boundaries), write the C, `rodata_split.py <stem> <a> <b> --section .data`,
  `verify_all.sh` (full). `rodata_inject.py <stem> --dry` shows the plan (`data` lines).
- Non-const local arrays: `s32 sp1C[2] = {0x38, 0x54};`; a `u8` local passed by address needs
  `u8 sp24[4]` (4-byte slot); declare the struct before the array to get the array lower.
- Screening (`screen.py`) does not accept .data relocations; `tools/eu_port/fdiff.py src_eu/X.c
  func` (container, from `conker/`) rebuilds the object and prints a word diff with disassembly
  against the ROM, for functions without a `.s`.
- Near misses in `game_36680` (drafts in comments): `func_1500A6D8`, `func_1500A7E8`: everything
  matches except the local array at sp+0x28 instead of sp+0x24 (tried pads of every size, array /
  struct / flat shapes, declaration orders).

### rodata_inject layout fixes

- A float/double literal item now ends after 4/8 bytes; an unreferenced word after it becomes its
  own item and goes to a GLOBAL_ASM neighbour (`func_151CC190` in game_eu_1F7960: unused
  `D_800AB29C` after its literal). `func_151CC190` needed `Sub151CC190 *v = arg0 + 0x70` set before
  the call and the exact literal `6.283186f` (0x40C90FDC, not 2pi).
- Compiler-owned items whose end is not the next reference take a hint in the C file:
  `// rodata_inject: size 0x24CB34 4` (`func_1518F9CC`, const array followed by an unreferenced
  table in game_eu_1BAF40; a stale `extern struct_eu_bytes4b D_800A78B4;` had made the whole block
  "named by C" and was removed).

## Session 11: spawngen with calls, hand-written spawners and float functions

Sequential, 3 work commits (`c6ae2b4`..`fce108a`), +15 functions (2757 -> 2772; one of them is an
EU stub `func_eu_1507340C` split off a merged `.s`), +4,596 bytes.

### `spawngen.py` extensions

- Calls before the spawner: arity and return type from `functions.h` / the C file, or inferred (int
  args = a-registers written since the last call, result type from whether `$v0` or `$f0` is read;
  an inferred function gets a block-scope `rt f();` declaration). A call result used once is
  inlined, otherwise it gets a local; reloads of struct slots become `tmp.unkX`; stores through
  argument pointers (`arg0[0x16] |= 4`) become statements; saved registers survive calls; ALU ops on
  non-constants, `&global` and derefs of global expressions are modelled.
- New variants: `s32` return type without a `return` (see below) and `if (arg0 != NULL) { ... }`.
- Result: still only 2 more functions. The ~45 remaining spawners almost all have branches or
  loops (`bgez/bne/beql`, `slti`), several spawns, or `sinf`/`cosf`; the interpreter is straight-line
  only. Hand-writing them works (most of this session's matches); extending spawngen to branches
  is probably not worth it.

### Patterns that matched (hand work)

- **`s32` function with no `return`**: the spawner result is copied `or v1, v0` in the `beqz` delay
  slot although nothing is returned (`func_15014094`; void gives DIFF9).
- **`base + range * rand`**: random ranges are `s[2] + s[4] * func_150ADA68()`; m2c's
  `func() * s[4] + s[2]` swaps float registers (`func_151BE7C0`, DIFF4 -> OK).
- Float operand order generally: try both orders of every `+`/`*` (`func_151320EC`:
  `x * k + y` instead of `y + x * k`, and `-a * b` for the negated product).
- **Merged switch cases** `case 0xF: case 0x11:` (one constant register shared, `beql` with the
  store in the delay slot), `func_151A0A10`.
- **Stack layout**: declaration order decides the slots (first declared = highest); put
  `temp_v0` (or another 4-byte local) before/after the struct to move it by 4; unused pads go to the
  bottom and grow the frame, so they rarely help. Reusing one pointer variable for two unrelated
  values (table entry, then the spawner result: `func_150139AC`; `arg0` itself: `func_150144B8`
  near miss) removes a slot. A value used twice without a named local (`arg1 + 4` written out
  twice) is spilled where a named local would not be (`func_1514FBB0`).
- **Caller passes more args than the callee takes**: `func_151CFE48` homes only a1/a2; its
  4-argument prototype moved from `functions.h` into the caller's file (`game_eu_DCEF0.c`), the
  definition has 3 params.
- `memcpy` prototype declared after its first use in a file breaks drafts (`redeclaration of
  memcpy`): move the file's `s32 memcpy(...)` line to the top (`game_eu_114640.c`).
- A merged `jr ra; nop` stub at the end of a `.s` (screen reports SIZE-1 with only the stub's words
  different): add `void func_eu_<addr>(void) {}` after the function (`func_15072F10`).
- `u32` bitfield reads (`(x & 0xFFFF)` with `bgez`/`0x4F800000` fix-up) need `(u32)` casts on the
  `s32` field before shifting/masking (`func_150142EC`).

### Near misses left (session 11; drafts were in the session scratch dir, not kept)

- `func_150E909C` / twin `func_150E96F8` (game_eu_114640): DIFF10, only the saved-register order of
  the three hoisted loop invariants (`&D_800DCD90`, `&D_800DCDC4`, 13). Shape: `f32 *pos =
  func_15144B34(D_800BEE08); f32 *v = arg0 + 0x28; v[2] += ...; while (v[2] > 1.0f) { r = rand *
  D_800DCD90; walk list D_800DCDC4; func_1514470C(node->unk0, &tmp); if (dist2 < 3240000.0f) spawn
  ((rand % 13U) + 5, ...); v[2] -= 1.0f; }`, `pos`/`v` declared before the struct, `u8 pad18[8]`.
- `func_150CE710` (game_eu_FBE70): DIFF12, only the scheduling of the `291.0f` load; the const
  `{0.0f, -49.0f, -2.0f, 30000.0f}` is a `static const f32[4]` passed to `func_15143134`.
- `func_15109034`, `func_151091B8` (game_eu_1365E0): DIFF1, `addu s0, a0, t6` operand order of
  `arg0 + *(s32 *)(arg0 + 0x50)`; every spelling tried gives `t6, a0`.
- `func_151D2E5C` (game_1FFF60, u8 handler): DIFF1, `bnel t9, v1` operand order in the swap case.
- `func_15074A94` (game_981E0): DIFF16, float register numbering only (all expression shapes give
  the same result).
- `func_150144B8` (game_40490): DIFF6, needs a 4-byte gap between `tmp` and the matrix.
- `func_15013778` (game_40490): DIFF17 with `func_1000FA64`'s `arg5`/`arg6` as `s32` in
  `functions.h` (the call passes `unk8 * 2` / `unk8 / 2` unmasked; the change keeps all other
  callers matching but was not committed); left: `mtc1 $zero, $f12` scheduled early.
- `func_151CC784`: then-branch recomputes `arg0 + 0x70` and reads through it; every shape gives
  direct `arg0 + 0xC4` offsets.
- `func_1510A454` (ternary spawner): still SIZE+1/-3; args are read from their home slots (`lb
  0x53(sp)`) in the reference.
- `func_151BCD44`: trail-point loop, frame 0xA0 with f20-f28 saved; m2c far off, not attempted in
  depth.

## Session 12: decomp-permuter

Sequential, 3 work commits (`4df1653`..`364d883`), +8 functions (2772 -> 2780), +1,444 bytes, all
found by the permuter or by a hint it printed.

### Setup (`tools/eu_port/permute.sh`, `tools/eu_port/permute/setup.py`)

- decomp-permuter is cloned to `tools/decomp-permuter` (gitignored; `git clone
  https://github.com/simonlindholm/decomp-permuter tools/decomp-permuter` if missing). Nothing to
  install: the container's Python 3.12 already has `toml` and `Levenshtein`, and the permuter ships
  its own pycparser (`perm_pycparser`). It runs inside `conkerdev`.
- `permute.sh <func> [draft.c] [secs=600] [jobs=8]` or `permute.sh -l <list> [secs] [jobs]` (list
  lines `func draft.c`; default draft `$DRAFTS/<func>.c`). Per function it recreates
  `tools/decomp-permuter/nm/<func>/` with `setup.py` (base.c = the C file with all GLOBAL_ASM pragmas
  removed and the draft in place, through `cpp`; target.o = the `.s` (with its `rodata_inject`
  words) assembled with `macro.inc`; compile.sh = the file's own IDO `cc` line from `make -n`, so
  per-file OPT_FLAGS apply), runs `permuter.py -j<jobs> --stop-on-zero --better-only --stack-diffs`
  under `timeout`, extracts the best output's function to `best.c` (the draft's own declarations
  kept above it) and screens it with `m2c/try`. A screened OK also goes to `match.c`. Output, one line
  per function: `func base=<score> best=<score> try=<OK|DIFFn|SIZE±n> <file>`. Log: `nm/<func>/log.txt`.
- `setup.py extract <func> <source.c> [draft.c]` adds `// PERMUTER CHANGED DECL: new (base: old)` lines
  when the permuter changed a declaration outside the function (it has a pass that changes callee
  return/param types). `try` does not see those changes: apply them by hand (header edit) and re-check
  every file (`verify_all.sh` runs `check_files.py` on all).
- `m2c/try` takes `TRYDIR=<name>` (work dir `conker/build/<name>`), so several tries can run at once.
- Throughput: ~16 iterations/s with `-j8` on a small function; 3 parallel streams of `-j3` on the
  10-CPU Docker VM worked fine.

Pitfalls found while setting it up (all handled by the scripts):
- **`--stack-diffs` is required.** Without it the permuter's scorer ignores stack offsets: an m2c
  draft that is DIFF18 in `try` (`func_151C2600`, frame size off) scores 0.
- **Do not strip function bodies before the target.** IDO -O2 uses the register usage of callees it
  has already compiled in the same file; with earlier bodies reduced to prototypes, codegen changed
  (score 0 in the permuter, DIFF4 in `try`). `setup.py` strips only bodies after the target
  (`PERM_NOSTRIP=1` keeps everything).
- Permuter score 0 ignores relocation symbol names, so `try` stays the authority.

### Results on the session 8-11 near-miss list

Starting drafts: the best m2c variant per function (`JT=1 ONLY=<list> gen2.py`, `screenall`), not the
hand drafts of earlier sessions (those were lost); continuation runs started from the previous
`best.c`. Runs of 300-400 s, then 900 s for the closest ones.

Solved:
- `func_1517A220` (game_eu_1A6C30): DIFF1 -> OK (sqrt result in its own local).
- `func_1514EA78`, `func_1514EB28`, `func_1514EBD8`, `func_1514EC88` (game_eu_17A800, the `v1`/`v2`
  near misses): the permuter changed the callee `func_1514F18C` from `void` to `int`. Now `s32` in
  `functions.h`; the m2c drafts then match as they are. The strings are the `variables.h` externs
  `D_800A5CB0..CEC` (the file does not own its .rodata).
- `func_151A547C` (game_eu_1D1150, "flag spilled as a byte across a call"): `sp1B = 1;` both before and
  after the call.
- `func_151A53E4` (game_eu_1D1150, operand order): the `u8` index read into a `u32` local first.
- `func_15109034` (game_eu_1365E0, `addu s0, a0, t6` order): `p = arg0; p += *(s32 *)q;` with `q = arg0 +
  0x50` a pointer local, plus a reused pointer local for the sinf part.

Not solved (best permuter result, `try` of that result):
- Close (worth a longer run or a hand look at `nm/<func>/best.c`): `func_1509CEA8` DIFF1 (stuck at
  score 5 for 15 min), `func_151C2600` DIFF2, `func_15074A94` DIFF3, `func_15034710` DIFF8,
  `func_15034790` DIFF9, `func_151D5FC8` DIFF10, `func_151CBAC0` DIFF11, `func_151AFA80` DIFF13.
  `func_151091B8` (twin of `func_15109034`, SIZE+1): try the same `+=` shape by hand.
- No improvement at all (score 10/60 from the start, 15 min): `func_150351A4`, `func_150C60D4` (float
  operand order), `func_1511CAD0`, `func_150A7CB0` (instruction order).
- Far (m2c drafts too far off, score hundreds-thousands): `func_15007168`, `func_151E2B9C`,
  `func_15146EE0`, `func_150EB610` (permuter suggests `func_150EB4D0`'s last param `int` instead of
  `u8`), `func_151472D0`, `func_151343AC`, `func_1519E6BC`, `func_151596F4`, `func_151597A0`,
  `func_151AEBF0`, `func_151D2E5C`, `func_151CC784`, `func_1510A454`, `func_15109990`, `func_150CE710`,
  `func_15182BE0`, `func_151C4BF4`, `func_151BCD44`, `func_1500A6D8`, `func_1500A7E8`. These need a
  hand-written draft close to the HANDOFF notes first; the permuter only finishes the last few words.
- Not run (no compilable m2c draft; the session-11 hand drafts are gone): `func_150E909C`,
  `func_150E96F8`, `func_150144B8`, `func_15013778`, `func_150E6E30`, `func_151D469C`, `func_150D03A8`.

Useful settings: `-j3`..`-j8`; 300 s is enough to see whether a function moves; DIFF1-4 drafts that
do not improve in 15 min rarely do. Restart from `best.c` (strip the `PERMUTER CHANGED` lines) to
continue a run. Read `nm/<func>/best.c` for hints (callee types, extra locals) even when it is not 0.

## Session 13: scripted near-miss sweep

Sequential, 3 work commits (`2b846db`..`3a88cab`), +19 functions (2780 -> 2799), +2,524 bytes.

### `tools/eu_port/sweep.sh` (rerun it as is)

```sh
tools/eu_port/sweep.sh gen 200          # ~22 min: list.py, JT=1 gen2.py 1..200 (fresh ctx/), narrow.py,
                                        # screen v0..v7 + n0..n7, best variant per function
tools/eu_port/sweep.sh perm tools/decomp-permuter/sweep/cand.txt 300 3 3   # run_in_background
tools/eu_port/sweep.sh apply            # apply.py on every nm/<f>/match.c still GLOBAL_ASM + needsyms.py
tools/eu_port/verify_all.sh --quick     # then commit
```

- Work dir `tools/decomp-permuter/sweep/` (gitignored, survives `verify_all.sh`): `best.txt` (best
  screen result per function and its variant dir), `cand.txt` (SIZE±1 and DIFF1-5, closest first;
  drafts copied to `drafts/`), `ok/` (drafts that screened OK as generated), `perm_<list>.txt`
  (permute.sh summary lines, one per function; `perm_<list>_<i>.txt` per stream while it runs).
- `perm` splits the list round-robin into N streams of `permute.sh -l` (3 x `-j3` on the 10-CPU VM).
  The streams use `conker/build/perm_<f>` for `try`: do not run the full `verify_all.sh` (it wipes
  `conker/build` and `conker/asm`) while a sweep runs; `--quick` and `apply` are fine.
- Second pass used here: functions whose permuter score improved (`best < base`, not OK), ranked by
  best score, restarted from their `best.c` minus the `// PERMUTER CHANGED` lines (`drafts2/`,
  `cand2.txt`), 750 s each.
- `tools/eu_port/needsyms.py [--apply] func...` (new, called by `sweep.sh apply`): a function that
  leaves GLOBAL_ASM can take the last reference to a splat auto symbol (`D_8009F970 = 0x8009F970;`
  in `undefined_syms_auto.txt`) with it; the next clean split drops it and the link fails if the C
  names it. It appends those symbols to `undefined_syms.eu.txt`. (`--quick` does not catch this,
  only the full `verify_all.sh` does.)

### Statistics

- `gen`: 2050 functions drafted (<= 200 instructions), 2 OK as generated (`func_150CFA40` applied;
  `func_151EF7B0` rejected again, the 0x40-byte padding issue), **278 candidates**: DIFF1 2, DIFF2 2,
  DIFF3 3, DIFF5 7, SIZE-1 156, SIZE+1 108 (nothing at DIFF4).
- Pass 1 (300 s, 3 x `-j3`, ~6 h): **16 OK** by bucket: DIFF2 1/2, DIFF5 3/7, SIZE-1 8/156,
  SIZE+1 4/108 (DIFF1 0/2, DIFF3 0/3). 254 improved without reaching 0 (best score <= 50: 19,
  <= 150: 14 more, <= 300: 42 more, the rest > 300), 8 never produced a better output.
- Pass 2 (top 54 improved, 750 s, ~3.8 h): **2 OK** (`func_1519CE80`, `func_15080830`).
- Matched: `func_150F13C8`, `func_150F6980`, `func_15121E34`, `func_15173948` (the `return arg0`
  one from session 4's list), `func_1518FDC8`, `func_151AF8E8`, `func_15080600`, `func_150A11F4`,
  `func_150721A4`, `func_1507266C`, `func_1517FD24`, `func_1518B0D0`, `func_151B5654`,
  `func_151E5AB8`, `func_15033618`, `func_15085ABC`, `func_1519CE80`, `func_15080830`, plus
  `func_150CFA40` (m2c).
- `func_150A11F4` (game_eu_CE6C0, no own .rodata): the permuter/screen accept float literals, but
  `apply.py` rejects them in a file that does not own its .rodata; the two literals became the
  externs `D_8009F970`/`D_8009F974` the asm names (each `lwc1` has its own symbol). Same fix for any
  future literal match in an un-owned file.
- Yield: SIZE±1 drafts are mostly real structural differences; 300 s solves ~5%. The permuter's
  score-0 outputs that `try` still rejects (`func_1505E7CC` DIFF1: a branch offset;
  `func_151B7C28` DIFF1; `func_15129E30` SIZE+2) and the closest non-zero ones (`func_151AC3B0`
  score 1, DIFF1: a `u8` stack local at sp+0x1C instead of 0x1D; `func_1509CEA8`, `func_1515C668`,
  `func_1517D534` score 5, DIFF1) are the best hand targets: `tools/decomp-permuter/nm/<f>/best.c`.

### `PERMUTER CHANGED DECL` review

None of the suggested prototype changes came with a score-0 result, so none were applied:
`func_1000FA64` arg0 `u16 -> int` (from `func_150A28C4`, score 745 -> 160, SIZE-1; session 11 also
suspected this prototype's `arg5`/`arg6`), `func_150026C4` `void -> u16` return (`func_15003668`),
`func_15127EB8` `void -> int`, `func_1514F250` arg1 `s32 -> char`, `func_150EB4D0` last param
`u8 -> int` (again), `func_1000853C`/`func_100111C8`/`func_1513F680` (`volatile` noise). The 21
`guBlinkRdpDL` lines are a whitespace artefact. Worth one test each: edit `functions.h`, re-run the
affected function's permuter from `best.c`, and `verify_all.sh --quick` (check_files on all files).

## Session 14: native toolchain, sweep passes 3 and 4

Sequential (restarted once for the toolchain switch), 3 work commits: `2f1f805` (7 functions the
stopped first run had matched: the six HANDOFF hand targets `func_1505E7CC`, `func_151B7C28`,
`func_15129E30`, `func_151AC3B0`, `func_1515C668`, `func_1517D534`, plus `func_1509CEA8`), `09f578e`
(7 from pass 3), `c896fcf` (6 hand-finished + 1 from pass 4). +21 functions (2799 -> 2820), +2,936 bytes.
Session cut short by the user during pass 4.

### Sweep statistics (native `conker-arm` toolchain, 3 streams x `-j3`, 100 s per function)

- **Pass 3** (`sweep/cand3.txt`: the improved-but-unsolved functions of ranks 9-96 of `improved.txt`, best
  score <= 415, restarted from their `best.c` = `drafts3/`): **79 functions in 44:41 wall** (2681 s; the
  old x86 toolchain needed ~6 h for 278 functions at 300 s, i.e. ~78 s wall per function vs ~34 s now).
  **7 OK** (`func_1518FE0C`, `func_1507EA98`, `func_150A28C4`, `func_150A2C6C`, `func_150BE710`,
  `func_150C6440`, `func_150C6D70`), 64 improved on their pass-2 best, 14 never produced a better output.
- **Pass 4** (`sweep/cand4.txt`: the 158 remaining improved functions, best score > 415, from
  `drafts4/`): stopped by the user after **90 of 158 functions in 51:43 wall** (3103 s). **2 OK**:
  `func_150A2E20` applied; `func_150E0B78` REJECTed by `apply.py` (not investigated; probably a float
  literal in a file that does not own its .rodata, see `func_150A11F4` in session 13). The 68 functions
  on lines 91-158 of `cand4.txt` were not run: restart with
  `tail -n +91 sweep/cand4.txt > sweep/cand4b.txt; sweep.sh perm sweep/cand4b.txt 100 3 3`.

### `func_1000FA64` prototype test

`arg0 u16 -> s32` in `functions.h` breaks `init_EB00` (92 words differ, the C callers
`func_10010558`/`func_10010720`); reverted. `func_150A28C4` matched anyway in pass 3 with the old
prototype.

### Hand-finished from permuter `best.c` (pass-3 leftovers)

- `func_150D2050`: permuter score 0 but `try` SIZE+1; its `PERMUTER CHANGED DECL` was the key:
  `func_1515D4D4` re-truncates only arg3, so its prototype is now `(s32, s32, s32, u8)` in
  `functions.h` (all files still match). `(arg0 ^ 0) + 0x28` is needed (forces arg0 through its home
  slot); the 0.2489f literal is the extern `D_800A0CB0` (file does not own .rodata).
- `func_150F2A00`: `u8 *q = arg0 + 0x50; u8 *p = arg0; p += *(s32 *)q; p += 0xF8;` (session 12 trick
  for `addu s0, a0, t6` order) and plain `*(f32 *)(p + X)` accesses.
- `func_1513A594`: an empty `if (*(s32 *)(arg0 + 0x1D4) != 0) { if (arg0) {} }` after the call (keeps the
  reload of arg0 into `v0`).
- `func_15016588`: `lw s2, 0x44(sp)` of an uninitialised local; `bit` and `sp40` declared **inside the
  loop body** put them at sp+0x44/0x40 (function scope gives 0x48/0x4C, pads grow the frame).
- `func_151182BC`, `func_150CF5B0`: the flag update `f = p[0x73]` (s32 local) `p[0x73] = f & 0xFFFC;
  p[0x73] |= 2;` or `p[0x73] &= 0xFFFC; p[0x73] |= 2;`. 19 larger asm functions (56-650 instructions,
  mostly `game_eu_142E40`) contain the same `andi 0xFFFC / ori 2 / sb 0x73` sequence.
- Not solved: `func_151D51E8` (u8 handler; SIZE-1, the unfilled-delay-slot shape of session 7),
  `func_1510BA9C` (0x180-stride table: the reference computes `base + off` and `off + base` separately;
  every non-CSE spelling tried is DIFF11+; permuter best DIFF8 uses `(off ^ 0)`), `func_1514EDF0`
  (SIZE+1, permuter suggests `func_1514F2AC` returning `volatile u8`), `func_15183EE4` (DIFF15),
  and the other DIFF leftovers in `sweep/perm_cand3.txt`.

## Session 15: prototype checker and stack-slot helper

Sequential. Work commits `63f199e` (protocheck + prototype fixes + 2 functions), `ae35e92`
(stackfix + 1 function). +3 functions (2820 -> 2823), +736 bytes. A third batch (permuter on the 4
closest callers of changed prototypes, 200 s each) found nothing, so the session stopped at 2 work commits.

### `tools/eu_port/protocheck.py` (host side; ~4 s for a report)

```sh
python3 tools/eu_port/protocheck.py                 # report: one line per contradiction + totals
python3 tools/eu_port/protocheck.py --sig func_X    # everything known about one function
python3 tools/eu_port/protocheck.py --apply --skip-logged [--strong] [--max N] [--dry]
python3 tools/eu_port/rescreen.py                   # rescreen drafts of the asm callers of changed functions
```

- **DEF**: functions defined in C vs every other prototype of them (functions.h, other C files).
  Codegen classes are compared (`s32/u32/ptr` count as one class, so only real differences show;
  `--all` adds those minor ones).
- **ASM** (function still GLOBAL_ASM): a small dataflow over the `.s` (branches, likely-branch delay
  slots, call clobbers) gives live-in argument registers (`a0-a3`, `f12/f14`, stack args), prologue
  re-truncation (`andi 0xFF/0xFFFF` and `sll/sra 24/16` written back to `$aN`), narrow reloads of arg
  slots (`lbu 0x..3(sp)` of a home/stack arg with no word load of the same slot), whether `$v0/$f0`
  is set by the function and unread at `jr ra`, and, across all asm callers, whether `$v0/$f0` is read
  after `jal f`. Kinds: `ret` (void prototype, value returned or used), `retvoid` (weak), `narrow`,
  `wide` (weak), `count`, `float`. Hand-written asm (eret/mtc0/cache) is skipped.
- **`--apply`**: per prototype line, the combined change first, then each part alone if that fails;
  the objects of every C file that mentions the function are rebuilt in `conkerdev` and checked with
  `check_files.py`; kept only if they all match (compile errors count as failure). Everything goes
  to `tools/eu_port/protocheck.log` (KEEP/REJECT with old/new line and evidence); `--skip-logged`
  does not retry REJECTed lines. A full pass takes ~10 min; it was run until it converged.
- Numbers (first report): DEF 23 MAJOR, ASM narrow 237, ret 41, count 3, wide 3, retvoid 1.
  **152 prototype lines fixed for 104 functions** (132 from asm evidence, 20 from C definitions;
  46 in `functions.h`, the rest file-local m2c prototypes); **137 attempts rejected** (24 compile
  errors: C callers that pass a different number of args or use the value; 113 changed caller
  codegen, mostly retries of single params of the 47-param `func_1516DF0C` and of `func_150E856C`,
  `func_15182BE0`, `func_151A6308`). Left after convergence: narrow 46, count 3, wide 2, DEF 8
  (all verified to break callers; e.g. `func_15043BB8` reads 3 args and returns a value, but its C
  caller passes one; `func_1000FD38`'s caller passes 4 args to a 3-param definition).
  Examples: `func_15083568`, `func_1505327C`, `func_15140410`, `func_15115244` void -> s32 (callers
  read `$v0`); `func_15052F9C`, `func_1505E874`, `func_15166120`, `func_150ED750` -> f32;
  `func_15169850`, `func_151DC484`, `func_1514D3B0`, `func_151149AC` u8/s16 params.
- **Value**: rescreening the existing drafts of the 375 asm callers of changed functions (only 12 had
  drafts in `nm/` or `sweep/drafts*`) gave 0 OK; a fresh m2c run over the 375 callers
  (`ONLY=<callers> JT=1 gen2.py ... 1 600`, narrow, screen) gave **1 OK, `func_1514E404`** (needs
  `func_15083568` to return s32; strings/float are externs, the file does not own .rodata), 2
  functions improved over their session-13 best (`func_15095B70` CERR -> SIZE±1, `func_15143E94`
  DIFF77 -> SIZE±1), 197 unchanged, 2 worse. So the prototype fixes mostly pay off later, when these
  callers are drafted by hand: the header now tells the truth about returns and narrow params.
- Not covered: callers' argument counts (the data is collected, `callargs`, but not reported), too many
  params in a prototype (`func_150D03A8` has a 3-param handler prototype but only reads `a0`; its own
  definition with 1 param would need its C caller changed: an old-style `()` declaration changed the
  caller's codegen).

### `tools/eu_port/stackfix.py`

```sh
python3 tools/eu_port/stackfix.py func_X draft.c [--rounds 2] [--beam 4]   # -> conker/build/stackfix/func_X/{best,match}.c
python3 tools/eu_port/stackfix.py --scan list.txt          # "func draft.c" lines: which are off by stack offsets only
python3 tools/eu_port/stackfix.py --bisect func_X draft.c  # statements whose removal changes the frame size
```

- Decodes sp-based loads/stores/`addiu` from `screen.py`'s word diff (`SCREEN_V=1`) and prints the
  frame (mine/target), whether every differing word is the same instruction with a different sp
  offset, and the offset map (`28->24`).
- Candidates (per declaration block, multi-line `struct {...} x;` locals are one unit): every order
  (<= 5 units, else rotations/swaps/move-to-front/back), `s32`/`u8[8|12|16]` pads at each position,
  array sizes ±1/±2/+4 (locals and struct fields), locals moved into each enclosing block of all their
  uses and out of inner blocks. Screened 8 at a time with `screen.py`; beam search over rounds, ranked
  by (stack-only, DIFF).
- `screen.py` (and `try`/`tryall`) take `SCREEN_DATAREL=1`: relocations to the TU's own `.data`
  (non-const local array initialisers) are accepted with their contents unchecked; apply.py/fdiff
  remain the authority. stackfix always sets it.
- Results:
  - `func_1500A6D8` (session-10 array at sp+0x28 vs 0x24): **matched in round 1** (167 candidates):
    `s32 temp_v0;` declared before the array, i.e. `struct220 sp48; f32 sp30[6]; s32 temp_v0; u8
    sp24[2][3] = ...; s32 i;`.
  - `func_1500A7E8` (its twin): the same order fixed the stack; then DIFF10 of scheduling; moving the
    `unk14` store before the `sp48` stores (session-10 hint) + 300 s permuter -> **matched**.
  - `func_150144B8` (session 11, no draft left): new hand draft (in
    `tools/decomp-permuter/drafts/`); stackfix took it from DIFF30 to **DIFF4, stack-only**: all slots
    right except `x` and the frame (0xC8 vs 0xC0). `--bisect` shows that removing
    `tmp.unk1C *= D_80096A38;` gives 0xC0: that statement costs 8 hidden bytes (not a local; spellings
    `x = x * k`, `k * x`, a block-scope `k` tried). Permuter 300 s: no improvement.
  - `func_150D03A8`: SIZE+2 from the 3-param prototype (IDO homes the unused `a1`/`a2`; the ROM
    only homes `a0`); not a stack problem, see above.
  - `--scan` over 259 drafts (every still-asm `nm/<f>/best.c`, else the newest `sweep/drafts*`):
    1 stack-only (`func_100046E4`), 2 almost (`func_151F0730`, `func_10006530`, frame/1-2 words),
    1 OK (`func_150E0B78`, rejected by apply: literals 2570/3850 must be `D_800A13A0/A4`, which
    then gives DIFF14). `func_100046E4`: stackfix -> DIFF2, only the frame (0x90 vs 0x80) differs,
    16 unused bytes above `OSIoMesg sp68` that no declaration change removes (`--bisect`: dropping the
    `osPiStartDma` call gives 0x78; register locals, array sizes, dropping permuter temps: no).
  - So stack-only near misses are rare in the current pool (1 in 259 drafts); the tool's main value
    is on hand drafts (2 matches + 1 DIFF4 out of the 4 targets) and `--bisect` for frame-size puzzles.

## Session 16: structured, budgeted "repair" loop (LLM rewrites vs. the permuter)

Sequential, 3 work commits (`c5c5784`, `380bff1`, `f68cfe6`), +19 functions (2823 -> 2842), +2,520 bytes.

### Tools

- `tools/eu_port/repair_ctx.sh <func>`: compact context for one function: target `.s` (instructions only; skipped above
  60 insns, `MAXT=n` to force), the current draft (`tools/decomp-permuter/repair/<f>.c` = latest attempt, else permuter
  `best.c`, else a sweep draft), and the aligned word diff (`ref mine asm`, only the differing region +-3 lines; `**` marks
  differing words; lines that only differ by relocation are not counted). Runs `repair_try.sh` itself when no diff exists yet.
- `tools/eu_port/repair_try.sh <func> <draft.c>`: screens the draft (`m2c/try`), saves it as `repair/<f>.c` and the diff as
  `repair/<f>.diff`, prints `func RESULT` (OK / DIFFn / SIZE+-n / CERR + first error). An OK draft is also `keep`-ed in
  `conker/build/hand`. Careful: it overwrites `repair/<f>.c` with whatever file you pass, so never pass a stale `/tmp/d.c`.
- `tools/decomp-permuter/repair/` (gitignored): `worklist.txt` / `worklist2.txt` (start bucket, function, insn count for the
  252 near-miss drafts, screened fresh against the current headers), the latest draft and diff per function.
- `tools/eu_port/repair_log.tsv`: func, start bucket, attempts, end bucket, matched y/n, permuter used y/n, note.
- Workflow per function: ctx, up to 3 reasoned rewrites (each followed by `repair_try.sh`), `stackfix.py` when only the frame/slots
  are off (it counted as part of an attempt), `permute.sh` (200 s, background) only for DIFF<=4. Batches: `apply.py build/hand`,
  float literals in files that do not own `.rodata` become the externs the asm names (apply REJECTs literals), `needsyms.py`,
  full `verify_all.sh`, commit.

### Numbers

- Worklist: SIZE+-1 and DIFF<=5 first, then DIFF6-14 up to ~70 instructions (skipped: > 70 insns, hand asm such as
  `func_10007D14`, the unfilled-delay-slot handlers, `func_1502B8E0` varargs printf).
- **47 functions tried, 19 matched (40%)**, 100 rewrite attempts (**0.19 matches per attempt**; the 19 matches took 33
  attempts, i.e. 1.7 each, and 16 of them matched within <= 2 attempts). Permuter used on 4 (all DIFF<=4 after 3 attempts):
  1 solved (`func_150C60D4`, < 200 s), 3 not (`func_150A7CB0`, `func_150A0744`, `func_1502F17C`).
- Cost: roughly 330k tokens in total including building the tools and the HANDOFF reading, i.e. ~17k tokens per match, or
  ~3.3k per attempt; wall clock was dominated by the model, not the compiler (a `try` is ~3 s). For comparison the
  permuter sweep (sessions 13-14) needed ~10 h of 9-core time and ~100-300 s per function for ~35 matches out of 400
  candidates (9%); the repair loop got 40% of a hand-picked 47 in about an hour of model time, and the two approaches
  complement each other: the repair loop wins when the draft's *structure* is wrong, the permuter when only
  temp/register/operand order is off.
- Matched: `func_151A544C`, `func_1519D510`, `func_15033730`, `func_150C60D4`, `func_1501BFF0`, `func_1503D774`,
  `func_150D51D4`, `func_151B53FC`, `func_15100248`, `func_150D02C8`, `func_151073F8`, `func_15088A68`, `func_1507F2D4`,
  `func_15096DB0`, `func_150F9FA0`, `func_151B44D8`, `func_1511C37C`, `func_1503E4E4`, `func_1510083C`.

### What kinds of rewrites worked

1. **Fix the call, not the body** (6 of 19): m2c drops or invents arguments. Check the registers set before each `jal`:
   untouched `a0..a3` are *pass-through* arguments (`func_15100248`: `f(a0..a4)` forwards a0-a3 to the callee;
   `func_1510FDA0`: 7 params); a float following int args goes in `a1/a2/a3` as bits, so the prototype is `(u8, f32, f32)`,
   not an int plus `f12` (`func_1501BFF0`); `lw` of a field into `a1/a2` means the parameter is `s32`, not `f32`
   (`func_1511C37C`).
2. **Strip permuter junk first** (`func_15088A68`): `do {} while (0)`, `if (!x && !x && !x) {}`, `volatile`, `(0, x)`,
   `x = x;`, `goto dummy_label`. They are noise from the permuter's own passes; the clean version matched at once.
3. **Roll back what IDO unrolled** (`func_15096DB0`): a 4x-unrolled loop with remainder prologue (`andi 3`) is just
   `for (i = 0; i < n; i++) if (tbl[i * 0x24]) return 1;`. m2c writes the unrolled form literally.
4. **Compound assignments** (`func_151A544C`, `func_1519D510`, `func_150F9FA0`): `p[0x30] |= 1; p[0x30] |= 4;`
   (two stores, the second `ori` of the first result) and `*(s32 *)(p + 0x84) |= 0x80; ... &= ~8;`. A temp in between
   lets IDO fold the constants (`ori 5`). Lerp: `x += (t - x) * k;` without a temp (`func_150D51D4`, also fixes the
   `add.s` operand order).
5. **Control-flow shape**: `switch` with merged cases (`func_15033730`), if/else instead of fall-through into a second
   test (`func_1503E4E4`), `if (s) v = s; else v = f();` with two locals (`func_1511C37C`), table typed as an array of
   function pointers instead of `s32` with `* 4` index (`func_151073F8`; the m2c/permuter `&D + i * 4` on an `s32` extern
   scales twice, so check any `(&D_x) + (i * 4)`).
6. **Register-order tricks**: a pointer alias declared first and the other pointer read through it (`q = arg0 + 0x28;
   o = *(u8 **)q;` fixed v0/v1 in `func_1510083C`); a block-scope alias `f32 *dst = arg1;` keeps `arg1` out of `a3`
   (`func_151B44D8`); the loop parameter itself as the walking pointer plus a `start` copy (`func_1503D774`); a single
   pointer variable reused for base and `+= 0x58` (`func_1507F2D4`); `u8 *` ptr-typed base instead of `s32` for
   `base + (idx << 6)` operand order was a no-op but the permuter then found the rest (`func_150C60D4`).
7. **`stackfix.py` after a clean rewrite** (`func_150D02C8`, `func_1507F2D4`): the rewrite gets the code right, the
   tool finds the local declaration order/scope.
- Did not help: parameter-as-temp (adds homing), `&arg0` deref tricks for home-slot reloads, `if (x) {}` liveness hacks,
  reordering statements for scheduling. Those cases stayed at DIFF6-30.

### Left (see `repair_log.tsv` for the notes)

- Rewritten but not matching: `func_150351A4` (DIFF1, `mul.s` operand order), `func_15030060` (DIFF5, `a2` register),
  `func_150104F0` (SIZE-1, `or v0, zero` before chained byte stores), `func_151F0730` (SIZE+1, `sw a2` not in the `jal`
  delay slot), `func_150A7CB0` (DIFF3), `func_1502F17C` (DIFF3, best draft in `repair/`: `u8` truncation of `v - 2`),
  `func_150A0744` (DIFF7, register numbering), `func_1510FDA0` (screens OK with the 0.02f literal, 1 word off in the real
  file with the extern `D_800A316C`: `c.eq.s` operand order; file does not own .rodata; owning it should fix it),
  `func_15087040` (SIZE-3, trailing dead `jr ra; nop` after an inline `sqrt.s`), `func_151149AC`, `func_151999BC`
  (table-search family), `func_150FC8E8` (`&&` chain, `v0/v1` of two pointers), `func_150836AC`, `func_150E0150`,
  `func_151016C8` (frame fixed, registers off), `func_15190A2C` (needs `p = arg0 + 0x30` spilled separately),
  `func_15104A0C`, `func_151BE65C`, `func_150C1B60` (ref homes only `a2/a3`).
- Blocked by the session-7 unfilled-delay-slot shape (not attempted or abandoned): `func_15193850`, `func_151B255C`,
  `func_151B7664`, `func_151D51E8`.
- Not yet tried from `repair/worklist2.txt`: ~170 entries, mostly DIFF12+ or > 70 instructions.

### Next steps (session 16)

- Continue the repair loop on `worklist2.txt` (DIFF12-30, <= 60 insns first), and extend it to *fresh* m2c drafts of
  short functions (m2c output with correct call prototypes after the protocheck fixes), not only to drafts that already
  were near misses: the 6 "wrong call" fixes suggest many failed drafts are only wrong at their calls.
- Check m2c drafts for the call patterns in item 1 automatically (pass-through `a0..a3`, `lw` into `a1..a3` before a call
  whose prototype says `f32`, float after int args) and for `(&D + i * k)` scaling on non-byte externs.
- Own `.rodata` of `game_eu_13C400` and retry `func_1510FDA0`.

## Session 17: draft pre-check hints, fresh short-function drafts, callee-arity fixes

Sequential, 3 work commits (`f300d27`, `75e7386`, `3b05e9d`), +35 functions (2842 -> 2877), +4,048 bytes. The repair loop of
session 16 with a script that checks the drafts' *calls* first. Full `verify_all.sh` before every commit.

### Tools

- `tools/eu_port/draftcheck.py <func> [draft.c]` (also run by `repair_ctx.sh`, section `=== HINTS`): walks the target `.s` call
  segment by call segment (delay slots and `$sp+0x10..` stack-arg stores included) and prints `HINT` lines when the draft disagrees:
  * *pass-through*: `a0..a3` untouched since entry and live-in (read by the function) before a `jal` are arguments of the callee;
    the draft passes fewer (`pass-through a0 ... draft passes 2`);
  * *arity*: callee prototype (C definition in `src_eu`, else `functions.h`, else file declarations, else the draft's own) has fewer
    params than the registers/stack slots the asm sets; draft passes more args than the asm sets (invented args);
  * *float*: `mfc1 aN` before the call but the prototype says non-float (float after int args), f12/f14 set but first param not
    float; `lw aN` into a float param only when the prototype is the draft's/file's own, not a definition;
  * *table*: `(&D + i * k)` on a non-byte extern (scales twice), `*(&D + idx)` on a 4-byte extern (the asm may read bytes).
  False positives to ignore: callee is a C function with fewer params than the registers (junk in `a1..a3`), `sp`-spill copies in `a3`.
- `tools/eu_port/gen40.sh [max]`: `list.py` + `gen2.py` (JT=1) + narrow + screen for every asm function up to `max` instructions,
  ranked list in `tools/decomp-permuter/repair/fresh.txt` (`score result func dir`), best drafts in `repair/fresh/<f>.c`
  (`repair_ctx.sh` prefers these). 422 functions <= 40 insns: **2 OK as generated** (`func_15115244` applied, `func_151EF7B0`
  still the padding case), 27 SIZE-1, 24 SIZE+1, 103 CERR (mostly undeclared `spXX` locals of m2c: add `f32 sp28[4][4];` etc.).
- `tools/eu_port/rlog.sh`: append a `repair_log.tsv` row. `m2c/try` now passes `SCREEN_OPT` into the container
  (`SCREEN_OPT="-O1 -g3" repair_try.sh ...`).
- Pitfalls: `verify_all.sh` wipes `conker/build` (also `build/hand_done`): `make` before `apply.py`, `mkdir build/hand_done`, and move
  applied drafts out of `build/hand` (apply crashes on an already applied one); a `sed -i '$d'` on the log after a failed `rlog` deletes
  the previous row.

### Numbers

- Rows in `repair_log.tsv` this session: 66, of which 59 with attempts: **59 tried, 33 matched (56%)**, 106 rewrite attempts =
  **0.31 matches per attempt** (the matches took 47 attempts: 1.4 each; 25 of 33 matched with <= 2 attempts). Plus `func_1510FDA0`
  (not in the log; matched once `game_eu_13C400` owns its `.rodata`). Permuter 200 s on 2 DIFF2 leftovers
  (`func_15074A94`, `func_1511CAD0`): no improvement.
- Cumulative repair loop (sessions 16 + 17): **106 tried, 52 matched (49%), 206 attempts = 0.25 matches per attempt**.
- About two thirds of the 33 matches came from a call/prototype fix found by `draftcheck.py` or by reading the callee's liveins with
  `protocheck.py --sig`: the call patterns are by far the best predictor of a cheap match.
- Matched (33): `func_15115244` (fresh), `func_1507ECE8`, `func_150D07C4`, `func_150D0644`, `func_151D8D90`, `func_15045A70`,
  `func_150DF0D8`, `func_150D18B0`, `func_1507EE24`, `func_151A94CC`, `func_151791A4`, `func_15190AC0`, `func_15182CD8`,
  `func_1517FA48`, `func_150EF328`, `func_150D2804`, `func_15063894`, `func_15194F64`, `func_1507EE9C`, `func_15114E28`,
  `func_1511084C`, `func_151000EC`, `func_1510ED24`, `func_1510EDAC`, `func_1510EE3C`, `func_150BA1F4`, `func_15133A80`,
  `func_15133CD0`, `func_15082D5C`, `func_150FB768`, `func_150234E8`, `func_1508823C`, `func_15095EA0`.
- `game_eu_13C400` now owns `.rodata` 0x2483A0-0x2483F0 (3 functions with f32 literals use literals directly).

### Rewrite patterns that worked (new this session)

1. **Pass-through args** (`func_150DF0D8`, `func_150EF328`, `func_15182CD8`, `func_15190AC0`, `func_151A94CC`):
   untouched `a0..a3` are real arguments. m2c drops them, so the call has 1-3 args too few and every later register shifts.
   Callees seen: `func_1517F5FC` (6 args: `(arg0, v[3], v[0], v[1], v[2], v[4])`, `func_150D2804`, `func_15182CD8`, `func_1517FA48`),
   `func_1510EED0` (16 args), `func_150D0420` (8 args), `func_15142600` / `func_151424F4` / `func_15142838` (12/12/9 args,
   `a0` pass-through, object fields via `lw a1..a3`, f32 stack args), `func_15104B60` (`(u8 *, s32, f32)`: 250.0f is a `lui a2`).
2. **The opposite: m2c invented args** when the callee is a C function with fewer params (`func_1516D850/898`, `func_15179108`,
   `func_15088D24`): read the definition (`protocheck.py --sig f`) before trusting the registers.
3. **Narrow protos make the prologue**: a `u8`/`s16` callee param whose argument is the function's own `u8`/`s16` param gives
   `sw a0; andi t6,a0,0xFF; or a0,t6` and `sll/sra` for free (`func_150D07C4/0644`: prototype `(u8, s32, s16, s32, s32, s32, u8, s32)`
   AND params `(u8, s32, s16, u8, s32)`; with `s32` params nothing is truncated). `s32` call result passed to a `u8` param: `andi`.
4. **A float following int args is an `f32` param** even if you only see `lw`/`mfc1` into `a1..a3`: `(u8 *, f32, s32 *, u8 *)` for
   `func_1504627C`; an f32 stack arg handed on goes through `lw a3, off(sp)` (`func_15095EA0`: keep the header's `f32 arg4`).
5. **K&R definition when a C caller passes more args than the callee reads** (`func_1507EE9C`): `void f(arg0) u8 *arg0; { ... }`
   avoids the `number of arguments` clash with the earlier call and keeps both codegens.
6. **Missing m2c locals**: CERR drafts with `&sp28[0]`/`sp20` and no declaration are matrices: `f32 sp28[4][4];`
   (`func_15114E28`, `func_1511084C`, `func_150F2A98`); a struct local `struct { f32 x; s16 y; } sp2C;` for a memcpy source with
   mixed field sizes (`func_150D07C4`, `u8 sp30[4]`-style gave worse results than `s8 sp30` + stackfix pad).
7. **Tables**: `extern s32 D_x` read as `*(&D_x + idx)` was `u8 D_x[]` with byte stride (`func_151D8D90`, a `for` with `u8 i` and
   `1 << i`); function-pointer table `extern void (*D[])(u8 *, s32, u8)` called with all 3 args (`func_15190AC0`);
   `s32 *` + `arg1 + temp_v0` scales by 4: keep the pointer an `s32`/`u8 *` (`func_1507EE24`).
8. **Struct index**: `arg0 - D_800CC2D0` with `struct127 *arg0` (not `u8 *`) gives the `div 0x32C` (`func_15063894`, `func_151000EC`).
9. **s32 locals instead of `u8`** for loop bounds loaded from byte externs (`func_15082D5C`); `(u16)` cast on an s16 table read for `lhu`
   (`func_1517FA48`); statement order inside a float block (`func_150D18B0`: the `0x3C` multiply before the `0xC4` add);
   hoist a `u16` load into a local before the call (`func_151000EC`).
10. **Draft declares a callee that a later C function in the same file calls differently**: add the prototype to the draft
    (`void func_1503EF90(s32);`), else the implicit declaration clashes (CERR `redeclaration`).

### Left (notes in `repair_log.tsv`)

- **Shape that keeps recurring: reload-from-home / unfilled delay slot.** Handlers and small functions where the ref reloads
  `arg0` from its home slot, has `b L; lw ra` (epilogue instruction in the delay slot of each return) and `beqz ..; nop`:
  `func_150C5060`, `func_150F1B78`, `func_150F7890`, `func_151007B0`, `func_151D7AE8` (same 4-arg handler template: `-O1 -g3` gives
  DIFF28 not OK), `func_150C62C0`, `func_150C6BF0` (DIFF11), `func_151095E4` (switch layout right, case end unfilled).
  Still unsolved; maybe a pragma or a different object boundary.
- **A dead `addiu v0, v0, K` that IDO drops from my C**: `func_150C63FC` (+ `func_150C6D2C`, `func_151AB730`), `func_150C7DE0`.
- Register numbering only (permuter candidates, DIFF > 4 so not run): `func_1503DE70`, `func_1503F1B0`, `func_150F2A98` (t7/t8),
  `func_150FB708` (f0/f2), `func_15034710` (t6..t9), `func_15116690` (DIFF7), `func_151F0114` (DIFF9), `func_151674DC` (DIFF23).
- DIFF2 permuter-resistant: `func_15074A94` (f12/f8 swap), `func_1511CAD0`, `func_151D51E8` (handler shape).
- `func_1507ED48` (SIZE-2), `func_150AEDF8` (SIZE-1), `func_151BD7CC` (SIZE-1, u8 handlers), `func_15022BB0` (needs the loop not
  unrolled: `goto` form is DIFF22), `func_1508039C`, `func_150DF1A8`, `func_150F2910`, `func_1509FC5C`, `func_150882C4`.
- Not tried: the other worklist2 entries (DIFF12+, ~140), `func_1517AF18`, `func_15094CD0`, fresh SIZE+-2 ranks, 41-70 insn
  functions of `fresh.txt`'s CERR group after adding the missing locals.

### Next steps (session 17)

- Run `gen40.sh 70` and use `draftcheck.py` hints as the filter; start with drafts where it prints *pass-through* / *proto has N
  params, asm passes M* against a prototype that is a C definition (those are real).
- Make `draftcheck.py` auto-apply the safe part: rewrite the draft's call (add pass-through args), declare the callee from the
  asm liveins when no definition exists, add `sp` matrix locals for undeclared `spXX` (would turn many CERR into screenable drafts).
- Look at the reload-from-home shape with a fresh idea (list above): 8 functions wait on it.

## Session 18: repair loop on fresh gen40 drafts (hint filter), reuse-one-local patterns

Sequential, 2 work commits (`82a7b53`, `d14edb0`), +22 functions (2877 -> 2899), +2,272 bytes. Full `verify_all.sh` before the last
commit, `--quick` before the first (plus a failed full run that caught the `func_15178E14` caller size).

### Tools / setup

- `gen40.sh 70` rerun (7 min, 932 ranked entries in `repair/fresh.txt`; 240 are still CERR). It does **not** refresh
  `repair/fresh/`, so the new `tools/eu_port/fctx.sh <func>` copies the draft from the dir named in `fresh.txt` into `repair/fresh/`
  and prints `repair_ctx.sh` (MAXT=60 default). Use it instead of `repair_ctx.sh` for gen40 drafts.
- Hint filter used: `draftcheck.py` over all non-CERR fresh drafts that are still asm and not in the log (329 files, 115 with hints). Most
  hints are `proto has 1 params, asm passes a0..a3` on `func_1516972C` (a C function with one param: junk regs, ignore) and `sinf/cosf`
  pass-through (libm, ignore). The real ones were callee arity (`func_15094DAC`, `func_15123A54`, `func_1511084C`); most other matches
  were statement-order/local fixes, so "short + DIFF <= 12" was a better filter than the hints.
- Pitfalls: BSD `sed -i` needs `sed -i ''` (without it the script is taken as the backup suffix: "extra characters at the end of d
  command"). `rlog.sh` with an unquoted `DIFF?` in zsh is a glob error and writes no row.

### Numbers

- Rows in `repair_log.tsv` this session: **40 tried, 22 matched (55%)**, 68 rewrite attempts = **0.32 matches per attempt**
  (the 22 matches took 28 attempts, 1.3 each). Permuter 200 s on 2 leftovers (DIFF3 each): **2 solved** (`func_150EA904`,
  `func_150F791C`, both < 200 s).
- Cumulative repair loop (sessions 16 + 17 + 18): **146 tried, 74 matched (51%), 274 attempts = 0.27 matches per attempt**.
- Matched (22): `func_151108E0`, `func_1512C5D8`, `func_15094CD0`, `func_1503BC4C`, `func_15178E14`, `func_151C8D5C`, `func_151927C0`,
  `func_150EA904`, `func_1516FEF4`, `func_150C7D70`, `func_151D90D4`, `func_1508F054`, `func_1508EFEC`, `func_1508F0B8`,
  `func_15133FC0`, `func_150CFA88`, `func_15150108`, `func_150F791C`, `func_151992B0`, `func_150FF148`, `func_15133F44`, `func_150E3C3C`.

### New rewrite patterns

1. **Callee arity from the asm, again** (`func_1512C5D8`, `func_15094CD0`, `func_151108E0`, `func_150C7D70`): m2c invented f32 args for a
   callee that takes only `arg0`; or dropped the pass-through `a0` (`func_15094DAC(arg0, sp50)`, `func_15116A8C(arg0, 1, 0x43, f32)`).
2. **Byte-table read into an `s32` temp** (`func_1503BC4C`, `func_1508F054/EFEC/F0B8`): `lbu v0, %lo(D)(v0)` with the table folded into
   the load needs `s32 t = *((u8 *)&D + idx * 0x32C);`. A `u8 t` goes to `v1`; an `s32` temp lands in `v0` as the ref has it.
3. **Reuse one local** (`func_1516FEF4`): `s32 v = *(s16 *)p; v = v * arg1; *(s16 *)p = v >> 8;` numbers the temps like the ref
   (no skipped `t6`). The same idea only half-worked on `func_1516FE5C/FE8C` (v0 right, `t6/t7` swapped).
4. **Statement order decides schedule and regs** (`func_151927C0`: compute `y` first, then the constant stores, then `(y << 16) + y`;
   explicit `(y << 16) + y` beats `* 0x10001`; `func_15133FC0/F44`: the `0x3C` store first, `temp_f0` loaded after it;
   `func_150CFA88`: accumulate `D * 0x1A` first, then the `0x1C` temp; `func_150FF148`: hoist the third call argument into a local;
   `func_1512C5D8`: store `0x384` before `0x5CC = 0`; `func_151992B0`: load the `0x98` pointer before the test).
5. **Frame size = local sizes**: `func_15150108` had `s32 sp34; s32 sp28;` but the frame wants `s32 sp34[3]; s32 sp28[3];` (12-byte
   vectors); `func_15094CD0`: `u8 *sp50[16]` and a plain `for` instead of m2c's `var_s1 += 4` on a `u8 **` (scaled twice).
6. **Stack-passed 5th..7th parameters**: `lw t8, 0x18($sp)` in a leaf with a 4-register prologue is the 7th parameter: add dummy
   `arg4/arg5` (`func_151C8D5C`); `p`/`q` locals order the loads.
7. **Loop shapes**: `u8 i` with a `u8` callee param gives the `v0 = s0 & 0xFF` copy for free (`func_151D90D4`); the s32 form
   `i += 1; i = i & 0xFF; while (i < 2)` (permuter result for `func_150F791C`; `t = (i + 1) & 0xFF` made a spurious `v0`); an `s32 *` array
   walked as `p[i + 2]`, never `(p + i * 4)`.
8. **Parameter as the temp** (`func_150E3C3C`: `arg0 = arg0 - 1;` keeps the table index in `a0`, `v0` for the loaded pointer).
9. **Header prototype vs. real arity** (`func_15178E14`): the caller in `game_CB1C0.c` passed two args to a one-param function; fixing
   the prototype to `void func_15178E14(u8);` and the caller to one argument matched both. (`()` in the header plus a K&R definition matched the
   function but shrank the caller by 4 insns, so don't.)
10. **Permuter output cleanup**: `p[0x73] = (p[0x73] & 0xFFFF) | 3;` (`func_150EA904`) is what the permuter found; keep it verbatim.

### Left (notes in `repair_log.tsv`)

- **Float literal needs an extern, and the extern schedules differently**: `func_1515F61C` screens OK with the literal `32767.0f` (nested
  if/else clamp), but in the real file (no `.rodata` ownership) the extern `D_eu_800A6904` puts `lui at` before `c.le.s` and costs one insn.
  Own the `.rodata` of `game_eu_18B1C0` (like `game_eu_13C400` in session 17) and write the literal. The same trap may hide in other
  "OK" float drafts that `apply.py` REJECTs.
- Leaf float functions with `f0/f2/f4` numbering where mine starts at `f4/f12` (`func_150AD930` sqrt of squares, `func_150ADDE0` dot
  product, DIFF11-12): maybe not compiled like the rest (try other `SCREEN_OPT`).
- Dead `addiu v0, v0, K` again (`func_150C7E30`, a0 pass-through to `func_1511563C`), `func_151C9C8C`; `func_1514143C` (ref keeps `v0 = a0 + 0x110`
  unfolded); `func_15141478` (ref spills `v1` to `0x24($sp)` across calls, mine gets an s-reg: frame 0x28).
- Reload-from-home shape again: `func_150A33C4/3484`, `func_150802A8` (`or a2, a0` alias), `func_151CA0E0`, `func_151CA114`.
- Register-number leftovers: `func_1517A028` (a0/a1, DIFF6), `func_1514F114` (DIFF5, hoisted `lw t8`), `func_151EFDD0` (DIFF8), `func_15155CF0`
  (DIFF8 scheduling), `func_1515D4D4`, `func_15109100`, `func_151DDA10`, `func_100038E0`, `func_1516FE5C/FE8C`.
- Skipped as too big/odd: `func_1000CDA0` (67 insns), `func_150E2EA4/E3334` (27-arg call), handwritten `func_150A7770`, `func_150ADACC`.
- Not tried: the rest of `fresh.txt` (SIZE-1/+1 at 25-60 insns, ~100 entries), worklist2 (nothing from it this session), the CERR group
  (240; add the missing `spXX` locals).

### Next steps (session 18)

- Own the `.rodata` of `game_eu_18B1C0` and retry `func_1515F61C`; scan `repair/*.c` for other drafts REJECTed only for literals.
- Run `permute.sh` also on DIFF5-6 register-only leftovers (`func_1517A028`, `func_1514F114`, `func_151EFDD0`): it solved both DIFF3
  cases in < 200 s this session.
- Try "reuse one local" and "statement order" first on any short DIFF<=12 draft; they produced 9 of the 22 matches.
- Remaining `fresh.txt` entries by DIFF score, then worklist2.

## Session 19: repair loop on fresh drafts (short, DIFF<=12), permuter on leftovers, initializer copies

Sequential, 2 work commits (`b466fd2` + the final one), +23 functions (2899 -> 2922), +3,248 bytes. Full `verify_all.sh` before both.

### Tools / setup

- `game_eu_18B1C0` now owns `.rodata` 0x24BB80-0x24BBA0 (`rodata_split.py --own ... --resplit`); `func_1515F61C` matches with the literal `32767.0f`.
- `tools/eu_port/gensome.sh <func>...`: regenerates m2c drafts for just those functions (ONLY=list into `conker/build/ks`), narrows, screens and copies the
  best draft per function into `repair/fresh/` (prints `result func`). Needed because a `--resplit` or `verify_all.sh` wipes `conker/build/k40`, so `fctx.sh`
  can no longer find the gen40 drafts of functions not already in `repair/fresh/` (the dir named in `fresh.txt` is gone).
- Permuter (`permute.sh -l list 200 4`, background, 7 + 6 functions): **5 of the 13 solved outright** (`func_1514F114`, `func_15030060`, `func_15022864`,
  `func_1518AADC`, `func_1519E764`, all < 200 s; the register-only/scheduling leftovers) and two more brought to DIFF1/2 whose last word was hand-fixed
  (`func_151B9190`: mul operand order; `func_151A4EB0`: multu operand order). `match.c` goes through `repair_try.sh` (-> `build/hand`) like any draft.
- Pitfalls: `apply.py` aborts if `build/hand/screen.txt` still lists a function whose `.c` was moved to `hand_done` (delete the line); a draft that
  declares a prototype for a callee that an earlier-applied function of the same file now defines must drop that declaration (`func_15172474`, REJECT until
  `func_15172210`'s decl line was removed and `temp_v0` made `u8 *`).

### Numbers

- Rows in `repair_log.tsv` this session: **39 tried, 23 matched (59%)**; 81 rewrite attempts (the 16 reasoned matches took 29; 7 matches came from
  the permuter, 6 of them with 0-3 hand tweaks). Cumulative repair loop (sessions 16-19): **185 tried, 97 matched (52%)**.
- Matched (23): `func_1515F61C`, `func_150D09D4`, `func_1519EEE0`, `func_150B42B0`, `func_150E7498`, `func_1515C710`, `func_1515C7B4`, `func_15172210`,
  `func_15172474`, `func_1518FA0C`, `func_15107B9C`, `func_150C4FD8`, `func_151D1488`, `func_15134DAC`, `func_151E3A1C`, `func_151B90F0`,
  plus permuter: `func_1514F114`, `func_15030060`, `func_15022864`, `func_1518AADC`, `func_1519E764`, `func_151B9190`, `func_151A4EB0`.

### New rewrite patterns

1. **`or a1, a0` / `or a2, a0` copies of a parameter** (`func_15107B9C`, `func_150C4FD8`, `func_151D1488`): `u8 *p = arg0;` as a *declaration with initializer* gives
   the copy into `a1`; the same via a later assignment `p = arg0;` puts it in `a2`. Twin handlers: `if (*(s32 *)(p + K) != 0) func_1516972C(*(struct102 **)(p + K));`.
   (Did not carry over to `func_151C9CBC`/`func_151C8C24`: copies right, but frame 0x28 instead of 0x20.)
2. **One-byte local passed by address** (`func_150D09D4`, `func_150B42B0`): `s8 sp30[8]` / `s8 sp24[4]` array (assign `sp[0]`, pass `sp`) puts the byte at the
   ref offset and fixes the frame, where `s8 sp30;` + stackfix pad only reached DIFF2.
3. **Constant store order in object-init functions** (`func_1519EEE0`, `func_15172210`, `func_15134DAC`): the ref has the argument-derived stores first, then
   the constant (0/1) stores, then the last byte store (`+0x59`); `s16` negated store before the `1`-store. Writing in that order gives the ref schedule.
4. **Float operand order matters for the register numbers**: `addend + (x * sinf(y))` (`func_151B9190`, `func_151B90F0`); a lerp `(v[4] - (b = v[1])) * t + b` with
   separate locals per component loads the far operand first (`func_150E7498`, with the table through `((f32 **)&D)[idx % 6U]`); `(f32)s16 + load` in
   `func_1515C710` (use if/else instead of an early `return`). Integer multiplies: swap operands when `multu` has `rs`/`rt` reversed (`func_151A4EB0`).
5. **Several `||` operands: name every load** (`func_1518FA0C`: four temps loaded before the test, compare order `a0 == a1`).
6. **Byte vs word reads of a struct field** (`func_1519E764`): m2c's `(u8)*(s32 *)p` / `*(u8 *)(p + 4)` were really `*p` (byte at +0) and `*(s32 *)(p + 4)`.
7. **`D_800E0FC9` as `u8`** (`func_151E3A1C`): a different type for the second of two `= 1` stores stops IDO from CSE-ing the constant across a call.
8. **Pointer arithmetic on a struct pointer scales the offset** (`func_15172474`: `(u8 *)temp_v0 + 0x10`; `struct102 *` + 0x10 was `+0x400`).

### Left (notes in `repair_log.tsv`)

- `func_1513B798` DIFF2 (permuter best.c kept as the draft: the flag byte is `lbu` at sp+0x1B; `char` gives `lb` at 0x1A, `u8` is DIFF10).
- Dead `addiu v1, -0xC` in a delay slot (`func_100043B4`, same family as `func_150C63FC`); `func_15174E90` (clamp branch with unfilled delay slot, blocked shape);
  `func_10001420` (memclear loop: mine materialises the base address twice); `func_150B7258` (ref keeps `&D_800D9CB4` in `s0`, then reuses it for `D_800D9CB8`).
- Not solved: `func_150D19AC` (same pointer in two stack slots + mtc1 hoist), `func_151C9CBC`/`func_151C8C24` (frame size), `func_150ADDE0` (leaf float f0/f2/f4; -O1/-O3/-mips1 no help).
- Untried from the DIFF<=12 list: `func_150F2F14`, `func_15031044`, `func_1503F7A0`, `func_150FE1AC`, `func_1510B8AC`, `func_1510BB78`, `func_1515C3C0`; the rest of `fresh.txt` and worklist2.
- Earlier leftovers still open: `func_1517A028` (permuter DIFF1), `func_151E8998` (DIFF10), `func_1516FE5C/FE8C` (DIFF4/5), `func_1510B930` (nothing).

### Next steps (session 19)

- Run the permuter (200 s, 4 jobs, background) *first* on every register/scheduling-only DIFF<=6 leftover and on the untried DIFF<=12 list; it solved 5/13 and took
  two more to DIFF1-2. Then hand-fix the last word (operand order of `mul`/`multu`/`add`, byte types).
- Use the initializer-copy and constant-store-order patterns on the remaining 12-insn delete-handlers and object-init functions.

## Session 20: permuter first on every leftover, dead-addiu and table-call families solved

Sequential, 1 work commit (`028cb85`) + this hand-off, +26 functions (2922 -> 2948), +2,032 bytes. Full `verify_all.sh` (code build, check_files,
full ROM all OK). ~50 functions tried (12 of them only by the permuter).

### Numbers

- Rows in `repair_log.tsv` this session: 33 (26 matched). Hand-written rewrites matched 14 (mostly callee prototype/arity, array locals, copies);
  the permuter (120-150 s, 5 jobs, run in the background while drafting) solved **10 of ~25** draft runs it was given, many of which had stayed open for
  several sessions. A DIFF2-7 hand draft is a better permuter input than a raw m2c DIFF12 draft: the seven fresh DIFF11-12 drafts of the session-19 list
  were not run (the permuter was killed in favour of hand-improved drafts), the DIFF<=6 old leftovers `func_1513B798`, `func_1511CAD0`, `func_15074A94`,
  `func_150A7CB0`, `func_1510B930` got **no improvement** in 150 s.
- Matched (26): `func_1519D4E0`, `func_151308E4`, `func_151343AC`, `func_151A3180`, `func_15135424`, `func_1503E1FC`, `func_151C3444`, `func_150ED750`,
  `func_150D1920`, `func_15034118`, `func_1519072C`, `func_151A625C`, `func_151A629C`, `func_151D5E30`, `func_1510DBB0`, `func_151635A8`,
  `func_151D7958`, `func_15107C24`, `func_150D034C`, `func_1508F060`, `func_150C6D2C`, `func_151AB730`, `func_150C7E30`, `func_150C7DE0`,
  `func_150C63FC`, `func_1514143C`.
- Pitfalls: `apply.py` is `tools/eu_port/m2c/apply.py` (run it in the container with cwd `conker`: `docker exec -w /conker/conker conkerdev python3
  ../tools/eu_port/m2c/apply.py build/hand`), and an applied draft must be moved to `build/hand_done` with its line removed from `build/hand/screen.txt`
  before the next run. Permuter `match.c` may change the return type of the function (`volatile short func_1514143C`); the real build is the judge:
  `void` did **not** match, `s32`/`s16` did (kept `s32`, the function has no return statement). `verify_all.sh` wipes `conker/build`: after it, functions that
  are already C have no `.s` to screen against (`repair_try.sh` prints just the name).

### New rewrite patterns

1. **Dead `addiu v0, v0, K` kept (the old "dead addiu" blocked family, 6 functions)**: IDO folds `p + K` into the offsets and drops the add, but not across
   `p += K + 1; p--;`. Write `p = base; p += K+1; p--;` then address everything with the *reduced* offsets (`p + (off - K)`):
   `func_150C6D2C/151AB730/150C63FC` (K=0x58), `func_150C7E30/7DE0` (K=0x1E0, read at `p + 0x3C` instead of `0x21C`). The permuter found `p++; p--;`
   (adds 0); `+K+1/-1` makes it exact.
2. **Indirect call through a table re-reads the index** (`func_151635A8`, `func_15107C24`, `func_151D7958`; IDO CSEs the second `lbu` otherwise): the permuter
   solves it with `int new_var = 0x25; ... D[arg0[new_var]]` (constant index in a variable) or `u8 *new_var = &arg0[0x2C];` for the second read. For
   `func_15107C24` keep the local table pointer `void (**tab)(u8 *, s32, u8) = D;`. Handler params `(u8 *, s32, u8 arg2)`.
3. **Re-load of a field instead of reuse**: `u16 *new_var = (u16 *)(p + 0x6C); if (*new_var) f(*new_var);` (`func_151A625C/629C`: gives `lhu t6` for the test and a
   fresh `lhu a0`, no `andi`); the loop `s32 *t = arg0[i]; if (t) { new_var = arg0[i]; f(new_var, 3); }` (`func_151D5E30`).
4. **A constant that must stay a register** (`func_1508F060`: `v0 = 2; sll t6, v0, 4`): `int new_var = 2; int *new_var2 = &new_var; ... (*new_var2) * 16`.
5. **Locals optimised away that the ref keeps in memory**: `s32 sp20[2]; s32 sp18[2];` arrays assigned element-wise (`func_15135424`); `u8 sp1C[4]` array
   passed to a 2-arg callee (`func_1519D4E0`); initializer copy of a 8-byte `.data` blob: `struct_eu_s32x2 sp18 = D_800A3C40;` (`func_151343AC`).
6. **Callee arity/types from the asm, again** (`func_151308E4`: 6-param callee, a0 pass-through + stack `u8`; `func_151A3180`: callee `(s16, s16, f32, s32)`, the
   draft passed 5 args; `func_150ED750`: `arg0 = func(arg0)` spills into the param home so the frame stays 0x18).
7. **`s8` param -> `s32`** (`func_1503E1FC`): an `s8` param makes IDO home `a1`; `s32` stores the byte directly.
8. **`u8 *` instead of `s32` for object pointers in loops/compares** (`func_15034118`, `func_151C3444`, `func_150D1920`: draft was already right, only the types
   made the m2c draft CERR/SIZE-off).
9. **Hoisted `p + n` before the guard** (`func_1510DBB0`, permuter): `new_var = p + n; if (n > 0) { end = new_var; do { ... } while (end != p); }` with `s16 *q = arg0;`.

### Left (notes in `repair_log.tsv`)

- Not solved: `func_151F0754` (varargs `(u8 *, s32, ...)`, DIFF4 with the permuter: `a0` home before `ra`, `lw a1` placement), `func_150C572C` (DIFF2: `addiu s1/s0`
  order), `func_1513B798`, `func_151CA484` (ref keeps `&sp24` in `s0`: permuter DIFF4), `func_15199954`/`func_1519C428` (search-loop family, DIFF22), `func_1514F3E0`
  (arg0 reloaded from home), `func_1515A120` (SIZE-3, arg1 homed), `func_151D1694` (CERR: return type vs. the implicit declaration in the caller),
  `func_100043B4` (dead `addiu v1, -0xC` in a jal delay slot: `arg0 -= 2; arg0--;` made it worse, DIFF15), `func_15197F7C` (string literals: needs `.rodata` ownership),
  `func_151600E0` (empty `if` with dead `bltz`), `func_1502DE10` (switch/jump table), `func_151D5E30`-style CERR group of `fresh.txt` (many left).
- Untried: the 7 DIFF11-12 fresh drafts of the session-19 list (`func_150F2F14`, `func_15031044`, `func_1503F7A0`, `func_150FE1AC`, `func_1510B8AC`, `func_1510BB78`,
  `func_1515C3C0`), the rest of `fresh.txt` above ~30 instructions, worklist2.

### Next steps (session 20)

- Re-try the other known "dead addiu" leftovers with pattern 1 (`func_15109100`, `func_15141478`, `func_151C9C8C`) and every function that logged "ref keeps `v0 = a0 + K`".
- Give the permuter *hand-improved* DIFF2-8 drafts rather than raw ones; hand drafts that screen at DIFF<=8 with a known blocked shape (table call, dead add,
  constant in a register) are worth 120 s each.
- Run the permuter with 5 jobs in the background from the first minute and draft meanwhile (this session did, and it paid off).

## Session 21: fakematch labels, untried DIFF<=12 list, strings for func_15197F7C

2 work commits (`2ad4fa9` + the next) + this hand-off; +11 functions (2948 -> 2959). ~32 functions tried. Full `verify_all.sh` before each commit.

- **Fakematch labels**: every `new_var` pin, `p += K+1; p--;`, `if (0) { }`, chained pointer, dead-test construct committed in sessions 19-20 and today's has a
  `// fakematch: <why>` comment (`grep -rn fakematch conker/src_eu`). Comments only; code unchanged. **Pitfall**: BSD `sed -i -E` on macOS treats `-E` as the
  backup suffix and leaves `*.c-E` files in `src_eu/` that the Makefile's `grep GLOBAL_ASM` then picks up (build error "target doesn't match"); use `perl -pi`
  or `sed -i ''  -E`, and `rm conker/src_eu/*-E` if they appear.
- **Own .rodata for `game_eu_1C3530`** (`rodata_split.py --own game_eu_1C3530 --resplit`): `func_15197F7C` matches with string literals. `func_151422C0` (a stub
  returning `(arg3+arg2)>>1`) really takes 6 args (`..., char *file, s32 line`); prototype and definition changed.
- Matched (11): permuter solved `func_150F2F14` (loop limit/arg1 register swap, `new_var = 0x405D`), `func_151CA114`, `func_15156468`, `func_1508B20C`, outright;
  permuter + 1-2 hand edits: `func_1515C3C0` (swap two float copies), `func_1503F7A0` (`s16 sp40[2]`, `(u32)arg0 + D*4` operand order), `func_150C1E78` (load `q` first;
  `t = (v*8) & 0xFFFFFFFFFFFFFFFF` keeps `t` in a temp), `func_150D26DC` (reload the loop-invariant instead of a `temp_f2` local), `func_15034630`/`func_150346A0`
  (`arg0 += 2; arg0[-1] = ...` instead of the permuter's `+= 4; (u8*)arg0 - 2`), plus `func_15197F7C`.
- Permuter on the other 5 untried DIFF<=12 drafts: `func_15031044` nothing, `func_1510B8AC` best DIFF8, `func_1510BB78` DIFF2 by hand (spill slot 0x28 vs 0x2C, stackfix no help),
  `func_150FE1AC` / `func_151BE6E8` (see below). The permuter solved 5 of ~25 raw/hand drafts given (80-150 s, 4-5 jobs); `permute.sh` removes the `nm/<func>` dir
  at the start, so never pass a draft *from* that dir for the same function (SETUP-FAILED).
- New pattern: a copy of `arg0` in `a1` that is **spilled to `0x20(sp)` = the home slot of `a0`** (`func_150FE1AC`, `func_151BE6E8`, frame 0x20): `u8 *p = arg0;`
  gives the copy, but the spill is placed in a fresh local (frame 0x28/0x30). Not solved; `arg0 = p` before the call (SIZE+2) is closest.
- Left: `func_151EF7B0` (4-insn function followed by 16 nops of file padding: apply.py REJECTs on size; needs the padding split into the next file or a no-op filler),
  `func_150E394C` (`extern s32 func_150E394C;` in the same file must be removed first; ref: `lw v0; a0=2; bnez; or a1,v0` reuse not reproduced),
  `func_151B92AC` DIFF12, `func_151B8B5C` DIFF14, `func_1515F5B0` DIFF26, `func_151A0EC0` DIFF13, `func_150848F0` DIFF14, `func_150F2230` DIFF25, `func_15109140`, `func_1512D7A8`,
  `func_15031044`, `func_1510B8AC`. `func_150A7770/ADACC/7EF4`, `func_151F911C/9150` are hand-written asm (not C).

### Next steps (session 21)

- Several short leftovers are `hand-written asm` marked with `/* Handwritten function */`: skip them, they will need `INCLUDE_ASM`-style stubs anyway.
- The `a1 -> 0x20(sp)` spill family (delete handlers with 3-4 `if (f) func(f)`): look for a construct that makes IDO treat the param copy as the param itself.
- Untried from `fresh.txt`: everything above ~17 insns; `gensome.sh` + `permute.sh -l` (80 s, 5 jobs) is a cheap first pass, then hand-fix DIFF<=2.

## Session 22: large functions (70-150 insns) as a byte-percentage experiment

1 work commit (`8fdd85e`) + this hand-off; +4 functions (2959 -> 2963) but **+1,536 bytes** (309,380 -> 310,916), i.e. 384 bytes/function against
78 bytes/function for session 20 (26 functions, 2,032 bytes). Full `verify_all.sh` OK. 28 functions looked at (24 with hand work, the rest permuter only).

### What was done

- Candidates: 885 asm functions of 70-150 insns without jump tables (`tools/eu_port/m2c/all.txt`). `gensome.sh` on all of them (about 8 minutes, 760 got a
  draft; 0 OK): 110 DIFFn, 386 SIZE+-n, 264 CERR. Ranking DIFF/insns: the best were DIFF9 of 97, DIFF9 of 75, DIFF11 of 85, DIFF12 of 91; the SIZE+-1..3 drafts have
  ~25 of them under 130 insns. Raw ranking by DIFF/size is a poor predictor (SIZE-n with n > 3 is just a missing chunk; ignore it).
- Matched (4): `func_1507839C` (97 insns), `func_15121C68` (116), `func_1502B224` (76), `func_15137F30` (97).
- Numbers for the size class (rows 256-282 of `repair_log.tsv`): 27 functions, 32 reasoned rewrite/stackfix attempts, **4 matched (15% of functions, 1 match per
  8 attempts)**; compare cumulative short-function loop (sessions 16-19) 52% of functions, ~2 attempts per match. Permuter: 5 raw m2c drafts (DIFF15-17) at 240 s: 0
  solved; 9 hand-improved drafts at 150 s: 1 solved (`func_1502B224`, from DIFF1), 1 more to DIFF4 on a 147-insn function (`func_151C2600`, then DIFF2 with stackfix).
- **Tokens per byte**: the 4 matches took roughly 10-12 tool calls each including dead ends, ~100 bytes per call, about 3-5 times the bytes per call of a
  short function. Success rate is a third of short functions' though, so expected bytes per attempt is about equal to 1.5-2x of short ones. Recommendation: keep
  spending on the 70-150 class only for drafts with a **small, local diff** (DIFF <= 12 or a single register/operand-order issue); skip the frame-size/stack cases
  (frame 0x58 vs 0x50 etc.), drafts that keep an `arg0` copy spilled into a0's home slot, and anything with float literals in files that do not own `.rodata`.

### New patterns

1. **`a + b*s` in float vector code** (`func_15137F30`): write the product first, `(b*s) + a`; IDO then loads `b` before `a` like the ref (6 lines of one function).
   The same swap on 20 other drafts that contain that shape was screened mechanically: no other function benefited.
2. **A scalar field re-read instead of a temp** (`func_15121C68`): `arg0[0x23E]` in every comparison instead of `u8 temp_v0` removes a `move`; and statement order (`|= 0x80` last in
   its branch) fixed the scheduling of `lw` vs `mtc1`.
3. **Float global array indexed by byte offset** (`func_1507839C`): `*(f32 *)((u8 *)D_800CC2E8 + i * 0x32C)`, not `D[i*0x32C]`.
4. A comma expression `(0, var)` flips the operands of a `beq` (`func_1502B224`, permuter; labelled `// fakematch`). stackfix order + the comma gave the match.
5. Literal floats in files that do not own `.rodata`: replace the one that the asm references by symbol (`extern f32 D_800A4C0C;`, `func_15137F30`); constants that
   are `lui $at` immediates (217.0f etc.) are fine as literals.

### Left (see `repair_log.tsv`)

- `func_151C2600` (147 insns): DIFF2, only the f32 spill slot (0x30 vs 0x34) differs; best is `conker/build/stackfix/func_151C2600/best.c` (wiped by `verify_all.sh`, the
  permuter draft is `tools/decomp-permuter/nm/func_151C2600/best.c` + stackfix order `sp4C,sp48,temp_f0,sp40,temp_v0,temp_v0_2,temp_v1`).
- `func_1000FC18` permuter DIFF7 (limit reload hoisted into a `beql` delay slot), `func_1501A220` permuter DIFF9 (`arg0` copy in `s1` in the `bnez` delay slot), `func_150D368C`
  (frame 0x28 vs 0x20), `func_150E35A0` (object pointer in a1/a2 instead of a0), `func_150F3794` / `func_151D16E8` / `func_10003C10` (arg copy spilled to the a0 home slot family).
- `func_151D5FC8`, `func_151154C4`: global-address/delay-slot shapes; `func_150F83A0`, `func_1510660C`, `func_150FE320`, `func_150FDDA0`: frame size (stackfix best DIFF16-21).
- Drafts for all 760 are in `tools/decomp-permuter/repair/fresh/` (gitignored); the SIZE+-1..3 list is easy to regenerate with `gensome.sh $(...)`.

### Next steps (session 22)

- If tokens are cheap, go through the remaining SIZE+-1..3 drafts of 70-130 insns (`func_150CE710`, `func_150DB858`, `func_151621B8`, `func_15003668`, `func_1519D7B0`, `func_15150258` ...):
  try operand-order variants, the arg-copy patterns above and the permuter with a hand-fixed draft only.
- Otherwise go back to short functions (higher match rate) but prefer ones above 40 insns for bytes.

## Session 23 and Known IDO shapes

2 work commits (`e5241d4`, `270f3d8`) + this hand-off; +8 functions (2963 -> 2971), +1,764 bytes. Full `verify_all.sh` OK.
Matched: `func_150FE1AC`, `func_151BE6E8`, `func_150FE320`, `func_150FDDA0`, `func_150D368C`, `func_151411E4`, `func_15141250`, `func_151C00DC`.
About 25 functions tried; rows in `repair_log.tsv`. New helper: `tools/eu_port/m2c/mine <func> <draft.c>` compiles a draft and prints MY disassembly of
that one function on a single line (`;` separated), next to the screen result; far quicker for shape experiments than reading word diffs.
(It needs the `SCREEN_KEEP` env hook added to `m2c/screen.py`.) Tip: `tryall` runs 8 drafts in parallel, so enumerating 100-1000 mechanical variants
(declaration orders, operand forms) costs only minutes: used for the frame puzzles below.

### Known IDO shapes (recipes and ruled-out hypotheses; do not repeat)

**A. Arg copy in a1/a2/a3 spilled to the a0 home slot (`or a1,a0,zero ... sw a1,0x20(sp)` around calls), delete handlers.** SOLVED for the
`if (p->X) f(p->X); ...` family (`func_150FE1AC`, `func_151BE6E8`):
- Do not copy `arg0` into a named local; use `arg0` itself. Then IDO keeps it in the copy register and spills it to its own home slot.
- Define the second pointer **first, at the top**: `u8 *v = arg0 + 0x110;` (a definition just before its first use is folded into the load offsets
  and `v` then never exists in a register; defined first, IDO rematerialises `addiu v0,a1,0x110` after each reload and spills `v` to 0x18).
- Compare as **pointer-typed field** for the single-load tests (`if (*(struct102 **)(v + 0x28)) f(*(struct102 **)(v + 0x28))` = `lw a0; beqzl a0`),
  but compare as `*(s32 *)` for the double-load tests (`lw t6; beql t6; ... lw a0` again, the first test of those functions). This is the whole difference.
- `func_151411E4`/`func_15141250` (table call `D[u8 field](arg0)`): `if (*(s32 *)((u8 *)arg0 + 0x154) != 0) { f(*(f32 **)((u8 *)arg0 + 0x154), arg0); }` and
  `D_8008A33C[*(u8 *)((u8 *)arg0 + 0x168)](arg0)`; the struct-field version (`arg0->unk110.unk44`) loads once into a2, which is wrong.
  The a1 copy is just the 2nd call argument (`arg0`), nothing exotic.
- `func_151C00DC` (loop over two slots): `arg0` must stay out of the s-regs: the permuter found `new_var = arg0 + 0x28; if (*(s32 *)new_var) ...` then a
  second `v = arg0 + 0x28` for the loop (`// fakematch`).
- NOT solved: `func_150F3794` (frame 0x30 vs 0x28 with identical spill slots; `--bisect` only says the 3-arg call matters; named temps removed, inline
  `temp_f2`, `v`/`t` declaration order: no change), `func_151D16E8` (124 insns), `func_10003C10` (leaf that stores a0 to 0(sp), not attempted).

**B. Frame bigger than the locals explain.**
- Out-parameter locals are 12-byte vectors: `s32 spA8[3]` etc., not `s32 spA8` (`func_150FE320`, `func_150FDDA0`, same template; frame 0xB8/0xC0).
- **Named locals take stack slots even when unused; unnamed spill temps (e.g. an `f32` result that survives two later calls) go below the named ones.**
  Do not give the spilled float results a name: put the calls inline in the argument list (`(func_150ADA68() * 10.0f) + 25.0f, ...`; IDO evaluates left to right).
  Then one unused `s32 pad;` declared **first** moves those temps to the ref offsets (0x78/0x7C). Labelled `// fakematch`. Found by brute-forcing
  declaration orders (5040 + 1680 permutations with `tryall`); `stackfix.py` alone only got DIFF2/DIFF3.
- A `var = 0;` default set before a call that returns (e.g. `var_v0 = 0` before `sinf`) is live across the call and grows the frame by 8: set it after
  the calls (`func_150D368C`, frame 0x28 -> 0x20), or return constants from the branches.
- `func_150ADA20` returned `u8` in `functions.h`: every use that is kept across a branch got `andi v1,v0,0xFF` where the ref has `or v1,v0,zero`. Changed the
  prototype to `s32` (the whole build still matches); 189 call sites.
- Float expression order (`func_150D368C`): `a + (b * sinf(x))` for one statement and `(b * sinf(y)) + a` for another were needed, found by trying the 16 combinations
  with `tryall`; the last `mul.s` operand order came from the permuter.
- Not solved: `func_150F83A0` (DIFF6: spill slot 0x18 vs 0x1C, `s32 pad` first/last no help, permuter best in `nm/`), `func_1514E014` (DIFF2: `sp24` spill
  at 0x24 vs 0x18: the ref keeps a real named local above the array; 168 declaration/pad orders tried; the 2-word `sp1C[2]` array is needed for the two zero stores),
  `func_1510660C` (frame 0x38 vs 0x30, nonstack diff 17; stackfix no help), `func_150F2910` (`buf[12]` fixes the frame; K&R definition `f(a,b,c) u8 *a; u8 b; s32 c;`
  makes IDO store all three args like the ref, but `lbu a2,0x2F(sp)` is hoisted above `sw ra` instead of sitting in the `jal` delay slot).

**C. Reload from home slot / `b L; lw ra` / `beqz; nop` (4-arg handlers).** PARTLY SOLVED in session 26 (see the "Session 26" section for the
recipes; the original notes follow). Hypotheses ruled out for `func_150C5060`:
- `-O1`, `-O3`, `-g3` flags (all give `s0 = arg0` instead of memory args), `volatile` params, an extra unused 4th param, switch instead of if-chain, K&R definition
  (arg0 goes to s0 unless its address is taken), separate pointer locals per branch, hoisting the `arg0` load above the first compare.
- Taking the address `*(u8 **)&arg0` (as `func_150D380C`) gives the memory form (all args stored at entry, each use reloads). The permuter (150 + 240 s) then found
  `u8 **new_var = &arg0, **new_var2 = &arg0;` used in the branches, which fixes all registers (a2 for `p`, t0 for the else-branch copy); DIFF2 left: `p += 0x28; p[0x16] = p[0x3E]...`
  loads `0x66` where the ref loads `0x3E(a2)` before the `addiu`. Best draft is in `tools/decomp-permuter/nm/func_150C5060/best.c` (regenerate with
  `permute.sh func_150C5060 <draft>`; the draft is the session-22 one with `&arg0` in every branch). Using a temp `t = p[0x3E] & 0xFFFD` before `p += 0x28` (the natural form) changes the registers again (12 variants tried).
- `func_150F1B78`, `func_150F7890`, `func_151007B0`, `func_151D7AE8`, `func_150C62C0`, `func_150C6BF0`, `func_151095E4`, `func_1514F3E0`: not retried, same template.
  `func_150C6BF0`: the `sb` sits before `b L` while `lw ra` is in its delay slot (epilogue instruction hoisted by the scheduler); source variants unchanged.
- Permuter note: it returns NOSYM on K&R definitions; give it the ANSI form.

**C, session 27 additions (confirmed / ruled out).**
- CONFIRMED: `u8 **q = &arg0;` is only needed when the ref reloads arg0 in every block; a plain 1-arg function with an `sw a0,N(sp)` entry spill that
  reloads `lw a0` after a call is normal (value live across a call, no s-reg): do not add `q` there (`func_15160134`: plain locals; `func_1515D9F0` needed `s32 *q = &arg0`).
- CONFIRMED: `volatile` on exactly the parameter that the ref stores at entry *and* reloads (`volatile s32 arg3` in `func_15047978`: `sw a3,0x7C; lw a3,0x7C`;
  `volatile u8 arg2` in `func_1519E92C`: `lbu` reload after each call) gives the byte-exact result. Try it per parameter, one at a time (`volatile s32 arg3` alone, not all).
- CONFIRMED: **dispatch template** `switch (probe(a0, a2, a3)) { case 0: return g(a0, a1, a2, a3); case 1: return 0; case 2: return 1; }` (no default, no return after) gives
  `beqz; li at,1; beq; li at,2; beql ...; b end`. An if-chain gives `bnez/bnel` (DIFF20). 5 members: `func_15046F70`, `func_15045AF0`, `func_15047274`, `func_15046EF0`, `func_150455FC`.
  Their callee `func_15045A70` / `func_150473A0` is already C with an `f32` 3rd/2nd parameter, so the whole family takes `f32 arg2` and the file header got prototypes
  (`s32 func_150472F4(u8 *, f32, u8 *);` etc.): an unprototyped K&R call would promote the f32 to double.
- CONFIRMED: particle-spawner template `s8 sp18[8]; ... *(s16 *)(sp18 + 2) = rand() % N + K; sp18[5] = 1 << (*(u8 **)(arg0 + 0x318))[0x23D]; ... func_151D8E18(sp18, 0, 0xFF, 1)`:
  `sp18[6] = -1` needs `s8` (a `u8` array gives `li 255`). 4 members matched first try: `func_150FED54`, `func_151001BC`, `func_150FE808`, `func_151C1FB8`
  (`func_1519A1A4`, `func_151C62D0`, `func_151C8F4C` also call `func_151D8E18` but are large).
- CONFIRMED: `x * y + z` operand forms: 16 combinations with `m2c/mine` found them (`func_151B9204`: DIFF14 -> OK with a `s32 pad;` declared first moving the spill to 0x18).
- RULED OUT for the `func_150F1B78` family (arg1 loaded twice, 2nd `lw` hoisted above the `beq`): `q1 = &arg1` and `*q1` uses are folded away (output identical to plain arg1);
  `s32 *arg1` / compare order / `!=` forms: identical output. Best is `q = &arg0; u8 *volatile arg1; volatile u8 arg2; a = *(s32 *)arg1; p = *q + 0x28; t = arg1; if ((a == *(s32 *)p) || (p[4] == t[4]))`
  = DIFF6 (register numbering only: ref uses t0 for the hoisted reload, mine v1; mine allocates arg0's temp t1 where the ref has t2). `func_150F7890` (loads the `p` side first) best DIFF6 with
  `*(s32 *)p == *(s32 *)arg1` but the arg1 reload stays after the beq. Permuter (90-100 s each) found nothing better. The family is still open; `func_150AEDF8` not retried.
- A callee that the *same file* calls implicitly before its definition (`func_15199EF0`, `func_1518FE50`, `func_1519E688`) makes every draft CERR (`redeclaration`): put a forward prototype in the draft
  (or in the file above the first caller; for a `void` function use `void f(void *)`), do not change the draft body.
- A wrong `void` prototype in `functions.h` hides a return value the ref uses (`func_1513EDE4` -> `s32` with `return func_1513EAD8(...)`, build unchanged).
- Call arity: `func_150473A0` was a "shape C" only because the callee has 5 params (stale a1): count `a0..a3 + stack` writes in the ref before anything exotic.

**D. `store; jr ra; nop` (unfilled return slot) in 2-case u8 handlers** (`func_151AEBF0` and 6 more). Not solved. New information:
- All registers and everything else match once the loaded value is a **single shared variable** `a = *(s32 *)arg1;` assigned inside both arms
  (`if (t == 0) { a = ...; if (a == arg0->x) {store} return; } if (t == 0x2D) { a = ...; b = ...; ...}`); `func_151AEBF0` then differs only in that arm 1 ends
  `jr ra; sw zero,0x44(a0)` (filled) instead of `sw zero,0x44(a0); jr ra; nop`.
- Ruled out for the unfilled slot: `return;` in the arm or not, `goto done`, empty `else {}`, `s32` return type, K&R definition, switch, -O2/-O3/-g variants.
  Probably a structure that only exists in the original source (an instruction after the store that the compiler deleted), not a flag.

### Next steps (session 23)

- Finish the near misses with a documented residue: `func_150C5060` (DIFF2, see C), `func_150F83A0` (DIFF6), `func_1514E014` (DIFF2), `func_150F2910` (DIFF8).
- Apply recipe A to other "arg0 copy in a1/a2" functions of the list produced by grepping `asm/nonmatchings` for `or $aN, $a0, $zero` + `sw $aN, 0x18/0x20($sp)`
  (about 20 below 60 insns, e.g. `func_15183EE4`, `func_151AB06C`, `func_1518AF80`); recipe B (arrays, unnamed temps, pad first) for the other frame-size cases.
- Always try `m2c/mine` + 10-20 mechanical variants through `tryall` before the permuter; the permuter found the last step of 2 of the 8 matches.

## Session 24: shapes.py and family-wide recipes

2 work commits (`27e612a` + the batch of 5 in the hand-off commit) + hand-off; +20 functions (2971 -> 2991), +3,600 bytes. Full `verify_all.sh` OK.
About 33 functions looked at; rows in `repair_log.tsv`.

### New tools

- `tools/eu_port/shapes.py` scans the asm of every function still in GLOBAL_ASM and tags the known shapes (A arg-copy spilled to the a0 home slot,
  B out-parameter vectors `x[3]`, C reload from home slot, D unfilled `store; jr ra; nop`). `shapes.py` prints counts per shape and size bucket;
  `shapes.py --list A 100` lists the tagged functions up to 100 insns, smallest first. Heuristics only (B is loose: any two `addiu aN,sp,X` 12 apart in a
  frame >= 0x20, so most >150 hits are noise; A needs `or aN,a0,zero` + `sw aN,<frame>(sp)`).
- `tools/eu_port/sh.sh <func>`: the asm on one line plus the gensome draft (use it instead of reading the .s).
- Workflow that worked: `gensome.sh ${=LIST}` (zsh needs `${=...}` to split a variable; a plain `$L` passes one word and the run finishes in 2 s with one CERR),
  `m2c/mine func draft.c` to see my asm, stackfix for slot-only diffs, `repair_try.sh` to keep an OK draft, `apply.py build/hand` (reset `build/hand/screen.txt`
  to only the new OK rows first, and do not `rm` the hand files before apply), `permute.sh -l list 120 8` for DIFF<=8 leftovers.

### Counts of the still-open shapes (live GLOBAL_ASM functions, 2876 at the start of the session, 2856 at the end)

| shape | <=20 | 21-40 | 41-60 | 61-100 | 101-150 | >150 | total (start) |
|---|---|---|---|---|---|---|---|
| A arg copy spilled | 0 | 10 | 18 | 28 | 18 | 28 | 102 |
| B out-param `x[3]` | 0 | 4 | 17 | 18 | 33 | 156 | 228 |
| C reload from home slot | 5 | 49 | 80 | 86 | 75 | 147 | 442 |
| D unfilled `store; jr ra; nop` | 16 | 58 | 46 | 37 | 14 | 5 | 176 |
| all functions | 79 | 301 | 424 | 566 | 495 | 1011 | 2876 |

After the session A has 95, B 215, C 430, D 176 left (C and D untouched).

### Hit rate

- Shape A (<=100 insns, smallest first): 15 tried or looked at, **8 matched** (`func_1518AF80`, `func_150D0544`, `func_150D03A8`, `func_1519F970`, `func_1511ACC0`, `func_151A5620`,
  `func_1503F1B0`, plus `func_150F0718` which is a B/A mix); failed: `func_15190A2C`, `func_151AB06C`, `func_15183EE4` (DIFF4), `func_151321F4` (DIFF3), `func_1510DD2C`;
  skipped without trying (float literals in a file without .rodata, or m2c draft too far off): `func_151220D0`, `func_151CCD2C`, `func_151AF820`.
- Shape B (<=100 insns): 16 tried, **13 matched** (`func_150F2230`, `func_150F9ED0`, `func_1506AB5C`, `func_1506AD28`, `func_1515A120`, and the 7-function template family `func_151D44C4`,
  `func_151D45A4`, `func_151C09C8`, `func_151C1E10`, `func_150B64E0`, `func_151C5C54`, `func_151BC494`); failed `func_1506AC24` (float literals + slot offsets), skipped `func_1514F878`
  (string rodata), `func_151AFA80` (rodata floats).
- Overall for these two shapes: 20 of about 31 tried (65%), well above the 52% of the short-function loop. The family templates (7 siblings from one solved case, 1 attempt each) carry a good part of it.

### Recipe refinements

1. **Recipe B, the data-structure form.** When an m2c draft has `sp48`, `sp49`, `sp4A`, `sp4C` byte/half locals followed by `sp3C/sp40/sp44` s32s that are passed by address
   (`func_151602C0((Header *)&sp48, (Header2 *)&sp3C, ...)`), write `s8 sp48[8]; s32 sp3C[3];` and `*(s16 *)(sp48 + 2) = ...`, `sp48[4] = 0;`. This matched at the first try for seven
   functions (all "particle spawner" bodies, only constants differ: `% N + K`, colours). See `/tmp`-style generator idea: a 10-line python script that regexes the draft constants into the template.
2. **Frame bigger than the vectors (`func_150F9ED0`, frame 0xA8):** `s32 pad[15];` declared first (fakematch) puts the five 12-byte vectors at the ref offsets; then stackfix order search finishes the
   spill slots, and the last diff was an operand order (`(x << 6) + y` not `y + (x << 6)`). Size the pad as (ref frame - highest used offset) / 4.
3. **Missing callee argument = stale register.** Several drafts failed because m2c invented arguments (`func_15183EE4`, `func_1511ACC0`, `func_150D03A8`): if the asm sets no register for an
   argument, call with fewer args (the stale value in a1 is the arg0 copy). A handler stored as 3-arg in a table that only reads a0 must be declared 1-arg for the C to spill like the ref
   (`func_150D03A8`; the file's prototype and its one caller were changed, whole build still matches).
4. **Recipe A extra:** a table call whose index byte is read twice (`lb t6,0x4C(a1)` for the compare, `lb t7,0x4C(a1)` again for the index after the spills): the second read as
   `*(volatile s8 *)` (fakematch, `func_150D0544`). The first test of a `lw t6; beqz; or a0,t6` double-load is a `*(s32 *)` compare followed by passing `*(u8 **)` of the same field;
   subsequent single-load tests are pointer-typed. A callee prototype `(u8 *)` instead of `(s32)` was needed for `lw a0,..; beql a0` in `func_1519F970`.
5. **A 4-byte stack argument off by one slot** (`func_1515A120`: `lw t6,0x48(sp)`): float arguments take a0..a3 slots, so add dummy `s32 arg4, s32 arg5` parameters.
6. **No sign extension of a halfword result:** use `s32 temp` for `lh x; subu; sh x` (no `sll/sra`) (`func_1503F1B0`); the last step was permuter (split `temp = load; temp = temp - D;`, fakematch).
7. stackfix does help for A-shape near misses: `func_1518AF80` (DIFF2 -> OK by declaration order `n,a2,h,k`) and `func_150F0718` (`r,sp4C,sp40,sp3C,sp54`). It did not help `func_15183EE4`
   (needs a named local at 0x18 so the unnamed `v0` spill lands at 0x1C; pads go above, not below), nor frame-size cases.
8. Callee prototype conflicts when screening: a file-local `void f(s16 *);` conflicts with a draft that calls with more args; temporarily change the file's declaration to `void f();` or
   drop the draft's own prototype for functions the file already calls implicitly (`func_1511AA1C`). `func_10004074` has three different local prototypes in three files.

### Left

- A: `func_15190A2C` (v = arg0+0x30 is folded instead of kept in `t7` and spilled to 0x18; frame 0x18 vs 0x20; 8 variants), `func_151AB06C` (frame 0x28 vs 0x30, `(x+0x80)+4` folded),
  `func_15183EE4` (DIFF4 slots), `func_151321F4` (DIFF3, sum temp in t0 not a0), `func_1510DD2C` (frame 0x30 vs 0x28 with 4 named locals), `func_150F3794`, `func_1514E014` (older).
- B: `func_1506AC24` (+4 slot shift and float-literal scheduling), `func_151AFA80`, `func_1514F878`, `func_151CCD2C`, `func_151220D0` (rodata floats; need the `extern f32 D_...` form).
- The remaining A (95) and B (215) functions above 100 insns were not touched; the 101-150 bucket of A has 18, B 33.
- C and D (430 and 176 functions) are still open; sessions 23 notes still apply.

### Next steps (session 24)

- Run the same A/B recipes on the 101-150 insn functions of `shapes.py --list A 150` / `--list B 150` (expected hit rate lower, bytes per function higher).
- Look for more "templates": functions whose drafts differ only in constants (the 7-function family above); group `gensome` drafts by their normalised text to find them.
- Shapes C and D remain the biggest pools (430 + 176); D is mostly 2-case u8 handlers (see session 23 section D).

## Session 25: clones.py (template families)

2 work commits (`b59b0cc` + the batch in the hand-off commit) + hand-off. +35 functions (2991 -> 3026), +10,388 bytes. Full `verify_all.sh` OK. Tools: `tools/eu_port/clones.py`.
About 41 functions tried (35 matched); rows in `repair_log.tsv` (start bucket `CLONE` for clone drafts).

### clones.py

- `clones.py` (report): objdump of every `conker/build/src_eu/*.o` (one docker exec, cached in `conker/build/clones.dump`; `--refresh` after a build that
  changed the live set) -> per function a skeleton = opcode + registers per instruction, immediates / branch targets / reloc symbols abstracted
  (sp offsets and `addiu sp/aN,sp,K` kept). Prints (a) asm-only clusters, (b) GLOBAL_ASM functions whose skeleton equals a matched C function.
  `--min N` (default 6 insns), `--top K`. Loosening the skeleton (register renaming, sp offsets dropped) gave the identical clusters, so the
  strict one is enough: template families are rare in this ROM.
- `clones.py --draft [--lax] [--per K]` writes `conker/build/cl/v0..` drafts (+ `clones.txt` with `asm <- sibling status`), by copying the C sibling and substituting
  aligned immediate / reloc differences (literal 17 -> 33, `unk3C` -> `unk4C` field names, data symbols with their `extern`, callee prototypes copied from the sibling file).
  Then `m2c/screenall build/cl` and the normal `keep` / `apply.py` flow. `--lax` keeps the sibling's own data-symbol names (aliases of the same address link
  identically) and ignores addend immediates: the screen reports those as DIFFn (names differ) although the linked bytes match, so apply them with a hand dir whose
  `screen.txt` has fake `OK` rows: `apply.py` byte-checks the whole file and REJECTs the bad ones (used for 5 libultra copies).
- `clones.py --asm-clusters` lists asm-only clusters (smallest member first) for solving one and cloning to the rest.

### Statistics (start of session, 2857 GLOBAL_ASM functions, 5641 functions in objects, skeleton >= 6 insns)

- (a) asm-only clusters (>= 2 members): 67 clusters, 161 functions. Sizes: 2 members x 53, 3 x 7, 4 x 4, 5 x 2, 8 x 1. Biggest by bytes are pairs of huge functions
  (`func_151B6ED8`/`func_151BD040` 483 insns, `func_160021FC`/`func_10002718` 420, `func_16001BB4`/`func_100020D0` 402: the 16xxxxxx overlay copy against the init copy).
  After the session: `func_150AEDF8` x 8 (43 insns, 2-case u8 handler, shape C, see below), `func_1500B8F4` x 3 (113 insns), `func_151AB954` x 3 (197 insns).
- (b) GLOBAL_ASM functions with a matched C sibling: **33 functions in 28 clusters, 10,388 bytes** (most are the second copy of libultra in the game segment).
- Clone hit rate: of the 33 type-(b) candidates **30 matched** (91%); 11 straight from the generated draft (6 screened OK, 5 libultra with `--lax` link-check),
  19 after a small hand fix: -O1 for the libultra files, a `controller.h` include / forward prototype, a struct-typed draft rewritten with `u8 *arg0` raw offsets
  (field names of another struct), float literals, a 64-bit global kept as one symbol, `* 8` -> `* 32` (the `sll` amount is not a literal in the C).
  Not matched: `func_151EF850` (osContInit, SIZE-22), `func_151F0260` (osContStartReadData), `func_10001AA8` (369 insns, other segment's types).
- asm-only: solved `func_151B0454` (106 insns) by hand and cloned: 4 of 4 siblings matched at the first screen.
- Bytes: the game copy of libultra pfs code (`game_eu_21E520`, 8 functions, ~1,900 insns) was a verbatim copy of `init_eu_27C40.c`.

### Findings

- **The game segment has a second copy of libultra built -O1.** `game_eu_21D060`, `21D420`, `21D990`, `21DA70`, `21E490`, `21E520`, `220050`, `220400` got `OPT_FLAGS := -O1`
  in `conker/Makefile` (like `21E320`/`21D010` already had), and `#include "controller.h"`. Check the neighbours (`21D010`..`2205xx`) for the same when more of them show up.
  Names of data symbols differ between the copies (`__osPfsPifRam` / `D_80042D60`) but link to the same addresses; `D_80042D44` is the low word of the 64-bit
  `D_80042D40` (`func_151F0C80`: the C keeps `extern OSTime D_80042D40`).
- **IDO unrolls `for (i = n; i != 0; i--)` at -O2** when the body only uses a hoisted pointer: `f32 *p = (f32 *)(arg0 + 0xA8); for (i = D_800BE9E4; i != 0; i--) { *(f32 *)(arg0 + 0x58) *= *p; *(f32 *)(arg0 + 0x60) *= *p; }`
  gives the 4x unrolled loop with remainder prologue of `func_151B0454` (`i = 0; i < n` forms are not unrolled).
- A clone target whose callee is defined later in the file needs a forward prototype in the draft (`func_151985C4`), and a function first called implicitly in its own
  file needs a prototype at the top of the file (`func_15147ECC`, `func_15157734`, `func_15158F90`; the callers pass `void *`).

### Not solved

- `func_150AEDF8` family (8 members: `func_150CEBA4`, `func_150D7370`, `func_150D7578`, `func_151937A4`, `func_15193850`, `func_151B255C`, `func_151BEB08`): same body as the matched
  `func_151985C4` but with the `arg2 == 0x2D` arm first. Draft with `u8 *v = arg0 + 0x28` at the top gets DIFF21 only because the 0x2D arm ends `sb; b L; lw ra` (epilogue
  load in the branch delay slot) where mine puts the `sb` in the delay slot: shape C/D again. Variants tried: return in arm, nested else, inverted condition; permuter 150 s (see `nm/func_150AEDF8`).
- `func_1500B8F4` family (3 x 113 insns, float interpolation), `func_151AB954` family (3 x 197): not attempted.

### Next steps (session 25)

- Rerun `clones.py --refresh --draft --lax` after every batch (new C functions create new siblings; the 4 clones of `func_151B0454` came exactly that way).
- Solve one member of each asm-only pair cluster with <= 150 insns, then clone (list: `clones.py --asm-clusters`).
- Shapes A/B in the 101-150 bucket (session 24 next steps) were not touched this session.

## Session 26: shape C hypotheses, recipes

2 work commits (`d257144` + the batch in the hand-off commit) + hand-off; +13 functions (3026 -> 3039), +1,448 bytes. Full `verify_all.sh` OK.
About 30 functions looked at (13 matched); rows in `repair_log.tsv`. `clones.py --refresh --draft --lax` found nothing new (the 2 candidates are the
known failures `func_10001AA8`, `func_151EF850`).
Matched: `func_150C5060`, `func_150C62C0`, `func_150C6BF0`, `func_1519F928`, `func_15173298`, `func_150B00D4`, `func_15157E08`, `func_1514DFA8`,
`func_1514DEE8`, `func_1510B8AC`, `func_151968A0`, `func_15196924`, `func_151AE61C`.
Helper used (not committed, 20 lines): a "compile this draft with SCREEN_OPT=<flags> and print my asm" wrapper around `screen.py` (the `mine` script
does not pass `SCREEN_OPT` through; `docker exec -e SCREEN_OPT=...` is all it takes).

### Shape C hypotheses (confirmed / ruled out)

- **CONFIRMED: address-taken `arg0` via a pointer local** fixes `func_150C5060` completely:
  `u8 **q = &arg0;` (label `// fakematch`) and then `p = *q + 0x28; p[0x16] = p[0x16] & 0xFFFD;` in each branch, `*q` for every other use of `arg0`.
  The permuter's `p += 0x28; p[0x16] = p[0x3E]...` was a *wrong semantic* (0x66 load); the natural un-hoisted `p[0x16]` form compiles to the ref's
  `lbu 0x3E(a2); addiu a2,a2,0x28; sb 0x16(a2)`. It must be a real `*q` use: `*(&arg0)` is folded away (s0 form), an unused `q`, `volatile u8 *arg0` (pointee
  volatile), or passing `&arg0` to a dummy callee all fail.
- **CONFIRMED: `b L; lw ra` vs `sb` in the delay slot** (`func_150C6BF0`, `func_150C62C0`): write `if (x) { ... } else { ... }` and NOT `if (x) { ...; return; }`.
  With the early `return` the scheduler puts the `sb` into the `b` delay slot; with if/else the `sb` stays before `b` and the epilogue `lw ra` takes the slot.
  (Also needed: `u8 *p = *(u8 **)(arg0 + 0x6C); p += 0xB0; p[4] = 1;` instead of `*(s8 *)(x + 0xB0 + 4)` to get the separate `addiu`.)
- **RULED OUT as a general cause: per-function flags.** `-O0`, `-g`, `-O1`, `-O2`, `-O2 -g`(= `-g`), `-O3` on the plain draft of `func_150C5060` all give wrong sizes.
  `-O1` is the only one with the right frame size (0x20) and memory args, but it never fills delay slots (`bne; nop`), spills named locals (`p` to 0x24(sp))
  and has no `bnel`/`lw ra` in slots, so no EU file boundary is implied. `-g` alone is `-O0` (everything via `sw`/`lw`, no scheduling).
- **Partly useful: `volatile` parameters** (`s32 * volatile arg1`, `volatile u8 arg2`) make IDO reload that param at every use *and* store a0..a2 at entry like the
  ref. For the `func_150F1B78` family (below) `q = &arg0` + `volatile arg1/arg2` gets DIFF13. A `volatile` arg0 is wrong (no hoisted `lw t3,0x20(sp)`).
- Not tried: a struct parameter passed by value.
- A shape-C-looking function is often just a 1-arg function with unprototyped/missing call arguments: `func_15173298` (`f(arg0, arg1, 1)` with the stale a1 as an
  unused 2nd parameter), `func_1519F928` (`f(arg0, 6)`: m2c dropped arg0), `func_15157E08` (callee prototype with an `f32` 3rd parameter gives `mtc1 a3,f12; mfc1 a2,f12`
  and a0 passthrough). Check call arities before anything exotic.

### Other findings

- Float operand order: `a*b + c` in source can come out as `add.s c,(a*b)`; try the 4 forms. `func_150B00D4`: `x*y + z` for the first, `v[0] + v[4] * sinf()` for the
  last; and no named `f32` temp (a named float local grew the frame by 8).
- Local-array + pointer spill order: `s32 buf[7]; u8 *r;` puts `r` BELOW buf; declare `u8 *r;` first to get `r` at the higher slot (`func_1514DFA8`), buf first for
  the other (`func_1514DEE8`, 8-word `f32 buf[8]` with `buf[4] = 12.0f`). `stackfix.py` found the `sp1F,a,sp1E` order for `func_151AE61C` in 31 candidates.
- `f32` parameters after an `s32` one are passed in a1..a3 and stored/reloaded by `lw`/`lwc1` (`func_1510B8AC`): declare them `f32`, struct of three `f32`.
- A table call `D[i](arg0)` with `s8 i = o[0x65]` and `arg0` kept in memory came out right on the first try (`func_151968A0`, clone `func_15196924`).

### Not solved (shape C), with the closest drafts

- **`func_150AEDF8` family (8) + `func_150F1B78` family** (`func_150F1B78`, `func_150F7890`, `func_151007B0`, `func_151D7AE8`, `func_151BE65C`, probably more `func_150F`/`func_151F`:
  grep for `jal func_1516972C` after `sw $a2, 0x28($sp)`). Constants differ only (`0x43/0x3E/0x48/0x3D/0x3B`, field 0x28/0x40, callee `func_15149514`/`func_15169850`).
  Best: `u8 **q = &arg0; s32 * volatile arg1; volatile u8 arg2`, per-branch `p = *q + 0x28;` -> DIFF13: the ref loads `arg1` twice and hoists the 2nd `lw` above the `beq`
  (uopt does not CSE `arg1` across the `||` block boundary in the ref; it does in every variant of mine, including `&arg1` locals), and compares `p[0]`-side operand
  second. For `func_150AEDF8` itself (`arg2 == 0x2D` arm first) best.c is DIFF6: the only difference is the `arg1[0]` load order/register in the `arg2 == 0` arm.
- `func_151016C8` (DIFF13): first `if (*(T **)(arg0+0x138)) f(that)` needs `lw t7` + `or a0,t7,zero` (ref) vs my `lw a1/v0` + `move a0`.
- `func_15116690` (ref reuses `a1` as the temp for `*(arg0+0x3C)`: an unused 2nd parameter reassigned; the implicit 1-arg call in `game_eu_142E40.c:226` forbids a 2-arg definition).
- `func_151A8B34` / `func_151A8B84` (twins): ref spills `a0` in the delay slot of each call (`jalr` and the next `jal`), mine stores it at entry once there are 3 calls (with 2 calls it matches).
- `func_150C1B60` (ref stores only a2/a3 home slots, reloads a2), `func_151DDA10` (DIFF11, libultra-ish `__osSiGetAccess`), `func_150639D8`, `func_1511645C`.

### Next steps (session 26)

- Shape C is not one thing: the cheap wins were (1) `&arg0` through `*q`, (2) if/else instead of early return, (3) fix call arities. Run those three on `shapes.py --list C 60`
  (about 20 of the 60 smallest were looked at), with `gensome.sh` for drafts; most CERRs there are prototype conflicts (add a forward prototype in the draft).
- Solve the `func_150F1B78` family arg1-double-load problem (5+ members): try `arg1` as `s32 arg1[]` / struct pointer, or `||` written with the byte compare first and `goto`.
- Shapes A/B in the 101-150 bucket were not touched.

## Session 27: shape C family hypotheses, recipes over `shapes.py --list C 60`

2 work commits (`e737c24`, `78c945e`) + hand-off; +20 functions (3039 -> 3059), +2,708 bytes. Full `verify_all.sh` OK.
About 36 functions tried (20 matched); rows in `repair_log.tsv`.
Matched: `func_150FED54`, `func_151001BC`, `func_150FE808`, `func_151C1FB8` (spawner template), `func_151B9204`, `func_150473A0`, `func_1515D9F0`, `func_15160134`, `func_151A7118` (clone),
`func_1503F6F4`, `func_15047978`, `func_15046F70`, `func_15045AF0`, `func_15047274`, `func_15046EF0`, `func_150455FC` (dispatch template), `func_15199EF0`, `func_151A0F5C`,
`func_1519E92C`, `func_150FE120`.
Tool: `m2c/mine` now passes `SCREEN_OPT` through (`SCREEN_OPT="-O1" m2c/mine func draft.c`). `clones.py --refresh --draft --lax` at the end: only the known failures
(`func_10001AA8`, `func_151EF850`); new siblings of the dispatch/spawner templates are not exact-skeleton clones (constants/regs differ), so they had to be done by hand.
Findings are in "Known IDO shapes" (C, session 27 additions).

### Not solved
- `func_150F1B78` family (DIFF6, see Known IDO shapes), `func_150AEDF8` family untouched this session.
- `func_150C7E68` (DIFF11; ref loads `lh` and does `addiu` on the global pointer before the `if (v)`, returns stale v0), `func_1517F910` (DIFF21: ref passes the call result unmasked and
  hoists `lw a0`/`lw v1` above the branch; needs `u8` return for an implicitly-declared callee), `func_151640C0` (DIFF11), `func_1518FD34` (DIFF31: `v = arg0 + 0x30` is defined after the first call
  in the ref), `func_15167B44` (DIFF15: v0/v1 roles swapped, `s32 temp_a1`), `func_150CB5E0` (ref keeps arg0 in `s0`, IDO does not).
- Skipped: `func_1000CDA0`, `func_1516AAA8` (15-arg float call), `func_150FF1A8` (float literals without .rodata). C 61-100 was only scanned (24 drafts generated, 3 tried): most of those are > 60 insns of float code.

### Next steps (session 27)
- C 61-100: the SIZE+-1 drafts (`func_15167B44`, `func_1516AAA8`, `func_151B97C4`, `func_1000E46C`) and the CERRs that only need a forward prototype.
- Look for more "templates" by hand (dispatch `switch(probe) {0,1,2}`, `s8 spNN[8]` spawners): grep asm for `beqz $v0; ...; addiu $at,$zero,1; beq $v0,$at; addiu $at,$zero,2; beql $v0,$at`.
- `func_150F1B78` family: permuter with `volatile arg1` base and a `t = arg1` temp, longer than 100 s, or matching the hoisted-load register by splitting the condition in a nested `if`.

## Session 28: clones.py --near, permuter on the func_150F1B78 family

2 commits (work commit `18922a7` + the batch of 3 in the hand-off commit) + hand-off; +12 functions (3059 -> 3071), about 40 functions looked at. Rows in `repair_log.tsv` (start bucket `NEARn` = skeleton distance).
Matched: `func_150C5970`, `func_150C59C0` (table dispatch pair), `func_150C620C`, `func_1519EAE0`, `func_151AC304`, `func_151A5338` (the `arg2 == 0` first handler family, template `func_1513E084`),
`func_151C6424`, `func_151C8C24`, `func_151C9CBC`, `func_150472F4`, `func_15083FB0`, `func_151B27DC`.

### clones.py --near K (fuzzy mode)

`clones.py --near K [--maxlen N=200] [--only f1,f2] [--draft [DIR=conker/build/nr]] [--lax]`: for every GLOBAL_ASM function without an exact skeleton sibling, the closest matched C function by banded
edit distance over the skeleton lines (insert / delete / substitute = 1 edit; a register difference counts as an edit, because registers are part of the skeleton). Prefilter: multiset difference of skeleton lines <= K.
`--draft` writes `DIR/v0/<func>.c` from the sibling (same substitutions as the exact mode, applied only to aligned instruction pairs with the same opcode) with a first-line comment
`/* NEAR d from <sibling>: <edit list> */` (the edit list is the quickest way to see what the hand fix must change). Screen with `m2c/screenall build/nr`. About 11 s per run.
Statistics (2,8xx GLOBAL_ASM functions, skeleton >= 6 insns, <= 200): functions with a sibling within K edits / bytes:
K=2: 4 / 420; K=4: 10 / 776; K=8: 38 / 2,996; K=12: 72 / 5,444; K=16: 118 / 9,764 (distances 1..5: 3,1,3,3,8; 6: 12; 9: 10; 12: 13).
Screen of the K=12 drafts (67 written): 0 OK straight away, 2 DIFF3, 27 CERR (mostly missing extern types, prototypes), the rest SIZE/DIFF. The pairs found were true near-templates:
a table-dispatch pair (`lw` -> `lbu`, other table symbol and size), the `func_1513E084` handler family (members that differ in the first compare, +extra store), `f32` compare-order swaps, a 3-line wrapper.
Of the 15 hand-finished, 12 matched (80%). Hand fixes needed each time: externs / array types for data symbols (`D_80088B60` in variables.h became `void (*[2])(void)`), a forward prototype when the file calls the
callee implicitly earlier (CERR `redeclaration`), compare order, `s32` instead of `u8` parameter when the ref has no `andi`.

### Findings
- Handler family `func_150C620C` (arg2 == 0 arm first, then 0x2D): copy of `func_1513E084` with `if (arg2 == 0) {...} else { v = arg0 + K; if (arg2 == 0x2D) {...} }`; in the 0x2D arm the compares are `arg1[0] == *(s32 *)v`, `arg1[1] == *(s32 *)v`
  (compare order from the ref `bnel $v1,$a0`). Offset 0xC8 or 0x28. Not matching: `func_1519ED88` (same plus `D_800E0D50 = 0;` after the call: mine puts the `sw` in the `b` delay slot, ref has `sw; b; lw ra`; volatile / return / else-split variants no help, DIFF26).
- `func_150F1B78` family: permuter 700 s with -j4 from the session 27 DIFF6 drafts (`func_150F1B78`, `func_150F7890`): best score 35 / 53, `try` DIFF6 / DIFF8, no improvement. Still open. The `func_150AEDF8` family was not touched.
- C 61-100: gensome on the 76 unlogged functions: 25 CERR, 0 DIFF below 23; the SIZE-1 ones (`func_15095B70`, `func_151166FC`, `func_1519F500`) are float code with rodata; not pursued. `func_151E8998` (one `lui` shared by four stores to
  D_800E0FD0..FDC) and `func_151F0730` (`memcpy(a,b,n) + n`, ref stores a2 in the jal delay slot) are SIZE+1.

### Next steps (session 28)
- `clones.py --near 12 --lax --draft` after each batch; hand-finish the dist <= 8 ones (see the list in `repair_log.tsv`, `NEAR*` rows).
- `func_150F1B78` family: different idea needed (permuter does not find it; try `s32 *` pointer compare through a struct, or the 2nd load as a separate `*(s32 *)&arg1[...]`).

## Layout

- `conker.eu.yaml`, `game.eu.rzip.yaml`: outer ROM split. The game code is compressed
  with "rzip" (gzip with a custom header).
- `conker/`: code sub-project.
  - `conker.eu.yaml` is generated by `tools/eu_port`.
  - `src_eu/` holds the EU C.
  - `symbol_addrs.eu.txt` and `undefined_syms.eu.txt` are generated.
- `tools/eu_port/`: US→EU porting pipeline. Rerun everything with `tools/eu_port/run.sh`
  from the repo root.
  - `baseline/`: the asm-only inputs, the `fff8a37` versions of `conker.eu.yaml`,
    `symbol_addrs.eu.txt` and `undefined_syms.eu.txt`. `run.sh` always starts from these.
  - `compile_us.py`: compiles each US C file with `GLOBAL_ASM` stripped into
    `conker/build_port/us/`.
  - `match.py`: fingerprints functions with relocations masked and matches US to EU.
    Shift resolution settles ambiguous matches. Symbols and `.rodata` bases come from
    relocation votes. Output: `build_port/match.json`.
  - `port.py`: places each US file's functions in EU, by shift first, then by
    before/after anchors. Writes `src_eu/`, the yaml subsegments, symbols and the
    `.rodata` splits. Report: `build_port/port_report.json`.
  - `eu_asm.py`: reads function starts, sizes and labels from splat's asm.
  - `bindiff.py`: lists the words that differ between the built and original binary
    (run from `conker/`).
- Verification (run from `conker/` inside the container, after building objects):
  - `check_files.py [src_eu/X.c ...]`: **the reliable check.** Whole-object `.text`
    vs the original EU bytes at the file's rom range, relocations masked. Covers C
    functions, which `check_funcs.py` cannot (splat writes no `.s` for a function that
    is already C). Known false SIZE reports for the last file of each code segment:
    `init_eu_289A0`, `game_eu_227BF0`, `debugger_eu_259B40`.
  - `revert_bad.py HEAD_CONKER_DIR src_eu/X.c ...`: reverts non-matching new C
    functions back to GLOBAL_ASM (see the incident section).
- Hand-porting helpers (run from `conker/`, the first two inside the container):
  - `check_funcs.py src_eu/X.c [func ...] [-v] [-s]`: builds the object through make
    and compares each function with `asm/nonmatchings/X/<func>.s`, relocations masked.
    `-v` prints a word-by-word diff, `-s` prints the address each referenced symbol
    must have in EU (`SYM name = 0x...`). Reference `.s` files only exist for
    functions that were GLOBAL_ASM at split time.
  - `implied_syms.sh file:func ...`: `-s` for several functions.
  - `cmp_syms.py <name addr list>`: compares implied addresses with the symbol files,
    the map and the asm labels; prints `undef` and `MISMATCH` lines.
  - `add_syms.py <cmp output>`: appends the `undef` ones to `undefined_syms.eu.txt`.
  - `toggle_us.py on|list file.c [func]`: swaps an `#if 0 // US version` block back in.
  - `survey.py <us stem>`: a US file's functions with their match.json status.
  - `port_one.py <stem> <eu rom start> <eu rom end> [US=0xEU ...] [--auto-anchors]
    [--src= --first= --last=] [--apply]`: places one US file in EU by piecewise
    shift, reports merged stubs and extra EU functions, and with `--apply` adds the
    symbols, edits the yaml and deletes `src_eu/<stem>.c` so that the next split writes
    a GLOBAL_ASM stub plus every function's `.s`. Then copy the US C in and check it.

**Important:** `run.sh` deletes and regenerates `src_eu/`, the EU yaml and the symbol
files. Once anyone hand-edits `src_eu/`, stop using `run.sh` as-is, or teach it to
preserve manual files. Treat the current commit as the hand-off point from automated
porting to manual work.

## Conventions

- EU symbols keep their **US names**, even though the address in the name is the US
  address. This lets `include/functions.h` and `include/variables.h` work for both
  versions.
- An EU symbol whose splat auto-name would clash with a US name gets an explicit name,
  `func_eu_XXXXXXXX` or `D_eu_XXXXXXXX`.
- A US C function whose EU code differs becomes a prototype plus
  `#pragma GLOBAL_ASM(...)`, with the US body kept under `#if 0 // US version; EU code differs`.
- EU data segments are mostly binary blobs (`databin`/`rodatabin`); files that own their
  .rodata are listed in the session 8 section. Data symbols the C code uses
  are defined in `undefined_syms.eu.txt`.

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

## Pitfalls already hit

- `git checkout` of generated files reverts them to whatever `HEAD` has, which is now
  generated output, not the baseline. Use `tools/eu_port/baseline/`.
- splat orders a segment's `.data` before its `.rodata`: a `.data` piece needs only data-typed
  pieces before it (game_data: `databin` up to 0x237060).
- The baseline EU split merged tiny `jr ra; nop` stubs into the preceding function.
  This shows up as US vs EU size differences of +8 or +16 bytes.
- `ld_align_section_vram_end: False` is needed in `conker/conker.eu.yaml`. Otherwise
  the binary gets 8 bytes of trailing padding.
- REA (reverse-engineering MCP) can open the linked ELF but can't decompile it. Ghidra
  isn't installed (`GHIDRA_INSTALL_DIR` is unset), and REA's Ghidra MIPS lane only
  accepts MIPS32r2 ELFs; this ROM is MIPS-II/VR4300.
- Do not push or commit to upstream. Commit locally on `eu` with the attribution
  trailer.
- `check_funcs.py` reports trailing `nop`s in the EU asm as a DIFF. At the end of a
  file that is just 16-byte padding and links fine. Anywhere else it means EU has a
  file boundary there: split the C file and add a subsegment (`game_30E60`,
  `game_8FCB0`).
- Adding a US name in `symbol_addrs.eu.txt` at an address that already has a
  `func_eu_`/`D_eu_` name makes splat stop with "Duplicate symbol"; drop the `_eu_`
  line if nothing references it.
- splat writes auto names such as `D_8003B9D0 = 0x8003B9D0` into
  `undefined_syms_auto.txt`, which the linker reads after `undefined_syms.eu.txt`, so
  it wins over a US name with the same spelling. Give the EU address an explicit
  `D_eu_` name in both `symbol_addrs.eu.txt` and `undefined_syms.eu.txt`, then re-split.
- An `extern u64` global is stored with two `lui`s; a tentative definition in the same
  file gets one. Keep the definition; `.bss`/COMMON is discarded by the linker script
  and the address comes from `undefined_syms.eu.txt`.
- `-O2 -g3` does not fill the `jr ra` delay slot of a one-line leaf; `-O2` does
  (`n_cspgetstate`).
- `check_funcs.py` silently skips functions that are already written in C (no `.s` is
  generated for them), so "all OK" from it says nothing about new C. Use
  `check_files.py`.
- Adding a prototype to a shared header can change codegen in files that called the
  function implicitly before. After header edits, run `check_files.py` on everything.
- A failed compile leaves the previous object in place, so a check right after it
  reports the old (matching) state. Delete the object first (the `cf` helper does).
- `make` prints `build/conker.eu.bin: OK` only when it relinks; delete
  `conker/build/conker.eu.ok` to force the check (the `verify` helper does).
- m2c needs `pycparser<3`; with 3.x it fails on `pycparser.plyparser`.
- Changing a file's `OPT_FLAGS` in the Makefile does not rebuild its object; delete the
  `.o` (the `m2c/flags` helper does) or `verify_all.sh --quick` checks a stale object.
- `rodata_split.py --resplit` and `verify_all.sh` (full) wipe `conker/build/`: keep m2c drafts
  and hand drafts outside it (e.g. the session scratch dir) while splitting.
- After changing which functions of an owned file are C, re-run `rodata_inject.py <stem>`
  before building (apply.py does), otherwise the old plan's raw rodata is still in the .s files.
- `progress.py` counted `.L..._game_data` labels (splat defines them for jump-table targets
  once a file's .rodata is known) as functions; it skips `.L` names now.
- `apply.py` used to truncate a C file when inserting a draft failed (open for write before
  building the text); fixed. Check `git diff --stat` for emptied files after any crash.
- `rodata_split.py --resplit`, `verify_all.sh` (full) and `file_split.py --resplit` wipe
  `conker/build/`, including `build/hand` (kept drafts) and m2c draft dirs: apply kept drafts before
  re-splitting, or keep copies outside (session scratch dir).
- `apply.py` run twice on the same `build/hand` crashes (pragmas already replaced); harmless.
- `tryall` with hundreds of drafts used to start them all at once and got OOM-killed in the
  container; it now runs 8 at a time (~1 s per draft).
- A C table that references a function still in GLOBAL_ASM needs that function's prototype
  above the table (`game_36680`).
- Never `git checkout` a source file to undo an experiment once `protocheck.py --apply` has edited
  it: that drops the kept prototype fixes too (happened to `game_eu_FCE60.c` in session 15; restored
  from `protocheck.log`). Edit the line back instead.
- `verify_all.sh` (full) wipes `conker/build/`, including `build/pc` (m2c drafts of protocheck callers)
  and `build/stackfix`; keep drafts you want in `tools/decomp-permuter/drafts/`.
- `tools/n64splat` shows as modified in `git status` (submodule content); that was
  already the case before this work and is not part of any commit.
