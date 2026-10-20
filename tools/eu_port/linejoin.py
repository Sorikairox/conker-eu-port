#!/usr/bin/env python3
"""linejoin.py <draft.c> <outdir> [maxvariants=128] [func]

Same-line statement variants (s68 recipe 1, s70 sweep). With -g3 IDO keeps the source order of
statements on separate lines; statements joined onto one line form one scheduling unit and can
be reordered. For the target function body (named by `func`, else by the draft's file name
func_XXXXXXXX, else the last function in the file) this writes variants that join runs of
adjacent simple statements (assignments, compound assignments, ++/--; no declarations, control
flow, braces, `//` comments or multi-line statements) onto one line. Order, widest first:
all runs fully joined, each run fully joined alone, every single triple, every single pair,
then pair/triple tilings and combinations of two single joins, up to maxvariants.
Everything outside the joined lines stays byte-identical. Writes <outdir>/lj_NNN.c and
<outdir>/index.txt ("lj_NNN.c <description>"); prints the number of variants.
"""
import sys, os, re, itertools

TYPES = set('''s8 u8 s16 u16 s32 u32 s64 u64 f32 f64 int char short long float double void unsigned signed
const volatile static extern register struct union enum Gfx Mtx Vp OSTime'''.split())
CTRL = set('if else for while do switch case default return goto break continue'.split())
ASSIGN = re.compile(r'(?<![=!<>])(=|\+=|-=|\*=|/=|%=|&=|\|=|\^=|<<=|>>=)(?!=)|\+\+|--')

def is_simple(line):
    s = line.strip()
    if not s.endswith(';') or '//' in s or '/*' in s or '{' in s or '}' in s or s.startswith('#'):
        return False
    if s.count(';') != 1:
        return False
    w = re.match(r'[A-Za-z_]\w*', s)
    if w and (w.group(0) in CTRL or w.group(0) in TYPES):
        return False
    if re.match(r'[A-Za-z_]\w*\s+\**\s*[A-Za-z_]\w*\s*(=|;|\[|,)', s):   # "type name ..." declaration
        return False
    if re.match(r'\w+\s*:', s) and not re.match(r'\w+\s*::', s):           # label
        return False
    return bool(ASSIGN.search(s))

def find_body(lines, func):
    """index range (start, end) of the body lines (exclusive of the opening/closing brace lines)."""
    defn = None
    for i, l in enumerate(lines):
        if re.match(r'^[A-Za-z_].*\b%s\s*\(' % re.escape(func), l) and not l.rstrip().endswith(';'):
            defn = i
    if defn is None:
        return None
    depth = 0; start = None
    for i in range(defn, len(lines)):
        for ch in lines[i]:
            if ch == '{':
                depth += 1
                if start is None: start = i + 1
            elif ch == '}':
                depth -= 1
                if start is not None and depth == 0:
                    return start, i
    return None

def runs_of(lines, a, b):
    runs = []; cur = []
    for i in range(a, b):
        if is_simple(lines[i]):
            cur.append(i)
        else:
            if len(cur) >= 2: runs.append(cur)
            cur = []
    if len(cur) >= 2: runs.append(cur)
    return runs

def render(lines, segs):
    """segs: list of (first, last) line index ranges to join (inclusive, non-overlapping)."""
    out = list(lines); drop = set()
    for f, l in segs:
        if f == 'S':   # split line l into one statement per line
            ind = re.match(r'\s*', lines[l]).group(0)
            out[l] = ''.join(ind + x.strip() + ';\n' for x in lines[l].strip().split(';')[:-1])
            continue
        ind = re.match(r'\s*', lines[f]).group(0)
        out[f] = ind + ' '.join(lines[k].strip() for k in range(f, l + 1)) + '\n'
        drop.update(range(f + 1, l + 1))
    return [x for k, x in enumerate(out) if k not in drop]

def tilings(run, w, off):
    segs = []; k = off
    while k + w <= len(run):
        segs.append((run[k], run[k + w - 1])); k += w
    return segs

def main():
    src, outd = sys.argv[1], sys.argv[2]
    cap = int(sys.argv[3]) if len(sys.argv) > 3 else 128
    lines = open(src).read().splitlines(True)
    func = sys.argv[4] if len(sys.argv) > 4 else None
    if not func:
        m = re.search(r'(func_[0-9A-Fa-f]{8})', os.path.basename(src))
        func = m.group(1) if m else None
    if not func:
        names = re.findall(r'^[A-Za-z_][^;\n]*\b(\w+)\s*\([^;]*$', ''.join(lines), re.M)
        func = names[-1] if names else None
    rng = find_body(lines, func) if func else None
    if not rng:
        print(0); return
    runs = runs_of(lines, *rng)
    cands = []   # (desc, segs)
    # lines that already hold several simple statements (permuter output): split variants first
    multi = []
    for i in range(*rng):
        parts = [x.strip() + ';' for x in lines[i].strip().split(';')[:-1]]
        if len(parts) > 1 and lines[i].strip().endswith(';') and all(is_simple(x) for x in parts):
            multi.append(i)
    if multi:
        cands.append(('split_all', [('S', i) for i in multi]))
        if len(multi) > 1: cands += [('split_L%d' % (i + 1), [('S', i)]) for i in multi]
    if runs:
        cands.append(('all_runs', [(r[0], r[-1]) for r in runs]))
        for r in runs:
            if len(r) > 3: cands.append(('run_L%d-%d' % (r[0] + 1, r[-1] + 1), [(r[0], r[-1])]))
    singles3 = [(r[k], r[k + 2]) for r in runs for k in range(len(r) - 2)]
    singles2 = [(r[k], r[k + 1]) for r in runs for k in range(len(r) - 1)]
    cands += [('tri_L%d' % (s[0] + 1), [s]) for s in singles3]
    cands += [('pair_L%d' % (s[0] + 1), [s]) for s in singles2]
    for w in (3, 2):
        for off in range(w):
            segs = [s for r in runs for s in tilings(r, w, off)]
            if len(segs) > 1: cands.append(('tile%d_off%d' % (w, off), segs))
    singles = singles3 + singles2
    for a, b in itertools.combinations(singles, 2):
        if a[1] < b[0] or b[1] < a[0]:
            cands.append(('pair2_L%d_L%d' % (a[0] + 1, b[0] + 1), sorted([a, b])))
        if len(cands) > cap * 4: break
    os.makedirs(outd, exist_ok=True)
    seen = set(); n = 0; idx = []
    base = ''.join(lines)
    for desc, segs in cands:
        txt = ''.join(render(lines, segs))
        if txt == base or txt in seen: continue
        seen.add(txt)
        name = 'lj_%03d.c' % n
        open(os.path.join(outd, name), 'w').write(txt)
        idx.append('%s %s' % (name, desc)); n += 1
        if n >= cap: break
    open(os.path.join(outd, 'index.txt'), 'w').write('\n'.join(idx) + '\n')
    print(n)

if __name__ == '__main__':
    main()
