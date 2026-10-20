#!/usr/bin/env python3
# usage: rep.py func  (C code on stdin) ; replaces GLOBAL_ASM pragma or previous C body marked by markers
import sys,glob,re,os
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
os.chdir(os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/conker'))
func=sys.argv[1]
code=sys.stdin.read().strip('\n')
for p in glob.glob('src_eu/**/*.c',recursive=True):
    s=open(p).read()
    m=re.search(r'#pragma GLOBAL_ASM\("asm/nonmatchings/[^"]*/%s\.s"\)'%func,s)
    if m:
        s=s[:m.start()]+'//BEGIN '+func+'\n'+code+'\n//END '+func+s[m.end():]
        open(p,'w').write(s); print(p); break
    m=re.search(r'//BEGIN %s\n.*?//END %s'%(func,func),s,re.S)
    if m:
        s=s[:m.start()]+'//BEGIN '+func+'\n'+code+'\n//END '+func+s[m.end():]
        open(p,'w').write(s); print(p); break
else:
    print('not found'); sys.exit(1)
