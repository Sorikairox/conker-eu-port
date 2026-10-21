#!/usr/bin/env python3
"""Near-miss inventory for the main slot (init + lo game slice < 0x130000) (s141).

usage: nearmiss.py [--out docs/sessions/s141_nearmiss.txt] [--skip f1,f2,...] [--all]

1. Lists the functions still GLOBAL_ASM (m2c/list.py) in the slice (src_eu/init*.c, game files
   whose stem offset is < 0x130000; --all: every file).
2. Collects drafts for them: docs/sessions/*_drafts/<func>*.c and tools/decomp-permuter/nm/<func>/{best,draft}.c.
   CERR drafts that fail on a redeclaration are re-tried through redeclfix.py.
3. Screens every draft with m2c/screen.py in rounds (round r = the r-th draft of each function, one
   screen.py run per round over conker/build_port/nearmiss/r<r>/), 8 jobs.
4. Writes the ranking (best draft per function): OK, then DIFF n / SIZE+-n by key
   (DIFF n -> n, SIZE+-n -> 10*|n|), CERR last. Columns: result func insns draft [others: n].
Skipped: --skip names, plus every function named on a line of HANDOFF.md / docs/sessions/*.md that
says "permuter-resistant" or "handwritten asm".
"""
import os, re, sys, glob, subprocess, shutil, collections
R = os.path.realpath(os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker')))
DEV = os.environ.get('CONKERDEV', 'conkerdev')
os.environ['PATH'] += ':/Applications/Docker.app/Contents/Resources/bin'
args = sys.argv[1:]
out = os.path.join(R, 'docs/sessions/s141_nearmiss.txt'); skip = set(); allslice = False
while args:
    a = args.pop(0)
    if a == '--out': out = os.path.abspath(args.pop(0))
    elif a == '--skip': skip |= set(x for x in args.pop(0).split(',') if x)
    elif a == '--all': allslice = True
FN = re.compile(r'\b((?:func|sub|init)_(?:eu_)?[0-9A-Fa-f]{6,8}|[A-Za-z_]\w*)\b')

def inslice(src):
    b = os.path.basename(src)
    if allslice or b.startswith('init'): return True
    m = re.match(r'game(?:_eu)?_([0-9A-F]+)\.c$', b)
    return bool(m) and int(m.group(1), 16) < 0x130000

lst = subprocess.run(['python3', R + '/tools/eu_port/m2c/list.py'], capture_output=True, text=True, cwd=R).stdout
asm = {}
for ln in lst.splitlines():
    p = ln.split()
    if len(p) >= 3 and p[0].isdigit() and inslice(p[1]): asm[p[2]] = (int(p[0]), p[1])
# skip lists from the docs
for doc in [R + '/HANDOFF.md'] + glob.glob(R + '/docs/sessions/*.md'):
    for ln in open(doc, errors='replace'):
        if re.search(r'permuter-resistant|handwritten asm', ln, re.I):
            skip |= set(re.findall(r'\bfunc_[0-9A-F]{8}\b', ln))
drafts = collections.defaultdict(list)
for d in sorted(glob.glob(R + '/docs/sessions/*_drafts/*.c')):
    m = re.match(r'(func_[0-9A-F]{8}|[A-Za-z_]\w*?)(?:_|\.c$)', os.path.basename(d))
    f = m and m.group(1)
    if f not in asm:  # names like __n_foo_DIFF3.c: longest asm-name prefix
        b = os.path.basename(d)[:-2]
        f = max((k for k in asm if b == k or b.startswith(k + '_')), key=len, default=None)
    if f in asm: drafts[f].append(d)
for d in glob.glob(R + '/tools/decomp-permuter/nm/*/best.c') + glob.glob(R + '/tools/decomp-permuter/nm/*/draft.c'):
    f = os.path.basename(os.path.dirname(d))
    if f in asm and os.path.getsize(d) > 0: drafts[f].append(d)
excl = sorted(f for f in drafts if f in skip)
for f in excl: del drafts[f]
nr = max((len(v) for v in drafts.values()), default=0)
base = R + '/conker/build_port/nearmiss'; shutil.rmtree(base, ignore_errors=True)
idx = {}
for r in range(nr):
    rd = '%s/r%d' % (base, r); os.makedirs(rd)
    for f, v in drafts.items():
        if r < len(v): shutil.copy(v[r], '%s/%s.c' % (rd, f)); idx[(r, f)] = v[r]
shutil.copy(R + '/tools/eu_port/m2c/screen.py', R + '/conker/build/screen.py')
sys.stderr.write('%d slice asm funcs, %d with drafts (%d drafts, %d rounds), %d skipped\n'
                 % (len(asm), len(drafts), sum(map(len, drafts.values())), nr, len(excl)))
res = collections.defaultdict(list)
for r in range(nr):
    rel = 'build_port/nearmiss/r%d' % r
    subprocess.run(['docker', 'exec', '-e', 'SCREEN_TMP=build_port/nearmiss/tmp%d' % r, '-w', '/conker/conker', DEV,
                    'python3', 'build/screen.py', rel, '8'], capture_output=True)
    st = '%s/r%d/screen.txt' % (base, r)
    if not os.path.exists(st): continue
    for ln in open(st):
        p = ln.split()
        if len(p) >= 2 and (r, p[1]) in idx: res[p[1]].append((p[0], idx[(r, p[1])]))

def key(s):
    if s == 'OK': return 0
    m = re.match(r'DIFF(\d+)', s)
    if m: return int(m.group(1))
    m = re.match(r'SIZE([+-]\d+)', s)
    if m: return 10 * abs(int(m.group(1)))
    return 10 ** 6
# CERR "redeclaration of X" (prototype drift since the draft was written): redeclfix.py, 4 at a time
def fix(f):
    o = '%s/fix/%s.c' % (base, f)
    p = subprocess.run(['python3', R + '/tools/eu_port/redeclfix.py', f, res[f][0][1], o], capture_output=True,
                       text=True, cwd=R, env=dict(os.environ, TRYDIR='rd_' + f))
    t = p.stdout.split(); r = t[1] if len(t) > 1 else 'CERR'
    if r == 'CERR' and os.path.exists(o) and "redeclaration of '%s'" % f in p.stdout:
        # the draft's return type disagrees with the file/header prototype: take the prototype's
        rt = None
        for h in [R + '/conker/' + asm[f][1]] + glob.glob(R + '/conker/include/**/*.h', recursive=True):
            m = re.search(r'^\s*(?:extern\s+)?([A-Za-z_][\w\s\*]*?)\s*\b%s\s*\([^;{]*\)\s*;' % f, open(h, errors='replace').read(), re.M)
            if m: rt = m.group(1).strip(); break
        if rt:
            src = open(o).read()
            src2 = re.sub(r'^[A-Za-z_][\w\s\*]*?(\b%s\s*\([^;]*?\)\s*\n?\s*\{)' % f, lambda mm: rt + ' ' + mm.group(1), src, count=1, flags=re.M)
            if src2 != src:
                o2 = o[:-2] + '_rt.c'; open(o2, 'w').write(src2)
                p = subprocess.run(['python3', R + '/tools/eu_port/redeclfix.py', f, o2, o], capture_output=True,
                                   text=True, cwd=R, env=dict(os.environ, TRYDIR='rd_' + f))
                t = p.stdout.split(); r = t[1] if len(t) > 1 else 'CERR'
    if os.path.exists(o) and key(r) < key(res[f][0][0]): res[f].insert(0, (r, o))
os.makedirs(base + '/fix', exist_ok=True)
for f in res: res[f].sort(key=lambda x: key(x[0]))
cerr = [f for f in res if res[f][0][0] == 'CERR']
if cerr:
    from concurrent.futures import ThreadPoolExecutor
    with ThreadPoolExecutor(4) as ex: list(ex.map(fix, cerr))
    sys.stderr.write('redeclfix on %d CERR drafts\n' % len(cerr))
rows = []
for f, v in res.items():
    v.sort(key=lambda x: key(x[0])); s, d = v[0]
    rows.append((key(s), asm[f][0], s, f, os.path.relpath(d, R), len(v) - 1, asm[f][1]))
rows.sort()
with open(out, 'w') as fo:
    fo.write('# nearmiss.py: best screened draft per slice function still GLOBAL_ASM (key: DIFF n = n, SIZE+-n = 10|n|)\n')
    fo.write('# result func insns file draft (+n other drafts)\n')
    for k, n, s, f, d, o, src in rows: fo.write('%-9s %-14s %4d %-28s %s +%d\n' % (s, f, n, os.path.basename(src), d, o))
    if excl: fo.write('# skipped (skip list): %s\n' % ' '.join(excl))
print('%d rows -> %s; OK %d, key<=30 %d' % (len(rows), out, sum(r[0] == 0 for r in rows), sum(r[0] <= 30 for r in rows)))
