import sys
# usage: p68_insert.py file.c FUNC draft.c  -- wraps the GLOBAL_ASM pragma of FUNC in #ifdef NON_MATCHING <draft> #else ... #endif
f, fn, d = sys.argv[1:4]
s = open(f).read()
dir = f.split('/')[-1][:-2]
prag = '#pragma GLOBAL_ASM("asm/nonmatchings/%s/%s.s")' % (dir, fn)
assert s.count(prag) == 1, prag
i = s.index(prag)
assert not s[:i].rstrip().endswith('#else'), 'already wrapped'
body = open(d).read().rstrip() + '\n'
s = s.replace(prag, '#ifdef NON_MATCHING\n' + body + '#else\n' + prag + '\n#endif', 1)
open(f, 'w').write(s)
print('ok', fn)
