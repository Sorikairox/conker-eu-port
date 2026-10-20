#!/usr/bin/env python3
"""s110: real callee prototypes from the matched C sources (m2c drafts drop stack args).

Scans conker/src_eu/**/*.c and conker/include/*.h for top-level prototypes and C
definitions. Per function, the distinct prototypes (param names stripped) are ranked:
the C definition first (if the function is matched), then by how many files declare it.

usage:
  realproto.py show func...          ranked prototypes (count, where); FLAG = shapes disagree
  realproto.py report                every function whose prototypes disagree in shape
                                     (arity or int/float class of a slot / the return)
  realproto.py fix in.c out.c [file.c]  rewrite a draft: replace/insert the real prototype of
                                     every called function, retype the defined function's
                                     params from include/functions.h, pad calls that pass
                                     fewer args than the real prototype with 0 (/* PAD */).
                                     Types unknown to file.c (+ include/) -> void * / s32.
                                     Prints a one-line summary to stderr.
Shape classes: f = f32/float, d = f64/double, v = void, i = anything else.
"""
import glob, os, re, sys
from collections import defaultdict

R = os.environ.get('CONKER_ROOT', os.path.expanduser('~/conker'))
TYPEWORDS = {'s8', 's16', 's32', 's64', 'u8', 'u16', 'u32', 'u64', 'f32', 'f64', 'void', 'int',
             'char', 'short', 'long', 'float', 'double', 'unsigned', 'signed', 'const',
             'volatile', 'struct', 'union', 'enum', 'Gfx', 'Mtx', 'OSTime'}
HEAD = re.compile(r'^((?:static\s+|extern\s+|inline\s+)*)([A-Za-z_][\w\s\*]*?[\s\*])\s*([A-Za-z_]\w*)\s*\((.*)\)$', re.S)


def strip_comments(s):
    s = re.sub(r'/\*.*?\*/', ' ', s, flags=re.S)
    s = re.sub(r'//[^\n]*', '', s)
    s = re.sub(r'^\s*#[^\n]*', '', s, flags=re.M)
    s = re.sub(r'"(?:\\.|[^"\\])*"', '""', s)
    return s


def norm_param(p):
    p = ' '.join(p.replace('*', ' * ').split())
    if p in ('', 'void', '...'):
        return p
    toks = p.split(' ')
    if len(toks) >= 2 and re.match(r'^[A-Za-z_]\w*$', toks[-1]) and toks[-1] not in TYPEWORDS \
            and not (len(toks) == 2 and toks[0] in ('struct', 'union', 'enum', 'unsigned', 'signed')):
        toks = toks[:-1]
    return ' '.join(toks).replace(' *', '*').replace('* ', '*').replace('*', ' *').replace('  ', ' ')


def split_params(s):
    out, d, cur = [], 0, ''
    for ch in s:
        if ch == '(':
            d += 1
        elif ch == ')':
            d -= 1
        if ch == ',' and d == 0:
            out.append(cur); cur = ''
        else:
            cur += ch
    out.append(cur)
    return [x.strip() for x in out]


def cls(t):
    t = t.strip()
    if '*' in t or '(' in t:
        return 'i'
    if t in ('f32', 'float'):
        return 'f'
    if t in ('f64', 'double'):
        return 'd'
    if t == 'void':
        return 'v'
    if t == '...':
        return '.'
    return 'i'


def parse_head(stmt):
    m = HEAD.match(' '.join(stmt.split()))
    if not m:
        return None
    ret = ' '.join(m.group(2).replace('*', ' * ').split()).replace(' *', '*').replace('*', ' *')
    if any(w in ('typedef', 'return', 'else', 'if', 'while', 'for', 'switch') for w in ret.split()):
        return None
    name, ps = m.group(3), m.group(4)
    if ps.strip() == '':
        return None                       # K&R `f();`: no information
    params = [norm_param(p) for p in split_params(ps)]
    if any('(' in p for p in params) or '(' in ret:
        return None
    if params == ['void']:
        params = []
    proto = '%s %s(%s);' % (ret, name, ', '.join(params) if params else 'void')
    shape = cls(ret) + ':' + ''.join(cls(p) for p in params)
    return name, proto, shape, params


def top_statements(src):
    """(text, is_definition) for each depth-0 statement."""
    d, cur = 0, ''
    for ch in src:
        if d == 0:
            if ch == ';':
                yield cur, False; cur = ''
            elif ch == '{':
                yield cur, True; cur = ''; d = 1
            elif ch == '}':
                cur = ''
            else:
                cur += ch
        else:
            if ch == '{':
                d += 1
            elif ch == '}':
                d -= 1
                if d == 0:
                    cur = ''


def scan():
    db = defaultdict(lambda: defaultdict(lambda: {'n': 0, 'def': False, 'hdr': False, 'where': set()}))
    shapes = {}
    files = glob.glob(R + '/conker/src_eu/**/*.c', recursive=True) + glob.glob(R + '/conker/include/*.h')
    for fn in files:
        src = strip_comments(open(fn, errors='replace').read())
        short = os.path.relpath(fn, R + '/conker')
        for st, isdef in top_statements(src):
            r = parse_head(st.strip())
            if not r:
                continue
            name, proto, shape, _ = r
            e = db[name][proto]
            e['n'] += 1; e['where'].add(short)
            e['def'] |= isdef; e['hdr'] |= fn.endswith('.h')
            shapes[proto] = shape
    return db, shapes


def ranked(db, name):
    return sorted(db[name].items(), key=lambda kv: (-kv[1]['def'], -len(kv[1]['where']), kv[0]))


def flagged(db, shapes, name):
    return len({shapes[p] for p in db[name]}) > 1


def show(db, shapes, names):
    for n in names:
        if n not in db:
            print('%s: none' % n); continue
        print('%s%s' % (n, '  FLAG' if flagged(db, shapes, n) else ''))
        for p, e in ranked(db, n):
            print('  %2d %s%s %-60s %s' % (len(e['where']), 'D' if e['def'] else '-', 'H' if e['hdr'] else '-',
                                         p, ','.join(sorted(e['where']))[:80]))


KNOWN = None
LOCAL = {}


def best(db, name):
    """prototype to use: the header one if any (anything else fails to compile), then the target
    file's own declaration (a different one is a redeclaration error), else rank 1."""
    if name in LOCAL:
        return LOCAL[name]
    if name not in db:
        return None
    for p, e in db[name].items():
        if e['hdr']:
            return p
    if name in LOCAL:
        return LOCAL[name]
    p = ranked(db, name)[0][0]
    return generic(p, KNOWN) if KNOWN is not None else p


CALL = re.compile(r'\b([A-Za-z_]\w*)\s*\(')
KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof'}


def calls_in(body):
    return {m.group(1) for m in CALL.finditer(body) if m.group(1) not in KW}


def pad_calls(text, name, nparams):
    """append `0 /* PAD */` args to calls of name that pass fewer than nparams args."""
    out, i, npad = '', 0, 0
    for m in re.finditer(r'\b%s\s*\(' % re.escape(name), text):
        if m.start() < i:
            continue
        j, d = m.end() - 1, 0
        for k in range(j, len(text)):
            if text[k] == '(':
                d += 1
            elif text[k] == ')':
                d -= 1
                if d == 0:
                    break
        else:
            continue
        args = text[j + 1:k]
        n = 0 if args.strip() == '' else len(split_params(args))
        if n < nparams and not re.match(r'\s*[\w\s\*]*\)\s*;', text[j + 1:]):  # not a declaration
            add = ', '.join(['0 /* PAD */'] * (nparams - n))
            args = (args + ', ' + add) if args.strip() else add
            npad += 1
        out += text[i:j + 1] + args + ')'
        i = k + 1
    return out + text[i:], npad


def known_types(cfile):
    names = set(TYPEWORDS)
    fs = glob.glob(R + '/conker/include/**/*.h', recursive=True) + ([cfile] if cfile else [])
    for fn in fs:
        t = strip_comments(open(fn, errors='replace').read())
        names |= set(re.findall(r'\}\s*([A-Za-z_]\w*)\s*;', t))
        names |= set(re.findall(r'typedef\s+[^;{]*?\b([A-Za-z_]\w*)\s*;', t))
        names |= set(re.findall(r'\b(?:struct|union)\s+([A-Za-z_]\w*)', t))
    return names


def generic(proto, known):
    """replace types the target file does not know: pointers -> void *, values -> s32."""
    def fx(t):
        ws = re.findall(r'[A-Za-z_]\w*', t)
        if all(w in known for w in ws):
            return t
        return 'void *' if '*' in t else 's32'
    i, j = proto.index('('), proto.rindex(')')
    head = proto[:i].split()
    name = head[-1]; ret = ' '.join(head[:-1])
    ps = [fx(p) for p in split_params(proto[i + 1:j])]
    return '%s %s(%s);' % (fx(ret), name, ', '.join(ps))


def fix(db, shapes, inp, outp, cfile=None):
    global KNOWN
    KNOWN = known_types(cfile)
    if cfile:
        for st, isdef in top_statements(strip_comments(open(cfile, errors='replace').read())):
            r = parse_head(st.strip())
            if r and r[0] not in LOCAL and not any(e['hdr'] for e in db.get(r[0], {}).values()):
                LOCAL[r[0]] = r[1]
    src = open(inp).read()
    lines = src.split('\n')
    # the defined function = last top-level definition head
    defname = None
    for st, isdef in top_statements(strip_comments(src)):
        if isdef:
            r = parse_head(st.strip())
            if r:
                defname = r[0]
    body = src
    called = calls_in(strip_comments(src)) - {defname}
    replaced, inserted, padded, kept = 0, 0, 0, 0
    newl, have = [], set()
    for l in lines:
        st = l.strip()
        if st.endswith(';') and not l.startswith((' ', '\t')):
            r = parse_head(st[:-1])
            if r and r[0] != defname:
                nm = r[0]
                b = best(db, nm)
                if b is None:
                    newl.append(l); have.add(nm); kept += 1; continue
                if nm in have:
                    continue
                have.add(nm)
                hdr = any(e['hdr'] for e in db[nm].values())
                if hdr:
                    replaced += 1; continue          # functions.h declares it
                if b != r[1]:
                    replaced += 1
                newl.append(b); continue
        newl.append(l)
    # insert missing prototypes (not in header, not declared) before the first non-extern line
    ins = []
    for nm in sorted(called):
        if nm in have or (nm not in db and nm not in LOCAL) or any(e['hdr'] for e in db[nm].values()):
            continue
        ins.append(best(db, nm)); inserted += 1
    k = 0
    while k < len(newl) and (newl[k].startswith(('extern', '#', '//')) or newl[k].strip() == ''
                            or newl[k].rstrip().endswith(');')):
        k += 1
    newl = newl[:k] + ins + newl[k:]
    out = '\n'.join(newl)
    # retype the definition's params from functions.h
    if defname and defname in db:
        hp = [p for p, e in db[defname].items() if e['hdr']]
        if hp:
            m = re.search(r'^([^\n;{}]*\b%s\s*\()([^)]*)\)\s*\{' % defname, out, re.M)
            if m:
                ps = split_params(m.group(2))
                hparams = split_params(hp[0][hp[0].index('(') + 1:hp[0].rindex(')')])
                hret = hp[0][:hp[0].index(defname)].strip()
                if hparams == ['void']:
                    hparams = []
                if len(hparams) == len([p for p in ps if p and p != 'void']):
                    newps = []
                    for i, (t, p) in enumerate(zip(hparams, ps)):
                        nmm = re.search(r'([A-Za-z_]\w*)\s*$', p)
                        newps.append('%s%s%s' % (t, '' if t.endswith('*') else ' ', nmm.group(1) if nmm else 'arg%d' % i))
                    head = '%s %s(%s) {' % (hret, defname, ', '.join(newps) if newps else 'void')
                    out = out[:m.start()] + head + out[m.end():]
    # pad short calls
    for nm in sorted(called):
        b = best(db, nm)
        if not b:
            continue
        ps = split_params(b[b.index('(') + 1:b.rindex(')')])
        if ps == ['void'] or '...' in ps:
            continue
        out, n = pad_calls(out, nm, len(ps))
        padded += n
    open(outp, 'w').write(out)
    sys.stderr.write('realproto %s: replaced %d inserted %d padded %d unknown %d\n'
                     % (defname, replaced, inserted, padded, kept))


def main():
    a = sys.argv[1:]
    if not a:
        print(__doc__); return
    db, shapes = scan()
    if a[0] == 'show':
        show(db, shapes, a[1:])
    elif a[0] == 'report':
        n = 0
        for name in sorted(db):
            if flagged(db, shapes, name):
                n += 1
                show(db, shapes, [name])
        print('# %d functions with disagreeing shapes, %d with prototypes' % (n, len(db)))
    elif a[0] == 'fix':
        fix(db, shapes, a[1], a[2], a[3] if len(a) > 3 else None)


if __name__ == '__main__':
    main()
