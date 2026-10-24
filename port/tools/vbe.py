"""vbe: give a game TU *virtual big-endian* memory semantics (docs/port/MEMORY.md, "Endianness").

Storage model ("word-swapped", the N64 emulator layout): every aligned 32-bit word holds its
big-endian value as a native little-endian i32. Then
    32-bit access at A (A % 4 == 0)   -> native access at A          (pointers, s32, f32: free)
    16-bit access at A (A % 2 == 0)   -> native access at A ^ 2
     8-bit access at A                -> native access at A ^ 3
    64-bit access at A (A % 4 == 0)   -> native i64 at A, halves swapped (rotate by 32)
and every mixed-width aliasing (an s32 read as two s16, a u8 read out of a u32) behaves as on the
N64. ROM bytes become this layout with one bswap32 per word, whatever the data format is.

This pass rewrites the LLVM IR of one TU, compiled at -O0 *before* any optimisation (clang's
little-endian load narrowing/combining then only ever sees the already-rewritten, LE-correct
program):
  * load/store i8, i16 (align >= 2), i64/double: address xor / half swap as above;
  * i16 with align 1, i32/float with align < 4: helper calls (__vbe_ld16u, __vbe_ld32u, ...);
  * llvm.memcpy/memmove/memset unless word-aligned with a constant multiple-of-4 length:
    __vbe_memcpy/__vbe_memmove/__vbe_memset;
  * global definitions: `constant` -> `global`, align >= 4, size padded to a multiple of 4 (so the
    xor permutation never leaves the object), and initialisers that contain 1/2/8-byte scalars get a
    descriptor + a constructor that converts them in place at startup (__vbe_fix).
usage: vbe.py in.ll out.ll  (prints one stats line)
"""
import collections, re, sys

# ---------------------------------------------------------------- type layout (wasm32 datalayout)
SCAL = {'i1': (1, 1), 'i8': (1, 1), 'i16': (2, 2), 'i32': (4, 4), 'i64': (8, 8), 'float': (4, 4),
        'double': (8, 8), 'ptr': (4, 4), 'i128': (16, 16), 'fp128': (16, 16)}


def split_top(s, sep=','):
    out, depth, cur, q = [], 0, [], False
    for ch in s:
        if ch == '"':
            q = not q
        if not q:
            if ch in '([{<':
                depth += 1
            elif ch in ')]}>':
                depth -= 1
        if ch == sep and depth == 0 and not q:
            out.append(''.join(cur)); cur = []
        else:
            cur.append(ch)
    out.append(''.join(cur))
    return [x.strip() for x in out]


def take_type(s):
    """Split a leading LLVM type off s -> (type, rest)."""
    s = s.lstrip()
    if s[0] in '[{<':
        close = {'[': ']', '{': '}', '<': '>'}
        depth = 0
        for i, ch in enumerate(s):
            if ch in '[{<(':
                depth += 1
            elif ch in ']}>)':
                depth -= 1
                if depth == 0:
                    return s[:i + 1], s[i + 1:]
        raise ValueError(s)
    m = re.match(r'(%[\w.$"-]+|i\d+|float|double|ptr|half|fp128|x86_fp80)', s)
    return m[1], s[m.end():]


class Layout:
    def __init__(self, named):
        self.named = named  # name -> body text
        self.memo = {}

    def info(self, t):
        """-> (size, align, leaves) ; leaves = [(off, size, count, stride)] for 1/2/8-byte scalars."""
        if t in self.memo:
            return self.memo[t]
        if t in SCAL:
            sz, al = SCAL[t]
            r = (sz, al, [(0, sz, 1, sz)] if sz in (1, 2, 8) else [])
        elif t.startswith('%'):
            body = self.named.get(t)
            if body is None or body == 'opaque':
                raise ValueError('opaque ' + t)
            r = self.info(body)
        elif t.startswith('['):
            m = re.match(r'\[\s*(\d+)\s+x\s+(.*)\]$', t, re.S)
            n, et = int(m[1]), m[2].strip()
            esz, eal, el = self.info(et)
            leaves = []
            for (o, s, c, st) in el:
                if c == 1:
                    leaves.append((o, s, n, esz))
                elif n * len(el) <= 4096:
                    leaves += [(i * esz + o, s, c, st) for i in range(n)]
                else:
                    raise ValueError('nested array too big ' + t)
            r = (esz * n, eal, leaves)
        elif t.startswith('{') or t.startswith('<{'):
            packed = t.startswith('<')
            inner = t[2:-2] if packed else t[1:-1]
            off, al, leaves = 0, 1, []
            for ft in (split_top(inner) if inner.strip() else []):
                fsz, fal, fl = self.info(ft)
                if not packed:
                    off = (off + fal - 1) // fal * fal
                    al = max(al, fal)
                leaves += [(off + o, s, c, st) for (o, s, c, st) in fl]
                off += fsz
            off = (off + al - 1) // al * al
            r = (off, al, leaves)
        elif t.startswith('<'):  # vector
            m = re.match(r'<\s*(\d+)\s+x\s+(.*)>$', t)
            esz, eal, el = self.info(m[2].strip())
            r = (esz * int(m[1]), esz * int(m[1]), [(o, s, int(m[1]), esz) for (o, s, c, st) in el])
        else:
            raise ValueError('type ' + t)
        self.memo[t] = r
        return r


# ---------------------------------------------------------------- rewriting
LOAD = re.compile(r'^(\s*)(%[\w.$-]+) = load (volatile )?(.*)$')
STORE = re.compile(r'^(\s*)store (volatile )?(.*)$')
MEMI = re.compile(r'^(\s*)(?:tail )?call void @llvm\.(memcpy|memmove|memset)\.[\w.]+\((.*)\)(.*)$')
GLOB = re.compile(r'^(@[\w.$"-]+) = ((?:[a-z_]+ )*?)(global|constant) (.*)$')
ALLOCA = re.compile(r'^(\s*%[\w.$"-]+ = alloca )(.*)$')
ALIGN = re.compile(r'align (\d+)')

DECLS = {
    '__vbe_ld16u': 'declare i16 @__vbe_ld16u(ptr)', '__vbe_st16u': 'declare void @__vbe_st16u(ptr, i16)',
    '__vbe_ld32u': 'declare i32 @__vbe_ld32u(ptr)', '__vbe_st32u': 'declare void @__vbe_st32u(ptr, i32)',
    '__vbe_memcpy': 'declare void @__vbe_memcpy(ptr, ptr, i32)',
    '__vbe_memmove': 'declare void @__vbe_memmove(ptr, ptr, i32)',
    '__vbe_memset': 'declare void @__vbe_memset(ptr, i32, i32)',
    '__vbe_fix': 'declare void @__vbe_fix(ptr, ptr, i32)',
    'llvm.fshl.i64': 'declare i64 @llvm.fshl.i64(i64, i64, i64)',
}


class Pass:
    def __init__(self, lines):
        self.lines = lines
        self.n = 0
        self.need = set()
        self.st = dict(ld8=0, st8=0, ld16=0, st16=0, ld64=0, st64=0, helper=0, mem=0, memkeep=0,
                       glob=0, globfix=0, other=0, alloca4=0, allocapad=0)
        named = {}
        for l in lines:
            m = re.match(r'^(%[\w.$"-]+) = type (.*)$', l)
            if m:
                named[m[1]] = m[2].strip()
        self.lay = Layout(named)

    def tmp(self):
        self.n += 1
        return f'%vbe.{self.n}'

    def xaddr(self, ind, p, x, out):
        a, b, c = self.tmp(), self.tmp(), self.tmp()
        out += [f'{ind}{a} = ptrtoint ptr {p} to i32', f'{ind}{b} = xor i32 {a}, {x}',
                f'{ind}{c} = inttoptr i32 {b} to ptr']
        return c

    def rot(self, ind, v, out):
        r = self.tmp()
        out.append(f'{ind}{r} = call i64 @llvm.fshl.i64(i64 {v}, i64 {v}, i64 32)')
        self.need.add('llvm.fshl.i64')
        return r

    def do_load(self, m, out):
        ind, res, vol, rest = m[1], m[2], m[3] or '', m[4]
        parts = split_top(rest)
        ty, ptr = parts[0], parts[1]
        if not ptr.startswith('ptr '):
            return False
        p = ptr[4:].strip()
        tail = ', ' + ', '.join(parts[2:]) if len(parts) > 2 else ''
        al = ALIGN.search(tail)
        al = int(al[1]) if al else SCAL.get(ty, (1, 1))[1]
        if ty in ('i8', 'i1'):
            q = self.xaddr(ind, p, 3, out); self.st['ld8'] += 1
            out.append(f'{ind}{res} = load {vol}{ty}, ptr {q}{tail}')
        elif ty == 'i16' and al >= 2:
            q = self.xaddr(ind, p, 2, out); self.st['ld16'] += 1
            out.append(f'{ind}{res} = load {vol}{ty}, ptr {q}{tail}')
        elif ty == 'i16':
            out.append(f'{ind}{res} = call i16 @__vbe_ld16u(ptr {p})'); self.need.add('__vbe_ld16u')
            self.st['helper'] += 1
        elif ty in ('i64', 'double') and al >= 4:
            v = self.tmp(); self.st['ld64'] += 1
            out.append(f'{ind}{v} = load {vol}i64, ptr {p}{tail}')
            r = self.rot(ind, v, out)
            out.append(f'{ind}{res} = ' + (f'bitcast i64 {r} to double' if ty == 'double' else f'or i64 {r}, 0'))
        elif ty in ('i32', 'float') and al < 4:
            self.need.add('__vbe_ld32u'); self.st['helper'] += 1
            if ty == 'i32':
                out.append(f'{ind}{res} = call i32 @__vbe_ld32u(ptr {p})')
            else:
                v = self.tmp()
                out += [f'{ind}{v} = call i32 @__vbe_ld32u(ptr {p})', f'{ind}{res} = bitcast i32 {v} to float']
        elif ty in ('i32', 'float', 'ptr'):
            return False
        else:
            self.st['other'] += 1
            return False
        return True

    def do_store(self, m, out):
        ind, vol, rest = m[1], m[2] or '', m[3]
        parts = split_top(rest)
        ty, val = take_type(parts[0])
        val = val.strip()
        ptr = parts[1]
        if not ptr.startswith('ptr '):
            return False
        p = ptr[4:].strip()
        tail = ', ' + ', '.join(parts[2:]) if len(parts) > 2 else ''
        al = ALIGN.search(tail)
        al = int(al[1]) if al else SCAL.get(ty, (1, 1))[1]
        if ty in ('i8', 'i1'):
            q = self.xaddr(ind, p, 3, out); self.st['st8'] += 1
            out.append(f'{ind}store {vol}{ty} {val}, ptr {q}{tail}')
        elif ty == 'i16' and al >= 2:
            q = self.xaddr(ind, p, 2, out); self.st['st16'] += 1
            out.append(f'{ind}store {vol}{ty} {val}, ptr {q}{tail}')
        elif ty == 'i16':
            out.append(f'{ind}call void @__vbe_st16u(ptr {p}, i16 {val})'); self.need.add('__vbe_st16u')
            self.st['helper'] += 1
        elif ty in ('i64', 'double') and al >= 4:
            v = val
            if ty == 'double':
                v = self.tmp(); out.append(f'{ind}{v} = bitcast double {val} to i64')
            r = self.rot(ind, v, out); self.st['st64'] += 1
            out.append(f'{ind}store {vol}i64 {r}, ptr {p}{tail}')
        elif ty in ('i32', 'float') and al < 4:
            v = val
            if ty == 'float':
                v = self.tmp(); out.append(f'{ind}{v} = bitcast float {val} to i32')
            out.append(f'{ind}call void @__vbe_st32u(ptr {p}, i32 {v})'); self.need.add('__vbe_st32u')
            self.st['helper'] += 1
        elif ty in ('i32', 'float', 'ptr'):
            return False
        else:
            self.st['other'] += 1
            return False
        return True

    def do_alloca(self, m, out):
        """P185: stack slots get IDO's layout: every alloca starts on a word (align >= 4; 8-byte types keep clang's
        align 8) and a fixed-size slot is padded to a multiple of 4 bytes. So no two locals share a word: a 32-bit
        access to a 2-aligned `s16 x[2]` (passed as `s32 *`, P178 func_1509B8FC) or an xor-2 / xor-3 sub-word access
        can no longer reach a neighbouring slot."""
        parts = split_top(m[2])
        ty, rest = parts[0].strip(), [x.strip() for x in parts[1:]]
        al = next((int(x.split()[1]) for x in rest if x.startswith('align ')), 1)
        hascount = any(not x.startswith('align ') and not x.startswith('addrspace') for x in rest)
        try:
            size = self.lay.info(ty)[0]
        except (ValueError, TypeError, AttributeError):
            size = None
        nal = max(al, 4)
        if size is not None and size >= 8 and self.lay.info(ty)[1] >= 8:
            nal = max(nal, 8)
        nty = ty
        if not hascount and size is not None and size % 4:
            nty = f'<{{ {ty}, [{4 - size % 4} x i8] }}>'
            self.st['allocapad'] += 1
        if nal == al and nty == ty:
            return False
        if nal != al:
            self.st['alloca4'] += 1
        rest = [x for x in rest if not x.startswith('align ')] + [f'align {nal}']
        out.append(m[1] + ', '.join([nty] + rest))
        return True

    def do_mem(self, m, out):
        ind, kind, args = m[1], m[2], split_top(m[3])
        def strip_attrs(a):  # "ptr align 4 %x" -> ("%x", 4)
            t = a.split()
            al = int(t[t.index('align') + 1]) if 'align' in t else 1
            return t[-1] if not t[-1].startswith('noundef') else t[-2], al
        d, dal = strip_attrs(args[0])
        ln = args[2].split()[-1]
        if kind == 'memset':
            v = args[1].split()[-1]
            ok = dal >= 4 and ln.lstrip('-').isdigit() and int(ln) % 4 == 0
            if ok:
                self.st['memkeep'] += 1
                return False
            x = self.tmp()
            out.append(f'{ind}{x} = zext i8 {v} to i32')
            out.append(f'{ind}call void @__vbe_memset(ptr {d}, i32 {x}, i32 {ln})')
        else:
            s, sal = strip_attrs(args[1])
            if dal >= 4 and sal >= 4 and ln.isdigit() and int(ln) % 4 == 0:
                self.st['memkeep'] += 1
                return False
            out.append(f'{ind}call void @__vbe_{kind}(ptr {d}, ptr {s}, i32 {ln})')
        self.need.add('__vbe_' + kind); self.st['mem'] += 1
        return True

    def do_global(self, m, out, fixes):
        name, attrs, kw, rest = m[1], m[2], m[3], m[4]
        if name.startswith('@llvm.') or 'external' in attrs.split():
            return False
        ty, rest2 = take_type(rest)
        parts = split_top(rest2)
        init, opts = parts[0], parts[1:]
        try:
            size, _, leaves = self.lay.info(ty)
        except ValueError:
            self.st['other'] += 1
            return False
        opts = [o for o in opts if not o.startswith('align ')]
        al = ALIGN.search(rest2)
        al = max(4, int(al[1]) if al else 4)
        pad = (-size) % 4
        if pad:
            ty2 = f'<{{ {ty}, [{pad} x i8] }}>'
            init = 'zeroinitializer' if init == 'zeroinitializer' else f'<{{ {ty} {init}, [{pad} x i8] zeroinitializer }}>'
            ty = ty2
        attrs = attrs.replace('unnamed_addr ', '')  # objects must not be merged/rewritten as constants
        out.append(f'{name} = {attrs}global {ty} {init}' + ''.join(', ' + o for o in opts) + f', align {al}')
        self.st['glob'] += 1
        if leaves and init not in ('zeroinitializer', 'undef', 'poison'):
            fixes.append((name, leaves, ty, size))
        return True

    def run(self):
        out, fixes = [], []
        for l in self.lines:
            done = False
            if l.startswith('  '):
                m = LOAD.match(l)
                if m:
                    done = self.do_load(m, out)
                else:
                    m = STORE.match(l)
                    if m:
                        done = self.do_store(m, out)
                    else:
                        m = MEMI.match(l)
                        if m:
                            done = self.do_mem(m, out)
                        else:
                            m = ALLOCA.match(l)
                            if m:
                                done = self.do_alloca(m, out)
            elif l.startswith('@'):
                m = GLOB.match(l)
                if m:
                    done = self.do_global(m, out, fixes)
            if not done:
                out.append(l)
        if fixes:
            self.st['globfix'] = len(fixes)
            calls = []
            for i, (g, leaves, ty, size) in enumerate(fixes):
                # header word 0: our layout size, word 1: LLVM's alloc size (checked at run time)
                words = ', '.join([f'i32 {size}', f'i32 ptrtoint (ptr getelementptr ({ty}, ptr null, i32 1) to i32)']
                                  + [f'i32 {x}' for lf in leaves for x in lf])
                out.append(f'@__vbe_desc.{i} = private constant [{4 * len(leaves) + 2} x i32] [{words}]')
                calls.append(f'  call void @__vbe_fix(ptr {g}, ptr @__vbe_desc.{i}, i32 {len(leaves)})')
            out += ['define internal void @__vbe_ctor() {'] + calls + ['  ret void', '}']
            if any(l.startswith('@llvm.global_ctors') for l in self.lines):
                raise SystemExit('vbe: TU already has llvm.global_ctors (not supported)')
            out.append('@llvm.global_ctors = appending global [1 x { i32, ptr, ptr }] '
                       '[{ i32, ptr, ptr } { i32 101, ptr @__vbe_ctor, ptr null }]')
            self.need.add('__vbe_fix')
        text = '\n'.join(out)
        for k in sorted(self.need):
            if not re.search(r'^declare [^\n]*@' + re.escape(k) + r'\(', text, re.M):
                text += '\n' + DECLS[k]
        return text + '\n'


# Game TUs that define libc names (the decomp's own libc/libultra) would replace emscripten's libc for
# the PC layer too (musl's vfprintf calling the game's vbe strlen/memcpy). They are renamed to
# @vbe.<name> in every game TU. List = game-defined symbols that libc.a/libcompiler_rt.a also define:
#   comm -12 <(llvm-nm --defined-only -j libc.a libcompiler_rt.a | sort -u) <(llvm-nm --defined-only -j port/build/vobj/*.o | sort -u)
LIBC_CLASH = ['ldiv', 'lldiv', 'memcpy', 'sinf', 'sqrtf', 'strchr', 'strlen', 'tanf']
# P25: libc names the game only *calls* (GLOBAL_ASM in the decomp) and that emscripten's libc would
# otherwise satisfy with host-byte semantics (bcopy/bzero on vbe memory) or a different algorithm
# (cosf). They get the same @vbe.<name> rename; port/ultra/pc_libc.c and pc_gu.c define them.
LIBC_VBE = ['bcopy', 'bzero', 'cosf']
RENAME = re.compile(r'@(' + '|'.join(LIBC_CLASH + LIBC_VBE) + r')\b(?![.\w])')
# P26: the decomp's NON_MATCHING `f32 sqrtf(f32 v) { return sqrtf(v); }` (init_eu_26860.c) relies on IDO's
# `#pragma intrinsic(sqrtf)`. Under clang -fno-builtin it is self-recursion, which -O1 turns into an endless
# loop (the first caller hung node after 5 frames). Inside a definition of one of these names, a call to
# itself becomes the LLVM intrinsic (IEEE sqrt, as the R4300's sqrt.s).
SELF_INTRINSIC = {'vbe.sqrtf': ('float', 'llvm.sqrt.f32')}


def self_intrinsic(text, st):
    for name, (ty, intr) in SELF_INTRINSIC.items():
        m = re.search(r'^define [^\n]*@' + re.escape(name) + r'\([^\n]*\{$', text, re.M)
        if not m:
            continue
        end = text.index('\n}', m.end())
        body = text[m.end():end]
        nb, n = re.subn(r'call (?:\w+ )*' + ty + r' @' + re.escape(name) + r'\(', f'call {ty} @{intr}(', body)
        if n:
            st['self_intrinsic'] += n
            text = text[:m.end()] + nb + text[end:]
            if not re.search(r'^declare [^\n]*@' + re.escape(intr) + r'\(', text, re.M):
                text += f'\ndeclare {ty} @{intr}({ty})\n'
    return text


# Data symbols that the N64 link places at absolute addresses below the RAM range: ROM offsets (and a
# texture id) that the game uses as `&sym` and hands to the PI DMA / texture cache. In the port they
# must keep their absolute value, so every reference becomes a constant `inttoptr` and the external
# declaration is dropped (no zero-filled data stub is generated any more). Values: the symbol
# addresses in conker.eu.ld / port/stubs/stubs_report.txt (session P9).
ROM_ABS = {'D_11AF': 0x11AF, 'D_2D810': 0x2D810, 'D_1A3B40': 0x1A3B40, 'D_AB2240': 0xAB2240,
           # P37: more absolute symbols used as numbers (undefined_syms_auto.txt): texture ids passed as &D_D11 /
           # &D_A4A to func_1510D66C (game_A9D90.c, game_eu_200480.c) and values &D_2C1 / &D_1C0 (game_eu_F2A30.c).
           # As data stubs they were wasm addresses: func_1510D66C stored the id in D_800DA37C (before its range
           # check), so func_1510D984 walked its cache tables up to 0x10xxxxxx and fed garbage to the inflater.
           'D_D11': 0xD11, 'D_A4A': 0xA4A, 'D_2C1': 0x2C1, 'D_1C0': 0x1C0,
           # P37: texture ids stored as D_89C / D_85D (boot screen func_151EC300, game_eu_216470.c), and the ROM range of
           # the fixed player-slot setup table that func_15016950 (game_eu_44010.c) DMAs: D_1A3750..D_1A3840..D_1A3B40.
           'D_89C': 0x89C, 'D_85D': 0x85D, 'D_1A3750': 0x1A3750, 'D_1A3840': 0x1A3840,
           # P228: texture ids D_88C (barrel menu title) / D_87B (fill bar) of the C barrel_menu_draw func_151ECE00
           # (port P226): as data stubs they were wasm addresses (0x10A377xx) -> func_1510D66C range -> fatal
           # func_150ADC50 + trap in func_1510D984 in the multiplayer barrel menu (frame 4442).
           'D_88C': 0x88C, 'D_87B': 0x87B}
# P233: link symbols whose value is the PHYSICAL / segment address of real RAM data (KSEG0 | value = that symbol).
# The C hands them to the RSP as pointers (gSPMatrix(&D_89810) = the identity matrix D_80089810 in the shadow pass of
# game_eu_1B1ED0.c); as zero data stubs the port drew with an all-zero view matrix. Every reference is renamed to the
# RAM symbol (n64mem.py mirrors it like any other D_800xxxxx). port/tools/romabs_check.py checks both tables.
RAM_ALIAS = {'D_89810': 'D_80089810'}
# Functions declared `extern s32 func_X;` and passed as callbacks (&func_X). Declaring them as
# functions makes &func_X a function-table index (registered by icall.py, stubbed by gen_stubs.py)
# instead of a zero-filled data stub. (func_151DE100 used to be a data stub, read as code bytes by func_151E86A4's
# checksum; since P127 the NON_MATCHING func_151E86A4 skips the checksum and func_151DE100 is C, so it is a
# plain function and n64mem.py relocates D_8009018C[0] to its table slot - P131.)
FUNC_AS_DATA = ['func_15033ECC', 'func_150D5634', 'func_150E394C', 'func_151BB690',
                'func_150ADC50',  # P23: debugger.c compares a thread pc with &func_150ADC50
                # P26: callbacks handed to func_1000FA64 / stored in D_800E0D64 / func_16001830.
                # func_1000EC24 (P26) dropped in P29: port P28 declares it as a function under NON_MATCHING.
                'func_15103AA0', 'func_15103910', 'func_150DE8AC', 'func_160036F0']
ABS_REF = re.compile(r'@(' + '|'.join(ROM_ABS) + r')\b(?![.\w])')
ALIAS_REF = re.compile(r'@(' + '|'.join(RAM_ALIAS) + r')\b(?![.\w])')
EXT_DECL = re.compile(r'^@([\w.$-]+) = external (?:dso_local )?global [^\n]*$', re.M)


def abs_syms(text, st):
    def decl(m):
        if m[1] in ROM_ABS:
            st['romabs_decl'] += 1
            return ''
        if m[1] in RAM_ALIAS:
            st['ramalias_decl'] += 1
            t = RAM_ALIAS[m[1]]
            # drop it when the module already declares / defines the target, else declare the target instead
            if re.search(r'^@' + t + r' = ', text, re.M):
                return ''
            return m[0].replace('@' + m[1] + ' ', '@' + t + ' ', 1)
        if m[1] in FUNC_AS_DATA:
            st['func_as_data'] += 1
            return f'declare void @{m[1]}()'
        return m[0]
    text = EXT_DECL.sub(decl, text)

    def ref(m):
        st['romabs_ref'] += 1
        return f'inttoptr (i32 {ROM_ABS[m[1]]} to ptr)'
    text = ABS_REF.sub(ref, text)

    def aref(m):
        st['ramalias_ref'] += 1
        return '@' + RAM_ALIAS[m[1]]
    return ALIAS_REF.sub(aref, text)


# KSEG0 pointer tests in Rare's audio code (session P9). The N64 code tells a resident pointer from an
# unloaded reference with (p & 0xFF000003) == 0x80000000, and a RAM pointer with
# K0_TO_PHYS(p) <= 0x800000. Port pointers are wasm addresses 0x10000000..0x15FFFFFF, so:
#   and p, 0xFF000003 ; icmp eq/ne 0x80000000   ->  and p, 0xF0000003 ; icmp eq/ne 0x10000000
#   and p, 0x1FFFFFFF ; icmp ugt 0x800000       ->  ... icmp ugt 0x16000000 (end of wasm memory)
# Unloaded references (ROM offset << 5 | tag, small offsets) keep failing the first test: their
# tag has the low bits set. Sites: init_1AAE0, init_15550, init_214F0 (the only ones in the game).
K0_AND = re.compile(r'^\s*(%[\w.$-]+) = and i32 %[\w.$-]+, (-16777213|536870911)$', re.M)


def k0_checks(text, st):
    names = {}
    def and_(m):
        names[m[1]] = m[2]
        if m[2] == '-16777213':
            st['k0_mask'] += 1
            return m[0].replace(', -16777213', ', -268435453')
        return m[0]
    text = K0_AND.sub(and_, text)
    if not names:
        return text
    def cmp(m):
        kind = names.get(m[2])
        if kind == '-16777213' and m[1] in ('eq', 'ne') and m[3] == '-2147483648':
            st['k0_cmp'] += 1
            return f'icmp {m[1]} i32 {m[2]}, 268435456'
        if kind == '536870911' and m[1] == 'ugt' and m[3] == '8388608':
            st['k0_ram'] += 1
            return f'icmp ugt i32 {m[2]}, 369098752'
        return m[0]
    return re.sub(r'icmp (\w+) i32 (%[\w.$-]+), (-?\d+)', cmp, text)


# P42: "is a KSEG0 pointer" tests on level-geometry vertex / DL pointers. Game pointers here are wasm addresses
# (>= 0x10000000, GLOBAL_BASE), never above 0x80000000, so each listed compare against the KSEG0 boundary is moved
# to the wasm data base 0x10000000. Small values (area-2 object vertex offsets <= 0x100000, segment addresses
# 0x0Exxxxxx) stay on the "not a pointer" side, as on the N64. Scoped by function, with the expected count:
#   func_15002008 (game_eu_2F180, leaf lists):        (u32)p < 0x80000001 -> (u32)p < 0x10000000
#   func_15002248 (game_eu_2F180, quadtree helper):   (u32)p < 0x80000001 -> (u32)p < 0x10000000
#   func_15004CE0 (game_30E90, DL MOVEWORD reloc):    unk4 < 0x80000000   -> unk4 < 0x10000000
# Not rewritten: func_15001460's `>= 0x100001` holds for wasm pointers as it is. List: docs/port/MEMORY.md.
K0_PTR_SITES = {
    'func_15002008': ('ult', '-2147483647', 1),
    'func_15002248': ('ult', '-2147483647', 1),
    'func_15004CE0': ('ult', '-2147483648', 1),
}


def k0_ptr_sites(text, st):
    out = []
    for blk in re.split(r'(?=^define )', text, flags=re.M):
        m = re.match(r'define [^@\n]*@(\w+)\(', blk)
        site = K0_PTR_SITES.get(m[1]) if m else None
        if site:
            op, c, want = site
            blk, n = re.subn(rf'icmp {op} i32 (%[\w.$-]+), {c}\b', rf'icmp {op} i32 \1, 268435456', blk)
            st['k0_ptr'] += n
            if n != want:
                sys.stderr.write(f'vbe.py: k0_ptr_sites {m[1]}: {n} compares rewritten, expected {want}\n')
        out.append(blk)
    return ''.join(out)


# P185: PHYS_TO_K0 on an address the PC layer already returns as a wasm pointer. func_151F3C4C (libultra/audio
# game_21FC90, the mixer's read callback, installed by func_15016170 since port P172) does `p = dma(...); p +=
# 0x80000000; bcopy(p, ...)`: the dma proc returns osVirtualToPhysical(buf), which is the wasm address on the PC
# (pc_os.c), so the add is dropped (+0). Without it the first mixer read traps (bcopy out of bounds, boot ~retrace 120).
K0_ADD_SITES = {'func_151F3C4C': 1}


def k0_add_sites(text, st):
    out = []
    for blk in re.split(r'(?=^define )', text, flags=re.M):
        m = re.match(r'define [^@\n]*@(\w+)\(', blk)
        want = K0_ADD_SITES.get(m[1]) if m else None
        if want:
            blk, n = re.subn(r'= add i32 (%[\w.$-]+), -2147483648$', r'= add i32 \1, 0', blk, flags=re.M)
            st['k0_add'] += n
            if n != want:
                sys.stderr.write(f'vbe.py: k0_add_sites {m[1]}: {n} adds rewritten, expected {want}\n')
        out.append(blk)
    return ''.join(out)

# P19: RCP / PI / SI register accesses through a constant KSEG1 address (rcp.h IO_READ / IO_WRITE in
# matched game C, e.g. `IO_READ(AI_LEN_REG)` in func_100095A0) are not memory on the PC. Constant
# 32-bit loads/stores in 0xA4000000..0xA4FFFFFF become calls to the PC register model
# (port/ultra/pc_os.c __port_io_read / __port_io_write). Non-constant addresses are left alone.
IO_LD = re.compile(r'^(\s*)(%[\w.$-]+) = load (?:volatile )?i32, ptr inttoptr \(i32 (-?\d+) to ptr\)(?:, align \d+)?$', re.M)
IO_ST = re.compile(r'^(\s*)store (?:volatile )?i32 ([^,]+), ptr inttoptr \(i32 (-?\d+) to ptr\)(?:, align \d+)?$', re.M)


def rcp_io(text, st):
    def isio(n):
        return 0xA4000000 <= (int(n) & 0xFFFFFFFF) <= 0xA4FFFFFF
    def ld(m):
        if not isio(m[3]):
            return m[0]
        st['rcp_io'] += 1
        return f'{m[1]}{m[2]} = call i32 @__port_io_read(i32 {m[3]})'
    def stv(m):
        if not isio(m[3]):
            return m[0]
        st['rcp_io'] += 1
        return f'{m[1]}call void @__port_io_write(i32 {m[3]}, i32 {m[2]})'
    n = st['rcp_io']
    text = IO_ST.sub(stv, IO_LD.sub(ld, text))
    # P42: IO_READ with a computed address, i.e. PHYS_TO_K1(x) = `or i32 x, 0xA0000000` -> inttoptr -> volatile
    # load (func_15001A08: IO_READ(osRomBase | 0xB0000D24), the cart word). The load becomes __port_io_read(x);
    # the register model answers the cart domain 0xB0000000.. with the big-endian ROM word.
    k1 = set(re.findall(r'^\s*(%[\w.$-]+) = or i32 %[\w.$-]+, -1610612736$', text, re.M))
    if k1:
        ptr = {}
        for m in re.finditer(r'^\s*(%[\w.$-]+) = inttoptr i32 (%[\w.$-]+) to ptr$', text, re.M):
            if m[2] in k1:
                ptr[m[1]] = m[2]
        def dld(m):
            if m[3] not in ptr:
                return m[0]
            st['rcp_io_dyn'] += 1
            return f'{m[1]}{m[2]} = call i32 @__port_io_read(i32 {ptr[m[3]]})'
        text = re.sub(r'^(\s*)(%[\w.$-]+) = load volatile i32, ptr (%[\w.$-]+)(?:, align \d+)?$', dld, text, flags=re.M)
        if st['rcp_io_dyn']:
            n = -1
    if st['rcp_io'] != n:
        if not re.search(r'^declare [^\n]*@__port_io_read\(', text, re.M):
            text += '\ndeclare i32 @__port_io_read(i32)\n'
        if not re.search(r'^declare [^\n]*@__port_io_write\(', text, re.M):
            text += '\ndeclare void @__port_io_write(i32, i32)\n'
    return text


def main():
    src, dst = sys.argv[1], sys.argv[2]
    st0 = collections.Counter()
    p = Pass(self_intrinsic(rcp_io(k0_add_sites(k0_ptr_sites(k0_checks(abs_syms(RENAME.sub(r'@vbe.\1', open(src).read()), st0), st0), st0), st0), st0), st0).split('\n'))
    p.st.update(st0)
    if len(sys.argv) > 3:  # canonical signatures (port/tools/sigs.py, written by vbe_build.py)
        import json, sigs
        st = collections.Counter()
        can = json.load(open(sys.argv[3]))
        for k in LIBC_VBE:  # sigdb is collected before the rename: alias @vbe.<name> (P25 names only;
            # aliasing LIBC_CLASH too would re-type _Litob's sret call to lldiv, a new link warning)
            if '@' + k in can:
                can['@vbe.' + k] = can['@' + k]
        p.lines = sigs.normalize(p.lines, can, p.tmp, st)
        p.st.update(st)
    # indirect calls -> site-typed trampolines with a signature check (port/tools/icall.py)
    import icall
    st2 = collections.Counter()
    p.lines, need = icall.rewrite(p.lines, st2)
    regs = icall.registrations(p.lines)
    p.st.update(st2)
    open(dst, 'w').write(icall.epilogue(p.run(), need, regs))
    open(dst + '.isig', 'w').write(''.join(sorted({w + '\n' for _, w in regs})))
    print(src, ' '.join(f'{k}={v}' for k, v in p.st.items() if v))


if __name__ == '__main__':
    main()
