#!/usr/bin/env python3
# P77 setups for func_150954E4 (texture loader). EU addresses: D_800D30C0 / D_800D30BC are not moved in EU (0x800D30C0 / 0x800D30BC),
# func_1510D66C = 0x1510D66C. Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
import random
R=random.Random(954)
G=0x80440000; T=0x80420000
i=0
def P(fmt=0,siz=2,flag=0,w=32,h=32,addr=0x80300000,tmem=0,tile=0,frame=0,sfrac=0,cm=0,uls=0,ult=0,age=3,ret=0x80310000):
    global i
    pk={T:addr,T+4:(w<<16)|h,T+8:(fmt<<24)|(siz<<16)|(flag<<8)|R.getrandbits(8),0x800D30C0:0x11111111,0x800D30BC:0x22222222}
    for k in range(0,0x60,4): pk[G+k]=0xDEAD0000|k
    a='0=%X,1=%X,2=%X,3=%X,4=%X,5=%X,6=%X,7=%X,8=%X,9=%X'%(G,T,tmem&0xFFFFFFFF,tile,frame&0xFFFFFFFF,sfrac,cm,uls&0xFFFFFFFF,ult&0xFFFFFFFF,age)
    print('t%d ! %s ! %s ! 1510D66C=%X ! ! ! ! !'%(i,a,','.join('%08X=%08X'%kv for kv in sorted(pk.items())),ret))
    i+=1
for fmt in range(6):
    for siz in range(4):
        P(fmt=fmt,siz=siz)
        P(fmt=fmt,siz=siz,w=R.choice([1,2,3,5,17,64,100]),h=R.choice([1,2,3,4,9,48,256]),flag=1,frame=R.randint(0,5),tmem=R.randint(0,0x3FF),tile=R.randint(0,7),sfrac=R.randint(0,3),cm=R.randint(0,3),uls=R.randint(0,0x500),ult=R.randint(0,0x500))
for addr in (0x00001234,0x0FFFFFFF,0x10000000,0x80000000,0x8FFFFFF0):
    for ret in (0x80310000,0x80000000,0):
        P(addr=addr,ret=ret,flag=1,frame=2,fmt=2,siz=R.randint(0,1))
for w,h in ((128,128),(256,64),(64,63),(4096,1),(3,3),(2,2),(0,0),(1,1),(65535,2)):
    for siz in (0,1,3): P(w=w,h=h,siz=siz,fmt=R.choice([0,2,3,4,5]))
for k in range(12):
    P(fmt=R.choice([0,2,3,4,5]),siz=R.randint(0,3),flag=R.randint(0,1),w=R.randint(1,300),h=R.randint(1,300),frame=R.randint(-2,9),
      tmem=R.choice([0,0x100,0x1FF,0x200,-1]),tile=R.choice([0,6,7,8]),sfrac=R.randint(-4,8),cm=R.randint(0,7),uls=R.randint(-50,0x800),ult=R.randint(-50,0x800),age=R.randint(0,5),addr=R.choice([0x80300000,0x123]))
