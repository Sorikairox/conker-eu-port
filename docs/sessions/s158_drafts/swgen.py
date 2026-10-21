#!/usr/bin/env python3
# swgen.py func 'proto {' 'case-body-template' 'default-body' > draft.c
# switch (arg0[4]) style jump-table functions: finds the jtbls (runs of label words in conker.eu.bin),
# groups case values by label, body template gets {K} = first `addiu $X, $zero, K` (or 0 when the block stores $zero) and {S} = first %hi(sym).
import re,struct,sys,glob
func,proto,tmpl,dflt=sys.argv[1:5]
R='/Users/sorikairo/conker-wt/a/conker/'
asm=open(glob.glob(R+'asm/nonmatchings/*/%s.s'%func)[0]).read()
rom=open(R+'conker.eu.bin','rb').read()
addrs=[int(a,16) for a in re.findall(r'/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/',asm)]
lo,hi=min(addrs),max(addrs)
# jtbl refs: (offset subtract, length) from 'addiu tX, v0, -K ; sltiu at, tX, N' and 'sltiu at, v0, N'
segs=[]
m=re.search(r'addiu\s+\$t\d, \$v0, -(0x[0-9A-F]+)\s.*?sltiu\s+\$at, \$t\d, (0x[0-9A-F]+)',asm,re.S); segs.append((int(m.group(1),16),int(m.group(2),16)))
m=re.search(r'\.L[0-9A-F]+:\n.*?sltiu\s+\$at, \$v0, (0x[0-9A-F]+)',asm,re.S); segs.append((0,int(m.group(1),16)))
names=re.findall(r'%lo\((jtbl_\w+)\)',asm)
tables=[]
SW=sys.argv[5] if len(sys.argv)>5 else 'arg0[4]'
def va(nm): return int(re.search(r'jtbl_([0-9A-F]{8})',nm).group(1),16)
for (off,n),nm in zip(segs,names):
    if tables:
        tables.append((off,n,tables[0][2]+va(nm)-va(names[0]))); continue
    found=None
    for p in range(0,len(rom)-4*n,4):
        w=struct.unpack_from('>I',rom,p)[0]
        if lo<=w<=hi and all(lo<=x<=hi for x in struct.unpack_from('>%dI'%n,rom,p)) and (p<4 or not lo<=struct.unpack_from('>I',rom,p-4)[0]<=hi or True):
            # verify label words point at block starts
            found=p; break
    tables.append((off,n,found))
# label blocks
blocks={}
cur=None
for line in asm.split('\n'):
    mm=re.match(r'\s*(?:glabel\s+)?\.L([0-9A-F]{8})(?:_\w+)?:?\s*$',line)
    if mm: cur=int(mm.group(1),16); blocks[cur]=[]; continue
    if cur is not None: blocks[cur].append(line)
# unlabeled jr-blocks: treat any word address as a block start using the instruction address
ins={}
for line in asm.split('\n'):
    mm=re.match(r'\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s*(.*)',line)
    if mm: ins[int(mm.group(1),16)]=mm.group(2)
cases={}
default=None
for off,n,p in tables:
    ws=struct.unpack_from('>%dI'%n,rom,p)
    for k,w in enumerate(ws): cases.setdefault(w,[]).append(k+off)
# default label = target of the first beqz
dl=int(re.search(r'beqz\s+\$at, \.L([0-9A-F]{8})',asm).group(1),16)
out=[proto,'    switch (%s) {'%SW]
for l in sorted(cases):
    if l==dl: continue
    seq=[]
    for a in sorted(ins):
        if a<l: continue
        seq.append(ins[a])
        if len(seq)>=2 and re.match(r'(jr|b)\s',seq[-2]): break
    txt=' ; '.join(seq)
    txt=re.sub(r'or\s+(\$\w+), \$zero, \$zero',r'addiu \1, $zero, 0',txt)
    k=re.search(r'addiu\s+\$\w+, \$zero, (-?0x[0-9A-F]+|-?\d+)',txt)
    K=k.group(1) if k else '0'
    s=re.search(r'%hi\((\w+)\)',txt); S=s.group(1) if s else ''
    for c in cases[l]: out.append('    case 0x%X:'%c)
    out.append(tmpl.replace('{K}',K).replace('{S}',S))
out+=['    default:',dflt,'    }','}']
print('\n'.join(out))
print('// tables',[(o,n,hex(p) if p else None) for o,n,p in tables],file=sys.stderr)
