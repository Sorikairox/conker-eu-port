#!/usr/bin/env python3
"""collect.py > list : hi-slice (game >= 0x130000 + debugger) GLOBAL_ASM functions that have
drafts in docs/sessions/*_drafts/ or tools/decomp-permuter/nm/*/best.c; 'func path' lines.
Functions mentioned next to 'handwritten' anywhere in docs are skipped (stderr)."""
import os, re, glob, subprocess, sys
R = os.environ.get('CONKER_ROOT')
out = subprocess.run(['python3', R + '/tools/eu_port/m2c/list.py'], capture_output=True, text=True).stdout
asm = {}
for l in out.splitlines():
    p = l.split()
    if len(p) < 3: continue
    stem = os.path.basename(p[1])[:-2]
    m = re.search(r'_([0-9A-F]+)$', stem)
    hi = 'debugger' in p[1] or (stem.startswith('game') and m and int(m.group(1), 16) >= 0x130000)
    if hi: asm[p[2]] = stem
hw = set()
for doc in glob.glob(R + '/docs/**/*.md', recursive=True) + [R + '/HANDOFF.md']:
    for l in open(doc, errors='ignore'):
        if 'handwritten' in l.lower():
            hw.update(re.findall(r'func_[0-9A-F]{8}', l))
res = []
for f in sorted(asm):
    if f in hw: print('skip-hw', f, file=sys.stderr); continue
    c = glob.glob(R + '/docs/sessions/*_drafts/%s*.c' % f) + glob.glob(R + '/docs/sessions/*_drafts/*/%s*.c' % f)
    b = R + '/tools/decomp-permuter/nm/%s/best.c' % f
    if os.path.exists(b): c.append(b)
    for x in sorted(set(c)): print(f, x)
