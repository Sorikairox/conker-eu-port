import re,sys
src,dst=sys.argv[1:3]
s=open(src).read()
pat=re.compile(r'^(\s*)\(\*\((?:s32|f32) \*\)\(\(u8 \*\)\((&sp\.u[0-9A-F]+)\) \+ 0\)\) = \((?:s32|f32)\) \(\*\((?:s32|f32) \*\)\(\(u8 \*\)(.+?) \+ 0\)\);\n\s*\(\*\((?:s32|f32) \*\)\(\(u8 \*\)\(\2\) \+ 4\)\) = .*\n\s*\(\*\((?:s32|f32) \*\)\(\(u8 \*\)\(\2\) \+ 8\)\) = .*\n',re.M)
s=pat.sub(lambda m:f'{m.group(1)}*(V3i *) {m.group(2)} = *(V3i *) {m.group(3)};\n',s)
if 'V3i' in s: s='typedef struct { s32 x, y, z; } V3i;\n'+s
for f in set(re.findall(r'sp\.u([0-9A-F]+) = 0xFF;',s)):
    s=s.replace(f'        s8 u{f};\n',f'        u8 u{f};\n')
open(dst,'w').write(s)
