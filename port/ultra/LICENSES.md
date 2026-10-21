# port/ultra: provenance and licenses

The PC libultra layer (`pc_os.c`, `pc_sched.c`, `pc_video.c`, `pc_mem.c`, `pc_icall.c`, `pc_gu.c`,
`pc_libc.c`) was written for this port. It is not copied from any libultra source.

## ultralib (decompals/ultralib) — reference for behaviour only, no code copied

- Checked in session P25: `~/conker/tools/ultralib` at e24c836 (origin github.com/decompals/ultralib).
- **The repository has no LICENSE file.** Its README states no license either.
- Its C files keep the original **Silicon Graphics copyright header**: "unpublished proprietary
  information ... may not be ... copied or duplicated in any form, in whole or in part, without the
  prior written consent of Silicon Graphics, Inc." (for example `src/gu/mtxutil.c`).
- Conclusion: there is **no license that allows copying ultralib code** into the port. Session P25
  therefore did not port ultralib's C.
  - ultralib was used only to confirm *what* a function does (argument order, the Mtx layout, return
    values).
  - Every body was written from the game's own EU ROM code instead: the disassembly in `conker/asm/`,
    or the decomp's reconstruction of it in `conker/src_eu/`.
  - The math definitions (fixed-point s15.16, round to nearest) are facts of the hardware format.

| function (port/ultra) | written from |
|---|---|
| `guMtxF2L` (pc_gu.c) | `asm/nonmatchings/libultra/gu/guMtxF2L/guMtxF2L.s` (Rare's unrolled `cvt.w.s` version) |
| `func_150A7B80` = guMtxIdent (pc_gu.c) | `asm/nonmatchings/game_D5030/func_150A7B80.s` |
| `cosf` (`vbe.cosf`, pc_gu.c) | the reconstruction and constants in `conker/src_eu/libultra/gu/cosf.c` (commented C next to the GLOBAL_ASM) |
| `func_150AD780` / `func_150AD78C` fast cos/sin (pc_gu.c) | `asm/D5E90.s` 0x150ADC60..0x150ADD7C; constants read from game .rodata at run time |
| `bcopy` / `bzero` (`vbe.bcopy` / `vbe.bzero`, pc_libc.c) | libultra's documented semantics (overlap-safe copy, clear), on the port's `__vbe_memmove` / `__vbe_memset` |
| interrupt mask, `__osProbeTLB`, `__osSetCompare`, `__osCleanupThread`, `func_10024190` (pc_os.c) | the port's own model (cooperative scheduler, no TLB/caches); the asm in `init_eu_*` shows the contracts |

## For the port branch

The decomp itself contains SGI-derived libultra C: for example `conker/src_eu/game_eu_21DCD0.c`
(`guMtxF2L2` / `guMtxL2F`, the SDK text minus the header). That is outside `port/`; it is mentioned here
only so that the port's license review covers it.

## Third-party code built into the page

- Emscripten runtime and musl libc: MIT / musl license (shipped by the emsdk image, unmodified).
- SDL2 (emscripten port): zlib license.
