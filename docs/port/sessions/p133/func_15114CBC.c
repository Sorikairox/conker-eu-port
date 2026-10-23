void func_151148C8(s32, s32 *, s32 *, s32 *);
extern f32 D_800A3330;   /* world-object timer scale */
extern u16 D_800CC1C0[]; /* per object: world-object index + 1 it follows */

/*
 * world_object_timer_update: for a visible world-object record idx (< D_800DC320) and its object, refreshes the
 * object's +0x14 / +0x18 / +0x1C (func_151148C8) and advances its u16 timer +0x76 by the record's +0x64 speed
 * times D_800A3330 (float -> unsigned as IDO, stored as u16); when the object's +0x137 flag is set and its
 * D_800CC1C0 entry (index from the 0x32C-byte array D_800CC2D0) is idx + 1, +0x7A gets the same value.
 */
void func_15114CBC(struct127 *arg0, s32 idx) {
    u8 *obj = (u8 *) arg0;
    u8 *rec;
    u32 t;

    if (obj == NULL || idx >= D_800DC320) {
        return;
    }
    func_151148C8(idx, (s32 *) (obj + 0x14), (s32 *) (obj + 0x18), (s32 *) (obj + 0x1C));
    rec = (u8 *) D_800DBEF4 + idx * 0xA0;
    t = (f32) *(u16 *) (obj + 0x76) + *(f32 *) (rec + 0x64) * D_800A3330;
    *(u16 *) (obj + 0x76) = t;
    if (obj[0x137] != 0 && D_800CC1C0[(obj - (u8 *) D_800CC2D0) / 0x32C] == idx + 1) {
        *(u16 *) (obj + 0x7A) = t;
    }
}
