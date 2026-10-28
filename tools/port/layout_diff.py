#!/usr/bin/env python3
"""P353: compare two memory dumps (port/web/audprobe.js PROBE_DUMP, taken at the same ?nethashstop retrace) of two
builds that differ only in where the n64_rdram mirror is (port/Makefile RDRAM_SHIFT, tools/port/scripts/layout_cmp.sh).

Every aligned word that is a wasm pointer into the mirror (or n64_seg16) is compared as its N64 address, so only real
differences of game state are listed, grouped into runs and named with the symbols of each build's conker.map
(mirror offsets also with the N64 data symbol from port/symbols/symbols.tsv when there is one).
  layout_diff.py A.dump A_conker.map B.dump B_conker.map [--max N] [--real]
Exit status 1 when a difference is not explained as a stale pointer fragment or address text.
"""
import bisect
import json
import re
import struct
import sys


def load_map(path):
    syms = []
    for l in open(path, errors='replace'):
        m = re.match(r'^\s*([0-9a-f]+)\s+([0-9a-f]+)\s+([0-9a-f]+)\s+(\S+)\s*$', l)
        if m and int(m[1], 16) >= 0x10000000 and not m[4].startswith(('build/', '<')):
            syms.append((int(m[1], 16), int(m[3], 16), m[4]))
    syms.sort()
    addrs = [s[0] for s in syms]
    rd = next(a for a, _, n in syms if n == 'n64_rdram')
    sg = next(a for a, _, n in syms if n == 'n64_seg16')
    pads = [(a, a + z) for a, z, n in syms if n in ('port_rdram_pad_lo', 'port_rdram_pad_hi')]
    return syms, addrs, rd, sg, pads


def load_n64syms():
    out = []
    try:
        for l in open('port/symbols/symbols.tsv'):
            f = l.rstrip('\n').split('\t')
            if len(f) >= 2:
                try:
                    a = int(f[1], 16) if not f[1].startswith('0x') else int(f[1], 16)
                except ValueError:
                    continue
                if 0x80000000 <= a < 0x80800000:
                    out.append((a, f[0]))
    except OSError:
        pass
    out.sort()
    return out


def load_dump(path):
    with open(path, 'rb') as f:
        hdr = json.loads(f.readline())
        regs = []
        for r in hdr['regions']:
            regs.append((r['i'], r['addr'], f.read(r['len'])))
    return hdr, regs


def name(mp, n64s, a):
    syms, addrs, rd, sg, _ = mp
    if 0 <= a - rd < 0x800000:
        n64 = 0x80000000 + a - rd
        i = bisect.bisect_right([x[0] for x in n64s], n64) - 1
        nm = f'{n64s[i][1]}+0x{n64 - n64s[i][0]:X}' if i >= 0 and n64 - n64s[i][0] < 0x10000 else ''
        return f'N64 {n64:08X} {nm}'
    i = bisect.bisect_right(addrs, a) - 1
    if i >= 0:
        s = syms[i]
        return f'{s[2]}+0x{a - s[0]:X}' + ('' if a - s[0] < max(s[1], 1) else ' (past end)')
    return '?'


def main():
    a_d, a_m, b_d, b_m = sys.argv[1:5]
    mx = int(sys.argv[sys.argv.index('--max') + 1]) if '--max' in sys.argv else 60
    words = '--words' in sys.argv
    A, B = load_map(a_m), load_map(b_m)
    # the ranges the state hash leaves out (port/tools/net_regions.py), next to the map in a layout_cmp.sh build dir
    netx = []
    try:
        for l in open(a_m.rsplit('/', 1)[0] + '/conker_netx.txt'):
            f = l.split()
            if len(f) >= 2: netx.append((int(f[0], 16), int(f[0], 16) + int(f[1], 16)))
    except OSError:
        print('(no conker_netx.txt next to the map: nothing excluded)')
    netx.sort()
    nxa = [a for a, _ in netx]
    def excluded(addr):
        i = bisect.bisect_right(nxa, addr) - 1
        return i >= 0 and addr < netx[i][1]
    n64s = load_n64syms()
    ha, ra = load_dump(a_d)
    hb, rb = load_dump(b_d)
    print(f'A {a_d}: n64_rdram {A[2]:08X}, retrace {ha["frame"]}; B {b_d}: n64_rdram {B[2]:08X}, retrace {hb["frame"]}')

    def norm(mp, w):
        rd, sg = mp[2], mp[3]
        if 0 <= w - rd < 0x800000: return 0x80000000 + w - rd, 1
        if 0 <= w - sg < 0x10000: return 0x16000000 + w - sg, 1
        return w, 0

    runs = []
    total = 0
    for (ia, aa, da), (ib, ab, db) in zip(ra, rb):
        if len(da) != len(db):
            print(f'region {ia}: length differs {len(da)} vs {len(db)}; compared up to the shorter')
        n = min(len(da), len(db)) // 4 * 4
        # address in A -> address in B for the same object (static region: same address except inside the mirror)
        wa = struct.unpack_from(f'<{n // 4}I', da)
        wb = struct.unpack_from(f'<{n // 4}I', db)
        if ia == 0:
            # the mirror sits at different offsets of the region in A and B: its words are paired by N64 offset; the
            # shift pads (zero in both, different sizes) are skipped; every other word has the same address in both
            ra0, rb0 = (A[2] - aa) // 4, (B[2] - ab) // 4
            pads = [((lo - aa) // 4, (hi - aa) // 4) for lo, hi in A[4]]
            def pairs():
                for k in range(len(wa)):
                    if ra0 <= k < ra0 + 0x200000:
                        yield k, rb0 + (k - ra0)
                    elif not any(lo <= k < hi for lo, hi in pads):
                        yield k, k
            idx = pairs()
        else:
            idx = [(k, k) for k in range(len(wa))]
        cur = None
        for k, kb in idx:
            x, px = norm(A, wa[k])
            y, py = norm(B, wb[kb])
            if x != y and wa[k] != wb[kb]:   # equal raw values are data that merely look like mirror pointers
                addr = aa + 4 * k
                if ia == 0 and excluded(addr):
                    continue
                total += 1
                if cur and cur['reg'] == ia and k == cur['end'] + 1:
                    cur['end'] = k
                    cur['n'] += 1
                    cur['all'].append((wa[k], wb[kb]))
                    if len(cur['w']) < 4: cur['w'].append((wa[k], wb[kb]))
                else:
                    cur = {'reg': ia, 'start': k, 'end': k, 'n': 1, 'addr': addr, 'w': [(wa[k], wb[kb])], 'all': [(wa[k], wb[kb])]}
                    runs.append(cur)
    # classify: a stale fragment of a mirror pointer (some byte-aligned window of the two words differs by exactly the
    # mirror displacement, the rest is equal: bytes of a freed block's pointers that a new owner never overwrote), log
    # text that prints an address (ASCII hex digits), or a real difference
    d = (B[2] - A[2]) & 0xFFFFFFFF
    def fragment(x, y):
        for lo in (0, 8, 16):
            for hi in (16, 24, 32):
                if hi - lo < 8:
                    continue
                m = ((1 << (hi - lo)) - 1) << lo
                k = (1 << (hi - lo)) - 1
                # the window of p + d is the window of p plus d's window, plus a carry from the bits below it
                if (x & ~m) == (y & ~m) and (((y & m) - (x & m)) >> lo) & k in ((d >> lo) & k, ((d >> lo) + 1) & k):
                    return True
        return False
    def text(x, y):
        hx = set(b'0123456789abcdefABCDEF')
        return all(c in hx for c in x.to_bytes(4, 'little')) and all(c in hx for c in y.to_bytes(4, 'little'))
    real = 0
    for r in runs:
        r['kind'] = ' '.join('frag' if fragment(x, y) else 'text' if text(x, y) else 'REAL' for x, y in r['w'])
        r['real'] = any(not fragment(x, y) and not text(x, y) for x, y in r['all'])
        real += r['real']
    print(f'{total} differing words in {len(runs)} runs; {real} runs not explained as stale pointer fragments / '
          f'address text: {"none" if not real else "see REAL below"}')
    if '--real' in sys.argv:
        runs = [r for r in runs if r['real']]
    for r in runs[:mx]:
        addr = r['addr']
        where = name(A, n64s, addr) if r['reg'] == 0 else f'stack region {r["reg"]} +0x{addr - [x for x in ra if x[0] == r["reg"]][0][1]:X}'
        ws = ' '.join(f'{x:08X}/{y:08X}' for x, y in r['w'])
        print(f'  {addr:08X} {r["n"]:6d} words  {where}   A/B: {ws}  [{r["kind"]}]')
    return real


if __name__ == '__main__':
    sys.exit(1 if main() else 0)
