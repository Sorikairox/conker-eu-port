#!/usr/bin/env python3
# P157: setups for func_10010154 / func_10010344 (object sounds) and func_1000F568 (variant pick). usage: gensnd.py snd|f568
import sys, struct
def fb(f): return struct.unpack('>I', struct.pack('>f', f))[0]
O = 0x80480000
def line(name, arg, mem, ret):
    print('%s ! %s ! %s ! %s ! ! ! !' % (name, arg, ','.join('%08X=%08X' % kv for kv in sorted(mem.items())), ','.join('%08X=%X' % kv for kv in ret.items())))
if sys.argv[1] == 'snd':
    print('# object sound setups (gensnd.py snd). name ! ARG ! POKE ! RET')
    def s(name, state=1, typ=0x10, mp=0, pl=0, ctx=0, c94=0, vol=0x4000, a3=300, a4=2500, fd9=0, fa64=0x1234):
        mem = {O: state, O + 4: (typ << 24) | 0x00123400, O + 0x38: 0x00000027, O + 0x13C: mp << 24, O + 0x318: pl, O + 0x31C: ctx,
               O + 0x184: 0x12345678, O + 0x8C: 0x11112222, O + 0x14: fb(-1234.7), O + 0x18: fb(56.2), O + 0x1C: fb(30000.9),
               0x80042378: fd9 << 16, 0x80490094: c94 << 24}
        line(name, '0=1A3,1=%X,2=%X,3=%X,4=%X' % (O, vol & 0xFFFFFFFF, a3 & 0xFFFF, a4), mem, {0x1000FD54: fa64, 0x10010ED8: 0x5678})
    s('dead0', state=0); s('dead5', state=5); s('alive2', state=2)
    s('pl', pl=1); s('pl_fd9', pl=1, fd9=1); s('pl_ctx', pl=1, ctx=0x80490000, c94=1); s('pl_ctx2', pl=1, ctx=0x80490000, c94=2)
    s('pl_neg', pl=1, vol=-300); s('neg', vol=-0x2000)
    for t in (0x16, 5, 0x4F, 0x83, 0x8A, 0x23, 0x10):
        s('t%02X' % t, typ=t); s('t%02X_mp' % t, typ=t, mp=1)
    s('t16_lo', typ=0x16, a3=1300, a4=2500); s('t16_eq', typ=0x16, a3=1250, a4=2500); s('t16_neg', typ=0x16, a3=0x9000, a4=100)
    s('t16_big', typ=0x16, a3=0x6000, a4=0x9000)
else:
    print('# func_1000F568 setups (gensnd.py f568). name ! ARG ! POKE ! RET')
    T = 0x80470000
    def f(name, base=0x100, n=3, tbl=T, byte=None, rnd=7):
        mem = {0x800422FC: tbl}
        if byte is not None: mem[T + (base & ~3)] = byte << (8 * (3 - (base & 3)))
        line(name, '0=%X,1=%X,3=1' % (base, n), mem, {0x150ADF00: rnd})
    f('big', base=0x6E2); f('big1', base=0x6E1, byte=0x80); f('n1', n=1); f('n0r', n=1, rnd=0xFFFFFFFF); f('notbl', tbl=0)
    for b in (0x00, 0x7F, 0x80, 0xFF, 0x81, 0x82, 0x84, 0x86, 0x85, 0x83, 0x87, 0xF8, 0xC5):
        for n, r in ((3, 7), (3, 2), (2, 1), (7, 13), (5, 0xFFFFFFFE)):
            f('b%02X_n%d_r%X' % (b, n, r & 0xFFFF), base=0x101, n=n, byte=b, rnd=r)
    f('n8', n=8, byte=0x80, rnd=13); f('n9', n=9, byte=0x80, rnd=0x12345); f('n100', n=100, rnd=0xFFFFFFFF)
