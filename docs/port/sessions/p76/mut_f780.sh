#!/bin/bash
# P76: func_1502F780 mutants on sf780.txt (mutfast.sh)
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p76
$D/mutfast.sh func_1502F780 port_work/p76/f780.c $D/sf780.txt \
 's/tris\[tri \* 3 + k\]/tris[tri * 3 + k + 1]/' \
 's/range\[1\] \* 16/range[1] * 8/' \
 's/>= range\[0\]/> range[0]/' \
 's/joint\[k\] = range\[2\];/joint[k] = range[1];/' \
 's/} while (found != 7);/} while (found != 3);/' \
 's/obj->unk1D8 == NULL || //' \
 's/if (g == 1)/if (g == 2)/' \
 's/u = -100.0f;/u = 0.5f;/' \
 's/u < 0.0f || u > 1.0f/u < 0.0f/' \
 's/(d\[2\] - u \* e1\[0\]\[2\])/(d[2] - u * e1[0][1])/' \
 's/v < 0.0f || v > 1.0f/v > 1.0f/' \
 's/    d\[1\] = e2\[0\]\[1\] \* v + u \* e1\[0\]\[1\];//' \
 's/w\[k\] = e2\[1\]\[k\]/w[k] = e2[0][k]/' \
 's/- d\[2\]) - p\[0\]\[0\]\[2\]/- d[2]) - p[1][0][2]/' \
 's/den = e1\[0\]\[0\] \* e2\[0\]\[2\] - e2/den = e1[0][0] * e2[0][2] + e2/' \
 's/if (i == D_800C6318\[kind\])/if (i == D_800C6318[kind] + 1)/' \
 's/s\[0\], s\[1\], s\[2\]/s[0], s[2], s[1]/' \
 's/v = -100.0f;/v = 0.5f;/'
