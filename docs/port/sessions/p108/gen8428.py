# P108 setups for func_15148428 (trail step). obj 80430000, rec 80430200, pts 80430400.
import itertools, random
random.seed(8428)
O, R, P = 0x80430000, 0x80430200, 0x80430400
tbl = {0x8008A784: 0x15148E34, 0x8008A788: 0x15149064, 0x8008A79C: 0x1518CAB0, 0x8008A7D4: 0x15149638}  # 1-arg handler: a3 at the end-handler call is a leftover register
n = 0
for h0, h1, h2, ret0, ret1, fl, cnt in itertools.product((0, 1, 2), (0, 1), (0, 2), (0, 1), (0, 1), (0, 0x40), (0, 1, 3)):
    if h0 == 0 and ret0: continue
    if h1 == 0 and ret1: continue
    if random.random() < 0.55: continue
    timer = random.choice((1, 5, 0x20, -3, 0x10, 0x10)); lim = random.choice((0x10, 0x40)); rate = random.choice((3, 8, 0x30))
    alpha = random.choice((0x10, 0x80, 0xFF))
    tail = random.randrange(0, 4)
    pk = dict(tbl)
    pk[O + 0x1C] = ((timer & 0xFFFF) << 16) | 0x35
    pk[O + 0x2C] = (cnt << 24) | (tail << 16) | (((tail + cnt) % 5) << 8) | 1
    pk[O + 0x24] = (5 << 16)  # +0x25 = capacity 5
    pk[O + 0x94] = P; pk[O + 0x98] = R
    pk[R + 0x18] = (fl << 24) | (1 << 16) | (0xFF << 8) | alpha
    pk[R + 0x1C] = (lim << 16) | rate
    pk[R + 0x20] = (h0 << 24) | (h1 << 16) | (h2 << 8)
    for i in range(5):
        for k in range(3):
            pk[P + i * 0x14 + k * 4] = random.getrandbits(32) & 0x7FFFFFFF
    rets = []
    if h0: rets.append('%08X=%X' % (tbl[0x8008A780 + 4 * h0], ret0))
    if h1: rets.append('%08X=%X' % (0x1518CAB0, ret1))
    print('t8428_%d ! 0=%08X,3=0 ! %s ! %s !  !  !  ! ' % (n, O, ','.join('%08X=%08X' % kv for kv in sorted(pk.items())), ','.join(rets)))
    n += 1
