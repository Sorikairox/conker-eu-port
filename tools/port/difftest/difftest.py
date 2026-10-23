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
import sys as _pgs, os as _pgo; _pgs.path.insert(0, _pgo.path.join(_pgo.path.dirname(_pgo.path.abspath(__file__)), '..')); import portguard  # wrong-checkout guard (P7)
import sys, os, re, glob, subprocess, shlex, struct, hashlib, json, random, gc, pickle
# Unicorn 2.1.x mis-translates a call whose delay slot holds an FPU instruction (lwc1/swc1/...):
# the callee's first block runs with stale delay-slot flags and jumps to 0 (UC_ERR_EXCEPTION at
# 0x00000000).  2.0.1 is correct.  Pinned copy: pip3 install --target /conker/port_work/pyuc201 unicorn==2.0.1.post1
_UC = os.environ.get('DIFFTEST_UNICORN', os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../../port_work/pyuc201'))
if os.path.isdir(_UC): sys.path.insert(0, os.path.abspath(_UC))
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection
from unicorn import Uc, UcError, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, \
    UC_HOOK_MEM_UNMAPPED, UC_HOOK_MEM_WRITE, UC_HOOK_MEM_READ, UC_HOOK_CODE, UC_HOOK_BLOCK, UC_PROT_ALL
from unicorn.mips_const import *

HERE = os.path.dirname(os.path.abspath(__file__))
PRAG = re.compile(r'#pragma GLOBAL_ASM\("([^"]*)/(\w+)\.s"\)')
WORD_RE = re.compile(r"/\*\s+([0-9A-F]+)\s+([0-9A-F]+)\s+([0-9A-F]{8})\s+\*/\s*(.*)")
PAGE = 0x1000
HEAP_LO, HEAP_HI = 0x80400000, 0x80600000       # fake heap (lazy random)
STK_LO, STK_TOP = 0x80600000, 0x80680000        # stack (zero-filled)
TU_BASE = 0x80705000                            # candidate TU .rodata/.data/.bss
# P18: NOT 0x80700000. Unicorn 2.0.1 bug: after an access to virtual page 0 (a null pointer + offset), a kseg0
# page in the same softmmu TLB slot ((vaddr >> 12) & 0xFF == 0: 0x80000000, 0x80100000, ..., 0x80700000)
# reads wrong data or segfaults (port_work/p18/uc_alias.py). With TU_BASE there, a candidate's own float
# literal read 0 whenever the function had touched page 0 first: the P17 "literal reads as 0" false DIFFER.
# Heap pointers skip those pages too (heap_ptr).
def heap_ptr(v):
    return v + PAGE if (v >> 12) & 0xFF == 0 else v
RET_MAGIC = 0x807FF000
CAND_ALT = 0x0F000000                           # (| the 256 MB jal region of vram) candidate code when it would overlap a callee
SP_ENTRY = STK_TOP - 0x100
# P89: stack-range values below SP_ENTRY - STK_WIN (and below the lowest sp the run saw) are not frame addresses and
# compare exactly. DIFFTEST_STK_OLD=1 restores the pre-P89 rule (the whole stack range compares equal).
STK_WIN = 0x1000
STK_OLD = os.environ.get('DIFFTEST_STK_OLD') == '1'
STKW_OLD = os.environ.get('DIFFTEST_STKW_OLD') == '1'   # P90
# P18: Unicorn 2.0.1's reg_read/reg_write of the MIPS FPRs are no-ops (reg_write(F4) then mfc1 reads the old
# value; reg_read(Fn) is always 0). So float args were never set, stubs never returned a float, and f0 returns
# / FP call args / f20-f31 were compared as 0 == 0. Leftover f0 after a stubbed float callee then differed by
# register allocation: the "candidate float literal reads as 0" false DIFFER of P17. FPRs now move through
# memory with real lwc1/swc1 code: a prologue loads the inputs, every stub jumps to a helper that saves
# f12-f15 and loads the random f0/f1/f2, and an epilogue at RET_MAGIC saves f0/f1/f20-f31. Base register k0
# (never used by compiled code) = SCR, a scratch page whose writes are not recorded.
SCR = 0x807FE000
HELPER_OFF = 0x0E000000                         # (| region) the FPR helper every stub jumps to
PROLOGUE = SCR + 0x400
_K0 = 26
def _lwc1(ft, off): return (49 << 26) | (_K0 << 21) | (ft << 16) | off
def _swc1(ft, off): return (57 << 26) | (_K0 << 21) | (ft << 16) | off
# SCR layout: +0x00 f12-f15 at the last call, +0x10 f0/f1/f2 a stub returns, +0x40 f12-f15 inputs,
# +0x50 f20-f31 inputs, +0x100 f0/f1 at return, +0x108 f20-f31 at return
HELPER_CODE = [_swc1(12 + i, 4 * i) for i in range(4)] + [_lwc1(i, 0x10 + 4 * i) for i in range(3)] + [0x03E00008, 0]
PROLOGUE_CODE = [_lwc1(12 + i, 0x40 + 4 * i) for i in range(4)] + [_lwc1(20 + i, 0x50 + 4 * i) for i in range(12)] + \
    [0x03600008, 0]   # jr k1 (= the function)
EPILOGUE_CODE = [_swc1(0, 0x100), _swc1(1, 0x104)] + [_swc1(20 + i, 0x108 + 4 * i) for i in range(12)] + \
    [(43 << 26) | (_K0 << 21) | 0x13C, 0, 0]   # sw zero, 0x13C(k0): the epilogue completed
RET_END = RET_MAGIC + 4 * len(EPILOGUE_CODE)
STEP = os.environ.get('DIFFTEST_STEP') == '1' or '--step' in sys.argv
# P47 (debug, opt-in): DIFFTEST_WLOG="LO-HI" (physical hex) + DIFFTEST_WLOG_T=trial prints every non-stack write
# into [LO, HI) of that trial with the writing pc (R = reference, C = candidate). Debug aid for long functions.
WLOG = tuple(int(x, 16) for x in os.environ['DIFFTEST_WLOG'].split('-')) if os.environ.get('DIFFTEST_WLOG') else None
WLOG_T = os.environ.get('DIFFTEST_WLOG_T', '0'); WLOG_ON = [None]
OUTPARAMS = os.environ.get('DIFFTEST_OUTPARAMS') == '1' or '--outparams' in sys.argv
NOFORK = os.environ.get('DIFFTEST_NOFORK') == '1'   # P16: run trials in-process (old behaviour)


def words2b(ws):
    return b''.join(struct.pack('>I', w) for w in ws)


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
def _s64(x): return x - (1 << 64) if x >> 63 else x
def _tdiv(a, b): q = abs(a) // abs(b); return q if (a < 0) == (b < 0) else -q
LL_HELPERS = {   # P45: emulated libultra 64-bit helpers (unsigned 64-bit operands in, None = leave random)
    '__ll_lshift': lambda x, y: x << (y & 63),
    '__ull_rshift': lambda x, y: x >> (y & 63),
    '__ll_rshift': lambda x, y: _s64(x) >> (y & 63),
    '__ll_mul': lambda x, y: x * y,
    '__ull_div': lambda x, y: x // y if y else None,
    '__ull_rem': lambda x, y: x % y if y else None,
    '__ll_div': lambda x, y: _tdiv(_s64(x), _s64(y)) if y else None,
    '__ll_rem': lambda x, y: _s64(x) - _tdiv(_s64(x), _s64(y)) * _s64(y) if y else None,
}

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
        if re.search(r'^[A-Za-z_][^\n;#/]*\b%s\s*\([^;]*?\)\s*\{' % func, src, re.M):
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
    if words and is_branch(words[-1]): words.append(0)   # keep the delay slot of the final jr ra
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
    m = re.search(r'^[A-Za-z_][^\n;#/]*\b%s\s*\([^;{]*?\)\s*\{' % func, src, re.M)
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
        # P80: comment / blank lines may sit between the #else and the pragma (game_981E0.c "// ??" notes)
        e = src.rfind('#else\n', 0, a)
        between = src[e + len('#else\n'):a] if e >= 0 else None
        only_notes = between is not None and all(not l.strip() or l.strip().startswith('//') for l in between.split('\n'))
        # P73: the NON_MATCHING side may hold more functions than this one
        nmside = func_span(src[k:e], func) if k >= 0 and k < e and '#endif' not in src[k:a] else None
        if k >= 0 and e > k and only_notes and '#endif' not in src[k:a] and src[b:].startswith('\n#endif'):
            a, b = k, b + len('\n#endif')   # already converted: replace the whole NON_MATCHING block
            tu = src[:a] + '\n' + code + '\n' + src[b:]
        elif nmside:
            # P73: the NON_MATCHING side holds more than this function (func_1501B300 + func_1501B640): replace
            # only its definition there. Before, the candidate went into the #else side, which nm_resolve drops,
            # so the src_eu body was tested instead of the candidate (every mutant "survived").
            tu = src[:k + nmside[0]] + code + src[k + nmside[1]:]
        else:
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
    # P73 / P80: the candidate must survive the splice and the NON_MATCHING resolution (else a different body would be
    # tested). P80's form: compare the candidate's own NM-resolved definition (P73 compared the raw text, which fails
    # when the candidate itself holds #ifdef NON_MATCHING lines).
    cr = nm_resolve(code, True); cs = func_span(cr, func)
    if cs is not None and cr[cs[0]:cs[1]] not in tu:
        raise RuntimeError('candidate %s was dropped when splicing it into %s' % (func, p))
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
    # P15: headers as the NON_MATCHING build sees them (the TU's own NM blocks are already resolved)
    r = subprocess.run(cmd + ['-DNON_MATCHING', '-o', opath, cpath], capture_output=True, text=True)
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
            if sym.name == func: return vram   # recursion: the candidate's own run address
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
        # P13: also stop at the delay slot of an earlier branch/jump (j - 1 is that branch): its writes belong
        # to the earlier call or path (a jal's delay slot a2=3 widened a 1-arg call to 3 args)
        if j < idx and (is_branch(w) or (0 < j and is_branch(words[j - 1]))): break
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

_NOC = {}
def _nocomment(tu):
    k = hash(tu)
    if k not in _NOC: _NOC[k] = re.sub(r'/\*.*?\*/', ' ', re.sub(r'//[^\n]*', '', tu), flags=re.S)
    return _NOC[k]

_HDR = None
def hdr_protos():
    """P93: include/functions.h. Callees declared only there had an unknown arity, so their stack arguments came from
    the call-site stores (sp+0x10..0x3C only): arguments 16+ of e.g. func_1513D594 (17) were never compared. Only
    prototypes with more than 16 arguments are taken from it (shorter ones keep the call-site rule)."""
    global _HDR
    if _HDR is None:
        try: _HDR = open('include/functions.h').read()
        except OSError: _HDR = ''
    return _HDR

_ALLHDR = None
def all_hdr_protos():
    """P100: every header under include/ (functions.h, libc/math.h, ...). Float-register and float-slot info for a
    callee with no declaration in the TU comes from here: sinf / cosf are declared only in include/libc/math.h, so
    their f12 argument was never compared and a `rad = ang` mutant survived (port-b P96)."""
    global _ALLHDR
    if _ALLHDR is None:
        import glob as _g
        parts = []
        for f in sorted(_g.glob('include/**/*.h', recursive=True)):
            try: parts.append(open(f, errors='replace').read())
            except OSError: pass
        _ALLHDR = '\n'.join(parts)
    return _ALLHDR

def proto_arity(tu, name):
    """number of parameter words of name per the declarations in tu (None if unknown / K&R)"""
    best = None
    tu = _nocomment(tu)   # P30: commented-out old drafts (`//     func_X(a, b, c, d);`) are not prototypes
    ms = list(re.finditer(r'\b%s\s*\(([^()]*(?:\([^()]*\)[^()]*)*)\)\s*[;{]' % re.escape(name), tu))
    # P71: a declaration (type before the name) wins over call statements: `func_X((s32 *) M(rec, 0x28), 4);`
    # counted the comma inside M(...) and made a 2-argument callee look like 3 (func_15030448 / func_100043B4)
    decl = [m for m in ms if _is_decl(tu, m)]
    for m in decl or ms:
        ps = m.group(1).strip()
        if ps in ('', ): continue
        if ps == 'void': return 0
        if '...' in ps: return 99
        n = 0
        for p in _split_top(ps):
            n += 2 if re.search(r'\b(f64|double|s64|u64|long long)\b', p) and '*' not in p else 1
        best = n
    return best

def _split_top(ps):
    """P71: split a parameter / argument list at the commas outside parentheses"""
    out, d, cur = [], 0, ''
    for ch in ps:
        if ch == ',' and d == 0: out.append(cur); cur = ''; continue
        d += {'(': 1, ')': -1}.get(ch, 0); cur += ch
    return out + [cur]

_DECL_PRE = re.compile(r'^\s*(?:(?:extern|static|inline)\s+)*[A-Za-z_]\w*[\s*]+$')
def _is_decl(tu, m):
    """P47: the match is a declaration / definition (a type before the name on its line), not a call statement
    such as `    func_X(temp_f12);` that would hide the real prototype's float slots"""
    return bool(_DECL_PRE.match(tu[tu.rfind('\n', 0, m.start()) + 1:m.start()]))

def _decl_first(tu, name):
    """matches of `name(...)` followed by ; or {: the declarations first, then (as before P47) the other matches"""
    ms = list(re.finditer(r'\b%s\s*\(([^()]*)\)\s*[;{]' % re.escape(name), tu))
    return [m for m in ms if _is_decl(tu, m)] + [m for m in ms if not _is_decl(tu, m)]

FSKIP = {}
def proto_fslots(tu, name):
    """P13: a-register slots that the prototype's leading float/double parameters occupy under o32 (they travel in
    f12/f14, so a0/a1 at the call hold junk and must not be compared)"""
    for m in _decl_first(tu, name):
        ps = [p for p in m.group(1).split(',') if p.strip()]
        out, slot = set(), 0
        for p in ps[:2]:
            if '*' in p or '[' in p: break   # P50: array parameters (f32 mf[4][4]) are pointers
            if re.search(r'\b(f32|float)\b', p): out.add(slot); slot += 1
            elif re.search(r'\b(f64|double)\b', p): out |= {slot, slot + 1}; slot += 2
            else: break
        return out
    return set()

FREGS = {}
def proto_fregs(tu, name):
    """P18: FP argument registers (f12-f15) the prototype of name passes (o32: only leading float/double params
    travel in FPRs), None if unknown. P100: declarations only; a call statement such as `s = sinf(temp->unk8);` was
    parsed as a prototype with an int parameter and gave set(), so no FPR argument was compared at all."""
    for m in [m for m in _decl_first(_nocomment(tu), name) if _is_decl(_nocomment(tu), m)]:
        ps = [p.strip() for p in m.group(1).split(',') if p.strip()]
        if ps == ['void'] or not ps: return set()
        out = set(); fr = 12
        for p in ps[:2]:
            if '*' in p or '[' in p: break   # P50: array parameters are pointers
            if re.search(r'\b(f32|float)\b', p): out.add(fr); fr += 2
            elif re.search(r'\b(f64|double)\b', p): out |= {fr, fr + 1}; fr += 2
            else: break
        return out
    return None


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

# P10 (opt-in): DIFFTEST_POKE="ADDR=VAL[*N],..." (hex) fixes lazily created memory words (N consecutive words),
# identically for the reference and the candidate, to reach paths random words never take (e.g. a -1
# "empty slot" sentinel). It only narrows the inputs; nothing about the comparison changes.
POKES = {}
for _p in filter(None, os.environ.get('DIFFTEST_POKE', '').split(',')):
    _a, _v = _p.split('=')
    _v, _n = (_v.split('*') + ['1'])[:2]
    for _k in range(int(_n)):
        POKES[(int(_a, 16) + 4 * _k) & 0x1FFFFFFF] = int(_v, 16) & 0xFFFFFFFF

# P106 (opt-in): DIFFTEST_MEMSTK="ADDR,..." (hex): memory words that hold a stack address (a function that saves
# its sp in a global, e.g. func_150ADFD0 -> D_800D3858) compare by class ('STK' in the used stack window), not bytes.
MEMSTK = [int(_a, 16) & 0x1FFFFFFF for _a in filter(None, os.environ.get('DIFFTEST_MEMSTK', '').split(','))]

# P13 (opt-in): DIFFTEST_RET="ADDR=VAL,..." (hex) makes the stub at ADDR return VAL in v0, for both sides, to
# reach code behind a callee's result (e.g. an early return unless func_1517F51C() == 0).
STUBRET = {}
for _p in filter(None, os.environ.get('DIFFTEST_RET', '').split(',')):
    _a, _v = _p.split('=')
    # P24: "ADDR=V1;V2;..." returns V1 on the first call, V2 on the second, ... (the last value repeats),
    # e.g. a message loop: osRecvMesg=0;0;0;FFFFFFFF
    STUBRET[int(_a, 16) & 0x1FFFFFFF] = [int(x, 16) & 0xFFFFFFFF for x in _v.split(';')]

# P50 (opt-in): DIFFTEST_RETF="ADDR=V1;V2;...,..." (hex float bits) makes the stub at ADDR return V in f0 (V1 on the
# first call, ...; the last repeats), e.g. func_1504B0FC's speed in func_1504CB98 (a random f0 is often 0 / NaN).
STUBRETF = {}
for _p in filter(None, os.environ.get('DIFFTEST_RETF', '').split(',')):
    _a, _v = _p.split('=')
    STUBRETF[int(_a, 16) & 0x1FFFFFFF] = [int(x, 16) & 0xFFFFFFFF for x in _v.split(';')]

# P34 (opt-in): DIFFTEST_OUTW="ADDR=N:V1;V2;...,..." (hex ADDR/V, decimal N): at each call to ADDR the stub
# writes the word V (V1 on the first call, V2 on the second, ..., the last repeats) through aN, e.g. the
# found / count out-params of func_1502B6BC. Several "N:V" for one ADDR are separated by '/'. P64: N >= 4 = stack argument.
def _outn(s):
    # P100: N may be '@ADDR' (hex): the stub writes at that absolute address instead of through an argument
    # (results a callee leaves in globals, e.g. func_1517C11C's per-voice flags read by func_1517E3CC).
    return ('abs', int(s[1:], 16)) if s.startswith('@') else int(s)

OUTW = {}
for _p in filter(None, os.environ.get('DIFFTEST_OUTW', '').split(',')):
    _a, _v = _p.split('=')
    OUTW[int(_a, 16) & 0x1FFFFFFF] = [(_outn(_x.split(':')[0]), [int(_y, 16) & 0xFFFFFFFF for _y in _x.split(':')[1].split(';')])
                                     for _x in _v.split('/')]

# P38 (opt-in): DIFFTEST_OUTA="ADDR=N:W0;W1;...,..." (hex ADDR/W, decimal N): at every call to ADDR the stub writes
# the words W0, W1, ... (an array) through argument N; N >= 4 is a stack argument (the pointer at sp+0x10+4*(N-4)),
# e.g. func_15186494's 5-word strip table. Several "N:W..." for one ADDR are separated by '/'.
OUTA = {}
for _p in filter(None, os.environ.get('DIFFTEST_OUTA', '').split(',')):
    _a, _v = _p.split('=')
    OUTA[int(_a, 16) & 0x1FFFFFFF] = [(_outn(_x.split(':')[0]), [int(_y, 16) & 0xFFFFFFFF for _y in _x.split(':')[1].split(';')])
                                     for _x in _v.split('/')]

# P41 (opt-in): DIFFTEST_OUTB="ADDR=N:B0;B1;...,..." like DIFFTEST_OUTA but writes bytes (hex B), e.g. u8 out-params
# that sit next to each other in the caller's frame (func_150851E0's angle / flag bytes).
OUTB = {}
for _p in filter(None, os.environ.get('DIFFTEST_OUTB', '').split(',')):
    _a, _v = _p.split('=')
    OUTB[int(_a, 16) & 0x1FFFFFFF] = [(_outn(_x.split(':')[0]), [int(_y, 16) & 0xFF for _y in _x.split(':')[1].split(';')])
                                     for _x in _v.split('/')]

# P28 (opt-in): DIFFTEST_ARGMEM="ADDR=N:LEN,..." (hex ADDR, decimal N/LEN): at each call to ADDR, the LEN bytes
# that aN points to are logged and compared (e.g. a stack table passed by address, which stubs never read).
# N >= 4 (P43): the stack argument at sp+0x10+4*(N-4).
ARGMEM = {}
for _p in filter(None, os.environ.get('DIFFTEST_ARGMEM', '').split(',')):
    _a, _v = _p.split('=')
    _n, _l = _v.split(':')
    # P100: N may be 'N+OFF' (hex OFF): compare LEN bytes from aN + OFF (skips padding a struct argument leaves
    # uninitialised, e.g. func_151DA6F8's spawn block: bytes 0x16-0x17 are stack garbage in both builds).
    _n, _o = (_n.split('+') + ['0'])[:2]
    ARGMEM.setdefault(int(_a, 16) & 0x1FFFFFFF, []).append((int(_n), int(_l), int(_o, 16)))

def rand_word(seed, addr):
    if POKES and (addr & 0x1FFFFFFF) in POKES:
        return POKES[addr & 0x1FFFFFFF]
    h = h32('m', seed, addr)
    c = h % 100; r = h32('v', seed, addr)
    if c < 20: return 0
    if c < 35: return r % 9
    if c < 45: return ((r % 5) << 16) | ((r >> 8) % 5)                     # two small halfwords
    if c < 55: return ((r % 4) << 24) | (((r >> 4) % 4) << 16) | (((r >> 8) % 4) << 8) | ((r >> 12) % 4)
    if c < 77: return heap_ptr(HEAP_LO + (r % ((HEAP_HI - HEAP_LO) // 16)) * 16)
    if c < 83: return fbits(SMALLF[r % len(SMALLF)])
    if c < 92: return fbits(((r % 20001) - 10000) / 100.0)
    return r

def fbits(x):
    return struct.unpack('>I', struct.pack('>f', x))[0]

def rand_arg(rng, kind='any'):
    c = rng.random()
    if kind == 'ptr':
        return 0 if c < 0.04 else heap_ptr(HEAP_LO + rng.randrange((HEAP_HI - HEAP_LO) // 16) * 16)
    if kind == 'float':
        return fbits(rng.choice(SMALLF)) if c < 0.3 else rand_float_bits(rng)
    if kind == 'int':
        if c < 0.6: return rng.randrange(0, 9)
        if c < 0.7: return 0xFFFFFFFF
        if c < 0.85: return rng.randrange(0, 0x10000)
        return rng.getrandbits(32)
    if c < 0.45: return heap_ptr(HEAP_LO + rng.randrange((HEAP_HI - HEAP_LO) // 16) * 16)
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

# P20 (opt-in): DIFFTEST_ARG="N=V1|V2|...,..." (hex) gives integer argument slot N (0-3 = a0-a3, 4+ = stack) one of the
# listed values per trial, to reach paths behind rare argument bits (func_1502B350's packed-record flag).
ARGFIX = {}
for _p in filter(None, os.environ.get('DIFFTEST_ARG', '').split(',')):
    _a, _v = _p.split('=')
    ARGFIX[int(_a)] = [int(x, 16) & 0xFFFFFFFF for x in _v.split('|')]

STK_IN_MAX = 60   # P95: stack argument words sp+0x10 .. sp+0xFC (SP_ENTRY = STK_TOP - 0x100)

def make_inputs(rng, kinds):
    r = _make_inputs(rng, kinds)
    # P95: arguments 16+ (stack words 12+) were never set: a 19-argument function (func_15035220) read whatever the
    # harness left there, and DIFFTEST_ARG N >= 16 was ignored silently. Only when needed (more than 16 parameters
    # or an ARG knob >= 16), from a separate generator so the main random stream (and older results) do not move.
    need = max([len(kinds) if kinds else 0] + [n + 1 for n in ARGFIX])
    if need > 16:
        xr = random.Random(r['stk'][0] ^ (r['a'][0] << 1))
        for slot in range(16, min(need, STK_IN_MAX + 4)):
            k = kinds[slot] if kinds and slot < len(kinds) else None
            r['stk'].append(rand_arg(xr, k) if k not in (None, 'double') else rand_arg(xr))
    for n, vs in ARGFIX.items():
        v = vs[rng.randrange(len(vs))]
        if n < 4: r['a'][n] = v
        elif n - 4 < len(r['stk']): r['stk'][n - 4] = v
        else: print('NOTE: DIFFTEST_ARG %d is beyond the %d stack words that can be set' % (n, STK_IN_MAX))
    return r

def _make_inputs(rng, kinds):
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
    def __init__(self, words, vram, extra, trial, romdata, tu, maxi, forced=None, trace=False, pwatch=False):
        self.forced = forced or {}; self.loads = []; self.trace = trace; self.pread = set()
        self.words, self.vram, self.end = words, vram, vram + 4 * len(words)
        self.seed, self.romdata, self.tu = trial, romdata, tu
        self.mu = mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        self.mapped = set(); self.writes = {}; self.calls = []; self.ncall = {}; self.maxi = maxi
        self.init = {}  # phys page -> initial bytes
        for v, b in extra: self.premap(v, b)
        # MIPS III ld/sd are not in Unicorn's MIPS32 CPU: they are patched to nop in the mapped
        # code and their memory effect is done by a code hook on that address (delay slots work)
        self.d64 = {}; self.d64hi = {}
        mwords = list(words)
        for k, w in enumerate(words):
            if (w >> 26) in (25, 55, 63):   # daddiu, ld, sd
                self.d64[vram + 4 * k] = w; mwords[k] = 0
        code = b''.join(struct.pack('>I', w) for w in mwords)
        self.premap(vram, code, overlay=True)
        self.premap(STK_LO, bytes(STK_TOP - STK_LO + 0x1000))
        self.premap(RET_MAGIC, words2b(EPILOGUE_CODE) + bytes(PAGE - 4 * len(EPILOGUE_CODE)))
        self.premap(SCR, bytes(0x400) + words2b(PROLOGUE_CODE) + bytes(PAGE - 0x400 - 4 * len(PROLOGUE_CODE)))
        self.helpers = set(); self.pending = None
        mu.hook_add(UC_HOOK_MEM_UNMAPPED, self.on_unmapped)
        mu.hook_add(UC_HOOK_MEM_WRITE, self.on_write)
        mu.hook_add(UC_HOOK_BLOCK, self.on_block)
        self.last_pc = None
        for a in self.d64: mu.hook_add(UC_HOOK_CODE, self.on_d64, begin=a, end=a)
        # callee stubs are real code: `jr ra; nop` written at every call target before it runs.
        # (Redirecting PC from the block hook let the callee's first block execute anyway, and a
        # branch right after the call then raised UC_ERR_EXCEPTION at 0x00000000.)
        self.stubs = set()
        for k, w in enumerate(words):
            op = w >> 26
            if op in (2, 3):     # j / jal outside the body: a call or tail call
                self.stub_at(((vram + 4 * k + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2))
            elif op == 0 and (w & 0x3F) in (8, 9) and not ((w & 0x3F) == 8 and (w >> 21) & 31 == 31):
                mu.hook_add(UC_HOOK_CODE, self.on_jalr, begin=vram + 4 * k, end=vram + 4 * k)
        if STEP and not trace:
            # P7: a code hook over the body makes Unicorn translate one instruction per block. Works around
            # a 2.0.1 mis-run seen in func_100049E0 (a jump-table lw read 0 after a branch-likely that follows
            # a stubbed call); slower, so opt-in (DIFFTEST_STEP=1 or --step)
            mu.hook_add(UC_HOOK_CODE, self.on_code, begin=vram, end=self.end - 1)
        if pwatch and POKES:   # P93: which DIFFTEST_POKE words the reference really reads (one hook per poked page)
            # one global hook: Unicorn 2.0.1 range-bound read hooks missed some lbu reads (func_15035AF8: obj+4 / +7 / +0x74)
            self.ppages = {a & ~(PAGE - 1) for a in POKES}
            mu.hook_add(UC_HOOK_MEM_READ, self.on_pread)
        if trace:
            mu.hook_add(UC_HOOK_MEM_READ, self.on_read)
            mu.hook_add(UC_HOOK_CODE, self.on_code, begin=vram, end=self.end - 1)

    def on_code(self, mu, addr, size, ud):
        self.last_pc = addr

    def stub_at(self, a):
        if a in self.stubs or self.vram <= a < self.end or a == RET_MAGIC or a & 3: return
        try:
            p = phys(a)
            for pp in {p & ~(PAGE - 1), (p + 7) & ~(PAGE - 1)}: self.ensure(pp)
            h = ((a + 4) & 0xF0000000) | HELPER_OFF
            if h < 0xC0000000:   # P18: j helper (saves f12-f15, loads the stub's f0/f1/f2, jr ra)
                if h not in self.helpers:
                    self.ensure(phys(h)); self.mu.mem_write(phys(h), words2b(HELPER_CODE)); self.helpers.add(h)
                self.mu.mem_write(p, struct.pack('>II', 0x08000000 | ((h >> 2) & 0x3FFFFFF), 0))
            else:
                self.mu.mem_write(p, b'\x03\xe0\x00\x08\x00\x00\x00\x00')
            self.mu.ctl_remove_cache(a, a + 8)
        except Exception:
            pass
        self.stubs.add(a)

    def on_jalr(self, mu, addr, size, ud):
        if len(self.stubs) > 400:   # random function pointers: every new target costs a fresh page; give up (timeout)
            mu.emu_stop(); return
        w = self.words[(addr - self.vram) // 4]
        self.stub_at(mu.reg_read(UC_MIPS_REG_0 + ((w >> 21) & 31)) & 0xFFFFFFFF)

    def on_d64(self, mu, addr, size, ud):
        w = self.d64.get(addr)
        if w is None: return
        self.last_pc = addr
        base, rt = (w >> 21) & 31, (w >> 16) & 31
        off = w & 0xFFFF; off -= (off & 0x8000) << 1
        if (w >> 26) == 25:   # daddiu: 64-bit add on the (shadowed or sign-extended) register
            lo = mu.reg_read(UC_MIPS_REG_0 + base) & 0xFFFFFFFF if base else 0
            sh = self.d64hi.get(base)
            hi = sh[1] if sh and sh[0] == lo else (0xFFFFFFFF if lo & 0x80000000 else 0)
            v = (((hi << 32) | lo) + off) & 0xFFFFFFFFFFFFFFFF
            if rt:
                mu.reg_write(UC_MIPS_REG_0 + rt, v & 0xFFFFFFFF); self.d64hi[rt] = (v & 0xFFFFFFFF, v >> 32)
            return
        ea = (mu.reg_read(UC_MIPS_REG_0 + base) + off) & 0xFFFFFFFF
        p = phys(ea)
        try:
            if ea & 7 or ea >= 0xC0000000: raise ValueError
            for pp in {p & ~(PAGE - 1), (p + 7) & ~(PAGE - 1)}: self.ensure(pp)
        except Exception:
            self.d64fault = addr; mu.emu_stop(); return
        if (w >> 26) == 63:   # sd: the upper word is the one ld loaded if the register still holds its low word
            lo = mu.reg_read(UC_MIPS_REG_0 + rt) & 0xFFFFFFFF if rt else 0
            sh = self.d64hi.get(rt)
            hi = sh[1] if sh and sh[0] == lo else (0xFFFFFFFF if lo & 0x80000000 else 0)
            b = struct.pack('>II', hi, lo)
            mu.mem_write(p, b)
            if self.trace: self.loads.append((ea, lo))
            if not phys(STK_LO) <= p < phys(STK_TOP) + PAGE:
                for i in range(8): self.writes[p + i] = b[i]
        else:                 # ld
            hi, lo = struct.unpack('>II', bytes(mu.mem_read(p, 8)))
            if self.trace: self.loads.append((ea + 4, lo))
            if rt:
                mu.reg_write(UC_MIPS_REG_0 + rt, lo); self.d64hi[rt] = (lo, hi)

    def on_pread(self, mu, access, addr, size, value, ud):
        if phys(addr) & ~(PAGE - 1) not in self.ppages: return
        for a in range(phys(addr) & ~3, phys(addr) + size, 4):
            if a in POKES: self.pread.add(a)

    def on_read(self, mu, access, addr, size, value, ud):
        if size == 4 and not addr & 3:
            try: self.loads.append((addr, struct.unpack('>I', mu.mem_read(phys(addr), 4))[0]))
            except Exception: pass

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
        fw = [(a, v) for a, v in self.forced.items() if pp <= a < pp + PAGE]
        if fw:
            buf = bytearray(buf)
            for a, v in fw: buf[a - pp:a - pp + 4] = struct.pack('>I', v)
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
        if phys(STK_LO) <= p < phys(STK_TOP) + PAGE or phys(SCR) <= p < phys(SCR) + PAGE: return
        v = value & ((1 << (8 * size)) - 1)
        if WLOG and WLOG[0] <= p < WLOG[1] and WLOG_ON[0]:
            print('WLOG %s pc=%08X addr=%08X size=%d val=%X' % (WLOG_ON[0], mu.reg_read(UC_MIPS_REG_PC), p, size, v))
        for i in range(size):
            self.writes[p + i] = (v >> (8 * (size - 1 - i))) & 0xFF

    def dirty(self):
        out = []
        w = self.writes
        if MEMSTK:   # P106: words that hold a stack address (e.g. a saved sp) compare by class, like registers
            w = dict(w)
            for a in MEMSTK:
                if all(a + i in w for i in range(4)):
                    v = struct.unpack('>I', bytes(w[a + i] for i in range(4)))[0]
                    if self.norm(v) == 'STK':
                        for i in range(4): w[a + i] = 0x5A
        for p in sorted(w):
            init = self.page_init(p & ~(PAGE - 1))[p & (PAGE - 1)]
            if w[p] != init: out.append((p, w[p]))
        return out

    def norm(self, v):
        # P89: only addresses in the part of the stack the function really used (its frame, or the window below
        # the entry sp that a small frame covers) are frame addresses that may differ between ref and candidate.
        # Other stack-range values (stub returns, pokes, random words such as 0x8066xxxx) did not come from sp and
        # compare exactly (P86: a +0x10 / +0x14 mutant on a stub-returned 0x806xxxxx pointer compared equal as 'STK').
        if STK_OLD: return v if not phys(STK_LO) <= phys(v) < phys(STK_TOP) + PAGE else 'STK'
        lo = min(self.minsp, SP_ENTRY - STK_WIN)
        return 'STK' if phys(lo) <= phys(v) < phys(STK_TOP) + PAGE else v

    def flush_fregs(self):
        """P18: f12-f15 of the last call, saved by the helper after its on_block"""
        if self.pending is not None:
            v = struct.unpack('>4I', bytes(self.mu.mem_read(phys(SCR), 16)))
            self.calls[self.pending]['fregs'] = {12 + i: v[i] for i in range(4)}
            self.pending = None

    def on_block(self, mu, addr, size, ud):
        if (addr & 0x0FFFFFFF) == HELPER_OFF and (addr & 0xF0000000) | HELPER_OFF in self.helpers: return
        if addr == PROLOGUE: return
        self.flush_fregs()
        if self.vram <= addr < self.end:
            self.icount += max(1, size // 4)
            # P89: the frame is set up in the entry block; the next blocks see the function's own sp
            if self.nblk < 4:
                self.nblk += 1; self.minsp = min(self.minsp, mu.reg_read(UC_MIPS_REG_SP))
            return
        if addr == RET_MAGIC:
            self.done = True; return   # the epilogue saves the FPRs, emu_start stops at RET_END
        ra = mu.reg_read(UC_MIPS_REG_RA)
        site = (ra - 8 - self.vram) // 4
        # tail call: ra still points at the caller
        if ra == RET_MAGIC or not (0 <= site < len(self.words)):
            site = None
        name = addr2name(addr) or ('0x%08X' % addr)
        a, f, stk = call_site_writes(self.words, site) if site is not None else (set(), set(), set())
        sp = mu.reg_read(UC_MIPS_REG_SP)
        self.minsp = min(self.minsp, sp)
        regs = [mu.reg_read(r) for r in A_REGS]
        # P90: all outgoing stack words a prototype can name (args 4..63); before P90 only sp+0x10..0x3C (args 4..15)
        # were captured, so arguments 16+ (func_1516DF0C's 49, func_150E2030's 28, func_1516FAB8's 17) were never
        # compared. DIFFTEST_STKW_OLD=1 restores the old window.
        stkw = [struct.unpack('>I', mu.mem_read(phys(sp) + o, 4))[0] for o in range(16, 0x40 if STKW_OLD else 0x100, 4)]
        fregs = {n: 0 for n in (12, 13, 14, 15)}   # filled by flush_fregs once the helper ran
        self.calls.append(dict(addr=addr, name=name, regs=regs, a=a, f=f, stk=stk, stkw=stkw, fregs=fregs,
                               mem=hashlib.md5(repr(self.dirty()).encode()).hexdigest()[:8], tail=site is None, ra=ra))
        if (addr & 0x1FFFFFFF) in ARGMEM:
            am = []
            for _n, _l, _o in ARGMEM[addr & 0x1FFFFFFF]:
                # P43: N >= 4 is a stack argument (the pointer at sp+0x10+4*(N-4)), as in DIFFTEST_OUTA
                try: am.append(bytes(mu.mem_read(phys((regs[_n] if _n < 4 else stkw[_n - 4]) + _o), _l)).hex())
                except Exception: am.append('unmapped')
            self.calls[-1]['argmem'] = am
        self.pending = len(self.calls) - 1
        k = self.ncall.get(addr, 0); self.ncall[addr] = k + 1
        r = random.Random(h32('ret', self.seed, addr, k))
        mu.reg_write(UC_MIPS_REG_V0, rand_arg(r)); mu.reg_write(UC_MIPS_REG_V1, rand_arg(r))
        if (addr & 0x1FFFFFFF) in STUBRET:
            _rs = STUBRET[addr & 0x1FFFFFFF]; mu.reg_write(UC_MIPS_REG_V0, _rs[min(k, len(_rs) - 1)])
        # P45: the libultra 64-bit helpers are pure; compute them (a0:a1 op a2:a3 -> v0:v1) instead of a random
        # return, so u64 bit-mask loops (func_150A16A4) run their real course on both sides.
        if name in LL_HELPERS:
            _x = (regs[0] << 32) | regs[1]; _y = (regs[2] << 32) | regs[3]
            _r = LL_HELPERS[name](_x, _y)
            if _r is not None:
                _r &= (1 << 64) - 1
                mu.reg_write(UC_MIPS_REG_V0, _r >> 32); mu.reg_write(UC_MIPS_REG_V1, _r & 0xFFFFFFFF)
        mu.mem_write(phys(SCR) + 0x10, struct.pack('>3I', rand_float_bits(r), rand_float_bits(r), rand_float_bits(r)))
        if (addr & 0x1FFFFFFF) in STUBRETF:
            _rs = STUBRETF[addr & 0x1FFFFFFF]; mu.mem_write(phys(SCR) + 0x10, struct.pack('>I', _rs[min(k, len(_rs) - 1)]))
        # P7, opt-in (DIFFTEST_OUTPARAMS=1 or --outparams): a callee writes a deterministic random
        # word through each aligned aN that points into the caller's frame (out-params such as
        # osRecvMesg's &msg). Keyed by (callee, call number, arg index), so both runs see the same value.
        if OUTPARAMS:
            idx = sorted(a) if site is not None and a else range(4)
            for i in idx:
                v = regs[i]
                if v & 3 == 0 and sp <= v < STK_TOP - 4:
                    ro = random.Random(h32('out', self.seed, addr, k, i))
                    mu.mem_write(phys(v), struct.pack('>I', rand_arg(ro)))
        if (addr & 0x1FFFFFFF) in OUTW:
            for _n, _vs in OUTW[addr & 0x1FFFFFFF]:
                # P64: N >= 4 is a stack argument (the pointer at sp+0x10+4*(N-4)), as in DIFFTEST_OUTA
                _p = _n[1] if isinstance(_n, tuple) else regs[_n] if _n < 4 else struct.unpack('>I', bytes(mu.mem_read(phys(sp + 0x10 + 4 * (_n - 4)), 4)))[0]
                mu.mem_write(phys(_p), struct.pack('>I', _vs[min(k, len(_vs) - 1)]))
        if (addr & 0x1FFFFFFF) in OUTA:
            for _n, _ws in OUTA[addr & 0x1FFFFFFF]:
                _p = _n[1] if isinstance(_n, tuple) else regs[_n] if _n < 4 else struct.unpack('>I', bytes(mu.mem_read(phys(sp + 0x10 + 4 * (_n - 4)), 4)))[0]
                mu.mem_write(phys(_p), struct.pack('>%dI' % len(_ws), *_ws))
        if (addr & 0x1FFFFFFF) in OUTB:
            for _n, _ws in OUTB[addr & 0x1FFFFFFF]:
                _p = _n[1] if isinstance(_n, tuple) else regs[_n] if _n < 4 else struct.unpack('>I', bytes(mu.mem_read(phys(sp + 0x10 + 4 * (_n - 4)), 4)))[0]
                mu.mem_write(phys(_p), bytes(_ws))
        # callee clobbers caller-saved registers
        for reg in SCRATCH[3:] + A_REGS:
            mu.reg_write(reg, r.getrandbits(32))
        if addr not in self.stubs:   # not stubbed in time (should not happen): old PC redirect
            mu.reg_write(UC_MIPS_REG_PC, ra)

    def run(self, inputs):
        if WLOG_ON[0]: print('WLOG %s --- run' % WLOG_ON[0])
        mu = self.mu
        self.done = False
        for r, v in zip(A_REGS, inputs['a']): mu.reg_write(r, v)
        mu.mem_write(phys(SCR) + 0x40, struct.pack('>4I', *inputs['f']))
        mu.mem_write(phys(SCR) + 0x50, struct.pack('>12I', *[0x3F800000 + n for n in range(20, 32)]))
        mu.reg_write(UC_MIPS_REG_K0, SCR); mu.reg_write(UC_MIPS_REG_K1, self.vram)
        mu.mem_write(phys(SCR) + 0x13C, b'\x00\x00\x00\x01')
        for i, v in enumerate(inputs['stk']): mu.mem_write(phys(SP_ENTRY) + 16 + 4 * i, struct.pack('>I', v))
        for i, r in enumerate(S_REGS): mu.reg_write(r, 0x5EED0000 + i)
        for i, r in enumerate(SCRATCH): mu.reg_write(r, 0xDEAD0000 + i)
        mu.reg_write(UC_MIPS_REG_SP, SP_ENTRY); mu.reg_write(UC_MIPS_REG_RA, RET_MAGIC)
        self.fault = None; self.icount = 0; pc = PROLOGUE; self.d64fault = None
        self.minsp = SP_ENTRY; self.nblk = 0
        while True:
            self.resume = None
            try:
                mu.emu_start(pc, RET_END, count=max(1, self.maxi - self.icount))
            except UcError as e:
                self.fault = '%s at 0x%08X' % (e, mu.reg_read(UC_MIPS_REG_PC))
                self.fault_pc = self.last_pc if self.last_pc is not None else mu.reg_read(UC_MIPS_REG_PC)
                self.fault_regs = [mu.reg_read(UC_MIPS_REG_0 + i) for i in range(32)]
                break
            if self.d64fault is not None:
                self.fault = 'ld/sd address error at 0x%08X' % self.d64fault
                self.fault_pc = self.d64fault
                self.fault_regs = [mu.reg_read(UC_MIPS_REG_0 + i) for i in range(32)]
                break
            if self.resume is None or self.done: break
            pc = self.resume
            if self.icount >= self.maxi or len(self.calls) > 20000: break
        self.flush_fregs()
        pc = mu.reg_read(UC_MIPS_REG_PC)
        fo = struct.unpack('>16I', bytes(mu.mem_read(phys(SCR) + 0x100, 64)))
        self.done = self.done and fo[15] == 0   # (Unicorn may stop with PC short of RET_END)
        self.out = dict(v0=mu.reg_read(UC_MIPS_REG_V0), v1=mu.reg_read(UC_MIPS_REG_V1),
                        f0=fo[0], f1=fo[1],
                        sp=mu.reg_read(UC_MIPS_REG_SP), s=[mu.reg_read(r) for r in S_REGS],
                        fs=list(fo[2:]))
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


LIBULTRA_PREFIXES = ('os', '__os', 'gu', 'bzero', 'bcopy')
EXACT = set(filter(None, os.environ.get('DIFFTEST_EXACT', '').split(',')))


def compare(R, C, rk, arity):
    """-> None if equal, else a reason string"""
    if C.fault and not R.fault and not R.done:
        pass   # the reference timed out first (the candidate has a larger cap): prefix compare only
    elif R.fault or C.fault:
        if bool(R.fault) != bool(C.fault):
            if R.fault: return None   # ref faulted on an input the candidate did not touch: inconclusive trial
            return 'fault only in cand: %s' % C.fault
        if R.fault.split(' at ')[0] != C.fault.split(' at ')[0]:
            return 'different faults: ref %s / cand %s' % (R.fault, C.fault)
    elif R.done != C.done and R.done:
        return 'timeout only in cand'   # the candidate gets 4x the reference's instruction cap
    elif not R.done:
        pass   # the reference timed out (inconclusive): only the common call prefix is compared below
    n = min(len(R.calls), len(C.calls))
    for i in range(n):
        a, b = R.calls[i], C.calls[i]
        if a['addr'] != b['addr']:
            return 'call #%d: ref calls %s, cand calls %s' % (i, a['name'], b['name'])
        na = arity.get(a['name'])
        # with a known prototype, only the reference's call-site writes widen it (P7: a candidate that
        # happens to compute something in a2 right before a 1-arg call was a false DIFFER)
        cnt = max(na if na is not None else 0, max(a['a'] if na not in (None, 99) else a['a'] | b['a'], default=-1) + 1)
        # P65: a known prototype fixes the register arguments (func_1503AB20 reloads a spilled a2 right before a
        # one-argument call to func_15048A40, which made a2 look like an argument)
        if na is not None and na != 99 and os.environ.get('DIFFTEST_PROTO_ARGS', '1') == '1': cnt = min(cnt, na)
        if na is None or na == 99: cnt = max(cnt, max(a['a'], default=-1) + 1)
        # libultra prototypes are exact: a call site that also reloads a spilled a3 is not a 4th argument
        if na not in (None, 99) and a['name'].startswith(LIBULTRA_PREFIXES): cnt = na
        # P30 (opt-in): DIFFTEST_EXACT="NAME,..." or "*": those known prototypes are exact too (a scratch a2 left
        # by the reference right before a 1-arg call is not an argument)
        if na not in (None, 99) and (a['name'] in EXACT or '*' in EXACT): cnt = na
        for k in range(min(cnt, 4)):
            if k in FSKIP.get(a['name'], ()): continue
            if not same_val(R, a['regs'][k], C, b['regs'][k]):
                return 'call #%d %s: a%d ref=0x%X cand=0x%X' % (i, a['name'], k, a['regs'][k], b['regs'][k])
        # outgoing stack args: the contiguous run of slots from sp+0x10 written right before the call
        # (other sp+0x10..0x3F stores can be locals), plus what a known prototype says
        w = a['stk'] | b['stk']; slots = set(); o = 16
        while o in w: slots.add(o); o += 4
        # P65: a known prototype with > 4 args fixes the slots exactly (hand asm func_150A69E0 keeps ra at sp+0x20,
        # right after its 8th argument, so the contiguous run took it for a 9th)
        if na is not None and na != 99 and na > 4: slots = {16 + 4 * j for j in range(na - 4)}
        # P24: a known prototype with <= 4 args has no stack args (hand asm such as func_150A8050 keeps ra at sp+0x10)
        if na is not None and na != 99 and na <= 4: slots = set()
        for o in sorted(slots):
            j = (o - 16) // 4
            if j < len(a['stkw']) and not same_val(R, a['stkw'][j], C, b['stkw'][j]):
                return 'call #%d %s: stack arg sp+0x%X ref=0x%X cand=0x%X' % (i, a['name'], o, a['stkw'][j], b['stkw'][j])
        pf = FREGS.get(a['name'])
        # unknown prototype: only FPRs both sides set right before the call (a lone scratch f12 is not an argument)
        for fr in sorted(a['f'] & b['f'] if pf is None else pf):
            if a['fregs'][fr] != b['fregs'][fr]:
                return 'call #%d %s: f%d ref=0x%X cand=0x%X' % (i, a['name'], fr, a['fregs'][fr], b['fregs'][fr])
        if a['mem'] != b['mem']:
            return 'memory state before call #%d (%s) differs' % (i, a['name'])
        if a.get('argmem') != b.get('argmem'):
            return 'call #%d %s: argument memory (DIFFTEST_ARGMEM) differs: ref %s cand %s' % (
                i, a['name'], a.get('argmem'), b.get('argmem'))
    if not R.done and not R.fault:
        return None
    if R.fault or C.fault:
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
    # P106: DIFFTEST_SIGNORE="7,..." leaves s-registers out (hand asm that uses s7 as its ra save: the event VM's
    # native helpers, whose caller saved s7 itself)
    sig = {int(x) for x in filter(None, os.environ.get('DIFFTEST_SIGNORE', '').split(','))}
    os_ = [v for k, v in enumerate(o['s']) if k not in sig]; ps_ = [v for k, v in enumerate(p['s']) if k not in sig]
    if o['sp'] != p['sp'] or os_ != ps_ or o['fs'][::2] != p['fs'][::2]:
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


LOADSTORE = set(range(32, 40)) | set(range(40, 47)) | {49, 53, 55, 57, 61, 63}

def learn_pointer(rwords, vram, trial, romdata, tu, maxi, inputs, forced):
    """automatic input template: the reference faulted (an invalid input).  Re-run it with a load trace,
    find the word the faulting base register came from (a memory word, an argument or a stack arg) and
    make it a valid heap pointer.  -> True if something was forced (forced / inputs are updated)"""
    R = Run(rwords, vram, [], trial, romdata, tu, maxi, forced, trace=True).run(inputs)
    R.mu = None
    if not R.fault or not hasattr(R, 'fault_pc'): return False
    k = (R.fault_pc - vram) // 4
    if not 0 <= k < len(rwords): return False
    w = rwords[k]
    if (w >> 26) not in LOADSTORE: return False
    B = R.fault_regs[(w >> 21) & 31]
    near = lambda v: 0 <= (B - v) & 0xFFFFFFFF < 0x8000
    ptr = heap_ptr(HEAP_LO + (h32('force', trial, B, len(forced)) % ((HEAP_HI - HEAP_LO) // 16)) * 16)
    stk = (phys(STK_LO), phys(STK_TOP) + PAGE)
    for a, v in reversed(R.loads):
        if near(v) and not stk[0] <= phys(a) < stk[1] and phys(a) not in forced:
            forced[phys(a)] = ptr; return True
    for i, v in enumerate(inputs['a']):
        if near(v): inputs['a'][i] = ptr; return True
    for i, v in enumerate(inputs['stk']):
        if near(v): inputs['stk'][i] = ptr; return True
    return False


def explain(R, C, inputs, forced):
    """-v: the diverging trial in detail (inputs, both call traces, the memory writes that differ)"""
    print('--- diverging trial: a0-a3 %s  stack args %s%s' % (' '.join('%08X' % x for x in inputs['a']),
          ' '.join('%08X' % x for x in inputs['stk'][:4]), '  learned pointers at ' + ' '.join('%08X' % a for a in forced) if forced else ''))
    fmt = lambda c: '%-22s %s' % (c['name'][:22], ' '.join('%08X' % x for x in c['regs']))
    n = max(len(R.calls), len(C.calls))
    print('--- calls (ref | cand), a0-a3:')
    for i in range(int((os.environ.get('DIFFTEST_CALLS_FROM') or '0')), min(n, int((os.environ.get('DIFFTEST_CALLS_FROM') or '0')) + 24)):   # P47: window
        a = fmt(R.calls[i]) if i < len(R.calls) else '-'
        b = fmt(C.calls[i]) if i < len(C.calls) else '-'
        print('%s#%-3d %-60s | %s' % ('*' if a != b else ' ', i, a, b))
    dr, dc = dict(R.dirty()), dict(C.dirty())
    ks = sorted(k for k in set(dr) | set(dc) if dr.get(k) != dc.get(k))
    if ks:
        print('--- final memory bytes that differ (addr: ref cand), %d total:' % len(ks))
        for k in ks[:16]:
            print('  %08X: %s %s' % (k, '%02X' % dr[k] if k in dr else '--', '%02X' % dc[k] if k in dc else '--'))
    print('--- return v0 ref=%08X cand=%08X  f0 ref=%08X cand=%08X  fault ref=%s cand=%s' % (
        R.out['v0'], C.out['v0'], R.out['f0'], C.out['f0'], R.fault, C.fault))


def strip_pad(words):
    """drop IDO's trailing alignment nops (P7): with them the candidate covered the next function's first
    word, so no stub could go there and a tail call into it ran the padding (func_10004DB0 --self DIFFER)"""
    n = len(words)
    while n > 1 and words[n - 1] == 0: n -= 1
    if n < len(words) and (is_branch(words[n - 1]) or (words[n - 1] >> 26) in (2, 3)
                           or ((words[n - 1] >> 26) == 0 and (words[n - 1] & 0x3E) == 8)):
        n += 1   # the last instruction has a delay slot (a nop)
    return words[:n]


def die_with_parent(ppid):
    """P18: SIGKILL this process when its parent dies (Linux prctl PR_SET_PDEATHSIG). A hung trial child used to
    survive convert.py killing its function process and kept a core at 100% (P17)."""
    try:
        import ctypes, signal
        ctypes.CDLL(None, use_errno=True).prctl(1, signal.SIGKILL, 0, 0, 0)
        if os.getppid() != ppid: os._exit(0)   # the parent died before prctl
    except Exception:
        pass


def wait_child(pid, rfd, wall):
    """P18: read a trial child's pickled result with a wall-clock limit -> (bytes or None, status, hung).
    The child is killed on timeout, and also if anything (convert.py's SIGALRM _Hang) interrupts the wait."""
    import select, time, signal
    chunks = []; hung = False; deadline = time.time() + wall; reaped = False; st = 0
    try:
        while True:
            left = deadline - time.time()
            if left <= 0:
                hung = True; break
            r, _, _ = select.select([rfd], [], [], min(left, 5.0))
            if not r: continue
            c = os.read(rfd, 1 << 16)
            if not c: break
            chunks.append(c)
        if hung:
            os.kill(pid, signal.SIGKILL)
        _, st = os.waitpid(pid, 0); reaped = True
    finally:
        if not reaped:
            try: os.kill(pid, signal.SIGKILL); os.waitpid(pid, 0)
            except OSError: pass
        os.close(rfd)
    return (b''.join(chunks) if chunks and not hung else None), st, hung


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
        cwords = strip_pad(cwords)
        if not spath:   # C function: reference = ROM bytes, same length as the matched object
            rom = vram2rom(vram); raw = open('conker.eu.bin', 'rb').read()
            n = len(cwords) if self_mode else int(os.environ.get('DIFFTEST_REFLEN') or '0') // 4 or len(cwords)
            rwords = [struct.unpack_from('>I', raw, rom + 4 * k)[0] for k in range(n)]
    except CompileError as e:
        return dict(func=func, file=p, result='CERR', line='CERR %s: %s' % (func, str(e).replace('\n', ' | ')[:300]))
    except Exception as e:
        return dict(func=func, file=p, result='ERROR', line='ERROR %s: %s' % (func, e))
    # a candidate longer than the reference would overlap the following functions: if it calls one of
    # them (its code would sit where the stub must go), run the candidate at CAND_ALT instead
    cvram = vram
    rend, cend = vram + 4 * len(rwords), vram + 4 * len(cwords)
    for k, w in enumerate(cwords):
        if (w >> 26) in (2, 3) and rend <= ((((vram + 4 * k + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2))) < cend:
            cvram = (vram & 0xF0000000) | CAND_ALT
            cwords, cdata = link_candidate(opath, func, cvram)
            cwords = strip_pad(cwords)
            break
    rk = ret_kind(tu, func)
    kinds = param_kinds(tu, func)
    arity = {}
    differ = None; ok = inconcl = 0; ncalls = 0; learned = [0]
    import time
    t0 = time.time(); budget = float(os.environ.get('DIFFTEST_BUDGET', '30'))
    def one(t):
        rng = random.Random(h32('trial', seed, t))
        inputs = make_inputs(rng, kinds)
        romdata = t % 2 == 1 or os.environ.get('DIFFTEST_ROMDATA') == '1'   # P106: always the ROM .data (jump / opcode tables)
        forced = {}; lrn = 0
        WLOG_ON[0] = 'R' if WLOG and str(t) == WLOG_T else None
        pw = t < 2
        R = Run(rwords, vram, [], (seed, t), romdata, tu, maxi, pwatch=pw).run(inputs)
        if R.fault and not os.environ.get('DIFFTEST_NOLEARN'):
            inputs = dict(a=list(inputs['a']), f=list(inputs['f']), stk=list(inputs['stk']))
            for _ in range(int(os.environ.get('DIFFTEST_LEARN', '8'))):
                if not learn_pointer(rwords, vram, (seed, t), romdata, tu, maxi, inputs, forced): break
                R = Run(rwords, vram, [], (seed, t), romdata, tu, maxi, forced, pwatch=pw).run(inputs)
                if not R.fault: break
            if not R.fault: lrn = 1
        WLOG_ON[0] = 'C' if WLOG and str(t) == WLOG_T else None
        C = Run(cwords, cvram, cdata, (seed, t), romdata, tu, 4 * maxi, forced).run(inputs)
        WLOG_ON[0] = None
        new = {}
        for c in R.calls + C.calls:
            if c['name'] not in arity and c['name'] not in new:
                pn = 'func_' + c['name'][2:] if c['name'].startswith('0x') else c['name']  # P13: unnamed EU address
                new[c['name']] = (proto_arity(tu, pn), proto_fslots(tu, pn), proto_fregs(tu, pn))
                if new[c['name']][0] is None:   # P93: no declaration in the TU: a >16-argument prototype in functions.h
                    ha = proto_arity(hdr_protos(), pn)
                    if ha is not None and 16 < ha < 99:
                        new[c['name']] = (ha, proto_fslots(hdr_protos(), pn), proto_fregs(hdr_protos(), pn))
                if new[c['name']][2] is None:   # P100: no declaration in the TU: FP argument registers from include/**.h
                    hf = proto_fregs(all_hdr_protos(), pn)
                    if hf:
                        new[c['name']] = (new[c['name']][0], new[c['name']][1], hf)
                arity[c['name']] = new[c['name']][0]; FSKIP[c['name']] = new[c['name']][1]; FREGS[c['name']] = new[c['name']][2]
        why = compare(R, C, rk, arity)
        if verbose:
            print('trial %d: %s ref(done=%s fault=%s calls=%d) cand(done=%s fault=%s calls=%d)' % (
                t, why or 'same', R.done, R.fault, len(R.calls), C.done, C.fault, len(C.calls)))
            if R.fault and getattr(R, 'fault_pc', None) is not None:   # P65: where the reference faulted
                print('  ref fault pc 0x%08X regs %s' % (R.fault_pc, ' '.join('%X' % x for x in R.fault_regs)))
            if why: explain(R, C, inputs, forced)
        return dict(why=why, ok=bool(not R.fault and R.done), ncalls=len(R.calls), learned=lrn, new=new, pread=R.pread, pw=pw, called={c['addr'] & 0x1FFFFFFF for c in R.calls})
    crashed = 0; hung = 0
    pread = set(); pwatched = [0]; called = set()
    twall = float(os.environ.get('DIFFTEST_TRIAL_WALL', '0')) or max(60.0, 2 * budget)
    for t in range(trials):
        if time.time() - t0 > budget and t >= 8:
            break
        if NOFORK:
            o = one(t)
            gc.collect()
        else:
            # P16: each trial runs in a forked child that exits without closing its emulators. With unicorn
            # 2.0.1 (aarch64 container) a uc_close -- explicit, or unicorn's weakref finalizer when the GC
            # collects a dropped Run/Uc -- makes a LATER emulator segfault inside emu_start (func_1509BA04: all
            # seeds exit 139; never closing: EQUIV). These were the "random Unicorn segfaults" of P7-P15, and
            # through them the convert.py Pool deadlock. A child that still dies counts as inconclusive.
            sys.stdout.flush()
            rfd, wfd = os.pipe()
            ppid = os.getpid()
            pid = os.fork()
            if pid == 0:
                die_with_parent(ppid)
                os.close(rfd)
                gc.disable()   # no collection = no uc_close inside the child (dropped learn_pointer runs)
                if os.environ.get('DIFFTEST_TEST_HANG') == str(t): time.sleep(1e9)   # P18 test knob: a hung trial
                try: o = one(t)
                except BaseException as e: o = dict(exc='%s: %s' % (type(e).__name__, e))
                try:
                    sys.stdout.flush()
                    data = pickle.dumps(o)
                    while data: data = data[os.write(wfd, data):]
                finally:
                    os._exit(0)
            os.close(wfd)
            data, st, hg = wait_child(pid, rfd, twall)
            if data is None:
                crashed += 1; inconcl += 1; hung += hg
                if verbose: print('trial %d: child %s, inconclusive' % (t, 'killed after %ds wall' % twall if hg else 'died (status %d)' % st))
                continue
            o = pickle.loads(data)
            if 'exc' in o: raise RuntimeError('trial %d: %s' % (t, o['exc']))
            for k, (ar, fs, fr) in o['new'].items(): arity[k] = ar; FSKIP[k] = fs; FREGS[k] = fr
        ncalls += o['ncalls']; learned[0] += o['learned']
        if o.get('pw'): pread |= o['pread']; pwatched[0] += 1
        called |= o.get('called', set())
        if o['why']:
            differ = 'trial %d: %s' % (t, o['why'])
            break
        if o['ok']: ok += 1
        else: inconcl += 1
    res = dict(func=func, file=p, ret=rk, ref_words=len(rwords), cand_words=len(cwords), ok=ok, inconclusive=inconcl, learned=learned[0], crashed=crashed, hung=hung)
    if differ:
        line = 'DIFFER %s: %s' % (func, differ); res['result'] = 'DIFFER'; res['why'] = differ
    elif ok < max(4, trials // 8):
        line = 'UNSURE %s: only %d trials ran to completion (%d faulted/timed out)' % (func, ok, inconcl); res['result'] = 'UNSURE'
    else:
        line = 'EQUIV %s (%d trials ok, %d inconclusive, %d calls, ret=%s, ref %d words, cand %d words%s)' % (
            func, ok, inconcl, ncalls, rk, len(rwords), len(cwords),
            ', %d trials via learned pointer inputs' % learned[0] if learned[0] else '') + (' [%d trials crashed%s]' % (crashed, ', %d hung' % hung if hung else '') if crashed else ''); res['result'] = 'EQUIV'
    res['line'] = line + poke_notes(pread, pwatched[0]) + knob_notes(called, ok + inconcl)
    return res


def knob_notes(called, ntrials):
    """P93: DIFFTEST_RET / RETF / OUTW / OUTA / OUTB / ARGMEM keys whose callee the reference never called (a US
    address instead of the decoded EU jal target, e.g. func_1513D2F0 is jal 0x1513D860, or an unreached call)."""
    if not ntrials: return ''
    un = []
    for nm, d in (('RET', STUBRET), ('RETF', STUBRETF), ('OUTW', OUTW), ('OUTA', OUTA), ('OUTB', OUTB), ('ARGMEM', ARGMEM)):
        un += ['%s %08X' % (nm, a) for a in sorted(d) if a not in called]
    return ' [knob callee never called: %s]' % ', '.join(un) if un else ''


def poke_notes(pread, nwatched):
    """P93: DIFFTEST_POKE words the reference never read in trials 0-1 (a wrong address, e.g. the US address of a
    symbol: P90 poked D_800C3958 at 0x800C395C, its EU address is 0x800C3D78, and the knob silently did nothing), and
    pokes inside the ROM image (odd trials load the ROM .data / .rodata over them, so they only hold in even trials)."""
    out = ''
    if POKES and nwatched:
        un = sorted(a for a in POKES if a not in pread)
        if un: out += ' [POKE unread: %s]' % ','.join('%08X' % (0x80000000 | a) for a in un[:12]) + ('...' if len(un) > 12 else '')
    if POKES:
        rom = sorted(a for a in POKES if any(phys(v) <= a < phys(v) + len(b) for v, b, k in image() if k != 'code'))
        if rom: out += ' [POKE in ROM data (even trials only): %s]' % ','.join('%08X' % (0x80000000 | a) for a in rom[:12])
    return out


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
