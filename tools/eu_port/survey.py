#!/usr/bin/env python3
"""Survey a US C file for manual EU porting. Run from conker/: survey.py <us file stem>"""
import json, re, sys
sys.path.insert(0, '../tools/eu_port')
import eu_asm
stem = sys.argv[1]
src = open(f'src/{stem}.c').read()
m = json.load(open('build_port/match.json'))
order = []
for mm in re.finditer(r'^(?:#pragma GLOBAL_ASM\("[^"]*/(\w+)\.s"\)|(?:static\s+)?[\w\s\*]+?\b(\w+)\s*\([^;{]*\)\s*\{)', src, re.M):
    if mm.group(2) in ('if', 'switch', 'while', 'for', 'return', 'else'):
        continue
    if mm.group(1):
        order.append((mm.group(1), 'asm'))
    else:
        order.append((mm.group(2), 'C'))
eu = eu_asm.functions()
byaddr = {v[0]: (k, v[1]) for k, v in eu.items()}
amb = m['ambiguous']
for name, kind in order:
    us = int(name[-8:], 16) if re.search(r'[0-9A-F]{8}$', name) else None
    info = ''
    if name in m['matches']:
        e = m['matches'][name]
        info = f"EU {e['vram']:08X} ({e['eu']}) shift {e.get('shift')}"
    elif name in amb:
        info = 'ambiguous ' + ' '.join(amb[name]['candidates'][:6])
    else:
        um = [u for u in m['unmatched'] if u['name'] == name]
        info = 'unmatched' + (f" {um[0]['words']} words" if um else ' (asm in US)')
    print(f'{kind:4} {name:32} {info}')
