import random
R = random.Random(28)
def vtx(n, end, seg): return (0x01000000 | (n << 12) | (end * 2), seg)
lines = []
for s in range(40):
    cmds = [vtx(32, 32, 0x06000038 + 16 * R.choice([0, 0x40]))]
    for _ in range(R.randint(3, 14)):
        c = R.random()
        if c < 0.3:
            n = R.randint(1, 8); end = R.randint(n, 32)
            seg = 0x06000038 + 16 * R.choice([R.randint(0, 60), 0, 4, 8, 32, 36])
            cmds.append(vtx(n, end, seg))
        elif c < 0.45: cmds.append((0xDA380003, 0x01000000 | (R.choice([0, 1, 2, 3]) << 6) | R.randint(0, 63)))
        elif c < 0.6: cmds.append((0x05000000 | (R.randint(0, 31) * 2 << 16) | (R.randint(0, 31) * 2 << 8) | R.randint(0, 31) * 2, 0))
        elif c < 0.75:
            b = [R.randint(0, 31) * 2 for _ in range(6)]
            cmds.append((0x06000000 | b[0] << 16 | b[1] << 8 | b[2], b[3] << 16 | b[4] << 8 | b[5]))
        elif c < 0.9: cmds.append(((R.randint(0x10, 0x1F) << 24) | R.getrandbits(24), R.getrandbits(32)))
        else: cmds.append((R.choice([0xE7000000, 0xFC000000, 0x02000000, 0x20000000]), R.getrandbits(32)))
    cmds.append((0xDF000000, 0))
    pk = {0x800C6030: 0, 0x800C48B0: 0x80481010, 0x80481010: 0x80482000, 0x800C5D3C: 0x00400000, 0x800D1DC8: 0x80490000}
    for i, (a, b) in enumerate(cmds): pk[0x80482000 + 8 * i] = a; pk[0x80482004 + 8 * i] = b
    ret = R.choice(['80483000;80484000'] * 6 + ['0', '80483000;0'])
    pre = R.random() < 0.05
    if pre: pk[0x800C6030] = 0x80483000
    poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
    lines.append('s%02d_n%d_%s%s ! 0=2 ! %s ! 10003E90=%s !' % (s, len(cmds), 'ok' if ret.startswith('80483000;8') else 'fail', '_pre' if pre else '', poke, ret))
print('\n'.join(lines))
