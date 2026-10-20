import glob,re,os,collections
os.chdir(os.path.expanduser('~/conker'))
PRAG=re.compile(r'#pragma GLOBAL_ASM\("([^"]*)/(\w+)\.s"\)')
f2s={}
for p in glob.glob('conker/src_eu/**/*.c',recursive=True):
    b=os.path.basename(p)
    if not b.startswith('game'): continue
    m=re.search(r'_([0-9A-Fa-f]+)\.c$',b)
    if not m or int(m.group(1),16)>=0x130000: continue
    for mm in PRAG.finditer(open(p).read()): f2s[mm.group(2)]=('conker/'+mm.group(1)+'/'+mm.group(2)+'.s',p)
have=collections.Counter()
src={}
for f in f2s:
    s=[]
    for q in ('tools/decomp-permuter/repair/%s.c'%f,'tools/decomp-permuter/repair/fresh/%s.c'%f,'tools/decomp-permuter/nm/%s/best.c'%f):
        if os.path.exists(q): s.append(q)
    src[f]=s
allp=glob.glob('docs/sessions/s*_drafts/**/*.c',recursive=True)+glob.glob('conker/build_port/**/*.c',recursive=True)+glob.glob('tools/decomp-permuter/drafts/*.c')
for p in allp:
    for f in set(re.findall(r'func_[0-9A-Fa-f]{8}',p)):
        if f in src: src[f].append(p)
log=set(l.split('\t')[0] for l in open('tools/eu_port/repair_log.tsv'))
rows=[]
for f,(s,p) in f2s.items():
    if not os.path.exists(s): continue
    t=open(s).read()
    n=len(re.findall(r'^\s*/\*\s+[0-9A-F]+ [0-9A-F]+ [0-9A-F]{8} \*/',t,re.M))
    rows.append((n,f,len(src[f]),f in log,bool(re.search(r"jr\s+\$ra",t)), bool(re.search(r'jr\s+\$(?!ra)',t)),p))
rows.sort()
nd=[r for r in rows if r[2]==0]
print('slice asm',len(rows),'with draft',len(rows)-len(nd),'nodraft',len(nd),'nodraft logged',sum(r[3] for r in nd),'no jr ra',sum(not r[4] for r in nd), 'jt',sum(r[5] for r in nd))
import sys
with open('conker/build_port/s73/nodraft.tsv','w') as o:
    for r in nd: o.write('\t'.join(map(str,r))+'\n')
h=collections.Counter(min(r[0]//50*50,400) for r in nd); print(sorted(h.items()))
