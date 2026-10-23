#!/usr/bin/env python3
"""P147: decode SETCIMG / SCISSOR / FILLRECT / TEXRECT of the ?dltracef task in a chrome.log.  rects.py LOG"""
import sys
f = 0
out = []
for l in open(sys.argv[1], errors='replace'):
    if 'dltracef' in l: f = 1; print(l.strip()); continue
    if f and l.startswith('[gfx] task '): break
    if not f or not l.startswith('[gfx]   0x'): continue
    p = l.split(); w0 = int(p[2], 16); w1 = int(p[3], 16); op = w0 >> 24
    a = ((w0 >> 12) & 0xFFF) / 4; b = (w0 & 0xFFF) / 4; c = ((w1 >> 12) & 0xFFF) / 4; d = (w1 & 0xFFF) / 4
    if op == 0xFF: out.append('SETCIMG %08X %08X' % (w0, w1))
    elif op == 0xED: out.append('SCISSOR %g,%g..%g,%g' % (a, b, c, d))
    elif op in (0xF6, 0xE4, 0xE5): out.append('%s %g,%g..%g,%g' % ({0xF6: 'FILL', 0xE4: 'TEXRECT', 0xE5: 'TEXRECTF'}[op], c, d, a, b))
prev, n = None, 0
for o in out + [None]:
    if o == prev: n += 1; continue
    if prev: print('%3d %s' % (n, prev))
    prev, n = o, 1
