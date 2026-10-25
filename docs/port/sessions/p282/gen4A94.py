#!/usr/bin/env python3
# P282: writes s4A94.txt (setups for func_15054A94). Field pokes (addr, size, value) are merged into big-endian words.
import os
OBJ, ANIM, PANIM, CTL, PADS, PAD = 0x80450000, 0x80451000, 0x80452000, 0x80453000, 0x80454000, 0x80455000
BASE = 0x800CC6F0  # D_800CC2D0 (EU)
def setup(name, idx=2, oid=0x1D, oanim=0, f8=5.0, f18=10.0, e4=0, e8=0, pid_anim=0xC7, p65=0, hp=5, g13c=0, stun=0,
          ptype=0x12, s11a=0, c84=1, c197=1, c8a=0, pf8=7.0, p3c=0, padflag=0x10):
    import struct
    part = BASE + (idx - 1) * 0x32C
    f = [(OBJ + 4, 1, oid), (OBJ + 0x65, 1, idx), (OBJ + 0x84, 2, oanim), (OBJ + 0x2D0, 4, ANIM), (OBJ + 0x2E4, 4, e4),
         (OBJ + 0x2E8, 4, e8), (ANIM + 8, 4, struct.unpack('>I', struct.pack('>f', f8))[0]),
         (ANIM + 0x18, 4, struct.unpack('>I', struct.pack('>f', f18))[0]),
         (part + 0x2D0, 4, PANIM), (part + 0x84, 2, pid_anim), (part + 0x65, 1, p65), (part + 0x1CA, 1, hp),
         (part + 0x13C, 1, g13c), (part + 0x104, 1, stun), (part + 0x31C, 4, CTL),
         (CTL + 0x78, 1, ptype), (CTL + 0x11A, 1, s11a), (CTL + 0x84, 1, c84), (CTL + 0x197, 1, c197), (CTL + 0x8A, 2, c8a),
         (PANIM + 8, 4, struct.unpack('>I', struct.pack('>f', pf8))[0]), (PANIM + 0x3C, 2, p3c & 0xFFFF),
         (0x800BEB48, 4, PADS), (PADS + 4, 4, PAD), (PADS + 0x14, 4, PAD), (PAD, 2, padflag)]
    words = {}
    for a, n, v in f:
        for k in range(n):
            b = a + k; byte = (v >> (8 * (n - 1 - k))) & 0xFF
            w = b & ~3; sh = (3 - (b & 3)) * 8
            words[w] = (words.get(w, 0) & ~(0xFF << sh)) | (byte << sh)
    pk = ','.join('%08X=%08X' % (w, v) for w, v in sorted(words.items()))
    return '%s ! 0=%08X ! %s ! ! ! ! !' % (name, OBJ, pk)
L = ['# P282 setups for func_15054A94 (carried_by_partner_update), from gen4A94.py. obj 80450000, partner = EU D_800CC2D0 (800CC6F0) [idx - 1],',
     '# anims 80451000 / 80452000, controller 80453000, D_800BE728 (EU 800BEB48) -> pads 80454000 -> pad 80455000.']
L += [setup('a_drop', oid=0x41, pid_anim=0x50), setup('a_start', oid=0x41, pid_anim=0x48, f8=0.0),
      setup('a_follow', oid=0x41, pid_anim=0x4B, f8=5.0), setup('a_end', oid=0x41, pid_anim=0x48, oanim=1, f8=9.5),
      setup('a_mid', oid=0x41, pid_anim=0x48, oanim=1, f8=8.0), setup('a_both', oid=0x41, pid_anim=0x4B, f8=0.0),
      setup('other', oid=0x30), setup('p65', p65=1), setup('dead', hp=0), setup('ctl', ptype=0x20),
      setup('ctl3', ptype=0x20, s11a=3, pid_anim=0x50), setup('ctl18', ptype=0x18, pid_anim=0x50), setup('ctl41', ptype=0x41, pid_anim=0x50),
      setup('grab', g13c=1), setup('stun', stun=1), setup('stun6E', oid=0x6E, stun=1, pid_anim=0xFB)]
for oid, a1, a2 in ((0x1D, 0xC4, 0xC7), (0x6E, 0xFB, 0xFC), (0x2F, 0x2C8, 0x2C9)):
    t = '%X' % oid
    L += [setup('s%s_on' % t, oid=oid, pid_anim=a2, pf8=7.0), setup('s%s_lo' % t, oid=oid, pid_anim=a2, pf8=5.0),
          setup('s%s_hi' % t, oid=oid, pid_anim=a2, pf8=11.0), setup('s%s_off' % t, oid=oid, pid_anim=a2, e4=1, pf8=11.0),
          setup('s%s_keep' % t, oid=oid, pid_anim=a2, e4=1, pf8=10.0), setup('s%s_a1' % t, oid=oid, pid_anim=a1, e4=1),
          setup('s%s_c6' % t, oid=oid, pid_anim=0xC6), setup('s%s_x' % t, oid=oid, pid_anim=0x77, e4=2)]
L += [setup('t12', pid_anim=0x10A, c8a=0x2000), setup('t12on', pid_anim=0x10A, c8a=0x2000, e8=1),
      setup('t12f', pid_anim=0x10A, c8a=0x2000, p3c=1), setup('t12n', pid_anim=0x10A, c8a=0x2000, p3c=-1),
      setup('t12b', pid_anim=0x10A, c8a=0x1FFF), setup('t18', ptype=0x18, pid_anim=0x10A, c8a=0x2000, c84=0, c197=1),
      setup('t18p', ptype=0x18, pid_anim=0x10A, c8a=0x2000, c84=0, c197=1, padflag=0xFFEF),
      setup('t18q', ptype=0x18, pid_anim=0x10A, c8a=0x2000, c84=1, c197=1, padflag=0xFFEF),
      setup('t18z', ptype=0x18, pid_anim=0x10A, c8a=0x2000, c84=1, c197=0),
      setup('t18i6', idx=6, ptype=0x18, pid_anim=0x10A, c8a=0x2000, c84=0, c197=1, padflag=0),
      setup('t18i5', idx=5, ptype=0x18, pid_anim=0x10A, c8a=0x2000, c84=0, c197=1, padflag=0),
      setup('stop', pid_anim=0x50, e8=1), setup('stop2', pid_anim=0x10A, e8=1, c8a=0)]
open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 's4A94.txt'), 'w').write('\n'.join(L) + '\n')
