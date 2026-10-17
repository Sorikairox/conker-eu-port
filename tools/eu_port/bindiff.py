#!/usr/bin/env python3
"""Report which object files contain bytes differing from the target binary.
Usage (from conker/): bindiff.py [VERSION]"""
import re
import sys

version = sys.argv[1] if len(sys.argv) > 1 else "eu"
want = open(f"conker.{version}.bin", "rb").read()
got = open(f"build/conker.{version}.bin", "rb").read()
print(f"size target {len(want):#x} built {len(got):#x}")

# rom ranges of each linked object, from the map's __romPos-relative layout
spans = []
section_rom = None
for line in open(f"build/conker.{version}.map"):
    m = re.match(r"\s*(\S+_ROM_START) = __romPos", line)
    m = re.match(r"^ (\.\w+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)", line)
    if m:
        spans.append((int(m.group(2), 16), int(m.group(3), 16), m.group(4), m.group(1)))
# map vram -> rom using each output section's load address
loads = {}
for line in open(f"build/conker.{version}.map"):
    m = re.match(r"^(\.\w+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+) load address 0x([0-9a-f]+)", line)
    if m:
        loads[m.group(1)] = (int(m.group(2), 16), int(m.group(4), 16))
first = None
bad = {}
for i in range(0, min(len(want), len(got)), 4):
    if want[i:i + 4] != got[i:i + 4]:
        first = i if first is None else first
        for vram, size, obj, sec in spans:
            base = loads.get(sec)
            if not base:
                continue
            rom = vram - base[0] + base[1]
            if rom <= i < rom + size:
                bad.setdefault(obj, []).append(i)
                break
        else:
            bad.setdefault("?", []).append(i)
print("first diff", hex(first) if first is not None else None)
for obj, offs in sorted(bad.items(), key=lambda x: x[1][0]):
    print(f"{obj}: {len(offs)} words, first at rom {offs[0]:#x}")
