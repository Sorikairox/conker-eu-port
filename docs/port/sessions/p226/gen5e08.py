#!/usr/bin/env python3
# P226: setups for func_151E5E08 (mp_match_rules_update). EU data addresses (port_work/p28h/euaddr.sh).
# Players: D_800CC2D0 (EU 800CC6F0) stride 0x32C: +0x128 team byte, +0x31C ctl -> 80470000 + i*0x400 (+0x1AA s16).
# D_80090174 -> 80450000 (+0x42 mode byte, +0x46 s16 scores), D_80087640 -> 80460000 (stride 0x84, +0x29 / +0x2A).
# keys: func_150859AC jal 15085E1C (RET sequence: per player (i,4), (i,3), (team,6)), func_150432FC 150435EC.
def b4(*b): return '%02X%02X%02X%02X' % tuple(x & 0xFF for x in b)
def h2(a, b): return '%04X%04X' % (a & 0xFFFF, b & 0xFFFF)
REC = [0x800CC6F0 + i * 0x32C for i in range(4)]
def setup(name, ffa=1, n=4, sc=(0, 0, 0, 0), hc=(0, 0, 0, 0), tb=(0, 0, 0, 0), team=(0, 1, 2, 3), ee0=(-1,) * 4,
          ed8=0x0F, ed9=7, el=0, spec=(0, 0, 0, 0), s1010=(0, 0, 0, 0), lim4=0, lim16=0, lim12=0, t118=0,
          bea38=4, q134=4, q110=0, f160=0, mode=0, recs=((0, 0x7F), (0, 2), (5, 0x7F), (0, 3)), fa0=0, nteams=4,
          over=0, ret=''):
    p = {0x800E1050: b4(over, 0, 0, 0), 0x800E1010: b4(*s1010), 0x800E1014: b4(lim4, 0, lim16, 0),
         0x800E1020: b4(0, 0, lim12, 0), 0x80090118: '%08X' % (t118 & 0xFFFFFFFF), 0x80090168: b4(ffa, 0, 0, 0),
         0x8009012C: b4(n, 0, 0, 0), 0x80090130: b4(n, 0, 0, 0), 0x80090174: '80450000',
         0x80450040: h2(0, mode << 8), 0x80450044: h2(0, sc[0]), 0x80450048: h2(sc[1], sc[2]), 0x8045004C: h2(sc[3], 0),
         0x800D1CC0: h2(el, 0), 0x800E0ED8: b4(ed8, ed9, 0x55, 0), 0x800E0EE0: b4(*ee0), 0x800E0EE4: 'FFFFFFFF',
         0x800E0EF0: '00000000', 0x800E0F00: h2(hc[0], hc[1]), 0x800E0F04: h2(hc[2], hc[3]),
         0x80090110: b4(q110, 0, 0, 0), 0x800BEA38: b4(bea38, 0, 0, 0), 0x80090134: b4(q134, 0, 0, 0),
         0x80090160: h2(f160, 0), 0x80087610: b4(*spec), 0x80083330: '%08X' % fa0, 0x800E0FE0: b4(nteams, 0, 0, 0),
         0x80087640: '80460000'}
    for i in range(4):
        p[REC[i] + 0x128] = b4(team[i], 0, 0, 0)
        p[REC[i] + 0x31C] = '%08X' % (0x80470000 + i * 0x400)
        p[0x80470000 + i * 0x400 + 0x1A8] = h2(0, tb[i])
        p[0x80460000 + i * 0x84 + 0x28] = b4(0, recs[i][0], recs[i][1], 0)
    poke = ','.join('%08X=%s' % kv for kv in sorted(p.items()))
    print('%s ! ! %s ! %s ! ! ! !' % (name, poke, ret))
R6 = '15085E1C=1;2;3;0;1;4;2;2;5;3;0;1'
setup('ffa_rank', sc=(3, 5, 5, 1), tb=(1, 4, 4, 2))
setup('ffa_tieidx', sc=(3, 5, 5, 5), tb=(1, 4, 4, 4), fa0=1)
setup('ffa_tieidx0', sc=(5, 5, 5, 5), tb=(4, 4, 4, 4), fa0=0)
setup('ffa_tb', sc=(2, 2, 7, 2), tb=(3, 1, 0, 5))
setup('ffa_limit', sc=(3, 5, 6, 1), tb=(1, 4, 4, 2), lim16=5, hc=(0, 2, 0, 1))
setup('ffa_limit_no', sc=(3, 4, 4, 1), tb=(1, 4, 4, 2), lim16=5, hc=(1, 0, 3, 0))
setup('ffa_hcap', sc=(6, 5, 5, 7), tb=(1, 2, 3, 4), hc=(2, 0, 1, 5))
setup('ffa_elim', sc=(3, 5, 6, 1), el=0x5, ed9=6)
setup('ffa_elim_fixed', sc=(3, 5, 6, 1), el=0x6, ee0=(-1, 2, -1, -1))
setup('ffa_spect', sc=(3, 5, 6, 1), spec=(0, 10, 0, 0), ee0=(-1, -1, 4, -1))
setup('ffa_3p', n=3, sc=(3, 5, 6, 9))
setup('ffa_queue', sc=(1, 2, 3, 4), bea38=2, q110=1)
setup('ffa_queue2', sc=(1, 2, 3, 4), bea38=4, q134=1, q110=1)
setup('ffa_queue3', sc=(1, 2, 3, 4), bea38=3, q134=2, q110=1)
setup('ffa_f80', sc=(1, 2, 3, 4), f160=0x80, ee0=(-1, 3, -1, -1))
setup('ffa_f80_3', n=3, sc=(1, 2, 3, 4), f160=0x81, ee0=(-1, -1, -1, 2))
setup('ffa_time', sc=(1, 2, 3, 4), s1010=(0, 0, 0, 3), t118=0)
setup('ffa_time_left', sc=(1, 2, 3, 4), s1010=(0, 0, 0, 4), t118=5)
setup('ffa_time_neg', sc=(1, 2, 3, 4), s1010=(0, 0, 0, 2), t118=-1)
setup('over', over=1)
T = dict(ffa=0, team=(0, 1, 0, 1), ret=R6)
setup('team_m0', mode=0, lim4=5, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_m0_hit', mode=0, lim4=3, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_m2', mode=2, lim12=4, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_m8', mode=8, lim12=1, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_m10', mode=10, lim12=7, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_m9a', mode=9, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_m9b', mode=9, s1010=(0, 0, 0, 3), t118=100, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_m5', mode=5, lim4=1, lim12=1, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_m11', mode=11, lim4=1, lim12=1, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), **T)
setup('team_tie', mode=7, sc=(2, 2, 3, 3), tb=(1, 2, 3, 4), ffa=0, team=(0, 1, 0, 1), ret='15085E1C=1;0;3')
setup('team_tie2', mode=7, sc=(2, 3, 3, 2), tb=(1, 5, 3, 4), ffa=0, team=(0, 1, 0, 1), ret='15085E1C=1;0;3')
setup('team_tie3', mode=7, sc=(2, 3, 3, 2), tb=(5, 1, 3, 4), ffa=0, team=(0, 1, 0, 1), ret='15085E1C=1;0;3')
setup('team_4', mode=9, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), ffa=0, team=(0, 1, 2, 3), ret=R6)
setup('team_2of4', mode=9, nteams=2, sc=(1, 2, 3, 4), tb=(1, 2, 3, 4), ffa=0, team=(0, 0, 1, 1), ret=R6)
setup('team_elim', mode=9, sc=(1, 2, 3, 4), el=0xA, ffa=0, team=(0, 1, 0, 1), ret=R6)
setup('team_elim2', mode=9, sc=(1, 2, 3, 4), el=0x3, ffa=0, team=(0, 1, 2, 3), ed9=9, ret=R6)
setup('team_cpu', mode=9, sc=(1, 2, 3, 4), ed8=0x0C, ffa=0, team=(0, 1, 0, 1), ret=R6)
setup('team_cpu1', mode=9, sc=(1, 2, 3, 4), ed8=0x02, ffa=0, team=(0, 1, 0, 1), ret=R6)
setup('team_spect', mode=9, sc=(1, 2, 3, 4), spec=(10, 0, 10, 0), ffa=0, team=(0, 1, 0, 1), ee0=(-1, 2, -1, -1), ret=R6)
setup('team_fixed', mode=9, sc=(1, 2, 3, 4), ffa=0, team=(0, 1, 2, 3), ee0=(-1, 2, -1, 1), ret=R6)
setup('ffa_limit_eq', sc=(3, 5, 4, 1), tb=(1, 4, 4, 2), lim16=5)
setup('ffa_f01', sc=(1, 2, 3, 4), f160=0x01, ee0=(-1, 3, -1, -1))
setup('team_sum', mode=9, s1010=(0, 0, 0, 3), t118=100, sc=(5, 2, 1, 1), ffa=0, team=(0, 1, 0, 1), ret=R6)
setup('team_kd', mode=9, sc=(1, 5, 1, 1), ffa=0, team=(0, 1, 0, 1), ret='15085E1C=6;0;0;0;1;0;0;0;0;0;0;0')
setup('team_m0_zero', mode=0, lim4=0, sc=(1, 2, 3, 4), **T)
setup('team_fixed2', mode=9, sc=(1, 2, 3, 4), ffa=0, team=(0, 1, 2, 3), ee0=(-1, -1, 1, -1), ret=R6)
setup('team_tie4', mode=7, sc=(2, 3, 1, 2), tb=(1, 5, 3, 4), ffa=0, team=(0, 1, 0, 1), ret='15085E1C=1;0;3')
setup('team_time', mode=5, s1010=(0, 0, 0, 3), t118=0, sc=(1, 2, 3, 4), **T)
