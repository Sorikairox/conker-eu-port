#!/usr/bin/env python3
"""P36: find packed assets (BE u32 size | deflate) in the ROM whose raw-deflate output length equals the header."""
import zlib, struct, sys, json
rom = open(sys.argv[1], 'rb').read()
start = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x25C000
out = []
off = start; end = len(rom) - 8
while off < end:
    n = struct.unpack_from('>I', rom, off)[0] & 0x7FFFFFFF
    b = rom[off + 4]
    if 16 <= n < 1000000 and (b >> 1) & 3 != 3:
        d = zlib.decompressobj(-15)
        try:
            r = d.decompress(rom[off + 4: off + 4 + n + 1024], n + 1)
            if d.eof and len(r) == n:
                clen = len(rom[off + 4: off + 4 + n + 1024]) - len(d.unused_data)
                out.append((off, n, clen))
                off += 4 + clen
                off = (off + 1) & ~1
                continue
        except zlib.error:
            pass
    off += 2
json.dump(out, open(sys.argv[3] if len(sys.argv) > 3 else 'assets.json', 'w'))
print(len(out), 'assets; sizes', min(x[1] for x in out), max(x[1] for x in out))
