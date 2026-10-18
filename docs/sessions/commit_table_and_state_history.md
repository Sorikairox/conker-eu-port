## Current state

- The full EU ROM rebuilds **byte-identical** (`build/conker.eu.z64: OK`).
- **3139 / 5913 functions in C (53.1%)**; code bytes 340,772 / 2,253,856 (15.1%)
  (end of session 32, from `verify_all.sh`).
  - init: 361/540 functions (38.5% of bytes)
  - game: 2727/5330 (13.0%)
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
| `1b87444`, next, next | Session 31: `gfxfind.py`, Gfx-macro / switch / list-search recipes; 16 functions, +2,004 bytes |
| `a4d295b`, next, next | Session 30: `shortpool.py`, `m2cfix.py`, Gfx-macro / clamp / queue-add recipes; 22 functions, +2,960 bytes |

**From `b5aeddd` on, `src_eu/`, the EU yaml and the symbol files are hand-edited.
Do not run `tools/eu_port/run.sh`: it would regenerate them from the baseline and
throw all of that away.**
