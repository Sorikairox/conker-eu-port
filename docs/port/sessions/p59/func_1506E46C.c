s32 func_100107F8(struct127 *arg0);
s32 func_10010894(struct127 *arg0);
s32 func_151F2CDC(void);
s32 func_1000F568(s32, s32);
s32 func_150ADA20(void);
extern s32 *D_800BE9C8[];

/* Resolves a sound / event word *slot for a record. Bit 21: conditional on mode (0 / 1: record tests, 2: a global
 * test). Ids >= 2000 come from the per-level table D_800BE9C8[rec->unk288] (high bits kept if set). Bits 24-31 are
 * a random-chance byte, bits 16-20 a variant count. Returns 1 and writes *slot, or 0 when it should not play. */
s32 func_1506E46C(struct127 *rec, s32 *slot, s32 mode) {
    u32 w = *slot;
    u32 id = w & 0x7FFF;
    u32 v;
    u32 hi;

    if (w & 0x200000) {
        if (mode == 0) {
            if (func_100107F8(rec) != 0) {
                return 0;
            }
        } else if (mode == 1) {
            if (func_10010894(rec) != 0) {
                return 0;
            }
        } else if (mode == 2) {
            if (func_151F2CDC() == 1) {
                return 0;
            }
        }
    }
    if (id >= 2000) {
        v = D_800BE9C8[*((u8 *)rec + 0x288)][id - 2000];
        if (v == 0) {
            return 0;
        }
        hi = w & 0xFF200000;
        if (hi != 0) {
            w = hi | (v & 0xFFFFFF);
        } else {
            w = v;
        }
    }
    if ((w >> 16) != 0) {
        u32 variants = (w >> 16) & 0x1F;
        if ((w >> 24) < (u32)(func_150ADA20() & 0xFF)) {
            return 0;
        }
        w &= 0x7FFF;
        if (variants != 0) {
            w = func_1000F568(w, variants);
        }
    }
    *slot = w;
    return 1;
}
