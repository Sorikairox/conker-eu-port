import re,sys
src=open(sys.argv[1]).read()
body=src[src.index('{',src.index('func_15156E68('))+1:]
lines=[l.strip() for l in body.split('\n') if '=' in l or 'func_' in l]
fields={}  # off -> (type,size)
stmts=[]
TS={'s16':2,'u16':2,'s32':4,'f32':4,'u8':1,'s8':1}
for l in lines:
    m=re.match(r'sp([0-9A-F]+) = \(\*\((\w+) \*\)\(\(u8 \*\)arg0 \+ (0x[0-9A-F]+|\d+)\)\);',l)
    if m:
        off=int(m.group(1),16); t=m.group(2); a=int(m.group(3),0)
        fields[off]=(t,TS[t]); stmts.append((off,'    %s.u%X = *(%s *)(arg0 + 0x%X);'%('B' if off>=0x98 else 'sp',off,t,a))); continue
    m=re.match(r'\(\*\(s32 \*\)\(\(u8 \*\)\(&sp([0-9A-F]+)\) \+ 0\)\) = \(s32\) \(\*\(s32 \*\)\(\(u8 \*\)arg0 \+ (0x[0-9A-F]+|\d+)\)\);',l)
    if m:
        off=int(m.group(1),16); a=int(m.group(2),0)
        # size: 12 (V3) unless next stmt pattern shows only +4
        fields[off]=('V3',12); stmts.append((off,'    %s.u%X = *(V3_6E68 *)(arg0 + 0x%X);'%('B' if off>=0x98 else 'sp',off,a))); continue
    m=re.match(r'sp([0-9A-F]+) = (0\.0f);',l)
    if m:
        off=int(m.group(1),16); fields[off]=('f32',4); stmts.append((off,'    sp.u%X = 0.0f;'%off)); continue
    if l.startswith('func_15153F24'): stmts.append((0,'    func_15153F24(&B, arg1);')); continue
    if l.startswith('func_151308E4'): stmts.append((0,'    func_151308E4(&sp, arg0[0x88], 0, arg1, 0);')); continue
    if '(&sp' in l and '+ 4)' in l or '+ 8)' in l: 
        m=re.match(r'\(\*\(s32 \*\)\(\(u8 \*\)\(&sp([0-9A-F]+)\) \+ 4\)\)',l)
        continue
    print('//??',l,file=sys.stderr)
# 8-byte copy at 0x50 (only +0,+4): fix
def struct(lo,hi,name):
    out=['    struct {']; o=lo
    for off in sorted(k for k in fields if lo<=k<hi):
        if off>o: out.append('        u8 pad%X[0x%X];'%(o,off-o))
        t,sz=fields[off]
        if t=='V3' and off==0x50: t,sz='V2_6E68',8
        out.append('        %s u%X;'%(t if t!='V3' else 'V3_6E68',off)); o=off+sz
    if o<hi: out.append('        u8 pad%X[0x%X];'%(o,hi-o))
    out.append('    } %s;'%name); return '\n'.join(out)
hdr='''s32 func_151308E4(void *, s32, s32, u8, s32);
typedef struct { f32 x, y, z; } V3_6E68;
typedef struct { s32 a, b; } V2_6E68;
void func_15156E68(u8 *arg0, u8 arg1) {
'''
txt=hdr+struct(0x98,0xE0,'B')+'\n'+struct(0x28,0x98,'sp')+'\n\n'+'\n'.join(s for o,s in stmts).replace('*(V3_6E68 *)(arg0 + 0x6C)','*(V2_6E68 *)(arg0 + 0x6C)')+'\n}\n'
txt=txt.replace('void func_15153F24','void func_15153F24')
open(sys.argv[2],'w').write(txt)
