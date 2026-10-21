"""Minimal reader for wasm relocatable objects (clang -c output): symbol table + function import types."""
import struct

VT = {0x7f: 'i32', 0x7e: 'i64', 0x7d: 'f32', 0x7c: 'f64', 0x7b: 'v128', 0x70: 'funcref', 0x6f: 'externref'}
SYM_FUNC, SYM_DATA, SYM_GLOBAL, SYM_SECTION, SYM_TAG, SYM_TABLE = range(6)
WEAK, LOCAL, UNDEF, EXPLICIT = 0x1, 0x2, 0x10, 0x40


class R:
    def __init__(self, b, p=0):
        self.b, self.p = b, p

    def u8(self):
        v = self.b[self.p]; self.p += 1; return v

    def leb(self):
        r = s = 0
        while True:
            x = self.u8(); r |= (x & 0x7f) << s; s += 7
            if not x & 0x80:
                return r

    def str(self):
        n = self.leb(); v = self.b[self.p:self.p + n].decode(); self.p += n; return v


def read(path):
    """-> list of (name, kind, flags, sig) ; sig = (params tuple, results tuple) for functions."""
    b = open(path, 'rb').read()
    assert b[:4] == b'\0asm', path
    p = 8
    types, fimports, syms = [], [], []
    while p < len(b):
        sid = b[p]; r = R(b, p + 1); size = r.leb(); start = r.p; end = start + size; p = end
        if sid == 1:
            for _ in range(r.leb()):
                assert r.u8() == 0x60
                ps = tuple(VT.get(r.u8(), '?') for _ in range(r.leb()))
                rs = tuple(VT.get(r.u8(), '?') for _ in range(r.leb()))
                types.append((ps, rs))
        elif sid == 2:
            for _ in range(r.leb()):
                mod, field, kind = r.str(), r.str(), r.u8()
                if kind == 0:
                    fimports.append((field, r.leb()))
                elif kind == 1:
                    r.u8(); fl = r.u8(); r.leb(); fl & 1 and r.leb()
                elif kind == 2:
                    fl = r.u8(); r.leb(); fl & 1 and r.leb()
                elif kind == 3:
                    r.u8(); r.u8()
                elif kind == 4:
                    r.u8(); r.leb()
        elif sid == 0:
            name = r.str()
            if name != 'linking':
                continue
            r.leb()  # version
            while r.p < end:
                st = r.u8(); ln = r.leb(); nxt = r.p + ln
                if st == 8:
                    for _ in range(r.leb()):
                        kind = r.u8(); flags = r.leb()
                        if kind in (SYM_FUNC, SYM_GLOBAL, SYM_TAG, SYM_TABLE):
                            idx = r.leb()
                            if not (flags & UNDEF) or (flags & EXPLICIT):
                                nm = r.str()
                            else:
                                nm = fimports[idx][0] if kind == SYM_FUNC and idx < len(fimports) else None
                            sig = None
                            if kind == SYM_FUNC and (flags & UNDEF) and idx < len(fimports):
                                sig = types[fimports[idx][1]]
                            syms.append((nm, kind, flags, sig))
                        elif kind == SYM_DATA:
                            nm = r.str()
                            if not flags & UNDEF:
                                r.leb(); r.leb(); r.leb()
                            syms.append((nm, kind, flags, None))
                        elif kind == SYM_SECTION:
                            r.leb()
                r.p = nxt
    return syms
