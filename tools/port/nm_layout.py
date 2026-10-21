#!/usr/bin/env python3
"""nm_layout.py: what moved in the NON_MATCHING link (run in the container from /conker/conker,
after `make VERSION=eu` and `make VERSION=eu NON_MATCHING=1`).
Compares build/conker.eu.elf with build_nm/conker.eu.elf: section sizes, how many functions and data
symbols moved (and from where), and the hazards a moved layout hits (raw pointers in the data blobs)."""
import sys as _pgs, os as _pgo; _pgs.path.insert(0, _pgo.path.dirname(_pgo.path.abspath(__file__))); import portguard  # wrong-checkout guard (P7)
import sys
from elftools.elf.elffile import ELFFile
def load(p):
    e = ELFFile(open(p, 'rb'))
    secs = {s.name: (s['sh_addr'], s['sh_size']) for s in e.iter_sections() if s['sh_addr']}
    syms = {}
    for s in e.get_section_by_name('.symtab').iter_symbols():
        if s.name and s['st_shndx'] not in ('SHN_UNDEF', 'SHN_ABS'):
            syms[s.name] = (s['st_value'], s['st_info']['type'])
    return secs, syms
a_s, a_y = load('build/conker.eu.elf'); b_s, b_y = load('build_nm/conker.eu.elf')
for n in sorted(a_s, key=lambda n: a_s[n][0]):
    if n in b_s and a_s[n][1] != b_s[n][1]:
        print('section %-14s size %+d (0x%X -> 0x%X)' % (n, b_s[n][1] - a_s[n][1], a_s[n][1], b_s[n][1]))
moved = sorted((a_y[k][0], k, b_y[k][0] - a_y[k][0], a_y[k][1]) for k in a_y if k in b_y and a_y[k][0] != b_y[k][0])
fn = [m for m in moved if m[3] == 'STT_FUNC']; ob = [m for m in moved if m[3] != 'STT_FUNC']
print('moved: %d functions, %d other symbols (of %d)' % (len(fn), len(ob), len(a_y)))
for lab, l in (('first moved function', fn), ('first moved other', ob)):
    if l: print('%s: %s 0x%08X %+d' % (lab, l[0][1], l[0][0], l[0][2]))
# absolute D_ symbols (linker-script assignments) cannot follow a move: any moved data symbol is a hazard
