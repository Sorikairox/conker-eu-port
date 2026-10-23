void *memcpy(void *, const void *, s32);
extern void (*D_80090010[])(u8 *obj, s32 sound, f32 *point);

typedef struct {
    u8 *obj;     /* 0x00 */
    u8 objId;    /* 0x04: obj[0x3B] */
    s16 sound;   /* 0x06: -1, 0x82 for kind 6 */
    u8 kind;     /* 0x08 */
    f32 unkC;    /* 0x0C */
    u8 flags;    /* 0x10: bit 0 = point valid */
    f32 point[3]; /* 0x14 */
} ObjEffectRec_151D469C; /* 0x20 bytes, copied to the record at +0x28 */

// object_point_effect_spawn: fills a 0x20-byte record (object, kind, the kind's point on the object from the
// D_80090010 handler when the object has bone matrices and obj[0x74] low nibble != 0xF) and spawns event 0x41 /
// kind 0x35 through func_15149130 with it. Returns 0 (callers in game_981E0 declare it implicitly as int).
void func_151D469C(u8 *obj, u8 kind, s16 arg2, u8 arg3, s32 arg4) {
    ObjEffectRec_151D469C rec;
    u8 *p;

    rec.obj = obj;
    rec.objId = obj[0x3B];
    rec.sound = -1;
    rec.flags = 0;
    rec.kind = kind;
    rec.unkC = 0.0f;
    if (kind == 6) {
        rec.sound = 0x82;
    }
    if (*(u8 **)(obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 0xF) {
        D_80090010[kind](obj, rec.sound, rec.point);
        rec.flags |= 1;
    }
    p = (u8 *)func_15149130(arg2, -1, 0x41, -1, 1, 0x35, (struct37 *)0x20, arg3, arg4);
    if (p != NULL) {
        memcpy(p + 0x28, &rec, 0x20);
    }

}
