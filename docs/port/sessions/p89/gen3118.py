#!/usr/bin/env python3
"""P89: knob setups for func_15073118 (child object spawn). EU: func_1505ED34 = jal 1505F0E0, D_800CC2D0 = 800CC6F0,
D_800C42B0 = 800C42B0 (u8), D_80082FA0 = 80083330 (.game_data: real value, not pokeable). Writes s3118.txt."""
import struct
f = lambda x: '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
P = 0x80470000
out = []
def setup(name, joint=-1, kind=5, mtx=0, l2f=0, ang=0.0, yaw=0x1234, x=1.0, y=2.0, z=3.0, o=0x80480000, d9f0='0', b66=0xFF):
    pokes = {P + 0x1D4: '%08X' % mtx, 0x800C42B0: '%02X000000' % l2f, P + 0x78: '0000%04X' % yaw, P + 0x64: '0000%02X00' % b66,
             P + 0x14: f(10.0), P + 0x18: f(20.0), P + 0x1C: f(30.0)}
    args = '0=%X,1=%X,2=%X,3=%s,4=%s,5=%s,6=%s,7=%s,8=%s,9=%s' % (P, joint & 0xFFFFFFFF, kind, f(x), f(y), f(z), f(ang), f(1.5), f(2.5), f(3.5))
    pk = ','.join('%08X=%s' % kv for kv in sorted(pokes.items()))
    ret = '1505F0E0=%X,1515D9F0=%s' % (o, d9f0)
    out.append(' ! '.join([name, args, pk, ret, '', '', '', '']))
for k in (5, 0x42, 0x1F):
    setup('nomtx_k%X' % k, kind=k)
    setup('j2_k%X' % k, joint=2, kind=k, mtx=0x80490000)
    setup('j2l2f_k%X' % k, joint=2, kind=k, mtx=0x80490000, l2f=1)
setup('jm1_mtx', joint=-1, mtx=0x80490000)
setup('j0_nomtx', joint=0, mtx=0)
for a in (90.0, -45.0, -0.5, 400.0, -720.0):
    setup('ang%g' % a, ang=a, yaw=0x8000)
setup('yawffff', yaw=0xFFFF, ang=1.0)
setup('inarray', o=0x800CC6F0 + 0x32C * 5)
setup('inarray0', o=0x800CC6F0)
for s in ('0', '7', '0;0;0;9', '5;0'):
    setup('d9f0_%s' % s.replace(';', '_'), d9f0=s)
setup('b66', b66=0x5D)
open(__file__.replace('gen3118.py', 's3118.txt'), 'w').write('\n'.join(out) + '\n')
print(len(out), 'setups')
