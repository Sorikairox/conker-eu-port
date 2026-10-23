#!/usr/bin/env python3
"""P114: knob setups for func_15024910 (scene event handler A). Writes s24910.txt next to this file.
ev 0x80480000, obj 0x804A0000 (or object slot 3 = 0x800CD2F4 where the index matters), wrec 0x804C0000, data 0x804B0000,
player 1, track 2, now 0x10, flag 0x1B7. EU addresses: D_800C3958 800C3D78, D_800CC2D0 800CC6F0, D_800DBFF0 800DC420,
D_800D1C90 800D20B0, D_800B0DF0 800B1200, D_800BE9F0 800BEE10. jal keys from the asm words."""
import os, struct
EV, OBJ, WREC, DATA = 0x80480000, 0x804A0000, 0x804C0000, 0x804B0000
SLOT3 = 0x800CC6F0 + 3 * 0x32C
REC = 0x80490000 + 2 * 0x44
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
BASE = {
    0x800C3D7C: '80490000', REC: f(5.5), REC + 4: f(6.5), REC + 8: f(-7.5), REC + 0x10: f(9.25), REC + 0x24: f(-123.75),
    REC + 0x28: f(456.5),
    0x800C3A14: '804D3000', 0x804D3010: '00010000', 0x804D3018: '00020000', 0x804D3020: '00030000',  # refs: track 2 kind 1
    0x800C3A58: '00000005',            # D_800C3A5A[1] = 5 (byte 800C3A5B)
    0x800C3A04: '804D2000', 0x804D2000: '804D2100', 0x804D2004: '804D2200', 0x804D2008: '804D2300',
    0x804D2100: '41424300', 0x804D2200: 'BE414200', 0x804D2300: 'BF414200',
    0x800DC420: '804D8000', 0x804D85F0: '00000101',
    0x800CCA0C: '804D9000', 0x800CC7BC: '00010000', 0x800CC6F0 + 0xF8: '0F000033', 0x800CC754: '05060708',
    0x800D20B0 + 0x58 * 4: '804DC000', 0x804DC004: '0000FF85',
    0x800B1200: '804DA000', 0x804DA008: '11223344',
    0x800D34B8: '804DB000',
    0x804D4000: '00000000', 0x804D4004: '00800000', 0x804D400C: '01000000', 0x804D4034: '804D4100',
    0x804D5018: '11112222',
    0x804D6070: '00000077',
    OBJ + 4: '58123456', OBJ + 0x38: '000000A5', OBJ + 0x31C: '804D9800',
    OBJ + 0x94: '0F0F0F0F', OBJ + 0x100: '00110000', OBJ + 0x9C: '01020304',
    SLOT3 + 4: '53123456', SLOT3 + 0x31C: '804D9800', SLOT3 + 0x100: '00110000',
    0x800C3A18: '02000000', 0x800E1024: '00000000', 0x800BEECB - 3: '00000000',
}
def evw(t, i, b4=0, b5=0, w6=0):
    return {EV: '%02X07%04X' % (t & 0xFF, i & 0xFFFF), EV + 4: '%02X%02X%04X' % (b4 & 0xFF, b5 & 0xFF, w6 & 0xFFFF)}
RET0 = {'15023C60': '40', '1502354C': '804D4000', '15031C4C': '804D5000', '15114F2C': '804D6000', '15084418': '5',
        '151905AC': '804D7000', '1516AD20': '804D4444', '1516D8E8': '804D4200', '1516D934': '804D4300'}
OUTW0 = '151905AC=1:3'
L = []
def S(name, t, i, b4=0, b5=0, w6=0, obj=OBJ, wrec=WREC, flag=0x1B7, poke=None, ret=None, outw=OUTW0):
    p = dict(BASE); p.update(evw(t, i, b4, b5, w6))
    if poke: p.update(poke)
    r = dict(RET0)
    if ret: r.update(ret)
    arg = '0=%X,1=2,2=99,3=10,4=1,5=%X,6=%X,7=%X,8=%X' % (EV, obj, wrec, DATA, flag)
    L.append('%s ! %s ! %s ! %s !  !  ! %s ! ' % (name, arg, ','.join('%X=%s' % kv for kv in sorted(p.items())),
             ','.join('%s=%s' % kv for kv in r.items()), outw))
# --- cutscene lights (D_800E1024 set): type -> required D_800BEECB
for t, sel in ((7, 0), (0xE, 4), (0xF, 2), (0x10, 3), (0x12, 1)):
    on = {0x800E1024: '01000000', 0x800BEECB - 3: '%08X' % sel}
    S('L%X_b0' % t, t, 1, 0, 1, 0, poke=on)
    S('L%X_off' % t, t, 1, 0, 1, 0, poke={0x800E1024: '01000000', 0x800BEECB - 3: '%08X' % ((sel + 1) % 5)})
on = {0x800E1024: '01000000', 0x800BEECB - 3: '00000000'}
for k in (0, 1, 2):
    S('L7_id%d' % k, 7, k, 0, 2 - k, 0, poke=on)
S('L7_c0', 7, 1, 0, 0, 0, poke={**on, 0x804D400C: '00000000'})
S('L7_b2', 7, 2, 0, 2, 0, poke=on)
S('L7_null', 7, 1, 0, 0, 0, poke=on, ret={'1502354C': '0'})
S('L7_b4_1', 7, 1, 1, 3, 0, poke=on)
for b5 in (0, 1):
    for w6 in (0, 1, 2, 3):
        S('L7_b4_2_%d_%d' % (b5, w6), 7, 1, 2, b5, w6, poke=on)
S('L7_b4_5', 7, 1, 5, 1, 3, poke={**on, 0x804D4004: 'FFFFFFFF'})
S('L7_b4_2_flags', 7, 1, 2, 0, 1, poke={**on, 0x804D4004: 'FFFFFFFF'})
S('L7_disabled', 7, 1, 0, 0, 0)
S('L12_disabled', 0x12, 1, 0, 0, 0)
# --- object types
S('C_id0', 0xC, 0, 0, 0, 0)
S('C_w6', 0xC, 0x123, 0, 0, 7)
S('C_b5', 0xC, 0x1A5, 2, 1, 0)
S('C_span', 0xC, 0x1A5, -2, 0, 0)
S('C_span2', 0xC, 0x22, 1, 0, 0, ret={'15023C60': '5'})
for b4 in (0, 1, 2, 3, 4):
    S('D_b4%d' % b4, 0xD, 0x54, b4, 1, 0)
S('D_b2_neg', 0xD, -2, 2, 2, 0)
S('D_null', 0xD, 0x54, 0, 0, 0, obj=0)
S('D_attnull', 0xD, 0x54, 2, 1, 0, ret={'15031C4C': '0'})
for nm, rv in (('big', '310'), ('zero', '10'), ('one', '11'), ('neg', 'D'), ('mid', '1F'), ('negbig', 'FFFFF000')):
    S('4_%s' % nm, 4, 0x1C5, 0, 0, 0, ret={'15023C60': rv})
S('4_b4', 4, 0xC, 1, 0, 0)
S('4_null', 4, 0xC, 0, 0, 0, obj=0)
S('3_ok', 3, 3, 0, 0, 0, poke={0x804D3018: '00010000'})
S('3_kind2', 3, 3, 0, 0, 0)
S('3_same', 3, 2, 0, 0, 0)
S('3_count', 3, 5, 0, 0, 0)
S('3_k1', 3, 1, 0, 0, 0, poke={0x804D3008: '00010000'}); S('3_kind3', 3, 4); S('3_count_k1', 3, 5, poke={0x804D3028: '00010000'})
for b4 in (0, 1, 2):
    S('9_b4%d' % b4, 9, 0x1F9, b4, 0, 0)
S('9_null', 9, 0x19, 0, 0, 0, obj=0)
S('1_id0', 1, 0, 0, 0, 0)
S('1_id', 1, 0x185, 0, 0, 0)
S('1_null', 1, 7, 0, 0, 0, obj=0)
S('X_unknown', 0x22, 0x67, 0, 0, 0)
S('X_t0', 0, 0x67, 0, 0, 0)
S('X_tB', 0xB, 0x67, 0, 0, 0)
# --- type 5
def T5(name, i, b4=0, b5=0, w6=0, **kw): S('5_%02X_%s' % (i, name), 5, i, b4, b5, w6, **kw)
for b4 in (0, 1): T5('b%d' % b4, 0x3B, b4)
for i in (8, 9, 0xD, 0x12, 0x15, 0x7C, 0x84, 0x85, 0x6D):
    for b4 in (0, 3): T5('b%d' % b4, i, b4)
for b4 in (0, -3, 0x45): T5('b%X' % (b4 & 0xFF), 0x13, b4)
T5('b0', 0x14, 0); T5('b1', 0x14, 1); T5('null', 0x14, 0, obj=0)
for b5 in (0, 1): T5('b0_%d' % b5, 0x41, 0, b5)
T5('b1', 0x41, 1); T5('null', 0x41, 0, obj=0)
T5('b5', 0x44, 0x15, 1, 0x1234); T5('b5_0', 0x44, -3, 0, 0x55)
for i in (0x17, 0x16):
    T5('b0', i, 0, 3, 0x1C5); T5('b1', i, 1, 3, 0x1C5); T5('b0_neg', i, 0, -1, 7); T5('null', i, 0, obj=0)
for i in (0x18, 0x66, 0x6B): T5('nop', i, 0)
T5('k3_b0', 0x1D, 0, poke={0x804D3010: '00030000'}); T5('k3_b1', 0x1D, 1, poke={0x804D3010: '00030000'})
T5('k1', 0x1D, 0); T5('k2', 0x1D, 0, poke={0x804D3010: '00020000'}); T5('k3_null', 0x1D, 0, wrec=0, poke={0x804D3010: '00030000'})
T5('b4', 0x1E, 4, poke={0x800BEE10: '00000121'}); T5('neg', 0x1E, -1)
T5('b5_0', 3, 0, 0, 0x177); T5('b5_1', 3, 0, 1, 0x177); T5('null', 3, 0, 0, 7, ret={'15114F2C': '0'})
for b4 in range(0, 25):
    T5('b%d' % b4, 0x6C, b4, 1 if b4 % 2 else 0)
for b4 in (2, 3, 7, 21): T5('b%d_b5' % b4, 0x6C, b4, 0 if b4 % 2 else 1)
for b4 in (20, 22, 23): T5('b%d_null' % b4, 0x6C, b4, 0, obj=0)
T5('b10_flag', 0x6C, 10, 0, flag=0x2C5)
T5('ok', 0x6E, 0, 0, 2); T5('n', 0x6E, 0, 0, 3); T5('neg', 0x6E, 0, 0, -1); T5('null', 0x6E, 0, 0, 1, ret={'151905AC': '0'})
for b5 in (0, 1, 3, 5): T5('b5_%d' % b5, 5, 0, b5, 0)
T5('w6', 5, 0, 1, 2); T5('b4', 5, 1, 1, 0); T5('flag', 5, 0, 2, 0, flag=0x37)
T5('b0', 0x36, 0); T5('b1', 0x36, 1); T5('b2', 0x36, 2)
for b4 in (0, 1, 2, 3, 4, -1): T5('b%X' % (b4 & 0xFF), 0x30, b4)
T5('null', 0x30, 0, obj=0)
T5('b0', 0x46, 0); T5('b1', 0x46, 1)
T5('b0', 0x25, 0); T5('b7', 0x25, 7); T5('bneg', 0x25, -7)
T5('w0', 0x58, 0, 0, 0); T5('w', 0x58, 0, 0, 0x1F5); T5('wneg', 0x58, 0, 0, -3)
for b5 in (0, 1, 2): T5('b5_%d' % b5, 0x3C, 0x12, b5, -0x2F0F)
T5('null', 0x3C, 0, 0, obj=0); T5('b5_2even', 0x3C, 0x12, 2, 0x2F10)
T5('b0', 0x3D, 0, 9, 0x1C7); T5('b0_none', 0x3D, 0, 9, 0x1C7, ret={'15084418': 'FFFFFFFF'}); T5('b1', 0x3D, 1); T5('null', 0x3D, 0, obj=0)
for b4 in range(-1, 11): T5('b%X' % (b4 & 0xFF), 0x42, b4)
T5('b0', 0x43, 0); T5('b1', 0x43, 1)
T5('b0', 0x45, 0, poke={0x800BEE08: '00000777'}); T5('b1', 0x45, 1)
for b4 in (0, 2, 3, -1): T5('b%X' % (b4 & 0xFF), 0x49, b4, 0, 0x1E5)
T5('null', 0x49, 0, obj=0)
T5('a', 0x4B, 0x12, 0x85, -0x2F0F); T5('b', 0x4B, -0x12, 5, 0x0F0F); T5('null', 0x4B, 0, obj=0)
T5('b0', 0x4A, 0, 0x45); T5('b0neg', 0x4A, 0, -5); T5('b1', 0x4A, 1, 0x45)
T5('a', 0x54, 0x0C); T5('neg', 0x54, -2)
T5('a', 0x55, 0x0C); T5('neg', 0x55, -2)
for i in (0x59, 0x70, 0x78, 0x7F): T5('set', i, 0)
for k in ('53', '28', '21', '58'):
    T5('k' + k, 0x5A, 0, obj=SLOT3, poke={SLOT3 + 4: k + '123456'})
T5('obj', 0x71, 0); T5('null', 0x71, 0, obj=0)
for b5 in (0, 1, 2): T5('b0_%d' % b5, 0x37, 0, b5, 0x45 * b5)
T5('b1', 0x37, 1)
T5('b0', 0x38, 0, 3, 0); T5('b0w', 0x38, 0, -3, 0x123); T5('b1', 0x38, 1)
for lv in ('18', '21', '1D'):
    T5('lv' + lv, 0x5C, 0, 3, poke={0x800BEE10: '000000' + lv})
T5('lv21_next', 0x5C, 0, 3, poke={0x800BEE10: '00000021'}, outw='151905AC=1:3,15023C60=3:804D0000'); T5('lv18_next', 0x5C, 0, 3, poke={0x800BEE10: '00000018'}, outw='151905AC=1:3,15023C60=3:804D0000')
T5('lv18_b5neg', 0x5C, 0, -2, poke={0x800BEE10: '00000018'}); T5('b1', 0x5C, 1, 0, poke={0x800BEE10: '00000021'})
T5('a', 0x62, 0)
T5('a', 0x63, 0, 0, -0x1234)
T5('b0', 0x64, 0); T5('b1', 0x64, 1)
T5('a', 0x67, 0); T5('b1', 0x67, 1)
T5('a', 0x73, 0)
for b4 in range(0, 8): T5('b%d' % b4, 0x69, b4, obj=SLOT3)
T5('null', 0x69, 3, obj=0)
T5('a', 0x6A, 0, 0, -0x1234); T5('a', 0x7A, 0, -3, 0x1234); T5('b', 0x7A, 0, 7, 0)
T5('a', 0x74, 0, 0x85); T5('a', 0x6F, 3, 0x85); T5('neg', 0x6F, -2, 5); T5('null', 0x6F, 0, obj=0)
T5('a', 0x72, 0); T5('null', 0x72, 0, obj=0)
T5('a', 0x79, 0); T5('null', 0x79, 0, wrec=0)
T5('lv1D', 0x7B, 0, poke={0x800BEE10: '0000001D'}); T5('lv21', 0x7B, 0, poke={0x800BEE10: '00000021'})
T5('b0', 0x7D, 0); T5('b1', 0x7D, 1); T5('null', 0x7D, 0, obj=0)
T5('a', 0x7E, 0, obj=SLOT3); T5('null', 0x7E, 0, obj=0)
T5('a', 0x80, -5)
T5('b0', 0x81, 0, 0, 0x123); T5('b1', 0x81, 1, 0, -2)
for b4 in (5, 100, 101, -1, 0x7F): T5('b%X' % (b4 & 0xFF), 0x82, b4)
T5('a', 0x83, 0, 0, -0x1234)
T5('unknown', 0x11, 0); T5('unknown2', 0x65, 0); T5('unknown3', 0x86, 0); T5('unknown4', -1, 0)
open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 's24910.txt'), 'w').write('\n'.join(L) + '\n')
print(len(L), 'setups')
# --- real events of level 0x21 scene 1 (unique type/id/b4/b5/w6), written to s24910_rom.txt (ROM: argv[1])
import sys
if len(sys.argv) > 1:
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from scdis import scene
    rom = open(sys.argv[1], 'rb').read()
    L[:] = []; seen = set()
    for lv, sc in ((0x21, 1), (0x21, 0), (0x21, 2), (0x1D, 1)):
        r = scene(rom, lv, sc)
        if not r: continue
        for t, kind, rid, evs in r[1]:
            for tm, k, ty, d, i, b4, b5, w6 in evs:
                key = (ty, i, b4, b5, w6)
                if key in seen: continue
                seen.add(key)
                S('R%X_%X_t%d_%d' % (lv, sc, t, k), ty, i, b4, b5, w6, poke={0x800BEE10: '000000%02X' % lv})
    open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 's24910_rom.txt'), 'w').write('\n'.join(L) + '\n')
    print(len(L), 'ROM setups')
