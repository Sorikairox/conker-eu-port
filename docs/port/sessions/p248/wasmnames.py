#!/usr/bin/env python3
"""P248: print wasm function names for table indices / function indices given in hex (name section; indirect
function table entries via the element section).  wasmnames.py WASM HEX..."""
import sys
def leb(b, i):
    r = s = 0
    while True:
        x = b[i]; i += 1; r |= (x & 0x7f) << s; s += 7
        if x < 0x80: return r, i
b = open(sys.argv[1], 'rb').read(); i = 8; names = {}; elems = {}; nimp = 0
while i < len(b):
    sid = b[i]; i += 1; sz, i = leb(b, i); end = i + sz
    if sid == 2:
        n, j = leb(b, i)
        for _ in range(n):
            for _ in range(2):
                l, j = leb(b, j); j += l
            k = b[j]; j += 1
            if k == 0: _, j = leb(b, j); nimp += 1
            elif k == 1: j += 1; fl, j = leb(b, j); _, j = leb(b, j); j = j if not fl & 1 else leb(b, j)[1]
            elif k == 2: fl, j = leb(b, j); _, j = leb(b, j); j = j if not fl & 1 else leb(b, j)[1]
            elif k == 3: j += 2
    elif sid == 9:
        n, j = leb(b, i)
        for _ in range(n):
            fl, j = leb(b, j)
            if fl == 0:
                assert b[j] == 0x41; off, j = leb(b, j + 1); j += 1   # i32.const off; end
                c, j = leb(b, j)
                for k in range(c):
                    f, j = leb(b, j); elems[off + k] = f
            else:
                break
    elif sid == 0:
        l, j = leb(b, i); nm = b[j:j + l]; j += l
        if nm == b'name':
            while j < end:
                t = b[j]; j += 1; ssz, j = leb(b, j); se = j + ssz
                if t == 1:
                    n, j = leb(b, j)
                    for _ in range(n):
                        idx, j = leb(b, j); l, j = leb(b, j); names[idx] = b[j:j + l].decode(errors='replace'); j += l
                j = se
    i = end
for h in sys.argv[2:]:
    v = int(h, 16); f = elems.get(v)
    print(h, 'table ->', f, names.get(f, '?'))
