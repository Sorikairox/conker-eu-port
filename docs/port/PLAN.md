# Conker's Bad Fur Day (EU): source port plan

Goal: the game running **in a web browser** (WebAssembly via Emscripten, wasm32), built from full C
source. Not N64Recomp, and not static recompilation. Native Mac/Windows builds come second, from the same C
codebase. TypeScript is used only for the page, the UI and JS glue. The game logic stays C.

Starting point (2026-10-21, branch `port`): a splat + IDO 5.3 matching decomp that builds a
byte-identical ROM. 3992 of 5913 functions are C; about 1890 are still `#pragma GLOBAL_ASM`.

## Memory map facts that drive the plan

| segment | vram | ROM storage | notes |
|---|---|---|---|
| init code | 0x10001000 | plain | kuseg, TLB-mapped |
| init_data | 0x80029400 | plain | |
| game code | 0x15000000 | **rzip**: 4 KB blocks plus an offsets table (`TEXT_SECTION_LENGTH` 1335000 fixed) | TLB-mapped, decompressed at boot |
| game_data | 0x80082EB0 | rzip | .data, then .rodata |
| debugger | 0x16000000 / 0x16003700 | plain | |

- The data segments are mostly **incbin'd binary blobs** (`assets/*.databin.bin`,
  `*.rodatabin.bin`). They hold raw 32-bit pointers to code and data: function tables, jump tables of
  the GLOBAL_ASM functions, and pointer tables.
- Data symbols are **absolute**: 7771 `D_` entries in `undefined_syms_auto.txt` and 1786 in
  `undefined_syms.eu.txt`.
- Consequence: the build is **not shiftable**. If any code or data moves, the blobs and the absolute
  symbols point into the wrong places. This is the main blocker for Phase 2 and Phase 3, so it gets
  its own workstream (Phase 2b).

## Phase 1: every function in C (non-matching allowed), with an equivalence gate

Status: the infrastructure is done (this session). See `docs/port/HANDOFF.md`.

- **Convention.** A converted function goes in its source file as
  `#ifdef NON_MATCHING <C> #else #pragma GLOBAL_ASM(...) #endif`. The default build stays byte-identical
  (`verify_all.sh`). `make VERSION=eu NON_MATCHING=1` compiles the C into `conker/build_nm/`.
- **Gate.** `tools/port/difftest.sh FUNC draft.c` must print `EQUIV`. It is a Unicorn MIPS
  differential test: original bytes against the IDO-compiled C, with random inputs, a lazily
  randomised memory model and stubbed callees. It compares the call trace (with arguments), the
  memory state at each call, the final memory, the return value and the callee-saved registers.
  `UNSURE` (too few trials completed) does not pass.
- **Pipeline.** `tools/port/convert.py --tag T -l list [--insert]` does m2c (typed and untyped
  contexts, narrow and argfix variants) → autofix → IDO compile → difftest → insert.
- **Fan-out.** Sessions take disjoint file ranges, as the decomp worktrees do. Each session runs
  convert.py over its range, hand-fixes the `DIFFER`/`CERR` leftovers using the difftest reason, and
  commits after `verify_all.sh`. Order: small functions first. Hardware and libultra functions
  (`mtc0`, `cache`, TLB) are left in asm or replaced by the PC layer in Phase 3; they need no C
  equivalent.
- **Data.** For each converted function, also write down its rodata (the literals and jump tables
  live in blobs today). Phase 2b needs this.
- Done when `grep -c GLOBAL_ASM` outside `#else` branches is 0 (except hardware stubs), and every
  `NON_MATCHING` body has a difftest `EQUIV` record (`port_work/*/results.tsv`, summarised in the hand-off).

## Phase 2: NON_MATCHING N64 ROM that boots (end-to-end check)

Two routes. Do A first; B is needed anyway for Phase 3.

**A. Address-stable hybrid ROM (recommended first).** Keep the matching layout. Compile each
NON_MATCHING body into an *overflow* object. Patch the original function entry with a trampoline
(`j overflow_func; nop`) at link time. Every address in the blobs and symbol files stays valid, so
nothing has to be shiftable. Steps:

1. Build: compile every NON_MATCHING body in its own TU, made from the file's includes plus
   declarations. Link its `.text` at an overflow vram in the same 256 MB region as the game code
   (say 0x17000000), so `j`/`jal` reach both ways. Link its `.rodata`/`.data` at a kseg0 overflow
   area (0x80400000, the expansion-pak RAM).
2. A boot hook (patched into the init code, or a converted init function) DMAs the overflow blob from
   the end of the ROM, installs one TLB entry mapping 0x17000000 → physical 0x00400000, and
   invalidates the caches. Check which TLB index the game leaves free.
3. Trampolines: `tools/port/` should gain a post-link patcher that rewrites the first 2 words of
   each original function. That leaves the rzip code blocks to rebuild. `compress_dir.py` already does
   that, but the code size stays the same, so the offsets table length is unchanged.
4. Test in ares or mupen64plus (8 MB) and bisect bad functions by enabling subsets.
   Differential check: compare RDRAM snapshots, per frame, between the original ROM and the hybrid
   ROM under the same recorded inputs.

**B. Shiftable build (Phase 2b, the prerequisite of Phase 3).** Symbolize the data:

1. Turn each `databin`/`rodatabin` blob into `.s` (later C) with `.word sym` for every word that is
   a pointer. Candidates are words inside a code or data vram range. Confirm them with the code
   references (`tools/eu_port/datarefs.py`) and the jump-table owners.
2. Replace the absolute `D_` symbols with labels defined in those data files.
3. Generate the rzip offsets and padding from the actual sizes. `TEXT_SECTION_LENGTH`,
   `OFFSETS_LENGTH` and `DATA_SECTION_LENGTH` are hardcoded in the Makefile.
4. Proof: a ROM built with `NON_MATCHING=1` boots. Once it does, the code layout no longer matters.

What the in-place `NON_MATCHING=1` build does today is in `docs/port/HANDOFF.md`, section "NON_MATCHING build".

## Phase 3: browser build (wasm32), then native

### 3.0 Toolchain

- emsdk inside a container, e.g. a new `Dockerfile.emsdk` (`emscripten/emsdk` image). Nothing
  installed on the host. Builds use CMake plus `emcmake`. The output is `conker.wasm` + `conker.js`
  + a small TS page (`web/`, built with esbuild/vite inside the same container).
- The same CMake builds native targets with clang/MSVC later.
- Host installs: none needed. To serve the page locally, any static server inside the container
  is enough (`emrun` or `python3 -m http.server`).

### 3.1 Why wasm32 first

- wasm32 pointers are 32-bit, like the N64. The offset-style decomp C (`*(s32 *)(p + 0x1C)`, `s32`
  temporaries holding pointers, structs that embed pointers) keeps its layout. The sizes of `long` and
  `size_t` match too. This removes the biggest cost of a 64-bit port from the critical path.
- wasm is little-endian, like x86 and ARM. Big-endian asset handling (3.6) is therefore the same work
  for web and native.
- Native 64-bit comes later (3.9).

### 3.2 Build layout and memory

- Compile all segments (init, game, debugger) as one wasm module. There are no overlays.
- The rzip decompression and the TLB mapping of 0x15000000/0x16000000 become no-ops. On the N64 the
  code is executed from the TLB window; on the PC the code is native wasm. The `osMapTLB*`/`osUnmapTLB*` calls are stubbed.
- Code that uses segment symbols (`game_VRAM`, `*_ROM_START`) or that copies code or data around
  for the overlay loader is found by grepping for those symbols. It is replaced by direct pointers.
- Phase 2b output (symbolized data) becomes C arrays, or a data blob plus a relocation table that is
  patched at load time. Pointers in the data must hold wasm addresses. Option: keep the data
  blobs, but relocate them at startup with the Phase 2b relocation list. This is fast to bring up.
- Fixed RDRAM addresses (frame buffers, `osMemSize`, KSEG0/1 casts `| 0xA0000000`,
  `PHYSICAL_TO_VIRTUAL`) are wrapped in macros that map them onto a 4–8 MB static arena.
- ROM access: `osPiStartDma`/`osEPiStartDma` read from the user-supplied ROM bytes held in memory
  (see 3.7). Compressed assets keep going through the game's own rzip/inflate C code.

### 3.3 Renderer: F3DEX2 display-list interpreter (Fast3D, libultraship style)

Status (P6): `port/gfx/` is an F3DEX2 interpreter on WebGL2, written fresh rather than ported
from Fast3D. It is wired to `osSpTaskStartGo`. Conker's custom TRI4 opcodes and its ucode
variants are documented in `docs/port/design/P6.md`.

- Conker builds with `F3DEX_GBI_2`. Port the **Fast3D interpreter** (sm64-port `gfx_pc.c`, as
  maintained in libultraship's `Fast3D`). It interprets `Gfx` command lists in software: geometry,
  matrices and lighting run on the CPU, and the rasterisation, combiner and texture state go to a
  backend.
- Backend: **WebGL2** through Emscripten's GLES3 (`-sMAX_WEBGL_VERSION=2`). The existing
  OpenGL/GLES backend works almost unchanged. WebGPU (Dawn/`emdawnwebgpu`) is the second option for
  later. The same interpreter drives OpenGL/Metal/D3D11 natively.
- **RT64 is not viable in the browser.** It needs D3D12/Vulkan/Metal and reads display lists from an
  emulated RDRAM. It is ruled out for the web target.
- Conker-specific work:
  - check for custom or modified microcode commands (Rare titles sometimes add `G_` ops) by logging
    unknown opcodes;
  - the combiner modes and texture formats Conker uses;
  - frame-buffer effects (motion blur, letterbox, CPU reads of the colour or depth buffer) need
    specific emulation or a cut.
- Display lists in ROM assets use segmented addresses. Fast3D resolves `gsSPSegment` bases. With 32-bit
  wasm pointers the `Gfx` words keep their N64 width.

### 3.4 Audio

- Conker uses libultra `n_audio` (`n_alAudioFrame` builds RSP audio command lists for `n_aspMain`).
  HLE that command list on the CPU, in an "naudio" ABI interpreter like mupen64plus-rsp-hle
  `alist_naudio.c` or sm64-port `mixer.c`. Write it from documentation; check licenses before
  copying (rsp-hle is GPLv2).
- Output goes through SDL2 audio (Emscripten SDL2 → WebAudio). The browser needs a user gesture before
  audio starts, so start the audio on the "Load ROM / Play" click.

### 3.5 Input, saves, platform layer

- `libultra` is replaced by a PC layer (`src/pc/ultra/*.c`). It keeps the `os*` API so the game
  code is unchanged:
  - `osContStartReadData`/`osContGetReadData` map to SDL2 game controllers and the keyboard. The
    page offers a rebinding UI (TS).
  - EEPROM (`osEeprom*`) and controller pak (`osPfs*`) become RAM images flushed to
    **IndexedDB** through a small JS shim (`EM_JS`), with a localStorage fallback. Native builds
    use plain files.
  - VI (`osViSwapBuffer`, retrace messages) is driven by the frame loop (3.8).
  - Timers (`osGetTime`, `osGetCount`) map to `emscripten_get_now`.

### 3.6 Endianness and assets

> **Superseded (P4):** the browser build uses *virtual big-endian* game memory (IR pass, no per-format
> swappers) and a mirror + load-time relocation for the data blobs. See `docs/port/MEMORY.md`.

- The ROM is big-endian. Code that reads asset structures through typed pointers
  (`*(s16 *)(p + 4)` on data loaded from ROM) needs byte-swapping. Plan:
  1. Inventory the asset loaders: every `osPiStartDma` destination and every rzip decompress
     output, grouped by asset type (models / display lists, textures, animations, audio banks,
     text).
  2. Byte-swap each asset type once, at load time, with a per-format swapper (16-bit and 32-bit
     fields, `Gfx`/`Vtx` words). Textures and other byte data stay as they are; Fast3D reads
     16-bit texels big-endian, so check this per format.
  3. The game's own RAM structures are native-endian automatically, because they are compiled C.
- Data blobs from Phase 2b are swapped at build time when they become C arrays.
- Risk: offset-style code that reads a field with a different width than it was written (an
  `s32` read as two `s16`, unions, `lwl`/`lwr` patterns). Find these with tests (3.10), and
  convert them to struct fields as they turn up.

### 3.7 ROM handling

- The ROM never ships. The page asks for the user's `.z64`, `.n64` or `.v64` file. It detects and
  normalises the byte order, checks the SHA1 (`ee7bc665…`, EU), and stores the ROM in IndexedDB.
  It then passes the ROM to wasm (`Module.FS` or a `malloc`'d buffer).
- Assets are read from that buffer at runtime. No asset extraction step is needed.

### 3.8 Main loop vs libultra threads (major design risk)

The game is written for libultra's preemptive threads: `osCreateThread`, `osStartThread`, and
blocking `osRecvMesg(OS_MESG_BLOCK)` on queues fed by VI, SP, DP, AI and PI interrupts. Browsers
run one main thread that must return to the event loop every frame. Options:

1. **ASYNCIFY + cooperative threads (recommended to start).** Implement `OSThread` as Emscripten
   fibers (`emscripten_fiber_*`, which need ASYNCIFY). This is cooperative scheduling: a
   blocking `osRecvMesg` on an empty queue yields to the scheduler, which picks the highest-priority
   runnable thread. When all threads are blocked waiting for the VI message, the scheduler returns
   to the browser (`emscripten_set_main_loop` callback). The next frame posts the VI retrace message
   and resumes. Interrupt sources (SP task done, DP done, AI, PI DMA done) are simulated
   synchronously: `osSpTaskStart` runs Fast3D or audio HLE right away and posts the done-message.
   - Pros: the game code is unchanged, and priorities and message semantics are preserved.
   - Cons: ASYNCIFY makes the binary bigger and slower (about 1.5–2x code size, slower calls on the
     instrumented paths). Use `ASYNCIFY_ONLY`/`ASYNCIFY_ADD` with the list of functions that can block,
     derived from the call graph to `osRecvMesg`/`osYieldThread`, to keep the overhead small.
   - Native builds use the same scheduler with ucontext / Windows fibers (or real threads under a big lock).
2. **JSPI (JS Promise Integration)**: a lower-overhead stack switch. It is available in recent
   Chrome; Firefox and Safari support lag behind. Keep it as a later build flag.
3. **pthreads (SharedArrayBuffer)**: real threads plus a global lock to emulate the single-CPU
   priority semantics. This needs COOP/COEP headers on the host and does not remove the need to
   yield to the browser for rendering. Not recommended.
4. **Restructuring the game loop** into a per-frame function is the most work, and diverges from the
   source. Use it only if 1 and 2 are too slow.

Risks to check early: busy-wait loops on hardware registers or `osGetCount` that would never yield
(convert them to yields), threads that rely on preemption (a low-priority thread spinning on a flag),
and stack-size assumptions (fiber stacks of about 64 KB each).

### 3.9 Native 64-bit builds (later)

- Requirements: pointer-sized fields in every struct that crosses the asset boundary, `uintptr_t`
  for pointer temporaries (m2c drafts often keep pointers in `s32`), and no pointer arithmetic
  through `s32`.
- Two strategies:
  1. Convert the offset-style accesses to real structs (decomp clean-up). Assets with embedded
     pointers get native structs at load time.
  2. An "N64 address space" arena (4 GB-aligned base, pointers stored as 32-bit offsets with
     `P32()` macros). It is mechanical but invasive.
- Do 32-bit native first (Windows x86, Linux `-m32`) to separate platform bugs from pointer-width
  bugs. macOS has no 32-bit target, so it needs option 1 or 2.

### 3.10 Testing

- Per function: difftest EQUIV (Phase 1).
- Whole game: the Phase 2 hybrid ROM; later, record controller inputs in an emulator and replay them
  in the wasm build, then compare the game-state structures at checkpoints.
- Graphics: screenshot comparison against an LLE emulator (ares, angrylion) at fixed frames.

## Order of work and estimates

1. Phase 1 fan-out: ~1890 functions. Pilot pass rates are in the hand-off. Plan for automated
   conversion plus hand repair, in sessions over disjoint file ranges.
2. Phase 2A hybrid ROM, in parallel with the end of Phase 1. It catches equivalence escapes early.
3. Phase 2b data symbolization. It can start now, independently, from datarefs.py.
4. Phase 3: emsdk container and CMake skeleton with stub libultra → boot to the first frame with
   Fast3D/WebGL2 → threads/ASYNCIFY scheduler → input → audio HLE → saves → asset endianness
   sweep → page UI.
5. Native builds (32-bit, then 64-bit).

## Biggest risks

1. **Non-shiftable data** (raw pointer blobs, absolute `D_` symbols). It blocks both a real
   NON_MATCHING ROM and the PC data layout. Phase 2b is the fix, and it is a sizeable reverse-engineering task.
2. **Threads vs the browser loop** (3.8). ASYNCIFY overhead, and code that relies on preemption.
3. **Asset endianness** in offset-style code (3.6): mixed-width reads are only found by testing.
4. **Equivalence escapes.** difftest is randomised. It cannot see FP-exact corner cases, huge loops,
   TLB-window pointers or code that depends on the real data. The Phase 2 boot test is the backstop.
5. **Microcode specifics** (custom GBI ops, frame-buffer effects) in Fast3D.
6. **Audio ABI** details of `n_aspMain` (ADPCM, reverb, resampler).
