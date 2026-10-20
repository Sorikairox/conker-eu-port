#!/usr/bin/env python3
# usage: blkvar.py draft.c outprefix  (s69, shape D)
# Writes outprefix_bN.c: one variant per if/else/loop body block with `s32 blk_t;` declared at its top
# (a declaration in the block = basic-block boundary -> unfilled `store; jr ra; nop`), plus _ball.c (all blocks).
# Prints the variant file names (feed them to m2c/tryall).
import sys, re
src = open(sys.argv[1]).read().split('\n'); out = sys.argv[2]
ctl = re.compile(r'^\s*(\}?\s*else\b|if\s*\(|else\s+if\b|while\s*\(|for\s*\(|do\b)')
spots = []
depth = 0
for i, l in enumerate(src):
    s = l.strip()
    if s.endswith('{') and depth > 0:
        if ctl.match(s) or (s == '{' and i > 0 and ctl.match(src[i-1].strip())):
            spots.append(i)
    depth += l.count('{') - l.count('}')
def emit(name, idx):
    o = []
    for i, l in enumerate(src):
        o.append(l)
        if i in idx: o.append('    s32 blk_t; // fakematch?: block-local declaration = basic-block boundary (s69)')
    open(name, 'w').write('\n'.join(o)); print(name)
for n, i in enumerate(spots): emit('%s_b%d.c' % (out, n), {i})
if len(spots) > 1: emit('%s_ball.c' % out, set(spots))
