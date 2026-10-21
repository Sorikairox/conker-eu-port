#!/usr/bin/env python3
"""Conversion priority list for the browser build: the asm stubs the game actually hits, plus the
asm functions that these stubs call (what will be hit next, once they are C).
usage: python3 port/tools/priority.py RUNLOG [N]   (RUNLOG = node_run.js / page output with [stubs])
  1. measured: the "[stubs]" ranking printed by port_dump_stubs (calls per run);
  2. next wave: asm-only callees (jal, 2 levels) of the measured stubs, scored by the parent's call
     count times the number of call sites, skipping functions already listed."""
import glob, os, re, sys, collections
sys.path.insert(0, os.path.dirname(__file__))
from gen_stubs import asm_only

log, N = sys.argv[1], int(sys.argv[2]) if len(sys.argv) > 2 else 50
asm = asm_only()
asmfile = {os.path.splitext(os.path.basename(p))[0]: p for p in glob.glob('conker/asm/nonmatchings/**/*.s', recursive=True)}
measured = []
for l in open(log, errors='replace'):
    m = re.match(r'\s*\d+\.\s+(\w+)\s+(\d+)\s+#\d+\s+f\d+\s+(\S+)', l)
    if m:
        measured.append((m[1], int(m[2]), m[3]))


def jals(f):
    return re.findall(r'\bjal\s+(\w+)', open(asmfile[f]).read()) if f in asmfile else []


listed = {f for f, _, _ in measured}
score, via = collections.Counter(), {}
for f, n, _ in measured:
    for c1, k1 in collections.Counter(jals(f)).items():
        if c1 in asm and c1 not in listed and not c1.startswith(('os', '__os')):
            score[c1] += n * k1; via.setdefault(c1, f)
        for c2, k2 in collections.Counter(jals(c1)).items() if c1 in asm else ():
            if c2 in asm and c2 not in listed and c2 != c1 and not c2.startswith(('os', '__os')):
                score[c2] += max(1, n * k1 * k2 // 4); via.setdefault(c2, c1)
print(f'# conversion priority (browser build): {len(measured)} measured stubs + next wave')
print(f'{"rank":>4} {"function":14s} {"score":>8}  {"kind":8s} source / via')
r = 0
for f, n, what in measured:
    r += 1
    print(f'{r:4d} {f:14s} {n:8d}  measured {what}')
for f, s in score.most_common(max(0, N - r)):
    r += 1
    print(f'{r:4d} {f:14s} {s:8d}  next     asm:{asm[f]} (called by {via[f]})')
