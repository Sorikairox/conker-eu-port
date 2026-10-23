# Dump D_8008B3CC's 5 pointers and the s8 lists / pair table they reach, from the EU ROM's game_data (zlib, as n64mem.py)
import struct, zlib, sys
rom = open(sys.argv[1], 'rb').read()
off = 0x427B0 + 0x145ED8; base = 0x80082EB0
n, = struct.unpack('>I', rom[off:off+4]); d = zlib.decompressobj(-15).decompress(rom[off+4:off+4+0x40000])[:n]
w = lambda a: struct.unpack('>I', d[a-base:a-base+4])[0]
b = lambda a: struct.unpack('b', d[a-base:a-base+1])[0]
print('D_8008B3CC:', [hex(w(0x8008B3CC+4*i)) for i in range(6)])
for i in range(5):
    p = w(0x8008B3CC+4*i); print(' list', i, hex(p), [b(p+j) for j in range(28)])
print('D_8008B370:', [hex(w(0x8008B370+4*i)) for i in range(23)])
print('D_800A65E0 pairs:', [(hex(w(0x800A65E0+8*j)), hex(w(0x800A65E4+8*j))) for j in range(28)][:4], '...')
