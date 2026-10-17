#!/usr/bin/env python3
"""Hand-port one US C file to EU (for files port.py could not place).

    port_one.py <stem> <eu rom start> <eu rom end> [US_NAME=0xEUVRAM ...] [--auto-anchors] [--apply]

--auto-anchors uses every match.json match of the file as an anchor.
--src=<us stem> --first=<func> --last=<func> port part of a US file under another name.

Function placement is piecewise-shift: every function keeps the shift of the last
anchor before it (the first function is anchored at the EU rom start). Prints the
placement and whether each EU address is a function start, a merged stub (inside
another function) or nothing. With --apply:
  * adds "US name = EU addr; // type:func" lines to symbol_addrs.eu.txt,
  * turns the EU asm subsegment at <start> into [start, c, stem] (and makes sure
    an [end, asm] boundary follows),
  * removes src_eu/<stem>.c so that splat writes a GLOBAL_ASM-only stub (and the
    .s files for every function); copy the US C in afterwards.
Run from conker/.
"""
import bisect
import os
import re
import sys

sys.path.insert(0, os.path.dirname(__file__))
import eu_asm  # noqa: E402
from port import (US_SEGMENTS, EU_SEGMENTS, seg_of, rom_to_vram, file_functions_live,  # noqa: E402
                  load_symbol_file, us_vram_of)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply = "--apply" in sys.argv
    stem, start, end = args[0], int(args[1], 16), int(args[2], 16)
    anchors = {}
    for a in args[3:]:
        n, v = a.split("=")
        anchors[n] = int(v, 16)
    opts = dict(a[2:].split("=", 1) for a in sys.argv[1:] if a.startswith("--") and "=" in a)
    if "--auto-anchors" in sys.argv:
        import json
        mt = json.load(open("build_port/match.json"))["matches"]
        for n, e in mt.items():
            if e.get("file") == opts.get("src", stem) and n not in anchors and n.startswith(("func_", "n_", "os", "__")):
                anchors[n] = e["vram"]
    opts = dict(a[2:].split("=", 1) for a in sys.argv[1:] if a.startswith("--") and "=" in a)
    src_stem = opts.get("src", stem)
    text = open(f"src/{src_stem}.c", encoding="latin-1").read()
    funcs = file_functions_live(text)
    us_syms = load_symbol_file("symbol_addrs.us.txt")
    # order by US address
    funcs = sorted(funcs, key=lambda f: us_vram_of(f[0], us_syms))
    names = [f[0] for f in funcs]
    lo = names.index(opts["first"]) if "first" in opts else 0
    hi = names.index(opts["last"]) + 1 if "last" in opts else len(funcs)
    funcs = funcs[lo:hi]
    eu = eu_asm.functions()
    starts = sorted((v, n, s) for n, (v, s) in eu.items())
    svals = [s[0] for s in starts]
    seg = "init" if start < EU_SEGMENTS["game"][0] else ("game" if start < EU_SEGMENTS["debugger"][0] else "debugger")
    eu_v0 = rom_to_vram(start, EU_SEGMENTS, seg)
    eu_end = rom_to_vram(end, EU_SEGMENTS, seg)
    shift = None
    placed = []
    for name, kind in funcs:
        usv = us_vram_of(name, us_syms)
        if shift is None:
            shift = eu_v0 - usv
        if name in anchors:
            shift = anchors[name] - usv
        ev = usv + shift
        i = bisect.bisect_right(svals, ev) - 1
        st = "?"
        if i >= 0 and svals[i] == ev:
            st = f"start ({starts[i][1]}, {starts[i][2]:#x})"
        elif i >= 0 and svals[i] < ev < svals[i] + starts[i][2]:
            st = f"inside {starts[i][1]}+{ev - svals[i]:#x}"
        if not (eu_v0 <= ev < eu_end):
            st += " OUTSIDE FILE"
        placed.append((name, kind, ev))
        print(f"{kind:4} {name:30} US {usv:08X} EU {ev:08X} {st}")
    inrange = [s for s in starts if eu_v0 <= s[0] < eu_end]
    covered = {p[2] for p in placed}
    extra = [s for s in inrange if s[0] not in covered]
    for s in extra:
        print(f"EXTRA EU function {s[1]} at {s[0]:08X} size {s[2]:#x}")
    if not apply:
        return
    syms = load_symbol_file("symbol_addrs.eu.txt")
    by_addr = {}
    for n, v in syms.items():
        by_addr.setdefault(v, []).append(n)
    lines = []
    for name, kind, ev in placed:
        if syms.get(name) == ev:
            continue
        if name in syms:
            sys.exit(f"{name} already mapped to {syms[name]:08X}")
        others = [n for n in by_addr.get(ev, []) if n != name]
        if others:
            print(f"note: {ev:08X} also named {others}; leaving them")
        lines.append(f"{name:<32}= 0x{ev:08X}; // type:func")
    with open("symbol_addrs.eu.txt", "a") as f:
        for line in lines:
            f.write(line + "\n")
    print(f"added {len(lines)} symbols")
    y = open("conker.eu.yaml").read()
    old = f"      - [0x{start:X}, asm]\n"
    if old not in y:
        sys.exit(f"no [0x{start:X}, asm] subsegment in conker.eu.yaml")
    new = f"      - [0x{start:X}, c, {stem}]\n"
    if f"[0x{end:X}," not in y:
        new += f"      - [0x{end:X}, asm]\n"
    y = y.replace(old, new)
    open("conker.eu.yaml", "w").write(y)
    path = f"src_eu/{stem}.c"
    if os.path.exists(path):
        os.remove(path)
    print("yaml updated")


if __name__ == "__main__":
    main()
