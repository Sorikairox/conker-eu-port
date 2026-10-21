#!/usr/bin/env python3
# s149: untried hi-slice (first func >= 0x15190000) asm functions 30-250 insns
import glob,os,re,subprocess
R=os.path.expanduser('~/conker'); os.chdir(R+'/conker')
logged={l.split('\t')[0] for l in open(R+'/tools/eu_port/repair_log.tsv')}
docs=''
for p in glob.glob(R+'/docs/sessions/**/*',recursive=True):
    if os.path.isfile(p) and not p.endswith('.c'):
        try: docs+=open(p,errors='ignore').read()
        except: pass
docs+=open(R+'/HANDOFF.md').read()
wt=subprocess.run("git -C /Users/sorikairo/conker-wt/a log eu..eu-wt-a --name-only --format=; git -C /Users/sorikairo/conker-wt/a status --short",shell=True,capture_output=True,text=True).stdout
skip={'func_151037D4','_Ldtob'}
rows=[]
for c in sorted(glob.glob('src_eu/game*.c')):
    s=open(c).read()
    names=re.findall(r'func_(1[0-9A-F]{7})',s)
    defs=re.findall(r'^\S[^;=]*\bfunc_([0-9A-F]{8})\s*\([^;]*$',s,re.M)
    asm=re.findall(r'GLOBAL_ASM\("(asm/nonmatchings/[^"]+/(\w+)\.s)"\)',s)
    allf=[int(x,16) for x in defs]+[int(m.group(1),16) for _,n in asm for m in [re.match(r'func_([0-9A-F]{8})$',n)] if m]
    if not allf or min(allf)<0x15190000: continue
    if os.path.basename(c) in wt: continue
    nc=len(set(defs))
    for p,n in asm:
        if n in skip or n in logged or n in docs: continue
        k=sum(1 for l in open(p) if re.match(r'\s*/\*\s*[0-9A-F]+ ',l))
        if 30<=k<=250: rows.append((nc,k,n,os.path.basename(c)))
rows.sort(key=lambda r:(-(r[0]>=5),r[3],r[1]))
for r in rows: print(r[2],r[1],r[3],'C=%d'%r[0])
