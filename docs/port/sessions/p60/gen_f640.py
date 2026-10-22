#!/usr/bin/env python3
"""P60 setups for func_1507F640 -> f640.txt. D_800D154C = record 1 (0x800CCA1C), D_800C3E78 = 0|1, ctl = 0x8042D000.
D_8008FD8C / D_80086F40 / D_8009BC80 are .game_data (pokes ignored): real values in the .data half of the trials."""
import sys
sys.path.insert(0, '../p59'); from pk import build
def setup(name, ctl='', rec='', glob='', ret='1507F834=0'):
    spec = '800D196C:0=w:800CCA1C;800C4298:0=b:0;800BEA36:0=b:0' + glob + ';'
    spec += 'r1:5=b:1,13C=b:0,1CA=b:3,2F8=h:0,31C=w:8042D000' + rec + ';'
    spec += '8042D000:8=h:0,17=b:0,1A=b:0,32=h:0,4E=b:0,59=b:0,5C=b:1,5D=b:2,78=b:1,120=b:0,198=b:0,1B2=b:0' + ctl
    return '%s ! ! %s ! %s !' % (name, build(spec), ret)
S = [
  ('a',  dict()),                                   # ch 1: no idle anim -> idle sets
  ('a2', dict(ret='1507F834=1')),                   # func_1507F834 != 0, ctl +0x198 == 0: func_1507F3B0
  ('a3', dict(ctl=',5C=b:0,5D=b:0,78=b:9')),        # idle set entry 0 -> per-character fallbacks
  ('a4', dict(ctl=',5C=b:0,5D=b:0,78=b:23')),
  ('a5', dict(ctl=',5C=b:0,5D=b:0,78=b:16')),
  ('a6', dict(ctl=',5C=b:0,5D=b:0', rec=',1CA=b:1')),
  ('a7', dict(ctl=',5C=b:0,5D=b:0,1A=b:0', rec=',1CA=b:2')),
  ('a8', dict(ctl=',5C=b:0,5D=b:4')), ('a9', dict(ctl=',5C=b:6,5D=b:3')),   # idle entries with a delay (e[4] = 1 / 2)
  ('b',  dict(ctl=',59=b:3,5A=h:1234')),                      # idle delay counting down
  ('b2', dict(rec=',2F8=h:20')),
  ('b3', dict(ctl=',120=b:1')),
  ('b4', dict(rec=',5=b:4')),
  ('b5', dict(glob=',0=b:1'.replace('0=b:1','0=b:0'), rec=',1CA=b:0')),   # out of health: func_1507CD64
  ('b6', dict(rec=',89=b:FA,8A=b:FF,83=b:5,AA=b:5,7A=h:1234,100=b:3,2F8=h:1F')),
  ('b7', dict(rec=',89=b:F9,8A=b:FE')),
  ('c',  dict(ctl=',17=b:1')),                      # random idle 0x4F / 0x4D
  ('d',  dict(ctl=',78=b:22')), ('d2', dict(ctl=',78=b:2')), ('d3', dict(ctl=',78=b:41')), ('d4', dict(ctl=',78=b:13')),
  ('d5', dict(ctl=',78=b:3B')), ('d6', dict(ctl=',78=b:2E')), ('d7', dict(ctl=',78=b:42')), ('d8', dict(ctl=',78=b:24')),
  ('e',  dict(ctl=',78=b:16,1B2=b:1')), ('e2', dict(ctl=',78=b:15,1B2=b:1')),
  ('e3', dict(ctl=',4E=b:2')), ('e4', dict(ctl=',8=h:1,78=b:38')), ('e5', dict(ctl=',1A=b:1')),
  ('e6', dict(ctl=',32=h:3')), ('e7', dict(ctl=',32=h:1')), ('e8', dict(ctl=',32=h:1,8=h:FF00')),
  ('f',  dict(rec=',13C=b:64')), ('f2', dict(rec=',13C=b:63')),
  ('g',  dict(glob=',0=b:1')), ('g2', dict(glob=',0=b:1', ctl=',78=b:23')), ('g3', dict(glob=',0=b:1', ctl=',78=b:9')),
  ('g4', dict(glob=',0=b:1', ctl=',78=b:16')),
  ('h',  dict(ret='1507F834=1', ctl=',198=b:1,5C=b:0,78=b:3')), ('h2', dict(ret='1507F834=1', ctl=',198=b:1,5C=b:0,78=b:9')),
  ('h3', dict(ret='1507F834=1', ctl=',198=b:1,5C=b:0,78=b:16')), ('h4', dict(ret='1507F834=1', ctl=',198=b:1,5C=b:0,78=b:23')),
  ('h5', dict(ret='1507F834=1', ctl=',198=b:1,5C=b:0,78=b:4')), ('h6', dict(ret='1507F834=1', ctl=',198=b:1,5C=b:1,78=b:3')),
]
for n, kw in S: print(setup(n, **kw))
