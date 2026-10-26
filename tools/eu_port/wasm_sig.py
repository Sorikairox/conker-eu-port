#!/usr/bin/env python3
"""md5 of a wasm file without its custom sections (the `name` section holds function names): two builds with the same
signature run the same code on the same data layout, so a pure rename must keep it.
Usage: tools/eu_port/wasm_sig.py [port/build/web/conker.wasm]"""
import hashlib, sys

d = open(sys.argv[1] if len(sys.argv) > 1 else 'port/build/web/conker.wasm', 'rb').read()
h, i = hashlib.md5(d[:8]), 8
while i < len(d):
    j, sz, s = i + 1, 0, 0
    while True:
        b = d[j]; j += 1; sz |= (b & 0x7F) << s; s += 7
        if b < 0x80:
            break
    if d[i] != 0:          # 0 = custom section
        h.update(d[i:j + sz])
    i = j + sz
print(h.hexdigest())
