#!/usr/bin/env python3
"""Split a game C file that is really two EU objects (rodata_bounds.py BOUNDARY) in one command.

usage: file_split.py <stem> [--at FUNC] [--dry] [--no-own] [--resplit]

1. Finds the .rodata boundary B: the 16-byte aligned end of the late item (float/jump table)
   just before the first data item that follows late items (rodata_split.own_range's BOUNDARY).
2. Finds the text boundary: a function F, 16-byte aligned, such that every function before it
   references only this file's .rodata below B and every function from F on only at/above B.
   Ties are broken by .data references (the second object's .data comes after the first's) and
   by nop padding before F. --at FUNC forces F.
3. Moves F.. (pragmas and C, plus a comment block directly above F after a blank line) into
   src_eu/game_eu_<rom of F>.c with the original preamble (includes, prototypes) and fixed pragma
   paths, adds the c subsegment to conker.eu.yaml, and (unless --no-own) gives both halves their
   .rodata with rodata_split.py --own (a half that is itself still several objects is reported
   and left unowned: run file_split.py on it after a re-split).
--resplit re-splits in the conkerdev container afterwards. Needs conker/build/conker.eu.map
(addresses only; it may predate earlier splits of this session). Then: verify_all.sh --quick.
"""
import os, re, sys, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import datarefs as DR
import rodata_split as RS

ROOT = DR.ROOT
SRC = os.path.join(ROOT, 'src_eu')
LATE = {'lwc1', 'ldc1', 'jtbl'}


def map_funcs(v0, v1):
    out = []
    for l in open(os.path.join(ROOT, 'build/conker.eu.map')):
        m = re.match(r'^\s+0x([0-9a-f]{8,16})\s+([A-Za-z_]\w*)\s*$', l)
        if m:
            v = int(m.group(1), 16)
            if v0 <= v < v1:
                out.append((v, m.group(2)))
    return sorted(set(out))


def us_text_starts():
    """US vram of every subsegment start of the US game segment (US file boundaries; EU
    functions keep their US names)."""
    us = open(os.path.join(ROOT, 'conker.us.yaml')).read()
    i = us.index('- name:  game\n')
    seg = us[i:us.index('- name:', i + 10)]
    st = int(re.search(r'start:\s*0x([0-9A-Fa-f]+)', seg).group(1), 16)
    vr = int(re.search(r'vram:\s*0x([0-9A-Fa-f]+)', seg).group(1), 16)
    return {int(x, 16) - st + vr for x in re.findall(r'- \[0x([0-9A-Fa-f]+),', seg)}


def analyse(stem, at=None):
    segs = DR.segments()
    sd, dd = segs['game'], segs['game_data']
    files = DR.code_files('game')
    fi = [f[2] for f in files].index(stem)
    a, b, _ = files[fi]
    tv = sd['vram'] - sd['start']
    dv = dd['vram'] - dd['start']
    rstart = min(r for r, t, n in dd['subs'] if t in ('rodatabin', '.rodata'))
    allrefs = DR.refs('game')
    own = DR.owners('game', allrefs)
    funcs = map_funcs(a + tv, b + tv)
    USB = us_text_starts()
    if not funcs:
        sys.exit('%s: no functions in the map (build first)' % stem)
    kinds = {}
    for t, k, f, st, pc in allrefs:
        if f == fi:
            kinds.setdefault(t - dv, set()).add(k)
    mine = sorted(r for r, f in own.items() if f == fi)
    negoff = None
    # boundary: first data item after late items
    seen, D, lastlate = None, None, None
    for r in mine:
        ks = kinds.get(r, set())
        if ks & LATE:
            seen = seen or r
            lastlate = r
        elif seen:
            D = r
            break
    if D is None:
        sys.exit('%s: no BOUNDARY in its .rodata' % stem)
    data = open(DR.BIN, 'rb').read()
    ks = kinds[lastlate]
    if 'jtbl' in ks:
        e = lastlate
        while a + tv <= int.from_bytes(data[e:e + 4], 'big') < b + tv:
            e += 4
    else:
        e = lastlate + (8 if 'ldc1' in ks else 4)
    B = (e + 15) & ~15
    if B > D and B - D < 16 and any(k.endswith('x') for k in kinds[D]):
        print('  data item 0x%X is an indexed access with a negative offset; boundary 0x%X' % (D, B))
        negoff = D
    elif B > D:
        sys.exit('%s: late item 0x%X ends after data item 0x%X' % (stem, lastlate, D))
    # per function: owned rodata refs and .data refs
    starts = [v for v, n in funcs]
    import bisect
    fr = [[] for _ in funcs]
    fd = [[] for _ in funcs]
    mineset = set(mine)
    for t, k, f, st, pc in allrefs:
        if f != fi:
            continue
        i = bisect.bisect_right(starts, pc) - 1
        r = t - dv
        if r in mineset:
            fr[i].append(B if r == negoff else r)
        elif dd['start'] <= r < rstart:
            fd[i].append(r)
    lo_k = max([i + 1 for i in range(len(funcs)) if any(r < B for r in fr[i])] or [1])
    hi_k = min([i for i in range(len(funcs)) if any(r >= B for r in fr[i])] or [len(funcs)])
    bad = [funcs[i][1] for i in range(len(funcs)) if any(r < B for r in fr[i]) and i >= hi_k]
    cands = []
    for k in range(max(lo_k, 1), hi_k + 1):
        if k >= len(funcs):
            continue
        v = funcs[k][0]
        if v % 16:
            continue
        r = v - tv
        z = 0
        while z < 8 and data[r - 4 * (z + 1):r - 4 * z] == b'\0\0\0\0':
            z += 1
        d1 = [x for i in range(k) for x in fd[i]]
        d2 = [x for i in range(k, len(funcs)) for x in fd[i]]
        viol = sum(1 for x in d1 for y in d2 if x >= y)
        m = re.match(r'func_([0-9A-F]{8})$', funcs[k][1])
        us = bool(m and int(m.group(1), 16) in USB)
        cands.append((-us, viol, -(z >= 2), -k, k, z))
    print('%s: rodata boundary 0x%X (last late item 0x%X, data item 0x%X); text split between '
          '%s and %s%s' % (stem, B, lastlate, D, funcs[lo_k - 1][1], funcs[min(hi_k, len(funcs) - 1)][1],
                           ('; BAD: ' + ' '.join(bad)) if bad else ''))
    for c in sorted(cands):
        print('  candidate %s rom 0x%X data-order violations %d, %d zero words before%s'
              % (funcs[c[4]][1], funcs[c[4]][0] - tv, c[1], c[5], ', US file start' if c[0] else ''))
    if at:
        k = [n for v, n in funcs].index(at)
    else:
        if bad or not cands:
            sys.exit('no clean split point')
        k = sorted(cands)[0][4]
    return funcs[k][1], funcs[k][0] - tv


DEF = r'^[A-Za-z_][^;=]*\b%s\s*\('


def split_c(stem, func, new):
    path = os.path.join(SRC, stem + '.c')
    L = open(path).read().split('\n')
    unit = re.compile(r'^#pragma GLOBAL_ASM\(".*/(\w+)\.s"\)|' + DEF % r'(\w+)')
    first = None
    cut = None
    for i, l in enumerate(L):
        m = unit.match(l)
        if not m or l.rstrip().endswith(';'):
            continue
        name = m.group(1) or m.group(2)
        if first is None:
            first = i
        if name == func:
            cut = i
            break
    if cut is None:
        sys.exit('%s not found in %s' % (func, path))
    # a comment block right above F (after a blank line) goes with F
    j = cut
    while j > 0 and L[j - 1].startswith('//'):
        j -= 1
    if j < cut and (j == 0 or L[j - 1].strip() == ''):
        cut = j
    j = first
    while j > 0 and L[j - 1].startswith('//'):
        j -= 1
    pre = L[:j]
    while pre and pre[-1].strip() == '':
        pre.pop()
    body = L[cut:]
    body = [l.replace('asm/nonmatchings/%s/' % stem, 'asm/nonmatchings/%s/' % new) for l in body]
    head = L[:cut]
    while head and head[-1].strip() == '':
        head.pop()
    return path, '\n'.join(head) + '\n', '\n'.join(pre + [''] + body).rstrip('\n') + '\n'


def main():
    a = sys.argv[1:]
    stem = a[0]
    at = a[a.index('--at') + 1] if '--at' in a else None
    func, rom = analyse(stem, at)
    new = 'game_eu_%X' % rom
    print('split %s at %s (rom 0x%X) -> %s' % (stem, func, rom, new))
    path, h1, h2 = split_c(stem, func, new)
    Y = open(DR.YAML).read()
    if ', .rodata, %s]' % stem in Y:
        sys.exit('%s already owns .rodata; un-own it first' % stem)
    m = re.search(r'^(\s*)- \[0x[0-9A-Fa-f]+, c, %s\][^\n]*\n' % stem, Y, re.M)
    if not m:
        sys.exit('no c subsegment for %s' % stem)
    line = '%s- [0x%X, c, %s] # EU file boundary (file_split.py)\n' % (m.group(1), rom, new)
    if a.count('--dry'):
        print('would write %s (%d lines) and %s (%d lines)' % (path, h1.count('\n'),
              new + '.c', h2.count('\n')))
        return
    open(path, 'w').write(h1)
    open(os.path.join(SRC, new + '.c'), 'w').write(h2)
    open(DR.YAML, 'w').write(Y[:m.end()] + line + Y[m.end():])
    mk = open(os.path.join(ROOT, 'Makefile')).read()
    if '/%s.c.o:' % stem in mk:
        print('WARNING: %s has its own OPT_FLAGS in conker/Makefile; add one for %s' % (stem, new))
    if '--no-own' not in a:
        for s in (stem, new):
            r = subprocess.run([sys.executable, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                'rodata_split.py'), '--own', s], capture_output=True, text=True)
            out = (r.stdout + r.stderr).strip().split('\n')
            print('  own %s: %s' % (s, ' | '.join(x for x in out if x and not x.startswith('next:'))))
    if '--resplit' in a:
        RS.resplit()


if __name__ == '__main__':
    main()
