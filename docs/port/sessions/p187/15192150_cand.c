void func_1504715C(s32 *, struct127 *);
void *memcpy(void *, const void *, u32);
/* dust effect data (0x68 bytes) copied to the effect object at +0x28 */
typedef struct {
    /* 0x00 */ u8 *obj;
    /* 0x04 */ u8 objId;     /* obj +0x3B */
    /* 0x08 */ f32 offset[3];
    /* 0x14 */ s32 kind;     /* arg2 << 6 */
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s32 ground[9]; /* floor query of obj (func_1504715C) */
    /* 0x48 */ f32 u48;
    /* 0x4C */ f32 u4C;
    /* 0x50 */ s16 u50;
    /* 0x52 */ s16 u52;
    /* 0x54 */ u8 u54;
    /* 0x55 */ u8 u55;
    /* 0x58 */ f32 u58;
    /* 0x5C */ f32 u5C;
    /* 0x60 */ f32 u60;
    /* 0x64 */ u8 u64;
} ObjDustData;
// obj_dust_effect_spawn: starts an effect object (func_15149130, type 0x1D, 0x68 bytes of data) that follows obj
// at `offset` (an f32[3]) with the given parameters and a snapshot of obj's floor query; life `life` (-1: 300 and
// not timed). Returns the effect object or NULL (also for a NULL obj). Only caller func_151925C4.
struct260 *func_15192150(u8 *obj, f32 *offset, u8 kind, f32 a3, f32 arg4, s16 life, f32 arg6, f32 arg7, s16 arg8, s16 arg9, u8 arg10, u8 arg11, f32 arg12, f32 arg13, f32 arg14, u8 arg15, u8 arg16, s32 arg17) {
    ObjDustData d;
    struct260 *fx;

    if (obj == NULL) {
        return NULL;
    }
    d.obj = obj;
    d.objId = obj[0x3B];
    d.offset[0] = offset[0];
    d.offset[1] = offset[1];
    d.offset[2] = offset[2];
    d.kind = kind << 6;
    d.u1C = a3;
    d.u18 = 0.0f;
    d.u20 = arg4;
    func_1504715C(d.ground, (struct127 *) obj);
    d.u48 = arg6;
    d.u4C = arg7;
    d.u50 = arg8;
    d.u52 = arg9;
    d.u54 = arg10;
    d.u55 = arg11;
    d.u58 = arg12;
    d.u5C = arg13;
    d.u60 = arg14;
    d.u64 = arg15;
    /* argument 6 is the data size here (the header types it struct37 *) */
    fx = func_15149130((life == -1) ? 300 : life, -1, 0x1D, -1, life != -1, 0x1D, (struct37 *) 0x68, arg16, arg17);
    if (fx != NULL) {
        memcpy((u8 *) fx + 0x28, &d, sizeof(d));
    }
    return fx;
}
