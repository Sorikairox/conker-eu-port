import itertools,re
src=open('/Users/sorikairo/conker/docs/sessions/s65_drafts/func_150F8B20_SIZE+1.c').read()
lines=src.split('\n')
s=lines.index('    sp.uB0 = (s32) sp.uC4;'); e=lines.index('    sp.uCC = (*(f32 *)((u8 *)arg1 + 0x1C));')
G={'P':['    sp.uC4 = (*(f32 *)((u8 *)arg1 + 0x14));','    sp.uC8 = (*(f32 *)((u8 *)arg1 + 0x18)) + 50.0f;','    sp.uCC = (*(f32 *)((u8 *)arg1 + 0x1C));'],
 'A':['    sp.uBC = 3;','    sp.uBD = -1;'],'B':['    sp.uBE = (func_150ADA20() % 9U) + 5;'],'C':['    sp.uC0 = 0;'],
 'T':['    sp.uB0 = (s32) sp.uC4;','    sp.uB4 = (s32) sp.uC8;','    sp.uB8 = (s32) sp.uCC;']}
n=0
for p in itertools.permutations('PABCT'):
    if p.index('P')>p.index('T'): continue
    if p.index('A')>p.index('B'): continue
    body=[l for g in p for l in G[g]]
    out='\n'.join(lines[:s]+body+lines[e+1:])
    open(f'v_{"".join(p)}.c','w').write(out); n+=1
print(n)
