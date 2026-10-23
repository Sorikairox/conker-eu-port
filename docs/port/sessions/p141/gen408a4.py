#!/usr/bin/env python3
# P141: setups for func_151408A4 (particle_glow_update). Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
import struct
def F(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
OBJ = 0x80490000; E = OBJ + 0x110; VIEW = 0x804A0000; CAM = 0x804B0000; VERT = 0x804C0000; LINK = 0x804D0000; BUF = 0x804E0000
CEC, B34, D6310 = '1514525C', '151450A4', '151D6310'
def setup(name, pl=0, kind=-1, flags=0x12, src=(100., 50., 200.), dirp=(100., 50., 900.), cam=(400., 120., 600.),
          scr=(100., 80.), vis=1, reload=1, link=1, e=None, z=(0x1000, 0x7FFC), bufnull=False, oz=0.5, oinv=1.0,
          kret=1, view=(0., 240., 0., 320.), inten=0x80, s44=0x1FF, s4C=0x1FF, sel=0, s54=0, s5C=0):
    p = {}
    def w(a, v): p[a] = v
    w(OBJ + 0x168, ((kind & 0xFF) << 16))
    w(OBJ + 0x58, flags)
    w(OBJ + 0x28, 0x000000C0)  # +0x2B = 0xC0
    for i, v in enumerate(src): w(OBJ + 0x34 + 4 * i, int(F(v), 16))
    for i, v in enumerate(dirp): w(OBJ + 0x40 + 4 * i, int(F(v), 16))
    for i in range(4): w(OBJ + 0x100 + 4 * i, BUF + 0x100 * i)
    ev = e or {0: 60., 4: 40., 8: 20., 0xC: 10., 0x10: 0.8, 0x14: 0.2, 0x18: 0.9, 0x1C: 0.3, 0x20: 0.0004, 0x48: 1.5}
    for k, v in ev.items(): w(E + k, int(F(v), 16))
    w(E + 0x44, LINK if link else 0)
    w(E + 0x4C, (z[0] << 16) | z[1]); w(E + 0x50, (z[1] << 16) | z[0])
    w(E + 0x54, inten * 0x01010101)
    w(0x800BEA48, VIEW); w(0x800BEDE0, sel << 24)
    for q in range(4):
        b = VIEW + 0x180 * q
        w(b + 0x24, int(F(view[0]), 16)); w(b + 0x28, int(F(view[1]), 16)); w(b + 0x2C, int(F(view[2]), 16)); w(b + 0x30, int(F(view[3]), 16))
        w(b + 0x44, (s44 << 16) | 0); w(b + 0x4C, (s4C << 16) | 0); w(b + 0x54, (s54 << 16) | 0); w(b + 0x5C, (s5C << 16) | 0)
    for i, v in enumerate(cam): w(CAM + 4 * i, int(F(v), 16))
    poke = ','.join('%08X=%08X' % (a, v) for a, v in sorted(p.items()))
    ret = '%s=%X,%s=%X,%s=0' % (CEC, vis, B34, CAM, D6310)
    if kind != -1:
        tab = ['15102E2C', '151C9C8C', '15141D88'][kind]
        ret += ',%s=%X' % (tab, kret)
    outa = '%s=1:%s;%s' % (CEC, F(scr[0]), F(scr[1]))
    outw = '%s=2:%s/4:%s,%s=3:%X' % (CEC, F(oz), F(oinv), D6310, 0 if bufnull else VERT)
    outb = '%s=4:%X' % (D6310, reload)
    return '%s ! 0=%X,1=%X ! %s ! %s ! ! %s ! %s ! %s' % (name, OBJ, pl, poke, ret, outa, outw, outb)
S = [
 setup('base'), setup('pl1', pl=1), setup('pl3', pl=3), setup('noreload', reload=0), setup('nolink', link=0),
 setup('noocc', flags=0x2), setup('normed', flags=0x16), setup('zero_dir', dirp=(100., 50., 200.)),
 setup('noflag2', flags=0x10), setup('invis', vis=0), setup('bufnull', bufnull=True),
 setup('scr_left', scr=(-5., 80.)), setup('scr_right', scr=(330., 80.)), setup('scr_top', scr=(100., -3.)), setup('scr_bot', scr=(100., 250.)),
 setup('behind', cam=(100., 50., -300.)), setup('behind_ok', cam=(100., 50., -300.), flags=0x10012),
 setup('above', cam=(100., 500., 200.)), setup('above_x', cam=(100.00005, 500., 200.00005)),
 setup('far', cam=(4000., 100., 4000.)), setup('hidden', z=(0x0010, 0x0010)), setup('visible', z=(0xE000, 0xFFFC), oz=0.1),
 setup('edge', z=(0x7FF0, 0x7FF0), oz=0.9, oinv=1.2), setup('inten_hi', inten=0xFF), setup('inten_lo', inten=0x03),
 setup('kind0_ok', kind=0), setup('kind0_no', kind=0, kret=0), setup('kind2_ok', kind=2), setup('kind1_ok', kind=1),
 setup('side', cam=(-500., 300., 150.), src=(10., 20., 30.), dirp=(-200., 300., 100.)),
 setup('negscale', e={0: 30., 4: 50., 8: 70., 0xC: 5., 0x10: 0.3, 0x14: 0.6, 0x18: 0.1, 0x1C: 0.95, 0x20: 0.0002, 0x48: 2.0}),
 setup('pl2_view', pl=2, s44=0x0100, s4C=0x0200, z=(0x2000, 0x3000)),
 setup('scr_edge', scr=(0., 80.)), setup('r2_small', cam=(100., 500., 200.005)), setup('fade_low', cam=(1600., 50., 1800.)),
 setup('sel1', sel=1, s54=0x0123, s5C=0x0456, z=(0x2000, 0x2000)), setup('occ_edge', oz=0.0, s44=0, s4C=897, z=(0x6004, 0x6004)),
 setup('occ_edge1', oz=0.0, s44=0, s4C=896, z=(0x6004, 0x6004)),
]
print('\n'.join(S))
