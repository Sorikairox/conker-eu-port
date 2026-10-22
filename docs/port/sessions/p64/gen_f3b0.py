#!/usr/bin/env python3
"""P64 setups for func_1507F3B0 -> f3b0.txt. D_800D154C = record 1 (0x800CCA1C), ctl = 0x8042D000 (idle state +0x58).
Stubs: func_1507F018 (0x1507F018) returns `seen`, writes picked[] (arg 2) and the count (arg 3) through OUTA."""
import sys
sys.path.insert(0, '../p59'); from pk import build
def setup(name, ctl='', rec='', glob='', ret='', cnt=3):
    spec = '800D196C:0=w:800CCA1C;800C4298:0=b:0;800D1CE0:0=b:0;800BEE10:0=w:1' + glob + ';'
    spec += 'r1:4=b:0,139=b:0,13A=b:0,1CA=b:3,2F8=h:0,31C=w:8042D000' + rec + ';'
    spec += '8042D000:5A=h:200,5C=b:0,5D=b:5,64=b:0,65=b:0,66=h:0,78=b:0' + ctl
    r = '1507F018=1,1507F8A0=10,1515999C=0,15031C4C=0,150803E0=1,150ADF00=7' + ret
    outa = '1507F018=2:0B0C0D0E;0F101112/3:%X' % cnt
    return '%s ! ! %s ! %s ! ! %s' % (name, build(spec), r, outa)
S = [
  ('a',  dict()),                                     # mode 0 -> group 1
  ('a1', dict(ctl=',64=b:1')),                        # mode 1 -> group 0
  ('a2', dict(ctl=',64=b:2,65=b:4')),                 # mode 2, count 4, func_150803E0 -> groups 1 + 3
  ('a3', dict(ctl=',64=b:2,65=b:3')),
  ('a4', dict(ctl=',64=b:2,65=b:4', ret=',150803E0=0')),
  ('a5', dict(cnt=1)), ('a6', dict(cnt=0x10)), ('a7', dict(ret=',1507F018=0')),
  ('f',  dict(rec=',13A=b:1,139=b:20')), ('f2', dict(rec=',13A=b:1,139=b:21')),
  ('g',  dict(glob=';800D1CE0:0=b:2')), ('g2', dict(glob=';800D1CE0:0=b:3')),
  ('h',  dict(ctl=',66=h:1,5A=h:10')), ('h2', dict(ctl=',66=h:1,5A=h:64')), ('h3', dict(ctl=',66=h:1,5A=h:65,64=b:2')),
  ('h4', dict(ctl=',66=h:1,78=b:1')), ('h5', dict(ctl=',66=h:8000,5A=h:FFFF')),
  ('i',  dict(rec=',1CA=b:1')), ('i2', dict(rec=',1CA=b:2')), ('i3', dict(ret=',1515999C=1')),
  ('i4', dict(ctl=',5A=h:10')), ('i5', dict(ctl=',5A=h:F')), ('i6', dict(ctl=',5A=h:8000', ret=',1507F8A0=FFFF')),
  ('j',  dict(rec=',2F8=h:200')), ('j2', dict(ctl=',78=b:9')), ('j3', dict(ctl=',78=b:23')), ('j4', dict(ctl=',78=b:16')),
  ('j5', dict(ret=',15031C4C=800CCA1C')),
  ('k',  dict(glob=';800BEE10:0=w:31')), ('k2', dict(glob=';800BEE10:0=w:31;800D1CE0:0=b:4')),
  ('l',  dict(rec=',4=b:96')),
] + [('m%X' % v, dict(glob=';800BEE10:0=w:%X' % v)) for v in (0xE, 0x10, 0x1B, 0x1C, 0x1E, 0x23, 0x26, 0x28, 0x2F, 0x36, 0x3A, 0x3B)] + [
  ('n',  dict(glob=';800D1CE0:0=b:1')), ('n2', dict(glob=';800D1CE0:0=b:8')), ('n3', dict(glob=';800D1CE0:0=b:9', ctl=',64=b:1')),
]
for n, kw in S: print(setup(n, **kw))
