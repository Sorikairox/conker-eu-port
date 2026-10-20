#!/usr/bin/env python3
"""Rodata for m2c: the .rodata items a function .s references, as labelled asm data.

usage: rodasm.py <func.s> [out.s]   (stdout if no out; prints nothing if the function uses none)

Passing the result as a second input file lets m2c turn `lwc1 %lo(D_x)` into float literals,
jump tables into switch statements and `addiu %lo(D_x)` of strings into string literals.
Items: lwc1 -> 1 word, ldc1 -> 2 words, jtbl_ -> words while they point into the function
(.word .L<addr>), addiu of a NUL-terminated printable string -> .asciz.
Only addresses in a *_data segment at or after its .rodata start are used.
"""
import os, re, sys, struct
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import datarefs as DR

LINE = re.compile(r'/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\S+)\s+(.*)')


def load_syms():
    m = {}
    for f in ('undefined_syms_auto.txt', 'undefined_syms.eu.txt', 'symbol_addrs.eu.txt'):
        p = os.path.join(DR.ROOT, f)
        if os.path.exists(p):
            for l in open(p):
                mm = re.match(r'\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', l)
                if mm:
                    m.setdefault(mm.group(1), int(mm.group(2), 16))
    return m


_CACHE = {}


def rodata_ranges():
    if 'r' not in _CACHE:
        out = []
        for name, s in DR.segments().items():
            if name.endswith('_data') and 'vram' in s:
                rs = [r for r, t, n in s['subs'] if t in ('rodatabin', '.rodata')]
                if rs and s.get('start') is not None and s.get('end') is not None:
                    r0 = min(rs)
                    out.append((r0 - s['start'] + s['vram'], s['end'] - s['start'] + s['vram'],
                                s['vram'] - s['start']))
        _CACHE['r'] = out
        _CACHE['bin'] = open(DR.BIN, 'rb').read()
        _CACHE['syms'] = load_syms()
    return _CACHE['r']


def gen(spath):
    ranges = rodata_ranges()
    data, syms = _CACHE['bin'], _CACHE['syms']
    lines = open(spath).read().split('\n')
    lo = hi = None
    uses = {}
    for l in lines:
        m = LINE.search(l)
        if not m:
            continue
        v = int(m.group(1), 16)
        lo = v if lo is None else lo
        hi = v + 4
        for s in re.findall(r'%lo\((\w+)\)', m.group(3)):
            uses.setdefault(s, set()).add(m.group(2))
    out = []
    for s in sorted(uses, key=lambda x: syms.get(x, 0)):
        va = syms.get(s)
        if va is None:
            mm = re.match(r'(?:D|jtbl)_([0-9A-F]{8})', s)
            va = int(mm.group(1), 16) if mm else None
        if va is None:
            continue
        rng = [r for r in ranges if r[0] <= va < r[1]]
        if not rng:
            continue
        dv = rng[0][2]
        rom = va - dv
        ops = uses[s]
        body = []
        if s.startswith('jtbl_'):
            r = rom
            while True:
                w = struct.unpack('>I', data[r:r + 4])[0]
                if not (lo <= w < hi):
                    break
                body.append('.word .L%08X' % w)
                r += 4
        elif ops & {'lwc1', 'swc1'}:
            body.append('.word 0x%08X' % struct.unpack('>I', data[rom:rom + 4])[0])
        elif ops & {'ldc1', 'sdc1'}:
            body.append('.word 0x%08X, 0x%08X' % struct.unpack('>II', data[rom:rom + 8]))
        elif 'addiu' in ops:
            z = data.find(b'\0', rom)
            st = data[rom:z]
            if z - rom < 200 and all(32 <= c < 127 or c in (9, 10) for c in st):
                esc = st.decode().replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\t', '\\t')
                body.append('.asciz "%s"' % esc)
                body.append('.balign 4')
        if body:
            out.append('glabel %s' % s)
            out.extend(body)
    if not out:
        return ''
    return '.section .rodata\n\n' + '\n'.join(out) + '\n'


if __name__ == '__main__':
    t = gen(sys.argv[1])
    if len(sys.argv) > 2:
        if t:
            open(sys.argv[2], 'w').write(t)
    else:
        sys.stdout.write(t)
