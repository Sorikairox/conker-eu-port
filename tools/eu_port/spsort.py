#!/usr/bin/env python3
"""Sort runs of stack-struct field stores (`sp.uXX = ...;`) into struct field order (s65).

m2c emits the stores of a spawner/stack-struct initialiser in the scheduled (ref asm) order;
the source wrote them in field order, and IDO's scheduler only reproduces the ref order from
that (func_150F0FA4: SIZE/DIFF92 -> OK by sorting alone).

usage: spsort.py in.c out.c [--const]
  Every maximal run of consecutive lines `    sp.u<hex>[...] = <expr>;` is sorted by the hex
  offset (stable). --const only moves lines whose right-hand side has no call `(`-after-name.
"""
import re, sys

PAT = re.compile(r'^\s*sp\.u([0-9A-Fa-f]+)\b[^=]*=[^=].*;\s*$')
CALL = re.compile(r'[A-Za-z_]\w*\s*\(')


def movable(line, const_only):
    if not PAT.match(line):
        return False
    if const_only:
        rhs = line.split('=', 1)[1]
        return not CALL.search(rhs.replace('(f32)', '').replace('(s32)', ''))
    return True


def main():
    a = sys.argv[1:]
    const_only = '--const' in a
    a = [x for x in a if x != '--const']
    src, dst = a
    lines = open(src).read().split('\n')
    out, run = [], []

    def flush():
        run.sort(key=lambda l: int(PAT.match(l).group(1), 16))
        out.extend(run)
        run.clear()

    for l in lines:
        if movable(l, const_only):
            run.append(l)
        else:
            flush()
            out.append(l)
    flush()
    open(dst, 'w').write('\n'.join(out))


if __name__ == '__main__':
    main()
