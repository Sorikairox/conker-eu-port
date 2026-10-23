#!/usr/bin/env python3
# P134: list NM bodies whose reference has a call site where the P132 trap-check scan finds stack argument stores
# the pre-P132 scan missed (an IDO division trap check between the argument stores and the jal).
# Run inside the container from /conker/conker:  python3 ../docs/port/sessions/p134/trapscan.py
import sys, re, glob
sys.path.insert(0, '../tools/port/difftest')
import difftest as D

out = []
for p in sorted(glob.glob('src_eu/**/*.c', recursive=True)):
    src = open(p).read()
    for m in D.PRAG.finditer(src):
        func = m.group(2)
        if not re.search(r'^[A-Za-z_][^\n;#/]*\b%s\s*\([^;{]*?\)\s*\{' % func, src, re.M): continue   # no NM body
        try: vram, w = D.ref_from_s(m.group(1) + '/' + func + '.s')
        except OSError: continue
        for i, x in enumerate(w):
            if (x >> 26) != 3 and x & 0xFC00003F != 9: continue
            D.TRAPSCAN_OLD = True;  _, _, s0 = D.call_site_writes(w, i)
            D.TRAPSCAN_OLD = False; _, _, s1 = D.call_site_writes(w, i)
            if s1 != s0:
                tgt = ((vram + 4 * i + 4) & 0xF0000000) | ((x & 0x3FFFFFF) << 2) if (x >> 26) == 3 else 0
                callee = (D.addr2name(tgt) or '0x%08X' % tgt) if tgt else 'jalr'
                out.append('%s\t%s\t%08X\t%s\tnew %s\n' % (p, func, vram + 4 * i, callee,
                           ','.join('%X' % o for o in sorted(s1 - s0))))
sys.stdout.write(''.join(out))
