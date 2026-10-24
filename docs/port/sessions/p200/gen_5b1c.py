#!/usr/bin/env python3
# P200: setups for func_15155B1C (effect_overlap_find). lists D_800DD280[bank][0x5D / 0x57] (EU = US address), nodes at 80460000 + 0x40 * n.
import struct
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def g(name, lists, nodes, pos=(100.0, 50.0), ext=(10.0, 5.0), kinds=(3, 7), count=None):
    # lists: {(bank, list): [node indices]}; nodes: {n: (kind, x, y, hx, hy)}
    p = ['80450000=%s' % f(pos[0]), '80450004=%s' % f(pos[1]), '80450010=%s' % f(ext[0]), '80450014=%s' % f(ext[1])]
    for i, k in enumerate(kinds): p.append('%08X=%08X' % (0x80450020 + 4 * i, k & 0xFFFFFFFF))
    for b in (0, 1):
        for l in (0x5D, 0x57):
            ch = lists.get((b, l), [])
            p.append('%08X=%08X' % (0x800DD280 + b * 0x1A0 + l * 4, 0x80460000 + 0x40 * ch[0] if ch else 0))
            for i, n in enumerate(ch):
                p.append('%08X=%08X' % (0x80460008 + 0x40 * n, 0x80460000 + 0x40 * ch[i + 1] if i + 1 < len(ch) else 0))
    for n, (k, x, y, hx, hy) in nodes.items():
        b = 0x80460000 + 0x40 * n
        p += ['%08X=%s' % (b + 0x10, f(x)), '%08X=%s' % (b + 0x14, f(y)), '%08X=%s' % (b + 0x18, f(hx)), '%08X=%s' % (b + 0x1C, f(hy)), '%08X=0000%02X00' % (b + 0x28, k)]
    print('%s ! 0=80450000,1=80450010,2=80450020,3=%X ! %s ! ! ! ! ! ' % (name, (len(kinds) if count is None else count) & 0xFFFFFFFF, ','.join(p)))
print('# P200 func_15155B1C (gen_5b1c.py)')
N = {0: (3, 100, 50, 2, 2), 1: (7, 300, 50, 2, 2), 2: (9, 100, 50, 2, 2)}
g('hit0', {(0, 0x5D): [0]}, N)
g('hit57', {(0, 0x57): [0]}, N)
g('hitbank1', {(1, 0x5D): [0]}, N)
g('hitbank1_57', {(1, 0x57): [2, 0]}, N)
g('kindno', {(0, 0x5D): [2]}, N)
g('kindlast', {(0, 0x5D): [0]}, N, kinds=(7, 3))
g('kindfirst', {(0, 0x5D): [0]}, N, kinds=(3, 7, 8))
g('count1', {(0, 0x5D): [0]}, N, kinds=(7, 3), count=1)
g('count0', {(0, 0x5D): [0]}, N, count=0)
g('countneg', {(0, 0x5D): [0]}, N, count=0xFFFFFFFF)
g('far', {(0, 0x5D): [1]}, N)
g('chain', {(0, 0x5D): [2, 1, 0]}, N)
g('empty', {}, N)
for nm, (x, y) in {'xlo': (88, 50), 'xlo_in': (88.01, 50), 'xhi': (112, 50), 'xhi_out': (112.01, 50), 'ylo': (100, 43), 'ylo_out': (100, 42.99),
                   'yhi': (100, 57), 'yhi_out': (100, 57.01)}.items():
    g('edge_' + nm, {(0, 0x5D): [0]}, {0: (3, x, y, 2, 2)})
g('kind_hi', {(0, 0x5D): [0]}, {0: (0x83, 100, 50, 2, 2)}, kinds=(0xFFFFFF83, 0x83))
g('kind_hi_neg', {(0, 0x5D): [0]}, {0: (0x83, 100, 50, 2, 2)}, kinds=(0xFFFFFF83,))
