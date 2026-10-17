#!/usr/bin/env python3
"""Who references what in a data segment (EU).

Scans the code of a segment (init/game/debugger) in conker/conker.eu.bin, follows
lui/addiu/load/store pairs (and jump-table `addu` chains) per register, and maps every
reference into the matching *_data segment to the C file (yaml subsegment) whose code makes it.

usage: datarefs.py [game|init] [--lo 0x.. --hi 0x..] [--file stem] [--runs]
  default        one line per referenced address: rom  vram  kind  file  func
  --runs         collapse consecutive addresses referenced by the same file into runs,
                 with the file's link index; a drop in index marks a section boundary
                 (all .data of a segment is linked before all .rodata)
  --file stem    only references made by that C file (rom ranges of its rodata)

Importable: refs(seg) -> list of (target_vram, kind, file_index, stem, insn_vram).
kind: 'lw','lwc1','ldc1','addiu','jtbl',... (the instruction that uses %lo); an 'x' suffix
(or 'lwx') marks an indexed access (base + register), i.e. an array, never a literal.
"""
import sys, re, os, struct, bisect

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '../../conker'))
YAML = os.path.join(ROOT, 'conker.eu.yaml')
BIN = os.path.join(ROOT, 'conker.eu.bin')

SEGRE = re.compile(r'^\s*- name:\s*(\w+)')
SUBRE = re.compile(r'^\s*- \[0x([0-9A-Fa-f]+)(?:,\s*([\w.]+))?(?:,\s*([\w/.]+))?')


def segments():
    """{name: dict(start, vram, subs=[(rom, type, name)])} from the EU yaml."""
    segs = {}
    cur = None
    for l in open(YAML):
        m = SEGRE.match(l)
        if m:
            cur = segs.setdefault(m.group(1), {'subs': []})
            continue
        if cur is None:
            continue
        m = re.match(r'^\s*(start|vram):\s*0x([0-9A-Fa-f]+)', l)
        if m:
            cur[m.group(1)] = int(m.group(2), 16)
            continue
        m = SUBRE.match(l)
        if m:
            cur['subs'].append((int(m.group(1), 16), m.group(2), m.group(3)))
    # end of each segment's last subsegment = next segment start
    names = list(segs)
    for i, n in enumerate(names):
        s = segs[n]
        nxt = None
        for n2 in names[i + 1:]:
            if 'start' in segs[n2]:
                nxt = segs[n2]['start']
                break
        s['end'] = nxt
    return segs


def code_files(seg):
    """[(rom_start, rom_end, stem)] for the c/asm subsegments of a code segment."""
    s = segments()[seg]
    subs = s['subs']
    out = []
    for i, (rom, t, name) in enumerate(subs):
        end = subs[i + 1][0] if i + 1 < len(subs) else s['end']
        if t in ('c', 'asm', 'hasm'):
            out.append((rom, end, name))
    return out


LOADS = {0x20: 'lb', 0x21: 'lh', 0x23: 'lw', 0x24: 'lbu', 0x25: 'lhu', 0x31: 'lwc1', 0x35: 'ldc1',
         0x28: 'sb', 0x29: 'sh', 0x2B: 'sw', 0x39: 'swc1', 0x3D: 'sdc1', 0x37: 'ld', 0x3F: 'sd'}


def refs(seg='game'):
    segs = segments()
    s = segs[seg]
    data = open(BIN, 'rb').read()
    files = code_files(seg)
    starts = [f[0] for f in files]
    out = []
    rom0, vram0 = s['start'], s['vram']
    for fi, (a, b, stem) in enumerate(files):
        hi = {}  # reg -> value
        pending = {}  # branch target rom -> register state at the branch
        for rom in range(a, b, 4):
            w = struct.unpack('>I', data[rom:rom + 4])[0]
            op = w >> 26
            rs = (w >> 21) & 31
            rt = (w >> 16) & 31
            rd = (w >> 11) & 31
            imm = w & 0xFFFF
            simm = imm - 0x10000 if imm & 0x8000 else imm
            pc = vram0 + rom - rom0
            if rom in pending:  # a branch target: registers set before the branch are live here
                for k_, v_ in pending.pop(rom).items():
                    hi.setdefault(k_, v_)
            if op in (1, 4, 5, 6, 7, 0x14, 0x15, 0x16, 0x17) or (op == 0x11 and rs == 8):
                pending.setdefault(rom + 4 + simm * 4, dict(hi))
            if op == 0x0F:  # lui
                hi[rt] = imm << 16
                hi.pop(('j', rt), None)
                continue
            if op in (0x09,) and rs in hi:  # addiu
                out.append(((hi[rs] + simm) & 0xFFFFFFFF, 'addiu', fi, stem, pc))
                if rt != rs:
                    hi.pop(rt, None)
                else:
                    hi.pop(rt, None)
                continue
            if op in LOADS and rs in hi:
                k = LOADS[op]
                if k != 'lw' and ('j', rs) in hi:
                    k += 'x'  # indexed: an array element, not a literal
                if k == 'lw' and ('j', rs) in hi:
                    # indexed load: a jump table if a `jr rt` follows shortly
                    k = 'lwx'
                    for r2 in range(rom + 4, min(rom + 20, b), 4):
                        w2 = struct.unpack('>I', data[r2:r2 + 4])[0]
                        if w2 >> 26 == 0 and (w2 & 0x3F) == 0x08 and (w2 >> 21) & 31 == rt:
                            k = 'jtbl'
                            break
                out.append(((hi[rs] + simm) & 0xFFFFFFFF, k, fi, stem, pc))
                if op in (0x20, 0x21, 0x23, 0x24, 0x25, 0x37):
                    hi.pop(rt, None)
                continue
            if op == 0 and (w & 0x3F) == 0x21:  # addu
                if rs in hi and rt not in hi:
                    hi[rd] = hi[rs]; hi[('j', rd)] = 1
                    continue
                if rt in hi and rs not in hi:
                    hi[rd] = hi[rt]; hi[('j', rd)] = 1
                    continue
            # generic invalidation of the written register
            if op == 0:
                hi.pop(rd, None); hi.pop(('j', rd), None)
            elif op in (0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E) or op in LOADS:
                hi.pop(rt, None); hi.pop(('j', rt), None)
            elif op == 0x03:  # jal clobbers
                hi.clear()
    return out


def owners(seg='game', allrefs=None):
    """{rom addr: file index} for the .rodata part of <seg>_data: every referenced address gets
    one of its referencing files such that owners never decrease with the address (all .rodata
    of a segment is linked in file order), keeping as many addresses as possible (longest
    non-decreasing chain). Addresses left out are cross-file references to shared tables."""
    import bisect
    S = segments()[seg + '_data']
    r0 = min(r for r, t, n in S['subs'] if t in ('rodatabin', '.rodata'))
    dv = S['vram'] - S['start']
    cand = {}
    for t, k, fi, stem, pc in (allrefs if allrefs is not None else refs(seg)):
        r = t - dv
        if r0 <= r < S['end']:
            cand.setdefault(r, set()).add(fi)
    seq = []
    for r in sorted(cand):
        for fi in sorted(cand[r], reverse=True):
            seq.append((r, fi))
    tails, tidx, prev = [], [], [None] * len(seq)
    for i, (r, fi) in enumerate(seq):
        j = bisect.bisect_right(tails, fi)
        if j == len(tails):
            tails.append(fi); tidx.append(i)
        else:
            tails[j] = fi; tidx[j] = i
        prev[i] = tidx[j - 1] if j else None
    out = {}
    i = tidx[-1] if tidx else None
    while i is not None:
        out[seq[i][0]] = seq[i][1]
        i = prev[i]
    return out


def main():
    a = sys.argv[1:]
    seg = a[0] if a and not a[0].startswith('-') else 'game'
    dseg = seg + '_data'
    S = segments()[dseg]
    lo = int(a[a.index('--lo') + 1], 16) if '--lo' in a else S['start']
    hi_ = int(a[a.index('--hi') + 1], 16) if '--hi' in a else S['end']
    only = a[a.index('--file') + 1] if '--file' in a else None
    dv0, dr0 = S['vram'], S['start']
    R = []
    for t, k, fi, stem, pc in refs(seg):
        rom = t - dv0 + dr0
        if lo <= rom < hi_ and (only is None or stem == only):
            R.append((rom, k, fi, stem, pc))
    R.sort()
    if '--runs' in a:
        run = None
        for rom, k, fi, stem, pc in R:
            if run and run[2] == fi:
                run[1] = rom; run[3].add(k)
                continue
            if run:
                print('0x%06X-0x%06X %4d %-34s %s' % (run[0], run[1], run[2], run[4], ','.join(sorted(run[3]))))
            run = [rom, rom, fi, {k}, stem]
        if run:
            print('0x%06X-0x%06X %4d %-34s %s' % (run[0], run[1], run[2], run[4], ','.join(sorted(run[3]))))
        return
    seen = set()
    for rom, k, fi, stem, pc in R:
        key = (rom, stem, k)
        if key in seen:
            continue
        seen.add(key)
        print('0x%06X 0x%08X %-5s %4d %s 0x%08X' % (rom, rom - dr0 + dv0, k, fi, stem, pc))


if __name__ == '__main__':
    main()
