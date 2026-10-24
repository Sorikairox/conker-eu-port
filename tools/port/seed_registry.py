#!/usr/bin/env python3
# P221: seed tools/port/verify_registry.tsv from the session docs (conversion sections) and the session script dirs.
# usage: tools/port/seed_registry.py P198 P200 ... > rows.tsv   (run from the repo root; prints rows, no header)
# func = every `| func_X |` table row / `### func_X` heading inside a "## N. Conversion..." section.
# file = src_eu file holding the definition (NM block or plain). setup_file / mutant_file = pNNN/<HEX8>_setups*.txt /
# <HEX8>_muts*.txt, or port-b's s<hex4>.txt / m<hex4>*.txt (comma-joined). knobs = explicit global DIFFTEST_ tokens
# (ROMDATA, MEMSTK, STKFILL, ...) and TR=N found in the function's row / subsection or the setup files' # comments. Unknown -> blank (never guessed).
import sys, re, glob, os
KN = r'DIFFTEST_(?:ROMDATA|MEMSTK|STKFILL|ARGMEM|JALRSKIP|SIGNORE|JALR_DYN|VARARGS_REF|OUTPARAMS|REFLEN|TUCMP_LEN)=[^\s,;)`]+'
defs = {}
for p in sorted(glob.glob('conker/src_eu/*.c')):
    for m in re.finditer(r'^[A-Za-z_][^\n;#/=]*\b(func_[0-9A-F]{8})\s*\([^;{]*\)\s*\{', open(p).read(), re.M):
        defs.setdefault(m.group(1), os.path.basename(p)[:-2])
for s in sys.argv[1:]:
    t = open('docs/port/sessions/%s.md' % s).read(); d = 'docs/port/sessions/' + s.lower()
    secs = re.findall(r'^## [^\n]*Conversion[^\n]*\n(.*?)(?=^## |\Z)', t, re.M | re.S)
    seen = []
    for sec in secs:
        # chunks: table rows and ### subsections
        chunks = [(m.group(1), m.group(0)) for m in re.finditer(r'^\| (func_[0-9A-F]{8}) \|[^\n]*', sec, re.M)]
        chunks += [(m.group(1), m.group(0)) for m in re.finditer(r'^### (func_[0-9A-F]{8})[^\n]*\n(?:(?!###)[^\n]*\n?)*', sec, re.M)]
        for fn, txt in chunks:
            if fn in seen: continue
            seen.append(fn); h = fn[5:]; h4 = h[4:].lower()
            st = sorted(glob.glob('%s/%s_setups*.txt' % (d, h))) or sorted(glob.glob('%s/s%s.txt' % (d, h4))) or sorted(glob.glob('%s/%s_setups*.txt' % (d, h4)))
            mu = sorted(glob.glob('%s/%s_muts*.txt' % (d, h))) or sorted(glob.glob('%s/m%s*.txt' % (d, h4))) or sorted(glob.glob('%s/%s_mut*.txt' % (d, h4)))
            com = ''.join(l for f in st for l in open(f) if l.lstrip().startswith('#'))  # setup-file comments
            kv = {}
            for k in sorted(set(k.rstrip('.:') for k in re.findall(KN, txt + com))):
                a, v = k.split('=', 1); kv.setdefault(a, []).append(v)  # same knob twice -> comma-joined list
            kn = ['%s=%s' % (a, ','.join(v)) for a, v in kv.items()]
            tr = re.findall(r'\bTR=(\d+)', txt); kn += ['TR=' + tr[0]] if tr else []
            print('\t'.join([fn, defs.get(fn, ''), ','.join(st), ' '.join(kn), ','.join(mu), s]))
