#!/usr/bin/env python3
# cosmetic cleanup of m2c --valid-syntax field accesses in modified files
import re,sys,subprocess,os
os.chdir(os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+''))
files=subprocess.run(['git','diff','--name-only','--','conker/src_eu'],capture_output=True,text=True).stdout.split()
for p in files:
    s=open(p).read(); t=s
    t=re.sub(r'\(\(u8 \*\)\((\w+)\) \+ ',r'((u8 *)\1 + ',t)
    t=re.sub(r'\(\*\((\w+ \*+)\)\(\(u8 \*\)(\w+) \+ 0\)\)',r'(*(\1)\2)',t)
    if t!=s: open(p,'w').write(t)
