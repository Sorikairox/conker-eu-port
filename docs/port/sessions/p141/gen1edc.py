#!/usr/bin/env python3
# P141: setups for func_151E1EDC (menu_team_select_page). Fields: name ! ARG ! POKE ! RET ! RETF ! OUTA ! OUTW ! OUTB
# ROM layouts (D_800ABAF4 via D_800ABA75 row byte): x42 0 = 4 teams (size 2 / 1), 2 = 2 teams fixed1 2 colours 7 8,
# 8 = 2 teams fixed1 2 colours 9 5, 9 = 2 teams fixed1 0 colours 4 5.
REC = 0x80490000
def setup(name, x42=0, n=2, queue=(0, 1), teams=(0, 1), pads=(0, 0, 0, 0), extra=0, shift=0, inp=0, pending=0xFF,
          alpha=0x80, tick=1, scores=0):
    b = {}
    def byte(a, v): b[a] = v & 0xFF
    def half(a, v): byte(a, v >> 8); byte(a + 1, v)
    def word(a, v): half(a, v >> 16); half(a + 2, v)
    byte(0x800E0EC6, pending); byte(0x800E0EC5, alpha); word(0x800BEE04, tick); word(0x80090174, REC)
    byte(0x800901E0, n); byte(0x80090140, extra); byte(0x80090164, shift)
    for i in range(16):
        byte(0x800901E4 + i, queue[i] if i < len(queue) else 0x55)
        byte(0x800E1030 + i, teams[i] if i < len(teams) else 0)
    byte(REC + 0x42, x42); half(REC + 0x20, inp)
    for i in range(4): half(REC + 0x22 + 2 * i, pads[i])
    words = {}
    for a, v in b.items():
        w = a & ~3; words.setdefault(w, [0, 0, 0, 0]); words[w][a & 3] = v
    poke = ','.join('%08X=%02X%02X%02X%02X' % (w, *v) for w, v in sorted(words.items()))
    outa = '151E2C88=0:%s' % ';'.join('%X' % (0x10 + 3 * i) for i in range(7))
    return '%s ! ! %s ! 151E2C88=%X ! ! %s ! ! ' % (name, poke, scores, outa)
S = []
for x in (0, 2, 8, 9):
    S += [setup('x%d_n1' % x, x42=x, n=1, queue=(0,), teams=(0,)),
          setup('x%d_n2' % x, x42=x),
          setup('x%d_n3' % x, x42=x, n=3, queue=(0, 1, 2), teams=(0, 1, 0)),
          setup('x%d_n4' % x, x42=x, n=4, queue=(0, 1, 2, 3), teams=(0, 1, 1, 0), scores=1),
          setup('x%d_right' % x, x42=x, pads=(8, 0, 0, 0)), setup('x%d_left' % x, x42=x, pads=(0, 4, 0, 0)),
          setup('x%d_up' % x, x42=x, pads=(2, 0, 0, 0), extra=1), setup('x%d_down' % x, x42=x, pads=(1, 0, 0, 0), extra=0),
          setup('x%d_extra3' % x, x42=x, extra=3), setup('x%d_cl' % x, x42=x, inp=0x40, shift=1), setup('x%d_cr' % x, x42=x, inp=0x80, shift=-1),
          setup('x%d_shift9' % x, x42=x, shift=9), setup('x%d_shiftm9' % x, x42=x, shift=-9),
          setup('x%d_acc' % x, x42=x, inp=0x10, alpha=0xFF), setup('x%d_back' % x, x42=x, inp=0x20, alpha=0xF8, tick=2),
          setup('x%d_gap' % x, x42=x, n=3, queue=(0, -1, 2), teams=(1, 1, 1), pads=(0, 0, 8, 0), scores=1)]
S += [setup('fadeout', pending=4, alpha=0x80), setup('fadeout_end', pending=4, alpha=0x10, tick=1),
      setup('fadein_full', alpha=0xF0, tick=2), setup('both', pads=(8, 8, 0, 0), x42=0),
      setup('crowd', x42=0, n=4, queue=(0, 1, 2, 3), teams=(0, 0, 0, 0), pads=(4, 4, 8, 0)),
      setup('upleft', x42=9, n=2, pads=(0xA, 5, 0, 0), extra=2, scores=1)]
S += [setup('fadeout_zero', pending=4, alpha=0x20, tick=1), setup('n0', n=0, queue=(), teams=()), setup('x0_t23', x42=0, n=3, queue=(0, 1, 2), teams=(2, 3, 3), pads=(8, 0, 4, 0)),
      setup('x9_n3_shift', x42=9, n=3, queue=(0, 1, 2), teams=(0, 1, 0), shift=1, inp=0x40)]
print('\n'.join(S))
