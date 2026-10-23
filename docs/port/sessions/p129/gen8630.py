# P129: setups for func_15188630 (knobs: name ! ARG ! POKE ! RET). Entries D_800DFB30 + 0x24 k, count D_800DFBE4,
# frames D_800BE9E4 (0x800BEE04), f32 frame time D_800BE9A4 (0x800BEDC4). sinf 15048050, rand 151EFDD0.
import random, struct
r = random.Random(8630); out = []
f2h = lambda f: struct.unpack('>I', struct.pack('>f', f))[0]
for n in range(48):
    cnt = r.choice([1, 2, 3, 5])
    frames = r.choice([1, 2, 3, 0, 9, 40])
    pk = ['800DFBE4=%08X' % cnt, '800BEE04=%08X' % frames, '800BEDC4=%08X' % f2h(r.choice([1.0, 0.5, 2.0]))]
    for k in range(cnt):
        a = 0x800DFB30 + 0x24 * k
        mode = r.choice([0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4])
        t = r.choice([0.0, 0.25, 0.5, 0.75, 1.0, 0.999, 0.001])
        cols = [r.randrange(256) for _ in range(6)]
        w1c = 0; w20 = 0
        if mode == 1:
            w1c = f2h(r.choice([0.0, 1.0, 6.2, 6.28, 6.3, 3.0])); w20 = r.randrange(1 << 32)
        elif mode == 2:
            w1c = r.choice([0, 3, 6, 7, 8, 0xFFFFFFFF]); w20 = r.choice([0, 0xFFFFFFF8, 0xFFFFFFFE, 0xFFFFFFFF, 1, 5, frames, 0x40]) 
        elif mode == 3:
            st = r.choice([0, 1, 2, 3, 4]); w1c = st
            if st in (0, 2): w20 = f2h(r.choice([1.0, 0.5, 0.0, t, 0.6]))
            else: w20 = r.choice([0, 1, frames, frames + 1, 0x30, 0xFFFFFFF0])
        speed = r.choice([0.05, 0.1, 0.5, 1.0])
        pk += ['%08X=%02X%02X%02X%02X' % (a, *cols[:4]), '%08X=%02X%02X%02X%02X' % (a + 4, cols[4], cols[5], 0x11, 0x22),
               '%08X=%08X' % (a + 0xC, f2h(t)), '%08X=%08X' % (a + 0x10, mode), '%08X=%08X' % (a + 0x14, f2h(speed)),
               '%08X=%08X' % (a + 0x1C, w1c), '%08X=%08X' % (a + 0x20, w20)]
    ret = '151EFDD0=%s' % ';'.join('%08X' % r.choice([0, 1, 2, 29, 30, 31, 59, 0x7FFFFFFF, 0x80000001, 0xFFFFFFFF, r.randrange(1 << 32)]) for _ in range(6))
    out.append('s%d ! ! %s ! %s ! 15048050=%08X;%08X' % (n, ','.join(pk), ret, f2h(r.uniform(-1, 1)), f2h(r.uniform(-1, 1))))
print('\n'.join(out))
