#!/usr/bin/env python3
"""P78: turn the [p78hex] texture dumps of a boot log (?p78tex=N) into PNGs (x8 nearest zoom) + a contact sheet.
   python3 port/tools/p78tex.py BOOT.LOG OUTDIR"""
import sys, os, zlib, struct

def png(path, w, h, rows):
    raw = b''.join(b'\0' + bytes(r) for r in rows)
    def chunk(t, d): return struct.pack('>I', len(d)) + t + d + struct.pack('>I', zlib.crc32(t + d) & 0xffffffff)
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 6, 0, 0, 0))
                           + chunk(b'IDAT', zlib.compress(raw)) + chunk(b'IEND', b''))

log, out = sys.argv[1], sys.argv[2]
os.makedirs(out, exist_ok=True)
texs, cur = [], None
for line in open(log, errors='replace'):
    if not line.startswith('[p78hex] '): continue
    s = line[9:].strip()
    if s.startswith('T'):
        name, _, _, _, tile, dims = s.split()[:6]
        w, h = map(int, dims.split('x')); cur = [name + '_tile' + tile, w, h, []]; texs.append(cur)
    elif cur: cur[3].append(bytes.fromhex(s))
Z = 8
for name, w, h, rows in texs:
    big = []
    for r in rows:
        line = b''.join(r[4 * x:4 * x + 4] * Z for x in range(w))
        big += [line] * Z
    png(os.path.join(out, name + '.png'), w * Z, len(rows) * Z, big)
print(len(texs), 'textures ->', out)
