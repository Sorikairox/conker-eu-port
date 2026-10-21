#!/usr/bin/env python3
"""insert_nm.py FUNC draft.c [FUNC draft.c ...]   (host or container; CONKER_ROOT selects the checkout)

Replaces `#pragma GLOBAL_ASM(".../FUNC.s")` in its src_eu file with

    #ifdef NON_MATCHING
    <draft>
    #else
    #pragma GLOBAL_ASM(".../FUNC.s")
    #endif

so the default build keeps the original bytes and `make NON_MATCHING=1` compiles the C.
Draft directives (same as m2c/screen.py): `//HOIST <decl>` lines go into one
`#ifdef NON_MATCHING // hoisted` block after the file's last #include; `//DROP <line>` wraps that
exact line of the file in `#ifndef NON_MATCHING ... #endif`. A function that already has a
NON_MATCHING block gets its C side replaced.
"""
import sys, os, re, glob

ROOT = os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker')) if not os.path.exists('/.dockerenv') else '/conker'
HOIST_TAG = '#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies'


def find(func):
    pat = re.compile(r'^#pragma GLOBAL_ASM\("[^"]*/%s\.s"\)\s*$' % func, re.M)
    for p in glob.glob(os.path.join(ROOT, 'conker/src_eu/**/*.c'), recursive=True):
        s = open(p).read()
        m = pat.search(s)
        if m: return p, s, m
    return None, None, None


def insert(func, draft):
    p, s, m = find(func)
    if p is None: return 'NOPRAGMA'
    lines = draft.rstrip('\n').split('\n')
    hoist = [l[8:] for l in lines if l.startswith('//HOIST ')]
    drop = [l[7:] for l in lines if l.startswith('//DROP ')]
    body = '\n'.join(l for l in lines if not l.startswith(('//HOIST ', '//DROP '))).strip('\n')
    prag = m.group(0).rstrip()
    # already wrapped? (the pragma sits in the #else of a NON_MATCHING block)
    a, b = m.start(), m.end()
    pre = s[:a]
    k = pre.rfind('#ifdef NON_MATCHING\n')
    if k >= 0 and pre.endswith('#else\n') and '#endif' not in pre[k:] and s[b:].startswith('\n#endif'):
        a, b = k, b + len('\n#endif')
    block = '#ifdef NON_MATCHING\n%s\n#else\n%s\n#endif' % (body, prag)
    s = s[:a] + block + s[b:]
    for l in drop:
        i = s.find(l + '\n')
        if i >= 0 and not s[:i].endswith('#ifndef NON_MATCHING\n'):
            s = s[:i] + '#ifndef NON_MATCHING\n' + l + '\n#endif\n' + s[i + len(l) + 1:]
    if hoist:
        if HOIST_TAG in s:
            i = s.index(HOIST_TAG) + len(HOIST_TAG) + 1
            e = s.index('#endif', i)
            have = set(s[i:e].split('\n'))
            s = s[:e] + ''.join(h + '\n' for h in hoist if h not in have) + s[e:]
        else:
            ms = list(re.finditer(r'^#include[^\n]*\n', s, re.M)); k = ms[-1].end() if ms else 0
            s = s[:k] + HOIST_TAG + '\n' + '\n'.join(hoist) + '\n#endif\n' + s[k:]
    open(p, 'w').write(s)
    return 'OK ' + os.path.relpath(p, ROOT)


if __name__ == '__main__':
    a = sys.argv[1:]
    if not a or len(a) % 2: print(__doc__); sys.exit(2)
    for f, d in zip(a[::2], a[1::2]):
        print(f, insert(f, open(d).read()))
