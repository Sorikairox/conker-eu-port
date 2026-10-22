# Memory model of the wasm32 build

Status: chosen and prototyped in session P4 (branch `port-web`). Code: `port/tools/{n64mem,vbe,vbe_build,sigs}.py`,
`port/ultra/pc_mem.{c,h}`. Session notes and numbers: `docs/port/sessions/P4.md`.

## The problem

The game's data segments are raw ROM blobs: `init_data` (0x80029400, plain), `game_data`
(0x80082EB0, rzip) and `debugger_data` (0x16003700, plain, TLB-mapped). They are full of absolute
N64 addresses:

- KSEG0 `0x80xxxxxx` data pointers, plus a few KSEG1 `0xA0xxxxxx`;
- TLB-mapped code addresses: function tables (`0x10xxxxxx`, `0x15xxxxxx`, `0x16xxxxxx`), and jump
  tables whose entries are code labels inside GLOBAL_ASM functions;
- data in the TLB-mapped debugger segment (`0x16003xxx`);
- ROM offsets and segment addresses used as `&sym` (`D_10029400` and 45 others).

On the N64 these blobs sit at fixed addresses and the code reaches 1704 absolute `D_` symbols. In
wasm, a function pointer is a table index, data addresses are chosen by the linker, and memory is
little-endian. P3 linked 1635 zero-filled stubs instead of the data.

## Options

| | (a) linear memory mirrors N64 RAM | (b) symbolic data (Phase 2B) | (c) hybrid (chosen) |
|---|---|---|---|
| idea | data at `wasm = base + (N64 & 0x1FFFFFFF)`; pointers translated at load or by a helper | blobs become C / relocatable objects with real symbols; the linker places everything | (a)'s layout-preserving mirror and load-time relocation now; objects move to (b) one at a time |
| how data pointers are found | scan of the blob words, by range | splat/`datarefs.py` symbol references, code xrefs, then hand-checked `.word sym` | scan plus classification rules, reported for review; C definitions take over objects as they are symbolized |
| false positives | silent corruption of the one word | none once checked, but every word must be checked before it works | same as (a); bounded by the rules below, listed in `n64mem_report.txt` |
| function pointers | address→function table | `.word func`, so the linker does it | generated address→function table with exact prototypes |
| layout assumptions (`p + 0x1C`, `&a - &b`, bss clear between two symbols, arrays past their declared end) | kept: the layout is byte-identical | broken unless every object is split exactly | kept |
| works with today's tree (1764 asm functions, untyped blobs) | yes | no: needs the blobs typed first | yes |
| end state | still N64-shaped | clean, native-friendly, needed for 64-bit | converges to (b) |

(a) alone is fast to bring up but gives no route to a clean build. (b) alone is right in the long
run, but it cannot run before thousands of blob words are classified by hand and every
offset-style access is checked against the split. (c) needs no blob typing to boot. It keeps every
layout assumption of the decomp, and it goes on working while Phase 2B replaces mirror objects with
C definitions: when an object gets a C definition, its label disappears from the mirror, and the
relocator sends pointers into its range to the C object (the `port_cdata` table). That mechanism
already handles the 18 C-defined objects the blobs point to today.

## Decision

1. **Address space.** Two mirror arrays are defined as wasm `.bss` (zero-filled, no file size):
   `n64_rdram[8 MB]` for KSEG0, KSEG1 and physical addresses, and `n64_seg16[64 KB]` for the TLB
   window at 0x16000000. Every N64 data symbol without a C definition becomes a **label inside the
   mirror** at its N64 offset (`port/stubs/n64mem_labels.s`, generated wasm assembly; 1659 + 39 labels).
   The N64 layout is preserved byte for byte, so `&D_x - &D_y`, struct overruns, and the game's bss
   clear all keep working. Code (0x10/0x15/0x16) has no memory image: it is native wasm.
2. **Loading.** `port_mem_load()` (`port/ultra/pc_mem.c`) copies the three data segments out of the
   user's ROM. The ROM is already in wasm memory through the page's ROM picker. `game_data` goes
   through a small raw-DEFLATE inflater (rzip = big-endian u32 size + raw deflate). Bytes are written
   in the vbe layout described below.
3. **Relocation.** A build-time list (`port/stubs/n64mem_tab.c`, 5354 words) names the data words
   that hold pointers. At load each one is rewritten to `port_n64_to_wasm(value)`, which checks in
   order: an exact function start (gives the wasm table index), the range of a C-defined object (its
   wasm address plus the offset), the mirror arrays.
4. **Endianness: virtual big-endian memory, applied to game code by an IR pass.** See below. This
   is the decision that matters most for the C code.
5. **Calls: one wasm signature per function** (`port/tools/sigs.py`), so that IDO-era call/definition
   mismatches don't link as traps.

### How pointers in data are found, and false positives

`port/tools/n64mem.py` scans every aligned big-endian word of the three segments. It uses the N64
ELF (`conker/build/conker.eu.elf`) for function starts and the symbol files for data symbols:

| class | rule | count (EU) | action |
|---|---|---|---|
| F | value is exactly a function start (ELF `FUNC` symbol that is not a `.L` label, or a `func_XXXXXXXX` name) | 3244 | → wasm function (table index) |
| D | `0x80000400 <= v < 0x80400000` (KSEG0 game RAM, 4 MB), its KSEG1 alias, or `0x16003700..0x16004D58` | 2110 (42 into C objects) | → mirror or C object |
| J | inside a code range but not a function start: jump-table entries and code labels | 5977 | left as N64 addresses (only asm uses them; C `switch` compiles natively) |
| F-data | a function start whose name some TU declares as *data* | 1 | left raw (wasm-ld type clash) |

Why the rules hold, and what is left to check:

- A float in `0x80000400..0x80400000` is a negative denormal, which game data never contains. An
  int there is below −2³¹+4M, which no plausible counter or flag is.
- A word that equals a known function start exactly, read as a float, is about 1e-26 to 1e-29.
  Exact equality with one of 6600 addresses is very unlikely to happen by chance.
- The residual risks:
  - bit masks inside the KSEG0 window (`0x80000400` and up);
  - a packed `s16 pair` such as `0x8012, 0x3456`;
  - pointers stored unaligned.

  The next step is to cross-check the D list against `tools/eu_port/datarefs.py` and against the
  code's own `lui/addiu` references to the containing object. A wrongly relocated word becomes a
  wasm address: it is wrong in the same way as any bad data, and easy to spot because it falls
  inside `n64_rdram`.
- Words left alone on purpose: jump tables (J); values below 0x80000400 (`0x80000000`/`0x80000001`
  masks, `0xA0000002` IDs, as seen in `D_800877D0[0].unk4`); KSEG0 values above 4 MB.
- (b) removes the scan for an object once that object is symbolized.

### Function pointers

`n64mem_tab.c` takes the address of every function the data refers to (2569 names). Each prototype
is exact (the definition's wasm signature, read from the objects by `wasmobj.py`), so wasm-ld puts
the real function in the table. A prototype that doesn't match would get a trap thunk. Functions
that the data refers to but that have neither a C body nor a stub get a `void(void)` stub (877 of
them), so the table is complete and each hit is logged by name. The table is sorted by N64 address
and searched with a binary search by `port_n64_to_wasm`. `port/boot/game_entry.c` shows the reverse
case: a jump table whose words are code labels is read from the loaded data and turned back into
cases.

### Indirect calls (session P6)

`call_indirect` traps when the caller's function-pointer type differs from the target's
definition. IDO-era code does this constantly: handler tables mix `void f(void)`, `void f(s32)` and
`f32 f(s32)` entries that are called through one pointer type. On MIPS o32 such calls just work.

**Chosen: site-typed trampolines with a runtime signature check** (`port/tools/icall.py`, applied by
`vbe.py` to every game TU; `port/tools/icall_gen.py`; `port/ultra/pc_icall.{c,h}`):

- Each indirect call `call R %fp(args)` is rewritten into a direct call to
  `@__icall.<hash>(ptr %fp, args)`. This trampoline has exactly the site's type and is emitted
  `linkonce_odr` per TU, so the linker merges duplicates. 209 call sites today.
- The trampoline reads the target's wasm signature id from `port_fsig[table index]`. This table is
  filled before `main`:
  - each vbe TU registers every function it defines, `static` ones included, from a constructor;
  - `icall_tab.c` registers the asm stubs, the n64mem stubs and the PC layer, with exact wasm
    prototypes read from the objects.
- **Fast path:** the ids are equal, or the target is unknown. This is a plain `call_indirect`, and
  the cost is one table load and one compare.
- **Slow path:** the arguments go into an i64 register file with a 2-bit kind mask.
  `__port_icall_slow` switches over the 218 target signatures and calls the target with its own
  type. Arguments and the result are converted as `sigs.py` converts direct calls:
  - int↔int: sign-extend or truncate;
  - f32↔int: bitcast;
  - f32↔f64: widen or narrow;
  - missing arguments become 0, extra arguments are dropped;
  - a void result becomes 0.

  The first 16 mismatches are logged, and `port_icall_report()` gives the totals.
- Ids are a CRC of the wasm-level signature (`"f:i"` = `f32(i32)`), which is exactly what
  `call_indirect` checks. `icall_gen.py` asserts that no two signatures collide.

Why this option and not the others:

- **`-sEMULATE_FUNCTION_POINTER_CASTS`** makes *every* indirect call slow, including the 99% that
  match. It converts by reinterpreting raw i64 bits, so f32↔int and f32→f64 are wrong. It also
  makes the table thunk-based, which breaks function-pointer identity with the PC layer.
- **A uniform `(i32 × N) → i32` thunk table** has three problems:
  - every function pointer stored by game code or relocated from ROM data would have to be a
    thunk index;
  - comparisons against `&func` from the PC layer and from libultra would no longer agree;
  - f32 and f64 arguments still need per-type handling.
- **Typing `call_indirect` per table in the IR** needs the set of targets of each call site. That
  set is unknown for pointers loaded from data. Most of the 3244 relocated function pointers are
  only reachable that way.

The trampolines keep function pointers as real table entries and are exact on the fast path. They
reproduce the o32 behaviour on the slow path. The remaining gaps:

- Variadic call sites and variadic targets are left alone; they are registered as "unknown", so
  they take the fast path.
- An o32 call with an f32 first argument passes it in `$f12`. A caller that typed it as int and a
  callee that reads a float disagree on MIPS too. The bitcast rule reproduces that.

**Self-test** (`port/boot/game_icalltest.c` plus the generated `port_icall_check()`):

- *Registry check:* 654 entries of five ROM function tables (`D_8008FC10`, `D_80084840`,
  `D_8008A860`, `D_80089E10`, `D_80086634`). For each entry, the pointer relocated at load is
  looked up in the registry and compared with the signature that Python derives from the ROM and
  the signature DB. This checks the whole relocation → table → registry chain.
- *Calls:* real handlers of `D_8008FC10` (the characterflamethrower effect table) are called
  through mismatching types:
  - `f32(s32)` called as `s32(s32)`: result is the bits;
  - called as `f32(void)`: missing argument;
  - `void(s32)` called as `f32(s32)` and as `s32(s32,s32,s32,s32)`: result 0;
  - called as `void(void)`;
  - called as `f64(...)`: result widened.

  Without the pass, every one of these calls traps. The test passes in node and in headless
  Chrome.
- The main-loop state table `jtbl_80095DE0` holds code labels (class J), not functions. It is
  decoded into `switch` cases (P4) and is not called indirectly.

### Heap and allocator regions

All 8 MB of RDRAM is mirrored, so whatever the game carves out at run time lands inside
`n64_rdram`:

- the heap after the bss;
- the framebuffers from `func_10003C6C`;
- `osMemSize` = 8 MB, set by `port_boot`.

The game computes these regions from symbols, and symbols are already wasm addresses, so the
allocator's arithmetic stays consistent. Three things break:

1. **Integer constants that are addresses** in C (`0x80400000`, `(void *)0x80000400`). They need
   `port_n64_to_wasm()` or a macro wrapper (PLAN 3.2).
2. **Masking a pointer**, as in `K0_TO_PHYS(p)` / `p & 0x1FFFFFFF` / `| 0xA0000000`. The mirror base
   is not 0x80000000. The physical address of `p` is `port_wasm_to_n64(p) & 0x1FFFFFFF`. The PC
   `osVirtualToPhysical` returns the wasm address, which is what the PC renderer and audio need.
3. **Writes through NULL.** Stubs return 0, so the game writes through null pointers. wasm
   addresses below 256 MB are kept free (`-sGLOBAL_BASE=256MB` since P8; it was 16 MB before) as a
   null zone, and `port_mem_null_report()` counts what landed in its first 16 MB. On the N64 these
   writes would TLB-miss. See "Address space and RSP segments" below for why the base is 256 MB.

A 4 GB identity mapping (mirror base = 0x80000000, `-sMAXIMUM_MEMORY=4GB`) would make cases 1 and
2 work unchanged. It was rejected for now: it needs 2 GB+ of linear memory, which mobile browsers
and Safari can refuse; pointers above 2³¹ need care in the JS glue; and wasm-ld cannot place one
section at a fixed address. It stays an option if constants turn out to be everywhere.

### Address space and RSP segments (session P8)

**Decision: link the game with `-sGLOBAL_BASE=256MB`** (`-sINITIAL_MEMORY=352MB`, growth on). Every
wasm data address, static or heap, is then `>= PORT_WASM_BASE` (0x10000000, `pc_mem.h`), and
the 32-bit values a display list can hold fall into four disjoint classes:

| value | meaning | renderer (`gfx_addr`) |
|---|---|---|
| `>= 0x80000000` | N64 KSEG0/KSEG1 pointer left in ROM data | `port_n64_to_wasm` |
| `0x10000000..0x7FFFFFFF` | wasm pointer stored by game C code or the PC layer | used as is |
| `0x01000000..0x0FFFFFFF` | RSP segment address `seg << 24 \| off` | `segtab[seg] + off`; 0 (counted) if the segment was never set |
| `< 0x01000000` | segment 0: N64 physical, or an id | `segtab[0]` if set, else the RDRAM mirror |

`port_mem_load()` checks the invariant at start-up (fatal log if `n64_rdram` or the ROM copy is
below the base), and logs the layout: `n64_rdram 0x10242CA0, n64_seg16 0x10A42CA0, rom 0x10B53378`.

**The problem it removes (P6).** With `GLOBAL_BASE=16MB`, data, the RDRAM mirror (≈0x010A9F20), the
64 MB ROM copy (up to ≈0x0B000000) and the heap all had addresses that read as segments 1–15. The
game sets most of those segments every frame (1 model file, 3 bone matrices, 8 material DLs,
2/4–11 texture banks), so a game pointer such as `gsSPDisplayList(p)` with `p = 0x03xxxxxx` would
have been resolved through segment 3. The value alone cannot tell the two apart.

**Cost, measured.** Linear memory is reserved and zero-filled on demand; pages that are never written
cost no physical memory. The null zone is written only in its first 0x1530 bytes (1327 words in the
10 s boot run). node 10 s boot, `maxRSS`: 1488 MB with the 16 MB base, 1496 MB with the 256 MB base
(+8 MB, run-to-run noise; most of the RSS is V8 compiling the 2.7 MB module). The headless-Chrome
viewer and the boot run are unchanged.

**Browsers.**

- *Desktop (Chrome, Firefox, Safari, 64-bit):* fine. wasm32 memories are allocated as a large
  virtual reservation; V8 and SpiderMonkey reserve the whole 4 GB + guard region for every memory
  whatever its size, so the base changes only how much is committed, not what is reserved.
- *Android Chrome, 64-bit builds:* same as desktop.
- *32-bit browser processes* (older Android devices and older 32-bit Chrome builds): the memory is
  one contiguous ArrayBuffer inside a 4 GB address space. 352 MB is above the old 128 MB + 64 MB
  ROM growth (≈200 MB) and can fail with a RangeError on a fragmented address space. That is the real risk,
  and the build was already near that range because of the ROM copy. Mitigation if it matters: a
  fallback link with `GLOBAL_BASE=16MB` and P6's "segment wins" rule, selected by the page when
  the large `WebAssembly.Memory` fails.
- *iOS / iPadOS Safari (64-bit only):* the per-tab limit (jetsam) counts dirty pages, and the
  untouched zone has none. Allocation failures of large initial memories are known on older iOS
  versions and devices. 352 MB has **not been tried on a device** (none in this setup), so check
  it before relying on mobile Safari.

**Alternatives evaluated and rejected:**

- *Move only the RDRAM mirror to a high address (reserved region).* wasm linear memory is one range
  starting at 0, so the cost is the same as moving everything. It also leaves the ROM copy, the
  PC-side allocations and the C-defined game objects (`port_cdata`) in segment space, so it fixes
  only part of the problem.
- *A renderer rule ("a set segment wins", the P6 rule).* It is wrong exactly when the game sets
  segment *n* and stores a pointer into `0x0n000000..`, and the game sets most segments every
  frame. With the 64 MB ROM copy and the heap above 16 MB, that would happen as soon as frames were live.
- *Translate only addresses that went through segmented form.* That needs the origin of every DL
  word. The game writes DL words with plain stores (`gbi.h` macros) from constants, pointers and
  ROM asset data alike, so tracking it would mean changing `gbi.h` or the game code. Rejected.
- *4 GB identity mapping* (see above): fixes this too, but it costs 2 GB+ of linear memory.

Rules for PC code: never construct wasm pointers below `PORT_WASM_BASE`. Treat any value below it that
reaches the renderer as segmented or physical. `port_n64_to_wasm` results always satisfy this.

### Pointer-range tests in game C: every rewrite site (sessions P9, P42)

Game C that tells "a resident KSEG0 pointer" from "an offset / id / no pointer" by comparing against the KSEG0
boundary is wrong on the PC: real game pointers are wasm addresses `0x10000000..0x15FFFFFF`. `port/tools/vbe.py`
rewrites each known site in the IR. Game `.c` files are not changed. Every site is listed here.

| Site | N64 test | PC test | vbe.py pass |
|---|---|---|---|
| init_1AAE0, init_15550, init_214F0 (audio, 4 compares) | `(p & 0xFF000003) == 0x80000000` | `(p & 0xF0000003) == 0x10000000` | `k0_checks` (P9) |
| same files | `K0_TO_PHYS(p) > 0x800000` | `> 0x16000000` | `k0_checks` (P9) |
| func_15002008 (game_eu_2F180, leaf lists) | `(u32)p < 0x80000001` → vertex = (0, 0, 0) | `(u32)p < 0x10000000` | `k0_ptr_sites` (P42) |
| func_15002248 (game_eu_2F180, quadtree helper) | `(u32)p < 0x80000001` → vertex = (0, 0, 0) | `(u32)p < 0x10000000` | `k0_ptr_sites` (P42) |
| func_15004CE0 (game_30E90, MOVEMEM 0x0E relocation) | `unk4 < 0x80000000` → add the base | `unk4 < 0x10000000` | `k0_ptr_sites` (P42); its caller func_150039E0 is still asm, so not run yet |

`k0_ptr_sites` is scoped by function name and logs a warning to stderr if the number of rewritten compares
differs from the expected count (1 per function). Without the P42 rewrites, every level triangle would read as
(0, 0, 0) in the quadtree box tests.

Checked and **not** rewritten: func_15001460 (game_2DF70, level-DL triangle scan) recomputes bounds only when
`(u32)verts[0] >= 0x100001`. Wasm pointers pass that test, and area-2 object vertex offsets (≤ 0x100000) fail it,
as on the N64. Its G_VTX segment test `(addr >> 24) & 0xF` is 0 for every wasm address in the RDRAM mirror
(0x105xxxxx..0x10Dxxxxx). Addresses at 0x11000000 and above would read as segments 1..15, so the mirror must stay
below 0x11000000.

**Hardware reads with a computed address (P42):** `IO_READ(osRomBase | dev)` is `or x, 0xA0000000` → inttoptr →
volatile load. `vbe.py rcp_io` now turns that load into `__port_io_read(x)` as well, and the register model
answers the cart domain 0xB0000000.. with the big-endian ROM word (func_15001A08 reads ROM 0xD24 = 0x98CCE31A, so
the node pool is not doubled). This also catches the weak libultra `osPiRawReadIo`, `__osSpRawReadIo` and
`osSpTaskLoad`. The first is overridden by the PC layer, and the other two are not run.

### DMA, PI and rzip

`osPiStartDma`/`osEPiStartDma` → `port_rom_read()`. It copies ROM bytes into game memory in the vbe
layout: one `bswap32` per aligned word, byte by byte otherwise. Asset formats need no knowledge
here. The game's own rzip/inflate code runs on vbe memory unchanged: it reads the compressed stream
with byte loads and writes bytes, both through the lane mapping. Code overlays don't exist on the PC.
`func_10001194`'s code decompression and TLB setup are skipped, and the data segments come from
`port_mem_load`. One thing needs checking per loader: assets that contain **absolute N64
addresses**, pre-linked to a fixed load address, need `port_n64_to_wasm` when they are loaded.
Assets with segment-relative offsets that the game rebases at run time already work, because the
base is a wasm address.

## Endianness (critical)

**Decision: game memory is *virtual big-endian*.** Storage is "word-swapped", as in N64 emulators:
each aligned 32-bit word holds its big-endian value as a native little-endian i32. Then:

| access at virtual address A | native access |
|---|---|
| 32-bit (`A % 4 == 0`): `s32`, `f32`, pointers | at A, unchanged: zero cost |
| 16-bit (`A % 2 == 0`) | at `A ^ 2` |
| 8-bit | at `A ^ 3` |
| 64-bit (`s64`, `f64`) | at A, halves swapped (rotate by 32) |
| misaligned 16/32-bit, unaligned `memcpy`/`memset` | helper calls (`__vbe_*`) |

ROM bytes become this layout with one `bswap32` per word, whatever the format. So:

- the data blobs, display lists, vertices, animations, audio banks and text that the game loads at
  run time need **no per-format swapper**;
- every mixed-width access behaves exactly as on the N64: an `s32` read as two `s16` (the
  `lh 0x2(D_800BEE24)` in `func_15007830`), a `u8` read out of a `u32`, unions, offset-style reads.

**Where it is applied.** `port/tools/vbe.py` rewrites the LLVM IR of every game TU, compiled at
`-O0` with optnone disabled, *before* any optimization. The rewritten program is a correct
little-endian program, so clang's LE load narrowing and load/store combining run afterwards and stay
correct. A binary rewrite of the finished wasm would be wrong exactly there: `x & 0xFF` on a `u32`
is narrowed to a byte load at offset 0. On the full tree the pass rewrites 5558 byte loads, 5072
byte stores, 2800 halfword loads, 2760 halfword stores, 142/86 64-bit accesses, 76 misaligned
accesses (to helpers) and 56 `memcpy`/`memset` calls. Global initializers are converted at startup:
69 globals contain 1-, 2- or 8-byte scalars, and each gets a descriptor and a constructor
(`__vbe_fix`, checked against LLVM's own size of the object). All game globals are aligned and
padded to 4 bytes, so the lane permutation never leaves an object.

**Rejected alternatives:**

- *Struct-by-struct swap at load* (PLAN 3.6's first idea). It needs the type of every blob and
  every runtime asset format, and Conker has hundreds that nobody has reverse-engineered. Every
  mixed-width or union access silently reads the wrong half. It is still needed for 64-bit native
  pointers, but not for wasm32.
- *Swap-on-access macros in the C* (`BE16(p->x)`). Thousands of functions would need edits, it
  conflicts with keeping the matching source, and an access that is missed is silently wrong.

**What this implies for the C code:**

1. **Game C code needs no endianness edits.** Converted functions read ROM and asset data with N64
   semantics. This is what the `port_memtest` check proves in node and Chrome. Write converted code
   as for the N64. There's no need to add swaps.
2. **Bitfields are the exception.** IDO allocates bitfields from the MSB, clang (LE) from the LSB. A
   bitfield declared in a game header reads the wrong bits. There are 152 bitfield declarations,
   almost all in `gbi.h`/`abi.h`/`rdb.h` (the PC renderer and audio interpret those themselves), plus
   `game_eu_1207F0.c`. Those need a `#ifdef PORT` reversed declaration, or masks.
3. **The PC layer** (`port/ultra`, the future Fast3D and audio) is compiled natively. *Sub-word*
   fields of game memory must go through `vbe_ld8/vbe_st8/vbe_ld16/vbe_st16` (`pc_mem.h`). 32-bit
   fields, pointers and `Gfx` words are plain. Cases so far:
   - `OSContPad`/`OSContStatus` writes;
   - the `OSThread` `u16` fields, which the PC scheduler still writes natively (to fix);
   - game strings (`port_gstr`, `port_glog`).

   Coming later:
   - Fast3D vertex `s16` fields → `vbe_ld16`;
   - textures: bswap32 per word when converting for upload;
   - audio `s16` samples → `vbe_ld16`.
4. **libc.** The decomp's own `memcpy`, `strlen`, `strchr`, `sinf`, `sqrtf`, `tanf`, `ldiv` and
   `lldiv` are renamed to `vbe.*` in game TUs. Otherwise they would replace emscripten's libc for the
   PC layer too (musl `vfprintf` calling a vbe `strlen` garbles all output). The PC layer must never
   pass game memory to emscripten's byte-wise libc functions (`strlen`, unaligned `memcpy`). Use
   `__vbe_memcpy` and the other `__vbe_*` helpers.
5. **Varargs.** A `double` passed through `...` is written natively by the caller's backend and read
   back by the vbe-rewritten `va_arg` load: the halves get swapped. The game's own `printf` family
   prints `%f` wrong until the pass handles `va_arg` loads.
6. **Cost.** An `xor` per byte or halfword access. `inttoptr` limits some alias analysis. Not
   measured yet against a non-vbe build. The whole wasm is 1.37 MB, ASYNCIFY included; the function
   table keeps the 2569 functions the data refers to alive (P3's 64 KB was mostly dead-stripped).
7. **Native builds.** The pass is plain LLVM IR, so it works the same for clang x86/ARM targets. The
   64-bit pointer width (PLAN 3.9) is a separate problem.

## Calls: one signature per function

IDO linked anything: implicit `int f()`, local prototypes that disagree with the definition,
f32/s32 mix-ups. In wasm, a direct call whose type differs from the callee's is linked as a trap.
P3 counted 262 such functions. `vbe_build.py` first emits IR for all TUs and collects every
non-static `define`, prototyped variadic `declare` and direct call site. It writes the canonical
signature of each function to `port/build/sigdb.json`: the definition's, or for asm-only functions
the most common call-site signature, which the stub generator also uses. `sigs.py` then rewrites the
791 mismatching call sites and their `declare`s. Arguments are converted the way an o32 register
would pass them: int widths sign-extend or truncate, ptr↔int, f32↔i32 bitcast; a missing argument
becomes 0 and an extra one is dropped. 27 sites mix f32 and int, which is wrong on the MIPS side too
(the value is in another register). Link signature warnings went from 288 to 1: `corrupted`, defined
twice with different arity.

## Path to (b)

1. Phase 2B symbolizes a blob object into C, using the same reloc classification as the starting
   point.
2. Its label leaves the mirror, the C object becomes authoritative, and the relocation table sends
   blob pointers into it to its wasm address.
3. When no labels are left, the mirror shrinks to the run-time heap and framebuffers, and the
   pointer scan is gone.
4. The vbe model stays: run-time asset data remains big-endian, whatever the static data becomes.
