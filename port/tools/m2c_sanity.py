#!/usr/bin/env python3
"""m2c_sanity.py (P118): find m2c translation bugs in the NON_MATCHING bodies the port compiles, by comparing each
body's clang IR with the EU asm of the same function.

Bug class (P116): P15-era m2c bodies that are wrong in C although the N64 build never compiled them:
  * pointer stride: `var_s6 += 4` on a `u8 **` (asm `addiu s6,s6,4` = one pointer), `(n * 0x78) + &D_800C3AA8` on an
    `s32 *` (scaled x4) -- func_1502457C;
  * load width: `*(s32 *)p != -0xE` where the asm does `lb` -- func_150337A8.

Usage (worktree root, after `eval "$(tools/eu_port/wt.sh env web)"`; runs on the host, needs Homebrew LLVM `opt`):
    python3 port/tools/m2c_sanity.py [--out docs/port/m2c_sanity.tsv] [--func NAME] [--top 40] [--all]

Method
  scope   : functions defined inside `#ifdef NON_MATCHING` branches of conker/src_eu/**/*.c (what the port compiles).
  IR      : port/build/ll/<tu>.c.ll (-O0, no optnone) -> `opt -passes=sroa,instcombine` (cached in
            port/build/m2c_sanity/) so locals are SSA values and constant GEPs are byte offsets (`gep i8, p, C`).
            The raw -O0 IR is used for the scaled-index check (the GEP element type is still the C pointer type).
  asm     : port/build/arity/eu_elf.dis (objdump of conker/build/conker.eu.elf, arity_scan.py's cache) and
            eu_elf.sym for global addresses.
  location: every memory access gets a location: G:<addr> for a global (asm: lui/addiu/addu constant tracking;
            IR: @sym -> ELF symbol value, + constant GEP offset; `+` = with a variable index), A<i>:<off> for an
            entry argument register a0..a3 / IR parameter i, O:<off> for any other base (both sides pooled).
            Stack accesses (sp base, IR allocas) are ignored.
Kinds
  width   : at one location the two sides use different access sizes (byte/half/word/dword) -- one side has a
            size the other lacks there while having another size at the same location. Confidence: high for G/A
            locations with disjoint size sets, med for G/A otherwise or O with disjoint sets, low for pooled O.
  sign    : same location and size (1/2) but lb vs lbu / lh vs lhu disagrees with the IR sext/zext use. low.
  stride  : loop increment of a pointer (IR `phi ptr` fed by `gep p, C`) or of an index scaled by a GEP
            element size, whose byte step is not a self-increment step (`addiu r,r,C`, also C<<sll) in the asm.
            high when IR step = 4x / 2x / 8x of an asm step (typed-pointer scaling), else med.
  scaled  : -O0 GEP with element size k > 1 whose index is `mul x, K` / `shl x, c`, and the body source has the m2c
            byte idiom `(... * K) + &SYM` / `&SYM + (... * K)` / `SYM + (... * K)` on that symbol: effective byte
            scale K*k where m2c meant K. high if the asm has no access stride K*k ... (always reported high when the
            idiom matches; med for `mul` on a non-byte GEP of a global without the idiom).
Frame path: `path` column = 2 when the function name appears in the P113/P116 runtime logs / notes (port_work/p113,
port_work/p116, docs/port/sessions/P113.md, P116.md), 1 when it is a direct C callee/caller of such a function, else 0.
"""
import os, re, sys, glob, subprocess, collections

ROOT = os.getcwd()
if not os.path.exists(os.path.join(ROOT, 'conker/src_eu')):
    sys.exit('run from the worktree root')
cr = os.environ.get('CONKER_ROOT')
if cr and os.path.realpath(cr) != os.path.realpath(ROOT):
    sys.exit('CONKER_ROOT %s != cwd %s' % (cr, ROOT))
args = sys.argv[1:]


def opt(name, d=None):
    return args[args.index(name) + 1] if name in args else d


OUT = opt('--out', 'docs/port/m2c_sanity.tsv')
ONLY = opt('--func')
TOP = int(opt('--top', '40'))
OPT = opt('--opt', '/opt/homebrew/opt/llvm/bin/opt')
DIS = 'port/build/arity/eu_elf.dis'
SYM = 'port/build/arity/eu_elf.sym'
LLDIR = 'port/build/ll'
CACHE = 'port/build/m2c_sanity'

# ---------------------------------------------------------------- source: NM function list


def nm_select(text):
    """1 per line: line compiled with NON_MATCHING defined AND inside an NM branch."""
    res, stack = [], []
    for line in text.split('\n'):
        s = line.strip()
        m = re.match(r'#\s*(ifdef|ifndef|if|elif|else|endif)\b(.*)', s)
        if m:
            d, rest = m.group(1), m.group(2).strip()
            if d in ('ifdef', 'ifndef', 'if'):
                nm = None
                if d == 'ifdef' and rest == 'NON_MATCHING' or d == 'if' and re.fullmatch(r'defined\s*\(?\s*NON_MATCHING\s*\)?', rest):
                    nm = True
                elif d == 'ifndef' and rest == 'NON_MATCHING' or d == 'if' and re.fullmatch(r'!\s*defined\s*\(?\s*NON_MATCHING\s*\)?', rest):
                    nm = False
                stack.append(nm)
            elif d == 'else' and stack and stack[-1] is not None:
                stack[-1] = not stack[-1]
            elif d == 'endif' and stack:
                stack.pop()
            res.append(0)
            continue
        live = all(x is not False for x in stack)
        res.append(1 if live and any(x is True for x in stack) else 0)
    return res


DEF_RE = re.compile(r'^[A-Za-z_][\w \t\*]*?\b([A-Za-z_]\w*)\s*\(([^;{)]*(?:\([^)]*\)[^;{)]*)*)\)\s*\{', re.M)
nmfuncs = {}   # name -> (file, body text)
for p in sorted(glob.glob('conker/src_eu/**/*.c', recursive=True)):
    text = open(p, errors='replace').read()
    sel = nm_select(text)
    starts = [0]
    for ln in text.split('\n'):
        starts.append(starts[-1] + len(ln) + 1)
    for m in DEF_RE.finditer(text):
        name = m.group(1)
        if name in ('if', 'while', 'for', 'switch'):
            continue
        ln = text.count('\n', 0, m.start())
        if ln < len(sel) and sel[ln]:
            end = text.find('\n}', m.end())
            nmfuncs.setdefault(name, (p, text[m.start():end]))

# ---------------------------------------------------------------- asm
syms = {}
for line in open(SYM):
    f = line.split()
    if len(f) >= 5 and re.fullmatch(r'[0-9a-f]{8}', f[0]):
        syms.setdefault(f[-1], int(f[0], 16))

asm = {}
cur = None
for line in open(DIS):
    m = re.match(r'^([0-9a-f]+) <(\w+)>:', line)
    if m:
        cur = m.group(2); asm[cur] = []; continue
    if cur and line[:1] in '0123456789abcdef' and ':\t' in line:
        p = line.rstrip('\n').split('\t')
        if len(p) >= 2:
            asm[cur].append((int(p[0].rstrip(':'), 16), p[1], p[2] if len(p) > 2 else ''))

MEM = {'lb': (1, 's', 'L'), 'lbu': (1, 'u', 'L'), 'lh': (2, 's', 'L'), 'lhu': (2, 'u', 'L'), 'lw': (4, '', 'L'),
       'lwc1': (4, 'f', 'L'), 'ldc1': (8, 'f', 'L'), 'ld': (8, '', 'L'), 'sb': (1, '', 'S'), 'sh': (2, '', 'S'),
       'sw': (4, '', 'S'), 'swc1': (4, 'f', 'S'), 'sdc1': (8, 'f', 'S'), 'sd': (8, '', 'S')}
NOWRITE = set('sb sh sw swc1 sdc1 sd swl swr mtc1 ctc1 mult multu div divu dmult dmultu ddiv ddivu j jr jal jalr '
              'nop syscall break teq tne cache sync b bal'.split())
GPR = set('zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 t8 t9 s0 s1 s2 s3 s4 s5 s6 s7 s8 fp k0 k1 gp ra'.split())
CALLER = set('at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 t8 t9 ra'.split())


def asm_facts(name):
    """-> (accesses [(loc, width, sign, dir, addr)], self-steps {C: [regs]}, sll shifts per reg)"""
    st = {'a0': ('a', 0), 'a1': ('a', 1), 'a2': ('a', 2), 'a3': ('a', 3)}
    acc, steps, shl = [], collections.defaultdict(set), collections.defaultdict(set)
    stepcnt = collections.Counter()
    # linear tracker: lin[reg] = (symbol id, coefficient); collects the constant multipliers IDO builds with
    # sll/addu/subu chains or mult by a li constant (x*0x78 = ((x<<4)-x)<<3)
    lin, coefs, fresh, kval, lastmul = {}, set(), [0], {}, [None]

    def L(r):
        if r == 'zero':
            return None
        if r not in lin:
            fresh[0] += 1
            lin[r] = (fresh[0], 1)
        return lin[r]
    for addr, op, ops in asm.get(name, []):
        o = [x.strip() for x in ops.split(',')] if ops else []
        nl = None
        try:
            if op == 'sll' and len(o) == 3 and o[1] != 'zero':
                a = L(o[1]); nl = (a[0], a[1] << int(o[2], 0))
            elif op in ('addu', 'subu') and len(o) == 3:
                a, b = L(o[1]), L(o[2])
                if a and b and a[0] == b[0]:
                    nl = (a[0], a[1] + b[1] if op == 'addu' else a[1] - b[1])
                elif op == 'addu' and a and b:
                    nl = a if abs(a[1]) > 1 else b if abs(b[1]) > 1 else None
            elif op in ('mult', 'multu') and len(o) == 2:
                ka, kb = kval.get(o[0]), kval.get(o[1])
                lastmul[0] = (L(o[1])[0], ka) if ka is not None else (L(o[0])[0], kb) if kb is not None else None
            elif op == 'mflo' and lastmul[0] and lastmul[0][1] is not None:
                nl = lastmul[0]
            elif op == 'negu' and len(o) == 2:
                a = L(o[1]); nl = (a[0], -a[1]) if a else None
            elif op == 'move' and len(o) == 2:
                nl = L(o[1])
        except (ValueError, TypeError):
            nl = None
        if op == 'li' and len(o) == 2:
            try:
                kval[o[0]] = int(o[1], 0)
            except ValueError:
                pass
        elif o and o[0] in GPR and op not in NOWRITE and not op.startswith('b'):
            kval.pop(o[0], None)
        if o and o[0] in GPR and op not in NOWRITE and not (op.startswith('b') and op != 'break'):
            if nl:
                lin[o[0]] = nl
                if abs(nl[1]) > 1:
                    coefs.add(abs(nl[1]))
            else:
                lin.pop(o[0], None)
        if op in MEM and len(o) == 2:
            w, sg, dr = MEM[op]
            mm = re.match(r'(-?\d+)\((\w+)\)', o[1])
            if mm:
                off, base = int(mm.group(1)), mm.group(2)
                s = st.get(base)
                if base == 'sp' or (s and s[0] == 's'):
                    acc.append((('S',), w, sg, dr, addr, o[0]))
                else:
                    if s and s[0] in 'cg':
                        loc = ('G', (s[1] + off) & 0xFFFFFFFF, s[0] == 'g')
                    elif s and s[0] == 'a':
                        loc = ('A', s[1], off)
                    else:
                        loc = ('O', off)
                    acc.append((loc, w, sg, dr, addr, o[0]))
            if dr == 'L' and o[0] in GPR:
                st[o[0]] = None
            continue
        if op.startswith('b') and op not in ('break',):
            continue
        if op in ('jal', 'jalr'):
            for r in CALLER:
                st[r] = None
            continue
        if op in NOWRITE or not o or o[0] not in GPR:
            continue
        d = o[0]
        v = None
        try:
            if op == 'lui':
                v = ('c', int(o[1], 0) << 16)
            elif op in ('addiu', 'addi', 'daddiu') and len(o) == 3:
                s, imm = st.get(o[1]), int(o[2], 0)
                if o[1] == d and imm and not (s and s[0] == 'c' and (s[1] & 0xFFFF) == 0):
                    steps[imm].add(d)
                    stepcnt[(d, imm)] += 1
                if o[1] == 'sp' or (s and s[0] == 's'):
                    v = ('s', 0)
                elif s and s[0] in 'cg':
                    v = (s[0], s[1] + imm)
                elif s and s[0] == 'a' and imm == 0:
                    v = s
            elif op == 'li' and len(o) == 2:
                v = ('k', int(o[1], 0))
            elif op == 'move':
                v = st.get(o[1])
            elif op in ('addu', 'add') and len(o) == 3:
                a, b = st.get(o[1]), st.get(o[2])
                if o[2] == 'zero':
                    v = a
                elif o[1] == 'zero':
                    v = b
                elif a and a[0] in 'cg' and not (b and b[0] in 'cg'):
                    v = ('g', a[1])
                elif b and b[0] in 'cg' and not (a and a[0] in 'cg'):
                    v = ('g', b[1])
            elif op == 'sll' and len(o) == 3:
                shl[o[1]].add(int(o[2], 0))
        except ValueError:
            v = None
        st[d] = v
    # derived steps: register r self-incremented by C and shifted left by k -> C << k
    eff = set()
    for c, regs in steps.items():
        eff.add(abs(c))
        for r in regs:
            for k in shl.get(r, ()):
                eff.add(abs(c) << k)
    # unrolled loops: one register stepped m times by C in the body = one IR step of m*C (instcombine folds them)
    ins = asm.get(name, [])
    stk_st = {a for loc, w, sg, dr, a, rt in acc if loc[0] == 'S' and dr == 'S'}
    acc = [x for x in acc if x[0][0] != 'S' or x[3] == 'L' and False]
    pos = {a: i for i, (a, op, ops) in enumerate(ins)}
    keep = []
    for loc, w, sg, dr, addr, rt in acc:
        if dr == 'L':
            i = pos[addr]
            cp = False
            for a2, op2, ops2 in ins[i + 1:i + 5]:
                if op2 in MEM and MEM[op2][2] == 'S' and ops2.split(',')[0].strip() == rt and a2 in stk_st:
                    cp = True
                    break
            if cp:
                continue
        keep.append((loc, w, sg, dr, addr))
    acc = keep
    unroll = collections.Counter()
    for (r, c), m in stepcnt.items():
        unroll[abs(c)] = max(unroll[abs(c)], m)
    return acc, (steps, unroll), eff, coefs

# ---------------------------------------------------------------- IR


def run_opt(tu):
    src = os.path.join(LLDIR, tu)
    dst = os.path.join(CACHE, tu.replace('.c.ll', '.o.ll'))
    if not os.path.exists(dst) or os.path.getmtime(dst) < os.path.getmtime(src):
        os.makedirs(CACHE, exist_ok=True)
        r = subprocess.run([OPT, '-S', '-passes=sroa,instcombine<no-verify-fixpoint>', src, '-o', dst], capture_output=True, text=True)
        if r.returncode:
            sys.stderr.write('opt failed %s: %s\n' % (tu, r.stderr[:300]))
            return None
    return dst


def functions(path):
    """name -> (param count, [lines]); plus struct types"""
    res, structs, cur = {}, {}, None
    for line in open(path):
        if cur is None:
            m = re.match(r'(%[\w.$"]+) = type (<?\{.*\}>?)\s*$', line)
            if m:
                structs[m.group(1)] = m.group(2)
                continue
            m = re.match(r'define [^@]*@"?([\w.$]+)"?\((.*)\)[^{]*\{', line)
            if m:
                ps = m.group(2).strip()
                cur = m.group(1); res[cur] = (0 if not ps else len(re.findall(r'%\d+', ps)) or ps.count(',') + 1, [])
            continue
        if line.startswith('}'):
            cur = None
            continue
        res[cur][1].append(line.rstrip('\n'))
    return res, structs


def split_top(s):
    out, d, c = [], 0, ''
    for ch in s:
        if ch in '([{<':
            d += 1
        elif ch in ')]}>':
            d -= 1
        if ch == ',' and d == 0:
            out.append(c.strip()); c = ''
        else:
            c += ch
    if c.strip():
        out.append(c.strip())
    return out


class Types:
    def __init__(self, structs):
        self.structs = structs
        self.cache = {}

    def fields(self, t):
        body = self.structs.get(t, t)
        packed = body.startswith('<')
        inner = body.strip('<>').strip()[1:-1].strip()
        return (split_top(inner) if inner else []), packed

    def size_align(self, t):
        t = t.strip()
        if t in self.cache:
            return self.cache[t]
        r = None
        prim = {'i1': (1, 1), 'i8': (1, 1), 'i16': (2, 2), 'i32': (4, 4), 'i64': (8, 8), 'float': (4, 4),
                'double': (8, 8), 'ptr': (4, 4), 'i128': (16, 16)}
        if t in prim:
            r = prim[t]
        else:
            m = re.fullmatch(r'\[(\d+) x (.+)\]', t)
            if m:
                s, a = self.size_align(m.group(2))
                r = (int(m.group(1)) * s, a)
            elif t.startswith('%') or t.startswith('{') or t.startswith('<{'):
                fl, packed = self.fields(t)
                off, al = 0, 1
                for f in fl:
                    s, a = self.size_align(f)
                    if not packed:
                        off = (off + a - 1) // a * a
                        al = max(al, a)
                    off += s
                off = (off + al - 1) // al * al
                r = (off, al)
            else:
                r = (4, 4)
        self.cache[t] = r
        return r

    def field_off(self, t, i):
        fl, packed = self.fields(t)
        off = 0
        for k, f in enumerate(fl):
            s, a = self.size_align(f)
            if not packed:
                off = (off + a - 1) // a * a
            if k == i:
                return off, f
            off += s
        return off, 'i8'

    def gep(self, elem, idx):
        """idx: list of (type, value str). -> (const byte offset, [(var, scale)])"""
        const, var = 0, []
        size = self.size_align(elem)[0]
        t = elem
        for n, (it, iv) in enumerate(idx):
            if n == 0:
                sc = size
            else:
                m = re.fullmatch(r'\[(\d+) x (.+)\]', t)
                if m:
                    t = m.group(2); sc = self.size_align(t)[0]
                elif t.startswith('%') or t.startswith('{') or t.startswith('<{'):
                    try:
                        o, t = self.field_off(t, int(iv))
                    except ValueError:
                        return None
                    const += o
                    continue
                else:
                    sc = 1
            try:
                const += int(iv) * sc
            except ValueError:
                var.append((iv, sc))
        return const, var


GEP_RE = re.compile(r'getelementptr (?:inbounds )?(?:nuw )?(?:nusw )?\(?\s*(.+)$')
CEXPR_RE = re.compile(r'getelementptr (?:inbounds )?(?:nuw )?(?:nusw )?\((.*)\)')


def parse_gep_operands(s, T):
    """'<elem>, ptr <base>, i32 a, i32 b' -> (elem, base, [(t, v)])"""
    parts = split_top(s)
    if len(parts) < 2:
        return None
    elem = parts[0]
    bp = parts[1].split(None, 1)
    base = bp[1] if len(bp) > 1 else bp[0]
    idx = []
    for p in parts[2:]:
        q = p.split(None, 1)
        if len(q) == 2 and q[0].startswith('i'):
            idx.append((q[0], q[1].strip()))
    return elem, base.strip(), idx


def ir_facts(lines, nparams, T, rawlines=None):
    defs = {}
    for ln in lines:
        m = re.match(r'\s*(%[\w.$]+) = (.*)$', ln)
        if m:
            defs[m.group(1)] = m.group(2)

    def const_of(v):
        try:
            return int(v)
        except ValueError:
            return None

    def resolve(ptr, depth=0):
        """-> (loc kind, base, const off, has_var) or None (stack)"""
        ptr = ptr.strip()
        if depth > 30:
            return ('O', None, 0, True)
        m = CEXPR_RE.match(ptr)
        if m:
            g = parse_gep_operands(m.group(1), T)
            if g:
                r = T.gep(g[0], g[2])
                if r:
                    b = resolve(g[1], depth + 1)
                    if b:
                        return (b[0], b[1], b[2] + r[0], b[3] or bool(r[1]))
            return ('O', None, 0, True)
        if ptr.startswith('@'):
            nm = ptr[1:].strip('"')
            return ('G', nm, 0, False)
        if ptr == 'null':
            return ('G', '#0', 0, False)
        m = re.match(r'inttoptr \(i32 (-?\d+) to ptr\)', ptr)
        if m:
            return ('G', '#%d' % (int(m.group(1)) & 0xFFFFFFFF), 0, False)
        m = re.fullmatch(r'%(\d+)', ptr)
        if m and int(m.group(1)) < nparams:
            return ('A', int(m.group(1)), 0, False)
        d = defs.get(ptr)
        if d is None:
            return ('O', None, 0, False)
        if d.startswith('alloca'):
            return None
        m = GEP_RE.match(d)
        if m and d.startswith('getelementptr'):
            g = parse_gep_operands(m.group(1), T)
            if g:
                r = T.gep(g[0], g[2])
                if r:
                    b = resolve(g[1], depth + 1)
                    if b is None:
                        return None
                    return (b[0], b[1], b[2] + r[0], b[3] or bool(r[1]))
            return ('O', None, 0, True)
        m = re.match(r'inttoptr i32 (\S+) to ptr', d)
        if m:
            v = m.group(1)
            c = const_of(v)
            if c is not None:
                return ('G', '#%d' % (c & 0xFFFFFFFF), 0, False)
            dd = defs.get(v, '')
            mm = re.match(r'(?:add|or) (?:nuw )?(?:nsw )?(?:disjoint )?i32 (\S+), (-?\d+)$', dd)
            if mm:
                return ('O', None, int(mm.group(2)), True)
            return ('O', None, 0, True)
        if d.startswith('phi ptr') or d.startswith('select') or d.startswith('load'):
            return ('O', None, 0, False)
        return ('O', None, 0, False)

    acc = []
    for ln in lines:
        m = re.match(r'\s*(%[\w.$]+) = load (?:volatile )?([^,]+), ptr (.+?), align \d+', ln)
        if m:
            acc.append((m.group(1), m.group(2).strip(), m.group(3), 'L'))
            continue
        m = re.match(r'\s*store (?:volatile )?(\S+) (.+?), ptr (.+?), align \d+', ln)
        if m:
            acc.append((None, m.group(1), m.group(3), 'S'))
    # signedness of narrow loads from users
    users = collections.defaultdict(list)
    for ln in lines:
        for v in re.findall(r'%[\w.$]+', ln.split('=', 1)[1] if ' = ' in ln else ln):
            users[v].append(ln)
    WID = {'i8': 1, 'i16': 2, 'i32': 4, 'ptr': 4, 'float': 4, 'i64': 8, 'double': 8}
    out = []
    for dst, ty, ptr, dr in acc:
        w = WID.get(ty)
        if w is None:
            continue
        loc = resolve(ptr)
        if loc is None:
            continue
        sg = ''
        if dst and w in (1, 2):
            us = ' '.join(users.get(dst, []))
            if re.search(r'sext %s\b' % re.escape(dst), us) or re.search(r'icmp s[lg][te] i(8|16) %s\b' % re.escape(dst), us):
                sg = 's'
            elif re.search(r'zext (?:nneg )?%s\b' % re.escape(dst), us) or re.search(r'icmp u[lg][te] i(8|16) %s\b' % re.escape(dst), us):
                sg = 'u'
        kind, base, off, var = loc
        if kind == 'G':
            if base.startswith('#'):
                a = int(base[1:])
            elif base in syms:
                a = syms[base]
            else:
                kind = 'O'
        if kind == 'G':
            L = ('G', (a + off) & 0xFFFFFFFF, var)
        elif kind == 'A':
            L = ('A', base, off)
        else:
            L = ('O', off)
        if ty == 'float' or ty == 'double':
            sg = 'f'
        out.append((L, w, sg, dr, ptr.strip()[:60]))
    # strides
    strides = []
    for v, d in defs.items():
        if d.startswith('phi ptr'):
            for inc in re.findall(r'\[ (%[\w.$]+), %[\w.$]+ \]', d):
                g = defs.get(inc, '')
                m = GEP_RE.match(g)
                if m and g.startswith('getelementptr'):
                    pg = parse_gep_operands(m.group(1), T)
                    if pg and pg[1] == v:
                        r = T.gep(pg[0], pg[2])
                        if r and not r[1] and r[0]:
                            subs = set()
                            for w, dd in defs.items():
                                if dd.startswith('getelementptr') and w != inc:
                                    mm = GEP_RE.match(dd)
                                    q = parse_gep_operands(mm.group(1), T) if mm else None
                                    if q and q[1] == v:
                                        rr = T.gep(q[0], q[2])
                                        if rr and not rr[1] and rr[0]:
                                            subs.add(abs(rr[0]))
                            strides.append(('ptr', v, r[0], subs))
    for v, d in defs.items():
        if d.startswith('getelementptr'):
            m = GEP_RE.match(d)
            pg = parse_gep_operands(m.group(1), T) if m else None
            r = T.gep(pg[0], pg[2]) if pg else None
            if not r:
                continue
            for iv, sc in r[1]:
                k = 1
                src = defs.get(iv, '')
                mm = re.match(r'shl (?:nuw )?(?:nsw )?i32 (%[\w.$]+), (\d+)$', src)
                if mm:
                    iv, k = mm.group(1), 1 << int(mm.group(2))
                    src = defs.get(iv, '')
                if src.startswith('phi i32'):
                    for inc in re.findall(r'\[ (%[\w.$]+), %[\w.$]+ \]', src):
                        mm = re.match(r'add (?:nuw )?(?:nsw )?i32 %s, (-?\d+)$' % re.escape(iv), defs.get(inc, ''))
                        if mm and sc * k > 1:
                            strides.append(('idx', iv, int(mm.group(1)) * sc * k, set()))
    return out, strides


def scaled_raw(lines, body_src):
    """-O0 IR: GEP elem size>1 on a global, index = mul x, K / shl x, c; with the m2c `(.. * K) + &SYM` idiom."""
    defs = {}
    for ln in lines:
        m = re.match(r'\s*(%[\w.$]+) = (.*)$', ln)
        if m:
            defs[m.group(1)] = m.group(2)
    res = []
    for v, d in defs.items():
        if not d.startswith('getelementptr'):
            continue
        m = GEP_RE.match(d)
        pg = parse_gep_operands(m.group(1), T) if m else None
        if not pg or len(pg[2]) != 1:
            continue
        elem, base, idx = pg
        k = T.size_align(elem)[0]
        if k <= 1:
            continue
        iv = idx[0][1]
        src = defs.get(iv, '')
        mm = re.match(r'sext i\d+ (%[\w.$]+) to i32', src)
        if mm:
            src = defs.get(mm.group(1), '')
        K = None
        mm = re.match(r'mul (?:nuw )?(?:nsw )?i32 (\S+), (-?\d+)$', src) or re.match(r'mul (?:nuw )?(?:nsw )?i32 (-?\d+), (\S+)$', src)
        if mm:
            K = int(mm.group(2)) if re.fullmatch(r'-?\d+', mm.group(2)) else int(mm.group(1))
        mm = re.match(r'shl (?:nuw )?(?:nsw )?i32 \S+, (\d+)$', src)
        if mm:
            K = 1 << int(mm.group(1))
        if not K or K <= 1:
            continue
        sym = base[1:].strip('"') if base.startswith('@') else None
        kpat = r'(?:0x0*%X|0x0*%x|%d)\b' % (K, K, K)
        idiom = False
        if sym:
            s = re.escape(sym)
            if re.search(r'\*\s*' + kpat + r'\s*\)*\s*\+\s*\(?\s*&?\s*' + s + r'\b', body_src) or \
               re.search(r'&?\s*' + s + r'\s*\)?\s*\+\s*\(*[^;]*?\*\s*' + kpat, body_src):
                idiom = True
        else:
            if re.search(r'\*\s*' + kpat + r'\s*\)\s*\+\s*\(?\s*(arg\d|var_\w+|temp_\w+|sp\w+)\b(?!\s*\*)', body_src):
                idiom = 'local'
        res.append((sym or base, elem, k, K, idiom))
    return res

# ---------------------------------------------------------------- frame path


def frame_path():
    ev = set()
    files = glob.glob('port_work/p113/**/*.log', recursive=True) + glob.glob('port_work/p116/**/*.log', recursive=True) + \
        glob.glob('port_work/p116/**/*.out', recursive=True) + glob.glob('port_work/p116/**/prof.txt', recursive=True) + \
        ['docs/port/sessions/P113.md', 'docs/port/sessions/P116.md']
    for f in files:
        if os.path.isfile(f) and os.path.getsize(f) < 50e6:
            ev |= set(re.findall(r'func_[0-9A-F]{8}', open(f, errors='replace').read()))
    return ev


# ---------------------------------------------------------------- main
WN = {1: 'b', 2: 'h', 4: 'w', 8: 'd'}


def locs(L):
    if L[0] == 'G':
        return 'G:%08X%s' % (L[1], '+' if L[2] else '')
    if L[0] == 'A':
        return 'A%d:%d' % (L[1], L[2])
    return 'O:%d' % L[1]


def compare(name, aacc, iacc):
    rows = []
    # precise maps (G and A), and a pooled offset map over all non-global locations
    def maps(acc):
        P = collections.defaultdict(lambda: collections.defaultdict(list))
        Q = collections.defaultdict(lambda: collections.defaultdict(list))
        for L, w, sg, dr, x in acc:
            if L[0] == 'G':
                P[('G', L[1])][w].append((sg, dr, x))
            else:
                if L[0] == 'A':
                    P[L][w].append((sg, dr, x))
                Q[('O', L[-1])][w].append((sg, dr, x))
        return P, Q
    def tot(M, w):
        return sum(len(M[L].get(w, ())) for L in M)
    aP, aQ = maps(aacc)
    iP, iQ = maps(iacc)
    for level, A, I in (('P', aP, iP), ('Q', aQ, iQ)):
        for L in sorted(set(A) & set(I), key=str):
            aw, iw = set(A[L]), set(I[L])
            if aw == iw:
                # signedness
                for w in aw & {1, 2}:
                    asg = {s for s, d, x in A[L][w] if d == 'L' and s in 'su' and s}
                    isg = {s for s, d, x in I[L][w] if d == 'L' and s}
                    if asg and isg and not (asg & isg) and level == 'P':
                        rows.append(('sign', 'low', '%s %s: asm %s, IR %s' % (
                            'G:%08X' % L[1] if L[0] == 'G' else locs(L), WN[w], '/'.join(sorted(asg)), '/'.join(sorted(isg)))))
                continue
            ax, ix = aw - iw, iw - aw
            if not ax and not ix:
                continue
            # one side has a size the other lacks while the other has some size there
            narrow = any(w < 4 for w in ax | ix)
            if not narrow and not ({8} & (ax | ix)):
                continue
            disjoint = not (aw & iw)
            if (ax | ix) <= {4, 8}:
                # dword vs word: an 8-byte struct/double copy split into lw pairs (or memcpy folded to i64) -> low
                rows.append(('width', 'low', '%s asm{%s} IR{%s} (8 vs 4: copy?)' % (
                    'G:%08X' % L[1] if L[0] == 'G' else locs(L), ','.join(WN[w] for w in sorted(aw)),
                    ','.join(WN[w] for w in sorted(iw))), None))
                continue
            if level == 'P':
                conf = 'high' if disjoint else 'med'
            else:
                conf = 'med' if disjoint else 'low'
                # pooled offsets: raise when the function as a whole has fewer accesses of the exclusive narrow size
                if conf == 'low' and any(w < 4 and tot(I, w) < tot(A, w) for w in ax) or \
                        any(w < 4 and tot(A, w) < tot(I, w) for w in ix):
                    conf = 'med'
                # pooled offsets with no common access direction (asm only stores there, IR only loads, ...) are
                # usually two unrelated bases at the same offset
                adir = {d for w in aw for sg_, d, x in A[L][w]}
                idir = {d for w in iw for sg_, d, x in I[L][w]}
                if not (adir & idir):
                    conf = 'low'
                # asm loads bytes/halves here but the IR never loads that size anywhere in the function, and loads a
                # wider value at this offset (func_150337A8: `*(s32 *)p == -0xE` vs `lb`) -> high
                elif any(w < 4 and tot(I, w) < tot(A, w) and any(d == 'L' for sg_, d, x in A[L][w]) for w in ax) and not {w for w in iw if w < 4} and \
                        any(d == 'L' for w in iw if w > max(ax) for sg_, d, x in I[L][w]):
                    conf = 'high'
            if level == 'Q' and any(r[0] == 'width' and r[3] == L[1] for r in rows if len(r) > 3):
                continue
            Ls = 'G:%08X' % L[1] if L[0] == 'G' else locs(L)

            def desc(M, ws):
                return ','.join('%s%d%s' % (WN[w], len(M[w]), ''.join(sorted({d for s, d, x in M[w]}))) for w in sorted(ws))
            rows.append(('width', conf, '%s asm{%s} IR{%s}' % (Ls, desc(A[L], aw), desc(I[L], iw)),
                         L[1] if L[0] != 'G' else None))
    return [r[:3] for r in rows]


def main():
    ev = frame_path()
    # TU of each NM function: the .ll that defines it
    want = set(nmfuncs)
    if ONLY:
        want = {ONLY}
    results, n_scanned, missing_asm, missing_ir = [], 0, [], []
    seen = set()
    global T
    for tu in sorted(os.listdir(LLDIR)):
        if not tu.endswith('.c.ll'):
            continue
        raw = os.path.join(LLDIR, tu)
        with open(raw) as fh:
            txt = fh.read()
        names = [n for n in re.findall(r'^define [^@]*@"?([\w.$]+)"?\(', txt, re.M) if n in want and n not in seen]
        if not names:
            continue
        o = run_opt(tu)
        if not o:
            continue
        ofun, ostructs = functions(o)
        rfun, rstructs = functions(raw)
        T = Types(dict(rstructs, **ostructs))
        for n in names:
            seen.add(n)
            if n not in ofun:
                missing_ir.append(n); continue
            if n not in asm:
                missing_asm.append(n); continue
            n_scanned += 1
            file, body = nmfuncs[n]
            np_, lines = ofun[n]
            iacc, istr = ir_facts(lines, np_, T)
            aacc, asteps, aeff, acoef = asm_facts(n)
            rows = compare(n, aacc, iacc)
            # strides
            unroll = asteps[1]
            for kind, v, S, subs in istr:
                a = abs(S)
                if a in aeff or (kind == 'idx' and a in acoef) or a <= 1:
                    continue
                # unrolled loop: the asm steps one register m times by c, the IR folded them into one m*c step and
                # still addresses the intermediate elements at c multiples off the phi
                if any(a % c == 0 and a // c <= m and any(x % c == 0 for x in subs) for c, m in unroll.items() if c > 1):
                    continue
                rel = [s for s in aeff if s and (a == 4 * s or a == 2 * s or a == 8 * s or 4 * a == s or 2 * a == s)]
                conf = ('high' if rel else 'med') if kind == 'ptr' else 'low'  # idx steps: IDO unroll/index forms, noisy
                rows.append(('stride', conf, 'IR %s %s step %d, asm self-steps {%s}' % (
                    kind, v, S, ','.join(str(x) for x in sorted(aeff)[:8]))))
            # scaled index (m2c byte idiom)
            if n in rfun:
                for sym, elem, k, K, idiom in scaled_raw(rfun[n][1], body):
                    sc = acoef | aeff
                    ev_ = 'asm has %s%s' % ('x%d ' % K if K in sc else '', 'x%d' % (K * k) if K * k in sc else '') \
                        if (K in sc or K * k in sc) else 'asm scale unseen'
                    if K * k in sc and K not in sc:
                        conf = None          # the asm builds the C's byte scale: C is right
                    elif K in sc and K * k not in sc:
                        conf = 'high'
                    else:
                        conf = 'med' if idiom is True else 'low'
                    if conf and idiom is True:
                        rows.append(('scaled', conf, '(x*%d)+&%s on %s (size %d): byte scale %d, m2c meant %d; %s' % (K, sym, elem, k, K * k, K, ev_)))
                    elif conf and idiom == 'local':
                        rows.append(('scaled', conf, '(x*%d)+ptr %s on %s (size %d): byte scale %d; %s' % (K, sym, elem, k, K * k, ev_)))
            path = 2 if n in ev else 0
            rows = list(dict.fromkeys(rows))
            for kind, conf, det in rows:
                results.append((n, file, kind, conf, path, det))
    # path 1: direct C callees/callers of evidenced functions
    calls = {}
    for n, (f, body) in nmfuncs.items():
        calls[n] = set(re.findall(r'\bfunc_[0-9A-F]{8}\b', body)) - {n}
    near = set()
    for n, cs in calls.items():
        if n in ev or cs & ev:
            near.add(n)
    for f in ev:
        near |= calls.get(f, set())
    CONF = {'high': 3, 'med': 2, 'low': 1}
    KORD = {'scaled': 0, 'stride': 1, 'width': 2, 'sign': 3}
    res = []
    for n, file, kind, conf, path, det in results:
        if path == 0 and n in near:
            path = 1
        res.append((n, file, kind, conf, path, det))
    # pooled-offset width rows (O:) rank half a level below the located ones (G:/A:, scaled, ptr stride)
    res.sort(key=lambda r: (-CONF[r[3]] + (0.5 if r[2] == 'width' and r[5].startswith('O:') else 0), -r[4],
                            KORD[r[2]], r[0], r[5]))
    os.makedirs(os.path.dirname(OUT) or '.', exist_ok=True)
    with open(OUT, 'w') as fh:
        fh.write('function\tfile\tkind\tconf\tpath\tdetail\n')
        for r in res:
            fh.write('%s\t%s\t%s\t%s\t%d\t%s\n' % r)
    by = collections.Counter((r[2], r[3]) for r in res)
    funcs = collections.Counter()
    for r in res:
        funcs[r[3]] += 0
    fset = {c: len({r[0] for r in res if r[3] == c}) for c in CONF}
    print('NM functions in source: %d; scanned (IR+asm): %d; no IR: %d; no asm: %d' % (
        len(nmfuncs), n_scanned, len(missing_ir) + len(want - seen), len(missing_asm)))
    print('rows: %d  %s' % (len(res), ' '.join('%s/%s=%d' % (k, c, v) for (k, c), v in sorted(by.items()))))
    print('functions with a row, by best confidence: ' + ' '.join('%s=%d' % (c, fset[c]) for c in CONF))
    for r in res[:TOP] if '--all' not in args else res:
        print('\t'.join(str(x) for x in r))


main()
