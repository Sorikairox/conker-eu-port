#!/usr/bin/env python3
"""Expected values for the P25 libgu self-test (port/boot/gu_test.c), computed from the N64 definitions.

usage: python3 port/tools/gu_expect.py > port/stubs/gutest_expect.h

Every float operation is rounded to IEEE single after each step (f32()), which reproduces the R4300's
single-precision results exactly for + - * / (double has more than 2p+2 bits). Conversions follow the
game: guMtxF2L uses cvt.w.s with round-to-nearest-even; the game's sinf/cosf use the libultra
polynomial with ROUND(d) = (int)(d +- 0.5f)."""
import math, struct

def f32(x): return struct.unpack('<f', struct.pack('<f', x))[0]
def bits(x): return struct.unpack('<I', struct.pack('<f', x))[0]
def fromb(u): return struct.unpack('<f', struct.pack('<I', u))[0]
def trunc(x): return int(x)  # C (int) cast

P = [fromb(u) for u in (0x3F800000, 0xBE2AAAA6, 0x3C088769, 0xB94FB7FD, 0x362EDEFA)]
RPI, PIHI, PILO = fromb(0x3EA2F984), fromb(0x40490FDC), fromb(0x330885A3)

def poly(xsq):
    p = f32(P[4] * xsq); p = f32(p + P[3]); p = f32(p * xsq); p = f32(p + P[2]); p = f32(p * xsq)
    return f32(p + P[1])

def rnd(d): return trunc(f32(d + 0.5)) if d >= 0 else trunc(f32(d - 0.5))

def sinf(x):
    x = f32(x); xpt = (bits(x) >> 22) & 0x1FF
    if xpt < 0xFF:
        if xpt >= 0xE6:
            xsq = f32(x * x); return f32(x + f32(f32(x * xsq) * poly(xsq)))
        return x
    if xpt < 0x136:
        dn = f32(x * RPI); n = rnd(dn); dn = f32(n)
        dx = f32(x - f32(dn * PIHI)); dx = f32(dx - f32(dn * PILO))
        xsq = f32(dx * dx); r = f32(dx + f32(f32(dx * xsq) * poly(xsq)))
        return -r if n & 1 else r
    return 0.0

def cosf(x):
    x = f32(x); xpt = (bits(x) >> 22) & 0x1FF
    if xpt < 0x136:
        a = abs(x); dn = f32(f32(a * RPI) + 0.5); n = rnd(dn); dn = f32(f32(n) - 0.5)
        dx = f32(a - f32(dn * PIHI)); dx = f32(dx - f32(dn * PILO))
        xsq = f32(dx * dx); r = f32(dx + f32(f32(dx * xsq) * poly(xsq)))
        return -r if n & 1 else r
    return 0.0

def cvt_w(x):  # cvt.w.s, RM = nearest even
    return int(round(x)) & 0xFFFFFFFF  # Python round() is half-to-even

def f2l(mf):
    out = [0] * 16
    for k in range(8):
        e1 = cvt_w(f32(mf[2 * k] * 65536.0)); e2 = cvt_w(f32(mf[2 * k + 1] * 65536.0))
        out[k] = (e1 & 0xFFFF0000) | (e2 >> 16)
        out[k + 8] = ((e1 << 16) & 0xFFFF0000) | (e2 & 0xFFFF)
    return out

def l2f(m):
    out = []
    for k in range(8):
        ai, af = m[k], m[k + 8]
        e1 = (ai & 0xFFFF0000) | (af >> 16); e2 = ((ai << 16) & 0xFFFF0000) | (af & 0xFFFF)
        for e in (e1, e2):
            q = e - (1 << 32) if e & 0x80000000 else e
            assert float(f32(q)) == q, f'0x{e:08X} is not exact in single precision (round trip test)'
            out.append(f32(f32(q) / 65536.0))
    return out

def perspective(fovy, aspect, near, far, scale):
    """the game's guPerspectiveF (conker/src_eu/libultra/gu/guPerspectiveF.c)"""
    mf = [[1.0 if i == j else 0.0 for j in range(4)] for i in range(4)]
    k = fromb(bits(0.008726646192371845))
    aspect = f32(aspect * k); mf[0][0] = f32(cosf(aspect) / sinf(aspect))
    fovy = f32(fovy * k); mf[1][1] = f32(cosf(fovy) / sinf(fovy))
    nf, d = f32(near + far), f32(near - far)
    mf[2][2] = f32(nf / d); mf[2][3] = -1.0
    mf[3][2] = f32(f32(f32(2.0 * near) * far) / d); mf[3][3] = 0.0
    flat = [f32(mf[r][c] * scale) for r in range(4) for c in range(4)]
    pn = 0xFFFF if nf <= 2.0 else (trunc(f32(131072.0 / nf)) & 0xFFFF)
    return flat, pn

def lookat(e, a, up):
    """guLookAtF, N64 definition (gu.h: view matrix, row vectors), in single precision"""
    ex, ey, ez = map(f32, e); ax, ay, az = map(f32, a); ux, uy, uz = map(f32, up)
    lx, ly, lz = f32(ax - ex), f32(ay - ey), f32(az - ez)
    n = f32(-1.0 / f32(math.sqrt(f32(f32(f32(lx * lx) + f32(ly * ly)) + f32(lz * lz)))))
    lx, ly, lz = f32(lx * n), f32(ly * n), f32(lz * n)
    rx = f32(f32(uy * lz) - f32(uz * ly)); ry = f32(f32(uz * lx) - f32(ux * lz)); rz = f32(f32(ux * ly) - f32(uy * lx))
    n = f32(1.0 / f32(math.sqrt(f32(f32(f32(rx * rx) + f32(ry * ry)) + f32(rz * rz)))))
    rx, ry, rz = f32(rx * n), f32(ry * n), f32(rz * n)
    ux = f32(f32(ly * rz) - f32(lz * ry)); uy = f32(f32(lz * rx) - f32(lx * rz)); uz = f32(f32(lx * ry) - f32(ly * rx))
    n = f32(1.0 / f32(math.sqrt(f32(f32(f32(ux * ux) + f32(uy * uy)) + f32(uz * uz)))))
    ux, uy, uz = f32(ux * n), f32(uy * n), f32(uz * n)
    dot = lambda p, q, r: f32(f32(f32(p * ex) + f32(q * ey)) + f32(r * ez))
    return [rx, ux, lx, 0.0, ry, uy, ly, 0.0, rz, uz, lz, 0.0,
            f32(-dot(rx, ry, rz)), f32(-dot(ux, uy, uz)), f32(-dot(lx, ly, lz)), 1.0]

def carr(name, typ, vals, fmt):
    return f'static const {typ} {name}[{len(vals)}] = {{' + ', '.join(fmt(v) for v in vals) + '};'

def fl(v): return f'{v!r}f' if v == v else '0.0f'

h = lambda v: f'0x{v:08X}'
F2L_IN = [1.0, -1.0, 0.5, 100.25, 1.5 / 65536, 2.5 / 65536, -1.5 / 65536, -2.5 / 65536,
          -32768.0, 32767.5, 0.0, -0.0, 3.14159265, -2.71828, 1234.5678, -0.0000076]
F2L_IN = [f32(x) for x in F2L_IN]
L2F_IN = [0x00010002, 0xFFFF7FFF, 0x00000000, 0x00120000, 0x0000FFFF, 0x007FFF80, 0x00010001, 0x00640000,
          0x80000000, 0x0000C000, 0x12345678, 0xFFFF0001, 0x40008000, 0xFFFFFFFF, 0x00000000, 0x80000000]
PERSP, PNORM = perspective(45.0, 60.0, 10.0, 10000.0, 1.0)
LOOK = lookat((100.0, 50.0, -200.0), (0.0, 25.0, 0.0), (0.0, 1.0, 0.0))
COS_IN = [f32(x) for x in (0.0, 0.5, 1.0, -1.0, 1.5707964, 3.0, -3.0, 10.0, 100.0, 0.001)]

print('/* GENERATED by port/tools/gu_expect.py - do not edit. P25 libgu self-test expectations. */')
print(carr('gu_f2l_in', 'float', F2L_IN, fl))
print(carr('gu_f2l_want', 'unsigned', f2l(F2L_IN), h))
print(carr('gu_l2f_in', 'unsigned', L2F_IN, h))
print(carr('gu_l2f_want', 'unsigned', [bits(v) for v in l2f(L2F_IN)], h))
print(carr('gu_persp_want', 'unsigned', f2l(PERSP), h))
print(f'#define GU_PERSP_NORM 0x{PNORM:04X}')
print(carr('gu_persp_float', 'unsigned', [bits(v) for v in PERSP], h))
print(carr('gu_look_in', 'unsigned', [bits(v) for v in LOOK], h))
print(carr('gu_look_want', 'unsigned', f2l(LOOK), h))
print(carr('gu_cos_in', 'float', COS_IN, fl))
print(carr('gu_cos_want', 'unsigned', [bits(cosf(x)) for x in COS_IN], h))
