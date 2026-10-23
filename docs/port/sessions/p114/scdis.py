#!/usr/bin/env python3
"""P114: scene script disassembler. A scene = asset (6, level, scene) (func_1501D240 -> func_1502B6BC(.., 3, 6, lv, sc)).
Its chunk table (func_1502B4A8) is: [0] header u16 n0, n1, n2, n3; then n0 track position chunks (D_eu_800C3C88),
n0 ref entries (8 bytes each, D_800C3A10 = first of them), n1 key chunks (D_800C3B98), n2 event tracks (D_800C3AA8,
count = size / 8), n3 words. An event track: 0x20-byte header (+2 s16 start time), then 8-byte events
{s8 type, u8 delta, s16 id, s8 b4, s8 b5, s16 w6}; time += delta; type 0 delta 0 sets time = id (func_15023C60).
Handlers (func_1502AB94): func_15024910 first (A), then func_150268BC (B), then func_15029EA8 (C).
usage: scdis.py ROM LEVEL SCENE [--grep ID]      (hex)
       scdis.py ROM --scan TYPE ID                -> every (level, scene, track, time) with that type / id"""
import sys, struct, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from scasset import load, chunks
A_TOP = {7, 0xE, 0xF, 0x10, 0x12, 0xC, 0xD, 4, 3, 9, 1}     # whole types func_15024910 owns (7..12 only if D_800E1024)
A_T5 = {0x3B, 8, 9, 0xD, 0x12, 0x13, 0x15, 0x14, 0x41, 0x44, 0x17, 0x16, 0x18, 0x1D, 0x1E, 3, 0x6C, 0x6E, 5, 0x36, 0x30,
        0x46, 0x25, 0x58, 0x3C, 0x3D, 0x42, 0x43, 0x45, 0x49, 0x4B, 0x4A, 0x54, 0x55, 0x59, 0x5A, 0x71, 0x37, 0x38, 0x5C,
        0x62, 0x7C, 0x84, 0x85, 0x63, 0x64, 0x66, 0x67, 0x73, 0x69, 0x6A, 0x7A, 0x6B, 0x6D, 0x74, 0x6F, 0x70, 0x72, 0x78,
        0x79, 0x7B, 0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83}
def owner(t, i):
    if t in A_TOP: return 'A'
    if t == 5 and i in A_T5: return 'A'
    if t in (0xB, 0x11, 5): return 'B?'
    return 'C?'
def scene(rom, lv, sc):
    b = load(rom, [6, lv, sc])
    if b is None: return None
    ch = chunks(b)
    n0, n1, n2, n3 = struct.unpack_from('>4H', b, ch[0][0])
    first = 1 + n0 + n0 + n1
    tracks = []
    for t in range(n2):
        o, s = ch[first + t]
        evs = []
        if o is not None:
            tm = struct.unpack_from('>h', b, o + 2)[0]
            for k in range(4, s // 8):
                ty, d, i, b4, b5, w6 = struct.unpack_from('>bBhbbh', b, o + 8 * k)
                if ty == 0 and d == 0: tm = i; continue
                tm += d
                evs.append((tm, k, ty, d, i, b4, b5, w6))
        refo = ch[1 + n0][0]
        kind, rid = struct.unpack_from('>HB', b, refo + 8 * t) if refo is not None else (0, 0)
        tracks.append((t, kind, rid, evs))
    return (n0, n1, n2, n3), tracks
if __name__ == '__main__':
    rom = open(sys.argv[1], 'rb').read()
    if sys.argv[2] == '--scan':
        T, I = int(sys.argv[3], 16), int(sys.argv[4], 16)
        for lv in range(0, 0x40):
            for sc in range(0, 0x40):
                try: r = scene(rom, lv, sc)
                except Exception: r = None
                if not r: continue
                for t, kind, rid, evs in r[1]:
                    for e in evs:
                        if e[2] == T and e[4] == I: print('level %X scene %X track %d time %d event %d b4 %d b5 %d w6 %d' % (lv, sc, t, e[0], e[1], e[5], e[6], e[7]))
        sys.exit()
    lv, sc = int(sys.argv[2], 16), int(sys.argv[3], 16)
    hdr, tracks = scene(rom, lv, sc)
    print('level %X scene %X: n0 %d n1 %d n2 %d n3 %d' % ((lv, sc) + hdr))
    for t, kind, rid, evs in tracks:
        print('track %d (ref kind %d id %d): %d events' % (t, kind, rid, len(evs)))
        for tm, k, ty, d, i, b4, b5, w6 in evs:
            print('  t=%5d #%-3d type %02X id %04X b4 %d b5 %d w6 %d  [%s]' % (tm, k, ty & 0xFF, i & 0xFFFF, b4, b5, w6, owner(ty, i)))
