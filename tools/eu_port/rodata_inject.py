#!/usr/bin/env python3
"""Give GLOBAL_ASM functions their .rodata (and .data) back, for C files that own such a section.

.data (session 10): an owned `[addr, .data, stem]` range is planned like the strings/const part of
.rodata (one region, no late items): items of C functions (local array initialisers, C-defined
variables) are the compiler's; everything else goes, as raw words in `.section .data`, into a
GLOBAL_ASM function between its C neighbours. Data symbols the C code names get a glabel.
A float/double literal item ends after 4/8 bytes; for other compiler-owned items whose end is not
the next reference, put `// rodata_inject: size <rom addr> <bytes>` in the C file.

Runs after splat (hooked into `make VERSION=eu extract`). For every `[addr, .rodata, stem]`
subsegment of a *_data segment in conker.eu.yaml whose src_eu/<stem>.c still has GLOBAL_ASM
pragmas, the bytes of that range are distributed over the file's functions:

  - every rodata item (an address the file's code references with %hi/%lo) belongs to the first
    function (in file order) that references it;
  - items at or after the first float/double/jump-table item form the "late" region (IDO puts
    float/double literals and jump tables after strings and const data);
  - a GLOBAL_ASM function gets its items prepended to its .s file as raw words in
    `.section .rodata` / `.section .late_rodata` (asm-processor then reserves the space at the
    right place in the object);
  - items of C functions are left to the compiler (literals, strings, switch tables), unless the
    C source names them (an extern such as `D_800xxxxx`): those, and items no function of the file
    references, are attached to a neighbouring GLOBAL_ASM function.

usage: rodata_inject.py [stem ...] [--dry]   (default: every owned file)
  --dry   print the plan (one line per chunk) without touching the .s files
Exit status 1 if a file's layout cannot be expressed (message says why).
"""
import os, re, sys, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import datarefs as DR

ROOT = DR.ROOT
LATE_KINDS = {'lwc1', 'ldc1', 'jtbl'}
MARK = '# rodata_inject'


def sym_addrs():
    m = {}
    for f in ('symbol_addrs.eu.txt', 'undefined_syms.eu.txt', 'undefined_syms_auto.txt',
              'undefined_funcs_auto.txt'):
        p = os.path.join(ROOT, f)
        if not os.path.exists(p):
            continue
        for l in open(p):
            mm = re.match(r'\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)', l)
            if mm:
                m.setdefault(mm.group(1), int(mm.group(2), 16))
    return m


def asm_range(path):
    """(start vram, end vram) of a splat function .s (from the /* rom vram word */ comments)."""
    lo = hi = None
    for l in open(path):
        mm = re.match(r'\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/', l)
        if mm:
            v = int(mm.group(1), 16)
            lo = v if lo is None else lo
            hi = v + 4
    return lo, hi


def owned_files(sections=('.rodata',)):
    """[(code seg, stem, rom a, rom b, data seg dict)] for .rodata (or `sections`) subsegments of
    *_data segments; with several sections the tuple gets the section as a 6th element."""
    segs = DR.segments()
    out = []
    for name, s in segs.items():
        if not name.endswith('_data'):
            continue
        subs = s['subs']
        for i, (rom, t, stem) in enumerate(subs):
            if t in sections and stem:
                end = subs[i + 1][0] if i + 1 < len(subs) else s['end']
                out.append((name[:-5], stem, rom, end, s) + ((t,) if len(sections) > 1 else ()))
    return out


def named_ids(csrc, names, va, vb):
    return [i for i in set(re.findall(r'\b[A-Za-z_]\w*\b', csrc)) if i in names and va <= names[i] < vb]


class Fail(Exception):
    pass


def plan(seg, stem, a, b, dseg, allrefs, data, names, sec='.rodata'):
    """List of chunks (start, end, region, owner) for one owned file; owner = func name,
    'C' (compiler) or raises Fail. sec='.data': one region 'data' (no late items); data items the
    C code names (externs) also get labels (returned in plan.labels)."""
    base = 'data' if sec == '.data' else 'rodata'
    late_kinds = set() if sec == '.data' else LATE_KINDS
    cpath = os.path.join(ROOT, 'src_eu', stem + '.c')
    src = open(cpath).read()
    pragmas = re.findall(r'#pragma GLOBAL_ASM\("([^"]+)"\)', src)
    if not pragmas:
        return None, []
    funcs = []  # (start, end, name, spath)
    for p in pragmas:
        sp = os.path.join(ROOT, p)
        if not os.path.exists(sp):
            raise Fail('%s: missing %s (split first)' % (stem, p))
        lo, hi = asm_range(sp)
        funcs.append((lo, hi, os.path.basename(p)[:-2], sp))
    funcs.sort()
    files = DR.code_files(seg)
    fi = [f[2] for f in files].index(stem)
    segd = DR.segments()[seg]
    t0 = segd['vram'] + files[fi][0] - segd['start']
    t1 = segd['vram'] + files[fi][1] - segd['start']
    dv = dseg['vram'] - dseg['start']
    va, vb = a + dv, b + dv

    def owner(pc):
        for lo, hi, n, _ in funcs:
            if lo <= pc < hi:
                return (lo, n)
        return (pc, 'C')

    # extern names used by the C code (pragma lines removed)
    csrc = re.sub(r'#pragma GLOBAL_ASM\([^)]*\)', '', src)
    named = set()
    for ident in set(re.findall(r'\b[A-Za-z_]\w*\b', csrc)):
        if ident in names and va <= names[ident] < vb:
            named.add(names[ident])

    # data the C file defines itself (a file-scope `name[] = ...` / `name = ...` line, not extern)
    cdefined = set()
    for ident in (named_ids(csrc, names, va, vb) if sec == ".data" else []):
        if re.search(r'^(?!extern|typedef)\w[^\n;]*\b%s\b[^\n;]*=' % ident, csrc, re.M):
            cdefined.add(names[ident])
    items = {}  # vram -> dict(owner=(key,name), kinds=set, ext=bool)
    for t, k, f, st, pc in allrefs:
        if not (va <= t < vb):
            continue
        it = items.setdefault(t, {'owner': None, 'kinds': set(), 'other': False})
        if st == stem and t0 <= pc < t1:
            o = owner(pc)
            it['kinds'].add(k)
            if it['owner'] is None or o[0] < it['owner'][0]:
                it['owner'] = o
        else:
            it['other'] = True
    for t in named:
        items.setdefault(t, {'owner': None, 'kinds': set(), 'other': False})
    plan.labels = {names[i] - dv: i for i in set(re.findall(r'\b[A-Za-z_]\w*\b', csrc))
                   if i in names and va <= names[i] < vb} if sec == '.data' else {}
    if not items:
        raise Fail('%s: no references into 0x%X-0x%X' % (stem, a, b))
    addrs = sorted(items)

    def word(v):
        r = v - dv
        return struct.unpack('>I', data[r:r + 4])[0]

    # end of the last item
    last = addrs[-1]
    ks = items[last]['kinds']
    if 'jtbl' in ks:
        e = last
        while e < vb and t0 <= word(e) < t1:
            e += 4
    elif 'ldc1' in ks:
        e = last + 8
    elif 'lwc1' in ks or 'lw' in ks:
        e = last + 4
    else:  # string / table: up to the trailing zero padding, word aligned
        e = vb
        while e > last + 1 and data[e - 1 - dv] == 0:
            e -= 1
        e = (e + 3) & ~3
    tail = data[e - dv:b]
    if any(tail):
        raise Fail('%s: nonzero bytes after the last item (0x%X-0x%X)' % (stem, e - dv, b))
    # a literal item ends after its own size; words between it and the next item are unreferenced
    # (they become their own owner-less items, resolved onto a GLOBAL_ASM neighbour below)
    for i, t in enumerate(list(addrs)):
        ks = items[t]['kinds']
        if ks and ks <= {'lwc1', 'ldc1'} and base == 'rodata':
            size = 8 if 'ldc1' in ks else 4
            nxt = addrs[i + 1] if i + 1 < len(addrs) else e
            if t + size < nxt:
                items[t + size] = {'owner': None, 'kinds': set(), 'other': False}
    # explicit item sizes from the C source, for compiler-owned data whose end cannot be told from
    # the references (e.g. a const local array followed by an unreferenced table):
    #   // rodata_inject: size <rom addr> <bytes>
    for ra, sz in re.findall(r'rodata_inject: size (0x[0-9A-Fa-f]+) (0x[0-9A-Fa-f]+|\d+)', src):
        t = int(ra, 16) + dv + int(sz, 0)
        if va <= t < e and t not in items:
            items[t] = {'owner': None, 'kinds': set(), 'other': False}
    addrs = sorted(items)
    bounds = addrs + [e]
    if addrs[0] > va:
        bounds[0] = va  # leading unreferenced bytes go with the first item
    lates = [t for t in addrs if items[t]['kinds'] & late_kinds]
    L = lates[0] if lates else e
    chunks = []
    for i, t in enumerate(addrs):
        it = items[t]
        reg = 'late' if t >= L else base
        o = it['owner']
        if t in cdefined:
            name, o = 'C', (o[0] if o else t, 'C')
        elif o is not None and o[1] == 'C':
            name = 'CX' if t in named else 'C'
        elif o is not None:
            name = o[1]
        else:
            name = None
        s, en = bounds[i], bounds[i + 1]
        if chunks and chunks[-1][3] == name and chunks[-1][2] == reg and chunks[-1][4] == (o[0] if o else None):
            chunks[-1][1] = en
        else:
            chunks.append([s, en, reg, name, o[0] if o else None])
    asmnames = {n for _, _, n, _ in funcs}
    # strings/const data: only the compiler's own items (strings of C functions) are fixed; every
    # other run between two of them goes, in address order, into one GLOBAL_ASM function placed
    # between those C functions (file-scope const tables need not follow function order)
    reg_chunks = [c for c in chunks if c[2] == base]
    late_chunks = [c for c in chunks if c[2] == 'late']
    newreg = []
    run = []

    def flush(klo, khi):
        if not run:
            return
        cands = [(lo, n) for lo, hi, n, _ in funcs if klo < lo < khi]
        if not cands:
            raise Fail('%s: %s 0x%X-0x%X has no GLOBAL_ASM function between its C '
                       'neighbours; define it in C' % (stem, sec, run[0][0] - dv, run[-1][1] - dv))
        pref = [x for x in cands if x[1] in {c[3] for c in run}]
        lo, n = (pref or cands)[0]
        newreg.append([run[0][0], run[-1][1], base, n, lo])
        del run[:]
    klo = -1
    for c in reg_chunks:
        if c[3] == 'C':
            flush(klo, c[4])
            newreg.append(c)
            klo = c[4]
        else:
            run.append(c)
    flush(klo, 1 << 40)
    chunks = newreg + late_chunks
    # late items: resolve extern-named / unreferenced chunks onto a neighbouring GLOBAL_ASM chunk
    changed = True
    while changed:
        changed = False
        for i, c in enumerate(chunks):
            if c[3] in ('CX', None):
                for j in (i - 1, i + 1):
                    if 0 <= j < len(chunks) and chunks[j][3] in asmnames and chunks[j][2] == c[2]:
                        c[3], c[4] = chunks[j][3], chunks[j][4]
                        changed = True
                        break
                else:
                    if c[3] is None and i > 0 and chunks[i - 1][3] is not None and chunks[i - 1][2] == c[2]:
                        c[3], c[4] = chunks[i - 1][3], chunks[i - 1][4]  # padding/unused after a C item
                        changed = True
        merged = []
        for c in chunks:
            if merged and merged[-1][3] == c[3] and merged[-1][2] == c[2] and merged[-1][1] == c[0]:
                merged[-1][1] = c[1]
            else:
                merged.append(c)
        chunks = merged
    for c in chunks:
        if c[3] in ('CX', None):
            raise Fail('%s: 0x%X-0x%X (%s) is named by C code or unreferenced and has no '
                       'GLOBAL_ASM neighbour; define it in C' % (stem, c[0] - dv, c[1] - dv, c[2]))
    # order check: owners must follow file order within each region, one chunk per asm function
    for reg in (base, 'late'):
        seen = set()
        prev = -1
        for c in chunks:
            if c[2] != reg:
                continue
            if c[4] is not None and c[4] < prev:
                raise Fail('%s: %s chunk 0x%X of %s is out of function order' % (stem, reg, c[0] - dv, c[3]))
            prev = c[4] if c[4] is not None else prev
            if c[3] in asmnames:
                if c[3] in seen:
                    raise Fail('%s: %s has two separate %s chunks' % (stem, c[3], reg))
                seen.add(c[3])
    return funcs, [(c[0] - dv, c[1] - dv, c[2], c[3]) for c in chunks]


def symbols_at(funcs, names, dv):
    """{rom addr: name} of the data symbols the GLOBAL_ASM functions use (labels for them are
    emitted with the bytes, since splat leaves symbols inside an owned .rodata undefined)."""
    out = {}
    for _, _, n, sp in funcs:
        for nm in set(re.findall(r'%(?:lo|hi)\((\w+)\)', open(sp).read())):
            m = re.match(r'(?:D|jtbl)_([0-9A-F]{8})(?:_\w+)?$', nm)
            va = int(m.group(1), 16) if m else names.get(nm)
            if va is not None:
                out.setdefault(va - dv, nm)
    return out


def emit(funcs, chunks, data, labels={}):
    byname = {n: sp for _, _, n, sp in funcs}
    per = {}
    for a, b, reg, n in chunks:
        if n in byname:
            per.setdefault(n, []).append((a, b, reg))
    for n, sp in byname.items():
        body = open(sp).read()
        if body.startswith(MARK):
            body = body.split(MARK + ' end\n', 1)[1]
            if n not in per:
                open(sp, 'w').write(body)  # stale block from an earlier plan
        if n not in per:
            continue
        cs = per[n]
        out = [MARK]
        for a, b, reg in cs:
            out.append('.section .%s' % {'late': 'late_rodata'}.get(reg, reg))
            r = a
            while r < b:
                if r in labels:
                    out.append('glabel %s' % labels[r])
                if r % 4 == 0 and r + 4 <= b:
                    ws = []
                    while r % 4 == 0 and r + 4 <= b and len(ws) < 4 and (not ws or r not in labels):
                        ws.append('0x%08X' % struct.unpack('>I', data[r:r + 4])[0])
                        r += 4
                    out.append('.word ' + ', '.join(ws))
                else:
                    out.append('.byte 0x%02X' % data[r])
                    r += 1
        out.append('.text')
        out.append(MARK + ' end')
        open(sp, 'w').write('\n'.join(out) + '\n' + body)
    return per


def main():
    args = [x for x in sys.argv[1:] if not x.startswith('--')]
    dry = '--dry' in sys.argv
    data = open(DR.BIN, 'rb').read()
    names = sym_addrs()
    refcache = {}
    bad = 0
    todo = {}
    for seg, stem, a, b, dseg, sec in owned_files(('.rodata', '.data')):
        if args and stem not in args:
            continue
        if seg not in refcache:
            refcache[seg] = DR.refs(seg)
        try:
            funcs, chunks = plan(seg, stem, a, b, dseg, refcache[seg], data, names, sec)
        except Fail as e:
            print('rodata_inject: FAIL', e)
            bad = 1
            continue
        if funcs is None:
            continue
        dv = dseg['vram'] - dseg['start']
        t = todo.setdefault(stem, [funcs, [], {}])
        t[1] += chunks
        t[2].update(symbols_at(funcs, names, dv))
        t[2].update(plan.labels)
    for stem, (funcs, chunks, labels) in todo.items():
        if dry:
            for c in chunks:
                print('%-30s 0x%06X-0x%06X %-6s %s' % (stem, c[0], c[1], c[2], c[3]))
            continue
        per = emit(funcs, chunks, data, labels)
        print('rodata_inject: %s: %d chunks, %d asm functions' % (stem, len(chunks), len(per)))
    sys.exit(bad)


if __name__ == '__main__':
    main()
