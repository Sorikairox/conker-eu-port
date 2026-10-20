import sys
# mvline.py draft.c 'line substring' start_sub end_sub outprefix : move line to every position between start and end
src, pat, a, b, out = sys.argv[1:6]
L = open(src).read().split('\n')
i = next(k for k,l in enumerate(L) if pat in l)
line = L.pop(i)
s = next(k for k,l in enumerate(L) if a in l); e = next(k for k,l in enumerate(L) if b in l)
n = 0
for p in range(s, e+1):
    M = L[:p] + [line] + L[p:]
    open('%s%02d.c' % (out, n), 'w').write('\n'.join(M)); n += 1
print(n)
