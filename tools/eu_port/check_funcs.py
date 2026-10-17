#!/usr/bin/env python3
"""Compare the functions of a compiled EU object against the EU asm.

Usage (from conker/, inside the build container):
    python3 ../tools/eu_port/check_funcs.py src_eu/game_981E0.c [func ...] [-v]

Builds build/<c>.c.o through make, then for each function symbol compares the
instruction words to asm/nonmatchings/<file>/<func>.s with relocated fields
masked. Prints OK / DIFF per function; -v prints a side-by-side of differences.
"""
import os
import re
import subprocess
import sys

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

WORD_RE = re.compile(r"/\*\s+[0-9A-F]+\s+([0-9A-F]+)\s+([0-9A-F]{8})\s+\*/\s*(.*)")


def asm_words(path):
    words, text = [], []
    global VRAM0
    with open(path) as f:
        for line in f:
            m = WORD_RE.search(line)
            if m:
                if not words:
                    VRAM0 = int(m.group(1), 16)
                words.append(int(m.group(2), 16))
                text.append(m.group(3).strip())
    return words, text


def sext16(x):
    x &= 0xFFFF
    return x - 0x10000 if x & 0x8000 else x


def disasm(o_path, sym):
    out = subprocess.run(
        ["mips-linux-gnu-objdump", "-d", "-r", "--no-show-raw-insn", "-M", "no-aliases",
         "--disassemble=" + sym, o_path], capture_output=True, text=True).stdout
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    verbose = "-v" in sys.argv
    c_file = args[0]
    want = set(args[1:])
    obj = os.path.join("build", c_file[:-2] + ".c.o")
    r = subprocess.run(["make", "VERSION=eu", obj], capture_output=True, text=True)
    if r.returncode != 0:
        print(r.stdout[-3000:])
        print(r.stderr[-3000:])
        sys.exit(1)
    base = os.path.splitext(c_file)[0]
    rel = os.path.relpath(base, "src_eu")
    asm_dir = os.path.join("asm", "nonmatchings", rel)

    with open(obj, "rb") as f:
        elf = ELFFile(f)
        text = elf.get_section_by_name(".text")
        data = text.data()
        relmask = {}
        rels = []
        for sec in elf.iter_sections():
            if isinstance(sec, RelocationSection) and sec.name in (".rel.text", ".rela.text"):
                for rr in sec.iter_relocations():
                    t = rr["r_info_type"]
                    off = rr["r_offset"]
                    rels.append((off, t, rr["r_info_sym"]))
                    if t == 4:  # R_MIPS_26
                        relmask[off] = 0xFC000000
                    elif t in (5, 6):  # HI16/LO16
                        relmask[off] = 0xFFFF0000
                    elif t == 2:
                        relmask[off] = 0
        symtab = elf.get_section_by_name(".symtab")
        rels = [(o, t, symtab.get_symbol(i).name) for o, t, i in rels]
        tidx = [i for i, s in enumerate(elf.iter_sections()) if s.name == ".text"][0]
        funcs = []
        for s in symtab.iter_symbols():
            if s["st_shndx"] == tidx and s["st_info"]["type"] == "STT_FUNC":
                funcs.append((s["st_value"], s["st_size"], s.name))
        funcs.sort()
        # static functions can carry st_size 0: size them up to the next symbol
        for k, (a, sz, nm) in enumerate(funcs):
            if sz == 0:
                nxt = funcs[k + 1][0] if k + 1 < len(funcs) else len(data)
                funcs[k] = (a, nxt - a, nm)

    bad = 0
    for addr, size, name in funcs:
        if want and name not in want:
            continue
        spath = os.path.join(asm_dir, name + ".s")
        if not os.path.exists(spath):
            print(f"?? {name}: no asm file {spath}")
            continue
        ref, reftext = asm_words(spath)
        mine = [int.from_bytes(data[addr + i:addr + i + 4], "big") for i in range(0, size, 4)]
        # strip trailing nops IDO may pad with
        diffs = []
        n = max(len(ref), len(mine))
        for i in range(n):
            a = ref[i] if i < len(ref) else None
            b = mine[i] if i < len(mine) else None
            m = relmask.get(addr + i * 4, 0xFFFFFFFF)
            if a is None or b is None or (a & m) != (b & m):
                diffs.append(i)
        if "-s" in sys.argv:
            last_hi = None
            for off, t, sname in rels:
                if not (addr <= off < addr + size):
                    continue
                i = (off - addr) // 4
                if i >= len(ref):
                    continue
                if t == 5:
                    last_hi = i
                elif t == 6 and last_hi is not None:
                    h = last_hi
                    tgt = ((ref[h] & 0xFFFF) << 16) + sext16(ref[i])
                    add = ((mine[h] & 0xFFFF) << 16) + sext16(mine[i])
                    print(f"SYM {sname} = 0x{(tgt - add) & 0xFFFFFFFF:08X}  ({reftext[i]})")
                elif t == 4:
                    tgt = ((ref[i] & 0x3FFFFFF) << 2) | (VRAM0 & 0xF0000000)
                    add = (mine[i] & 0x3FFFFFF) << 2
                    print(f"SYM {sname} = 0x{(tgt - add) & 0xFFFFFFFF:08X}  ({reftext[i]})")
        if not diffs:
            print(f"OK   {name}")
        else:
            bad += 1
            print(f"DIFF {name}: ref {len(ref)} insns, mine {len(mine)}, {len(diffs)} differing")
            if verbose:
                for i in range(n):
                    a = ref[i] if i < len(ref) else None
                    b = mine[i] if i < len(mine) else None
                    mark = "*" if i in diffs else " "
                    at = reftext[i] if a is not None else ""
                    print(f" {mark} {i*4:4X} {a if a is None else format(a,'08X')} {b if b is None else format(b,'08X')}  {at}")
                print(disasm(obj, name))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
