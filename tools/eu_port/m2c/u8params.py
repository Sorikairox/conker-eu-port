#!/usr/bin/env python3
# usage: u8params.py  (from anywhere; reads ~/conker/conker/asm/nonmatchings)
# Lists asm functions whose prologue re-truncates an argument register
# (`andi $tX, $aN, 0xFF|0xFFFF` then `or $aN, $tX, $zero`): the source had a u8/u16 param N.
# Output lines: func file argN u8|u16
import os,re,glob
R=os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/conker/asm/nonmatchings')
I=re.compile(r'\*/\s+(\w+)\s+(.*)')
for p in sorted(glob.glob(R+'/*/*.s')):
    ins=[]
    for l in open(p):
        m=I.search(l)
        if m: ins.append((m.group(1),[x.strip() for x in m.group(2).split(',')]))
        if len(ins)>=24: break
    found={}
    for i,(op,a) in enumerate(ins):
        if op=='andi' and len(a)==3 and re.fullmatch(r'\$a[0-3]',a[1]) and a[2] in ('0xFF','0xFFFF') \
           and not any(b and b[0]==a[1] and not o.startswith(('s','b')) for o,b in ins[:i]):
            for op2,b in ins[i+1:i+10]:
                if op2=='or' and b==[a[1],a[0],'$zero']:
                    found[int(a[1][2])]='u8' if a[2]=='0xFF' else 'u16'
    for n,t in sorted(found.items()):
        print(os.path.basename(p)[:-2],os.path.basename(os.path.dirname(p)),n,t)
