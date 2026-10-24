#!/usr/bin/env python3
# P211: every event-script native-6 call (D_80088874 dispatch) whose id word has nibble 0xF (= func_1509E3D4, the rail
# commands) in the EU ROM's event blocks; prints block, pc, rail command number (args[1]) and whether a later
# instruction reads the result register (operand mode 5) before the next call / return (linear walk).
# usage: railcmds.py ROM   (uses p106/evasset.py's loader)
import sys, struct, collections
import os; sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'p106'))
import evasset
CNTS = evasset.CNTS
def ops(b):
    end = struct.unpack_from('>H', b, 8)[0] or len(b); pc = 0x20; out = []
    while pc + 2 <= min(end, len(b)):
        op = struct.unpack_from('>H', b, pc)[0]; at = pc; pc += 2
        o = op & 0x3F; c = CNTS[o]
        if c == 0 or o == 0 or o >= 0x1F: break
        lng = (op >> 6) & 1; opd = []
        for k, sh in enumerate((13, 10, 7)[:c - 1]):
            m = (op >> sh) & 7
            if m in (3, 4, 6) and lng: v = struct.unpack_from('>I', b, pc)[0]; pc += 4; lng = 0
            else: v = struct.unpack_from('>H', b, pc)[0]; pc += 2
            opd.append((m, v))
        out.append((at, o, opd))
    return out
def follow(L, n, depth, seen=None):
    """P211: does an instruction read the result register (mode 5) before the next call / return? Jumps (0F) and
    conditional jumps (10 / 11, both ways) are followed (code offsets are mode-4 operands)."""
    seen = set() if seen is None else seen
    pos = {at: k for k, (at, o, opd) in enumerate(L)}
    while n < len(L) and depth < 8:
        at2, o2, opd2 = L[n]
        if at2 in seen: return 'unused (loop)'
        seen.add(at2)
        if any(m == 5 for m, v in opd2): return 'READ at %X op%02X' % (at2, o2)
        if o2 == 0x1C and depth < 6:
            # P211: a plain return keeps the result register: follow every script call of the function that holds it
            calls = [(k, opd[0][1]) for k, (a, o, opd) in enumerate(L) if o == 0x19 and opd and opd[0][0] != 6]
            starts = sorted({t for k, t in calls if t <= at2})
            if not starts: return 'unused (return from an entry)'
            fs = starts[-1]; rs = []
            for k, t in calls:
                if t == fs:
                    rs.append(follow(L, k + 1, depth + 1, seen))
                    if rs[-1].startswith('READ'): return rs[-1] + ' (after return to %X)' % L[k][0]
            return 'unused (returns to %d callers)' % len(rs)
        if o2 in (0x19, 0x1A, 0x1C): return 'unused (next op%02X at %X)' % (o2, at2)
        if o2 in (0x0F, 0x10, 0x11):
            t = [v for m, v in opd2 if m in (3, 4)]
            tt = [x for x in ((t[-1], t[-1] + 0x20) if t else ()) if x in pos]
            if tt:
                r = follow(L, pos[tt[0]], depth + 1, seen)
                if r.startswith('READ') or o2 == 0x0F: return r
            elif o2 == 0x0F: return 'unknown jump at %X to %s' % (at2, opd2)
        n += 1
    return 'unused (end)'
res = collections.Counter()
for i in range(0x400):
    try: b = evasset.load(i)
    except Exception: b = None
    if not b: continue
    L = ops(b); pushes = []
    for n, (at, o, opd) in enumerate(L):
        if o == 0x18: pushes.append(opd[0] if opd else None); continue
        if o == 0x19 and opd and opd[0][0] == 6:
            nat = opd[0][1]
            if nat == 6 and pushes and pushes[-1] and pushes[-1][0] in (3, 4) and (pushes[-1][1] >> 12) & 0xF == 0xF:
                cmd = pushes[-2] if len(pushes) > 1 else None
                use = follow(L, n + 1, 0)
                c = cmd[1] if cmd and cmd[0] in (3, 4) else cmd
                print('block %03X pc %04X id %04X cmd %s %s' % (i, at, pushes[-1][1], c, use))
                res[(c, use.split()[0])] += 1
            pushes = []
        elif o in (0x19, 0x1A, 0x1C, 0x0F, 0x10, 0x11): pushes = []
print(sorted(res.items(), key=str))
