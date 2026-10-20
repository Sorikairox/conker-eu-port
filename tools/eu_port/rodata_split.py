#!/usr/bin/env python3
"""Carve a C file's own section out of the data blobs in conker/conker.eu.yaml.

usage:
  rodata_split.py --own <stem> [--dry] [--resplit]
  rodata_split.py <stem> <rom a> <rom b> [--section .data] [--dry] [--resplit]
      Give src_eu/<stem>.c its .rodata: the range is computed from the code's references
      (datarefs.py): from the 16-byte aligned start of the first item the file references to
      the aligned end of its last item. Prints the range and the plan (rodata_inject.py --dry).
      --resplit then re-splits in the conkerdev container (rm asm build *_auto.txt; make
      extract, which runs rodata_inject.py) so the file's GLOBAL_ASM functions carry their
      rodata and C functions can use literals, strings and switch statements.
  rodata_split.py <stem> <rom start> <rom end> [--section .data|.rodata]
      Explicit range (e.g. a .data piece; .data only before the .rodata start of the segment).

The blob line is split into [blob start, blob type], [start, section, stem], [end, blob type]
(empty pieces dropped). Only the full ROM check (verify_all.sh) covers data bytes.
"""
import sys, re, os, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import datarefs as DR

YAML = DR.YAML


def split(stem, a, b, sec, dry=False):
    L = open(YAML).read().split('\n')
    R = re.compile(r'^(\s*)- \[0x([0-9A-Fa-f]+),\s*([\w.]+)')
    for i, l in enumerate(L):
        m = R.match(l)
        if not m:
            continue
        s = int(m.group(2), 16)
        nxt = None
        for l2 in L[i + 1:]:
            m2 = R.match(l2) or re.match(r'^\s*- \[0x([0-9A-Fa-f]+)\]', l2)
            if m2:
                nxt = int(m2.group(2) if m2.re is R else m2.group(1), 16)
                break
        if m.group(3) in ('rodatabin', 'databin') and s <= a and nxt is not None and b <= nxt:
            ind = m.group(1)
            bt = m.group(3)
            new = []
            if s < a:
                new.append('%s- [0x%X, %s]' % (ind, s, bt))
            new.append('%s- [0x%X, %s, %s]' % (ind, a, sec, stem))
            if b < nxt:
                new.append('%s- [0x%X, %s]' % (ind, b, bt))
            L[i:i + 1] = new
            if not dry:
                open(YAML, 'w').write('\n'.join(L))
            print('\n'.join(new))
            return
    sys.exit('no rodatabin/databin contains 0x%X-0x%X' % (a, b))


def resplit():
    # keeps conker/build/<dirs> of m2c drafts? no: build/ is wiped like in verify_all.sh
    docker = '/Applications/Docker.app/Contents/Resources/bin/docker'
    cmd = ('cd /conker/conker && rm -rf asm build && find . -maxdepth 1 -name "*_auto.txt" -delete'
           ' && make VERSION=eu extract 2>&1 | grep -E "rodata_inject|rror" ; true')
    subprocess.run([docker, 'exec', os.environ.get('CONKERDEV','conkerdev'), 'bash', '-c', cmd])


def own_range(stem):
    """(seg, rom a, rom b) of the file's .rodata, from code references."""
    segs = DR.segments()
    for seg in ('game', 'init', 'debugger'):
        if stem in [f[2] for f in DR.code_files(seg)]:
            break
    else:
        sys.exit('%s: not a code subsegment' % stem)
    d = segs[seg + '_data']
    rstart = min(r for r, t, n in d['subs'] if t in ('rodatabin', '.rodata'))
    dv = d['vram'] - d['start']
    data = open(DR.BIN, 'rb').read()
    files = DR.code_files(seg)
    fi = [f[2] for f in files].index(stem)
    sd = segs[seg]
    t0 = sd['vram'] + files[fi][0] - sd['start']
    t1 = sd['vram'] + files[fi][1] - sd['start']
    warn_gap = []
    allrefs = DR.refs(seg)
    own = DR.owners(seg, allrefs)
    kinds = {}
    for t, k, f, st, pc in allrefs:
        if f == fi:
            kinds.setdefault(t - dv, set()).add(k)
    mine = [(r, k) for r, f in own.items() if f == fi for k in kinds.get(r, ())]
    before = [r for r, f in own.items() if f < fi]
    after = [r for r, f in own.items() if f > fi]
    if not mine:
        sys.exit('%s: owns no .rodata' % stem)
    lo = min(r for r, k in mine)
    hi_r, hi_k = max(mine)
    ks = {k for r, k in mine if r == hi_r}
    if 'jtbl' in ks:
        e = hi_r
        while t0 <= int.from_bytes(data[e:e + 4], 'big') < t1:
            e += 4
    elif 'ldc1' in ks:
        e = hi_r + 8
    elif ks & {'lwc1', 'lw'}:
        e = hi_r + 4
    else:
        e = hi_r + 1
        while data[e]:
            e += 1
        e += 1
    # zero gaps up to a 16-byte boundary between two late items: an EU file boundary?
    def iend(r):
        ks = kinds.get(r, set())
        if 'jtbl' in ks:
            e2 = r
            while t0 <= int.from_bytes(data[e2:e2 + 4], 'big') < t1:
                e2 += 4
            return e2
        return r + (8 if 'ldc1' in ks else 4) if ks & {'lwc1', 'ldc1'} else None
    myaddrs = sorted({r for r, k in mine})
    for p_, q_ in zip(myaddrs, myaddrs[1:]):
        pe = iend(p_)
        if pe is not None and q_ % 16 == 0 and q_ - pe >= 4 and not any(data[pe:q_]) \
                and kinds.get(q_, set()) & {'lwc1', 'ldc1', 'jtbl'}:
            warn_gap.append('zero padding 0x%X-0x%X between late items: EU file boundary? '
                            '(item 0x%X)' % (pe, q_, q_))
    # data (strings, tables) after floats/jump tables can't come from one IDO object
    seen_late = None
    for r in myaddrs:
        ks = kinds.get(r, set())
        if ks & {'lwc1', 'ldc1', 'jtbl'}:
            seen_late = seen_late or r
        elif seen_late and not ks & {'lwc1', 'ldc1', 'jtbl'}:
            warn_gap.append('FILE BOUNDARY: data item 0x%X (%s) after late items from 0x%X: '
                            'this C file is two EU objects; split it first'
                            % (r, ','.join(sorted(ks)), seen_late))
            break
    a = lo & ~15
    b = (e + 15) & ~15
    warn = warn_gap
    if any(a <= r < lo for r in before):
        warn.append('an earlier file references 0x%X-0x%X' % (a, lo))
    if any(r < b for r in after if r >= lo):
        warn.append('a later file references bytes below 0x%X (shared table?)' % b)
    if any(data[e:b]):
        warn.append('nonzero bytes after the last item 0x%X-0x%X' % (e, b))
    pb = max([r for r in before if r < a] or [rstart])
    if any(data[(pb + 16) & ~15:a]) and (pb + 16) & ~15 < a:
        warn.append('unreferenced nonzero bytes 0x%X-0x%X before the range (may be this file\'s)'
                    % ((pb + 16) & ~15, a))
    return seg, a, b, warn


def main():
    a = sys.argv[1:]
    if '--own' in a:
        stem = a[a.index('--own') + 1]
        if ', .rodata, %s]' % stem in open(YAML).read():
            print('%s already owns its .rodata' % stem)
            if '--resplit' in a:
                resplit()
            return
        seg, lo, hi, warn = own_range(stem)
        print('%s .rodata 0x%X-0x%X' % (stem, lo, hi))
        for w in warn:
            print('WARNING:', w)
        if any('BOUNDARY' in w for w in warn) and '--force' not in a and '--dry' not in a:
            sys.exit('not done (--force to override)')
        split(stem, lo, hi, '.rodata', dry='--dry' in a)
        if '--dry' in a:
            return
        # externs that name this file's float constants become literals again
        subprocess.run([sys.executable, os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                                     'rodata_literals.py'), stem, '--apply'])
        if '--resplit' in a:
            resplit()
        else:
            print('next: re-split (rodata_split.py --own %s --resplit does it), then build' % stem)
        return
    stem, lo, hi = a[0], int(a[1], 16), int(a[2], 16)
    sec = a[a.index('--section') + 1] if '--section' in a else '.rodata'
    split(stem, lo, hi, sec, dry='--dry' in a)
    if '--dry' in a:
        print('(dry run: conker.eu.yaml not changed)')
    elif '--resplit' in a:
        resplit()


if __name__ == '__main__':
    main()
