#!/usr/bin/env python3
"""P102: mutants for func_15097E9C: 'cmd|sed' lines -> 'sed % setups of cmd' (mut.sh format)."""
import sys
for l in open(sys.argv[1]):
    l = l.rstrip('\n')
    if not l or l.startswith('#'): continue
    c, e = l.split('|', 1)
    names = ' '.join('e9c_%02X_%d' % (int(x, 16), k) for x in c.split(',') for k in range(int(sys.argv[2]) if len(sys.argv) > 2 else 4))
    print('%s %% %s' % (e, names))
