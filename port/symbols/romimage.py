#!/usr/bin/env python3
"""The EU ROM's code + data image, unpacked from the user's ROM (baserom.eu.z64) at run time (P328).

image(rom) -> bytes laid out exactly like the matching build's extracted conker/conker.eu.bin:
  header (ROM 0x0..0x40) | boot (0x40..0x1000) | init code+data (0x1000..0x2D810)
  | game code + game data, both rzip-inflated (packed at ROM 0x427B0) | debugger code+data (ROM 0x19EDE8, 0x4D58 bytes)
so image offsets are the "rom" offsets of conker.eu.yaml / port/symbols/segments.tsv. Nothing ROM-derived is
committed: this only knows the layout. Proven equal to the splat-extracted conker.eu.bin (md5 6d8edea9...) in P328.

usage: romimage.py [ROM] [OUT]   (writes the image to OUT, or prints its md5)
"""
import hashlib, os, struct, sys, zlib

ROM = os.environ.get('CONKER_ROM', 'baserom.eu.z64')
GAME_RZIP = 0x427B0            # game.eu.rzip in the ROM
GAME_RZIP_XOR = 0x8039CCCA     # key of the code chunk offset table (game.eu.rzip.yaml)
GAME_DATA_RZIP = 0x145ED8      # compressed game .data, relative to GAME_RZIP
DEBUGGER = (0x19EDE8, 0x4D58)  # debugger code + data, stored uncompressed


def _runzip(b):
    """Rare zip: 4-byte uncompressed length + raw deflate."""
    return zlib.decompressobj(-15).decompress(b[4:])


def game_bytes(rom):
    z = rom[GAME_RZIP:]
    starts, i = [], 1           # word 0 = data length; then xor'd chunk starts until a zero word
    while True:
        w, = struct.unpack_from('>I', z, i * 4); i += 1
        if w == 0:
            break
        starts.append(w ^ GAME_RZIP_XOR)
    code = b''.join(_runzip(z[a:b]) for a, b in zip(starts, starts[1:]))
    return code + _runzip(z[GAME_DATA_RZIP:])


def image(rom=None):
    if rom is None:
        rom = open(ROM, 'rb').read()
    return rom[:0x2D810] + game_bytes(rom) + rom[DEBUGGER[0]:DEBUGGER[0] + DEBUGGER[1]]


if __name__ == '__main__':
    img = image(open(sys.argv[1] if len(sys.argv) > 1 else ROM, 'rb').read())
    if len(sys.argv) > 2:
        open(sys.argv[2], 'wb').write(img)
    print(f'{len(img)} bytes md5 {hashlib.md5(img).hexdigest()}')
