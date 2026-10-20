#!/usr/bin/env python3
"""calleefam.py: callee-family sweep list (s80).

For every callee that has at least one matched C caller (anywhere in src_eu),
list the GLOBAL_ASM callers in a slice with their sizes (insns), ranked by the
number of small unmatched callers.  Each family gets a hint: the call statement
in one matched C caller plus the declarations of the locals passed by address
(struct type / local layout).

usage: calleefam.py [--slice hi|lo|all] [--max N] [--top K] [--callee func_X]
  --slice hi : game files >= 0x130000 + init_* + libultra/** + debugger* (worktree a)
  --slice lo : game files < 0x130000
  --max N    : "small" = at most N insns (default 120)
  --top K    : families to print (default 25)
  --callee F : only this family (prints every caller)
  --typed    : only callees that a matched caller passes a stack local by address (argument blocks)
Reads $CONKER_ROOT (default ~/conker).
"""
import os, re, sys, glob, argparse

root = os.environ.get('CONKER_ROOT', os.path.expanduser('~/conker'))
cdir = os.path.join(root, 'conker')
ap = argparse.ArgumentParser()
ap.add_argument('--slice', default='hi')
ap.add_argument('--max', type=int, default=120)
ap.add_argument('--top', type=int, default=25)
ap.add_argument('--callee')
ap.add_argument('--typed', action='store_true', help='only callees a matched caller passes a stack local by address')
a = ap.parse_args()

def in_slice(rel):
    base = os.path.basename(rel)[:-2]
    if a.slice == 'all':
        return True
    special = base.startswith('init_') or rel.startswith('libultra/') or base.startswith('debugger')
    m = re.search(r'_([0-9A-F]{5,6})$', base)
    off = int(m.group(1), 16) if m else None
    if a.slice == 'hi':
        return special or (off is not None and off >= 0x130000 and base.startswith('game'))
    return (not special) and off is not None and off < 0x130000 and base.startswith('game')

GA = re.compile(r'#pragma GLOBAL_ASM\("([^"]+)"\)')
CALL = re.compile(r'\b(func_[0-9A-Fa-f_eu]+|[A-Za-z_]\w*)\s*\(')
KW = {'if', 'while', 'for', 'switch', 'return', 'sizeof', 'do'}

def strip_comments(s):
    s = re.sub(r'/\*.*?\*/', lambda m: '\n' * m.group(0).count('\n'), s, flags=re.S)
    return re.sub(r'//[^\n]*', '', s)

def c_functions(text):
    """yield (name, body) of top-level function definitions."""
    i, n, depth = 0, len(text), 0
    start = 0
    while i < n:
        ch = text[i]
        if ch == '{':
            if depth == 0:
                head = text[start:i]
                m = re.search(r'(\w+)\s*\([^;{}]*\)\s*$', head)
                bstart = i
            depth += 1
        elif ch == '}':
            depth -= 1
            if depth == 0:
                if m and m.group(1) not in KW:
                    yield m.group(1), text[bstart:i + 1]
                start = i + 1
        elif ch == ';' and depth == 0:
            start = i + 1
        i += 1

matched_callers = {}   # callee -> list of (file, caller, hint)
unmatched = []         # (rel, func, asmpath)
for path in sorted(glob.glob(os.path.join(cdir, 'src_eu', '**', '*.c'), recursive=True)):
    rel = os.path.relpath(path, os.path.join(cdir, 'src_eu'))
    raw = open(path, errors='replace').read()
    if in_slice(rel):
        for g in GA.findall(raw):
            unmatched.append((rel, os.path.basename(g)[:-2], os.path.join(cdir, g)))
    text = strip_comments(raw)
    text = re.sub(r'#[^\n]*', '', text)
    for fname, body in c_functions(text):
        for cm in CALL.finditer(body):
            callee = cm.group(1)
            if callee in KW or callee == fname:
                continue
            lst = matched_callers.setdefault(callee, [])
            if any(x[1] == fname for x in lst):
                continue
            # hint: call statement + decls of &locals
            ls = body.rfind('\n', 0, cm.start()) + 1
            le = body.find(';', cm.start())
            stmt = ' '.join(body[ls:le + 1].split())
            decls = []
            for v in re.findall(r'&(\w+)', stmt):
                d = re.search(r'\n\s*([\w ]+?[\s\*]+' + re.escape(v) + r'\s*(\[[^\]]*\])*)\s*;', body)
                if d and ' '.join(d.group(1).split()) not in decls:
                    decls.append(' '.join(d.group(1).split()))
            lst.append((rel, fname, stmt[:160], decls))

JAL = re.compile(r'\bjal\s+(\w+)')
fam = {}
for rel, f, ap_ in unmatched:
    try:
        lines = open(ap_).read().splitlines()
    except OSError:
        continue
    ninsn = sum(1 for l in lines if l.lstrip().startswith('/*'))
    for c in set(JAL.findall('\n'.join(lines))):
        if c in matched_callers:
            fam.setdefault(c, []).append((ninsn, f, rel))

def show(c, callers, allc):
    callers.sort()
    small = [x for x in callers if x[0] <= a.max]
    mc = matched_callers[c]
    print(f'{c}: {len(small)} small / {len(callers)} unmatched in slice, {len(mc)} matched C callers')
    for rel, fn, stmt, decls in mc[:2]:
        print(f'   hint {fn} ({rel}): {stmt}' + (f'   decl: {"; ".join(decls)}' if decls else ''))
    for n, f, rel in (callers if allc else small[:12]):
        print(f'   {n:4d} {f} {rel}')

if a.callee:
    show(a.callee, fam.get(a.callee, []), True)
    sys.exit()
if a.typed:
    fam = {c: v for c, v in fam.items() if c not in ('memcpy', 'bzero', 'memset') and any(
        any(not d.split()[-1].startswith('*') and '*' not in d for d in x[3]) for x in matched_callers[c])}
rank = sorted(fam.items(), key=lambda kv: (-sum(1 for x in kv[1] if x[0] <= a.max), kv[0]))
for c, callers in rank[:a.top]:
    if not any(x[0] <= a.max for x in callers):
        continue
    show(c, callers, False)
