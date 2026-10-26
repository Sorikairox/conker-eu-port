#!/usr/bin/env python3
"""P329: strip the byte-matching wrappers from the source, as the port build (-DNON_MATCHING) sees it:
- `#ifdef NON_MATCHING A #else B #endif` -> A; `#ifndef NON_MATCHING A #else B #endif` -> B (other #if blocks
  nested inside are kept or dropped with their side);
- every `#pragma GLOBAL_ASM(...)` line is removed;
- a comment on the `#ifdef/#ifndef NON_MATCHING` line itself is kept as its own line (if its side is kept).
Then runs of 3+ blank lines are squeezed to 2. Usage: strip_nm.py FILE...  (rewrites in place, prints counts)."""
import re, sys
D_NM = re.compile(r'^\s*#\s*(ifdef|ifndef)\s+NON_MATCHING\b(.*)$')
D_IF = re.compile(r'^\s*#\s*if')
D_ELSE = re.compile(r'^\s*#\s*else\b')
D_ELIF = re.compile(r'^\s*#\s*elif\b')
D_END = re.compile(r'^\s*#\s*endif\b')
PRAG = re.compile(r'^\s*#\s*pragma\s+GLOBAL_ASM\b')

def strip(text):
    out, stack = [], []   # frame: ['nm', keep_now] or ['other', None]
    vis = lambda: all(f[1] for f in stack if f[0] == 'nm')
    nnm = nprag = 0
    for l in text.split('\n'):
        m = D_NM.match(l)
        if m:
            rest = m.group(2).strip()
            stack.append(['nm', m.group(1) == 'ifdef']); nnm += 1
            if rest and vis():
                out.append(rest)
            continue
        if D_IF.match(l):
            if vis(): out.append(l)
            stack.append(['other', None]); continue
        if D_ELIF.match(l):
            if stack and stack[-1][0] == 'nm': raise SystemExit('elif in a NON_MATCHING block')
            if vis(): out.append(l)
            continue
        if D_ELSE.match(l):
            if stack and stack[-1][0] == 'nm':
                stack[-1][1] = not stack[-1][1]; continue
            if vis(): out.append(l)
            continue
        if D_END.match(l):
            if not stack: raise SystemExit('unbalanced #endif')
            f = stack.pop()
            if f[0] == 'other' and vis(): out.append(l)
            continue
        if PRAG.match(l):
            nprag += 1; continue
        if vis(): out.append(l)
    if stack: raise SystemExit('unterminated #if')
    s = re.sub(r'\n{4,}', '\n\n\n', '\n'.join(out))
    return s, nnm, nprag

tot = [0, 0, 0]
for p in sys.argv[1:]:
    t = open(p, errors='surrogateescape').read()
    try:
        s, a, b = strip(t)
    except SystemExit as e:
        print('ERROR', p, e); sys.exit(1)
    if s != t:
        open(p, 'w', errors='surrogateescape').write(s); tot[0] += 1
    tot[1] += a; tot[2] += b
print('files changed %d, NON_MATCHING blocks %d, GLOBAL_ASM lines %d' % tuple(tot))
