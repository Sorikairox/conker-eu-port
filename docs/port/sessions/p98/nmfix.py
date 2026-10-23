#!/usr/bin/env python3
"""P98: nmfix.py FILE START_SUBSTR OLD NEW [OLD NEW ...]
Finds the statement/declaration that starts on the unique line containing START_SUBSTR and ends at the first
line ending in ';' from there; applies the OLD->NEW replacements (each must hit) to it. If the statement is
NM-only (inside #ifdef NON_MATCHING) it is edited in place, else it is wrapped as
#ifdef NON_MATCHING / new / #else / old / #endif (default build unchanged)."""
import sys, os
sys.argv_ = sys.argv
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
p, start, reps = sys.argv[1], sys.argv[2], sys.argv[3:]
txt = open(p).read(); L = txt.split('\n')
# NM-only lines
nm, stack = set(), []
import re
for n, line in enumerate(L):
    m = re.match(r'#\s*(ifdef|ifndef|if|else|endif)\b(.*)', line.strip())
    if m:
        d, rest = m.group(1), m.group(2).strip()
        if d in ('ifdef', 'ifndef', 'if'): stack.append((d != 'ifndef') if rest == 'NON_MATCHING' else None)
        elif d == 'else' and stack and stack[-1] is not None: stack[-1] = not stack[-1]
        elif d == 'endif' and stack: stack.pop()
        continue
    if any(x is True for x in stack): nm.add(n)
hits = [i for i, l in enumerate(L) if start in l]
assert len(hits) == 1, ('start hits', hits)
a = hits[0]; b = a
while not L[b].rstrip().endswith(';'): b += 1
old = '\n'.join(L[a:b + 1]); new = old
for i in range(0, len(reps), 2):
    assert new.count(reps[i]) == 1, ('rep', reps[i])
    new = new.replace(reps[i], reps[i + 1])
if all(i in nm for i in range(a, b + 1)):
    L[a:b + 1] = new.split('\n'); how = 'in place'
else:
    L[a:b + 1] = ['#ifdef NON_MATCHING'] + new.split('\n') + ['#else'] + old.split('\n') + ['#endif']; how = 'wrapped'
open(p, 'w').write('\n'.join(L)); print('ok', p, a + 1, how)
