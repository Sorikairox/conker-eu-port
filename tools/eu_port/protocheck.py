#!/usr/bin/env python3
"""Prototype checker (host side, repo at ~/conker).

usage: protocheck.py [--all] [--func F ...]        report (compact)
       protocheck.py --apply [--strong] [--max N] [--dry] [--func F ...]
                                                    try fixes one prototype at a time
       protocheck.py --sig F                        show what is known about one function

Report kinds (one line each, `kind func where: detail`):
  DEF    a function defined in C whose prototype elsewhere (functions.h / another C file)
         differs from the definition (MAJOR: count, narrow ints, floats, void; minor: s32/u32/ptr)
  ASM    a function still in GLOBAL_ASM whose prototype contradicts its .s / its asm callers:
         ret      void prototype, but the function leaves a value in $v0/$f0 that it never reads
                  itself, or asm callers read $v0/$f0 after the call
         retvoid  non-void prototype, but no exit path sets $v0/$f0 and no asm caller reads it (weak)
         narrow   the prologue re-truncates $aN (andi 0xFF/0xFFFF, sll/sra 24/16 written back to $aN),
                  or a stack/home slot is read with lbu/lb/lhu/lh at the low bytes
         wide     prototype says u8/s8/u16/s16, the function reads $aN untruncated (weak)
         count    the function reads more argument registers/stack args than the prototype has
         float    $f12/$f14 are live-in (float args) but the prototype puts an int there, or the
                  reverse
--apply: each candidate rewrites one one-line prototype; the objects of every C file that
mentions the function are rebuilt in conkerdev and checked with check_files.py; the change is
kept only if every one of them still matches (compile errors count as failure).
Applied/rejected lines go to tools/eu_port/protocheck.log.
"""
import os, re, sys, glob, subprocess, collections
import sys as _gsys
def _conker_guard():
    # refuse to run on a checkout other than CONKER_ROOT (e.g. a worktree shell without the wt.sh env)
    import os as _o, subprocess as _s
    if _o.path.exists("/.dockerenv"):
        return  # inside a build container: paths are /conker, not the host checkout
    try:
        top = _s.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()
    except Exception:
        return
    root = _o.path.realpath(_o.path.expanduser(_o.environ.get("CONKER_ROOT", "~/conker")))
    if top and _o.path.realpath(top) != root:
        _gsys.stderr.write("refusing: cwd repo %s != CONKER_ROOT %s (eval the wt.sh env)\n" % (top, root))
        _gsys.exit(3)
_conker_guard()

R = os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/conker')
SRC = R + '/src_eu'
ASM = R + '/asm/nonmatchings'
LOG = os.path.expanduser(os.environ.get('CONKER_ROOT','~/conker')+'/tools/eu_port/protocheck.log')
DOCKER = '/Applications/Docker.app/Contents/Resources/bin/docker'

# ---------------------------------------------------------------- C parsing
def strip_comments(s):
    out, i, n = [], 0, len(s)
    while i < n:
        c = s[i]
        if s.startswith('/*', i):
            j = s.find('*/', i + 2); j = n if j < 0 else j + 2
            out.append('\n' * s.count('\n', i, j)); i = j
        elif s.startswith('//', i):
            j = s.find('\n', i); i = n if j < 0 else j
        elif c in '"\'':
            j = i + 1
            while j < n and s[j] != c:
                j += 2 if s[j] == '\\' else 1
            out.append(s[i:j + 1]); i = j + 1
        else:
            out.append(c); i += 1
    return ''.join(out)

def strip_pp(s):
    """drop #if 0 blocks and all preprocessor lines (keeps line count)."""
    lines, out, skip = s.split('\n'), [], 0
    for l in lines:
        t = l.strip()
        if skip:
            if re.match(r'#\s*if', t): skip += 1
            elif re.match(r'#\s*endif', t): skip -= 1
            out.append(''); continue
        if re.match(r'#\s*if\s+0\b', t): skip = 1; out.append(''); continue
        out.append('' if t.startswith('#') else l)
    return '\n'.join(out)

KW = {'int', 'char', 'short', 'long', 'float', 'double', 'unsigned', 'signed', 'void'}
QUAL = {'extern', 'static', 'inline', 'const', 'volatile', 'register', '__inline'}
BASE = {'int': 'i32', 'signed int': 'i32', 'long': 'i32', 'long int': 'i32', 'signed long': 'i32',
        'signed': 'i32', 'unsigned int': 'u32', 'unsigned': 'u32', 'unsigned long': 'u32',
        'unsigned long int': 'u32', 'short': 's16', 'signed short': 's16', 'short int': 's16',
        'unsigned short': 'u16', 'unsigned short int': 'u16', 'char': 'u8', 'unsigned char': 'u8',
        'signed char': 's8', 'float': 'f32', 'double': 'f64', 'void': 'void', 'long long': 'i64',
        'signed long long': 'i64', 'unsigned long long': 'u64'}

def load_typedefs():
    td = {}
    files = glob.glob(R + '/include/**/*.h', recursive=True)
    for p in files:
        s = strip_pp(strip_comments(open(p, errors='replace').read()))
        for m in re.finditer(r'typedef\s+([\w\s]+?)\s*(\*?)\s*(\w+)\s*;', s):
            b, star, name = m.group(1).split(), m.group(2), m.group(3)
            b = [x for x in b if x not in QUAL]
            if star: td[name] = 'ptr'
            elif b and b[0] in ('struct', 'union'): td[name] = 'struct'
            elif b and b[0] == 'enum': td[name] = 'i32'
            else: td[name] = ' '.join(b)
        for m in re.finditer(r'typedef\s+(?:struct|union)\s*\w*\s*\{', s):   # typedef struct {...} X;
            d, j = 0, m.end() - 1
            while j < len(s):
                d += {'{': 1, '}': -1}.get(s[j], 0); j += 1
                if d == 0: break
            m2 = re.match(r'\s*(\*?)\s*(\w+)', s[j:])
            if m2: td[m2.group(2)] = 'ptr' if m2.group(1) else 'struct'
        for m in re.finditer(r'typedef\s+[^;()]*\(\s*\*\s*(\w+)\s*\)', s):   # function pointer types
            td[m.group(1)] = 'ptr'
    return td

TD = None
def tclass(t):
    """normalised codegen class of a type string (param name already removed)."""
    global TD
    if TD is None: TD = load_typedefs()
    if '*' in t or '[' in t or '(' in t: return 'ptr'
    w = [x for x in re.findall(r'\w+', t) if x not in QUAL]
    if not w: return '?'
    if w[0] in ('struct', 'union'): return 'struct'
    if w[0] == 'enum': return 'i32'
    k = ' '.join(w)
    for _ in range(8):
        if k in BASE: return BASE[k]
        if k in ('ptr', 'struct'): return k
        if k in TD: k = TD[k]; continue
        if len(w) == 1 and k.startswith('struct'): return 'struct'
        return 'T:' + k
    return 'T:' + k

def split_top(s, sep=','):
    out, d, cur = [], 0, ''
    for c in s:
        if c in '([{': d += 1
        elif c in ')]}': d -= 1
        if c == sep and d == 0: out.append(cur); cur = ''
        else: cur += c
    if cur.strip(): out.append(cur)
    return out

def parse_param(p):
    """-> (type string, name or None)"""
    p = p.strip()
    m = re.match(r'(.*\(\s*\*\s*)(\w+)(\s*\).*)', p)          # function pointer param
    if m: return m.group(1) + m.group(3), m.group(2)
    arr = ''
    m = re.match(r'(.*?)(\s*\[[^\]]*\])+$', p)
    if m: p, arr = m.group(1), '[]'
    toks = re.findall(r'\w+|\*', p)
    if len(toks) >= 2 and re.match(r'\w+$', toks[-1]) and toks[-1] not in KW | QUAL:
        rest = [t for t in toks[:-1] if t not in QUAL]
        if rest and rest != ['struct'] and rest != ['union'] and rest != ['enum']:
            nm = toks[-1]
            return p[:p.rfind(nm)].strip() + arr, nm
    return p + arr, None

class Sig:
    def __init__(self, ret, params, text, where, line, kind):
        self.ret, self.params, self.text, self.where, self.line, self.kind = ret, params, text, where, line, kind
        # params: list of (type, name) ; None = unspecified (old style "()")
    def classes(self):
        if self.params is None: return None
        return [tclass(t) for t, n in self.params]
    def rclass(self): return tclass(self.ret)
    def fmt(self):
        if self.params is None: return '%s()' % self.rclass()
        return '%s(%s)' % (self.rclass(), ','.join(self.classes()) or 'void')

FDECL = re.compile(r'^(?P<ret>[\w\s\*]*?[\w\*])\s*\b(?P<name>\w+)\s*\((?P<params>.*)\)\s*$', re.S)

def scan_c(path, text=None):
    """-> (defs, protos, pragma funcs) for one C file. Line numbers are 1-based."""
    raw = open(path, errors='replace').read() if text is None else text
    prag = re.findall(r'#pragma\s+GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', raw)
    s = strip_pp(strip_comments(raw))
    defs, protos = [], []
    i, n, d, start = 0, len(s), 0, 0
    while i < n:
        c = s[i]
        if c == '{' and d == 0:
            head = s[start:i]
            j, dd = i, 0
            while j < n:
                if s[j] == '{': dd += 1
                elif s[j] == '}':
                    dd -= 1
                    if dd == 0: break
                j += 1
            m = FDECL.match(head.strip())
            if m and '=' not in head and not re.search(r'\b(struct|union|enum|typedef)\s*\w*\s*$', head.strip()):
                sig = mk_sig(m, head.strip(), path, s.count('\n', 0, start + len(head) - len(head.lstrip())) + 1, 'def')
                if sig: defs.append((m.group('name'), sig))
            i = j + 1
            # a struct/union body: continue the declaration up to ';'
            if re.search(r'\b(struct|union|enum)\b[^;(]*$', head) or '=' in head:
                k = s.find(';', i); i = n if k < 0 else k + 1
            start = i
            continue
        if c == ';':
            head = s[start:i].strip()
            m = FDECL.match(head)
            if m and '=' not in head and not head.startswith('typedef') and m.group('name') not in ('if', 'while'):
                ln = s.count('\n', 0, start + len(s[start:i]) - len(s[start:i].lstrip())) + 1
                sig = mk_sig(m, head, path, ln, 'proto')
                if sig: protos.append((m.group('name'), sig))
            start = i + 1
        i += 1
    return defs, protos, prag

def mk_sig(m, head, path, line, kind):
    ret = ' '.join(x for x in m.group('ret').split() if x not in ('extern', 'static', 'inline'))
    if ret in ('', 'return', 'else') or m.group('name') in KW: return None
    ps = m.group('params').strip()
    if ps == '': params = None
    elif ps == 'void': params = []
    else:
        params = [parse_param(p) for p in split_top(ps)]
        if any(t.strip() == '...' for t, n in params): return None
    return Sig(ret, params, head, path, line, kind)

def collect():
    """defs {f: Sig}, protos {f: [Sig]}, asmfuncs {f: stem}, mentions {f: set(c files)}"""
    defs, protos, asmf = {}, collections.defaultdict(list), {}
    files = sorted(glob.glob(SRC + '/**/*.c', recursive=True))
    for p in files:
        d, pr, prag = scan_c(p)
        for f, s in d: defs[f] = s
        for f, s in pr: protos[f].append(s)
        stem = os.path.relpath(p, SRC)[:-2]
        for f in prag: asmf[f] = stem
    for h in ['functions.h', 'variables.h', 'structs.h']:
        d, pr, _ = scan_c(R + '/include/' + h)
        for f, s in pr: protos[f].append(s)
    return defs, protos, asmf, files

# ---------------------------------------------------------------- asm analysis
INS = re.compile(r'/\*\s+[0-9A-F]+\s+[0-9A-F]+\s+[0-9A-F]{8}\s+\*/\s+(\S+)\s*(.*)')
LAB = re.compile(r'^\s*(\.L\w+|\w+):\s*$|^\s*(?:glabel|jlabel|dlabel)\s+(\w+)')
REG = re.compile(r'\$(\w+)')
STORES = {'sb', 'sh', 'sw', 'swl', 'swr', 'swc1', 'sdc1', 'sd'}
CALLER_SAVED = ['v0', 'v1', 'a0', 'a1', 'a2', 'a3', 'at'] + ['t%d' % i for i in range(10)] + ['f%d' % i for i in range(20)]

def parse_s(path):
    ins, labels = [], {}
    for l in open(path):
        m = LAB.match(l)
        if m: labels[m.group(1) or m.group(2)] = len(ins); continue
        m = INS.search(l)
        if m:
            ops = [x.strip() for x in split_top(m.group(2))] if m.group(2).strip() else []
            ins.append((m.group(1), ops))
    return ins, labels

def regs_of(op):
    return REG.findall(op)

def defuse(op, ops):
    """-> (defs, uses) register names without $ ; doubles expand to pairs."""
    rs = [regs_of(o) for o in ops]
    flat = [r for x in rs for r in x]
    dbl = '.d' in op and not op.startswith('cvt.s.') and not op.startswith('cvt.w.')
    def pair(rr, d):
        out = []
        for r in rr:
            out.append(r)
            if d and re.match(r'f\d+$', r): out.append('f%d' % (int(r[1:]) + 1))
        return out
    if op in STORES or op.startswith('b') or op in ('jr', 'jalr', 'mult', 'multu', 'div', 'divu', 'mtlo', 'mthi', 'teq', 'tne', 'break') \
            or op.startswith('c.'):
        uses = flat
        if op == 'sdc1': uses = pair(rs[0], True) + rs[1] if len(rs) > 1 else flat
        if op.startswith('c.') and op.endswith('.d'): uses = pair(flat, True)
        return [], uses
    if op in ('mtc1', 'ctc1', 'dmtc1'): return (rs[1] if len(rs) > 1 else []), rs[0]
    if op in ('mfc1', 'cfc1'): return rs[0], (rs[1] if len(rs) > 1 else [])
    if op in ('mflo', 'mfhi', 'lui'): return flat[:1], []
    if op in ('ldc1',): return pair(rs[0], True), rs[1] if len(rs) > 1 else []
    if op == 'nop' or not ops: return [], []
    if op.startswith('cvt.'):   # cvt.d.s f0, f12: dest double if .d. first
        dd = op.startswith('cvt.d.'); sd = op.endswith('.d')
        return pair(rs[0], dd), pair(rs[1], sd) if len(rs) > 1 else []
    d0 = rs[0]
    return pair(d0, dbl), pair([r for x in rs[1:] for r in x], dbl)

class FuncInfo:
    pass

def analyse(path):
    ins, labels = parse_s(path)
    N = len(ins)
    if any(op in ('eret', 'mtc0', 'mfc0', 'cache', 'syscall') for op, ops in ins): return None   # hand-written asm
    fi = FuncInfo(); fi.calls = []; fi.livein = set(); fi.exit_v0 = set(); fi.exit_f0 = set()
    fi.used_ret = collections.defaultdict(set)   # target -> {'v0','f0','v1'}
    fi.callargs = collections.defaultdict(list)  # target -> list of sets of arg regs/slots written
    fi.trunc = {}; fi.narrowload = {}; fi.wideslot = set(); fi.dblin = set(); fi.untrunc_read = set()
    frame = 0
    for op, ops in ins[:3]:
        if op == 'addiu' and ops[:2] == ['$sp', '$sp'] and ops[2].startswith('-'):
            frame = int(ops[2][1:], 0)
    fi.frame = frame
    # successors
    def tgt(o):
        return labels.get(o.strip())
    succ = [[] for _ in range(N + 1)]   # node N = exit
    callnode = {}
    for i, (op, ops) in enumerate(ins):
        nxt = i + 1
        if op in ('jal', 'jalr'):
            succ[i] = [i + 1] if i + 1 < N else [N]
            callnode[i + 1] = (ops[-1] if op == 'jal' else '?')
            continue
        isbr = op.startswith('b') and op not in ('break',)
        if isbr or op in ('j', 'jr'):
            likely = op.endswith('l') and op not in ('bal',) and isbr and op not in ('b',)
            if op == 'jr':
                t = [N] if ops == ['$ra'] else sorted(set(labels.values()))
            else:
                t = [tgt(ops[-1])] if tgt(ops[-1]) is not None else []
            uncond = op in ('b', 'j', 'jr')
            fall = [] if uncond else [i + 2 if i + 2 < N else N]
            if likely:
                succ[i] = [i + 1] + fall; succ_delay = t
            else:
                succ[i] = [i + 1]; succ_delay = t + fall
            if i + 1 < N: ins[i + 1] = ins[i + 1]   # delay slot
            succ.__setitem__(i + 1, succ_delay) if i + 1 < N else None
            continue
        if succ[i]: continue                     # already set as a delay slot
        succ[i] = [nxt if nxt < N else N]
    # delay slots of branches were set above; make sure we didn't overwrite them
    # (we process in order: a delay slot's own entry is set before reaching it, and the
    #  `if succ[i]: continue` keeps it)
    TR = ['a0', 'a1', 'a2', 'a3', 'v0', 'v1', 'f0', 'f12', 'f13', 'f14', 'f15']
    # state: dict reg -> frozenset(tags); tags: 'E' entry, 'W' own write unread, 'R' own write read,
    #        ('C',t) call result unread, ('D',t) call result read, 'X' clobbered by call
    init = {r: frozenset(['E']) for r in TR}
    for k in range(4, 12): init['s%d' % k] = frozenset()   # outgoing stack slots 0x10+4(k-4)
    states = [None] * (N + 1)
    states[0] = init
    work = [0]
    def merge(a, b):
        if a is None: return dict(b)
        ch = False; out = dict(a)
        for k, v in b.items():
            u = out.get(k, frozenset()) | v
            if u != out.get(k): out[k] = u; ch = True
        return out if ch else None
    early = 6   # prologue window for truncation detection
    while work:
        i = work.pop()
        st = dict(states[i])
        if i == N:
            continue
        op, ops = ins[i]
        dfs, uses = defuse(op, ops)
        # reads
        for r in uses:
            if r in st:
                tags = st[r]
                if 'E' in tags:
                    fi.livein.add(r)
                    if r.startswith('a') and op not in STORES and not (op in ('andi', 'sll') and i < 12):
                        fi.untrunc_read.add(r)
                    if r in ('f12', 'f14') and ('.d' in op or op == 'sdc1'): fi.dblin.add(r)
                nt = set()
                for t in tags:
                    if t == 'W': nt.add('R')
                    elif isinstance(t, tuple) and t[0] == 'C':
                        fi.used_ret[t[1]].add(r); nt.add(('D', t[1]))
                    else: nt.add(t)
                st[r] = frozenset(nt)
        # stack loads / stores
        if ops and re.match(r'-?(0x[0-9A-Fa-f]+|\d+)\(\$sp\)$', ops[-1]):
            off = int(ops[-1].split('(')[0], 0)
            if op in STORES and 0x10 <= off < 0x30 and frame:
                st['s%d' % (4 + (off - 0x10) // 4)] = frozenset(['W'])
            if op[0] == 'l' and off >= frame and frame:
                k, b = (off - frame) // 4, (off - frame) % 4
                if op in ('lbu', 'lb', 'lhu', 'lh') and ((op[1] == 'b' and b == 3) or (op[1] == 'h' and b == 2)):
                    fi.narrowload.setdefault(k, set()).add({'lbu': 'u8', 'lb': 's8', 'lhu': 'u16', 'lh': 's16'}[op])
                if op in ('lw', 'lwc1'): fi.wideslot.add(k)
                if k >= 4: fi.livein.add('stk%d' % k)
            elif op[0] == 'l' and off >= 0x10 and not frame:
                k = off // 4
                if k >= 4: fi.livein.add('stk%d' % k)
                if op in ('lw', 'lwc1'): fi.wideslot.add(k)
                b = off % 4
                if op in ('lbu', 'lb', 'lhu', 'lh') and ((op[1] == 'b' and b == 3) or (op[1] == 'h' and b == 2)):
                    fi.narrowload.setdefault(k, set()).add({'lbu': 'u8', 'lb': 's8', 'lhu': 'u16', 'lh': 's16'}[op])
        # truncation patterns on entry values
        if i < 16 and op in ('andi', 'sll') and len(ops) == 3:
            src = ops[1].lstrip('$')
            if re.match(r'a[0-3]$', src) and states[i].get(src) == frozenset(['E']):
                n = int(src[1])
                if op == 'andi' and ops[2] in ('0xFF', '0xFFFF'):
                    ty = 'u8' if ops[2] == '0xFF' else 'u16'
                    dst = ops[0].lstrip('$')
                    if dst == src: fi.trunc[n] = ty
                    else:
                        for op2, b in ins[i + 1:i + 10]:
                            if op2 == 'or' and b == ['$' + src, '$' + dst, '$zero']: fi.trunc[n] = ty
                elif op == 'sll' and ops[2] in ('24', '16', '0x18', '0x10'):
                    sh = ops[2]; dst = ops[0]
                    ty = 's8' if int(sh, 0) == 24 else 's16'
                    for op2, b in ins[i + 1:i + 6]:
                        if op2 == 'sra' and b[1] == dst and b[2] == sh:
                            if b[0] == '$' + src: fi.trunc[n] = ty
                            else:
                                for op3, c in ins[i + 1:i + 10]:
                                    if op3 == 'or' and c == ['$' + src, b[0], '$zero']: fi.trunc[n] = ty
                            break
        for r in dfs:
            if r in st: st[r] = frozenset(['W'])
        if i in callnode:
            t = callnode[i]
            wr = set(r for r in ('a0', 'a1', 'a2', 'a3') if 'W' in st[r] or 'R' in st[r])
            wr |= set(r for r in st if r.startswith('s') and 'W' in st[r])
            fi.calls.append(t); fi.callargs[t].append(wr)
            for r in TR:
                st[r] = frozenset([('C', t)]) if r in ('v0', 'v1', 'f0') else frozenset(['X'])
            for k in range(4, 12): st['s%d' % k] = frozenset()
        for j in succ[i]:
            if j is None: continue
            m = merge(states[j], st)
            if m is not None:
                states[j] = m; work.append(j)
    if states[N]:
        fi.exit_v0 = states[N]['v0']; fi.exit_f0 = states[N]['f0']
    return fi

# ---------------------------------------------------------------- evidence vs prototype
def expected_regs(classes):
    """O32 assignment -> list of (reg or stkK) per param."""
    out, slot, allf = [], 0, True
    for i, c in enumerate(classes):
        if c in ('f64', 'i64', 'u64') and slot % 2: slot += 1
        if c in ('f32', 'f64') and allf and i < 2:
            out.append('f%d' % (12 + 2 * i))
        else:
            out.append('a%d' % slot if slot < 4 else 'stk%d' % slot)
        if c not in ('f32', 'f64'): allf = False
        slot += 2 if c in ('f64', 'i64', 'u64') else 1
    return out

NARROW = {'u8', 's8', 'u16', 's16'}
INTISH = {'i32', 'u32', 'ptr', 'struct'}

def asm_evidence(f, fi, sig, callers_used, callers_args):
    """-> list of (kind, strength, detail, suggestion dict)"""
    res = []
    cl = sig.classes()
    rc = sig.rclass()
    w_v0 = 'W' in fi.exit_v0
    w_f0 = 'W' in fi.exit_f0
    used = callers_used
    if rc == 'void':
        if w_f0 or 'f0' in used:
            res.append(('ret', 'strong', 'f0 set at exit' if w_f0 else 'callers read f0', {'ret': 'f32'}))
        elif w_v0 or 'v0' in used:
            res.append(('ret', 'strong', ('v0 set at exit' if w_v0 else '') + (' callers read v0' if 'v0' in used else ''), {'ret': 's32'}))
    elif rc in ('f32', 'f64'):
        if w_v0 and not w_f0 and not any(isinstance(t, tuple) for t in fi.exit_f0):
            res.append(('ret', 'strong', 'float proto but v0 set, f0 not', {'ret': 's32'}))
    else:
        if w_f0 and not w_v0:
            res.append(('ret', 'strong', 'int proto but f0 set at exit', {'ret': 'f32'}))
        elif fi.exit_v0 and fi.exit_v0 <= {'E'} and not w_f0 and 'v0' not in used:
            res.append(('retvoid', 'weak', 'no v0 at exit, no asm caller reads it', {'ret': 'void'}))
    if cl is None: return res
    exp = expected_regs(cl)
    # count / float
    argregs = ['a0', 'a1', 'a2', 'a3', 'f12', 'f14']
    live = set(r for r in fi.livein if r in argregs or r.startswith('stk'))
    # a0-a3 that are live-in only because a double/float arg occupies them are fine when expected
    unexpected = sorted(r for r in live if r not in exp)
    # f13/f15 pairs
    if unexpected:
        flt = [r for r in unexpected if r.startswith('f')]
        ints = [r for r in unexpected if not r.startswith('f')]
        if flt:
            res.append(('float', 'strong', 'live-in %s, proto regs %s' % (','.join(flt), ','.join(exp)), {'float': flt}))
        if ints:
            def idx(r): return int(r[1:]) if r[0] == 'a' else int(r[3:])
            n = max(idx(r) for r in ints) + 1
            if n > len(cl) and not flt:
                res.append(('count', 'strong', 'reads %s, proto has %d params' % (','.join(ints), len(cl)), {'count': n}))
            elif not flt:
                res.append(('float', 'strong', 'live-in %s, proto regs %s' % (','.join(ints), ','.join(exp)), {}))
    # caller arg counts (writes of a-regs / out slots unread at the call)
    # narrow params
    for n, ty in fi.trunc.items():
        if n < len(cl) and exp[n] == 'a%d' % n and cl[n] != ty:
            res.append(('narrow', 'strong', 'a%d re-truncated as %s, proto %s' % (n, ty, cl[n]), {'param': (n, ty)}))
    for k, tys in fi.narrowload.items():
        if len(tys) == 1 and k < len(cl):
            ty = next(iter(tys))
            if cl[k] in INTISH and cl[k] != 'ptr' and k not in fi.trunc and k not in fi.wideslot \
                    and 'a%d' % k not in fi.untrunc_read:
                res.append(('narrow', 'strong', 'arg slot %d read as %s, proto %s' % (k, ty, cl[k]), {'param': (k, ty)}))
    for n, c in enumerate(cl):
        if c in NARROW and n < 4 and exp[n] == 'a%d' % n and n not in fi.trunc and 'a%d' % n in fi.untrunc_read \
                and n not in fi.narrowload:
            res.append(('wide', 'weak', 'a%d read untruncated, proto %s' % (n, c), {'param': (n, 's32')}))
    return res

# ---------------------------------------------------------------- prototype rewriting
CT = {'s32': 's32', 'f32': 'f32', 'void': 'void', 'u8': 'u8', 's8': 's8', 'u16': 'u16', 's16': 's16'}

def rewrite(sig, sug, f):
    """new one-line prototype text or None"""
    params = list(sig.params) if sig.params is not None else None
    ret = sig.ret
    if 'ret' in sug: ret = CT[sug['ret']]
    if 'param' in sug:
        n, ty = sug['param']
        t, nm = params[n]
        params[n] = (ty, nm)
    if 'count' in sug:
        while len(params) < sug['count']:
            params.append(('s32', 'arg%d' % len(params) if all(p[1] for p in params) else None))
    if 'float' in sug and sug['float']:
        # f12 -> param0 float, f14 -> param1 float (O32 only when param0 is float too)
        for r in sug['float']:
            n = 0 if r == 'f12' else 1
            while len(params) <= n: params.append(('s32', None))
            t, nm = params[n]; params[n] = ('f32', nm)
    if 'def' in sug:
        # keep the prototype's own type text where the codegen class agrees; take the
        # definition's where it differs (basic types only; other pointers -> void *)
        d = sug['def']
        def pick(pt, dt):
            pc, dc = (tclass(pt) if pt is not None else None), tclass(dt)
            if pc is not None and (pc == dc or (pc in INTISH and dc in INTISH)): return pt
            if dc == 'ptr' and not re.fullmatch(r'\s*(void|u8|s8|u16|s16|s32|u32|f32|f64|char|int)\s*\*+\s*', dt): return 'void *'
            if dc.startswith('T:') or dc == 'struct': return None
            return dt
        r = pick(sig.ret, d.ret)
        if r is None: return None
        ret = r
        if d.params is None: params = None
        else:
            named = sig.params is not None and any(nm for t, nm in sig.params)
            params = []
            for i, (dt, dn) in enumerate(d.params):
                pt = sig.params[i][0] if sig.params is not None and i < len(sig.params) else None
                t = pick(pt, dt)
                if t is None: return None
                nm = (sig.params[i][1] if sig.params is not None and i < len(sig.params) else None) or ('arg%d' % i if named else None)
                params.append((t, nm))
    def fp(t, nm):
        if nm is None: return t
        m = re.match(r'(.*\(\s*\*\s*)(\s*\).*)', t)
        if m: return m.group(1) + nm + m.group(2)
        if t.endswith('[]'): return '%s %s[]' % (t[:-2].strip(), nm)
        return '%s %s' % (t, nm) if not t.endswith('*') else t + nm
    ps = 'void' if params == [] else '' if params is None else ', '.join(fp(t, nm) for t, nm in params)
    return '%s %s(%s);' % (ret.strip(), f, ps)

def proto_line(sig):
    """(path, lineno, full line) when the prototype is a one-liner we can rewrite"""
    lines = open(sig.where).read().split('\n')
    ln = sig.line - 1
    if ln < 0 or ln >= len(lines): return None
    l = lines[ln]
    name = re.search(r'\b(\w+)\s*\(', sig.text)
    if not name or not re.search(r'\b%s\s*\(' % name.group(1), l) or not l.rstrip().endswith(';'): return None
    if l.count(';') != 1: return None
    return sig.where, ln, l

# ---------------------------------------------------------------- main report
def build_all(only=None):
    defs, protos, asmf, files = collect()
    infos = {}
    for f, stem in asmf.items():
        p = '%s/%s/%s.s' % (ASM, stem, f)
        if os.path.exists(p):
            try:
                fi = analyse(p)
                if fi: infos[f] = fi
            except Exception as e: print('ERR', f, e, file=sys.stderr)
    used = collections.defaultdict(set); cargs = collections.defaultdict(list)
    for f, fi in infos.items():
        for t, rs in fi.used_ret.items(): used[t] |= rs
        for t, l in fi.callargs.items(): cargs[t] += l
    return defs, protos, asmf, files, infos, used, cargs

def findings(only=None, include_minor=False):
    defs, protos, asmf, files, infos, used, cargs = build_all()
    out = []
    for f, ds in sorted(defs.items()):
        if only and f not in only: continue
        if f in asmf: continue
        dc, dr = ds.classes(), ds.rclass()
        for p in protos.get(f, []):
            pc, pr = p.classes(), p.rclass()
            if pc is None or dc is None:
                continue
            if pc == dc and pr == dr: continue
            major = len(pc) != len(dc) or any(a != b and not (a in INTISH and b in INTISH) and not (a.startswith('T:') or b.startswith('T:'))
                                              for a, b in zip(pc, dc)) or (pr != dr and not (pr in INTISH and dr in INTISH))
            if not major and not include_minor: continue
            out.append(dict(kind='DEF', f=f, sig=p, strength='strong' if major else 'minor',
                            detail='def %s %s:%d, proto %s' % (ds.fmt(), os.path.relpath(ds.where, R), ds.line, p.fmt()),
                            sug={'def': ds}))
    for f, fi in sorted(infos.items()):
        if only and f not in only: continue
        for p in protos.get(f, []):
            for kind, strength, detail, sug in asm_evidence(f, fi, p, used.get(f, set()), cargs.get(f, [])):
                out.append(dict(kind='ASM:' + kind, f=f, sig=p, strength=strength, detail=detail, sug=sug))
    return out, (defs, protos, asmf, files, infos, used, cargs)

def mentions(f, files):
    pat = re.compile(r'\b%s\b' % re.escape(f))
    out = []
    for p in files:
        s = open(p, errors='replace').read()
        if pat.search(re.sub(r'#pragma GLOBAL_ASM\([^)]*\)', '', s)): out.append(p)
    return out

def dexec(cmd):
    return subprocess.run([DOCKER, 'exec', '-w', '/conker/conker', os.environ.get('CONKERDEV','conkerdev'), 'bash', '-c', cmd],
                          capture_output=True, text=True)

def check(cfiles):
    rel = [os.path.relpath(p, R) for p in cfiles]
    objs = ' '.join('build/%s.o' % r for r in rel)
    r = dexec('rm -f %s; make VERSION=eu -j8 %s >/dev/null 2>build/protocheck.err; echo MAKE=$?; python3 ../tools/eu_port/check_files.py %s'
              % (objs, objs, ' '.join(rel)))
    o = r.stdout
    if 'MAKE=0' not in o: return False, 'compile error'
    if ' bad of ' not in o: return False, 'check_files failed'
    bad = [l for l in o.split('\n') if re.match(r'(DIFF|SIZE|MISSING|DATA)', l)
           and not re.search(r'init_eu_289A0|game_eu_227BF0|debugger_eu_259B40', l) and 'OK' not in l.split()[0]]
    return (not bad), ('; '.join(bad[:3]) if bad else 'ok')

def main():
    a = sys.argv[1:]
    only = None
    if '--func' in a:
        i = a.index('--func'); only = set(x for x in a[i + 1:] if not x.startswith('--'))
    if '--sig' in a:
        f = a[a.index('--sig') + 1]
        defs, protos, asmf, files, infos, used, cargs = build_all()
        if f in defs: print('def', defs[f].fmt(), defs[f].where)
        for p in protos.get(f, []): print('proto', p.fmt(), '%s:%d' % (os.path.relpath(p.where, R), p.line), p.text)
        if f in infos:
            fi = infos[f]
            print('asm frame=0x%X livein=%s trunc=%s narrowload=%s exit_v0=%s exit_f0=%s' % (
                fi.frame, sorted(fi.livein), fi.trunc, fi.narrowload, sorted(map(str, fi.exit_v0)), sorted(map(str, fi.exit_f0))))
        print('asm callers read:', sorted(used.get(f, ())), ' call sites:', len(cargs.get(f, [])))
        return
    res, ctx = findings(only, include_minor='--all' in a)
    if '--apply' not in a:
        cnt = collections.Counter((r['kind'], r['strength']) for r in res)
        for r in res:
            if r['strength'] == 'minor' and '--all' not in a: continue
            print('%-12s %-6s %-14s %s:%d  %s' % (r['kind'], r['strength'], r['f'], os.path.relpath(r['sig'].where, R),
                                                  r['sig'].line, r['detail']))
        print('# totals:', ', '.join('%s/%s=%d' % (k[0], k[1], v) for k, v in sorted(cnt.items())))
        return
    files = ctx[3]
    strong_only = '--strong' in a
    mx = int(a[a.index('--max') + 1]) if '--max' in a else 10 ** 9
    dry = '--dry' in a
    logged = set()
    if os.path.exists(LOG):
        L = open(LOG).read().split('\n')
        for i, l in enumerate(L):
            if l.startswith('REJECT') and i + 2 < len(L): logged.add((L[i + 1][4:].strip(), L[i + 2][4:].strip()))
    log = open(LOG, 'a')
    done = set(); n = 0; kept = 0
    # group suggestions per prototype line: apply the combined change for one line at a time
    by_line = collections.OrderedDict()
    for r in res:
        if strong_only and r['strength'] != 'strong': continue
        if r['strength'] == 'minor': continue
        pl = proto_line(r['sig'])
        if not pl: print('SKIP', r['f'], 'not a one-line prototype', os.path.relpath(r['sig'].where, R), r['sig'].line); continue
        by_line.setdefault((pl[0], pl[1]), []).append(r)
    for (path, ln), rs in by_line.items():
        if n >= mx: break
        f = rs[0]['f']; sig = rs[0]['sig']
        # combine suggestions for this prototype (strong first)
        sug = {}
        for r in sorted(rs, key=lambda r: r['strength'] != 'strong'):
            for k, v in r['sug'].items():
                if k == 'param':
                    sug.setdefault('params', []).append(v)
                else: sug.setdefault(k, v)
        def build(sg):
            cur = Sig(sig.ret, sig.params, sig.text, sig.where, sig.line, sig.kind)
            if 'def' in sg:
                return rewrite(cur, {'def': sg['def']}, f)
            for p in sg.get('params', []):
                t = rewrite(cur, {'param': p}, f); cur = parse_one(t, cur)
            for k in ('ret', 'count', 'float'):
                if k in sg:
                    t = rewrite(cur, {k: sg[k]}, f); cur = parse_one(t, cur)
            return rewrite(cur, {}, f)
        # attempts: the combined change, then (if that fails) each part on its own
        parts = []
        if 'def' in sug:
            d = sug['def']
            parts.append({'def': Sig(d.ret, sig.params, d.text, d.where, d.line, 'def')})
            if sig.params is not None and d.params is not None:
                parts.append({'def': Sig(sig.ret, d.params, d.text, d.where, d.line, 'def')})
        else:
            parts += [{'params': [p]} for p in sug.get('params', [])]
            parts += [{k: sug[k]} for k in ('ret', 'count', 'float') if k in sug]
        attempts = [sug] + (parts if len(parts) > 1 else [])
        why = ' | '.join('%s:%s' % (r['kind'], r['detail']) for r in rs)
        for ai, sg in enumerate(attempts):
            if n >= mx: break
            txt = build(sg)
            if txt is None: print('SKIP', f, 'definition uses a type the prototype file may not know'); continue
            lines = open(path).read().split('\n')
            old = lines[ln]
            indent = re.match(r'\s*', old).group(0)
            tail = old[old.rfind(';') + 1:]
            newl = indent + txt + tail
            if newl.strip() == old.strip(): continue
            key = (old.strip(), newl.strip())
            if '--skip-logged' in a and key in logged: continue
            n += 1
            if dry:
                print('WOULD %s\n   - %s\n   + %s\n   (%s)' % (os.path.relpath(path, R), old.strip(), newl.strip(), why)); continue
            lines[ln] = newl
            open(path, 'w').write('\n'.join(lines))
            cf = mentions(f, files)
            if path.endswith('.c') and path not in cf: cf.append(path)
            ok, msg = check(cf) if cf else (True, 'no C mentions')
            if ok:
                kept += 1
                print('KEEP %s %s: %s  [%d files]' % (f, os.path.relpath(path, R), newl.strip(), len(cf)))
                log.write('KEEP %s %s:%d\n  - %s\n  + %s\n  why: %s\n' % (f, os.path.relpath(path, R), ln + 1, old.strip(), newl.strip(), why))
                log.flush()
                break
            lines[ln] = old
            open(path, 'w').write('\n'.join(lines))
            print('REJECT %s %s: %s (%s)' % (f, os.path.relpath(path, R), newl.strip(), msg))
            log.write('REJECT %s %s:%d\n  - %s\n  + %s\n  why: %s\n  result: %s\n' % (f, os.path.relpath(path, R), ln + 1, old.strip(), newl.strip(), why, msg))
            log.flush()
            check(cf)   # rebuild the restored objects
    print('# tried %d, kept %d' % (n, kept))

def parse_one(txt, base):
    m = FDECL.match(txt.rstrip(';').strip())
    s = mk_sig(m, txt.rstrip(';'), base.where, base.line, 'proto')
    return s

if __name__ == '__main__':
    main()
