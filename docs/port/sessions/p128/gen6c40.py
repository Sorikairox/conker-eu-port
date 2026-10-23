#!/usr/bin/env python3
# P128: setups for func_150A6C40 (PVS row decode): tree at 80430000 (codes 0 -> A5, 10 -> 3C, 11 -> FF; one setup
# with 3-level codes), stream at 80410000, row index at 80420000, records at 80440000.
import random
random.seed(6)
tree = ['80430000=FFFF0006', '80430004=000C00A5', '80430008=00000000', '8043000C=FFFF0012',
        '80430010=0018003C', '80430014=00000000', '80430018=00FF0000', '8043001C=00000000']
tree3 = ['80430000=FFFF0006', '80430004=000C0013', '80430008=00000000', '8043000C=FFFF0012',
         '80430010=0018FFFF', '80430014=001E0024', '80430018=00800000', '8043001C=0000007F',
         '80430020=00000000', '80430024=00010000', '80430028=00000000']
rows = ['80420000=00000000', '80420004=00020005', '80420008=FFFF0000', '8042000C=00070003', '80420010=0001FFFF', '80420014=00030009']
def stream():
    return ['%08X=%08X' % (0x80410000 + 4 * i, random.getrandbits(32)) for i in range(8)]
def recs(n, alt_every):
    out = []
    for i in range(n):
        a = 0x80440000 + 0x10 * i
        vis = random.getrandbits(16); last = i == n - 1
        use_alt = i + 2 <= n - 1 and alt_every and i % alt_every == 1
        nxt = 0 if (last or use_alt) else 0x10
        alt = 0x20 if use_alt else 0
        out += ['%08X=%04X%04X' % (a, vis, random.getrandbits(16)), '%08X=%04X0000' % (a + 4, alt),
                '%08X=%04X0000' % (a + 0xC, nxt)]
    return out
k = 0
for view in range(4):
    for row in range(6):
        for n, ae in ((1, 0), (9, 3), (20, 4)):
            if (view + row + n) % 2 and n == 9: continue
            dc = ['800DC260=%04X%04X' % (row if view == 0 else 0, row if view == 1 else 0),
                  '800DC264=%04X%04X' % (row if view == 2 else 0, row if view == 3 else 0)]
            t = tree3 if k % 3 == 2 else tree
            poke = ['800BE9F0=80410000', '800BE9F4=80420000', '800BE9F8=80430000', '800DC278=80440000'] + dc + rows + t + stream() + recs(n, ae)
            print('v%dr%dn%d ! 0=%X ! %s ! ! ! ! ' % (view, row, n, view, ','.join(poke)))
            k += 1
base = ['800BE9F4=80420000', '800BE9F8=80430000', '800DC260=00010001'] + rows + tree + stream() + recs(3, 0)
print('nostream ! 0=0 ! %s ! ! ! ! ' % ','.join(['800BE9F0=00000000', '800DC278=80440000'] + base))
print('norecs ! 0=1 ! %s ! ! ! ! ' % ','.join(['800BE9F0=80410000', '800DC278=00000000'] + base))
