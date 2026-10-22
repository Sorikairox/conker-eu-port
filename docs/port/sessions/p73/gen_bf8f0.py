# setups for func_151BF8F0 (lives pop-up). EU addresses: func_15149130 151496A0, func_150859AC 15085E1C,
# func_15157580 15157580, D_800D2458 800D2878.
i = 0
for lives in [0, 1, 2, 9, 10, 11, 20, 99, 100, 101, 150]:
    for wide in [0, 1]:
        for hud, spr in [(0x80420000, 0x80430000), (0x80420000, 0), (0, 0x80430000)]:
            for a0, a1 in [(0xFF, 1), (3, 0x1234)]:
                pk = f"800D2878={wide << 24:08X},800A5860=3F800000,800A5864=40000000,800A5868=40400000"
                ret = f"151496A0={hud:X},15085E1C={lives:X},15157580={spr:X}"
                print(f"f{i} ! 0={a0:X},1={a1:X} ! {pk} ! {ret} ! ! ! ! "); i += 1
