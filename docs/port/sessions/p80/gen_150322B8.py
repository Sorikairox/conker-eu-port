#!/usr/bin/env python3
"""P80: generate the C tables / switch cases of func_150322B8 (game_eu_5D910.c, NON_MATCHING) from the ROM.

The seven jump tables of func_150322B8 (jtbl_80097490 ... jtbl_80097EF0) are read from the ROM image
(conker/conker.eu.bin = the decompressed EU ROM splat works from; its sha1 is checked against conker.eu.sha1;
located by searching the bytes the splat .s lists, and both must agree). Each table entry is a
code address; the code block at that address is classified from the function's .s:
  - `b .L15033398` + `addiu $a2, $zero, X` (or `or $a2, $zero, $zero`)  -> value X  (the animation index)
  - `b .L15033498` + `addiu $v0, $zero, 1`                             -> RET1 (return 1, no animation change)
  - anything else                                                        -> CODE (hand-written case in the C)
Value-only tables are printed as `static const u8` arrays (the default of the range check is printed with them),
mixed tables as grouped `case` labels.

usage: gen_150322B8.py [ROM] [ASM]   (defaults: conker/conker.eu.bin, conker/asm/.../func_150322B8.s)
"""
import re
import sys
import os
import hashlib

ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '../../../..'))
ROM = sys.argv[1] if len(sys.argv) > 1 else os.path.join(ROOT, 'conker/conker.eu.bin')
ASM = sys.argv[2] if len(sys.argv) > 2 else os.path.join(ROOT, 'conker/asm/nonmatchings/game_eu_5D910/func_150322B8.s')

src = open(ASM).read().splitlines()
rom = open(ROM, 'rb').read()
want = open(os.path.join(ROOT, 'conker/conker.eu.sha1')).read().split()[0]
if hashlib.sha1(rom).hexdigest() != want:
    sys.exit('%s: sha1 is not the EU ROM image (%s)' % (ROM, want))

# --- tables as listed by splat
tables = {}
order = []
cur = None
for ln in src:
    m = re.match(r'glabel (jtbl_[0-9A-F]+)', ln.strip())
    if m:
        cur = m.group(1); tables[cur] = []; order.append(cur); continue
    if ln.strip() == '.text':
        cur = None
    if cur and ln.strip().startswith('.word'):
        tables[cur] += [int(w, 16) for w in ln.strip()[5:].split(',')]

# --- the same words from the ROM (table bytes are unique in the ROM; must be found exactly once)
for name in order:
    blob = b''.join(w.to_bytes(4, 'big') for w in tables[name])
    at = rom.find(blob)
    if at < 0 or rom.find(blob, at + 1) >= 0:
        sys.exit('%s: not found exactly once in the ROM' % name)
    romw = [int.from_bytes(rom[at + 4 * i: at + 4 * i + 4], 'big') for i in range(len(tables[name]))]
    assert romw == tables[name]
    tables[name] = romw
    print('/* %s: %d entries, ROM offset 0x%X */' % (name, len(romw), at), file=sys.stderr)

# --- code blocks: address -> the two instructions after the label
ins = []   # (addr, text)
for ln in src:
    m = re.match(r'\s*/\* [0-9A-F]+ ([0-9A-F]+) [0-9A-F]+ \*/\s*(.*)', ln)
    if m:
        ins.append((int(m.group(1), 16), re.sub(r'\s+', ' ', m.group(2).strip())))
byaddr = {a: i for i, (a, _) in enumerate(ins)}


def classify(addr):
    if addr == 0x15033398:
        return 'KEEP'      # the common tail with no new animation (index stays -1)
    i = byaddr[addr]
    a, b = ins[i][1], ins[i + 1][1]
    if a == 'b .L15033398':
        m = re.match(r'addiu \$a2, \$zero, (-?0x[0-9A-F]+|\d+)$', b)
        if m:
            return int(m.group(1), 16) if 'x' in m.group(1) else int(m.group(1))
        if b == 'or $a2, $zero, $zero':
            return 0
    if a == 'b .L15033498' and b == 'addiu $v0, $zero, 0x1':
        return 'RET1'
    return 'CODE@%08X' % addr


def fmt(v):
    return '0x%02X' % v if isinstance(v, int) else v


# switch key: (first key value, key description) per table, from the asm's range checks
KEYS = {
    'jtbl_80097490': (0x58, 'obj[4] (object kind)'),
    'jtbl_8009751C': (0x00, 'anim id obj+0x84 (kinds 0x5A / 0x74 / 0x7A)'),
    'jtbl_800975C8': (0x83, 'att[1] (attachment model id)'),
    'jtbl_8009763C': (0x14, 'anim id (model 0x9A, object kind 0x99)'),
    'jtbl_8009767C': (0x17F, 'anim id (models 0x8F / 0x90)'),
    'jtbl_80097DB8': (0x104, 'anim id (models 0x8F / 0x90)'),
    'jtbl_80097EF0': (0x171, 'anim id (model 0x87)'),
}

for name in order:
    base, what = KEYS[name]
    vals = [classify(a) for a in tables[name]]
    n = len(vals)
    print('/* generated from %s (ROM): %s 0x%X..0x%X */' % (name, what, base, base + n - 1))
    if all(isinstance(v, int) for v in vals):
        cname = 'sAnim_%s' % name[5:]
        print('static const u8 %s[0x%X] = {' % (cname, n))
        for k in range(0, n, 16):
            row = ', '.join(fmt(v) for v in vals[k:k + 16])
            print('    /* 0x%03X */ %s,' % (base + k, row))
        print('};')
    else:
        groups = {}
        for k, v in enumerate(vals):
            groups.setdefault(v, []).append(base + k)
        for v, keys in groups.items():
            print('    /* %s */ %s' % (fmt(v), ' '.join('case 0x%X:' % x for x in keys)))
    print()
