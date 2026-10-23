#!/usr/bin/env python3
# P93: mutate argument K (0-based; 'last' = the last one) of every call to CALLEE in a draft: ARG -> (ARG) + 1
# usage: mutwide.py draft.c CALLEE K out.c
import sys, re
src, callee, k, out = sys.argv[1:]
s = open(src).read(); res = []; i = 0; n = 0
for m in re.finditer(r'\b%s\s*\(' % callee, s):
    st = m.end(); j = st; d = 1; args = []; a0 = st
    while d:
        c = s[j]
        if c in '([': d += 1
        elif c in ')]': d -= 1
        if (c == ',' and d == 1) or d == 0: args.append((a0, j)); a0 = j + 1
        j += 1
    pre = s[:m.start()].rstrip()
    if pre.endswith(')') or re.search(r'\b(s32|void|u8|s16|u16|f32)\s*\*?\s*$', pre) or len(args) < 17: continue   # a declaration
    kk = len(args) - 1 if k == 'last' else int(k)
    a, b = args[kk]
    res.append((a, b, '(%s) + 1' % s[a:b].strip())); n += 1
for a, b, t in reversed(res): s = s[:a] + t + s[b:]
open(out, 'w').write(s); print('%d call(s) mutated' % n)
