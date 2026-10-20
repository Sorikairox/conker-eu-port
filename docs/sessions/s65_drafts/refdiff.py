#!/usr/bin/env python3
# usage: d.py func draft.c  -> unified opcode+operand diff (ref vs mine), relocs normalised
import sys,subprocess,re,glob,difflib
f,dr=sys.argv[1],sys.argv[2]
s=glob.glob(f'/Users/sorikairo/conker/conker/asm/nonmatchings/*/{f}.s')[0]
ref=[]
for l in open(s):
    m=re.match(r'\s*/\*.*?\*/\s+(\S+)\s*(.*)',l)
    if m:
        op,a=m.group(1),m.group(2)
        a=re.sub(r'%(hi|lo)\([^)]*\)','0',a).replace('$','').replace(' ','')
        a=re.sub(r'0x([0-9A-Fa-f]+)',lambda x:str(int(x.group(1),16)),a)
        if op=='or' and a.endswith(',zero'): op='move'; a=a[:-5]
        a=re.sub(r'^(\w+),zero,(-?\d+)$',r'\1,\2',a) if op=='addiu' and ',zero,' in a else a
        if op=='addiu' and re.match(r'\w+,zero,',a): pass
        ref.append(op+' '+a)
out=subprocess.run(['/Users/sorikairo/conker/tools/eu_port/m2c/mine',f,dr],capture_output=True,text=True).stdout
mine=[x.strip() for x in out.split(';')[1:] if x.strip()]
def norm(x):
    x=re.sub(r'\.L\w+|\b[0-9a-f]+$','L',x) if x.split()[0] in('beqz','bnez','b','bne','beq','beql','bnel','bnezl','beqzl','bltz','bgez','blez','bgtz') else x
    x=re.sub(r'0x([0-9a-f]+)',lambda m:str(int(m.group(1),16)),x)
    return x.replace(' ','',1).replace('(','(').replace('li ','li ') 
R=[norm(x.replace(' ','',0)) for x in ref]; M=[norm(x) for x in mine]
R=[re.sub(r'^addiu(\w+),zero,','li\\1,',r.replace(' ','')) for r in R]
M=[m.replace(" ","").replace("$","") for m in M]
M=[re.sub(r"^(bc1[ft]l?)\w+",r"\1L",m) for m in M]
R=[re.sub(r"^(bc1[ft]l?)\.?\w+",r"\1L",r) for r in R]
R=[r.replace('$','') for r in R]
R=[re.sub(r'^addiu(\w\w),(-?\d+)$',r'li\1,\2',r) for r in R]
n=0
for l in difflib.unified_diff(R,M,'ref','mine',n=1,lineterm=''):
    print(l); n+=1
    if n>int(sys.argv[3] if len(sys.argv)>3 else 80): break
