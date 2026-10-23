#!/usr/bin/env python3
# P156: status of functions in a tree: C (default C / NM body) or ASM (GLOBAL_ASM only). usage: isasm.py ROOT func...
import sys, re, glob, os
root = sys.argv[1]; fs = sys.argv[2:]
src = {q: open(q, errors='replace').read() for q in glob.glob(root + '/conker/src_eu/*.c') + glob.glob(root + '/conker/src_eu/nm_asm/*')}
for f in fs:
    ga = [os.path.basename(q) for q, t in src.items() if re.search(r'GLOBAL_ASM\("[^"]*/%s\.s"\)' % f, t)]
    cd = [os.path.basename(q) for q, t in src.items() if re.search(r'^[A-Za-z_][^\n;#/=]*\b%s\s*\([^;]*?\)\s*\{' % f, t, re.M)]
    print('%-14s %-4s asm:%s c:%s' % (f, 'C' if cd else 'ASM', ','.join(ga), ','.join(cd)))
