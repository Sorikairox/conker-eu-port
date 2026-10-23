u8 *func_1514BE54(u8 *arg0, u8 *arg1, s16 arg2, u8 arg3, u8 *arg4, f32 arg5, f32 arg6, f32 arg7, u8 arg8, u8 arg9,
                  u8 argA, s32 argB, u8 argC, s16 argD, s16 argE, s32 argF, u8 arg10, s32 arg11);
void *func_151D2BA4(void *arg0, void *arg1, s32 arg2, u8 arg3, s32 arg4);

// bone_sparks_emit: while the emitter's counter (self + 0x30) is above 1, emits one spark per unit (if the live
// count +0x20 is below the limit +0x5C): a random attachment point of set +0x78 (D_800E0990 / D_800E0968: 16-byte
// entries, bone index + offset) is transformed by the owner's (+0x10) bone matrix, a particle (kind 0x13 / 0x14) is
// spawned there and a follower (func_151D2BA4) ties it to the bone. Owners without matrices or hidden (nibble 0xF)
// only drain the counter.
void func_1518FE50(s32 arg0) {
    u8 *self = (u8 *)arg0;
    u8 *owner = *(u8 **)(self + 0x10);
    f32 *count = (f32 *)(self + 0x30);
    u8 *point;
    u8 *part;
    s32 set;
    s32 size;
    s32 kind;
    f32 at[3];
    f32 speed[2];
    struct {
        u8 *owner;      /* 0x00 */
        u8 owner_id;    /* 0x04 */
        f32 offset[3];  /* 0x08 */
        u8 bone;        /* 0x14 */
        s16 life;       /* 0x16 */
        u8 u18;
        u8 u19;
        u8 u1A;
        u8 *particle;   /* 0x1C */
        u8 *emitter;    /* 0x20 */
    } rec;

    if (!(1.0f < *count)) {
        return;
    }
    if (*(void **)(owner + 0x1D4) == NULL || (owner[0x74] & 0xF) == 0xF) {
        do {
            *count -= 1.0f;
        } while (1.0f < *count);
        return;
    }
    do {
        if (*(s16 *)(self + 0x20) < *(s32 *)(self + 0x5C)) {
            set = *(s32 *)(self + 0x78);
            point = (u8 *)D_800E0990[set] + ((u32)func_150ADA20() % (u16)D_800E0968[set]) * 16;
            speed[0] = func_150ADA68() * *(f32 *)(self + 0x4C) + *(f32 *)(self + 0x44);
            speed[1] = func_150ADA68() * *(f32 *)(self + 0x50) + *(f32 *)(self + 0x48);
            func_15143134(point + 4, at, *(u8 **)(owner + 0x1D4) + (point[0] << 6));
            size = func_150ADA20();
            kind = (func_150ADA20() & 1) ? 0x13 : 0x14;
            part = func_1514BE54((u8 *)at, (u8 *)speed, -1, (u32)size % (self[0x55] + 1) + self[0x54], D_800A5860,
                                 0.0f, 1.0f, *(f32 *)(self + 0x80), 0, 0x23, 0, kind, 1, 1, 0xFF, 0, self[0xC],
                                 self[1]);
            if (part != NULL) {
                rec.owner = owner;
                rec.owner_id = owner[0x3B];
                rec.offset[0] = ((f32 *)(point + 4))[0];
                rec.offset[1] = ((f32 *)(point + 4))[1];
                rec.offset[2] = ((f32 *)(point + 4))[2];
                rec.bone = point[0];
                rec.life = (u32)func_150ADA20() % (*(s16 *)(self + 0x58) + 1) + *(s16 *)(self + 0x56);
                rec.u18 = 1;
                rec.u19 = (self[0x7C] & 1) ? 1 : 0;
                rec.u1A = 0;
                rec.emitter = self;
                rec.particle = part;
                func_151D2BA4(&rec, at, 0, self[0xC], self[1]);
            }
        }
        *count -= 1.0f;
    } while (1.0f < *count);
}
