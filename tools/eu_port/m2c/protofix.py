#!/usr/bin/env python3
# usage: protofix.py indir outdir u8list  -- drafts that call a function with known u8/u16
# params (u8params.py list) get a matching prototype: an m2c-emitted declaration of the callee
# is retyped at those positions, or (if neither the draft, its C file nor functions.h declares
# it) a prototype is added: void if every call is a statement, other params typed from the
# caller's own params when passed through (argN), else s32. Writes only changed drafts.
import sys,os,re,glob
ind,outd,lst=sys.argv[1:4]; os.makedirs(outd,exist_ok=True)
C=os.path.expanduser('~/conker/conker')
want={}
for l in open(lst):
    f,src,k,t=l.split(); want.setdefault(f,{})[int(k)]=t
srcof={}
for l in open(os.path.join(os.path.dirname(os.path.abspath(__file__)),'all.txt')).read().split('\n')[1:]:
    if l: x=l.split(); srcof[x[2]]=x[1]
hdr=open(C+'/include/functions.h').read()
def split_args(s):
    out=[];d=0;cur=''
    for ch in s:
        if ch in '([': d+=1
        if ch in ')]': d-=1
        if ch==',' and d==0: out.append(cur.strip()); cur=''; continue
        cur+=ch
    if cur.strip(): out.append(cur.strip())
    return out
def call_args(src,i):
    d=0;j=i
    while True:
        c=src[j]
        if c=='(': d+=1
        elif c==')':
            d-=1
            if d==0: return split_args(src[i+1:j])
        j+=1
n=0
for p in glob.glob(os.path.join(ind,'func_*.c')):
    name=os.path.basename(p)[:-2]; src=open(p).read(); orig=src
    sig=re.search(r'^[^\n;]*\b%s\(([^)]*)\)\s*\{'%name,src,re.M)
    ptypes={}
    if sig:
        for q in split_args(sig.group(1)):
            m=re.fullmatch(r'(.*?)\s*\b(arg\d+)',q)
            if m: ptypes[m.group(2)]=m.group(1)
    cfile=open(C+'/'+srcof[name]).read() if name in srcof else ''
    for g in sorted(set(re.findall(r'\b(func_\w+)\(',src))):
        if g==name or g not in want: continue
        dm=re.search(r'^(\w[\w *]*?\b)%s\(([^)]*)\);'%g,src,re.M)
        if dm:
            ps=split_args(dm.group(2))
            for k,t in want[g].items():
                if k<len(ps): ps[k]=t
            src=src[:dm.start(2)]+', '.join(ps)+src[dm.end(2):]
            continue
        if re.search(r'\b%s\([^;{]*\);'%g,hdr) or re.search(r'^[^\n]*\b%s\([^)]*\);'%g,cfile,re.M) and re.search(r'^\w[\w *]*\b%s\(.*\);'%g,cfile,re.M):
            continue
        calls=[m for m in re.finditer(r'\b%s\('%g,src)]
        args=call_args(src,calls[0].end()-1)
        stmt=all(re.match(r'\s*$',src[src.rfind('\n',0,m.start())+1:m.start()]) for m in calls)
        ts=[]
        for k,a in enumerate(args):
            if k in want[g]: ts.append(want[g][k])
            elif a in ptypes: ts.append(ptypes[a])
            else: ts.append('s32')
        proto='%s %s(%s);\n'%('void' if stmt else 's32',g,', '.join(ts) if ts else 'void')
        src=proto+src
    if src!=orig:
        open(os.path.join(outd,name+'.c'),'w').write(src); n+=1
print(n)
