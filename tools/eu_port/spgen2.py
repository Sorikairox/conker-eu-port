#!/usr/bin/env python3
# spgen2.py func draft.c template.c out.c : fill the s92 func_151308E4 spawner template (docs/sessions/s95_drafts/af04_Ay.c) from an m2c draft
# (gensome.sh output); s92 spgen.py with the m2c struct base shifted onto the template (struct at sp+0x34). Check the frame: pad98[0xC] vs [0x10].
import re, sys
fn, draft, tmpl, out = sys.argv[1:5]
d = open(draft).read()
t = open(tmpl).read()
body = d[d.index('{', d.index(fn + '(')) + 1:]
base = int(re.search(r'func_151308E4\(&sp([0-9A-F]+)', body).group(1), 16)
delta = 0x34 - base
lines = [l.strip() for l in body.split('\n') if '=' in l or 'func_' in l]
res = []
for l in lines:
    m = re.match(r'temp_f\d+ = random_float\(\) \* ([0-9.e+-]+f);', l)
    if m:
        add = re.search(r'temp_f\d+ = temp_f\d+ \+ ([0-9.e+-]+f);', d).group(1)
        res.append('    sp.u5C = sp.u60 = (random_float() * %s) + %s;' % (m.group(1), add)); continue
    if re.match(r'sp[0-9A-F]+ = (temp|random_int)', l) or l.startswith('temp_') and 'func_151308E4' not in l:
        continue
    m = re.match(r'func_15143794\(arg8, \(s16\) \(\(\(u32\) sp[0-9A-F]+ (% \d+U|& 0x[0-9A-F]+)\) - (0x[0-9A-F]+)\), (.*), &sp[0-9A-F]+\);', l)
    if m:
        res.append('    func_15143794(arg8, (s16) ((random_int() %s) - %s), %s, sp.u7C);' % (m.group(1), m.group(2), m.group(3))); continue
    m = re.match(r'sp([0-9A-F]{2}) (=|\|=) (.*);', l)
    if m:
        off = int(m.group(1), 16) + delta
        if off == 0x2C: res.append('    scale = %s;' % m.group(3)); continue
        res.append('    sp.u%X %s %s;' % (off, m.group(2), m.group(3))); continue
    if l.startswith('if (random_int() & 1)'):
        res.append('    ' + l); continue
    if l.startswith('temp_v0 = func_151308E4'):
        res.append('    obj = ' + re.sub(r'&sp[0-9A-F]+', '&sp', l.split('= ', 1)[1])); continue
head = t[:t.index('    sp.u51 = ')]
tail = t[t.index('    if (obj != 0) {'):]
s = '\n'.join(res)
s = re.sub(r'(    if \(random_int\(\) & 1\) \{)\n(    sp.u8C \|= [^\n]+)', r'\1\n    \2\n    }', s)
open(out, 'w').write(head.replace('func_150CAF04', fn) + s + '\n' + tail)
