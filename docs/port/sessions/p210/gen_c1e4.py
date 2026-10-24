#!/usr/bin/env python3
# P210: setups for func_1505C1E4 (object_receive_hit). Prints knobs.sh lines. EU addresses; rule lists from the ROM
# (DIFFTEST_ROMDATA=1, port_work/p210/rules.txt) except the 'p*' setups, which poke a heap list for type 1.
import struct, sys
sys.path.insert(0, __file__.rsplit('/', 1)[0])
import contextlib, io
with contextlib.redirect_stdout(io.StringIO()):   # gen_b9c4 prints its own setups on import
    from gen_b9c4 import M, f, SELF, HEAPOBJ, CTL, OBJS
DESCS, RULES = 0x80430000, 0x80490000
IDX = 2

def setup(name, typ, kind, o_state=0, health=10, stunned=0, oaddr=HEAPOBJ, ctl4e=2, ctl84=0, unk28=1.5, b84=0,
          fc=0, sound=0, handler=3, damage=3, mask=0xF, slot=3, hits=0x100, rule=None, ret=''):
    m = M()
    m.w32(SELF, 0); m.w32(SELF + 0x14, f(3.0)); m.w32(SELF + 0x1C, f(-4.0)); m.w16(SELF + 0x7A, 0x2345)
    m.w8(SELF + 0xD0, 9); m.w8(SELF + 0x232, 9); m.w32(SELF + 0x218, 0x80470000); m.w32(SELF + 0x2EC, 5)
    a = oaddr
    m.w32(a, o_state); m.w32(a + 0x14, f(10.0)); m.w32(a + 0x1C, f(-20.0)); m.w32(a + 0x28, f(unk28))
    m.w16(a + 0x7A, 0x1000); m.w8(a + 0x81, 4); m.w16(a + 0x84, b84); m.w8(a + 0x89, 0); m.w8(a + 0xD0, 5)
    m.w32(a + 0xF4, 0xFFFFFFFF); m.w32(a + 0xFC, fc); m.w8(a + 0x104, stunned); m.w8(a + 0x1CA, health)
    m.w32(a + 0x1C4, 7); m.w32(a + 0x218, 0x80470000); m.w8(a + 0x232, 0x66); m.w8(a + 0x239, typ)
    m.w32(a + 0x31C, CTL); m.w32(a + 0x20, f(1.0)); m.w32(a + 0x24, f(1.0)); m.w32(a + 0x3C, f(1.0))
    m.w8(CTL + 0x4E, ctl4e); m.w8(CTL + 0x84, ctl84); m.w8(CTL + 0x50, 0x44)
    d = DESCS + IDX * 0x28
    m.w8(d, kind); m.w32(d + 4, sound); m.w8(d + 8, handler); m.w8(d + 0xF, damage)
    if rule:   # one rule for type 1 at RULES (count of type 1 is 1 in the ROM)
        m.w32(0x80086E44, RULES); m.w8(RULES, rule[0]); m.w8(RULES + 1, rule[1]); m.w8(RULES + 2, rule[2]); m.w8(RULES + 3, rule[3])
    arg = '0=%X,1=%X,2=%X,3=%X,4=%X,5=%X,6=%X' % (SELF, a, DESCS, IDX, slot, hits, mask)
    r = '1505A9B0=00001234' + (',' + ret if ret else '')
    print('%s ! %s ! %s ! %s' % (name, arg, m.pokes(), r))

P2 = OBJS + 2 * 0x32C
setup('t0', 0, 0x0B)
setup('t80', 0x80, 0x0B)
setup('t1', 0x81, 0x8B)                          # rule 0/0B/86/00: except 0x0B -> skip -> B9C4
setup('t1b', 1, 0x0C)                            # -> action 6 param 0
setup('t4catch', 4, 0x36, sound=0x1234)          # action 8 param 0x10
setup('t4catchp', 4, 0x36, o_state=1, oaddr=P2)  # player: ctl 4E 2, 84 0
setup('t4catchq', 4, 0x36, o_state=1, oaddr=P2, ctl4e=1)
setup('t4catchr', 4, 0x36, o_state=1, oaddr=P2, ctl84=1)
setup('t4h', 4, 0x20)                            # action 3
setup('t4n', 4, 0x1C)                            # action 9
setup('t4m', 4, 0x12)                            # action 4 param FF
setup('t4x', 4, 0x05, slot=7)                    # except 0x12 -> action 6 param 3
setup('t5', 5, 0x11)                             # skip, then action 5 param 6
setup('t7', 7, 0x13, mask=7)                     # action 5 param 7
setup('t10a', 10, 0x21, health=10, damage=3)     # action 7 fails -> next rule 9
setup('t10b', 10, 0x21, health=3, damage=3)      # action 7 taken
setup('t10c', 10, 0x21, health=3, damage=0x13, mask=7)
setup('t17', 17, 0x11)                           # action 8 param 0x0E
setup('t19a', 19, 0x1C, ret='1505C4EC=00004000')  # cond 1 ok -> action 8
setup('t19b', 19, 0x1C, ret='1505C4EC=00004001')  # cond 1 fails -> 0x83 -> action 3
setup('t20a', 20, 0x1B, ret='1505C4EC=00004000')  # cond 2 ok
setup('t20b', 20, 0x1B, ret='1505C4EC=00003FFF')
setup('t26', 26, 0x0A)                           # action 4 param 1
setup('t30a', 30, 0x01, fc=0x55, sound=0x777, ret='1506E82C=1')   # action 0xD
setup('t30b', 30, 0x01, fc=0x55, ret='1506E82C=0')
setup('t30c', 30, 0x01, fc=0, handler=5, slot=1)
setup('t47b', 47, 0x42, unk28=9.0)               # action 0xB
setup('t47c', 47, 0x42, unk28=8.0)
setup('t47a', 47, 0x43, b84=0x283)               # action 0xA
setup('t47d', 47, 0x43, b84=0x282)
setup('t47e', 47, 0x15, unk28=0.0)               # action 0xC
setup('t47f', 47, 0x15, unk28=2.0)
setup('t53', 53, 0x07, sound=0x99)               # 0x8D: action 0xD
setup('t16', 16, 0x10)                           # action 6 param 8
setup('t18', 18, 0x05)                           # no rule matches
setup('t29', 29, 0x29)                           # except 0x29 -> no rule
for act in (0, 1):
    for ang, nm in ((0x1000, 'f'), (0x5000, 'b'), (0xF000, 'c'), (0x9500, 'd')):
        setup('p%d%s' % (act, nm), 1, 0x0B, rule=(0, 0x0B, act, 5), ret='1505A9B0=%08X' % ang)
setup('p2', 1, 0x0B, rule=(0, 0x0B, 2, 4))
setup('p3s', 1, 0x0B, rule=(3, 0x0B, 2, 4), stunned=1)
setup('p3n', 1, 0x0B, rule=(3, 0x0B, 2, 4), stunned=0)
setup('p4s', 1, 0x0B, rule=(4, 0x0B, 2, 4), stunned=1)
setup('p4n', 1, 0x0B, rule=(4, 0x0B, 2, 4), stunned=0)
setup('p4m', 1, 0x0B, rule=(0, 0x0B, 4, 6))
setup('p0e', 1, 0x0B, rule=(0, 0x0B, 0x0E, 6))
setup('p5c', 1, 0x0B, rule=(5, 0x0B, 3, 6))
setup('p42', 1, 0x0B, rule=(0, 0x0B, 0x42, 6))
setup('t10d', 10, 0x21, health=3, damage=0x11, mask=7)
