#!/usr/bin/env python3
# P203: setups for func_1518ECAC particle_quad_velocity_build. jal keys: 151D6310 (block), 15048D30 (sin),
# 15048CA0 (cos), memcpy 10023360. Globals: D_800DD608 / D_800DD618 (f32[4]), D_800BEDC8 (f32).
import sys, struct
def fb(x): return struct.unpack('>I', struct.pack('>f', x))[0]
R = []
P = 0x80410000
def add(name, view=0, blk=0x80450000, fresh=0, prev=(10.0, 20.0, 30.0), cur=(14.0, 21.0, 25.0), w=12.0, h=30.0, k=0.5,
        sc=(0.6, 0.8), inv=1.0, sincos=(0.38, 0.92)):
    p = {P + 0x2C: fb(w), P + 0x30: fb(h), P + 0x34: fb(cur[0]), P + 0x38: fb(cur[1]), P + 0x3C: fb(cur[2]),
         P + 0x40: fb(prev[0]), P + 0x44: fb(prev[1]), P + 0x48: fb(prev[2]), P + 0x160: fb(k),
         P + 0x100 + view * 4: 0x80460000, 0x800DD608 + view * 4: fb(sc[0]), 0x800DD618 + view * 4: fb(sc[1]),
         0x800BEDC8: fb(inv)}
    pk = ','.join('%08X=%08X' % (a, v) for a, v in sorted(p.items()))
    retf = '15048D30=%08X,15048CA0=%08X' % (fb(sincos[0]), fb(sincos[1]))
    R.append('%s ! 0=%X,1=%X ! %s ! ! %s ! ! 151D6310=3:%X ! 151D6310=4:%X' % (name, P, view, pk, retf, blk, fresh))
add('base')
add('fresh', fresh=1)
add('noblk', blk=0)
add('view1', view=1, sc=(-0.3, 0.95))
add('view3_fresh', view=3, fresh=1, sc=(1.0, 0.0))
add('fwd', prev=(20.0, 0.0, 10.0), cur=(10.0, 0.0, 30.0))
add('clamp', prev=(1000.0, 0.0, 0.0), cur=(0.0, 0.0, 0.0), k=2.0)
add('clamp_neg', prev=(0.0, 0.0, 0.0), cur=(1000.0, 0.0, 0.0), k=2.0)
add('tiny_neg', prev=(10.0, 0.0, 0.0), cur=(10.0001, 0.0, 0.0), k=0.01)
add('zero', prev=(5.0, 5.0, 5.0), cur=(5.0, 5.0, 5.0))
add('inv0', inv=0.0)
add('big', w=300.5, h=-40.25, cur=(-2000.5, 500.75, 1234.5), prev=(-2010.0, 499.0, 1240.0), sincos=(-0.7, 0.71))
add('k_large', k=40.0, sc=(0.2, -0.98))
add('lean153', prev=(10.0, 0.0, 0.0), cur=(12.3409, 0.0, 0.0), k=1.0, sc=(0.0, 1.0))
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
