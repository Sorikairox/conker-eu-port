#!/usr/bin/env python3
# P184: print N big-endian words at an EU vram from conker.eu.bin (segments from the EU yaml). usage (from conker/): romwords.py VRAM N
import sys, struct
sys.path.insert(0, '../tools/port/difftest')
import difftest
v, n = int(sys.argv[1], 16), int(sys.argv[2])
r = difftest.vram2rom(v); rom = open('conker.eu.bin', 'rb').read()
for i in range(n): print('%08X %08X' % (v + 4 * i, struct.unpack('>I', rom[r + 4 * i:r + 4 * i + 4])[0]))
