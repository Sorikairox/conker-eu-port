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

Indirect calls are still type-checked by `call_indirect`. A C caller whose function-pointer type
differs from the target's definition traps. Today `sigs.py` normalizes only direct calls. The
fallback is emscripten's `-sEMULATE_FUNCTION_POINTER_CASTS`, which costs speed on every indirect
call. The planned fix is a pass that types the function-pointer tables from their call sites.

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
   addresses 0..16 MB are kept free (`-sGLOBAL_BASE=16MB`) as a null zone, and
   `port_mem_null_report()` counts what landed there. On the N64 these writes would TLB-miss.

A 4 GB identity mapping (mirror base = 0x80000000, `-sMAXIMUM_MEMORY=4GB`) would make cases 1 and
2 work unchanged. It was rejected for now: it needs 2 GB+ of linear memory, which mobile browsers
and Safari can refuse; pointers above 2³¹ need care in the JS glue; and wasm-ld cannot place one
section at a fixed address. It stays an option if constants turn out to be everywhere.

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
