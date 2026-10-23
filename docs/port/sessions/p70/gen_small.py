#!/usr/bin/env python3
"""P70: knob setups for func_1503B840 (sb840.txt) and func_15039CC8 (s9cc8.txt). Object at 0x800CC6F0.
usage: gen_small.py b840|9cc8 > file"""
import random, subprocess, sys, os
H = os.path.dirname(os.path.abspath(__file__))
def tab(a, n, k):
    return [int(v, 16) for v in subprocess.check_output(['python3', H + '/rd.py', a, str(n), k]).split()]
O = 0x800CC6F0
R = random.Random(0x70)
lines = []
if sys.argv[1] == 'b840':
    t1 = tab('80098BE0', 3, 'h'); t2 = tab('80098B2C', 90, 'h')
    ks = [(k, 1) for k in t1 + t2] + [(R.randint(0, 0x400), R.choice([1, 0, 2])) for _ in range(12)] + [(0xE9, 0), (0x4B, 2)]
    for n, (k, st) in enumerate(ks):
        pk = {O: st, O + 0x84: k << 16, O + 0x2F8: R.choice([0, 0x10])}
        poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
        lines.append('b%02d_s%d_k%X ! 0=%08X ! %s ! !' % (n, st, k, O, poke))
else:
    ids = tab('8009822C', 192, 'b'); cnt = tab('80098400', 24, 'b'); lp = tab('80084710', 24, 'w')
    for n in range(40):
        idv = R.choice([0, 0x0B, 0x0C, 0x16, 0x20, 0x21, 0x53, 0x53, 0x05, 0x31, 0x36, R.randint(0, 191)])
        li = ids[idv]
        lst = tab('%08X' % lp[li - 1], cnt[li - 1], 'h') if li else []
        k = R.choice(lst + [0x15, R.randint(0, 0x300)] if lst else [0x15, R.randint(0, 0x300), 0])
        st = R.choice([1, 1, 0, 3]); hp = R.choice([0, 1, 5]); wat = R.choice([0, 1])
        spd = R.choice([0x00000000, 0x40000000, 0x40A00000, 0x41000000, 0x41A00000, 0x41C00000])
        rec = R.choice([0x80490000] * 5 + [0])
        pk = {O: st, O + 4: idv << 24, O + 0x84: k << 16, O + 0x1C8: hp << 8, O + 0xAC: wat << 16,
              O + 0x3C: spd, O + 0x324: rec, O + 0x31C: 0x804A0000, 0x804A0194: R.choice([0, 0, 1]),
              O + 0x2F8: R.choice([0, 0x02]), 0x800BEDD4: R.choice([0, 0, 0x01000000])}
        for i in range(0x30, 0x3C, 4):
            pk[0x80490000 + i] = R.randint(0, 0xFFFFFFFF)
        poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
        lines.append('r%02d_i%02X_s%d_k%X ! 0=%08X ! %s ! !' % (n, idv, st, k, O, poke))
if sys.argv[1] != 'b840':
    # every condition combination of the flag tail (id 0x05: no list; id 0x21 with an unlisted +0x84)
    n = 0
    for st in (1, 0):
        for hp in (0, 1):
            for wat in (0, 1):
                for spd in (0, 0x40A00000, 0x40A00001, 0x41A00000, 0x41A00001):
                    for b in (0, 1):
                        if st == 0 and (wat or b or spd not in (0, 0x41A00001)): continue
                        idv = R.choice([0x21, 0x0B])  # ids with a list (0x05 has none and returns early)
                        pk = {O: st, O + 4: idv << 24, O + 0x84: 0x7FFF << 16, O + 0x1C8: hp << 8, O + 0xAC: wat << 16,
                              O + 0x3C: spd, O + 0x324: 0x80490000, O + 0x31C: 0x804A0000, 0x804A0194: b, O + 0x2F8: 0,
                              0x800BEDD4: 0}
                        poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
                        lines.append('t%02d_s%d_h%d_w%d_v%X_b%d ! 0=%08X ! %s ! !' % (n, st, hp, wat, spd, b, O, poke)); n += 1
print('\n'.join(lines))
