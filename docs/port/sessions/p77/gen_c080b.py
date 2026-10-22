# P77: setups for func_1512C080's 4 P73 survivors (from p68/gen_c080.py; adds y2fc, z-only difference, probe OUTA) (EU addresses: D_800BE9F0 = 0x800BEE10, func_151236D0 = 0x15123C40)
import struct
def h(f): return struct.unpack('>I', struct.pack('>f', f))[0]
C=0x80420000; T=0x80430000; F=0x80440000
def line(n, f84=0, t95=0, mode=0, f5f0=0, d374=100.0, lvl=0, b23e=0, view=0, f102=0, same=1, t1b3=0, b23c=0, hit=0, floor=-50.0, y2fc=2.0, outa=''):
    pk = {C+0x84: f84, C+0x3D4: T, C+0x3D0: F, T+0x94: t95 << 16, C+0x2C: mode, C+0x5F0: f5f0, C+0x374: h(d374),
          0x800BEE10: lvl, C+0x23C: (b23c << 24) | (7 << 16) | (b23e << 8), C+0x73C: view << 16, F+0x100: f102 << 8,
          C+0x2B0: h(5.0), C+0x2B8: h(6.0), F+0x14: h(5.0 if same in (1, 2) else 5.5), F+0x1C: h(6.0 if same in (1, 3) else 7.0),
          T+0x1B0: t1b3, C+0x2F8: h(1.0), C+0x2FC: h(y2fc), C+0x300: h(3.0), C+0x18C: h(0.5), C+0x354: h(-1.0),
          C+0x37C: h(45.0), C+0x644: 0x12345, C+0x304: h(4.0), C+0x308: h(5.0), C+0x30C: h(6.0), C+0x26C: h(0.5),
          C+0x7B4: h(0.25), 0x800894C0: 0x00AABBCC, 0x800CC1F0: 0x0000EEFF, 0x800CC1F4: 0x77000000}
    ret = f"15044670={hit:X}"
    outw = f"1510EE3C=2:{h(floor):X}"
    return f"{n} ! 0={C:X} ! " + ",".join(f"{a:X}={v:08X}" for a, v in pk.items()) + f" ! {ret} ! ! {outa} ! {outw} !"
i = 0
def P(**k):
    global i; print(line(f"q{i}", **k)); i += 1
# 1. +0x23E outside {2, 3} in level 0x31
for b23e in [0, 1, 5, 0xFF]: P(lvl=0x31, b23e=b23e)
# 2. followed moved in x only (+0x2B8 == followed+0x1C, +0x2B0 != followed+0x14)
for view in [0, 1, 3]:
    for t1b3 in [0, 1]: P(view=view, f102=1, same=3, t1b3=t1b3)
# 3. mode 0x100 with a probe whose y the collision call changed (func_15044670 writes probe x / y / z)
probe = lambda y: "15044670=3:" + ";".join(["0"] * 5 + [f"{h(1.25):X}", f"{h(y):X}", f"{h(3.5):X}"])
for f5f0 in [0, 0x800]:
    for hit in [0, 1]:
        for mode in [0x100, 0]:
            P(mode=mode, f5f0=f5f0, hit=hit, outa=probe(9.0))
# 4. eye exactly 40 above the floor: -0.0 vs +0.0
for y, fl in [(-0.0, -40.0), (0.0, -40.0), (2.0, -38.0)]:
    for f5f0 in [0, 0x800]: P(hit=1, y2fc=y, floor=fl, f5f0=f5f0)
