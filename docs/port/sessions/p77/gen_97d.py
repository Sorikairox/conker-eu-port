#!/usr/bin/env python3
# P77 setups for func_15097D20 (d*) and func_15097DDC (x*). EU: D_800D20FC = 0x800D251C (records 0x30 at 0x80420000),
# func_15083E0C = 15084274, func_15083E90 = 150842F8, func_15082E44 = 15082E44, func_1505EEF4 = 1505F2A0, D_800D2520 byte (top of word 800D2520).
R=0x80420000; O=0x80430000
base={0x800D251C:R}
for k in range(0,0x30*8,4): base[R+k]=0xAAAAAAAA
base[O+0x13C]=0x00000057
def pk(d): x=dict(base); x.update(d); return ','.join('%08X=%08X'%kv for kv in sorted(x.items()))
n=0
for e in (5,0x1234,0x2FF):
    for r0,r1,r2,r3 in (('FFFFFFFF','0','1','3'),('3',f'{O:X}','1','3'),('3','0','1','4'),('3','0','0','4'),('0',f'{O:X}','1','0'),('2','0','1','0'),('6','0','1','FFFFFFFF')):
        print('d%d ! 0=%X ! %s ! 15084274=%s;%s,150842F8=%s,15082E44=%s ! ! ! ! !'%(n,e,pk({}),r0,r3,r1,r2)); n+=1
n=0
for idv in (0,3,7,9):
    for words,a1 in ((2,0),(2,1),(3,1),(4,0)):
        for cnt in (0,8):
            for ob in (O,0):
                print('x%d ! 0=%X,1=80440000 ! %s ! 1505F2A0=%X ! ! ! ! !'%(n,idv,pk({0x800D2520:cnt<<24,0x800D3C60:words,0x80440000:0x11,0x80440004:a1}),ob)); n+=1
