#!/usr/bin/env python3
# P93: knob setups for func_15035AF8 (object draw queue). idx 2 -> obj 0x800CCD48 (D_800CC2D0 EU 0x800CC6F0 + 2 * 0x32C)
O = 0x800CCD48
def setup(name, mode=1, istate=1, op=0x80, dist=0x300, cnt=3, top=0x01000000, hi=0, att=True, a48=0, slot=0, a34=0,
          cull=0, acc=1, ent='804B0000;804B0010;804B0020', att2=False, m1d4=0x80450000, a3=0x80, u74=1, e4=False):
    p = {0x800C4320: cnt << 24, O: istate, O + 4: 0x05000000 | op, O + 0x14: 0x41200000, O + 0x18: 0x41A00000,
         O + 0x1C: 0x41F00000, O + 0x38: 7, O + 0x74: u74 << 24, O + 0x1D4: m1d4, 0x800C42A8: 0x80460000,
         0x800C42AC: 0x80460000, 0x800C4298: 3, 0x800C429C: top, 0x800C3A08: hi << 8, 0x800DC420: 0x80470000,
         0x804702F8: 0x42C80000, 0x804702FC: 0x43480000, 0x80470300: 0x43960000, 0x800C4300: 0x80480000 if att else 0,
         0x800BEDE0: 0x01000000, 0x80480000: 0x07000000 | a3, 0x80480004: 0x200, 0x80480034: a34, 0x80480048: a48,
         0x8048004C: 0x804A1000, 0x80480050: slot, 0x80480054: 0x80481000 if att2 else 0, 0x804903F4: 0x03000000,
         0x80481000: 0x09000080, 0x80481054: 0}
    if e4: p.update({0x804B0004: 0xC8000000, 0x804B0014: 0xC8000000, 0x804B0024: 0xC8000000})
    if att2: p.update({0x80481000: 0x07000080, 0x80481004: 0x300, 0x80481050: 0x804A2000, 0x80481048: 0})
    poke = ','.join('%08X=%08X' % kv for kv in p.items())
    ret = '150ADE80=%X,150359B8=%s,15035A04=%X,1502DE10=4,15031360=%X,10003E90=804C0000' % (dist, ent, cull, acc)
    print('%s ! 0=%X,1=2,9=43000000 ! %s ! %s !  ! 1502D83C=1:11;22;33 ! 15031360=2:80455000 ! ' % (name, mode, poke, ret))
setup('base')
setup('fade', dist=0x500)
setup('far', dist=0x600)
setup('opaque', op=0xFF, dist=0x500)
setup('hi_near', hi=1, dist=0x2600)
setup('hi_fade', hi=1, dist=0x2700)
setup('hi_far', hi=1, dist=0x2800)
setup('op0', op=0)
setup('m0_s1', mode=0)
setup('m0_s2', mode=0, istate=2)
setup('m2', mode=2)
setup('nomodel', m1d4=0)
setup('full', top=0x00030000)
setup('cnt15', cnt=15)
setup('noent', ent='0')
setup('noent2', ent='804B0000;0')
setup('cull', cull=1)
setup('noatt', att=False)
setup('a3zero', a3=0)
setup('reject', acc=0)
setup('a48', a48=0x80490000)
setup('slot', slot=0x804A3000)
setup('a34', a34=1)
setup('two', att2=True, a48=0x80490000)
setup('two_slot', att2=True, slot=0x804A3000, a34=1)
# second round (mutant survivors): entry +4 bytes != 0 so the fade shows, unk74 == 7, arena exactly full
setup('e_fade', dist=0x500, e4=True)
setup('e_fade_hi', hi=1, dist=0x2700, e4=True)
setup('e_near', e4=True)
setup('e_opaque', op=0xFF, dist=0x500, e4=True)
setup('e_opFE', op=0xFE, dist=0x500, e4=True)
setup('u74_7', u74=7)
setup('u74_F', u74=0x1F)
setup('arena_edge', top=0x00040000)
setup('e_fade2', dist=0x4B5, e4=True)
# third round: distances where the truncated fade differs by one for the small mutants (computed in f32)
setup('d_4B1', dist=0x4B1, op=0xFF, e4=True)
setup('d_2649', hi=1, dist=0x2649, op=0xFF, e4=True)
setup('d_4C6', dist=0x4C6, op=0xFF, e4=True)
setup('d_4B3', dist=0x4B3, op=0xFF, e4=True)
