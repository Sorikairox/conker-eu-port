#!/usr/bin/env python3
"""P252 (from P245; env YMAX = ignore floors above it): text grid of the highest upward floor per cell from a [p248tri] dump.
colgrid.py TRI.txt X0 X1 Z0 Z1 STEP  -> rows z (top = Z0), cells 'hhf': h = y/100 (rounded, signed), f = flag low hex digit; '.' none."""
import sys, math, os
YMAX = float(os.environ.get("YMAX", "1e9"))  # P252: ignore floors above YMAX
T = []
for ln in open(sys.argv[1]):
    p = ln.split()
    if len(p) >= 12: T.append((list(map(int, p[2:11])), p[11]))
X0, X1, Z0, Z1, S = map(int, sys.argv[2:7])
def floor(px, pz):
    best = None
    for v, fl in T:
        (x0, y0, z0), (x1, y1, z1), (x2, y2, z2) = v[0:3], v[3:6], v[6:9]
        if px < min(x0, x1, x2) or px > max(x0, x1, x2) or pz < min(z0, z1, z2) or pz > max(z0, z1, z2): continue
        det = (z1 - z2) * (x0 - x2) + (x2 - x1) * (z0 - z2)
        if det == 0: continue
        l0 = ((z1 - z2) * (px - x2) + (x2 - x1) * (pz - z2)) / det; l1 = ((z2 - z0) * (px - x2) + (x0 - x2) * (pz - z2)) / det
        if min(l0, l1, 1 - l0 - l1) < 0: continue
        ux, uy, uz = x1 - x0, y1 - y0, z1 - z0; wx, wy, wz = x2 - x0, y2 - y0, z2 - z0
        nx, ny, nz = uy * wz - uz * wy, uz * wx - ux * wz, ux * wy - uy * wx
        ny /= math.sqrt(nx * nx + ny * ny + nz * nz) or 1
        if ny < 0.5: continue
        y = l0 * y0 + l1 * y1 + (1 - l0 - l1) * y2
        if y > YMAX: continue
        if best is None or y > best[0]: best = (y, fl)
    return best
print("      " + "".join(f"{x:>5}" for x in range(X0, X1 + 1, S)))
for z in range(Z0, Z1 + 1, S):
    row = []
    for x in range(X0, X1 + 1, S):
        b = floor(x, z)
        row.append("    ." if b is None else f"{round(b[0] / 100):>4}{(b[1][-1] if b[1] not in ('FFFFFFFF',) else '?')}")
    print(f"{z:>6}" + "".join(row))
