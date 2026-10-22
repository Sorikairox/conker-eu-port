#!/usr/bin/env python3
"""P56: mutants of the generated wall engine / ray cast C (src_eu/nm_asm/D5E90_walls.inc / D5E90_ray.inc): apply one,
rebuild NON_MATCHING, run nmasm_walls.py, restore. Run on the host from the worktree root (uses docker exec)."""
import os, re, subprocess, sys
CT = os.environ.get('CONKERDEV', 'conkerdev-portb')
D = 'conker/src_eu/nm_asm/'
MUT = [  # (file, exact old text, new text, nth occurrence (0-based), harness args)
    ('D5E90_walls.inc', 't0 = 0 + 100;', 't0 = 0 + 99;', 0, '200 21 --only ab6d0'),               # visited cap
    ('D5E90_walls.inc', 'at = 0x42820000;', 'at = 0x42840000;', 0, '300 21 --only ac8c4'),        # step window 65
    ('D5E90_walls.inc', 't3 = t0 - t2;', 't3 = t0 - t2 - 1;', 0, '200 21 --only ab6d0'),           # node radius
    ('D5E90_walls.inc', 'cc = !(F[21].f >= F[18].f);', 'cc = F[21].f < F[18].f;', 0, '200 21 --only ab6d0'),
    ('D5E90_walls.inc', 'at = 0x3F000000;', 'at = 0x3F010000;', 0, '200 21 --only ab6d0'),   # centre 0.5
    ('D5E90_walls.inc', 'v0 = v0 | 4;', 'v0 = v0 | 0;', 0, '200 21 --only ab6d0'),                # outcode bit
    ('D5E90_ray.inc', 'at = 0x47800000;', 'at = 0x47000000;', 0, '200 21 --only ray'),
    ('D5E90_ray.inc', 's1 = 0 + 1;', 's1 = 0 + 0;', 0, '200 21 --only ray'),
    ('D5E90_ray.inc', 'at = 0 + 3;', 'at = 0 + 2;', 0, '200 21 --only ray'),                     # edge-sign count
    ('D5E90_ray.inc', 'F[28].f = F[1].f * F[1].f;', 'F[28].f = F[1].f;', 0, '200 21 --only ray'),    # default range
]
def sh(c): return subprocess.run(c, shell=True, capture_output=True, text=True).stdout
def build(): sh('docker exec -w /conker/conker %s make VERSION=eu NON_MATCHING=1 -j8' % CT)
for f, old, new, nth, args in (MUT[int(sys.argv[1]):] if len(sys.argv) > 1 else MUT):
    p = D + f; src = open(p).read()
    idx = -1
    for _ in range(nth + 1):
        idx = src.find(old, idx + 1)
        if idx < 0: break
    if idx < 0: print('mutant did not apply:', f, old, nth); continue
    open(p, 'w').write(src[:idx] + new + src[idx + len(old):]); os.utime(D + 'D5E90.c')
    build()
    out = sh('docker exec -w /conker/conker %s sh -c "python3 ../tools/port/difftest/nmasm_walls.py %s 2>&1 | tail -1"' % (CT, args))
    print('mutant %s [%s -> %s #%d]: %s' % (f, old, new, nth, out.strip()[-200:]), flush=True)
    open(p, 'w').write(src); os.utime(D + 'D5E90.c')
build()
