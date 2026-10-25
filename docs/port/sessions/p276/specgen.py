#!/usr/bin/env python3
"""P276: generate C assignments for an Emitter2Spec built on the stack by a constant-filler function (asm .s).
usage: specgen.py file.s  -> prints `spec.uXXX = value;` lines (base = the a1 sp offset of the func_15199A28 call)."""
import re, struct, sys
src = open(sys.argv[1]).read()
rod = {m.group(1): int(m.group(2), 16) for m in re.finditer(r'glabel (D_\w+)\n\.word (0x[0-9A-Fa-f]+)', src)}
def flit(b):
    v = struct.unpack('>f', struct.pack('>I', b))[0]
    if v == 0: return '0.0f'
    if v == int(v) and abs(v) < 1e7: return '%d.0f' % int(v)
    for p in range(1, 10):
        s = '%.*g' % (p, v)
        if struct.pack('>f', float(s)) == struct.pack('>I', b):
            if 'e' not in s and '.' not in s: s += '.0'
            return s + 'f'
    raise SystemExit('no literal for %08X' % b)
R = {'zero': ('i', 0)}; stores = {}; base = None
for line in src.split('\n'):
    m = re.match(r'\s*/\*.*?\*/\s+(\w+(?:\.\w+)?)\s+(.*)', line)
    if not m: continue
    op, args = m.group(1), [a.strip() for a in re.split(r',\s*', m.group(2).split('/*')[0].strip())]
    rn = lambda a: a.lstrip('$')
    if op == 'lui':
        mm = re.match(r'\((0x[0-9A-F]+) >> 16\)', args[1])
        R[rn(args[0])] = ('i', int(mm.group(1), 16)) if mm else ('hi', args[1])
    elif op == 'mtc1': R[rn(args[1])] = ('f', R[rn(args[0])][1])
    elif op == 'lwc1':
        mm = re.match(r'%lo\((\w+)\)', args[1]); R[rn(args[0])] = ('f', rod[mm.group(1)])
    elif op == 'addiu' and args[1] == '$zero': R[rn(args[0])] = ('i', int(args[2], 0) & 0xFFFFFFFF)
    elif op == 'addiu' and args[1] == '$sp' and args[0] == '$a1': base = int(args[2], 0)
    elif op == 'lw' and '%lo(' in args[1]: R[rn(args[0])] = ('e', re.match(r'%lo\((\w+)\)', args[1]).group(1))
    elif op in ('lbu', 'lb'):
        mm = re.match(r'(-?0x[0-9A-F]+|\d+)\(\$(\w+)\)', args[1]); b = R.get(mm.group(2))
        R[rn(args[0])] = ('e', '((u8 *) %s)[%s]' % (b[1], mm.group(1))) if b and b[0] == 'e' else ('?', line)
    elif op in ('sw', 'sh', 'sb', 'swc1'):
        mm = re.match(r'(-?0x[0-9A-F]+|\d+)\(\$sp\)', args[1])
        if mm: stores[int(mm.group(1), 0)] = (op, R.get(rn(args[0]), ('?', args[0])))
    elif op == 'or' and args[1] == '$zero' and args[2] == '$zero': R[rn(args[0])] = ('i', 0)
for off in sorted(stores):
    if base is None or off < base or off >= base + 0x11C: continue
    op, v = stores[off]; o = off - base
    if v[0] == 'f': val = flit(v[1])
    elif v[0] == 'i':
        x = v[1]
        if op == 'sb': x &= 0xFF; val = '0x%X' % x if x > 9 else str(x)
        elif op == 'sh': x = x - 0x10000 if (x & 0xFFFF) >= 0x8000 else x & 0xFFFF; val = ('0x%X' % x if x > 9 else str(x)) if x >= 0 else str(x)
        else: x = x - (1 << 32) if x >= 0x80000000 else x; val = ('0x%X' % x if x > 9 else str(x)) if x >= 0 else str(x)
        if op == 'swc1': val = flit(v[1])
    elif v[0] == 'e': val = '(u8 *) ' + v[1] if v[1].startswith('D_') else v[1]
    else: val = '/* ? %s */' % (v,)
    print('    spec.u%03X = %s;' % (o, val))
