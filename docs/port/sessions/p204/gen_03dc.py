#!/usr/bin/env python3
# P204: setups for func_151A03DC (foot_trail_draw). t 80450000, points 80460000 (0x24 each), rec 80470000,
# vertex buffer via OUTW func_151D6310 a3 -> 80480000, gfx stubs (decoded jal keys) return 80490000.
import struct
def F(x): return struct.pack('>f', x)
GFX = ['15143394', '151430EC', '15143180', '15143260', '1513FA54', '1514352C']
def g(name, size=6, count=4, tail=1, head=5, side=6, u1e=0, live=(5.0, 7.0, 9.0), flags=0, f40=2, f41=0x30,
      f42=2, f43=0x50, t46=0x100, t4a=0x200, pts=None, vtxp='80480000', slot=3, rgb=(10, 20, 30), w38=12.0):
    mem = {}
    def put(a, b):
        for i, c in enumerate(b): mem[a + i] = c
    T, P, R = 0x80450000, 0x80460000, 0x80470000
    put(T + 0x10, F(live[0]) + F(live[1]) + F(live[2]))
    put(T + 0x1C, struct.pack('>HH', 0, u1e))
    put(T + 0x20, struct.pack('>i', side))
    put(T + 0x24, bytes([0, size, 0, 0]))
    put(T + 0x2C, struct.pack('>bbbb', count, tail, head, 0))
    put(T + 0x94, struct.pack('>II', P, R))
    put(R + 4, bytes([flags, 0, 0, 0]))
    put(R + 0x28, bytes([0, 0]) + bytes(rgb) + b'\0')
    put(R + 0x38, F(w38))
    put(R + 0x40, bytes([f40, f41, f42, f43]))
    put(R + 0x44, struct.pack('>hhhh', 0, t46, 0, t4a))
    if pts is None:
        pts = [(100.0 + 13 * i, 3.0 * i, 50.0 - 7 * i * i, 4.0 + i, 0x40 + 9 * i, 0x60 + 0x11 * i, 0x20 * i) for i in range(size)]
    for i, (x, z, y, w, al, fade, u) in enumerate(pts):
        put(P + 0x24 * i, F(x) + F(z) + F(y) + F(w) + struct.pack('>hhhhhh', al, 0, fade, u, 0, 0))
    words = {}
    for a, c in mem.items():
        words.setdefault(a & ~3, bytearray(4))
    for a in words:
        for i in range(4): words[a][i] = mem.get(a + i, 0)
    poke = ','.join('%08X=%s' % (a, words[a].hex().upper()) for a in sorted(words))
    ret = ','.join('%s=80490000' % k for k in GFX)
    print('%s ! 0=80450000,1=80490000,2=%X ! %s ! %s ! ! ! 151D6310=3:%s ! ' % (name, slot, poke, ret, vtxp))
print('# P204 func_151A03DC setups (gen_03dc.py)')
g('base')
g('few', count=1)
g('two', count=2, tail=2, head=4)
g('novtx', vtxp='00000000')
g('live', u1e=2)
g('live_r', u1e=2, side=7)
g('right', side=7)
g('other', side=5)
g('wrap', tail=4, head=2, count=4)
g('wrap0', tail=3, head=0, count=3)
g('full', tail=2, head=2, count=6)
g('fin', flags=2)
g('fin0', flags=2, f40=0)
g('finlong', flags=2, f40=9, f41=0xC0)
g('fout', flags=4)
g('fout0', flags=4, f42=0, tail=0, head=3, count=3)
g('foutlong', flags=4, f42=9, f43=0x70, tail=3, head=1)
g('both', flags=6, f40=3, f42=3, u1e=2)
g('tvwrap', t46=0x7F00, t4a=0x200)
g('tvwrapneg', t46=-0x7F10, t4a=-0x300)
g('tvneg', t46=-0x1234, t4a=0x100)
g('tvwrapodd', t46=0x7FF3, t4a=0x7FF0, side=7)
flat = [(100.0, 10.0, 0.0, 5.0, 0x80, 0xFF, 0x10 * i) for i in range(6)]
g('flat', pts=flat)
g('flatlive', pts=flat, u1e=2, live=(100.0, 30.0, 4.0))
g('samelive', pts=flat, u1e=2, live=(100.0, 10.0, 1.0))
g('tinylive', pts=flat, u1e=2, live=(100.00001, 10.00001, 1.0))
xs = [(100.0 + i * 0.5, 10.0, 0.0, 5.0, 0x80, 0xFF, 7) for i in range(6)]
g('samez', pts=xs)
zs = [(100.0, 10.0 + i * 2, 0.0, 5.0, 0x80, 0xFF, 7) for i in range(6)]
g('samex', pts=zs)
g('alpha_hi', pts=[(i * 40.0, -i * 30.0, 5.0, 8.0, 0x7FFF - i, -0x20 * i, -i) for i in range(6)])
g('neg', pts=[(-500.0 - i * 40.0, -i * 30.5, -50.0, -3.0, -0x40, 0x90, 0x1000) for i in range(6)], side=7)
g('big8', size=8, count=7, tail=6, head=5, flags=6, f40=4, f42=5, u1e=2)
# P204 survivor round: eps band, tiny step with a huge width, equal v span, negative wrap
g('dxeps', pts=[(100.0 + 0.0005 * i, 10.0, 0.0, 5.0e4, 0x80, 0xFF, 7) for i in range(6)])
g('inveps', u1e=2, w38=1.0e6, pts=flat, live=(100.0, 4.0, 10.00009))
g('tveq', t46=0x1234, t4a=0)
g('tvnegwrap', t46=-0x100, t4a=-0x50)
g('tvnegwrap2', t46=-0x7F3, t4a=-0x10, side=7)
