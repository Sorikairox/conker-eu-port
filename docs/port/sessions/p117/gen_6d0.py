#!/usr/bin/env python3
"""P117: setups for func_151E06D0 (title_slot_page). Record 80480000; slots D_800BE818 (16 bytes each)."""
S = []
def slot(k, t, score, used, e=5):
    a = 0x800BE818 + 16 * k
    return '%08X=%08X,%08X=%08X,%08X=%08X,%08X=1100%02X33' % (a, t, a + 4, score, a + 8, used & 0xFFFFFFFF, a + 12, e & 0xFF)
for tp in (3, 4, 5):
    for used in (-1, 0, 7):
        for sel in (0, 1, 2, 3):
            for inp in (0, 8, 0x10, 0x20, 0xC):
                pk = ['80090174=80480000', '80480020=%04X0000' % inp, '8048002C=%02X000000' % tp, '800901CC=%02X000000' % sel,
                      '800E0EC4=A0000000'] + [slot(k, 3725 + 1000 * k, 0x7D00 if (k == tp - 3 and sel == 1) else 1234 + k, used, k - 1) for k in range(3)]
                S.append('t%d_u%d_s%d_i%X ! ! %s ! ! ! ! !' % (tp, used, sel, inp, ','.join(pk)))
print('\n'.join(S))
