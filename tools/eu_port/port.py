#!/usr/bin/env python3
"""Port US C sources to the EU version.

Uses build_port/match.json (match.py + resolve.py) and the current EU asm split to
  * place every function of each US C file in EU (matched C bodies directly,
    GLOBAL_ASM functions via the US->EU shift of their file),
  * copy portable files into src_eu/, turning C functions whose EU code differs
    into GLOBAL_ASM includes (US C kept under #if 0 for reference),
  * write EU subsegments for those files into conker.eu.yaml,
  * write symbol_addrs.eu.txt with US names at EU addresses.

Run from conker/ (plain python3, no third-party modules).
"""
import bisect
import glob
import json
import os
import re

import eu_asm
import sys

US_SEGMENTS = {  # name: (rom start, vram start)
    "init": (0x1000, 0x10001000),
    "game": (0x2D4B0, 0x15000000),
    "debugger": (0x255880, 0x16000000),
}
EU_SEGMENTS = {
    "init": (0x1000, 0x10001000),
    "game": (0x2D810, 0x15000000),
    "debugger": (0x256450, 0x16000000),
}
SEG_BY_VRAM_TOP = {0x10: "init", 0x15: "game", 0x16: "debugger"}

# C files with .data/.bss of their own; .rodata-only files are placed via section_bases
SKIP_DATA_FILES = {"init_50A0"}
DATA_SEGMENTS = {  # name: (rom start, vram start, size)
    "init_data": (0x29400, 0x80029400, 0x4410),
    "game_data": (0x228130, 0x80082EB0, 0x2E320),
    "debugger_data": (0x259B50, 0x16003700, 0x1658),
}

FUNC_RE = re.compile(r"func_([0-9A-F]{8})")


def seg_of(vram):
    return SEG_BY_VRAM_TOP[vram >> 24]


def rom_to_vram(rom, segs, seg):
    r, v = segs[seg]
    return rom - r + v


def vram_to_rom(vram, segs):
    r, v = segs[seg_of(vram)]
    return vram - v + r


def load_symbol_file(path):
    out = {}
    if os.path.exists(path):
        for line in open(path):
            m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
            if m:
                out[m.group(1)] = int(m.group(2), 16)
    return out


def us_vram_of(name, us_syms):
    m = FUNC_RE.fullmatch(name)
    return int(m.group(1), 16) if m else us_syms.get(name)


def eu_function_table():
    """EU function starts {vram: (name, size)} from the current split."""
    return {vram: (name, size) for name, (vram, size) in eu_asm.functions().items()}


def us_c_files():
    """[(us rom, name)] for c subsegments, plus the rom of the following subsegment."""
    entries = []
    for m in re.finditer(r"^\s+- \[(0x[0-9A-Fa-f]+), *([.\w]+)(?:, *([\w/]+))?\]", open("conker.us.yaml").read(), re.M):
        entries.append((int(m.group(1), 16), m.group(2), m.group(3)))
    files = []
    for i, (rom, kind, name) in enumerate(entries):
        if kind == "c":
            files.append((rom, name, entries[i + 1][0] if i + 1 < len(entries) else None))
    return files


def file_functions(name):
    """Ordered (func, kind) for a US C file: kind 'c' for defined bodies, 'asm' for GLOBAL_ASM."""
    text = open(f"src/{name}.c", encoding="latin-1").read()
    found = []
    for m in re.finditer(r'#pragma\s+GLOBAL_ASM\("([^"]+)/(\w+)\.s"\)', text):
        found.append((m.start(), m.group(2), "asm"))
    # function definitions: identifier followed by '(' on a line starting at column 0, not ending in ';'
    for m in re.finditer(r"^(?!#|//|\s|typedef|extern|static\s+\w+\s+\w+\s*;)[^\n;=]*?\b(\w+)\s*\([^;{]*\)\s*\{", text, re.M):
        if m.group(1) not in ("if", "while", "for", "switch", "sizeof"):
            found.append((m.start(), m.group(1), "c"))
    found.sort()
    seen, out = set(), []
    for _, fn, kind in found:
        if fn not in seen:
            seen.add(fn)
            out.append((fn, kind))
    return text, out


def strip_if0(text):
    """Remove #if 0 blocks so commented-out code isn't treated as live functions."""
    return re.sub(r"^#if 0\b.*?^#endif\b[^\n]*", lambda m: "\n" * m.group(0).count("\n"), text, flags=re.M | re.S)


def function_span(text, fn):
    """(start, end) character span of a C function definition."""
    m = re.search(r"^[^\n;#]*\b" + re.escape(fn) + r"\s*\([^;{]*\)\s*\{", text, re.M)
    if not m:
        return None
    depth, i = 0, m.end() - 1
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                end = text.find("\n", i)
                return m.start(), (end + 1 if end != -1 else len(text))
        i += 1
    return None


def place_by_shift(funcs, us_vrams, us_end, matches, eu_funcs, eu_starts, pool):
    """Each function at its US address plus the shift of the nearest matched function
    (in this file if any, else the segment); sizes must agree."""
    anchors = [(uv, matches[fn]["vram"] - uv) for (fn, _), uv in zip(funcs, us_vrams) if fn in matches]
    local = bool(anchors)
    placed = []
    for i, (fn, kind) in enumerate(funcs):
        uv = us_vrams[i]
        if kind == "c" and fn in matches:
            placed.append((fn, kind, matches[fn]["vram"], True))
            continue
        shift = min(anchors or pool, key=lambda a: abs(a[0] - uv))[1]
        ev = uv + shift
        if ev not in eu_funcs:
            return None, f"{fn}: predicted EU {ev:#x} is not a function start"
        # sizes must agree; the last function may differ by its alignment padding
        nxt = us_vrams[i + 1] if i + 1 < len(funcs) else us_end
        if nxt is not None and nxt > uv:
            diff = (nxt - uv) - eu_funcs[ev][1]
            if diff != 0 and not (i + 1 == len(funcs) and 0 < diff < 16):
                return None, f"{fn}: size US {nxt - uv:#x} != EU {eu_funcs[ev][1]:#x}"
        elif not local:
            return None, f"{fn}: borrowed shift and no size to verify"
        placed.append((fn, kind, ev, False))
    vrams = [p[2] for p in placed]
    if vrams != sorted(vrams) or len(set(vrams)) != len(vrams):
        return None, "EU order differs"
    i0, i1 = eu_starts.index(vrams[0]), eu_starts.index(vrams[-1])
    if eu_starts[i0:i1 + 1] != vrams:
        return None, "EU has extra functions in range"
    return placed, None


def place_by_anchors(funcs, us_vrams, us_end, matches, eu_funcs, eu_starts, pool, eu_labels):
    """Predict each EU address from the nearest matched function before it and after it.
    They agree unless a function between them changed size; then take the prediction
    that lands on a known EU function or label. Tolerates EU stubs merged by the split."""
    keys = [a for a, _ in pool]
    placed = []
    for (fn, kind), uv in zip(funcs, us_vrams):
        if fn in matches:
            placed.append((fn, kind, matches[fn]["vram"], kind == "c"))
            continue
        i = bisect.bisect_right(keys, uv)
        fwd = uv + pool[i - 1][1] if i else None
        bwd = uv + pool[i][1] if i < len(pool) else None
        known = eu_funcs.keys() | eu_labels
        if fwd == bwd or (fwd in known and bwd not in known):
            ev = fwd
        elif bwd in known and fwd not in known:
            ev = bwd
        else:
            return None, f"{fn}: cannot choose EU address ({fwd and hex(fwd)} / {bwd and hex(bwd)})"
        placed.append((fn, kind, ev, False))
    vrams = [p[2] for p in placed]
    if None in vrams or vrams != sorted(vrams) or len(set(vrams)) != len(vrams):
        return None, "EU order differs"
    if vrams[0] not in known:
        return None, f"EU start {vrams[0]:#x} is not a function or label"
    # no unexplained EU function may start inside the file
    i = bisect.bisect_left(keys, us_end) if us_end else len(pool)
    end = (us_end + pool[i][1]) if us_end and i < len(pool) else None
    lo = bisect.bisect_left(eu_starts, vrams[0])
    hi = bisect.bisect_left(eu_starts, end) if end else bisect.bisect_right(eu_starts, vrams[-1])
    extra = [v for v in eu_starts[lo:hi] if v not in set(vrams)]
    if extra:
        return None, f"EU has extra functions in range: {[hex(v) for v in extra[:3]]}"
    return placed, None


def main():
    d = json.load(open("build_port/match.json"))
    matches = d["matches"]
    voted = {k: int(v, 16) for k, v in d["symbols"].items()}
    us_syms = load_symbol_file("symbol_addrs.us.txt")
    us_syms.update(load_symbol_file("undefined_funcs.us.txt"))
    eu_funcs = eu_function_table()
    eu_starts = sorted(eu_funcs)
    eu_labels = eu_asm.labels()
    global_anchors = {s: [] for s in US_SEGMENTS}
    for m in matches.values():
        if "us_vram" in m and seg_of(m["us_vram"]) == seg_of(m["vram"]):
            global_anchors[seg_of(m["us_vram"])].append((m["us_vram"], m["shift"]))
    for seg, pool in global_anchors.items():
        pool.sort()
        # drop outliers: both neighbours agree with each other but not with this one
        global_anchors[seg] = [a for i, a in enumerate(pool)
                               if not (0 < i < len(pool) - 1 and pool[i - 1][1] == pool[i + 1][1] != a[1])]

    report = {"ported": [], "failed": {}}
    eu_c_files = []  # (eu rom start, eu rom end, name)
    func_names = {}  # US name -> EU vram
    rodata_files = []  # (eu vram, size, name)
    for us_rom, name, next_rom in us_c_files():
        if name in SKIP_DATA_FILES:
            report["failed"][name] = "has own data sections"
            continue
        text, funcs = file_functions(name)
        live = {fn for fn, _ in file_functions_live(text)}
        funcs = [(fn, k) for fn, k in funcs if fn in live]
        if not funcs:
            report["failed"][name] = "no functions found"
            continue
        us_vrams = [us_vram_of(fn, us_syms) for fn, _ in funcs]
        if None in us_vrams:
            report["failed"][name] = f"cannot place {funcs[us_vrams.index(None)][0]} (no US address)"
            continue
        seg = seg_of(us_vrams[0])
        if us_vrams[0] != rom_to_vram(us_rom, US_SEGMENTS, seg):
            report["failed"][name] = "first function is not at US file start"
            continue
        us_end = rom_to_vram(next_rom, US_SEGMENTS, seg) if next_rom else None
        if us_end is not None and seg_of(us_end) != seg:
            us_end = None
        rodata = None
        if name in d["us_sections"]:
            base = d["section_bases"].get(f"{name}:.rodata")
            if set(d["us_sections"][name]) != {".rodata"} or base is None:
                report["failed"][name] = "data sections not placeable"
                continue
            rodata = (int(base, 16), d["us_sections"][name][".rodata"])
        ctx = (funcs, us_vrams, us_end, matches, eu_funcs, eu_starts, global_anchors[seg])
        placed, problem = place_by_shift(*ctx)
        if problem:
            placed, problem2 = place_by_anchors(*ctx, eu_labels)
            if problem2:
                report["failed"][name] = f"{problem} / {problem2}"
                continue
        vrams = [p[2] for p in placed]
        i1 = bisect.bisect_right(eu_starts, vrams[-1]) - 1
        last_v = vrams[-1]
        nxt = eu_starts[i1 + 1] if i1 + 1 < len(eu_starts) and seg_of(eu_starts[i1 + 1]) == seg_of(last_v) else None
        end_rom = vram_to_rom(nxt, EU_SEGMENTS) if nxt else None
        eu_c_files.append((vram_to_rom(vrams[0], EU_SEGMENTS), end_rom, name, placed))
        if rodata:
            rodata_files.append((rodata[0], rodata[1], name))
        for fn, _, ev, _ in placed:
            func_names[fn] = ev
        report["ported"].append(name)

    # write src_eu
    differing = 0
    for _, _, name, placed in eu_c_files:
        text = open(f"src/{name}.c", encoding="latin-1").read()
        for fn, kind, ev, matched in placed:
            if kind == "c" and not matched:
                span = function_span(text, fn)
                if span is None:
                    sys.exit(f"cannot find body of {fn} in {name}")
                s, e = span
                # keep the signature visible so later callers still see the prototype
                proto = " ".join(text[s:text.index("{", s)].split()) + ";\n"
                pragma = f'#pragma GLOBAL_ASM("asm/nonmatchings/{name}/{fn}.s")\n'
                text = (text[:s] + proto + pragma + "#if 0 // US version; EU code differs\n"
                        + text[s:e] + "#endif\n" + text[e:])
                differing += 1
        out = f"src_eu/{name}.c"
        os.makedirs(os.path.dirname(out), exist_ok=True)
        open(out, "w", encoding="latin-1").write(text)

    # symbols: US names at EU addresses. Functions from placement, data from relocation votes.
    old_eu = {}
    for line in open("build_port/symbol_addrs.eu.base.txt"):
        m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if m:
            old_eu[m.group(1)] = int(m.group(2), 16)
    taken = {}
    lines = []
    for fn, ev in sorted(func_names.items(), key=lambda x: x[1]):
        taken[ev] = fn
        lines.append(f"{fn:<32}= 0x{ev:08X}; // type:func")
    data_lines, alias_lines = [], []
    for sym, a in sorted(voted.items(), key=lambda x: x[1]):
        if sym in func_names:
            continue
        if a in taken:  # second name for one address: linker-only, splat keeps the first
            if (a >> 24) not in SEG_BY_VRAM_TOP:
                alias_lines.append(f"{sym:<32}= 0x{a:08X};")
            continue
        if (a >> 24) in SEG_BY_VRAM_TOP:  # a function referenced but not in a ported file
            lines.append(f"{sym:<32}= 0x{a:08X}; // type:func")
        else:
            data_lines.append(f"{sym:<32}= 0x{a:08X};")
        taken[a] = sym
    known = set(func_names) | set(voted)
    for sym, a in sorted(old_eu.items(), key=lambda x: x[1]):
        if sym not in known and a not in taken:
            lines.append(f"{sym:<32}= 0x{a:08X};")
            taken[a] = sym
    # A US address-derived name now living elsewhere would collide with splat's
    # auto-name for whatever EU symbol sits at that address; name those explicitly.
    used = set(taken.values())
    baseline_names = set()
    for path in glob.glob("asm/**/*.s", recursive=True):
        baseline_names.update(re.findall(r"\b(?:func|D)_[0-9A-F]{8}\b", open(path).read()))
    for sym in sorted(used):
        m = re.fullmatch(r"(func|D)_([0-9A-F]{8})", sym)
        if not m:
            continue
        a = int(m.group(2), 16)
        if a in taken:
            continue
        if m.group(1) == "func":
            if a in eu_funcs:
                lines.append(f"func_eu_{a:08X}{'':<15}= 0x{a:08X}; // type:func")
            elif sym in baseline_names:  # a label splat already emits inside a function
                lines.append(f"func_eu_{a:08X}{'':<15}= 0x{a:08X};")
        elif m.group(1) == "D":
            data_lines.append(f"D_eu_{a:08X}{'':<18}= 0x{a:08X};")
        taken[a] = sym
    open("symbol_addrs.eu.txt", "w").write("\n".join(lines + data_lines) + "\n")
    # data lives in binary blobs for now, so define referenced data symbols for the linker
    open("undefined_syms.eu.txt", "w").write("\n".join(data_lines + alias_lines) + "\n")

    # yaml: replace subsegment lists of code segments
    yaml_text = open("conker.eu.yaml").read()
    for seg in ("init", "game", "debugger"):
        yaml_text = rewrite_segment(yaml_text, seg, [f for f in eu_c_files if seg_of(f[3][0][2]) == seg])
    for seg, (rom0, vram0, seg_size) in DATA_SEGMENTS.items():
        items = [(v - vram0 + rom0, size, n) for v, size, n in rodata_files if 0 <= v - vram0 < seg_size]
        if items:
            yaml_text = rewrite_data_segment(yaml_text, seg, rom0, sorted(items))
    open("conker.eu.yaml", "w").write(yaml_text)

    json.dump(report, open("build_port/port_report.json", "w"), indent=1)
    print(f"ported {len(report['ported'])} files, failed {len(report['failed'])}; "
          f"{differing} C functions differ in EU and fall back to asm")


def file_functions_live(text):
    stripped = strip_if0(text)
    found = []
    for m in re.finditer(r'#pragma\s+GLOBAL_ASM\("([^"]+)/(\w+)\.s"\)', stripped):
        found.append((m.group(2), "asm"))
    for m in re.finditer(r"^(?!#|//|\s|typedef|extern)[^\n;=]*?\b(\w+)\s*\([^;{]*\)\s*\{", stripped, re.M):
        found.append((m.group(1), "c"))
    return found


def rewrite_segment(yaml_text, seg, files):
    """Merge c-file boundaries into a code segment's subsegment list."""
    head = re.search(r"^  - name:\s+" + seg + r"\n(?:    \w+:.*\n)*?    subsegments:\n", yaml_text, re.M)
    body_start = head.end()
    m = re.compile(r"(?:^ {4,}- .*\n|^ {4,}#.*\n|^\s*\n)*", re.M).match(yaml_text, body_start)
    body = yaml_text[body_start:m.end()]
    bounds = {}
    for line in body.splitlines():
        mm = re.match(r"\s+- \[(0x[0-9A-Fa-f]+), *(\w+)", line)
        if mm:
            bounds[int(mm.group(1), 16)] = ("asm", None)
    starts = sorted(f[0] for f in files)
    for start, end, name, _ in files:
        # a file never extends past the start of the next ported file
        later = [s for s in starts if s > start]
        if later and (end is None or end > later[0]):
            end = later[0]
        for b in [b for b in bounds if start < b < (end if end else 1 << 32)]:
            del bounds[b]
        bounds[start] = ("c", name)
        if end is not None and end not in bounds:
            bounds[end] = ("asm", None)
    out = []
    for b in sorted(bounds):
        kind, name = bounds[b]
        out.append(f"      - [0x{b:X}, c, {name}]" if kind == "c" else f"      - [0x{b:X}, asm]")
    return yaml_text[:body_start] + "\n".join(out) + "\n" + yaml_text[m.end():]



def rewrite_data_segment(yaml_text, seg, rom0, items):
    """Carve each file's .rodata out of a data segment's binary blob."""
    head = re.search(r"^  - name:\s+" + seg + r"\n(?:    \w+:.*\n)*?    subsegments:\n", yaml_text, re.M)
    m = re.compile(r"(?:^ {4,}- .*\n|^ {4,}#.*\n|^\s*\n)*", re.M).match(yaml_text, head.end())
    out, pos = [], rom0
    for rom, size, name in items:
        if rom > pos:
            out.append(f"      - [0x{pos:X}, rodatabin]")
        out.append(f"      - [0x{rom:X}, .rodata, {name}]")
        pos = rom + size
    # rodatabin rather than bin: splat orders a segment's .data before its .rodata
    out.append(f"      - [0x{pos:X}, rodatabin]")
    return yaml_text[:head.end()] + "\n".join(out) + "\n" + yaml_text[m.end():]


if __name__ == "__main__":
    main()
