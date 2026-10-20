#!/usr/bin/env python3
"""opcmp.py obj.o asmdir refname=eufunc ... : opcode-sequence compare of a compiled reference object vs splat asm."""
import sys, subprocess, re, os, difflib
obj, asmdir = sys.argv[1], sys.argv[2]
dis = subprocess.run(['docker','exec','-w','/conker','conkerdev','mips-linux-gnu-objdump','-d','--no-show-raw-insn','-M','reg-names=numeric',obj],capture_output=True,text=True).stdout
funcs={}; cur=None
for l in dis.split('\n'):
    m=re.match(r'^[0-9a-f]+ <(\w+)>:',l)
    if m: cur=m.group(1); funcs[cur]=[]; continue
    m=re.match(r'^\s+[0-9a-f]+:\s+(\S+)',l)
    if m and cur: funcs[cur].append(m.group(1))
for pair in sys.argv[3:]:
    r,e=pair.split('=')
    a=[]
    for l in open(os.path.join(asmdir,e+'.s')):
        m=re.match(r'\s*/\* \w+ \w+ \w+ \*/\s+(\S+)',l)
        if m: a.append(m.group(1))
    mine=funcs.get(r,[])
    if len(sys.argv)>3 and os.environ.get("OFF"): o=int(os.environ["OFF"]); mine=mine[o:o+len(a)]
    elif len(mine)>len(a): mine=mine[:len(a)]
    while mine and mine[-1]=='nop' and len(mine)>len(a): mine.pop()
    while a and a[-1]=='nop' and len(a)>len(mine): a.pop()
    sm=difflib.SequenceMatcher(None,mine,a,autojunk=False)
    print(f'{r}={e}: mine {len(mine)} ref {len(a)} ratio {sm.ratio():.3f} eq {mine==a}')
