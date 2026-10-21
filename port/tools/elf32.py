"""Minimal ELF32 big-endian (MIPS) symbol table reader for the N64 build (conker/build/conker.eu.elf)."""
import struct


def symbols(path):
    """-> list of (name, value, size, type, bind, shndx, section_name)."""
    d = open(path, 'rb').read()
    assert d[:4] == b'\x7fELF' and d[4] == 1 and d[5] == 2, 'want ELF32 BE'
    shoff, = struct.unpack_from('>I', d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('>HHH', d, 0x2E)
    sh = [struct.unpack_from('>IIIIIIIIII', d, shoff + i * shentsize) for i in range(shnum)]
    def cstr(off):
        return d[off:d.index(b'\0', off)].decode('latin1')
    shstr = sh[shstrndx][4]
    names = [cstr(shstr + s[0]) for s in sh]
    out = []
    for s in sh:
        if s[1] != 2:  # SHT_SYMTAB
            continue
        strtab = sh[s[6]][4]
        for i in range(s[5] // 16):
            nm, val, size, info, other, shndx = struct.unpack_from('>IIIBBH', d, s[4] + i * 16)
            if not nm:
                continue
            out.append((cstr(strtab + nm), val, size, info & 15, info >> 4, shndx,
                        names[shndx] if 0 < shndx < len(names) else ''))
    return out


def sections(path):
    d = open(path, 'rb').read()
    shoff, = struct.unpack_from('>I', d, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('>HHH', d, 0x2E)
    sh = [struct.unpack_from('>IIIIIIIIII', d, shoff + i * shentsize) for i in range(shnum)]
    shstr = sh[shstrndx][4]
    return [(d[shstr + s[0]:d.index(b'\0', shstr + s[0])].decode(), s[3], s[5], s[1]) for s in sh]
