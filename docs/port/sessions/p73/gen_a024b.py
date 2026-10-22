# targeted setups for func_1509A024 survivors: base = setup c<CMD>_0 of a024.txt, plus extra pokes / knobs
# (later POKE / RET / OUTW entries override earlier ones).
import struct
def h(f): return struct.unpack('>I', struct.pack('>f', f))[0]
base = {}
for l in open('/Users/sorikairo/conker-wt/portb/docs/port/sessions/p73/a024.txt'):
    f = l.split('!'); base[f[0].strip()] = [x.strip() for x in f]
O, A, R = 0x80430000, 0x80420000, 0x80450000
T = [
    ('tB1a', 'B1', {O: 0x27}, '', ''), ('tB1b', 'B1', {O: 8}, '', ''),
    ('t95', '95', {O + 0x13C: 0x66000000}, '', ''),
    ('t98', '98', {O + 0x18: h(70000.0)}, '', ''),
    ('t9E', '9E', {A + 8: 7, A + 12: 26, A + 16: 5}, '', ''),
    ('tA6', 'A6', {O + 0x1CC: h(170.5)}, '', ''),
    ('tCB', 'CB', {}, '150ACEA0=1', '150ACEA0=10:0/11:447A0000'),
    ('tCC', 'CC', {}, '150A3674=804B0270', ''),
    ('tCF', 'CF', {A + 8: 2}, '150871B8=FE', ''),
    ('tD3a', 'D3', {R + 0x74: 0x00210000}, '', ''), ('tD3b', 'D3', {R + 0x74: 0x003F0000}, '', ''),
    ('tD7', 'D7', {O + 0x1CC: h(570.0), O + 0x118: 0xC61C4000}, '', ''),
    ('tE7', 'E7', {A + 12: 1, A + 16: 20, 0x80480000: 0x0032000A, 0x80480004: 0x00460000,
                   0x80480008: 0x7FFF0000, 0x8048000C: 0x7FFF0000, 0x80480010: 0x7FFF0000, 0x80480014: 0x7FFF0000}, '', ''),
    ('tEB', 'EB', {A + 8: 7, A + 12: 26, A + 16: 5}, '', ''), ('tF1', 'F1', {O + 0x74: 0x07000000}, '', ''),
    ('tC8', 'C8', {O + 0x20C: 5, O + 0x210: 0x00060000, O + 0x214: 0}, '', '1508712C=1:41700000;41700000/2:41E00000;41E00000/3:41F00000;41F00000'),
]
for n, c, pk, ret, outw in T:
    b = list(base['c%s_0' % c])
    b[0] = n
    if pk: b[2] = b[2] + ',' + ','.join('%X=%08X' % kv for kv in pk.items())
    if ret: b[3] = b[3] + ',' + ret
    if outw: b[6] = outw
    print(' ! '.join(b))
