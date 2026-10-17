#!/usr/bin/env python3
"""Word diff of one C function's object code against the ROM (for functions with no .s, e.g. in
files whose .data is owned and so cannot be screened). Run from conker/ in the container:

    python3 ../tools/eu_port/fdiff.py src_eu/X.c func [-a]   (-a: print all lines, not just diffs +-2)

Rebuilds the object (make), then prints `off  built  rom  built-disasm | rom-disasm`, `**` on
differing words (relocated fields masked).
"""
import os, re, sys, struct, subprocess
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import check_files as CF
from elftools.elf.elffile import ELFFile

src, func = sys.argv[1], sys.argv[2]
allp = '-a' in sys.argv
stem = os.path.basename(src)[:-2]
obj = 'build/src_eu/%s.c.o' % stem
if os.path.exists(obj):
    os.remove(obj)
subprocess.run(['make', '-s', 'VERSION=eu', obj], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
data, masked = CF.text_words(obj)
with open(obj, 'rb') as f:
    e = ELFFile(f)
    sym = [s for s in e.get_section_by_name('.symtab').iter_symbols() if s.name == func][0]
    off, size = sym['st_value'], sym['st_size']
start, _ = CF.file_ranges()[stem]
rom = open('conker.eu.bin', 'rb').read()


def dis(b):
    open('/tmp/fd.bin', 'wb').write(b)
    o = subprocess.run(['mips-linux-gnu-objdump', '-D', '-b', 'binary', '-mmips:4300', '-EB', '/tmp/fd.bin'],
                       capture_output=True, text=True).stdout
    return [l.split('\t', 2)[-1].strip().replace('\t', ' ') for l in o.split('\n') if re.match(r'\s+[0-9a-f]+:\t', l)]


mine = dis(data[off:off + size])
ref = dis(rom[start + off:start + off + size])
rows = []
nd = 0
for i in range(0, size, 4):
    a = struct.unpack('>I', data[off + i:off + i + 4])[0]
    b = struct.unpack('>I', rom[start + off + i:start + off + i + 4])[0]
    m = masked.get(off + i, 0xFFFFFFFF)
    d = (a & m) != (b & m)
    nd += d
    rows.append((d, '%s %04X %08X %08X  %-28s | %s' % ('**' if d else '  ', i, a, b, mine[i // 4] if i // 4 < len(mine) else '', ref[i // 4] if i // 4 < len(ref) else '')))
print('%s: %d differing words of %d' % (func, nd, size // 4))
for k, (d, l) in enumerate(rows):
    if allp or any(rows[j][0] for j in range(max(0, k - 2), min(len(rows), k + 3))):
        print(l)
