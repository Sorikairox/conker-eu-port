# port/audio licensing

Everything in this directory was written for this port in session P9. No third-party code was
copied or adapted.

- **Command encodings** come from the decomp's own headers (`include/2.0L/PR/n_abi.h`, `abi.h`) and
  from the command lists Conker's C code builds (`src_eu/init_1E530.c`, `init_1FB40.c`,
  `init_20000.c`, `init_210C0.c`, `init_214F0.c`, `init_22040.c`, `init_22460.c`,
  `libultra/audio/n_synthesizer.c`).
- **Command semantics** (the naudio DMEM layout relative to 0x4F0, the Conker/MP3 command table with
  OVERLOAD at 0 and the filter at 0x0E, ADPCM history handling, the resampler's Q16 accumulator and
  4-tap lookup, the envelope ramp, the pole/IIR filters, interleave) were taken as a *behavioural
  reference* from mupen64plus-rsp-hle (`src/alist_naudio.c`, `src/alist.c`,
  https://github.com/mupen64plus/mupen64plus-rsp-hle, GPL-2.0). The code here is an independent
  implementation of that behaviour; its structure, DMEM model (big-endian byte array) and state
  layouts differ. Nothing was pasted from it.
- **The resample table** is not embedded: `aud_init_tables()` reads it from the user's ROM (the audio
  microcode's data block, `D_8002CCC0`, found at ROM 0x2CD80 in the EU ROM).
- **VADPCM decoding** follows the public N64 SDK description of the format (2 x 8 predictor
  coefficients per codebook entry, 4-bit residuals scaled by the frame header).
- **SDL**: `aud_out.c` uses Emscripten's built-in SDL audio (`library_sdl.js`, part of Emscripten,
  MIT/University of Illinois licence).

If code is ever adapted from another implementation, record its name, URL, commit and licence here.
N64ModernRuntime / ultramodern (MIT) would be compatible; rsp-hle (GPL-2.0) would not be, unless the
whole port is GPL.
