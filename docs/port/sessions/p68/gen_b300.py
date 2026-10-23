# setups for func_1501B300 (camera = D_800DBFF0 + player * 0x9A0)
import struct
def h(f): return struct.unpack('>I', struct.pack('>f', f))[0]
CAMS=0x80420000
def line(n, player, frozen, f698, fff4, pitch, heading, sp, sh, a70, trig):
    cam = CAMS + player * 0x9A0
    pk = {0x800BEEE0: frozen << 24, 0x800DC420: CAMS, 0x800DC424: fff4, cam + 0x698: f698, cam + 0x388: h(pitch),
          cam + 0x380: h(heading), 0x800BEAE0 + 4 * player: h(sp), 0x800BEAF0 + 4 * player: h(sh), 0x800DD160: 0x11223344, 0x800DD164: 0x55667788}
    rf = f"15048D60={h(a70[0]):X};{h(a70[1]):X},15048050={h(trig[0]):X};{h(trig[1]):X},15047EF0={h(trig[2]):X};{h(trig[3]):X}"
    return f"{n} ! 0={player:X} ! " + ",".join(f"{a:X}={v:08X}" for a, v in pk.items()) + f" ! ! {rf} ! ! !"
i = 0
for player in [0, 1, 2]:
    for frozen, f698, fff4 in [(1, 0, 0), (0, 1, 0), (0, 0, 1), (0, 0, 0), (0, 0, 0x100)]:
        for pitch, sp in [(-10.0, 5.0), (370.0, 0.0), (360.0, 1.0), (200.0, -30.0), (180.0, 2.0), (90.0, 89.0)]:
            for sh, a70 in [(10.0, (5.0, 100.0)), (350.0, (20.0, -95.0)), (-1.0, (0.5, 90.0)), (359.9, (4.0, -90.0)), (0.0, (-370.0, 89.0))]:
                print(line(f"b{i}", player, frozen, f698, fff4, pitch, 123.0, sp, sh, a70, (0.5, -0.25, 0.8, -0.9))); i += 1
