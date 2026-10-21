#!/usr/bin/env python3
"""List symbols used as data in one TU and as a function in another (wasm-ld 'symbol type mismatch')."""
import sys, os, collections
sys.path.insert(0, os.path.dirname(__file__)); import wasmobj
use = collections.defaultdict(lambda: collections.defaultdict(set))
for o in sys.argv[1:]:
    for nm, kind, flags, sig in wasmobj.read(o):
        if nm and not flags & wasmobj.LOCAL and kind in (0, 1):
            use[nm][kind].add(os.path.basename(o))
for nm, k in sorted(use.items()):
    if len(k) == 2:
        print(f"{nm}\tdata-in: {' '.join(sorted(k[1]))}\tfunc-in: {' '.join(sorted(k[0]))[:120]}")
