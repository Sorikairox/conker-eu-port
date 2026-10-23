#!/usr/bin/env python3
# P128: setups for func_1505327C. obj at 80400000 (unk124 = player index), player records D_800CC2D0 (EU 800CC6F0,
# 0x32C each), player state block at 80420000, path table at 80430000.
B = 0x800CC6F0
out = 'ARG0'
for idx in (0, 2):
    P = B + 0x32C * idx
    for dr, st, b6b in ((0, 0, 0), (0, 0, 1), (1, 0, 0), (0, 0x80, 0)):
        for path, pt in ((0, 0), (0x80430000, 0xFFFFFFFF), (0x80430000, 3), (0x80430000, 0)):
            if (dr or st or b6b) and path: continue
            poke = ['80400124=%02X000000' % idx, '804001D4=%08X' % path, '80400078=1234ABCD', '80400014=42C80000',
                    '8040001C=C3480000', '80400218=80450000', '80400230=00000000',
                    '%08X=00%02X0000' % (P + 0x88, dr), '%08X=%02X000000' % (P + 0x104, st), '%08X=80420000' % (P + 0x31C),
                    '%08X=00000000' % (P + 0x124), '%08X=00000000' % (P + 0x20), '%08X=00000000' % (P + 0x80),
                    '80420068=%08X' % (b6b << 16), '80420024=00000000', '80420028=00000000', '8042002C=00000000', '80420030=00000000']
            print('i%dd%ds%dk%dq%dp%X ! 0=80400000,1=421C0000,2=40400000,3=1F2,4=%X ! %s ! ! ! 150442E0=0:41200000;42000000;C2480000 ! '
                  % (idx, dr, st, b6b, path != 0, pt & 0xF, pt, ','.join(poke)))
