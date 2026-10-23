#!/usr/bin/env python3
"""P124: find '&spXX' of a scalar stack local passed to a call while other spYY locals sit
above it (the m2c 'scattered struct' pattern: callee reads N bytes from &spXX).
Usage: spaddr_scan.py src_eu/*.c  -> TSV: file func line local type n_higher_locals callee"""
import re, sys
SCALAR = re.compile(r'^\s*(?:volatile\s+)?((?:unsigned\s+)?(?:s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|int|char|short|long|void\s*\*|[A-Za-z_]\w*\s*\*+|\w+\s*\*+))\s*(sp[0-9A-Fa-f]+)\s*;')
FUNC = re.compile(r'^[A-Za-z_][\w\s\*]*\b(func_[0-9A-F]+)\s*\([^;]*\)\s*\{\s*$')
for path in sys.argv[1:]:
    lines = open(path, errors='replace').read().split('\n')
    i = 0
    while i < len(lines):
        m = FUNC.match(lines[i])
        if not m:
            i += 1; continue
        name = m.group(1); depth = 0; body = []; j = i
        while j < len(lines):
            depth += lines[j].count('{') - lines[j].count('}')
            body.append((j + 1, lines[j]))
            if depth <= 0 and j > i: break
            j += 1
        decl = {}
        for ln, t in body[1:]:
            d = SCALAR.match(t)
            if d: decl[d.group(2)] = d.group(1).strip()
        allsp = [k for k in decl]
        for ln, t in body[1:]:
            for a in re.finditer(r'&(sp[0-9A-Fa-f]+)\b(?!\s*\[)', t):
                v = a.group(1)
                if v not in decl: continue
                off = int(v[2:], 16)
                higher = [k for k in allsp if int(k[2:], 16) > off]
                if not higher: continue
                c = re.search(r'(func_[0-9A-F]+|\w+)\s*\([^()]*&' + v, t)
                print(f"{path}\t{name}\t{ln}\t{v}\t{decl[v]}\t{len(higher)}\t{c.group(1) if c else '?'}")
        i = j + 1
