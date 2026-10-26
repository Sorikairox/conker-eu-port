#!/usr/bin/env python3
"""implicit_scan.py: list implicitly declared function calls in the NON_MATCHING sources (P230).

An implicit declaration makes the call `int f()`: float arguments are promoted to double and a float
return is read from v0 / as int. IDO accepts this silently (no warning even with -Xfullwarn); on N64
the code is wrong, and on wasm the call traps or gets wrong values (P227: cosf in game_eu_142E40.c).

Runs a host clang syntax-only pass per TU (src_eu/**/*.c except libultra) with
-DNON_MATCHING and only -Wimplicit-function-declaration enabled, then also without NON_MATCHING, and
reports call sites that are implicit in the NM build. Rows whose callee is float-related (libm names,
or a prototype elsewhere in src_eu / include with a by-value f32/f64 parameter or return) are marked FLOAT.

Usage: tools/port/implicit_scan.py [--all] [--tsv OUT] [files...]
  default: report only call sites inside `#ifdef NON_MATCHING` regions (NM-only implicit decls) plus
  a count of the rest; --all lists every implicit call site.
Output TSV columns: file line callee nm_only float proto_hint
A standing check: run after each conversion session; NM-relevant rows should be 0 (or listed).
P329: the source has no NON_MATCHING / #else halves any more (matching build on branch exact-byte-decomp-wip), so
every implicit call site is in the code the port compiles and counts as NM; the gate is 0 NM+float.
"""
import os, re, subprocess, sys, glob
from concurrent.futures import ThreadPoolExecutor

ROOT = os.environ.get("CONKER_ROOT")
if not ROOT:
    sys.exit("set CONKER_ROOT (eval \"$(tools/eu_port/wt.sh env port)\")")
SRC = os.path.join(ROOT, "conker")
FLAGS = ["-fsyntax-only", "--target=mips-linux-gnu", "-std=gnu89", "-D_LANGUAGE_C", "-D_FINALROM",
         "-DF3DEX_GBI_2", "-D_MIPS_SZLONG=32", "-I", ".", "-I", "include", "-I", "include/2.0L",
         "-I", "include/2.0L/PR", "-I", "include/libc", "-I", "include/libultra/os", "-I", "include/libultra/audio",
         "-I", "include/libultra/io", "-nostdinc", "-Wno-everything", "-Wno-error",
         "-Wimplicit-function-declaration", "-ferror-limit=0"]
LIBM = {"sinf", "cosf", "tanf", "sqrtf", "atan2f", "atanf", "asinf", "acosf", "fabsf", "powf", "expf",
        "logf", "floorf", "ceilf", "fmodf", "sin", "cos", "sqrt", "atan2", "fabs", "pow", "floor", "ceil",
        "fmod", "acos", "asin", "atan", "exp", "log"}
RX = re.compile(r"^(.*?):(\d+):\d+: (?:warning|error): (?:call to undeclared (?:library )?function|"
                r"implicit declaration of function|implicitly declaring library function) '(\w+)'")


def clang(path, nm):
    args = ["clang"] + FLAGS + (["-DNON_MATCHING"] if nm else []) + [path]
    p = subprocess.run(args, cwd=SRC, capture_output=True, text=True)
    if nm and p.returncode != 0:
        ERRS.append((path, sum(" error: " in l for l in p.stderr.splitlines())))
    out = set()
    for ln in p.stderr.splitlines():
        m = RX.match(ln)
        if m and os.path.normpath(m.group(1)) == os.path.normpath(path):
            out.add((int(m.group(2)), m.group(3)))
    return out


def nm_lines(path):
    """line numbers that are inside an `#ifdef NON_MATCHING` (non-#else) region."""
    res, stack = set(), []
    with open(os.path.join(SRC, path), errors="replace") as f:
        for i, ln in enumerate(f, 1):
            s = ln.strip()
            if re.match(r"#\s*if", s):
                stack.append("NM" if re.match(r"#\s*ifdef\s+NON_MATCHING\b|#\s*if\s+defined\(NON_MATCHING\)", s) else "X")
            elif re.match(r"#\s*else", s) and stack:
                stack[-1] = {"NM": "NOTNM", "NOTNM": "NM"}.get(stack[-1], stack[-1])
            elif re.match(r"#\s*endif", s) and stack:
                stack.pop()
            if "NM" in stack:
                res.add(i)
    return res


_protos = None
ERRS = []  # TUs where clang reported hard errors (the scan of those TUs may be incomplete)


def proto_hint(name):
    """a prototype of `name` found anywhere in the tree (headers / other TUs), for the float flag."""
    global _protos
    if _protos is None:
        _protos = {}
        rx = re.compile(r"^\s*(?:extern\s+)?(?:static\s+)?([A-Za-z_][\w\s\*]*?)\b(func_\w+|\w+f)\s*\(([^;{]*)\)\s*[;{]?\s*$")
        for p in glob.glob(os.path.join(SRC, "**/*.[ch]"), recursive=True):
            if "/build" in p or "/src/" in p or "/src_ects/" in p or "/src_debug/" in p:
                continue
            try:
                for ln in open(p, errors="replace"):
                    m = rx.match(ln)
                    if m and not re.match(r"(return|else|case|goto)\b", m.group(1).strip()):
                        _protos.setdefault(m.group(2), ("%s %s(%s)" % (m.group(1).strip(), m.group(2), m.group(3).strip()),
                                                        os.path.relpath(p, SRC)))
            except OSError:
                pass
    return _protos.get(name)


_asm = None
FPREG = re.compile(r"\$f(\d+)")


def asm_float_hint(name):
    """for a callee that is still asm: 'f12/f14 in' if it reads $f12/$f14 before writing them,
    'f0 out' if it writes $f0 within 4 insns before a jr $ra (or in its delay slot) and never $v0. '' otherwise / no asm file."""
    global _asm
    if _asm is None:
        _asm = {}
        for p in glob.glob(os.path.join(SRC, "asm/nonmatchings/**/func_*.s"), recursive=True):
            _asm.setdefault(os.path.basename(p)[:-2], p)
    p = _asm.get(name)
    if not p:
        return ""
    written, fin, f0w, v0w = set(), set(), False, False
    f0at, jrat, i = [], [], 0
    for ln in open(p, errors="replace"):
        m = re.search(r"\*/\s+([a-z0-9.]+)\s*(.*)$", ln) or re.match(r"\s+([a-z][a-z0-9.]*)\s+(.*)$", ln)
        if not m:
            continue
        op, ops = m.group(1), [o.strip() for o in m.group(2).split(",")]
        i += 1
        if op == "jr" and ops and ops[0] == "$ra":
            jrat.append(i)
        regs = [FPREG.findall(o) for o in ops]
        if op in ("swc1", "sdc1", "mfc1", "dmfc1", "cfc1") or op.startswith("c.") or op.startswith("b"):
            srcs, dst = [r for rr in regs for r in rr], None
        elif op in ("lwc1", "ldc1", "mtc1", "dmtc1", "ctc1"):
            srcs, dst = [], (regs[-1][0] if op in ("mtc1", "dmtc1", "ctc1") and regs[-1] else (regs[0][0] if regs[0] else None))
        elif ops and regs and regs[0] and op.endswith((".s", ".d", ".w", ".l")):
            srcs, dst = [r for rr in regs[1:] for r in rr], regs[0][0]
        else:
            srcs, dst = [], None
            if ops and re.match(r"\$v0$", ops[0]) and not op.startswith(("s", "b", "j")):
                v0w = True
        for r in srcs:
            if r in ("12", "14") and r not in written:
                fin.add(r)
        if dst is not None:
            written.add(dst)
            if dst == "0":
                f0at.append(i)
    h = []
    if fin:
        h.append("f%s in" % "/f".join(sorted(fin)))
    f0w = any(j - 4 <= k <= j + 1 for j in jrat for k in f0at)
    if f0w and not v0w:
        h.append("f0 out")
    return " ".join(h)


def float_by_value(proto):
    """f32/f64 return or by-value parameter (pointers are passed as words and are fine on N64)."""
    m = re.match(r"(.*?)\b(\w+)\s*\((.*)\)$", proto)
    if not m:
        return False
    ret, params = m.group(1), m.group(3)
    if re.search(r"\b(f32|f64|float|double)\b(?!\s*\*)", ret):
        return True
    return any(re.match(r"\s*(const\s+)?(f32|f64|float|double)\b(?!\s*[\*\(])", a) for a in params.split(","))


def main():
    argv = sys.argv[1:]
    show_all = "--all" in argv
    tsv = None
    if "--tsv" in argv:
        tsv = argv[argv.index("--tsv") + 1]
    files = [a for a in argv if a.endswith(".c")]
    if not files:
        files = sorted(os.path.relpath(p, SRC) for d in ("src_eu",)
                       for p in glob.glob(os.path.join(SRC, d, "**/*.c"), recursive=True))
    files = [f for f in files if "libultra" not in f]

    def one(f):
        nm = clang(f, True)
        if not nm:
            return f, []
        # P329: the NON_MATCHING wrappers are gone, every line is port code: every implicit call counts as "NM"
        return f, [(ln, fn, True) for ln, fn in sorted(nm)]

    with ThreadPoolExecutor(8) as ex:
        res = list(ex.map(one, files))
    rows = []
    for f, hits in res:
        for ln, fn, nmonly in hits:
            ph = proto_hint(fn)
            ah = "" if ph else asm_float_hint(fn)
            fl = fn in LIBM or bool(ph and float_by_value(ph[0])) or bool(ah)
            rows.append((f, ln, fn, nmonly, fl, "%s [%s]" % ph if ph else ("asm: " + ah if ah else "")))
    sel = rows if show_all else [r for r in rows if r[3]]
    for r in sel:
        print("%s:%d\t%s\t%s\t%s\t%s" % (r[0], r[1], r[2], "NM" if r[3] else "both", "FLOAT" if r[4] else "-", r[5]))
    if tsv:
        with open(tsv, "w") as o:
            o.write("file\tline\tcallee\tnm_only\tfloat\tproto_hint\n")
            for r in rows:
                o.write("%s\t%d\t%s\t%d\t%d\t%s\n" % (r[0], r[1], r[2], r[3], r[4], r[5]))
    for f, n in sorted(ERRS):
        print("clang errors (scan may be incomplete): %s (%d)" % (f, n))
    print("implicit_scan: %d TUs, %d implicit call sites (%d in NM code, %d float-related, %d NM+float)" % (
        len(files), len(rows), sum(r[3] for r in rows), sum(r[4] for r in rows), sum(r[3] and r[4] for r in rows)))


if __name__ == "__main__":
    main()
