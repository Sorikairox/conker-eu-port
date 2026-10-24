extern s32 (*D_80088B00[])(u8 *); /* motion handlers (func_150C6088, func_150C60D4) (index obj +0x30, -1 = none); 0 = remove the object */

/* object_motion_step: for an active object (flag word +0x10 bit 0), runs its motion handler D_80088B00[+0x30] (if
 * any); when the handler returns 0 the object is removed (func_1516972C). Otherwise, if the offset position +0x18 -
 * +0x24 (f32[3] each) changed across the handler, its length (func_15143E64) is stored in +0xC0. Table record word
 * 0x8008C680 (update slot), like its neighbours `void (struct102 *)`. */
void func_150C5A68(struct102 *obj) {
    u8 *o = (u8 *) obj;
    f32 dx, dy, dz;
    f32 d[3];
    u8 remove = 0;

    if (!(*(s32 *) (o + 0x10) & 1)) {
        return;
    }
    dx = *(f32 *) (o + 0x18) - *(f32 *) (o + 0x24);
    dy = *(f32 *) (o + 0x1C) - *(f32 *) (o + 0x28);
    dz = *(f32 *) (o + 0x20) - *(f32 *) (o + 0x2C);
    if (*(s8 *) (o + 0x30) != -1) {
        if (D_80088B00[*(s8 *) (o + 0x30)](o) == 0) {
            remove = 1;
        }
    }
    if (!remove) {
        d[0] = *(f32 *) (o + 0x18) - *(f32 *) (o + 0x24);
        d[1] = *(f32 *) (o + 0x1C) - *(f32 *) (o + 0x28);
        d[2] = *(f32 *) (o + 0x20) - *(f32 *) (o + 0x2C);
        if (d[0] != dx || d[1] != dy || d[2] != dz) {
            *(f32 *) (o + 0xC0) = func_15143E64(d);
        }
    }
    if (remove) {
        func_1516972C(obj);
    }
}
