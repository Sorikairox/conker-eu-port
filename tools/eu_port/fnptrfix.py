#!/usr/bin/env python3
"""fnptrfix.py <in.c> <out.c>: m2c writes a call through a function-pointer table as
   *(s32 *)((u8 *)&TAB + (i * 4))(args)   (a deref of the call result) -> (*(s32 (**)())(...))(args)   (s56)"""
import sys,re
s=open(sys.argv[1]).read()
out=[];i=0;n=0
pat=re.compile(r'\*\((?:s32|u8 \*|u32|void \*) \*\)\(')
while True:
    m=pat.search(s,i)
    if not m: out.append(s[i:]);break
    j=m.end(); d=1
    while j<len(s) and d:
        if s[j]=='(':d+=1
        elif s[j]==')':d-=1
        j+=1
    # s[m.end()-1:j] is the parenthesised address
    if j<len(s) and s[j]=='(' and not s[m.start()-1:m.start()].isalnum():
        out.append(s[i:m.start()]); out.append('(*(s32 (**)())'+s[m.end()-1:j]+')'); i=j; n+=1
    else:
        out.append(s[i:m.end()]); i=m.end()
open(sys.argv[2],'w').write(''.join(out))
print(n)
