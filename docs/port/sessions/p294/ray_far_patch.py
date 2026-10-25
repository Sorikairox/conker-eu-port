#!/usr/bin/env python3
"""P294: patch tools/port/difftest/nmasm_walls.py: ray scenes whose only hit lies in a later leaf (ray_far)."""
import sys
p = sys.argv[1]
s = open(p).read()

old = "def ray_grid_tree(rng, m, vs, pos):"
new = "def ray_grid_tree(rng, m, vs, pos, geo=None):"
assert old in s; s = s.replace(old, new)
old = """    g = rng.choice([2, 3, 4, 6]); h = rng.choice([60, 150, 300, 600])
    cx0, cz0 = pos[0] + rng.randint(-h, h), pos[2] + rng.randint(-h, h)
"""
new = """    g = rng.choice([2, 3, 4, 6]); h = rng.choice([60, 150, 300, 600])
    cx0, cz0 = pos[0] + rng.randint(-h, h), pos[2] + rng.randint(-h, h)
    if geo: g, h, cx0, cz0 = geo   # P294: ray_far's grid
"""
assert old in s; s = s.replace(old, new)

old = "def ray_aim(rng, p0, vs):"
new = '''def ray_far(rng, m, pos, nt, vs):
    """P294: one wall triangle (index 0) whose only hit lies in a later leaf of a g x g grid tree; the other
    triangles are lifted 5000 units out of the way. The ray leaves the origin's leaf toward -z / +z (often exactly
    along z: dx 0.0 / -0.0, the dx == 0 exit) / -x / +x / diagonally (-x, -z); maxDist sometimes just past the
    first exit point (1.5 .. 9.5 units before it: the +10 of the exit point decides). Returns (p0, d, maxDist)."""
    g = rng.choice([3, 4, 5]); h = rng.choice([40, 60, 150, 300])
    cx0, cz0 = pos[0], pos[2]
    cell = lambda i: -g * h + h + 2 * h * i
    ax = rng.choice(['-z', '-z', '-z', '+z', '+z', '-x', '-x', '+x', 'd'])
    i0, j0 = rng.randrange(g), rng.randrange(g)
    if ax == '-z': j0 = rng.randrange(1, g)
    elif ax == '+z': j0 = rng.randrange(0, g - 1)
    elif ax == '-x': i0 = rng.randrange(1, g)
    elif ax == '+x': i0 = rng.randrange(0, g - 1)
    else: i0, j0 = rng.randrange(1, g), rng.randrange(1, g)
    ox = cx0 + cell(i0) + rng.uniform(-0.6, 0.6) * h; oz = cz0 + cell(j0) + rng.uniform(-0.6, 0.6) * h
    if rng.random() < 0.4: ox, oz = float(round(ox)), float(round(oz))
    oy = float(pos[1] + rng.randint(-20, 20))
    s = rng.choice([1.0, 64.0, 0.01, 300.0])
    w = rng.choice([10, 30, h * 0.5])
    small = rng.choice([0.0, 0.0, -0.0, rng.uniform(-0.01, 0.01)])
    md = 0.0
    if ax in ('-z', '+z', '-x', '+x'):
        sg = -1 if ax[0] == '-' else 1
        along = 2 if ax[1] == 'z' else 0
        i = j0 if along == 2 else i0; o = oz if along == 2 else ox; c0 = cz0 if along == 2 else cx0
        k = 1 if rng.random() < 0.5 else rng.randrange(1, (i + 1) if sg < 0 else (g - i))
        t = c0 + cell(i + sg * k) + rng.uniform(-0.7, 0.7) * h      # the wall's plane, inside a leaf k ahead
        exitd = abs(c0 + cell(i) + sg * h - o)
        md = rng.choice([0.0, 0.0, exitd + rng.uniform(1.5, 9.5), exitd + rng.uniform(10.5, 40.0)])
        if along == 2:
            d = [small * s, 0.0, sg * s]
            v = [[ox - w, oy - 30, t], [ox + w, oy - 30, t], [ox, oy + 60, t]]
        else:
            d = [sg * s, 0.0, small * s]
            v = [[t, oy - 30, oz - w], [t, oy - 30, oz + w], [t, oy + 60, oz]]
    else:
        r = rng.uniform(0.5, 2.0); n = math.sqrt(1 + r * r); u = [-1 / n, -r / n]
        te = min((ox - (cx0 + cell(i0) - h)) / -u[0], (oz - (cz0 + cell(j0) - h)) / -u[1])
        dd = te + rng.uniform(5, 2 * h)
        q = [ox + dd * u[0], oz + dd * u[1]]; pp = [-u[1], u[0]]
        d = [u[0] * s, 0.0, u[1] * s]
        v = [[q[0] - w * pp[0], oy - 30, q[1] - w * pp[1]], [q[0] + w * pp[0], oy - 30, q[1] + w * pp[1]],
             [q[0], oy + 60, q[1]]]
    v = [[int(round(a)) for a in q] for q in v]
    for kk in range(3): W(m, VP + 8 * kk, '3h', *v[kk]); W(m, VOFS + 4 * kk, 'I', VP + 8 * kk)
    W(m, BND, '4h', min(q[0] for q in v), min(q[2] for q in v), max(q[0] for q in v), max(q[2] for q in v))
    W(m, YB, '2h', min(q[1] for q in v), max(q[1] for q in v))
    out = [v]
    for t2 in range(1, nt):                                     # the others: 5000 up
        vv = [[q[0], min(32760, q[1] + 5000), q[2]] for q in vs[t2]]
        for kk in range(3): W(m, VP + 0x18 * t2 + 8 * kk, '3h', *vv[kk])
        W(m, YB + 4 * t2, '2h', min(q[1] for q in vv), max(q[1] for q in vv))
        out.append(vv)
    ray_grid_tree(rng, m, out, pos, geo=(g, h, cx0, cz0))
    return out, ([ox, oy, oz], d, md)

def ray_aim(rng, p0, vs):'''
assert old in s; s = s.replace(old, new)

old = """def ray_call(ref, cand, m, rng, pos, vs=None):
    p0 = [pos[0] + rng.uniform(-50, 50), pos[1] + rng.uniform(-50, 150), pos[2] + rng.uniform(-50, 50)]
    if rng.random() < 0.3:
        p0 = [float(round(q)) for q in p0]   # integer origins: exact hits on integer vertices / edges
    if vs and rng.random() < 0.75: d = ray_aim(rng, p0, vs)
    else: d = [rng.choice([0.0, rng.uniform(-400, 400)]) for _ in range(3)]
    if rng.random() < 0.05: d = [0.0, 0.0, 0.0]
"""
new = """def ray_call(ref, cand, m, rng, pos, vs=None, far=None):
    p0 = [pos[0] + rng.uniform(-50, 50), pos[1] + rng.uniform(-50, 150), pos[2] + rng.uniform(-50, 50)]
    if rng.random() < 0.3:
        p0 = [float(round(q)) for q in p0]   # integer origins: exact hits on integer vertices / edges
    if vs and rng.random() < 0.75: d = ray_aim(rng, p0, vs)
    else: d = [rng.choice([0.0, rng.uniform(-400, 400)]) for _ in range(3)]
    if rng.random() < 0.05: d = [0.0, 0.0, 0.0]
    md = rng.choice([0.0, 0.0, 50.0, 300.0])
    if far: p0, d, md = far                  # P294: ray_far's ray
"""
assert old in s; s = s.replace(old, new)
old = "             b32(rng.choice([0.0, 0.0, 50.0, 300.0])))"
new = "             b32(md))"
assert old in s; s = s.replace(old, new)

old = """            if rng.random() < 0.5: ray_grid_tree(rng, m, vs, pos)
            W(m, DBE08, 'I', R(m, T278, 'I')[0])
            nobj, ovs = ray_objects(rng, m, nt, pos); W(m, DC320, 'i', nobj); vs = vs + ovs"""
new = """            far = None
            if rng.random() < 0.35: vs, far = ray_far(rng, m, pos, nt, vs); hist['ray far'] = hist.get('ray far', 0) + 1
            elif rng.random() < 0.5: ray_grid_tree(rng, m, vs, pos)
            W(m, DBE08, 'I', R(m, T278, 'I')[0])
            nobj, ovs = ray_objects(rng, m, nt, pos)
            if far and rng.random() < 0.7: nobj, ovs = 0, []
            W(m, DC320, 'i', nobj); vs = vs + ovs"""
assert old in s; s = s.replace(old, new)
old = "                ok, v0, info, m1 = ray_call(ref, cand, m, rng, pos, vs)"
new = "                ok, v0, info, m1 = ray_call(ref, cand, m, rng, pos, vs, far)"
assert old in s; s = s.replace(old, new)
old = "        key = '%s:%s' % (kind, v0 if v0 in (0, 1) else 'other')\n        if kind == 'ac8c4'"
new = "        key = '%s:%s' % (kind, v0 if v0 in (0, 1) else 'other')\n        if kind == 'ray' and far: key += ' far'\n        if kind == 'ac8c4'"
assert old in s; s = s.replace(old, new)
open(p, 'w').write(s)
print('patched')
