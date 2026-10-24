#!/usr/bin/env python3
# P226: setups for func_151ECE00 (barrel_menu_draw). ARG 0 = gdl 80480000. D_80090174 -> 80450000 (+0 slide, +8 fade,
# +0xC vel f32, +0x2C page, +0x40 mode, +0x41 sel). keys: func_151EDBE8 jal 151EDBE8 (RET gdl sequence), cosf 15047EF0 /
# sinf 15048050 (RETF), func_151E2C88 151E2C88 (RET count, OUTA scores), func_151EA90C 151EA90C (RET).
# Knob DIFFTEST_ARGMEM=151EDBE8=1:4 compares D_80090410 (the sprite pointer) at every draw call.
F = {0: '00000000', 0.1: '3DCCCCCD', 0.3: '3E99999A', 0.4: '3ECCCCCD', 0.5: '3F000000', 0.6: '3F19999A', 0.7: '3F333333',
     1.0: '3F800000', -1.0: 'BF800000', 0.2: '3E4CCCCD', 0.9: '3F666666', 0.85: '3F59999A'}
def b4(*b): return '%02X%02X%02X%02X' % tuple(x & 0xFF for x in b)
GDL = ';'.join('%08X' % (0x80481000 + 0x100 * i) for i in range(24))
COS = '15047EF0=3F800000;3F19999A;3E4CCCCD;BE4CCCCD;BF19999A;BF800000;BE4CCCCD;3F000000'
def setup(name, slide=0.7, fade=0.6, vel=0, page=4, mode=0, sel=2, pg=1, banners=(1, 1, 1, 1, 1), ring=0, cc=0,
          bedcc=0x25, ec4=0x80, ec5=0xC0, nq=2, q=(0, 2, -1, -1), chars=(3, 5, 6, 7), fd0=(1, 1, 0, 0),
          fill=(0x10, 0xFF, 0, 0x80), be9e4=2, nsc=2, sin='3F000000', cos=COS):
    p = {0x80090174: '80450000', 0x80450000: F[slide], 0x80450008: F[fade], 0x8045000C: F[vel],
         0x8045002C: b4(page, 0, 0, 0), 0x80450040: b4(mode, sel, 0, 0), 0x800904A8: b4(pg, 0, 0, 0),
         0x800E10B8: b4(*fill), 0x800E0EC4: b4(ec4, ec5, 0, 0), 0x80090188: F[ring], 0x800901CC: b4(cc, 0, 0, 0),
         0x800BEDCC: '%08X' % bedcc, 0x800901E0: b4(nq, 0, 0, 0), 0x800901E4: b4(*q), 0x800E0FC0: b4(*chars),
         0x800BEE04: '%08X' % be9e4, 0x80090410: '00000000'}
    for i in range(5):
        p[0x80090488 + 4 * i] = '%08X' % (0x80460000 + 0x100 * i if banners[i] else 0)
        p[0x800904AC + 4 * i] = '%08X' % (0x80470000 + 0x100 * i)
    for i in range(4):
        p[0x800E0FD0 + 4 * i] = '%08X' % (0x80490000 + 0x200 * i if fd0[i] else 0)
    poke = ','.join('%08X=%s' % kv for kv in sorted(p.items()))
    ret = '151EDBE8=%s,151EA90C=80488000,151E2C88=%X' % (GDL, nsc)
    print('%s ! 0=80480000 ! %s ! %s ! %s,15048050=%s ! 151E2C88=0:4;7;9;B ! ! !' % (name, poke, ret, cos, sin))
setup('m0_ring')
setup('m0_ring_rot', ring=0.3, sel=0)
setup('m0_ring_sel4', sel=4)
setup('m0_ring_cc', cc=1)
setup('m0_ring_bedcc', bedcc=0x30, ec4=0xFF, ec5=0xFF)
setup('m0_ring_bedcc2', bedcc=0x1F, ec4=0x40, ec5=0xFF)
setup('m0_fade_low', fade=0.4)
setup('m0_fade_half', fade=0.5)
setup('m0_page3', page=3)
setup('m0_fade0', fade=0, vel=0, page=0, slide=0.5)
setup('page0_velneg', fade=0.1, vel=-1.0, page=0, pg=2)
setup('page0_velpos', fade=0.1, vel=0.5, page=0, pg=2)
setup('page2', fade=0.1, vel=0.5, page=2, pg=1, slide=0.9)
setup('page2_pg0', fade=0.1, vel=0.5, page=2, pg=0, slide=0.2)
setup('page_banner4', fade=0.2, vel=0.5, page=1, pg=4, slide=1.0)
setup('banner_null', fade=0.1, vel=0.5, page=1, pg=1, banners=(1, 0, 1, 1, 1))
setup('fade_big', fade=1.0, page=1)
setup('slide_half', slide=0.5, fade=0.1, vel=0.5, page=1)
setup('m3', mode=3, page=1)
setup('m5', mode=5, page=1, fade=0.1)
setup('m4_4', mode=4, page=1, fade=0.1)
setup('m4_2', mode=4, page=7, fade=0.1)
setup('m4_fd0null', mode=4, page=1, fade=0.1, fd0=(0, 1, 0, 0))
setup('m4_noscore', mode=4, page=1, fade=0.1, nsc=0)
setup('m4_1score', mode=4, page=1, fade=0.1, nsc=1, q=(1, 2, -1, -1))
setup('m4_clamp', mode=4, page=1, fade=0.1, be9e4=0x40, fill=(0x10, 0xFE, 0x01, 0x80))
setup('m4_queue', mode=4, page=1, fade=0.1, nq=3, q=(3, 1, 2, -1), fd0=(1, 0, 0, 1), fill=(0x10, 0x20, 0xFF, 0xFF))
setup('m4_empty', mode=4, page=1, fade=0.1, nq=0, fill=(0, 0, 0, 0), ec5=0x7F, bedcc=0x11, sin='BF000000')
setup('page0_vel0', fade=0.1, vel=0, page=0, pg=2)
setup('fade_085', fade=0.85, page=1)
setup('m0_ring_eq', cos='15047EF0=3F800000;3E4CCCCD;3E4CCCCD;BE4CCCCD;BE4CCCCD;BF800000;BF800000;3F000000')
setup('m0_ring_b20', bedcc=0x20, ec4=0xFF, ec5=0xFF)
setup('m4_dup', mode=4, page=1, fade=0.1, nq=3, q=(2, 0, 2, -1), fd0=(1, 0, 0, 0), fill=(0x10, 0x20, 0x30, 0xFF))
setup('m4_slot0', mode=4, page=1, fade=0.1, fill=(0xFF, 0x20, 0x30, 0x40), q=(1, 2, -1, -1))
setup('m4_full', mode=4, page=1, fade=0.1, ec5=0xFF)
