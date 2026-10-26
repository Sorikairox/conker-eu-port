#!/usr/bin/env python3
"""P40: whole-pipeline check of the level visibility data build, asm vs NON_MATCHING C, on real level data.

Reference: build/conker.eu.elf (collision_build_level_tris / collision_scan_level_dl / func_15001A08 / func_15002008 / func_15002248 /
func_150183D0 + func_150184B0 are asm). Candidate: build_nm/conker.eu.elf (all C), on the reference's .game_data
image (+ its own .nm_rodata). Both run in Unicorn MIPS32 (no 64-bit instructions on this path).

Per trial:
  - the level model list (asset (4, level), Python zlib on the ROM record) is placed in RAM and relocated as
    level_load_models + gfx_dl_relocate_segments do (parts 0-3: D_800B0E00[i], vertex base hdr + 0x28 + 0xFF000000); part DLs
    >= 4 become area-2 object records (D_800DBEF4, 0xA0 bytes, +0x1C DL, +0x4F flag, random 0x20 skips);
  - knobs: D_800DBE63 (full-range bounds), the cart word at ROM 0xD24 (pool size x1 / x2), D_80082FA0 (grid),
    segment table D_800D3048, PVS assets (2, 5, level * 2 / + 1) present or not;
  - collision_build_level_tris(level) then collision_build_quadtrees() run; allocate_memory is a bump allocator (zeroed blocks),
    asset_load returns the PVS buffers, func_10004074 / PI access are no-ops.
Compared: all RDRAM except the stack and the candidate's .nm_rodata. Reported: triangle counts per area, node /
leaf counts, PVS index size.
Smoke: func_150A5858 (C) on the C-built area-0 tree with sample view matrices: emitted commands / triangles, and the
same call through the VR4300 reference (nmasm_vis5858.Ref) on the same memory.
Synthetic mode (--synth N): random DLs (VTX incl. segment addresses, TRI1 / TRI2 / 0x1x, other commands) through
collision_scan_level_dl alone.

Run in the container from /conker/conker after both builds:
  python3 ../tools/port/difftest/nmasm_level.py ../baserom.eu.z64 [trials] [seed] [--level 0x21] [--synth N]"""
import struct, random, sys, os, zlib, subprocess
_HERE = os.path.dirname(os.path.abspath(__file__))
_UC = os.environ.get('DIFFTEST_UNICORN', os.path.join(_HERE, '../../../port_work/pyuc201'))
if os.path.isdir(_UC): sys.path.insert(0, os.path.abspath(_UC))
from unicorn import Uc, UcError, UC_ARCH_MIPS, UC_MODE_MIPS32, UC_MODE_BIG_ENDIAN, UC_PROT_ALL, UC_HOOK_CODE
from unicorn.mips_const import *

RET = 0x153F0000
SP0 = 0x807FE000
RAM = 0x800000
LOW = 0x1000
ARENA = 0x80505000
NMRO = 0x80400000
phys = lambda a: a & 0x1FFFFFFF
A = dict(D_800B0E00=0x800B1210, level=0x800BEE10, objs=0x800DC324, nobj=0x800DC320, work=0x800383FC,
         seg=0x800D3048, flag63=0x800DC293, tree=0x800DC278, vis0=0x800D3A88, vis1=0x800D3A8C,
         grid=0x80083330, tri=0x800DC26C, nodes=0x800B11DC, leaves=0x800B11E0, counts=0x800DC248, pvs=0x800BE9F0,
         pvsix=0x800BE9F4, huff=0x800BE9F8, rowlen=0x800DC258)


def section(elf, name):
    out = '/tmp/p40_%s_%s.bin' % (elf.replace('/', '_'), name)
    subprocess.check_call(['mips-linux-gnu-objcopy', '-O', 'binary', '-j', name, elf, out])
    for l in subprocess.check_output(['mips-linux-gnu-objdump', '-h', elf]).decode().split('\n'):
        f = l.split()
        if len(f) > 3 and f[1] == name: return int(f[3], 16), open(out, 'rb').read()
    return None


def syms(elf):
    d = {}
    for l in subprocess.check_output(['mips-linux-gnu-nm', elf]).decode().split('\n'):
        f = l.split()
        if len(f) == 3: d[f[2]] = int(f[0], 16)
    return d


# ---- ROM assets (asset_load / asset_load_with_subfiles / asset_rec_read_cached / asset_load_alloc in Python) ----
def asset(rom, keys):
    p = 0xAB2240
    info = 0
    for k in keys:
        off, info = struct.unpack('>iI', rom[p + 8 * k:p + 8 * k + 8])
        if not info & 0x0FFFFFFF: return None
        p += off
    size = ((info & 0x0FFFFFFF) + 1) & ~1
    raw = rom[p:p + size]
    if (info & 0x70000000) == 0x10000000:
        n = struct.unpack('>I', raw[:4])[0] & 0x7FFFFFFF
        out = zlib.decompressobj(-15).decompress(raw[4:])
        assert len(out) >= n, (keys, len(out), n)
        return bytearray(out[:n])
    return bytearray(raw)


class Emu:
    def __init__(self, elf, ref_elf):
        self.s = syms(elf)
        self.rs = syms(ref_elf)
        self.is_ref = elf == ref_elf
        secs = [section(ref_elf if n in ('.game_data', '.init_data') else elf, n) for n in ('.game', '.game_data', '.init', '.init_data', '.nm_rodata')]
        self.secs = [x for x in secs if x]
        self.nmro = next(((v, len(b)) for v, b in self.secs if v == NMRO), (NMRO, 0))
        mu = Uc(UC_ARCH_MIPS, UC_MODE_MIPS32 | UC_MODE_BIG_ENDIAN)
        mu.mem_map(0, 0x1000, UC_PROT_ALL)   # page 0: osRomBase (0x80000308); see P18 for the page-0 TLB-slot bug
        mu.mem_map(LOW, RAM - LOW, UC_PROT_ALL)
        mu.mem_map(0x10000000, 0x100000, UC_PROT_ALL)
        mu.mem_map(0x15000000, 0x400000, UC_PROT_ALL)
        mu.mem_map(0x04600000, 0x1000, UC_PROT_ALL)   # PI regs (PI_STATUS = 0)
        self.code = [(v, b) for v, b in self.secs if v < 0x80000000]
        for v, b in self.code: mu.mem_write(v, b)
        self.mu = mu
        self.stubs = {self.s['allocate_memory']: self.st_alloc, self.s['func_10004074']: self.st_nop,
                      self.s['func_10023BC0']: self.st_nop, self.s['func_10023C04']: self.st_nop,
                      self.s['asset_load']: self.st_asset}
        for a in self.stubs: mu.hook_add(UC_HOOK_CODE, self.hook, begin=a, end=a)

    def hook(self, uc, addr, size, ud):
        r = self.stubs[addr](uc)
        if r is not None: uc.reg_write(UC_MIPS_REG_V0, r & 0xFFFFFFFF)
        uc.reg_write(UC_MIPS_REG_PC, uc.reg_read(UC_MIPS_REG_RA))

    def st_nop(self, uc): return None

    def st_alloc(self, uc):
        n = uc.reg_read(UC_MIPS_REG_A0)
        self.allocs.append(n)
        p = self.brk
        self.brk = (self.brk + n + 15) & ~15
        assert self.brk < 0x80700000 - 0x10000, 'arena full'
        uc.mem_write(phys(p), bytes(self.brk - p))
        return p

    def st_asset(self, uc):
        k = (uc.reg_read(UC_MIPS_REG_A2), uc.reg_read(UC_MIPS_REG_A3))
        return self.assets.get(k, 0)

    def load(self, mem, assets):
        self.brk = ARENA
        self.allocs = []
        self.assets = assets
        self.mu.mem_write(LOW, bytes(mem[LOW:RAM]))
        self.mu.mem_write(0, bytes(mem[0:LOW]))
        for v, b in self.secs:
            if v >= 0x80000000 and (v != NMRO or not self.is_ref): self.mu.mem_write(phys(v), b)

    def call(self, fn, args=(), maxi=200000000):
        mu = self.mu
        for k, a in enumerate(args[:4]): mu.reg_write(UC_MIPS_REG_A0 + k, a & 0xFFFFFFFF)
        for k, a in enumerate(args[4:]): mu.mem_write(phys(SP0) + 0x10 + 4 * k, struct.pack('>I', a & 0xFFFFFFFF))
        mu.reg_write(UC_MIPS_REG_SP, SP0); mu.reg_write(UC_MIPS_REG_RA, RET); mu.reg_write(UC_MIPS_REG_GP, 0)
        try:
            mu.emu_start(self.s[fn], RET, count=maxi)
        except UcError as e:
            raise RuntimeError('%s: %s at pc %08X ra %08X' % (fn, e, mu.reg_read(UC_MIPS_REG_PC), mu.reg_read(UC_MIPS_REG_RA)))
        if mu.reg_read(UC_MIPS_REG_PC) != RET: raise RuntimeError('%s: timeout' % fn)
        return mu.reg_read(UC_MIPS_REG_V0)

    def ram(self):
        m = bytearray(RAM)
        m[LOW:RAM] = self.mu.mem_read(LOW, RAM - LOW)
        m[0:LOW] = self.mu.mem_read(0, LOW)
        return m


def W(mem, a, fmt, *v):
    mem[phys(a):phys(a) + struct.calcsize('>' + fmt)] = struct.pack('>' + fmt, *v)


def R(mem, a, fmt):
    v = struct.unpack('>' + fmt, bytes(mem[phys(a):phys(a) + struct.calcsize('>' + fmt)]))
    return v[0] if len(v) == 1 else v


def relocate_dl(mem, dl, arg1, hdr):
    """gfx_dl_relocate_segments"""
    i = 0
    while mem[phys(dl) + 8 * i] != 0xDF:
        c = phys(dl) + 8 * i
        op = mem[c]
        if op in (0xDE, 0x01) or (op == 0xDC and mem[c + 3] == 0xE):
            add = hdr if op == 0xDC else arg1
            W(mem, dl + 8 * i + 4, 'I', (R(mem, dl + 8 * i + 4, 'I') + add) & 0xFFFFFFFF)
        i += 1
    return i


def level_setup(rng, base, models, level, stats):
    """level_load_models in Python: model list at 0x80100000; returns mem."""
    mem = bytearray(base)
    H = 0x80105000
    mem[phys(H):phys(H) + len(models)] = models
    # asset_relocate_subfiles(base, 0): {offset, info} until info bit 31
    n = 0
    while True:
        off, info = R(mem, H + 8 * n, 'iI')
        n += 1
        if info & 0x80000000: break
    ents = []
    for i in range(n):
        off, info = R(mem, H + 8 * i, 'iI')
        info &= 0x0FFFFFFF
        ptr = 0 if (off == -1 or info == 0) else (off + H) & 0xFFFFFFFF
        ents.append((ptr, info))
    objdls = []
    for i, (hdr, size) in enumerate(ents):
        if hdr == 0 or size == 0: continue
        for o in (0, 8, 0x10):
            v = R(mem, hdr + o, 'I')
            if v: W(mem, hdr + o, 'I', (v + hdr) & 0xFFFFFFFF)
        dl = R(mem, hdr, 'I')
        if i < 4:
            W(mem, A['D_800B0E00'] + 4 * i, 'I', dl)
            if dl: stats.setdefault('dlcmds', []).append(relocate_dl(mem, dl, (hdr + 0x28 + 0xFF000000) & 0xFFFFFFFF, hdr))
        elif dl:
            relocate_dl(mem, dl, 0, hdr)
            objdls.append(dl)
    # area-2 object records
    nobj = len(objdls)
    rec = 0x80305000
    mem[phys(rec):phys(rec) + 0xA0 * max(1, nobj)] = bytes(0xA0 * max(1, nobj))
    # the triangle tables of the 3 areas share one pool of D_80091C04[level] bytes (24 per triangle + alignment):
    # objects that would overflow it get the 0x20 skip flag (a pool overflow corrupts the allocations after it)
    def ntri(dl):
        n = i = 0
        while dl and mem[phys(dl) + 8 * i] != 0xDF:
            op = mem[phys(dl) + 8 * i]
            n += 4 if op >> 4 == 1 else 2 if op == 6 else 1 if op == 5 else 0
            i += 1
        return n
    room = R(mem, 0x80091FB4 + 4 * level, 'i') - 16 - 24 * (ntri(R(mem, A['D_800B0E00'], 'I')) + ntri(R(mem, A['D_800B0E00'] + 12, 'I')))
    for k, dl in enumerate(objdls):
        W(mem, rec + 0xA0 * k + 0x1C, 'I', dl)
        f = rng.choice([0, 0, 0, 0x20, 0x60, 0x40, 0x80])
        if f & 0x60 != 0x20:
            if 24 * ntri(dl) > room: f = 0x20
            else: room -= 24 * ntri(dl)
        mem[phys(rec + 0xA0 * k + 0x4F)] = f
    W(mem, A['objs'], 'I', rec)
    W(mem, A['nobj'], 'i', nobj)
    stats['parts'] = n
    stats['objs'] = nobj
    return mem


def knobs(rng, mem, level, flag63):
    W(mem, A['level'], 'i', level)
    W(mem, A['work'], 'I', 0x80385000)
    W(mem, 0x80000308, 'I', 0xB0000000)
    mem[phys(A['flag63'])] = flag63
    # segment table: 0 (the object DLs' other segments then give pointers below 0x80000001, i.e. 'no vertex';
    # random kseg0 bases sent level 0x1d's object vertices outside RDRAM). collision_build_level_tris clears segment 1 itself.
    for s in range(16): W(mem, A['seg'] + 4 * s, 'I', 0)
    W(mem, A['grid'], 'i', rng.choice([0, 1, 2, 3, R(mem, A['grid'], 'i')]))


def summary(m):
    nt = [R(m, A['counts'] + 4 * a, 'i') for a in range(3)]
    return 'tris %s nodes %d leaves %d pvs %08X ix %08X' % (nt, R(m, A['nodes'], 'i'), R(m, A['leaves'], 'i'),
                                                             R(m, A['pvs'], 'I'), R(m, A['pvsix'], 'I'))


def compare(ref, cand, m1, m2):
    lo, hi = phys(SP0) - 0x8000, phys(SP0) + 0x100
    nlo, nhi = phys(cand.nmro[0]), phys(cand.nmro[0]) + cand.nmro[1]
    bad = []
    for a, b in sorted([(0, lo), (hi, RAM)]):
        for x, y in ((a, min(b, nlo)), (max(a, nhi), b)):
            if x < y and m1[x:y] != m2[x:y]:
                bad += [i for i in range(x, y) if m1[i] != m2[i]]
    bad.sort()
    return bad


def smoke(ref_vr, cand, m, rng, nview):
    """func_150A5858 (C) on the C-built area-0 tree; also the asm through the VR4300 interpreter."""
    out = []
    dl = R(m, A['D_800B0E00'], 'I')
    OUT, MTX = 0x80705000, 0x80715000
    for v in range(nview):
        mm = bytearray(m)
        # collision_build_quadtrees ends with collision_select_area(0): area 0's tree / tables are selected
        W(mm, 0x800D3A00, 'ff', rng.uniform(0.5, 1.5), rng.uniform(0.5, 1.5))
        W(mm, 0x800D3A90, 'f', rng.uniform(-12000, -3000))
        mtx = [0.0] * 16
        mtx[0] = mtx[5] = mtx[10] = mtx[15] = 1.0
        for k in (1, 2, 4, 6, 8, 9): mtx[k] = rng.uniform(-0.3, 0.3)
        mtx[12], mtx[13], mtx[14] = rng.uniform(-2000, 2000), rng.uniform(-500, 500), rng.uniform(-4000, 0)
        W(mm, MTX, '16f', *mtx)
        mm[phys(OUT):phys(OUT) + 0x8000] = bytes(0x8000)
        mask = rng.choice([1, 2, 4, 3])
        args = [dl, OUT, MTX, 0, 0, mask]
        cand.load(mm, {})
        try:
            v0 = cand.call('func_150A5858', args)
        except RuntimeError as e:
            out.append(('cand fault', str(e))); continue
        cm = cand.ram()
        ntri = sum(1 for k in range(0, (v0 - OUT) & 0xFFFFFF, 8) if cm[phys(OUT) + k] in (5, 6) or cm[phys(OUT) + k] >> 4 == 1)
        rr = None
        if ref_vr is not None:
            rm = bytearray(mm)
            for vv, b in cand.secs:
                if vv >= 0x80000000 and vv != NMRO: rm[phys(vv):phys(vv) + len(b)] = b
            try:
                r0 = ref_vr.run(rm, args)
                lo, hi = phys(SP0) - 0x8000, phys(SP0) + 0x100
                same = r0 == v0 and all(rm[i] == cm[i] for i in range(phys(OUT), phys(OUT) + 0x8000)) and \
                    rm[phys(R(mm, A['vis0'], 'I')):phys(R(mm, A['vis1'], 'I'))] == cm[phys(R(mm, A['vis0'], 'I')):phys(R(mm, A['vis1'], 'I'))]
                rr = 'asm same' if same else 'asm DIFF v0 %08X' % r0
            except Exception as e:
                rr = 'asm err %s' % e
        out.append(((v0 - OUT) // 8, ntri, rr))
    return out


def synth(ref, cand, base, rng, n):
    bad = 0
    st = {}
    for t in range(n):
        mem = bytearray(base)
        DL, VB, T0, T1, T2 = 0x80105000, 0x80115000, 0x80205000, 0x80245000, 0x80265000
        mem[phys(VB):phys(VB) + 0x2000] = bytes(rng.getrandbits(8) for _ in range(0x2000))
        cmds = []
        for _ in range(rng.randrange(1, 40)):
            op = rng.choice([1, 1, 5, 6, 0x10, 0x13, 0x1F, 0xE7, 0xDE, 0x02, 0x20, 0xF5])
            if op == 1:
                nv = rng.choice([rng.randrange(1, 33), 32, 16])
                v0 = rng.choice([0, 0, rng.randrange(0, 32 - nv + 1)])
                addr = rng.choice([VB + 16 * rng.randrange(0, 64), 0x01000000 + 16 * rng.randrange(0, 64), 0x03000000 | rng.randrange(0, 0x100) * 16])
                cmds.append(((1 << 24) | (nv << 12) | ((v0 + nv) << 1), addr))
            elif op == 5:
                cmds.append(((5 << 24) | (rng.randrange(32) * 2 << 16) | (rng.randrange(32) * 2 << 8) | rng.randrange(32) * 2, 0))
            else:
                cmds.append(((op << 24) | rng.getrandbits(24), rng.getrandbits(32)))
        cmds.append((0xDF000000, 0))
        # vertex cache must be filled before use: start with a full VTX
        cmds.insert(0, ((1 << 24) | (32 << 12) | (32 << 1), VB))
        for k, (a, b) in enumerate(cmds): W(mem, DL + 8 * k, 'II', a, b)
        W(mem, A['tri'], 'III', T0, T1, T2)
        W(mem, 0x800DC268, 'i', rng.choice([0, 0, 7]))
        mem[phys(A['flag63'])] = rng.choice([0, 0, 0, 1])
        d3088 = rng.choice([0, 1])
        mem[phys(0x800D3088)] = d3088
        for s in range(16):   # segment s maps to VB + a small offset (so every vertex pointer is in RAM)
            W(mem, A['seg'] + 4 * s, 'I', (VB + 16 * rng.randrange(0, 8) - (s << 24) + (d3088 << 24)) & 0xFFFFFFFF)
        res = []
        for e in (ref, cand):
            e.load(mem, {})
            e.call('collision_scan_level_dl', [DL])
            res.append(e.ram())
        d = compare(ref, cand, res[0], res[1])
        st['tris'] = st.get('tris', 0) + R(res[0], 0x800DC268, 'i')
        if d:
            bad += 1
            if bad <= 5: print('SYNTH DIFF trial %d: %d bytes, first %08X' % (t, len(d), 0x80000000 + d[0]))
    print('synth collision_scan_level_dl: %s, %d differences in %d trials, %s' % ('EQUIV' if not bad else 'DIFFER', bad, n, st))
    return bad


def main():
    a = sys.argv[1:]
    opts = {}
    pos = []
    while a:
        x = a.pop(0)
        if x.startswith('--'): opts[x[2:]] = a.pop(0)
        else: pos.append(x)
    rom = open(pos[0], 'rb').read()
    N = int(pos[1]) if len(pos) > 1 else 6
    seed = int(pos[2]) if len(pos) > 2 else 1
    level = int(opts.get('level', '0x21'), 0)
    ref = Emu('build/conker.eu.elf', 'build/conker.eu.elf')
    cand = Emu('build_nm/conker.eu.elf', 'build/conker.eu.elf')
    base = bytearray(RAM)
    for v, b in ref.secs:
        if v >= 0x80000000: base[phys(v):phys(v) + len(b)] = b
    rng = random.Random(seed)
    bad = 0
    if 'synth' in opts:
        bad += synth(ref, cand, base, rng, int(opts['synth']))
    models = asset(rom, [4, level])
    pvs = (asset(rom, [5, level * 2]), asset(rom, [5, level * 2 + 1]))
    print('level %#x: model list %d bytes, PVS %s' % (level, len(models), [None if p is None else len(p) for p in pvs]))
    ref_vr = None
    try:
        sys.path.insert(0, _HERE)
        import nmasm_vis5858
        ref_vr = nmasm_vis5858.Ref('build/conker.eu.elf')
    except Exception as e:
        print('no VR4300 reference:', e)
    for t in range(N):
        stats = {}
        mem = level_setup(rng, base, models, level, stats)
        flag63 = 1 if t % 4 == 3 else 0
        knobs(rng, mem, level, flag63)
        magic = t % 3 == 1
        assets = {}
        if pvs[0] is not None and t % 5 != 4:
            P1, P2 = 0x80425000, 0x80495000
            mem[phys(P1):phys(P1) + len(pvs[0])] = pvs[0]
            mem[phys(P2):phys(P2) + len(pvs[1])] = pvs[1]
            assets = {(5, level * 2): P1, (5, level * 2 + 1): P2}
        res = []
        for e in (ref, cand):
            m = bytearray(mem)
            e.load(m, assets)
            e.mu.mem_write(0x10000D24, struct.pack('>I', 0x98CCE31A if magic else 0x12345678))
            e.call('collision_build_level_tris', [level])
            e.call('collision_build_quadtrees', [])
            res.append((e.ram(), list(e.allocs)))
        # area 2 (objects): vertex pointers are segment offsets (D_800D304C = 0), so the asm writes its stale
        # stack bounds (never recomputed: cache entry 0 <= 0x100000); the C writes 0. Those bounds are excluded,
        # after checking that every area-2 triangle really has vertex 0 of the cache <= 0x100000 (pointers small).
        m1, m2 = res[0][0], res[1][0]
        n2 = R(m1, A['counts'] + 8, 'i')
        b270, b274, t26c = R(m1, 0x800DC218 + 8, 'I'), R(m1, 0x800DC228 + 8, 'I'), R(m1, 0x800DC208 + 8, 'I')
        small = all(R(m1, t26c + 4 * k, 'I') <= 0x100000 for k in range(3 * n2))
        if small:
            for m in (m1, m2):
                m[phys(b270):phys(b270) + 8 * n2] = bytes(8 * n2)
                m[phys(b274):phys(b274) + 4 * n2] = bytes(4 * n2)
        d = compare(ref, cand, m1, m2)
        same = not d and res[0][1] == res[1][1]
        print('trial %d (flag63 %d, magic %d, pvs %d, objs %d, area-2 bounds masked %d): %s; %s' % (t, flag63, magic, bool(assets), stats['objs'], small,
              'same' if same else 'DIFF %d bytes first %08X allocs %s' % (len(d), 0x80000000 + (d[0] if d else 0), res[0][1] != res[1][1]),
              summary(res[0][0])))
        if not same:
            bad += 1
            if d:
                print('   ref ', bytes(res[0][0][d[0] - 8:d[0] + 24]).hex())
                print('   cand', bytes(res[1][0][d[0] - 8:d[0] + 24]).hex())
        if t == 0 and 'nosmoke' not in opts:
            for r in smoke(ref_vr, cand, res[1][0], rng, int(opts.get('views', '6'))):
                print('   smoke func_150A5858 (C tree):', r)
    print('EQUIV' if bad == 0 else 'DIFFER')


if __name__ == '__main__':
    main()
