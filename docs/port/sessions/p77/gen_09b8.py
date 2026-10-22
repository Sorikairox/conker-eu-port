#!/usr/bin/env python3
# P77 setups for func_150A09B8 (sequence-slot query handler). EU addresses. Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
import random
R=random.Random(78)
A=0x80420000; SL=0x804B0000; OBJ=0x800CC6F0; REC=0x80450000
def rnd(): return R.getrandbits(32)
def line(n,slot,cmd,extra,pokes,ret='',outw=''):
    p={0x800D3C60:2+len(extra),0x800D34B8:SL,A:slot,A+4:cmd}
    for i,w in enumerate(extra): p[A+8+4*i]=w&0xFFFFFFFF
    for s in range(4):                     # slot records: 0x34 bytes of random words
        for o in range(0,0x34,4): p[SL+s*0x34+o]=rnd()
    p.update(pokes)
    ps=','.join('%08X=%08X'%(k,v&0xFFFFFFFF) for k,v in sorted(p.items()))
    print('%s ! 0=%X,1=%X,2=%08X ! %s ! %s ! ! ! %s !'%(n,slot,cmd,A,ps,ret,outw))
def objs(ids,b13f=None,b3b=None,rec78=None):
    p={}
    for i,v in enumerate(ids):
        o=OBJ+i*0x32C; p[o]=v
        p[o+0x13C]=(b13f[i] if b13f else rnd())&0xFF      # byte +0x13F = low byte of word +0x13C
        p[o+0x38]=(b3b[i] if b3b else rnd())&0xFF         # byte +0x3B
        p[o+0x31C]=REC+i*0x100
        p[REC+i*0x100+0x78]=((rec78[i] if rec78 else R.choice([3,1,0]))&0xFF)<<24
    return p
for v in range(4):
    s=R.randint(0,3)
    for cmd in (6,0xD):
        for kind in (0x2000,0x9000,0x1000,0xA000):
            arg=kind|R.randint(0,0xFFF)|(R.getrandbits(16)<<16)
            for r in (0,1,7):
                o='%08X'%(OBJ+R.randint(0,24)*0x32C)
                if cmd==6 and kind==0x2000 and v==0 and r==0: o='0'
                line('c%X_%X_%d_%d'%(cmd,kind>>12,v,r),s,cmd,[arg],{},ret='1505F2A0=%s,150A2EA8=%X,150A3264=%X,150A33C4=%X,150A3484=%X'%(o,r,r,r+3,r+5))
    line('c7_%d'%v,s,7,[],{})
    for cmd in (8,9):
        for fl,b in ((0,0),(1,0),(5,1),(1,2),(1,1)):
            line('c%X_%d_%d_%d'%(cmd,v,fl,b),s,cmd,[],{0x800C3A08:(rnd()&0xFFFF00FF)|(b<<8)},outw='150A3810=1:%X/2:%X/3:%X/4:%X'%(rnd(),rnd(),fl,rnd()))
    line('cA_%d'%v,s,0xA,[],{})
    line('cE_%d'%v,s,0xE,[],{})
    line('c12_%d'%v,s,0x12,[],{SL+s*0x34+0x10:R.choice([0x42C80000,0xC2C80000,0x3F000000,0x47000000])})
    for a in range(5): line('c11_%d_%d'%(v,a),s,0x11,[[0,1,2,3,7][a]],{})
    for r in (0xFFFFFFFF,0,2): line('cF_%d_%X'%(v,r&0xF),s,0xF,[],{},ret='150A3184=%X'%r)
    # 0xB / 0xC: objects with ids, attached test func_150A29C8 sequence
    ids=[R.choice([7,9,0x2007]) for _ in range(25)]
    for cmd in (0xB,0xC):
        for seq in ('0','1;0','1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1;1','1;1;0'):
            line('c%X_%d_%d'%(cmd,v,len(seq)),s,cmd,[R.choice([7,9,0x2007,5])],objs(ids),ret='150A2EA8=%s'%seq)
    # 0x10
    for k in range(8):
        n=R.randint(0,4); words=R.choice([2,3,4])
        rec78=[R.choice([3,0,1]) for _ in range(25)]
        seq=';'.join(R.choice(['0','1','0']) for _ in range(10))
        line('c10_%d_%d'%(v,k),s,0x10,[R.choice([0x2007,0x9003,0x91234005]),R.choice([0,1,5])][:words-2] if words>2 else [],
             {**objs([0]*25,rec78=rec78),0x80090130:(n<<24)|(rnd()&0xFFFFFF)},
             ret='150A3184=%s,150A3264=%s'%(R.choice(['FFFFFFFF','FFFFFFFF','3']),seq))
for c in (0,5,0x13,0x80000006,-1): line('cbad_%X'%(c&0xFFFFFFFF),1,c&0xFFFFFFFF,[],{})
# P77 targeted: negative z in 0xA (sign of the low half), the only matching object at index 24 in 0xB / 0xC
for k,(x,z) in enumerate([(0x0123,0x8001),(0xFFFF,0xFFFE),(0x7FFF,0x8000)]):
    line('cAz_%d'%k,k,0xA,[],{SL+k*0x34:(x<<16)|0x5555,SL+k*0x34+4:(z<<16)|0xAAAA})
for cmd in (0xB,0xC):
    ids=[9]*24+[7]
    line('c%Xlast'%cmd,1,cmd,[7],objs(ids),ret='150A2EA8=0')
    line('c%Xlast2'%cmd,1,cmd,[9],objs([9]*25),ret='150A2EA8='+';'.join(['1']*24+['0']))
