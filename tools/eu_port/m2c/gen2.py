#!/usr/bin/env python3
# usage: [ONLY=funclist] gen2.py outdir min max   -> outdir/v<k>/<func>.c variants, generated in parallel
import sys,re,os,subprocess
from multiprocessing import Pool
S=os.path.dirname(os.path.abspath(__file__))
os.chdir(os.path.expanduser('~/conker/conker'))
od,mn,mx=sys.argv[1],int(sys.argv[2]),int(sys.argv[3])
BAD=('M2C_ERROR','M2C_BITWISE','M2C_STRUCT_COPY','M2C_MEMCPY','M2C_LWL','M2C_FIRST3','M2C_UNALIGNED','M2C_TRAP','M2C_BREAK','M2C_SYNC','GLUE_F64','MULT_HI','MULTU_HI','M2C_CARRY','M2C_OVERFLOW','CLZ(','unksp','saved_reg','(bitwise','/* irregular */','goto *')
def repl_field(s):
    out='';i=0
    while True:
        j=s.find('M2C_FIELD(',i)
        if j<0: return out+s[i:]
        out+=s[i:j]; k=j+len('M2C_FIELD('); depth=1; args=[]; cur=''
        while depth:
            c=s[k]; k+=1
            if c=='(': depth+=1
            elif c==')':
                depth-=1
                if depth==0: break
            if c==',' and depth==1: args.append(cur); cur=''; continue
            cur+=c
        args.append(cur)
        a,t,o=[x.strip() for x in args]
        a=repl_field(a)
        if re.fullmatch(r'\w+',a): a=a
        else: a='('+a+')'
        out+='(*(%s)((u8 *)%s + %s))'%(t,a,o); i=k
def post(c):
    c=repl_field(c)
    c=re.sub(r'\bM2C_UNK8\b','s8',c); c=re.sub(r'\bM2C_UNK16\b','s16',c); c=re.sub(r'\bM2C_UNK64\b','s64',c)
    c=re.sub(r'\bM2C_UNK(32)?\b','s32',c)
    c=c.replace('void *','u8 *')
    c=re.sub(r'\?(?=\d)','s',c)
    c=re.sub(r'(^|[(,]\s*)\?(?=[\s*,)])',lambda m:m.group(1)+'s32',c,flags=re.M)
    c=re.sub(r'^\? ','s32 ',c,flags=re.M)
    c=re.sub(r'^(extern|static) \? ',r'\1 s32 ',c,flags=re.M)
    c=re.sub(r'\s*/\* extern \*/','',c)
    c=re.sub(r'[ \t]+$','',c,flags=re.M)
    return c
def revdecl(c):
    # reverse the order of the local declarations block of the (last) function
    m=re.search(r'\) \{\n((?:    [^\n=]*;\n)+)\n',c)
    if not m: return None
    ls=m.group(1).split('\n')[:-1]
    if len(ls)<2: return None
    return c[:m.start(1)]+'\n'.join(ls[::-1])+'\n'+c[m.end(1):]
sys.path.insert(0,S)
import rodasm
def m2c_inputs(sp):
    # the function .s without a rodata_inject block, plus its .rodata items (rodasm.py) so m2c
    # writes float literals, switch statements and strings
    d=os.path.join(S,'rod'); os.makedirs(d,exist_ok=True)
    f=os.path.basename(sp)[:-2]
    body=open(sp).read()
    if body.startswith('# rodata_inject'):
        body=body.split('# rodata_inject end\n',1)[1]
    t=rodasm.gen(sp)
    # jump-table targets need labels (splat only labels them when it saw the table)
    for tg in set(re.findall(r'\.word \.L([0-9A-F]{8})',t or '')):
        if '.L%s:'%tg not in body:
            body=re.sub(r'(\n)(\s*/\* [0-9A-F]+ %s )'%tg,r'\1  .L%s:\n\2'%tg,body,count=1)
    a=os.path.join(d,f+'.s'); open(a,'w').write(body)
    ins=[a]
    if t:
        b=os.path.join(d,f+'.rod.s'); open(b,'w').write(t); ins.append(b)
    return ins
def m2c(sp,cx,extra):
    r=subprocess.run([S+'/venv/bin/python','tools/mips_to_c/m2c.py','--valid-syntax','--context',cx]+extra+m2c_inputs(sp),capture_output=True,text=True)
    if r.returncode or not r.stdout.strip() or any(b in r.stdout for b in BAD): return None
    c=post(r.stdout)
    return None if 'M2C' in c else c
def ctx(p):
    stem=p.replace('/','_')[:-2]
    cx=S+'/ctx/'+stem+'.c'
    if not os.path.exists(cx):
        r=subprocess.run(['gcc','-E','-P','-Iinclude','-Iinclude/2.0L','-Iinclude/2.0L/PR','-Isrc','-D_LANGUAGE_C','-ffreestanding','-DF3DEX_GBI_2',p],capture_output=True,text=True)
        open(cx,'w').write(''.join(x+'\n' for x in r.stdout.split('\n') if not x.startswith('#pragma')))
    return cx
def fixscale(c):
    ext=dict((m.group(2),m.group(1)) for m in re.finditer(r'^extern (\w+) (\w+);',c,re.M))
    def r(m):
        t=ext.get(m.group(1))
        if not t: return m.group(0)
        return '*(%s *)((u8 *)&%s + (%s))'%(t,m.group(1),m.group(2))
    return re.sub(r'\*\(&(\w+) \+ \(([^()]+ \* (?:0x[0-9A-F]+|\d+))\)\)',r,c)
def addpad(c):
    ms=[x.end() for x in re.finditer(r'\) \{\n',c)]
    if not ms: return None
    i=ms[-1]
    return c[:i]+'    s32 pad;\n'+c[i:]
def work(a):
    f,p,sp=a
    cx=ctx(p); n=0
    base=m2c(sp,cx,[])
    vs={}
    if base:
        base=fixscale(base)
        vs['v0']=base
        u=re.sub(r'\bs8 \*','u8 *',base)
        if u!=base: vs['v1']=u
        r=revdecl(base)
        if r: vs['v3']=r
        pd=addpad(base)
        if pd: vs['v5']=pd
    a2=m2c(sp,cx,['--no-andor'])
    if a2 and a2!=base: vs['v2']=fixscale(a2)
    a4=m2c(sp,cx,['--no-stack-spill'])
    if a4 and a4!=base:
        a4=fixscale(a4); vs['v4']=a4
        pd=addpad(a4)
        if pd: vs['v6']=pd
        r=revdecl(a4)
        if r: vs['v7']=r
    for k,v in vs.items():
        os.makedirs(od+'/'+k,exist_ok=True)
        open('%s/%s/%s.c'%(od,k,f),'w').write(v)
    return len(vs)
def main():
    items=[]
    only=set(x.split()[0] for x in open(os.environ['ONLY'])) if os.environ.get('ONLY') else None
    for l in open(S+'/all.txt').read().split('\n')[1:]:
        if not l: continue
        ins,p,f,jt,fl=l.split(); ins=int(ins)
        if ins>mx or ins<mn or (jt=='True' and not os.environ.get('JT')): continue
        if only is not None and f not in only: continue
        m=re.search(r'#pragma GLOBAL_ASM\("([^"]*/%s\.s)"\)'%f,open(p).read())
        if m: items.append((f,p,m.group(1)))
    os.makedirs(S+'/ctx',exist_ok=True)
    with Pool(8) as pool:
        print(sum(pool.map(work,items,chunksize=4)), len(items))

if __name__=='__main__':
    main()
