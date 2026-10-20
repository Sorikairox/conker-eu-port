#!/usr/bin/env python3
"""ljsweep.py <list> <name> [par=8] > results

Screens many drafts of many functions at once. <list> has "func path" lines (any number per
function). Entry k of each function goes to conker/build/lj_<name>/<k>/<func>.c; the container
then runs m2c/screen.py on every <k> dir (par dirs at a time, one job each, own SCREEN_TMP).
Prints "<result> <func> <path>" per list line (s70 line-join sweep; also usable as a
multi-function tryall). Does not touch conker/build/ta, so it can run next to tryall.
"""
import sys, os, shutil, subprocess, collections
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
R = os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker'))
lst, name = sys.argv[1], sys.argv[2]
par = int(sys.argv[3]) if len(sys.argv) > 3 else 8
d = os.path.join(R, 'conker/build/lj_' + name)
shutil.rmtree(d, ignore_errors=True)
cnt = collections.Counter(); where = []
for l in open(lst):
    if not l.strip(): continue
    f, p = l.split()[:2]
    k = cnt[f]; cnt[f] += 1
    os.makedirs('%s/%d' % (d, k), exist_ok=True)
    src = p if os.path.isabs(p) else os.path.join(R, p)
    shutil.copy(src, '%s/%d/%s.c' % (d, k, f))
    where.append((f, p, k))
shutil.copy(os.path.join(R, 'tools/eu_port/m2c/screen.py'), os.path.join(R, 'conker/build/screen.py'))
env = os.environ.copy(); env['PATH'] = '/Applications/Docker.app/Contents/Resources/bin:' + env['PATH']
cmd = ("ls build/lj_%s | xargs -P %d -I{} sh -c 'SCREEN_TMP=build/lj_%s/{}/tmp python3 build/screen.py build/lj_%s/{} 1 >/dev/null 2>&1'"
       % (name, par, name, name))
subprocess.run(['docker', 'exec', '-w', '/conker/conker', os.environ.get('CONKERDEV', 'conkerdev'), 'bash', '-c', cmd], env=env)
res = {}
for k in range(max(cnt.values()) if cnt else 0):
    sp = '%s/%d/screen.txt' % (d, k)
    if os.path.exists(sp):
        for l in open(sp):
            c = l.split()
            if len(c) >= 2: res[(c[1], k)] = c[0]
for f, p, k in where:
    print(res.get((f, k), 'NORES'), f, p)
