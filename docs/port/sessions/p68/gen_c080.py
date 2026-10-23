# setups for func_1512C080 (EU addresses: D_800BE9F0 = 0x800BEE10, func_151236D0 = 0x15123C40)
import struct
def h(f): return struct.unpack('>I', struct.pack('>f', f))[0]
C=0x80420000; T=0x80430000; F=0x80440000
def line(n, f84=0, t95=0, mode=0, f5f0=0, d374=100.0, lvl=0, b23e=0, view=0, f102=0, same=1, t1b3=0, b23c=0, hit=0, floor=-50.0):
    pk = {C+0x84: f84, C+0x3D4: T, C+0x3D0: F, T+0x94: t95 << 16, C+0x2C: mode, C+0x5F0: f5f0, C+0x374: h(d374),
          0x800BEE10: lvl, C+0x23C: (b23c << 24) | (7 << 16) | (b23e << 8), C+0x73C: view << 16, F+0x100: f102 << 8,
          C+0x2B0: h(5.0), C+0x2B8: h(6.0), F+0x14: h(5.0 if same else 5.5), F+0x1C: h(6.0 if same & 1 else 7.0),
          T+0x1B0: t1b3, C+0x2F8: h(1.0), C+0x2FC: h(2.0), C+0x300: h(3.0), C+0x18C: h(0.5), C+0x354: h(-1.0),
          C+0x37C: h(45.0), C+0x644: 0x12345, C+0x304: h(4.0), C+0x308: h(5.0), C+0x30C: h(6.0), C+0x26C: h(0.5),
          C+0x7B4: h(0.25), 0x800894C0: 0x00AABBCC, 0x800CC1F0: 0x0000EEFF, 0x800CC1F4: 0x77000000}
    ret = f"15044670={hit:X}"
    outw = f"1510EE3C=2:{h(floor):X}"
    return f"{n} ! 0={C:X} ! " + ",".join(f"{a:X}={v:08X}" for a, v in pk.items()) + f" ! {ret} ! ! ! {outw} !"
i = 0
def P(**k):
    global i; print(line(f"k{i}", **k)); i += 1
for f84 in [0x40000, 0x80, 0x200]: P(f84=f84)
P(t95=1); P(mode=0x40)
for b23c in [0, 1]:
    for hit in [0, 1]:
        for mode in [0, 0x100]:
            for f5f0 in [0x800, 0x10, 0]:
                P(f5f0=f5f0, b23c=b23c, hit=hit, mode=mode)
for d374 in [580.0, 581.0]: P(d374=d374)
for lvl, b23e in [(0x31, 3), (0x31, 2), (0x30, 3)]: P(lvl=lvl, b23e=b23e)
for view in [0, 1, 2, 3, 4, -1]:
    for f102 in [0, 1]:
        for same in [1, 0, 2]:
            for t1b3 in [0, 1]:
                P(view=view, f102=f102, same=same, t1b3=t1b3)
for f84 in [0x80000000, 0x10000, 0x80010000]: P(f84=f84)
for lvl in [0x37, 0x1B]:
    P(lvl=lvl, hit=1)
for mode, small_lvl in [(0x100, 0), (0x100, 1)]:
    P(mode=mode, lvl=0x31 if small_lvl else 0, b23e=3)
for floor in [-50.0, -38.0, -37.5, 10.0]:
    for f5f0 in [0, 0x800]:
        P(hit=1, floor=floor, f5f0=f5f0)
