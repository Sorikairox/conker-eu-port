#!/usr/bin/env python3
# P306: generates sBE40.txt (func_150FBE40 setups). obj 80480000 (id +4, flags +0x74, bones +0x1D4 -> 80470000),
# shooter 80440000 (func_1507515C RET, EU key 1507551C) with aim record 80450000 (+0x197 aimed, +0x130 dir, +0x13C
# point) and camera 80460000 (+0x23D index). Level D_800BE9F0, D_800BE616 poked. EU keys: 150ADF00 func_150ADA20 (RET),
# 150ADF48 func_150ADA68 (RETF), 15146414 func_15145EA4 (OUTP dst[0..2]), 15145624 func_151450B4 (OUTA a2 normal).
import struct, sys
def f(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def vec(v): return ';'.join(f(x) for x in v)
def setup(name, side=0, ident=0x10, noown=0, aimed=1, cam=0x80460000, camidx=3, nib=0x12, lvl=0x10, f616=0,
          owner=0x80440000, aimrec=0x80450000, bones=0x80470000, rand='00000000;00000008;00000002', obj=0x80480000,
          rf='3F000000;3E800000;3F400000;3DCCCCCD;3F666666;3E4CCCCD;3F19999A;3F333333', dt=0.375,
          fl=0x1C, ow=2, ndir=(0.6, 0.0, 0.8)):
    pk = ['80480004=%02X000000' % ident, '80480074=%02X000000' % nib, '804801D4=%08X' % bones,
          '80440318=%08X' % cam, '8044031C=%08X' % aimrec, '80450194=000000%02X' % aimed,
          '80450130=%s' % f(ndir[0]), '80450134=%s' % f(ndir[1]), '80450138=%s' % f(ndir[2]),
          '8045013C=%s' % f(100.0), '80450140=%s' % f(-10.0), '80450144=%s' % f(50.0),
          '8046023C=00%02X0000' % camidx, '800BEE10=%08X' % lvl, '800BEA34=0000%02X00' % f616]
    args = '0=%08X,1=%X,2=%s,3=%X,4=%X,5=%X' % (obj, side, f(dt), noown, fl, ow)
    print('%s ! %s ! %s ! 150ADF00=%s,1507551C=%08X ! 150ADF48=%s ! 15145624=2:%s !  !' % (
        name, args, ','.join(pk), rand, owner, rf, vec((0.3, -0.7, 0.2))))
setup('aim0')
setup('aim1', side=1)
setup('aimnocam', cam=0)
setup('aimcam7', camidx=7, rand='00000010;00000000;00000006;0000001F;00000001')
setup('noaim', aimed=0)
setup('noaim1', aimed=0, side=1)
setup('aimbyte', aimed=0x80)
setup('noown', noown=1)
setup('noown1', noown=1, side=1)
setup('noown23', noown=1, ident=0x23)
setup('noown23s1', noown=1, ident=0x23, side=1)
setup('aim23', ident=0x23)
setup('aim23s1', ident=0x23, side=1)
setup('noaim23', ident=0x23, aimed=0)
setup('noaim23s1', ident=0x23, aimed=0, side=1)
setup('nullobj', obj=0)
setup('side2', side=2)
setup('side255', side=0xFF)
setup('noshooter', owner=0)
setup('noaimrec', aimrec=0)
setup('nobones', bones=0)
setup('nibF', nib=0x3F)
setup('nibF2', nib=0x2E)
setup('lvl34', lvl=0x34)
setup('lvl26', lvl=0x26)
setup('lvl27', lvl=0x27)
setup('f616', f616=1)
setup('nospark', rand='00000005;00000001;00000002')
setup('noshell', rand='00000008;00000003;00000002')
setup('big', rand='FFFFFFF8;FFFFFFF0;FFFFFFFE;FFFFFFFF;FFFFFFFD;FFFFFFFC')
setup('r2', rand='0000003E;00000010;0000001D;00000065;00000033;00000037;00000002')
setup('fl', fl=0x1FF, ow=0x77)
setup('dtneg', dt=-1.5)
setup('ndir', ndir=(-0.25, 0.5, 0.125))
setup('flashr', rand='00000000;00000001;00000001;00000006;00000037')
if len(sys.argv) > 1:   # the OUTP knob (registry): func_15145EA4's three output vectors
    print('15146414=1.0:%s/1.1:%s/1.2:%s' % (vec((10.5, -20.25, 30.75)), vec((14.0, -18.0, 33.0)), vec((11.0, -25.0, 40.0))))
