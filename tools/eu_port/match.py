#!/usr/bin/env python3
"""Locate decompiled US functions inside the EU build.

Each function is fingerprinted with relocated instruction fields masked out
(jal targets, %hi/%lo immediates), then looked up among the EU functions
assembled from splat's output. Matched pairs vote on where each US symbol
lives in EU, using the relocations at identical instruction offsets.

Run from conker/ inside the docker image after compile_us.py and an EU build.
Output: build_port/match.json
"""
import bisect
import glob
import json
import os
import re
import struct
from collections import Counter, defaultdict

import eu_asm
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

R_MIPS_26, R_MIPS_HI16, R_MIPS_LO16 = 4, 5, 6
MASKS = {R_MIPS_26: 0xFC000000, R_MIPS_HI16: 0xFFFF0000, R_MIPS_LO16: 0xFFFF0000}


def sext16(v):
    return v - 0x10000 if v & 0x8000 else v


def load_object(path):
    """Return (.text bytes, symbols {name: (offset, size, is_func)}, relocs {offset: (type, symname)})."""
    with open(path, "rb") as f:
        elf = ELFFile(f)
        text_sec = elf.get_section_by_name(".text")
        if text_sec is None:
            return b"", {}, {}
        text_idx = elf.get_section_index(".text")
        text = text_sec.data()
        symtab = elf.get_section_by_name(".symtab")
        syms = {}
        for s in symtab.iter_symbols():
            if s["st_shndx"] == text_idx and s.name and not s.name.startswith("$"):
                syms[s.name] = (s["st_value"], s["st_size"], s["st_info"]["type"] == "STT_FUNC")
        relocs = {}
        for sec in elf.iter_sections():
            if isinstance(sec, RelocationSection) and sec.name in (".rel.text", ".rela.text"):
                for r in sec.iter_relocations():
                    sym = symtab.get_symbol(r["r_info_sym"])
                    name = sym.name
                    if sym["st_info"]["type"] == "STT_SECTION":
                        name = "section:" + elf.get_section(sym["st_shndx"]).name
                    relocs[r["r_offset"]] = (r["r_info_type"], name)
    return text, syms, relocs


def function_spans(syms, text_len):
    """Sorted (name, start, end) for function symbols, sizing by next symbol when needed."""
    funcs = sorted((off, name, size) for name, (off, size, is_func) in syms.items() if is_func or size)
    spans = []
    for i, (off, name, size) in enumerate(funcs):
        nxt = funcs[i + 1][0] if i + 1 < len(funcs) else text_len
        end = off + size if size else nxt
        if end > off:
            spans.append((name, off, end))
    return spans


def fingerprint(text, start, end, relocs):
    words = []
    for off in range(start, end, 4):
        w = struct.unpack(">I", text[off:off + 4])[0]
        if off in relocs:
            w &= MASKS.get(relocs[off][0], 0xFFFFFFFF)
        words.append(w)
    # trailing nops are alignment padding, which differs between files
    while words and words[-1] == 0:
        words.pop()
    return tuple(words)


def eu_functions():
    """EU functions from splat's .s files, with vram resolved through the linked ELF."""
    with open("build/conker.eu.elf", "rb") as f:
        elf = ELFFile(f)
        addr = {s.name: s["st_value"] for s in elf.get_section_by_name(".symtab").iter_symbols() if s.name}
    sizes = {name: size for name, (_, size) in eu_asm.functions().items()}
    funcs = []
    for obj in glob.glob("build/asm/**/*.s.o", recursive=True):
        text, syms, relocs = load_object(obj)
        for name, (off, _, _) in syms.items():
            if name not in sizes or name not in addr:
                continue
            start, end = off, off + sizes[name]
            funcs.append({
                "name": name, "vram": addr[name], "fp": fingerprint(text, start, end, relocs),
                "relocs": {o - start: r for o, r in relocs.items() if start <= o < end},
                "words": [struct.unpack(">I", text[o:o + 4])[0] for o in range(start, end, 4)],
            })
    return funcs, addr


def us_functions():
    funcs = []
    for obj in glob.glob("build_port/us/**/*.o", recursive=True):
        rel = os.path.relpath(obj, "build_port/us")[:-2]
        text, syms, relocs = load_object(obj)
        for name, start, end in function_spans(syms, len(text)):
            funcs.append({
                "name": name, "file": rel, "fp": fingerprint(text, start, end, relocs),
                "relocs": {o - start: r for o, r in relocs.items() if start <= o < end},
                "words": [struct.unpack(">I", text[o:o + 4])[0] for o in range(start, end, 4)],
            })
    return funcs


def us_target_addend(rtype, word, hi_words):
    """Addend IDO encoded in a REL instruction (symbol-relative offset)."""
    if rtype == R_MIPS_LO16:
        return sext16(word & 0xFFFF)
    if rtype == R_MIPS_26:
        return (word & 0x03FFFFFF) << 2
    return None


def us_vram_of(name, us_syms):
    m = re.fullmatch(r"func_([0-9A-F]{8})", name)
    return int(m.group(1), 16) if m else us_syms.get(name)


def resolve_ambiguous(matches, ambiguous, eu_vram):
    """Pick among identical-looking EU candidates using the US->EU address shift of
    the nearest uniquely matched function; annotate every match with its shift."""
    us_syms = {}
    for line in open("symbol_addrs.us.txt"):
        m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)", line)
        if m:
            us_syms[m.group(1)] = int(m.group(2), 16)
    anchors = sorted((us_vram_of(n, us_syms), m["vram"] - us_vram_of(n, us_syms))
                     for n, m in matches.items() if us_vram_of(n, us_syms) is not None)
    keys = [a for a, _ in anchors]
    for name in list(ambiguous):
        v = us_vram_of(name, us_syms)
        if v is None:
            continue
        i = bisect.bisect_left(keys, v)
        shifts = {anchors[j][1] for j in (i - 1, i) if 0 <= j < len(anchors) and anchors[j][0] >> 24 == v >> 24}
        hits = [c for c in ambiguous[name]["candidates"] if eu_vram[c] - v in shifts]
        if len(hits) == 1:
            matches[name] = {"eu": hits[0], "vram": eu_vram[hits[0]], "file": ambiguous.pop(name)["file"], "via": "shift"}
    for n, m in matches.items():
        v = us_vram_of(n, us_syms)
        if v is not None:
            m["us_vram"], m["shift"] = v, m["vram"] - v


def main():
    eu, eu_addr = eu_functions()
    us = us_functions()
    by_fp = defaultdict(list)
    for f in eu:
        by_fp[f["fp"]].append(f)

    matches, ambiguous, unmatched = {}, {}, []
    for f in us:
        cands = by_fp.get(f["fp"], [])
        if len(f["fp"]) == 0:
            continue
        if len(cands) == 1:
            matches[f["name"]] = {"eu": cands[0]["name"], "vram": cands[0]["vram"], "file": f["file"]}
        elif cands:
            ambiguous[f["name"]] = {"file": f["file"], "candidates": [c["name"] for c in cands]}
        else:
            unmatched.append({"name": f["name"], "file": f["file"], "words": len(f["fp"])})

    resolve_ambiguous(matches, ambiguous, {f["name"]: f["vram"] for f in eu})

    # symbol votes from relocations at identical offsets in matched pairs
    eu_by_name = {f["name"]: f for f in eu}
    votes = defaultdict(Counter)
    us_by_name = {f["name"]: f for f in us}
    for name, m in matches.items():
        u, e = us_by_name[name], eu_by_name[m["eu"]]
        votes[name][m["vram"]] += 100
        for off, (rtype, usym) in u["relocs"].items():
            if usym.startswith("section:") or off not in e["relocs"]:
                continue
            etype, esym = e["relocs"][off]
            if etype != rtype or rtype == R_MIPS_HI16 or esym not in eu_addr:
                continue
            us_add = us_target_addend(rtype, u["words"][off // 4], None)
            eu_add = us_target_addend(etype, e["words"][off // 4], None)
            if rtype == R_MIPS_26:
                us_add, eu_add = 0, 0
            votes[usym][eu_addr[esym] + eu_add - us_add] += 1

    symbols = {}
    conflicts = {}
    for sym, c in votes.items():
        (best, n), *rest = c.most_common()
        symbols[sym] = best
        if rest:
            conflicts[sym] = {hex(a): k for a, k in c.most_common()}

    json.dump({
        "matches": matches, "ambiguous": ambiguous, "unmatched": unmatched,
        "symbols": {k: hex(v) for k, v in sorted(symbols.items())}, "conflicts": conflicts,
    }, open("build_port/match.json", "w"), indent=1)
    print(f"US functions: {len(us)}  EU functions: {len(eu)}")
    print(f"matched {len(matches)}  ambiguous {len(ambiguous)}  unmatched {len(unmatched)}")
    print(f"symbols mapped {len(symbols)}  with conflicting votes {len(conflicts)}")


if __name__ == "__main__":
    main()
