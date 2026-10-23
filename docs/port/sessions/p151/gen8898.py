# P151: setups for func_15058898 (object at 0x80480000; D_800CC2D0 EU 0x800CC6F0, players 0x32C apart)
import struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
O = 0x80480000; P = 0x800CC6F0
def setup(name, f8, id=0x10, u5=0, state=1, pos=(100., 50., 200.), old=(90., 50., 190.), u28=0., speed=10., f180=60.,
          p13C=0, p13D=0, p127=0, p24E=0, p255=0, p256=0, stun=0, p103=0, p124=3, p2CC=0, u224=0xFF80, heading=0x1234,
          pf8=(), a44=0, floor=55., fbc8=33., moved=True, a630=0x4000, dadc=0xFF, aim=(0x56, 0x78), arg1=7., movez=False, movex=True, p102=0):
    pk = {O: state, O + 4: (id << 24) | (u5 << 16), O + 0x28: fb(u28), O + 0x3C: fb(speed), O + 0x74: heading,
          O + 0x78: 0x11112222, O + 0xF8: f8, O + 0xF4: 0x00000001, O + 0x100: p103 | (p102 << 8), O + 0x104: stun << 24,
          O + 0x124: (p124 << 24) | p127, O + 0x13C: (p13C << 24) | (p13D << 16), O + 0x180: fb(f180),
          O + 0x188: 0x55, O + 0x224: u224 << 16, O + 0x24C: p24E << 8, O + 0x254: (p255 << 16) | (p256 << 8),
          O + 0x2CC: p2CC, O + 0x218: 0x80470000, O + 0x230: 0}
    for k in range(3):
        pk[O + 0x14 + 4 * k] = fb(pos[k]); pk[O + 0x2C + 4 * k] = fb(old[k])
    for i, v in pf8: pk[P + i * 0x32C + 0xF8] = v
    pks = ','.join('%X=%s' % (a, v if isinstance(v, str) else '%08X' % v) for a, v in pk.items())
    ret = '150A44A4=%X,1505A9B0=%X,1505DE88=%X,1507BEE8=80490000' % (a44, a630, dadc)
    retf = '1510FBC8=%s' % fb(fbc8)
    outw = '150A44A4=4:%s,1510EE3C=2:%s' % (fb(floor), fb(floor))
    mv = []
    if moved and movex: mv.append('@80480014:%s' % fb(pos[0] - 5.))
    if moved and movez: mv.append('@8048001C:%s' % fb(pos[2] + 3.))
    if mv: outw += ',15044670=' + '/'.join(mv)
    outb = '1505DE88=1:%02X;%02X' % aim
    print(' ! '.join([name, '0=80480000,1=%s' % fb(arg1), pks, ret, retf, '', outw, outb]))
setup('frozen', 0x8000)
setup('frozen7', 0x8000, u5=7)
setup('fixed', 0x200000)
setup('fixed_pos', 0x200000, u224=0x0123)
setup('plain', 0)
setup('plain8', 8)
setup('plain_big', 0x04000008)
setup('solid_hit', 2 | 8, a44=1)
setup('solid_hit_no8', 2, a44=1)
setup('solid_miss', 2 | 8, a44=0)
setup('owner0_solid', 8, p13C=100, pf8=[(0, 2)], a44=1)
setup('owner0_nosolid', 8, p13C=100, pf8=[(0, 0)], a44=1)
setup('owner1', 8, p13C=101, pf8=[(1, 2)], a44=1)
setup('wall_nomove', 4, moved=False)
setup('wall_move', 4)
setup('wall_move8', 4 | 8 | 0x04000000)
setup('wall_13D', 4, p13D=1)
setup('wall_skip', 4, p127=0xFF, old=(100., 55., 200.), pos=(100., 50., 200.), floor=55.)
setup('wall_skip_x', 4, p127=0xFF, old=(101., 55., 200.), pos=(100., 50., 200.), floor=55.)
setup('wall_skip_y', 4, p127=0xFF, old=(100., 56., 200.), pos=(100., 50., 200.), floor=55.)
setup('wall_skip_28', 4, p127=0xFF, old=(100., 55., 200.), pos=(100., 50., 200.), floor=55., u28=1.)
setup('wall_skip_z', 4, p127=0xFF, old=(100., 55., 201.), pos=(100., 50., 200.), floor=55.)
setup('wall_1B', 4, id=0x1B)
setup('wall_7E', 4, id=0x7E)
setup('owner_wall', 0, p13C=102, pf8=[(2, 4)])
setup('owner_wall9A', 0, p13C=102, pf8=[(2, 4)], id=0x9A)
setup('owner_nowall', 4, p13C=102, pf8=[(2, 0)])
setup('carry', 4, p24E=3)
setup('carryC', 4, p24E=3, id=0xC)
setup('bounce', 0x1004)
setup('bounce21', 0x1004, state=0x21)
setup('bounce26', 0x1004, state=0x26)
setup('bounce4', 0x1004, state=4)
setup('bounce4_aim', 0x1004, state=4, p103=1)
setup('bounce4_aimhit', 0x1004, state=4, p103=1, dadc=2)
setup('bounce4_aim0', 0x1004, state=4, p103=1, p124=0, dadc=2)
setup('bounce_snd', 0x1004, p2CC=0x77, speed=40.)
setup('bounce_snd_slow', 0x1004, p2CC=0x77, speed=10.)
setup('bounce_snd_eq', 0x1004, state=0x21, p2CC=0x77, speed=5.5)
setup('bounce_ang', 0x1004, a630=0xC123, heading=0x8001)
setup('fall', 0, p255=2, p256=1, f180=100., floor=50.)
setup('fall_edge', 0, p255=2, p256=6, f180=100., floor=51.)
setup('fall_edge2', 0, p255=2, p256=6, f180=100., floor=52.)
setup('fall_stun', 0, p255=2, p256=1, f180=100., floor=50., stun=1)
setup('fall_none', 0, p255=0, p256=1, f180=100., floor=50.)
setup('fall_wall', 0x1004, p255=5, p256=0, f180=100., floor=50., state=4)
setup('wall_movez', 4, movex=False, movez=True)
setup('bounce_xz', 0x1004, movez=True)
setup('bounce4_102', 0x1004, state=4, p102=0xAB)
