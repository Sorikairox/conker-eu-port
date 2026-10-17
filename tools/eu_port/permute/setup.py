#!/usr/bin/env python3
# Runs inside the container from /conker/conker.
# usage: setup.py <func> <draft.c> <outdir>
#   Builds a decomp-permuter input dir for one GLOBAL_ASM function:
#   - base.c: the function's C file with every GLOBAL_ASM pragma removed and the draft in place of
#     the function's pragma (same TU as m2c/screen.py), run through cpp, bodies of functions after
#     the target reduced to prototypes (faster compiles; earlier bodies must stay: IDO uses the
#     register usage of callees it has already compiled in the same file);
#   - target.o: the function's .s (rodata_inject words included) assembled with macro.inc;
#   - compile.sh: the file's own IDO cc line from `make -n` (per-file OPT_FLAGS apply);
#   - settings.toml: func_name, compiler_type = "ido".
# usage: setup.py extract <func> <source.c> [draft.c]  -> prints the function's definition from a
#   permuter output source.c (to feed m2c/try or rep.py).
import sys, os, re, subprocess, shlex
sys.path.insert(0, '/conker/tools/eu_port/m2c')
PRAG = re.compile(r'#pragma GLOBAL_ASM\("([^"]*)/(\w+)\.s"\)')
ROOT = '/conker/conker'


def find_src(func):
    out = subprocess.run(['grep', '-rl', '--include=*.c', '/%s.s"' % func, 'src_eu'],
                         capture_output=True, text=True).stdout.split()
    return out[0] if out else None


def cc_cmd(p):
    r = subprocess.run(['make', '-n', '-B', 'VERSION=eu', 'build/' + p + '.o'],
                       capture_output=True, text=True).stdout
    for l in r.split('\n'):
        if '/cc ' in l and ' -c ' in l:
            a = shlex.split(l)
            i = a.index('-o'); a = a[:i] + a[i + 2:]
            a = [x for x in a if not x.endswith('.c')]
            a[0] = os.path.normpath(os.path.join(ROOT, a[0]))
            return a
    return None


def find_body(src, name, start=0):
    """(start, end) of the definition of `name` (from the line start to the closing brace)."""
    for m in re.finditer(r'^[^\n;#]*?\b%s\s*\(' % re.escape(name), src[start:], re.M):
        i = start + m.end(); depth = 1
        while depth and i < len(src):
            depth += {'(': 1, ')': -1}.get(src[i], 0); i += 1
        j = i
        while j < len(src) and src[j] in ' \t\n': j += 1
        if j < len(src) and src[j] == '{':
            d = 0
            for k in range(j, len(src)):
                if src[k] == '{': d += 1
                elif src[k] == '}':
                    d -= 1
                    if d == 0: return start + m.start(), k + 1, j
    return None


def strip_others(src, keep):
    """replace every function body except `keep`'s with ';'"""
    out = []; i = 0; seen = False
    fn = re.compile(r'^[A-Za-z_][^\n;#=]*?\b(\w+)\s*\(', re.M)
    while True:
        m = fn.search(src, i)
        if not m: out.append(src[i:]); break
        r = find_body(src, m.group(1), m.start())
        if not r or r[0] != m.start():
            out.append(src[i:m.end()]); i = m.end(); continue
        s, e, brace = r
        if m.group(1) == keep or not seen:
            # IDO -O2 uses the register usage of callees compiled earlier in the same file, so
            # bodies before the target must stay; later ones only cost compile time.
            out.append(src[i:e])
            if m.group(1) == keep: seen = True
        else:
            out.append(src[i:brace].rstrip() + ';')
        i = e
    return ''.join(out)


def setup(func, draft, od):
    os.makedirs(od, exist_ok=True)
    p = find_src(func)
    if not p: sys.exit('no GLOBAL_ASM pragma for %s' % func)
    src = open(p).read()
    m = [x for x in PRAG.finditer(src) if x.group(2) == func][-1]
    spath = m.group(1) + '/' + func + '.s'
    tu = src[:m.start()] + '\n' + open(draft).read() + '\n' + src[m.end():]
    tu = PRAG.sub('', tu)
    cmd = cc_cmd(p)
    # preprocess with the file's -D/-I flags
    cpp = ['cpp', '-P', '-undef', '-D__sgi', '-D_LANGUAGE_C', '-DPERMUTER', '-D_MIPS_SZINT=32',
           '-D_MIPS_SZLONG=32', '-nostdinc', '-']
    for i, a in enumerate(cmd):
        if a in ('-D', '-I'): cpp += [a, cmd[i + 1]]
        elif a.startswith('-D') or a.startswith('-I'): cpp.append(a)
    r = subprocess.run(cpp, input=tu, capture_output=True, text=True, cwd=ROOT)
    if r.returncode: sys.exit('cpp failed:\n' + r.stderr[-2000:])
    base = r.stdout if os.environ.get('PERM_NOSTRIP') else strip_others(r.stdout, func)
    open(os.path.join(od, 'base.c'), 'w').write(base)
    # compile.sh: permuter calls `compile.sh in.c -o out.o`
    sh = '#!/bin/bash\nset -e\nIN=$(realpath "$1"); OUT=$(realpath -m "$3")\ncd %s\n%s -o "$OUT" "$IN"\n' % (
        ROOT, ' '.join(shlex.quote(a) for a in cmd))
    open(os.path.join(od, 'compile.sh'), 'w').write(sh); os.chmod(os.path.join(od, 'compile.sh'), 0o755)
    # target.o
    s = open(spath).read()
    asm = '.include "macro.inc"\n.set noat\n.set noreorder\n.set gp=64\n.text\n' + s + '\n'
    open(os.path.join(od, 'target.s'), 'w').write(asm)
    r = subprocess.run(['mips-linux-gnu-as', '-EB', '-mtune=vr4300', '-march=vr4300', '-mabi=32',
                        '-I', 'include', '-o', os.path.join(od, 'target.o'), os.path.join(od, 'target.s')],
                       capture_output=True, text=True, cwd=ROOT)
    if r.returncode: sys.exit('as failed:\n' + r.stderr[-2000:])
    open(os.path.join(od, 'settings.toml'), 'w').write(
        'func_name = "%s"\ncompiler_type = "ido"\n' % func)
    open(os.path.join(od, 'src.txt'), 'w').write(p + '\n')
    # sanity: the base must compile
    r = subprocess.run([os.path.join(od, 'compile.sh'), os.path.join(od, 'base.c'), '-o',
                        os.path.join(od, 'base.o')], capture_output=True, text=True)
    if r.returncode: sys.exit('base.c does not compile:\n' + (r.stdout + r.stderr)[-1500:])
    print('setup %s (%s) -> %s' % (func, p, od))


def extract(func, path, draft=None):
    s = open(path).read()
    r = find_body(s, func)
    if not r: sys.exit('function not found')
    pre = ''
    if draft:   # keep the draft's own declarations above the function
        d = open(draft).read(); rd = find_body(d, func)
        if rd: pre = d[:rd[0]]
    # the permuter may also change declarations outside the function (e.g. a callee's return
    # type); report them as comments, they are not part of the draft
    note = ''
    bp = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(path))), 'base.c')
    if os.path.exists(bp):
        DECL = re.compile(r'^([^\n;{}#]*?\b(\w+)\s*\([^;{}]*\)\s*);', re.M)
        def top(t):   # text at brace depth 0 (drops bodies and struct members)
            o = []; d = 0
            for ch in t:
                if ch == '{': d += 1; o.append(';')
                elif ch == '}': d -= 1
                elif d == 0: o.append(ch)
            return ''.join(o)
        def decls(t):
            t = top(t)
            return {m.group(2): re.sub(r'^extern', '', re.sub(r'\s+', '', m.group(1))) for m in DECL.finditer(t)}
        b = decls(open(bp).read()); n = decls(s[:r[0]] + s[r[1]:])
        for k in sorted(n):
            if k in b and n[k] != b[k] and not b[k].startswith(k) and not n[k].startswith(k):
                note += '// PERMUTER CHANGED DECL: %s (base: %s)\n' % (n[k], b[k])
    print(note + pre + s[r[0]:r[1]])


if __name__ == '__main__':
    os.chdir(ROOT)
    if sys.argv[1] == 'extract': extract(*sys.argv[2:5])
    else: setup(sys.argv[1], sys.argv[2], sys.argv[3])
