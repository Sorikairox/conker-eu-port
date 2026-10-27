#!/usr/bin/env python3
"""P337 online multiplayer phase 0: compare two per-retrace state-hash logs and locate a divergence.

  tools/port/nethash_diff.py LOG_A LOG_B [--dump A.bin B.bin] [--max N]

LOG_*: chrome.log (or node output) of runs with ?nethash=F: lines "[nethash] RETRACE H S" (H = static memory, S = fiber
stacks; port/ultra/pc_nethash.c). Prints how many retraces both logs cover, whether they are identical, and the first
retrace where H or S differs.
--dump: memory dumps of both runs at the same ?nethashstop retrace (netrun.sh DUMP=1, port/web/audprobe.js PROBE_DUMP):
compares every hashed byte (the exclusions of port/build/web/conker_netx.txt and the logged GPU write-back ranges are
skipped, as in the hash) and names each differing run of bytes: n64_rdram offsets as N64 addresses with the frozen symbol
(port/symbols/symbols.tsv) and its current name (tools/eu_port/names.tsv), other static bytes by the linker map
(port/build/conker.map), stack bytes by thread slot."""
import bisect, json, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HASH = re.compile(r'^\[nethash\] (\d+) ([0-9A-F]{16}) ([0-9A-F]{16})')
GPU = re.compile(r'GPU write-back range ([0-9A-F]+) \+([0-9A-F]+)')


def read_log(path):
    h, gpu = {}, set()
    for line in open(path, errors='replace'):
        m = HASH.match(line)
        if m:
            h[int(m.group(1))] = (m.group(2), m.group(3))
        m = GPU.search(line)
        if m:
            a = int(m.group(1), 16); gpu.add((a, a + int(m.group(2), 16)))
    return h, gpu


def read_dump(path):
    raw = open(path, 'rb').read()
    nl = raw.index(b'\n')
    info = json.loads(raw[:nl]); o = nl + 1; regs = []
    for r in info['regions']:
        regs.append((r['i'], r['addr'], raw[o:o + r['len']])); o += r['len']
    return info, regs


def map_symbols():
    syms, special = [], {}
    p = ROOT / 'port/build/conker.map'
    for line in open(p):
        f = line.split(None, 3)
        if len(f) == 4 and f[0] != '-' and ':(' in f[3]:
            obj, sec = f[3].strip().rsplit(':(', 1)
            name = sec.rstrip(')').split('.', 2)[-1]
            a, n = int(f[0], 16), int(f[2], 16)
            syms.append((a, n, obj.split('/')[-1] + ':' + name))
            if name in ('n64_rdram', 'n64_seg16'):
                special[name] = (a, n)
    syms.sort()
    return syms, special


def n64_symbols():
    rows = []
    for line in open(ROOT / 'port/symbols/symbols.tsv'):
        if line.startswith('#'):
            continue
        f = line.rstrip('\n').split('\t')
        if len(f) > 3 and re.fullmatch(r'[0-9A-Fa-f]{8}', f[1]) and f[3] not in ('func', 'none'):
            rows.append((int(f[1], 16), int(f[2] or '0', 16) if re.fullmatch(r'[0-9A-Fa-f]+', f[2] or '') else 0, f[0]))
    rows.sort()
    new = {}
    for line in open(ROOT / 'tools/eu_port/names.tsv'):
        f = line.rstrip('\n').split('\t')
        if len(f) >= 2 and not line.startswith('#'):
            new[f[0]] = f[1]
    return rows, new


def name_n64(addr, rows, new):
    i = bisect.bisect_right([r[0] for r in rows], addr) - 1
    if i < 0:
        return '?'
    a, n, s = rows[i]
    label = s + (f' ({new[s]})' if s in new else '')
    return f'{label}+0x{addr - a:X}' + ('' if not n or addr < a + n else ' (past its end)')


def main():
    args = sys.argv[1:]
    dumps = None; mx = 40
    if '--dump' in args:
        k = args.index('--dump'); dumps = args[k + 1:k + 3]; del args[k:k + 3]
    if '--max' in args:
        k = args.index('--max'); mx = int(args[k + 1]); del args[k:k + 2]
    if len(args) != 2:
        sys.exit(__doc__)
    (ha, ga), (hb, gb) = read_log(args[0]), read_log(args[1])
    common = sorted(set(ha) & set(hb))
    print(f'A: {len(ha)} hashed retraces, B: {len(hb)}; common {len(common)}' + (f' ({common[0]}..{common[-1]})' if common else ''))
    first = next((f for f in common if ha[f] != hb[f]), None)
    if not common:
        print('NO COMMON RETRACES: nothing to compare')
    elif first is None:
        print(f'IDENTICAL: all {len(common)} common retraces have the same static and stack hashes')
    else:
        a, b = ha[first], hb[first]
        what = ' and '.join(w for w, x, y in (('static memory', a[0], b[0]), ('fiber stacks', a[1], b[1])) if x != y)
        ndiff = sum(1 for f in common if ha[f] != hb[f])
        print(f'DIVERGED at retrace {first}: {what} ({ndiff} of {len(common)} common retraces differ); last equal: '
              f'{max([f for f in common if f < first], default="none")}')
        for k, w in ((0, 'static memory'), (1, 'fiber stacks')):
            fk = next((f for f in common if ha[f][k] != hb[f][k]), None)
            nk = sum(1 for f in common if ha[f][k] != hb[f][k])
            print(f'  {w}: ' + (f'first differs at retrace {fk}, {nk} retraces differ' if fk else 'identical at every common retrace'))
    if not dumps:
        return
    (ia, ra), (ib, rb) = read_dump(dumps[0]), read_dump(dumps[1])
    print(f'dumps at retrace {ia["frame"]} / {ib["frame"]}')
    excl = []
    for line in open(ROOT / 'port/build/web/conker_netx.txt'):
        f = line.split()
        if len(f) >= 2:
            a = int(f[0], 16); excl.append((a, a + int(f[1], 16)))
    excl += sorted(ga | gb)
    syms, special = map_symbols()
    rows, new = n64_symbols()
    sym_addrs = [s[0] for s in syms]
    rb_by = {i: (a, d) for i, a, d in rb}
    runs = []
    for i, addr, da in ra:
        if i not in rb_by:
            runs.append((i, addr, len(da), 'region only in A')); continue
        addr_b, db = rb_by[i]
        if addr_b != addr or len(db) != len(da):
            runs.append((i, addr, len(da), f'region moved / resized in B ({addr_b:08X} +{len(db):X})')); continue
        mask = bytearray(len(da))
        if i == 0:
            for a, b in excl:
                lo, hi = max(a - addr, 0), min(b - addr, len(da))
                if lo < hi:
                    mask[lo:hi] = b'\x01' * (hi - lo)
        o, n = 0, len(da)
        while o < n:
            # skip equal 4 KB blocks fast
            if da[o:o + 4096] == db[o:o + 4096]:
                o += 4096; continue
            end = min(o + 4096, n); k = o
            while k < end:
                if da[k] != db[k] and not mask[k]:
                    s = k
                    while k < end and (da[k] != db[k] or (k + 1 < end and da[k + 1] != db[k + 1])) and not mask[k]:
                        k += 1
                    runs.append((i, addr + s, k - s, None))
                k += 1
            o = end
    print(f'{len(runs)} differing byte runs (excluded ranges skipped)')
    for i, a, n, note in runs[:mx]:
        if note:
            print(f'  region {i}: {note}'); continue
        if i == 0:
            where = '?'
            for name, (ba, bn) in special.items():
                if ba <= a < ba + bn:
                    base = 0x80000000 if name == 'n64_rdram' else 0x16000000
                    where = f'{name} N64 {base + a - ba:08X} {name_n64(base + a - ba, rows, new)}'
            if where == '?':
                j = bisect.bisect_right(sym_addrs, a) - 1
                if j >= 0:
                    sa, sn, nm = syms[j]
                    where = f'{nm}+0x{a - sa:X}' + ('' if a < sa + sn else ' (between symbols)')
        else:
            where = f'thread slot {(i - 1) >> 1} {"asyncify" if (i - 1) & 1 else "C"} stack'
        print(f'  {a:08X} +{n:<5X} {where}')


if __name__ == '__main__':
    main()
