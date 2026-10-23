#!/usr/bin/env python3
"""P106: knob setups for the event VM func_150ADFD0: real event blocks from the ROM and synthetic scripts per
opcode family, assembled into an event block at BLK (DIFFTEST_POKE words). Output: vm_setups.txt (knobs.sh format:
name ! ARG ! POKE ! RET ...). Run with DIFFTEST_ROMDATA=1 (the VM's jump / opcode tables are .data).
usage: gen_vm.py ROM > vm_setups.txt"""
import struct, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
BLK = 0x80490000
DATA, VARS = 0x300, 0x200
FR, VA, DA, IM, LB, RS, NA = range(7)
E8BE9A0 = 0x800BEDC0          # D_800BE9A0 (u8) EU address
STK_TOP = 0x800D3C80 + 0x17FC  # operand stack top

def ins(op, *opds, wide=False):
    """opds: (mode, value). Returns halfwords."""
    w = op | (0x40 if wide else 0)
    for k, (m, v) in enumerate(opds):
        w |= m << (13, 10, 7)[k]
    hw = [w]
    lw = wide
    for m, v in opds:
        if m in (IM, LB, NA) and lw:
            hw += [(v >> 16) & 0xFFFF, v & 0xFFFF]; lw = False
        else:
            hw.append(v & 0xFFFF)
    return hw

def block(code, entries=(), flags=0x1000, varsz=0x40, data_words=(), var_words=()):
    """code: list of halfwords at +0x20 (or a dict offset->halfwords). Returns POKE words {addr: value}."""
    b = bytearray(0x400)
    hdr = [flags, 0, 0x340, varsz, DATA, VARS, 0] + list(entries) + [0] * (4 - len(entries))
    struct.pack_into('>11H', b, 0, *hdr)
    if isinstance(code, dict):
        for off, h in code.items(): struct.pack_into('>%dH' % len(h), b, off, *h)
    else:
        struct.pack_into('>%dH' % len(code), b, 0x20, *code)
    for i, w in enumerate(data_words): struct.pack_into('>i', b, DATA + 4 * i, w)
    for i, w in enumerate(var_words): struct.pack_into('>i', b, VARS + 4 * i, w)
    return b

def poke(b, n=None):
    n = n or len(b)
    ws = struct.unpack('>%dI' % (n // 4), bytes(b[:n]))
    return ','.join('%X=%X' % (BLK + 4 * i, w) for i, w in enumerate(ws))

def line(name, b, entry=0, extra='', ret='', n=None):
    p = poke(b, n) + (',' + extra if extra else '')
    return '%s ! 0=%X,1=%X ! %s ! %s ! ! ! !' % (name, BLK, entry, p, ret)

def prog(*parts):
    hw = []
    for p in parts: hw += p
    return hw

ENTER = lambda n=0x10: ins(0x1B, (IM, n))
RET = ins(0x1C)
RETV = lambda m, v: ins(0x1A, (m, v))
out = []
def reloc(raw):
    """as func_1509B950 (block at BLK): variables after the script at an 8-aligned offset, cleared"""
    b = bytearray(raw)
    size, varsz = struct.unpack_from('>HH', b, 4)
    pos = (size + (8 - ((BLK + size) & 7))) & 0xFFFF
    struct.pack_into('>H', b, 0xA, pos)
    b += bytearray(pos + varsz + 8 - len(b))
    return b + bytearray((-len(b)) % 4)
# ---- real blocks
from evasset import load
rom = sys.argv[1]
import evasset
for i, ents in ((0xC9, range(5)),):
    raw = load(i)
    b = reloc(raw)
    for e in ents:
        out.append(line('rom%X_e%d' % (i, e), b, e))
# a few bigger real blocks, entries 0..4 (natives are stubs; the run follows the stub results)
for i in (0x11, 0x2A, 0x64, 0xCA, 0xD0, 0x120):
    try: raw = load(i)
    except Exception: raw = None
    if not raw or len(raw) > 0x1800: continue
    b = reloc(raw)
    for e in range(5):
        out.append(line('rom%X_e%d' % (i, e), b, e))

# ---- arithmetic / compare: dest var 0, sources in several modes
srcs = {'imm': ((IM, 7), (IM, -3)), 'var': ((VA, 4), (VA, 8)), 'frm': ((FR, -4), (FR, -8)), 'res': ((RS, 0), (IM, 2)),
        'dat': ((DA, 0x10), (IM, 3)), 'neg': ((IM, -20), (IM, 3)), 'big': ((VA, 12), (VA, 16)), 'eq': ((IM, 7), (VA, 20))}
VW = [0, 1000, -77, 0x7FFFFFF0, 0x12345, 7, 0]
for op in list(range(1, 6)) + list(range(9, 0xE)) + list(range(0x12, 0x18)):
    for sn, (s1, s2) in srcs.items():
        code = prog(ENTER(), ins(0x0E, (FR, -4), (IM, 11)), ins(0x0E, (FR, -8), (IM, -5)),
                    ins(op, (VA, 0), s1, s2), ins(op, (FR, -12), s2, s1), RET)
        out.append(line('op%02X_%s' % (op, sn), block(code, var_words=VW), extra='%X=0000002A' % 0x800D3C68))
# div / mod by zero and INT_MIN / -1 (VR4300 results)
for op in (4, 5):
    for nm, a_, b_ in (('z', 7, 0), ('zn', -7, 0), ('m1', -0x80000000, -1), ('m1b', 5, -1), ('m1c', -9, -1)):
        code = prog(ENTER(), ins(op, (VA, 0), (VA, 4), (VA, 8)), RET)
        out.append(line('op%02X_%s' % (op, nm), block(code, var_words=[0, a_, b_])))
# two-operand ops: neg / lognot / bitnot / move
for op in (6, 7, 8, 0xE):
    for sn, s in (('imm', (IM, 5)), ('zero', (IM, 0)), ('var', (VA, 4)), ('res', (RS, 0)), ('dat', (DA, 8)), ('frm', (FR, 8))):
        code = prog(ENTER(), ins(op, (VA, 0), s), ins(op, (RS, 0), (VA, 0)), ins(op, (FR, -4), (VA, 0)), RET)
        out.append(line('op%02X_%s' % (op, sn), block(code, var_words=VW)))
# long immediates in each position
for nm, code in (('w1', ins(0x18, (IM, 0x12345678), wide=True) + ins(0x0E, (VA, 0), (FR, -4 - 4))),
                 ('w2', ins(0x01, (VA, 0), (IM, 0x00100002), (IM, 3), wide=True)),
                 ('w3', ins(0x01, (VA, 0), (VA, 4), (IM, -0x76543210 & 0xFFFFFFFF), wide=True)),
                 ('w23', ins(0x02, (VA, 0), (IM, 0x7FFF0001), (IM, 0x7FFF), wide=True)),
                 ('wnone', ins(0x01, (VA, 0), (VA, 4), (VA, 8), wide=True) + ins(0x01, (VA, 12), (IM, 1), (IM, 2)))):
    out.append(line('long_' + nm, block(prog(ENTER(), code, RET), var_words=VW)))
# jumps: F / 10 / 11, taken and not taken (targets are block offsets)
def jprog(op, cond):
    # +0x20 enter; +0x24 jump; ...; target sets var0 = 1, fallthrough sets var0 = 2
    head = ENTER() + ins(0x0E, (VA, 4), (IM, cond))
    j = ins(op, (LB, 0)) if op == 0xF else ins(op, (VA, 4), (LB, 0))
    pre = 0x20 + 2 * (len(head) + len(j))
    fall = ins(0x0E, (VA, 0), (IM, 2)) + RET
    tgt = pre + 2 * len(fall)
    j = ins(op, (LB, tgt)) if op == 0xF else ins(op, (VA, 4), (LB, tgt))
    return head + j + fall + ins(0x0E, (VA, 0), (IM, 1)) + RET
for op in (0xF, 0x10, 0x11):
    for c in (0, 1, -1):
        out.append(line('jmp%02X_c%d' % (op, c), block(jprog(op, c))))
# loop: count var4 down from 5, accumulate into var0 (backward jz / jnz / jump)
code = ENTER() + ins(0x0E, (VA, 4), (IM, 5))
loop = 0x20 + 2 * len(code)
code += ins(0x01, (VA, 0), (VA, 0), (VA, 4)) + ins(0x02, (VA, 4), (VA, 4), (IM, 1)) + ins(0x11, (VA, 4), (LB, loop)) + RET
out.append(line('loop_jnz', block(code)))
# push / script call / enter / return value / frame args
def callprog(retop, nargs, pushmode):
    sub_off = 0x100
    main = ENTER(8)
    for k in range(nargs):
        main += ins(0x18, pushmode(k))
    main += ins(0x19, (LB, sub_off)) + ins(0x0E, (VA, 0), (RS, 0)) + ins(0x0E, (VA, 4), (FR, -4)) + RET
    sub = ENTER(4) + ins(0x0B, (FR, -4), (FR, 8), (FR, 12)) + ins(0x0E, (VA, 8), (FR, 4)) + retop
    return {0x20: main, sub_off: sub}
for rn, rop in (('retv', RETV(FR, -4)), ('retimm', RETV(IM, 99)), ('ret', RET)):
    for pn, pm in (('imm', lambda k: (IM, 10 + k)), ('var', lambda k: (VA, 4 * k)), ('dat', lambda k: (DA, 4 * k)),
                   ('res', lambda k: (RS, 0)), ('frm', lambda k: (FR, -4 - 4 * k))):
        for n in (0, 2, 3):
            out.append(line('call_%s_%s%d' % (rn, pn, n), block(callprog(rop, n, pm), var_words=VW),
                            extra='%X=00000005' % 0x800D3C68))
# script call from a frame-less main: the callee's return leaves sp == top and must go on (asm: sp < top)
code = {0x20: ins(0x19, (LB, 0x80)) + ins(0x0E, (VA, 0), (RS, 0)) + RET, 0x80: ENTER(4) + RETV(IM, 9)}
out.append(line('call_noenter', block(code)))
# nested script calls (3 deep, recursion on a counter)
code = {0x20: ENTER() + ins(0x0E, (VA, 0), (IM, 3)) + ins(0x19, (LB, 0x80)) + ins(0x0E, (VA, 4), (RS, 0)) + RET,
        0x80: ENTER(4) + ins(0x02, (VA, 0), (VA, 0), (IM, 1)) + ins(0x10, (VA, 0), (LB, 0xC0)) + ins(0x19, (LB, 0x80))
              + ins(0x01, (VA, 8), (VA, 8), (RS, 0)) + RETV(IM, 7)}
code[0xC0] = RETV(VA, 8)
out.append(line('call_nested', block(code, var_words=[0, 0, 1])))
# natives: external entries (0, 1, 2, 13: stubs) with pushed args; result used after the call
for idx in (0, 1, 2, 13):
    for n in (0, 1, 3):
        code = ENTER()
        for k in range(n): code += ins(0x18, (IM, 0x100 + k))
        code += ins(0x19, (NA, idx)) + ins(0x0E, (VA, 0), (RS, 0)) + ins(0x01, (VA, 4), (RS, 0), (IM, 1)) + RET
        out.append(line('nat%d_n%d' % (idx, n), block(code)))
        out.append(line('nat%d_n%d_r0' % (idx, n), block(code), ret='1509E120=0,1509E130=0,1509E140=0,1509E150=0'))
# internal natives (test candidate maps them to the C functions): dispatchers 3..6 with nibble 0..F, 7 random,
# 8 frame count, 9 / 10 timers
for idx in (3, 4, 5, 6):
    for idw in (0x0005, 0x1003, 0x2010, 0x5ABC, 0xF001, 0x12345 | 0x40000):
        code = ENTER() + ins(0x18, (IM, 77)) + ins(0x18, (IM, idw & 0xFFFF) if idw < 0x8000 else (IM, idw), wide=idw >= 0x8000) \
               + ins(0x19, (NA, idx)) + ins(0x0E, (VA, 0), (RS, 0)) + RET
        out.append(line('nat%d_id%X' % (idx, idw), block(code)))
for idx in (7, 8, 9, 10):
    for v in (0, 1, 2, 3, 5, -1, -2, -3, -5, 100, -0x80000000, 0x7FFFFFFF):
        for fr in (1, 2, 4):
            if idx == 8 and v != 0: continue
            code = ENTER() + ins(0x18, (VA, 4)) + ins(0x19, (NA, idx)) + ins(0x0E, (VA, 0), (RS, 0)) + RET
            out.append(line('nat%d_v%X_f%d' % (idx, v & 0xFFFFFFFF, fr), block(code, var_words=[0, v]),
                            extra='%X=%08X' % (E8BE9A0, fr << 24)))
# arrays 1D / 1E
for k in (0, 1, 3, -1):
    code = ENTER() + ins(0x1E, (IM, 55 + k), (VA, 8), (IM, k)) + ins(0x1D, (VA, 0), (VA, 8), (IM, k)) \
           + ins(0x1D, (FR, -4), (DA, 0), (VA, 4)) + RET
    out.append(line('arr_k%d' % k, block(code, var_words=[0, 2, 0, 0, 0], data_words=[11, 22, 33, 44])))
# quirks: operand 1 in mode 5 as a source (push), operand 3 in mode 2 (reads as 5), entries 1..4
code = ENTER() + ins(0x18, (RS, 0)) + ins(0x0E, (VA, 0), (FR, -8)) + ins(0x01, (VA, 4), (IM, 1), (DA, 0x40)) + RET
out.append(line('quirk_res_dat', block(code)))
code = {0x20: ENTER() + ins(0x0E, (VA, 0), (IM, 1)) + RET}
for e, off in enumerate((0x40, 0x50, 0x60, 0x70)):
    code[off] = ENTER() + ins(0x0E, (VA, 0), (IM, 10 + e)) + RET
for e in range(5):
    out.append(line('entry%d' % e, block(code, entries=(0x40, 0x50, 0x60, 0x70)), e))
print('\n'.join(out))
