#!/usr/bin/env python3
"""P294: nmasm_walls.py unit mode: helper ac200 (projects_inside, f4 side output)."""
import sys
p = sys.argv[1]
s = open(p).read()
old = "    'aaf00': (0x150AAF00, list(range(0, 3)) + list(range(23, 32)), {}, ['v0'], 'triangle vs box'),\n"
new = old + "    'ac200': (0x150AC200, [19, 20, 21, 22, 26, 27, 28], {}, [8, 'f4'], 'projected point inside (P294)'),\n"
assert old in s; s = s.replace(old, new)
old = "        frame = [0] * (0x268 // 4)\n"
new = old + """        if nm == 'ac200':                                       # P294: triangle at sp+0x20C, often the point on
            tri = [unit_val(rng, 23 + k, pooled) for k in range(9)]   # it and the triangle's own plane
            for k in range(9): frame[0x20C // 4 + k] = b32(tri[k])
            v = [tri[0:3], tri[3:6], tri[6:9]]
            if rng.random() < 0.6:
                w = rng.sample(rng.choice([(1, 0, 0), (0.5, 0.5, 0), (0.25, 0.25, 0.5), (0.6, 0.3, 0.1), (1.2, -0.1, -0.1)]), 3)
                for d in range(3): fv[26 + d] = b32(sum(w[i] * v[i][d] for i in range(3)) + rng.choice([0.0, 0.0, 3.0, -0.5]))
            if rng.random() < 0.5:
                a = [v[1][d] - v[0][d] for d in range(3)]; b = [v[2][d] - v[0][d] for d in range(3)]
                n = [a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]]
                if any(n):
                    for d in range(3): fv[19 + d] = b32(n[d])
                    fv[22] = b32(sum(n[d] * v[0][d] for d in range(3)))
"""
assert old in s; s = s.replace(old, new)
open(p, 'w').write(s)
print('patched')
