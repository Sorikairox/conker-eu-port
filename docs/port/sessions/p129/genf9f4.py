# P129: setups for func_1508F9F4 (knobs fields name ! ARG ! POKE). Run with DIFFTEST_STKFILL=8067FEF4=800BEDF0
# (port_work/p129/dts.sh: the N64 value of the spawn flag slot). Records 0x800D2880 + 16k, timer 0x800D28E0,
# frames 0x800BEE04, object 0 = 0x800CC6F0 (+0xAD flag, +0xB2 value).
import random
r = random.Random(1508); out = []
vals = [0x5A, 0x5B, 0xEF, 0xF0, 0x59F, 0x5A0, 0x7D0, 0xFFFF, 0x100, 0x300]
for n in range(36):
    frames = r.choice([1, 1, 2, 3, 0, 7, 0x40])
    timer = r.choice([0, 0, 0, 1, frames, 10, -1 & 0xFFFFFFFF])
    flag = r.choice([0, 1, 1, 1]); val = vals[n % len(vals)]
    pk = ['800BEE04=%08X' % frames, '800D28E0=%08X' % timer, '800CC79C=00%02X0000' % flag, '800CC7A0=0000%04X' % val]
    for k in range(6):
        a = 0x800D2880 + 16 * k
        st = r.choice([0, 0, 1, 2, 2, 3, 3, 4])
        xs = [r.randrange(0x10000) for _ in range(6)]
        if st == 1: xs[3] = r.choice([0x600, 0x665, 0x500, 0x7FFF, 0x8000, r.randrange(0x10000)])
        if st in (2, 3): xs[5] = r.choice([0, 1, frames, frames + 1, 0x8000, 0xFFFF, r.randrange(0x10000)])
        c = r.choice([0, 0x1F, 0x20, 0x21, 0xFF, r.randrange(256)])
        pk += ['%08X=%04X%04X' % (a, xs[0], xs[1]), '%08X=%04X%04X' % (a + 4, xs[2], xs[3]),
               '%08X=%04X%04X' % (a + 8, xs[4], xs[5]), '%08X=%02X%02X%02X%02X' % (a + 12, c, st, r.randrange(256), r.randrange(256))]
    out.append('s%d ! ! %s' % (n, ','.join(pk)))
print('\n'.join(out))
