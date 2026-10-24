// effect_overlap_find: whether a live effect of one of the `count` kinds in the s32 list `kinds` already overlaps the
// box around `spec` (centre spec +0 / +4, half sizes ext[0] / ext[1]): walks the effect lists 0x5D and 0x57 of both
// D_800DD280 banks; an effect (kind +0x2A, centre +0x10 / +0x14, half sizes +0x18 / +0x1C) overlaps when its centre
// lies within the summed half sizes on both axes (edges included). Returns 1 on the first overlap, else 0.
s32 func_15155B1C(u8 *spec, f32 *ext, s32 kinds, s32 count) {
    u8 *node;
    u8 *next;
    s32 bank;
    u8 j;
    s32 i;
    s32 found;
    f32 hx;
    f32 hy;
    f32 x;
    f32 y;

    for (bank = 0; bank < 2; bank++) {
        for (j = 0; j < 2; j++) {
            node = (u8 *) D_800DD280[bank][j == 0 ? 0x5D : 0x57]; // the asm copies {0x5D, 0x57} from .rodata
            while (node != NULL) {
                next = *(u8 **) (node + 8);
                found = 0;
                for (i = count; i > 0; i--) {
                    if (node[0x2A] == ((s32 *) kinds)[i - 1]) {
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    hx = *(f32 *) (node + 0x18) + ext[0];
                    hy = *(f32 *) (node + 0x1C) + ext[1];
                    x = *(f32 *) (spec + 0);
                    if (x - hx <= *(f32 *) (node + 0x10) && *(f32 *) (node + 0x10) <= x + hx) {
                        y = *(f32 *) (spec + 4);
                        if (y - hy <= *(f32 *) (node + 0x14) && *(f32 *) (node + 0x14) <= y + hy) {
                            return 1;
                        }
                    }
                }
                node = next;
            }
        }
    }
    return 0;
}
