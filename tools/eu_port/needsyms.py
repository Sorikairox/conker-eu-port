#!/usr/bin/env python3
# usage: needsyms.py [--apply] func...   (host or container; run from anywhere)
# A function that leaves GLOBAL_ASM can take the last reference to a splat auto symbol
# (`D_8009F970 = 0x8009F970;` in undefined_syms_auto.txt) with it; the next clean split then
# drops the symbol and the link fails if the new C names it. For each function, prints the
# symbols its .s references that are only defined in undefined_syms_auto.txt and that its C
# file names; --apply appends them to undefined_syms.eu.txt.
import sys, os, re, glob
C = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'conker')
apply = '--apply' in sys.argv
funcs = [a for a in sys.argv[1:] if a != '--apply']
def defs(p):
    return set(m.group(1) for m in re.finditer(r'^\s*(\w+)\s*=', open(p).read(), re.M))
have = defs(f'{C}/undefined_syms.eu.txt') | defs(f'{C}/symbol_addrs.eu.txt')
auto = {m.group(1): m.group(2) for m in re.finditer(r'^(\w+)\s*=\s*(0x[0-9A-Fa-f]+);', open(f'{C}/undefined_syms_auto.txt').read(), re.M)}
srcs = glob.glob(f'{C}/src_eu/**/*.c', recursive=True)
out = []
for f in funcs:
    s = glob.glob(f'{C}/asm/nonmatchings/*/{f}.s') + glob.glob(f'{C}/asm/nonmatchings/**/{f}.s', recursive=True)
    if not s: print(f, 'no .s'); continue
    syms = set(re.findall(r'%(?:hi|lo)\((\w+)\)', open(s[0]).read()))
    src = next((p for p in srcs if re.search(r'^\w[^;]*\b%s\s*\(' % f, open(p).read(), re.M)), None)
    text = open(src).read() if src else ''
    for y in sorted(syms):
        if y in have or y not in auto or not re.search(r'\b%s\b' % y, text): continue
        out.append(f'{y} = {auto[y]};'); have.add(y); print(f, y, auto[y])
if apply and out:
    with open(f'{C}/undefined_syms.eu.txt', 'a') as fo: fo.write('\n'.join(out) + '\n')
