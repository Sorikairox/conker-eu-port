#!/usr/bin/env python3
"""Resolve git conflict blocks by keeping both sides (ours, then theirs), dropping exact
duplicate lines that theirs repeats from ours. Meant for append-only files that parallel
sessions both extend: repair_log.tsv, undefined_syms.eu.txt, docs/IDO_SHAPES.md, HANDOFF.md
(check HANDOFF's "Current state" by hand afterwards).

Usage (repo root, during a conflicted merge): merge_union.py FILE...
"""
import re
import sys

BLOCK = re.compile(r"^<<<<<<< [^\n]*\n(.*?)^=======\n(.*?)^>>>>>>> [^\n]*\n", re.M | re.S)


def resolve(text):
    def keep_both(m):
        ours, theirs = m.group(1), m.group(2)
        seen = set(ours.splitlines())
        extra = [l for l in theirs.splitlines() if l not in seen or not l.strip()]
        return ours + ("\n".join(extra) + "\n" if extra else "")
    return BLOCK.sub(keep_both, text)


for path in sys.argv[1:]:
    s = open(path).read()
    n = len(BLOCK.findall(s))
    open(path, "w").write(resolve(s))
    print(f"{path}: {n} block(s) resolved")
