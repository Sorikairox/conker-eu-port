#!/usr/bin/env python3
"""P86: knob setups for func_1502AB94 (entry dispatcher). Object / record returns live in the fake heap: 0x806xxxxx is the harness stack, normalised away in call compares. Writes sab94.txt. EU addresses: D_800C3A08 800C3A08 (u8[4]),
D_800C3A10 800C3A10 (table pointer per player), D_800C3958 = 800C3D78 (record pointer per player), D_800C3C88 = 800C40A8.
jal targets: func_15083E90 150842F8, func_151149AC 15114F2C, handlers 15024910 / 150268BC / 15029EA8.
arg1 / arg2 are u8 / u16 in the prototype (the caller masks), so ARG gives them in range."""
import random
TAB, REC = 0x80520000, 0x80530000
out = []
def setup(name, player=0, a1=0, a2=0x1234, kind=2, ident=7, obj=0x80460000, rec=0x80470000, h=(0, 0, 0), c88=0, flags=(1, 0, 5, 9)):
    w = {}
    w[0x800C3A08] = '%02X%02X%02X%02X' % flags
    for p in range(4):
        w[0x800C3A10 + 4 * p] = '%08X' % (TAB + 0x400 * p)
        w[0x800C3D78 + 4 * p] = '%08X' % (REC + 0x2000 * p)
    w[0x800C40A8] = '%02X000000' % c88
    e = TAB + 0x400 * player + 8 * a1
    w[e] = '%04X%02X11' % (kind, ident)
    w[e + 4] = '22334455'
    pokes = ','.join('%08X=%s' % kv for kv in sorted(w.items()))
    args = '0=%X,1=%X,2=%X,3=%X,4=%X' % (0x4000 + a1, a1, a2, 0x77, player)
    ret = '150842F8=%X,15114F2C=%X,15024910=%X,150268BC=%X,15029EA8=%X' % ((obj, rec) + h)
    out.append(' ! '.join([name, args, pokes, ret, '', '', '', '']))
for p in range(4):
    for k in (0, 1, 2, 3, 4):
        setup('p%d_k%d' % (p, k), player=p, a1=(3 * p + k) % 8, kind=k, ident=0x10 + k)
setup('obj0', kind=2, obj=0)
setup('objm14', kind=2, obj=0xFFFFFFEC)
setup('rec0', kind=3, rec=0)
setup('k3_obj0', kind=3, obj=0)
setup('k2_rec0', kind=2, rec=0)
for c in (0, 1, 2, 3):
    for hs in ((0, 0, 0), (5, 0, 0), (0, 6, 0), (0, 0, 7), (0, 0xFFFFFFFF, 3), (8, 9, 10)):
        setup('c%d_h%X%X%X' % ((c,) + tuple(x & 0xF for x in hs)), c88=c, h=hs, kind=(c + hs[2]) % 4, a1=c + 2, player=c)
setup('a1_ff', a1=0xFF, a2=0xFFFF, kind=2)
setup('a1_80', a1=0x80, player=3, kind=3)
rng = random.Random(861)
for k in range(10):
    setup('mix%02d' % k, player=rng.randrange(4), a1=rng.randrange(40), a2=rng.randrange(0x10000), kind=rng.randrange(5),
          ident=rng.randrange(256), obj=rng.choice([0, 0x80460000]), rec=rng.choice([0, 0x80470000]),
          h=tuple(rng.choice([0, 0, 1, 0x12345]) for _ in range(3)), c88=rng.randrange(3),
          flags=tuple(rng.randrange(256) for _ in range(4)))
open(__file__.replace('genab94.py', 'sab94.txt'), 'w').write('\n'.join(out) + '\n')
print(len(out), 'setups')
