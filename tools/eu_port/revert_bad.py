#!/usr/bin/env python3
"""Revert non-matching newly decompiled functions back to GLOBAL_ASM.

For each given src_eu file: build its object, find the first function whose
bytes differ from the original EU rom (relocations masked), and if HEAD had that
function as GLOBAL_ASM, restore the pragma (copying the .s from a HEAD split).
Repeat until the file matches or the culprit isn't a new function.

Usage (from conker/, in the build container):
    revert_bad.py HEAD_CONKER_DIR src_eu/X.c [...]
HEAD_CONKER_DIR is the conker/ dir of a split of HEAD (provides nonmatchings .s).
"""
import os
import re
import shutil
import struct
import subprocess
import sys

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

sys.path.insert(0, os.path.dirname(__file__))
from check_files import MASKS, file_ranges  # noqa: E402
from port import function_span  # noqa: E402


def load(obj):
    with open(obj, "rb") as f:
        elf = ELFFile(f)
        sec = elf.get_section_by_name(".text")
        idx = elf.get_section_index(".text")
        data = sec.data()
        masked = {}
        for s in elf.iter_sections():
            if isinstance(s, RelocationSection) and s.name == ".rel.text":
                for r in s.iter_relocations():
                    masked[r["r_offset"]] = MASKS.get(r["r_info_type"], 0)
        funcs = sorted((s["st_value"], s.name) for s in elf.get_section_by_name(".symtab").iter_symbols()
                       if s["st_shndx"] == idx and s["st_info"]["type"] == "STT_FUNC" and s.name)
    return data, masked, funcs


def first_bad_function(name, rom, start, end):
    data, masked, funcs = load(f"build/src_eu/{name}.c.o")
    want = rom[start:end]
    for off in range(0, max(len(data), len(want)), 4):
        a = data[off:off + 4]
        b = want[off:off + 4]
        if len(a) < 4 or len(b) < 4:
            bad = off
            break
        m = masked.get(off, 0xFFFFFFFF)
        if (struct.unpack(">I", a)[0] & m) != (struct.unpack(">I", b)[0] & m):
            bad = off
            break
    else:
        return None, None
    owner = None
    for addr, fn in funcs:
        if addr <= bad:
            owner = fn
    return owner, bad


def main():
    head = sys.argv[1]
    rom = open("conker.eu.bin", "rb").read()
    ranges = file_ranges()
    for arg in sys.argv[2:]:
        name = arg[len("src_eu/"):-2]
        start, end = ranges[name]
        head_src = open(os.path.join(head, "src_eu", name + ".c"), encoding="latin-1").read()
        reverted = []
        for _ in range(50):
            r = subprocess.run(["make", "VERSION=eu", f"build/src_eu/{name}.c.o"], capture_output=True, text=True)
            if r.returncode:
                print(f"BUILD-FAIL {name}: {r.stderr.strip().splitlines()[-1:]}")
                break
            fn, off = first_bad_function(name, rom, start, end)
            if fn is None:
                print(f"OK {name} (reverted {len(reverted)}: {' '.join(reverted)})")
                break
            pragma = f'#pragma GLOBAL_ASM("asm/nonmatchings/{name}/{fn}.s")'
            if pragma not in head_src:
                print(f"STUCK {name}: first diff at +{off:#x} in {fn}, which was not GLOBAL_ASM at HEAD")
                break
            text = open(f"src_eu/{name}.c", encoding="latin-1").read()
            span = function_span(text, fn)
            if span is None:
                print(f"STUCK {name}: cannot find C body of {fn}")
                break
            s, e = span
            text = text[:s] + pragma + "\n" + text[e:]
            open(f"src_eu/{name}.c", "w", encoding="latin-1").write(text)
            dst = f"asm/nonmatchings/{name}/{fn}.s"
            os.makedirs(os.path.dirname(dst), exist_ok=True)
            shutil.copy(os.path.join(head, dst), dst)
            reverted.append(fn)
        else:
            print(f"GAVE-UP {name} after {len(reverted)} reverts")


if __name__ == "__main__":
    main()
