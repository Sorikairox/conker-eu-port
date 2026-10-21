#!/usr/bin/env python3
"""Compile every conker/src_eu/**/*.c for wasm32 (emcc/clang) and write a failure census.

Runs inside the conker-emsdk container from the repo root (port/web/run.sh census, or make -C port objs).

Two passes per TU:
  strict  clang's defaults for -std=gnu89 (what an unmodified tree hits)
  build   the port flags (PORT_RELAX below) that downgrade IDO-tolerated errors to warnings;
          its object goes to port/build/obj/ and is linked into the game build.
Outputs (port/build/census/):
  summary.txt   per-category counts of errors (strict + build) and of the relaxed warnings
  files.tsv     file, strict_errors, build_errors, build_ok
  diag/<file>.strict.txt, diag/<file>.build.txt   raw diagnostics
"""
import os, re, subprocess, sys, collections, concurrent.futures as cf
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import srcfix

ROOT = os.getcwd()
SRC = 'conker/src_eu'
OUT = 'port/build'
OBJ = f'{OUT}/obj'
CEN = f'{OUT}/census'

INC = ['-Iconker', '-Iconker/include', '-Iconker/include/2.0L', '-Iconker/include/2.0L/PR',
       '-Iconker/include/libc', '-Iconker/src/libultra/os', '-Iconker/src/libultra/audio',
       '-Iconker/src/libultra/io']
DEFS = ['-DNON_MATCHING', '-DPORT', '-D_LANGUAGE_C', '-D_FINALROM', '-DF3DEX_GBI_2',
        '-D_MIPS_SZLONG=32', '-D_MIPS_SZINT=32']
BASE = ['emcc', '-c', '-O1', '-g0', '-std=gnu89', '-nostdinc', '-fno-builtin', '-fno-strict-aliasing',
        '-fwrapv', '-fsigned-char',
        '-include', 'port/ultra/port_prefix.h'] + DEFS + INC
# IDO accepts these; clang >= 15/16 makes them errors by default.
PORT_RELAX = ['-Wno-error=int-conversion', '-Wno-error=incompatible-pointer-types',
              '-Wno-error=incompatible-function-pointer-types', '-Wno-error=implicit-int',
              '-Wno-error=implicit-function-declaration', '-Wno-error=return-type',
              '-Wno-error=return-mismatch', '-Wno-error=int-to-pointer-cast',
              '-Wno-unknown-pragmas', '-Wno-error=pointer-sign']
# warnings counted in the census (the ones that matter for a correct port)
TRACK = ['int-conversion', 'incompatible-pointer-types', 'incompatible-function-pointer-types',
         'implicit-int', 'implicit-function-declaration', 'return-type', 'return-mismatch',
         'int-to-pointer-cast', 'pointer-to-int-cast', 'unknown-pragmas', 'deprecated-non-prototype',
         'shift-count-overflow', 'array-bounds', 'tautological-constant-out-of-range-compare',
         'constant-conversion', 'incompatible-library-redeclaration', 'main-return-type',
         'strict-prototypes', 'knr-promoted-parameter']

DIAG = re.compile(r'^(?P<file>[^:\s]+):(?P<line>\d+):\d+: (?P<kind>error|warning): (?P<msg>.*?)(?: \[(?P<flag>-W[^\]]+)\])?$')


def norm(msg):
    msg = re.sub(r"'[^']*'", "'X'", msg)
    msg = re.sub(r'\d+', 'N', msg)
    msg = msg.replace(" (aka 'X')", '')
    msg = re.sub(r'; (remove|take|dereference).*$', '', msg)
    return msg[:110]


def compile_one(path):
    rel = os.path.relpath(path, SRC)
    tag = rel.replace('/', '__')
    obj = f'{OBJ}/{tag}.o'
    res = {}
    for mode, extra, out in (('strict', [], '/dev/null'), ('build', PORT_RELAX, obj)):
        p = subprocess.run(BASE + extra + [path, '-o', out], capture_output=True, text=True)
        res[mode] = (p.returncode, p.stderr)
        with open(f'{CEN}/diag/{tag}.{mode}.txt', 'w') as f:
            f.write(p.stderr)
    # P23: retry a failing build with a diagnostic-driven patched copy (port/tools/srcfix.py)
    fixed = srcfix.path_for(rel)
    if os.path.exists(fixed):
        os.remove(fixed)
    if res['build'][0]:
        fx = srcfix.fix(path, rel, res['build'][1])
        if fx:
            p = subprocess.run(BASE + PORT_RELAX + ['-iquote', os.path.dirname(path), fx, '-o', obj],
                               capture_output=True, text=True)
            with open(f'{CEN}/diag/{tag}.srcfix.txt', 'w') as f:
                f.write(p.stderr)
            if p.returncode == 0:
                res['srcfix'] = True
                res['build'] = (0, res['build'][1])
            else:
                os.remove(fx)
    return rel, res


def main():
    os.makedirs(OBJ, exist_ok=True)
    os.makedirs(f'{CEN}/diag', exist_ok=True)
    files = []
    for d, _, fs in os.walk(SRC):
        files += [os.path.join(d, f) for f in fs if f.endswith('.c')]
    files.sort()
    only = sys.argv[1:]
    if only:
        files = [f for f in files if any(o in f for o in only)]
    errs = {m: collections.Counter() for m in ('strict', 'build')}
    errfiles = {m: collections.defaultdict(set) for m in ('strict', 'build')}
    warns = collections.Counter(); warnfiles = collections.defaultdict(set)
    rows = []; fixedl = []
    with cf.ThreadPoolExecutor(os.cpu_count() or 4) as ex:
        for rel, res in ex.map(compile_one, files):
            row = [rel]
            for mode in ('strict', 'build'):
                rc, err = res[mode]
                n = 0
                for line in err.splitlines():
                    m = DIAG.match(line)
                    if not m:
                        continue
                    flag = (m['flag'] or '').split(',')[0].lstrip('-W')
                    if m['kind'] == 'error':
                        n += 1
                        key = (flag + ': ' if flag else '') + norm(m['msg'])
                        errs[mode][key] += 1; errfiles[mode][key].add(rel)
                    elif mode == 'build' and flag in TRACK:
                        warns[flag] += 1; warnfiles[flag].add(rel)
                row.append(n)
            row.append('ok' if res['build'][0] == 0 else 'FAIL')
            if res.get('srcfix'):
                fixedl.append(rel)
            rows.append(row)
    with open(f'{CEN}/files.tsv', 'w') as f:
        f.write('file\tstrict_errors\tbuild_errors\tbuild\n')
        for r in rows:
            f.write('\t'.join(map(str, r)) + '\n')
    nfail = {m: sum(1 for r in rows if r[1 if m == 'strict' else 2]) for m in ('strict', 'build')}
    with open(f'{CEN}/summary.txt', 'w') as f:
        f.write(f'TUs: {len(rows)}\n')
        f.write(f"strict (clang defaults, -std=gnu89): {nfail['strict']} TUs with errors, "
                f"{sum(errs['strict'].values())} errors\n")
        f.write(f"build  (PORT_RELAX flags):          {nfail['build']} TUs with errors, "
                f"{sum(errs['build'].values())} errors\n")
        f.write(f"srcfix (P23, patched copy builds):  {len(fixedl)} TUs: {' '.join(sorted(fixedl))}\n\n")
        for mode in ('strict', 'build'):
            f.write(f'== {mode} errors by category (count / files) ==\n')
            for k, v in errs[mode].most_common(60):
                f.write(f'{v:6d} {len(errfiles[mode][k]):4d}  {k}\n')
            f.write('\n')
        f.write('== tracked warnings in build mode (count / files) ==\n')
        for k, v in warns.most_common():
            f.write(f'{v:6d} {len(warnfiles[k]):4d}  -W{k}\n')
    print(open(f'{CEN}/summary.txt').read())


if __name__ == '__main__':
    main()
