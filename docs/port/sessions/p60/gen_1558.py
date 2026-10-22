#!/usr/bin/env python3
"""P60 setups for func_15051558 -> 1558.txt (p60/knobs.sh, 6th field = DIFFTEST_OUTA).
rec = record 1 (0x800CCA1C) at (100, 0, 100), old position (90, 0, 95); x / z args = (100, 100); ctl = 0x8042D000.
func_1510FDA0's out-params: OUTA slot 5 = dx, 6 = dz (stack args), 2 = fx, 3 = fz."""
import sys, struct
sys.path.insert(0, '../p59'); from pk import build
F = lambda v: '%08X' % struct.unpack('>I', struct.pack('>f', v))[0]
def setup(name, rec='', ctl='', glob='', ret='', retf='', outw='', ang='4000|C000'):
    args = '0=800CCA1C,1=%s,2=%s,3=%s' % (F(100.0), F(100.0), ang)
    spec = ('r1:14=f:100,18=f:0,1C=f:100,20=f:-5,28=f:0,2C=f:90,30=f:0,34=f:95,3C=f:10,44=f:4,54=f:2,76=h:100,7A=h:200,'
            '83=b:0,84=h:5,89=b:0,8A=b:0,AD=b:0,B8=f:3,C4=f:5,100=b:0,104=b:0,110=b:0,112=h:0,118=f:50,13C=b:0,162=b:0,'
            '164=f:1,168=f:2,16C=f:4,170=f:8,184=w:0,188=w:0,1CA=b:3,274=b:0,31C=w:8042D000' + rec + ';')
    spec += ('8042D000:0=f:10,4=w:0,17=b:0,24=h:0,3E=h:0,44=b:0,4E=b:0,4F=b:0,84=b:0,11A=b:0,120=b:0,19B=b:0' + ctl + ';')
    spec += '800CC69C:0=b:0;800BEA36:0=b:0;800CC670:0=w:5;800BEDC0:0=b:2;800BEDC8:0=f:0.5;800C4298:0=b:1;r0:4=b:8' + glob + ';'
    return '%s ! %s ! %s ! %s ! %s ! %s' % (name, args, build(spec), ret, retf, outw)
PUSH = '1510FDA0=5:3F800000/6:40000000/2:40400000/3:C0000000'   # dx 1, dz 2, fx 3, fz -2
S = [
  ('a',  dict()),                                            # standing, no push
  ('a2', dict(outw=PUSH)),                                   # push > 1: slide starts
  ('a3', dict(outw=PUSH, rec=',184=w:3000')),                # floor kind 3: no slide
  ('a4', dict(rec=',184=w:4000')),                           # floor kind 4: slide
  ('a5', dict(outw=PUSH, rec=',274=b:1')),                   # carried by record 0 (id 8): no slide_start
  ('a6', dict(outw=PUSH, rec=',274=b:1', glob=';r0:4=b:9')),
  ('a7', dict(outw=PUSH, ctl=',84=b:1')),
  ('a8', dict(outw=PUSH, ctl=',4F=b:1')),                    # ctl +0x4F: no floor push
  ('a9', dict(outw=PUSH, rec=',28=f:3,110=b:1')),            # in the air but sliding
  ('b',  dict(glob=';800CC69C:0=b:1', ctl=',17=b:1', rec=',110=b:1')),   # sliding, ctl +0x17
  ('b2', dict(glob=';800CC69C:0=b:1', rec=',110=b:1,162=b:1')),
  ('b3', dict(glob=';800CC69C:0=b:1', rec=',110=b:1,89=b:FE')),
  ('b4', dict(glob=';800CC69C:0=b:1', rec=',110=b:0,162=b:1', ret='1505A9B0=0')),
  ('b5', dict(rec=',162=b:1,110=b:3')),                      # slide ended: speed rebuilt (17.9 after mode 3)
  ('b6', dict(rec=',162=b:1,110=b:3,89=b:FE,3C=f:1')),
  ('b7', dict(rec=',162=b:1,110=b:1,2C=f:99.9,34=f:99.9')),  # slow: speed 22
  ('c',  dict(outw=PUSH, ret='1505A9B0=0')),                 # slide start facing the slope: mode 3 (0x28E)
  ('c2', dict(outw=PUSH, ret='1505A9B0=0', rec=',274=b:1')), # mode 1 / 2 by the stick angle
  ('c3', dict(outw=PUSH, ret='1505A9B0=0', rec=',274=b:1,44=f:9')),
  ('c4', dict(outw=PUSH, ret='1505A9B0=0', rec=',274=b:1,104=b:1')),
  ('c5', dict(outw=PUSH, ret='1505A9B0=0', rec=',13C=b:1')),
  ('c6', dict(outw=PUSH, ret='1505A9B0=0', rec=',89=b:FF')),
  ('c7', dict(outw=PUSH, ret='1505A9B0=0', rec=',83=b:FA')),
  ('c8', dict(outw=PUSH, ret='1505A9B0=0', ctl=',11A=b:1')), ('c9', dict(outw=PUSH, ret='1505A9B0=0', ctl=',11A=b:3')),
  ('c10', dict(outw=PUSH, ret='1505A9B0=0', ctl=',120=b:1')), ('c11', dict(outw=PUSH, ret='1505A9B0=0', ctl=',19B=b:1')),
  ('c12', dict(outw=PUSH, ret='1505A9B0=3000')),             # turn outside the window
  ('c13', dict(outw=PUSH, ret='1505A9B0=0', rec=',274=b:1', ang='7000|9000|5800|A800')),
  ('d',  dict(rec=',110=b:2,84=h:D0,3C=f:1')),               # backward slide stops: turn around
  ('d2', dict(rec=',110=b:2,84=h:101,3C=f:1,104=b:1'), ),
  ('d3', dict(rec=',110=b:2,84=h:28E,3C=f:1,28=f:1')),
  ('d4', dict(rec=',110=b:1,3C=f:11')), ('d5', dict(rec=',110=b:1,3C=f:13')),
  ('d6', dict(rec=',110=b:1,84=h:101', ctl=',11A=b:3')),
  ('e',  dict(retf='15052478=40A00000', ctl=',4=w:1')),       # tilt: func_1505210C returns 5
  ('e2', dict(retf='15052478=40A00000', outw=PUSH)),
  ('e3', dict(retf='15052478=40A00000', outw=PUSH, ctl=',4E=b:11')),
  ('e4', dict(retf='15052478=40A00000', outw=PUSH, rec=',110=b:1')),
  ('f',  dict(outw=PUSH, ctl=',4E=b:2')),                    # ice
  ('f2', dict(outw=PUSH, ctl=',4E=b:2', rec=',28=f:-1')),
  ('f3', dict(outw=PUSH, ctl=',4E=b:2', rec=',28=f:100')),
  ('f4', dict(outw=PUSH, ctl=',4E=b:2', rec=',28=f:-1,89=b:1')),
  ('f5', dict(ctl=',4E=b:2,44=b:3', rec=',C4=f:80,20=f:-40')),  # wobble sound
  ('f6', dict(ctl=',4E=b:2,44=b:3,24=h:1', rec=',C4=f:10')),
  ('f7', dict(ctl=',4E=b:2', rec=',C4=f:80,1CA=b:0')),
  ('f8', dict(ctl=',4E=b:2', rec=',C4=f:80', glob=';800BEA36:0=b:1')),
  ('f9', dict(ctl=',4E=b:2', rec=',C4=f:-80', retf='15052478=42A00000')),
  ('f10', dict(outw='1510FDA0=5:41F00000/6:41F00000', ctl=',4E=b:2', rec=',28=f:3')),   # m > 1000
  ('g',  dict(rec=',AD=b:1')),                               # in water
  ('g2', dict(rec=',AD=b:1,118=f:400')), ('g3', dict(rec=',AD=b:1,B8=f:40')), ('g4', dict(rec=',AD=b:1,118=f:0,3C=f:0')),
]
for n, kw in S: print(setup(n, **kw))
