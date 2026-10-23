struct252 *func_1505C1A4(struct127 *arg0);
s32 func_1505C1E4(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
u8 func_1505B9C4(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
extern s16 D_800D16B6; /* the asm's name for this halfword (D_800D1296 in the US list) */

// object_send_hit: sends a hit / message of kind `flags & 0xFF` to the object `obj` from the current object.
/* Nothing (returns 0) while D_800C35EA is 1, or when the object is immune (flag 0x20000), stunned (0x40000) or has
 * no health (unless flag 0x100000). Sets the parameter D_800D1340 (arg3 + 1, 0 for -1) and the value `val` in
 * D_800D1292 / D_800D16B6. The sender record is D_8009A9F8, or func_1505C1A4(D_800D154C) with flag 0x10000.
 * Flag 0x80000 uses func_1505C1E4 and returns its result; else func_1505B9C4 and returns the object's bit
 * (1 << its index in D_800CC2D0). */
s32 func_1505D024(struct127 *obj, s32 flags, u16 val, s32 arg3) {
    struct252 *from = &D_8009A9F8;
    s32 idx;
    s32 bit;

    if (D_800C35EA == 1) {
        return 0;
    }
    if ((flags & 0x20000) && obj->immune != 0) {
        return 0;
    }
    if ((flags & 0x40000) && obj->stunned != 0) {
        return 0;
    }
    if (!(flags & 0x100000) && obj->health == 0) {
        return 0;
    }
    if (arg3 == -1) {
        D_800D1340 = 0;
    } else {
        D_800D1340 = arg3 + 1;
    }
    D_800D1292 = val;
    D_800D16B6 = val;
    if (flags & 0x10000) {
        from = func_1505C1A4(D_800D154C);
    }
    idx = ((s32)obj - (s32)D_800CC2D0) / 0x32C;
    bit = 1 << idx;
    if (flags & 0x80000) {
        return func_1505C1E4((struct127 *)&D_800D121C, obj, from, flags & 0xFF, idx + 1, 0, 7);
    }
    func_1505B9C4((struct127 *)&D_800D121C, obj, (s32)from, (s32)from, flags & 0xFF, idx + 1, 7);
    return bit;
}
