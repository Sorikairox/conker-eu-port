#!/usr/bin/env python3
# P148: setups for func_1517B270 (player_morph_blend). EU addresses: D_800CC2D0 800CC6F0 (player 0), D_800D19A0 800D1DC0,
# D_800C4440 800C4440, D_800C4730 800C4730, D_800DD460 800DD890, D_800BEAC0 800BEEE0, D_800BE9E4 800BEE04, D_800BE9C0 800BEDE0.
# Shape sets from ROM D_800A7610 (DIFFTEST_ROMDATA=1): [0] type 0 n 16 counts 0x151 / 0xC / 0xC, [1] type 0x3A n 7 counts 0x6D / 0x19 / 0x18.
import struct
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
PL = 0x800CC6F0
def setup(name, target=1, frames=4, found=0x3A, ptype=2, c1c8=0, vtx=0x804A0000, d19=1, t=0.0, rate=0.25, prev=0, cur=0, hold=3,
          cache=0x80470000, ents=((0x80451000, 0x80450000), (0x80453000, 0x80452000)), noadv=0, rets='', tick=1, split=0):
    i = 1 if found == 0x3A else 0
    pk = {PL + 4: ptype << 24, PL + 0x260: 0x80490000, PL + 0x1C8: c1c8 << 24, PL + 0x28C: vtx, 0x800BEDE0: 0,
          0x800D1DC0 + 4 * ptype: d19, 0x800D1DC0 + 4 * found: d19, 0x800C4440 + 4 * ptype: 0x80460000, 0x800C4440 + 4 * found: 0x80460000,
          0x80460000: 0, 0x80460004: 0x20, 0x800DD890 + 4 * i: cache, 0x800BEEE0: noadv << 24, 0x800BEE04: tick,
          0x80490000: f(t), 0x80490004: f(rate), 0x80490008: prev << 24 | cur << 16 | hold << 8}
    if split: pk[0x800D1DC0 + 4 * ptype] = 0; pk[0x800C4440 + 4 * ptype] = 0x80460100
    ty = 0x3A if i else 0
    a = 0x800C4730 + ((ty * 2) & ~3)
    pk[a] = (2 << 16) if (ty * 2) % 4 == 0 else 2
    if cache:
        pk[cache] = 0x80470100; pk[cache + 4] = 0x80470200
        for j, (h0, h1) in enumerate(ents):
            base = 0x80470100 + 0x100 * j
            for s in range(8): pk[base + 8 * s] = 0; pk[base + 8 * s + 4] = 0
            pk[base + 8 * prev] = h0 if prev != 0xFF else 0; pk[base + 8 * cur] = h1 if cur != 0xFF else 0
            if target < 8 and target != cur: pk[base + 8 * target] = h1
    pks = ','.join('%08X=%s' % (k, v if isinstance(v, str) else '%08X' % v) for k, v in pk.items())
    r = '15084E08=%X' % found + (',' + rets if rets else '')
    print('%s ! 0=%X,1=%X,2=0 ! %s ! %s' % (name, target, frames & 0xFFFFFFFF, pks, r))
setup('new'); setup('new0', found=0); setup('same0', cur=1, hold=0); setup('same2', cur=1, prev=0, t=0.9, hold=2)
setup('done', cur=1, t=1.0, hold=2); setup('fr0', frames=0); setup('frneg', frames=-3); setup('curff', cur=0xFF, prev=2)
setup('noadv', noadv=1, cur=1, t=0.5, hold=1); setup('nofound', found=5)
setup('s1c8', c1c8=1, vtx=0, cur=1, t=0.9); setup('s1c8n', c1c8=1, vtx=0, cur=2, prev=0); setup('s1c8ff', c1c8=1, vtx=0, cur=0xFF)
setup('s1c8d', c1c8=1, d19=0, cur=3); setup('m1c8', c1c8=1, ptype=5); setup('d19z', d19=0); setup('vtx0', vtx=0)
setup('alloc', cache=0, rets='10003E90=80440000;80440100;80440200,1502B8B8=80450000')
setup('allocf', cache=0, rets='10003E90=80440000;80440100;0'); setup('allocz', cache=0, rets='10003E90=0')
setup('ldcur', ents=((0x80451000, 0), (0x80453000, 0)), rets='1502B8B8=80450000')
setup('ldcurf', ents=((0x80451000, 0), (0x80453000, 0)), rets='1502B8B8=0')
setup('ldprev', cur=1, ents=((0, 0x80450000), (0, 0x80452000)), rets='1502B8B8=80451000')
setup('ldprevf', cur=1, ents=((0, 0x80450000), (0, 0x80452000)), rets='1502B8B8=0')
setup('tick3', tick=3); setup('m1c8b', c1c8=1, ptype=5, split=1)
