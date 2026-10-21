#!/usr/bin/env python3
"""host side of tools/port/nmrepair.sh (see there)"""
import sys as _pgs, os as _pgo; _pgs.path.insert(0, _pgo.path.dirname(_pgo.path.abspath(__file__))); import portguard  # wrong-checkout guard (P7)
import sys, os, re, glob, subprocess, shutil

R = os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker'))
a = sys.argv[1:]
if not a: print(open(os.path.join(R, 'tools/port/nmrepair.sh')).read()); sys.exit(2)
func = a[0]; trials = '32'; wide = shutil.get_terminal_size((200, 40)).columns
draft = None; i = 1
while i < len(a):
    if a[i] == '--trials': trials = a[i + 1]; i += 2; continue
    if a[i] == '--wide': wide = int(a[i + 1]); i += 2; continue
    draft = a[i]; i += 1
if draft is None:
    c = sorted(glob.glob(os.path.join(R, 'port_work/*/best/%s.c' % func)) + glob.glob(os.path.join(R, 'port_work/*/pass/%s.c' % func)),
               key=os.path.getmtime)
    if not c: print('no draft for %s in port_work/*/best (run convert.py first or pass one)' % func); sys.exit(2)
    draft = c[-1]
    res = os.path.join(os.path.dirname(os.path.dirname(draft)), 'results.tsv')
    if os.path.exists(res):
        for l in open(res):
            if l.startswith(func + '\t'): print('convert: ' + ' | '.join(l.rstrip('\n').split('\t')[1:])[:wide])
print('== draft %s' % os.path.relpath(draft, R))
p = subprocess.run([os.path.join(R, 'tools/port/difftest.sh'), func, draft, '-v', '--trials', trials], capture_output=True, text=True)
out = (p.stdout + p.stderr).rstrip('\n').split('\n')
show = [l for l in out if not re.match(r'trial \d+: same ', l)]
print('\n'.join(show[-60:]))
code = open(draft).read().rstrip('\n').split('\n')
asmp = glob.glob(os.path.join(R, 'conker/asm/nonmatchings/**/%s.s' % func), recursive=True)
asm = []
for l in (open(asmp[0]) if asmp else []):
    m = re.match(r'\s*/\*\s*\w+\s+([0-9A-F]+)\s+[0-9A-F]+\s*\*/\s+(.*)$', l)
    if m: asm.append('%s %s' % (m.group(1)[-4:], re.sub(r'\s+', ' ', m.group(2)))); continue
    if re.match(r'\s*\.L\w+:', l): asm.append(l.strip())
half = max(60, (wide - 3) // 2)
print('== draft | asm (%d lines | %d insns+labels)' % (len(code), len(asm)))
for k in range(max(len(code), len(asm))):
    l = ('%3d %s' % (k + 1, code[k].replace('\t', '    '))) if k < len(code) else ''
    r = asm[k] if k < len(asm) else ''
    print('%-*s | %s' % (half, l[:half], r))
