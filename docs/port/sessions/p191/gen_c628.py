# P191: setups for the D_8008ADA0 handlers func_151AC628 (chunk) / func_151ACBCC (dust): the level-0 call shape of
# func_1514CBE8 (mode 2, debris_burst_spawn owner block {src, arg, light}) for the ROM kinds, lights and angles.
# usage: gen_c628.py c628|cbcc > setups.txt
import sys
which = sys.argv[1]
def f(v):
    import struct; return '%08X' % struct.unpack('>I', struct.pack('>f', v))[0]
rows = []
def row(name, kind, light, a, fr, mode=2, i=3, argB=0x1F4, src=0x80420000):
    args = {0: mode, 1: i, 2: f(200.0), 3: f(100.0), 4: f(-200.0), 5: f(190.0), 6: f(100.0), 7: f(-210.0), 8: a, 9: 0x10,
            10: f(10.0), 11: kind, 12: f(1.5), 13: 0x80410000, 14: argB}
    arg = ','.join('%d=%X' % (k, (v if isinstance(v, int) else int(v, 16)) & 0xFFFFFFFF) for k, v in args.items())
    poke = '80410000=%08X,80410004=00000007,80410008=%02X000000' % (src, light)
    rand = '150ADF48=' + ';'.join(f(x) for x in fr)
    rows.append('%s ! %s ! %s ! ! %s ! ! !' % (name, arg, poke, rand))
for kind in (0, 1, 2, 3, 4, 5):
    row('k%d' % kind, kind, 0, 0x37, (0.3, 0.5, 0.25, 0.75))
    row('k%dn' % kind, kind, 6, 0x37, (0.7, 0.9, 0.1, 0.2))
for light in (5, 0xB, 7, 0xF):
    row('l%X' % light, 1, light, 0xC0, (0.49, 0.2, 0.6, 0.4))
row('a1A5', 2, 3, 0x1A5, (0.51, 0.8, 0.3, 0.6))
row('aneg', 3, 8, -0x30, (0.1, 0.33, 0.66, 0.99))
row('bFF', 1, 2, 0x80, (0.6, 0.5, 0.5, 0.5), argB=0x12345FF, mode=0, i=0)
print('\n'.join(rows))
