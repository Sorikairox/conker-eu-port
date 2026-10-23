# P151: setups for func_1514CFF0 (type byte +4, mode D_800BE9F0 @0x800BEE10, sub byte +0x3B)
subs = {0x02: [7, 9, 0xD, 0xE, 0xF, 0x17, 0x19, 8], 0x0A: list(range(6, 0x11)), 0x0E: [1, 8, 2],
        0x07: [0x10, 1], 0x14: [0x10, 1], 0x10: [6, 1], 0x1D: [9, 1]}
rows = []; t = 0
for m in list(range(0x37)) + [0x40, 0xFFFFFFFF]:
    for s in subs.get(m, [1, 0]):
        ty = 0x9C if m == 0x2B and s == 1 else (0x9D if m == 0x2B else t % 0xBD)
        t += 1
        rows.append((m, s, ty))
for ty in range(t, 0xC0):
    rows.append((0x99, 1, ty))
for m, s, ty in rows:
    print('m%x_s%x_t%x ! 0=80480000,1=80481000,2=80481010,3=80481020 ! 800BEE10=%08X,80480004=%02X000000,80480038=000000%02X,80481000=AAAAAAAA,80481010=BBBBBBBB,80481020=CCCCCCCC ! ! ! ! ' % (m, s, ty, m, ty, s))
