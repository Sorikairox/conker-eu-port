#!/usr/bin/env python3
# P213: setups for func_150562FC (62fc) and func_1505E874 (e874). usage: gen_p213.py TAG > s<TAG>.txt (EU addresses)
# Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW
import sys, struct

def f(x): return struct.unpack('>I', struct.pack('>f', x))[0]

class M:
    def __init__(s): s.b = {}
    def w8(s, a, v): s.b[a] = v & 0xFF
    def w16(s, a, v): s.w8(a, v >> 8); s.w8(a + 1, v)
    def w32(s, a, v): s.w16(a, v >> 16); s.w16(a + 2, v)
    def pokes(s):
        ws = {}
        for a in sorted(s.b):
            ws.setdefault(a & ~3, [0, 0, 0, 0])[a & 3] = s.b[a]
        return ','.join('%08X=%02X%02X%02X%02X' % ((a,) + tuple(v)) for a, v in sorted(ws.items()))

OBJS, TYPES, STEP, FAST, NUM, LEVEL, SND = 0x800CC6F0, 0x800D19A8, 0x800BEDC0, 0x800BEDD4, 0x800C4298, 0x800BEE10, 0x800D19A0
O, CTL, CAM, MODEL, TREC, ROWS = 0x80410000, 0x80460000, 0x80440000, 0x80450000, 0x80470010, 0x80480000
E7CC, E650, A184, D9C8, D5C, E46C, A30, B04, E5FC, E8D8, CD64, F9F8 = (
    '1505EB78', '1505E9FC', '1505A504', '15059D48', '15064D5C', '1506E82C', '15060DDC', '15060EB0', '1506E9BC',
    '1506EC98', '1507D144', '1517F9F8')

def out(name, m, arg='', ret='', retf='', outa='', outw=''):
    print('%s ! %s ! %s ! %s ! %s ! %s ! %s' % (name, arg, m.pokes(), ret, retf, outa, outw))

def rows(m, kind=20, sound=0, b8=0x33, cells=((0x101, 50, 4), (0x102, 0, 200), (0x103, 25, 7)), nrows=4):
    # every row the same unless overridden; cell = (anim, speed %, flags)
    m.w32(TYPES + 4 * m.id, TREC); m.w32(TREC - 8, ROWS)
    for r in range(nrows):
        a = ROWS + r * 0x18
        m.w8(a, kind); m.w32(a + 4, sound); m.w8(a + 8, b8 + r)
        for k, (an, sp, fl) in enumerate(cells):
            m.w16(a + 0xA + 4 * k, an + 0x10 * r if an else 0); m.w8(a + 0xC + 4 * k, sp); m.w8(a + 0xD + 4 * k, fl)
        m.w16(a + 0xA + 4 * len(cells), 0)

t = sys.argv[1]
if t == '62fc':
    H = OBJS + 2 * 0x32C
    def s62(name, oid=0x10, t21c=12, step=1, fast=0, hstate=0, water=0, hanim=0, model=False, row=2, u28=50.0,
            b10f=40, b13e=3, u10c=250, cell1=0x222, mh=-30):
        m = M(); m.id = oid
        m.w8(O + 4, oid); m.w8(O + 0x13D, 102); m.w16(O + 0x21C, t21c); m.w8(STEP, step); m.w8(FAST, fast)
        m.w8(O + 0x10F, b10f); m.w8(O + 0x13E, b13e); m.w16(O + 0x10C, u10c); m.w32(O + 0x28, f(u28))
        m.w32(O + 0xC4, f(3.0)); m.w32(O + 0x14, f(10.0)); m.w32(O + 0x18, f(20.0)); m.w32(O + 0x1C, f(-30.0))
        m.w8(O + 0x101, 0x50); m.w8(O + 0x65, 0x77); m.w32(O + 0x5C, 0x55)
        m.w32(H, hstate); m.w8(H + 0xAD, water); m.w16(H + 0x84, hanim); m.w16(H + 0x7A, 0x1234)
        m.w32(H + 0x180, f(7.5)); m.w32(H + 0x14, f(100.0)); m.w32(H + 0x18, f(50.0)); m.w32(H + 0x1C, f(-60.0))
        m.w32(H + 0xC4, f(9.0)); m.w32(H + 0x1D4, MODEL if model else 0); m.w16(MODEL + 0x25A, mh & 0xFFFF)
        rows(m, cells=((0x101, 50, 4), (cell1, 70, 0), (0x103, 25, 7)))
        out(name, m, '0=%X' % O, '%s=%X' % (E7CC, row), '', '',
            '%s=3:%08X/4:%08X/5:%08X' % (A184, f(11.0), f(-13.0), f(17.0)))
    s62('plain')
    s62('plain_fast', fast=1)
    s62('t19', t21c=19); s62('t20', t21c=20); s62('t29', t21c=29, step=3); s62('t30', t21c=30, step=3)
    s62('t6m', t21c=6, step=0, model=True); s62('t7m', t21c=7, step=0, model=True); s62('t13m', t21c=13, step=0, model=True)
    s62('t14m', t21c=14, step=0, model=True); s62('t20m', t21c=20, step=0, model=True, u10c=-450)
    s62('e_m', oid=0xE, model=True); s62('x13_m', oid=0x13, model=True)
    s62('x13_nm', oid=0x13, model=False)
    for a in (0x114, 0x116, 0x117, 0x5):
        s62('57_%X' % a, oid=0x57, hanim=a)
    s62('57_t9', oid=0x57, t21c=8, hanim=0x114); s62('57_t9b', oid=0x57, t21c=9, hanim=0x116)
    for a in (0x1A6, 0x1A7, 0x5):
        s62('8c_%X' % a, oid=0x8C, hanim=a)
    s62('8c_t9', oid=0x8C, t21c=9, step=0, hanim=0x1A7)
    for oid in (0xA8, 0xA9):
        for a in (0x1B0, 0x1B1, 0x5):
            s62('%x_%X' % (oid, a), oid=oid, hanim=a, t21c=2)
    for a in (0x286, 0x27E, 0x5):
        s62('5e_%X' % a, oid=0x5E, hanim=a, t21c=3)
    s62('w1', hstate=1, water=1); s62('w1z', hstate=1, water=1, cell1=0); s62('w0', hstate=1, water=0)
    s62('w2', hstate=2, water=1); s62('w1_57', oid=0x57, hstate=1, water=1, hanim=0x117, cell1=0)
    s62('s15a', hstate=0x15, u28=150.0, t21c=25, model=True); s62('s15b', hstate=0x15, u28=150.0, t21c=20, step=0)
    s62('s15c', hstate=0x15, u28=150.0, t21c=21, step=0); s62('s15d', hstate=0x15, u28=100.0, t21c=25)
    s62('s15e', hstate=0x15, u28=50.0, t21c=40, oid=0x5E, hanim=0x27E)
elif t == 'e874':
    def se(name, oid=0x10, row=1, phase=0, sound=0, e46=0, snd_out=None, b13d=0, player=0xFF, health=5, ctl=True,
           cam=True, c197=1, kind=20, cells=((0x101, 50, 4), (0x102, 0, 200), (0x103, 25, 7)), water=0, u184=0,
           level=0x10, state=0, nrows=4, a0=0x5A, notypes=False):
        m = M(); m.id = oid
        m.w8(O + 4, oid); m.w8(O + 0x106, row); m.w8(O + 0x105, phase); m.w8(O + 0x13D, b13d); m.w8(O + 0x127, player)
        m.w8(O + 0x1CA, health); m.w32(O + 0x31C, CTL if ctl else 0); m.w32(O + 0x318, CAM if cam else 0)
        m.w8(CTL + 0x197, c197); m.w8(CTL + 0x26, 0x99); m.w8(CTL + 0x58, 0x98); m.w8(CTL + 0x1AC, 0x97)
        m.w8(CAM + 0x23D, 0x42); m.w8(O + 0xAD, water); m.w32(O + 0x184, u184); m.w32(LEVEL, level)
        m.w32(O, state); m.w32(O + 0xF4, 0xFFFFFFFF); m.w32(O + 0xF8, 0xFFFFFFFF); m.w8(O + 0x10B, 0xF6)
        m.w8(O + 0x10F, 0x66); m.w8(O + 0x8A, 0x65); m.w8(O + 0x104, 0x64); m.w16(O + 0x10C, 0x1234)
        m.w32(SND, 0x11223344)
        if notypes:
            m.w32(TYPES + 4 * oid, TREC); m.w32(TREC - 8, 0)
        else:
            rows(m, kind=kind, sound=sound, cells=cells, nrows=nrows)
        ow = '%s=1:%08X' % (E46C, snd_out) if snd_out is not None else ''
        out(name, m, '0=%X,1=%X' % (a0, O), '%s=%X' % (E46C, e46), '', '', ow)
    se('p0'); se('p1', phase=1); se('p2', phase=2); se('p3', phase=3); se('p4', phase=7)
    se('null', notypes=True); se('ff', oid=0xFF)
    se('snd_no', sound=0x21, e46=0); se('snd_a', sound=0x21, e46=1); se('snd_33', sound=0x33, e46=1)
    se('snd_to33', sound=0x21, e46=1, snd_out=0x33); se('snd_from33', sound=0x33, e46=1, snd_out=0x44)
    se('nojctl', ctl=False); se('5e_h', oid=0x5E, b13d=3); se('5e_0', oid=0x5E, b13d=0)
    se('pl_shake', player=1); se('pl_nocam', player=1, cam=False); se('pl_noctl', player=1, ctl=False, state=0)
    se('pl_c0', player=1, c197=0); se('pl_p1', player=1, phase=1)
    se('spd0', phase=1); se('fl200', phase=1)
    se('anim0', cells=((0, 50, 4), (0x102, 0, 200))); se('anim0_pl', cells=((0, 50, 4),), state=1)
    se('anim0_st1', phase=1, cells=((0x101, 50, 4), (0, 0, 0)), state=1)
    se('p3_st1', phase=3, state=1)
    # end actions: living (unk127 != 0xFF, health 0) and phase past the last animation
    one = ((0x101, 50, 4),)
    se('end_0', player=1, health=0, cells=one)                     # last 1 -> 2, phase 0: no end
    se('end_1', player=1, health=0, phase=1, cells=one)            # last = 1 -> 2 == phase + 1
    se('end_2', player=1, health=0, phase=2)                       # cells 3 -> last 3 == 3
    se('end_h1', player=1, health=1, phase=2)
    se('end_np', player=0xFF, health=0, phase=2)
    se('end_p1', player=1, health=0, phase=1)                      # last 3 != 2
    se('end_9a', oid=0x9A, player=1, health=0, phase=2); se('end_53', oid=0x53, player=1, health=0, phase=2)
    se('end_w', player=1, health=0, phase=2, water=1)
    se('end_g14', player=1, health=0, phase=2, u184=0xE0 | 14); se('end_g19', player=1, health=0, phase=2, u184=19)
    se('end_g14l', player=1, health=0, phase=2, u184=14, level=0x34); se('end_g15', player=1, health=0, phase=2, u184=15)
    for k in (5, 13, 14, 15, 16, 17, 31, 32, 33, 34, 37, 38, 44, 45, 46, 47, 48, 51, 52, 53, 65, 66, 67, 68, 71, 72, 73, 0xFF):
        se('k%d' % k, player=1, health=0, phase=2, kind=k, state=1 if k == 16 else 0)
elif t == 'a0dc':
    def sa(name, objs, radius=150.0, last_state=0, ret='7'):
        m = M()
        m.w32(O + 0x10, f(10.0)); m.w32(O + 0x18, f(-20.0)); m.w32(O + 0x44, f(radius))
        for k in range(25):
            m.w32(OBJS + k * 0x32C, last_state if k == 24 else 0)
        for k, kw in objs:
            a = OBJS + k * 0x32C
            m.w32(a, kw.get('st', 1)); m.w8(a + 4, kw.get('id', 0x10)); m.w32(a + 0x28, f(kw.get('u28', 5.0)))
            m.w8(a + 0x125, kw.get('imm', 0)); m.w32(a + 0x14, f(10.0 + kw.get('dx', 200.0))); m.w32(a + 0x1C, f(-20.0 + kw.get('dz', 0.0)))
            m.w8(a + 0x13C, kw.get('b13c', 0)); m.w8(a + 0x124, kw.get('hold', 5)); m.w16(a + 0x7A, 0x1357)
            m.w8(a + 0x89, 0x77); m.w32(a + 0x218, 0x80450000); m.w8(a + 0x232, 0x66)
            m.w8(OBJS + kw.get('hold', 5) * 0x32C + 0x65, kw.get('h65', 0))
        out(name, m, '0=%X' % O, '1505D3D0=%s' % ret)
    sa('p1', [(2, {})]); sa('last', [(24, {})]); sa('last5', [], last_state=5); sa('lastsk', [(24, {'st': 2})])
    sa('r0', [(3, {'dx': 120.0, 'dz': 160.0})], radius=100.0)          # reach exactly 0
    sa('r250', [(3, {'dx': 120.0, 'dz': 160.0})], radius=350.0)        # reach exactly 250
    sa('r249', [(3, {'dx': 120.0, 'dz': 160.0})], radius=349.0); sa('rneg', [(3, {'dx': 120.0, 'dz': 160.0})], radius=99.0)
    sa('u20', [(4, {'u28': 20.0})]); sa('u19', [(4, {'u28': 19.9})]); sa('imm', [(4, {'imm': 3})])
    sa('st2', [(6, {'st': 2})]); sa('k53', [(7, {'id': 0x53, 'st': 2})]); sa('k53h', [(7, {'id': 0x53, 'h65': 1})])
    sa('k53l', [(7, {'id': 0x53, 'b13c': 1, 'dx': 300.0})], radius=310.0); sa('k53u', [(7, {'id': 0x53, 'b13c': 0, 'dx': 300.0})], radius=310.0)
    sa('k53far', [(7, {'id': 0x53, 'b13c': 1, 'dx': 300.0})], radius=150.0); sa('k53ufar', [(7, {'id': 0x53, 'b13c': 0, 'dx': 600.0})], radius=310.0)
    sa('two', [(1, {}), (24, {'dz': 50.0})], ret='3;9')
    sa('dead53', [(8, {'id': 0x53, 'st': 0})])                         # state 0 is skipped even for type 0x53
    sa('k53edge', [(7, {'id': 0x53, 'b13c': 0, 'dx': 300.0})], radius=49.5)   # reach -0.5 (151: +0.5)
else:
    sys.exit('tag?')
