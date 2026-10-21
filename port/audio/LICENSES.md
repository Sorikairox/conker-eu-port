# port/audio licensing

Everything in this directory was written for this port in sessions P9 and P14. No third-party code
was copied or adapted.

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
- **MP3 synthesis (P14, `aud_abi.c` commands 7/8)** is written from the MPEG-1 audio standard's
  description of the polyphase synthesis filterbank (ISO/IEC 11172-3, 2.4.3.2: matrixing, V FIFO,
  512-tap window). mupen64plus-rsp-hle's `src/mp3.c` and the `NAUDIO_MP3` / `NAUDIO_MP3ADDY`
  handlers in `src/alist_naudio.c` (GPL-2.0) were used as a *behavioural reference only*, to confirm
  the command fields (index = w0 & 0x1E, address = w1), the 8-byte header and that the output
  overwrites the granule buffer from its start (from knowledge of its behaviour; its source was not
  opened or copied in P14). The game's own C (`game_221290.c`, `game_21FC90.c`) gave the buffer
  layout and gain header. rsp-hle's fixed-point code was not used; the
  implementation here is float, keeps the FIFO per state address and has a different structure.
  The 512-tap window is not embedded: it is read from the audio ucode data in the user's ROM
  (0x2CFD0 in the EU ROM).
- **`mp3_pc.c` (P14)**: the bit reader and the two Huffman routines are translations of Conker's
  own hand-written asm (`asm/nonmatchings/game_eu_226870/`); the two IMDCTs are written from the
  ISO 11172-3 hybrid synthesis description (IMDCT, block windows, overlap-add, frequency inversion).
- **SDL**: `aud_out.c` uses Emscripten's built-in SDL audio (`library_sdl.js`, part of Emscripten,
  MIT/University of Illinois licence).

If code is ever adapted from another implementation, record its name, URL, commit and licence here.
N64ModernRuntime / ultramodern (MIT) would be compatible; rsp-hle (GPL-2.0) would not be, unless the
whole port is GPL.
