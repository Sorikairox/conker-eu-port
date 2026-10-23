#!/usr/bin/env python3
"""P117: setups for func_151EE704 (menu_sprites_load). jal keys: allocate_memory 10003E90, func_1502B6BC 1502B9AC."""
S = []
def asset(k, cmds):
    a = 0x80490000 + k * 0x1000; p = ['%08X=%08X' % (a, a + 0x10)]
    for i, (w0, w1) in enumerate(cmds):
        p += ['%08X=%08X' % (a + 0x10 + 8 * i, w0), '%08X=%08X' % (a + 0x14 + 8 * i, w1)]
    return a, p
def setup(name, cmdsf, alloc='80480000'):
    rets, pk = [], []
    for k in range(30):
        a, p = asset(k, cmdsf(k)); rets.append('%08X' % a); pk += p
    S.append('%s ! ! %s ! 10003E90=%s,1502B9AC=%s ! ! ! ! !' % (name, ','.join(pk), alloc, ';'.join(rets)))
setup('mix', lambda k: [(0x01020040, 0x100), (0xFC000000, 0x12345678), (0xEF000000, 0x00000001), (0xE7000000, 5), (0x01000000, 0x200 + k), (0xDF000000, 0)])
setup('plain', lambda k: [(0xDF000000, 0x77)])
setup('order', lambda k: [(0xEF003000, 0xAAAA), (0xFC111111, 1), (0x01FF0000, 0x300), (0x02000000, 9), (0xDF123456, 0x55)])
setup('fail', lambda k: [(0xDF000000, 0)], alloc='00000000')
print('\n'.join(S))
