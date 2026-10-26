# port/gfx licensing

Everything in this directory was written for this port in session P6. No third-party code was
copied or adapted.

The F3DEX2 command encodings come from the decomp's own `include/2.0L/PR/gbi.h`. The RDP and TMEM
behaviour follows the public N64 programming documentation. Fast3D (sm64-port / libultraship)
served as the architectural model only: CPU T&L, then a GPU backend.

Conker's TRI4 bit layout (opcodes 0x10–0x1F) was worked out from the ROM's display lists and
checked by rendering. It is described in `docs/port/design/P6.md`.

If code is ever adapted from another renderer, record its name, URL, commit and license here.
Candidates are libultraship's Fast3D (MIT) and GLideN64 (GPL-2.0, which is incompatible unless the
whole port is GPL).
