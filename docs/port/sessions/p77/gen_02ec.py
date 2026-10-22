#!/usr/bin/env python3
# P77 setups for func_150A02EC (game-state query handler). EU addresses. Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
import random
R=random.Random(77)
A=0x80420000
def line(n,cmd,extra,pokes,ret='',retf='',id_=5):
    p={0x800D3C60:2+len(extra)}
    p.update({A:id_,A+4:cmd})
    for i,w in enumerate(extra): p[A+8+4*i]=w&0xFFFFFFFF
    p.update(pokes)
    ps=','.join('%08X=%08X'%(k,v&0xFFFFFFFF) for k,v in sorted(p.items()))
    print('%s ! 0=%X,1=%X,2=%08X ! %s ! %s ! %s ! ! !'%(n,id_&0xFFFFFFFF,cmd,A,ps,ret,retf))
def rnd(): return R.getrandbits(32)
for v in range(4):
    # 0x1A flag bit: D_800D2E4C (EU 800D326C) -> 80430000 bytes
    id_=R.choice([0,7,8,13,37,63])
    line('c1A_%d'%v,0x1A,[],{0x800D326C:0x80430000,0x80430000:rnd(),0x80430004:rnd(),0x80430008:rnd()},id_=id_)
    line('c1B_%d'%v,0x1B,[],{0x80430000:rnd()},ret='1509BB14=80430000',id_=R.choice([5,0x12345,0x8001]))
    line('c1C_%d'%v,0x1C,[],{0x800BEE10:rnd()})
    n=R.randint(0,4)
    tab=[R.choice([10,10,3,0,-1]) for _ in range(4)]
    w=0
    for i,t in enumerate(tab): w|=(t&0xFF)<<(24-8*i)
    line('c1D_%d'%v,0x1D,[],{0x8009012C:n<<24,0x80087610:w,0x800D1CC0:R.getrandbits(16)<<16})
    line('c1E_%d'%v,0x1E,[rnd()&0xFF],{},ret='151E6710=%X'%R.randint(0,9))
    line('c1F_%d'%v,0x1F,[],{0x800BEE18:rnd()})
    line('c20_%d'%v,0x20,[],{0x800BE7FC:rnd()})
    line('c21_%d'%v,0x21,[],{0x800BE800:rnd()})
    line('c23_%d'%v,0x23,[],{0x80090130:rnd()})
    line('c24_%d'%v,0x24,[],{0x800E0FE0:rnd()})
    line('c25_%d'%v,0x25,[],{0x8009015C:rnd()})
    line('c26_%d'%v,0x26,[],{0x8009012C:rnd()})
    line('c27_%d'%v,0x27,[v],{0x800BED50:rnd(),0x800BED54:rnd()})
    line('c28_%d'%v,0x28,[v],{0x800BED38+4*i:rnd() for i in range(6)})
    line('c29_%d'%v,0x29,[],{0x800E0FC4:[0x02000000,0x01000000,0x03000000,0x02FFFFFF][v]})
    line('c2A_%d'%v,0x2A,[rnd()],{0x800EA130:rnd()})
    line('c2B_%d'%v,0x2B,[],{0x80430000:[0x2000<<16,0,0xFFFF0000,0xDFFF1234][v]},ret='1509BB14=%s'%('0' if v==3 else '80430000'))
    line('c2B_null%d'%v,0x2B,[],{},ret='1509BB14=0')
    line('c2C_%d'%v,0x2C,[R.randint(0,3)]*(1 if v<2 else (2 if v==2 else 0)),{},ret='1517F51C=%X'%R.randint(0,1))
    line('c2D_%d'%v,0x2D,[],{0x800D3260:rnd()})
    line('cbad_%d'%v,[0x19,0x2E,0,0x80000000][v],[],{})
# P77: 0x1D with D_800D18A0 = 0 / one bit (the random masks hid the != 10 test)
for v,(n,w,m) in enumerate([(4,0x0A030A00,0),(4,0x030A0AFF,0x0002),(3,0x0A0A0A0A,0),(2,0x03030303,0x8000)]):
    line('c1Dz_%d'%v,0x1D,[],{0x8009012C:n<<24,0x80087610:w,0x800D1CC0:m<<16})
# 0x22 weighted random: count, weights, F0 = 0..1
for v,(ws,f) in enumerate([([1,2,3],0x3F000000),([0,0,5],0x3F7FFFFF),([3,0,0,1],0x3E800000),([],0x3F000000),([0,0,0],0x3F000000),([1,1,1,1,1,1],0),([2,-1,4],0x3F400000),([5,0,5],0x3F000000),([1,2,3],0x3F7FFFFF),([4],0x3F800000),([1,1,1,1],0x3F4CCCCD),([1]*8,0x3F666666)]):
    line('c22_%d'%v,0x22,[len(ws)]+ws,{},retf='150ADF48=%08X'%f)
