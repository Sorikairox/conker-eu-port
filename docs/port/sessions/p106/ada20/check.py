#!/usr/bin/env python3
# P106 (P95 ada68/check.py pattern): instruction-level models of the EU asm of the MIPS III / harness-untestable event
# VM natives vs the NM C (src_eu text, compiled for the host with gcc), over random + edge states:
#   func_150ADA20 (ld/sd LFSR step), func_150AE674 (random below n: divu after jal with lw in the delay slot),
#   func_150AE6A0 (dmult 16.16), func_150AE6BC (ddiv 16.16), func_150AE6D4 / func_150AE714 (timers).
# usage: check.py SRC_DIR (conker/src_eu)
import random, subprocess, sys, os, re
M = (1 << 64) - 1
def sx32(v): v &= 0xFFFFFFFF; return v - (1 << 32) if v >> 31 else v
def s64(v): v &= M; return v - (1 << 64) if v >> 63 else v

def m_ada20(x):
    a2 = ((x << 63) & M) >> 31             # dsll32 a2,a0,31 ; dsrl a2,a2,31
    a1 = ((x << 31) & M) >> 32             # dsll a1,a0,31 ; dsrl32 a1,a1,0
    a2 |= a1
    a0 = ((x << 44) & M) >> 32             # dsll32 a0,a0,12 ; dsrl32 a0,a0,0
    a2 ^= a0
    a0 = ((a2 >> 20) & 0xFFF) ^ a2         # dsrl ; andi ; xor
    return a0, sx32(a0)                    # sd a0 ; dsll32 / dsra32 v0
def m_674(rand, n):
    n &= 0xFFFFFFFF; r = rand & 0xFFFFFFFF
    return sx32(r if n == 0 else r % n)    # divu: VR4300 x % 0 = x (hi = dividend)
def m_6a0(a, b):
    p = (sx32(a) * sx32(b)) & M            # dmult of sign-extended words, mflo
    return sx32(p >> 16)                   # dsrlv 16 ; the VM stores the low word
def m_6bc(a, b):
    n = s64(sx32(a) << 16); d = sx32(b)    # dsll 16 ; ddiv
    if d == 0: return 1 if n < 0 else -1   # VR4300 ddiv by 0: lo = n < 0 ? 1 : -1
    q = abs(n) // abs(d); q = q if (n < 0) == (d < 0) else -q
    return sx32(q)
def m_6d4(t, d):
    t = sx32(t); y = sx32(t + d)           # add (wraps; the asm would trap on overflow)
    if t < 0 and y >= 0: return 0
    if t == 0: return 1
    return y
def m_714(t, d):
    t = sx32(t); y = sx32(t - d)
    if t >= 2 and y < 2: return 1
    if t == 1: return 0
    return y

src = open(os.path.join(sys.argv[1], 'game_DAE50.c')).read() + open(os.path.join(sys.argv[1], 'game_eu_DB7E0.c')).read()
def body(name):
    m = re.search(r'^s32 %s\(.*?\n\}\n' % name, src, re.M | re.S)
    return m.group(0)
c = '''#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long u64; typedef long long s64; typedef int s32; typedef unsigned int u32; typedef unsigned char u8;
s64 D_80088950; u8 D_800BE9A0; static u32 RAND;
s32 func_150ADA20_stub(void) { return RAND; }
%s
#define func_150ADA20 func_150ADA20_stub
%s
%s
%s
%s
%s
#undef func_150ADA20
int main(int c, char **v) {
  for (int i = 1; i + 3 < c; i += 4) {
    u64 x = strtoull(v[i], 0, 16); s32 a = (s32) strtoul(v[i + 1], 0, 16), b = (s32) strtoul(v[i + 2], 0, 16);
    s32 args[2] = {a, b}; s32 t[1] = {a}; D_800BE9A0 = (u8) strtoul(v[i + 3], 0, 16); RAND = (u32) b;
    D_80088950 = (s64) x; s32 r = func_150ADA20();
    printf("%%016llx %%08x %%08x %%08x %%08x %%08x %%08x\\n", (u64) D_80088950, (u32) r, (u32) func_150AE674(t),
           (u32) func_150AE6A0(args), (u32) func_150AE6BC(args), (u32) func_150AE6D4(t), (u32) func_150AE714(t));
  }
}
''' % (body('func_150ADA20'), body('func_150AE674'), body('func_150AE6A0'), body('func_150AE6BC'), body('func_150AE6D4'),
       body('func_150AE714'))
open('/tmp/p106chk.c', 'w').write(c)
subprocess.check_call(['gcc', '-O1', '-fwrapv', '-o', '/tmp/p106chk', '/tmp/p106chk.c'])
rng = random.Random(1)
E32 = [0, 1, 2, 3, 5, 0x10000, 0x7FFFFFFF, 0x80000000, 0x80000001, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFF0000, 0x8000, 0x12345678]
cases = []
for a in E32:
    for b in E32:
        cases.append((rng.getrandbits(64), a, b, rng.choice([0, 1, 2, 4, 255])))
cases += [(s, 0, 0, 1) for s in (0, 1, M, 1 << 63, 0x8000000000000001, 0xFFFFFFFF, 0x100000000)]
cases += [(rng.getrandbits(64), rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(8)) for _ in range(3000)]
bad = {}
for k in range(0, len(cases), 400):
    ch = cases[k:k + 400]
    out = subprocess.check_output(['/tmp/p106chk'] + [w for x, a, b, d in ch for w in ('%x' % x, '%x' % a, '%x' % b, '%x' % d)]).decode().split('\n')
    for (x, a, b, d), line in zip(ch, out):
        got = [int(w, 16) for w in line.split()]
        st, r = m_ada20(x)
        exp = [st, r & 0xFFFFFFFF, m_674(b, a) & 0xFFFFFFFF, m_6a0(a, b) & 0xFFFFFFFF, m_6bc(a, b) & 0xFFFFFFFF,
               m_6d4(a, d) & 0xFFFFFFFF, m_714(a, d) & 0xFFFFFFFF]
        for nm, e, g in zip(('ADA20.state', 'ADA20', 'AE674', 'AE6A0', 'AE6BC', 'AE6D4', 'AE714'), exp, got):
            if e != g:
                bad.setdefault(nm, []).append((x, a, b, d, e, g))
for nm in ('ADA20.state', 'ADA20', 'AE674', 'AE6A0', 'AE6BC', 'AE6D4', 'AE714'):
    b = bad.get(nm, [])
    print('%s %s model check: %d cases, %d differ %s' % ('EQUIV' if not b else 'DIFFER', nm, len(cases), len(b),
                                                        ' '.join('%x/%x/%x/%x:%x!=%x' % t for t in b[:3])))
