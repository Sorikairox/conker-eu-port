#!/usr/bin/env python3
# P47: list inserted NON_MATCHING bodies whose asm calls a libultra 64-bit helper, or whose C uses u64/s64.
import re, glob, os
R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../conker')
H = {}
for l in open(R + '/symbol_addrs.eu.txt'):
    m = re.match(r'(__u?ll_\w+)\s*=\s*0x([0-9A-Fa-f]+)', l)
    if m: H['%08X' % (0x0C000000 | ((int(m.group(2), 16) & 0x0FFFFFFF) >> 2))] = m.group(1)
names = set(H.values())
blk = re.compile(r'#ifdef NON_MATCHING\n(.*?)#else\n#pragma GLOBAL_ASM\("([^"]*)/(\w+)\.s"\)\n#endif', re.S)
for p in sorted(glob.glob(R + '/src_eu/**/*.c', recursive=True)):
    s = open(p).read()
    for m in blk.finditer(s):
        body, d, f = m.group(1), m.group(2), m.group(3)
        sp = os.path.join(R, d, f + '.s')
        why = set()
        if os.path.exists(sp):
            a = open(sp).read()
            for w, n in H.items():
                if w in a: why.add(n)
            for n in names:
                if re.search(r'\b%s\b' % n, a): why.add(n)
        cu = bool(re.search(r'\b(u64|s64|unsigned long long|long long)\b', body))
        if why or cu:
            print('%s\t%s\tasm=%s\tC64=%d' % (f, os.path.relpath(p, R), ','.join(sorted(why)) or '-', cu))
