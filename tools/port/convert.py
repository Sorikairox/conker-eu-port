#!/usr/bin/env python3
"""convert.py: batch asm -> functionally equivalent C (NON_MATCHING bodies).

Host:  tools/port/convert.py [--tag T] [--trials N] [--jobs J] [--insert] [--no-gen] (FUNC... | -l LIST)
  1. m2c drafts with the existing pipeline: gen2.py (JT=1 LAX=1 TYPED=1, typed contexts) into
     port_work/T/gen/v0..v7 and narrow.py variants into n0..n7
  2. in $CONKERDEV: every distinct draft of a function is compiled (IDO, file flags) and run through
     difftest; compile errors go through the autofix passes below (up to 4 rounds per draft);
     the first EQUIV draft wins
  3. --insert: insert the winners under #ifdef NON_MATCHING (insert_nm.py)
  Output: port_work/T/results.tsv (func, result, variant, fixes, reason), port_work/T/pass/<f>.c,
  a summary on stdout.
Container (internal): convert.py --eval DIR [--trials N] [--jobs J] FUNC...
"""
import sys, os, re, glob, json, subprocess, collections

HERE = os.path.dirname(os.path.abspath(__file__))
INSIDE = os.path.exists('/.dockerenv')


# ------------------------------------------------------------------ autofix passes
def _decl_lines(code, name):
    return [l for l in code.split('\n') if re.match(r'^(extern\s+)?[A-Za-z_][\w\s\*]*\b%s\b\s*(\(|\[|;)' % re.escape(name), l)
            and l.rstrip().endswith(';')]

def fix_redecl(code, err, func=None, src=None):
    """IDO 'redeclaration of X' / 'Incompatible type ... X': drop the draft's own declaration of X"""
    names = re.findall(r"redeclaration of '(\w+)'", err) + re.findall(r'\b(func_\w+|D_\w+)\b.*incompatible', err, re.I)
    names += re.findall(r"Incompatible[^']*'(\w+)'", err)
    ch = False
    for n in set(names):
        for l in _decl_lines(code, n):
            code = code.replace(l + '\n', '', 1); ch = True
    return code if ch else None

def fix_question_types(code, err, func=None, src=None):
    """leftover m2c '?' types"""
    if '?' not in code: return None
    c = re.sub(r'^\? (\w+\()', r's32 \1', code, flags=re.M)
    c = re.sub(r'\(\?\)', '(s32)', c); c = re.sub(r'\? \*', 's32 *', c); c = re.sub(r'\b\? ', 's32 ', c)
    return c if c != code else None

def fix_m2c_macros(code, err):
    """M2C_ERROR(...) / unknown m2c helpers: not fixable automatically"""
    return None

def fix_undeclared(code, err, func=None, src=None):
    """'X' undefined: declare X as an extern s32 array / function, hoisted"""
    names = re.findall(r"'(\w+)' undefined", err) + re.findall(r'(\w+) undefined', err)
    add = []
    for n in set(names):
        if n.startswith('func_'): add.append('//HOIST s32 %s();' % n)
        elif n.startswith(('D_', 'jtbl_')): add.append('//HOIST extern u8 %s[];' % n)
    if not add: return None
    return '\n'.join(add) + '\n' + code

def fix_args_count(code, err, func=None, src=None):
    """'too few/many arguments' to a callee whose header prototype disagrees with m2c: K&R-call it
    through a cast to an unprototyped pointer"""
    m = re.search(r'(?:too (?:few|many) arguments|number of arguments).*?(func_\w+)', err, re.I)
    if not m:
        return None
    n = m.group(1)
    c = re.sub(r'(?<![\w*])%s\(' % n, '((s32 (*)())%s)(' % n, code)
    # keep the definition name intact
    return c if c != code else None

def _ctx_lines(err):
    return [l[2:] for l in err.split(' | ') if l.startswith('@@')] + re.findall(r'@@([^|]*)', err)

def fix_implicit_proto(code, err, func=None, src=None):
    """'redeclaration of X; previous declaration at line N': X was used before its (prototyped) definition,
    so the implicit int X() clashes. Hoist X's prototype (from its C definition in the file or in the draft)."""
    names = re.findall(r"redeclaration of '(\w+)'", err)
    add = []
    for n in set(names):
        for text in (code, src or ''):
            m = re.search(r'^([A-Za-z_][^;{}()\n]*\b%s\s*\([^;{}]*?\))\s*\{' % n, text, re.M)
            if m:
                add.append('//HOIST %s;' % ' '.join(m.group(1).split())); break
    add = [a for a in add if a not in code]
    return '\n'.join(add) + '\n' + code if add else None

def fix_cmp_cast(code, err, func=None, src=None):
    """'Unacceptable operand of == or !=' (pointer vs int / incompatible pointers): compare as s32"""
    if 'Unacceptable operand' not in err: return None
    ptrs = set(re.findall(r'\*\s*(\w+)\s*[;,)=]', code))
    out = code
    for ln in _ctx_lines(err):
        new = ln
        new = re.sub(r'(?<![\w)*.>])(&\w+)', r'(s32)\1', new)
        for v in ptrs:
            new = re.sub(r'(?<![\w*>.(])\b%s\b(?!\s*(?:->|\[|\())' % re.escape(v), '(s32)' + v, new)
        new = re.sub(r'\(s32\)\(s32\)', '(s32)', new)
        if new != ln: out = out.replace(ln, new)
    return out if out != code else None

def fix_fnptr(code, err, func=None, src=None):
    if 'Non-function name referenced' not in err: return None
    import tempfile
    a = tempfile.mktemp(suffix='.c'); b = a + '.out.c'; open(a, 'w').write(code)
    subprocess.run(['python3', os.path.join(HERE, '../eu_port/fnptrfix.py'), a, b], capture_output=True)
    return open(b).read() if os.path.exists(b) else None

def fix_passthrough(code, why, func):
    """DIFFER 'call #k X: aN ref=.. cand=..' where the reference leaves aN untouched (the caller's own argN
    passed through, which m2c drops): append the caller's params as extra arguments of X up to N"""
    m = re.search(r': call #\d+ (\w+): a(\d) ref=', why or '')
    if not m: return None
    callee, n = m.group(1), int(m.group(2))
    if callee.startswith('0x'): callee = 'func_' + callee[2:].upper()
    dm = re.search(r'\b%s\s*\(([^)]*)\)\s*\{' % func, code)
    if not dm: return None
    params = [re.findall(r'(\w+)\s*$', p.strip())[0] for p in dm.group(1).split(',') if p.strip() and p.strip() != 'void']
    if n >= len(params): return None
    out = []; i = 0; ch = False
    pat = re.compile(r'(?<![\w*])%s\(' % re.escape(callee))
    while True:
        mm = pat.search(code, i)
        if not mm: out.append(code[i:]); break
        j = mm.end(); depth = 1; args = []; cur = ''
        while depth and j < len(code):
            c = code[j]; j += 1
            if c in '([': depth += 1
            elif c in ')]':
                depth -= 1
                if depth == 0: break
            if c == ',' and depth == 1: args.append(cur); cur = ''; continue
            cur += c
        if cur.strip(): args.append(cur)
        args = [x.strip() for x in args]
        line_start = code.rfind('\n', 0, mm.start()) + 1
        is_decl = code[line_start:mm.start()].strip() != '' and code[j:j + 1] == ';' and not re.search(r'[=(]', code[line_start:mm.start()])
        if is_decl:
            # widen the prototype
            if len(args) <= n: args = (args if args != ['void'] else []) + ['s32'] * (n + 1 - len(args if args != ['void'] else []))
        elif len(args) == n:
            args = args[:n] + [params[n]]
        elif len(args) < n:
            return None
        else:
            # an argument occupies slot n: insert the passthrough before it (m2c shifted the args)
            args = args[:n] + [params[n]] + args[n:]
        out.append(code[i:mm.end()] + ', '.join(args) + ')'); i = j; ch = True
    return ''.join(out) if ch else None

def lint(code):
    """EQUIV-but-fragile patterns that difftest cannot see (it never dereferences pointers inside stubs)"""
    out = []
    scal = set(re.findall(r'^\s+(?:s8|u8|s16|u16|s32|u32|f32|f64|s64|u64)\s+(sp[0-9A-F]+);', code, re.M))
    if any(re.search(r'&%s\b' % v, code) for v in scal):
        out.append('lint:stackaddr')   # &scalar stack local passed on: callee may read neighbours -> make it an array/struct (vecfix.py/spstruct.py)
    if re.search(r'\bsubroutine_arg|\bsaved_reg|M2C_', code): out.append('lint:m2cmacro')
    return out

FIXES = [('implproto', fix_implicit_proto), ('cmpcast', fix_cmp_cast), ('fnptr', fix_fnptr), ('redecl', fix_redecl), ('qtypes', fix_question_types), ('undecl', fix_undeclared), ('argc', fix_args_count)]


# ------------------------------------------------------------------ container side
def eval_one(item):
    func, drafts, trials, tmp = item
    sys.path.insert(0, os.path.join(HERE, 'difftest'))
    import difftest
    rank = {'EQUIV': 0, 'UNSURE': 1, 'DIFFER': 2, 'CERR': 3, 'ERROR': 4}
    best = None
    src = open(difftest.find_file(func)[0]).read() if difftest.find_file(func)[0] else ''
    log = []
    import time
    t0 = time.time(); budget = float(os.environ.get('CONVERT_BUDGET', '150'))
    for vname, code in drafts:
        if time.time() - t0 > budget: log.append('%s\t-\t-\tbudget exhausted' % func); break
        fixes = []
        for rnd in range(6):
            res = difftest.check(func, code, False, trials, 1, 100000, False, tmp)
            res.update(variant=vname, fixes=','.join(fixes), code=code)
            log.append('%s\t%s\t%s\t%s' % (func, vname, ','.join(fixes), res['line'][:200]))
            if best is None or rank[res['result']] <= rank[best['result']]: best = res
            c2 = None
            if res['result'] == 'CERR':
                for nm, fx in FIXES:
                    c2 = fx(code, res['line'], func, src)
                    if c2 is not None and c2 != code: break
                    c2 = None
            elif res['result'] == 'DIFFER':
                nm = 'passthru'; c2 = fix_passthrough(code, res.get('why'), func)
            if c2 is None: break
            code = c2; fixes.append(nm)
        if best['result'] == 'EQUIV': break
    if best is None: best = dict(func=func, result='NODRAFT', line='NODRAFT %s' % func, variant='', fixes='')
    best['log'] = log
    if best['result'] == 'EQUIV':
        lt = lint(best['code'])
        if lt: best['fixes'] = ','.join([x for x in [best.get('fixes', '')] + lt if x])
    if best is None: best = dict(func=func, result='NODRAFT', line='NODRAFT %s' % func, variant='', fixes='')
    return best

def inner_eval(d, funcs, trials, jobs):
    from multiprocessing import Pool
    items = []
    for f in funcs:
        seen = set(); dr = []
        for v in sorted(glob.glob(os.path.join(d, 'gen', '*', f + '.c')), key=lambda x: ('vuan'.find(os.path.basename(os.path.dirname(x))[0]), x)):
            c = open(v).read()
            if c in seen: continue
            seen.add(c); dr.append((os.path.basename(os.path.dirname(v)), c))
        items.append((f, dr, trials, 'build/convert_tmp/%s' % f))
    os.makedirs(os.path.join(d, 'pass'), exist_ok=True)
    with Pool(jobs) as pool, open(os.path.join(d, 'results.tsv'), 'w') as fo, open(os.path.join(d, 'attempts.tsv'), 'w') as fd:
        for r in pool.imap_unordered(eval_one, items):
            reason = r['line'].split(': ', 1)[1] if ': ' in r['line'] else r['line']
            fo.write('\t'.join([r['func'], r['result'], r.get('variant', ''), r.get('fixes', ''), reason.replace('\t', ' ')]) + '\n'); fo.flush()
            fd.write('\n'.join(r.get('log', [])) + '\n'); fd.flush()
            if r['result'] == 'EQUIV':
                open(os.path.join(d, 'pass', r['func'] + '.c'), 'w').write(r['code'])
            print(r['line'][:160], flush=True)


# ------------------------------------------------------------------ host side
def host(argv):
    tag, trials, jobs, insert, gen = 'default', 64, 8, False, True
    funcs = []; i = 0
    while i < len(argv):
        a = argv[i]
        if a == '--tag': tag = argv[i + 1]; i += 2; continue
        if a == '--trials': trials = int(argv[i + 1]); i += 2; continue
        if a == '--jobs': jobs = int(argv[i + 1]); i += 2; continue
        if a == '-l': funcs += [l.split()[0] for l in open(argv[i + 1]) if l.strip()]; i += 2; continue
        if a == '--insert': insert = True
        elif a == '--no-gen': gen = False
        else: funcs.append(a)
        i += 1
    R = os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker'))
    W = os.path.join(R, 'port_work', tag); os.makedirs(W, exist_ok=True)
    open(os.path.join(W, 'only.txt'), 'w').write('\n'.join(funcs) + '\n')
    M = os.path.join(R, 'tools/eu_port/m2c')
    env = dict(os.environ, ONLY=os.path.join(W, 'only.txt'), JT='1', LAX='1', TYPED='1', CONKER_ROOT=R)
    if gen:
        subprocess.run(['rm', '-rf', os.path.join(W, 'gen')])
        with open(os.path.join(W, 'gen.log'), 'w') as lg:
            subprocess.run([os.path.join(M, 'venv/bin/python3'), os.path.join(M, 'gen2.py'), os.path.join(W, 'gen'), '1', '5000'],
                           env=env, stdout=lg, stderr=subprocess.STDOUT, cwd=R)
            # untyped contexts too (TYPED drafts can scale byte offsets on struct127 pointers)
            env2 = dict(env); env2.pop('TYPED')
            subprocess.run(['rm', '-rf', os.path.join(W, 'genu')])
            subprocess.run([os.path.join(M, 'venv/bin/python3'), os.path.join(M, 'gen2.py'), os.path.join(W, 'genu'), '1', '5000'],
                           env=env2, stdout=lg, stderr=subprocess.STDOUT, cwd=R)
            for v in sorted(glob.glob(os.path.join(W, 'genu', 'v*'))):
                os.rename(v, os.path.join(W, 'gen', 'u' + v[-1]))
            for v in sorted(glob.glob(os.path.join(W, 'gen', 'v*')) + glob.glob(os.path.join(W, 'gen', 'u*'))):
                subprocess.run(['python3', os.path.join(M, 'narrow.py'), v, os.path.join(W, 'gen', 'n' + os.path.basename(v))],
                               stdout=lg, stderr=subprocess.STDOUT, cwd=R)
            # argfix variants: callee prototypes re-derived from the caller's asm (fixes wrong header arities)
            for v in sorted(glob.glob(os.path.join(W, 'gen', 'v*')) + glob.glob(os.path.join(W, 'gen', 'u*'))):
                ad = os.path.join(W, 'gen', 'a' + os.path.basename(v)); os.makedirs(ad, exist_ok=True)
                for c in glob.glob(os.path.join(v, '*.c')):
                    f = os.path.basename(c)[:-2]
                    subprocess.run(['python3', os.path.join(R, 'tools/eu_port/argfix.py'), '--tail', f, c, os.path.join(ad, f + '.c')],
                                   stdout=lg, stderr=subprocess.STDOUT, cwd=R, env=env)
    dk = os.environ.get('CONKERDEV', 'conkerdev')
    cw = '/conker/' + os.path.relpath(W, R)
    subprocess.run(['docker', 'exec', '-w', '/conker/conker', dk, 'python3', '../tools/port/convert.py', '--eval', cw,
                    '--trials', str(trials), '--jobs', str(jobs)] + funcs)
    rows = [l.rstrip('\n').split('\t') for l in open(os.path.join(W, 'results.tsv'))]
    cnt = collections.Counter(r[1] for r in rows)
    print('== %s: %d functions: %s' % (tag, len(rows), ', '.join('%s %d' % kv for kv in cnt.most_common())))
    if insert:
        sys.path.insert(0, HERE); import insert_nm
        for r in rows:
            if r[1] == 'EQUIV':
                print(r[0], insert_nm.insert(r[0], open(os.path.join(W, 'pass', r[0] + '.c')).read()))


if __name__ == '__main__':
    if len(sys.argv) > 2 and sys.argv[1] == '--eval':
        d = sys.argv[2]; a = sys.argv[3:]; trials, jobs = 64, 8; fs = []; i = 0
        while i < len(a):
            if a[i] == '--trials': trials = int(a[i + 1]); i += 2; continue
            if a[i] == '--jobs': jobs = int(a[i + 1]); i += 2; continue
            fs.append(a[i]); i += 1
        inner_eval(d, fs, trials, jobs)
    else:
        if not INSIDE: os.environ['PATH'] += ':/Applications/Docker.app/Contents/Resources/bin'
        host(sys.argv[1:])
