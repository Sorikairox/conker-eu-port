#!/usr/bin/env python3
# P95: func_150ADA68 uses MIPS III 64-bit instructions (ld/sd/dsll32...) that the Unicorn MIPS32 harness cannot run.
# Instruction-level model of the EU asm vs the NM C compiled for the host (gcc), over random states + edge states.
import random, struct, subprocess, sys, os
M = (1 << 64) - 1
def asm_model(a0):
    a2 = ((a0 << 63) & M) >> 31            # dsll32 a2,a0,31 ; dsrl a2,a2,31
    a1 = ((a0 << 31) & M) >> 32            # dsll a1,a0,31 ; dsrl32 a1,a1,0
    a2 |= a1
    a0b = ((a0 << 44) & M) >> 32           # dsll32 a0,a0,12 ; dsrl32 a0,a0,0
    a2 ^= a0b
    a0n = ((a2 >> 20) & 0xFFF) ^ a2        # dsrl a0,a2,20 ; andi 0xFFF ; xor
    lo = a0n & 0xFFFFFFFF                  # dsll32 / dsra32: sign-extended low word, andi 0xFFFF
    v0 = lo & 0xFFFF
    f = struct.unpack('>f', struct.pack('>f', float(v0)))[0] * struct.unpack('>f', bytes.fromhex('37800080'))[0]
    return a0n, struct.unpack('>I', struct.pack('>f', f))[0]
here = os.path.dirname(os.path.abspath(__file__))
src = open(sys.argv[1]).read()
c = '''#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long u64; typedef long long s64; typedef int s32; typedef float f32;
s64 D_80088950;
%s
int main(int c, char **v) { for (int i = 1; i < c; i++) { D_80088950 = (s64) strtoull(v[i], 0, 16);
  f32 r = func_150ADA68(); unsigned u; __builtin_memcpy(&u, &r, 4); printf("%%016llx %%08x\\n", (u64) D_80088950, u); } }
''' % src.replace('extern s64 D_80088950;', '')
open('/tmp/ada68.c', 'w').write(c)
subprocess.check_call(['gcc', '-O1', '-ffp-contract=off', '-o', '/tmp/ada68', '/tmp/ada68.c'])
rng = random.Random(1)
states = [0, 1, M, 1 << 63, 0x8000000000000001, 0xFFFFFFFF, 0x100000000] + [rng.getrandbits(64) for _ in range(2000)]
out = subprocess.check_output(['/tmp/ada68'] + ['%x' % s for s in states]).decode().split('\n')
bad = 0
for s, line in zip(states, out):
    st, fb = asm_model(s)
    got = line.split()
    if int(got[0], 16) != st or int(got[1], 16) != fb:
        bad += 1
        if bad < 5: print('DIFF state %016x: asm %016x %08x c %s' % (s, st, fb, line))
print('%s func_150ADA68 model check: %d states, %d differ' % ('EQUIV' if bad == 0 else 'DIFFER', len(states), bad))
