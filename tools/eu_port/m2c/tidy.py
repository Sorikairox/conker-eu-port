#!/usr/bin/env python3
# cosmetic cleanup of m2c --valid-syntax field accesses in modified files
import re,sys,subprocess,os
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
os.chdir(os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+''))
files=subprocess.run(['git','diff','--name-only','--','conker/src_eu'],capture_output=True,text=True).stdout.split()
for p in files:
    s=open(p).read(); t=s
    t=re.sub(r'\(\(u8 \*\)\((\w+)\) \+ ',r'((u8 *)\1 + ',t)
    t=re.sub(r'\(\*\((\w+ \*+)\)\(\(u8 \*\)(\w+) \+ 0\)\)',r'(*(\1)\2)',t)
    if t!=s: open(p,'w').write(t)
