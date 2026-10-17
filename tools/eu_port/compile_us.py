#!/usr/bin/env python3
"""Compile every US C source with GLOBAL_ASM pragmas stripped, so the
decompiled functions can be fingerprinted and located in another ROM version.

Run from conker/ inside the docker image. Output: build_port/us/<path>.o
"""
import os
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

SRC = "src"
OUT = "build_port/us"
CC = "../ido/ido5.3_recomp/cc"

INCLUDE = "-I . -I include -I include/2.0L -I include/2.0L/PR -I include/libc -I src/libultra/os -I src/libultra/audio -I src/libultra/io"
CFLAGS = ("-G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul "
          "-D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI_2 -D_MIPS_SZLONG=32 -woff 649,838 " + INCLUDE)
MIPSBIT = "-mips2 -o32"


def opt_overrides():
    """Mirror the per-file OPT_FLAGS overrides from the Makefile."""
    exact, prefixes = {}, []
    for line in open("Makefile"):
        m = re.match(r"\$\(BUILD_DIR\)/\$\(SRC_DIR\)/(\S+): OPT_FLAGS := (.+)", line.strip())
        if not m:
            continue
        target, flags = m.groups()
        if target.endswith("%.o"):
            prefixes.append((target[:-3], flags))
        else:
            exact[re.sub(r"\.(c\.)?o$", "", target)] = flags
    return exact, prefixes


def flags_for(rel, exact, prefixes):
    stem = rel[:-2]
    if stem in exact:
        return exact[stem]
    for p, f in prefixes:
        if rel.startswith(p):
            return f
    return "-O2 -g3"


def build(rel, exact, prefixes):
    src = os.path.join(SRC, rel)
    stripped = os.path.join(OUT, rel)
    obj = stripped[:-2] + ".o"
    os.makedirs(os.path.dirname(stripped), exist_ok=True)
    text = open(src, encoding="latin-1").read()
    text = re.sub(r'^\s*#pragma\s+GLOBAL_ASM\(.*\)\s*$', "", text, flags=re.M)
    open(stripped, "w", encoding="latin-1").write(text)
    cmd = f"{CC} -c -32 {CFLAGS} {flags_for(rel, exact, prefixes)} {MIPSBIT} -o {obj} {stripped}"
    r = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return rel, r.returncode, r.stderr.strip().splitlines()[-3:]


def main():
    exact, prefixes = opt_overrides()
    files = [os.path.relpath(os.path.join(d, f), SRC)
             for d, _, fs in os.walk(SRC) for f in fs if f.endswith(".c")]
    with ThreadPoolExecutor(os.cpu_count()) as ex:
        results = list(ex.map(lambda r: build(r, exact, prefixes), sorted(files)))
    failed = [r for r in results if r[1]]
    for rel, _, err in failed:
        print("FAIL", rel, *err, sep="\n  ")
    print(f"{len(results) - len(failed)}/{len(results)} compiled")


if __name__ == "__main__":
    sys.exit(main())
