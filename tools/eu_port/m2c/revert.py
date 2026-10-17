#!/usr/bin/env python3
# usage: revert.py func  -> put back GLOBAL_ASM
import sys,glob,re,os
os.chdir(os.path.expanduser('~/conker/conker'))
func=sys.argv[1]
for p in glob.glob('src_eu/**/*.c',recursive=True):
    s=open(p).read()
    m=re.search(r'//BEGIN %s\n.*?//END %s'%(func,func),s,re.S)
    if m:
        d=glob.glob('asm/nonmatchings/*/%s.s'%func)[0]
        s=s[:m.start()]+'#pragma GLOBAL_ASM("%s")'%d+s[m.end():]
        open(p,'w').write(s); print(p); break
