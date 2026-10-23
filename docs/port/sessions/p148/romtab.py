#!/usr/bin/env python3
# P148: dump N words of an EU vram table from conker.eu.bin with the defining file of each function entry.
# usage (in conker/): python3 ../docs/port/sessions/p148/romtab.py ADDR N
import sys, os, re, glob, struct
sys.path.insert(0, '../tools/eu_port'); import datarefs
segs = datarefs.segments(); rom = open('conker.eu.bin', 'rb').read()
def v2r(v):
    for nm, sg in segs.items():
        if 'vram' in sg and sg.get('end') is not None and sg['vram'] <= v < sg['vram'] + sg['end'] - sg['start']:
            return v - sg['vram'] + sg['start']
a, n = int(sys.argv[1], 16), int(sys.argv[2]); r = v2r(a)
asm = set(open('../port_work/p98/asmonly.txt').read().split()) if os.path.exists('../port_work/p98/asmonly.txt') else set()
where = {}
for p in glob.glob('src_eu/*.c'):
    for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/[^/]+/(func_\w+)\.s"\)', open(p).read()): where.setdefault(m.group(1), os.path.basename(p))
for i in range(n):
    w = struct.unpack('>I', rom[r + 4 * i: r + 4 * i + 4])[0]; f = 'func_%08X' % w
    print('%2d %08X %s %s' % (i, w, where.get(f, '-'), 'ASM' if f in asm else ''))
