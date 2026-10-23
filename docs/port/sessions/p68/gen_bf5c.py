# setups for func_1506BF5C (EU addresses from port_work/p68_sym.sh)
import struct
def h(f): return struct.unpack('>I', struct.pack('>f', f))[0]
O=0x80420000; DESC=0x80430000; ALIAS=0x80440000; CAM=0x80450000
def line(n, cmd, oid=5, alias=0, atype=9, players=1, surf=3, cc=0, f118=-10000.0, y=0.0, cam=0, camv=5.0, yv=12.0, sndret=0x55, pl=0x42):
    pk = {0x800D196C: O, 0x800D19A0: cmd, 0x800D20B0 + 4 * oid: DESC, DESC + 4: (alias << 24) | (2 << 16),
          0x8008704C + 8: ALIAS, ALIAS: atype << 24, O + 4: oid << 24, 0x80083330: players, 0x800D1C9C: 0x5A5A5A5A,
          O + 0x184: 0x77, O + 0xCC: (cc & 0xFFFF) << 16, O + 0x118: h(f118), O + 0x18: h(y), O + 0x31C: CAM if cam else 0,
          CAM: h(camv), O + 0x20: h(yv), O + 0x8C: 0x1234}
    ret = f"1510FE4C={surf:X},100121A8={sndret:X},1000F858=66,1001176C={pl:X}"
    # u16 volume out-param of func_10011EB8: bytes (a word would also hit the next stack slot), only when
    # the call gets &volume (not the in-air call with NULL)
    path3 = (cmd & 0x3800) == 0x2000 and not (surf == 12 and cc > -17) and (f118 == -10000.0 or y > f118)
    outb = "100121A8=1:40;00" if path3 else ""
    return f"{n} ! ! " + ",".join(f"{a:X}={v:08X}" for a, v in pk.items()) + f" ! {ret} ! ! ! ! {outb}"
i = 0
def P(**k):
    global i; print(line(f"f{i}", **k)); i += 1
for cond in [0, 0x4000, 0x8000, 0xC000]:
    for want in [5, 9, 6]:
        for alias in [0, 1]:
            P(cmd=(want << 24) | cond | 0x0123, alias=alias)
P(cmd=0x00010123); P(cmd=0x05014123)
for mode in range(0, 0x4000, 0x800):
    P(cmd=0x0123 | mode)
    P(cmd=0x07FF | mode, pl=0x7FF)
for players in [1, 2]:
    for surf in [3, 12, 8]:
        for cc in [0, -17, -18, 5]:
            for f118, y in [(-10000.0, 0.0), (5.0, 5.0), (5.0, 4.0), (4.0, 5.0)]:
                P(cmd=0x2123, players=players, surf=surf, cc=cc, f118=f118, y=y)
for cam, camv, yv in [(1, 5.0, 0.0), (1, -3.0, 0.0), (1, 40.0, 0.0), (0, 0.0, 11.0), (0, 0.0, 9.0), (0, 0.0, -1.0), (0, 0.0, 31.0)]:
    for surf, f118 in [(3, -10000.0), (12, -10000.0), (3, 5.0)]:
        P(cmd=0x2123, surf=surf, cam=cam, camv=camv, yv=yv, f118=f118, y=6.0)
P(cmd=0x2123, sndret=0); P(cmd=0x2123, sndret=0, surf=3, f118=5.0, y=6.0); P(cmd=0x2123, surf=3, f118=5.0, y=4.0, sndret=0)
P(cmd=0x2123, surf=3, f118=-10000.0, y=-20000.0); P(cmd=0x2123, surf=12, cc=-30, f118=-10000.0, y=-20000.0)
