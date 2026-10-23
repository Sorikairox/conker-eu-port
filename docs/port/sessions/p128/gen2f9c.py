#!/usr/bin/env python3
# P128: setups for func_15052F9C. obj at 80400000, player D_800CC2D0 (EU 800CC6F0, 0x32C each), state block at
# 80420000, partner record (func_15034174 return) at 80450000 (+6 = partner id). D_800BE9F0 EU 800BEE10,
# D_800C3E78 EU 800C4298.
B = 0x800CC6F0
for idx in (1,):
    P = B + 0x32C * idx
    cases = []
    for oid in (0x48, 0x30):
        for part in (0x7A, 0x7B, None):
            if oid != 0x48 and part != 0x7A: continue
            for st in (0x20, 0x21):
                for lvl in (6, 7):
                    if (st != 0x20 or oid == 0x48) and lvl == 7: continue
                    for force, py, vy in ((1, '43000000', '3F800000'), (0, '42000000', 'BF800000'), (0, '43000000', 'BF800000'), (0, '42000000', '3F800000')):
                        if force == 0 and (st != 0x20 or part != 0x7A) and py != '42000000': continue
                        cases.append((oid, part, st, lvl, force, py, vy))
    for n, (oid, part, st, lvl, force, py, vy) in enumerate(cases):
        snd = 0x55 if n % 2 else 0
        rst = 1 if n % 3 == 1 else 0
        poke = ['80400000=%08X' % st, '80400004=%02X000000' % oid, '80400124=%02X000000' % idx, '80400018=42A00000',
                '80400150=3F000000', '80400078=0000C123', '80400064=00000000', '80400100=00110000', '8040005C=00000000',
                '%08X=00000000' % (P + 0x88), '%08X=%s' % (P + 0x18, py), '%08X=%s' % (P + 0x20, vy), '%08X=80420000' % (P + 0x31C),
                '%08X=00220000' % (P + 0x100), '%08X=00000000' % (P + 0x64),
                '800BEE10=%08X' % lvl, '800C4298=07000000', '80450004=0000%02X00' % (part or 0)]
        ret = '15034174=%s' % ('80450000' if part else '0')
        print('c%d ! 0=80400000,1=42480000,2=1C,3=6,4=%X,5=1F7,6=FF,7=8,8=%X,9=%X ! %s ! %s ! ! ! '
              % (n, rst, force, snd, ','.join(poke), ret))
