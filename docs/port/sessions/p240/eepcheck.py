#!/usr/bin/env python3
# P240: decode the save areas of a Conker EU EEPROM image (hex file from an [eepdump] line): per area (blocks
# area*16+4 .. +0x13, 0x80 bytes) the checksum check of func_15006590 (0xCC + sum(b[i] << (i & 3)), i = 2..0x7F, 16 bits)
# against the big-endian u16 at 0, slot kind, stamp, D_800BE3DF / D_800BE800 / D_800BE804 / D_800BE3E8.
import sys
b = bytes.fromhex(open(sys.argv[1]).read().strip())
for area in range(4):
    o = (area * 16 + 4) * 8; blk = b[o:o + 0x80]
    if not any(blk): print(f'area {area}: empty'); continue
    s = 0xCC
    for i in range(2, 0x80): s = (s + (blk[i] << (i & 3))) & 0xFFFF
    ck = blk[0] << 8 | blk[1]
    p = 2 + 5 + 27 + 9
    print(f'area {area}: checksum {ck:04X} computed {s:04X} {"OK" if s == ck else "BAD"}; slot {blk[2]} stamp {int.from_bytes(blk[3:7], "big")}; '
          f'flags27 {blk[7:34].hex()} D_800D2E60 {blk[34:43].hex()} 3DF {blk[p]} 800 {blk[p+1]} 804 {blk[p+2] << 8 | blk[p+3]} 3E8 {int.from_bytes(blk[p+4:p+8], "big"):08X}')
