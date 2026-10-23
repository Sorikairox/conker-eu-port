s32 func_151CDA70(s32 src_p, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s16 *src = (s16 *)src_p;
    struct {
        f32 size_x;     /* 0x00 */
        f32 size_y;     /* 0x04 */
        f32 u08;
        f32 u0C;
        f32 rate0;      /* 0x10 */
        f32 rate1;      /* 0x14 */
        f32 x;          /* 0x18 */
        f32 z;          /* 0x1C */
        f32 u20;
        f32 radius;     /* 0x24 */
        f32 grow;       /* 0x28 */
        f32 u2C;
        f32 rate2;      /* 0x30 */
        f32 radius2;    /* 0x34 */
        f32 min0;       /* 0x38 */
        f32 min1;       /* 0x3C */
        f32 u40;
        f32 y;          /* 0x44 */
        s32 owner;      /* 0x48 */
        u8 owner_id;    /* 0x4C */
    } params;
    struct {
        f32 x, y, z;    /* 0x00 */
        s16 life;       /* 0x0C */
        s16 kind;       /* 0x0E */
        s32 type;       /* 0x10 */
        u8 u14;
        u8 u15;
        s32 u18;
    } rec;
    f32 size;
    u8 *obj;

    size = src[3];
    rec.u15 = 0x23;
    rec.x = src[0];
    rec.y = src[1] + src[4];
    rec.z = src[2];
    rec.life = 300;
    rec.kind = 0x34;
    rec.type = 11;
    params.radius = size * 0.875f;
    params.size_x = size * 0.125f;
    params.size_y = size * 0.125f;
    params.rate0 = 0.0300000012f;
    params.rate1 = 0.0400000028f;
    params.u08 = 0.0f;
    params.u0C = 0.0f;
    params.y = src[1];
    params.x = rec.x;
    params.z = rec.z;
    params.radius2 = params.radius;
    params.grow = size * 0.0625f;
    params.u2C = 0.0f;
    params.rate2 = 0.0550000034f;
    params.u40 = 0.0f;
    params.owner = arg2;
    params.min0 = -16384.0f;
    params.min1 = -16384.0f;
    params.u20 = 0.0f;
    params.owner_id = arg1;
    rec.u18 = 0;
    rec.u14 = 7;
    obj = func_15147FF0(&rec, 0x50, 0x1C, 9, 9, 9, 0, 0, 0, arg3, arg4);
    if (obj != NULL) {
        memcpy(*(void **)(obj + 0x98), &params, 0x50);
    }
    return (s32)obj;
}
