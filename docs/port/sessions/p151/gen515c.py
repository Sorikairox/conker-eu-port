# P151: setups for func_1507515C. D_800CC2D0 EU 0x800CC6F0, 26 objects of 0x32C.
B = 0x800CC6F0
def setup(name, owner, objs):
    # objs: {index: (state, id, u65)}; all others state 0
    pk = []
    for i in range(26):
        st, id_, u = objs.get(i, (0, 1, owner + 1))
        a = B + i * 0x32C
        pk += ['%X=%08X' % (a, st), '%X=%08X' % (a + 4, id_ << 24), '%X=%08X' % (a + 0x64, u << 16)]
    print(' ! '.join([name, '0=%X' % (B + owner * 0x32C), ','.join(pk), '', '', '', '', '']))
setup('none', 2, {})
for t in range(26):
    setup('t%d' % t, 3, {t: (1, 5, 4)})
setup('ff', 1, {0: (1, 0xFF, 2), 4: (1, 0xFE, 2)})
setup('wrong', 1, {0: (1, 3, 1), 1: (1, 3, 3), 7: (1, 3, 2)})
setup('dead', 0, {0: (0, 3, 1), 9: (5, 3, 1)})
setup('two', 5, {3: (1, 3, 6), 8: (1, 3, 6)})
setup('o25', 25, {24: (1, 3, 26)})
setup('neg', 0, {10: (-1, 3, 1)})
