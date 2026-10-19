#!/usr/bin/env python3
"""shortpool.py [max=50]  GLOBAL_ASM functions <= max insns not in repair_log.tsv, minus fragments / hand-written asm.
Prints counts to stderr, candidate names (one per line, smallest first) to stdout."""
import sys,os,re,glob,collections
R=os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+''); mx=int(sys.argv[1]) if len(sys.argv)>1 else 50
os.chdir(R+'/conker')
logged={l.split('\t')[0] for l in open(R+'/tools/eu_port/repair_log.tsv')}
idx={}
for p in glob.glob('asm/nonmatchings/**/*.s',recursive=True): idx[os.path.basename(p)[:-2]]=p
cnt=collections.Counter(); out=[]
HW=re.compile(r'\b(mtc0|mfc0|eret|syscall|cache|tlb\w+|break|sync|ll|sc|lld|scd|dmfc\d|dmtc\d|cfc1|ctc1)\b')
for l in open(R+'/tools/eu_port/m2c/all.txt').read().split('\n')[1:]:
    t=l.split()
    if len(t)<4: continue
    n=int(t[0]); f=t[2]
    if n>mx: continue
    cnt['<=%d'%mx]+=1
    if f in logged: cnt['logged']+=1; continue
    s=idx.get(f)
    if not s: cnt['nofile']+=1; continue
    txt=open(s).read()
    ins=re.findall(r'\*/\s+(\w[\w.]*)\s*(.*)',txt)
    ops=[i[0] for i in ins]
    if 'Handwritten' in txt or any(HW.fullmatch(o) for o in ops): cnt['handwritten']+=1; continue
    if not re.search(r'jr\s+\$ra',txt): cnt['frag:no jr ra']+=1; continue
    if re.search(r'jr\s+\$(?!ra)',txt): cnt['jumptable/jr']+=1; continue
    # fragment: a callee-saved/temp/v reg read before any write
    w=set(); frag=False
    for o,a in ins:
        regs=re.findall(r'\$(\w+)',a)
        store=o in('sw','sd','sb','sh','swc1','sdc1','swl','swr','lwc1','ldc1') or o[0] in 'bj' or o in('mtc1','dmtc1')
        if o=='jal' or o=='jalr': w|={'v0','v1','t0','t1','t2','t3','t4','t5','t6','t7','t8','t9'}; continue
        if o in('mtc1','lwc1','ldc1') : srcs=regs[:1] if o=='mtc1' else regs[1:]; dst=None
        elif store: srcs=regs; dst=None
        else: dst=regs[0] if regs else None; srcs=regs[1:]
        if o in('sw','sd') and re.fullmatch(r's[0-7]',regs[0]): srcs=regs[1:]; w.add(regs[0])
        for r in srcs:
            if re.fullmatch(r's[0-7]|t[0-9]|v[01]',r) and r not in w: frag=True
        if dst: w.add(dst)
        if frag: break
    if frag: cnt['frag:reads unset reg']+=1; continue
    out.append((n,f)); cnt['candidates']+=1
for k,v in cnt.items(): print(k,v,file=sys.stderr)
for n,f in sorted(out): print(f)
