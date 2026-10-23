#!/usr/bin/env python3
# P150 (port-b copy: lists port-b's own files instead): P145: asm-only functions in slot `port`'s files (not port-b's forbidden list, not files holding func_1513CFE4
# handlers per port-b P142.md) with insns and C call sites (NON_MATCHING branches selected, comments stripped).
# run from the worktree root after progress_nm.py --list > port_work/p162/asmonly.txt
import re, glob, os, sys
sys.path.insert(0, 'docs/port/sessions/p95')
forbid = set("""game_eu_170760 game_169510 game_eu_4A070 game_eu_78230 game_eu_C2B60 game_eu_C5530 game_eu_CE0A0 game_14FF90
game_eu_48B10 game_eu_158110 game_eu_15A210 game_34F20 game_eu_1EC610 game_A28B0 game_eu_175B20 game_eu_15C660 game_eu_E0430
game_eu_156560 game_eu_156A30 game_eu_15C370 game_eu_13DC30 game_eu_1A5190 game_eu_1ACBC0 game_eu_1B1010 game_eu_1B1ED0
game_eu_13A8A0 game_eu_15B2E0 game_D5030 game_eu_F5580 game_eu_D4C90 game_eu_13B700 game_eu_1772D0 game_eu_1A6C30 game_1944C0
game_eu_193A00 game_eu_1A7B30 game_eu_138E00 game_eu_1B5C40 game_BC510 game_eu_186A80 game_eu_D3880 game_eu_D4550
game_eu_197680 game_eu_EF6D0 game_eu_EF410 game_eu_EF370 game_eu_1CE7D0 game_eu_E0170 game_eu_E17A0 game_eu_1D9C00
game_eu_11CB90 game_eu_12A7C0 game_eu_12E390 game_eu_AF2A0 game_eu_E7BC0 game_eu_1B7D70 game_eu_1DDE10 game_eu_1BE5C0
game_eu_1D3420 game_2062D0 game_eu_AE930 game_eu_17D3C0 game_eu_1EDA00 game_eu_1D5710 game_eu_1984F0 game_eu_1D4CC0 game_eu_201240 game_eu_125200 game_eu_12C0B0 game_eu_12BB30 game_eu_12D5D0 game_eu_1F4090
game_eu_F6060 game_eu_192500 game_eu_1BAF40 game_eu_1FB080""".split())
cfe4 = 'E7BC0 FABD0 11CB90 12A7C0 12E390 169510 16DC80 1B7D70 1BAF40 1BE5C0 1C3530 1D3420 1DDE10'.split()
def nm_select(t):
    out, st = [], []
    for l in t.split('\n'):
        s = l.strip()
        if s.startswith('#if'):
            st.append('NM' if 'NON_MATCHING' in s and not s.startswith('#ifndef') else ('NOTNM' if 'NON_MATCHING' in s else 'X'))
        elif s.startswith('#else') and st:
            st[-1] = {'NM': 'NOTNM', 'NOTNM': 'NM'}.get(st[-1], st[-1])
        elif s.startswith('#endif') and st: st.pop()
        elif 'NOTNM' not in st: out.append(l)
    return '\n'.join(out)
code = ''
for p in glob.glob('conker/src_eu/**/*.c', recursive=True):
    t = re.sub(r'/\*.*?\*/', '', open(p, errors='replace').read(), flags=re.S)
    t = re.sub(r'//[^\n]*', '', nm_select(t))
    code += '\n'.join(l for l in t.split('\n') if 'GLOBAL_ASM' not in l) + '\n'
from collections import Counter
calls_c, tok_c, paren_c = Counter(), Counter(), Counter()
for l in code.split('\n'):
    for m in re.finditer(r'\b(\w+)\b(\s*\()?', l):
        tok_c[m.group(1)] += 1
        if m.group(2):
            paren_c[m.group(1)] += 1
            pre = l[:m.start()]
            if not re.match(r'^\s*(extern\s+|static\s+)?[A-Za-z_][\w\s\*]*\**\s*$', pre) or 'return' in pre: calls_c[m.group(1)] += 1
# P162: functions defined in C under NM (one NM block can hold several functions: func_150A6070 in D3880's P130
# block was listed as asm-only) are dropped
cdefs = set(re.findall(r'^(?:static\s+)?[A-Za-z_][\w\s\*]*?\b(func_[0-9A-F]{8})\s*\([^;{]*\)\s*\{', code, re.M))
rows = []
for line in open('port_work/p162/asmonly.txt'):
    p = line.rstrip('\n').split('\t')
    if len(p) != 3 or not p[1].isdigit(): continue
    fn, n, f = p
    if f not in forbid or 'hand' in f or fn in cdefs: continue
    rows.append((int(n), f, fn, calls_c[fn], tok_c[fn] - paren_c[fn]))
rows.sort()
print('asm-only in port files:', len(rows), 'with C calls:', sum(1 for r in rows if r[3]), 'with C refs:', sum(1 for r in rows if r[4]))
for r in rows:
    if r[3] or r[4] or '--all' in sys.argv: print('%5d %-18s %s calls=%d refs=%d' % r)
