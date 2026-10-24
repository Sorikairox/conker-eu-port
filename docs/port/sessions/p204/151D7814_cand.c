/* P204 (from the s163 draft 7814_b.c) */
extern s32 (*D_80090040[])(u8 *);
f32 func_15143E64(struct17 *);
void func_151D7DE0(u8 *);
// effect_follow_update: per-frame handler (D_8008A980 table, void (u8 *)) of an effect-carrier object: remembers its
// position (+0x30) and flag +0x2D bit 0, then runs the kind's update D_80090040[+0x2C]; when that returns 0 the object
// is retired (+0xE = -1, +0xD bit 0). Otherwise, when bit 0 of +0x2D was set before and is still set and the object
// moved less than +0x3C this frame, an effect is attached by func_151D7DE0 if there is none yet (+0x28 == NULL);
// in every other case func_151D7D78 releases the attached effect.
void func_151D7814(u8 *obj) {
    f32 pos[3];
    u8 active;
    f32 d[3];

    pos[0] = *(f32 *) (obj + 0x30);
    pos[1] = *(f32 *) (obj + 0x34);
    pos[2] = *(f32 *) (obj + 0x38);
    active = obj[0x2D] & 1;
    if (D_80090040[obj[0x2C]](obj) == 0) {
        *(s16 *) (obj + 0xE) = -1;
        obj[0xD] |= 1;
        return;
    }
    if ((obj[0x2D] & 1) && active) {
        d[0] = *(f32 *) (obj + 0x30) - pos[0];
        d[1] = *(f32 *) (obj + 0x34) - pos[1];
        d[2] = *(f32 *) (obj + 0x38) - pos[2];
        if (func_15143E64((struct17 *) d) < *(f32 *) (obj + 0x3C)) {
            if (*(u8 **) (obj + 0x28) == NULL) {
                func_151D7DE0(obj);
            }
            return;
        }
    }
    func_151D7D78(obj);
}
