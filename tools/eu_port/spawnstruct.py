#!/usr/bin/env python3
# spawnstruct.py (s138 spstruct.py) draft.c outprefix : m2c spawner draft (func_151559FC(&spA..) + memcpy(&spB, 0x58)) ->
# two local structs (A = spawner template, B = 0x58 copy block); variants with s32 pad[n] for the frame.
import re, sys
src = open(sys.argv[1]).read(); out = sys.argv[2]
A_T = {0x10:'u8',0x12:'s16',0x14:'u16',0x16:'s16',0x18:'s16',0x40:'u8',0x41:'u8',0x44:'u8'}
for o in range(0x1A,0x24): A_T[o]='u8'
for o in range(0x24,0x40,4): A_T[o]='s32'
decls = dict((int(m.group(3),16),(m.group(1)+m.group(2))) for m in re.finditer(r'^\s+([\w ]+?) (\*?)sp([0-9A-F]+);$', src, re.M))
a = int(re.search(r'func_151559FC\(&sp([0-9A-F]+)', src).group(1),16)
b = int(re.search(r'memcpy\([^,]+, &sp([0-9A-F]+), 0x58\)', src).group(1),16)
def sz(t): return 4 if ('*' in t or '32' in t) else 2 if '16' in t else 1
def mk(base, end, tmap, name):
    fs=[]; o=base; offs=sorted(k for k in decls if base<=k<end)
    for k in offs:
        if k>o: fs.append('        u8 pad%X[0x%X];' % (o-base, k-o))
        t = tmap.get(k-base, decls[k]) if tmap is not None else decls[k]
        if t=='s8' and tmap is not None and (k-base) in A_T: t=A_T[k-base]
        fs.append('        %s f%X;' % (t.replace('*',' *').replace('  ',' '), k-base)); o=k+sz(t)
    if end>o: fs.append('        u8 pad%X[0x%X];' % (o-base, end-o))
    return fs, offs
aend = max(k for k in decls if k>=a); aend = (aend+4)&~3
afs, aoffs = mk(a, aend, A_T, 'sp')
bfs, boffs = mk(b, b+0x58, None, 'b')
body = src
for k in aoffs: body = re.sub(r'\bsp%X\b' % k, 'sp.f%X' % (k-a), body)
for k in boffs: body = re.sub(r'\bsp%X\b' % k, 'b.f%X' % (k-b), body)
body = re.sub(r'^\s+[\w ]+? \*?(sp|b)\.f[0-9A-F]+;\n', '', body, flags=re.M)
body = body.replace('&sp.f0,', '&sp,').replace('&b.f0,', '&b,')
body = re.sub(r'\(\*\(u8 \*\)\(\(u8 \*\)arg0 \+ 0x23D\)\)', 'arg0[0x23D]', body)
body = body.replace('s32 func_151559FC(f32 *,', 's32 func_151559FC(void *,')
for n in (0,2,4,6,8):
    st = ('    s32 pad[%d];\n' % n if n else '') + '    struct {\n' + '\n'.join(afs) + '\n    } sp;\n    struct {\n' + '\n'.join(bfs) + '\n    } b;\n'
    v = re.sub(r'(\) \{\n)', r'\1' + st.replace('\\','\\\\'), body, count=1)
    open('%s_p%d.c' % (out, n), 'w').write(v)
