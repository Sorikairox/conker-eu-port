#!/usr/bin/env python3
"""arityscan.py [--slice lo|hi|all] (s87): GLOBAL_ASM functions whose prototype (header or file) has MORE
parameters than the asm uses (s85 recipe 1: a stale a3 home store in drafts / register copies in callers).
For each asm function: live-in arg registers/stack args (protocheck.analyse, includes entry home stores)
vs the O32 slots of every known prototype. Prints `func stem nproto used=<regs> extra=<regs> proto`."""
import sys, os, re, glob
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import protocheck as pc
sl = sys.argv[sys.argv.index('--slice') + 1] if '--slice' in sys.argv else 'lo'
defs, protos, asmf, files = pc.collect()
def inslice(stem):
    m = re.search(r'game\w*_([0-9A-F]+)$', stem.split('/')[-1])
    if not m: return sl == 'all'
    off = int(m.group(1), 16)
    return sl == 'all' or (off < 0x130000) == (sl == 'lo')
for f, stem in sorted(asmf.items()):
    if not inslice(stem) or f not in protos: continue
    path = glob.glob(pc.ASM + '/*/%s.s' % f)
    if not path: continue
    fi = pc.analyse(path[0])
    if fi is None: continue
    live = set(r for r in fi.livein if r in ('a0','a1','a2','a3','f12','f14') or r.startswith('stk'))
    for sig in protos[f]:
        cl = sig.classes()
        if not cl: continue
        exp = pc.expected_regs(cl)
        extra = [r for r in exp if r not in live and not (r in ('f12','f14') and ('a%d' % ((int(r[1:])-12)//2*1)) in live)]
        # only trailing extras are arity evidence
        k = len(exp)
        while k and exp[k-1] in extra: k -= 1
        tail = exp[k:]
        if tail:
            print(f, stem, len(exp), 'used=' + ','.join(sorted(live)), 'extra=' + ','.join(tail), '|', sig.text.strip()[:110])
            break
if '--callers' in sys.argv:
    # second pass: does each asm caller write the extra registers? (s87)
    import collections
    hits = [l.split() for l in open(sys.argv[sys.argv.index('--callers') + 1]) if l.strip()]
    for h in hits:
        f = h[0]; extra = h[4][6:].split(',')
        res = collections.Counter()
        for p in glob.glob(pc.ASM + '/*/*.s'):
            if ('jal ' not in open(p).read()) or (f not in open(p).read()): continue
            fi = pc.analyse(p)
            if fi is None: continue
            for wr in fi.callargs.get(f, []):
                res['writes' if any(r in wr for r in extra if r.startswith('a')) else 'nowrite'] += 1
        print(f, 'extra', ','.join(extra), dict(res))
