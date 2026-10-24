#!/usr/bin/env python3
# P237: setups for func_15160E30 (light_beam_update). Effect E 80450000: +0x14 light 80460000, +0x18 object 80470000,
# +0x1C uid / +0x1D attach point, +0x20 offset, +0x2C end, +0x38 scale, +0x3C flags. Object: +0 live, +0x3B uid,
# +0x1D4 matrices 80480000, +0x74 nibble, +0x14 pos. func_15145EA4 = jal 15146414 (outputs stay stack fill),
# func_15145128 = jal 15145698 (RET), func_15081A90 (15081A90; OUTA through arg 7: hit object, t, x, y, z, ..., +0x58
# word with the +0x59 hit byte). Hit object H 80490000 (+4 kind).
import struct
def f(x): return struct.unpack('>I', struct.pack('>f', x))[0]
E, L, O, M, H = 0x80450000, 0x80460000, 0x80470000, 0x80480000, 0x80490000
def setup(name, live=1, uid=7, ouid=7, mtx=True, flags=1, nib=3, norm=1, hit=2, kind=0x9E, t=0.5, scale=100.0, pt=3):
    pk = {E + 0x14: L, E + 0x18: O, E + 0x1C: (uid << 24) | (pt << 16), E + 0x20: f(1.0), E + 0x24: f(2.0), E + 0x28: f(3.0),
          E + 0x2C: f(4.0), E + 0x30: f(5.0), E + 0x34: f(6.0), E + 0x38: f(scale), E + 0x3C: flags << 24,
          O: live, O + 0x38: ouid, O + 0x1D4: M if mtx else 0, O + 0x74: nib << 24, O + 0x14: f(123.6), O + 0x18: f(-45.2),
          O + 0x1C: f(900.9), L + 0x8: 0x55555555, L + 0x2C: 0x66666666, H + 4: kind << 24}
    words = [H, f(t), f(-77.7), f(66.4), f(1500.2)] + [0] * 17 + [hit << 16]
    outa = '15081A90=7:' + ';'.join('%X' % w for w in words)
    print('%s ! 0=%X ! %s ! 15145698=%X ! ! %s ! ! !' % (name, E, ','.join('%08X=%08X' % kv for kv in sorted(pk.items())), norm, outa))
setup('dead', live=0)
setup('uid', ouid=8)
setup('nomtx', mtx=False)
setup('noflag', flags=2)
setup('hidden', nib=0xF)
setup('nonorm', norm=0)
setup('nohit', hit=0)
setup('world', hit=1, flags=3)
setup('obj9E', hit=2, flags=3)
setup('obj9E_noflag2', hit=2, flags=1)
setup('obj_other', hit=3, flags=3, kind=0x9D)
setup('bright_hi', hit=1, t=4.0)
setup('bright_neg', hit=1, t=-0.25)
setup('bright_mid', hit=1, t=0.37, scale=300.0, pt=0)
setup('uid_pt', pt=9, mtx=False)
setup('bright_neg15', hit=1, t=-0.015)
