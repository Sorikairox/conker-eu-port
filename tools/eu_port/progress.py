#!/usr/bin/env python3
"""Summarize conker/progress.csv: functions and bytes in C per section.
Usage (from conker/): progress.py [progress.csv]"""
import collections
import csv
import sys

path = sys.argv[1] if len(sys.argv) > 1 else "progress.csv"
rows = [r for r in csv.DictReader(open(path)) if r["length"] != "length"]
t = collections.defaultdict(lambda: [0, 0, 0, 0])
for r in rows:
    s, n, c = r["section"], int(r["length"]), r["language"] == "c"
    t[s][0] += 1
    t[s][1] += c
    t[s][2] += n
    t[s][3] += n * c
total = [sum(x) for x in zip(*t.values())]
for s, (n, nc, b, bc) in list(t.items()) + [("total", total)]:
    print(f"{s:9} funcs {nc:5}/{n:5} ({100 * nc / n:4.1f}%)  bytes {bc:7}/{b:7} ({100 * bc / b:4.1f}%)")
