#!/usr/bin/env python3
"""gfxfind.py [--list] [--untried] [--hints FUNC ...] [--min N]
Finds GLOBAL_ASM functions that build F3DEX2 display lists: `lui` constants whose top byte is a GBI opcode,
stored with `sw r,0(base)` and a following `sw x,4(base)`, in a function that advances a pointer by 8.
Default: counts, size buckets, per-command tag counts. --list: one line per function (size, tags, logged?).
--untried: only functions not in repair_log.tsv. --hints F...: draft gSP/gDP macro lines for those functions
(word 0 decoded from the constant, word 1 from its source: zero / const / &sym / ?). Use `gdl++` as pkt."""
import sys, os, re, glob, collections
R = os.path.expanduser('~/conker'); os.chdir(R + '/conker')
logged = {l.split('\t')[0] for l in open(R + '/tools/eu_port/repair_log.tsv')}
NAMES = {0xE7: 'PIPESYNC', 0xE6: 'LOADSYNC', 0xE8: 'TILESYNC', 0xE9: 'FULLSYNC', 0xDA: 'MTX', 0xDB: 'MOVEWORD',
         0xD9: 'GEOMODE', 0xD8: 'POPMTX', 0xD7: 'TEXTURE', 0xFB: 'ENVCOLOR', 0xFA: 'PRIMCOLOR', 0xFC: 'COMBINE',
         0xFD: 'SETTIMG', 0xF5: 'SETTILE', 0xF2: 'TILESIZE', 0xF6: 'FILLRECT', 0xF7: 'FILLCOLOR', 0xF8: 'FOGCOLOR',
         0xF9: 'BLENDCOLOR', 0xFE: 'DEPTHIMG', 0xFF: 'COLORIMG', 0xE2: 'OTHER_L', 0xE3: 'OTHER_H', 0xEF: 'OTHERMODE',
         0xDE: 'DL', 0xDF: 'ENDDL', 0xDC: 'MOVEMEM', 0xF0: 'LOADTLUT', 0xF3: 'LOADBLOCK', 0xF4: 'LOADTILE',
         0xE4: 'TEXRECT', 0xE1: 'RDPHALF1', 0xF1: 'RDPHALF2',
         0x01: 'VTX', 0x05: 'TRI1', 0x06: 'TRI2', 0x07: 'QUAD', 0x03: 'CULLDL', 0x04: 'BRANCHZ'}
WEAK = {0x01, 0x03, 0x04, 0x05, 0x06, 0x07, 0xE1, 0xF1}

def hx(x): return '0x%X' % x

def parse(path):
    txt = open(path).read()
    ins = []
    for m in re.finditer(r'\*/\s+(\w[\w.]*)\s*(.*)', txt):
        ins.append((m.group(1), [a.strip() for a in re.split(r',\s*(?![^()]*\))', m.group(2).split('#')[0].strip())]))
    return ins

def num(s):
    try: return int(s, 0)
    except Exception: return None

def scan(ins):
    """-> (stores, adv8). stores: list of (w0, w1src, idx). w1src in 'zero','const:0x..','sym:name','?'"""
    const = {}; sym = {}; stores = []; adv8 = False; seen = []
    for i, (o, a) in enumerate(ins):
        if o == 'lui' and len(a) == 2:
            m = re.match(r'\((0x[0-9A-Fa-f]+) >> 16\)', a[1])
            if m:
                const[a[0]] = int(m.group(1), 16); sym.pop(a[0], None)
                if (const[a[0]] >> 24) in NAMES and (const[a[0]] >> 24) not in WEAK: seen.append((const[a[0]], '?', i))
            elif a[1].startswith('%hi('): sym[a[0]] = a[1][4:-1]; const.pop(a[0], None)
            elif num(a[1]) is not None: const[a[0]] = num(a[1]) << 16; sym.pop(a[0], None)
        elif o == 'ori' and len(a) == 3:
            m = re.match(r'\((0x[0-9A-Fa-f]+) & 0xFFFF\)', a[2])
            if m: const[a[0]] = int(m.group(1), 16)
            elif a[1] in const and num(a[2]) is not None: const[a[0]] = const[a[1]] | num(a[2])
            else: const.pop(a[0], None)
        elif o == 'addiu' and len(a) == 3:
            if a[2] == '0x8' and a[0] != '$sp': adv8 = True
            if a[2].startswith('%lo(') and a[1] in sym: sym[a[0]] = sym[a[1]]; const.pop(a[0], None)
            elif a[1] == '$zero' and num(a[2]) is not None: const[a[0]] = num(a[2]) & 0xFFFFFFFF; sym.pop(a[0], None)
            else: const.pop(a[0], None); sym.pop(a[0], None)
        elif o == 'sw' and len(a) == 2:
            m = re.match(r'(0x[0-9A-Fa-f]+|-?\d+)\((\$\w+)\)', a[1])
            if m and num(m.group(1)) == 0 and a[0] in const and (const[a[0]] >> 24) in NAMES:
                w0 = const[a[0]]; base = m.group(2); w1 = '?'
                for (o2, a2) in ins[i + 1:i + 16]:
                    if o2 == 'sw' and len(a2) == 2:
                        m2 = re.match(r'(0x[0-9A-Fa-f]+|\d+)\((\$\w+)\)', a2[1])
                        if m2 and num(m2.group(1)) == 4 and m2.group(2) == base:
                            r = a2[0]
                            w1 = 'zero' if r == '$zero' else ('const:' + hx(const[r]) if r in const else
                                                              'sym:' + sym[r] if r in sym else '?')
                            break
                stores.append((w0, w1, i))
        else:
            if len(a) > 0 and a[0].startswith('$') and o not in ('sb', 'sh', 'swc1', 'beq', 'bne', 'nop', 'jr', 'j', 'b'):
                if o not in ('lui', 'ori', 'addiu'): const.pop(a[0], None); sym.pop(a[0], None)
    if not stores and adv8: stores = seen  # opcode built indirectly (or with a variable)
    return stores, adv8

def isgfx(stores, adv8):
    if not adv8: return False
    strong = [s for s in stores if (s[0] >> 24) not in WEAK]
    return len(strong) >= 1 or len(stores) >= 2

def ptr(w1):
    if w1.startswith('sym:'): return '&' + w1[4:]
    if w1.startswith('const:'): return w1[6:]
    return '0' if w1 == 'zero' else 'w1?'

def hint(w0, w1):
    op = w0 >> 24; lo = w0 & 0xFFFFFF; w1v = num(w1[6:]) if w1.startswith('const:') else (0 if w1 == 'zero' else None)
    P = 'gdl++'
    if op == 0xE7: return f'gDPPipeSync({P});'
    if op == 0xE6: return f'gDPLoadSync({P});'
    if op == 0xE8: return f'gDPTileSync({P});'
    if op == 0xE9: return f'gDPFullSync({P});'
    if op == 0xDE: return f'gSPDisplayList({P}, {ptr(w1)});' if (w0 >> 16) & 0xFF == 0 else f'gSPBranchList({P}, {ptr(w1)});'
    if op == 0xDF: return f'gSPEndDisplayList({P});'
    if op == 0xDA:
        p = (w0 & 0xFF) ^ 1
        fl = '|'.join(['G_MTX_PROJECTION' if p & 4 else 'G_MTX_MODELVIEW', 'G_MTX_LOAD' if p & 2 else 'G_MTX_MUL',
                       'G_MTX_PUSH' if p & 1 else 'G_MTX_NOPUSH'])
        return f'gSPMatrix({P}, {ptr(w1)}, {fl});'
    if op == 0xD8: return f'gSPPopMatrix({P}, {hx(w1v) if w1v is not None else "?"});'
    if op == 0xDB:
        idx = (w0 >> 16) & 0xFF; off = w0 & 0xFFFF
        if idx == 6: return f'gSPSegment({P}, {off // 4}, {ptr(w1)});'
        n = {0: 'G_MW_MATRIX', 2: 'G_MW_NUMLIGHT', 4: 'G_MW_CLIP', 8: 'G_MW_FOG', 0xA: 'G_MW_LIGHTCOL', 0xE: 'G_MW_PERSPNORM'}.get(idx, hx(idx))
        if idx == 2 and w1v is not None: return f'gSPNumLights({P}, {w1v // 24});'
        if idx == 8 and w1v is not None:
            m = (w1v >> 16) & 0xFFFF; o = w1v & 0xFFFF
            return f'gMoveWd({P}, G_MW_FOG, G_MWO_FOG, {hx(w1v)});  /* gSPFogFactor(mul={m - 0x10000 if m & 0x8000 else m}, off={o - 0x10000 if o & 0x8000 else o}) */'
        return f'gMoveWd({P}, {n}, {hx(off)}, {ptr(w1)});'
    if op == 0xD9:
        clr = (~w0) & 0xFFFFFF
        return f'gSPGeometryMode({P}, {hx(clr)}, {ptr(w1)});  /* clear=~{hx(lo)}; Set/Clear forms when one side is 0 */'
    if op == 0xD7:
        lvl = (w0 >> 11) & 7; tile = (w0 >> 8) & 7; on = (w0 >> 1) & 0x7F
        s = f'{(w1v >> 16) & 0xFFFF:#x}, {w1v & 0xFFFF:#x}' if w1v is not None else 's, t'
        return f'gSPTexture({P}, {s}, {lvl}, {tile}, {"G_ON" if on else "G_OFF"});'
    if op == 0xFB or op == 0xF8 or op == 0xF9 or op == 0xFA:
        n = {0xFB: 'gDPSetEnvColor', 0xF8: 'gDPSetFogColor', 0xF9: 'gDPSetBlendColor', 0xFA: 'gDPSetPrimColor'}[op]
        c = f'{(w1v >> 24) & 255}, {(w1v >> 16) & 255}, {(w1v >> 8) & 255}, {w1v & 255}' if w1v is not None else 'r, g, b, a'
        if op == 0xFA: return f'{n}({P}, {(w0 >> 8) & 255}, {w0 & 255}, {c});'
        return f'{n}({P}, {c});'
    if op == 0xF7: return f'gDPSetFillColor({P}, {hx(w1v) if w1v is not None else "?"});'
    if op == 0xFC: return f'gDPSetCombine({P}, {hx(lo)}, {hx(w1v) if w1v is not None else "?"});'
    if op == 0xEF: return f'gDPSetOtherMode({P}, {hx(lo)}, {hx(w1v) if w1v is not None else "?"});'
    if op in (0xE2, 0xE3):
        ln = (w0 & 0xFF) + 1; sh = 32 - ((w0 >> 8) & 0xFF) - ln
        return f'gSPSetOtherMode({P}, {"G_SETOTHERMODE_L" if op == 0xE2 else "G_SETOTHERMODE_H"}, {sh}, {ln}, {hx(w1v) if w1v is not None else "?"});'
    if op == 0xF2:
        a = f'{(w1v >> 24) & 7}, {hx(w1v >> 12 & 0xFFF)}, {hx(w1v & 0xFFF)}' if w1v is not None else 't, lrs, lrt'
        return f'gDPSetTileSize({P}, tile={(w1v >> 24) & 7 if w1v is not None else "?"}, uls={hx((w0 >> 12) & 0xFFF)}, ult={hx(w0 & 0xFFF)}, lrs/lrt from w1={w1});'
    if op == 0xF6: return f'gDPFillRectangle({P}, ulx, uly, lrx={(w0 >> 14) & 0x3FF}, lry={(w0 >> 2) & 0x3FF});  /* w1={w1} */'
    if op == 0xFD: return f'gDPSetTextureImage({P}, fmt={(w0 >> 21) & 7}, siz={(w0 >> 19) & 3}, width={(w0 & 0xFFF) + 1}, {ptr(w1)});'
    if op == 0xFF: return f'gDPSetColorImage({P}, fmt={(w0 >> 21) & 7}, siz={(w0 >> 19) & 3}, width={(w0 & 0xFFF) + 1}, {ptr(w1)});'
    if op == 0xFE: return f'gDPSetDepthImage({P}, {ptr(w1)});'
    if op == 0xF5: return f'gDPSetTile({P}, ...);  /* w0={hx(w0)} w1={w1} */'
    if op == 0x01:
        n = (w0 >> 12) & 0xFF; v0 = ((w0 >> 1) & 0x7F) - n
        return f'gSPVertex({P}, {ptr(w1)}, {n}, {v0});'
    if op == 0x05: return f'gSP1Triangle({P}, {(w0 >> 17) & 0x7F}, {(w0 >> 9) & 0x7F}, {(w0 >> 1) & 0x7F}, 0);'
    if op == 0x06: return f'gSP2Triangles({P}, {(w0 >> 17) & 0x7F}, {(w0 >> 9) & 0x7F}, {(w0 >> 1) & 0x7F}, 0, ...w1={w1});'
    return f'/* {NAMES[op]} {hx(w0)} {w1} */'

def main():
    args = sys.argv[1:]
    lst = '--list' in args; untried = '--untried' in args
    hints = []
    if '--hints' in args:
        hints = args[args.index('--hints') + 1:]
    live = set()  # functions that still have a GLOBAL_ASM pragma (the .s files stay on disk after a match)
    for c in glob.glob('src_eu/*.c'):
        live.update(re.findall(r'^#pragma GLOBAL_ASM\("[^"]*/(\w+)\.s"\)', open(c).read(), re.M))
    idx = {}
    for p in glob.glob('asm/nonmatchings/**/*.s', recursive=True):
        if os.path.basename(p)[:-2] in live: idx[os.path.basename(p)[:-2]] = p
    res = []
    for f, p in idx.items():
        if hints and f not in hints: continue
        ins = parse(p)
        stores, adv8 = scan(ins)
        if hints:
            print('//', f, len(ins), 'insns')
            for w0, w1, i in stores: print('    ', hint(w0, w1))
            continue
        if isgfx(stores, adv8): res.append((len(ins), f, stores))
    if hints: return
    res.sort()
    if untried: res = [r for r in res if r[1] not in logged]
    if lst:
        for n, f, st in res:
            tags = collections.Counter(NAMES[s[0] >> 24] for s in st)
            print(n, f, 'logged' if f in logged else 'new', ' '.join(f'{k}{"x%d" % v if v > 1 else ""}' for k, v in sorted(tags.items())))
        return
    print('gfx writers:', len(res), '(logged %d, untried %d)' % (sum(r[1] in logged for r in res), sum(r[1] not in logged for r in res)))
    b = collections.Counter()
    for n, f, st in res: b['<=20' if n <= 20 else '<=50' if n <= 50 else '<=100' if n <= 100 else '>100'] += 1
    print('size buckets:', dict(b))
    t = collections.Counter()
    for n, f, st in res:
        for k in {NAMES[s[0] >> 24] for s in st}: t[k] += 1
    print('functions per command:', ' '.join(f'{k}={v}' for k, v in t.most_common()))

main()
