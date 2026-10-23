#!/usr/bin/env python3
# P157: setups for func_15064F50 player_move_animation. Prints knobs.sh lines.
import struct
def fb(f): return struct.unpack('>I', struct.pack('>f', f))[0]
P, C, MP = 0x80480000, 0x80490000, 0x804A0000
def setup(name, vel=10.0, stick=0.5, anim=0, push=7.0, pb=None, cb=None, pf=None, ch=None, g=None, mpkind=None, ret=None):
    mem = {}
    def byte(a, val):
        w = a & ~3; sh = (3 - (a & 3)) * 8
        mem[w] = (mem.get(w, 0) & ~(0xFF << sh)) | ((val & 0xFF) << sh)
    def half(a, val):
        w = a & ~3; sh = 16 if (a & 2) == 0 else 0
        mem[w] = (mem.get(w, 0) & ~(0xFFFF << sh)) | ((val & 0xFFFF) << sh)
    mem[P + 0x31C] = C
    for k, x in {0x13C: 0, 0xAA: 0x11, 0x89: 0, 0x8A: 0x22, 0x83: 0x33}.items(): byte(P + k, x)
    half(P + 0x84, 0x1000)
    mem[P + 0x3C] = fb(5.0); mem[P + 0x44] = fb(5.0)
    for k, x in {0x4E: 0, 0x50: 0, 0x78: 0, 0x1B2: 0, 0x23: 0, 0x1A: 0, 0x17: 0, 0x3C: 0x44}.items(): byte(C + k, x)
    for k, x in {0x46: 0, 8: 0, 0xE: 0x1357, 0x32: 0}.items(): half(C + k, x)
    mem[0x800D196C] = MP; byte(MP + 0x13C, 2); mem[0x800CC6A4] = 0x804B0000; mem[0x804B0000] = 0
    mem[0x800BEA34] = 0; mem[0x800D19A0] = 0x5555
    for k, x in (pb or {}).items(): byte(P + k, x)
    for k, x in (cb or {}).items(): byte(C + k, x)
    for k, x in (ch or {}).items(): half(C + k, x)
    for k, x in (pf or {}).items(): mem[P + k] = fb(x)
    if mpkind is not None: byte(0x800B89C4 + 2 * 0x32C, mpkind)
    for k, x in (g or {}).items(): mem[k] = x
    r = {0x1504C370: 0x1111, 0x1504C3B0: 0x2222, 0x150ADF00: 0x12345}
    r.update(ret or {})
    arg = '0=%X,1=%X,2=%X,3=%X,4=%X' % (P, fb(vel), fb(stick), anim, fb(push))
    print('%s ! %s ! %s ! %s ! ! ! !' % (name, arg, ','.join('%08X=%08X' % kv for kv in sorted(mem.items())),
                                         ','.join('%08X=%X' % kv for kv in r.items())))
print('# func_15064F50 player_move_animation (gen4f50.py). name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB')
setup('ladder', ch={0x46: 3}); setup('swim2', cb={0x4E: 2}); setup('swim2b', cb={0x4E: 2, 0x50: 1}); setup('swim2n', cb={0x4E: 2, 0x50: 0x80})
for k in (0x8C, 0x57, 0xA8, 0xA9, 0x13, 0x89, 0x00, 0x14):
    for v in (0.5, 10.0, 14.0, 15.0):
        setup('mp%02X_%g' % (k, v), pb={0x13C: 100}, pf={0x3C: v}, mpkind=k)
setup('mp255', pb={0x13C: 255}, pf={0x3C: 20.0}, mpkind=0x8C)
setup('mv', anim=0x77); setup('mv78', anim=0x77, cb={0x78: 9}, pf={0x44: 0.5})
setup('fast', pf={0x44: 3.0}, ch={0x32: 1}); setup('fast26', pf={0x44: 2.6}, ch={0x32: 1}); setup('fastno', pf={0x44: 3.0}, ch={0x32: 2})
kinds = [0x16, 0x09, 0x38, 0x39, 0x37, 0x3B, 0x12, 0x18, 0x41, 0x24, 0x22, 0x21, 0x26, 0x3A, 0x25, 0x2D, 0x2E, 0x23, 0x15]
for k in kinds:
    for v in (0.5, 1.0, 15.0, 20.0):
        setup('k%02X_%g' % (k, v), cb={0x78: k}, pf={0x44: v})
setup('k16b', cb={0x78: 0x16, 0x1B2: 1}, pf={0x44: 3.0})
for v in (3.0, 25.0): setup('k09_616_%g' % v, cb={0x78: 9}, pf={0x44: v}, g={0x800BEA34: 0x100})
setup('k39_1EB', cb={0x78: 0x39}, pb={}, pf={0x44: 3.0}, g={}); 
for k, h in ((0x39, 0x1EB), (0x37, 0x1F4), (0x3B, 0x222), (0x3B, 0x236)):
    s = {}
    setup('k%02X_h%X' % (k, h), cb={0x78: k}, pf={0x44: 3.0}, g={P + 0x84: h << 16})
setup('k3B_23', cb={0x78: 0x3B, 0x23: 1}, pf={0x44: 0.5}); setup('k3B_23n', cb={0x78: 0x3B, 0x23: 0x80}, pf={0x44: 0.5})
for k in (0x19, 0x40):
    for v in (0.5, 1.0, 18.0): setup('k%02X_%g' % (k, v), cb={0x78: k}, pf={0x3C: v, 0x44: 30.0 - v})
setup('swim', cb={0x1A: 1}, stick=1.5); setup('swim1', cb={0x1A: 1}, stick=1.0)
setup('c8lo', ch={8: 2}, stick=0.5); setup('c8hi', ch={8: 2}, stick=1.0); setup('c8neg', ch={8: 0x8000}, stick=1.0)
B = 0x804B0000
setup('hold_btn', cb={0x17: 1}, g={B: 0x20000000}); setup('hold_btn283', cb={0x17: 1}, g={B: 0x20000000, P + 0x84: 0x02830000})
setup('hold', cb={0x17: 1}); setup('hold_slow', cb={0x17: 1}, pf={0x44: 0.5}); setup('hold_89', cb={0x17: 1}, pb={0x89: 1})
setup('hold283', cb={0x17: 1}, g={P + 0x84: 0x02830000}); setup('hold283s', cb={0x17: 1}, g={P + 0x84: 0x02830000}, pf={0x44: 0.5})
setup('hold_btnx', cb={0x17: 1}, g={B: 0xDFFFFFFF})
for r in (0, 987, 988, 999, 1988, 0x12345, 0xFFFFFFFF, 1989):
    setup('push_%X' % r, ch={0x32: 2}, ret={0x150ADF00: r})
setup('push_slow', ch={0x32: 2}, pf={0x44: 0.5}); setup('push_bit1', ch={0x32: 0xFFFD})
setup('none', pf={0x44: 3.0})
for k in (0x8C, 0x57, 0xA8, 0x00):
    setup('mp%02X_14q' % k, pb={0x13C: 100}, pf={0x3C: 14.25}, mpkind=k)
setup('hold_v12', cb={0x17: 1}, pf={0x44: 1.2}); setup('hold_3c', cb={0x17: 1}, pf={0x3C: 7.0}); setup('push_v1', ch={0x32: 2}, pf={0x44: 1.0})
setup('hold283w', cb={0x17: 1}, g={P + 0x84: 0x02830000})
