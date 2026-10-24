#!/usr/bin/env python3
# P211: every jal to the command runners func_1509BFB0 (EU 1509c3c0, table D_80088874) / func_1509BE40 (EU 1509c250,
# table D_80088838): the command word in a1 (when a constant) and whether the caller reads v0 after the call before
# writing it (straight line; at the first branch both the fall-through and the target are followed one level).
# usage: runner_sites.py eu.dis [table-nibble]
import re, sys
L = [l for l in open(sys.argv[1]) if re.match(r'^[0-9a-f]{8}:\t', l)]
idx = {}; ins = []
for i, l in enumerate(L):
    p = l.split('\t'); a = int(p[0][:-1], 16); ins.append((a, p[2].strip() if len(p) > 2 else '', p[3].strip() if len(p) > 3 else ''))
    idx[a] = i
def regs(s): return re.findall(r'\b(v0|v1|a[0-3]|t[0-9]|s[0-8]|at|ra|sp|zero|f0)\b', s)
def reads_v0(i, depth=0):
    j = i + 2   # after the delay slot
    while j < len(ins) and j < i + 40:
        op, ar = ins[j][1], ins[j][2]
        rr = regs(ar)
        if op in ('jr',) : return 'v0 returned' if True else None
        dst = rr[0] if rr else None
        srcs = rr[1:] if op not in ('sw','sb','sh','swc1','beq','bne','beqz','bnez','blez','bgtz','bltz','bgez','beql','bnel','beqzl','bnezl','bltzl','bgezl','blezl','bgtzl','jr','jalr','mtc1') else rr
        if 'v0' in srcs: return '%x %s %s' % (ins[j][0], op, ar)
        if op.startswith('b') or op in ('j',):
            # delay slot
            d = ins[j + 1]; dr = regs(d[2])
            if 'v0' in dr[1:] or (d[1].startswith('s') and 'v0' in dr): return '%x %s %s' % (d[0], d[1], d[2])
            if dr and dr[0] == 'v0' and not d[1].startswith('s'): return None
            if depth == 0:
                m = re.match(r'([0-9a-f]+)', ar.split(',')[-1].strip())
                if m and int(m.group(1), 16) in idx:
                    r = reads_v0(idx[int(m.group(1), 16)] - 2, 1)
                    if r: return r
            j += 2; continue
        if op in ('jal', 'jalr'): return None
        if dst == 'v0': return None
        j += 1
    return None
for i, (a, op, ar) in enumerate(ins):
    if op == 'jal' and ar.split()[0] in ('1509c3c0', '1509c250'):
        w = None
        for k in range(i + 1, max(i - 80, 0), -1):
            o2, a2 = ins[k][1], ins[k][2]
            if a2.startswith('a1,'):
                m = re.match(r'a1,(?:zero,)?(-?0x[0-9a-f]+|-?\d+)$', a2)
                w = a2 if not (o2 in ('li', 'ori', 'addiu') and m) else hex(int(m.group(1), 0) & 0xFFFF)
                break
        fn = None
        for k in range(i, 0, -1):
            pass
        print('%x %s word=%s v0read=%s' % (a, 'BFB0' if ar.startswith('1509c3c0') else 'BE40', w, reads_v0(i)))
