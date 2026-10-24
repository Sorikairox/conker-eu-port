#!/usr/bin/env python3
# P218: setups for func_1508E080 (rail_weapons_update). Rail state D_800D27D0 (EU 800D27D0) -> R = 80500000;
# objects D_800CC2D0 (EU 800CC6F0, stride 0x32C), ext (+0x31C) of racer i at 80480000 + 0x200 i; frame time
# D_800BE9E4 (EU 800BEE04) = 8. Keys: func_1508EBDC 1508EBDC, func_15034118 15034118, func_151149AC 15114F2C,
# func_150871B8 150871B8, func_1508712C 1508712C (OUTA x / y / z), func_150ADA68 150ADF48 (RETF).
R = 0x80500000; OBJ = 0x800CC6F0
def obj(i, off): return OBJ + 0x32C * i + off
def ext(i): return 0x80480000 + 0x200 * i
def base(n=1, mode=0, ea4=0, frame=8):
    p = {0x800D27D0: R, R + 0x10: n, R + 0x16BC: mode << 16, R + 0xEA4: ea4, 0x800BEE04: frame}
    for i in range(5):
        p[obj(i, 0x31C)] = ext(i)
        p[obj(i, 0x128)] = 0          # +0x128 byte 0
        p[obj(i, 0)] = 0              # first word (scan of objects beyond the racers)
    return p
def b(p, a, v, sh):   # byte v at byte address a (word poke, other bytes 0)
    w = a & ~3; p[w] = p.get(w, 0) | (v << (8 * (3 - (a & 3))))
OUTA712 = '1508712C=1:42C80000/2:43480000/3:C2C80000'
def items(*k):
    return ',15034118=1:' + ';'.join('%X' % (0x80470000 + 0x100 * j) for j in range(len(k)))
S = []
def add(name, p, ret='', retf='', outa=OUTA712):
    S.append('%s ! ! %s ! %s ! %s ! %s ! !' % (name, ','.join('%X=%X' % kv for kv in sorted(p.items())), ret, retf, outa))
# ---- pass 1 ----
def racer(p, i, have=0, ammo=0, want=0, slot=-1, e11a=0, e128=0):
    e = ext(i); b(p, e + 0x75, have, 0); b(p, e + 0x19B, ammo, 0); b(p, e + 0x11A, e11a, 0); b(p, e + 0x128, e128, 0)
    p[R + 0xFF0 + 4 * i] = want & 0xFFFFFFFF; p[R + 0xEB0 + 4 * i] = slot & 0xFFFFFFFF
def itemkinds(p, *k):
    for j, v in enumerate(k): b(p, 0x80470000 + 0x100 * j + 6, v, 0)
p = base(); racer(p, 0, have=5, want=0x10); p[R + 0x1170] = 0x44
add('p1chg', p, '1508EBDC=1007;1003;FFFFFFFF,15034118=0')
p = base(); racer(p, 0, have=5, want=0, slot=2); p[R + 0x1174 + 8] = 0x20; p[R + 0x1170] = 0x44
add('p1slot', p, '1508EBDC=FFFFFFFF;1000;FFFFFFFF,15034118=0')
p = base(); racer(p, 0, have=0x20, want=0x457)
add('p1none', p, '1508EBDC=FFFFFFFF;FFFFFFFF;FFFFFFFF,15034118=0')
p = base(); racer(p, 0, have=3, want=0x457)
add('p1none3', p, '1508EBDC=1;1;FFFFFFFF,15034118=0')
p = base(mode=0xB8); racer(p, 0, e128=0xA1, want=0, slot=-1); p[R + 0x1170] = 0x80
add('p1b8', p, '1508EBDC=FFFFFFFF;500,15034118=0')
p = base(mode=0xB8); racer(p, 0, e128=0x80, want=1)
add('p1b8b', p, '1508EBDC=101D;1002,15034118=0')
p = base(mode=0xB8); racer(p, 0, e128=0x30, want=0x10)
add('p1b8c', p, '1508EBDC=1;1,15034118=0')
p = base(mode=0xB9); racer(p, 0, have=1, want=2); b(p, obj(0, 0x128), 1, 0)
add('p1b9skip', p, '1508EBDC=1;1;1,15034118=0')
p = base(mode=0xB9); racer(p, 0, have=1, want=2); racer(p, 1, have=1, want=0x457)
add('p1b9two', p, '1508EBDC=1;1;1D;1;1,15034118=0')
p = base(); racer(p, 0, have=0x3A, ammo=6, e11a=2)
add('p1ammo', p, '1508EBDC=1D,15034118=0')
p = base(); racer(p, 0, have=0x26, ammo=2, e11a=2)
add('p1ammo2', p, '1508EBDC=55,15034118=0')
p = base(); racer(p, 0, have=0x10, want=0x10, e11a=2); itemkinds(p, 0x1E, 0x40, 0x1D)
add('p1items', p, '1508EBDC=101D,15034118=3', outa=OUTA712 + items(1, 2, 3))
p = base(); racer(p, 0, have=0x10, want=0x10, e11a=2); itemkinds(p, 0x72, 0x07, 0x2A, 0x22, 0x2D, 0x73, 0x76, 0x77, 0x78)
add('p1keep', p, '1508EBDC=1033,15034118=9', outa=OUTA712 + items(*range(9)))
p = base(); racer(p, 0, have=0x10, want=0x10, e11a=2); itemkinds(p, 0x1E, 0x2C, 0x64, 0x40)
add('p1neg', p, '1508EBDC=FFFFFFFF,15034118=4', outa=OUTA712 + items(1, 2, 3, 4))
p = base(); racer(p, 0, have=0x20, want=0x20, e11a=2); itemkinds(p, 0x40)
add('p1is20', p, '1508EBDC=1033,15034118=1', outa=OUTA712 + items(1))
p = base(); racer(p, 0, have=0x10, want=0x10)
p[obj(1, 0)] = 1; b(p, obj(1, 0x65), 1, 0); b(p, obj(1, 4), 0x6D, 0)
p[obj(2, 0)] = 0; b(p, obj(2, 0x65), 1, 0); b(p, obj(2, 4), 0x6E, 0)
p[obj(3, 0)] = 1; b(p, obj(3, 0x65), 1, 0); b(p, obj(3, 4), 0x6E, 0)
add('p1scan', p, '1508EBDC=10,15034118=0')
p = base(n=2); racer(p, 0, have=0x10, want=0x10); racer(p, 1, have=0x10, want=0x10); p[0x800876E0] = 0x01000000
add('p1cur1', p, '1508EBDC=10,15034118=0')
# P218 mutant survivors: bit 7 of +0x75, ammo levels 5 and 1 (boundaries)
p = base(); racer(p, 0, have=0x90, want=0x10)
add('p1bit7', p, '1508EBDC=1;1;FFFFFFFF,15034118=0')
p = base(); racer(p, 0, have=0x3A, ammo=5, want=0x10)
add('p1ammo5', p, '1508EBDC=1;1;FFFFFFFF,15034118=0')
p = base(); racer(p, 0, have=0x26, ammo=1, want=0x10)
add('p1ammo1', p, '1508EBDC=1;1;FFFFFFFF,15034118=0')
p = base(); racer(p, 0, have=0x10, want=0x10, e11a=1)
add('p1e11a1', p, '1508EBDC=1D,15034118=0')
p = base(); racer(p, 0, have=0x10, want=0x10, e11a=2)
add('p1i2e', p, '1508EBDC=2E,15034118=0')
p = base(); racer(p, 0, have=0x10, want=0x10, e11a=2); itemkinds(p, 0x72, 0x1D)
add('p1found', p, '1508EBDC=101D,15034118=2', outa=OUTA712 + items(1, 2))
p = base(); racer(p, 0, have=0x10, want=0x10)
p[obj(2, 0)] = 1; b(p, obj(2, 0x65), 1, 0); b(p, obj(2, 4), 0x6E, 0)
add('p1scan55', p, '1508EBDC=55,15034118=0')
p = base(); racer(p, 0, have=0x10, want=0x10)
p[obj(2, 0)] = 1; b(p, obj(2, 0x65), 1, 0); b(p, obj(2, 4), 0x6E, 0)
p[obj(3, 0)] = 1; b(p, obj(3, 0x65), 1, 0); b(p, obj(3, 4), 0x6E, 0)
add('p1scan2', p, '1508EBDC=10,15034118=0')
# ---- pass 2 (no racers) ----
def slot(p, i, hide=0, resp=0, flags=0, weapon=0, fixed=0, pick80=0, home=(1, 2, 3)):
    p[R + 0xEF0 + 4 * i] = 0x1200 + i; p[R + 0x12F4 + 4 * i] = hide & 0xFFFFFFFF; p[R + 0x1070 + 4 * i] = resp & 0xFFFFFFFF
    p[R + 0x11F4 + 4 * i] = flags; p[R + 0x1174 + 4 * i] = weapon; p[R + 0x1274 + 4 * i] = fixed
    for k, v in enumerate(home): p[R + 0x1374 + 0x80 * k + 4 * i] = v
    p[0x80490000 + 0x100 * i + 0x80] = pick80
def pts(p, n, used):
    p[R + 0xEA8] = n; p[R + 0xEAC] = 0x77
    for k in range(n): p[R + 0x10F0 + 4 * k] = used[k] & 0xFFFFFFFF; p[R + 0x14F4 + 4 * k] = 0x30 + k
PICK = '15114F2C=80490000;80490100'
p = base(n=0, ea4=1); slot(p, 0, hide=5, resp=0, fixed=2); pts(p, 4, [9, 9, 9, 9])
add('p2hide', p, PICK + ',150871B8=7')
p = base(n=0, ea4=1); slot(p, 0, hide=20, resp=3); pts(p, 4, [9, 9, 9, 9])
add('p2home', p, PICK + ',150871B8=7')
p = base(n=0, ea4=1); slot(p, 0, hide=0, resp=1, fixed=3); pts(p, 4, [9, 9, 9, 9])
add('p2fixed', p, PICK + ',150871B8=FFFFFFFF')
p = base(n=0, ea4=1); slot(p, 0, hide=0, resp=1, flags=1); pts(p, 4, [1, 3, 9, 9])
add('p2rand', p, PICK + ',150871B8=5', '150ADF48=3F000000;3F400000')
p = base(n=0, ea4=1); slot(p, 0, hide=0, resp=1, flags=4); pts(p, 4, [9, 9, 9, 9])
add('p2flag4', p, PICK + ',150871B8=5')
p = base(n=0, ea4=1); slot(p, 0, resp=-1); pts(p, 4, [9, 9, 9, 9])
add('p2neg', p, PICK + ',150871B8=5')
p = base(n=0, ea4=1); slot(p, 0, resp=5); pts(p, 4, [9, 9, 9, 9])
add('p2wait', p, PICK + ',150871B8=5')
p = base(n=0, ea4=2); slot(p, 0, resp=0, pick80=0); slot(p, 1, resp=0, pick80=0); pts(p, 4, [9, 9, 9, 9])
add('p2null', p, '15114F2C=0;80490100,150871B8=5')
p = base(n=0, mode=0xB8, ea4=1); slot(p, 0, resp=0, weapon=0x10, pick80=3); pts(p, 4, [9, 9, 9, 9]); b(p, ext(2) + 0x128, 0x10, 0)
add('p2take', p, PICK + ',150871B8=5')
p = base(n=0, mode=0xB8, ea4=1); slot(p, 0, resp=0, weapon=1, pick80=2, flags=2); pts(p, 4, [9, 9, 9, 9]); b(p, ext(1) + 0x128, 1, 0)
add('p2take1', p, PICK + ',150871B8=5')
p = base(n=0, mode=0xB8, ea4=1); slot(p, 0, resp=0, weapon=0x80, pick80=2); pts(p, 4, [9, 9, 9, 9]); b(p, ext(1) + 0x128, 0x80, 0)
add('p2take80', p, PICK + ',150871B8=5')
p = base(n=0, mode=0xB8, ea4=1); slot(p, 0, resp=0, weapon=0x80, pick80=2); pts(p, 4, [9, 9, 9, 9]); b(p, ext(1) + 0x128, 0x81, 0)
add('p2takeno', p, PICK + ',150871B8=5')
p = base(n=0, mode=0xB9, ea4=1); slot(p, 0, resp=0, weapon=0x10, pick80=4, flags=2); pts(p, 4, [9, 9, 9, 9])
add('p2b9', p, PICK + ',150871B8=5')
p = base(n=0, mode=0xB8, ea4=1); slot(p, 0, resp=0, weapon=0x8AE, pick80=3); pts(p, 4, [9, 9, 9, 9]); b(p, ext(2) + 0x19A, 5, 0)
add('p2ammo', p, PICK + ',150871B8=5')
p = base(n=0, ea4=1); slot(p, 0, resp=0, weapon=0x8AE, pick80=3); pts(p, 4, [9, 9, 9, 9]); b(p, ext(2) + 0x19A, 1, 0)
add('p2ammo1', p, PICK + ',150871B8=5')
p = base(n=0, ea4=1, frame=8); slot(p, 0, hide=8, resp=0, fixed=2); pts(p, 4, [9, 9, 9, 9])
add('p2hide0', p, PICK + ',150871B8=7')
p = base(n=0, ea4=1, frame=3); slot(p, 0, hide=3, resp=0, fixed=2); pts(p, 4, [9, 9, 9, 9])
add('p2hide3', p, PICK + ',150871B8=7')
p = base(n=0, ea4=1); slot(p, 0, resp=-1, weapon=0x10, pick80=3); pts(p, 4, [9, 9, 9, 9])
add('p2neg2', p, PICK + ',150871B8=5')
print('\n'.join(S))
