# generates s1AF0.txt: func_150E1AF0 setups (25 objects of D_800CC2D0 = EU 800CC6F0, stride 0x32C)
import struct
def fh(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
B = 0x800CC6F0
def objs(dead=(), nohp=(), imm=(), n=25):
    p = []
    for i in range(26):
        a = B + i * 0x32C
        p.append('%08X=%08X' % (a, 0 if i in dead else 1 + i))
        p.append('%08X=%s' % (a + 0x14, fh(10.0 * i + 1.5)))
        p.append('%08X=%s' % (a + 0x18, fh(-3.25 * i)))
        p.append('%08X=%s' % (a + 0x1C, fh(100.0 - i)))
        p.append('%08X=%08X' % (a + 0xD0, 0x1000 + i))
        p.append('%08X=%08X' % (a + 0xD4, ((0x200 + i) << 16) | (0xFFF0 + i)))
        p.append('%08X=%08X' % (a + 0x74, 0x11110000 | (0x2222 + i)))
        p.append('%08X=%08X' % (a + 0x124, 0x07000000 | ((1 if i in imm else 0) << 16)))
        p.append('%08X=%08X' % (a + 0x1C8, 0 if i in nohp else 0x00000100 * (1 + i)))
    return p
def self_(own):  # self at 80460000: unk124 = own + 1, unk76 = 0xBEEF
    return ['80460124=%02X000000' % (own + 1), '80460074=0000BEEF']
G = '800C4298=0D000000'
ARG = lambda s, sk, kind=0x12: '0=%s,1=%s,2=%s,3=%s,4=%s,5=%s,6=%s,7=%X,8=%X' % (s, fh(5.0), fh(7.5), fh(-2.0), fh(55.0), fh(1.0), fh(-40.0), sk & 0xFFFFFFFF, kind)
out = ['# func_150E1AF0 setups (gen1AF0.py): self 80460000, objects D_800CC2D0 = EU 800CC6F0; func_15049440 = EU 15049730, func_1505D1C4 = EU 1505D570; D_800C3E78 = EU 800C4298']
def S(name, arg, pokes, ret, retf=''):
    out.append('%s ! %s ! %s ! %s ! %s ! ! !' % (name, arg, ','.join(pokes), ret, retf))
seq = ';'.join(str(x) for x in [9, 4, 6, 4, 8, 3, 7, 5, 9, 2, 6, 8, 7, 9, 5, 4, 6, 8, 9, 7, 5, 6, 8, 9, 7])
D = '1505D570=77'
S('all', ARG('80460000', 30), objs() + self_(30) + [G], '15049730=' + seq + ',' + D)
S('none', ARG('80460000', 30), objs() + self_(30) + [G], '15049730=0,' + D)
S('nullself', ARG('00000000', 30), objs() + [G], '15049730=0;0;5;0;3;0;4,' + D)
S('neg', ARG('80460000', -1), objs() + self_(-1) + [G], '15049730=5;FFFFFFF0;3;FFFFFFF8;1;80000000;7,' + D)
S('filters', ARG('80460000', 4), objs(dead=(2,), nohp=(6,), imm=(9,)) + self_(11) + [G], '15049730=' + ';'.join(str(30 - i) for i in range(25)) + ',' + D)
S('filters2', ARG('80460000', 24), objs(dead=(24,), nohp=(0,), imm=(23,)) + self_(22) + [G], '15049730=' + ';'.join(str(30 - i) for i in range(25)) + ',' + D)
S('first', ARG('80460000', 7), objs() + self_(0) + [G], '15049730=2;0;3;2;2;9,' + D)
S('kind', ARG('80460000', 12, 0x60005), objs() + self_(12) + [G], '15049730=0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;6,' + D)
open(__file__.replace('gen1AF0.py', 's1AF0.txt'), 'w').write('\n'.join(out) + '\n')
