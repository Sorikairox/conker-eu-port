# Original HANDOFF sections replaced by condensed versions (verbatim, pre session 33)

## Goal

Full matching decompilation of the **European** ROM. This is a private fork of
[mkst/conker](https://github.com/mkst/conker); upstream is US-first. The long-term aim
is a native Mac and Windows port. The user decided on a separate fork: nothing is
pushed, and nothing goes upstream.

- Repo: `~/conker`, branch `eu`. Remote `upstream` is mkst/conker.
- ROM: `~/conker/baserom.eu.z64`, z64 byte order, SHA1 `ee7bc6656fd1e1d9ffb3d19add759f28b88df710`.
  The user's original `~/Downloads/Conker's Bad Fur Day (Europe).n64` is byte-swapped
  and must not be modified.

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
