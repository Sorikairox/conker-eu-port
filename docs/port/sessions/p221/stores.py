#!/usr/bin/env python3
# P221 reading aid: lists the constant stack stores of an asm line range (straight-line register tracking:
# lui / addiu / ori / mtc1 / lwc1 %lo(sym)), as "off size value". usage: stores.py file.s FIRSTLINE LASTLINE
import re, sys
L = open(sys.argv[1]).read().split('\n')[int(sys.argv[2]) - 1:int(sys.argv[3])]
r = {'$zero': 0}; hi = {}; out = {}
for l in L:
    m = re.search(r'\*/\s+(\S+)\s+(.*)$', l)
    if not m: continue
    op, a = m.group(1), [x.strip() for x in m.group(2).split(',')]
    if op == 'lui':
        mm = re.match(r'\((0x[0-9A-F]+) >> 16\)', a[1]); r[a[0]] = int(mm.group(1), 16) & 0xFFFF0000 if mm else None
        if '%hi' in a[1]: r[a[0]] = re.search(r'%hi\((\w+)\)', a[1]).group(1)
    elif op == 'addiu':
        if '%lo' in a[2]: r[a[0]] = '&' + re.search(r'%lo\((\w+)\)', a[2]).group(1)
        elif r.get(a[1]) == 0 or a[1] == '$zero': r[a[0]] = int(a[2], 0) & 0xFFFFFFFF
        else: r[a[0]] = None
    elif op == 'ori': r[a[0]] = ('%s|%s' % (r.get(a[1]), a[2]))
    elif op == 'mtc1': r[a[1]] = r.get(a[0])
    elif op == 'lwc1':
        mm = re.search(r'%lo\((\w+)\)', a[1]); r[a[0]] = mm.group(1) if mm else 'sp:' + a[1]
    elif op == 'lhu' or op == 'lw' or op == 'lbu': r[a[0]] = 'load:' + a[1]
    elif op in ('sw', 'sh', 'sb', 'swc1'):
        mm = re.match(r'(-?0x[0-9A-F]+|\d+)\(\$sp\)', a[1])
        if mm:
            v = r.get(a[0], '?'); off = int(mm.group(1), 0)
            if isinstance(v, int) and op == 'swc1':
                import struct; v = '%gf' % struct.unpack('>f', struct.pack('>I', v))[0]
            elif isinstance(v, int): v = v - (1 << 32) if v & 0x80000000 else v; v = hex(v)
            out[off] = (op, v)
for o in sorted(out): print('%X %s %s' % (o, out[o][0], out[o][1]))
