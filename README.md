# Conker's Bad Fur Day (EU) — private decomp + browser port

> **Private repository. Do not make public.** It contains material derived from the game (screenshots and data dumps in the git history). No ROM is stored here — you need your own EU ROM.

**To play it yourself, see [PLAYING.md](PLAYING.md)** (one command: `tools/eu_port/play.sh`).

This is a private fork of [mkst/conker](https://github.com/mkst/conker) (the US decompilation). The goal is a **native source port of the EU version that runs in a web browser**: the game's own code rewritten as readable C, compiled to WebAssembly with Emscripten (TypeScript only for the page), with native Mac/Windows builds later from the same C. It is **not** a static recompilation.

## Branches

| branch | what it is | state |
|---|---|---|
| **`eu`** (default) | The **matching decompilation** of the EU ROM: C that recompiles to a byte-identical ROM. Also holds the project's coordination files: `orchestrator.md` (status + working rules), `docs/progress/` (per-session log for the retrospective), `docs/names/` (readable-name table), `tools/eu_port/` (build/merge/backup scripts). | Paused at ~3,990 of 5,915 functions matching (67.5%). Work moved to the port. |
| **`eu-wt-a`** | Second working branch used for the matching decomp when two sessions ran in parallel. Fully merged into `eu`. | Idle; kept for history. |
| **`port`** | **Conversion branch 1.** Every remaining assembly function gets hand-written, readable C under `#ifdef NON_MATCHING` (the original assembly stays under `#else`, so the default build is still byte-identical). Each conversion is checked against the original with the `tools/port/difftest` equivalence tester plus deliberately broken variants ("mutants"). Owns the test harness (`tools/port/difftest`). | Active. |
| **`exact-byte-decomp-wip`** | port-web as of P328 with the byte-matching build (IDO, splat, asm, GLOBAL_ASM / NON_MATCHING wrappers, US tree, session docs). Never merged back. | Frozen. |
| **`port-b`** | **Conversion branch 2.** Same work as `port`, in parallel, on a separate list of source files so the two never edit the same file. Merges `port` periodically and vice versa. | Active. |
| **`port-web`** | **The browser build.** The EU game as readable C (since P329 without the matching-build wrappers) plus the platform layer in `port/`: WebAssembly build, N64 OS/scheduler emulation, WebGL2 renderer for the N64 graphics microcode, audio, controller/keyboard input, saves, and the web page. Runtime checks happen here (node + Chrome), and they feed the list of what to convert next. | Active. Single player plays from the title through the intro into level 0x29 (Birdy, the river, the pit, the gargoyle scene); all multiplayer modes start and play; music, saves and loading work. |

How they flow:

```
 eu (matching decomp, coordination docs)
  └─ port ──┐            conversion to readable C (two parallel branches,
  └─ port-b ┘ ◄──► each   disjoint files, merged into each other regularly)
        │
        ▼
     port-web   browser build: merges both + platform layer in port/
```

## Repository layout (branch `port-web`, since P329)

| path | what |
|---|---|
| `conker/src_eu/` | the EU game as readable C (722 files). No `#pragma GLOBAL_ASM`, no `#ifdef NON_MATCHING`; `#ifdef PORT` marks deliberate port changes. 31 platform functions (privileged OS / boot code) have no C: the port's platform layer replaces them. |
| `conker/include/` | game headers, libultra headers (`2.0L/`, `libultra/{os,audio,io}`), libc headers |
| `port/` | the browser port: `ultra/` (N64 OS, scheduler, memory), `gfx/` (F3DEX2 interpreter, WebGL2), `audio/`, `boot/`, `web/` (page + build scripts), `tools/` (build generators: census, vbe, stubs, memory model), `symbols/` (frozen names / addresses of the EU build, read by the tools) |
| `tools/eu_port/` | `check.sh` (pre-commit checks), `rename.py` + `names.tsv` (renaming), `apply_names.sh`, `deploy_web.sh`, `play.sh`, `wt.sh` (worktrees / containers), `backup_push.sh` |
| `tools/port/` | `difftest` (equivalence tester: candidate C compiled with IDO 5.3 vs the original code from the ROM, in Unicorn), `verify_registry.tsv` + `testdata/` (per-function setups and mutants), `scripts/` (browser tests: `warp.sh`, `newgame.sh`, `holdl.sh`), `implicit_scan.py` |
| `docs/` | `port/HANDOFF.md` (current state + session notes), `port/PLAN.md`, `port/MEMORY.md`, `port/design/`, `RENAMING.md`, `names/`, `progress/` |

The byte-matching decompilation build (IDO + splat + asm-processor, the US/debug/ects configs, the US source tree and
the per-session history) is no longer on `port-web`; it is kept on branch **`exact-byte-decomp-wip`**.

## Where to read more

- `orchestrator.md`: current status snapshot and the rules the work follows.
- `docs/port/HANDOFF.md`: latest state, next steps and short session notes.
- `docs/progress/sessions.tsv`: one line per session, for the retrospective.

## How to build (browser version, branch `port-web`)

Requirements: Docker Desktop (Apple silicon), your own EU ROM (`baserom.eu.z64`, never committed). Everything runs in
containers; nothing is installed on the host.

```sh
port/web/run.sh image            # once: the emscripten toolchain image (conker-emsdk)
port/web/run.sh build            # incremental build -> port/build/web (conker.wasm, page); `build clean` = from scratch
port/web/run.sh serve            # http://localhost:8064 ; drop the ROM onto the page (it never leaves the browser)
tools/eu_port/play.sh            # or: frozen copy for playing on http://localhost:8070 (PLAYING.md)
```

The build reads `baserom.eu.z64` at the repo root (relocation scan and memory-model checks). For development
(difftest, checks), create the dev container with `tools/eu_port/wt.sh` (image `conker-arm` from `Dockerfile.arm`:
python, MIPS binutils, IDO 5.3 for difftest), then:

```sh
eval "$(tools/eu_port/wt.sh env web)"
tools/eu_port/check.sh           # implicit_scan + romabs_check + difftest selftest + census + build, GREEN/RED
tools/port/scripts/warp.sh t1 30 29   # 30 s gameplay smoke test on level 0x29 (headless Chrome, muted)
```

## Credits

Based on [mkst/conker](https://github.com/mkst/conker), the US decompilation of Conker's Bad Fur Day, which was built
with [n64splat](https://github.com/ethteck/n64splat), [asm-processor](https://github.com/simonlindholm/asm-processor),
[asm-differ](https://github.com/simonlindholm/asm-differ), [mips_to_c](https://github.com/matt-kempster/mips_to_c) and
[ido-static-recomp](https://github.com/Emill/ido-static-recomp) (still used here as difftest's compiler).
