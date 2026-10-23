#!/usr/bin/env python3
"""P106: extract event script blocks (asset 20 / id) from the EU ROM, as func_1502B5C8(&q, 2, 20, id) loads them.
usage: evasset.py ROM [id ...]  (no ids: scan all ids, print header + opcode/mode statistics)"""
import sys, struct, zlib, collections
rom = open(sys.argv[1], 'rb').read()
BASE = 0xAB2240
def rec(p, k): return struct.unpack_from('>iI', rom, p + 8 * k)
def load(id_):
    off, info = rec(BASE, 20); p = BASE + off
    off2, info2 = rec(p, id_)
    if info2 & 0x0FFFFFFF == 0 or off2 == -1: return None
    q = p + off2; size = ((info2 & 0x0FFFFFFF) + 1) & ~1
    raw = rom[q:q + size]
    if (info2 & 0x70000000) == 0x10000000:
        n = struct.unpack_from('>I', raw)[0] & 0x7FFFFFFF
        raw = zlib.decompressobj(-15).decompress(raw[4:], n)
    return raw
CNT = None
def disasm(b, cnt):
    """linear walk from +0x20 and the 4 entry offsets; returns list of (pc, op, modes)"""
    hdr = struct.unpack_from('>10H', b, 0)
    out = []
    starts = [0x20] + [h for h in hdr[7:10]] + [struct.unpack_from('>H', b, 0x14)[0]]
    return hdr, starts
if __name__ == '__main__':
    ids = [int(x, 16) for x in sys.argv[2:]]
    if ids:
        for i in ids:
            b = load(i)
            print('id %X: %s' % (i, 'none' if b is None else '%d bytes' % len(b)))
            if b: print(b.hex())
    else:
        n = 0
        for i in range(0, 0x400):
            try: b = load(i)
            except Exception: b = None
            if b: n += 1
        print(n, 'event blocks')

# ---- P106 scan: opcode / operand-mode statistics over every event block (linear walk of the code area)
CNTS = bytes.fromhex('0104040404040303030404040404030203030404040404040202020201040400') + bytes(32)
def walk(b):
    end = struct.unpack_from('>H', b, 8)[0] or len(b)
    pc = 0x20; st = collections.Counter(); bad = []
    while pc + 2 <= min(end, len(b)):
        op = struct.unpack_from('>H', b, pc)[0]; at = pc; pc += 2
        o = op & 0x3F; c = CNTS[o]
        st['op%02X' % o] += 1
        if c == 0 or o == 0 or o >= 0x1F: bad.append((at, op)); break
        lng = (op >> 6) & 1
        for k, sh in enumerate((13, 10, 7)[:c - 1]):
            m = (op >> sh) & 7
            st['m%d.%d' % (k + 1, m)] += 1
            if m in (3, 4, 6) and lng: pc += 4; lng = 0; st['long'] += 1
            else: pc += 2
    return st, bad
def scan():
    tot = collections.Counter(); nb = 0; bads = []
    for i in range(0, 0x400):
        try: b = load(i)
        except Exception: b = None
        if not b: continue
        nb += 1; st, bad = walk(b); tot += st
        if bad: bads.append((i, bad))
    print(nb, 'blocks'); print(' '.join('%s=%d' % kv for kv in sorted(tot.items())))
    print('stopped walks (op 0 / >=0x1F / count 0):', len(bads), bads[:8])
if __name__ == '__main__' and len(sys.argv) == 2: scan()
