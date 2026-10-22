#!/usr/bin/env python3
"""P84: labelled side-by-side PNG (stdlib only). sbs.py LEFT.png RIGHT.png OUT.png "LEFT LABEL" "RIGHT LABEL" """
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '../../../../port/tools'))
from png2gif import read_png, write_png
F = {  # 5x7 font, rows as 5-bit masks
 'A':[14,17,17,31,17,17,17],'B':[30,17,17,30,17,17,30],'C':[14,17,16,16,16,17,14],'D':[30,17,17,17,17,17,30],
 'E':[31,16,16,30,16,16,31],'F':[31,16,16,30,16,16,16],'G':[14,17,16,23,17,17,15],'H':[17,17,17,31,17,17,17],
 'I':[14,4,4,4,4,4,14],'K':[17,18,20,24,20,18,17],'L':[16,16,16,16,16,16,31],'M':[17,27,21,21,17,17,17],
 'N':[17,25,21,19,17,17,17],'O':[14,17,17,17,17,17,14],'P':[30,17,17,30,16,16,16],'R':[30,17,17,30,20,18,17],
 'S':[15,16,16,14,1,1,30],'T':[31,4,4,4,4,4,4],'U':[17,17,17,17,17,17,14],'W':[17,17,17,21,21,21,10],
 'Y':[17,17,10,4,4,4,4],'0':[14,17,19,21,25,17,14],'1':[4,12,4,4,4,4,14],'2':[14,17,1,2,4,8,31],
 '3':[30,1,1,14,1,1,30],'4':[2,6,10,18,31,2,2],'5':[31,16,30,1,1,17,14],'6':[6,8,16,30,17,17,14],
 '7':[31,1,2,4,8,8,8],'8':[14,17,17,14,17,17,14],'9':[14,17,17,15,1,2,12],' ':[0]*7,'+':[0,4,4,31,4,4,0],
 '-':[0,0,0,31,0,0,0],'(':[2,4,8,8,8,4,2],')':[8,4,2,2,2,4,8],'.':[0,0,0,0,0,12,12],':':[0,12,12,0,12,12,0]}
def img(p):
    w, h, bpp, rows = read_png(p)
    return [[tuple(r[x * bpp:x * bpp + 3]) for x in range(w)] for r in rows]
def text(pix, x, y, s, col, sc=3):
    for ch in s.upper():
        g = F.get(ch, F[' '])
        for ry, m in enumerate(g):
            for rx in range(5):
                if m >> (4 - rx) & 1:
                    for dy in range(sc):
                        for dx in range(sc):
                            yy, xx = y + ry * sc + dy, x + rx * sc + dx
                            if 0 <= yy < len(pix) and 0 <= xx < len(pix[0]): pix[yy][xx] = col
        x += 6 * sc
a, b = img(sys.argv[1]), img(sys.argv[2])
w, h, gap, band = len(a[0]), len(a), 12, 34
out = [[(255, 255, 255)] * (2 * w + gap) for _ in range(h + band)]
for y in range(h):
    out[y + band][:w] = a[y]; out[y + band][w + gap:] = b[y]
text(out, 8, 6, sys.argv[4], (0, 60, 200)); text(out, w + gap + 8, 6, sys.argv[5], (200, 60, 0))
write_png(sys.argv[3], out)
