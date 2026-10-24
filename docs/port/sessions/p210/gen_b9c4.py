#!/usr/bin/env python3
# P210: setups for func_1505B9C4 (object_apply_hit). Prints knobs.sh lines. EU addresses.
import struct
SELF, HEAPOBJ, BASE, CUR, CTL = 0x80410000, 0x80420000, 0x80430000, 0x80440000, 0x80460000
OBJS = 0x800CC6F0                      # D_800CC2D0 (EU)
MP, NUM, CUROBJ = 0x800BEA36, 0x800C4298, 0x800D196C   # D_800BE616, D_800C3E78, D_800D154C
IDX = 2

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

def obj(m, a, state=0, x=10.0, y=5.0, z=-20.0, health=10, stunned=0, unk65=0, b23b=0, uid=7, ctl=CTL):
    m.w32(a, state); m.w8(a + 4, 0x31); m.w32(a + 0x14, f(x)); m.w32(a + 0x18, f(y)); m.w32(a + 0x1C, f(z))
    m.w32(a + 0x28, f(1.5)); m.w8(a + 0x3B, uid); m.w8(a + 0x65, unk65); m.w16(a + 0x76, 0x1234)
    m.w8(a + 0x100, 0xFF); m.w8(a + 0x104, stunned); m.w8(a + 0x10B, 0x55); m.w8(a + 0x125, 0x11)
    m.w8(a + 0x1CA, health); m.w8(a + 0x23B, b23b); m.w32(a + 0x31C, ctl); m.w32(a + 0xF8, 0xFFFFFFFF)
    m.w8(a + 0x124, 0); m.w8(a + 0x3A, 0x5A); m.w8(a + 0x239, 0x8C); m.w8(a + 0x105, 0x66)

def desc(m, a, kind=5, sound=0, handler=3, damage=3, push=0x20, xz=4.0, yv=2.0, grav=0.5, b20=9, imm=0, flags=0):
    m.w8(a, kind); m.w32(a + 4, sound); m.w8(a + 8, handler); m.w8(a + 0xF, damage); m.w8(a + 0x10, push)
    m.w32(a + 0x14, f(xz)); m.w32(a + 0x18, f(yv)); m.w32(a + 0x1C, f(grav)); m.w8(a + 0x20, b20)
    m.w8(a + 0x22, imm); m.w16(a + 0x24, flags)

def setup(name, o=None, base=None, cur=None, sepcur=False, mp=0, selfid=0x10, s124=0, slot=3, mask=0xF,
          carrier_id=None, ctl4e=1, ctl98=0, ret=''):
    m = M()
    o = dict(o or {}); oa = o.pop('addr', HEAPOBJ)
    m.w32(SELF, 0); m.w8(SELF + 4, selfid); m.w32(SELF + 0x14, f(3.0)); m.w32(SELF + 0x18, f(1.0))
    m.w32(SELF + 0x1C, f(-4.0)); m.w16(SELF + 0x76, 0x4000); m.w8(SELF + 0x3B, 0x21); m.w8(SELF + 0x124, s124)
    obj(m, oa, **o)
    m.w8(CTL + 0x4E, ctl4e); m.w8(CTL + 0x98, ctl98); m.w8(CTL + 0x95, 0x33); m.w8(CTL + 0x6B, 0x33)
    if carrier_id is not None:
        m.w8(OBJS + 0x32C + 4, carrier_id); m.w8(OBJS + 0x32C + 0x232, 0x77); m.w32(OBJS + 0x32C + 0x218, 0x80470000)
    desc(m, BASE + IDX * 0x28, **(base or {}))
    if sepcur: desc(m, CUR + IDX * 0x28, **(cur or {}))
    m.w8(MP, mp); m.w8(NUM, 4); m.w32(CUROBJ, 0x80480000)
    arg = '0=%X,1=%X,2=%X,3=%X,4=%X,5=%X,6=%X' % (SELF, oa, BASE, CUR if sepcur else BASE, IDX, slot, mask)
    r = '1505A9B0=00001234,1505EB78=00000042' + (',' + ret if ret else '')
    print('%s ! %s ! %s ! %s' % (name, arg, m.pokes(), r))

P2 = OBJS + 2 * 0x32C   # D_800CC2D0[2]: a player slot
setup('plain')
setup('k27', base={'kind': 0x27})
setup('cur80', sepcur=True, cur={'kind': 0x86, 'handler': 0, 'damage': 0x22, 'push': 0x40, 'sound': 0}, base={'handler': 5})
setup('curnh', sepcur=True, cur={'kind': 0x06, 'handler': 7, 'damage': 0x41}, base={'kind': 0x09, 'handler': 5, 'damage': 0x20})
setup('stunm', o={'stunned': 3}, base={'flags': 1, 'damage': 5})
setup('stun0', o={'stunned': 0}, base={'flags': 0x11, 'damage': 15})
setup('ang44', selfid=0x44, base={'flags': 0x10})
setup('kill', o={'health': 2}, base={'damage': 7}, mask=7)
setup('kill2', o={'health': 3}, base={'damage': 0xB}, mask=0xF)
setup('pl', o={'addr': P2, 'state': 1}, ctl4e=1, ctl98=0)
setup('pl2', o={'addr': P2, 'state': 1}, ctl4e=2, ctl98=1)
setup('cnoskip', o={'addr': P2, 'state': 1, 'unk65': 2}, carrier_id=0x8A)
setup('cmp_y', o={'addr': P2, 'state': 1, 'unk65': 2}, carrier_id=0x8A, mp=1, base={'yv': 40.0})
setup('cmp_xz', o={'addr': P2, 'state': 1, 'unk65': 2}, carrier_id=0x23, mp=1, base={'yv': 0.0, 'xz': 120.0})
setup('cmp_no', o={'addr': P2, 'state': 1, 'unk65': 2}, carrier_id=0x23, mp=1, base={'yv': 30.0, 'xz': 110.0})
setup('c0c', o={'addr': P2, 'state': 1, 'unk65': 2}, carrier_id=0x0C)
setup('c05', o={'addr': P2, 'state': 1, 'unk65': 2}, carrier_id=0x05)
setup('cdead', o={'addr': P2, 'state': 1, 'unk65': 2, 'health': 1}, carrier_id=0x8A, base={'damage': 4})
setup('cflag2', o={'addr': P2, 'state': 1, 'unk65': 2}, carrier_id=0x23, base={'flags': 2})
setup('mp0', mp=1, s124=0)
setup('mp3', mp=1, s124=3)
setup('snd1', base={'sound': 0x12345678}, ret='1506E82C=1')
setup('snd0', base={'sound': 0x12345678}, ret='1506E82C=0')
setup('sndc', sepcur=True, cur={'sound': 0x01020304, 'handler': 2}, ret='1506E82C=1')
setup('mppl', mp=1, o={'addr': P2, 'state': 1}, base={'flags': 0x100})
setup('f100', base={'flags': 0x100})
setup('f40pl', o={'addr': P2, 'state': 1}, base={'flags': 0x42})
setup('f40', base={'flags': 0x40})
setup('b23b', o={'b23b': 0x19}, base={'flags': 0x208})
setup('yneg', base={'yv': -1.0, 'flags': 0x2})
setup('f400b', base={'flags': 0x400, 'imm': 0x85})
setup('f400c', sepcur=True, cur={'flags': 0x400}, base={'imm': 0x45})
setup('k27f', base={'kind': 0x27, 'flags': 0x40A, 'imm': 0xBF})
setup('slot1', slot=1, mp=1, base={'flags': 0x8})
setup('f100c', sepcur=True, cur={'flags': 0x100}, base={'flags': 0})
setup('f100b', sepcur=True, cur={'flags': 0}, base={'flags': 0x100})
setup('imm', base={'imm': 0xC5})
setup('curall', sepcur=True, cur={'b20': 0x31, 'grav': 3.25, 'sound': 0x0BADF00D, 'xz': 7.5, 'yv': -2.5}, base={'sound': 0x600DF00D, 'b20': 0x13}, ret='1506E82C=1')
