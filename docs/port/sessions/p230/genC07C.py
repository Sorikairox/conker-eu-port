#!/usr/bin/env python3
# P230: setups for func_1508C07C (rail_lane_shuffle). D_8008FD8C = EU 8009012C (s8 count), D_800D27D0 = 800D27D0
# -> 80450000 (rows at +0x15B4). func_150ADA68 = jal 150ADF48 (RETF list: start column / direction per row).
import struct
def fb(f): return '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
def setup(name, n, rnd):
    print('%s ! ! 8009012C=%08X,800D27D0=80450000 ! ! 150ADF48=%s ! ! ! !' % (name, (n & 0xFF) << 24, ';'.join(fb(x) for x in rnd)))
setup('n0', 0, [0.3])
setup('nneg', -2, [0.3])
setup('n1', 1, [0.0, 0.9])
setup('n2', 2, [0.6, 0.2, 0.1, 0.9])
setup('n3', 3, [0.1, 0.7, 0.1, 0.7, 0.1, 0.2])
setup('n4', 4, [0.9, 0.1, 0.9, 0.9, 0.5, 0.5, 0.26, 0.51])
setup('n5', 5, [0.5, 0.6, 0.5, 0.4, 0.5, 0.6, 0.99, 0.1, 0.0, 0.8])
setup('n6', 6, [0.2, 0.5, 0.2, 0.50001, 0.2, 0.3, 0.2, 0.7, 0.2, 0.1, 0.2, 0.9])
setup('n7', 7, [0.95, 0.9, 0.95, 0.1, 0.95, 0.9, 0.3, 0.3, 0.3, 0.6, 0.0, 0.0, 0.5, 0.5])
setup('n8', 8, [0.0, 0.1, 0.0, 0.1, 0.0, 0.9, 0.99, 0.2, 0.5, 0.6, 0.5, 0.4, 0.3, 0.3, 0.7, 0.7])
setup('n9', 9, [0.4, 0.8] * 9)
setup('n16', 16, [0.0, 0.2, 0.99, 0.2] * 8)
setup('n13', 13, [0.5, 0.7, 0.25, 0.1] * 7)
