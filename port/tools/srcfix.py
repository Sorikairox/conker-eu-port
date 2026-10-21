"""P23: build-time source fixes for game TUs that IDO accepts and clang rejects as hard errors.

The game .c files are never edited: census.py calls fix() when a TU fails its build pass, and a
patched copy goes to port/build/srcfix/<rel path>. census.py retries with it, and vbe_build.py
compiles that copy (with -iquote <original dir>) instead of the original. Fixes are driven by the
clang diagnostics, so only the reported lines change:

  assignment to cast is illegal      `(T)x = v;`  ->  `*(T *)&x = v;`
      m2c writes this for an integer store into a float / pointer slot (IDO's lvalue cast stores the
      bits of the cast type into the variable), so a reinterpreting store keeps the asm's semantics.
  too many / too few arguments       `f(...)`  ->  `((__typeof__(f(0, ..)) (*)())f)(...)`
      a K&R-defined function called with another arity in the same TU (IDO passes the registers
      through; clang knows the definition's parameter count). The call goes through an unprototyped
      pointer, which the icall/sigs layer already handles like any other mismatching call.
"""
import os, re

OUT = 'port/build/srcfix'
DIAG = re.compile(r'^(?P<file>[^:\s]+):(?P<line>\d+):(?P<col>\d+): error: (?P<msg>.*)$')
LCAST = re.compile(r'\(\s*([A-Za-z_][\w ]*?\s*\**)\s*\)\s*([A-Za-z_][\w.\[\]>-]*)\s*=(?!=)')
CALL = re.compile(r'([A-Za-z_]\w*)\s*\(')


def path_for(rel):
    return os.path.join(OUT, rel)


def fix(path, rel, stderr):
    """Return the patched path, or None when an error is not one of the fixable kinds."""
    lines = open(path, errors='replace').read().split('\n')
    todo = []
    for l in stderr.splitlines():
        m = DIAG.match(l)
        if not m or os.path.normpath(m['file']) != os.path.normpath(path):
            continue
        if 'assignment to cast is illegal' in m['msg']:
            todo.append(('cast', int(m['line']), int(m['col'])))
        elif re.match(r'too (many|few) arguments to function call, expected (\d+)', m['msg']):
            todo.append(('arity', int(m['line']), int(m['col']),
                         int(re.search(r'expected (\d+)', m['msg'])[1])))
        else:
            return None
    if not todo:
        return None
    for kind, ln, col, *nexp in todo:
        s = lines[ln - 1]
        if kind == 'cast':
            new, n = LCAST.subn(lambda m: f'*({m[1]} *)&{m[2]} =', s, count=1)
        else:
            # the column points at the offending argument; the callee is the last call opened before it
            head = s[:col - 1]
            calls = [m for m in CALL.finditer(head) if m[1] not in ('if', 'while', 'for', 'return', 'sizeof')]
            if not calls:
                return None
            m = calls[-1]
            f = m[1]
            zeros = ', '.join(['0'] * nexp[0])  # typeof operand is unevaluated; it only names the return type
            new = s[:m.start()] + f'((__typeof__({f}({zeros})) (*)()){f})(' + s[m.end():]
            n = 1
        if not n:
            return None
        lines[ln - 1] = new
    out = path_for(rel)
    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, 'w') as fh:
        fh.write(f'/* P23 srcfix copy of {path}: {len(todo)} line(s) patched (port/tools/srcfix.py) */\n')
        fh.write('#line 1 "' + path + '"\n')
        fh.write('\n'.join(lines))
    return out
