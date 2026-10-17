#!/usr/bin/env python3
"""Turn extern float/double constants back into literals in a file that owns its .rodata.

usage: rodata_literals.py <stem> [--apply]

Ported C often reads its float literals through externs (`if (D_800A56A8 < x)` with
`D_800A56A8 = 0x800A5A88` in undefined_syms.eu.txt). Once the file owns its .rodata
(rodata_split.py --own) the compiler must emit those constants itself, at their place among the
other literals, so the externs become literals again (`3.1415927f`). Codegen is the same
(lui + lwc1/ldc1 either way).

Only names whose EU address lies in the file's .rodata and which the file's code loads with
lwc1/ldc1 are replaced; `extern` declarations of them inside the file are removed. A warning is
printed when one function would use the same literal value twice (IDO merges equal literals
within a function, so the layout would change).
"""
import os, re, sys, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import datarefs as DR
import rodata_inject as RI


def flit(b):
    v = struct.unpack('>f', b)[0]
    for p in range(1, 10):
        s = '%.*g' % (p, v)
        if struct.pack('>f', float(s)) == b:
            break
    if 'e' in s and v == int(v) and abs(v) < 1e9:
        s = '%d' % v
    if 'e' not in s and '.' not in s and 'inf' not in s and 'nan' not in s:
        s += '.0'
    return s + 'f'


def dlit(b):
    v = struct.unpack('>d', b)[0]
    for p in range(1, 18):
        s = '%.*g' % (p, v)
        if struct.pack('>d', float(s)) == b:
            break
    if 'e' in s and v == int(v) and abs(v) < 1e15:
        s = '%d' % v
    if 'e' not in s and '.' not in s:
        s += '.0'
    return s


def main():
    stem = sys.argv[1]
    apply = '--apply' in sys.argv
    own = [x for x in RI.owned_files() if x[1] == stem]
    if not own:
        sys.exit('%s owns no .rodata' % stem)
    seg, _, a, b, dseg = own[0]
    dv = dseg['vram'] - dseg['start']
    data = open(DR.BIN, 'rb').read()
    files = DR.code_files(seg)
    fi = [f[2] for f in files].index(stem)
    kinds = {}
    for t, k, f, st, pc in DR.refs(seg):
        if f == fi and a <= t - dv < b:
            kinds.setdefault(t, set()).add(k)
    names = RI.sym_addrs()
    p = os.path.join(DR.ROOT, 'src_eu', stem + '.c')
    src = open(p).read()
    body = re.sub(r'#pragma GLOBAL_ASM\([^)]*\)', '', src)
    rep = {}
    for ident in sorted(set(re.findall(r'\b[A-Za-z_]\w*\b', body))):
        va = names.get(ident)
        if va is None or not (a <= va - dv < b):
            continue
        ks = kinds.get(va, set())
        r = va - dv
        if re.search(r'\b%s\s*\[|&\s*%s\b' % (ident, ident), body):
            print('SKIP %s (0x%X): used as an array/address' % (ident, va))
            continue
        if 'ldc1' in ks:
            rep[ident] = dlit(data[r:r + 8])
        elif 'lwc1' in ks:
            rep[ident] = flit(data[r:r + 4])
        else:
            print('SKIP %s (0x%X): not a float load (%s)' % (ident, va, ','.join(sorted(ks)) or 'unreferenced'))
    if not rep:
        print('%s: nothing to replace' % stem)
        return
    # same literal twice in one function?
    for m in re.finditer(r'\n[^\n;{}]*\([^;{}]*\)\s*\{(.*?)\n\}', body, re.S):
        vals = {}
        for ident in set(re.findall(r'\b\w+\b', m.group(1))) & set(rep):
            vals.setdefault(rep[ident], []).append(ident)
        for v, ids in vals.items():
            if len(ids) > 1:
                print('WARNING: %s used for %s in one function' % (v, ', '.join(ids)))
    out = src
    for ident, lit in rep.items():
        out = re.sub(r'^\s*extern\s+(?:f32|f64|float|double)\s+%s\s*;\s*\n' % ident, '', out, flags=re.M)
        out = re.sub(r'\b%s\b' % ident, lit, out)
        print('%s -> %s' % (ident, lit))
    if apply:
        open(p, 'w').write(out)


if __name__ == '__main__':
    main()
