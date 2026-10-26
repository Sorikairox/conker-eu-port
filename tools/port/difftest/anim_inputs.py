#!/usr/bin/env python3
"""P51 research: real ROM inputs for func_150A86B0 (skeleton / animation evaluator, asm/D5E90.s).

Reproduces, in Python, what the game does before obj_build_model_instance calls
  func_150A86B0(&D_800C42A8, m, A = obj+0x2D0, S = D_800C5000[id], n = model_joint_mtx_count(id), buf, remap, h)
for a single (unblended) animation:
  * model_load(id)          model asset (1, id)            -> S (skeleton), D_800C52F0[id] (joint count)
  * anim_bank_load(id)          anim bank asset (0xF, alias)   -> D_800D1588[id] (u16 key, u16 sfx, s32 ptr; 999 end),
                                                                 D_800C5A90[id] (animation count)
  * obj_set_type              obj[6] = obj_type_model_group(obj) (model alias), obj+0x58 = dir (2, obj[6])
  * obj_anim_state_alloc -> obj_start_anim -> anim_start_entry (fresh state, t2 = 1 path)
                               A+0x40 <- header record dir[key] (DMA, (size + 15) & ~15 bytes), A+0x28 <- ROM addr
                               of the key-frame stream dir[key + 1], A+0x18 = (f32)A[0x43], A+8 = start frame ...
  * anim_copy_keyframes (per frame, just before the evaluator)
                               copies 2 key frames (A[0x45] bytes each) of the stream from ROM into a stack buffer
                               (dbuf, 0x324 bytes) and sets A+0x30 (pointer to key frame) and A[0x38] (byte offset
                               of the next key frame from A+0x30), wrapping to frame 0 at the end.

Run in the container from /conker/conker:
  python3 ../port_work/p51/research/anim_inputs.py [--rom ../baserom.eu.z64] [--elf build/conker.eu.elf]
        --id ID [--anim K] [--time T] [--out DIR] [--base 0x80400000] [--list] [--scan]
  --scan     list every model id with a model asset / animation bank (counts)
  --list     list the animations of --id
  writes (with --out) DIR/anim_state.bin (0x3E0, A+0x30 relocated to --base + offset), DIR/anim_blob.bin (dbuf),
  DIR/skeleton.bin (n * 16 bytes) and DIR/info.json.
"""
import struct, sys, os, zlib, subprocess, json, argparse

ROOT = 0xAB2240  # D_AB2240


# ---------------- ROM directory (asset_rec_read_cached / asset_load / asset_load_alloc / asset_rec_fetch_block) ----------------
def rec(rom, p, k):
    return struct.unpack('>iI', rom[p + 8 * k:p + 8 * k + 8])


def walk(rom, keys):
    """asset_lookup_rom / asset_lookup_records path walk: p += rec(p, k).off for each key. Returns (p, info) or None."""
    p, info = ROOT, 1
    for k in keys:
        off, info = rec(rom, p, k)
        if not info & 0x0FFFFFFF:
            return None
        p += off
    return p, info


def asset(rom, keys):
    """asset_load / asset_load_with_subfiles: load (and zlib-unpack when info & 0x70000000 == 0x10000000)."""
    w = walk(rom, keys)
    if w is None:
        return None
    p, info = w
    size = ((info & 0x0FFFFFFF) + 1) & ~1
    raw = rom[p:p + size]
    if (info & 0x70000000) == 0x10000000:
        n = struct.unpack('>I', raw[:4])[0] & 0x7FFFFFFF
        out = zlib.decompressobj(-15).decompress(raw[4:])
        return bytearray(out[:n])
    return bytearray(raw)


# ---------------- ELF data (.game_data) ----------------
class Elf:
    def __init__(self, path):
        self.data = open(path, 'rb').read()
        self.secs = []
        for l in subprocess.check_output(['mips-linux-gnu-objdump', '-h', path]).decode().split('\n'):
            f = l.split()
            if len(f) >= 6 and f[0].isdigit():
                self.secs.append((int(f[3], 16), int(f[2], 16), int(f[5], 16)))
        self.syms = {}
        for l in subprocess.check_output(['mips-linux-gnu-nm', path]).decode().split('\n'):
            f = l.split()
            if len(f) == 3:
                self.syms[f[2]] = int(f[0], 16)

    def read(self, va, n):
        for vma, size, off in self.secs:
            if vma <= va and va + n <= vma + size:
                return self.data[off + va - vma:off + va - vma + n]
        raise KeyError(hex(va))

    def u8(self, va): return self.read(va, 1)[0]
    def u32(self, va): return struct.unpack('>I', self.read(va, 4))[0]


def alias(elf, cnt_sym, lst_sym, ngroups, x):
    """anim_bank_group_index (5 groups, D_80098C38 / D_800847A0) and obj_type_model_group (7 groups, D_8009DD24 / D_800875E0):
    the first id of the group that contains x, else x."""
    c, l = elf.syms[cnt_sym], elf.syms[lst_sym]
    for g in range(ngroups):
        n = elf.u8(c + g)
        lst = elf.u32(l + 4 * g)
        ids = [elf.u8(lst + i) for i in range(n)]
        if x in ids:
            return ids[0]
    return x


# ---------------- model (model_load) ----------------
def model(rom, mid):
    m = asset(rom, [1, mid])
    if m is None:
        return None
    ent = [struct.unpack('>iI', m[8 * i:8 * i + 8]) for i in range(7)]  # asset_relocate_subfiles(base, 7)
    off, info = ent[2]
    info &= 0x0FFFFFFF
    nj = info >> 4                                                     # D_800C52F0[id] = +0x14 >> 4
    sk = bytes(m[off:off + 16 * nj]) if off != -1 and info else b''    # D_800C5000[id] = base + off
    return dict(raw=m, ent=ent, skel=sk, joints=nj, skel_off=off)


def nmat(mid, nj):  # model_joint_mtx_count
    return nj - 4 if mid in (0x3B, 0x75, 0x82, 0x88, 0x90, 0x96, 0x98, 0x9C, 0x9D, 0x9F, 0xA0, 0xB1, 0xB2, 0xB4) else nj


# ---------------- animation bank (anim_bank_load / anim_bank_relocate) ----------------
def bank(rom, elf, mid):
    b = asset(rom, [0xF, alias(elf, 'D_80098C38', 'D_800847A0', 5, mid)])
    if b is None:
        return None
    ents = []
    p = 0x10
    while struct.unpack('>H', b[p:p + 2])[0] != 999:
        key, sfx, ptr = struct.unpack('>HHi', b[p:p + 8])
        ents.append((key, sfx, ptr))
        p += 8
    return dict(raw=b, entries=ents, hdr=struct.unpack('>4i', b[:16]))


# ---------------- animation state (anim_start_entry + anim_copy_keyframes) ----------------
def anim_state(rom, elf, mid, k, t, base, speed=1.0, obj6=None):
    bk = bank(rom, elf, mid)
    ents = bk['entries']
    key, sfx, _ = ents[k]
    if key == 999 or key >= 30000:
        raise SystemExit('anim %d: key %d -> obj_anim_reset (no animation)' % (k, key))
    if obj6 is None:
        obj6 = alias(elf, 'D_8009DD24', 'D_800875E0', 7, mid)        # obj[6] = obj_type_model_group(obj)
    d = walk(rom, [2, obj6])                                           # obj+0x58 = asset_lookup_rom(0, 2, 2, obj[6])
    p = d[0]
    hoff, hinfo = rec(rom, p, key)                                     # asset_rec_fetch_block(p, buf, key, 2)
    soff, sinfo = rec(rom, p, key + 1)
    hdr_rom, stream_rom = p + hoff, p + soff
    hsize = (hinfo + 15) & ~15 & 0xFFFFFFFF
    A = bytearray(0x3E0)
    A[0x40:0x40 + hsize] = rom[hdr_rom:hdr_rom + hsize][:0x3E0 - 0x40]
    struct.pack_into('>I', A, 0x0, elf.u32(elf.syms['D_800866AC'] + 4 * sfx))   # A+0 = D_800866AC[e[1]]
    struct.pack_into('>H', A, 0x4, k)                                  # A+4 = anim (| 0x8000 with arg6)
    struct.pack_into('>f', A, 0x8, t)                                  # A+8 = frame time (start arg4, advanced per frame)
    struct.pack_into('>f', A, 0x10, speed)                             # A+0x10 = speed (arg2)
    struct.pack_into('>f', A, 0x18, float(A[0x43]))                    # A+0x18 = frame count (types 0x92/0xB7-B9 differ)
    struct.pack_into('>f', A, 0x20, 0.0)                               # A+0x20 = arg5
    struct.pack_into('>I', A, 0x28, stream_rom if A[0x45] else 1)      # A+0x28 = stream ROM address (1 when static)
    # A+0x3C = 0 (single animation); A+0x210.. second slot left zero (fresh state).
    blob = bytearray(0x324)
    info = dict(model_id=mid, obj6=obj6, anim=k, key=key, sfx=sfx, hdr_rom=hdr_rom, hdr_size=hinfo,
                stream_rom=stream_rom, stream_size=sinfo, frames=A[0x43], keybytes=A[0x45], decim=A[0x48],
                channels_plus1=A[0x41], flags47=A[0x47], time=t)
    s3 = A[0x45]
    if s3 == 0:                                                         # anim_copy_keyframes: A[0x38] = 0, nothing copied
        A[0x38] = 0
        info['a30_off'] = None
        return A, blob, info
    cnt = float(A[0x43])
    v1 = int(t)
    if cnt <= float(v1):
        v1 = int(cnt - 1.0)
    v0 = A[0x48] + 1
    if v0 >= 2:
        f2 = cnt - 1.0
        if f2 <= float(v1):
            v1 = int((f2 + float(v0 - 1)) / float(v0))
        else:
            v1 = v1 // v0
    a0 = stream_rom + s3 * v1
    mis = a0 & 3
    a0 -= mis
    wrap = cnt <= t + 1.0
    s0 = (s3 if wrap else 2 * s3) + mis
    s1 = 0                                                              # dbuf aligned to 16 (blob offset 0)
    n = s0 if s0 < 0xC8 else (s0 + 15) & ~15                            # rom_read_direct exact / rom_dma_read rounded
    blob[s1:s1 + n] = rom[a0:a0 + n]
    a30 = s1 + mis
    if not wrap:
        A[0x38] = s3
    else:
        s1 = (s1 + s0 + 15) & ~15
        b0 = stream_rom
        mis2 = b0 & 1
        s0b = mis2 + s3
        b0 -= mis2
        n = s0b if s0b < 0xC8 else (s0b + 15) & ~15
        blob[s1:s1 + n] = rom[b0:b0 + n]
        A[0x38] = (s1 + mis2 - a30) & 0xFF
    struct.pack_into('>I', A, 0x30, base + a30)
    info.update(a30_off=a30, a38=A[0x38], key_index=v1, wrap=wrap)
    return A, blob, info


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--rom', default='../baserom.eu.z64')
    ap.add_argument('--elf', default='build/conker.eu.elf')
    ap.add_argument('--id', type=lambda s: int(s, 0))
    ap.add_argument('--anim', type=lambda s: int(s, 0), default=0)
    ap.add_argument('--time', type=float, default=0.0)
    ap.add_argument('--base', type=lambda s: int(s, 0), default=0x80400000, help='RAM address of anim_blob.bin')
    ap.add_argument('--out')
    ap.add_argument('--list', action='store_true')
    ap.add_argument('--scan', action='store_true')
    a = ap.parse_args()
    rom = open(a.rom, 'rb').read()
    elf = Elf(a.elf)
    if a.scan:
        for mid in range(0xBB):
            try:
                m = model(rom, mid)
                b = bank(rom, elf, mid)
            except Exception as e:
                print('%02X error %s' % (mid, e)); continue
            if m or b:
                print('%02X joints %3s anims %4s obj6 %02X' % (mid, m['joints'] if m else '-',
                      len(b['entries']) if b else '-', alias(elf, 'D_8009DD24', 'D_800875E0', 7, mid)))
        return
    m = model(rom, a.id)
    b = bank(rom, elf, a.id)
    print('model %02X: joints (D_800C52F0) %s, model_joint_mtx_count %s, animations (D_800C5A90) %s' % (
        a.id, m and m['joints'], m and nmat(a.id, m['joints']), b and len(b['entries'])))
    if a.list:
        for i, (key, sfx, ptr) in enumerate(b['entries']):
            print('  %3d key %5d sfx %3d ptr %08X' % (i, key, sfx, ptr & 0xFFFFFFFF))
        return
    A, blob, info = anim_state(rom, elf, a.id, a.anim, a.time, a.base)
    info['joints'] = m['joints']
    info['n'] = nmat(a.id, m['joints'])
    print(json.dumps({k: (hex(v) if isinstance(v, int) and k.endswith('rom') else v) for k, v in info.items()}))
    print('A+0x40..0x60:', A[0x40:0x60].hex())
    if a.out:
        os.makedirs(a.out, exist_ok=True)
        open(os.path.join(a.out, 'anim_state.bin'), 'wb').write(A)
        open(os.path.join(a.out, 'anim_blob.bin'), 'wb').write(blob)
        open(os.path.join(a.out, 'skeleton.bin'), 'wb').write(m['skel'])
        json.dump(info, open(os.path.join(a.out, 'info.json'), 'w'), indent=1)


if __name__ == '__main__':
    main()
