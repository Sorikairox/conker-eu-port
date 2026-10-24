#!/usr/bin/env python3
# P207: setups for func_1509E3D4 (one per command + edge values). args record at 0x80450000.
A = 0x80450000
def rec(w2, w3=0x12345, w4=-0x23456, w5=0x34567, b=None):
    p = ['%08X=%08X' % (A + 8 + 4*i, v & 0xFFFFFFFF) for i, v in enumerate((w2, w3, w4, w5))]
    return p
cam = ['800DC420=80470000', '804707B4=3F400000']
rows = []
for c in range(27):
    w2 = 1
    if c == 1: w2 = 0x77
    rows.append(('c%d' % c, c, rec(w2), '150871B8=3;' if False else '', '', ''))
rows += [
 ('c1_neg', 1, rec(-0x77), '', '', ''),
 ('c1_exact', 1, rec(120), '', '', ''),
 ('c16_ff', 16, rec(2), '150871B8=FF', '', ''),
 ('c16_pt', 16, rec(2, 0x55), '150871B8=3', '', '1508712C=1:42C80000/2:C3480000/3:44960000'),
 ('c24_none', 24, rec(0x10203040), '150842F8=0', '', ''),
 ('c24_obj', 24, rec(0x10203040), '150842F8=80460000', '', ''),
 ('c25_i2', 25, rec(2, 0x18000, -0x8000, 0x30000) + cam + ['800D3400=3F000000'], '', '', ''),
 ('c26_i3', 26, rec(3, 0x8000, 0x28000, -0x10000) + cam + ['800D3404=BF800000'], '', '', ''),
 ('c27', 27, rec(1), '', '', ''),
 ('cbig', 0x80000001, rec(1), '', '', ''),
]
for c in (4,5,6,7,8,9,10,11,12,13,14,15,22):
    pass
for n, c, poke, ret, retf, outw in rows:
    if n.startswith('c25') or n.startswith('c26') or n in ('c25', 'c26'): pass
    if n in ('c25', 'c26'): poke = poke + cam
    if n == 'c16': ret = '150871B8=4'; outw = '1508712C=1:3F800000/2:40000000/3:40400000'
    if n == 'c24': ret = '150842F8=80460000'
    print('%s ! 0=7,1=%X,2=%X ! %s ! %s ! %s ! ! %s' % (n, c & 0xFFFFFFFF, A, ','.join(poke), ret, retf, outw))
