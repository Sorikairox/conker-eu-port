#!/usr/bin/env python3
# P210: setups for the small script / draw callbacks. usage: gen_small.py TAG > s<TAG>.txt (EU addresses)
import sys, contextlib, io
sys.path.insert(0, __file__.rsplit('/', 1)[0])
with contextlib.redirect_stdout(io.StringIO()):
    from gen_b9c4 import M, f
CUR, OBJ0, CMD, PATHS = 0x800D196C, 0x800CC6F0, 0x800D1CB0, 0x800D2524   # D_800D154C, D_800CC2D0, D_800D1890, D_800D2104
O = 0x80410000

def out(name, m, arg='', ret=''):
    print('%s ! %s ! %s ! %s' % (name, arg, m.pokes(), ret))

def cmd(m, b0, b1, b2, b3):
    m.w8(CMD, b0); m.w8(CMD + 1, b1); m.w8(CMD + 2, b2); m.w8(CMD + 3, b3)

t = sys.argv[1]
if t == '6d3c':
    for nm, b in (('a', (0x64, 0x01, 0x32, 0x00)), ('b', (0x9C, 0xFF, 0x00, 0x80)), ('c', (0x01, 0x80, 0xFF, 0x7F)),
                  ('d', (0x00, 0x00, 0xE8, 0x03))):
        m = M(); m.w32(CUR, O); cmd(m, *b); m.w32(O + 0x14C, f(7.0)); m.w32(O + 0x150, f(9.0))
        out(nm, m)
elif t == '7c58':
    for nm, fr, b22, q in (('a', 0x0203, 0xFF, (10, -20, 30, 400, 500, 0x77)), ('b', 0x00FF, 0x05, (-1, 2, -3, 4, -5, 0x80)),
                           ('c', 0x0101, 0x00, (0x7FFF, -0x8000, 1, 2, 3, 0xFF)), ('d', 0x0302, 0xFE, (5, 6, 7, 8, 9, 1))):
        m = M(); m.w32(O + 0x10, 0x80420000); m.w32(0x80420000, 0x80430000)
        for k in range(4): m.w32(0x80430000 + 4 * k, 0x80440000 + 0x100 * k)
        m.w16(O + 0x14, fr)
        for k in range(5): m.w16(O + 0x18 + 2 * k, q[k] & 0xFFFF)
        m.w8(O + 0x22, b22); m.w8(O + 0x23, q[5])
        out(nm, m, '0=80400000,1=%X,2=1' % O, '15143394=80400100,1514352C=80400200,15095B70=80400300')
elif t == '9fbc':
    for nm, r65, spd, chased in (('r0', 0, 30.0, 0), ('slow', 1, 4.9, 0), ('five', 1, 5.0, 0), ('fast', 1, 30.0, 1),
                                 ('mid', 1, 24.0, 0), ('mid2', 1, 25.0, 0), ('ch16', 1, 16.9, 1), ('ch17', 1, 17.0, 1)):
        m = M(); m.w32(CUR, O); m.w8(OBJ0 + 0x65, r65); m.w32(OBJ0 + 0x44, f(spd)); m.w32(OBJ0 + 0x31C, 0x80460000)
        m.w16(0x80460000 + 0x4C, 0x9ABC); m.w8(0x80460000 + 0x4A, chased); cmd(m, 0x11, 0x22, 0x33, 0x44)
        m.w8(O + 0x232, 0x55); m.w32(O + 0xF4, 0x10000001); m.w16(O + 0x78, 0x1111)
        out(nm, m, '', '1507BEE8=80470010')
elif t == '602c':
    for nm, x, z, spd, ox, oz in (('far', 300, -400, 10.0, 0.0, 0.0), ('near', 30, 40, 10.0, 0.0, 0.0),
                                  ('mid', -60, 80, 20.0, 5.0, -5.0), ('slow', 1000, 1000, 1.0, -3.0, 2.0)):
        m = M(); m.w32(CUR, O); m.w8(O + 0x13F, 2); m.w32(PATHS, 0x80480000); m.w32(0x80480008, 0x80490000)
        cmd(m, 0x00, 0x03, 0x00, 0x00); m.w16(0x80490020, x & 0xFFFF); m.w16(0x80490022, 0x0777); m.w16(0x80490024, z & 0xFFFF)
        m.w32(O + 0x14, f(ox)); m.w32(O + 0x1C, f(oz)); m.w32(O + 0x44, f(spd)); m.w32(O + 0x24, f(-1.5))
        out(nm, m)
elif t == '68dc':
    # current object = D_800CC2D0[3]; candidates 0..24; type records D_800D1C90[id] (EU 0x800D20B0)
    def base(m, near=0x20, flag91=0, fov=0x40, heading=0x0000, s2ca=0):
        cur = OBJ0 + 3 * 0x32C
        m.w32(CUR, cur); m.w8(CMD, near); m.w8(CMD + 1, flag91); m.w8(CMD + 2, 0x15); m.w8(CMD + 3, 0x27)
        m.w8(cur + 4, 0x10); m.w32(cur + 0x18, f(5.0)); m.w32(cur + 0x14, f(0.0)); m.w32(cur + 0x1C, f(0.0))
        m.w16(cur + 0x76, heading); m.w8(cur + 0x2CA, s2ca); m.w8(cur + 0xA8, 0x33); m.w32(cur, 1)
        m.w32(0x800D20B0 + 0x10 * 4, 0x80450000); m.w8(0x80450017, fov)
        for k in range(25):
            o = OBJ0 + k * 0x32C
            if k != 3: m.w32(o, 0)
        return cur
    def cand(m, k, st=1, hp=5, f8=0x20, oid=0x11, y=5.0):
        o = OBJ0 + k * 0x32C
        m.w32(o, st); m.w8(o + 0x1CA, hp); m.w32(o + 0xF8, f8); m.w8(o + 4, oid); m.w32(o + 0x18, f(y))
        m.w32(o + 0x14, f(10.0 * k)); m.w32(o + 0x1C, f(5.0)); m.w8(o + 0x232, 0x44); m.w32(o + 0x218, 0x80470000); m.w8(o + 0x222, 0x55)
    R = '1507BEE8=80470010'
    def go(nm, cands, d, ang, **kw):
        m = M(); base(m, **kw)
        for c in cands: cand(m, *c[:1], **c[1])
        out(nm, m, '', R + ',1505AAAC=' + ';'.join(d) + ',1505A9B0=' + ';'.join(ang))
    # func_1505A72C (1505AAAC) returns f0: use RETF; func_1505A630 (1505A9B0) RET
    def go2(nm, cands, d, ang, **kw):
        m = M(); base(m, **kw)
        for c in cands: cand(m, c[0], **c[1])
        out(nm, m, '', R + ',1505A9B0=' + ';'.join(ang) + ' ! 1505AAAC=' + ';'.join(d))
    go2('one', [(5, {})], ['42000000'], ['00001000'])
    go2('two', [(1, {}), (7, {})], ['42200000', '41F00000'], ['00001000', '00002000'])
    go2('twob', [(1, {}), (7, {})], ['41F00000', '42200000'], ['00001000', '00002000'])
    go2('far', [(2, {})], ['43800000'], ['00001000'])
    go2('fov', [(2, {}), (4, {})], ['41000000', '41100000'], ['00006000', '0000F000'])
    go2('fovb', [(2, {}), (4, {})], ['41000000', '41100000'], ['0000E000', '00001F00'], heading=0x2000, s2ca=0xF0)
    go2('skips', [(0, {'st': 0}), (1, {'hp': 0}), (2, {'f8': 0x10}), (4, {'oid': 0x10}), (5, {'y': 60.0}), (6, {'y': 54.0})], ['41000000'], ['00001000'])
    go2('sameid', [(4, {'oid': 0x10})], ['41000000'], ['00001000'], flag91=1)
    go2('self', [(3, {})], ['41000000'], ['00001000'])
    go2('n2zero', [(6, {})], ['41000000'], ['00001000'])
    go2('fovodd', [(6, {})], ['41000000'], ['00001E00'], fov=0x3F)
elif t == '8544':
    for nm, c, b1, b2, b3, ang in (('m0', 0x05, 0x02, 0xFE, 0x9C, 0x4000), ('m0b', 0x3F, 0x80, 0x7F, 0x0F, 0xC123),
                                   ('m1', 0x47, 0x03, 0x04, 0x56, 0), ('m2', 0x81, 0xFF, 0x01, 0xF1, 0), ('m3', 0xC2, 0x10, 0xF0, 0x37, 0)):
        m = M(); m.w32(CUR, O); m.w8(CMD, c); m.w8(CMD + 1, b1); m.w8(CMD + 2, b2); m.w8(CMD + 3, b3)
        m.w8(O + 0x222, 2); m.w8(O + 0x13F, 1); m.w32(O + 0x14, f(100.0)); m.w32(O + 0x1C, f(-50.0))
        o = OBJ0 + 2 * 0x32C
        m.w32(o + 0x14, f(-20.0)); m.w32(o + 0x18, f(33.7)); m.w32(o + 0x1C, f(40.0)); m.w16(o + 0x7A, ang)
        m.w32(PATHS, 0x80480000); m.w32(0x80480004, 0x80490000)
        out(nm, m, '', ' ! 15048D30=3F000000,15048CA0=3F5DB3D7,15048790=40490FDB,15048050=3F19999A,15047EF0=BF4CCCCD')
elif t == 'aa48':
    for k in range(10):
        for nm2, b0, b1, b3 in (('a', 0x12, 0x34, 0x01), ('b', 0x02, 0x05, 0xF0)):
            m = M(); m.w32(CUR, O); m.w8(CMD, b0); m.w8(CMD + 1, b1); m.w8(CMD + 2, k); m.w8(CMD + 3, b3)
            m.w16(O + 0x76, 0x1111); m.w16(O + 0x78, 0x2222); m.w16(O + 0x7A, 0x3333); m.w8(O + 0x222, 4); m.w8(O + 0x13F, 1)
            m.w16(OBJ0 + 4 * 0x32C + 0x7A, 0x7654); m.w32(PATHS, 0x80480000); m.w32(0x80480004, 0x80490000)
            for p in range(0x40):
                m.w16(0x80490008 + p * 8, (p * 37 - 500) & 0xFFFF); m.w16(0x8049000C + p * 8, (900 - p * 53) & 0xFFFF)
            out('c%d%s' % (k, nm2), m, '', '150ADF00=00012345 ! 15048790=%s' % ('3FC90FDB' if nm2 == 'a' else 'BF800000'))
elif t == '9b30':
    def go(nm, b0, b1, b2, b3, num=4, fidx='00000006', ret2=''):
        m = M(); m.w32(CUR, O); cmd(m, b0, b1, b2, b3); m.w8(0x800C4298, num)
        for k in (4, 6):
            o = OBJ0 + k * 0x32C
            m.w32(o + 0x2E4, 0x100 + k); m.w32(o + 0x2E8, 0x200 + k); m.w32(o + 0x2EC, 0x300 + k)
            m.w8(o + 0x232, 0x21); m.w32(o + 0x218, 0x80470000); m.w16(o + 0x21C, 0x999); m.w32(o + 0xC8, f(2.0)); m.w32(o + 0xB8, f(3.0))
        m.w8(O + 0x222, 7); m.w8(O + 0x221, 0x11); m.w16(O + 0x244, 0x1111); m.w8(O + 0x236, 0x11); m.w8(O + 0x23D, 0x40); m.w8(O + 0x22A, 0x11)
        m.w32(0x800BEE04, 3); m.w16(0x800CC684, 0xFFF9)
        out(nm, m, '', '15084418=%s,1507BEE8=80470010%s' % (fidx, ret2))
    for v in (1, 2, 3):
        for op in range(8):
            go('v%do%d' % (v, op), 0x9A, 1 if op % 2 else 0, v, op)
    go('vneg', 0x9A, 5, 1, 0, fidx='FFFFFFFF')
    go('vidx', 0x9A, 5, 2, 3)
    go('run', 0x22, 3, 4, 0)
    go('run5', 0x21, 0, 5, 0)
    go('runsame', 0x21, 3, 4, 0)
    go('c6', 0xC8, 3, 6, 0)
    go('c7', 0xC8, 0, 7, 0)
    go('c8a', 0x5A, 0, 8, 0, ret2=',15079E58=00001000;00000800')
    go('c8b', 0x5A, 0, 8, 0, ret2=',15079E58=00000800;00001000')
    go('c9', 0x5A, 0, 9, 0xBC)
    go('c10', 0xF0, 0, 10, 0)
    go('c11', 0xF0, 1, 11, 0)
    # c12 (D_800D1892 = 12, default): the asm writes through an unset stack pointer; the C does nothing (DIFFER, expected)
elif t == '7e0c':
    def go(nm, life=100, fade=0, alpha=200, beh=0xFF, frame=0x100, speed=0x40, count=4, flags=0, end=0xFF, vel=(5, -3, 7), acc=2):
        m = M(); n = O
        m.w16(n + 0x38, life & 0xFFFF); m.w8(n + 0x3A, fade); m.w8(n + 0x3F, alpha); m.w8(n + 0x2F, beh); m.w8(n + 0x48, end)
        m.w16(n + 0x1C, frame & 0xFFFF); m.w16(n + 0x1E, speed & 0xFFFF); m.w32(n + 0x10, 0x80420000); m.w8(0x80420004, count)
        m.w16(n + 0x44, flags); m.w16(n + 0x20, 0x0123); m.w16(n + 0x22, 0xFF80); m.w16(n + 0x24, 0x7F00)
        m.w8(n + 0x2C, 0x80); m.w8(n + 0x2D, 0xFF); m.w8(n + 0x2E, 0x01)
        m.w16(n + 0x26, vel[0] & 0xFFFF); m.w16(n + 0x30, vel[1] & 0xFFFF); m.w16(n + 0x28, vel[2] & 0xFFFF); m.w16(n + 0x32, acc & 0xFFFF)
        m.w32(0x800BEE04, 3)
        out(nm, m, '0=%X' % n, '')
    go('plain')
    go('inf', life=0x7FFF)
    go('die', life=2)
    go('dieend', life=2, end=1)
    go('fade', fade=10, alpha=200)
    go('fadeout', fade=10, alpha=10, end=0)
    go('beh0', beh=0); go('beh2', beh=2)
    go('stop', speed=0)
    go('endstop', frame=0x3F0, flags=0x20)
    go('endbounce', frame=0x3F0, flags=0x2)
    go('endwrap', frame=0x3F0, speed=0x200, flags=0x100)
    go('endwrap2', frame=0x3FF, speed=0x7FF, flags=0)
    go('negstop', frame=0x10, speed=-0x40, flags=0x40)
    go('negbounce', frame=0x10, speed=-0x40, flags=0x2)
    go('negwrap', frame=0x10, speed=-0x40)
    go('negwrap2', frame=0x10, speed=-0x700, flags=0x80)
    go('neg_c1', frame=0x10, speed=-0x40, count=1, flags=2)
elif t == '85f0':
    def go(nm, ad=0, yv=30.0, y=10.0, u118=0.0, u1cc=200000.0, mp=0, st=0, stun=3, hp=5, t10c=10, u28=1.0, f4=0, ctl=0x80460000, h10b=0, u238=0, u109=7):
        m = M(); o = O
        m.w8(o + 0xAD, ad); m.w32(o + 0x20, f(yv)); m.w32(o + 0x18, f(y)); m.w32(o + 0x118, f(u118)); m.w32(o + 0x1CC, f(u1cc))
        m.w8(0x800BEA36, mp); m.w32(o, st); m.w8(o + 0x104, stun); m.w8(o + 0x1CA, hp); m.w16(o + 0x10C, t10c & 0xFFFF)
        m.w32(o + 0x28, f(u28)); m.w32(o + 0xF4, f4); m.w32(o + 0x31C, ctl); m.w8(o + 0x10B, h10b); m.w8(o + 0x238, u238)
        m.w8(o + 0x109, u109); m.w32(o + 0x24, f(1.5)); m.w8(o + 0x81, 9); m.w8(o + 0x83, 9); m.w32(o + 0xB8, f(2.0))
        m.w16(o + 0x21C, 0x1234); m.w16(o + 0x76, 0x1111); m.w16(o + 0x78, 0x2222); m.w16(o + 0x7A, 0x3333); m.w32(o + 0x3C, f(5.0))
        m.w32(o + 0xF8, 0xFFFFFFFF); m.w8(o + 0x23A, 0x44); m.w8(o + 0x80, 0x55); m.w8(0x8046007D, 0x66)
        m.w16(0x800CC684, 3); m.w8(0x800C4298, 5)
        out(nm, m, '0=%X' % o, '')
    go('plain'); go('cc', u1cc=50.0)
    go('lift', ad=5, yv=30.0, y=10.0, u118=100.0); go('lift2', ad=5, yv=70.0, y=200.0, u118=100.0); go('lift3', ad=12, y=200.0)
    go('lift4', ad=9, yv=59.0, y=80.0, u118=100.0); go('lift5', ad=1, y=80.1, u118=100.0)
    go('mppl', mp=1, st=1); go('mp0', mp=1, st=0); go('pl', st=1)
    go('s255', stun=0xFF); go('s254', stun=0xFE); go('dead', st=1, hp=0, stun=4); go('deadnp', st=0, hp=0, stun=4)
    go('t10', t10c=2); go('t10n', t10c=2, ctl=0); go('t10z', t10c=3); go('u28', u28=0.1, f4=0x100); go('u28b', u28=0.1); go('u28c', u28=0.3, f4=0x100)
    go('end', stun=1); go('endad', stun=1, ad=12); go('endadp', stun=1, ad=12, st=1); go('endp', stun=1, st=1); go('end238', stun=1, u238=0x17)
    go('h2', h10b=2); go('h4', h10b=4); go('h6', h10b=6); go('h1', h10b=0x81)
