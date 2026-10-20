#!/usr/bin/env python3
"""Stack-slot helper (host side, uses the conkerdev container).

usage: stackfix.py <func> <draft.c> [--rounds N] [--beam K] [--max M] [--out DIR]
       stackfix.py --scan <list>     (lines `func draft.c`): which drafts are off by stack offsets only
       stackfix.py --bisect <func> <draft.c>   statements whose removal changes the frame size
                     (finds hidden compiler temps: func_150144B8's `tmp.unk1C *= D_80096A38` costs 8 bytes)

1. Screens the draft (m2c/screen.py, SCREEN_V=1) and compares the stack accesses
   (`sp+N` loads/stores/address computations) and frame size of the target .s with the
   draft's compiled code. Prints whether the remaining diff is stack offsets only and the
   offset map (draft -> target).
2. Generates candidate drafts:
     order   every order (<=6 locals; otherwise rotations/swaps/reverse) of a block's local
             declarations
     pad     `s32 padN;` / `u8 padN[8]` inserted at each position of a declaration list
     array   each local array size +-1, +-2, +4 elements
     into    a function-level local moved into the innermost/each enclosing block that
             contains all of its uses (loop bodies: session 14, `func_15016588`)
     outof   a block-level local moved to function level
     split   `T a, b;` declarations are split first (one declarator per line)
3. Screens them in parallel (8 at a time, like m2c/tryall), keeps the best K by
   (stack-only?, DIFF count) and runs another round on them (beam search).
Results: <out>/best.c (lowest score) and <out>/match.c on an OK; one line per round.
"""
import os, re, sys, itertools, subprocess, shutil, collections
import sys as _gsys
def _conker_guard():
    # refuse to run on a checkout other than CONKER_ROOT (e.g. a worktree shell without the wt.sh env)
    import os as _o, subprocess as _s
    if _o.path.exists("/.dockerenv"):
        return  # inside a build container: paths are /conker, not the host checkout
    try:
        top = _s.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()
    except Exception:
        return
    root = _o.path.realpath(_o.path.expanduser(_o.environ.get("CONKER_ROOT", "~/conker")))
    if top and _o.path.realpath(top) != root:
        _gsys.stderr.write("refusing: cwd repo %s != CONKER_ROOT %s (eval the wt.sh env)\n" % (top, root))
        _gsys.exit(3)
_conker_guard()

HOME = os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'')
R = HOME + '/conker'
DOCKER = '/Applications/Docker.app/Contents/Resources/bin/docker'
sys.path.insert(0, HOME + '/tools/eu_port')

# ------------------------------------------------------------------ word analysis
LS = {0x20: 'lb', 0x21: 'lh', 0x23: 'lw', 0x24: 'lbu', 0x25: 'lhu', 0x28: 'sb', 0x29: 'sh', 0x2B: 'sw',
      0x31: 'lwc1', 0x35: 'ldc1', 0x39: 'swc1', 0x3D: 'sdc1', 0x09: 'addiu'}

def spacc(w):
    """(op, rt, offset) when the word is an sp-based load/store/addiu, else None"""
    op, rs, rt, imm = w >> 26, (w >> 21) & 31, (w >> 16) & 31, w & 0xFFFF
    if rs == 29 and op in LS:
        return LS[op], rt, imm - 0x10000 if imm & 0x8000 else imm
    return None

def read_diff(path):
    """screen.py SCREEN_V diff -> (ref words, mine words)"""
    ref, mine = [], []
    for l in open(path):
        m = re.match(r'(\*\*|  ) ([0-9A-F]{8}) ([0-9A-F]{8})', l)
        if m:
            a, b = int(m.group(2), 16), int(m.group(3), 16)
            if m.group(1) == '  ': b = a        # equal after relocation masking
            ref.append(a); mine.append(b)
    return ref, mine

def stack_report(ref, mine):
    """-> dict(frame_ref, frame_mine, stack_only, nonstack, pairs Counter((mine_off, ref_off)))"""
    fr = lambda ws: next((-(spacc(w)[2]) for w in ws[:3] if spacc(w) and spacc(w)[0] == 'addiu' and (w >> 16) & 31 == 29), 0)
    out = dict(frame_ref=fr(ref), frame_mine=fr(mine), pairs=collections.Counter(), nonstack=0)
    if len(ref) != len(mine):
        out['stack_only'] = False; out['nonstack'] = abs(len(ref) - len(mine)) + 1000
        return out
    for a, b in zip(ref, mine):
        if a == b: continue
        sa, sb = spacc(a), spacc(b)
        if sa and sb and sa[0] == sb[0] and sa[1] == sb[1] and (a & 0xFFFF0000) == (b & 0xFFFF0000):
            out['pairs'][(sb[2], sa[2])] += 1
        else:
            out['nonstack'] += 1
    out['stack_only'] = out['nonstack'] == 0
    return out

def fmt_report(r):
    p = ' '.join('%X->%X' % k + ('x%d' % v if v > 1 else '') for k, v in sorted(r['pairs'].items()))
    return 'frame %X/%X%s stack-only=%s nonstack=%d  %s' % (r['frame_mine'], r['frame_ref'],
                                                              '' if r['frame_mine'] == r['frame_ref'] else '(!)',
                                                              r['stack_only'], r['nonstack'], p)

# ------------------------------------------------------------------ screening
def screen(func, drafts, tag):
    """drafts: list of C texts -> list of (result, diff path or None)"""
    d = '%s/build/sf_%s' % (R, tag)
    shutil.rmtree(d, ignore_errors=True)
    for i, c in enumerate(drafts):
        os.makedirs('%s/%d' % (d, i)); open('%s/%d/%s.c' % (d, i, func), 'w').write(c)
    shutil.copy(HOME + '/tools/eu_port/m2c/screen.py', R + '/build/screen.py')
    subprocess.run([DOCKER, 'exec', '-e', 'SCREEN_V=1', '-e', 'SCREEN_DATAREL=1', '-w', '/conker/conker', os.environ.get('CONKERDEV','conkerdev'), 'bash', '-c',
                    "ls build/sf_%s | xargs -P 8 -I{} sh -c 'SCREEN_TMP=build/sf_%s/{}/tmp python3 build/screen.py build/sf_%s/{} 1 >/dev/null 2>&1'"
                    % (tag, tag, tag)], capture_output=True)
    out = []
    for i in range(len(drafts)):
        try: res = open('%s/%d/screen.txt' % (d, i)).read().split()[0]
        except Exception: res = 'NORES'
        dp = '%s/%d/%s.diff' % (d, i, func)
        out.append((res, dp if os.path.exists(dp) else None))
    return out

def score(res, dp):
    """lower is better"""
    if res == 'OK': return (0, 0, 0)
    if dp is None: return (9, 9999, 0)
    rep = stack_report(*read_diff(dp))
    n = int(res[4:]) if res.startswith('DIFF') else 500 + abs(int(res[4:])) * 10 if res.startswith('SIZE') else 9999
    return (1 if rep['stack_only'] else 2, rep['nonstack'] if not rep['stack_only'] else n, n)

# ------------------------------------------------------------------ C draft manipulation
TYPEWORDS = {'s8', 'u8', 's16', 'u16', 's32', 'u32', 's64', 'u64', 'f32', 'f64', 'int', 'char', 'short', 'long',
             'float', 'double', 'unsigned', 'signed', 'void', 'struct', 'union', 'const', 'volatile', 'register',
             'static'}
_TD = None
def is_type(w):
    global _TD
    if w in TYPEWORDS: return True
    if _TD is None:
        try:
            import protocheck; _TD = protocheck.load_typedefs()
        except Exception: _TD = {}
    return w in _TD

def find_func(text, func):
    m = re.search(r'^[^\n;{}]*\b%s\s*\([^;{]*\)\s*\{' % re.escape(func), text, re.M)
    if not m: raise SystemExit('function %s not found in draft' % func)
    s = m.end() - 1; d = 0
    for i in range(s, len(text)):
        if text[i] == '{': d += 1
        elif text[i] == '}':
            d -= 1
            if d == 0: return s, i
    raise SystemExit('unbalanced braces')

def body_lines(text, func):
    s, e = find_func(text, func)
    return text[:s + 1], text[s + 1:e].split('\n'), text[e:]

def parse_decl(line):
    """one-line declaration -> (indent, type, declarator, init, name) or None"""
    m = re.match(r'^(\s*)([^=;{}()]+?|[^=;{}]*\(\s*\*\s*\w+\s*\)\s*\([^;{}]*\))\s*(=\s*[^;]*)?;\s*(//.*)?$', line)
    if not m: return None
    lhs = m.group(2).strip()
    fm = re.match(r'^(.*\(\s*\*\s*)(\w+)(\s*\)\s*\(.*\))$', lhs)
    if fm: ty, nm, dcl = fm.group(1) + fm.group(3), fm.group(2), lhs
    else:
        mm = re.match(r'^(.*?)([\s\*]+)(\w+)((?:\s*\[[^\]]*\])*)$', lhs)
        if not mm: return None
        ty, nm = (mm.group(1) + mm.group(2)).strip(), mm.group(3)
        dcl = lhs[len(mm.group(1)):].strip()
    w = re.findall(r'\w+', ty)
    if not w or w[0] in ('return', 'goto', 'else', 'case'): return None
    base = [x for x in w if x not in ('const', 'volatile', 'register', 'static')]
    if not base or not (base[0] in ('struct', 'union') or is_type(base[0])): return None
    return m.group(1), ty, dcl, (m.group(3) or ''), nm

def split_multi(lines):
    out = []
    for l in lines:
        m = re.match(r'^(\s*)((?:const\s+|volatile\s+|register\s+)*(?:struct\s+)?\w+)\s+([^;=(]*,[^;=(]*);\s*$', l)
        if m and (is_type(m.group(2).split()[-1]) or m.group(2).startswith('struct')):
            for d in m.group(3).split(','):
                out.append('%s%s %s;' % (m.group(1), m.group(2), d.strip()))
        else: out.append(l)
    return out

def blocks(lines):
    """-> list of (open line idx, close line idx, depth) for each '{' ... '}'"""
    st, out = [], []
    for i, l in enumerate(lines):
        for c in re.sub(r'//.*', '', l):
            if c == '{': st.append(i)
            elif c == '}':
                if st: o = st.pop(); out.append((o, i, len(st) + 1))
    return out

def unit_at(lines, i):
    """a declaration unit starting at line i: (end line, name, init) or None"""
    pd = parse_decl(lines[i])
    if pd: return i, pd[4], pd[3]
    if re.match(r'^\s*(const\s+)?(struct|union)\s*\w*\s*\{\s*$', lines[i]):
        d = 0
        for j in range(i, len(lines)):
            d += lines[j].count('{') - lines[j].count('}')
            if d == 0:
                m = re.match(r'^\s*\}\s*(\w+)\s*(\[[^\]]*\])?\s*(=[^;]*)?;', lines[j])
                return (j, m.group(1), m.group(3) or '') if m else None
    return None

def decl_units(lines, start):
    """consecutive declaration units from `start` (blank lines skipped): [(s, e, name, init)]"""
    out, i = [], start
    while i < len(lines):
        if lines[i].strip() == '': i += 1; continue
        u = unit_at(lines, i)
        if not u: break
        out.append((i, u[0], u[1], u[2])); i = u[0] + 1
    return out

def variants(text, func, maxn=400):
    pre, lines, post = body_lines(text, func)
    lines = split_multi(lines)
    out = []
    def emit(nl, tag): out.append((tag, pre + '\n'.join(nl) + post))
    top = decl_units(lines, 0)
    inner = [b for b in blocks(lines) if not any(u[0] <= b[0] <= u[1] for u in top)]
    runs = [(-1, top)] + [(o, decl_units(lines, o + 1)) for (o, c, d) in inner]
    def rebuild(run, order):
        """lines with the units of `run` re-emitted in `order` (indices into run)"""
        s0, e0 = run[0][0], run[-1][1]
        chunk = []
        for k in order: chunk += lines[run[k][0]:run[k][1] + 1]
        return lines[:s0] + chunk + lines[e0 + 1:]
    # 1. orders
    for o, run in runs:
        n = len(run)
        if n < 2: continue
        perms = itertools.permutations(range(n)) if n <= 5 else \
            [list(range(k, n)) + list(range(k)) for k in range(1, n)] + [list(reversed(range(n)))] + \
            [[*range(j), j + 1, j, *range(j + 2, n)] for j in range(n - 1)] + \
            [[j] + [x for x in range(n) if x != j] for j in range(1, n)] + [[x for x in range(n) if x != j] + [j] for j in range(n - 1)]
        for p in perms:
            p = list(p)
            if p != list(range(n)): emit(rebuild(run, p), 'order@%d:%s' % (o, ','.join(run[k][2] for k in p)))
    # 2. pads
    for o, run in runs:
        pos = [u[0] for u in run] + ([run[-1][1] + 1] if run else [o + 1 if o >= 0 else 0])
        ind = re.match(r'\s*', lines[run[0][0]]).group(0) if run else '    '
        for k, i in enumerate(pos):
            for pad in ('s32 sfpad;', 'u8 sfpad[8];', 'u8 sfpad[12];', 'u8 sfpad[16];'):
                nl = list(lines); nl.insert(i, ind + pad)
                emit(nl, 'pad@%d.%d:%s' % (o, k, pad))
    # 3. arrays (local arrays, and array fields of local structs)
    for o, run in runs:
        for u in run:
            for i in range(u[0], u[1] + 1):
                for m in re.finditer(r'\[(\d+|0x[0-9A-Fa-f]+)\]', lines[i]):
                    n = int(m.group(1), 0)
                    for dn in (-2, -1, 1, 2, 4):
                        if n + dn < 1: continue
                        nl = list(lines); nl[i] = lines[i][:m.start()] + '[%d]' % (n + dn) + lines[i][m.end():]
                        emit(nl, 'array@%s:%d%+d' % (u[2], n, dn))
    # 4. into / out of blocks
    for u in top:
        nm = u[2]
        uses = [j for j, l in enumerate(lines) if not (u[0] <= j <= u[1]) and re.search(r'\b%s\b' % re.escape(nm), re.sub(r'//.*', '', l))]
        if not uses: continue
        enc = [(o, c, d) for (o, c, d) in inner if all(o < j <= c for j in uses) and o > u[1]]
        for (o, c, d) in sorted(enc, key=lambda x: -x[2]):
            unit = lines[u[0]:u[1] + 1]
            ind = re.match(r'\s*', lines[o + 1]).group(0) if o + 1 < len(lines) else '    '
            moved = [ind + x.strip() if k in (0, len(unit) - 1) else ind + '    ' + x.strip() for k, x in enumerate(unit)]
            nl = lines[:o + 1] + moved + lines[o + 1:]
            del nl[u[0]:u[1] + 1]
            emit(nl, 'into@%d:%s' % (o, nm))
    for o, run in runs[1:]:
        for u in run:
            unit = lines[u[0]:u[1] + 1]
            nl = lines[:u[0]] + lines[u[1] + 1:]
            ins = (top[-1][1] + 1) if top else 0
            if len(unit) == 1 and u[3]:   # initialiser: keep the assignment in place
                pd = parse_decl(unit[0])
                nl.insert(u[0], '%s%s %s;' % (pd[0], pd[4], pd[3]))
                unit = ['%s %s;' % (pd[1], pd[2])]
            nl = nl[:ins] + ['    ' + x.strip() for x in unit] + nl[ins:]
            emit(nl, 'outof@%d:%s' % (o, u[2]))
    seen, res = set(), []
    for tag, t in out:
        if t in seen or t == text: continue
        seen.add(t); res.append((tag, t))
    return res[:maxn]

def scan(listfile):
    """screen `func draft.c` lines in one batch; print the ones whose diff is stack offsets only"""
    items = [l.split() for l in open(listfile) if l.strip()]
    d = '%s/build/sf_scan' % R
    shutil.rmtree(d, ignore_errors=True)
    for i, (f, p) in enumerate(items):
        os.makedirs('%s/%d' % (d, i))
        open('%s/%d/%s.c' % (d, i, f), 'w').write(''.join(l for l in open(p) if not l.startswith('// PERMUTER')))
    shutil.copy(HOME + '/tools/eu_port/m2c/screen.py', R + '/build/screen.py')
    subprocess.run([DOCKER, 'exec', '-e', 'SCREEN_V=1', '-e', 'SCREEN_DATAREL=1', '-w', '/conker/conker', os.environ.get('CONKERDEV','conkerdev'), 'bash', '-c',
                    "ls build/sf_scan | xargs -P 8 -I{} sh -c 'SCREEN_TMP=build/sf_scan/{}/tmp python3 build/screen.py build/sf_scan/{} 1 >/dev/null 2>&1'"],
                   capture_output=True)
    cnt = collections.Counter()
    for i, (f, p) in enumerate(items):
        try: res = open('%s/%d/screen.txt' % (d, i)).read().split()[0]
        except Exception: res = 'NORES'
        dp = '%s/%d/%s.diff' % (d, i, f)
        if res == 'OK': print('OK        %s %s' % (f, p)); cnt['OK'] += 1; continue
        if not os.path.exists(dp): cnt['noresult'] += 1; continue
        rep = stack_report(*read_diff(dp))
        cnt['stack-only' if rep['stack_only'] else 'other'] += 1
        if rep['stack_only'] or rep['nonstack'] <= 2 and rep['pairs']:
            print('%-9s %s %s  %s' % (res, f, p, fmt_report(rep)))
    print('#', dict(cnt))

def bisect(func, draft):
    """drop each statement in turn; print the ones whose removal changes the frame size or slots"""
    t = open(draft).read()
    pre, lines, post = body_lines(t, func)
    vs, tags = [], []
    for i, l in enumerate(lines):
        if l.strip().endswith(';') and not parse_decl(l) and not l.strip().startswith('return'):
            vs.append(pre + '\n'.join(lines[:i] + lines[i + 1:]) + post); tags.append(l.strip()[:70])
    base = screen(func, [t], func + '_0')[0]
    b = stack_report(*read_diff(base[1])) if base[1] else None
    print('base %s frame %X (target %X)' % (base[0], b['frame_mine'], b['frame_ref']) if b else 'base %s' % base[0])
    for tg, (r, dp) in zip(tags, screen(func, vs, func + '_bis')):
        if not dp: continue
        rep = stack_report(*read_diff(dp))
        if b and rep['frame_mine'] != b['frame_mine']:
            print('frame %X without: %s' % (rep['frame_mine'], tg))

def main():
    a = sys.argv[1:]
    if a and a[0] == '--scan': return scan(a[1])
    if a and a[0] == '--bisect': return bisect(a[1], a[2])
    if len(a) < 2: print(__doc__); sys.exit(1)
    func, draft = a[0], a[1]
    rounds = int(a[a.index('--rounds') + 1]) if '--rounds' in a else 2
    beam = int(a[a.index('--beam') + 1]) if '--beam' in a else 4
    mx = int(a[a.index('--max') + 1]) if '--max' in a else 400
    outd = a[a.index('--out') + 1] if '--out' in a else '%s/build/stackfix/%s' % (R, func)
    os.makedirs(outd, exist_ok=True)
    text = open(draft).read()
    res = screen(func, [text], func + '_0')[0]
    base = score(*res)
    print('%s base %s %s' % (func, res[0], fmt_report(stack_report(*read_diff(res[1]))) if res[1] else ''))
    best = [(base, 'base', text)]
    open(outd + '/best.c', 'w').write(text)
    if res[0] == 'OK':
        open(outd + '/match.c', 'w').write(text); print('MATCH (base)'); return
    seen = {text}; total = 0
    for rnd in range(1, rounds + 1):
        cands = []
        for sc, tag, t in best:
            for tg, v in variants(t, func, mx):
                if v in seen: continue
                seen.add(v); cands.append((tag + ' > ' + tg if tag != 'base' else tg, v))
        if not cands: break
        total += len(cands)
        rs = screen(func, [c for _, c in cands], func)
        scored = sorted(((score(*r), tg, c, r) for (tg, c), r in zip(cands, rs)), key=lambda x: x[0])
        cnt = collections.Counter(r[0] for r in rs)
        top = scored[0]
        rep = fmt_report(stack_report(*read_diff(top[3][1]))) if top[3][1] else ''
        print('round %d: %d candidates, %s; best %s [%s] %s' % (rnd, len(cands),
              ' '.join('%s=%d' % kv for kv in sorted(cnt.items(), key=lambda kv: -kv[1])[:6]), top[3][0], top[1], rep))
        for sc, tg, c, r in scored:
            if r[0] == 'OK':
                open(outd + '/match.c', 'w').write(c); open(outd + '/best.c', 'w').write(c)
                print('MATCH', func, '[%s] -> %s/match.c' % (tg, outd)); return
        if top[0] < best[0][0]:
            open(outd + '/best.c', 'w').write(top[2])
        pool = sorted(best + [(sc, tg, c) for sc, tg, c, r in scored[:beam * 3]], key=lambda x: x[0])
        best = pool[:beam]
    print('no match; best %s -> %s/best.c (%d candidates)' % (best[0][1], outd, total))

if __name__ == '__main__':
    main()
