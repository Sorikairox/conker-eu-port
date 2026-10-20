#!/usr/bin/env python3
# usage: putc.py <func> <draft.c> [--dry]  replace `#pragma GLOBAL_ASM(.../<func>.s)` in conker/src_eu with the draft text (s69).
import sys, os, re, glob
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
f, d = sys.argv[1], sys.argv[2]
root = os.environ.get('CONKER_ROOT', os.path.expanduser('~/conker'))
pat = re.compile(r'#pragma GLOBAL_ASM\("[^"]*/%s\.s"\)\n' % re.escape(f))
for p in glob.glob(root + '/conker/src_eu/**/*.c', recursive=True):
    s = open(p).read()
    if pat.search(s):
        body = open(d).read().rstrip('\n') + '\n'
        if '--dry' not in sys.argv:
            open(p, 'w').write(pat.sub(lambda m: body, s, count=1))
        print(f, '->', os.path.relpath(p, root)); break
else:
    print(f, 'not found'); sys.exit(1)
