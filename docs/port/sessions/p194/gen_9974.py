# P194: setups for func_15119974 (rec 0x80410000)
import sys
def h(v): return '%08X' % (v & 0xFFFFFFFF)
R = []
for y in (0, 100, -100, 32000):
    for ph in (0, 0x80, 0x100, 0xFFFF, 0x8000):
        for amp in (0, 256, -512, 1000):
            for base in (0, 0x80000000 | 50, 0x8000FF00, 0x00000020):
                for spd in (0, 1, 7, 300, -5):
                    if (ph + amp + spd) % 3 and y != 0: continue
                    p = {0x80410010: (0x1111 << 16) | (y & 0xFFFF), 0x8041003C: (ph << 16) | 0x2345, 0x80410070: 0xAAAAAAFF,
                         0x8041007C: spd, 0x80410080: amp, 0x80410084: base}
                    R.append('y%d_p%X_a%d_b%X_v%d ! 0=80410000 ! %s ! ! ! ! !' % (y, ph, amp, base, spd,
                             ','.join('%08X=%s' % (a, h(v)) for a, v in sorted(p.items()))))
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
