import random
R = random.Random(0xAB20)
lines = []
for n in range(90):
    idv = R.choice([0x00, 0x00, 0x9A, 0x1E, 0x18, 0x52, 0x54, 0x96, 0x10])
    mode = R.choice([0, 1, 2, 3, 4, 5, 6, 0, 7]); timer = R.choice([0, 0, 5, 40, 0xFFFF, 200])
    phase = R.choice([0, 1, 0x0305, 0xFFFF, 2])
    angs = [R.randint(-40, 40) & 0xFFFF for _ in range(4)]; ofs = [R.randint(-25, 25) & 0xFF for _ in range(4)]
    tgt = R.choice(['none', 'pt', 'pt'])
    pk = {0x800CC6F4: idv << 24, 0x800CC8C4: 0x80480000, 0x800CC964: mode << 8, 0x800CC968: (phase << 16) | angs[0],
          0x800CC96C: (angs[1] << 16) | angs[2], 0x800CC970: (angs[3] << 16) | timer,
          0x800CC974: (ofs[0] << 24) | (ofs[1] << 16) | (ofs[2] << 8) | ofs[3],
          0x800CC9E8: R.choice([0, 4]), 0x800CCA0C: 0x80490000, 0x80490078: R.choice([0x2A000000, 0]),
          0x800CC774: R.choice([0x260000, 0]), 0x800BEE04: R.choice([1, 2, 3]), 0x800BEDE0: 0,
          0x800D20B0: R.choice([0x804A0000] * 4 + [0]), 0x804A002C: R.choice([0x1E14280F, 0xF00A1E05]),
          0x800C43FC: R.choice([0, 0, 0x01000000]), 0x800C4400: 0x41200000, 0x800C4404: R.choice([0xC0A00000, 0x41F40000, 0xC1780000]),
          0x804B0048: 0x804C0000, 0x804C03E8: R.choice([0x804D0000, 0])}
    if tgt == 'none': pk.update({0x800C43F0: 0xC7C34F80, 0x800C43F4: 0xC7C34F80, 0x800C43F8: 0xC7C34F80})
    else: pk.update({0x800C43F0: 0x41200000, 0x800C43F4: 0x41A00000, 0x800C43F8: 0xC1F00000})
    for i in range(16): pk[0x80480000 + 12 * 64 + 4 * i] = R.choice([0x3F800000, 0, 0x3F000000, 0xBF000000, 0x42C80000])
    ret = '150220CC=%s,15031C4C=%s' % (R.choice(['0', '0', '1']), R.choice(['804B0000', '0']))
    poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
    lines.append('n%02d_i%02X_m%d_t%X_%s ! 0=800CC6F0 ! %s ! %s !' % (n, idv, mode, timer, tgt, poke, ret))
for n in range(6):
    pk = {0x800CC6F4: 0, 0x800CC8C4: 0x80480000, 0x800CC964: 4 << 8, 0x800CC968: 0, 0x800CC96C: 0, 0x800CC970: 40,
          0x800CC974: (0xED - n) << 24, 0x800CC774: 0x260000, 0x800BEE04: 2, 0x800D20B0: 0x804A0000, 0x804A002C: 0x1E14280F}
    poke = ','.join('%08X=%08X' % kv for kv in sorted(pk.items()))
    lines.append('nod%d ! 0=800CC6F0 ! %s ! 150220CC=0 !' % (n, poke))
print('\n'.join(lines))
