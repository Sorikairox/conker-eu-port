#!/usr/bin/env python3
"""P67 setups for func_1507E7E4 -> e7e4.txt. obj = 0x80420000 (+0x6F anim, +0x70 default, +0x71 prio, +0x72 timer),
func_1507ED48 (count) / func_1507ECE8 (entry 0x80430000, +4 sound count) / func_1507EDD8 (sound list 0x80440000)."""
import sys
sys.path.insert(0, '../p59'); from pk import build
def setup(name, cur=5, dflt=1, prio=1, timer=10, anim=7, nprio=2, time=20, count=9, ent=2, snd='80440000'):
    spec = '80420000:6F=b:%X,70=b:%X,71=b:%X,72=h:%X;80430000:4=b:%X;80440000:0=w:11223344' % (cur, dflt, prio, timer, ent)
    ret = '1507ED48=%X,1507ECE8=80430000,1507EDD8=%s' % (count, snd)
    return '%s ! 0=80420000,1=%X,2=%X,3=%X,4=2A ! %s ! %s ! ! ! !' % (name, anim, nprio, time, build(spec), ret)
S = [('same', dict(cur=7, prio=2, timer=20)), ('same2', dict(cur=7, prio=2, timer=21)), ('same3', dict(cur=7, prio=3, timer=20)),
     ('base', {}), ('p3', dict(nprio=3, prio=5)), ('keep', dict(prio=2)), ('keep2', dict(prio=4)), ('dflt', dict(prio=4, dflt=5)),
     ('self', dict(prio=4, cur=7, timer=30)), ('t0', dict(prio=4, timer=0)), ('lt', dict(prio=1, nprio=2)),
     ('cnt', dict(count=7)), ('cnt8', dict(count=8)), ('cntneg', dict(count=0xFFFFFFFF)), ('e0', dict(ent=0)), ('e1', dict(ent=1)), ('e4', dict(ent=4)),
     ('nosnd', dict(snd='0')), ('ff', dict(time=0xFFFF, anim=0xFF, count=300))]
open(sys.argv[1] if len(sys.argv) > 1 else 'e7e4.txt', 'w').write('\n'.join(setup(n, **k) for n, k in S) + '\n')
