#!/usr/bin/env python3
# P282: writes s334C.txt (setups for func_1513334C). p = 80450000.
import os, struct
P = 0x80450000
def fw(v): return struct.unpack('>I', struct.pack('>f', v))[0]
def setup(name, flags, t73=1, t74=2, t75=1, typ=1, b12c=1, floor_hit=1, wall_hit=1, h1=1, h2=1, h3=1, vel=(3.0, -2.0, 1.5), yaw=0.25):
    w = {0x10: fw(5.0), 0x20: fw(0.1), 0x24: fw(0.2), 0x28: fw(0.3), 0x38: fw(100.0), 0x3C: fw(50.0), 0x40: fw(-20.0),
         0x44: fw(vel[0]), 0x48: fw(vel[1]), 0x4C: fw(vel[2]), 0x50: fw(0.5), 0x54: fw(-0.25), 0x58: fw(2.0), 0x5C: fw(-9.0),
         0x60: flags, 0x70: (t73 << 16) | (t74 << 8) | 0, 0x74: (t74 << 24) | (t75 << 16) | 0x00AB, 0x110: fw(12.5),
         0x114: 0x00010002, 0x118: 0x00030004, 0x11C: 0x00050006, 0x120: 0x00070008, 0x124: 0x00090000,
         0x12C: (b12c << 24) | (typ << 16), 0x148: 0x80000000, 0x140: fw(7.0), 0x144: fw(0.5)}
    # +0x70 word holds +0x73 (low byte); keep +0x71/+0x72 zero
    w[0x70] = t73
    pk = ','.join('%08X=%08X' % (P + k, v) for k, v in sorted(w.items())) + ',800BEDC4=3F000000'
    ret = '15046F70=%d,15044670=%d,150B8EC0=%d,150B9424=%d;%d,151A7EB8=%d,15133F44=%d' % (floor_hit, wall_hit, h1, h2, h3, h3, h1)
    return '%s ! 0=%08X ! %s ! %s ! 15048790=%08X ! ! !' % (name, P, pk, ret, fw(yaw))
L = ['# P282 setups for func_1513334C (particle_collide_update), from gen334C.py. D_800BE9A4 dt = EU 800BEDC4 (0.5).',
     '# handlers: D_80089CD4[1] = 150B8EC0, [6] = 15133F44; D_80089D10[2] = 150B9424; D_80089D14[1] = 150B9424, [3] = 151A7EB8']
for f in (0x00, 0x08, 0x20, 0x40, 0x68):
    L.append(setup('mv%02X' % f, f))
for f in (0x7F, 0x6F, 0x7B, 0x1, 0x11, 0x15, 0x14, 0x4):
    for typ, b in ((1, 0), (2, 1), (2, 2), (3, 0), (0, 0)):
        L.append(setup('f%02X_t%d_%d' % (f, typ, b), f, typ=typ, b12c=b))
L += [setup('nofl', 0x7F, floor_hit=0), setup('nowall', 0x7F, wall_hit=0), setup('h1z', 0x7F, h1=0), setup('h1zb', 0x17, typ=2, b12c=3, h1=0),
      setup('h2z', 0x7F, typ=3, h2=0), setup('h3z', 0x7F, h3=0), setup('t75_3', 0x7F, t75=3), setup('t73_0', 0x7F, t73=0, t74=0, t75=0),
      setup('t73_6', 0x7F, t73=6, typ=3, t74=2), setup('slow', 0x7F, vel=(0.5, 0.25, -0.5)), setup('slow3', 0x17, typ=3, vel=(0.5, 0.2, 0.1)),
      setup('yawneg', 0x7F, yaw=-1.5), setup('t74_0', 0x7F, typ=3, t74=0)]
open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 's334C.txt'), 'w').write('\n'.join(L) + '\n')
