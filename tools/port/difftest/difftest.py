#!/usr/bin/env python3
"""difftest: functional-equivalence check of a C body against the original machine code.

Runs inside the container from /conker/conker (use the host wrapper tools/port/difftest.sh).

usage: difftest.py FUNC [cand.c] [--self] [--trials N] [--seed S] [--max-insns N] [-v] [--json]
  FUNC        function name (US-style name, as in the .s / src_eu)
  cand.c      candidate C (the function definition; may start with //HOIST and //DROP lines like
              screen.py drafts, and may contain extra prototypes). Omitted with --self.
  --self      candidate = the function as it is already written in src_eu (for already-matched
              functions: proves the harness on known-good code)

Reference = the original bytes (the .s of a GLOBAL_ASM function, or conker.eu.bin at the
function's EU address for a C function). Candidate = the C compiled with IDO, with the flags of
the function's file, in a standalone TU built like m2c/screen.py (all other GLOBAL_ASM pragmas
dropped), then relocated so that every symbol has its real EU address.

Both run in Unicorn (MIPS32 BE) with the same inputs:
  * memory: the ROM image (code + rodata, and in half the trials the initial .data) mapped at its
    vram; every other page is created on first touch with deterministic pseudo-random words
    (zero / small ints / pointers into a fake heap at 0x80400000 / floats / noise), identical
    for both runs. kseg0/kseg1 alias to physical (addr & 0x1FFFFFFF).
  * args a0-a3, f12/f14 and 6 stack-arg words are random (pointers, small ints, noise).
  * every call outside the function body is a stub: it logs (callee, args) and returns
    deterministic random v0/v1/f0 (keyed by callee and call number) without touching memory.
Compared: callee trace (address, arguments up to the callee's arity), memory state at each
call (hash of non-stack bytes that differ from their initial value), final memory writes,
return value (by the candidate's declared return type) and the restoration of sp/s0-s8/f20-f30.
Prints one line: EQUIV <func> (n trials ...) | DIFFER <func>: <reason> | ERROR <func>: <why>.
"""
import sys, os, re, glob, subprocess, shlex, struct, hashlib, json, random
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
from unicorn import Uc, UcError, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, \
    UC_HOOK_MEM_UNMAPPED, UC_HOOK_MEM_WRITE, UC_HOOK_BLOCK, UC_PROT_ALL
from unicorn.mips_const import *

HERE = os.path.dirname(os.path.abspath(__file__))
PRAG = re.compile(r'#pragma GLOBAL_ASM\("([^"]*)/(\w+)\.s"\)')
WORD_RE = re.compile(r"/\*\s+([0-9A-F]+)\s+([0-9A-F]+)\s+([0-9A-F]{8})\s+\*/\s*(.*)")
PAGE = 0x1000
HEAP_LO, HEAP_HI = 0x80400000, 0x80600000       # fake heap (lazy random)
STK_LO, STK_TOP = 0x80600000, 0x80680000        # stack (zero-filled)
TU_BASE = 0x80700000                            # candidate TU .rodata/.data/.bss
RET_MAGIC = 0x807FF000
SP_ENTRY = STK_TOP - 0x100


def phys(a):
    return a & 0x1FFFFFFF if 0x80000000 <= a < 0xC0000000 else a


# ---------------------------------------------------------------- symbols / image
_SYMS = None
def symtab():
    global _SYMS
    if _SYMS is None:
        _SYMS = {}
        for f in ('undefined_syms_auto.txt', 'undefined_funcs_auto.txt', 'undefined_syms.eu.txt',
                  'undefined_funcs.eu.txt', 'symbol_addrs.eu.txt'):
            if os.path.exists(f):
                for l in open(f):
                    m = re.match(r'\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', l)
                    if m: _SYMS.setdefault(m.group(1), int(m.group(2), 16))
    return _SYMS

def symaddr(name):
    s = symtab()
    if name in s: return s[name]
    m = re.match(r'(?:D|jtbl|func)_([0-9A-F]{8})$', name)
    return int(m.group(1), 16) if m else None

_ADDR2NAME = None
def addr2name(a):
    global _ADDR2NAME
    if _ADDR2NAME is None:
        _ADDR2NAME = {}
        for n, v in symtab().items():
            if n.startswith('func_') or not n.startswith(('D_', 'jtbl_')):
                _ADDR2NAME.setdefault(v, n)
    return _ADDR2NAME.get(a)

def segments():
    sys.path.insert(0, os.path.join(os.getcwd(), '../tools/eu_port'))
    import datarefs
    return datarefs.segments()

_IMG = None
def image():
    """[(vram, bytes, kind)] kind in code/rodata/data, from conker.eu.bin + the EU yaml"""
    global _IMG
    if _IMG is None:
        rom = open('conker.eu.bin', 'rb').read()
        _IMG = []
        for nm, sg in segments().items():
            if 'vram' not in sg or sg.get('end') is None or nm in ('header', 'boot'): continue
            st, en, vr = sg['start'], sg['end'], sg['vram']
            if not nm.endswith('_data'):
                _IMG.append((vr, rom[st:en], 'code')); continue
            ro = next((r for r, t, _ in sg['subs'] if t and 'rodata' in t), en)
            _IMG.append((vr, rom[st:ro], 'data'))
            _IMG.append((vr + ro - st, rom[ro:en], 'rodata'))
    return _IMG

def vram2rom(v):
    for nm, sg in segments().items():
        if 'vram' in sg and sg.get('end') is not None and sg['vram'] <= v < sg['vram'] + sg['end'] - sg['start']:
            return v - sg['vram'] + sg['start']
    return None


# ---------------------------------------------------------------- reference
def find_file(func):
    for p in glob.glob('src_eu/**/*.c', recursive=True):
        src = open(p).read()
        for m in PRAG.finditer(src):
            if m.group(2) == func: return p, m.group(1) + '/' + func + '.s', src
        if re.search(r'^[^\n;#/]*\b%s\s*\([^;]*?\)\s*\{' % func, src, re.M):
            return p, None, src
    return None, None, None

def ref_from_s(spath):
    words, vram = [], None
    for line in open(spath):
        m = WORD_RE.search(line)
        if m:
            if vram is None: vram = int(m.group(2), 16)
            words.append(int(m.group(3), 16))
    while words and words[-1] == 0: words.pop()
    return vram, words


# ---------------------------------------------------------------- candidate build
_CC = {}
def cc_cmd(p):
    if p not in _CC: _CC[p] = _cc_cmd(p)
    return _CC[p]

def _cc_cmd(p):
    r = subprocess.run(['make', '-n', '-B', 'VERSION=eu', 'build/' + p + '.o'], capture_output=True, text=True).stdout
    for l in r.split('\n'):
        if '/cc ' in l and ' -c ' in l:
            a = shlex.split(l); i = a.index('-o'); a = a[:i] + a[i + 2:]
            return [x for x in a if not x.endswith('.c')]
    return None

def func_span(src, func):
    """(start, end) of the definition of func in src (start of its declarator line .. closing brace)"""
    m = re.search(r'^[^\n;#/]*\b%s\s*\([^;{]*?\)\s*\{' % func, src, re.M)
    if not m: return None
    i = m.end() - 1; depth = 0
    while i < len(src):
        c = src[i]
        if c == '{': depth += 1
        elif c == '}':
            depth -= 1
            if depth == 0: return m.start(), i + 1
        i += 1
    return None

def build_tu(func, p, src, code):
    hoist = [l[8:] for l in code.split('\n') if l.startswith('//HOIST ')]
    dropl = [l[7:] for l in code.split('\n') if l.startswith('//DROP ')]
    code = '\n'.join(l for l in code.split('\n') if not l.startswith(('//HOIST ', '//DROP ')))
    pm = [m for m in PRAG.finditer(src) if m.group(2) == func]
    if pm:
        m = pm[-1]; a, b = m.start(), m.end()
        k = src.rfind('#ifdef NON_MATCHING\n', 0, a)
        if k >= 0 and src[:a].endswith('#else\n') and '#endif' not in src[k:a] and src[b:].startswith('\n#endif'):
            a, b = k, b + len('\n#endif')   # already converted: replace the whole NON_MATCHING block
        tu = src[:a] + '\n' + code + '\n' + src[b:]
    else:
        sp = func_span(src, func)
        if sp is None: raise RuntimeError('no definition or pragma of %s in %s' % (func, p))
        tu = src[:sp[0]] + code + src[sp[1]:]
    for l in dropl: tu = tu.replace(l + '\n', '', 1)
    if hoist:
        ms = list(re.finditer(r'^#include[^\n]*\n', tu, re.M)); k = ms[-1].end() if ms else 0
        tu = tu[:k] + '\n'.join(hoist) + '\n' + tu[k:]
    tu = nm_resolve(tu, True)   # other NON_MATCHING blocks: keep the C side
    return PRAG.sub('', tu)

def nm_resolve(text, on=True):
    """evaluate the (non-nested) #ifdef/#ifndef NON_MATCHING ... [#else ...] #endif blocks"""
    out = []; state = None   # None | ('if'|'else', keep)
    for l in text.split('\n'):
        t = l.strip()
        if state is None and re.match(r'#\s*if(n?)def\s+NON_MATCHING\b', t):
            neg = t.startswith('#ifndef') or t.startswith('# ifndef')
            state = ['if', on != neg]; continue
        if state is not None and re.match(r'#\s*else\b', t):
            state = ['else', not state[1]]; continue
        if state is not None and re.match(r'#\s*endif\b', t):
            state = None; continue
        if state is None or state[1]: out.append(l)
    return '\n'.join(out)

def compile_tu(func, p, tu, tmp):
    cmd = cc_cmd(p)
    if cmd is None: raise RuntimeError('no cc command for ' + p)
    os.makedirs(tmp, exist_ok=True)
    cpath = os.path.join(tmp, func + '.c'); opath = os.path.join(tmp, func + '.o')
    open(cpath, 'w').write(tu)
    if os.path.exists(opath): os.remove(opath)
    r = subprocess.run(cmd + ['-o', opath, cpath], capture_output=True, text=True)
    if r.returncode or not os.path.exists(opath):
        em = [l for l in (r.stdout + r.stderr).split('\n') if 'rror' in l]
        tl = tu.split('\n'); ctx = []
        for l in em[:4]:
            m = re.search(r', line (\d+):', l)
            if m and 0 < int(m.group(1)) <= len(tl): ctx.append('@@' + tl[int(m.group(1)) - 1].strip())
        raise CompileError('\n'.join(em[:4] + ctx) or (r.stdout + r.stderr)[-400:])
    return opath

class CompileError(Exception): pass

def link_candidate(opath, func, vram):
    """-> (words, size) of func relocated to run at vram; TU data sections at TU_BASE"""
    with open(opath, 'rb') as fh:
        e = ELFFile(fh)
        secs = list(e.iter_sections())
        st = e.get_section_by_name('.symtab')
        tidx = [i for i, s in enumerate(secs) if s.name == '.text'][0]
        fs = sorted((s['st_value'], s['st_size'], s.name) for s in st.iter_symbols()
                    if s['st_shndx'] == tidx and s['st_info']['type'] == 'STT_FUNC')
        ent = [x for x in fs if x[2] == func]
        if not ent: raise RuntimeError('candidate object has no symbol ' + func)
        foff, fsize, _ = ent[0]
        text = bytearray(secs[tidx].data())
        if fsize == 0:
            nx = [x[0] for x in fs if x[0] > foff]; fsize = (nx[0] if nx else len(text)) - foff
        # place data sections
        base = {}; blobs = {}; cur = TU_BASE
        for i, s in enumerate(secs):
            if s.name in ('.rodata', '.data', '.bss', '.sdata', '.sbss') and s['sh_size']:
                cur = (cur + 15) & ~15; base[i] = cur
                blobs[i] = bytearray(s.data()) if s['sh_type'] != 'SHT_NOBITS' else bytearray(s['sh_size'])
                cur += s['sh_size']
        base[tidx] = vram - foff

        def S(sym):
            if sym['st_info']['type'] == 'STT_SECTION':
                if sym['st_shndx'] in base: return base[sym['st_shndx']]
                raise RuntimeError('reloc against section %s' % secs[sym['st_shndx']].name)
            a = symaddr(sym.name) if sym.name else None
            if a is not None: return a
            if sym['st_shndx'] not in ('SHN_UNDEF', 'SHN_ABS') and sym['st_shndx'] in base:
                if sym['st_shndx'] == tidx and sym.name != func:
                    raise RuntimeError('TU-local function %s has no EU address' % sym.name)
                return base[sym['st_shndx']] + sym['st_value']
            raise RuntimeError('unresolved symbol ' + sym.name)

        def apply(rs, buf, lo_ok):
            rels = list(rs.iter_relocations())
            for k, r in enumerate(rels):
                off, t = r['r_offset'], r['r_info_type']
                if not lo_ok(off): continue
                sym = st.get_symbol(r['r_info_sym']); s = S(sym)
                w = struct.unpack_from('>I', buf, off)[0]
                if t == 2:      # R_MIPS_32
                    w = (w + s) & 0xFFFFFFFF
                elif t == 4:    # R_MIPS_26
                    a = (w & 0x3FFFFFF) << 2
                    w = (w & 0xFC000000) | (((s + a) >> 2) & 0x3FFFFFF)
                elif t == 5:    # R_MIPS_HI16: pair with the next LO16 of the same symbol
                    lo = next((x for x in rels[k + 1:] if x['r_info_type'] == 6 and x['r_info_sym'] == r['r_info_sym']), None)
                    if lo is None: raise RuntimeError('HI16 without LO16')
                    lw = struct.unpack_from('>I', buf, lo['r_offset'])[0] & 0xFFFF
                    ahl = ((w & 0xFFFF) << 16) + (lw - 0x10000 if lw & 0x8000 else lw)
                    v = (s + ahl) & 0xFFFFFFFF
                    w = (w & 0xFFFF0000) | (((v + 0x8000) >> 16) & 0xFFFF)
                    hi_pending[r['r_info_sym']] = (w & 0xFFFF)
                elif t == 6:    # R_MIPS_LO16 (addend in place; the HI part does not change the low half)
                    a = w & 0xFFFF; a = a - 0x10000 if a & 0x8000 else a
                    w = (w & 0xFFFF0000) | ((s + a) & 0xFFFF)
                else:
                    raise RuntimeError('reloc type %d' % t)
                struct.pack_into('>I', buf, off, w)
        hi_pending = {}
        for s in secs:
            if isinstance(s, RelocationSection):
                tgt = s['sh_info']
                if tgt == tidx:
                    apply(s, text, lambda o: foff <= o < foff + fsize)
                elif tgt in blobs:
                    apply(s, blobs[tgt], lambda o: True)
        words = [struct.unpack_from('>I', text, foff + i)[0] for i in range(0, fsize, 4)]
        while len(words) > 2 and words[-1] == 0 and words[-2] == 0: words.pop()   # keep the delay-slot nop
        words.append(0)   # never fall into the ROM's next function
        data = [(base[i], bytes(b)) for i, b in blobs.items()]
        return words, data


# ---------------------------------------------------------------- static helpers
def gpr_dest(w):
    op = w >> 26; rs = (w >> 21) & 31; rt = (w >> 16) & 31; rd = (w >> 11) & 31
    if op == 0:
        fn = w & 63
        if fn in (8, 12, 13, 17, 19, 24, 25, 26, 27) or fn in range(48, 64): return None
        return rd
    if op == 1: return 31 if rt in (16, 17, 18, 19) else None
    if op == 3: return 31
    if 8 <= op <= 15: return rt
    if op == 17 and rs in (0, 2): return rt
    if op in (32, 33, 34, 35, 36, 37, 38, 48, 56): return rt
    return None

def fpr_dest(w):
    op = w >> 26; rs = (w >> 21) & 31; rt = (w >> 16) & 31
    if op == 17:
        if rs == 4: return (w >> 11) & 31
        if rs in (16, 17, 20, 21): return (w >> 6) & 31
        return None
    if op in (49, 53): return rt
    return None

def is_branch(w):
    op = w >> 26
    return (op == 0 and (w & 63) in (8, 9)) or op in (1, 2, 3, 4, 5, 6, 7, 20, 21, 22, 23) or (op == 17 and ((w >> 21) & 31) == 8)

def call_site_writes(words, idx):
    """arg registers / FP arg registers / stack arg slots written in the straight-line run before the
    call at idx (delay slot included)"""
    a, f, stk = set(), set(), set()
    j = idx + 1
    while j >= 0:
        w = words[j] if j < len(words) else 0
        if j < idx and (is_branch(w) or (j + 1 < idx and is_branch(words[j]))): break
        d = gpr_dest(w)
        if d is not None and 4 <= d <= 7: a.add(d - 4)
        fd = fpr_dest(w)
        if fd in (12, 13, 14, 15): f.add(fd)
        if (w >> 26) in (43, 57) and ((w >> 21) & 31) == 29:
            o = w & 0xFFFF
            if 16 <= o < 0x40: stk.add(o)
        j -= 1
        if idx - j > 40: break
    return a, f, stk

def proto_arity(tu, name):
    """number of parameter words of name per the declarations in tu (None if unknown / K&R)"""
    best = None
    for m in re.finditer(r'\b%s\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*[;{]' % re.escape(name), tu):
        ps = m.group(1).strip()
        if ps in ('', ): continue
        if ps == 'void': return 0
        if '...' in ps: return 99
        n = 0
        for p in ps.split(','):
            n += 2 if re.search(r'\b(f64|double|s64|u64|long long)\b', p) and '*' not in p else 1
        best = n
    return best

def ret_kind(tu, func):
    m = re.search(r'^([^\n;#/(){}]*?)\b%s\s*\([^;{]*?\)\s*\{' % func, tu, re.M)
    if not m:
        return 'int'
    t = m.group(1)
    if '*' in t: return 'int'
    if re.search(r'\bvoid\b', t): return 'void'
    if re.search(r'\b(f32|float)\b', t): return 'f32'
    if re.search(r'\b(f64|double)\b', t): return 'f64'
    if re.search(r'\b(s64|u64|long long)\b', t): return 'i64'
    return 'int'


# ---------------------------------------------------------------- emulation
def h32(*xs):
    return int.from_bytes(hashlib.blake2b(repr(xs).encode(), digest_size=4).digest(), 'big')

SMALLF = [0.0, 1.0, -1.0, 0.5, 2.0, 100.0]

def rand_word(seed, addr):
    h = h32('m', seed, addr)
    c = h % 100; r = h32('v', seed, addr)
    if c < 20: return 0
    if c < 35: return r % 9
    if c < 45: return ((r % 5) << 16) | ((r >> 8) % 5)                     # two small halfwords
    if c < 55: return ((r % 4) << 24) | (((r >> 4) % 4) << 16) | (((r >> 8) % 4) << 8) | ((r >> 12) % 4)
    if c < 77: return HEAP_LO + (r % ((HEAP_HI - HEAP_LO) // 16)) * 16
    if c < 83: return fbits(SMALLF[r % len(SMALLF)])
    if c < 92: return fbits(((r % 20001) - 10000) / 100.0)
    return r

def fbits(x):
    return struct.unpack('>I', struct.pack('>f', x))[0]

def rand_arg(rng, kind='any'):
    c = rng.random()
    if kind == 'ptr':
        return 0 if c < 0.04 else HEAP_LO + rng.randrange((HEAP_HI - HEAP_LO) // 16) * 16
    if kind == 'float':
        return fbits(rng.choice(SMALLF)) if c < 0.3 else rand_float_bits(rng)
    if kind == 'int':
        if c < 0.6: return rng.randrange(0, 9)
        if c < 0.7: return 0xFFFFFFFF
        if c < 0.85: return rng.randrange(0, 0x10000)
        return rng.getrandbits(32)
    if c < 0.45: return HEAP_LO + rng.randrange((HEAP_HI - HEAP_LO) // 16) * 16
    if c < 0.80: return rng.randrange(0, 9)
    if c < 0.85: return 0xFFFFFFFF
    if c < 0.95: return rng.randrange(0, 0x10000)
    return rng.getrandbits(32)

def param_kinds(tu, func):
    """o32 kinds of the declared parameters of func ('ptr'/'int'/'float'/'double'), None if unknown"""
    m = re.search(r'^[^\n;#/(){}]*?\b%s\s*\(([^;{]*?)\)\s*\{' % func, tu, re.M)
    if not m: return None
    ps = m.group(1).strip()
    if ps in ('', 'void'): return []
    out = []
    for p in ps.split(','):
        if '*' in p or '[' in p: out.append('ptr')
        elif re.search(r'\b(f32|float)\b', p): out.append('float')
        elif re.search(r'\b(f64|double)\b', p): out.append('double')
        else: out.append('int')
    return out

def make_inputs(rng, kinds):
    a = [rand_arg(rng) for _ in range(4)]; f = [rand_float_bits(rng), 0, rand_float_bits(rng), 0]
    stk = [rand_arg(rng) for _ in range(12)]
    if kinds is None: return dict(a=a, f=f, stk=stk)
    slot = 0; fpok = True; fi = 0
    for k in kinds:
        if k == 'double':
            slot = (slot + 1) & ~1
            v = struct.unpack('>Q', struct.pack('>d', rng.choice(SMALLF) if rng.random() < 0.3 else rng.uniform(-200, 200)))[0]
            hi, lo = v >> 32, v & 0xFFFFFFFF
            if fpok and fi < 2: f[2 * fi] = lo; f[2 * fi + 1] = hi; fi += 1   # FR=0: low word in the even reg
            for j, w in ((slot, hi), (slot + 1, lo)):
                if j < 4: a[j] = w
                elif j - 4 < 12: stk[j - 4] = w
            slot += 2; continue
        v = rand_arg(rng, k)
        if k == 'float' and fpok and fi < 2: f[2 * fi] = v; fi += 1
        else: fpok = False
        if k != 'float': fpok = False
        if slot < 4: a[slot] = v
        elif slot - 4 < 12: stk[slot - 4] = v
        slot += 1
    return dict(a=a, f=f, stk=stk)

def rand_float_bits(rng):
    return struct.unpack('>I', struct.pack('>f', rng.uniform(-200, 200)))[0]

A_REGS = [UC_MIPS_REG_A0, UC_MIPS_REG_A1, UC_MIPS_REG_A2, UC_MIPS_REG_A3]
S_REGS = [UC_MIPS_REG_S0 + i for i in range(8)] + [UC_MIPS_REG_FP]
FREG = lambda n: UC_MIPS_REG_F0 + n
SCRATCH = [UC_MIPS_REG_AT, UC_MIPS_REG_V0, UC_MIPS_REG_V1] + [UC_MIPS_REG_T0 + i for i in range(8)] + \
          [UC_MIPS_REG_T8, UC_MIPS_REG_T9]

class Run:
    def __init__(self, words, vram, extra, trial, romdata, tu, maxi):
        self.words, self.vram, self.end = words, vram, vram + 4 * len(words)
        self.seed, self.romdata, self.tu = trial, romdata, tu
        self.mu = mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        self.mapped = set(); self.writes = {}; self.calls = []; self.ncall = {}; self.maxi = maxi
        self.init = {}  # phys page -> initial bytes
        for v, b in extra: self.premap(v, b)
        code = b''.join(struct.pack('>I', w) for w in words)
        self.premap(vram, code, overlay=True)
        self.premap(STK_LO, bytes(STK_TOP - STK_LO + 0x1000))
        self.premap(RET_MAGIC, bytes(PAGE))
        mu.hook_add(UC_HOOK_MEM_UNMAPPED, self.on_unmapped)
        mu.hook_add(UC_HOOK_MEM_WRITE, self.on_write)
        mu.hook_add(UC_HOOK_BLOCK, self.on_block)

    def page_init(self, pp):
        """initial content of the physical page pp"""
        if pp in self.init: return self.init[pp]
        buf = None
        for v, b, kind in image():
            if kind == 'data' and not self.romdata: continue
            p0 = phys(v)
            if p0 <= pp + PAGE and pp < p0 + len(b):
                if buf is None: buf = bytearray(self.rand_page(pp))
                lo = max(pp, p0); hi = min(pp + PAGE, p0 + len(b))
                buf[lo - pp:hi - pp] = b[lo - p0:hi - p0]
        if buf is None: buf = self.rand_page(pp)
        self.init[pp] = bytes(buf)
        return self.init[pp]

    def rand_page(self, pp):
        return b''.join(struct.pack('>I', rand_word(self.seed, pp + i)) for i in range(0, PAGE, 4))

    def ensure(self, pp):
        if pp in self.mapped: return
        self.mu.mem_map(pp, PAGE, UC_PROT_ALL); self.mapped.add(pp)
        self.mu.mem_write(pp, self.page_init(pp))

    def premap(self, v, b, overlay=False):
        p0 = phys(v)
        for pp in range(p0 & ~(PAGE - 1), p0 + len(b), PAGE):
            if not overlay and pp not in self.init:
                self.init[pp] = bytes(PAGE)
            self.ensure(pp)
        self.mu.mem_write(p0, bytes(b))
        if not overlay:  # premapped content is the initial state
            for pp in range(p0 & ~(PAGE - 1), p0 + len(b), PAGE):
                self.init[pp] = bytes(self.mu.mem_read(pp, PAGE))

    def on_unmapped(self, mu, access, addr, size, value, ud):
        try:
            for a in {addr & ~(PAGE - 1), (addr + size - 1) & ~(PAGE - 1)}:
                self.ensure(phys(a) & ~(PAGE - 1))
            return True
        except Exception:
            return False

    def on_write(self, mu, access, addr, size, value, ud):
        p = phys(addr)
        if phys(STK_LO) <= p < phys(STK_TOP) + PAGE: return
        v = value & ((1 << (8 * size)) - 1)
        for i in range(size):
            self.writes[p + i] = (v >> (8 * (size - 1 - i))) & 0xFF

    def dirty(self):
        out = []
        for p in sorted(self.writes):
            init = self.page_init(p & ~(PAGE - 1))[p & (PAGE - 1)]
            if self.writes[p] != init: out.append((p, self.writes[p]))
        return out

    def norm(self, v):
        return 'STK' if phys(STK_LO) <= phys(v) < phys(STK_TOP) + PAGE else v

    def on_block(self, mu, addr, size, ud):
        if self.vram <= addr < self.end: return
        if addr == RET_MAGIC:
            self.done = True; mu.emu_stop(); return
        ra = mu.reg_read(UC_MIPS_REG_RA)
        site = (ra - 8 - self.vram) // 4
        # tail call: ra still points at the caller
        if ra == RET_MAGIC or not (0 <= site < len(self.words)):
            site = None
        name = addr2name(addr) or ('0x%08X' % addr)
        a, f, stk = call_site_writes(self.words, site) if site is not None else (set(), set(), set())
        sp = mu.reg_read(UC_MIPS_REG_SP)
        regs = [mu.reg_read(r) for r in A_REGS]
        stkw = [struct.unpack('>I', mu.mem_read(phys(sp) + o, 4))[0] for o in range(16, 0x40, 4)]
        fregs = {n: mu.reg_read(FREG(n)) & 0xFFFFFFFF for n in (12, 13, 14, 15)}
        self.calls.append(dict(addr=addr, name=name, regs=regs, a=a, f=f, stk=stk, stkw=stkw, fregs=fregs,
                               mem=hashlib.md5(repr(self.dirty()).encode()).hexdigest()[:8], tail=site is None))
        k = self.ncall.get(addr, 0); self.ncall[addr] = k + 1
        r = random.Random(h32('ret', self.seed, addr, k))
        mu.reg_write(UC_MIPS_REG_V0, rand_arg(r)); mu.reg_write(UC_MIPS_REG_V1, rand_arg(r))
        mu.reg_write(FREG(0), rand_float_bits(r)); mu.reg_write(FREG(1), rand_float_bits(r))
        mu.reg_write(FREG(2), rand_float_bits(r))
        # callee clobbers caller-saved registers
        for reg in SCRATCH[3:] + A_REGS:
            mu.reg_write(reg, r.getrandbits(32))
        mu.reg_write(UC_MIPS_REG_PC, ra)

    def run(self, inputs):
        mu = self.mu
        self.done = False
        for r, v in zip(A_REGS, inputs['a']): mu.reg_write(r, v)
        for i, v in enumerate(inputs['f']): mu.reg_write(FREG(12 + i), v)
        for i, v in enumerate(inputs['stk']): mu.mem_write(phys(SP_ENTRY) + 16 + 4 * i, struct.pack('>I', v))
        for i, r in enumerate(S_REGS): mu.reg_write(r, 0x5EED0000 + i)
        for i, r in enumerate(SCRATCH): mu.reg_write(r, 0xDEAD0000 + i)
        for n in range(20, 32): mu.reg_write(FREG(n), 0x3F800000 + n)
        mu.reg_write(UC_MIPS_REG_SP, SP_ENTRY); mu.reg_write(UC_MIPS_REG_RA, RET_MAGIC)
        self.fault = None
        try:
            mu.emu_start(self.vram, RET_MAGIC, count=self.maxi)
        except UcError as e:
            self.fault = '%s at 0x%08X' % (e, mu.reg_read(UC_MIPS_REG_PC))
        pc = mu.reg_read(UC_MIPS_REG_PC)
        self.done = self.done or pc == RET_MAGIC
        self.out = dict(v0=mu.reg_read(UC_MIPS_REG_V0), v1=mu.reg_read(UC_MIPS_REG_V1),
                        f0=mu.reg_read(FREG(0)) & 0xFFFFFFFF, f1=mu.reg_read(FREG(1)) & 0xFFFFFFFF,
                        sp=mu.reg_read(UC_MIPS_REG_SP), s=[mu.reg_read(r) for r in S_REGS],
                        fs=[mu.reg_read(FREG(n)) & 0xFFFFFFFF for n in range(20, 32)])
        return self


def same_val(R, a, C, b):
    """equal values, both stack pointers, or a candidate TU-local object (string / table literal)
    whose bytes equal those at the reference address"""
    if R.norm(a) == C.norm(b): return True
    if TU_BASE <= b < TU_BASE + 0x80000 or TU_BASE <= a < TU_BASE + 0x80000:
        try:
            return bytes(R.mu.mem_read(phys(a), 32)) == bytes(C.mu.mem_read(phys(b), 32))
        except Exception:
            return False
    return False


def compare(R, C, rk, arity):
    """-> None if equal, else a reason string"""
    if R.fault or C.fault:
        if bool(R.fault) != bool(C.fault):
            if R.fault: return None   # ref faulted on an input the candidate did not touch: inconclusive trial
            return 'fault only in cand: %s' % C.fault
        if R.fault.split(' at ')[0] != C.fault.split(' at ')[0]:
            return 'different faults: ref %s / cand %s' % (R.fault, C.fault)
    elif R.done != C.done:
        return 'timeout only in %s' % ('ref' if not R.done else 'cand')
    n = min(len(R.calls), len(C.calls))
    for i in range(n):
        a, b = R.calls[i], C.calls[i]
        if a['addr'] != b['addr']:
            return 'call #%d: ref calls %s, cand calls %s' % (i, a['name'], b['name'])
        na = arity.get(a['name'])
        cnt = max(na if na is not None else 0, max(a['a'] | b['a'], default=-1) + 1)
        if na is None or na == 99: cnt = max(cnt, max(a['a'], default=-1) + 1)
        for k in range(min(cnt, 4)):
            if not same_val(R, a['regs'][k], C, b['regs'][k]):
                return 'call #%d %s: a%d ref=0x%X cand=0x%X' % (i, a['name'], k, a['regs'][k], b['regs'][k])
        # outgoing stack args: the contiguous run of slots from sp+0x10 written right before the call
        # (other sp+0x10..0x3F stores can be locals), plus what a known prototype says
        w = a['stk'] | b['stk']; slots = set(); o = 16
        while o in w: slots.add(o); o += 4
        if na is not None and na != 99 and na > 4: slots |= {16 + 4 * j for j in range(na - 4)}
        for o in sorted(slots):
            j = (o - 16) // 4
            if j < len(a['stkw']) and not same_val(R, a['stkw'][j], C, b['stkw'][j]):
                return 'call #%d %s: stack arg sp+0x%X ref=0x%X cand=0x%X' % (i, a['name'], o, a['stkw'][j], b['stkw'][j])
        for fr in sorted(a['f'] | b['f']):
            if a['fregs'][fr] != b['fregs'][fr]:
                return 'call #%d %s: f%d ref=0x%X cand=0x%X' % (i, a['name'], fr, a['fregs'][fr], b['fregs'][fr])
        if a['mem'] != b['mem']:
            return 'memory state before call #%d (%s) differs' % (i, a['name'])
    if R.fault or C.fault or not R.done:
        return None if len(R.calls) == len(C.calls) else 'call count differs before fault/timeout'
    if len(R.calls) != len(C.calls):
        return 'call count ref=%d cand=%d (%s)' % (len(R.calls), len(C.calls),
                                                    (R.calls[n] if len(R.calls) > n else C.calls[n])['name'])
    dr, dc = R.dirty(), C.dirty()
    if dr != dc:
        sr, sc = dict(dr), dict(dc)
        k = min(set(sr) ^ set(sc) | {p for p in sr if p in sc and sr[p] != sc[p]})
        return 'memory differs at 0x%08X (ref=%s cand=%s)' % (k, '%02X' % sr[k] if k in sr else 'init', '%02X' % sc[k] if k in sc else 'init')
    o, p = R.out, C.out
    if o['sp'] != p['sp'] or o['s'] != p['s'] or o['fs'][::2] != p['fs'][::2]:
        return 'callee-saved registers not restored the same way'
    if rk == 'int' and not same_val(R, o['v0'], C, p['v0']):
        return 'return v0 ref=0x%X cand=0x%X' % (o['v0'], p['v0'])
    if rk == 'i64' and (o['v0'], o['v1']) != (p['v0'], p['v1']):
        return 'return v0:v1 differs'
    if rk == 'f32' and o['f0'] != p['f0']:
        return 'return f0 ref=0x%X cand=0x%X' % (o['f0'], p['f0'])
    if rk == 'f64' and (o['f0'], o['f1']) != (p['f0'], p['f1']):
        return 'return f0:f1 differs'
    return None


def check(func, code=None, self_mode=False, trials=64, seed=1, maxi=100000, verbose=False, tmp=None):
    """-> dict(result=EQUIV|DIFFER|UNSURE|ERROR|CERR, line=..., ...)"""
    p, spath, src = find_file(func)
    if p is None:
        return dict(func=func, result='ERROR', line='ERROR %s: not found in src_eu' % func)
    try:
        if spath:
            vram, rwords = ref_from_s(spath)
        else:
            vram = symaddr(func)
            if vram is None: raise RuntimeError('no EU address for ' + func)
        if self_mode:
            sp = func_span(src, func)
            if sp is None: raise RuntimeError('--self: %s is not C in %s' % (func, p))
            code = src[sp[0]:sp[1]]
        tu = build_tu(func, p, src, code)
        opath = compile_tu(func, p, tu, tmp or os.environ.get('DIFFTEST_TMP', 'build/difftest'))
        cwords, cdata = link_candidate(opath, func, vram)
        if not spath:   # C function: reference = ROM bytes, same length as the matched object
            rom = vram2rom(vram); raw = open('conker.eu.bin', 'rb').read()
            n = len(cwords) if self_mode else int(os.environ.get('DIFFTEST_REFLEN', '0')) // 4 or len(cwords)
            rwords = [struct.unpack_from('>I', raw, rom + 4 * k)[0] for k in range(n)]
    except CompileError as e:
        return dict(func=func, file=p, result='CERR', line='CERR %s: %s' % (func, str(e).replace('\n', ' | ')[:300]))
    except Exception as e:
        return dict(func=func, file=p, result='ERROR', line='ERROR %s: %s' % (func, e))
    rk = ret_kind(tu, func)
    kinds = param_kinds(tu, func)
    arity = {}
    differ = None; ok = inconcl = 0; ncalls = 0
    import time
    t0 = time.time(); budget = float(os.environ.get('DIFFTEST_BUDGET', '30'))
    for t in range(trials):
        if time.time() - t0 > budget and t >= 8:
            break
        rng = random.Random(h32('trial', seed, t))
        inputs = make_inputs(rng, kinds)
        romdata = t % 2 == 1
        R = Run(rwords, vram, [], (seed, t), romdata, tu, maxi).run(inputs)
        C = Run(cwords, vram, cdata, (seed, t), romdata, tu, maxi).run(inputs)
        for c in R.calls + C.calls:
            if c['name'] not in arity: arity[c['name']] = proto_arity(tu, c['name'])
        why = compare(R, C, rk, arity)
        ncalls += len(R.calls)
        if verbose:
            print('trial %d: %s ref(done=%s fault=%s calls=%d) cand(done=%s fault=%s calls=%d)' % (
                t, why or 'same', R.done, R.fault, len(R.calls), C.done, C.fault, len(C.calls)))
        if why:
            differ = 'trial %d: %s' % (t, why); break
        if R.fault or not R.done: inconcl += 1
        else: ok += 1
    res = dict(func=func, file=p, ret=rk, ref_words=len(rwords), cand_words=len(cwords), ok=ok, inconclusive=inconcl)
    if differ:
        line = 'DIFFER %s: %s' % (func, differ); res['result'] = 'DIFFER'; res['why'] = differ
    elif ok < max(4, trials // 8):
        line = 'UNSURE %s: only %d trials ran to completion (%d faulted/timed out)' % (func, ok, inconcl); res['result'] = 'UNSURE'
    else:
        line = 'EQUIV %s (%d trials ok, %d inconclusive, %d calls, ret=%s, ref %d words, cand %d words)' % (
            func, ok, inconcl, ncalls, rk, len(rwords), len(cwords)); res['result'] = 'EQUIV'
    res['line'] = line
    return res


def main():
    ap = sys.argv[1:]
    opts = dict(trials=64, seed=1, maxi=200000)
    flags = set(); pos = []
    i = 0
    while i < len(ap):
        a = ap[i]
        if a in ('--trials', '--seed', '--max-insns'):
            opts[{'--max-insns': 'maxi'}.get(a, a[2:])] = int(ap[i + 1]); i += 2; continue
        if a.startswith('-'): flags.add(a)
        else: pos.append(a)
        i += 1
    if not pos: print(__doc__); return 2
    code = open(pos[1]).read() if len(pos) > 1 else None
    if code is None and '--self' not in flags:
        print('need cand.c or --self'); return 2
    res = check(pos[0], code, '--self' in flags, opts['trials'], opts['seed'], opts['maxi'], '-v' in flags)
    print(json.dumps(res) if '--json' in flags else res['line'])
    return 0 if res['result'] == 'EQUIV' else 1


if __name__ == '__main__':
    sys.exit(main())
