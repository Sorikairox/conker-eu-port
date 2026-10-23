#!/usr/bin/env python3
# P157: setups for func_15064668 player_context_action. Prints knobs.sh lines.
import struct
def fb(f): return struct.unpack('>I', struct.pack('>f', f))[0]
P, C = 0x80480000, 0x80490000
def setup(name, v=0, buttons=0x4000, height=0.0, a3=0, nopad=0, pb=None, cb=None, pw=None, cw=None, g=None, ret=None):
    mem = {}
    def byte(a, val):
        w = a & ~3; sh = (3 - (a & 3)) * 8
        mem[w] = (mem.get(w, 0) & ~(0xFF << sh)) | ((val & 0xFF) << sh)
    def half(a, val):
        w = a & ~3; sh = 16 if (a & 2) == 0 else 0
        mem[w] = (mem.get(w, 0) & ~(0xFFFF << sh)) | ((val & 0xFFFF) << sh)
    mem[P + 0x31C] = C
    for k, x in {0x89: 0, 0x13C: 0, 0xAD: 0, 0x83: 0x11, 0x8A: 0x22, 0x80: 0x33, 0x81: 0x44}.items(): byte(P + k, x)
    for k, x in {0x7B: v, 0x198: 0, 0x4E: 0, 0x75: 0, 0x7C: 0, 0x84: 0, 0x30: 0x55, 0x11A: 0x66}.items(): byte(C + k, x)
    half(C + 8, 0); half(C + 0x4C, 0x1234); half(P + 0x84, 0x7777); half(P + 0x76, 0x8888)
    mem[P + 0x25C] = 0; mem[P + 0x28] = fb(0.5); mem[P + 0x14] = fb(-1500.0); mem[P + 0x1C] = fb(300.0)
    mem[P + 0x18] = fb(77.0); mem[P + 0x2E4] = 0x00140028; mem[P + 0x2E8] = 0x12345678; mem[P + 0x20] = fb(9.0)
    mem[0x800CC6AC] = 0xFFFFFFFF; mem[0x800D19A0] = 0x5555; mem[0x800BEA34] = 0; mem[0x800BEE10] = 5; mem[0x800EA130] = 0
    for k, x in (pb or {}).items(): byte(P + k, x)
    for k, x in (cb or {}).items(): byte(C + k, x)
    for k, x in (pw or {}).items(): mem[P + k] = x
    for k, x in (cw or {}).items(): mem[C + k] = x
    for k, x in (g or {}).items(): mem[k] = x
    r = {0x1505F458: 0x804A0000, 0x1505A9B0: 0x1234}
    r.update(ret or {})
    arg = '0=%X,1=%X,2=%X,3=%X,4=%X' % (P, buttons, fb(height), a3, nopad)
    print('%s ! %s ! %s ! %s ! ! ! !' % (name, arg, ','.join('%08X=%08X' % kv for kv in sorted(mem.items())),
                                         ','.join('%08X=%X' % kv for kv in r.items())))
print('# func_15064668 player_context_action (gen4668.py). name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB')
for v in range(0, 14): setup('v%d' % v, v=v, buttons=0)
for v in (1, 2, 6, 8, 9, 10, 12): setup('v%db' % v, v=v)
setup('v6up', v=6, height=1.0); setup('v6na', v=6, a3=1)
setup('v10hi', v=10, pw={0x28: fb(2.0)}); setup('v12hi', v=12, pw={0x28: fb(1.5)})
setup('v3w', v=3, pb={0xAD: 1}); setup('v3h', v=3, pw={0x28: fb(1.5)}); setup('v4w', v=4, pb={0xAD: 1}); setup('v4h', v=4, pw={0x28: fb(-1.5)})
O = 0x804A0000
setup('v5z', v=5, g={O + 0x2E4: 0, O + 0x1D4: 0x804B0000, 0x804B0158: 0x00000123})
setup('v5zb', v=5, buttons=0x8000, g={O + 0x2E4: 0, O + 0x1D4: 0x804B0000, 0x804B0158: 0xFFFF0000 | 0xFF00})
setup('v5h', v=5, buttons=0x8000, g={O + 0x2E4: 100, O + 0x1D4: 0})
setup('v5l', v=5, buttons=0x8000, g={O + 0x2E4: 50, O + 0x1D4: 0x804B0000})
setup('v5g', v=5, buttons=0xC000, g={O + 0x2E4: 150, O + 0x1D4: 0x804B0000, 0x804B0158: 0x00000040})
setup('v11far', v=11, pw={0x14: fb(-1884.0 + 900), 0x1C: fb(100.0 + 600)})
setup('v11near', v=11, pw={0x14: fb(-1884.0 + 300), 0x1C: fb(100.0 - 400)}, ret={0x1505A9B0: 0x5678})
setup('v11b', v=11, pw={0x14: fb(-1884.0 - 30), 0x1C: fb(100.0 + 20)})
setup('nopad', v=0, nopad=1); setup('nopad6', v=6, nopad=1)
# second part (B pressed, nothing pending)
setup('b_basic', v=0)
setup('b_up', height=0.5); setup('b_na', a3=1)
setup('b_198', cb={0x198: 1}); setup('b_mode1', cb={0x4E: 0x21}); setup('b_mode2', cb={0x4E: 2, 0x75: 1})
setup('b_mode3', cb={0x4E: 3, 0x75: 1}); setup('b_7c', cb={0x7C: 1}); setup('b_7c2', cb={0x7C: 1, 0x4E: 2})
setup('b_89', pb={0x89: 0xFF})
for lv in (0x2D, 0x2B, 0x30, 0x34, 0x2C): setup('b_lv%X' % lv, g={0x800BEE10: lv})
setup('b_ctx8', cw={8: 0x00010000})
setup('b_616', g={0x800BEA34: 0x100}); setup('b_616_400', g={0x800BEA34: 0x100, 0x800EA130: 0x400})
setup('b_616_800', g={0x800BEA34: 0x100, 0x800EA130: 0x800}); setup('b_616_c00', g={0x800BEA34: 0x100, 0x800EA130: 0xC00})
setup('b_84', cb={0x84: 1}); setup('b_4e', cb={0x4E: 0x12})
setup('s_100', pb={0x13C: 100}); setup('s_99', pb={0x13C: 99}); setup('s_25c', pb={0x13C: 200}, pw={0x25C: 0x20})
setup('s_25c2', pb={0x13C: 200}, pw={0x25C: 0xFFDF}); setup('s_616', pb={0x13C: 100}, g={0x800BEA34: 0x100})
setup('s_lv30', pb={0x13C: 100}, g={0x800BEE10: 0x30}); setup('s_616lv30', pb={0x13C: 100}, g={0x800BEA34: 0x100, 0x800BEE10: 0x30})
setup('v1neg', v=1, pw={0x2E4: 0xFFF08001}); setup('v10eq', v=10, pw={0x28: fb(1.0)}); setup('v12eq', v=12, pw={0x28: fb(1.0)})
setup('v11mid', v=11, pw={0x14: fb(-1884.0 + 950), 0x1C: fb(100.0)}); setup('b_mode9', cb={0x4E: 9})
for nm, gg in (('a', {0x800BEA34: 0x100}), ('b', {0x800BEA34: 0x100, 0x800EA130: 0x400}), ('c', {0x800BEA34: 0x100, 0x800EA130: 0x800}), ('d', {0x800BEA34: 0x100, 0x800EA130: 0xC00}), ('e', {0x800BEA34: 0, 0x800EA130: 0xC00})):
    setup('b84_616' + nm, cb={0x84: 1}, g=gg)
