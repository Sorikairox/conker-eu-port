#!/usr/bin/env python3
# usage: rep.py func  (C code on stdin) ; replaces GLOBAL_ASM pragma or previous C body marked by markers
import sys,glob,re,os
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
