H='''s32 func_15149AC0(f32 *, s32, s32, s32, s32, s32);
extern f32 D_80096A04, D_80096A08, D_80096A0C, D_80096A10, D_80096A14, D_80096A18, D_80096A1C, D_80096A20, D_80096A24, D_80096A28;

s32 func_15013DE8(u8 *arg0) {
    struct {
        f32 u28;
        f32 u2C;
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s16 u50;
        s16 u52;
        s16 u54;
        u8 u56;
        u8 u57;
        u8 u58;
        u8 u59;
        s16 u5A;
        u8 u5C;
        u8 u5D;
        u8 u5E;
        u8 u5F;
        s32 u60;
        u8 u64;
        u8 pad65[3];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
    } sp;

    arg0[0x16] |= 4;
BODY
    func_15149AC0(&sp.u30, 0xA, 1, CALLARG, 0xFF, 1);
    return 1;
}
'''
S={
'50':'    sp.u50 = 0x6231;\n','52':'    sp.u52 = 0x1A4D;\n','56':'    sp.u56 = 0;\n','57':'    sp.u57 = 0;\n','58':'    sp.u58 = 0;\n','59':'    sp.u59 = 0xFF;\n','5A':'    sp.u5A = 0;\n','5D':'    sp.u5D = 0xFF;\n','5E':'    sp.u5E = 0;\n','5F':'    sp.u5F = 0;\n','60':'    sp.u60 = 0;\n','64':'    sp.u64 = 0;\n','6C':'    sp.u6C = D_80096A0C;\n',
'2C':'    sp.u2C = *(s16 *)(arg0 + 6) * D_80096A04;\n','30':'    sp.u30 = *(s16 *)(arg0 + 0);\n','28':'    sp.u28 = *(s16 *)(arg0 + 8) * D_80096A08;\n','34':'    sp.u34 = *(s16 *)(arg0 + 2);\n','38':'    sp.u38 = *(s16 *)(arg0 + 4);\n','54':'    sp.u54 = 0x12C;\n','68':'    sp.u68 = 0.0f;\n','70':'    sp.u70 = D_80096A10;\n','74':'    sp.u74 = D_80096A14;\n',
'3C':'    sp.u3C = D_80096A18 * sp.u2C;\n','44':'    sp.u44 = D_80096A1C * sp.u2C;\n','40':'    sp.u40 = D_80096A20 * sp.u28;\n','48':'    sp.u48 = D_80096A24 * sp.u28;\n','4C':'    sp.u4C = D_80096A28 * sp.u28;\n',
'5C':'    sp.u5C = (func_150ADA20() % 56U) + 0xC8;\n',
}
m2c='50 52 56 57 58 59 5A 5D 5E 5F 60 64 6C 2C 30 28 34 38 54 68 70 74 5C 3C 40 44 48 4C'.split()
m2c2='50 52 56 57 58 59 5A 5D 5E 5F 60 64 6C 2C 30 28 34 38 54 68 70 74 5C 3C 44 40 48 4C'.split()
fo='2C 28 30 34 38 50 52 54 56 57 58 59 5A 5D 5E 5F 60 64 68 6C 70 74 5C 3C 40 44 48 4C'.split()
fo2='28 2C 30 34 38 50 52 54 56 57 58 59 5A 5D 5E 5F 60 64 68 6C 70 74 5C 3C 40 44 48 4C'.split()
CA=['(arg0[0x18] != 0) ? 2 : 1' ,'(*(s32 *)(arg0 + 0x18) != 0) ? 2 : 1','(u8)((*(s32 *)(arg0 + 0x18) != 0) ? 2 : 1)']
i=0
for o in (m2c,m2c2,fo,fo2):
  for ca in CA[1:]:
    open(f'v{i}.c','w').write(H.replace('BODY',''.join(S[k] for k in o)).replace('CALLARG',ca)); i+=1
rest=[k for k in m2c if k not in ('2C','28')]
O2={
'w0':['2C','28']+rest,
'w1':['28','2C']+rest,
'w2':['2C','30','28']+[k for k in rest if k!='30'],
'w3':['2C','28','30','34','38']+[k for k in rest if k not in ('30','34','38')],
'w4':'2C 28 50 52 56 57 58 59 5A 5D 5E 5F 60 64 6C 30 34 38 54 68 70 74 5C 3C 44 40 48 4C'.split(),
'w5':'2C 28 30 34 38 50 52 54 56 57 58 59 5A 5C 5D 5E 5F 60 64 68 6C 70 74'.split(),
}
for k,o in O2.items():
    b=''.join(S[x] for x in o)
    if k=='w5':
        b=b.replace(S['5C'],'').replace('    sp.u74 = D_80096A14;\n','    sp.u74 = D_80096A14;\n'+S['5C']+S['3C']+S['44']+S['40']+S['48']+S['4C'])
    open(k+'.c','w').write(H.replace('BODY',b).replace('CALLARG',CA[1]))
H2=H.replace('''        f32 u28;
        f32 u2C;
''','').replace('    } sp;\n','    } sp;\n    f32 b;\n    f32 c;\n')
S2=dict(S)
S2['2C']='    b = *(s16 *)(arg0 + 6) * D_80096A04;\n'
S2['28']='    c = *(s16 *)(arg0 + 8) * D_80096A08;\n'
for k in ('3C','44'): S2[k]=S[k].replace('sp.u2C','b')
for k in ('40','48','4C'): S2[k]=S[k].replace('sp.u28','c')
O3={
'x0':m2c,'x1':m2c2,
'x2':'50 52 56 57 58 59 5A 5D 5E 5F 60 64 6C 2C 30 28 34 38 54 68 70 74 5C 3C 44 40 48 4C'.split(),
'x3':'2C 28 50 52 56 57 58 59 5A 5D 5E 5F 60 64 6C 30 34 38 54 68 70 74 5C 3C 40 44 48 4C'.split(),
'x4':'50 52 56 57 58 59 5A 5D 5E 5F 60 64 6C 2C 30 28 34 38 54 68 70 74 5C 3C 44 40 48 4C'.split(),
}
for k,o in O3.items():
    for j,ca in enumerate(CA[1:]):
        open(f'{k}{j}.c','w').write(H2.replace('BODY',''.join(S2[x] for x in o)).replace('CALLARG',ca))
import itertools
n=0
for a,b,c in itertools.product((0,1),(0,1),(0,1)):
    o='2C 28 50 52 56 57 58 59 5A 5D 5E 5F 60 64 6C 30 34 38 54 68 70 74 5C 3C 40 44 48 4C'.split()
    if a: o[2],o[3]=o[3],o[2]
    if b:
        o.remove('60'); o.insert(o.index('5E'),'60')
    if c:
        o.remove('44'); o.insert(o.index('40'),'44')
    open(f'y{n}.c','w').write(H2.replace('BODY',''.join(S2[x] for x in o)).replace('CALLARG',CA[2])); n+=1
n=0
for p in itertools.permutations(['44','40','48','4C']):
    o='2C 28 50 52 56 57 58 59 5A 5D 60 5E 5F 64 6C 30 34 38 54 68 70 74 5C 3C'.split()+list(p)
    open(f'z{n:02d}.c','w').write(H2.replace('BODY',''.join(S2[x] for x in o)).replace('CALLARG',CA[2])); n+=1
