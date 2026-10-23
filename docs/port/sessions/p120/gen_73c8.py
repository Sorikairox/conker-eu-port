#!/usr/bin/env python3
# P120: knob setups for func_151E73C8 (menu camera / carousel). The menu .data tables are poked with their ROM values
# (DIFFTEST_ROMDATA=1 would drop the record pokes: .data pokes apply on even trials only). Run with DIFFTEST_ARGMEM=15049AD0=0:64 (compares the spline point arrays).
# fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
import struct, itertools
def fw(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
REC = 0x80480000; CAM = 0x80480400; OBJ3D0 = 0x804A0000; GRAPH = 0x804B0000
NONE = 'FFFFFFFF'
TABLES = [(0x800902F0, '0102030405060000'), (0x800902F8, '3c0b43963d4ccccd3cf5c28f3cf5c28f3cf5c28f3cf5c28f'),
          (0x80090310, '00000000000000003ef0a3d83f0000003f0000003f000000'), (0x80090328, '1e002d282d2d0000'),
          (0x80090330, '1e64503c3c3c0000'), (0x80090338, '1112131415161718'),
          (0x80090340, '3c449ba63d4ccccd3d4ccccd3d4ccccd3d4ccccd3d4ccccd3d4ccccd3d4ccccd'), (0x80090360, '01ff04060803ffffffff0905')]
CHAINS = {   # node id -> 5 links (+9..+13); func_150871B8 returns 2 (ids[0] = ids[1] = 2)
    'c2': {2: [0xFF] * 5},
    'c3': {2: [0xFF, 3, 0xFF, 0xFF, 0xFF], 3: [0xFF] * 5},
    'c4': {2: [3, 0xFF, 0xFF, 0xFF, 0xFF], 3: [0xFF, 2, 0xFF, 4, 0xFF], 4: [0xFF] * 5},
    'c5': {2: [3, 0xFF, 0xFF, 0xFF, 0xFF], 3: [2, 4, 0xFF, 0xFF, 0xFF], 4: [3, 0xFF, 0xFF, 0xFF, 5], 5: [0xFF] * 5},
    'c6': {2: [0x90, 0xFF, 0xFF, 0xFF, 0xFF], 0x90: [2, 0xFF, 0xFF, 0xFF, 0xFF]},   # node >= 0x80 (u8 index; a link back to it would loop: s8 compare)
    'cneg': {-16: [0xFF] * 5},
}
def chain_pokes(c, base_id=2):
    out = []
    for n, l in CHAINS[c].items():
        a = GRAPH + n * 16
        out.append('%08X=%02X%02X%02X%02X' % (a + 8, 0, l[0], l[1], l[2]))
        out.append('%08X=%02X%02X%02X%02X' % (a + 12, l[3], l[4], 0, 0))
    return out
def setup(name, x0=0.0, x4=0.0, fade=0.0, xC=0.0, x10=0.0, inp=0, x2A=0, x2B=0, tp=0, x2D=0, menu=0, x43=0, x44=0,
          chain='c4', dt=2, damp=1.0, obj=0x804C0000, sins=(0.5, 0.25), rid=2):
    p = ['80090174=%08X' % REC, '%08X=%s' % (REC, fw(x0)), '%08X=%s' % (REC + 4, fw(x4)), '%08X=%s' % (REC + 8, fw(fade)),
         '%08X=%s' % (REC + 0xC, fw(xC)), '%08X=%s' % (REC + 0x10, fw(x10)), '%08X=%s' % (REC + 0x14, fw(3.0)),
         '%08X=%s' % (REC + 0x18, fw(-5.0)), '%08X=%s' % (REC + 0x1C, fw(7.0)), '%08X=%04X0000' % (REC + 0x20, inp),
         '%08X=0000%02X%02X' % (REC + 0x28, x2A & 0xFF, x2B & 0xFF), '%08X=%02X%02X0000' % (REC + 0x2C, tp & 0xFF, x2D & 0xFF),
         '%08X=0000%02X00' % (REC + 0x3C, menu), '%08X=000000%02X' % (REC + 0x40, x43), '%08X=%02X000000' % (REC + 0x44, x44),
         '800DC420=%08X' % CAM, '%08X=%08X' % (CAM + 0x3D0, OBJ3D0), '800D2778=%08X' % GRAPH, '800BEE04=%08X' % dt,
         '80090170=%s' % fw(damp), '%08X=%s' % (CAM + 0x2F8, fw(11.0)), '%08X=%s' % (CAM + 0x2A4, fw(13.0))]
    p += chain_pokes(chain)
    for a, h in TABLES:
        p += ['%08X=%s' % (a + i, h[2 * i:2 * i + 8]) for i in range(0, len(h) // 2, 4)]
    ret = '150871B8=%X,15114F2C=%X' % (rid, obj)
    retf = '15048050=%s' % ';'.join(fw(s) for s in sins)
    vx = ';'.join(fw(1.0 + i) for i in range(12)); vy = ';'.join(fw(10.0 * (i + 2)) for i in range(12)); vz = ';'.join(fw(-3.0 * (i + 1)) for i in range(12))
    outw = '1508712C=1:%s/2:%s/3:%s' % (vx, vy, vz)
    return '%s ! 0=0 ! %s ! %s ! %s ! ! %s !' % (name, ','.join(p), ret, retf, outw)
L = []
for menu in (0, 1):
    m = 'm%d' % menu
    # slide (x4 != 0): crossing 1 (x2B wraps), crossing 0, mid
    for x0, x4, x2B in ((0.95, 0.05, 0), (0.95, 0.05, 5), (0.95, 0.05, 7), (0.05, -0.05, 2), (0.4, 0.05, 1), (0.6, -0.05, 3)):
        L.append(setup('%s_slide_%g_%g_%d' % (m, x0, x4, x2B), x0=x0, x4=x4, x2B=x2B, menu=menu))
    # zooming / zoomed (xC or fade != 0)
    for inp in (0, 0x10, 0x20, 0x30):
        for x2A, x2B in ((0, 0), (0, 3), (1, 0), (2, 0), (1, 2)):
            for fade, xC in ((0.5, 0.0), (0.0, 0.05), (0.98, 0.05), (0.02, -0.05)):
                L.append(setup('%s_zoom_i%X_a%d_b%d_f%g_c%g' % (m, inp, x2A, x2B, fade, xC), fade=fade, xC=xC, inp=inp, x2A=x2A, x2B=x2B, menu=menu, tp=x2B))
    for tp, x44 in ((0, 1), (0, 0), (1, 1)):
        L.append(setup('%s_zoomout_tp%d_x44_%d' % (m, tp, x44), fade=0.02, xC=-0.05, tp=tp, x44=x44, menu=menu))
    # at rest
    for inp in (0, 4, 8, 0xC, 0x10, 0x14, 0x20):
        for x2B, x43 in ((0, 0), (0, 1), (3, 0), (-1, 0), (9, 1), (5, 0)):
            L.append(setup('%s_rest_i%X_b%d_x43_%d' % (m, inp, x2B, x43), inp=inp, x2B=x2B, x43=x43, menu=menu))
    # path chains with zoom > 0
    for ch in [c for c in CHAINS if c != 'cneg']:
        for sins in ((0.5, 0.25), (0.5, 0.99), (0.5, 0.0), (0.5, 1.0)):
            L.append(setup('%s_path_%s_s%g' % (m, ch, sins[1]), fade=0.5, menu=menu, chain=ch, sins=sins, x2B=2, tp=2))
    L.append(setup('%s_path_neg_id' % m, fade=0.5, menu=menu, chain='cneg', rid=0xF0))
    for x2B in (0, 2):
        L.append(setup('%s_zoom_exact1_b%d' % (m, x2B), fade=0.5, xC=0.25, x2B=x2B, menu=menu))
    # look-at mirror / offset modes
    for x2A in (0, 1, 2, 3):
        for fade in (0.0, 0.1, 0.3, 1.0):
            for inp, x10, x4 in ((0x20, 0.0, 0.0), (0x20, 0.5, 0.0), (0x20, 0.0, 0.05), (0, 0.0, 0.0)):
                for x2D in (1, 3, 7):
                    if menu == 0 and x2D != 3: continue
                    L.append(setup('%s_mode_a%d_f%g_i%X_x10_%g_x4_%g_d%d' % (m, x2A, fade, inp, x10, x4, x2D), x2A=x2A, fade=fade, inp=inp, x10=x10, x4=x4, x2D=x2D, menu=menu))
    # toggle (fade >= 1, x2B 0), titlePage from x0 > 0.5 / wrap, main menu mapping
    for x2B in (0, 1):
        L.append(setup('%s_toggle_b%d' % (m, x2B), fade=1.0, x2B=x2B, menu=menu))
    for x0, x2B in ((0.6, 7), (0.6, 5), (0.4, 7), (0.5, 0)):
        L.append(setup('%s_tp_x0_%g_b%d' % (m, x0, x2B), x0=x0, x4=0.0, x2B=x2B, menu=menu, xC=0.0))
    # title objects: damping < 1, xC < 0 / > 0, NULL object
    for tp in range(6):
        for xC, damp in ((0.05, 1.0), (-0.05, 1.0), (0.0, 0.5), (0.0, 1.0)):
            L.append(setup('%s_obj_tp%d_c%g_d%g' % (m, tp, xC, damp), fade=0.4, xC=xC, damp=damp, tp=tp, x2B=tp, menu=menu))
    L.append(setup('%s_nullobj' % m, fade=0.4, xC=0.05, obj=0, menu=menu))
print('\n'.join(L))
