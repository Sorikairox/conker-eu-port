#!/usr/bin/env python3
# P148: jal targets of an asm function (decoded address, symbol name, defining file, ASM if asm-only) and data refs.
# usage (in conker/): python3 ../docs/port/sessions/p156/callees.py FUNC
import sys, os, re, glob
f = sys.argv[1]
p = glob.glob('asm/nonmatchings/*/%s.s' % f)[0]; s = open(p).read()
asm = set(re.findall(r'func_[0-9A-F]{8}', open('../port_work/p98/asmonly.txt').read()))
where = {}
for q in glob.glob('src_eu/*.c'):
    t = open(q).read()
    for m in re.finditer(r'(func_[0-9A-F]{8})', t): where.setdefault(m.group(1), set()).add(os.path.basename(q))
defs = {}
for q in glob.glob('src_eu/*.c'):
    t = open(q).read()
    for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/[^/]+/(func_\w+)\.s"\)', t): defs[m.group(1)] = os.path.basename(q)
    for m in re.finditer(r'^[A-Za-z_][^\n;#/=]*\b(func_[0-9A-F]{8})\s*\([^;]*?\)\s*\{', t, re.M): defs.setdefault(m.group(1), os.path.basename(q))
seen = []
for m in re.finditer(r'([0-9A-F]{8}) \*/\s+jal\s+(\w+)', s):
    w, n = int(m.group(1), 16), m.group(2); a = 'func_%08X' % (0x10000000 | ((w & 0x3FFFFFF) << 2))
    if (n, a) in seen: continue
    seen.append((n, a)); print('%-14s jal=%s %-22s %s' % (n, a[5:], defs.get(n, '?'), 'ASM' if n in asm else ''))
print('lines', s.count('\n'), 'data:', ' '.join(sorted(set(re.findall(r'%(?:hi|lo)\((D_\w+)', s)))))
