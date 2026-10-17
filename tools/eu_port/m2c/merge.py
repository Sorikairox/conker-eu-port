#!/usr/bin/env python3
# usage: merge.py outdir vdir...  -- for every function with an OK line in a vdir/screen.txt,
# copies the first OK draft into outdir and appends `OK func file` to outdir/screen.txt
# (skips functions already listed there). Then run apply.py on outdir.
import sys,os,shutil
od=sys.argv[1]; os.makedirs(od,exist_ok=True)
sf=os.path.join(od,'screen.txt')
have=set(l.split()[1] for l in open(sf)) if os.path.exists(sf) else set()
n=0
with open(sf,'a') as fo:
    for d in sys.argv[2:]:
        p=os.path.join(d,'screen.txt')
        if not os.path.exists(p): continue
        for l in open(p):
            r,f,src=l.split()
            if r=='OK' and f not in have:
                shutil.copy(os.path.join(d,f+'.c'),os.path.join(od,f+'.c'))
                fo.write('OK %s %s\n'%(f,src)); have.add(f); n+=1
print(n,'added')
