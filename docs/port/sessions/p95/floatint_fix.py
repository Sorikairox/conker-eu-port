#!/usr/bin/env python3
"""P95: apply the floatint_scan fixes (byte-identical by construction: matching code keeps its text under #else).

For each (file, callee, arg index): the TU prototype gets f32 at that index (in place when the prototype is already
only in the NON_MATCHING build, else an `#ifdef NON_MATCHING` copy); a callee without a TU prototype gets an NM-only
prototype before the enclosing function; each flagged call line has the literal replaced by the float literal
(in place inside NM blocks, else the line is duplicated under `#ifdef NON_MATCHING` / `#else`).
usage: floatint_fix.py [--dry]
"""
import os, re, sys, struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
REPO = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..', '..'))
SRC = os.path.join(REPO, 'conker', 'src_eu')
DRY = '--dry' in sys.argv

# file -> list of (callee, argidx, literal, proto-if-missing)
FIX = {
    'game_eu_103160.c': [('func_1514373C', 1, '0x3F800000', None), ('func_15154728', 2, '0x3FAFF1E9', None)],
    'game_161520.c': [('func_15139768', 2, '0x3F19999A', None), ('func_15139768', 2, '0x3F800000', None)],
    'game_eu_10CA50.c': [('func_15143874', 1, '0x41F00000', 'void func_15143874(s16, f32, f32 *, f32 *);')],
    'game_eu_10D650.c': [('func_151A2C9C', 3, '0x3F7CA4E3', None)],
    'game_eu_11F790.c': [('func_15143874', 1, '0x42C80000', None),
                         ('func_151D58E4', 1, '0x43FD0000', 'void func_151D58E4(void *, f32, f32, f32, u8, u8, s32);'),
                         ('func_151D58E4', 2, '0x447D4000', None), ('func_151D58E4', 3, '0x3A8163D3', None),
                         ('func_15154728', 2, '0x3FD20C49', None)],
    'game_eu_125200.c': [('func_15154728', 2, '0x3F030C35', None)],
    'game_eu_17A800.c': [('func_151AD010', 1, '0x41A00000', 'u8 *func_151AD010(u8 *, f32, s32);')],
    'game_eu_186A80.c': [('func_15046EF0', 2, '0x46985800', None)],
    'game_eu_1B8AA0.c': [('func_15046F70', 2, '0xC61C4000', 's32 func_15046F70(void *, u16, f32, void *);')],
    'game_eu_1D4CC0.c': [('func_151A2C9C', 3, '0x3F800000', None)],
    'game_eu_1DFE20.c': [('func_151B3660', 1, '0x3AC49BA6', 'u8 *func_151B3660(void *, f32, s32, u8, s32);')],
    'game_eu_1E61C0.c': [('func_151A2C9C', 3, '0x3F800000', None)],
    'game_eu_1E7CC0.c': [('func_151A2C9C', 3, '0x3F800000', None)],
    'game_eu_1EDA00.c': [('func_15154728', 2, '0x3F974EB9', None)],
    'game_eu_201240.c': [('func_15154728', 2, '0x3FD20C49', None)],
    'game_eu_5D910.c': [('func_1503F8A8', 3, '0x3F800000', None)],
    'game_eu_EBF20.c': [('func_15116A8C', 3, '0x43FA0000', None)],
    'game_eu_FCE60.c': [('func_151CFE48', 2, '0xC61C4000', None)],
    'libultra/audio/game_21FC90.c': [('func_1001CF38', 1, '0x46AC0800', None)],
}


def flit(h):
    v = int(h, 16)
    f = struct.unpack('>f', struct.pack('>I', v))[0]
    rt = lambda s: struct.unpack('>I', struct.pack('>f', float(s)))[0] == v
    s = next(('%.*f' % (d, f) for d in range(0, 14) if rt('%.*f' % (d, f))), None)
    if s is None or len(s) > 14:
        s = next('%.*g' % (n, f) for n in range(1, 18) if rt('%.*g' % (n, f)))
    if 'e' not in s and '.' not in s:
        s += '.0'
    return s + 'f'


def nm_flags(lines):
    """per line: True = only compiled with NON_MATCHING, False = compiled in both / matching only (ignored)."""
    res, stack = [], []
    for line in lines:
        s = line.strip()
        m = re.match(r'#\s*(ifdef|ifndef|if|else|endif)\b(.*)', s)
        if m:
            d, rest = m.group(1), m.group(2).strip()
            if d in ('ifdef', 'ifndef', 'if'):
                k = None
                if rest == 'NON_MATCHING' or re.fullmatch(r'defined\s*\(?\s*NON_MATCHING\s*\)?', rest):
                    k = (d != 'ifndef')
                stack.append(k)
            elif d == 'else' and stack and stack[-1] is not None:
                stack[-1] = not stack[-1]
            elif d == 'endif' and stack:
                stack.pop()
            res.append(None)
            continue
        res.append(True if any(x is True for x in stack) else (False if any(x is False for x in stack) else 'both'))
    return res


def split_top(s):
    parts, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([{':
            depth += 1
        elif ch in ')]}':
            depth -= 1
        if ch == ',' and depth == 0:
            parts.append(cur); cur = ''
        else:
            cur += ch
    parts.append(cur)
    return parts


def set_param(proto, callee, idx):
    m = re.search(re.escape(callee) + r'\s*\(', proto)
    i = m.end() - 1
    depth = 0
    for j in range(i, len(proto)):
        if proto[j] == '(':
            depth += 1
        elif proto[j] == ')':
            depth -= 1
            if depth == 0:
                break
    ps = split_top(proto[i + 1:j])
    old = ps[idx].strip()
    nm = re.match(r'.*?(\b\w+)\s*$', old)
    named = nm and nm.group(1) not in ('s32', 'u32', 'int', 'f32', 's16', 'u16', 'u8', 's8') and not old.endswith('*')
    ps[idx] = (' ' if idx else '') + ('f32 ' + nm.group(1) if named else 'f32')
    return proto[:i + 1] + ','.join(ps) + proto[j:]


for f, fixes in FIX.items():
    path = os.path.join(SRC, f)
    L = open(path).read().split('\n')
    flags = nm_flags(L)
    edits = {}      # line index -> list of replacement lines (already final)
    inserts = {}    # line index -> lines to insert before
    done_proto = set()
    inserted = set()
    for callee, idx, lit, newproto in fixes:
        if (callee, idx) not in done_proto:
            done_proto.add((callee, idx))
            pl = [i for i, x in enumerate(L) if re.match(r'\s*(extern\s+)?\w+\s*\**\s*' + callee + r'\s*\(.*\)\s*;', x)]
            if not pl and callee in inserted:
                pass
            elif not pl and not newproto:
                sys.exit('%s: no prototype for %s' % (f, callee))
            for i in pl:
                if flags[i] is False:
                    continue   # matching-only copy
                newl = set_param(L[i], callee, idx)
                if newl == L[i]:
                    continue
                if flags[i] is True:
                    edits[i] = [newl + ' /* P95: f32 (was the bit pattern as an int) */']
                else:
                    edits[i] = ['#ifdef NON_MATCHING', newl + ' /* P95: f32 parameter */', '#else', L[i], '#endif']
            if not pl and callee not in inserted:
                inserted.add(callee)
                first = min(i for i, x in enumerate(L) if re.search(r'\b' + callee + r'\s*\(', x))
                k = first
                while k > 0 and not re.match(r'^[A-Za-z_].*\)\s*\{\s*$', L[k]):
                    k -= 1
                inserts.setdefault(k, []).extend(['#ifdef NON_MATCHING', newproto + ' /* P95 */', '#endif'])
        # call lines
        hits = [i for i, x in enumerate(L) if re.search(r'\b' + callee + r'\s*\(', x) and lit in x
                and flags[i] is not False and not re.match(r'\s*(extern\s+)?\w+\s*\**\s*' + callee + r'\s*\(.*\)\s*;', x)]
        if not hits:
            sys.exit('%s: no call %s %s' % (f, callee, lit))
        for i in hits:
            cur = edits.get(i)
            base = cur[1] if cur and flags[i] != True else (cur[0] if cur else L[i])
            new = re.sub(r'\b' + lit + r'\b', flit(lit), base)
            if flags[i] is True:
                edits[i] = [new.rstrip() + ('' if 'P95' in new else ' /* P95: was %s as an int */' % lit)]
            else:
                edits[i] = ['#ifdef NON_MATCHING', new.rstrip() + ('' if 'P95' in new else ' /* P95: float literal (asm passes the bits %s) */' % lit), '#else', L[i], '#endif']
        # other calls of the callee: report their argument at idx
        for i, x in enumerate(L):
            for m in re.finditer(r'\b' + callee + r'\s*\(', x):
                if re.match(r'\s*(extern\s+)?\w+\s*\**\s*' + callee + r'\s*\(.*\)\s*;', x) or flags[i] is False:
                    continue
                a = split_top(x[m.end():])
                arg = a[idx].strip() if idx < len(a) else '?'
                print('  %s:%d %s arg%d = %s' % (f, i + 1, callee, idx, arg[:60]))
    out = []
    for i, x in enumerate(L):
        out.extend(inserts.get(i, []))
        out.extend(edits.get(i, [x]))
    print('%s: %d edits, %d inserts' % (f, len(edits), len(inserts)))
    for i in sorted(edits):
        for y in edits[i]:
            print('    + ' + y[:170])
    if not DRY:
        open(path, 'w').write('\n'.join(out))
