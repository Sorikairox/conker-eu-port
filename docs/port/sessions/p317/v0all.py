#!/usr/bin/env python3
# P317: v0use over the whole tree: every C function defined `void` in the NM selection of conker/src_eu/*.c, then
# tools/port/v0use.py over conker/asm/nonmatchings; prints only sites whose asm caller READs v0 or f0 (not stale tails).
import re, glob, subprocess, sys
sys.path.insert(0, 'tools/port')
def nmsel(t):
    out, st = [], []
    for l in t.split('\n'):
        s = l.strip()
        if s.startswith('#if'):
            st.append('NM' if 'NON_MATCHING' in s and not s.startswith('#ifndef') else ('NOTNM' if 'NON_MATCHING' in s else 'X'))
        elif s.startswith('#else') and st: st[-1] = {'NM': 'NOTNM', 'NOTNM': 'NM'}.get(st[-1], st[-1])
        elif s.startswith('#endif') and st: st.pop(); continue
        if 'NOTNM' in st: continue
        out.append(l)
    return '\n'.join(out)
voids = {}
for f in sorted(glob.glob('conker/src_eu/*.c')):
    t = nmsel(open(f, errors='replace').read())
    for m in re.finditer(r'^(?:static\s+)?void\s+(func_[0-9A-F]{8})\s*\([^;{]*\)\s*\{', t, re.M):
        voids[m.group(1)] = f.split('/')[-1]
names = sorted(voids)
out = subprocess.run(['python3', 'tools/port/v0use.py', 'conker/asm/nonmatchings'] + names, capture_output=True, text=True).stdout
n = 0
for l in out.splitlines():
    v0 = l.split('v0 ')[1].split(' | ')[0]; f0 = l.split('f0 ')[1]
    if 'READ' in v0 or 'READ' in f0:
        n += 1; print(voids[l.split(' ')[0]], l)
print('void C funcs', len(names), 'asm call sites', len(out.splitlines()), 'reading v0/f0', n)
