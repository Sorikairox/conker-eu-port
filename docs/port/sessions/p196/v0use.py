#!/usr/bin/env python3
# P182: for each FUNC, every asm `jal FUNC` site (asm/nonmatchings, by decoded jal target or name) and whether the
# caller reads v0 / f0 after the call before writing it (straight-line, follows the first branch target too).
# usage: v0use.py ASMDIR FUNC...
import os, re, sys
root = sys.argv[1]
INS = re.compile(r'/\*\s*[0-9A-F]+\s+([0-9A-F]+)\s+([0-9A-F]{8})\s*\*/\s+(\S+)\s*(.*)')
def load(path):
    out, labels = [], {}
    for l in open(path):
        m = re.match(r'\s*(\.L[0-9A-F_]+):', l)
        if m: labels[m.group(1)] = len(out); continue
        m = INS.search(l)
        if m: out.append((m.group(3), m.group(4).split('#')[0].strip()))
    return out, labels
def regs(ops): return [r.strip() for r in re.split(r',', ops)]
def scan(ins, labels, i, reg, depth=0):
    """reads/writes of reg from instruction i on"""
    k = i
    while k < len(ins) and k < i + 40:
        op, ops = ins[k]
        rs = regs(ops)
        srcs = ' '.join(rs[1:]) if rs else ''
        if op in ('sw', 'sh', 'sb', 'swc1', 'beq', 'bne', 'beql', 'bnel', 'mtc1') : srcs = ops
        if re.search(r'\$%s\b' % reg[1:], srcs) and not (op in ('jal',) ): return 'READ by %s %s' % (op, ops)
        if rs and rs[0] == reg and op not in ('sw', 'sh', 'sb', 'swc1', 'beq', 'bne', 'beql', 'bnel', 'bnez', 'beqz',
                                               'bltz', 'bgez', 'bgtz', 'blez', 'mtc1', 'jr'):
            return 'written (%s)' % op
        if op == 'jal': return 'next call'
        if op == 'jr':
            return 'RETURNED (jr)' if ops == '$ra' else 'jr'
        if op in ('b', 'j') or (op.startswith('b') and depth < 1 and op not in ('break',)):
            tgt = rs[-1]
            if tgt in labels:
                if op in ('b', 'j'):
                    r = scan(ins, labels, k + 1, reg, depth) if False else None
                    # delay slot first
                    d_op, d_ops = ins[k + 1]
                    dr = regs(d_ops)
                    if re.search(r'\$%s\b' % reg[1:], ' '.join(dr[1:])): return 'READ in delay'
                    if dr and dr[0] == reg: return 'written (delay)'
                    return scan(ins, labels, labels[tgt], reg, depth + 1)
                a = scan(ins, labels, labels[tgt], reg, depth + 1)
                if 'READ' in a or 'RETURNED' in a: return 'branch: ' + a
        k += 1
    return 'unknown'
names = sys.argv[2:]
for dp, dn, fn in os.walk(root):
    for f in fn:
        if not f.endswith('.s'): continue
        p = os.path.join(dp, f)
        txt = open(p).read()
        if not any(n in txt for n in names): continue
        ins, labels = load(p)
        for i, (op, ops) in enumerate(ins):
            if op == 'jal' and ops in names:
                print('%s <- %s: v0 %s | f0 %s' % (ops, os.path.relpath(p, root), scan(ins, labels, i + 2, '$v0'),
                                                    scan(ins, labels, i + 2, '$f0')))
