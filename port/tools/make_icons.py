#!/usr/bin/env python3
"""P375: the page's plain generic app icon (no game art): a dark rounded square with a light ring and a play triangle.

    python3 port/tools/make_icons.py port/web     writes icon-192.png, icon-512.png (icon.svg is the same picture)

Pure Python (zlib PNG writer, 3x3 supersampling); nothing derived from the ROM.
"""
import os, struct, sys, zlib

BG, FG = (0x1f, 0x24, 0x2e), (0xf2, 0xc1, 0x4e)


def inside(x, y):   # unit coordinates 0..1 -> 'bg' | 'fg' | None (outside the rounded square)
    r = 0.18
    cx, cy = min(max(x, r), 1 - r), min(max(y, r), 1 - r)
    if (x - cx) ** 2 + (y - cy) ** 2 > r * r:
        return None
    d2 = (x - 0.5) ** 2 + (y - 0.5) ** 2
    if 0.30 ** 2 <= d2 <= 0.36 ** 2:   # ring
        return 'fg'
    # play triangle: (0.42, 0.33) (0.42, 0.67) (0.68, 0.5)
    if x >= 0.42 and abs(y - 0.5) <= (0.68 - x) * (0.17 / 0.26):
        return 'fg'
    return 'bg'


def png(size, path):
    ss = 3; rows = []
    for py in range(size):
        row = bytearray([0])
        for px in range(size):
            acc = [0, 0, 0, 0]
            for sy in range(ss):
                for sx in range(ss):
                    k = inside((px + (sx + 0.5) / ss) / size, (py + (sy + 0.5) / ss) / size)
                    if k:
                        c = FG if k == 'fg' else BG
                        acc[0] += c[0]; acc[1] += c[1]; acc[2] += c[2]; acc[3] += 255
            n = ss * ss; a = acc[3] // n
            row += bytes([acc[0] // max(1, acc[3] // 255), acc[1] // max(1, acc[3] // 255), acc[2] // max(1, acc[3] // 255), a] if a else [0, 0, 0, 0])
        rows.append(bytes(row))
    chunk = lambda t, d: struct.pack('>I', len(d)) + t + d + struct.pack('>I', zlib.crc32(t + d) & 0xffffffff)
    data = b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', size, size, 8, 6, 0, 0, 0)) \
        + chunk(b'IDAT', zlib.compress(b''.join(rows), 9)) + chunk(b'IEND', b'')
    open(path, 'wb').write(data)


out = sys.argv[1] if len(sys.argv) > 1 else 'port/web'
for s in (192, 512):
    png(s, os.path.join(out, f'icon-{s}.png'))
