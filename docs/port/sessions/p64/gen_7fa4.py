#!/usr/bin/env python3
"""P64 setups for func_15017FA4 -> 7fa4.txt. zone at 0x80400000, out at 0x80401000; func_150A7E40 (0x150A7E40)
returns the 8 transformed corners through its stack out-params 4 / 5 / 6 (p64 OUTW, one word per call)."""
import sys, struct
sys.path.insert(0, '../p59'); from pk import build
fb = lambda v: '%08X' % struct.unpack('>I', struct.pack('>f', v))[0]
seqs = {
  'A': ([-3.5, 2.5, -2, 4.7, -6.2, 1, 7.9, 0.5], [5, -1.5, 6, -3, 2, -8.9, 9.1, 0], [0.3, -0.3, 12.6, -12.6, 3, 20, -20, 1]),
  'B': ([10, 20, -10, -20, 15, -15, 5, -5], [-1, -2, -3, -4, 1, 2, 3, 4], [100.9, -100.9, 50, -50, 0, 0, 200, -200]),
}
def setup(name, shape, sq, zone=''):
    spec = '80400000:0=h:64,2=h:FFF0,4=h:200,6=h:30,8=h:50,A=h:70,C=f:0.5,10=f:-1.25,15=b:%X%s' % (shape, zone)
    px, py, pz = seqs[sq]
    ow = '150A7E40=4:%s/5:%s/6:%s' % (';'.join(map(fb, px)), ';'.join(map(fb, py)), ';'.join(map(fb, pz)))
    return '%s ! 0=80400000,1=80401000 ! %s ! ! ! ! %s' % (name, build(spec), ow)
for sh in (0, 1, 2, 3):
    for sq in 'AB':
        print(setup('s%d%s' % (sh, sq), sh, sq))
print(setup('s0x', 0, 'A', ',15=b:FC'))
print(setup('s2x', 2, 'B', ',15=b:F6,6=h:FF00,8=h:7FFF,A=h:8001'))
