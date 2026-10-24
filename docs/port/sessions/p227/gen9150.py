#!/usr/bin/env python3
# P227: setups for func_151E9150 (mp_hud_draw). ARG 0 = DL 80480000, 1 = unused, 2 = alpha. EU addresses
# (port_work/p28h/euaddr.sh): D_80082FA0 80083330, D_8008FD8C 8009012C (players, byte), D_800E0FE0 (teams, byte),
# D_80090160 / D_8009015C (u16, high half), D_800BEDCC frame, D_800ABEA0 team colours, D_8009041C / D_80090420 digit
# sheet (poked with distinct bytes). Players D_800CC2D0 (EU 800CC6F0) stride 0x32C: +0x14 x, +0x1C z, +0x128 team,
# +0x13C active, +0x2E4 bonus, +0x31C -> 80470000 + i * 0x400 (+0x75 kind, +0x128 flags). Keys (decoded jal):
# func_1510D66C 1510D66C (texture), func_150859AC 15085E1C (team score), func_150871B8 / func_1508712C (rail point,
# OUTW px / pz through a1 / a3), func_151E8E94 / func_151E9E1C / func_151EA4C8 (draw helpers, return DL ends).
import struct
def fb(f): return '%08X' % struct.unpack('>I', struct.pack('>f', f))[0]
def setup(name, fa0=0, np=2, nt=2, f160=0x0009, f15c=0xFFFF, frame=0x1F, alpha=0x1C0,
          pl=((0, 0, 0, 0, 0, 0.0, 0.0), (0, 1, 0, 0, 0, 0.0, 0.0)), tex='80440000', scores='3;0;12345;7;99999',
          pt=None):
    pk = ['80083330=%08X' % fa0, '8009012C=%08X' % (np << 24), '800E0FE0=%08X' % ((nt & 0xFF) << 24),
          '80090160=%08X' % (f160 << 16), '8009015C=%08X' % (f15c << 16), '800BEDCC=%08X' % frame,
          '800ABEA0=11223300', '800ABEA4=44556600', '800ABEA8=77889900', '800ABEAC=AABBCC00',
          '8009041C=01020304', '80090420=05060708', '80090424=090A0B0C']
    for i, (act, team, bonus, cf, kind, x, z) in enumerate(pl):
        r = 0x800CC6F0 + i * 0x32C; c = 0x80470000 + i * 0x400
        pk += ['%08X=%s' % (r + 0x14, fb(x)), '%08X=%s' % (r + 0x1C, fb(z)), '%08X=%08X' % (r + 0x128, team << 24),
               '%08X=%08X' % (r + 0x13C, act << 24), '%08X=%08X' % (r + 0x2E4, bonus), '%08X=%08X' % (r + 0x31C, c),
               '%08X=%08X' % (c + 0x74, kind << 16), '%08X=%08X' % (c + 0x128, cf << 24)]
    ret = '1510D66C=%s,15085E1C=%s,151E8E94=80481000;80482000;80483000;80484000;80485000;80486000;80487000;80488000;' \
          '80489000;8048A000;8048B000;8048C000;8048D000;8048E000,151E9E1C=8048F000,151EA4C8=80490000,150871B8=17' % (tex, scores)
    outw = '1508712C=1:%s/3:%s' % pt if pt else ''
    print('%s ! 0=80480000,1=00000005,2=%08X ! %s ! %s ! ! ! %s !' % (name, alpha, ','.join(pk), ret, outw))
A, B = (1, 0, 0, 0, 0, 0.0, 0.0), (0, 1, 0, 0, 0, 0.0, 0.0)
setup('base')
setup('fa0', fa0=1)
setup('nt0', nt=0)
setup('nt3', nt=3, scores='0;A;64')  # hex: 0, 10, 100
setup('nt4neg', nt=4, scores='FFFFFFF6;0;1;10000')
setup('nt4big', nt=4, scores='0001869F;000F4240;00002710;0000270F')
setup('notex', tex='80000000')
setup('f8only', f160=0x8)
setup('f1only', f160=0x1, pl=(A, B))
setup('f1sel', f160=0x1, pl=(B, A))
setup('act_team1', f160=0x9, pl=(B, (1, 1, 0, 0, 0, 0.0, 0.0)))
setup('ctlflag', f160=0x9, pl=((0, 3, 0, 0x20, 0, 0.0, 0.0), B))
setup('ctlflag21', f160=0x1, pl=((0, 3, 0, 0x21, 0, 0.0, 0.0), B))
setup('arrow_t0', f160=0x8001, pl=(A, B))
setup('arrow_t1', f160=0x8001, pl=((1, 1, 0, 0, 0, 0.0, 0.0), B))
setup('arrow_both', f160=0x8000, pl=(A, (1, 1, 0, 0, 0, 0.0, 0.0)))
setup('bonus', f160=0x4000, pl=((0, 1, 5, 0, 0, 0.0, 0.0), B))
setup('bonus_t0', f160=0x4000, pl=((0, 0, 5, 0, 0, 0.0, 0.0), B))
setup('bonus_no4000', f160=0x0001, pl=((0, 1, 5, 0, 0, 0.0, 0.0), B))
setup('bonus_arrow', f160=0xC000, pl=((1, 1, 5, 0, 0, 0.0, 0.0), (1, 0, 0, 0, 0, 0.0, 0.0)))
setup('sel4000', f160=0x4001, pl=(A, B))
setup('sel_no1', f160=0x0008, pl=(A, B))
setup('blink', frame=0x2A, f160=0x8009, pl=(A, (1, 1, 5, 0, 0x25, 0.0, 0.0)), pt=('00000000', '00000000'))
setup('near', f160=0x0000, f15c=0, pl=(B, (0, 0, 0, 0, 0x25, 100.0, 200.0)), pt=(fb(1000.0), fb(1000.0)))
setup('near_far', f160=0x0000, pl=(B, (0, 0, 0, 0, 0xA5, 100.0, 200.0)), pt=(fb(2600.0), fb(200.0)))
setup('near_edge', f160=0x0000, pl=(B, (0, 0, 0, 0, 0x25, 0.0, 0.0)), pt=(fb(2499.0), fb(0.0)))
setup('near_sel', f160=0x4001, pl=(A, (0, 0, 0, 0, 0x25, 0.0, 0.0)), pt=(fb(10.0), fb(-10.0)))
setup('near_26', f160=0x0000, pl=(B, (0, 0, 0, 0, 0x26, 0.0, 0.0)), pt=(fb(10.0), fb(-10.0)))
setup('three', np=3, nt=3, f160=0x6349, pl=(A, (1, 1, 7, 0, 0, 0.0, 0.0), (0, 2, 0, 0x20, 0x25, 5.0, 5.0)),
      pt=(fb(5.0), fb(5.0)))
setup('timer', f160=0x0040)
setup('np0', np=0, f160=0xFFFF)
