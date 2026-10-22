#!/usr/bin/env python3
"""P87 setup generator for func_1501ECA4 (ECA4) / func_15020F6C (F6C). usage: gen.py eca4|f6c > setups.txt
Writes knobs.sh lines: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB (EU addresses from conker.eu.map)."""
import random, struct, sys

A = dict(EA=0x800C3A0A, POS=0x800C39D0, END=0x800C3A60, LEN=0x800C3A68, N=0x800C3A5A, E8=0x800C39E8,
         CAM=0x800C3D78, ENT=0x800C3A10, KEYS=0x800C3B98, PO=0x800C3C88, CNT=0x800C39F0, LK=0x800C3D80,
         C4=0x800C39C4, A18=0x800C3A18, GCAM=0x800DC420, F671=0x800C3A91)
NONE = -9999.0

class Mem:
    def __init__(s): s.b = {}; s.heap = 0x80430000
    def alloc(s, n):
        a = s.heap; s.heap += (n + 15) & ~15; return a
    def put(s, a, data):
        for i, x in enumerate(data): s.b[a + i] = x
    def w(s, a, v): s.put(a, struct.pack('>I', v & 0xFFFFFFFF))
    def h(s, a, v): s.put(a, struct.pack('>H', v & 0xFFFF))
    def f(s, a, v): s.put(a, struct.pack('>f', v))
    def u8(s, a, v): s.put(a, bytes([v & 0xFF]))
    def poke(s, R):
        ws = {}
        for a in sorted(s.b):
            wa = a & ~3
            if wa not in ws:
                ws[wa] = bytearray(R.getrandbits(32).to_bytes(4, 'big'))
            ws[wa][a - wa] = s.b[a]
        return ','.join('%08X=%08X' % (a, int.from_bytes(v, 'big')) for a, v in sorted(ws.items()))

def fl(R):
    c = R.random()
    if c < 0.08: return NONE
    if c < 0.15: return 0.0
    return round(R.uniform(-300, 300), 2)

def base(R, M, slot, n):
    M.u8(A['EA'] + slot, 1); M.u8(A['EA'] + (1 - slot), R.choice([0, 1, 2]))
    M.u8(A['N'] + slot, n)
    e8 = M.alloc(2 * n); M.w(A['E8'] + 4 * slot, e8)
    cnt = M.alloc(2 * n); M.w(A['CNT'] + 4 * slot, cnt)
    ent = M.alloc(8 * n); M.w(A['ENT'] + 4 * slot, ent)
    cam = M.alloc(0x44 * n); M.w(A['CAM'] + 4 * slot, cam)
    return e8, cnt, ent, cam

def eca4(R, name, slot):
    M = Mem(); n = R.randint(1, 4)
    e8, cnt, ent, cam = base(R, M, slot, n)
    pos = R.randint(0, 300)
    end = pos + R.randint(1, 100) if R.random() < 0.8 else pos - R.randint(0, 20)
    M.w(A['POS'] + 4 * slot, pos); M.w(A['END'] + 4 * slot, end)
    fr = pos * 60 // 50 if pos < end else R.randint(0, 400)
    M.w(A['LEN'], fr); M.f(A['C4'], round(R.uniform(-50, 50), 2))
    for i in range(n):
        M.h(e8 + 2 * i, R.choice([0, 1, 3]))
        p = M.alloc(8); M.w(A['PO'] + slot * 0x78 + 4 * i, p)
        for j in range(3): M.h(p + 2 * j, R.randint(-3000, 3000))
        M.h(ent + 8 * i, R.choice([1, 2, 3, 4, 5, 0, 6]))
        lk = M.alloc(4); M.w(A['LK'] + slot * 0x78 + 4 * i, lk); M.u8(lk, R.choice([0xFF, 0xFF, 0, 2]))
        if R.random() < 0.12:
            M.w(A['KEYS'] + slot * 0x78 + 4 * i, 0); M.h(cnt + 2 * i, R.randint(0, 3)); continue
        keys = []
        for ch in R.sample(range(15), R.randint(1, 8)):
            m = R.randint(1, 6); fs = sorted(R.randint(fr - 150, fr + 150) for _ in range(m))
            if R.random() < 0.3: fs[R.randrange(m)] = fr
            md = R.choice([0, 0, 1, 2])
            keys += [(fl(R), R.choice([md, md, 0, 1]), ch, f) for f in fs]
        # interleave channels, keeping each channel's order
        out = []; byc = {}
        for k in keys: byc.setdefault(k[2], []).append(k)
        while byc:
            c = R.choice(list(byc)); out.append(byc[c].pop(0))
            if not byc[c]: del byc[c]
        kp = M.alloc(8 * len(out)); M.w(A['KEYS'] + slot * 0x78 + 4 * i, kp); M.h(cnt + 2 * i, len(out))
        for j, (v, md, ch, f) in enumerate(out):
            M.f(kp + 8 * j, v); M.u8(kp + 8 * j + 4, md); M.u8(kp + 8 * j + 5, ch); M.h(kp + 8 * j + 6, f)
    rf = '15049AD0=%08X' % struct.unpack('>I', struct.pack('>f', round(R.uniform(-99, 99), 3)))[0]
    return '%s ! 0=%X ! %s !  ! %s' % (name, slot, M.poke(R), rf)

def f6c(R, name, slot):
    M = Mem(); n = R.randint(1, 5)
    e8, cnt, ent, cam = base(R, M, slot, n)
    M.w(A['POS'] + 4 * slot, R.randint(0, 999))
    camidx = R.randrange(n)
    a18 = R.choice([0xFF, camidx, camidx, R.randrange(n)])
    M.u8(A['A18'], a18); M.u8(A['F671'], R.choice([0, 0, 1]))
    g = M.alloc(0x40); M.w(A['GCAM'], g); M.w(g + 0x2C, R.choice([0, 0x40000, R.getrandbits(32)]))
    for i in range(n):
        M.h(e8 + 2 * i, R.choice([1, 1, 1, 0])); M.h(cnt + 2 * i, R.choice([2, 2, 2, 0]))
        M.h(ent + 8 * i, 1 if i == camidx else R.choice([0, 2, 3, 3, 4, 5, 5, 1, 6]))
        M.u8(ent + 8 * i + 2, R.choice([0, 1, 2, 3, 4]) if i == camidx or R.random() < 0.3 else R.randint(0, 40))
        M.u8(ent + 8 * i + 3, R.randrange(n) if R.random() < 0.85 else 0xFF); M.h(ent + 8 * i + 4, R.randint(-500, 500))
        for k in range(17):
            v = fl(R)
            if k == 13: v = R.choice([NONE, -50.0, -20.5, 39.5, -20.0, 0.0, 0.5, 1.0, 12.5, 40.0, 77.0, 255.0, 256.0, 300.0, -3.0])
            if k in (15, 16) and R.random() < 0.5: v = R.choice([NONE, -25.0, 45.0, 3.25, -20.5, 39.5])
            if k in (0, 1, 2, 14): v = round(R.uniform(-3000, 3000), 2)
            if k in (6, 7, 8) and R.random() < 0.35: v = NONE
            M.f(cam + 0x44 * i + 4 * k, v)
    obj = M.alloc(0x40); ent2 = M.alloc(0x90)
    ret = '1502330C=%X,150842F8=%X,15114F2C=%X' % (camidx, R.choice([obj, obj, 0]), R.choice([ent2, ent2, 0]))
    return '%s ! 0=%X ! %s ! %s' % (name, slot, M.poke(R), ret)

def db18(R, name, slot):
    M = Mem(); n = R.randint(1, 4)
    M.u8(A['N'] + slot, n)
    rets = []; outs = []
    for i in range(n):
        if R.random() < 0.15:
            M.w(0x800C3AA8 + slot * 0x78 + 4 * i, 0); continue
        M.w(0x800C3AA8 + slot * 0x78 + 4 * i, M.alloc(0x40))
        for c in range(6):
            rets.append(R.randint(0, 900))
            if R.random() < 0.55:
                k = M.alloc(8); M.u8(k + 5, R.choice([0, 1, 2, 3, 5, 0xFF])); M.h(k + 6, R.choice([1, 1, 0, 2]))
                outs.append(k)
            else:
                outs.append(0)
    if not rets: rets, outs = [0], [0]
    ret = '15023C60=' + ';'.join('%X' % v for v in rets)
    outw = '15023C60=3:' + ';'.join('%X' % v for v in outs)
    return '%s ! 0=%X ! %s ! %s !  !  ! %s' % (name, slot, M.poke(R), ret, outw)

def e888(R, name, slot):
    M = Mem()
    M.u8(A['EA'] + slot, R.choice([1, 1, 2, 0])); M.u8(0x800C3A08 + slot, R.randint(0, 30))
    M.u8(0x800C39E2, R.choice([0, 0, 1, 5])); M.u8(0x800C39E3, R.choice([0x25, 0x25, 3, 0]))
    M.u8(0x800C40AB, R.choice([0, 1])); M.w(0x800BEE10, R.randint(0, 40)); M.u8(0x800C40B0, R.randint(0, 9))
    M.w(0x800C40B4, R.getrandbits(32)); M.h(0x800C40AE, R.randint(0, 999))
    g = M.alloc(0x200); M.w(A['GCAM'], g); M.f(g + 0x19C, R.uniform(-9, 9)); M.f(g + 0x1A0, R.uniform(-9, 9))
    return '%s ! 0=%X,1=%X ! %s' % (name, R.choice([0, 1, 2]), slot, M.poke(R))

def f2h(v): return '%08X' % struct.unpack('>I', struct.pack('>f', v))[0]

def s20430(R, name, slot):
    M = Mem(); actor = R.randint(0, 2); cnt = R.choice([0, 1, 2, 2, 3, 4, 6])
    e8 = M.alloc(8); M.w(A['E8'] + 4 * slot, e8); M.h(e8 + 2 * actor, cnt)
    keys = M.alloc(8 * max(cnt, 1)); M.w(A['PO'] + slot * 0x78 + 4 * actor, keys)
    for k in range(max(cnt, 1)):
        M.h(keys + 8 * k + 6, R.choice([0, 0, 1, 2]))
    act = M.alloc(0x40 * 3); M.w(0x800C3E70 + 4 * slot, act)
    kl = M.alloc(4 * 8); M.w(act + 0x40 * actor + 4, kl)
    pts = [round(R.uniform(-500, 500), 2) for _ in range(12)]
    if R.random() < 0.2: pts[3:6] = pts[6:9]       # zero-length straight segment
    outa = '15020090=0:' + ';'.join(f2h(v) for v in pts)
    return '%s ! 0=%X,1=%X ! %s !  !  ! %s' % (name, actor, slot, M.poke(R), outa)

def c4c(R, name, slot):
    M = Mem(); n = R.randint(1, 4)
    e8, cnt, ent, cam = base(R, M, slot, n)
    f8 = M.alloc(2 * n); M.w(0x800C39F8 + 4 * slot, f8)
    anchor = R.randrange(n); atype = R.choice([6, 6, 7, 7, 7])
    M.u8(0x800C3A87, R.choice([0, 0, 1])); M.f(0x800C39B4, round(R.uniform(-180, 360), 2))
    for j in range(3): M.h(0x800C39AC + 2 * j, R.randint(-2000, 2000))
    for i in range(n):
        kc = R.choice([0, 1, 2, 3]) if i != anchor else R.choice([1, 2, 3])
        M.h(e8 + 2 * i, kc)
        pk = M.alloc(8 * max(kc, 1)); M.w(A['PO'] + slot * 0x78 + 4 * i, pk)
        for k in range(kc):
            for c in range(3): M.h(pk + 8 * k + 2 * c, R.randint(-3000, 3000))
        t = atype if i == anchor else R.choice([0, 1, 2, 3, 6, 7]) if i > anchor else R.choice([0, 1, 2, 3])
        if i < anchor and R.random() < 0.3: M.h(e8 + 2 * i, 0); t = R.choice([6, 7])
        M.h(ent + 8 * i, t); M.u8(ent + 8 * i + 2, R.choice([0, 0, 1, 1, 2])); M.u8(ent + 8 * i + 3, R.randint(0, 9))
        nk = R.choice([0, 1, 3, 5]); M.h(cnt + 2 * i, nk)
        kp = M.alloc(8 * max(nk, 1)); M.w(A['KEYS'] + slot * 0x78 + 4 * i, kp)
        for k in range(nk):
            M.f(kp + 8 * k, round(R.uniform(-360, 360), 2)); M.u8(kp + 8 * k + 5, R.choice([7, 7, 0, 3, 10]))
        M.h(f8 + 2 * i, R.choice([0, 1, 2]))
        sr = M.alloc(0x24); M.w(0x800C3AA8 + slot * 0x78 + 4 * i, sr); M.u8(sr + 0x20, R.choice([7, 0, 7, 3]))
    obj = M.alloc(0x40); e2 = M.alloc(0x40)
    for k in (0x14, 0x18, 0x1C): M.f(obj + k, round(R.uniform(-900, 900), 2))
    for k in (0x10, 0x12, 0x14): M.h(e2 + k, R.randint(-900, 900))
    ret = '150842F8=%X,15114F2C=%X' % (R.choice([obj, obj, 0]), R.choice([e2, e2, 0]))
    ca = R.uniform(0, 6.28)
    retf = '15047EF0=%s,15048050=%s' % (f2h(round(__import__('math').cos(ca), 5)), f2h(round(__import__('math').sin(ca), 5)))
    return '%s ! 0=%X ! %s ! %s ! %s' % (name, slot, M.poke(R), ret, retf)

def a4c(R, name, slot):
    M = Mem(); pl = R.choice([0, 1, 2, 3])
    M.w(0x80083334, pl); vp = M.alloc(0x180 * 4); M.w(0x800BEA48, vp)
    for k in (0xC, 0x10, 0x34, 0x38): M.f(vp + 0x180 * pl + k, round(R.uniform(-200, 300), 2))
    M.f(0x800D9F40, R.choice([1.0, 0.5, 15.0]))
    o = [M.alloc(4) for _ in range(4)]
    for a in o[:3]: M.f(a, round(R.uniform(-500, 500), 2))
    w = R.choice([0.25, 0.5, 1.0, 15.0, 2.0, 100.0, 4000.0, 5000.0, -3.0, 37.5])
    M.f(o[3], w); far = R.choice([4000.0, 100.0, 37.5])
    if R.random() < 0.15: o[1] = o[0]                      # sx == sy
    args = '3=%X,4=%X,5=%X,6=%X,7=%s' % (o[0], o[1], o[2], o[3], f2h(far))
    return '%s ! %s ! %s' % (name, args, M.poke(R))

def a8c(R, name, slot):
    M = Mem(); n = R.randint(1, 4)
    e8, cnt, ent, cam = base(R, M, slot, n)
    if slot == 1: M.w(A['E8'], R.choice([e8, 0]))
    obj = M.alloc(0x80); M.w(obj, R.choice([1, 1, 1, 0])); M.u8(obj + 5, 4 if slot else R.choice([0, 3, 5]))
    owner = R.choice([0, 0, 1, 2]); M.u8(obj + 0x65, owner); M.u8(obj + 0x3B, R.randint(0, 3))
    M.u8(0x800CC3FF + owner * 0x32C, R.randint(0, 3))
    for i in range(n):
        M.h(e8 + 2 * i, R.choice([1, 1, 0])); M.h(ent + 8 * i, R.choice([2, 2, 1, 3])); M.u8(ent + 8 * i + 2, R.randint(0, 3))
    return '%s ! 0=%X ! %s' % (name, obj, M.poke(R))

if __name__ == '__main__':
    which, cnt = sys.argv[1], int(sys.argv[2]) if len(sys.argv) > 2 else 40
    R = random.Random(87)
    g = dict(eca4=eca4, f6c=f6c, db18=db18, e888=e888, s20430=s20430, c4c=c4c, a4c=a4c, a8c=a8c)[which]
    for k in range(cnt):
        print(g(R, '%s_%d' % (which, k), k % 2))
