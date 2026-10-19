#!/usr/bin/env python3
"""opshift.py <func.diff>  opcode-level alignment of ref vs mine from a repair_try .diff (shows inserts/deletes/replaces)."""
import difflib,sys
rows=[]
for l in open(sys.argv[1]):
    t=l.split()
    if not t: continue
    if t[0]=='**': t=t[1:]
    if len(t)<3 or len(t[0])!=8: continue
    rows.append((t[0],t[1],' '.join(t[2:])))
ref=[r[0] for r in rows]; mine=[r[1] for r in rows]; asm=[r[2] for r in rows]
op=lambda w:int(w,16)>>26
sm=difflib.SequenceMatcher(None,[op(x) for x in ref],[op(x) for x in mine],autojunk=False)
for tag,i1,i2,j1,j2 in sm.get_opcodes():
    if tag!='equal': print(tag,i1,i2,j1,j2,asm[i1:i2][:6],[hex(int(m,16))[2:] for m in mine[j1:j2]][:6])
