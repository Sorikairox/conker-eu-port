// object_forget_target: clear the target byte +0x65 (object index + 1) of the first 25 live objects that point
// at `obj` (called by the object removal func_15060F28).
void func_15060D54(struct127 *obj) {
    s32 idx = obj - D_800CC2D0;
    u8 *o;
    s32 i;

    for (i = 0; i < 25; i++) {
        o = (u8 *) &D_800CC2D0[i];
        if (*(s32 *) o != 0 && o[0x65] == idx + 1) {
            o[0x65] = 0;
        }
    }
}
