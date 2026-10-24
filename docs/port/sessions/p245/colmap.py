#!/usr/bin/env python3
"""P245: top-down map of a [p245tri] dump. colmap.py TRI.txt OUT.png [CELL] [marks x,z;x,z...] [path x,z;...]
Floor = triangles with normal y > 0.5 (upward); each cell keeps the highest floor at its centre (barycentric).
Colour: height (blue low .. red high), flag low byte hue tint; walls (|ny| < 0.5) drawn dark. North = -z up."""
import sys, zlib, struct, math
T = []
for ln in open(sys.argv[1]):
    p = ln.split()
    if len(p) < 12: continue
    v = list(map(int, p[2:11])); T.append((int(p[0]), int(p[1]), v, p[11]))
C = int(sys.argv[3]) if len(sys.argv) > 3 else 25
xs = [t[2][i] for t in T for i in (0, 3, 6)]; zs = [t[2][i] for t in T for i in (2, 5, 8)]
X0, X1, Z0, Z1 = min(xs), max(xs), min(zs), max(zs)
import os
if os.environ.get('CROP'): X0, X1, Z0, Z1 = map(int, os.environ['CROP'].split(','))
W, H = (X1 - X0) // C + 1, (Z1 - Z0) // C + 1
hgt = [[None] * W for _ in range(H)]; flg = [[None] * W for _ in range(H)]; wall = [[0] * W for _ in range(H)]
for a, i, v, fl in T:
    (x0, y0, z0), (x1, y1, z1), (x2, y2, z2) = v[0:3], v[3:6], v[6:9]
    ux, uy, uz = x1 - x0, y1 - y0, z1 - z0; wx, wy, wz = x2 - x0, y2 - y0, z2 - z0
    nx, ny, nz = uy * wz - uz * wy, uz * wx - ux * wz, ux * wy - uy * wx
    L = math.sqrt(nx * nx + ny * ny + nz * nz) or 1
    ny /= L
    det = (z1 - z2) * (x0 - x2) + (x2 - x1) * (z0 - z2)
    cx0, cx1 = (min(x0, x1, x2) - X0) // C, (max(x0, x1, x2) - X0) // C
    cz0, cz1 = (min(z0, z1, z2) - Z0) // C, (max(z0, z1, z2) - Z0) // C
    for cz in range(max(0, cz0), min(H - 1, cz1) + 1):
        for cx in range(max(0, cx0), min(W - 1, cx1) + 1):
            px, pz = X0 + cx * C + C / 2, Z0 + cz * C + C / 2
            if det == 0:
                continue
            l0 = ((z1 - z2) * (px - x2) + (x2 - x1) * (pz - z2)) / det
            l1 = ((z2 - z0) * (px - x2) + (x0 - x2) * (pz - z2)) / det
            l2 = 1 - l0 - l1
            if min(l0, l1, l2) < -0.02: continue
            y = l0 * y0 + l1 * y1 + l2 * y2
            if abs(ny) < 0.5: wall[cz][cx] = 1; continue
            if ny < 0: continue
            if hgt[cz][cx] is None or y > hgt[cz][cx]: hgt[cz][cx] = y; flg[cz][cx] = fl
ys = [h for r in hgt for h in r if h is not None]; ymin, ymax = min(ys), max(ys)
if os.environ.get('YR'): ymin, ymax = map(float, os.environ['YR'].split(','))
def col(cz, cx):
    h = hgt[cz][cx]
    if wall[cz][cx] and h is None: return (40, 40, 40)
    if h is None: return (0, 0, 0)
    t = min(1, max(0, (h - ymin) / (ymax - ymin + 1e-9)))
    r, g, b = int(255 * t), int(255 * (1 - abs(2 * t - 1))), int(255 * (1 - t))
    f = flg[cz][cx]
    if f not in ("0", "FFFFFFFF", "-1"):
        k = int(f, 16) & 0xF
        if k == 5: r, g, b = r // 2, g // 2, 255   # flag 5: tint blue (water?)
        elif k == 4: r, g, b = 255, g, b // 2
        elif k == 1: r, g, b = r, 255, b
    if wall[cz][cx]: r, g, b = r // 2, g // 2, b // 2
    return (r, g, b)
img = [[col(cz, cx) for cx in range(W)] for cz in range(H)]
def mark(spec, c):
    for m in spec.split(';'):
        if not m: continue
        x, z = map(float, m.split(',')[:2]); cx, cz = int((x - X0) // C), int((z - Z0) // C)
        for dz in range(-2, 3):
            for dx in range(-2, 3):
                if 0 <= cz + dz < H and 0 <= cx + dx < W: img[cz + dz][cx + dx] = c
if len(sys.argv) > 4: mark(sys.argv[4], (255, 255, 255))
if len(sys.argv) > 5: mark(sys.argv[5], (255, 0, 255))
SC = int(os.environ.get('SCALE', '1'))
img = [[px for px in row for _ in range(SC)] for row in img for _ in range(SC)]
W, H = W * SC, H * SC
raw = b''.join(b'\0' + bytes(c for px in row for c in px) for row in img)   # row 0 = min z (north up if -z is north)
def chunk(t, d): return struct.pack('>I', len(d)) + t + d + struct.pack('>I', zlib.crc32(t + d) & 0xffffffff)
open(sys.argv[2], 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', W, H, 8, 2, 0, 0, 0)) + chunk(b'IDAT', zlib.compress(raw)) + chunk(b'IEND', b''))
print(f"grid {W}x{H} cell {C}: x {X0}..{X1} z {Z0}..{Z1} floor y {ymin:.0f}..{ymax:.0f}")
