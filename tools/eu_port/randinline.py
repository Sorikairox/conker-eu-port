#!/usr/bin/env python3
"""s108: rewrite an m2c draft of a rand spawner into the s106 recipe-1 form.

usage: randinline.py in.c outprefix [--all]

1. single-use temps assigned a bare rand call (`temp = random_int();` /
   `random_float()`) are inlined at their use (IDO evaluates call arguments
   left to right, so the rand calls end up in the ref's order);
2. `(rand() % (u32) G) + B` -> `(B + (rand() % (u32) G))` and
   `(random_float() * E) + B` -> `(B + E * random_float())` (ref operand order).

Writes <outprefix>_<v>.c for v in: i (inline only), is (inline + int/float add
swap), isf (inline + swap, float keeps rand*E), s (swap, no inline).
"""
import re, sys

RI, RF = 'random_int', 'random_float'


def group_end(s, i):
    """s[i] == '(' -> index after the matching ')'."""
    d = 0
    for j in range(i, len(s)):
        if s[j] == '(':
            d += 1
        elif s[j] == ')':
            d -= 1
            if d == 0:
                return j + 1
    return -1


TOK = re.compile(r'[A-Za-z_][\w]*(?:(?:->|\.)[A-Za-z_]\w*|\[[^\]]*\])*|0x[0-9A-Fa-f]+|\d+(?:\.\d+)?f?')


def operand_end(s, i):
    if s[i] == '(':
        return group_end(s, i)
    m = TOK.match(s, i)
    return m.end() if m else -1


def strip(g):
    g = g.strip()
    if g.startswith('(') and group_end(g, 0) == len(g):
        return g[1:-1].strip()
    return g


def swap_once(s, fmul):
    """one pass; returns (new, changed)."""
    i = 0
    while True:
        i = s.find('(', i)
        if i < 0:
            return s, False
        e = group_end(s, i)
        if e < 0:
            return s, False
        inner = s[i + 1:e - 1].strip()
        m_int = re.match(r'^(\(u32\)\s*)?' + RI + r'\(\)\s*%', inner)
        m_flt = inner.startswith(RF + '() * ')
        if (m_int or m_flt) and s.startswith(' + ', e):
            b0 = e + 3
            b1 = operand_end(s, b0)
            if b1 > 0:
                B = s[b0:b1]
                if m_flt and fmul:
                    E = inner[len(RF + '() * '):].strip()
                    new = '(%s + %s * %s())' % (B, E, RF)
                else:
                    new = '(%s + (%s))' % (B, inner)
                return s[:i] + new + s[b1:], True
        i += 1


def swap_all(s, fmul):
    out, n = [], 0
    for line in s.split('\n'):
        for _ in range(50):
            line, ch = swap_once(line, fmul)
            if not ch:
                break
        out.append(line)
    return '\n'.join(out)


def inline(s):
    lines = s.split('\n')
    changed = True
    while changed:
        changed = False
        for k, l in enumerate(lines):
            m = re.match(r'^\s*(\w+) = (' + RI + '|' + RF + r')\(\);\s*$', l)
            if not m:
                continue
            v, fn = m.groups()
            pat = re.compile(r'\b' + re.escape(v) + r'\b')
            uses = [(j, x) for j, x in enumerate(lines) if j != k and pat.search(x)
                    and not re.match(r'^\s*[\w ]+\*?\s*' + re.escape(v) + r';\s*$', x)]
            decl = [j for j, x in enumerate(lines) if re.match(r'^\s*[\w ]+\*?\s*' + re.escape(v) + r';\s*$', x)]
            if len(uses) != 1 or len(pat.findall(uses[0][1])) != 1 or uses[0][0] < k:
                continue
            j = uses[0][0]
            lines[j] = pat.sub(fn + '()', lines[j])
            for d in sorted(decl + [k], reverse=True):
                del lines[d]
            changed = True
            break
    return '\n'.join(lines)


def main():
    src = open(sys.argv[1]).read()
    pre = sys.argv[2]
    vs = {
        'i': inline(src),
        'is': swap_all(inline(src), True),
        'isf': swap_all(inline(src), False),
        's': swap_all(src, True),
    }
    for k, v in vs.items():
        open('%s_%s.c' % (pre, k), 'w').write(v)
    print(' '.join('%s_%s.c' % (pre, k) for k in vs))


if __name__ == '__main__':
    main()
