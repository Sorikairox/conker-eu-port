#!/usr/bin/env python3
import glob,re,os,sys
os.chdir(os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/conker'))
out=[]
for p in glob.glob('src_eu/**/*.c',recursive=True):
    for m in re.finditer(r'#pragma GLOBAL_ASM\("([^"]+)"\)',open(p).read()):
        s=m.group(1)
        if not os.path.exists(s): continue
        txt=open(s).read()
        n=len(re.findall(r'^\s*/\*\s+[0-9A-F]+ [0-9A-F]+ [0-9A-F]{8} \*/',txt,re.M))
        jt = bool(re.search(r'jr\s+\$(?!ra)',txt))
        fl = txt.count('.s ') + txt.count('.d ')
        out.append((n,p,os.path.basename(s)[:-2],jt,fl))
out.sort()
import collections
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
print(len(out), sum(o[0] for o in out))
for o in out: print(*o)
