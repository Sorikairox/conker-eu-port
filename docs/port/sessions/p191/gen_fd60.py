# P191: setups for func_1519FD60 foot_trail_update (t +0x23 is the low byte of the side word t +0x20). t = 80410000, rec 80420000, points 80430000 (8 x 0x24),
# owner 80440000, player 80450000; D_800BE9A4 (EU 800BEDC4). Stubs: func_1519F500 (RET), func_15045AF0 (RET, OUTW
# a3 = ground y), func_151491F4 (RET).
import struct
T, R, PT, OW, PL = 0x80410000, 0x80420000, 0x80430000, 0x80440000, 0x80450000
def fb(v): return struct.pack('>f', v)
BASE = dict(state=1, model=0x80460000, oid=5, uid=5, flags=4, side=6, b23=2, cnt=8, used=2, tail=0, head=2,
            cur=(103.0, 50.0, 204.0), prev=(100.0, 50.0, 200.0), scale=1.0, acc=0.2, phase=3.0, s28=10, s2E=40,
            s30=200, s32=5, w0=8.0, w1=0.5, b44=3, b45=4, f4c=2.0, px=10.0, py=20.0, pz=30.0, surf=60.0, d9a4=1.0,
            f500=1, grnd=1, gy='42480000', e=0x80470000)
def row(name, **kw):
    s = dict(BASE); s.update(kw); m = {}
    def put(a, b):
        for i, x in enumerate(b): m[a + i] = x
    put(T + 0x10, b''.join(fb(v) for v in s['cur'])); put(T + 0x1E, struct.pack('>H', s['flags']))
    put(T + 0x20, struct.pack('>I', s['side'])); put(T + 0x25, bytes([s['cnt']]))
    put(T + 0x2C, bytes([s['used'] & 0xFF, s['tail'] & 0xFF, s['head'] & 0xFF])); put(T + 0x94, struct.pack('>II', PT, R))
    put(R, struct.pack('>I', OW)); put(R + 8, fb(s['scale'])); put(R + 0xC, fb(s['acc']))
    put(R + 0x10, b''.join(fb(v) for v in s['prev'])); put(R + 0x1C, fb(s['phase']))
    put(R + 0x28, struct.pack('>h', s['s28'])); put(R + 0x2E, struct.pack('>hhh', s['s2E'], s['s30'], s['s32']))
    put(R + 0x38, fb(s['w0'])); put(R + 0x3C, fb(s['w1'])); put(R + 0x44, bytes([s['b44'], s['b45']])); put(R + 0x4C, fb(s['f4c']))
    put(OW + 0x18, struct.pack('>I', PL)); put(OW + 0x1C, bytes([s['oid']]))
    put(PL, struct.pack('>I', s['state'])); put(PL + 0x14, fb(s['px']) + fb(s['py']) + fb(s['pz']))
    put(PL + 0x1D4, struct.pack('>I', s['model'])); put(PL + 0x3B, bytes([s['uid']])); put(PL + 0x118, fb(s['surf']))
    put(0x800BEDC4, fb(s['d9a4']))
    for i in range(8):
        put(PT + i * 0x24 + 0x1C, fb(1.0 + i) + fb(-2.0 - i))
    words = {}
    for a in sorted(m):
        w = a & ~3
        words.setdefault(w, bytearray(4))[a - w] = m[a]
    poke = ','.join('%08X=%s' % (a, bytes(b).hex().upper()) for a, b in sorted(words.items()))
    ret = '1519F500=%X,15045AF0=%X,15149764=%X' % (s['f500'], s['grnd'], s['e'])
    print('%s ! 0=%08X ! %s ! %s ! ! ! 15045AF0=3:%s !' % (name, T, poke, ret, s['gy']))
row('move')
row('move7', side=7)
row('first', flags=0, cur=(100.0, 50.0, 200.0), acc=0.5)
row('firstmv', flags=0, acc=3.5)
row('firstfail', flags=0, f500=0)
row('wrap', head=7, used=3, tail=4)
row('full', used=7, tail=7, head=6)
row('full2', used=7, tail=0, head=7, cnt=8)
row('h0', head=0, used=3, tail=5)
row('k0', head=1, used=3, tail=6)
row('tailh', head=3, tail=2, used=1)
row('c0', used=0, head=2, tail=0)
row('nogrnd', grnd=0)
row('far', cur=(25000.0, 0.0, 10.0), prev=(24990.0, 0.0, 10.0))
row('farz', cur=(10.0, 0.0, -25000.0), prev=(10.0, 0.0, -24995.0))
row('nosurf', surf=-10000.0)
row('slow', scale=0.1, acc=0.95)
row('slow2', scale=0.1, acc=0.3)
row('ymove', cur=(100.0, 58.0, 200.0), acc=0.0)
row('rand45', b45=0, b44=0x80)
row('gone', state=0)
row('nomodel', model=0)
row('idmis', oid=6)
row('endtrail', f500=0)
row('endtrail7', f500=0, side=7)
row('endnull', f500=0, e=0)
row('tiny', cur=(100.005, 50.0, 200.0), acc=1.5)
row('surf9200', surf=-9200.0)
