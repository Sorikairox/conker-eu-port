#!/usr/bin/env python3
"""P86: knob setups for func_151143D4 (record / group update pass). Writes s43d4.txt. EU addresses: D_800DBEF4 = 800DC324
(record array pointer, 0xA0 each), D_800DC320 800DC320, D_800DC3C8 800DC3C8, D_80087380 = 80087720 (.data: even trials),
D_800D23C0 = 800D27E0 (group array pointer, 0x18 each). Callbacks point at real functions (stubbed by the harness)."""
import random
REC, GRP = 0x80480000, 0x80490000
FNS = (0x15024910, 0x150268BC, 0x15029EA8)
out = []
def setup(name, recs, total, sub, groups, ngroups=None, far=()):
    w = {0x800DC324: '%08X' % REC, 0x800DC320: '%08X' % total, 0x800DC3C8: '%08X' % sub, 0x800D27E0: '%08X' % GRP,
         0x80087720: '%08X' % ((len(groups) if ngroups is None else ngroups) & 0xFFFFFFFF)}
    for i, (fl, busy, pos, ex, fn) in enumerate(recs):
        b = REC + 0xA0 * i
        w[b + 0x38] = '%08X' % FNS[fn]
        w[b + 0x58] = '0000%04X' % (pos[0] & 0xFFFF); w[b + 0x5C] = '%04X%04X' % (pos[1] & 0xFFFF, pos[2] & 0xFFFF)
        w[b + 0x6C] = '0000%02X%02X' % (busy, fl)
        w[b + 0x80] = '%08X' % (ex & 0xFFFFFFFF)
    for idx in far:   # records past 0x7FF (the id mask is 0xFFF)
        b = REC + 0xA0 * idx
        w[b + 0x38] = '%08X' % FNS[1]; w[b + 0x58] = '00001234'; w[b + 0x5C] = '56789ABC'; w[b + 0x6C] = '00000040'; w[b + 0x80] = '0BADF00D'
    for g, (cnt, ids) in enumerate(groups):
        b = GRP + 0x18 * g
        w[b] = '0000%04X' % cnt
        ids = (list(ids) + [0] * 8)[:8]
        for k in range(4):
            w[b + 8 + 4 * k] = '%04X%04X' % (ids[2 * k], ids[2 * k + 1])
    out.append(' ! '.join([name, '0=1', ','.join('%08X=%s' % kv for kv in sorted(w.items())), '', '', '', '', '']))
def rec(rng, p=0.7):
    return (rng.choice([0x40, 0x40, 0xC0, 0x41, 0, 0xBF]) if rng.random() < p else 0x40, rng.choice([0, 0, 0, 1]),
            (rng.randrange(-40000, 40000), rng.randrange(-3000, 3000), rng.randrange(-200, 200)), rng.randrange(-2**31, 2**31), rng.randrange(3))
rng = random.Random(4334)
R = [rec(rng) for _ in range(16)]
setup('flat', R, 10, 2, [])
setup('flat0', R, 3, 3, [])
setup('flatneg', R, 2, 5, [])
setup('grp1', R, 0, 0, [(3, (0x2001, 0x2002, 0x2003))])
setup('grp_mix', R, 4, 1, [(4, (0x2004, 0x1005, 0x2006, 0x2007)), (2, (0x3001, 0x2002)), (3, (0x2009, 0x200A, 0x200B))])
setup('grp_cnt0', R, 0, 0, [(0, (0x2001, 0x2002)), (1, (0x2003, 0x2004))])
setup('grp_first_busy', [(0x40, 1, (5, 6, 7), 99, 0)] + R[1:], 0, 0, [(3, (0x2000, 0x2001, 0x2002))])
setup('grp_first_off', [(0x00, 0, (5, 6, 7), 99, 0)] + R[1:], 0, 0, [(3, (0x2000, 0x2001, 0x2002))])
setup('grp_carry', R, 0, 0, [(2, (0x2003, 0x2004)), (3, (0x2005, 0x2006, 0x2007)), (8, (0x2008,) + tuple(0x2000 + k for k in range(7)))])
setup('bigid', R, 0, 0, [(3, (0x2801, 0x2002, 0x2803))], far=(0x801, 0x803))
setup('grp_neg', R, 0, 0, [(2, (0x2003, 0x2004))], ngroups=-1)
for k in range(10):
    rr = random.Random(k)
    Rk = [rec(rr) for _ in range(16)]
    gs = [(rr.randrange(0, 9), [rr.choice([0x2000, 0x2000, 0x1000, 0x3000]) + rr.randrange(16) for _ in range(8)]) for _ in range(rr.randrange(0, 5))]
    setup('mix%d' % k, Rk, rr.randrange(0, 17), rr.randrange(0, 6), gs)
open(__file__.replace('gen43d4.py', 's43d4.txt'), 'w').write('\n'.join(out) + '\n')
print(len(out))
