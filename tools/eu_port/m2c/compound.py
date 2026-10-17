#!/usr/bin/env python3
# usage: compound.py indir outdir  -- rewrites `X = (T) (X op Y);` / `X = X op Y;` as `X op= Y;`
# in every draft of indir; writes only the drafts that changed into outdir (a new variant set).
import sys,os,re,glob
ind,outd=sys.argv[1],sys.argv[2]; os.makedirs(outd,exist_ok=True)
def strip_outer(s):
    s=s.strip()
    while s.startswith('(') and s.endswith(')'):
        d=0
        for i,c in enumerate(s):
            d+= c=='('; d-= c==')'
            if d==0 and i<len(s)-1: return s
        s=s[1:-1].strip()
    return s
LINE=re.compile(r'^(\s*)(.+?) = (.+);$')
CAST=re.compile(r'^\((?:u8|s8|u16|s16|u32|s32|f32|f64)\) ')
def fix(line):
    m=LINE.match(line)
    if not m: return line
    ind,lhs,rhs=m.groups()
    if '==' in lhs or lhs.count('(')!=lhs.count(')'): return line
    r=CAST.sub('',rhs.strip()); r=strip_outer(r)
    for op in ('+','-','|','&','^','*'):
        for l in (lhs,strip_outer(lhs)):
            p=l+' '+op+' '
            if r.startswith(p):
                rest=r[len(p):]
                if rest.count('(')!=rest.count(')') or not safe(rest,op): continue
                return '%s%s %s= %s;'%(ind,lhs,op,rest)
            p='('+l+') '+op+' '
            if r.startswith(p):
                rest=r[len(p):]
                if rest.count('(')!=rest.count(')') or not safe(rest,op): continue
                return '%s%s %s= %s;'%(ind,lhs,op,rest)
    return line
PREC={'*':10,'/':10,'%':10,'+':9,'-':9,'<<':8,'>>':8,'&':5,'^':4,'|':3}
TOK=re.compile(r' (\*|/|%|\+|-|<<|>>|&|\^|\||<|>|<=|>=|==|!=|&&|\|\||\?|:) ')
def safe(rest,op):
    d=0; top=''
    for c in rest:
        if c=='(': d+=1
        elif c==')': d-=1
        top+= c if d==0 else '_'
    for m in TOK.finditer(top):
        o=m.group(1)
        if o not in PREC: return False
        if PREC[o]>PREC[op]: continue
        if o==op and op in '+*|&^': continue
        return False
    return True
n=0
for f in glob.glob(os.path.join(ind,'func_*.c')):
    src=open(f).read()
    out='\n'.join(fix(l) for l in src.split('\n'))
    if out!=src:
        open(os.path.join(outd,os.path.basename(f)),'w').write(out); n+=1
print(n)
