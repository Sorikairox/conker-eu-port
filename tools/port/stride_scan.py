#!/usr/bin/env python3
"""P270: pointer-stride scan.  Lists C where a typed non-byte pointer (s16 *, f32 *, s32 *, T **, ...) gets a constant
offset (`p + 0xC`, `p += 0x10`, `p - 0x60`) without a `(u8 *)` cast.  C scales the constant by the element size; old m2c
batch bodies (P17 era) often meant bytes (P269: glow_trail_emit_points `f32 *temp_a0 + 0xC` = +0x30 bytes, asm addiu 0xC).

For each hit the function's asm (asm/nonmatchings/<file>/<func>.s) is searched for the immediate K (byte reading) and
K*size (element reading):  BYTE = only K found (likely bug), ELEM = only K*size found (C is right), BOTH / NONE = check
by hand (difftest).  Hits in matched C (outside #ifdef NON_MATCHING) are listed with kind=matched: they compile to the
original asm, so they are right by construction.

usage: tools/port/stride_scan.py [--all] [--hex-only] [files...]   (default: conker/src_eu/*.c; prints TSV + summary)
"""
import glob, os, re, sys

BYTE_T = {"u8", "s8", "char", "void", "UNK_TYPE1"}
SIZES = {"s16": 2, "u16": 2, "short": 2, "s32": 4, "u32": 4, "int": 4, "f32": 4, "float": 4, "long": 4,
         "s64": 8, "u64": 8, "f64": 8, "double": 8, "Vtx": 16, "Gfx": 8, "Mtx": 64}
DECL = re.compile(r"\b((?:unsigned\s+|signed\s+)?\w+)\s*(\*+)\s*(\w+)\s*(?:\[[^\]]*\])?\s*[;,)=]")
FUNC = re.compile(r"^[A-Za-z_][\w \*]*?\b(\w+)\(([^;]*)\)\s*\{\s*$")
NUM = r"(0x[0-9A-Fa-f]+|\d+)"


def elem_size(base, stars):
    if len(stars) > 1:
        return 4
    if base in BYTE_T:
        return 1
    return SIZES.get(base)  # None = unknown struct type (skipped)


def scan_file(path, root):
    rel = os.path.basename(path)[:-2]
    lines = open(path, errors="replace").read().split("\n")
    out = []
    nm_depth = []  # stack of booleans: inside an #ifdef NON_MATCHING arm
    i = 0
    while i < len(lines):
        l = lines[i]
        s = l.strip()
        if s.startswith("#if"):
            nm_depth.append("NON_MATCHING" in s and not s.startswith("#ifndef"))
        elif s.startswith("#else") and nm_depth:
            nm_depth[-1] = False
        elif s.startswith("#endif") and nm_depth:
            nm_depth.pop()
        m = FUNC.match(l)
        if not m:
            i += 1
            continue
        fname, params = m.group(1), m.group(2)
        kind = "NM" if any(nm_depth) else "matched"
        # body: up to the closing brace at column 0
        j = i + 1
        while j < len(lines) and not lines[j].startswith("}"):
            j += 1
        body = lines[i + 1:j]
        ptrs = {}
        for d in DECL.finditer(params + ";"):
            ptrs[d.group(3)] = (d.group(1), d.group(2))
        for b in body:
            if "=" in b.split(";")[0] and "(" in b:
                pass
            for d in DECL.finditer(b):
                # declarations only: line starts with the type
                if re.match(r"\s*(?:const\s+)?(?:unsigned\s+|signed\s+)?\w+\s*\*+\s*\w+", b) and not re.search(r"[=(]\s*$", b):
                    ptrs.setdefault(d.group(3), (d.group(1), d.group(2)))
        asm = os.path.join(root, "asm/nonmatchings", rel, fname + ".s")
        asmtxt = open(asm).read() if os.path.exists(asm) else None
        for k, b in enumerate(body):
            code = re.sub(r"/\*.*?\*/", "", b.split("//")[0])
            for name, (base, stars) in ptrs.items():
                es = elem_size(base, stars)
                if es is None or es == 1:
                    continue
                pat = re.compile(r"(?<![\w.>])((?:\w+\.)?" + re.escape(name) + r")\s*(\+=|-=|\+|-)\s*" + NUM + r"\b")
                for h in pat.finditer(code):
                    pre = code[:h.start()].rstrip()
                    if re.search(r"\(\s*(u8|s8|char|void)\s*\*\s*\)\s*$", pre):
                        continue  # (u8 *)p + K: byte arithmetic
                    if pre.endswith("*") and not pre.endswith("*)"):
                        continue  # *p += K: value arithmetic through the pointer
                    if pre.endswith("[") or re.match(r"\s*\]", code[h.end():]):
                        continue  # p[i + 1] index math
                    if re.search(r"\(\s*\w+\s*\)\s*$", pre):
                        continue  # (s32)p + K: integer arithmetic on a cast
                    var = h.group(1)
                    if "." in var and not var.endswith("." + name):
                        continue
                    if "." not in var and name != var:
                        continue
                    kv = int(h.group(3), 0)
                    if kv == 0:
                        continue
                    hexc = h.group(3).lower().startswith("0x")
                    verdict = "NOASM"
                    if asmtxt is not None:
                        def has(v):  # pointer steps show up as addiu immediates (or as load/store offsets for *(p + K))
                            return re.search(r"addiu\s+\$\w+, \$\w+, -?0x%X\s*$" % v, asmtxt, re.M) is not None or \
                                re.search(r"\s-?0x%X\(\$\w+\)" % v, asmtxt) is not None
                        a, e = has(kv), has(kv * es)
                        verdict = {(True, False): "BYTE", (False, True): "ELEM", (True, True): "BOTH", (False, False): "NONE"}[(a, e)]
                    out.append((kind, rel, fname, i + 2 + k, f"{base}{stars}", es, h.group(0), "hex" if hexc else "dec", verdict, code.strip()[:110]))
        i = j + 1
    return out


def main():
    a = [x for x in sys.argv[1:] if not x.startswith("--")]
    root = os.path.join(os.environ.get("CONKER_ROOT", os.path.expanduser("~/conker")), "conker")
    files = a or sorted(glob.glob(os.path.join(root, "src_eu/*.c")))
    hits = []
    for f in files:
        hits += scan_file(f, root)
    if "--hex-only" in sys.argv:
        hits = [h for h in hits if h[7] == "hex"]
    show = hits if "--all" in sys.argv else [h for h in hits if h[0] == "NM"]
    print("kind\tfile\tfunc\tline\ttype\tsize\texpr\tconst\tasm\tcode")
    for h in show:
        print("\t".join(map(str, h)))
    from collections import Counter
    c = Counter((h[0], h[8]) for h in hits)
    print("# summary:", ", ".join(f"{k[0]}/{k[1]}={v}" for k, v in sorted(c.items())),
          "| NM funcs:", len({h[2] for h in hits if h[0] == "NM"}), file=sys.stderr)


if __name__ == "__main__":
    main()
