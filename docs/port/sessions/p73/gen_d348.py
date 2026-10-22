# setups for func_1501D348 (scene loader). EU addresses: D_800C35EA 800C3A0A (u8[slot]), D_800C35C4 800C39E4,
# D_800BE9F0 800BEE10, D_800C3A88 800C3A88, D_8008448C 8008448C, allocate_memory 10003E90,
# func_1501D240 1501D240, func_1501D064 1501D064.
REC, HDR = 0x80440000, 0x80450000
def setup(n, slot, state, c4, same, d240, counts, cb, n064, zerobits):
    b = {}   # byte pokes
    b[0x800C3A0A + slot] = state
    b[0x800C39E4] = c4
    w = {0x800BEE10: 0x25, 0x800C3A88 + 4 * slot: REC, 0x8008448C + 4 * 2: 0x15000010}
    for a, v in b.items():
        wa = a & ~3; sh = (3 - (a & 3)) * 8
        w[wa] = (w.get(wa, 0) & ~(0xFF << sh)) | (v << sh)
    w[REC] = HDR; w[REC + 4] = 0x11
    w[HDR] = (counts[0] << 16) | counts[1]; w[HDR + 4] = (counts[2] << 16) | counts[3]
    for i in range(1, 1 + 2 * counts[0] + 1 + counts[1] + counts[2] + counts[3] + 1):
        w[REC + 8 * i] = 0x1000 + i
        w[REC + 8 * i + 4] = (3 if i in zerobits else 8 * i + 5)
    allocs = ";".join("%X" % (0x80460000 + 0x1000 * i) for i in range(40))
    ret = f"1501D240={d240:X},1501D064={n064:X},10003E90={allocs}"
    lvl = 0x25 if same else 0x1D
    pk = ",".join(f"{a:X}={v:08X}" for a, v in sorted(w.items()))
    return f"{n} ! 0={lvl:X},1=3,2={slot:X},3={cb:X},4=77 ! {pk} ! {ret} ! ! ! ! "
i = 0
for slot in [0, 1, 2]:
    for state, c4, same, d240 in [(1, 0, 1, 1), (0, 1, 1, 1), (0, 0, 0, 1), (2, 0, 0, 1), (0, 0, 1, 0)]:
        print(setup(f"d{i}", slot, state, c4, same, d240, (1, 0, 0, 0), 0, 0, ())); i += 1
    for state in [0, 2]:
        for counts in [(0, 0, 0, 0), (1, 0, 0, 0), (2, 3, 1, 2), (3, 1, 4, 0), (1, 2, 0, 5), (4, 0, 2, 1)]:
            for cb, n064, zb in [(0, 0, ()), (2, 5, (2,)), (0, 0x10003, (1, 3))]:
                print(setup(f"d{i}", slot, state, 0, 1, 1, counts, cb, n064, zb)); i += 1
