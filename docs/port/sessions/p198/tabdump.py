#!/usr/bin/env python3
# P196: dump words of ROM range [A, B) (hex ROM offsets) with EU vram and map names. usage (from conker/): tabdump.py A B
import struct, re, sys
sys.path.insert(0, '../tools/port/difftest')
import difftest
rom = open('conker.eu.bin', 'rb').read(); segs = difftest.segments()
def r2v(r):
    for n, s in segs.items():
        if 'vram' in s and s.get('end') is not None and s['start'] <= r < s['end']: return r - s['start'] + s['vram']
    return 0
names = {}
for l in open('build/conker.eu.map'):
    m = re.match(r'\s+0x0*([0-9a-f]{8})\s+(func_\w+)\s*$', l)
    if m: names[int(m.group(1), 16)] = m.group(2)
for r in range(int(sys.argv[1], 16), int(sys.argv[2], 16), 4):
    w = struct.unpack('>I', rom[r:r + 4])[0]
    print('%08X %08X %s' % (r2v(r), w, names.get(w, '')))
