#!/usr/bin/env python3
# P221: moved to tools/port (used by tools/port/reverify.sh). Run from the repo root.
# P214: write the NM C of FUNC (the NON_MATCHING block holding its definition, or the plain definition) to OUT, for
# difftest runs where --self fails (externs declared inside the NM block, or C in another file than the asm).
import sys, re, glob, os
fn, out = sys.argv[1:3]
for p in sorted(glob.glob('conker/src_eu/*.c')):
    t = open(p).read()
    m = re.search(r'^[A-Za-z_][^\n;#/=]*\b%s\s*\([^;{]*\)\s*\{' % fn, t, re.M)
    if not m: continue
    a = t.rfind('#ifdef NON_MATCHING\n', 0, m.start()); e = t.rfind('#endif', 0, m.start())
    if a >= 0 and a > e:
        b = t.index('\n#else\n', m.start()); s = t[a + len('#ifdef NON_MATCHING\n'):b + 1]
        # P235: NMBLOCK_WHOLE=1 writes the whole block (`#ifdef NON_MATCHING` .. `#endif`), i.e. the session draft's
        # text: line-numbered mutants (`51s/../../`) were written against the draft, so the body alone is one line off
        if os.environ.get('NMBLOCK_WHOLE'): s = t[a:t.index('\n#endif', b) + len('\n#endif')] + '\n'
    else:
        i = m.end() - 1; d = 0
        while True:
            d += {'{': 1, '}': -1}.get(t[i], 0); i += 1
            if d == 0: break
        s = t[m.start():i] + '\n'
    n = len(re.findall(r'^[A-Za-z_][^\n;#/=]*\bfunc_[0-9A-Fa-f_]+\s*\([^;{]*\)\s*\{', s, re.M))
    open(out, 'w').write(s); print(p, 'defs in block:', n); break
else:
    print('not found'); sys.exit(1)
