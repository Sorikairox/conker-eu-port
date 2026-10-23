#!/usr/bin/env python3
# P93: list NON_MATCHING bodies in conker/src_eu that call a function taking more than 16 arguments
# (difftest compared only arguments 0..15 before P90).
# Callee arity = max(args read by the callee in the EU ELF disassembly, params of any C prototype / definition).
# Call sites: decoded jal words of the body's asm (EU addresses) + plain calls in the C body text.
# usage: wide_scan.py eu.dis [MIN=17]   (eu.dis = objdump -d --no-show-raw-insn -M no-aliases build/conker.eu.elf)
import re, sys, glob, os
dis, MIN = sys.argv[1], int(sys.argv[2]) if len(sys.argv) > 2 else 17
R = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../..', 'conker')
# 1. callee-side arity from the ELF
addr2name, ar_elf = {}, {}
cur = frame = None
ld = re.compile(r'\s(?:lw|lh|lhu|lb|lbu|lwc1|ldc1|ld|addiu)\s+\w+,(?:sp,)?(-?\d+)\(?sp\)?')
for l in open(dis):
    m = re.match(r'^([0-9a-f]{8}) <([^>]+)>:', l)
    if m:
        cur = m.group(2); addr2name[int(m.group(1), 16)] = cur; frame = None; ar_elf[cur] = 0; continue
    if cur is None: continue
    m = re.search(r'\taddiu\tsp,sp,(-\d+)', l)
    if m and frame is None: frame = -int(m.group(1)); continue
    m = re.search(r'\t(?:lw|lh|lhu|lb|lbu|lwc1|ldc1|ld)\t\w+,(\d+)\(sp\)', l) or re.search(r'\taddiu\t\w+,sp,(\d+)$', l.rstrip())
    if m:
        off = int(m.group(1)) - (frame or 0)
        if 0x40 <= off < 0x400: ar_elf[cur] = max(ar_elf[cur], off // 4 + 1)
# 2. prototype params from C
ar_c = {}
srcs = glob.glob(R + '/src_eu/**/*.[ch]', recursive=True) + glob.glob(R + '/include/**/*.h', recursive=True)
proto = re.compile(r'\b(func_[0-9A-Fa-f]{8}|\w+)\s*\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*[;{]', re.S)
for f in srcs:
    s = open(f, errors='replace').read()
    for m in proto.finditer(s):
        p = m.group(2)
        if p.count(',') < MIN - 1: continue
        # declarations only: first param must start with a type keyword
        if not re.match(r'\s*(?:const\s+)?(?:unsigned\s+)?(?:s8|u8|s16|u16|s32|u32|f32|f64|s64|u64|int|void|char|short|long|float|double|struct|[A-Z]\w*)\b', p): continue
        n = p.count(',') + 1 - p.count('(') // 2 * 0
        ar_c[m.group(1)] = max(ar_c.get(m.group(1), 0), n)
wide = {n: max(ar_elf.get(n, 0), ar_c.get(n, 0)) for n in set(ar_elf) | set(ar_c)}
wide = {n: a for n, a in wide.items() if a >= MIN}
print('# wide callees (>= %d args):' % MIN, ' '.join('%s=%d' % kv for kv in sorted(wide.items())))
# 3. NON_MATCHING bodies
for f in sorted(glob.glob(R + '/src_eu/**/*.c', recursive=True)):
    L = open(f, errors='replace').read().split('\n')
    for i, l in enumerate(L):
        m = re.search(r'GLOBAL_ASM\("(asm/nonmatchings/[^"]+/(\w+)\.s)"\)', l)
        if not m or not L[i-1].startswith('#else'): continue
        fn, asm = m.group(2), R + '/' + m.group(1)
        j = i - 1
        while j > 0 and not L[j].startswith('#ifdef NON_MATCHING'): j -= 1
        body = '\n'.join(L[j+1:i-1])
        hits = {}
        if os.path.exists(asm):
            for a in open(asm):
                mm = re.search(r'/\* \w+ ([0-9A-F]{8}) ([0-9A-F]{8}) \*/\s+jal\s', a)
                if mm:
                    va, w = int(mm.group(1), 16), int(mm.group(2), 16)
                    t = ((w & 0x3FFFFFF) << 2) | (va & 0xF0000000)
                    n = addr2name.get(t, '%08X' % t)
                    if n in wide: hits[n] = 'jal'
        for n in wide:
            if re.search(r'\b%s\s*\(' % n, body) and n not in hits: hits[n] = 'C'
        if hits:
            print('%s\t%s\t%s' % (fn, os.path.basename(f), ' '.join('%s(%d,%s)' % (n, wide[n], k) for n, k in sorted(hits.items()))))
