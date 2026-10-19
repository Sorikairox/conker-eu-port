#!/usr/bin/env python3
"""fieldinfer.py (s54): infer the layout/types of the main game object (struct127, 0x32C bytes, D_800CC2D0[26]) and which
function parameters are struct127 pointers, so that m2c (which sees only raw offsets for untyped `arg0`) can emit `arg0->unk1D4`.

usage: fieldinfer.py [--out DIR] [--hdr ORIGINAL_structs.h] [--patch-header]      (default DIR = conker/build_port/s54/fi)
  writes DIR/struct127.h   typed struct body (offset-named fields; fields referenced from C keep header name+type)
         DIR/params.json   {func: [argindex,...]}  parameters of asm functions that are struct127 * (call-graph fixpoint)
         DIR/fields.tsv    per offset: access histogram (lb/lbu/lh/lhu/lw/lwc1/ldc1/sb/sh/sw/swc1/sdc1) + deref count
         DIR/renames.tsv   old header field name -> new name (only unreferenced `pad*` fields that were re-typed)
  --report prints a compact summary.

Evidence
  * C: the existing header struct (structs.h `struct struct127`) and the names referenced as `->x` / `.x` anywhere in src_eu
    ("pinned": name+type are kept verbatim, the matched code compiles against them).
  * asm: every remaining function (conker/asm/nonmatchings/*/*.s). A small linear register tracker follows pointers to the
    object: parameters (from `struct127 *` prototypes in include/ and src_eu/, then a call-graph fixpoint both ways),
    D_800CC2D0 / D_800CC5A0 base + index, globals of type struct127 * (variables.h), loads from header fields typed
    `struct127 *`.  For each access it records offset, op (width / signedness / float via lwc1) and whether a word loaded from
    the field is later used as a base register (pointer).
Unpinned header fields keep their type when the asm evidence is compatible, otherwise they are re-typed by weighted interval
selection over the observed (offset, size, kind) accesses; unobserved unpinned `pad*` stay padding.
"""
import re, os, sys, glob, json, collections

ROOT = os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker'))
R = ROOT + '/conker'
SIZE = 0x32C
TYPES = {'s8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'f32': 4, 'f64': 8, 'void': 4}

# ------------------------------------------------------------------ header struct
def parse_struct(path=None):
    path = path or R + '/include/structs.h'
    txt = open(path).read()
    m = re.search(r'struct struct127 \{\n(.*?)\n\}; // size 0x32C', txt, re.S)
    if not m: m = re.search(r'struct struct127 \{\n(.*?)\n\};', txt, re.S)
    body = m.group(1)
    fields = []   # dict(off,size,type,name,text)
    off = 0; i = 0
    lines = body.split('\n')
    while i < len(lines):
        l = lines[i]; i += 1
        s = re.sub(r'/\*.*?\*/', '', l)
        s = re.sub(r'//.*', '', s).strip()
        if not s: continue
        if s.startswith('union'):
            txtl = [l]
            while True:
                n = lines[i]; i += 1; txtl.append(n)
                if re.match(r'\s*\}\s*\w+\s*;', n): break
            name = re.match(r'\s*\}\s*(\w+)', txtl[-1]).group(1)
            sz = 0
            for t in txtl[1:-1]:
                mm = re.match(r'\s*(\w+)\s+\w+(?:\[(\w+)\])?;', t)
                if mm: sz = max(sz, TYPES[mm.group(1)] * (int(mm.group(2), 0) if mm.group(2) else 1))
            al = 2 if sz >= 2 else 1
            off = (off + al - 1) // al * al
            fields.append(dict(off=off, size=sz, type='union', name=name, text='\n'.join(txtl)))
            off += sz; continue
        mm = re.match(r'(struct\s+\w+|\w+)\s*(\*+)?\s*(\w+)(?:\[(\w+)\])?;', s)
        if not mm: raise SystemExit('struct127 parse: ' + l)
        t, star, name, arr = mm.groups()
        if star: sz = 4; al = 4; ty = t + ' ' + star
        else:
            sz = TYPES[t]; al = sz; ty = t
        n = int(arr, 0) if arr else 1
        off = (off + al - 1) // al * al
        mo = re.search(r'/\*\s*0x([0-9A-Fa-f]+)\s*\*/', l)
        if mo and int(mo.group(1), 16) != off: raise SystemExit('struct127 offset mismatch %s at 0x%X (comment 0x%s)' % (name, off, mo.group(1)))
        fields.append(dict(off=off, size=sz * n, type=ty, name=name, text=l.rstrip(), arr=n if arr else 0, elem=sz))
        off += sz * n
    if off != SIZE: raise SystemExit('struct127 size 0x%X != 0x%X' % (off, SIZE))
    return fields

def c_names():
    names = set()
    for p in glob.glob(R + '/src_eu/**/*.c', recursive=True) + glob.glob(R + '/include/*.h'):
        t = open(p, errors='replace').read()
        t = re.sub(r'/\*.*?\*/', '', t, flags=re.S); t = re.sub(r'//[^\n]*', '', t)
        names |= set(re.findall(r'(?:->|\.)\s*(\w+)', t))
    return names

# ------------------------------------------------------------------ prototypes
PTR = {}   # func -> {'ret': 1, i: 1}  pointer-typed return / params in any C prototype
PROTO = re.compile(r'(?m)^[ \t]*((?:extern |static |const |volatile |unsigned )*(?:struct\s+)?\w+[ \t*]+?)(\*{0,2}\s*)(\w+)\s*\(([^;{)]*)\)\s*[;{]')
def protos():
    """-> (params {func: {i: 'o'|'pp'}}, rets {func: 'o'})"""
    params = {}; rets = {}
    PTR.clear()
    files = glob.glob(R + '/include/*.h') + glob.glob(R + '/src_eu/**/*.c', recursive=True)
    for p in files:
        t = open(p, errors='replace').read()
        t = re.sub(r'/\*.*?\*/', '', t, flags=re.S); t = re.sub(r'//[^\n]*', '', t)
        for m in PROTO.finditer(t):
            ret, star, fn, args = m.groups()
            if fn in ('if', 'while', 'for', 'switch', 'return', 'sizeof'): continue
            if 'struct127' in ret and star.strip() == '*': rets[fn] = 'o'
            ps = [a.strip() for a in args.split(',')]
            if '*' in ret + star: PTR.setdefault(fn, {})['ret'] = 1
            for i, a in enumerate(ps):
                if '*' in a: PTR.setdefault(fn, {})[i] = 1
            d = {}
            for i, a in enumerate(ps):
                if 'struct127' not in a: continue
                if re.search(r'struct127\s*\*\s*\*', a): d[i] = 'pp'
                elif re.search(r'struct127\s*\*', a): d[i] = 'o'
            if d: params.setdefault(fn, {}).update(d)
    return params, rets

def globals_obj():
    """struct127 *G (pointer globals) and struct127 G[] arrays"""
    ptr = set(); arr = set()
    for p in glob.glob(R + '/include/*.h'):
        for l in open(p, errors='replace'):
            m = re.match(r'extern\s+struct127\s*(\*?)\s*(\w+)(\[[^\]]*\])?\s*;', l)
            if m:
                if m.group(1): ptr.add(m.group(2))
                elif m.group(3): arr.add(m.group(2))
    return ptr, arr

# ------------------------------------------------------------------ asm tracker
LINE = re.compile(r'^\s*/\*\s*[0-9A-F]+ [0-9A-F]+ [0-9A-F]{8} \*/\s+(\w+)\s*(.*?)\s*$')
MEM = re.compile(r'^(.*)\((\$\w+)\)$')
LOADS = {'lb': 1, 'lbu': 1, 'lh': 2, 'lhu': 2, 'lw': 4, 'lwc1': 4, 'ldc1': 8, 'lwl': 4, 'lwr': 4, 'ld': 8}
STORES = {'sb': 1, 'sh': 2, 'sw': 4, 'swc1': 4, 'sdc1': 8, 'swl': 4, 'swr': 4, 'sd': 8}
NODEST = set(STORES) | {'beq', 'bne', 'beqz', 'bnez', 'blez', 'bgtz', 'bltz', 'bgez', 'beql', 'bnel', 'beqzl', 'bnezl', 'blezl', 'bgtzl', 'bltzl', 'bgezl',
                       'b', 'j', 'jr', 'jal', 'jalr', 'mtc1', 'dmtc1', 'ctc1', 'mult', 'multu', 'div', 'divu', 'nop', 'break', 'sync', 'bc1t', 'bc1f', 'bc1tl', 'bc1fl',
                       'bgezal', 'bltzal', 'mthi', 'mtlo', 'teq', 'cache', 'c.lt.s', 'c.le.s', 'c.eq.s', 'c.lt.d', 'c.le.d', 'c.eq.d', 'dmult', 'dmultu', 'ddiv', 'ddivu'}
TEMPS = ['$at', '$v0', '$v1', '$a0', '$a1', '$a2', '$a3', '$t0', '$t1', '$t2', '$t3', '$t4', '$t5', '$t6', '$t7', '$t8', '$t9']
AREG = ['$a0', '$a1', '$a2', '$a3']
OBJ_SYMS_DEFAULT = {'D_800CC2D0', 'D_800CC5A0'}

def num(s):
    s = s.strip()
    try: return int(s, 0)
    except ValueError: return None

def load_funcs():
    fs = {}
    for p in sorted(glob.glob(R + '/asm/nonmatchings/*/*.s')):
        f = os.path.basename(p)[:-2]
        ins = []
        for l in open(p):
            m = LINE.match(l)
            if m: ins.append((m.group(1), m.group(2)))
        fs[f] = ins
    return fs

def liveargs(ins):
    """indices of $a0-$a3 read before any write in linear order (approximate arity of an asm function)"""
    written = set(); live = set()
    for op, ops in ins:
        a = [x.strip() for x in ops.split(',')] if ops else []
        if op in ('jal', 'jalr', 'jr'):
            if op == 'jalr' and a: live |= {i for i, r in enumerate(AREG) if r in a[-1:] and r not in written}
            continue
        dest = a[0] if a and op not in NODEST and not op.startswith('b') and op not in LOADS or (a and op in LOADS) else None
        srcs = a[1:] if dest else a
        for t in srcs:
            for r in re.findall(r'\$a[0-3]', t):
                if r not in written: live.add(AREG.index(r))
        if dest and re.fullmatch(r'\$a[0-3]', dest): written.add(dest)
    return live

class Ev:
    def __init__(self):
        self.acc = collections.defaultdict(collections.Counter)   # off -> op counter
        self.deref = collections.Counter()                         # off -> times loaded word used as base
        self.loads = collections.Counter()                         # off -> lw count
        self.fnoff = collections.defaultdict(set); self.cur = None
        self.ptr = collections.Counter()                           # off -> word field passed as pointer arg / assigned a pointer return

def analyze(fn, ins, objp, protos_p, rets, gptr, garr, objfields, ev=None):
    """-> (set of param indices found to be obj by callee hints (backward), list of (callee, argidx, state))"""
    st = {}
    for i, r in enumerate(AREG): st[r] = ('a', i)
    for i, k in objp.items():
        if i < 4: st[AREG[i]] = ('o', 0) if k == 'o' else ('pp', 0)
    back = set(); calls = []
    fresh = set()   # a-regs written since entry / the last call
    def mark(op, ops):
        a = [x.strip() for x in ops.split(',')] if ops else []
        if a and (op in LOADS or (op not in NODEST and not op.startswith('b'))): fresh.add(a[0])
    def getst(r): return st.get(r)
    n = len(ins); k = 0
    while k < n:
        op, ops = ins[k]; k += 1
        a = [x.strip() for x in ops.split(',')] if ops else []
        if op in ('jal', 'jalr'):
            callee = a[0] if op == 'jal' else None
            # delay slot executes before the call
            if k < n:
                dop, dops = ins[k]; k += 1
                step(st, dop, dops, ev, objfields, gptr, garr); mark(dop, dops)
            if callee:
                for i, r in enumerate(AREG):
                    s = st.get(r)
                    if s and s[0] == 'o' and s[1] == 0 and r in fresh: calls.append((callee, i, 'o'))
                    elif s and s[0] == 'a': calls.append((callee, i, ('a', s[1])))
                    if ev is not None and s and s[0] == 'p' and r in fresh and PTR.get(callee, {}).get(i): ev.ptr[s[1]] += 1
                    elif s and s[0] == 'pp': calls.append((callee, i, 'pp'))
            for r in TEMPS: st.pop(r, None)
            fresh.clear()
            if callee and rets.get(callee) == 'o': st['$v0'] = ('o', 0)
            elif callee and PTR.get(callee, {}).get('ret'): st['$v0'] = ('r', 0)
            continue
        step(st, op, ops, ev, objfields, gptr, garr); mark(op, ops)
    return calls

OBJSYM = None
def step(st, op, ops, ev, objfields, gptr, garr):
    a = [x.strip() for x in ops.split(',')] if ops else []
    if op in LOADS or op in STORES:
        mm = MEM.match(a[1]) if len(a) > 1 else None
        if not mm: return
        offs, base = mm.group(1), mm.group(2)
        bs = st.get(base)
        rt = a[0]
        if bs and bs[0] == 'hi':
            sym = bs[1]
            lo = re.match(r'%lo\((\w+)\)', offs)
            if lo and lo.group(1) in gptr and op == 'lw': st[rt] = ('o', 0)
            elif lo and lo.group(1) in garr and ev is not None:
                pass
            elif op in LOADS: st.pop(rt, None)
            return
        if bs and bs[0] == 'hisum':
            sym = bs[1]
            lo = re.match(r'%lo\((\w+)\)', offs)
            if lo and lo.group(1) in garr:
                # array element base + scaled index: offset = low part within the element (unknown) -> not recorded
                pass
            if op in LOADS: st.pop(rt, None)
            return
        o = num(offs)
        if bs and bs[0] == 'o' and o is not None:
            tot = bs[1] + o
            if 0 <= tot < SIZE and ev is not None:
                ev.fnoff[ev.cur].add(tot)
                if op == 'sw' and (st.get(rt) or ('',))[0] in ('r', 'o'): ev.ptr[tot] += 1
                ev.acc[tot][op] += 1
                if op == 'lw': ev.loads[tot] += 1
            if op in LOADS:
                if op == 'lw' and tot in objfields: st[rt] = ('o', 0)
                elif op == 'lw': st[rt] = ('p', tot)
                else: st.pop(rt, None)
            return
        if bs and bs[0] == 'p':
            if ev is not None: ev.deref[bs[1]] += 1
            if op in LOADS: st.pop(rt, None)
            return
        if bs and bs[0] == 'pp' and op == 'lw' and o == 0:
            st[rt] = ('o', 0); return
        if op in LOADS: st.pop(rt, None)
        return
    if op in ('beq', 'bne', 'beqz', 'bnez', 'nop', 'b', 'j', 'jr') or op.startswith('b') and op not in ('break',):
        return
    if not a: return
    d = a[0]
    if op in NODEST: return
    if op == 'lui':
        m = re.match(r'%hi\((\w+)\)', a[1])
        if m and (m.group(1) in OBJ_SYMS or m.group(1) in gptr): st[d] = ('hi', m.group(1))
        else: st.pop(d, None)
        return
    if op in ('addiu', 'addi', 'daddiu') and len(a) == 3:
        s = st.get(a[1]); imm = a[2]
        if s and s[0] == 'hi':
            m = re.match(r'%lo\((\w+)\)', imm)
            if m and m.group(1) in OBJ_SYMS and m.group(1) == s[1]: st[d] = ('o', 0)
            else: st.pop(d, None)
            return
        if s and s[0] == 'o':
            v = num(imm)
            if v is not None: st[d] = ('o', s[1] + v); return
        st.pop(d, None)
        if s and s[0] == 'a' and num(imm) is not None: pass
        return
    if op in ('addu', 'daddu', 'add') and len(a) == 3:
        s1, s2 = st.get(a[1]), st.get(a[2])
        for x, y in ((s1, s2), (s2, s1)):
            if x and x[0] == 'o' and not (y and y[0] in ('hi', 'p')):
                st[d] = ('o', x[1]); return
            if x and x[0] == 'hi':
                st[d] = ('hisum', x[1]); return
        # move via zero
        if a[2] == '$zero' and s1: st[d] = s1; return
        if a[1] == '$zero' and s2: st[d] = s2; return
        st.pop(d, None); return
    if op == 'or' and len(a) == 3:
        if a[2] == '$zero' and a[1] in st: st[d] = st[a[1]]; return
        if a[1] == '$zero' and a[2] in st: st[d] = st[a[2]]; return
        st.pop(d, None); return
    if op in ('mfc1', 'mov.s', 'mov.d') and False: return
    st.pop(d, None)

OBJ_SYMS = set(OBJ_SYMS_DEFAULT)

def run(verbose=False, hdrpath=None):
    global OBJ_SYMS
    hdr = parse_struct(hdrpath)
    gptr, garr = globals_obj()
    OBJ_SYMS = set(OBJ_SYMS_DEFAULT) | garr
    pparams, rets = protos()
    fs = load_funcs()
    objfields = {f['off'] for f in hdr if re.match(r'struct127\s*\*$', f['type'])}
    objp = {fn: dict(d) for fn, d in pparams.items() if fn in fs}
    LIVE = {fn: liveargs(ins) for fn, ins in fs.items()}
    # call-graph fixpoint
    for it in range(8):
        changed = False
        for fn, ins in fs.items():
            cur = objp.setdefault(fn, {})
            calls = analyze(fn, ins, cur, pparams, rets, gptr, garr, objfields)
            for callee, i, s in calls:
                if s == 'o' and callee in fs and i in LIVE[callee]:
                    d = objp.setdefault(callee, {})
                    if i not in d: d[i] = 'o'; changed = True
                elif isinstance(s, tuple) and s[0] == 'a':
                    ck = pparams.get(callee, {}).get(i) or objp.get(callee, {}).get(i)
                    if ck == 'o' and s[1] not in cur: cur[s[1]] = 'o'; changed = True
        if not changed: break
    ev = Ev(); ev.per = {}
    for fn, ins in fs.items():
        n0 = sum(sum(c.values()) for c in ev.acc.values()); ev.cur = fn
        analyze(fn, ins, objp.get(fn, {}), pparams, rets, gptr, garr, objfields, ev)
        ev.per[fn] = (sum(sum(c.values()) for c in ev.acc.values()) - n0, len(ins))
    # support filter: a hint only counts when the function itself touches the object at >= 3 distinct offsets
    # (drops memcpy-like helpers and pure pass-through wrappers)
    objp = {fn: d for fn, d in objp.items() if fn not in fs or len(ev.fnoff.get(fn, ())) >= 3}
    return hdr, ev, objp, pparams, fs

# ------------------------------------------------------------------ prototype retyping
RETYPE = re.compile(r'^(?:(?:u8|s8|void|u16|s16)\s*\*|(?:s32|u32))\s*(\w*)$')
def retype_protos(objp, apply=False):
    """rewrite C prototypes (headers + src_eu) of asm functions whose hinted params are `u8 *`/`s32`/... to `struct127 *`.
    Only lines of the form `ret f(params);` (declarations) and GLOBAL_ASM functions' file-local protos.  -> list of (file, old, new)"""
    out = []
    for path in glob.glob(R + '/include/*.h') + glob.glob(R + '/src_eu/**/*.c', recursive=True):
        t = open(path, errors='replace').read(); new = t; ch = False
        for m in PROTO.finditer(t):
            ret, star, fn, args = m.groups()
            if fn not in objp or not t[m.end() - 1] == ';': continue
            ps = [a.strip() for a in args.split(',')]; nps = list(ps); mod = False
            for i, k in objp[fn].items():
                if k != 'o' or i >= len(ps): continue
                mm = RETYPE.match(ps[i])
                if mm: nps[i] = 'struct127 *' + mm.group(1); mod = True
            if mod:
                old = m.group(0); nw = old.replace('(' + args + ')', '(' + ', '.join(nps) + ')')
                out.append((os.path.relpath(path, R), old.strip(), nw.strip())); new = new.replace(old, nw, 1); ch = True
        if ch and apply: open(path, 'w').write(new)
    return out

# ------------------------------------------------------------------ type selection
def cand_types(off, cnt, deref, loads, ptr):
    """-> list of (size, ctype, weight) candidates for one start offset"""
    c = []
    g = lambda *ops: sum(cnt.get(o, 0) for o in ops)
    for sz, sg, un in ((1, 's8', 'u8'),):
        a = g('lb'); b = g('lbu'); st = g('sb')
        if a + b + st: c.append((1, 's8' if a > b else 'u8', a + b + st))
    a = g('lh'); b = g('lhu'); st = g('sh')
    if a + b + st: c.append((2, 's16' if a > b else 'u16', a + b + st))
    fw = g('lwc1', 'swc1'); iw = g('lw', 'swl', 'swr') + g('sw')
    if fw + iw:
        if fw > iw: c.append((4, 'f32', fw + iw))
        else:
            if (loads.get(off, 0) >= 2 and deref.get(off, 0) * 2 >= loads.get(off, 0)) or ptr.get(off, 0) >= max(2, iw // 3): c.append((4, 'u8 *', fw + iw))
            else: c.append((4, 's32', fw + iw))
    d = g('ldc1', 'sdc1', 'ld', 'sd')
    if d: c.append((8, 'f64', d))
    return c

def build(hdr, ev, cnames):
    # 1. pinned header fields
    cells = []   # (off, size, ctype, name, text, pinned)
    pinned = []
    for f in hdr:
        names = {f['name']}
        if f['type'] == 'union' or f['name'] in cnames:
            pass
        isp = f['name'] in cnames
        pinned.append(isp)
    chosen = []   # final fields
    covered = [None] * SIZE
    for f, p in zip(hdr, pinned):
        if p:
            chosen.append(dict(f, how='pin'))
            for i in range(f['off'], f['off'] + f['size']): covered[i] = 1
    # 2. unpinned header fields compatible with evidence are kept; evidence elsewhere is typed
    # free intervals between pinned
    renames = {}
    def free_runs():
        runs = []; i = 0
        while i < SIZE:
            if covered[i]: i += 1; continue
            j = i
            while j < SIZE and not covered[j]: j += 1
            runs.append((i, j)); i = j
        return runs
    hmap = {f['off']: f for f, p in zip(hdr, pinned) if not p}
    for (lo, hi) in free_runs():
        # candidates in this run
        cands = []   # (off, size, type, weight)
        for off in range(lo, hi):
            cnt = ev.acc.get(off)
            if not cnt: continue
            for sz, ty, w in cand_types(off, cnt, ev.deref, ev.loads, ev.ptr):
                if off + sz <= hi and off % sz == 0: cands.append((off, sz, ty, w))
        # header (unpinned) fields as soft candidates with small weight when no evidence conflicts
        best = {lo: (0, [])}
        # weighted interval scheduling by DP over positions
        cb = collections.defaultdict(list)
        for c in cands: cb[c[0]].append(c)
        dp = [None] * (hi - lo + 1); dp[0] = (0, [])
        for i in range(hi - lo):
            pos = lo + i
            if dp[i] is not None and (dp[i + 1] is None or dp[i][0] > dp[i + 1][0]): dp[i + 1] = dp[i]
            for (off, sz, ty, w) in cb.get(pos, []):
                j = i + sz
                v = dp[i][0] + w
                if dp[j] is None or v > dp[j][0]: dp[j] = (v, dp[i][1] + [(off, sz, ty)])
        sel = dp[hi - lo][1] if dp[hi - lo] else []
        # keep unobserved/compatible header fields in the gaps
        taken = [None] * SIZE
        for off, sz, ty in sel:
            for q in range(off, off + sz): taken[q] = 1
        out = [dict(off=o, size=s, type=t, name=None, how='inf') for o, s, t in sel]
        for off, f in sorted(hmap.items()):
            if lo <= off and off + f['size'] <= hi and not any(taken[q] for q in range(off, off + f['size'])):
                pad = f['name'].startswith('pad') or re.match(r'u8$', f['type']) is None and False
                out.append(dict(f, how='hdr'))
                for q in range(off, off + f['size']): taken[q] = 1
        # exact-match inferred vs header field of same off/size/type -> reuse header (name/comment)
        # remaining gaps -> padding
        i = lo
        while i < hi:
            if taken[i]: i += 1; continue
            j = i
            while j < hi and not taken[j]: j += 1
            out.append(dict(off=i, size=j - i, type='pad', name=None, how='gap'))
            i = j
        chosen.extend(out)
    chosen.sort(key=lambda f: f['off'])
    # 3. naming/emit
    lines = []; off = 0
    ren = {}
    for f in chosen:
        if f['off'] != off: raise SystemExit('gap/overlap at 0x%X (have 0x%X) %s' % (off, f['off'], f))
        o = f['off']; sz = f['size']
        if f['how'] == 'pin' or f['how'] == 'hdr' and not f['name'].startswith('pad'):
            lines.append(f['text']);
            if f['how'] == 'hdr' and f['name'].startswith('pad'): pass
        elif f['how'] == 'hdr':
            # unobserved pad: keep
            lines.append(f['text'])
        elif f['type'] == 'pad':
            lines.append('    u8  pad%X[0x%X];' % (o, sz) if sz > 1 else '    u8  pad%X;' % o)
        else:
            t = f['type']
            lines.append(('    u8 *unk%X;' % o) if t == 'u8 *' else ('    %-3s unk%X;' % (t, o)))
        off += sz
    # drop old names of header fields that were replaced (renames)
    newnames = set()
    for f in chosen:
        if f['how'] in ('pin', 'hdr'): newnames.add(f['name'])
    for f, p in zip(hdr, pinned):
        if not p and f['name'] not in newnames: ren[f['name']] = None
    return chosen, lines, ren

def main():
    args = sys.argv[1:]
    out = R + '/build_port/s54/fi'
    if '--out' in args: out = args[args.index('--out') + 1]
    os.makedirs(out, exist_ok=True)
    hp = args[args.index('--hdr') + 1] if '--hdr' in args else None   # header to take the ORIGINAL struct127 from
    if hp is None:   # default: the pre-s54 header (names are offset-based across structs, so the tool is not idempotent on its own output)
        hp = R + '/build_port/s54/structs.h.orig'
        if not os.path.exists(hp):
            import subprocess
            os.makedirs(os.path.dirname(hp), exist_ok=True)
            open(hp, 'w').write(subprocess.run(['git', '-C', ROOT, 'show', '4bb1b44:conker/include/structs.h'], capture_output=True, text=True).stdout)
    hdr, ev, objp, pparams, fs = run(hdrpath=hp)
    cn = c_names()
    chosen, lines, ren = build(hdr, ev, cn)
    open(out + '/struct127.h', 'w').write('\n'.join(lines) + '\n')
    json.dump({fn: sorted(d) for fn, d in objp.items() if d and fn in fs}, open(out + '/params.json', 'w'), indent=0, sort_keys=True)
    with open(out + '/funcs.tsv', 'w') as w:   # func  object-accesses  insns  obj-params
        for fn, (na, ni) in sorted(ev.per.items()): w.write('%s\t%d\t%d\t%s\n' % (fn, na, ni, ','.join(map(str, sorted(objp.get(fn, {}))))))
    with open(out + '/fields.tsv', 'w') as w:
        for off in sorted(ev.acc):
            w.write('0x%X\t%s\tderef=%d\n' % (off, ' '.join('%s:%d' % kv for kv in sorted(ev.acc[off].items())), ev.deref.get(off, 0)))
    if '--protos' in args or '--apply-protos' in args:
        res = retype_protos(objp, apply='--apply-protos' in args)
        with open(out + '/protos.tsv', 'w') as w:
            for f, o, n in res: w.write('%s\t%s\t%s\n' % (f, o, n))
        print('retyped %d prototype lines%s' % (len(res), '' if '--apply-protos' in args else ' (dry run, see protos.tsv)'))
    if '--patch-header' in args:
        hp = R + '/include/structs.h'
        t = open(hp).read()
        m = re.search(r'(struct struct127 \{\n)(.*?)(\n\}; // size 0x32C)', t, re.S)
        open(hp, 'w').write(t[:m.start(2)] + '\n'.join(lines) + t[m.end(2):])
        print('patched', hp)
    if '--report' in args or True:
        how = collections.Counter(f['how'] for f in chosen)
        tys = collections.Counter(f['type'] for f in chosen if f['how'] == 'inf')
        nh = sum(1 for f in chosen if f['how'] == 'inf')
        print('fields: %d (pinned %d, header-kept %d, inferred %d, gap pads %d)' % (len(chosen), how['pin'], how['hdr'], how['inf'], how['gap']))
        print('inferred types:', dict(tys))
        print('asm funcs %d; with obj params %d; total obj params %d; accesses %d offsets, %d total' % (
            len(fs), sum(1 for d in objp.values() if d), sum(len(d) for fn, d in objp.items() if fn in fs),
            len(ev.acc), sum(sum(c.values()) for c in ev.acc.values())))

if __name__ == '__main__':
    main()
