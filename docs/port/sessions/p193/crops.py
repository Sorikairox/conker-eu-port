#!/usr/bin/env python3
"""P193: tile crops of several shots into one PNG with labels.  crops.py OUT.png X0 Y0 X1 Y1 SHOT.png[=LABEL]..."""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../../../port/tools'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../p84'))
from png2gif import read_png, write_png
out, x0, y0, x1, y1 = sys.argv[1], *map(int, sys.argv[2:6])
ST = int(os.environ.get("STEP", "1"))
cells = []
for a in sys.argv[6:]:
    p, _, lab = a.partition('=')
    w, h, bpp, rows = read_png(p)
    cells.append(([[tuple(r[x * bpp:x * bpp + 3]) for x in range(x0, x1, ST)] for r in rows[y0:y1:ST]], lab or os.path.basename(p)))
cw, ch, cols = len(cells[0][0][0]), len(cells[0][0]) + 24, 4
nr = (len(cells) + cols - 1) // cols
pix = [[(0, 0, 0)] * (cw * cols) for _ in range(ch * nr)]
F = {}
try:
    src = open(os.path.join(os.path.dirname(__file__), '../p84/sbs.py')).read()
    F = eval(src[src.index('F = {') + 4:src.index('}\n', src.index('F = {')) + 1])
except Exception: pass
def text(x, y, s):
    for c in s.upper():
        for ry, m in enumerate(F.get(c, [0] * 7)):
            for rx in range(5):
                if m >> (4 - rx) & 1:
                    for d in range(4):
                        yy, xx = y + ry * 2 + d // 2, x + rx * 2 + d % 2
                        if yy < len(pix) and xx < len(pix[0]): pix[yy][xx] = (255, 255, 0)
        x += 12
for i, (c, lab) in enumerate(cells):
    ox, oy = (i % cols) * cw, (i // cols) * ch
    text(ox + 4, oy + 4, lab)
    for y, r in enumerate(c):
        pix[oy + 24 + y][ox:ox + cw] = r
write_png(out, pix)
