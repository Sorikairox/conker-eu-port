#!/usr/bin/env python3
"""Rebuild docs/progress/history.tsv: one row per eu first-parent commit where the HANDOFF
"Current state" line (funcs / code bytes, from verify_all.sh) changed. Run from repo root;
merge_wt.sh runs it before committing a merge."""
import re, subprocess
def g(*a): return subprocess.run(["git",*a],capture_output=True,text=True).stdout
rows=[]
for line in g("log","--first-parent","--reverse","--format=%H|%ad|%s","--date=format:%Y-%m-%d %H:%M","eu").splitlines():
    h,d,s=line.split("|",2)
    hf=g("show",f"{h}:HANDOFF.md")
    m=re.search(r"\*\*(\d+) / (\d+) functions in C \(([\d.]+)%\)\*\*, code bytes ([\d,]+) / ([\d,]+) \(([\d.]+)%\)",hf)
    if not m: continue
    rows.append((d,h[:7],m.group(1),m.group(2),m.group(4).replace(",",""),m.group(6),s[:90]))
# keep only rows where the state changed
out=[];last=None
for r in rows:
    k=(r[2],r[4])
    if k!=last: out.append(r); last=k
print("date\tcommit\tfuncs\ttotal\tbytes\tbytes_pct\tsubject")
for r in out: print("\t".join(r))
