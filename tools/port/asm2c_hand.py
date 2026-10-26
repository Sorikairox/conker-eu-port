#!/usr/bin/env python3
"""P56: mechanical translator of hand-written MIPS asm (splat .s listing) into register-level portable C.

Used for the hand-asm wall engine / ray cast of asm/D5E90.s (collision_walls_slide / collision_ledge_probe -> func_150AB708,
collision_ray_cast), whose helpers use private register conventions and jump through continuation pointers stored on the
stack. The output is one C function body per "machine": GPRs are u32 locals, FPRs a union array F[32] (FR=0, single
precision only), every instruction one C statement in program order; branch delay slots are executed after the branch
condition is evaluated (likely branches only when taken); `jal` to a label inside the machine sets ra to the return
address and jumps; `jr reg` goes through a switch over every code address the machine can hold in a register (return
addresses of internal jals, code labels loaded with %hi / %lo). `jal` to code outside the machine becomes an ordinary C
call (EXTERN table below). The stack is a local buffer; sp holds its address.

Usage: asm2c_hand.py ASM NAME START END [START END ...] [eENTRY ...] > out.inc
   (ranges are vram [start, end) of the instructions that make up the machine)"""
import re, sys, os

GPR = ['zero', 'at', 'v0', 'v1', 'a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3', 't4', 't5', 't6', 't7',
       's0', 's1', 's2', 's3', 's4', 's5', 's6', 's7', 't8', 't9', 'k0', 'k1', 'gp', 'sp', 'fp', 'ra']

# C call for each external callee: registers in, registers out (o32: ints a0-a3, floats f12 / f14, v0 / f0 out)
EXTERN = {
    'obj_collision_cylinder': 'v0 = obj_collision_cylinder((struct127 *) a0, (s16 *) a1, (s16 *) a2, (s16 *) a3);',
    'func_150A69A8': 'v0 = func_150A69A8((s32) a0, (s32) a1, (s32 *) a2, (s32) a3);',
    'world_objects_transform_mesh': 'v0 = world_objects_transform_mesh((s32) a0, (s32 *) a1, (s32) a2);',
    'quadtree_set_test_box': 'quadtree_set_test_box(F[12].f, F[14].f, U2F(a2));',
    'math_atan2f': 'F[0].f = math_atan2f(F[12].f, F[14].f);',
    'collision_select_area': 'collision_select_area((s32) a0);',
    'sinf': 'F[0].f = sinf(F[12].f);',
    'cosf': 'F[0].f = cosf(F[12].f);',
}

LINE = re.compile(r'^\s*/\*\s*[0-9A-F]+\s+([0-9A-F]{8})\s+([0-9A-F]{8})\s*\*/\s*(.*)$')
LABEL = re.compile(r'^\s*(?:glabel\s+([A-Za-z_0-9.]+)|(\.L[0-9A-F]+):)\s*$')

def decode_word(w, addr):
    """the few encodings that splat left as .word (func_150AACF4)"""
    op = w >> 26; rs = (w >> 21) & 31; rt = (w >> 16) & 31; rd = (w >> 11) & 31; imm = w & 0xFFFF
    simm = imm - 0x10000 if imm & 0x8000 else imm
    g = lambda i: '$' + GPR[i]
    if w == 0: return 'nop', []
    if op == 0x0F: return 'lui', [g(rt), hex(imm)]
    if op == 0x09: return 'addiu', [g(rt), g(rs), str(simm)]
    if op == 0x31: return 'lwc1', ['$f%d' % rt, '%d(%s)' % (simm, g(rs))]
    if op == 0x03: return 'jal', ['ABS_%08X' % (((addr + 4) & 0xF0000000) | ((w & 0x3FFFFFF) << 2))]
    if op == 0x05: return 'bne', [g(rs), g(rt), 'ABS_%08X' % (addr + 4 + 4 * simm)]
    if op == 0x00:
        fn = w & 63
        if fn == 0x25: return 'or', [g(rd), g(rs), g(rt)]
        if fn == 0x24: return 'and', [g(rd), g(rs), g(rt)]
        if fn == 0x08: return 'jr', [g(rs)]
    if op == 0x11:
        fmt = rs; ft = rt; fs = rd; fd = (w >> 6) & 31; fn = w & 63
        if fmt == 4: return 'mtc1', [g(rt), '$f%d' % fs]
        if fmt == 8:
            tf = (w >> 16) & 3
            return ['bc1f', 'bc1t', 'bc1fl', 'bc1tl'][tf], ['ABS_%08X' % (addr + 4 + 4 * simm)]
        if fmt == 16:
            names = {0: 'add.s', 1: 'sub.s', 2: 'mul.s', 3: 'div.s', 5: 'abs.s', 6: 'mov.s', 7: 'neg.s',
                     0x32: 'c.eq.s', 0x34: 'c.olt.s', 0x35: 'c.ult.s', 0x36: 'c.ole.s', 0x37: 'c.ule.s'}
            n = names[fn]
            if n.startswith('c.'): return n, ['$f%d' % fs, '$f%d' % ft]
            if fn in (5, 6, 7): return n, ['$f%d' % fd, '$f%d' % fs]
            return n, ['$f%d' % fd, '$f%d' % fs, '$f%d' % ft]
    raise ValueError('cannot decode .word %08X at %08X' % (w, addr))

def parse(path):
    insns = []; labels = {}; pend = []
    for ln in open(path):
        m = LABEL.match(ln)
        if m: pend.append(m.group(1) or m.group(2)); continue
        m = LINE.match(ln)
        if not m: continue
        addr = int(m.group(1), 16); word = int(m.group(2), 16); txt = m.group(3).split('/*')[0].strip()
        for p in pend: labels[p] = addr
        pend = []
        if txt.startswith('.word'):
            try: op, args = decode_word(word, addr)
            except (ValueError, KeyError): op, args = '.word', [hex(word)]
        else:
            parts = txt.split(None, 1)
            op = parts[0]; args = [a.strip() for a in re.split(r',(?![^(]*\))', parts[1])] if len(parts) > 1 else []
        insns.append((addr, op, args))
    reloc_data(insns, labels)
    return insns, labels

CTRL = ('j', 'jal', 'jr', 'jalr', 'b', 'beq', 'bne', 'beql', 'bnel', 'beqz', 'bnez', 'blez', 'bgez', 'bltz', 'bgtz',
        'beqzl', 'bnezl', 'bc1t', 'bc1f', 'bc1tl', 'bc1fl')

def reloc_data(insns, labels):
    """P62: a raw-word `lui r, 0x80xx` (RDRAM, kseg0) whose register is then used as the base of loads / stores /
    addiu in the same straight-line run is a %hi / %lo pair of a data symbol: rewrite it to %hi(D_X) / %lo(D_X) so the C
    takes `(u32) &D_X` (the literal N64 address does not exist in a port). D_X must be declared in the including file."""
    at_label = set(labels.values())
    for k, (a, op, args) in enumerate(insns):
        if op != 'lui' or args[1].startswith('%'): continue
        hi = eval(args[1], {}) & 0xFFFF
        if not 0x8000 <= hi < 0x8080: continue
        r = args[0]; uses = []; j = k + 1; stop = None
        while j < len(insns) and stop is None:
            a2, op2, ar2 = insns[j]
            if a2 in at_label: break
            if op2 in CTRL: stop = j + 1
            for i, x in enumerate(ar2):
                m = re.match(r'^(-?\d+)\((\$[a-z0-9]+)\)$', x)
                if m and m.group(2) == r: uses.append((j, i, int(m.group(1))))
            if op2 == 'addiu' and ar2[1] == r: uses.append((j, 2, int(ar2[2])))
            if ar2 and ar2[0] == r and not op2.startswith(('s', 'b')) and op2 not in CTRL: break   # redefined
            j += 1
            if stop is not None and j <= stop and j < len(insns) and insns[j][0] not in at_label:
                a2, op2, ar2 = insns[j]
                for i, x in enumerate(ar2):
                    m = re.match(r'^(-?\d+)\((\$[a-z0-9]+)\)$', x)
                    if m and m.group(2) == r: uses.append((j, i, int(m.group(1))))
        addrs = {(hi << 16) + off for _, _, off in uses}
        if not uses: continue
        if len(addrs) != 1:
            raise ValueError('lui %s at %08X serves several data addresses %s' % (r, a, sorted(map(hex, addrs))))
        sym = 'D_%08X' % addrs.pop()
        insns[k] = (a, op, [r, '%%hi(%s)' % sym])
        for j, i, off in uses:
            a2, op2, ar2 = insns[j]; ar2 = list(ar2)
            ar2[i] = ('%%lo(%s)(%s)' % (sym, r)) if '(' in ar2[i] else '%%lo(%s)' % sym
            insns[j] = (a2, op2, ar2)

TRACE = os.environ.get('ASM2C_TRACE')

def main():
    path, name = sys.argv[1], sys.argv[2]
    entries = [int(x[1:], 16) for x in sys.argv[3:] if x.startswith('e')]
    nums = [x for x in sys.argv[3:] if not x.startswith('e')]
    rngs = [(int(nums[i], 16), int(nums[i + 1], 16)) for i in range(0, len(nums), 2)]
    allins, labels = parse(path)
    inr = lambda a: any(lo <= a < hi for lo, hi in rngs)
    ins = [x for x in allins if inr(x[0])]
    byaddr = {a: k for k, (a, _, _) in enumerate(ins)}
    addr_of = dict(labels)
    def tgt(s):
        if s.startswith('ABS_'): return int(s[4:], 16)
        if s in addr_of: return addr_of[s]
        raise KeyError(s)
    datasyms = set()
    def reg(s):
        s = s.strip()
        assert s.startswith('$'), s
        n = s[1:]
        if n == 'zero': return '0'
        if n[0] == 'f' and n[1:].isdigit(): raise ValueError(s)
        return n
    def freg(s): return int(s.strip()[2:])
    def imm(s):
        s = s.strip()
        m = re.match(r'^%(hi|lo)\(([A-Za-z_0-9]+)(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?\)$', s)
        if m:
            sym, off = m.group(2), int(m.group(3), 0) if m.group(3) else 0
            if sym in addr_of and inr(addr_of[sym]) or sym in addr_of and sym.startswith(('func_150A', 'D_150A')):
                v = addr_of[sym] + off
                if m.group(1) == 'hi': return '0x%X' % (((v + 0x8000) >> 16) & 0xFFFF), None
                lo = v & 0xFFFF
                return str(lo - 0x10000 if lo & 0x8000 else lo), None
            datasyms.add(sym)
            e = '(u32) &%s' % sym + (' + 0x%X' % off if off else '')
            return ('HI(%s)' if m.group(1) == 'hi' else 'LO(%s)') % e, sym
        return str(eval(s, {})), None
    def mem(s):
        m = re.match(r'^(.*)\((\$[a-z0-9]+)\)$', s.strip())
        off = m.group(1).strip() or '0'
        o, _ = imm(off)
        return '%s + %s' % (reg(m.group(2)), o) if o != '0' else reg(m.group(2))
    retaddrs = set(); codevals = set()
    out = []
    def label(a): return 'L_%08X' % a
    used_labels = set()
    def stmt(k):
        """C for instruction k (not a control transfer)"""
        a, op, args = ins[k]
        if op == 'nop': return ''
        if op == '.word': return '/* data %s */' % args[0]
        def setr(d, e): return '' if d == '0' else '%s = %s;' % (d, e)
        A = args
        if op in ('addiu', 'addi', 'addu', 'add'):
            if op in ('addiu', 'addi'):
                v, sym = imm(A[2])
                if not sym and A[2].startswith('%lo'):
                    codevals.add(None)
                return setr(reg(A[0]), '%s + %s' % (reg(A[1]), v))
            return setr(reg(A[0]), '%s + %s' % (reg(A[1]), reg(A[2])))
        if op in ('subu', 'sub'): return setr(reg(A[0]), '%s - %s' % (reg(A[1]), reg(A[2])))
        if op == 'and': return setr(reg(A[0]), '%s & %s' % (reg(A[1]), reg(A[2])))
        if op == 'or': return setr(reg(A[0]), '%s | %s' % (reg(A[1]), reg(A[2])))
        if op == 'xor': return setr(reg(A[0]), '%s ^ %s' % (reg(A[1]), reg(A[2])))
        if op == 'slt': return setr(reg(A[0]), '(s32) %s < (s32) %s' % (reg(A[1]), reg(A[2])))
        if op == 'sltu': return setr(reg(A[0]), '%s < %s' % (reg(A[1]), reg(A[2])))
        if op == 'slti': return setr(reg(A[0]), '(s32) %s < %s' % (reg(A[1]), imm(A[2])[0]))
        if op == 'andi': return setr(reg(A[0]), '%s & %s' % (reg(A[1]), imm(A[2])[0]))
        if op == 'ori': return setr(reg(A[0]), '%s | %s' % (reg(A[1]), imm(A[2])[0]))
        if op == 'xori': return setr(reg(A[0]), '%s ^ %s' % (reg(A[1]), imm(A[2])[0]))
        if op == 'lui':
            v, sym = imm(A[1])
            if sym: return setr(reg(A[0]), v)
            if A[1].startswith('%hi'): return setr(reg(A[0]), '%s << 16' % v)   # code label address
            return setr(reg(A[0]), '0x%X' % ((eval(A[1], {}) & 0xFFFF) << 16))
        if op == 'sll': return setr(reg(A[0]), '%s << %s' % (reg(A[1]), imm(A[2])[0]))
        if op == 'srl': return setr(reg(A[0]), '%s >> %s' % (reg(A[1]), imm(A[2])[0]))
        if op == 'sra': return setr(reg(A[0]), '(u32) ((s32) %s >> %s)' % (reg(A[1]), imm(A[2])[0]))
        if op == 'sllv': return setr(reg(A[0]), '%s << (%s & 31)' % (reg(A[1]), reg(A[2])))
        if op == 'mult': return 'MULT(%s, %s);' % (reg(A[0]), reg(A[1]))
        if op == 'div':
            r0 = A[0] if len(A) == 2 else A[1]; r1 = A[1] if len(A) == 2 else A[2]
            return 'DIV(%s, %s);' % (reg(r0), reg(r1))
        if op == 'mflo': return setr(reg(A[0]), 'lo')
        if op == 'mfhi': return setr(reg(A[0]), 'hi')
        L = {'lw': 'LW', 'lh': 'LH', 'lhu': 'LHU', 'lb': 'LB', 'lbu': 'LBU'}
        if op in L: return setr(reg(A[0]), '%s(%s)' % (L[op], mem(A[1])))
        S = {'sw': 'SW', 'sh': 'SH', 'sb': 'SB'}
        if op in S: return '%s(%s, %s);' % (S[op], mem(A[1]), reg(A[0]))
        if op == 'lwc1': return 'F[%d].u = LW(%s);' % (freg(A[0]), mem(A[1]))
        if op == 'swc1': return 'SW(%s, F[%d].u);' % (mem(A[1]), freg(A[0]))
        if op == 'mtc1': return 'F[%d].u = %s;' % (freg(A[1]), reg(A[0]))
        if op == 'mfc1': return setr(reg(A[0]), 'F[%d].u' % freg(A[1]))
        B = {'add.s': '+', 'sub.s': '-', 'mul.s': '*', 'div.s': '/'}
        if op in B: return 'F[%d].f = F[%d].f %s F[%d].f;' % (freg(A[0]), freg(A[1]), B[op], freg(A[2]))
        if op == 'mov.s': return 'F[%d].f = F[%d].f;' % (freg(A[0]), freg(A[1]))
        if op == 'neg.s': return 'F[%d].u = F[%d].u ^ 0x80000000;' % (freg(A[0]), freg(A[1]))
        if op == 'abs.s': return 'F[%d].u = F[%d].u & 0x7FFFFFFF;' % (freg(A[0]), freg(A[1]))
        if op == 'sqrt.s': return 'F[%d].f = sqrtf(F[%d].f);' % (freg(A[0]), freg(A[1]))
        if op == 'cvt.s.w': return 'F[%d].f = (f32) F[%d].i;' % (freg(A[0]), freg(A[1]))
        if op == 'cvt.w.s': return 'F[%d].i = CVTW(F[%d].f);' % (freg(A[0]), freg(A[1]))
        if op == 'trunc.w.s': return 'F[%d].i = (s32) F[%d].f;' % (freg(A[0]), freg(A[1]))
        C = {'c.eq.s': '%s == %s', 'c.olt.s': '%s < %s', 'c.ole.s': '%s <= %s', 'c.ult.s': '!(%s >= %s)',
             'c.ule.s': '!(%s > %s)'}
        if op in C:
            x, y = 'F[%d].f' % freg(A[0]), 'F[%d].f' % freg(A[1])
            return 'cc = %s;' % (C[op] % (x, y))
        raise ValueError('op %s at %08X' % (op, a))
    BR = {'beq': '%s == %s', 'bne': '%s != %s', 'beql': '%s == %s', 'bnel': '%s != %s'}
    BZ = {'beqz': '%s == 0', 'bnez': '%s != 0', 'blez': '(s32) %s <= 0', 'bgez': '(s32) %s >= 0',
          'bltz': '(s32) %s < 0', 'bgtz': '(s32) %s > 0', 'beqzl': '%s == 0', 'bnezl': '%s != 0'}
    FB = {'bc1t': 'cc', 'bc1f': '!cc', 'bc1tl': 'cc', 'bc1fl': '!cc'}
    def jump(t):
        if t in byaddr: used_labels.add(t); return 'goto %s;' % label(t)
        raise ValueError('jump out of the machine to %08X' % t)
    k = 0; slots = set()
    while k < len(ins):
        a, op, args = ins[k]
        lines = ['@%08X@' % a]
        if op in BR or op in BZ or op in FB or op in ('j', 'jal', 'jr'):
            slot = stmt(k + 1); slots.add(k + 1)
            likely = op.endswith('l') and op not in ('jal',)
            if op in BR: cond = BR[op] % (reg(args[0]), reg(args[1])); t = tgt(args[2])
            elif op in BZ: cond = BZ[op] % reg(args[0]); t = tgt(args[1])
            elif op in FB: cond = FB[op]; t = tgt(args[0])
            if op in BR or op in BZ or op in FB:
                if likely: lines.append('if (%s) { %s %s }' % (cond, slot, jump(t)))
                else: lines.append('c = %s; %s if (c) %s' % (cond, slot, jump(t)))
            elif op == 'j':
                lines.append('%s %s' % (slot, jump(tgt(args[0]))))
            elif op == 'jal':
                nm = args[0]
                t = tgt(nm) if (nm in addr_of or nm.startswith('ABS_')) else None
                if t is not None and t in byaddr:
                    ra = a + 8; retaddrs.add(ra)
                    lines.append('ra = 0x%X; %s %s' % (ra, slot, jump(t)))
                else:
                    if nm not in EXTERN: raise ValueError('extern %s at %08X' % (nm, a))
                    lines.append('%s %s' % (slot, EXTERN[nm]))
            else:
                lines.append('pc = %s; %s goto dispatch;' % (reg(args[0]), slot))
            out.append(' '.join(lines))
            if k + 1 < len(ins):
                a2 = ins[k + 1][0]
                # the slot instruction as a branch target of its own
                out.append('@IF0@%08X@%s' % (a2, stmt(k + 1)))
            k += 2
            continue
        out.append(lines[0] + stmt(k))
        k += 1
    # code addresses a register can hold: return addresses + code labels referenced by %hi/%lo
    for (a, op, args) in ins:
        for s in args:
            m = re.match(r'^%hi\(([A-Za-z_0-9]+)\)$', s)
            if m and m.group(1) in addr_of and addr_of[m.group(1)] in byaddr: codevals.add(addr_of[m.group(1)])
    codevals.discard(None)
    codevals.update(entries)
    print('/* generated by tools/port/asm2c_hand.py from %s: %s, %s */' % (
        path.split('/')[-1], name, ', '.join('[%08X, %08X)' % r for r in rngs)))
    need = used_labels | retaddrs | codevals
    for ln in out:
        if ln.startswith('@IF0@'):
            a2 = int(ln[5:13], 16)
            if a2 in need: print('    if (0) { %s: %s }' % (label(a2), ln[14:]))
            continue
        a = int(ln[1:9], 16); body = ln[10:].strip()
        if a in need: print('%s:' % label(a)); print('    NMW_TRACE(0x%X);' % a) if TRACE else None
        if body: print('    ' + body)
    # binary if-tree, not a switch: IDO would put a jump table in .rodata, which the NON_MATCHING link parks NOLOAD
    print('dispatch:')
    vals = sorted(retaddrs | codevals)
    def tree(lo, hi, ind):
        if hi - lo <= 3:
            for v in vals[lo:hi]: print('%sif (pc == 0x%X) goto %s;' % (ind, v, label(v)))
            return
        mid = (lo + hi) // 2
        print('%sif (pc < 0x%X) {' % (ind, vals[mid]))
        tree(lo, mid, ind + '    ')
        print('%s} else {' % ind)
        tree(mid, hi, ind + '    ')
        print('%s}' % ind)
    print('    if (pc == NMW_RET) goto done;')
    tree(0, len(vals), '    ')
    print('    goto bad;')
    sys.stderr.write('%s: %d insns, %d dispatch targets, data symbols: %s\n' % (
        name, len(ins), len(retaddrs | codevals), ' '.join(sorted(datasyms))))

if __name__ == '__main__':
    main()
