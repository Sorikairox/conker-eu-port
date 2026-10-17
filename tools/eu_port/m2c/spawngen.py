#!/usr/bin/env python3
"""Bulk C drafts for the effect-spawner family, read straight from the asm.

usage: spawngen.py <outdir> [func ...]   (default: every asm function under conker/asm/nonmatchings
       that calls func_15149130/func_151491F4 and then memcpy, and nothing else)

Shape (session 9): build a parameter struct on the stack, call the spawner (A = func_15149130,
9 args; B = func_151491F4, 8 args), and if it returned non-NULL memcpy the struct to ret + 0x28.
Optional `if (arg0 == NULL) return;` guard and `return ret;`. A small symbolic interpreter of the
asm recovers the struct fields (stores into [X, X+size) of the memcpy source), the call args
(a0-a3 at the jal and the 0x10.. stack slots) and the parameter types (lbu/lb/lh/lhu/lw/lwc1 of
arg homes, loads through an arg -> u8 *, mtc1 from an arg register -> f32).

Writes <outdir>/v<k>/<func>.c (variants: temp_v0 declared after/before the struct, assignments in
struct order / asm store order) and prints one line per function (OK n-variants, or SKIP reason).
Then screen.py each vK (container), merge.py, apply.py.
"""
import os, re, sys, glob, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import rodasm

ROOT = os.path.expanduser('~/conker/conker')
LINE = re.compile(r'/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/\s+(\S+)\s*(.*)')
CALLEE = {'func_15149130': 9, 'func_151491F4': 8}
PURE = {'func_150ADA20': ('$v0', 'u'), 'func_150ADA68': ('$f0', 'f')}   # no-arg helpers (random u8 / f32)
_SYMS = []


class Skip(Exception):
    pass


def owned(stem):
    y = open(os.path.join(ROOT, 'conker.eu.yaml')).read()
    return re.search(r'\.rodata,\s*%s\]' % re.escape(stem), y) is not None


def fval(sym):
    if not _SYMS:
        _SYMS.append(rodasm.load_syms())
    va = _SYMS[0].get(sym)
    if va is None:
        m = re.match(r'D_([0-9A-F]{8})$', sym)
        va = int(m.group(1), 16) if m else None
    if va is not None:
        for lo, hi, dv in rodasm.rodata_ranges():
            if lo <= va < hi:
                return struct.unpack('>f', rodasm._CACHE['bin'][va - dv:va - dv + 4])[0]
    raise Skip('no value for ' + sym)


def fval_ok(sym):
    try:
        fval(sym)
        return True
    except Skip:
        return False


_DECL = {}


def declared(sym):
    if not _DECL:
        for h in ('variables.h',):
            for l in open(os.path.join(ROOT, 'include', h)):
                m = re.match(r'extern\s+(\w+)\s+(\w+);', l)
                if m:
                    _DECL[m.group(2)] = m.group(1)
    return _DECL.get(sym, None if sym not in open(os.path.join(ROOT, 'include', 'variables.h')).read() else '?')


def flit(v):
    if v == int(v) and abs(v) < 1e7:
        return '%d.0f' % int(v)
    for p in range(6, 10):
        t = '%.*g' % (p, v)
        if struct.unpack('>f', struct.pack('>f', float(t)))[0] == v:
            break
    if 'e' not in t and '.' not in t:
        t += '.0'
    return t + 'f'


def bits2f(b):
    return struct.unpack('>f', struct.pack('>I', b & 0xFFFFFFFF))[0]


class E:
    def __init__(self, t, k='x', v=None, arg=None):
        self.t, self.k, self.v, self.arg = t, k, v, arg   # k: c const, a arg, s sp-address, r ret, f float, x other

    def __repr__(self):
        return self.t


def imm(s):
    s = s.strip()
    m = re.match(r'\((0x[0-9A-Fa-f]+) >> 16\)$', s)
    if m:
        return int(m.group(1), 16) >> 16
    if s.startswith('%'):
        raise Skip('reloc ' + s)
    return -int(s[1:], 0) if s.startswith('-') else int(s, 0)


def mem(op):
    m = re.match(r'(.*)\((\$\w+)\)$', op)
    return m.group(1), m.group(2)


class Sim:
    def __init__(self, path):
        self.name = os.path.basename(path)[:-2]
        self.stem = os.path.basename(os.path.dirname(path))
        self.ins = []
        for l in open(path):
            m = LINE.search(l)
            if m:
                ops = [x.strip() for x in m.group(3).split(',')] if m.group(3).strip() else []
                self.ins.append((m.group(2), ops))
            elif re.match(r'\s*\.L\w+:', l):
                self.ins.append(('label', [l.strip()[:-1]]))
        self.R = {'$zero': E('0', 'c', 0)}
        self.ptypes = {}
        self.nargs = 0
        self.stores = {}
        self.seq = 0
        self.guard = False
        self.ret = False
        self.call = None
        self.src = self.size = None
        self.post = False
        self.externs = []
        self.own = owned(self.stem)
        self.his = {}

    def setp(self, k, t):
        self.nargs = max(self.nargs, k + 1)
        cur = self.ptypes.get(k)
        if cur is None or cur == 's32':
            self.ptypes[k] = t
        elif t != 's32' and t != cur:
            raise Skip('arg%d %s/%s' % (k, cur, t))

    def arg(self, k, t='s32'):
        self.setp(k, t)
        return E('arg%d' % k, 'a', arg=k)

    def val(self, r):
        if r in self.R:
            return self.R[r]
        if r in ('$a0', '$a1', '$a2', '$a3') and not self.post:
            return self.arg(int(r[2]))
        if r.startswith('$f') and r in ('$f12', '$f14') and not self.post:
            return self.arg((int(r[2:]) - 12) // 2, 'f32')
        raise Skip('reg ' + r)

    def global_(self, sym, t):
        d = declared(sym)
        if d is None:
            self.externs.append('extern %s %s;' % (t, sym))
            return sym
        if d == t:
            return sym
        return '*(%s *)&%s' % (t, sym)

    def floatE(self, sym):
        if self.own:
            return E(flit(fval(sym)), 'f')
        self.externs.append('extern f32 %s;' % sym)
        return E(sym, 'f')

    def deref(self, e, off, t):
        if e.k == 'a':
            self.setp(e.arg, 'u8 *')
        elif e.k != 'x' or not e.t.startswith('arg'):
            if e.k != 'p':
                raise Skip('deref of ' + e.t)
        if t == 'u8':
            return E('%s[0x%X]' % (e.t, off))
        return E('*(%s *)(%s + 0x%X)' % (t, e.t, off), 'f' if t == 'f32' else 'x')

    def load(self, op, dst, src):
        o, b = mem(src)
        t = {'lw': 's32', 'lbu': 'u8', 'lb': 's8', 'lh': 's16', 'lhu': 'u16', 'lwc1': 'f32'}[op]
        if o.startswith('%lo('):
            sym = o[4:-1]
            if self.his.get(b) != sym:
                raise Skip('data load ' + sym)
            if op == 'lwc1' and fval_ok(sym):
                self.R[dst] = self.floatE(sym)
            else:
                self.R[dst] = E(self.global_(sym, t), 'f' if t == 'f32' else 'x')
            return
        off = imm(o)
        if b == '$sp':
            if off >= self.frame:
                k, byte = divmod(off - self.frame, 4)
                width = {'lw': 4, 'lwc1': 4, 'lbu': 1, 'lb': 1, 'lh': 2, 'lhu': 2}[op]
                if byte + width != 4:
                    raise Skip('odd arg load')
                self.R[dst] = self.arg(k, t)
            elif off in self.stores:
                self.R[dst] = self.stores[off][1]
            else:
                raise Skip('local load')
            return
        e = self.deref(self.val(b), off, t)
        if op == 'lw':
            e.blk = (self.val(b).t, off)
        self.R[dst] = e

    def store(self, op, srcr, dst):
        o, b = mem(dst)
        off = imm(o)
        e = self.val(srcr)
        if b == '$sp':
            if off >= self.frame:
                k = (off - self.frame) // 4
                if e.k == 'a' and e.arg == k:
                    self.nargs = max(self.nargs, k + 1)
                    return
                raise Skip('store to arg area')
        else:
            be = self.val(b)
            if be.k != 's':
                raise Skip('store through ' + be.t)
            if getattr(e, 'blk', None) and op == 'sw':
                self.stores[off + be.v] = ('blk', e, self.seq, be.v)
                self.seq += 1
                return
            off += be.v
        w = {'sw': 4, 'swc1': 4, 'sh': 2, 'sb': 1}[op]
        self.stores[off] = (op, e, self.seq, None)
        self.seq += 1

    def step(self, op, o):
        R = self.R
        if op in ('sw', 'lw') and o[0] in ('$ra', '$s0', '$s1') and o[1].endswith('($sp)') and \
                (o[0] == '$ra' or op == 'lw' or o[0] not in R):
            return
        if op in ('lw', 'lbu', 'lb', 'lh', 'lhu', 'lwc1'):
            self.load(op, o[0], o[1])
        elif op in ('sw', 'sb', 'sh', 'swc1'):
            self.store(op, o[0], o[1])
        elif op == 'addiu':
            if o[0] == '$sp':
                if not hasattr(self, 'frame'):
                    self.frame = -imm(o[2])
                return
            if o[2].startswith('%lo('):
                raise Skip('addiu reloc')
            s, v = o[1], imm(o[2])
            if s == '$zero':
                R[o[0]] = E(str(v) if -10 < v < 10 else ('0x%X' % v if v > 0 else '-0x%X' % -v), 'c', v)
            elif s == '$sp':
                R[o[0]] = E('sp%X' % v, 's', v)
            else:
                e = self.val(s)
                if e.k == 'a':
                    self.setp(e.arg, 'u8 *')
                    R[o[0]] = E('%s + 0x%X' % (e.t, v), 'p')
                elif e.k == 'r':
                    R[o[0]] = E('%s + 0x%X' % (e.t, v), 'p')
                elif e.k == 'c':
                    R[o[0]] = E(str(e.v + v), 'c', e.v + v)
                elif e.k in ('x', 'u'):
                    R[o[0]] = E('%s + %d' % (e.t, v) if v >= 0 else '%s - %d' % (e.t, -v), 'x')
                else:
                    raise Skip('addiu of ' + e.t)
        elif op == 'lui':
            if o[1].startswith('%hi('):
                self.his[o[0]] = o[1][4:-1]
                R.pop(o[0], None)
            else:
                v = imm(o[1]) << 16
                R[o[0]] = E('0x%X' % v, 'c', v)
        elif op == 'ori':
            e = self.val(o[1])
            if e.k != 'c':
                raise Skip('ori')
            v = e.v | imm(o[2])
            R[o[0]] = E('0x%X' % v, 'c', v)
        elif op in ('or', 'move', 'addu') and (op == 'move' or o[2] == '$zero'):
            R[o[0]] = self.val(o[1])
        elif op == 'mtc1':
            e = self.val(o[0])
            if e.k == 'c':
                R[o[1]] = E(flit(bits2f(e.v)), 'f')
            elif e.k == 'a':
                self.ptypes[e.arg] = 'f32'
                R[o[1]] = e
            else:
                raise Skip('mtc1')
        elif op == 'mov.s':
            R[o[0]] = self.val(o[1])
        elif op == 'sll' and o[2] in ('16', '24'):
            R[o[0]] = E('sll', 'sll', int(o[2]), arg=self.val(o[1]))
        elif op == 'sra':
            e = self.val(o[1])
            if e.k != 'sll' or e.v != int(o[2]) or e.arg.k not in ('a', 'x', 'u'):
                raise Skip('sra')
            if e.arg.k != 'a':
                R[o[0]] = e.arg
                return
            self.setp(e.arg.arg, 's16' if e.v == 16 else 's8')
            R[o[0]] = e.arg
        elif op == 'andi' and o[2] in ('0xFF', '0xFFFF'):
            e = self.val(o[1])
            if e.k != 'a':
                raise Skip('andi')
            self.setp(e.arg, 'u8' if o[2] == '0xFF' else 'u16')
            R[o[0]] = e
        elif op in ('divu', 'div'):
            x, y = self.val(o[1]), self.val(o[2])
            if op == 'divu' and y.k == 'c':
                y = E('%dU' % y.v, 'c', y.v)
            self.hilo = (x, y)
        elif op in ('mfhi', 'mflo'):
            x, y = self.hilo
            R[o[0]] = E('(%s %s %s)' % (x.t, '%' if op == 'mfhi' else '/', y.t), 'x')
        elif op in ('mul.s', 'add.s', 'sub.s', 'div.s'):
            x, y = self.val(o[1]), self.val(o[2])
            R[o[0]] = E('(%s %s %s)' % (x.t, {'mul.s': '*', 'add.s': '+', 'sub.s': '-', 'div.s': '/'}[op], y.t), 'f')
        elif op == 'nop':
            pass
        else:
            raise Skip('op %s' % op)

    def run(self):
        ins = self.ins
        calls = [o[0] for op, o in ins if op == 'jal' and o[0] not in PURE]
        if len(calls) != 2 or calls[1] != 'memcpy' or calls[0] not in CALLEE:
            raise Skip('calls %s' % ','.join(calls))
        self.callee = calls[0]
        i = 0
        while i < len(ins):
            op, o = ins[i]
            i += 1
            if op == 'label':
                continue
            if op in ('bnez', 'beqz', 'b', 'jal', 'jr'):
                dop, do = ins[i]
                i += 1
                if op == 'jr':
                    break
                self.step(dop, do)
                if op == 'jal':
                    self.jal(o[0])
                elif op in ('bnez', 'beqz') and not self.post:
                    e = self.val(o[0])
                    if e.k != 'a' or e.arg != 0:
                        raise Skip('branch on ' + e.t)
                    self.setp(0, 'u8 *')
                    self.guard = True
                    if op == 'bnez':     # guard path follows: skip to the target label
                        tgt = o[1]
                        j = i
                        while ins[j] != ('label', [tgt]):
                            if ins[j] == ('or', ['$v0', '$zero', '$zero']):
                                self.ret = True
                            j += 1
                        i = j
                elif op == 'beqz' and self.post:
                    if self.val(o[0]).k != 'r':
                        raise Skip('post branch')
                elif op == 'b':
                    raise Skip('b')
                continue
            if self.post and op == 'or' and o[:2] == ['$v0', '$v1']:
                self.ret = True
                continue
            self.step(op, o)
        if self.call is None or self.size is None:
            raise Skip('incomplete')

    def jal(self, f):
        if f in PURE:
            if self.post:
                raise Skip('pure call after spawn')
            keep = {r: e for r, e in self.R.items() if r in ('$zero', '$s0', '$s1')}
            self.R = keep
            r, k = PURE[f]
            self.R[r] = E('%s()' % f, k)
            return
        if f == self.callee:
            args = [self.val('$a%d' % k) for k in range(4)]
            for k in range(CALLEE[f] - 4):
                off = 0x10 + 4 * k
                if off not in self.stores:
                    raise Skip('stack arg %d' % (k + 4))
                args.append(self.stores.pop(off)[1])
            self.call = args
            self.post = True
            self.R = {'$zero': E('0', 'c', 0), '$v0': E('temp_v0', 'r')}
        else:
            if self.val('$a0').t != 'temp_v0 + 0x28':
                raise Skip('memcpy dst')
            s, z = self.val('$a1'), self.val('$a2')
            if s.k != 's' or z.k != 'c':
                raise Skip('memcpy src')
            self.src, self.size = s.v, z.v

    def fields(self):
        F = []
        for off in sorted(self.stores):
            op, e, seq, bstart = self.stores[off]
            if not self.src <= off < self.src + self.size:
                continue           # spill of v0 etc.
            r = off - self.src
            if op == 'blk':
                b0, o0 = e.blk
                if off == bstart:
                    F.append([r, 4, E('*(Blk%d *)(%s + 0x%X)' % (4, b0, o0) if o0 else '*(Blk%d *)%s' % (4, b0)), seq, b0, o0])
                    continue
                f = F[-1]
                if len(f) != 6 or f[0] + f[1] != r or f[4] != b0 or f[5] + f[1] != o0:
                    raise Skip('block copy shape')
                f[1] += 4
                f[2] = E('*(Blk%d *)(%s + 0x%X)' % (f[1], b0, f[5]) if f[5] else '*(Blk%d *)%s' % (f[1], b0))
                continue
            if op == 'swc1':
                t = 'f32'
            elif op == 'sh':
                t = 's16'
            elif op == 'sb':
                t = 'u8'
            elif e.k == 'a' and self.ptypes.get(e.arg) == 'u8 *':
                t = 'u8 *'
            elif e.k == 'f':
                t = 'f32'
            else:
                t = 's32'
            F.append((r, t, e, seq))
        return [tuple(f) if len(f) == 4 else (f[0], 'Blk%d' % f[1], f[2], f[3]) for f in F]

    def drafts(self):
        F = self.fields()
        size = {'f32': 4, 's32': 4, 'u8 *': 4, 's16': 2, 'u8': 1}
        decl = []
        pos = 0
        blks = sorted(set(t for r, t, e, seq in F if t.startswith('Blk')))
        for t in blks:
            size[t] = int(t[3:])
        for r, t, e, seq in F:
            if r < pos:
                raise Skip('overlap')
            if r > pos:
                decl.append('        u8 pad%X[%d];' % (pos, r - pos))
            decl.append('        %s%sunk%X;' % (t, '' if t.endswith('*') else ' ', r))
            pos = r + size[t]
        tail = self.size - pos
        params = []
        for k in range(self.nargs):
            t = self.ptypes.get(k, 's32')
            params.append('%s%sarg%d' % (t, '' if t.endswith('*') else ' ', k))
        sig = ', '.join(params) or 'void'
        rt = 'struct260 *' if self.ret else 'void '
        a = list(self.call)
        if self.callee == 'func_15149130' and a[6].k == 'p':
            a[6] = E('(struct37 *)(%s)' % a[6].t)
        if self.callee == 'func_15149130' and a[6].k == 'c' and a[6].v == 0:
            a[6] = E('NULL')
        call = '%s(%s)' % (self.callee, ', '.join(x.t for x in a))
        out = []
        for extra in (0, 4, 8):
          for vfirst in (0, 1):
            for asmord in (0, 1):
                dl = decl + (['        u8 pad%X[%d];' % (pos, tail + extra)] if tail + extra > 0 else [])
                Fs = sorted(F, key=lambda f: f[3]) if asmord else F
                b = ['%s%s(%s) {' % (rt, self.name, sig)]
                b += ['    typedef struct { s32 w[%d]; } %s;' % (int(t[3:]) // 4, t) for t in blks]
                b += ['    ' + x for x in sorted(set(self.externs))]
                st = ['    struct {'] + dl + ['    } tmp;']
                tv = ['    struct260 *temp_v0;']
                b += (tv + st if vfirst else st + tv) + ['']
                if self.guard:
                    b += ['    if (arg0 == NULL) {', '        return%s;' % (' NULL' if self.ret else ''), '    }']
                b += ['    tmp.unk%X = %s;' % (r, e.t) for r, t, e, s in Fs]
                b += ['    temp_v0 = %s;' % call, '    if (temp_v0 != NULL) {',
                      '        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x%X);' % self.size, '    }']
                if self.ret:
                    b += ['    return temp_v0;']
                b += ['}', '']
                out.append('\n'.join(b))
        return out


def candidates():
    for p in glob.glob(os.path.join(ROOT, 'asm/nonmatchings/*/*.s')):
        t = open(p).read()
        stem, fn = p.split('/')[-2], os.path.basename(p)[:-2]
        cf = os.path.join(ROOT, 'src_eu', stem + '.c')
        if not os.path.exists(cf) or '/%s.s"' % fn not in open(cf).read():
            continue
        if 'jal        memcpy' in t and re.search(r'jal\s+func_1514(9130|91F4)', t):
            yield p


def main():
    outdir = sys.argv[1]
    want = set(sys.argv[2:])
    n = 0
    for p in sorted(candidates()):
        name = os.path.basename(p)[:-2]
        if want and name not in want:
            continue
        try:
            s = Sim(p)
            s.run()
            ds = s.drafts()
        except (Skip, ValueError, KeyError, IndexError, AttributeError) as e:
            print('SKIP %s %s' % (name, e))
            continue
        for k, d in enumerate(ds):
            os.makedirs(os.path.join(outdir, 'v%d' % k), exist_ok=True)
            open(os.path.join(outdir, 'v%d' % k, name + '.c'), 'w').write(d)
        n += 1
        print('OK %s %d' % (name, len(ds)))
    print('%d functions' % n, file=sys.stderr)


if __name__ == '__main__':
    main()
