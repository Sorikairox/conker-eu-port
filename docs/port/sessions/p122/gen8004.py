#!/usr/bin/env python3
"""P122: difftest setups for func_15178004 (vtx_anims_update). EU addresses: D_800DD410 = 800DD840 (2 anim
pointers), D_800DD418 = 800DD848 (u8 count), D_800BE9C0 = 800BEDE0 (u8 frame); func_151149AC key 15114F2C.
usage: gen8004.py N SEED > setups.txt  (knobs.sh fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW)"""
import random, struct, sys

def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def w(x): return '%08X' % (x & 0xFFFFFFFF)

N, seed = int(sys.argv[1]), int(sys.argv[2])
rng = random.Random(seed)
for n in range(N):
    pk = {}
    cnt = rng.choice([1, 2, 2])
    frame = rng.choice([0, 1])
    pk[0x800DD848] = w(cnt << 24)
    pk[0x800BEDE0] = w(frame << 24)
    models = [0x80410000, 0x80420000]
    rets = []; vis = []
    for i in range(2):
        a = 0x80400000 + 0x100 * i
        pk[0x800DD840 + 4 * i] = w(a)
        mode = rng.choice([0, 1, 2, 4, 5, 6, 3, 7])
        flag2 = rng.choice([0, 0, 1])
        pk[a] = w((i << 24) | (mode << 16) | (flag2 << 8) | 0x33)
        pk[a + 0x20] = w(0x80430000 + 0x100 * i); pk[a + 0x24] = w(0x80431000 + 0x100 * i); pk[a + 0x28] = w(0x80432000 + 0x100 * i)
        m = models[i]
        ident = rng.random() < 0.5
        pos = [0.0, 0.0, 0.0] if ident else [rng.choice([0.0, 10.0]) for _ in range(3)]
        scl = [1.0, 1.0, 1.0] if ident else [rng.choice([1.0, 2.0]) for _ in range(3)]
        if not ident and pos == [0.0] * 3 and scl == [1.0] * 3: scl[rng.randrange(3)] = 0.5
        for k in range(3): pk[m + 4 * k] = f(pos[k]); pk[m + 0x2C + 4 * k] = f(scl[k])
        nv = rng.choice([1, 2, 3, 5])
        pk[m + 0x10] = w((rng.choice([0, 7, -20]) << 16) | (rng.choice([0, 3, -9]) & 0xFFFF))
        pk[m + 0x14] = w((rng.choice([0, 11, -5]) << 16) | nv)
        pk[m + 0x20] = w(0x80440000 + 0x1000 * i); pk[m + 0x24] = w(0x80440800 + 0x1000 * i)
        pk[m + 0x28] = w(0x80450000 + 0x1000 * i)
        fl = rng.choice([0x01, 0x0F, 0x10, 0x00, 0x03]); pk[m + 0x6C] = w(fl)
        vis.append(bool(fl & 0xF) and flag2 == 0)
    # func_151149AC: calls in order: loop 1 one per anim, loop 2 one per anim (+ one more when visible and +2 == 0)
    seq = []
    for i in range(cnt): seq.append(models[i])
    for i in range(cnt): seq += [models[i], models[i]] if vis[i] else [models[i]]
    xs = ';'.join(f(rng.choice([1.5, -2.7, 100.9, -0.2])) for _ in range(10))
    ys = ';'.join(f(rng.choice([3.2, -40.5, 7.0])) for _ in range(10))
    zs = ';'.join(f(rng.choice([-1.9, 22.1, 0.0])) for _ in range(10))
    print('v%d ! ! %s ! 15114F2C=%s ! ! ! 150A7E40=4:%s/5:%s/6:%s ! ' % (
        n, ','.join('%X=%s' % kv for kv in sorted(pk.items())), ';'.join('%X' % s for s in seq), xs, ys, zs))
