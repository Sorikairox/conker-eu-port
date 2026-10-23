#!/usr/bin/env python3
# P188: setups for func_151C62D0 (object_gun_fire). argv[1] = 'nomtx' (no bone matrices: muzzle computed from the
# func_15145740 direction, run with ARGMEM on the muzzle / start vectors) or 'mtx' (bone path; the transformed
# points come from stubs, so only the snd block is compared by ARGMEM). obj 80400000, matrices 80420000, sound
# record 80430000 (+0x23D voice). EU: D_80082FA0 = 80083330, D_800DCE50 = 800DCE50 (byte).
import sys, struct
def fb(x): return '%08X' % struct.unpack('>I', struct.pack('>f', x))[0]
def setup(name, side=0, aimed=0, att=0, mtx=0x80420000, snd=0x80430000, hid=0, mode=0, n=0, rng='1', busy=0,
          aim=(5.0, -2.0, 7.0), okatt=1, obj=0x80400000, kind=0xFFFF):
    p = {0x80400014: fb(10.0), 0x80400018: fb(20.0), 0x8040001C: fb(30.0), 0x804001D4: '%08X' % mtx,
         0x80400318: '%08X' % snd, 0x8043023C: '00030000', 0x80400074: '%08X' % (hid << 24),
         0x80083330: '%08X' % mode, 0x800DCE50: '%08X' % (n << 24)}
    pk = ','.join('%08X=%s' % kv for kv in p.items())
    arg = '0=%X,1=%X,2=%X,3=%X,4=%X,5=2A,6=1234' % (obj, side, aimed, att, kind)
    ret = '15142FCC=%X,15146ABC=%X,151C284C=80450000,150ADF00=%s' % (busy, okatt, rng)
    outa = '15145CB0=1:%s;%s;%s' % tuple(fb(v) for v in aim)
    return '%s ! %s ! %s ! %s ! 150ADF48=3F000000;3E800000 ! %s ! !' % (name, arg, pk, ret, outa)
if sys.argv[1] == 'nomtx':
    out = [setup('n0', mtx=0), setup('n1', mtx=0, side=1), setup('ntiny', mtx=0, aim=(1e-5, 3.0, -1e-5)),
           setup('nx', mtx=0, aim=(1.0, 0.0, 1e-5)), setup('nz', mtx=0, side=1, aim=(1e-5, 0.0, -2.0)),
           setup('naim', mtx=0, aimed=1), setup('nsnd0', mtx=0, snd=0), setup('nnull', obj=0),
           setup('nside2', side=2), setup('nbusy', busy=1), setup('nxneg', mtx=0, aim=(-3.0, 0.0, 1e-5)),
           setup('nr200', mtx=0, rng='1;1;C8')]
else:
    out = [setup('m1'), setup('m1s', side=1), setup('m2', rng='2'), setup('m2n1', rng='2', n=1), setup('m4n2', rng='4', n=2),
           setup('mseq', rng='1;1;2;1;4'), setup('mseq2', rng='2;3;1;1;4'), setup('maim', aimed=1, rng='2'),
           setup('maimatt', aimed=1, att=0x80410000), setup('matt0', att=0x80410000, okatt=0),
           setup('matt1', att=0x80410000), setup('mhid', hid=0xF), setup('mhid2', hid=0x1F, rng='2'),
           setup('mmode2', mode=2), setup('mmode2a', mode=2, aimed=1), setup('msnd0', snd=0), setup('mkind', kind=5),
           setup('maim1', aimed=1, side=1), setup('mhid7', hid=0x07), setup('mmode1', mode=1)]
print('\n'.join(out))
