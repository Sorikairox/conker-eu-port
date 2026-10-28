#!/usr/bin/env python3
"""P349 test aid: compare and crop canvas shots in pure Python (no Pillow on the host).

  pngtool.py diff A.png B.png            pixels that differ (count, max channel difference, bounding box)
  pngtool.py crop OUT.png X0,Y0,X1,Y1 ZOOM A.png [B.png ...]
        the same box of each input, scaled up ZOOM times (nearest), side by side with a 4-pixel magenta gap
"""
import struct
import sys
import zlib

sys.path.insert(0, __file__.rsplit('/', 1)[0])
from shots_gif import png_read  # noqa: E402  (8-bit RGB / RGBA decoder)


def png_write(path, w, h, rows):
    raw = b''.join(b'\x00' + bytes(r) for r in rows)
    chunk = lambda k, d: struct.pack('>I', len(d)) + k + d + struct.pack('>I', zlib.crc32(k + d) & 0xFFFFFFFF)
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0)) +
                           chunk(b'IDAT', zlib.compress(raw, 6)) + chunk(b'IEND', b''))


def rgb(img, x, y):
    w, h, bpp, rows = img
    r = rows[y]
    return r[x * bpp], r[x * bpp + 1], r[x * bpp + 2]


def diff(a, b):
    A, B = png_read(a), png_read(b)
    if A[:2] != B[:2]:
        print(f'size differs: {A[:2]} vs {B[:2]}')
        return 1
    n, mx, box = 0, 0, [1 << 30, 1 << 30, -1, -1]
    for y in range(A[1]):
        ra, rb = A[3][y], B[3][y]
        if ra == rb:
            continue
        for x in range(A[0]):
            pa, pb = rgb(A, x, y), rgb(B, x, y)
            if pa != pb:
                n += 1
                mx = max(mx, *(abs(p - q) for p, q in zip(pa, pb)))
                box = [min(box[0], x), min(box[1], y), max(box[2], x), max(box[3], y)]
    print(f'{a} vs {b}: {A[0]}x{A[1]}, {n} pixels differ' + (f', max channel diff {mx}, box {box}' if n else ' (identical)'))
    return 0 if n == 0 else 2


def crop(out, box, zoom, inputs):
    x0, y0, x1, y1 = box
    imgs = [png_read(p) for p in inputs]
    W, H = (x1 - x0) * zoom, (y1 - y0) * zoom
    gap = 4
    rows = []
    for Y in range(H):
        line = bytearray()
        for k, img in enumerate(imgs):
            if k:
                line += b'\xff\x00\xff' * gap
            y = y0 + Y // zoom
            for X in range(W):
                line += bytes(rgb(img, x0 + X // zoom, y))
        rows.append(line)
    png_write(out, W * len(imgs) + gap * (len(imgs) - 1), H, rows)
    print(f'{out}: {len(imgs)} x {W}x{H}')


if __name__ == '__main__':
    if sys.argv[1] == 'diff':
        sys.exit(diff(sys.argv[2], sys.argv[3]))
    if sys.argv[1] == 'crop':
        crop(sys.argv[2], [int(v) for v in sys.argv[3].split(',')], int(sys.argv[4]), sys.argv[5:])
