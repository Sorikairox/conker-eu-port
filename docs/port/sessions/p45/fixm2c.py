#!/usr/bin/env python3
# usage: fixm2c.py raw.c out.c -- P45: clean m2c's leftover markers in the func_1504CB98 draft
import re, sys
c = open(sys.argv[1]).read()
def args_at(s, i):  # s[i] == '(' -> (list of top-level args, index after ')')
    d = 0; a = []; st = i + 1
    for j in range(i, len(s)):
        ch = s[j]
        if ch == '(': d += 1
        elif ch == ')':
            d -= 1
            if d == 0: a.append(s[st:j]); return a, j + 1
        elif ch == ',' and d == 1: a.append(s[st:j]); st = j + 1
    raise ValueError
# pad-state copies (6 bytes: lwl/lwr word + lhu)
c = c.replace('M2C_FIELD(&sp188, s32 *, 0) = (s32) M2C_UNALIGNED32(M2C_FIELD(D_800CC6A4, s16 *, 0));',
              'sp188[0] = ((u16 *)D_800CC6A4)[0]; sp188[1] = ((u16 *)D_800CC6A4)[1];')
c = c.replace('M2C_FIELD(D_800CC6A4, s16 *, 0) = M2C_UNALIGNED32(M2C_FIELD(&sp188, s32 *, 0));',
              '((u16 *)D_800CC6A4)[0] = sp188[0]; ((u16 *)D_800CC6A4)[1] = sp188[1];')
c = c.replace('M2C_FIELD(&sp188, u16 *, 4)', 'sp188[2]')
c = c.replace('    M2C_UNK sp188;', '    u16 sp188[3];')
# float bit casts on s32-typed fields
c = re.sub(r'([\w>\-\.]+->unk2[8C]) = M2C_BITWISE\(s32, (.*)\);', r'*(f32 *)&\1 = \2;', c)
c = re.sub(r'M2C_BITWISE\(f32, ([\w>\-\.]+)\)', r'(*(f32 *)&\1)', c)
# M2C_FIELD(x, T, off) -> (*(T)((u8 *)(x) + off))
while True:
    i = c.find('M2C_FIELD(')
    if i < 0: break
    a, e = args_at(c, i + 9)
    c = c[:i] + '(*(%s)((u8 *)(%s) + %s))' % (a[1].strip(), a[0].strip(), a[2].strip()) + c[e:]
# prototypes / externs
c = re.sub(r'\bM2C_UNK\b', 's32', c)
c = re.sub(r'^(.*)/\* extern \*/$', r'\1', c, flags=re.M)
c = c.replace('*(&D_800BEB30 + (D_800C3E78 * 2))', 'D_800BEB30[D_800C3E78]').replace('extern s32 D_800BEB30;', 'extern u16 D_800BEB30[];')
c = c.replace('*(&D_8009952C + (var_v0_5 * 2))', 'D_8009952C[var_v0_5]').replace('extern s32 D_8009952C;', 'extern u16 D_8009952C[];')
c = c.replace('*(&D_800B89C4 + (D_800D154C->unk13C * 0x32C))', 'D_800B89C4[D_800D154C->unk13C * 0x32C]').replace('extern s32 D_800B89C4;', 'extern u8 D_800B89C4[];')
c = c.replace('(u8 *)(D_800D0000)', '(u8 *)(D_800CC6A4)').replace('extern void *D_800D0000;\n', '')
assert 'M2C' not in c, [l for l in c.split('\n') if 'M2C' in l][:5]
open(sys.argv[2], 'w').write(c)
