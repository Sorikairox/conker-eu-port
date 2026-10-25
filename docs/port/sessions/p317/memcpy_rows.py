#!/usr/bin/env python3
# P317: registry rows whose function's asm calls memcpy (jal 10023360) but whose knobs / setup files never set
# DIFFTEST_OUTA=10023360 (P301: the memcpy stub copies nothing, so edits of memcpy'd data go unseen).
import glob, re, os
asm = set()
for p in glob.glob('conker/asm/nonmatchings/*/*.s'):
    if re.search(r'jal\s+(memcpy|func_10023360)\b', open(p, errors='replace').read()):
        asm.add(os.path.basename(p)[:-2])
n = 0
for l in open('tools/port/verify_registry.tsv'):
    r = l.rstrip('\n').split('\t')
    if len(r) < 6 or r[0] not in asm: continue
    txt = r[3]
    for f in r[2].split(','):
        if f and os.path.exists(f): txt += '\n' + open(f, errors='replace').read()
    if re.search(r'OUTA=\S*10023360', txt): continue
    n += 1
    print('\t'.join([r[0], r[1], r[5], 'HARNESS' if 'HARNESS=' in r[3] else '-']))
print('rows', n, 'memcpy funcs', len(asm))
