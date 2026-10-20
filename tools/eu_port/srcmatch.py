#!/usr/bin/env python3
"""s89: find unmatched functions whose opcode sequence resembles a function compiled
from known source. usage: srcmatch.py <objdir> [--slice lo|hi|all] [--min 8] [--thr 0.8]
<objdir>: dir of IDO .o files (compiled reference source, e.g. banjo-kazooie core1).
Disassembles them in the container, compares opcode sequences (difflib) to every
GLOBAL_ASM function of the slice. Prints ratio, conker func, size, ref obj:func, size."""
import os, re, subprocess, sys, difflib, collections, glob
R = os.environ.get('CONKER_ROOT', os.path.expanduser('~/conker'))
C = os.environ.get('CONKERDEV', 'conkerdev')
a = sys.argv[1:]; objdir = os.path.abspath(a[0])
def opt(n, d):
    return type(d)(a[a.index(n)+1]) if n in a else d
sl = opt('--slice', 'lo'); mn = opt('--min', 8); thr = opt('--thr', 0.8)
os.environ['PATH'] += ':/Applications/Docker.app/Contents/Resources/bin'
ref = {}
rel = os.path.relpath(objdir, R)
out = subprocess.run(['docker', 'exec', C, 'bash', '-c',
    f'for o in /conker/{rel}/*.o; do echo "@@ $o"; mips-linux-gnu-objdump -d --no-show-raw-insn $o; done'],
    capture_output=True, text=True).stdout
cur = None; obj = None
for l in out.splitlines():
    if l.startswith('@@ '): obj = os.path.basename(l[3:]); continue
    m = re.match(r'^[0-9a-f]+ <([^>]+)>:', l)
    if m: cur = (obj, m.group(1)); ref[cur] = []; continue
    m = re.match(r'^\s+[0-9a-f]+:\s+(\S+)', l)
    if m and cur: ref[cur].append(m.group(1))
for k in list(ref):
    while ref[k] and ref[k][-1] == 'nop': ref[k].pop()
    if len(ref[k]) < mn: del ref[k]
lst = subprocess.run(['python3', f'{R}/tools/eu_port/m2c/list.py'], capture_output=True, text=True).stdout
mine = {}
for l in lst.splitlines():
    p = l.split()
    if len(p) < 3 or not p[1].startswith('src_eu/'): continue
    f = p[1]; fn = p[2]
    m = re.search(r'_([0-9A-F]+)\.c$', f)
    if sl == 'init':
        if not os.path.basename(f).startswith('init'): continue
    elif sl != 'all':
        if not (os.path.basename(f).startswith('game') and m): continue
        off = int(m.group(1), 16)
        if (sl == 'lo') != (off < 0x130000): continue
    stem = f[7:-2]
    s = f'{R}/conker/asm/nonmatchings/{stem}/{fn}.s'
    if not os.path.exists(s): continue
    ops = re.findall(r'^\s*/\*\s*[0-9A-F]+ [0-9A-F]+ [0-9A-F]+ \*/\s+(\S+)', open(s).read(), re.M)
    while ops and ops[-1] == 'nop': ops.pop()
    if len(ops) >= mn: mine[(f, fn)] = ops
def norm(o):
    return {'b': 'beq', 'beqz': 'beq', 'bnez': 'bne', 'negu': 'subu', 'move': 'or', 'li': 'addiu'}.get(o, o)
for d in (ref, mine):
    for k in d: d[k] = [norm(o) for o in d[k]]
res = []
for (f, fn), ops in mine.items():
    hm = collections.Counter(ops)
    for (o, rf), rops in ref.items():
        if not 0.8 <= len(rops) / len(ops) <= 1.25: continue
        hr = collections.Counter(rops)
        if sum((hm & hr).values()) / max(len(ops), len(rops)) < thr: continue
        r = difflib.SequenceMatcher(None, ops, rops, autojunk=False).ratio()
        if r >= thr: res.append((r, fn, len(ops), f'{o}:{rf}', len(rops), f))
res.sort(reverse=True)
seen = set()
key = 3 if "--byref" in a else 1
for r in res:
    if r[key] in seen: continue
    seen.add(r[key]); print(f'{r[0]:.2f} {r[1]} {r[2]} {r[3]} {r[4]} {r[5]}')
