#!/usr/bin/env python3
# P295: boundary setups for func_15054A94's 6 P286 survivors -> s4A94b.txt (reuses gen4A94.py's setup()).
import os
D = os.path.dirname(os.path.abspath(__file__))
src = open(os.path.join(D, '..', 'p282', 'gen4A94.py')).read()
exec(src[:src.index('\nL = [')])
P2 = 0x800CC6F0 + 0x32C  # partner idx 2
def outw(line, spec):  # fields: name ! args ! pokes ! RET ! RETF ! OUTA ! OUTW ! OUTB
    f = line.split('!'); f[6] = ' %s ' % spec; return '!'.join(f)
L = ['# P295 boundary setups for func_15054A94 (gen4A94b.py): idx 1 partner, anim end frame == len - 1, partner frame 6.0 /',
     '# 10.75, +0x2E8 = 2, func_150836CC (jal 15083ACC) changing the partner anim (OUTW @800CCAA0) before the reload.']
L += [setup('i1', idx=1), setup('i1t', idx=1, pid_anim=0x10A, c8a=0x2000),
      setup('a_eq', oid=0x41, pid_anim=0x48, oanim=1, f8=9.0),
      setup('s1D_six', pid_anim=0xC7, pf8=6.0), setup('s1D_105', pid_anim=0xC7, e4=1, pf8=10.75),
      setup('s1D_105b', pid_anim=0xC7, e4=0, pf8=10.75),
      setup('x2', pid_anim=0x50, e8=2),
      outw(setup('reload', pid_anim=0xC4, e4=1), '15083ACC=@%08X:00C60000' % (P2 + 0x84))]
open(os.path.join(D, 's4A94b.txt'), 'w').write('\n'.join(L) + '\n')
