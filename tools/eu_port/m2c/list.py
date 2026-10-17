#!/usr/bin/env python3
import glob,re,os,sys
os.chdir(os.path.expanduser('~/conker/conker'))
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
print(len(out), sum(o[0] for o in out))
for o in out: print(*o)
