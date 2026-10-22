# setups for func_1509A024 (object query handler). EU addresses: func_1505EEF4 1505F2A0, func_1505A630 1505A9B0,
# func_15144BC8 15145138, func_1508712C / 150871B8 / 15086508 / 15087204 at their names, func_150ACEA0 150ACEA0,
# func_150A3674 150A3674, func_15031C4C 15031C4C, func_150A2FCC 150A2FCC, func_15084000 15084468,
# D_800D3C60 800D3C60, D_800CC2D0 800CC6F0, D_800D2104 800D2524, D_800D2528 800D2528, D_800D2778 800D2778,
# D_800D34B8 800D34B8, D_8008FD8C 8009012C.
import struct
def h(f): return struct.unpack('>I', struct.pack('>f', f))[0]
ARGS, OBJ, OTH, REC = 0x80420000, 0x80430000, 0x80440000, 0x80450000
cmds = list(range(0x91, 0xF4)) + [0x80, 0xF4]
def line(n, cmd, v):
    obj = {0: OBJ, 1: 0, 2: OBJ, 3: OBJ, 4: OBJ, 5: 0x800CCA1C}[v]
    oth = 0 if v == 2 else OTH
    a = [0, cmd, 1, 1, 0x20, 7, 9] if v in (0, 1, 5) else ([0, cmd, 0, 3, 5, 0, 0] if v == 2 else [0, cmd, 3, 2, 30, 6, 9])
    pk = {ARGS + 4 * i: x for i, x in enumerate(a)}
    pk.update({0x800D3C60: 3 if v == 2 else 5, 0x800D2524: 0x80470000, 0x800D2528: 0x80490000, 0x800D2778: 0x804A0000,
               0x800D34B8: 0x804B0000, 0x8009012C: 0x04000000, 0x80490000: 0x03030303, 0x80490004: 0x03030303})
    for k in range(8): pk[0x80470000 + 4 * k] = 0x80480000 if v != 2 else 0
    for k in range(16): pk[0x80480000 + 4 * k] = ((k * 37) & 0xFF) << 16 | (k * 11)
    if v in (2, 3, 4) or v == 0:
        b = obj
        pk.update({b + 0x14: h(10.0), b + 0x18: h(20.0), b + 0x1C: h(30.0), OTH + 0x14: h(40.0), OTH + 0x18: h(25.0),
                   OTH + 0x1C: h(70.0), b + 0x31C: REC, b + 0x1CC: h(900.0 if v == 3 else 100.0), b + 0x40: h(45.0)})
        if v == 3:
            pk.update({b + 0x20C: 0x00000005, b + 0x210: 0x00050003, b + 0x108: 0x00008300, b + 0x274: 0x00020000,
                       b + 0x13C: 0x02000001, b + 0x22C: 0x03000000, b + 0x74: 0x0F000000, b + 0xA8: 0x00020000,
                       b + 0x64: 0x00020000, REC + 0x74: 0x00150000, REC + 0x194: 0x00010200})
        if v == 4:
            pk.update({b + 0x20C: 0x000000FF, b + 0x210: 0x00FF00FF, b + 0x274: 0, b + 0x13C: 0, b + 0x31C: 0,
                       b + 0x64: 0})
    ret = "1505F2A0=%X;%X,1505A9B0=1234,150871B8=5,1508712C=%X,15086508=%X,150ACEA0=%X,150A3674=%X,15031C4C=%X,15084468=2" % (
        obj, oth, 0 if v == 2 else 1, 0xFF if v == 4 else 7, 1 if v == 3 else 0, 0 if v == 4 else 0x804B0068,
        0x80460000 if v == 3 else 0)
    retf = "15145138=%X;%X;%X,15087204=%X" % (h(200.0), h(10.0), h(270.0), h(-1.0 if v == 3 else 1.0))
    outw = "1508712C=1:%X/2:%X/3:%X" % (h(15.0), h(28.0), h(12.0) if v != 3 else h(90.0))
    pks = ",".join("%X=%08X" % (k, x) for k, x in sorted(pk.items()))
    return "%s ! 0=%X,1=%X,2=%X ! %s ! %s ! %s ! ! %s ! " % (n, 3 if v != 5 else 1, cmd, ARGS, pks, ret, retf, outw)
for cmd in cmds:
    for v in range(6):
        print(line("c%X_%d" % (cmd, v), cmd, v))
