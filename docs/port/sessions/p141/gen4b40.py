#!/usr/bin/env python3
# P141: setups for func_151E4B40 (menu_level_start_page). Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
REC = 0x80490000
def setup(name, state=2, x42=0, players=2, queue=(0, 1, -1, 2), q1030=(0, 1, 2, 3), flags=(1, 0, 0, 0), chars=(4, 1, 2, 3),
          fade=0x40, tick=2, prevy=0, sticky=0, cursor=0, acc=0, ec0=0, attract=0, c40ac=0, drop=0, ret2cdc=1, inp=0xFFFF):
    b = {}
    def byte(a, v): b[a] = v & 0xFF
    def half(a, v): byte(a, v >> 8); byte(a + 1, v)
    def word(a, v): half(a, v >> 16); half(a + 2, v)
    byte(0x80090120, state); byte(0x80090128, players); byte(0x80090110, drop); half(0x8009016C, fade)
    byte(0x800901CC, cursor); byte(0x800902EC, prevy); byte(0x800BED3A, sticky)
    for i in range(16):
        byte(0x800901E4 + i, queue[i] if i < len(queue) else -1)
        byte(0x800E1030 + i, q1030[i] if i < len(q1030) else i & 3)
        byte(0x800E0EF0 + i, flags[i] if i < len(flags) else 0)
    for i in range(4): byte(0x800E0FF8 + i, chars[i])
    half(0x800E0FCA, acc); word(0x800E0EC0, ec0); byte(0x800C3A0A, attract); byte(0x800C40AC, c40ac)
    word(0x800BEE04, tick); word(0x80090174, REC); word(0x800DC420, 0x804A0000); word(0x800E1008, 0x804B0000)
    for i in range(4): half(0x800E1040 + 2 * i, 0x100 + 7 * i); word(0x800E1048 + 4 * i, 0x2000 + 0x31 * i)
    byte(REC + 0x42, x42); half(REC + 0x20, inp); byte(REC + 0x3F, 1)
    for i in range(8): word(0x804B0174 + 4 * i, 0x1100 + i)
    words = {}
    for a, v in b.items():
        w = a & ~3; words.setdefault(w, [0, 0, 0, 0]); words[w][a & 3] = v
    poke = ','.join('%08X=%02X%02X%02X%02X' % (w, *v) for w, v in sorted(words.items()))
    return '%s ! ! %s ! 151F349C=%X ! ! ! ! ' % (name, poke, ret2cdc)  # jal word of func_151F2CDC = 151F349C
S = []
for x in (0, 1, 2, 5, 0xB, 0xC):
    S.append(setup('s1_x%X' % x, state=1, x42=x))
    S.append(setup('s1_x%X_nof' % x, state=1, x42=x, flags=(0, 0, 0, 0)))
S.append(setup('s1_x0_q', state=1, x42=0, queue=(-1, 0, -1, -1), q1030=(3, 0, 1, 2), flags=(0, 0, 0, 1)))
for st in (2, 3, 4):
    for x in (0, 1, 3, 0xB, 0xC):
        S.append(setup('s%d_x%X' % (st, x), state=st, x42=x))
S += [
 setup('two_flag', flags=(1, 1, 0, 0)), setup('one_joined', players=1, queue=(0,)), setup('one_joined_nf', players=1, queue=(1,), q1030=(1,), flags=(1, 0, 0, 0)),
 setup('first_flag2', flags=(0, 0, 1, 0), chars=(1, 2, 4, 3)), setup('first_flag3', flags=(0, 0, 0, 1), chars=(4, 4, 4, 2)),
 setup('noflag', flags=(0, 0, 0, 0)), setup('fade_full', fade=0xFE, tick=3), setup('up_edge', prevy=0, sticky=-40), setup('down_edge', prevy=0, sticky=40),
 setup('hold_up', prevy=-40, sticky=-40), setup('hold_dn', prevy=40, sticky=40), setup('flip', prevy=40, sticky=-40), setup('flip2', prevy=-40, sticky=40),
 setup('cur1', cursor=1), setup('acc_yes', acc=0x8000), setup('acc_no', acc=0x8000, cursor=1), setup('acc_no_s3', acc=0x8000, cursor=1, state=3),
 setup('acc_yes_drop', acc=0x8000, drop=2, players=4, queue=(0, 1, 2, 3, 4, 5, 6)), setup('acc_yes_drop9', acc=0x8000, drop=9),
 setup('timeout', ec0=0x7D1), setup('timeout_eq', ec0=0x7D0), setup('attract', acc=0x8000, attract=1), setup('attract0', acc=0x8000, attract=1, ret2cdc=0),
 setup('mp_x0B', x42=0xB, players=4, queue=(0, -1, 2, 3), flags=(2, 3, 1, 0)), setup('mp_x0C', x42=0xC, players=3, queue=(-1, 1, 2), flags=(0, 1, 2, 3)),
 setup('st5', state=5),
 setup('thr_m31', prevy=0, sticky=-31), setup('thr_m30', prevy=0, sticky=-30), setup('thr_p31', prevy=30, sticky=31), setup('thr_p30', prevy=31, sticky=31),
 setup('s1_x1_f1', state=1, x42=1, flags=(0, 1, 0, 0)), setup('s1_x2_f1', state=1, x42=2, flags=(0, 1, 0, 0)), setup('s1_x8_f1', state=1, x42=8, flags=(0, 1, 0, 0)),
 setup('s1_x9_f1', state=1, x42=9, flags=(0, 1, 0, 0)), setup('s1_x0_f1', state=1, x42=0, flags=(0, 1, 0, 0)), setup('s1_x0_f2', state=1, x42=0, flags=(0, 0, 1, 0)), setup('st0_acc', state=0, acc=0x10), setup('st0_2', state=0, c40ac=2), setup('st6_x0B', state=6, x42=0xB, c40ac=2),
]
print('\n'.join(S))
