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
                       glob=0, globfix=0, other=0)
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
RENAME = re.compile(r'@(' + '|'.join(LIBC_CLASH) + r')\b(?![.\w])')


# Data symbols that the N64 link places at absolute addresses below the RAM range: ROM offsets (and a
# texture id) that the game uses as `&sym` and hands to the PI DMA / texture cache. In the port they
# must keep their absolute value, so every reference becomes a constant `inttoptr` and the external
# declaration is dropped (no zero-filled data stub is generated any more). Values: the symbol
# addresses in conker.eu.ld / port/stubs/stubs_report.txt (session P9).
ROM_ABS = {'D_11AF': 0x11AF, 'D_2D810': 0x2D810, 'D_1A3B40': 0x1A3B40, 'D_AB2240': 0xAB2240}
# Functions declared `extern s32 func_X;` and passed as callbacks (&func_X). Declaring them as
# functions makes &func_X a function-table index (registered by icall.py, stubbed by gen_stubs.py)
# instead of a zero-filled data stub. func_151DE100 is left alone: it is read as code bytes.
FUNC_AS_DATA = ['func_15033ECC', 'func_150D5634', 'func_150E394C', 'func_151BB690']
ABS_REF = re.compile(r'@(' + '|'.join(ROM_ABS) + r')\b(?![.\w])')
EXT_DECL = re.compile(r'^@([\w.$-]+) = external (?:dso_local )?global [^\n]*$', re.M)


def abs_syms(text, st):
    def decl(m):
        if m[1] in ROM_ABS:
            st['romabs_decl'] += 1
            return ''
        if m[1] in FUNC_AS_DATA:
            st['func_as_data'] += 1
            return f'declare void @{m[1]}()'
        return m[0]
    text = EXT_DECL.sub(decl, text)

    def ref(m):
        st['romabs_ref'] += 1
        return f'inttoptr (i32 {ROM_ABS[m[1]]} to ptr)'
    return ABS_REF.sub(ref, text)


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
    if st['rcp_io'] != n:
        if not re.search(r'^declare [^\n]*@__port_io_read\(', text, re.M):
            text += '\ndeclare i32 @__port_io_read(i32)\n'
        if not re.search(r'^declare [^\n]*@__port_io_write\(', text, re.M):
            text += '\ndeclare void @__port_io_write(i32, i32)\n'
    return text


def main():
    src, dst = sys.argv[1], sys.argv[2]
    st0 = collections.Counter()
    p = Pass(rcp_io(k0_checks(abs_syms(RENAME.sub(r'@vbe.\1', open(src).read()), st0), st0), st0).split('\n'))
    p.st.update(st0)
    if len(sys.argv) > 3:  # canonical signatures (port/tools/sigs.py, written by vbe_build.py)
        import json, sigs
        st = collections.Counter()
        p.lines = sigs.normalize(p.lines, json.load(open(sys.argv[3])), p.tmp, st)
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
