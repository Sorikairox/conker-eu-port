u32 func_1000F568(u32, s32);
s32 func_151F2CDC(struct127 *, u32);
extern s32 D_800BE9C8;

s32 func_1506E46C(struct127 *arg0, u32 *arg1, s32 arg2) {
    u32 v;
    u32 id;
    s32 t;
    u32 m;
    s32 k;

    v = *arg1;
    id = v & 0x7FFF;
    if (v & 0x200000) {
        switch (arg2) {
        case 0:
            if (func_100107F8(arg0) != 0) {
                return 0;
            }
            break;
        case 1:
            if (func_10010894(arg0) != 0) {
                return 0;
            }
            break;
        case 2:
            if (func_151F2CDC(arg0, v) == 1) {
                return 0;
            }
            break;
        }
    }
    if (id >= 2000) {
        m = v & 0xFF200000;
        t = ((s32 **)&D_800BE9C8)[*((u8 *)arg0 + 0x288)][id - 2000];
        if (t == 0) {
            return 0;
        }
        if (m != 0) {
            v = m | (t & 0xFFFFFF);
        } else {
            v = m | t;
        }
    }
    id = v >> 16;
    if (id != 0) {
        if ((v >> 24) < (func_150ADA20() & 0xFF)) {
            return 0;
        }
        k = id & 0x1F;
        v = v & 0x7FFF;
        if (k != 0) {
            v = func_1000F568(v, k);
        }
    }
    *arg1 = v;
    return 1;
}
