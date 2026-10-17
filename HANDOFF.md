# Hand-off: Conker's Bad Fur Day (EU) decompilation

Last updated: 2026-10-17 (fifth session). Update this file at the end of every work session.

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
- **2622 / 5913 functions in C (44.3%)**; code bytes 253,312 / 2,253,856 (11.2%)
  (end of session 5, from `verify_all.sh`; session 4 counted 2563 against 5916).
  - init: 320/542 functions (30.7% of bytes)
  - game: 2271/5328 (9.5%)
  - debugger: 31/43 (41.3%)
  - History: 1094 (18.5%) after the automated port, 1363 (23.1%) after the hand port,
    2374 after the first round of new decompilation (session 3), 2563 after session 4.
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

**From `b5aeddd` on, `src_eu/`, the EU yaml and the symbol files are hand-edited.
Do not run `tools/eu_port/run.sh`: it would regenerate them from the baseline and
throw all of that away.**

## Quick start for a new session

- Standard brief and rules: `tools/eu_port/AGENT_BRIEF.md`.
- One-command verification: `tools/eu_port/verify_all.sh` (`--quick` skips the
  re-split). It prints code build / check_files / full ROM status and progress.
- Progress summary only: `python3 tools/eu_port/progress.py conker/progress.csv`.

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
docker run -d --name conkerdev --platform linux/amd64 -v ~/conker:/conker -w /conker conker sleep infinity
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
- EU data segments are still binary blobs (`rodatabin`). Data symbols the C code uses
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
   Next steps (session 5):
   - **Remaining libultra C functions** (likely `-O1`, use `m2c/flags`): `osPiRawStartDma`
     (`init_eu_23CC0`, with asm `bcopy`), `__osSiDeviceBusy`, `__osSpGetStatus`,
     `__osSpRawReadIo/WriteIo` (`init_eu_26870`, shares the file with `__sinf`),
     `osJamMesg`, `osPiGetCmdQueue`, `osDestroyThread` (`init_eu_26370`, with the cont
     CRC functions), `osContInit/__osContGetInitData/__osPackRequestData`,
     `osContStartReadData/osContGetReadData` (`init_eu_24ED0`), `__osContRamRead/Write`,
     `__osContAddressCrc/DataCrc`, the pfs functions (`__osPfsRWInode`, `__osGetId`,
     `__osCheckId`, `__osRepairPackId`, ...), `ldiv/lldiv`, `_Litob`, `__osViSwapContext`,
     `__osViInit` (`func_10024720`), `osSetTimer`-style helpers, `osPfsChecker`.
     Handwritten asm (leave as is): `bzero`, `bcopy`, `__osGetSR/__osSetSR`,
     `__osSetFpcCsr`, `__osDisableInt/__osRestoreInt`, `osInvalICache/DCache`,
     `osWritebackDCacheAll`, `osGetCount`, `__osSetCompare`, `osMapTLB/osUnmapTLB`,
     `__osProbeTLB`, `osSetIntMask`, `sqrtf` (init copy), the `__ll_*` helpers (compiled
     with a different compiler), `func_10007D14` (`__osPopThread`, from exceptasm.s).
     Several init files mix two libultra objects with different flags: split them
     like `init_eu_23360` when one flag set does not fit.
   - Game-side copies of libultra exist too (`game_eu_21D010`, `game_eu_21E320`); look
     for more `func_151E`/`func_151F` functions that call `__osDisableInt` or touch
     `0xA4xx` registers.
   - Near misses left (1-4 differing words): `func_150351A4 func_150C60D4 func_151A53E4
     func_1517A220 func_151CBAC0` (commutative operand order), `func_1511CAD0` (store/load
     order), `func_15144B68 func_150A7CB0` (instruction order), `func_151A547C` (flag
     spilled as a byte across a call), `func_150D03A8` (one stack slot),
     `func_1514EA78 func_1514EB28 func_1514EBD8 func_1514EC88` (`v1`/`v2` choice),
     `func_1509CEA8` (unrolled `for` loop, init order), `func_15142E24 func_15052260
     func_151C2600` (100+ instructions). `conker/build/best.txt` has the full list.
   - `func_151EF7B0` matches as C but is followed by 0x40 bytes of nop padding in its
     file (`game_eu_21CFC0`), more than the 16-byte object alignment; needs an asm
     padding block or a different file split.
   - `func_15173948` (`return arg0;` with an unused second arg) has its `jr ra` delay
     slot filled: its file (`game_eu_1A1060`) would need a split with `-O2`.
   - About 250 functions screen as `SIZE±1`; quick looks found single-instruction
     differences that resisted easy fixes (e.g. `func_150104F0`: `or v0, zero, zero`
     stored twice).
   - Small functions are mostly done; what is left needs hand work or real types.
     Naming structs (`struct127` objects, `struct_eu_node` lists, message handlers
     with the `(obj, msg, u8 event)` signature) would make m2c's drafts much closer.
5. Later: split EU data properly (data/rodata/bss instead of blobs), document asset
   formats, then the PC port.

## Pitfalls already hit

- `git checkout` of generated files reverts them to whatever `HEAD` has, which is now
  generated output, not the baseline. Use `tools/eu_port/baseline/`.
- splat orders a segment's `.data` before its `.rodata`, so the data blob pieces must be
  `rodatabin`.
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
- `tools/n64splat` shows as modified in `git status` (submodule content); that was
  already the case before this work and is not part of any commit.
