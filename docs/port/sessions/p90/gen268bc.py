#!/usr/bin/env python3
"""P90: knob setups for func_150268BC (one ev per type / sub-type / variant). Writes s268bc.txt next to this file.
Line: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB   (knobs.sh format; ARGMEM goes through the env, see argmem.txt)
ev at 0x80480000, obj 0x804A0000, data (pos) 0x804B0000, rec arg 0x804C0000, player 1, track 2, now 0x10,
func_15023C60 (jal 15023C60) returns 0x40 -> span 0x30. D_800C3958[1] = 0x80490000 -> record 0x80490088."""
import os

EV, OBJ, DATA, RECARG = 0x80480000, 0x804A0000, 0x804B0000, 0x804C0000
REC = 0x80490000 + 2 * 0x44


def f(x):
    import struct
    return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]


BASE_POKE = {
    DATA: f(10.5), DATA + 4: f(20.25), DATA + 8: f(-30.75),
    0x800C395C: '80490000',
    REC: f(5.5), REC + 4: f(6.5), REC + 8: f(-7.5), REC + 0xC: f(8.0), REC + 0x10: f(9.0), REC + 0x18: f(11.0),
    REC + 0x1C: f(12.0), REC + 0x20: f(13.0), REC + 0x38: f(14.0),
    0x800C3E00: '804D0000',            # D_800C3D80[1][2]
    0x800C3D08: '804D1000',            # D_eu_800C3C88[1][2]
    0x804D1000: '00050006', 0x804D1004: '00070000',
    0x800C3A04: '804D2000',            # D_800C3A00[1]
    OBJ + 0x14: f(100.5), OBJ + 0x18: f(200.5), OBJ + 0x1C: f(-300.5),
}


def ev_words(t, i, b4=0, b5=0, w6=0):
    return {EV: '%02X07%04X' % (t & 0xFF, i & 0xFFFF), EV + 4: '%02X%02X%04X' % (b4 & 0xFF, b5 & 0xFF, w6 & 0xFFFF)}


def setup(name, t, i, b4=0, b5=0, w6=0, obj=OBJ, rec=RECARG, flag=0x37, poke=None, ret=None, retf=None, outa=''):
    p = dict(BASE_POKE)
    p.update(ev_words(t, i, b4, b5, w6))
    p[OBJ + 4] = '%08X' % (0x58000000 | 0x00123456)   # kind byte at +4 (overridden per setup)
    if poke:
        p.update(poke)
    r = {'15023C60': '40', '150ADF00': '12345', '151905AC': '0'}
    if ret:
        r.update(ret)
    rf = {'150ADF48': f(0.375), '15048D30': f(0.5), '15048CA0': f(-0.75)}
    if retf:
        rf.update(retf)
    arg = '0=%X,1=2,2=99,3=10,4=1,5=%X,6=%X,7=%X,8=%X' % (EV, obj, rec, DATA, flag)
    return '%s ! %s ! %s ! %s ! %s ! %s !  ! ' % (
        name, arg, ','.join('%X=%s' % kv for kv in sorted(p.items())), ','.join('%s=%s' % kv for kv in r.items()),
        ','.join('%s=%s' % kv for kv in rf.items()), outa)


S = []
A = S.append
# type 0x0B (sound)
for b4 in (0, 1, 2, 3, 4, 5):
    A(setup('t0B_b%d' % b4, 0x0B, 0x123, b4=b4, w6=0x80))
A(setup('t0B_b0_w0', 0x0B, 0x123, b4=0, w6=0))
A(setup('t0B_b1_w0', 0x0B, 0x123, b4=1, w6=0))
# type 0x11 (table byte), unknown type
A(setup('t11_b0', 0x11, 5, b4=0))
A(setup('t11_b1', 0x11, 5, b4=1))
A(setup('t07', 0x07, 5))
# type 0x05: simple sub-types, b4 0 and 1
simple = [0x0A, 0x0B, 0x0C, 0x19, 0x1A, 0x1C, 0x1F, 0x00, 0x20, 0x06, 0x07, 0x21, 0x60, 0x5B, 0x5D, 0x5E, 0x53, 0x50, 0x51,
          0x48, 0x0F, 0x3E, 0x3F, 0x32, 0x23, 0x22, 0x52, 0x40, 0x4D, 0x4E, 0x4F, 0x24, 0x10, 0x47, 0x2E, 0x31, 0x33,
          0x35, 0x26, 0x27, 0x02, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2F, 0x39, 0x3A, 0x11, 0x99]
for i in simple:
    A(setup('s%02X_b0' % i, 5, i, b4=0, b5=3, w6=0x150))
    A(setup('s%02X_b1' % i, 5, i, b4=1, b5=0, w6=0x50))
# variants
A(setup('s11_b5x_w0', 5, 0x11, b4=0, b5=1, w6=0))
A(setup('s11_b5n_w99', 5, 0x11, b4=0, b5=1, w6=99))   # b5 < 0 reads below the N64 stack copy (not reproducible)
A(setup('s11_b5_2_big', 5, 0x11, b4=0, b5=2, w6=0x7FFF))
A(setup('s19_b5_0', 5, 0x19, b4=0, b5=0, w6=-5))
A(setup('s1C_b2', 5, 0x1C, b4=2))
A(setup('s1C_null', 5, 0x1C, b4=0, obj=0))
A(setup('s1F_null', 5, 0x1F, obj=0))
A(setup('s00_null', 5, 0x00, obj=0))
A(setup('s23_null', 5, 0x23, obj=0))
A(setup('s22_null', 5, 0x22, obj=0))
A(setup('s52_null', 5, 0x52, obj=0))
A(setup('s26_null', 5, 0x26, obj=0))
A(setup('s2F_null', 5, 0x2F, obj=0))
A(setup('s23_idx3', 5, 0x23, obj=0x800CC2D0 + 3 * 812))
A(setup('s2F_idx5', 5, 0x2F, obj=0x800CC2D0 + 5 * 812))
for w6 in range(5):
    A(setup('s1B_w%d' % w6, 5, 0x1B, b4=0, b5=3, w6=w6, poke={OBJ + 0x78: '0000A5C3'}))
A(setup('s5E_b5_1', 5, 0x5E, b4=1, b5=1))
A(setup('s5E_b5_1b0', 5, 0x5E, b4=0, b5=1))
A(setup('s4C_k49', 5, 0x4C, b4=0, b5=4, w6=2, poke={OBJ + 4: '49000000'}, ret={'151905AC': '804E0000'},
        outa='151905AC=1:5', ))
A(setup('s4C_k58_out', 5, 0x4C, b4=0, b5=4, w6=7, poke={OBJ + 4: '58000000'}, ret={'151905AC': '804E0000'},
        outa='151905AC=1:5'))
A(setup('s4C_k49_null', 5, 0x4C, b4=0, w6=1, poke={OBJ + 4: '49000000'}, ret={'151905AC': '0'}, outa='151905AC=1:5'))
A(setup('s4C_other', 5, 0x4C, b4=0, b5=-4, poke={OBJ + 4: '12000000'}))
A(setup('s34_list', 5, 0x34, b4=0, b5=1, poke={OBJ + 0x2F4: '804F0000', 0x804F001C: '000D0000', 0x804F0014: '804F1000',
                                                0x804F0010: '804F2000', 0x804F101C: '00070000', 0x804F1014: '00000000',
                                                0x804F1010: '804F3000'}, ret={'1514DA28': '1'}))
A(setup('s34_list_no', 5, 0x34, b4=0, b5=0, poke={OBJ + 0x2F4: '804F0000', 0x804F001C: '00070000', 0x804F0014: '00000000',
                                                   0x804F0010: '804F2000'}, ret={'1514DA28': '0'}))
A(setup('s24_b5_13', 5, 0x24, b4=-1, b5=13))
A(setup('s24_b5_12', 5, 0x24, b4=7, b5=12))
A(setup('s10_b4_27', 5, 0x10, b4=27))
A(setup('s10_b4_26', 5, 0x10, b4=26))
A(setup('s33_b4_16', 5, 0x33, b4=16, b5=0))
A(setup('s33_b4_15', 5, 0x33, b4=15, b5=2))
A(setup('s2E_flag', 5, 0x2E, flag=0x1F7))
A(setup('s4C_k58_eq', 5, 0x4C, b4=0, w6=5, poke={OBJ + 4: '58000000'}, ret={'151905AC': '804E0000'}, outa='151905AC=1:5'))
A(setup('s33_b4_n', 5, 0x33, b4=-3, b5=-9))
A(setup('s35_b4_2', 5, 0x35, b4=2))
A(setup('s35_b4_n', 5, 0x35, b4=-2))
A(setup('s27_neg', 5, 0x27, b4=0, b5=0, w6=-1))
A(setup('s02_neg', 5, 0x02, b4=3, b5=-7, w6=-1))
A(setup('s28_rec0', 5, 0x28, rec=0))
A(setup('s28_both0', 5, 0x28, rec=0, obj=0))
A(setup('s29_rec0', 5, 0x29, rec=0))
A(setup('s29_both0', 5, 0x29, rec=0, obj=0))
A(setup('s3A_b4', 5, 0x3A, b4=-5))
A(setup('s48_b5', 5, 0x48, b4=0, b5=-6, retf={'150ADF48': '3F000000'}, ret={'150ADF00': '87654321'}))
# sub 0x65: b4 2 parts, b4 0 switch on b5 (1..26, 0, 27)
for b5 in (0x11, 0x12, 0x13, 0x14, 0x15):
    A(setup('s65_b2_%X' % b5, 5, 0x65, b4=2, b5=b5, w6=0x1C3))
for b5 in range(0, 28):
    A(setup('s65_%d' % b5, 5, 0x65, b4=0, b5=b5, w6=3, poke={OBJ + 4: '57000000'}))
A(setup('s65_9_k71', 5, 0x65, b4=0, b5=9, poke={OBJ + 4: '71000000'}))
A(setup('s65_9_k96', 5, 0x65, b4=0, b5=9, poke={OBJ + 4: '96000000'}))
A(setup('s65_9_k10', 5, 0x65, b4=0, b5=9, poke={OBJ + 4: '10000000'}))
A(setup('s65_11_r', 5, 0x65, b4=0, b5=11, ret={'151496A0': '804E2000'}))
A(setup('s65_11_0', 5, 0x65, b4=0, b5=11, ret={'151496A0': '0'}))
A(setup('s65_13_big', 5, 0x65, b4=0, b5=13, w6=0xE9))
A(setup('s65_13_e8', 5, 0x65, b4=0, b5=13, w6=0xE8))
A(setup('s65_22_big', 5, 0x65, b4=0, b5=22, w6=-1))
A(setup('s65_22_ce', 5, 0x65, b4=0, b5=22, w6=0xCE))
for b5 in (15, 16):
    A(setup('s65_%d_null' % b5, 5, 0x65, b4=0, b5=b5, obj=0))
    A(setup('s65_%d_neg' % b5, 5, 0x65, b4=0, b5=b5, ret={'15023C60': '5'}))
A(setup('s65_17_w', 5, 0x65, b4=0, b5=17, w6=0x102, poke={0x804D2000 + 4 * 0x102: '13572468'}))
A(setup('s65_24_hit', 5, 0x65, b4=0, b5=24, w6=0, ret={'15046F70': '1'}, outa='15046F70=3:' + f(-42.5) + ';0;0;0;0;0;0;00020000'))
A(setup('s65_24_hit3', 5, 0x65, b4=0, b5=24, w6=1, ret={'15046F70': '1'}, outa='15046F70=3:' + f(-42.5) + ';0;0;0;0;0;0;00030000'))
A(setup('s65_24_miss', 5, 0x65, b4=0, b5=24, ret={'15046F70': '0'}))
# sub 0x5F: switch (u8) b4 0..22, 23, -1
for b4 in range(0, 24):
    A(setup('s5F_%d' % b4, 5, 0x5F, b4=b4, b5=1, w6=0x1234, poke={OBJ + 0x1D4: '804E4000', OBJ + 4: '4A000000'}))
A(setup('s5F_m1', 5, 0x5F, b4=-1))
A(setup('s5F_0_hit', 5, 0x5F, b4=0, ret={'15046F70': '1'}, outa='15046F70=3:' + f(77.25)))
A(setup('s5F_0_null', 5, 0x5F, b4=0, obj=0))
for k in (0x5A, 0x74, 0x75, 0x7A, 0x86, 0x97, 0x98, 0x5B, 0x10):
    A(setup('s5F_2_k%X' % k, 5, 0x5F, b4=2, b5=-3, poke={OBJ + 4: '%02X000000' % k}, ret={'15031C4C': '804E6000', '15146ABC': '1'}))
A(setup('s5F_2_att0', 5, 0x5F, b4=2, poke={OBJ + 4: '5A000000'}, ret={'15031C4C': '0'}))
A(setup('s5F_2_ok0', 5, 0x5F, b4=2, poke={OBJ + 4: '74000000'}, ret={'15031C4C': '804E6000', '15146ABC': '0'}))
A(setup('s5F_2_null', 5, 0x5F, b4=2, obj=0))
A(setup('s5F_5_b0', 5, 0x5F, b4=5, b5=0, w6=1, ret={'15031C4C': '804E6000'}))
A(setup('s5F_5_w0', 5, 0x5F, b4=5, b5=2, w6=0))
A(setup('s5F_5_null', 5, 0x5F, b4=5, obj=0))
for b5 in (0, 1, 2):
    A(setup('s5F_10_%d' % b5, 5, 0x5F, b4=10, b5=b5, poke={OBJ + 0x1D4: '804E4000'}, ret={'150ADF00': '7'}))
A(setup('s5F_10_n', 5, 0x5F, b4=10, poke={OBJ + 0x1D4: '0'}))
A(setup('s5F_14_b0', 5, 0x5F, b4=14, b5=0, w6=0))
A(setup('s5F_14_neg', 5, 0x5F, b4=14, b5=-1, w6=-30))
A(setup('s5F_14_e8', 5, 0x5F, b4=14, b5=0x68, w6=3))
A(setup('s5F_15_b0', 5, 0x5F, b4=15, b5=0, ret={'150ADF00': 'FFFFFFF3'}))
A(setup('s5F_12_r', 5, 0x5F, b4=12, ret={'150ADF00': 'FFFFFFF3'}))
for b5 in (0, 1):
    A(setup('s5F_18_%d' % b5, 5, 0x5F, b4=18, b5=b5, poke={OBJ + 0x1D4: '804E4000'}))
for b5 in (0, 3, 7):
    A(setup('s5F_19_%d' % b5, 5, 0x5F, b4=19, b5=b5, poke={OBJ + 0x1D4: '804E4000'}))
A(setup('s5F_18_n', 5, 0x5F, b4=18, poke={OBJ + 0x1D4: '0'}))
A(setup('s5F_19_n', 5, 0x5F, b4=19, poke={OBJ + 0x1D4: '0'}))
A(setup('s5F_21_null', 5, 0x5F, b4=21, obj=0))
A(setup('s5F_22_null', 5, 0x5F, b4=22, obj=0))

out = os.path.join(os.path.dirname(os.path.abspath(__file__)), 's268bc.txt')
open(out, 'w').write('\n'.join(S) + '\n')
print(out, len(S), 'setups')
