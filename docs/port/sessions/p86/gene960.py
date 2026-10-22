#!/usr/bin/env python3
"""P86: knob setups for func_150CE960 (in-place zoom). Writes se960.txt. a0 = state at OBJ (flag byte +0x2C, step +0x28,
x0 / y0 / x1 / y1 at +0x30..+0x3C, maps at +0x48 / +0x548), a1 = frame buffer FB (lazy random heap).
D_800BE620 (row width) = 800BEA40."""
import random
OBJ, FB = 0x80480000, 0x80500000
out = []
def setup(name, flag=1, step=0x8000, x0=2, y0=1, x1=9, y1=6, w=16, extra=None):
    wd = {OBJ + 0x2C: '%02X000000' % flag, OBJ + 0x28: '%08X' % step, OBJ + 0x30: '%08X' % (x0 & 0xFFFFFFFF),
          OBJ + 0x34: '%08X' % (y0 & 0xFFFFFFFF), OBJ + 0x38: '%08X' % (x1 & 0xFFFFFFFF), OBJ + 0x3C: '%08X' % (y1 & 0xFFFFFFFF),
          0x800BEA40: '%08X' % w}
    wd.update(extra or {})
    out.append(' ! '.join([name, '0=%08X,1=%08X' % (OBJ, FB), ','.join('%08X=%s' % kv for kv in sorted(wd.items())), '', '', '', '', '']))
setup('half')
setup('off', flag=0)
setup('flag3', flag=3)
setup('flag2', flag=2)
setup('one', step=0x10000)
setup('quarter', step=0x4000, x0=0, y0=0, x1=15, y1=11, w=20)
setup('odd', step=0x9F37, x0=3, y0=2, x1=30, y1=17, w=40)
setup('big', step=0x23456, x0=1, y0=1, x1=12, y1=9)
setup('zero', step=0)
setup('point', x0=5, y0=5, x1=5, y1=5)
setup('row', x0=0, y0=4, x1=20, y1=4, w=24)
setup('col', x0=7, y0=0, x1=7, y1=12)
setup('xinv', x0=9, x1=2)
setup('yinv', y0=6, y1=1)
setup('neg_x0', x0=-1, x1=3, y0=0, y1=3)
# rowMap[y1 + 1] (past the rectangle) equal to rowMap[y1]: the bottom row must not be copied from below
setup('guard', extra={OBJ + 0x548 + 0xC: '00040004'})
setup('third', step=0x5555, x0=0, y0=0, x1=14, y1=10, w=16)
setup('wide', step=0xC000, x0=10, y0=3, x1=60, y1=8, w=64)
rng = random.Random(960)
for k in range(10):
    x0 = rng.randrange(0, 20); y0 = rng.randrange(0, 12); w = rng.choice([24, 32, 40])
    setup('mix%d' % k, flag=rng.choice([1, 1, 0, 0xFF]), step=rng.randrange(0, 0x20000), x0=x0, y0=y0,
          x1=x0 + rng.randrange(0, w - x0), y1=y0 + rng.randrange(0, 14), w=w)
open(__file__.replace('gene960.py', 'se960.txt'), 'w').write('\n'.join(out) + '\n'); print(len(out))
