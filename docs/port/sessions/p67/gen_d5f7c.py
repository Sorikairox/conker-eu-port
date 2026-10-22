#!/usr/bin/env python3
"""P67 setups for func_150D5F7C -> d5f7c.txt. rec = 0x80420000, camera = 0x80450000, type (func_15134070 = 0x151345E0)
= 2: D_800A42F4[2] = count, D_80089DC0[2] = 0x80440000 (sprite list); both tables are real ROM data (pokes do not reach them), so the setups vary the type. Run with
DIFFTEST_ARGMEM=15132FBC=0:124,151C0910=0:18,151C0910=1:12,150D6B00=0:18,150D6B00=1:12,150D6944=0:12,150D6898=0:12,151C0B54=0:12.
Callees: ACEA0 (out 8-10 hit, 11 t, 13 surface), E80 = 0x151453F0 (out 1-3 axes), normalise 0x15145698, dot 0x15144FE4,
basis 0x151465E8, polar 0x15143DE4 (out 2 / 3), rand int 0x150ADF00, rand f32 0x150ADF48."""
import sys, struct
sys.path.insert(0, '../p59'); from pk import build
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def V(*a): return ';'.join(fb(x) for x in a)
def setup(name, me='', glob='', count=4, ret='', retf='', outa='', outw='', a1='3', a2='7'):
    spec = '80083330:0=w:0;800A42FC:0=w:%X;80089DC8:0=w:80440000;80440000:0=w:11,4=w:22,8=w:33,C=w:44,10=w:55,14=w:66' % count + glob + ';'
    spec += '80420000:14=f:10,18=f:20,1C=f:30,2C=f:4,30=f:21,34=f:28,184=w:0,1D4=w:80460000,74=b:0,3B=b:5,14C=f:1.5,150=f:0.5,318=w:80450000' + me
    spec += ';80450000:23D=b:9'
    r = '151345E0=2,15145698=1,150ACEA0=1,151453F0=1,150ADF00=7;12345;E3' + (',' + ret if ret else '')
    rf = '150ADF48=' + V(0.25, 0.5, 0.75, 0.1, 0.9) + ',15144FE4=' + fb(-1) + (',' + retf if retf else '')
    oa = '151453F0=1:%s/2:%s/3:%s,151465E8=1:%s/2:%s' % (V(2, 0, 0), V(0, 0.5, 3), V(0, 4, 0), V(0.6, 0, 0.8), V(0, 1, 0)) + (',' + outa if outa else '')
    ow = '150ACEA0=8:%s/9:%s/10:%s/11:%s/13:0000000E,15143DE4=2:%s/3:%s' % (fb(1), fb(2), fb(3), fb(100), fb(0.3), fb(-0.7)) + (',' + outw if outw else '')
    return '%s ! 0=80420000,1=%s,2=%s ! %s ! %s ! %s ! %s ! %s' % (name, a1, a2, build(spec), r, rf, oa, ow)
S = [
  ('t63', dict(ret='151345E0=63')), ('base', {}), ('snd', dict(me=',184=w:2E')), ('snd2', dict(me=',184=w:1E')), ('n1d4', dict(me=',1D4=w:0')), ('u74', dict(me=',74=b:1F')),
  ('u74b', dict(me=',74=b:E')), ('nomove', dict(ret='15145698=0')), ('miss', dict(ret='150ACEA0=0')),
  ('far', dict(outw='150ACEA0=8:%s/9:%s/10:%s/11:%s/13:0000000E' % (fb(1), fb(2), fb(3), fb(397)))),
  ('near', dict(outw='150ACEA0=8:%s/9:%s/10:%s/11:%s/13:0000000E' % (fb(1), fb(2), fb(3), fb(396.9)))),
  ('surf', dict(outw='150ACEA0=8:%s/9:%s/10:%s/11:%s/13:0000001E' % (fb(1), fb(2), fb(3), fb(10)))),
  ('noe80', dict(ret='151453F0=0')), ('dotp', dict(retf='15144FE4=' + fb(0.5))), ('dot0', dict(retf='15144FE4=' + fb(0))),
  ('nomiss', dict(ret='15145698=0,150ACEA0=0')), ('ty0', dict(ret='151345E0=0')), ('ty1', dict(ret='151345E0=1')), ('ty3', dict(ret='151345E0=3')), ('ty5', dict(ret='151345E0=5')), ('ty9', dict(ret='151345E0=9')),
  ('nocam', dict(me=',318=w:0')), ('fa0', dict(glob=';80083330:0=w:1')), ('fa0n', dict(glob=';80083330:0=w:FFFFFFFF')),
  ('nocam2', dict(me=',318=w:0', outw='150ACEA0=8:%s/9:%s/10:%s/11:%s/13:00000001' % (fb(1), fb(2), fb(3), fb(10)))),
  ('args', dict(a1='1FF', a2='0')),
]
open(sys.argv[1] if len(sys.argv) > 1 else 'd5f7c.txt', 'w').write('\n'.join(setup(n, **k) for n, k in S) + '\n')
