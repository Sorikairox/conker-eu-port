#!/usr/bin/env python3
# spgen.py func draft.c template.c out.c : fill the func_151308E4 spawner template (af04_Ay.c) from an m2c draft
import re, sys
fn, draft, tmpl, out = sys.argv[1:5]
d = open(draft).read()
t = open(tmpl).read()
body = d[d.index('{', d.index(fn)) + 1:]
lines = [l.strip() for l in body.split('\n') if '=' in l or 'func_' in l]
res = []
mul = add = None
for l in lines:
    m = re.match(r'temp_f6 = func_150ADA68\(\) \* ([0-9.]+f);', l)
    if m:
        add = re.search(r'temp_f2 = temp_f6 \+ ([0-9.]+f);', d).group(1)
        res.append('    sp.u5C = sp.u60 = (func_150ADA68() * %s) + %s;' % (m.group(1), add)); continue
    if l.startswith(('sp5C = temp', 'sp60 = temp', 'sp24 = func', 'temp_')) and 'func_151308E4' not in l:
        continue
    m = re.match(r'func_15143794\(arg8, \(s16\) \(\(\(u32\) sp24 (% \d+U|& 0x[0-9A-F]+)\) - (0x[0-9A-F]+)\), (.*), &sp7C\);', l)
    if m:
        res.append('    func_15143794(arg8, (s16) ((func_150ADA20() %s) - %s), %s, sp.u7C);' % (m.group(1), m.group(2), m.group(3))); continue
    m = re.match(r'sp([0-9A-F]{2}) (=|\|=) (.*);', l)
    if m:
        off = int(m.group(1), 16)
        if off == 0x2C: res.append('    scale = %s;' % m.group(3)); continue
        if off in (0x64, 0x68, 0x6C): res.append('    sp.u%s = %s;' % (m.group(1), m.group(3))); continue
        res.append('    sp.u%s %s %s;' % (m.group(1), m.group(2), m.group(3))); continue
    if l.startswith('if (func_150ADA20() & 1)'):
        res.append('    ' + l); continue
    if l.startswith('temp_v0 = func_151308E4'):
        res.append('    obj = ' + l.split('= ', 1)[1].replace('&sp34', '&sp')); continue
for l in list(res):
    pass
# rebuild: template header up to first statement, then generated statements, then template tail from 'if (obj != 0)'
head = t[:t.index('    sp.u51 = ')]
tail = t[t.index('    if (obj != 0) {'):]
s = '\n'.join(res)
# close if-blocks for '|=' lines following an if
s = re.sub(r'(    if \(func_150ADA20\(\) & 1\) \{)\n(    sp.u8C \|= [^\n]+)', r'\1\n    \2\n    }', s)
open(out, 'w').write(head.replace('func_150CAF04', fn) + s + '\n' + tail)
