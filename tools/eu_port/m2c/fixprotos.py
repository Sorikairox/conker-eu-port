#!/usr/bin/env python3
# usage: fixprotos.py u8list [--apply]
# u8list: lines "func file argN u8|u16" (output of u8params.py). For every one-line prototype
# of func in conker/include/*.h and conker/src_eu/**/*.c, report the type of param N and,
# with --apply, change an int-like type (s32/u32/int/s16/s8/unsigned...) to u8/u16.
# Prints: FIX/OK/ODD path:line func argN old->new
import sys,re,glob,os
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
want={}
for l in open(sys.argv[1]):
    f,_,n,t=l.split(); want.setdefault(f,{})[int(n)]=t
apply='--apply' in sys.argv
INTS={'s32','u32','int','unsigned int','s16','u16','s8','u8','unsigned char','char','short','long','unsigned','signed'}
files=sorted(glob.glob('include/*.h'))+sorted(glob.glob('src_eu/**/*.c',recursive=True))
for path in files:
    lines=open(path,errors='replace').read().split('\n'); ch=False
    for i,l in enumerate(lines):
        for m in re.finditer(r'\b(func_\w+)\(([^()]*)\)\s*;',l):
            f=m.group(1)
            if f not in want: continue
            pre=l[:m.start()]
            if not re.fullmatch(r'\s*(extern\s+|static\s+)*[\w ]+[\s*]+',pre): continue  # not a declaration
            ps=[p.strip() for p in m.group(2).split(',')] if m.group(2).strip() else []
            newps=list(ps); bad=False
            for n,t in want[f].items():
                if n>=len(ps):
                    print('ODD %s:%d %s arg%d (only %d params)'%(path,i+1,f,n,len(ps))); bad=True; continue
                pm=re.fullmatch(r'((?:unsigned |signed )?\w+)(\s*\w*)',ps[n])
                if not pm or not pm.group(2).strip() and pm.group(1) not in INTS and not pm.group(1).startswith('struct'):
                    if not pm or not re.match(r'[A-Za-z_]',ps[n]) or ps[n].startswith(('arg','D_','temp','tmp','var','a','sp')): bad=True; break  # a call, not a declaration
                if not pm:
                    print('ODD %s:%d %s arg%d %r'%(path,i+1,f,n,ps[n])); bad=True; continue
                if pm.group(1)==t:
                    print('OK  %s:%d %s arg%d %s'%(path,i+1,f,n,t)); continue
                if pm.group(1) not in INTS:
                    print('ODD %s:%d %s arg%d %r'%(path,i+1,f,n,ps[n])); bad=True; continue
                print('FIX %s:%d %s arg%d %s->%s'%(path,i+1,f,n,pm.group(1),t))
                newps[n]=t+pm.group(2)
            if newps!=ps and apply:
                lines[i]=l[:m.start(2)]+', '.join(newps)+l[m.end(2):]; ch=True
    if ch: open(path,'w').write('\n'.join(lines))
