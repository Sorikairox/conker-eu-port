#!/usr/bin/env python3
# s163: never-touched rows, game files with first func >= 0x15190000 + init, 20-200 insns, size ascending
import glob,os,re
R=os.path.expanduser('~/conker'); W=os.path.expanduser('~/conker-wt/a'); os.chdir(R+'/conker')
logged=set()
for f in (R+'/tools/eu_port/repair_log.tsv',W+'/tools/eu_port/repair_log.tsv'):
    if os.path.exists(f): logged|={l.split('\t')[0] for l in open(f)}
docs=open(R+'/HANDOFF.md').read()+open(W+'/HANDOFF.md').read()
for base in (R,W):
    for p in glob.glob(base+'/docs/sessions/**/*',recursive=True):
        if os.path.isfile(p) and (re.search(r'/s\d+\.md$',p) or re.search(r'/s\d+_targets\.txt$',p)):
            docs+=open(p,errors='ignore').read()
ment=set(re.findall(r'func_(?:eu_)?[0-9A-F]{8}',docs))
rows=[]
for c in sorted(glob.glob('src_eu/game*.c')+glob.glob('src_eu/init*.c')):
    s=open(c).read()
    defs=re.findall(r'^\S[^;=]*\bfunc_([0-9A-F]{8})\s*\([^;]*$',s,re.M)
    asm=re.findall(r'GLOBAL_ASM\("(asm/nonmatchings/[^"]+/(\w+)\.s)"\)',s)
    allf=[int(x,16) for x in defs]+[int(m.group(1),16) for _,n in asm for m in [re.match(r'func_([0-9A-F]{8})$',n)] if m]
    if not allf: continue
    isinit=os.path.basename(c).startswith('init')
    if not isinit and min(allf)<0x15190000: continue
    for p,n in asm:
        if n in logged or n in ment or os.path.basename(c) in ('init_eu_5DA0.c',) or n=='bcopy': continue
        if not os.path.exists(p): continue
        k=sum(1 for l in open(p) if re.match(r'\s*/\*\s*[0-9A-F]+ ',l))
        if 20<=k<=200: rows.append((k,n,os.path.basename(c)))
rows.sort()
for r in rows: print(r[1],r[0],r[2])
