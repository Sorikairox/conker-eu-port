#!/usr/bin/env python3
"""cfix.py: draft rewrites used by convert.py (session P2).  Each fix_* takes (code, err_or_why, func, src)
and returns the rewritten code or None.  The rewrites are deliberately mechanical: difftest decides.

  fix_spframe   m2c stack locals -> one frame struct `struct {...} sp;` (fields sp.uXX at their frame
                offsets, explicit pads, tail pad up to the lowest register save slot).  Declares the
                'spXX undefined' locals, sizes 'missing size for array' ones, and removes lint:stackaddr
                (an &spXX scalar whose neighbours a callee may read).
  fix_u8arith   typed pointer +/- integer that m2c wrote as a byte offset (`s32 *p; p + 0xC`,
                `(arg0 * 2) + &D_x`, `p += 0xC`) -> `((T *)((u8 *)p + 0xC))`.
  fix_cmp       'Unacceptable operand of == or !=' -> both operands cast to (s32).
  fix_deref     'Dereferenced a non-pointer' -> `*(s32 *)(...)` on the error line.
  fix_rostr     `""` that m2c printed for a rodata symbol it took for an empty string -> the real D_
                symbol (the %lo symbols of the asm missing from the draft, float-constant loads excluded).
  fix_passthru  DIFFER 'call #k X: aN ref=.. cand=..' -> the argument the asm actually passes in aN:
                no write before the jal = caller's argN (pass-through); `lw aN, off(sp)` with
                off >= frame = the caller's stack arg (off-frame)/4; `addiu aN, sp, off` = &spOFF;
                `lw aN, off(sp)` below the frame = the local spOFF.  Inserted (m2c dropped it) or
                replaced (m2c passed something else), the callee's draft prototype widened.
"""
import sys as _pgs, os as _pgo; _pgs.path.insert(0, _pgo.path.dirname(_pgo.path.abspath(__file__))); import portguard  # wrong-checkout guard (P7)
import re, os, glob

ROOT = '/conker' if os.path.exists('/.dockerenv') else os.path.expanduser(os.environ.get('CONKER_ROOT', '~/conker'))
TSZ = {'s8': 1, 'u8': 1, 's16': 2, 'u16': 2, 's32': 4, 'u32': 4, 'f32': 4, 'f64': 8, 's64': 8, 'u64': 8,
       'char': 1, 'short': 2, 'int': 4, 'float': 4, 'double': 8}
_ASM = {}


# ------------------------------------------------------------------ asm
def asm_path(func):
    ps = glob.glob(os.path.join(ROOT, 'conker/asm/nonmatchings/**/%s.s' % func), recursive=True)
    return ps[0] if ps else None

class Asm:
    def __init__(self, func):
        self.ins = []; self.frame = 0; self.saves = []
        p = asm_path(func)
        if not p: return
        for l in open(p):
            if re.match(r'\s*\.L\w+:', l): self.ins.append(('LABEL', [])); continue
            m = re.match(r'\s*/\*\s*\w+\s+[0-9A-F]+\s+[0-9A-F]+\s*\*/\s+(\S+)\s*(.*)$', l)
            if not m: continue
            ops = [o.strip() for o in m.group(2).split(',')] if m.group(2).strip() else []
            self.ins.append((m.group(1), ops))
        for mn, ops in self.ins[:40]:
            if mn == 'addiu' and ops[:2] == ['$sp', '$sp'] and ops[2].startswith('-'): self.frame = int(ops[2][1:], 16)
            if mn in ('sw', 'sdc1', 'swc1') and len(ops) == 2 and re.match(r'\$(ra|s\d|fp|f2\d|f3\d)$', ops[0]):
                o = spoff(ops[1])
                if o is not None: self.saves.append(o)
        self.lowest_save = min(self.saves) if self.saves else self.frame

    def call_sites(self, callee):
        out = []
        for i, (mn, ops) in enumerate(self.ins):
            if mn == 'jal' and ops and (ops[0] == callee or ops[0].lower() == callee.lower()
                                        or ('0x' + callee[5:]).lower() == ops[0].lower()):
                out.append(i)
        return out

    def arg_source(self, site, n):
        """what the call at ins index `site` passes in a<n>: ('pass',) / ('stkarg', k) / ('addr', off) /
        ('local', off) / ('other',)"""
        reg = '$a%d' % n
        j = site + 1
        while j >= 0:
            if j < len(self.ins):
                mn, ops = self.ins[j]
                if mn == 'LABEL' or (j < site and (mn.startswith('b') or mn in ('j', 'jal', 'jr', 'jalr'))): break
                if ops and ops[0] == reg and mn not in ('sw', 'sh', 'sb', 'swc1', 'sdc1') and not mn.startswith('b'):
                    if mn == 'addiu' and len(ops) == 3 and ops[1] == '$sp': return ('addr', int(ops[2], 16))
                    if mn == 'lw' and spoff(ops[1]) is not None:
                        o = spoff(ops[1])
                        return ('stkarg', (o - self.frame) // 4) if self.frame and o >= self.frame else ('local', o)
                    return ('other',)
            j -= 1
            if site - j > 40: break
        return ('pass',)

    def lo_syms(self, skip_float=True):
        out = []
        for mn, ops in self.ins:
            for o in ops:
                for s in re.findall(r'%lo\((\w+)\)', o):
                    if skip_float and mn in ('lwc1', 'ldc1'): continue
                    if s not in out: out.append(s)
        flt = {s for mn, ops in self.ins if mn in ('lwc1', 'ldc1') for o in ops for s in re.findall(r'%lo\((\w+)\)', o)}
        return [s for s in out if s not in flt] if skip_float else out

def spoff(op):
    m = re.match(r'(-?0x[0-9A-Fa-f]+|\d+)\(\$sp\)$', op)
    return int(m.group(1), 16 if 'x' in m.group(1) else 10) if m else None

def asm(func):
    if func not in _ASM: _ASM[func] = Asm(func)
    return _ASM[func]


# ------------------------------------------------------------------ expression scanning
OPEN, CLOSE = '([{', ')]}'
ADD_STOPS = ['+', '-', '<<', '>>', '<', '>', '<=', '>=', '==', '!=', '&', '^', '|', '&&', '||', '=', '+=', '-=', '|=', '&=']
CMP_STOPS = ['==', '!=', '&', '^', '|', '&&', '||', '=', '+=', '-=', '|=', '&=']

def _stop_at(s, j, stops, fwd):
    for op in sorted(stops, key=len, reverse=True):
        t = ' ' + op + ' '
        if fwd and s.startswith(t, j): return True
        if not fwd and s.endswith(t, 0, j + 1): return True
    return False

def scan_right(s, i, stops):
    d = 0; j = i
    while j < len(s):
        c = s[j]
        if d == 0 and (c in ',;?:\n' or c in CLOSE or _stop_at(s, j, stops, True)): break
        if c in OPEN: d += 1
        elif c in CLOSE: d -= 1
        j += 1
    while j > i and s[j - 1] == ' ': j -= 1
    return j

def scan_left(s, i, stops):
    """i = exclusive end; returns the start index"""
    d = 0; j = i - 1
    while j >= 0:
        c = s[j]
        if d == 0 and (c in ',;?:\n{' or c in OPEN or _stop_at(s, j, stops, False)): break
        if c in CLOSE: d += 1
        elif c in OPEN: d -= 1
        j -= 1
    k = j + 1
    while k < i and s[k] == ' ': k += 1
    m = re.match(r'(return|case)\s+', s[k:i])
    return k + m.end() if m else k

def body_span(code, func):
    m = re.search(r'\b%s\s*\([^;{]*\)\s*\{' % re.escape(func or r'\w+'), code)
    return (m.end(), len(code)) if m else (0, len(code))

def _ctx_lines(err):
    return [x for x in re.findall(r'@@([^|]*)', err or '') if x.strip()]


# ------------------------------------------------------------------ spframe
DECL = re.compile(r'^    (?!return\b|goto\b|case\b)((?:struct\s+)?\w+)\s*(\**)\s*sp([0-9A-F]+)(\[(\w*)\])?;[ \t]*$', re.M)

def fix_spframe(code, err=None, func=None, src=None, force=False):
    if ' sp;' in code and 'struct {' in code: return None
    bs, _ = body_span(code, func)
    decls = {}
    for m in DECL.finditer(code):
        if m.start() < bs: continue
        t, stars, off, arr, n = m.groups(); off = int(off, 16)
        if off in decls: continue
        size = 4 if stars else TSZ.get(t)
        decls[off] = dict(t=t + (' ' + stars if stars else ''), size=size, n=(int(n, 0) if n else (0 if arr is not None else None)), m=m)
    body = code[bs:]
    used = {int(x, 16) for x in re.findall(r'\bsp([0-9A-F]+)\b', body)}
    taken = {int(x, 16) for x in re.findall(r'&sp([0-9A-F]+)\b', body)}
    undef = used - set(decls)
    arrays = {o for o, d in decls.items() if d['n'] is not None}
    cand = (taken | undef | arrays)
    if not cand: return None
    if not (undef or arrays or force or any(decls.get(o, {}).get('n') is None for o in taken)): return None
    if any(d['size'] is None for o, d in decls.items() if o >= min(cand)) and not force:
        pass
    base = min(cand)
    A = asm(func) if func else None
    top = A.lowest_save if A and A.frame else None
    offs = sorted(o for o in (set(decls) | undef) if o >= base)
    # types of undeclared ones: the type of the previous 4-byte slot, else s32
    for o in offs:
        if o in undef:
            prev = [decls[p] for p in sorted(decls) if p < o and decls[p]['size'] == 4 and decls[p]['n'] is None]
            decls[o] = dict(t=prev[-1]['t'] if prev and o - max(p for p in decls if p < o) <= 8 else 's32', size=4, n=None, m=None)
    start = base & ~7 if any((decls[o]['size'] or 4) == 8 and o % 8 == 0 for o in offs) else base
    fields = []; cur = start; covered = {}
    for k, o in enumerate(offs):
        d = decls[o]
        if o < cur:
            covered[o] = d; continue
        if o > cur: fields.append('        u8 pad%X[0x%X];' % (cur, o - cur)); cur = o
        nxt = next((p for p in offs[k + 1:] if p > o), None)
        if d['n'] == 0:   # unsized array: up to the next slot / the save area
            end = nxt or top or (o + 4)
            esz = d['size'] or 1
            d['n'] = max(1, (end - o) // esz)
        if d['size'] is None:   # struct / unknown type: keep its type, trust the compiler for its size
            fields.append('        %s u%X%s;' % (d['t'], o, '[%d]' % d['n'] if d['n'] else ''))
            cur = nxt or (o + 4)
            continue
        fields.append('        %s u%X%s;' % (d['t'], o, '[%d]' % d['n'] if d['n'] else ''))
        cur = o + d['size'] * (d['n'] or 1)
    if top and top > cur: fields.append('        u8 pad%X[0x%X];' % (cur, top - cur)); cur = top
    out = code
    # drop the old declarations (from the end so offsets stay valid)
    for o in sorted(offs, key=lambda o: -(decls[o]['m'].start() if decls[o]['m'] else -1)):
        m = decls[o]['m']
        if m: out = out[:m.start()] + out[m.end() + 1:]
    def rep(mm):
        o = int(mm.group(1), 16)
        if o < base or o not in decls: return mm.group(0)
        if o in covered:
            return '(*(%s *)((u8 *)&sp + 0x%X))' % (covered[o]['t'], o - start)
        return 'sp.u%X' % o
    bs2, _ = body_span(out, func)
    out = out[:bs2] + re.sub(r'\bsp([0-9A-F]+)\b', rep, out[bs2:])
    struct = '    struct {\n%s\n    } sp;\n' % '\n'.join(fields)
    # insert after the opening brace of the function
    out = out[:bs2] + '\n' + struct + out[bs2:].lstrip('\n') if not out[bs2:].startswith('\n') else out[:bs2 + 1] + struct + out[bs2 + 1:]
    return out


# ------------------------------------------------------------------ u8arith
def _ptr_vars(code, func):
    res = {}
    bs, _ = body_span(code, func)
    for m in re.finditer(r'^    ((?:struct\s+)?\w+)\s*(\*+)\s*(\w+);', code[bs:], re.M):
        t, st, n = m.groups()
        if st == '*' and TSZ.get(t) == 1 or t == 'void' and st == '*': continue
        res[n] = t + ' ' + st[1:] if len(st) > 1 else t
    dm = re.search(r'\b%s\s*\(([^)]*)\)\s*\{' % re.escape(func), code)
    if dm:
        for p in dm.group(1).split(','):
            m = re.match(r'\s*((?:struct\s+)?\w+)\s*(\*+)\s*(\w+)\s*$', p)
            if m:
                t, st, n = m.groups()
                if st == '*' and (TSZ.get(t) == 1 or t == 'void'): continue
                res[n] = t + ' ' + st[1:] if len(st) > 1 else t
    for m in re.finditer(r'^extern\s+((?:struct\s+)?\w+)\s+(D_\w+);', code, re.M):
        t, n = m.groups()
        if TSZ.get(t) != 1: res['&' + n] = t
    return res

def fix_u8arith(code, why=None, func=None, src=None):
    pv = _ptr_vars(code, func)
    if not pv: return None
    bs, _ = body_span(code, func)
    head, s = code[:bs], code[bs:]
    names = sorted(pv, key=len, reverse=True)
    alt = '|'.join(re.escape(n) for n in names)
    ch = False
    for _ in range(200):
        done = False
        # P += E / P -= E
        for m in re.finditer(r'(?<![\w.>*])(%s) ([+-])= ' % alt, s):
            n = m.group(1); e = scan_right(s, m.end(), [])
            new = '%s = (%s *)((u8 *)%s %s (%s))' % (n, pv[n], n, m.group(2), s[m.end():e])
            s = s[:m.start()] + new + s[e:]; done = True; break
        if done: ch = True; continue
        # P + E / P - E   (P not dereferenced / member / multiplied)
        for m in re.finditer(r'(?<![\w.>])(%s)(?![\w\[(]|->) ([+-]) ' % alt, s):
            pre = s[:m.start()]
            if pre.endswith('*') or pre.endswith('(u8 *)') or pre.endswith(' * ') or pre.endswith('->') : continue
            e = scan_right(s, m.end(), ADD_STOPS)
            rhs = s[m.end():e]
            if not rhs or rhs.lstrip('(').split(')')[0] in pv or rhs.startswith('&'): continue
            n = m.group(1)
            new = '((%s *)((u8 *)%s %s %s))' % (pv[n], n, m.group(2), rhs)
            s = s[:m.start()] + new + s[e:]; done = True; break
        if done: ch = True; continue
        # E + P
        for m in re.finditer(r' \+ (%s)(?![\w\[(]|->)' % alt, s):
            if s[m.end():m.end() + 1] not in ('', ')', ';', ',', ' '): continue
            b = scan_left(s, m.start(), ADD_STOPS)
            lhs = s[b:m.start()]
            if not lhs or lhs in pv or lhs.startswith('&') or lhs.startswith('(u8 *)'): continue
            n = m.group(1)
            new = '((%s *)((u8 *)%s + %s))' % (pv[n], n, lhs)
            s = s[:b] + new + s[m.end():]; done = True; break
        if done: ch = True; continue
        break
    return head + s if ch else None


# ------------------------------------------------------------------ CERR relaxations
def _wrap(x, cast):
    x = x.strip()
    if x.startswith(cast): return x
    return '%s(%s)' % (cast, x) if not re.match(r'^[\w.]+$', x) else cast + x

def fix_cmp(code, err, func=None, src=None):
    if 'Unacceptable operand of ==' not in (err or '') and 'Unacceptable operand of <' not in (err or ''): return None
    out = code
    for ln in _ctx_lines(err):
        if ln not in out: continue
        new = ln
        for op in ('==', '!=', '<', '>', '<=', '>='):
            k = 0
            while True:
                k = new.find(' %s ' % op, k)
                if k < 0: break
                a = scan_left(new, k, CMP_STOPS + (['<', '>', '<=', '>='] if op in '<=>=' else []))
                bst = k + len(op) + 2
                b = scan_right(new, bst, CMP_STOPS + ['<', '>', '<=', '>=', '+', '-'][:0])
                L, R = new[a:k], new[bst:b]
                if L.startswith('(s32)') and R.startswith('(s32)'): k = b; continue
                rep = '%s %s %s' % (_wrap(L, '(s32)'), op, _wrap(R, '(s32)'))
                new = new[:a] + rep + new[b:]; k = a + len(rep)
        if new != ln: out = out.replace(ln, new)
    return out if out != code else None

def fix_deref(code, err, func=None, src=None):
    if 'Dereferenced a non-pointer' not in (err or ''): return None
    out = code
    for ln in _ctx_lines(err):
        if ln not in out: continue
        new = re.sub(r'(?<![\w)\]])\*\((?!\s*(?:struct\s+)?\w+\s*\*+\s*\))', '*(s32 *)(', ln)
        new = re.sub(r'(?<![\w)\]] )(?<![\w)\]])\*(\w+)\b(?!\s*\()', lambda m: '*(s32 *)' + m.group(1) if not m.group(1).startswith('s32') else m.group(0), new) if new == ln else new
        if new != ln: out = out.replace(ln, new)
    return out if out != code else None


# ------------------------------------------------------------------ rodata strings
def fix_rostr(code, err=None, func=None, src=None):
    if '""' not in code or not func: return None
    A = asm(func)
    miss = [s for s in A.lo_syms() if not re.search(r'\b%s\b' % s, code) and not s.startswith('jtbl_')]
    n = code.count('""')
    if not miss: return None
    out = code
    for k in range(n):
        s = miss[k] if k < len(miss) else miss[-1]
        out = out.replace('""', '((u8 *)&%s)' % s, 1)
    hoist = ''.join('//HOIST extern u8 %s[];\n' % s for s in miss[:n]
                    if not re.search(r'\b%s\b' % s, src or '') and '%s[]' % s not in code)
    return hoist + out


# ------------------------------------------------------------------ passthru (asm-driven)
def _call_args(code, j):
    depth = 1; args = []; cur = ''
    while depth and j < len(code):
        c = code[j]; j += 1
        if c in '([': depth += 1
        elif c in ')]':
            depth -= 1
            if depth == 0: break
        if c == ',' and depth == 1: args.append(cur); cur = ''; continue
        cur += c
    if cur.strip(): args.append(cur)
    return [x.strip() for x in args], j

def fix_passthru(code, why, func, src=None):
    m = re.search(r': call #\d+ (\w+): a(\d) ref=0x([0-9A-F]+) cand=0x([0-9A-F]+)', why or '')
    if not m: return None
    callee, n = m.group(1), int(m.group(2))
    cname = 'func_' + callee[2:].upper() if callee.startswith('0x') else callee
    dm = re.search(r'\b%s\s*\(([^)]*)\)\s*\{' % func, code)
    if not dm: return None
    params = [re.findall(r'(\w+)\s*$', p.strip())[0] for p in dm.group(1).split(',') if p.strip() and p.strip() != 'void']
    A = asm(func)
    sites = A.call_sites(callee if not callee.startswith('0x') else cname) or A.call_sites(callee)
    srcs = {A.arg_source(s, n) for s in sites}
    expr = None; mode = 'auto'
    if len(srcs) == 1:
        k = next(iter(srcs))
        if k[0] == 'pass' and n < len(params): expr = params[n]
        elif k[0] == 'stkarg' and 0 <= k[1] < len(params): expr = params[k[1]]
        elif k[0] in ('addr', 'local'):
            o = k[1]; nm = 'sp%X' % o
            if re.search(r'\bsp\.u%X\b' % o, code): expr = ('&' if k[0] == 'addr' else '') + 'sp.u%X' % o
            elif re.search(r'^    [\w ]+\**\s*%s\[' % nm, code, re.M): expr = nm if k[0] == 'addr' else nm + '[0]'
            elif re.search(r'^    [\w ]+\**\s*%s;' % nm, code, re.M): expr = ('&' if k[0] == 'addr' else '') + nm
        if expr is None: return None
    elif not srcs and n < len(params):
        expr = params[n]
    else:
        return None
    # how many args the asm passes (written a-regs, pass-throughs up to n): fewer in the draft -> insert, else replace
    ar = max([n] + [r for s_ in sites for r in range(4) if A.arg_source(s_, r)[0] != 'pass']) + 1
    out = []; i = 0; ch = False
    pat = re.compile(r'(?<![\w*])%s\(' % re.escape(cname))
    while True:
        mm = pat.search(code, i)
        if not mm: out.append(code[i:]); break
        args, j = _call_args(code, mm.end())
        ls = code.rfind('\n', 0, mm.start()) + 1
        is_decl = code[ls:mm.start()].strip() != '' and code[j:j + 1] == ';' and not re.search(r'[=(]', code[ls:mm.start()])
        a0 = args if args != ['void'] else []
        if is_decl:
            if len(a0) <= n: a0 = a0 + ['s32'] * (n + 1 - len(a0))
            else: out.append(code[i:j]); i = j; continue
        elif len(a0) == n: a0 = a0 + [expr]
        elif len(a0) < n: return None
        elif a0[n] == expr: out.append(code[i:j]); i = j; continue
        else:
            # m2c shifted the args (dropped one) when the arg in slot n reappears later, else it passed a wrong value
            a0 = a0[:n] + [expr] + (a0[n:] if len(a0) < ar else a0[n + 1:])
        out.append(code[i:mm.end()] + ', '.join(a0) + ')'); i = j; ch = True
    return ''.join(out) if ch else None

def lint(code):
    out = []
    scal = set(re.findall(r'^\s+(?:s8|u8|s16|u16|s32|u32|f32|f64|s64|u64)\s+(sp[0-9A-F]+);', code, re.M))
    if any(re.search(r'&%s\b' % v, code) for v in scal):
        out.append('lint:stackaddr')
    if re.search(r'\bsubroutine_arg|\bsaved_reg|M2C_', code): out.append('lint:m2cmacro')
    return out


if __name__ == '__main__':
    import sys
    fx = globals()['fix_' + sys.argv[1]]
    code = open(sys.argv[2]).read()
    r = fx(code, sys.argv[4] if len(sys.argv) > 4 else '', sys.argv[3])
    print(r if r is not None else '(no change)')


# ------------------------------------------------------------------ prototypes (one signature per function, for wasm)
_CANON = None
_PCM = []
def _pc():
    if _PCM: return _PCM[0]
    import importlib.util
    sp = importlib.util.spec_from_file_location('nm_protocheck', os.path.join(os.path.dirname(os.path.abspath(__file__)), 'protocheck.py'))
    m = importlib.util.module_from_spec(sp); sp.loader.exec_module(m); _PCM.append(m); return m

def canon():
    """name -> (prototype text, ABI signature) of every C definition in src_eu (matching or NON_MATCHING)"""
    global _CANON
    if _CANON is None:
        pc = _pc()
        _CANON = {}
        for p in glob.glob(os.path.join(ROOT, 'conker/src_eu/**/*.c'), recursive=True):
            for m in pc.SIG.finditer(open(p, errors='replace').read()):
                ret, name, ps, end = m.groups()
                if end == '{' and name not in _CANON and not re.search(r'\b(static|if|while|return)\b', ret):
                    _CANON[name] = ('%s %s(%s)' % (_gen(ret), name, ', '.join(_gen(x) for x in re.split(r',(?![^()]*\))', ps)) if ps.strip() else ''),
                                    pc.sig(ret, ps))
    return _CANON

PRIM = {'s8', 'u8', 's16', 'u16', 's32', 'u32', 'f32', 'f64', 's64', 'u64', 'void', 'int', 'char', 'short', 'long', 'float',
        'double', 'unsigned', 'signed', 'const', 'volatile', 'struct', 'register'}
def _gen(t):
    """a definition's type, spelled so that any TU can use it: pointers to non-primitive types -> void *,
    parameter names dropped"""
    t = ' '.join(t.split())
    if t in ('void', '...', ''): return t
    if '(' in t: return 'void *'
    m = re.match(r'^(.*?)(\w+)?\s*(\[\w*\])?$', t)
    base = t
    if m and m.group(2) and len(re.findall(r'\w+', t)) > 1 and not t.endswith('*'):
        base = (m.group(1) + ('*' if m.group(3) else '')).strip()
    words = re.findall(r'\w+', base)
    if '*' in base and any(w not in PRIM for w in words): return 'void *'
    if any(w not in PRIM for w in words): return 's32'
    return base

def proto_problems(code, func):
    pc = _pc()
    C = canon(); out = []
    bdef = re.search(r'\b%s\s*\([^;{]*\)\s*\{' % re.escape(func), code)
    head = code[:bdef.start()] if bdef else code
    for m in pc.SIG.finditer(head.replace('//HOIST ', '')):
        ret, name, ps, end = m.groups()
        if end != ';' or name == func or name not in C: continue
        sg = pc.sig(ret, ps)
        if not pc.compat(sg, C[name][1]) or sg[1] is None and C[name][1][1] is not None:
            out.append((m.group(0), name))
    return out

def fix_proto(code, why=None, func=None, src=None):
    """replace draft-local / hoisted prototypes of callees that disagree with the callee's C definition
    (or are K&R `()`) by the definition's prototype; drop the `((s32 (*)())f)(` casts of the argc fix
    when the definition is known"""
    C = canon(); out = code
    for line, name in proto_problems(code, func):
        new = C[name][0] + ';'
        if line.lstrip().startswith('extern'): new = 'extern ' + new
        out = out.replace(line.strip(), new, 1) if line.strip() in out else out
        out = out.replace('//HOIST ' + new, '//HOIST ' + new)
    out = re.sub(r'\(\(s32 \(\*\)\(\)\)(\w+)\)\(', lambda m: m.group(1) + '(' if m.group(1) in C else m.group(0), out)
    # calls with more arguments than the definition takes: drop the extra ones (the callee never reads them)
    bdef = re.search(r'\b%s\s*\([^;{]*\)\s*\{' % re.escape(func), out)
    if bdef:
        body = out[bdef.end():]
        for name, (txt, sg) in [(n, C[n]) for n in set(re.findall(r'\b(\w+)\(', body)) if n in C and n != func]:
            if sg[1] is None or '...' in sg[1]: continue
            k = len(sg[1]); res = []; i = 0
            for mm in re.finditer(r'(?<![\w*])%s\(' % re.escape(name), body):
                if mm.start() < i: continue
                args, j = _call_args(body, mm.end())
                if len(args) > k:
                    res.append(body[i:mm.end()] + ', '.join(args[:k]) + ')'); i = j
            if res: body = ''.join(res) + body[i:]
        out = out[:bdef.end()] + body
    return out if out != code else None
