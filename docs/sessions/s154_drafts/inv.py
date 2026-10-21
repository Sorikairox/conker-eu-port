import re,glob,os,sys
# inventory commented drafts for GLOBAL_ASM funcs in slice files
out='/Users/sorikairo/conker-wt/a/conker/build_port/s154/d'
rows=[]
for f in sorted(glob.glob('/Users/sorikairo/conker-wt/a/conker/src_eu/*.c')):
    stem=os.path.basename(f)[:-2]
    if not (stem.startswith('game') or stem.startswith('debugger')): continue
    if stem.startswith('init'): continue
    T=open(f).read(); L=T.split('\n')
    addrs=[int(a,16) for a in re.findall(r'func_(15[0-9A-F]{6}|16[0-9A-F]{6})\b(?=\s*\()',T)]
    pr=re.findall(r'GLOBAL_ASM\("[^"]*/(func_[0-9A-F]{8})\.s"\)',T)
    alla=[int(p[5:],16) for p in pr]+[int(m,16) for m in re.findall(r"^[a-zA-Z].*\bfunc_([0-9A-F]{8})\([^;]*\)\s*\{\s*$",T,re.M)]
    if not alla: continue
    first=min(alla)
    if not stem.startswith('debugger') and not (0x15130000<=first<0x15190000): continue
    for fn in pr:
        # commented // block containing 'fn(' as a definition
        idx=[i for i,l in enumerate(L) if l.lstrip().startswith('//') and re.search(r'\b%s\s*\('%fn,l) and re.search(r'^\s*//\s*\S.*\b%s\s*\(.*\)\s*\{?\s*$'%fn,l) and 'NON-MATCHING' not in l and 'GLOBAL_ASM' not in l and not l.rstrip().endswith(';')]
        kind=None;b=[]
        if idx:
            s=idx[0]; kind='//'
            for l in L[s:]:
                if not l.lstrip().startswith('//'): break
                l=l.lstrip(); b.append(l[3:] if l.startswith('// ') else l[2:])
        else:
            # #if 0 or /* */ block
            for i,l in enumerate(L):
                if re.search(r'\b%s\s*\([^;]*$'%fn,l) and not l.startswith('#pragma'):
                    # look back for #if 0 or /* opener
                    j=i
                    while j>0 and not L[j].startswith('#if 0') and '/*' not in L[j] and L[j].strip()!='' : j-=1
                    if L[j].startswith('#if 0'):
                        kind='#if0'; k=j+1
                        while k<len(L) and not L[k].startswith('#endif'): b.append(L[k]); k+=1
                    elif '/*' in L[j] and '*/' not in L[j]:
                        kind='/**/'; k=j+1
                        while k<len(L) and '*/' not in L[k]: b.append(L[k]); k+=1
                    if kind: break
        if kind:
            open(f'{out}/{fn}.c','w').write('\n'.join(b)+'\n')
        rows.append((fn,stem,kind or '-',len(b)))
for r in rows:
    if r[2]!='-': print(*r)
print('total asm',len(rows),'with drafts',sum(1 for r in rows if r[2]!='-'),file=sys.stderr)
