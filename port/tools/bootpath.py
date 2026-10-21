#!/usr/bin/env python3
"""Which asm-only functions sit on the boot path? BFS over `jal` targets from the given roots.
usage: python3 port/tools/bootpath.py [--depth N] ROOT...   (host or container, from the repo root)
Prints each reachable function with its depth and whether it has C (C) or is GLOBAL_ASM (ASM).
C bodies are scanned for calls with a regex, asm bodies for `jal`."""
import os, re, sys, glob
sys.path.insert(0, os.path.dirname(__file__))
from gen_stubs import asm_only
args = sys.argv[1:]; depth = 4
if args[:1] == ['--depth']: depth = int(args[1]); args = args[2:]
asm = asm_only()
asmfile = {os.path.splitext(os.path.basename(p))[0]: p for p in glob.glob('conker/asm/nonmatchings/**/*.s', recursive=True)}
cbody = {}
for p in glob.glob('conker/src_eu/**/*.c', recursive=True):
    src = open(p, errors='replace').read()
    for m in re.finditer(r'^\w[\w\s\*]*?\b(func_[0-9A-F]{8}|\w+)\s*\(([^;{]*)\)\s*\{', src, re.M):
        end = src.find('\n}', m.end())
        cbody.setdefault(m[1], src[m.end():end])
def callees(f):
    if f in asm and f in asmfile:
        return re.findall(r'\bjal\s+(\w+)', open(asmfile[f]).read())
    return re.findall(r'\b(func_[0-9A-F]{8}|os\w+|__os\w+)\s*\(', cbody.get(f, ''))
seen = {}; q = [(r, 0) for r in args]
while q:
    f, d = q.pop(0)
    if f in seen: continue
    seen[f] = d
    if d < depth: q += [(c, d + 1) for c in callees(f) if c not in seen]
n_asm = 0
for f, d in sorted(seen.items(), key=lambda x: (x[1], x[0])):
    kind = 'ASM' if f in asm else ('C' if f in cbody else '?')
    n_asm += kind == 'ASM'
    print(f'{d}  {kind:3}  {f}  {asm.get(f, "")}')
print(f'# {len(seen)} functions within depth {depth}; {n_asm} asm-only')
