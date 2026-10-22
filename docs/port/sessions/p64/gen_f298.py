#!/usr/bin/env python3
"""P64 setups for func_1505F298 -> f298.txt. rec = record 0 (0x800CC6F0), ctl = 0x8042D000, pad = 0x80430000
(+0 buttons, +3 stick y). D_800CC288 (pressed) = 0x800CC6A8, D_800CC69C, D_800BE616 = 0x800BEA36, D_800BE9A0 = 0x800BEDC0,
D_800BE9F0 = 0x800BEE10. Record 1 (0x800CCA1C) is the ridden record (id at +4)."""
import sys
sys.path.insert(0, '../p59'); from pk import build
def setup(name, rec='', ctl='', pad='', glob='', ret='1506E46C=1'):
    spec = 'r1:4=b:0;800CC6A8:0=w:0;800CC69C:0=b:0;800BEA36:0=b:0;800BEDC0:0=b:1;800BEE10:0=w:1' + glob + ';'
    spec += 'r0:4=b:0,104=b:0,1CA=b:3,28=f:100,20=f:0,24=f:4,110=b:0,AD=b:0,84=h:0,118=f:-10000,18=f:0,1C=f:5,3C=f:0,44=f:0,4C=f:1,C0=f:10,137=b:0,65=b:0,13C=b:0,8A=b:0,89=b:0,184=w:0,81=b:0,100=b:FF,180=f:0,31C=w:8042D000' + rec + ';'
    spec += '8042D000:8=h:0,17=b:0,1A=b:0,21=b:0,22=b:0,30=b:0,31=b:0,36=b:0,46=h:0,4C=h:1234,4E=b:0,4F=b:0,53=b:0,54=b:0,55=b:0,68=h:0,6B=b:0,78=b:0,7B=b:0,84=b:0,95=b:0,97=b:1,98=b:0,11A=b:0' + ctl + ';'
    spec += '80430000:0=h:0,3=b:0' + pad
    return '%s ! 0=800CC6F0,1=80430000 ! %s ! %s ! ! !' % (name, build(spec), ret)
A = ';800CC6A8:0=w:8000'
S = [
  ('s1', dict(rec=',104=b:1')), ('s2', dict(rec=',1CA=b:0')), ('s3', dict(ctl=',46=h:1')), ('s4', dict(ctl=',36=b:64')), ('s5', dict(ctl=',6B=b:1')),
  ('w1', dict(rec=',AD=b:1,118=f:100,18=f:50', glob=A)), ('w1b', dict(rec=',AD=b:1,118=f:100,18=f:50', glob=A + ';800BEE10:0=w:29', ctl=',8=h:1')),
  ('w1c', dict(rec=',AD=b:1,118=f:100,18=f:50', glob=A, ctl=',68=h:9000,7B=b:7')), ('w1e', dict(rec=',AD=b:1,118=f:100,18=f:20', glob=A)), ('w1d', dict(rec=',AD=b:1,118=f:100,18=f:0', glob=A)),
  ('w2', dict(rec=',AD=b:1,118=f:100,18=f:50', ctl=',22=b:5')), ('w3', dict(rec=',AD=b:1,118=f:100,18=f:0', ctl=',22=b:5')),
  ('w2b', dict(rec=',AD=b:1,118=f:100,18=f:50,3C=f:3', ctl=',21=b:1')), ('w2c', dict(rec=',AD=b:1,118=f:100,18=f:50', pad=',0=h:4000', glob=';800CC6A8:0=w:4000')),
  ('w2d', dict(rec=',AD=b:1,118=f:100,18=f:50', ctl=',22=b:50', glob=';800CC6A8:0=w:4000')),
  ('w4', dict(rec=',AD=b:1,118=f:100,18=f:50')), ('w5', dict(rec=',AD=b:1,118=f:100,18=f:0,C0=f:0.1')),
  ('w6', dict(rec=',AD=b:2,118=f:100,18=f:0')), ('w6b', dict(rec=',AD=b:2,118=f:100,18=f:50')), ('w7', dict(rec=',AD=b:1,13C=b:1', ctl=',11A=b:1')), ('w8', dict(rec=',AD=b:1', ctl=',78=b:27')),
  ('w9', dict(rec=',AD=b:1', ctl=',78=b:5')), ('w10', dict(rec=',AD=b:1,84=h:262')), ('w11', dict(rec=',AD=b:1', ctl=',95=b:1')),
  ('h1', dict(rec=',137=b:1', pad=',3=b:40')), ('h2', dict(rec=',137=b:1', pad=',3=b:C0')), ('h3', dict(rec=',137=b:1', glob=A)),
  ('h4', dict(rec=',137=b:1', ctl=',53=b:1', pad=',3=b:40')), ('h5', dict(rec=',137=b:1', ctl=',84=b:1', pad=',3=b:40')), ('h6', dict(rec=',137=b:1', pad=',3=b:33')),
  ('j1', dict(rec=',28=f:0', glob=A)), ('j2', dict(rec=',28=f:0,3C=f:10', glob=A)), ('j3', dict(rec=',28=f:0,3C=f:10', ctl=',78=b:21', glob=A)),
  ('j4', dict(rec=',28=f:0', ctl=',17=b:1', glob=A)), ('j5', dict(rec=',28=f:0', ctl=',8=h:1', glob=A)), ('j6', dict(rec=',28=f:0', ctl=',1A=b:1', glob=A)),
  ('j7', dict(rec=',28=f:0', pad=',0=h:2000', glob=A)), ('j7b', dict(rec=',28=f:0,20=f:10', pad=',0=h:2000', glob=A + ';800CC69C:0=b:1')),
  ('j7c', dict(rec=',28=f:0,110=b:1', pad=',0=h:2000', glob=A)), ('j7d', dict(rec=',28=f:0', pad=',0=h:2000', ctl=',7B=b:8', glob=A)),
  ('j8', dict(rec=',28=f:0', glob=A + ';800CC69C:0=b:1')), ('j9', dict(rec=',28=f:0', ctl=',4E=b:2', glob=A)), ('j9b', dict(rec=',28=f:200', ctl=',4E=b:2', glob=A)),
  ('j9c', dict(rec=',28=f:0', ctl=',4E=b:2', glob=A, ret='1506E46C=0')),
  ('j10', dict(rec=',28=f:0,184=w:2C', glob=A)), ('j11', dict(rec=',28=f:0,184=w:13', glob=A)), ('j12', dict(rec=',28=f:0', ctl=',4E=b:1', glob=A)),
  ('j13', dict(rec=',28=f:0,89=b:5', glob=A)), ('j14', dict(rec=',28=f:0', ctl=',7B=b:7', glob=A)), ('j15', dict(rec=',28=f:0,13C=b:64', glob=A)),
  ('j16', dict(rec=',28=f:0,8A=b:1', glob=A)), ('j17', dict(rec=',28=f:0,89=b:FF', glob=A)), ('j18', dict(rec=',28=f:0', ctl=',11A=b:1', glob=A)),
  ('j19', dict(rec=',28=f:0', ctl=',11A=b:3', glob=A)), ('j20', dict(rec=',28=f:0', ctl=',55=b:1', glob=A)), ('j21', dict(rec=',28=f:100', ctl=',55=b:1')),
  ('j22', dict(rec=',28=f:0', ctl=',4E=b:1,7B=b:8', glob=A)), ('j23', dict(rec=',28=f:0')),
  ('r1', dict(rec=',65=b:2', glob=A, ) | {'rec': ',65=b:2'}), ('r2', dict(rec=',65=b:2')),
] + [('r%X' % i, dict(rec=',65=b:2', glob=A + ';r1:4=b:%X' % i)) for i in (0x8A, 0x23, 0x28, 0x29)] + [
  ('r28b', dict(rec=',65=b:2', glob=A + ';r1:4=b:28;800BEE10:0=w:23')), ('r8Ab', dict(rec=',65=b:2,1C=f:-5', glob=A + ';r1:4=b:8A;800BEA36:0=b:1')),
  ('r8Ac', dict(rec=',65=b:2,1C=f:5', glob=A + ';r1:4=b:8A;800BEA36:0=b:1')), ('r23b', dict(rec=',65=b:2,104=b:0', ctl=',4E=b:1', glob=A + ';r1:4=b:23')),
  ('a1', dict(ctl=',98=b:1', glob=A)), ('a2', dict(ctl=',95=b:1', glob=A)), ('a3', dict(rec=',44=f:2', ctl=',95=b:1', glob=A)),
  ('a4', dict(rec=',AD=b:0,8A=b:1', ctl=',95=b:1', glob=A)), ('a5', dict(rec=',44=f:8', ctl=',98=b:1', glob=A)),
  ('f1', dict(rec=',118=f:500,180=f:100', glob=A)), ('f2', dict(rec=',118=f:150,180=f:100', glob=A)), ('f3', dict(rec=',118=f:500,180=f:100,84=h:3B', glob=A)),
  ('f4', dict(rec=',118=f:500,180=f:100,28=f:50', glob=A)), ('f5', dict(rec=',118=f:500,180=f:100,137=b:2', glob=A)),
  ('g1', dict(ctl=',31=b:1', rec=',3C=f:10', glob=A)), ('g1b', dict(ctl=',31=b:2', rec=',84=h:E9', glob=A)), ('g1c', dict(ctl=',31=b:1', rec=',28=f:0.5', glob=A)),
  ('g1d', dict(ctl=',31=b:1', rec=',4=b:96', glob=A)), ('g1e', dict(ctl=',31=b:1', rec=',13C=b:65', glob=A)), ('g1f', dict(ctl=',31=b:1', glob=A + ';800BEA36:0=b:1')),
  ('g2', dict(ctl=',31=b:5', pad=',0=h:8000')), ('g3', dict(ctl=',31=b:12')), ('g4', dict(ctl=',31=b:3D', pad=',0=h:8000')),
  ('g5', dict(ctl=',31=b:C', pad=',0=h:8000', rec=',20=f:-20')), ('g6', dict(ctl=',31=b:10', pad=',0=h:8000')), ('g7', dict(ctl=',31=b:10', pad=',0=h:8000')),
  ('g8', dict(ctl=',31=b:5,4E=b:1', pad=',0=h:8000')),
  ('e1', dict(rec=',81=b:2')), ('e2', dict(rec=',81=b:6')), ('e3', dict(rec=',81=b:82')),
]
for n, kw in S: print(setup(n, **kw))
