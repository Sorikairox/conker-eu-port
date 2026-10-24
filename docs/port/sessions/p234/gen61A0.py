#!/usr/bin/env python3
# P234: setups for func_151B61A0 (ripple_spawn_flat). Arguments: pos 80450000, vel 80450010 / NULL, scale (a2 bits),
# dir 80450020, acc 80450030 / NULL, speed, life (s16), alpha, arg8, grow, shift, additive, layer, owner.
# func_15132FBC = jal 15132FBC (RET object 80460000 / 0); memcpy = jal 10023360.
import struct
def f(x): return struct.unpack('>I', struct.pack('>f', x))[0]
P = ','.join('%08X=%08X' % (0x80450000 + 4 * k, f(10.0 + k)) for k in range(16))
def setup(name, vel=True, acc=True, life=-1, shift=0, add=0, obj=True, scale=2.5, alpha=0x80):
    a = '0=80450000,1=%X,2=%X,3=80450020,4=%X,5=%X,6=%X,7=%X,8=1234,9=%X,10=%X,11=%X,12=7,13=80470000' % (
        0x80450010 if vel else 0, f(scale), 0x80450030 if acc else 0, f(1.5), life & 0xFFFF, alpha, f(0.25), shift, add)
    print('%s ! %s ! %s ! 15132FBC=%X ! ! ! ! !' % (name, a, P, 0x80460000 if obj else 0))
setup('base')
setup('novel', vel=False)
setup('noacc', acc=False)
setup('none', vel=False, acc=False)
setup('life', life=40, shift=2)
setup('life_neg', life=-5, shift=1)
setup('life_0', life=0, shift=8)
setup('shift3', shift=3)
setup('add', add=1)
setup('add2', add=0x80, life=7, shift=4)
setup('noobj', obj=False)
setup('noobj_life', obj=False, life=3, shift=5)
setup('alpha', alpha=0xFF, scale=-1.0)
