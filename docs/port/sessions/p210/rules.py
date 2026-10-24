# P210: dump the hit reaction rule lists (D_8009AA60 counts, D_80086E40 lists) from the EU ELF. Run in the container.
import struct, sys
from elftools.elf.elffile import ELFFile
e = ELFFile(open('build/conker.eu.elf', 'rb'))
def rd(a, n):
    for s in e.iter_sections():
        h = s.header
        if h.sh_addr and h.sh_addr <= a < h.sh_addr + h.sh_size and h.sh_type != 'SHT_NOBITS':
            return s.data()[a - h.sh_addr:a - h.sh_addr + n]
    return None
for t in range(1, 128):
    c = rd(0x8009AA60 + t, 1); p = rd(0x80086E40 + 4 * t, 4)
    if c is None or p is None: break
    c = c[0]; p = struct.unpack('>I', p)[0]
    if c == 0: continue
    d = rd(p, 4 * c)
    rules = ' '.join('%d/%02X/%02X/%02X' % tuple(d[i:i+4]) for i in range(0, len(d), 4)) if d else '?'
    print('%3d %08X %d: %s' % (t, p, c, rules))
