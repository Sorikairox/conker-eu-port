#!/usr/bin/env python3
# P120: knob setups for func_151E3AE4 (settings list). Run with DIFFTEST_ARGMEM=15049AD0=0:64 (ring point arrays).
# fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
import struct
def fw(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
MIN = bytes.fromhex('00000102010000010000000000020000000001000000000000000000')
MAX = bytes.fromhex('0201050a05040a140102040102140101040128010100012010001010')
REC = 0x80480000; TEXT = 0x80470000
def words(addr, b):
    b = b + bytes((-len(b)) % 4)
    return ['%08X=%s' % (addr + i, b[i:i + 4].hex().upper()) for i in range(0, len(b), 4)]
def setup(name, mask=0x02200200, a1=0, a2=1, alpha=0xC0, a4=1, inp=0, sel=9, d8=0.0, dc=0.0, eb2=0xFF, eb4=1,
          v184=0, v188=0.0, e13=2, vals=None, dt=2):
    if vals is None: vals = bytes(MIN)
    p = ['80090174=%08X' % REC, '%08X=%04X0000' % (REC + 0x20, inp), '800901D4=%02X000000' % sel,
         '800901D8=%s' % fw(d8), '800901DC=%s' % fw(dc), '800E0EB0=0000%04X' % (eb2 & 0xFFFF),
         '800E0EB4=%02X000000' % (eb4 & 0xFF), '80090184=%02X000000' % (v184 & 0xFF), '80090188=%s' % fw(v188),
         '800E1010=00000000', '800E1008=%08X' % TEXT, '800BEE04=%08X' % dt]
    p += words(0x800E1010, vals) + words(0x80090210, MIN) + words(0x8009022C, MAX)
    p = [x for x in p if not x.startswith('800E1010=00000000')]
    # D_800E1013 lives in D_800E1010's block: byte 3
    vb = bytearray(vals); vb[3] = e13 & 0xFF if len(vb) > 3 else 0
    p = [x for x in p if not x.startswith('800E1010=')] + ['800E1010=%s' % bytes(vb[0:4]).hex().upper()]
    arg = '0=%X,1=%X,2=%X,3=%X,4=%X' % (mask, a1, a2, alpha, a4)
    return '%s ! %s ! %s ! ! ! ! !' % (name, arg, ','.join(p))
def mk(n, start=0, stride=1):
    m = 0
    for k in range(n): m |= 1 << ((start + k * stride) % 28)
    return m
L = []
masks = {'title': 0x02200200, 'n1': mk(1, 5), 'n2': mk(2, 1, 3), 'n3': mk(3, 0, 2), 'n4': mk(4, 2, 2), 'n5': mk(5, 0, 3),
         'n6': mk(6, 1, 2), 'n7': mk(7, 0, 4), 'n9': mk(9, 0, 3), 'n10': mk(10, 0, 2), 'n11': mk(11, 3, 2), 'lo': 0x0FFF}
for mn, m in masks.items():
    for a1 in (0, 1):
        for d8 in (0.0, 0.4):
            for sel in (0, 3, 9, 27):
                L.append(setup('lay_%s_a%d_d%g_s%d' % (mn, a1, d8, sel), mask=m, a1=a1, d8=d8, sel=sel))
# input handling per mode
for a1 in (0, 1):
    for inp in (0, 1, 2, 4, 8, 3, 0xC, 0x10):
        for sel, mn in ((9, 'title'), (2, 'lo'), (0, 'lo'), (3, 'n10')):
            for d8, dc in ((0.0, 0.0), (-0.1, 0.0), (0.5, 0.075), (0.98, 0.075), (0.02, -0.075)):
                L.append(setup('in_a%d_i%X_s%d_%s_d%g_c%g' % (a1, inp, sel, mn, d8, dc), mask=masks[mn], a1=a1, inp=inp, sel=sel, d8=d8, dc=dc))
# value wrap (below min / above max) for the selected item, other items out of range
for a1 in (0, 1):
    for inp in (0, 1, 2, 4, 8):
        for which in ('lo', 'hi'):
            v = bytearray(MIN if which == 'lo' else MAX)
            L.append(setup('wrap_a%d_i%X_%s' % (a1, inp, which), mask=0x0FFF, a1=a1, inp=inp, sel=2, vals=bytes(v)))
    vb = bytearray(MIN); vb[5] = 0xFF; vb[7] = 0x30
    L.append(setup('clamp_a%d' % a1, mask=0x0FFF, a1=a1, vals=bytes(vb)))
# fade-in value (arg4) states
for a4 in (0, 1):
    for eb2 in (0xFF, -0xFF, -0x10, 0x80, 0xC0, 0xA4):
        for alpha in (0xFF, 0x40):
            for d8 in (0.0, 0.5):
                L.append(setup('fade_a4_%d_e%X_al%X_d%g' % (a4, eb2 & 0xFFFF, alpha, d8), a4=a4, eb2=eb2, eb4=3, alpha=alpha, d8=d8, mask=0x0FFF, sel=4))
# item types: values 0 / 1 / 3 for every item (types 0x7A..0x7F, lists, negative labels), D_800E1013
for vv in (0, 1, 3):
    for e13 in (2, 3):
        vals = bytes(min(vv, MAX[k]) for k in range(28))
        L.append(setup('types_v%d_e%d' % (vv, e13), mask=0x0FFFFFFF, vals=vals, e13=e13, sel=5))
        L.append(setup('types_v%d_e%d_ring' % (vv, e13), mask=0x0FFFFFFF & ~0x0F0F0F0, vals=vals, e13=e13, sel=1, a1=1))
# cursor arrows (arg2)
for a2 in (0, 1):
    for v184, v188 in ((0, 0.0), (0, 0.5), (2, 0.95), (1, 0.3), (5, 0.0)):
        for inp in (0, 3):
            L.append(setup('arrow_a%d_r%d_%g_i%d' % (a2, v184, v188, inp), a2=a2, v184=v184, v188=v188, inp=inp, mask=0x0FFF, sel=6))
print('\n'.join(L))
