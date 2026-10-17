#!/usr/bin/env python3
"""Which EU game C files look like more than one object, judged by their .rodata.

usage: rodata_bounds.py [stem ...]

For every game C file (or the given ones) prints, from rodata_split.py's analysis:
  BOUNDARY  data (string/table) after floats or jump tables: two IDO objects for sure
  PADDING   zero padding up to a 16-byte boundary between two late items: maybe two objects
  US        a rodata subsegment start of conker.us.yaml (the US authors split .rodata at file
            boundaries) that maps inside the file's .rodata (US->EU offset from the nearest
            US-named data symbol in undefined_syms.eu.txt)
Splitting such a file: find the first function of the second object (16-byte aligned start, its
own .data/.rodata start; see HANDOFF "game_16EE20"), add a c subsegment for it in
conker.eu.yaml, move the functions to src_eu/game_eu_<rom>.c with its pragma paths fixed, then
rodata_split.py --own both halves.
"""
import os, re, sys, bisect
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import datarefs as DR
import rodata_split as RS

ROOT = DR.ROOT


def us_hints():
    """EU rom offsets of the US game_data rodata subsegment starts."""
    us = open(os.path.join(ROOT, 'conker.us.yaml')).read()
    m = re.search(r'name:\s+game_data\n\s+type:\s+code\n\s+start:\s+(0x[0-9A-Fa-f]+)\n\s+vram:\s+(0x[0-9A-Fa-f]+)', us)
    us_start, us_vram = int(m.group(1), 16), int(m.group(2), 16)
    seg = us[m.end():us.find('- name:', m.end())]
    starts = [int(x, 16) for x in re.findall(r'- \[(0x[0-9A-Fa-f]+), rodata\]', seg)]
    pairs = []
    for l in open(os.path.join(ROOT, 'undefined_syms.eu.txt')):
        mm = re.match(r'\s*D_([0-9A-F]{8})\s*=\s*0x([0-9A-Fa-f]+)', l)
        if mm:
            pairs.append((int(mm.group(1), 16), int(mm.group(2), 16)))
    pairs.sort()
    keys = [p[0] for p in pairs]
    d = DR.segments()['game_data']
    out = []
    for r in starts:
        v = r - us_start + us_vram
        i = bisect.bisect_right(keys, v) - 1
        if i < 0:
            continue
        eu = v + (pairs[i][1] - pairs[i][0])
        out.append(eu - d['vram'] + d['start'])
    return out


def main():
    only = sys.argv[1:]
    R = DR.refs('game')
    O = DR.owners('game', R)
    DR.refs = lambda seg='game': R
    DR.owners = lambda seg='game', allrefs=None: O
    hints = us_hints()
    for a, b, stem in DR.code_files('game'):
        if not stem or (only and stem not in only):
            continue
        try:
            seg, lo, hi, warn = RS.own_range(stem)
        except SystemExit:
            continue
        lines = []
        for w in warn:
            if 'BOUNDARY' in w:
                lines.append('BOUNDARY ' + w.split(': ', 1)[1].split(': this')[0])
            elif 'zero padding' in w:
                lines.append('PADDING  ' + w.split(' between')[0].replace('zero padding ', ''))
        for h in hints:
            if lo < h < hi:
                lines.append('US       rodata split at 0x%X' % h)
        for l in lines:
            print('%-24s 0x%06X-0x%06X %s' % (stem, lo, hi, l))


if __name__ == '__main__':
    main()
