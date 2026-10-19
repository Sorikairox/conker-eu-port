#!/usr/bin/env python3
"""vecfix.py <indir> <outdir> [func ...]  m2c drafts declare an in-memory vector as separate scalars `f32 sp38; f32 sp3C; f32 sp40;`
and pass `&sp38`; IDO then drops the stores to sp3C/sp40 as dead (SIZE-n). Rewrite each run of spXX scalars (same type, offsets
4 apart, lowest one's address taken) as one array `T spXX[n]` and every spYY as `spXX[(YY-XX)/4]` (s55)."""
import sys,os,re
ind,outd=sys.argv[1],sys.argv[2]; os.makedirs(outd,exist_ok=True)
names=sys.argv[3:] or [f[:-2] for f in os.listdir(ind) if f.endswith('.c')]
n=0
for f in names:
    s=open(f'{ind}/{f}.c').read()
    decl=re.findall(r'^    (f32|s32|u32|s16|u16|u8|s8) (sp[0-9A-F]+);\n',s,re.M)
    off={nm:int(nm[2:],16) for t,nm in decl}; typ={nm:t for t,nm in decl}
    taken={m for m in re.findall(r'&(sp[0-9A-F]+)\b',s) if m in off}
    changed=False
    for base in sorted(taken,key=lambda x:off[x]):
        if base not in typ: continue
        if typ[base] not in('f32','s32','u32'): continue
        grp=[base]; o=off[base]+4
        while True:
            nx=[nm for nm in off if off[nm]==o and typ.get(nm)==typ[base]]
            if not nx: break
            grp.append(nx[0]); o+=4
        if len(grp)<2: continue
        for g in grp[1:]:
            s=re.sub(r'\b%s\b'%g,'%s[%d]'%(base,(off[g]-off[base])//4),s)
            s=s.replace('    %s %s[%d];\n'%(typ[base],base,(off[g]-off[base])//4),'')
        s=s.replace('    %s %s;\n'%(typ[base],base),'    %s %s[%d];\n'%(typ[base],base,len(grp)))
        # remove the now-renamed declarations of the other elements
        for k,g in enumerate(grp[1:],1):
            s=re.sub(r'^    %s %s\[%d\];\n'%(typ[base],base,k),'',s,flags=re.M)
        s=re.sub(r'&%s\b(?!\[)'%base,'@@ADDR@@',s)
        s=re.sub(r'(?<!\w)%s\b(?!\[)(?!;\n    )'%base,'%s[0]'%base,s)
        s=s.replace('@@ADDR@@',base)
        s=s.replace('%s[0][%d];'%(base,len(grp)),'%s[%d];'%(base,len(grp)))
        changed=True
    if changed:
        open(f'{outd}/{f}.c','w').write(s); n+=1
print('vecfix changed',n)
