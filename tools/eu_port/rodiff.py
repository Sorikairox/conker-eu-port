#!/usr/bin/env python3
"""usage (container, from conker/): rodiff.py src_eu/X.c [section]
Word diff of an object's own .rodata (or .data) against its ROM range (relocated words marked R)."""
import sys
sys.path.insert(0, '../tools/eu_port')
import check_files as cf
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
name = sys.argv[1][len('src_eu/'):-2]
sec = sys.argv[2] if len(sys.argv) > 2 else '.rodata'
rom = open('conker.eu.bin', 'rb').read()
rng = [x for x in cf.owned_sections().get(name, []) if x[0] == sec]
if not rng:
    sys.exit('%s owns no %s' % (name, sec))
_, a, b = rng[0]
with open('build/src_eu/%s.c.o' % name, 'rb') as f:
    e = ELFFile(f)
    d = e.get_section_by_name(sec).data()
    rel = set()
    for s in e.iter_sections():
        if isinstance(s, RelocationSection) and s.name == '.rel' + sec:
            rel |= {r['r_offset'] for r in s.iter_relocations()}
print('%s %s: object 0x%X bytes, rom 0x%X-0x%X (0x%X)' % (name, sec, len(d), a, b, b - a))
shown = 0
for off in range(0, max(len(d), b - a), 4):
    x = d[off:off + 4].hex() if off < len(d) else '--------'
    y = rom[a + off:a + off + 4].hex() if a + off < b else '--------'
    if x != y and off not in rel:
        print('+%04X rom %06X  obj %s  rom %s' % (off, a + off, x, y))
        shown += 1
        if shown > 12:
            break
