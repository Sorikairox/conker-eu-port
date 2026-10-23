#!/usr/bin/env python3
"""P102: targeted copies of e9c_v2.txt setups. usage: tweak.py src.txt > e9c_t.txt; edit T below.
T entries: (cmd, new name suffix, {arg index: value}, nwords or None, {RET key: value})."""
import sys
T = [(0x11, 'a', {2: -1000}, None, {}), (0x11, 'b', {2: -70000}, None, {}),
     (0x27, 'a', {2: 5}, 3, {}), (0x27, 'b', {2: 0}, 3, {}),
     (0x2F, 'a', {3: 2, 4: 0x55}, None, {'150725C8': '80431000'}), (0x2F, 'b', {3: 1, 4: 7}, None, {'150725C8': '80431000'}),
     (0x2F, 'c', {3: 0, 4: 0x30000, 5: -0x8000}, None, {'150725C8': '80431000'}),
     (0x42, 'a', {2: 0x1234}, None, {}), (0x42, 'b', {2: 0x1FF}, None, {}),
     (0x61, 'a', {2: 0x2000}, None, {}), (0x61, 'b', {2: 4}, None, {}), (0x61, 'c', {2: -1}, None, {}),
     # second batch: (D_80082FA0 / D_80090130 are ROM .data but the harness reads poked values)
     (0x67, 'a', {2: 3}, None, {}, {'80083330': '00000002'}), (0x67, 'b', {2: 2}, None, {}, {'80083330': '00000003'}),
     (0x6C, 'a', {2: 0x3B}, None, {}), (0x6C, 'b', {2: 9}, None, {}),
     (0x78, 'a', {2: 0}, None, {'1505F2A0': '800CCA1C'}, {'80090130': '01000000', '800CCD38': '80432000'}),
     (0x78, 'b', {2: 0}, None, {'1505F2A0': '800CC6F0'}, {'80090130': '01000000', '800CCA0C': '80432000'}),
     (0x78, 'c', {2: 3, 3: 0x2005}, None, {'1505F2A0': '800CC6F0;800CD074'}, {'800CCA0C': '80432000'}),
     (0x78, 'd', {2: 5}, None, {}),
     (0x8D, 'a', {}, None, {'1505F2A0': '800CC6F0'}, {'800CCD48': '00000001', '800CCD4C': '00050000', '800CCE6C': '01000000',
      '800CD074': '00000001', '800CD078': '00040000', '800CD198': '01000000', '800CD3A0': '00000001', '800CD3A4': '00050000',
      '800CD4C4': '00000000'})]
L = [l.rstrip('\n') for l in open(sys.argv[1])]
for t in T:
    cmd, suf, ov, nw, ret = t[:5]; extra = t[5] if len(t) > 5 else {}
    l = next(x for x in L if x.startswith('e9c_%02X_0 ' % cmd))
    f = l.split('!')
    args = int(dict(p.split('=') for p in f[1].strip().split(','))['2'], 16)
    pk = dict(p.split('=') for p in f[2].strip().split(','))
    for i, v in ov.items(): pk['%08X' % (args + 4 * i)] = '%08X' % (v & 0xFFFFFFFF)
    pk.update(extra)
    if nw: pk['800D3C60'] = '%08X' % nw
    rt = dict(p.split('=') for p in f[3].strip().split(','))
    rt.update(ret)
    f[0] = 'e9c_%02X_t%s ' % (cmd, suf)
    f[2] = ' ' + ','.join('%s=%s' % kv for kv in sorted(pk.items())) + ' '
    f[3] = ' ' + ','.join('%s=%s' % kv for kv in rt.items()) + ' '
    print('!'.join(f))
