#!/usr/bin/env python3
"""Spawner stack-struct fixes (s65 recipe, s67 tool): usage spawnfix.py in.c out.c
1. three s32/f32 copies of a vec3 into &sp.uXX -> one 12-byte struct copy (V3i);
2. fields stored with 0xFF / 0xB4 (li 255 / li 0xB4) become u8 (m2c's s8 gives li -1/-0x4C).
Run tools/eu_port/spsort.py first (field order)."""
import re,sys
src,dst=sys.argv[1:3]
s=open(src).read()
pat=re.compile(r'^(\s*)\(\*\((?:s32|f32) \*\)\(\(u8 \*\)\((&sp\.u[0-9A-F]+)\) \+ 0\)\) = \((?:s32|f32)\) \(\*\((?:s32|f32) \*\)\(\(u8 \*\)(.+?) \+ 0\)\);\n\s*\(\*\((?:s32|f32) \*\)\(\(u8 \*\)\(\2\) \+ 4\)\) = .*\n\s*\(\*\((?:s32|f32) \*\)\(\(u8 \*\)\(\2\) \+ 8\)\) = .*\n',re.M)
s=pat.sub(lambda m:f'{m.group(1)}*(V3i *) {m.group(2)} = *(V3i *) {m.group(3)};\n',s)
if 'V3i' in s and 'typedef struct { s32 x, y, z; } V3i;' not in s: s='typedef struct { s32 x, y, z; } V3i;\n'+s
for f in set(re.findall(r'sp\.u([0-9A-F]+) = (?:0xFF|0xB4);',s)):
    s=re.sub(rf'(\n\s+)s8 u{f};',rf'\1u8 u{f};',s)
open(dst,'w').write(s)
