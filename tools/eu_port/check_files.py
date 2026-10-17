#!/usr/bin/env python3
"""Compare each compiled src_eu object's .text with the original EU bytes at the
file's rom range from conker.eu.yaml (relocated fields masked). Independent of
link layout, and covers functions written in C (which have no nonmatchings .s).

Usage (from conker/, inside the build container, after the objects are built):
    python3 ../tools/eu_port/check_files.py [src_eu/X.c ...]
"""
import re
import struct
import sys

from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

MASKS = {4: 0xFC000000, 5: 0xFFFF0000, 6: 0xFFFF0000}
SEGMENTS = ("init", "game", "debugger")


def file_ranges():
    """{c file name: (rom start, rom end)} for c subsegments of the code segments."""
    entries, cur = [], None
    for line in open("conker.eu.yaml"):
        m = re.match(r"  - name:\s+(\w+)", line)
        if m:
            cur = m.group(1)
            entries.append((None, None, None))  # segment break
            continue
        m = re.match(r"\s+- \[(0x[0-9A-Fa-f]+), *([.\w]+)(?:, *([\w/]+))?\]", line)
        if m and cur in SEGMENTS:
            entries.append((int(m.group(1), 16), m.group(2), m.group(3)))
        m2 = re.match(r"  - \[(0x[0-9A-Fa-f]+)", line)
        if m2:
            entries.append((int(m2.group(1), 16), "end", None))
    seg_starts = {}
    for line in open("conker.eu.yaml"):
        pass
    out = {}
    for i, (rom, kind, name) in enumerate(entries):
        if kind == "c":
            nxt = next((e[0] for e in entries[i + 1:] if e[0] is not None), None)
            out[name] = (rom, nxt)
    return out


def text_words(path):
    with open(path, "rb") as f:
        elf = ELFFile(f)
        sec = elf.get_section_by_name(".text")
        data = sec.data() if sec else b""
        masked = {}
        for s in elf.iter_sections():
            if isinstance(s, RelocationSection) and s.name == ".rel.text":
                for r in s.iter_relocations():
                    masked[r["r_offset"]] = MASKS.get(r["r_info_type"], 0)
    return data, masked


def owned_sections():
    """{c file name: [(section, rom start, rom end)]} for .rodata/.data pieces of the *_data
    segments (a file's own data sections carved out of the blobs)."""
    out, cur, subs = {}, None, []
    lines = open("conker.eu.yaml").read().split("\n")
    for line in lines:
        m = re.match(r"  - name:\s+(\w+)", line)
        if m:
            cur = m.group(1)
        m = re.match(r"\s+- \[(0x[0-9A-Fa-f]+)(?:, *([.\w]+))?(?:, *([\w/]+))?\]", line)
        if m and cur:
            subs.append((cur, int(m.group(1), 16), m.group(2), m.group(3)))
    for i, (seg, rom, kind, name) in enumerate(subs):
        if seg.endswith("_data") and kind in (".rodata", ".data") and name:
            nxt = subs[i + 1][1] if i + 1 < len(subs) else None
            out.setdefault(name, []).append((kind, rom, nxt))
    return out


def section_diff(path, sec, want):
    """None if the object's section matches want (relocated words masked, the rest of want
    zero padding), else a short reason."""
    with open(path, "rb") as f:
        elf = ELFFile(f)
        s = elf.get_section_by_name(sec)
        data = s.data() if s else b""
        masked = set()
        for r in elf.iter_sections():
            if isinstance(r, RelocationSection) and r.name == ".rel" + sec:
                for x in r.iter_relocations():
                    masked.add(x["r_offset"] & ~3)
    if len(data) > len(want):
        return f"{sec} size {len(data):#x} > {len(want):#x}"
    if any(want[len(data):]):
        return f"{sec} size {len(data):#x} < {len(want):#x}"
    for off in range(0, len(data), 4):
        if off in masked:
            continue
        if data[off:off + 4] != want[off:off + 4]:
            return f"{sec} differs at +{off:#x}"
    return None


def main():
    rom = open("conker.eu.bin", "rb").read()
    ranges = file_ranges()
    owned = owned_sections()
    names = [a[len("src_eu/"):-2] for a in sys.argv[1:]] or sorted(ranges)
    bad = 0
    for name in names:
        if name not in ranges:
            print(f"SKIP {name} (no c subsegment)")
            continue
        start, end = ranges[name]
        try:
            data, masked = text_words(f"build/src_eu/{name}.c.o")
        except FileNotFoundError:
            print(f"MISSING {name}")
            bad += 1
            continue
        want = rom[start:end] if end else rom[start:start + len(data)]
        if len(data) != len(want):
            print(f"SIZE {name}: built {len(data):#x} expected {len(want):#x}")
            bad += 1
            continue
        diffs = []
        for off in range(0, len(data), 4):
            a = struct.unpack(">I", data[off:off + 4])[0]
            b = struct.unpack(">I", want[off:off + 4])[0]
            m = masked.get(off, 0xFFFFFFFF)
            if (a & m) != (b & m):
                diffs.append(off)
        if diffs:
            print(f"DIFF {name}: {len(diffs)} words, first at +{diffs[0]:#x} (rom {start + diffs[0]:#x})")
            bad += 1
            continue
        why = None
        for sec, a, b in owned.get(name, []):
            why = section_diff(f"build/src_eu/{name}.c.o", sec, rom[a:b])
            if why:
                break
        if why:
            print(f"DATA {name}: {why}")
            bad += 1
        else:
            print(f"OK {name}")
    print(f"{bad} bad of {len(names)}")


if __name__ == "__main__":
    main()
