#!/usr/bin/env python3
"""Inventory commented C drafts (/* */, #if 0, #ifdef NON_MATCHING, // lines) of functions that are
still GLOBAL_ASM, in main-slice files (game first func >= 0x15190000, plus init*).
usage: cinv.py outdir   -> writes outdir/<func>.c (draft body only) and prints 'file func insns'"""
import re, os, sys, glob
SRC = os.path.expanduser('~/conker/conker/src_eu')
out = sys.argv[1]
os.makedirs(out, exist_ok=True)
pragma = re.compile(r'#pragma GLOBAL_ASM\("([^"]+)"\)')

def addr(name):
    m = re.match(r'func_(?:eu_)?([0-9A-Fa-f]{8})$', name)
    return int(m.group(1), 16) if m else None

def regions(text):
    """(start, end) char ranges that are commented / disabled."""
    rs = []
    for m in re.finditer(r'/\*.*?\*/', text, re.S):
        rs.append((m.start(), m.end()))
    # #if 0 / #ifdef NON_MATCHING ... #else|#endif
    for m in re.finditer(r'^#\s*(if 0|ifdef NON_MATCHING|if defined\(NON_MATCHING\)|ifdef NONMATCHING)\b.*?^#\s*(else|endif)', text, re.S | re.M):
        rs.append((m.start(), m.end()))
    for m in re.finditer(r'(?:^//.*\n)+', text, re.M):
        rs.append((m.start(), m.end()))
    return rs

for path in sorted(glob.glob(SRC + '/*.c')):
    base = os.path.basename(path)
    text = open(path).read()
    asmf = [os.path.basename(p)[:-2] for p in pragma.findall(text)]
    names = asmf + re.findall(r'^[A-Za-z_][\w \*]*\b(func_\w+)\s*\([^;]*$', text, re.M)
    addrs = [addr(n) for n in names if addr(n)]
    if not addrs:
        continue
    if base.startswith('init'):
        pass
    elif base.startswith('game'):
        if min(addrs) < 0x15190000:
            continue
    else:
        continue
    rs = regions(text)
    for f in asmf:
        if not f.startswith('func_'):
            continue
        for m in re.finditer(r'^(?://\s*)?[A-Za-z_][\w \*]*\b' + f + r'\s*\([^;{]*\)?\s*\{?\s*$', text, re.M):
            pos = m.start()
            if not any(a <= pos < b for a, b in rs):
                continue
            # brace-count from pos
            seg = text[pos:]
            lines = seg.split('\n')
            buf, depth, started = [], 0, False
            for ln in lines:
                l2 = re.sub(r'^//\s?', '', ln) if ln.startswith('//') else ln
                if '*/' in l2 and depth == 0 and started:
                    break
                buf.append(l2)
                depth += l2.count('{') - l2.count('}')
                if '{' in l2:
                    started = True
                if started and depth <= 0:
                    break
                if len(buf) > 600:
                    break
            if not started or depth > 0:
                continue
            open(os.path.join(out, f + '.c'), 'w').write('\n'.join(buf) + '\n')
            s = os.path.expanduser('~/conker/conker/asm/nonmatchings')
            n = 0
            for cand in glob.glob(f'{os.path.expanduser("~/conker/conker/asm")}/**/{f}.s', recursive=True):
                n = sum(1 for x in open(cand) if re.match(r'\s*/\*\s*[0-9A-F]+ ', x))
                break
            print(base, f, n)
            break
