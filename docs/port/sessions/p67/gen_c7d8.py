#!/usr/bin/env python3
"""P67 setups for func_1505C7D8 -> c7d8.txt. self = 0x80420000, attack table (func_1505C1A4 result) = 0x80430000,
targets = records 0..2 (i = 1..3, count 4 via self+0xF8 & 0x100). EU: D_800D1550 = 0x800D1970, D_800C35EA = 0x800C3A0A,
D_800B30F0. Callees: A184 = 0x1505A504 (out a3 x / sp z / sp y), D34C = 0x1505D6F8, sin 0x150ADC60, cos 0x150ADC6C,
C7C0 = 0x1507C7C0, ACEA0 = 0x150ACEA0, len 0x151443D4, C1E4 = 0x1505C590, C1A4 = 0x1505C550."""
import sys, struct
sys.path.insert(0, '../p59'); from pk import build
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def T(n, extra=''):
    return ';r%d:0=w:1,1CA=b:1,125=b:0,14=f:0,18=f:0,1C=f:8,D2=h:14,D4=h:1E,D6=h:0,D8=h:0,DA=h:0,40=f:0,31C=w:0%s' % (n, extra)
def setup(name, me='', box='', t0='', t1='', t2='', glob='', arg1='7F', ret='', retf='', outw='', outa='', outb=''):
    spec = '800D1970:0=f:1;800C3A0A:0=b:0;800B30F0:0=w:0' + glob + ';'
    spec += '80420000:114=f:100,D0=b:1,14=f:0,18=f:0,1C=f:0,40=f:90,7A=h:0,14C=f:1,150=f:1,F8=w:100,124=b:0,13D=b:0,2F4=w:0,108=b:0,254=b:0' + me + ';'
    spec += '80430000:9=b:0,A=b:8,C=h:A,E=b:5,24=h:0' + box
    spec += T(0, t0) + T(1, ',14=f:1000' + t1) + T(2, ',14=f:1000' + t2)
    r = '1505C550=80430000,1505C590=1' + (',' + ret if ret else '')
    rf = ('3F800000'.join(['150ADC60=', ',150ADC6C=00000000'])) + (',' + retf if retf else '')
    ow = '1505A504=3:00000000/4:%s/5:00000000' % fb(8) + (',' + outw if outw else '')
    return '%s ! 0=80420000,1=%s ! %s ! %s ! %s ! %s ! %s ! %s' % (name, arg1, build(spec), r, rf, outa, ow, outb)
F = fb
S = [
  ('e1', {}), ('e2', dict(me=',114=f:0.5')), ('e3', dict(glob=';800C3A0A:0=b:1')), ('e4', dict(me=',114=f:300')),
  ('s1', {}), ('s1b', dict(t1=',14=f:10')), ('s1c', dict(t0=',18=f:25')), ('s1d', dict(t0=',18=f:-40')), ('s1e', dict(t0=',14=f:39.5')),
  ('s2', dict(arg1='0')), ('s2b', dict(arg1='81')), ('s3', dict(me=',124=b:1')), ('s3b', dict(me=',124=b:1', box=',24=h:1000')),
  ('s4', dict(t0=',D4=h:0')), ('s4b', dict(t0=',1CA=b:0')), ('s4c', dict(t0=',0=w:0')),
  ('s5', dict(t0=',D8=h:3,14=f:30', retf='1505D6F8=' + F(-29), outw='1505D6F8=4:' + F(2))),
  ('s5b', dict(t0=',DA=h:3,1C=f:50', retf='1505D6F8=' + F(1), outw='1505D6F8=4:' + F(-43))),
  ('s6', dict(box=',24=h:2000', ret='150ACEA0=1', retf='151443D4=' + F(50), outw='150ACEA0=11:' + F(10))),
  ('s6b', dict(box=',24=h:2000', ret='150ACEA0=1', retf='151443D4=' + F(5), outw='150ACEA0=11:' + F(10))),
  ('s6c', dict(box=',24=h:2000', ret='150ACEA0=0', retf='151443D4=' + F(50), outw='150ACEA0=11:' + F(10))),
  ('s7', dict(me=',2F4=w:80440000', glob=';80440000:0=f:1,4=f:2,8=f:3', box=',24=h:2000', ret='150ACEA0=1', retf='151443D4=' + F(50), outw='150ACEA0=11:' + F(10))),
  ('s8', dict(me=',13D=b:1', box=',24=h:2000', ret='150ACEA0=1', retf='151443D4=' + F(50), outw='150ACEA0=11:' + F(10))),
  ('s9', dict(t0=',31C=w:80450000', glob=';80450000:114=h:FFC0', box=',24=h:2000', ret='150ACEA0=0')),
  ('p1', dict(glob=';800B30F0:0=w:1', me=',254=b:7')), ('p2', dict(glob=';800B30F0:0=w:1', me=',254=b:0')),
  ('p3', dict(glob=';800B30F0:0=w:1', me=',254=b:7', box=',24=h:4')), ('p4', dict(box=',24=h:800')), ('p5', dict(box=',24=h:804', me=',108=b:2', glob=';800B3748:0=w:1')),
  ('p6', dict(ret='1505C590=0')),
  ('n26', dict(me=',F8=w:0')),
  ('b1', dict(box=',24=h:80,9=b:4,A=b:4,E=b:0', t0=',14=f:3,1C=f:5')),
  ('b2', dict(box=',24=h:80,9=b:4,A=b:4,E=b:2', t0=',14=f:3,1C=f:5')),
  ('b3', dict(box=',24=h:80,9=b:4,A=b:4,E=b:FE', t0=',14=f:30,1C=f:5')),
  ('b4', dict(box=',24=h:80,9=b:1,A=b:1,E=b:0', t0=',14=f:24,1C=f:5')),
  ('b5', dict(box=',24=h:80,9=b:1,A=b:1,E=b:0', t0=',14=f:3,1C=f:26')),
  ('b6', dict(box=',24=h:80,9=b:4,A=b:4,E=b:0,C=h:40', t0=',14=f:3,1C=f:5')),
  ('b7', dict(box=',24=h:80,9=b:4,A=b:4,E=b:0,C=h:FFD8', t0=',14=f:3,1C=f:5,D4=h:5')),
  ('b8', dict(box=',24=h:80,9=b:4,A=b:4', t0=',14=f:3,1C=f:5,D8=h:2', retf='1505D6F8=' + F(40), outw='1505D6F8=4:' + F(1))),
  ('b9', dict(box=',24=h:80,9=b:4,A=b:4', t0=',14=f:3,1C=f:5', retf='150ADC60=' + F(0.5) + ',150ADC6C=' + F(0.8))),
  ('b10', dict(box=',24=h:2080,9=b:4,A=b:4,E=b:0', t0=',14=f:3,1C=f:5', ret='150ACEA0=1', retf='151443D4=' + F(50), outw='150ACEA0=11:' + F(10))),
  ('b11', dict(box=',24=h:80,9=b:4,A=b:4,E=b:0', t0=',14=f:3,1C=f:5', me=',14C=f:0.5,40=f:30,150=f:2')),
]
def P(x=0, y=40, z=8, more=''): return ',14=f:%s,18=f:%s,1C=f:%s%s' % (x, y, z, more)
BX = ',24=h:80,9=b:4,A=b:4,E=b:0'
S += [
  ('e5', dict(me=',114=f:253.5')), ('im', dict(t2=',14=f:0,125=b:1')),
  ('sg1', dict(t0=P(y=-10), t1=P(y=-8), t2=P(y=-12))), ('sg2', dict(t0=P(x=39), t1=P(x=41), t2=P(x=-39.9))),
  ('sg3', dict(t0=P(z=46), t1=P(z=-31), t2=P(x=38))), ('sg4', dict(t0=P(more=',D4=h:1'), t1=P(y=30), t2=P(y=90))),
  ('sg5', dict(me=',18=f:20', t0=P(y=20), t1=P(y=60), t2=P(y=10))), ('sg6', dict(t0=P(x=20, y=-5), t1=P(x=25, y=-5), t2=P(z=40, y=5))),
  ('sg7', dict(t0=P(x=36, more=',D4=h:A'), t1=P(y=-5, more=',D4=h:A'), t2=P(y=-15, more=',D4=h:64'))),
  ('bg1', dict(box=BX, t0=P(x=39, z=0), t1=P(x=-39, z=0), t2=P(x=41, z=0))),
  ('bg2', dict(box=BX, t0=P(z=39, x=0), t1=P(z=-39, x=0), t2=P(z=-41, x=0))),
  ('bg2b', dict(box=BX, t0=P(z=41, x=0), t1=P(z=38, x=0), t2=P(z=-38, x=0))),
  ('bg3', dict(box=BX, t0=P(y=-14), t1=P(y=-16), t2=P(y=94))), ('bg4', dict(box=BX, t0=P(y=96), t1=P(y=-14, z=0), t2=P(x=-41, z=0))),
  ('bg5', dict(box=BX, t0=P(x=50, z=10), t1=P(x=10, z=50), t2=P(x=-20, z=30), retf='150ADC60=' + F(0.6) + ',150ADC6C=' + F(0.8))),
  ('bg6', dict(box=BX + ',E=b:FE', t0=P(x=3, z=0), t1=P(x=-25, z=0), t2=P(x=31, z=0))),
  ('bg7', dict(box=BX + ',E=b:2', t0=P(x=3, z=0), t1=P(x=-25, z=0), t2=P(x=49, z=0))),
  ('bg8', dict(box=BX, t0=P(x=3, z=5, more=',D8=h:2'), retf='1505D6F8=' + F(1), outw='1505D6F8=4:' + F(40))),
  ('bg9', dict(box=BX, me=',18=f:20', t0=P(y=-10), t1=P(y=50), t2=P(y=80))),
  ('sl1', dict(box=',24=h:2000', ret='150ACEA0=1', retf='151443D4=' + F(50), outw='150ACEA0=11:' + F(10), outb='1507C7C0=1:00;40')),
]
open(sys.argv[1] if len(sys.argv) > 1 else 'c7d8.txt', 'w').write('\n'.join(setup(n, **k) for n, k in S) + '\n')
