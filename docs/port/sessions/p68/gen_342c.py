# setups for func_1507342C (EU: D_800D154C = 0x800D196C, D_800D1580 = 0x800D19A0, D_800CC2D0 = 0x800CC6F0,
# func_15037988 = 0x15037988, func_150ADA20 = 0x150ADF00, func_15073118 = 0x150734D8, func_150484A0 = 0x15048790)
import struct
def h(f): return struct.unpack('>I', struct.pack('>f', f))[0]
CAM=0x80450000; SHOT=0x80460000
def line(n, cmd, slot=3, near=1, rnd=(150, 7, 33), ang=1.0, e2e4=50, xz=8.0, camxyz=(100.0, 20.0, -40.0)):
    O = 0x800CC6F0 + slot * 0x32C
    pk = {0x800D196C: O, 0x800D19A0: cmd, O + 0x318: CAM, O + 0x2E4: e2e4, CAM + 0x2F8: h(camxyz[0]), CAM + 0x2FC: h(camxyz[1]),
          CAM + 0x300: h(camxyz[2]), SHOT + 0x14: h(10.0), SHOT + 0x18: h(5.0), SHOT + 0x1C: h(-3.0), SHOT + 0x3C: h(xz),
          SHOT + 0xF8: 0x00000011, SHOT + 0x2E4: 0x77}
    ret = f"15037988={near:X},150ADF00=" + ";".join(f"{r:X}" for r in rnd) + f",150734D8={SHOT:X}"
    rf = f"15048790={h(ang):X}"
    return f"{n} ! ! " + ",".join(f"{a:X}={v:08X}" for a, v in pk.items()) + f" ! {ret} ! {rf} ! ! !"
i = 0
def P(**k):
    global i; print(line(f"s{i}", **k)); i += 1
for cmd in [0, 1, 2, 3, 4, 0xFFFFFFFF]:
    for rnd in [(150, 7, 33), (199, 39, 0), (200, 20, 19), (1199, 1000, 61), (0xFFFFFFFF, 0x80000000, 21)]:
        P(cmd=cmd, rnd=rnd)
for slot in [0, 1, 25]:
    for near in [0, 1]:
        P(cmd=0, slot=slot, near=near)
for ang in [0.5, 3.14159, 3.15, 6.0, -1.0, 0.0]:
    for xz in [8.0, 0.0]:
        P(cmd=0, ang=ang, xz=xz, rnd=(5,))
for e2e4 in [0, 100, -50]:
    P(cmd=1, e2e4=e2e4)
P(cmd=0, rnd=(5,), camxyz=(10.0, 5.0, -3.0))
