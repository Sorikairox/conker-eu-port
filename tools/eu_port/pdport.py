#!/usr/bin/env python3
"""Port functions from a reference decomp C file (e.g. Perfect Dark src/lib/mp3/decoder.c) (s91).

usage:
  pdport.py ctx <ref.c>... > ctx.h
      Struct/typedef/#define blocks and prototypes kept; every top-level variable definition
      becomes an extern declaration (initializer dropped). bool -> s32, true/false -> 1/0.
  pdport.py func <ref.c> <refname> <eu_func> [ctx.h] > draft.c
      The function body renamed to <eu_func> (bool/true/false rewritten), ctx.h prepended.
  pdport.py relmap <eu_func> <draft.c>
      Compiles the draft (m2c/mine machinery: build/mine_<f>/<f>.o), lists the relocation
      symbols of the function in order and zips them with the reference asm's %hi/jal symbols:
      prints "refname -> D_xxx" pairs (and conflicts), to rename the draft's globals.
  pdport.py rename <draft.c> <map.txt>   (map lines "old new"; word-boundary rename in place)
"""
import os, re, subprocess, sys

R = os.environ.get('CONKER_ROOT', os.path.expanduser('~/conker'))
DEV = os.environ.get('CONKERDEV', 'conkerdev')


def fix(s):
    s = re.sub(r'\bbool\b', 's32', s)
    s = re.sub(r'\btrue\b', '1', s)
    s = re.sub(r'\bfalse\b', '0', s)
    return s


def ctx(files):
    out = []
    for f in files:
        L = open(f).read().split('\n')
        i = 0
        while i < len(L):
            l = L[i]
            if l.startswith('#include') or l.startswith('#ifndef _') or l.startswith('#endif') or (l.startswith('#define _')):
                i += 1; continue
            if l.startswith('#define'):
                out.append(l); i += 1; continue
            if re.match(r'^(typedef )?(struct|union|enum) \w*\s*\{', l):
                j = i
                while not L[j].startswith('}'):
                    j += 1
                out += L[i:j + 1]; i = j + 1; continue
            m = re.match(r'^(extern )?((static |const )*[\w ]+?[\s*]+)(\w+)((\[[^\]]*\])*)\s*(=.*|;)\s*$', l)
            if m and '(' not in l.split('=')[0]:
                decl = 'extern ' + m.group(2).replace('static ', '') + m.group(4) + m.group(5) + ';'
                out.append(decl)
                if m.group(7).startswith('=') and not m.group(7).rstrip().endswith(';'):
                    j = i
                    while not L[j].rstrip().endswith(';'):
                        j += 1
                    i = j + 1; continue
                i += 1; continue
            if re.match(r'^[a-zA-Z][\w \*]*\w+\(.*\);\s*$', l):
                out.append(l)
            i += 1
    return fix('\n'.join(out)) + '\n'


def func(f, name, eu, ctxf=None):
    s = open(f).read()
    m = re.search(r'^[a-zA-Z][\w \*]*\b' + name + r'\(', s, re.M)
    if not m:
        sys.exit('not found: ' + name)
    e = s.index('\n}\n', m.start()) + 3
    body = s[m.start():e]
    body = re.sub(r'\b' + name + r'\(', eu + '(', body, count=1)
    pre = open(ctxf).read() if ctxf else ''
    return pre + fix(body)


def relmap(eu, draft):
    subprocess.run([os.path.join(R, 'tools/eu_port/m2c/mine'), eu, draft], capture_output=True)
    o = f'build/mine_{eu}/{eu}.o'
    d = subprocess.run(['docker', 'exec', '-w', '/conker/conker', DEV, 'mips-linux-gnu-objdump', '-dr', '-j', '.text', o],
                       capture_output=True, text=True).stdout
    mine, p = [], False
    for l in d.split('\n'):
        if re.match(r'^[0-9a-f]+ <' + eu + '>:', l):
            p = True; continue
        if p and re.match(r'^[0-9a-f]+ <', l):
            break
        m = re.search(r'R_MIPS_(HI16|26)\s+(\S+)', l)
        if p and m:
            mine.append(m.group(2))
    import glob
    s = open(glob.glob(f'{R}/conker/asm/nonmatchings/*/{eu}.s')[0]).read()
    ref = [m.group(2) or m.group(3) for m in re.finditer(r'(%hi\((\w+)\)|\bjal\s+(\w+))', s)]
    mp = {}
    for a, b in zip(mine, ref):
        if a.startswith('.'):
            print('# local', a, '->', b)
            continue
        if a in mp and mp[a] != b:
            print('CONFLICT', a, mp[a], b)
        mp.setdefault(a, b)
    if len(mine) != len(ref):
        print(f'# count differs: mine {len(mine)} ref {len(ref)}')
    for a, b in mp.items():
        if a != b:
            print(a, b)


def rename(draft, mapf):
    s = open(draft).read()
    pairs = [l.split() for l in open(mapf) if l.strip() and not l.startswith('#') and not l.startswith('CONFLICT')]
    for a, b in pairs:
        s = re.sub(r'\b' + re.escape(a) + r'\b', '@@' + b + '@@', s)
    s = s.replace('@@', '')
    open(draft, 'w').write(s)


if __name__ == '__main__':
    c = sys.argv[1]
    if c == 'ctx':
        sys.stdout.write(ctx(sys.argv[2:]))
    elif c == 'func':
        sys.stdout.write(func(*sys.argv[2:6]))
    elif c == 'relmap':
        relmap(sys.argv[2], sys.argv[3])
    elif c == 'rename':
        rename(sys.argv[2], sys.argv[3])
