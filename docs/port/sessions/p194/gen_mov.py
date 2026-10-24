# P194: setups for func_15116F34 / func_1511712C (rec at 0x80410000; D_800BE9E4 = EU 0x800BEE04)
import sys
def h(v): return '%08X' % (v & 0xFFFFFFFF)
def row(name, pos, tgt, snd, spd, handle, dt=2, flags=0):
    p = {0x10: ((pos[0] & 0xFFFF) << 16) | (pos[1] & 0xFFFF), 0x14: (pos[2] & 0xFFFF) << 16,
         0x3C: (snd << 10) | spd, 0x74: (handle & 0xFFFF) << 16, 0x7C: tgt[0], 0x80: tgt[1], 0x84: tgt[2],
         0x58: 0x11112222, 0x5C: 0x33334444, 0x70: flags}
    pk = ','.join('%X=%s' % (0x80410000 + k, h(v)) for k, v in sorted(p.items())) + ',800BEE04=%s' % h(dt)
    return '%s ! 0=80410000 ! %s ! 151152A4=0 ! ! ! !' % (name, pk)
R = []
for snd in (0, 1, 2, 3, 6):
    for hd in (0, 7):
        R.append(row('at_s%d_h%d' % (snd, hd), (10, -20, 30), (10, -20, 30), snd, 5, hd))
mv = [((0, 0, 0), (100, -100, 3)), ((100, -100, 50), (0, 0, 50)), ((5, -5, 9), (7, -7, 8)), ((-300, 200, 1000), (-290, 190, 990)),
      ((0, 0, 0), (0, 0, 40)), ((40, 40, 40), (0, 0, 0)), ((30000, -30000, 0), (32767, -32768, 1)), ((0, 5, 0), (0, 4, 0))]
for snd in (0, 2, 5, 6):
    for hd in (0, 7):
        for i, (a, b) in enumerate(mv):
            for spd in (3, 0x3FF if snd != 5 else 20):
                R.append(row('mv_s%d_h%d_%d_v%X' % (snd, hd, i, spd), a, b, snd, spd | (0x10000 if i == 3 else 0), hd, dt=(1 if i & 1 else 2)))
# arrival window (snd 5: lead 0x1E): remaining distance around lead * speed / 2 = 30 * spd / 2
for spd in (2, 4, 8):
    for d in range(20, 140, 6):
        R.append(row('ar_v%d_d%d_h0' % (spd, d), (0, 0, 0), (d, 0, 0), 5, spd, 0, dt=2))
        R.append(row('ar_v%d_d%d_h7' % (spd, d), (0, 0, 0), (0, -d, d // 2), 5, spd, 7, dt=2))
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
