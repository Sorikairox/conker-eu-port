#!/usr/bin/env python3
# P306: generates s67A0.txt (func_151E67A0 setups). Objects = D_800CC2D0 slots (EU 0x800CC6F0, 0x32C each), menu record
# D_80090174 -> 80420000, victim character record (unk31C) 80430000, scorer's 80438000, attacker 80440000 when it is
# not a slot. Counters: D_8008FD8C (EU 8009012C) = slot count, D_80090130 = humans, D_800E1030 = teams,
# D_8009015C flags. EU keys: 150ADF00 func_150ADA20 (RET rand), 1000F858 func_1000F568 (RET), 10010848 func_10010558,
# 10010920 func_10010630, 15085B80 func_15085710.
OBJ = 0x800CC6F0
def slot(k): return OBJ + k * 0x32C
class Mem:
    def __init__(s): s.b = {}
    def u8(s, a, v): s.b[a] = v & 0xFF
    def u16(s, a, v): s.u8(a, v >> 8); s.u8(a + 1, v)
    def u32(s, a, v): s.u16(a, v >> 16); s.u16(a + 2, v)
    def words(s):
        w = {}
        for a in s.b: w.setdefault(a & ~3, None)
        out = []
        for wa in sorted(w):
            v = 0
            for i in range(4): v = (v << 8) | s.b.get(wa + i, 0)
            out.append('%X=%08X' % (wa, v))
        return out
def obj(m, a, ident, health, state=0, u124=0, u278=0, char=0):
    m.u32(a, state); m.u8(a + 4, ident); m.u8(a + 0x124, u124); m.u8(a + 0x1CA, health); m.u16(a + 0x278, u278)
    m.u32(a + 0x31C, char)
def setup(name, att=0, vic=1, kind=0x2E, aid=0x80, vid=0x10, vhealth=5, ahealth=5, teams=(0, 1, 0, 1), count=4,
          humans=2, flags=0x200, kills=(10, 20, 30, 40), rows=None, vchar=(0, 0), schar=0x00, u124=0, state=0, u278=0,
          vnochar=False, rand='00000003;00000000;00000001', f568='0001057A', srcfix=None):
    m = Mem()
    m.u8(0x8009012C, count); m.u8(0x80090130, humans); m.u16(0x8009015C, flags); m.u32(0x80090174, 0x80420000)
    for i, t in enumerate(teams): m.u8(0x800E1030 + i, t)
    for i in range(4):
        m.u16(0x80420046 + 2 * i, kills[i])
        r = (rows or {}).get(i, (1, 2, 3, 4))
        for j, off in enumerate((0x66, 0x6A, 0x6E, 0x70)): m.u16(0x80420000 + i * 0xC + off, r[j])
    m.u8(0x80430078, vchar[0]); m.u8(0x804301AC, vchar[1]); m.u8(0x80438078, schar); m.u8(0x804380AF, 0x77)
    va = slot(vic)
    obj(m, va, vid, vhealth, char=0 if vnochar else 0x80430000)
    if isinstance(att, int) and att < 0x100:
        aa = slot(att); obj(m, aa, aid, ahealth, char=0x80438000, state=state, u278=u278)
    else:
        aa = att; obj(m, aa, 0x99, 9, state=state, u124=u124, u278=u278, char=0x80438000)
        if u124 and u124 - 1 < 8 and srcfix is None: obj(m, slot(u124 - 1), aid, ahealth, char=0x80438000)
    print('%s ! 0=%08X,1=%08X,2=%X ! %s ! 150ADF00=%s,1000F858=%s !  !  !  !' % (name, aa, va, kind, ','.join(m.words()), rand, f568))
NP = 0x80440000   # a non-player attacker
# scoring
setup('hit')                                          # other team, alive, kind 0x2E (0x6A too), 0x80 kind 0x2E
setup('hitk2f', kind=0x2F, rand='00000001')
setup('same', teams=(0, 0, 1, 1), kind=0x2C)           # same team, alive
setup('teamkill', teams=(0, 0, 1, 1), vhealth=0, kind=0x2C)
setup('teamkill2d', teams=(0, 0, 1, 1), vhealth=0, kind=0x2D)
setup('kill', vhealth=0, kind=0x2C)
setup('killnoflag', vhealth=0, kind=0x2C, flags=0x1FD)
setup('kill9998', vhealth=0, kind=0x2C, kills=(9998, 1, 2, 3))
setup('kill9999', vhealth=0, kind=0x2C, kills=(9999, 1, 2, 3))
setup('killt0', att=1, vic=0, teams=(0, 2, 0, 1), vhealth=0, kind=0x2C)   # scorer team 2 (!= 0)
setup('vbot', vic=3, kind=0x2C)                        # victim not human (no 0x6E)
setup('abot', att=3, vic=0, kind=0x2C, humans=2)       # scorer not human
setup('h1', humans=1, kind=0x2C)
setup('h0', humans=0, kind=0x2C)
setup('own', att=NP, u124=2, vic=0, kind=0x2C)               # non-player, owner slot 1
setup('own0', att=NP, u124=0, kind=0x2C)
setup('own5', att=NP, u124=5, kind=0x2C)              # owner slot 4 >= count
setup('own4', att=NP, u124=4, kind=0x2C)              # slot 3 < count
setup('slot5', att=5, vic=1, kind=0x2C, count=4)       # attacker slot beyond count, unk124 0
setup('selfhit', att=1, vic=1, kind=0x2C)
setup('nochar', vnochar=True, kind=0x2C)
setup('srcdead', ahealth=0, kind=0x2C)
# kind 0x33
setup('k33a', kind=0x33, vchar=(0x21, 0)); setup('k33b', kind=0x33, vchar=(0x22, 0)); setup('k33c', kind=0x33, vchar=(0x23, 0))
# scorer 0x75
for nm, kw in [('s75v75', dict(vid=0x75, rows={1: (1, 2, 3, 4)})), ('s75v75lo', dict(vid=0x75, rows={1: (1, 2, 3, 3)})),
               ('s75v75bot', dict(vid=0x75, vic=3)), ('s75k34', dict(kind=0x34)), ('s75k34n', dict(kind=0x34, rand='00000002')),
               ('s75', dict(kind=0x21)), ('s75alive', dict(kind=0x21, vhealth=3))]:
    kw.setdefault('vhealth', 0); setup(nm, aid=0x75, **kw)
# scorer 0x80
setup('s80v80', vid=0x80, vhealth=0, rows={1: (1, 2, 3, 5)}); setup('s80v80lo', vid=0x80, rows={1: (1, 2, 3, -2 & 0xFFFF)})
setup('s80v80bot', vid=0x80, vic=2, humans=2)
setup('s80m2d', att=NP, u124=1, vic=1, state=4, u278=2, vhealth=0, kind=0x40)
setup('s80m2a', att=NP, u124=1, vic=1, state=4, u278=2, kind=0x40, rand='00000008')
setup('s80m2n', att=NP, u124=1, vic=1, state=4, u278=2, kind=0x40, rand='00000004')
setup('s80m2s', att=NP, u124=1, vic=1, state=3, u278=2, kind=0x2C)   # state != 4: mode -1
setup('s80m3', att=NP, u124=1, vic=1, state=4, u278=3, kind=0x2C)
setup('s80c1d', vchar=(0, 1), vhealth=0, kind=0x2C); setup('s80c1a', vchar=(0, 1), kind=0x2C, rand='00000007')
setup('s80c1n', vchar=(0, 1), kind=0x2C, rand='00000002'); setup('s80c1k21', vchar=(0, 1), vhealth=0, kind=0x21)
setup('s80k2e23', schar=0x23, rand='00000004'); setup('s80k2e23n', schar=0x23, rand='00000005')
setup('s80k2f0', kind=0x2F, rand='00000002'); setup('s80k2c', kind=0x2C)
for k in (0x21, 0x20, 0x31):
    setup('s80k%Xd' % k, kind=k, vhealth=0); setup('s80k%Xa' % k, kind=k, rand='0000000B'); setup('s80k%Xn' % k, kind=k, rand='00000004')
setup('s80k40', kind=0x40)
# scorer 0x3B
setup('s3Bm2d', aid=0x3B, att=NP, u124=1, state=4, u278=2, vhealth=0, kind=0x40)
setup('s3Bm2a', aid=0x3B, att=NP, u124=1, state=4, u278=2, kind=0x40, rand='0000000F')
setup('s3Bm2n', aid=0x3B, att=NP, u124=1, state=4, u278=2, kind=0x40, rand='00000003')
setup('s3Bk2e', aid=0x3B); setup('s3Bk2c', aid=0x3B, kind=0x2C); setup('s3Bk2f', aid=0x3B, kind=0x2F)
setup('s3Bk25e', aid=0x3B, kind=0x25, vhealth=3); setup('s3Bk26e', aid=0x3B, kind=0x26, vhealth=0)
setup('s3Bk25o', aid=0x3B, att=1, vic=0, kind=0x25, vhealth=3); setup('s3Bk26o2', aid=0x3B, att=1, vic=0, kind=0x26, vhealth=2)
setup('s3Bk25o1', aid=0x3B, att=1, vic=0, kind=0x25, vhealth=1)
setup('s3Bk21', aid=0x3B, kind=0x21, rand='00000007'); setup('s3Bk21n', aid=0x3B, kind=0x21, rand='00000001')
for r in (0x10, 0x21, 0x22, 0x23, 0x13): setup('s3Bk20r%X' % r, aid=0x3B, kind=0x20, rand='%08X' % r)
setup('s3Bk40', aid=0x3B, kind=0x40)
# scorer 0x88
setup('s88alive', aid=0x88, kind=0x21); setup('s88k34', aid=0x88, kind=0x34, vhealth=0, rand='00000007')
setup('s88k34n', aid=0x88, kind=0x34, vhealth=0, rand='00000001'); setup('s88k21', aid=0x88, kind=0x21, vhealth=0)
setup('s88', aid=0x88, kind=0x2C, vhealth=0)
setup('s12', aid=0x12, kind=0x2C, vhealth=0)
# extra setups for mutants
setup('ah2', att=2, vic=1, kind=0x2C, humans=2)
setup('s80self4', state=4, u278=2, kind=0x2C)
setup('s3Bk20rA', aid=0x3B, kind=0x20, rand='0000000A')
