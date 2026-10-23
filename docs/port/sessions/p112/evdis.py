#!/usr/bin/env python3
"""P112: event script disassembler (linear walk) + table-handler call census.
usage: evdis.py ROM ID        -> listing of block ID
       evdis.py ROM --census  -> every native 3..6 call whose id was pushed as an immediate: table, handler idx, id, block"""
import sys, struct, collections, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)) + '/../p106')
sys.argv_saved = sys.argv; rom = sys.argv[1]
import importlib.util
spec = importlib.util.spec_from_file_location('ev', os.path.dirname(os.path.abspath(__file__)) + '/../p106/evasset.py')
sys.argv = [sys.argv[0], rom, 'X']  # evasset reads argv[1]
ev = importlib.util.module_from_spec(spec)
try: spec.loader.exec_module(ev)
except Exception: pass
sys.argv = sys.argv_saved
CNTS = ev.CNTS
NAMES = {1:'add',2:'sub',3:'mul',4:'div',5:'mod',6:'neg',7:'lnot',8:'not',9:'and',0xA:'or',0xB:'xor',0xC:'sll',0xD:'sra',
 0xE:'mov',0xF:'jmp',0x10:'jz',0x11:'jnz',0x12:'lt',0x13:'gt',0x14:'le',0x15:'ge',0x16:'eq',0x17:'ne',0x18:'push',
 0x19:'call',0x1A:'retv',0x1B:'enter',0x1C:'ret',0x1D:'aload',0x1E:'astore'}
MN = ['fr','var','dat','imm','lab','res','nat','m7']
TAB = {3:'7C0',4:'7FC',5:'838',6:'874'}
def walk(b):
    end = struct.unpack_from('>H', b, 8)[0] or len(b)
    pc = 0x20; out = []
    while pc + 2 <= min(end, len(b)):
        op = struct.unpack_from('>H', b, pc)[0]; at = pc; pc += 2
        o = op & 0x3F; c = CNTS[o]
        if c == 0 or o == 0 or o >= 0x1F: out.append((at, '?%04X' % op, [])); break
        lng = (op >> 6) & 1; ops = []
        for k, sh in enumerate((13, 10, 7)[:c - 1]):
            m = (op >> sh) & 7
            if m in (3, 4, 6) and lng:
                v = struct.unpack_from('>I', b, pc)[0]; pc += 4; lng = 0
            else:
                v = struct.unpack_from('>h', b, pc)[0]; pc += 2
            ops.append((m, v))
        out.append((at, o, ops))
    return out
def fmt(ops): return ', '.join('%s:%X' % (MN[m], v & 0xFFFFFFFF) for m, v in ops)
if __name__ == '__main__':
    if sys.argv[2] == '--census':
        cen = collections.defaultdict(set)
        for i in range(0x400):
            try: b = ev.load(i)
            except Exception: b = None
            if not b: continue
            name = b[0x20:0x20]  # unknown
            ins = walk(b); last = None
            for at, o, ops in ins:
                if o == 0x18: last = ops[0]
                elif o == 0x19 and ops and ops[0][0] == 6 and ops[0][1] in TAB:
                    if last and last[0] in (3, 4):
                        idv = last[1] & 0xFFFFFFFF; n = (idv >> 12) & 0xF
                        cen[(TAB[ops[0][1]], n - 1)].add((i, idv))
                    else: cen[(TAB[ops[0][1]], 'dyn')].add((i, None))
        for k in sorted(cen, key=str):
            s = sorted(cen[k], key=str)
            print(k, len(s), ' '.join('%X:%s' % (i, '%X' % v if v is not None else '?') for i, v in s[:40]))
    elif sys.argv[2] != '--calls':
        b = ev.load(int(sys.argv[2], 16))
        print('hdr', ' '.join('%04X' % x for x in struct.unpack_from('>16H', b, 0)))
        for at, o, ops in walk(b):
            print('%04X %-6s %s' % (at, NAMES.get(o, o), fmt(ops)))
# --- P112: per-block handler summary: evdis.py ROM --calls ID ELF ASMLIST
def calls(b):
    ins = walk(b); last = None; res = []
    for at, o, ops in ins:
        if o == 0x19 and ops and ops[0][0] == 6:
            res.append((at, ops[0][1], last))
        if o == 0x18: last = ops[0]
    return res
if __name__ == '__main__' and sys.argv[2] == '--calls':
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from elfrd import Elf
    e = Elf(sys.argv[4]); asm = set(l.split('\t')[0] for l in open(sys.argv[5]) if '\t' in l)
    T = {3: 'D_800887C0', 4: 'D_800887FC', 5: 'D_80088838', 6: 'D_80088874'}
    seen = collections.Counter()
    for at, nat, last in calls(ev.load(int(sys.argv[3], 16))):
        if nat in T and last and last[0] in (3, 4):
            idv = last[1] & 0xFFFF; n = idv >> 12
            h = e.name(e.w(e.byname[T[nat]] + 4 * (n - 1))) if n else '-'
            seen[(nat, h, '%X' % idv)] += 1
        else:
            nm = e.name(e.w(e.byname['D_80088A44'] + 4 * nat)) if nat < 13 else '?'
            seen[(nat, nm if nat not in T else 'dyn', '' if nat not in T else 'top=%s' % (MN[last[0]] if last else '?'))] += 1
    for (nat, h, i), c in sorted(seen.items(), key=str):
        print('nat%-2d %-14s %-6s x%-3d %s' % (nat, h, i, c, 'ASM' if h in asm else ''))
