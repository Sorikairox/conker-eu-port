#!/usr/bin/env python3
"""s147: rank files by global symbols shared across their GLOBAL_ASM functions.

usage: sharedsym.py [lo|init|hi|all] [min_funcs=3] [top=40]
Prints: n_asm  asm_insns  file  symbol  [extern decl in file]  funcs (insns, nearmiss key)
A symbol used by several asm functions of one file is a candidate for one struct type
(s143 recipe 1). Nearmiss keys come from docs/sessions/s141_nearmiss.txt when present.
"""
import glob, os, re, sys, collections
root = os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker'))
os.chdir(root + '/conker')
which = sys.argv[1] if len(sys.argv) > 1 else 'lo'
minf = int(sys.argv[2]) if len(sys.argv) > 2 else 3
top = int(sys.argv[3]) if len(sys.argv) > 3 else 40

def inslice(stem):
    if stem.startswith('init'):
        return which in ('init', 'all')
    m = re.match(r'game_(?:eu_)?([0-9A-F]+)$', stem)
    if not m:
        return False
    off = int(m.group(1), 16)
    if which == 'lo': return off < 0x130000
    if which == 'hi': return off >= 0x130000
    return which == 'all'

nm = {}
nmf = root + '/docs/sessions/s141_nearmiss.txt'
if os.path.exists(nmf):
    for l in open(nmf):
        m = re.match(r'((?:DIFF|SIZE)[+-]?\d+|OK|CERR)\s+(func_[0-9A-F]+)', l)
        if m and m.group(2) not in nm:
            nm[m.group(2)] = m.group(1)

rows = []
for p in sorted(glob.glob('src_eu/*.c')):
    stem = os.path.basename(p)[:-2]
    if not inslice(stem):
        continue
    src = open(p).read()
    use = collections.defaultdict(list)
    for s in re.findall(r'#pragma GLOBAL_ASM\("([^"]+)"\)', src):
        if not os.path.exists(s):
            continue
        txt = open(s).read()
        f = os.path.basename(s)[:-2]
        n = len(re.findall(r'^\s*/\*\s+[0-9A-F]+ [0-9A-F]+ [0-9A-F]{8} \*/', txt, re.M))
        for sym in set(re.findall(r'%(?:hi|lo)\(((?:D|B)_\w+)\)', txt)):
            use[sym].append((f, n))
    for sym, fl in use.items():
        if len(fl) >= minf:
            m = re.search(r'^.*\b' + re.escape(sym) + r'\b.*;', src, re.M)
            decl = m.group(0).strip()[:50] if m and 'extern' in m.group(0) else ''
            rows.append((len(fl), sum(n for _, n in fl), stem, sym, decl,
                         ' '.join('%s(%d,%s)' % (f[5:], n, nm.get(f, '-')) for f, n in sorted(fl))))
rows.sort(key=lambda r: (-r[0], r[1]))
for r in rows[:top]:
    print('%2d %5d %-16s %-14s [%s] %s' % r)
