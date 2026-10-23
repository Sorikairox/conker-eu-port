#!/usr/bin/env python3
"""P92 setup generator. usage: gen.py fd34|ff10 [n] > setups.txt
knobs.sh lines: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB (EU addresses = US here, from conker.eu.map).
Stubs keyed by the decoded jal words: func_1501F7D4 = 1501F7D4, func_15020090 = 15020090, func_150484A0 = 15048790."""
import random, struct, sys

E8, E70, C88 = 0x800C39E8, 0x800C3E70, 0x800C3C88
def fb(v): return struct.unpack('>I', struct.pack('>f', v))[0]

class Mem:
    def __init__(s): s.b = {}; s.heap = 0x80430000
    def alloc(s, n):
        a = s.heap; s.heap += (n + 15) & ~15; return a
    def put(s, a, data):
        for i, x in enumerate(data): s.b[a + i] = x
    def w(s, a, v): s.put(a, struct.pack('>I', v & 0xFFFFFFFF))
    def h(s, a, v): s.put(a, struct.pack('>H', v & 0xFFFF))
    def f(s, a, v): s.put(a, struct.pack('>f', v))
    def poke(s, R):
        ws = {}
        for a in sorted(s.b):
            wa = a & ~3
            if wa not in ws: ws[wa] = bytearray(R.getrandbits(32).to_bytes(4, 'big'))
            ws[wa][a - wa] = s.b[a]
        return ','.join('%08X=%08X' % (a, int.from_bytes(v, 'big')) for a, v in sorted(ws.items()))

def one(R, kind, name, i):
    M = Mem(); slot = i % 2; actor = R.randint(0, 3)
    cnt = R.choice([0, 1, 2, 2, 3, 5, 8]) if i >= 2 else 2 + i
    e8 = M.alloc(8); M.w(E8 + 4 * slot, e8); M.h(e8 + 2 * actor, cnt)
    acts = M.alloc(0x40 * 4); M.w(E70 + 4 * slot, acts)
    a = acts + 0x40 * actor
    M.f(a, round(R.uniform(0, 3000), 2))
    tab = M.alloc(101 * 4); M.w(a + 0x38, tab)
    v = 0.0
    for j in range(101):
        M.f(tab + 4 * j, v)
        if R.random() > 0.15: v += round(R.uniform(0, 40), 2)
    k = R.randint(0, 99); seg = R.randint(0, max(cnt - 2, 0))
    keys = M.alloc(8 * 8); M.w(C88 + slot * 0x78 + 4 * actor, keys)
    for j in range(8): M.h(keys + 8 * j + 6, R.choice([0, 0, 1, 2]))
    t = R.choice([-10.0, 0.0, 100.0, 150.0, 37.5, round(R.uniform(0, 100), 3), round(R.uniform(0, 100), 3)])
    ends = ';'.join('%08X' % fb(round(R.uniform(-500, 500), 2)) for _ in range(6))
    arg = '0=%X,1=%08X,2=80450000,3=80450010' % (actor, fb(t))
    if kind == 'fd34': arg += ',4=80450020,5=%X' % slot
    else: arg = '0=%X,1=%08X,2=80450000,3=%X' % (actor, fb(t), slot)
    outa = '1501F7D4=2:' + ends
    if kind == 'ff10':
        outa += ',15020090=0:' + ';'.join('%08X' % fb(round(R.uniform(-500, 500), 2)) for _ in range(12))
    retf = '15048790=%08X' % fb(round(R.uniform(-3.14, 3.14), 4)) if kind == 'ff10' else ''
    print('%s ! %s ! %s ! 1501F7D4=%X ! %s ! %s ! 1501F7D4=4:%X ! ' % (name, arg, M.poke(R), k, retf, outa, seg))

if __name__ == '__main__':
  kind = sys.argv[1]; n = int(sys.argv[2]) if len(sys.argv) > 2 else 40
  R = random.Random(92)
  for i in range(n): one(R, kind, '%s_%d' % (kind, i), i)
