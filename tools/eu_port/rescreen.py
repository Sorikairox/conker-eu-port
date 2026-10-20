#!/usr/bin/env python3
"""Rescreen existing drafts of the asm callers of changed functions (host side).

usage: rescreen.py [func ...]        (default: every KEEP of tools/eu_port/protocheck.log)

Callers = GLOBAL_ASM functions whose .s has `jal <func>`. Drafts per caller:
tools/decomp-permuter/nm/<f>/best.c and tools/decomp-permuter/sweep/drafts*/<f>.c, each as is
and with its own top-level prototypes of the changed functions removed (the header now
decides). Screens them with m2c/screen.py (8 jobs) and prints one line per caller with the
best result; OK drafts are copied to conker/build/hand/<f>.c for m2c/apply.py.
"""
import os, re, sys, glob, subprocess, shutil, collections
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
HOME = os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+''); R = HOME + '/conker'
DOCKER = '/Applications/Docker.app/Contents/Resources/bin/docker'
PERM = HOME + '/tools/decomp-permuter'

def changed_from_log():
    out = set()
    p = HOME + '/tools/eu_port/protocheck.log'
    for l in open(p):
        m = re.match(r'KEEP (\w+) ', l)
        if m: out.add(m.group(1))
    return out

def main():
    ch = set(sys.argv[1:]) or changed_from_log()
    asmf = {}
    for p in glob.glob(R + '/src_eu/**/*.c', recursive=True):
        for m in re.finditer(r'#pragma\s+GLOBAL_ASM\("([^"]*)/(\w+)\.s"\)', open(p).read()):
            asmf[m.group(2)] = R + '/' + m.group(1) + '/' + m.group(2) + '.s'
    callers = collections.defaultdict(set)
    for f, sp in asmf.items():
        if not os.path.exists(sp): continue
        for t in re.findall(r'\bjal\s+(\w+)', open(sp).read()):
            if t in ch: callers[f].add(t)
    drafts = collections.defaultdict(list)
    for f in callers:
        srcs = [PERM + '/nm/%s/best.c' % f] + sorted(glob.glob(PERM + '/sweep/drafts*/%s.c' % f))
        for s in srcs:
            if not os.path.exists(s): continue
            t = ''.join(l for l in open(s) if not l.startswith('// PERMUTER'))
            drafts[f].append((s, t))
            pat = re.compile(r'^[^\n(]*\b(%s)\s*\([^;{]*\);\s*$' % '|'.join(map(re.escape, callers[f])), re.M)
            t2 = pat.sub('', t)
            if t2 != t: drafts[f].append((s + ' (no protos)', t2))
    d = R + '/build/rescreen'
    shutil.rmtree(d, ignore_errors=True)
    nv = max((len(v) for v in drafts.values()), default=0)
    for i in range(nv):
        os.makedirs('%s/v%d' % (d, i))
        for f, l in drafts.items():
            if i < len(l): open('%s/v%d/%s.c' % (d, i, f), 'w').write(l[i][1])
    shutil.copy(HOME + '/tools/eu_port/m2c/screen.py', R + '/build/screen.py')
    for i in range(nv):
        subprocess.run([DOCKER, 'exec', '-e', 'SCREEN_TMP=build/rescreen/tmp%d' % i, '-w', '/conker/conker', os.environ.get('CONKERDEV','conkerdev'),
                        'python3', 'build/screen.py', 'build/rescreen/v%d' % i, '8'], capture_output=True)
    res = collections.defaultdict(list)
    for i in range(nv):
        p = '%s/v%d/screen.txt' % (d, i)
        if not os.path.exists(p): continue
        for l in open(p):
            w = l.split()
            if len(w) >= 2: res[w[1]].append((w[0], i))
    def key(r):
        x = r[0]
        if x == 'OK': return 0
        if x.startswith('DIFF'): return int(x[4:])
        if x.startswith('SIZE'): return 100 + abs(int(x[4:]))
        return 10000
    nok = 0
    os.makedirs(R + '/build/hand', exist_ok=True)
    for f in sorted(callers):
        if not res.get(f): print('%-14s none (%d drafts)' % (f, len(drafts[f]))); continue
        b = min(res[f], key=key)
        src = drafts[f][b[1]][0].replace(PERM + '/', '')
        print('%-14s %-8s %s  [callees %s]' % (f, b[0], src, ','.join(sorted(callers[f]))))
        if b[0] == 'OK':
            nok += 1; shutil.copy('%s/v%d/%s.c' % (d, b[1], f), R + '/build/hand/%s.c' % f)
    print('# %d callers, %d with drafts, %d OK' % (len(callers), sum(1 for f in callers if drafts[f]), nok))

if __name__ == '__main__':
    main()
