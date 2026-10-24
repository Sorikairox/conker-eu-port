# P210: where are functions referenced? Scans the EU ELF for jal words and data words equal to each function's EU
# address (map). usage (container, /conker/conker): python3 refs.py func_X ...
import struct, sys, re
from elftools.elf.elffile import ELFFile
e = ELFFile(open('build/conker.eu.elf', 'rb'))
addr = {}
for l in open('build/conker.eu.map'):
    m = re.match(r'\s+0x([0-9a-f]{8,16})\s+(func_[0-9A-F]{8})\s*$', l)
    if m: addr[m.group(2)] = int(m.group(1), 16) & 0xFFFFFFFF
syms = {}
for s in e.iter_sections():
    if s.name == '.symtab':
        for y in s.iter_symbols():
            if y['st_info']['type'] == 'STT_FUNC' and y['st_size']: syms[y['st_value']] = (y.name, y['st_size'])
fl = sorted(syms)
import bisect
def owner(a):
    i = bisect.bisect_right(fl, a) - 1
    if i >= 0 and fl[i] <= a < fl[i] + syms[fl[i]][1]: return syms[fl[i]][0]
    return '?'
for f in sys.argv[1:]:
    a = addr.get(f); out = []
    if a is None: print(f, 'no map address'); continue
    jal = 0x0C000000 | ((a & 0x0FFFFFFF) >> 2); hi = (a + 0x8000) >> 16; lo = a & 0xFFFF
    for s in e.iter_sections():
        h = s.header
        if not h.sh_addr or h.sh_type == 'SHT_NOBITS' or h.sh_size == 0: continue
        d = s.data()
        for i in range(0, len(d) - 3, 4):
            w = struct.unpack('>I', d[i:i+4])[0]
            if w == a: out.append('data %s %08X (%s)' % (s.name, h.sh_addr + i, owner(h.sh_addr + i)))
            elif w == jal: out.append('jal %08X in %s' % (h.sh_addr + i, owner(h.sh_addr + i)))
            elif (w >> 16) & 0xFFFF == (0x2400 | 0) and False: pass
            elif (w & 0xFC000000) == 0x24000000 and (w & 0xFFFF) == lo and h.sh_flags & 4:
                out.append('addiu-lo %08X in %s' % (h.sh_addr + i, owner(h.sh_addr + i)))
    print('%s %08X: %s' % (f, a, '; '.join(out) or 'none'))
