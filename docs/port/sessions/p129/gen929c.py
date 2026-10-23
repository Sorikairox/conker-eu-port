# P129: setups for func_1515929C (knobs.sh fields: name ! ARG ! POKE ! RET). Run with DIFFTEST_ROMDATA=1.
# obj 0x80410000, target 0x80420000. For rules whose handler list entry is set, pick old states inside the rule's
# old mask and stub returns giving new states inside its new mask (plus near-miss setups).
import struct, zlib, itertools, random
rom = open('baserom.eu.z64', 'rb').read(); off = 0x427B0 + 0x145ED8; base = 0x80082EB0
n, = struct.unpack('>I', rom[off:off+4]); d = zlib.decompressobj(-15).decompress(rom[off+4:off+4+0x40000])[:n]
w = lambda a: struct.unpack('>I', d[a-base:a-base+4])[0]
lists = [[struct.unpack('b', d[w(0x8008B3CC+4*k)-base+j:][:1])[0] for j in range(28)] for k in range(5)]
rules = [(w(0x800A65E0+8*j), w(0x800A65E4+8*j)) for j in range(28)]
OFS = (0, 3, 6, 9, 13)
mask = lambda s: sum(1 << ((v + o) & 31) for v, o in zip(s, OFS)) & 0xFFFFFFFF
def old_states(w0):
    for s in itertools.product(range(5), repeat=5):
        if mask(s) | w0 == w0: return s
def new_states(w1):
    for a, b, c, d3, e in itertools.product(range(4), range(4), range(4), range(4), range(5)):
        s1 = 2 if a else b; s2 = 0 if a else (1 if s1 == 0 else c)
        s = (a, s1, s2, d3, e)
        if mask(s) | w1 == w1: return (a, b, c, d3, e), s
rnd = random.Random(129); out = []
def setup(name, kind, armed, old, rets, extra=''):
    a, b, c, d3, e = rets
    poke = '80410018=80420000,8041001C=%02X%02X0000,8041002C=%02X%02X%02X%02X,80410030=%02X%02X0000' % (
        rnd.randrange(256), kind, *old[:4], old[4], armed)
    ret = '151595F4=%08X,15159690=%08X,151596F4=%08X,151597A0=%08X,15159828=%08X' % (
        a | (rnd.randrange(16) << 8), b, c, d3, e)
    out.append('%s ! 0=80410000 ! %s%s ! %s' % (name, poke, extra, ret))
for k in range(5):
    for j in range(28):
        if lists[k][j] == -1: continue
        o = old_states(rules[j][0]); ns = new_states(rules[j][1])
        if o is None or ns is None: print('# no states for kind', k, 'rule', j); continue
        setup('k%dr%d' % (k, j), k, 1, o, ns[0])
        setup('k%dr%dna' % (k, j), k, 0, o, ns[0])            # not armed
        setup('k%dr%dx' % (k, j), k, 1 | 0xFE & rnd.randrange(256), tuple((v + 1) & 3 for v in o), ns[0])
for i in range(12):
    setup('rnd%d' % i, rnd.randrange(5), 1, tuple(rnd.randrange(4) for _ in range(5)),
          tuple(rnd.randrange(4) for _ in range(5)))
print('\n'.join(out))
