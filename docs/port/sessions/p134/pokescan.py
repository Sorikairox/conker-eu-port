#!/usr/bin/env python3
# P134: setup files (docs/port/sessions/p*/*.txt, knobs.sh format: name ! ARG ! POKE ! ...) whose DIFFTEST_POKE words
# fall into the ROM image's .data / .rodata: before P132 the image overwrote them (.data in odd trials, .rodata always).
# Run inside the container from /conker/conker:  python3 ../docs/port/sessions/p134/pokescan.py
import sys, re, glob
sys.path.insert(0, '../tools/port/difftest')
import difftest as D

rng = [(v, v + len(b), k) for v, b, k in D.image() if k in ('data', 'rodata')]
def kind(a):
    for lo, hi, k in rng:
        if lo <= a < hi: return k
for f in sorted(glob.glob('../docs/port/sessions/p*/*.txt')):
    n = nd = nr = 0; addrs = set()
    for line in open(f, errors='replace'):
        if line.lstrip().startswith('#') or line.count('!') < 2: continue
        poke = line.split('!')[2]
        n += 1; hd = hr = False
        for m in re.finditer(r'([0-9A-Fa-f]{8})=', poke):
            k = kind(int(m.group(1), 16))
            if k: addrs.add('%s:%s' % (m.group(1).upper(), k[0]))
            hd |= k == 'data'; hr |= k == 'rodata'
        nd += hd; nr += hr
    if nd or nr: print('%s\t%d setups\t%d data\t%d rodata\t%s' % (f[3:], n, nd, nr, ','.join(sorted(addrs))[:200]))
