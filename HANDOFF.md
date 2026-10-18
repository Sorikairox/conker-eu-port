# Hand-off: Conker's Bad Fur Day (EU) decompilation

Last updated: 2026-10-18 (fifteenth session). Update this file at the end of every work session.

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
- **2823 / 5912 functions in C (47.8%)**; code bytes 293,688 / 2,253,856 (13.0%)
  (end of session 15, from `verify_all.sh`).
  - init: 361/540 functions (38.5% of bytes)
  - game: 2431/5329 (10.8%)
  - debugger: 31/43 (41.3%)
  - History: 1094 (18.5%) after the automated port, 1363 (23.1%) after the hand port,
    2374 after the first round of new decompilation (session 3), 2563 after session 4,
    2622 (253,312 bytes) after session 5, 2664 (265,996 bytes) after session 6, 2682
    (268,452 bytes) after session 7, 2706 (273,596 bytes) after session 8, 2735 (277,860 bytes)
    after session 9, 2757 (281,452 bytes) after session 10, 2772 (286,048 bytes) after session 11,
    2780 (287,492 bytes) after session 12, 2799 (290,016 bytes) after session 13, 2820 (292,952 bytes) after session 14.
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
