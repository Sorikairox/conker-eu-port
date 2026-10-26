#ifdef NON_MATCHING
u8 *trail_spawn(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                  s32 argA, u8 *argB, s32 argC, u8 argD, s32 argE);
extern u8 g_impact_kind_motion_byte[]; /* was D_800AB7D4 */
extern u8 g_impact_kind_flag20[]; /* was D_800AB7E4 */

/* Spawn one particle of kind `kind` (0x10 = spark / debris sprite) through trail_spawn:
 * - spawn block (0x1C bytes): position `pos`, sprite `sprite` + 0x10, model 0x35, count 1, -1, `tint`, `owner`;
 * - motion block (0x20 bytes): speed, velocity `vel`, scale, floor -10000, flags (8 | 0x40, 0x20 / 0x80 from the
 *   per-type tables g_impact_kind_flag20 / g_impact_kind_flags, 3 when `fade`), g_impact_kind_motion_byte[type], 0xFF, alpha, two s16 timers;
 * - fixed render block (0x1E bytes, constants).
 * On success the object's extra data (+0x98) gets (sx, sy, type) at +0x48. Returns the particle or NULL. */
u8 *impact_spark_spawn(u8 *pos, u8 *vel, f32 scale, s16 sprite, u8 alpha, f32 speed, s32 tint, u8 fade, f32 sx, f32 sy,
                  u8 bright, u8 type, s32 argC, s16 t0, s16 t1, s32 owner, u8 arg10, s32 arg11) {
    struct {
        s32 render[3];      /* sp54: words 0, 0x220005, 0x50600 */
        s32 mode[4];        /* 3, 0x46, 0x80, 0x20 */
        u8 b0;              /* 0 */
        u8 b1;              /* 0xC */
    } rb;
    struct {
        f32 sx;             /* sp84, copied to (+0x98)->+0x48 */
        f32 sy;
        u8 type;
    } extra;
    struct {
        f32 speed;          /* sp90 */
        s32 vel[3];
        f32 scale;
        f32 floor;
        u8 flags;
        u8 kind;
        u8 full;
        u8 alpha;
        s16 t0;
        s16 t1;
    } mb;
    struct {
        s32 pos[3];         /* spB0 */
        s16 sprite;
        s16 model;
        s32 count;
        s8 minus1;
        u8 tint;
        s32 owner;
    } sb;
    u8 *p;
    s32 a7, a8, a10, a11;
    s32 f;

    sb.tint = tint;
    sb.pos[0] = ((s32 *) pos)[0];
    sb.pos[1] = ((s32 *) pos)[1];
    sb.pos[2] = ((s32 *) pos)[2];
    sb.sprite = sprite + 0x10;
    sb.model = 0x35;
    sb.count = 1;
    sb.minus1 = -1;
    sb.owner = owner;
    mb.speed = speed;
    mb.vel[0] = ((s32 *) vel)[0];
    mb.vel[1] = ((s32 *) vel)[1];
    mb.vel[2] = ((s32 *) vel)[2];
    mb.scale = scale;
    mb.floor = -10000.0f;
    f = 8 | 0x40;
    if (g_impact_kind_flag20[type] != 0) {
        f |= 0x20;
    }
    if (((u8 *) &g_impact_kind_flags)[type] != 0) {
        f |= 0x80;
    }
    mb.full = 0xFF;
    mb.kind = g_impact_kind_motion_byte[type];
    mb.alpha = alpha;
    mb.t0 = t0;
    mb.t1 = t1;
    if (fade != 0) {
        mb.flags = f | 3;
        a7 = 7;
        a8 = 4;
    } else {
        mb.flags = f;
        a7 = 0;
        a8 = 0;
    }
    extra.sx = sx;
    extra.sy = sy;
    extra.type = type;
    rb.render[0] = 0;
    rb.render[1] = 0x220005;
    rb.render[2] = 0x50600;
    rb.mode[0] = 3;
    rb.mode[1] = 0x46;
    rb.mode[2] = 0x80;
    rb.mode[3] = 0x20;
    rb.b0 = 0;
    rb.b1 = 0xC;
    if (bright != 0) {
        a10 = 2;
        a11 = 0xFF;
    } else {
        a10 = 0;
        a11 = 0;
    }
    p = trail_spawn((u8 *) &sb, (s32) &mb, 0x10, 1, 0, 0, a7, a8, 0, a10, a11, (u8 *) &rb, argC, arg10, arg11);
    if (p != NULL) {
        memcpy(*(s32 *) (p + 0x98) + 0x48, (s32) &extra, 0xC);
    }
    return p;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2062D0/impact_spark_spawn.s")
#endif
