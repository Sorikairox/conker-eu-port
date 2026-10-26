#!/usr/bin/env python3
# usage: [VFIRST=1] spawn.py <func> A|B "<params>" "<fields>" "<call args>" <size> [g]
#   C for the "spawn an effect, then memcpy its parameter struct into ret+0x28" family.
#   A = effect_node_create (9 args), B = effect_node_create_nodraw (8 args); fields "u8 *unk0=arg0;u8 unk4=arg0[0x3B];f32 unk8=0.0f"
#   (in stack order); g = early `if (arg0 == NULL) return;`; VFIRST=1 declares temp_v0 before the struct.
import sys
name, kind, sig, fields, args, size = sys.argv[1:7]
guard = len(sys.argv) > 7
callee = {'A': 'effect_node_create', 'B': 'effect_node_create_nodraw'}[kind]
F = [f.strip() for f in fields.split(';') if f.strip()]
decl = []; asg = []
for f in F:
    d, v = f.split('=', 1) if '=' in f else (f, None)
    decl.append('        %s;' % d.strip())
    nm = d.strip().split()[-1].lstrip('*')
    if v is not None:
        asg.append('    tmp.%s = %s;' % (nm, v.strip()))
import os
if os.environ.get('VFIRST'):
    body = ['void %s(%s) {' % (name, sig), '    struct260 *temp_v0;', '    struct {'] + decl + ['    } tmp;', '']
else:
    body = ['void %s(%s) {' % (name, sig), '    struct {'] + decl + ['    } tmp;', '    struct260 *temp_v0;', '']
if guard:
    body += ['    if (arg0 == NULL) {', '        return;', '    }']
body += asg + ['    temp_v0 = %s(%s);' % (callee, args), '    if (temp_v0 != NULL) {',
               '        memcpy((u8 *)temp_v0 + 0x28, &tmp, %s);' % size, '    }', '}']
print('\n'.join(body))
