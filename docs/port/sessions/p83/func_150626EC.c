/* Removes the objects attached to obj (+0x65 = obj's slot + 1, +0x127 = 0xFF) with func_15060F28(child, mode). */
void func_150626EC(struct127 *obj, s32 mode) {
    struct127 *o;

    for (o = D_800CC2D0; o != (struct127 *)&D_800D121C; o++) {
        if (*(s32 *)o != 0 && ((u8 *)o)[0x65] == (obj - D_800CC2D0) + 1 && ((u8 *)o)[0x127] == 0xFF) {
            func_15060F28(o, mode);
        }
    }
}
