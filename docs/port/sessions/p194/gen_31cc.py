# P194: setups for func_151831CC (rec 0x80410000, buffers 0x8042xxxx, src verts 0x80430000, nodes 0x80440000+0x200w,
# D_800DBEF4 (EU 0x800DC324) -> 0x80450000; D_800BE9C0 = EU 0x800BEDE0). func_151834C8 RETF, func_150A7E40 OUTW 4/5/6.
import sys, struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def h(v): return '%08X' % (v & 0xFFFFFFFF)
R = []
def row(name, w, frame, counts, posf, outs, verts, heights):
    p = {0x80410010: ((100 & 0xFFFF) << 16) | (-50 & 0xFFFF), 0x80410014: (7 << 16) | 0x1234,
         0x80410020: 0x80420000, 0x80410024: 0x80420800, 0x80410028: 0x80430000, 0x8041003C: w,
         0x800DE284: 0x00010203, 0x800DC324: 0x80450000, 0x800BEDE0: frame << 24,
         0x80450014: counts[0], 0x804500B4: counts[1]}
    for k in range(4): p[0x800DE290 + 4 * k] = 0x80440000 + 0x200 * k
    for i, (x, y, z) in enumerate(verts):
        p[0x80430000 + i * 16] = ((x & 0xFFFF) << 16) | (y & 0xFFFF); p[0x80430004 + i * 16] = (z & 0xFFFF) << 16 | 0x5555
    for n in range(40): p[0x80440000 + 0x200 * w + n * 12 + 8] = int(fb(heights(n)), 16)
    pk = ','.join('%08X=%s' % (a, h(v)) for a, v in sorted(p.items()))
    retf = '151834C8=' + ';'.join(fb(x) for x in posf)
    outw = '150A7E40=' + '/'.join('%d:%s' % (4 + j, ';'.join(fb(o[j]) for o in outs)) for j in range(3))
    R.append('%s ! 0=80410000 ! %s ! ! %s ! ! %s !' % (name, pk, retf, outw))
V = [(10, 20, 30), (-40, 5, -300), (1000, -7, 77), (3, 3, 3)]
O = [(1.5, -2.25, 3.0), (-100.75, 50.5, 0.25), (20000.0, -31000.0, 7.5), (0.0, 0.0, 0.0)]
H = [lambda n: n * 3.5 - 40.0, lambda n: (n * 37 % 11) * 17.25 - 60.0, lambda n: 1000.0 - n * 61.0]
for w in range(4):
    for fr in (0, 1):
        for hi, hf in enumerate(H):
            for pi, pf in enumerate([(3.25, 0.0, 38.5, 12.75), (39.0, 38.0, 0.5, 20.0), (7.9, 1.1, 39.0, 0.0)]):
                for cnt in ((3, 2), (4, 1), (0, 0)):
                    if (cnt == (0, 0)) and (hi or pi): continue
                    R.append(None) if False else row('w%d_f%d_h%d_p%d_c%d%d' % (w, fr, hi, pi, cnt[0], cnt[1]), w, fr, cnt, pf, O, V, hf)
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
