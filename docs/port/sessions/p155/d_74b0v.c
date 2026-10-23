s32 func_15132FBC(void *, s32, s32, s32, s32, s32);
typedef struct {
    s16 count;       /* 0x00: pieces */
    u8 pad2[2];
    f32 pos[3];      /* 0x04: centre */
    s16 model;       /* 0x10 */
    u8 pad12[2];
    f32 radius;      /* 0x14: start offset 0..radius along the direction */
    s16 yawMin;      /* 0x18 */
    s16 yawRange;
    s16 pitchMin;    /* 0x1C */
    s16 pitchRange;
    f32 speedMin;    /* 0x20 */
    f32 speedRange;
    f32 upMin;       /* 0x28: mode 0 vertical speed */
    f32 upRange;
    f32 dir[3];      /* 0x30: modes 2 / 3 velocity */
    f32 sizeMin;     /* 0x3C */
    f32 sizeRange;
    f32 spinMin;     /* 0x44 */
    f32 spinRange;
    f32 rotMin;      /* 0x4C */
    f32 rotRange;
    u8 u54;          /* 0x54..0x59: copied to the piece's extra data */
    u8 u55;
    s16 u56;
    s16 u58;
} Spray74B0;
// debris_spray_spawn: spawns spray->count debris pieces (func_15132FBC, 0x10 extra bytes at +0x170) around
// spray->pos, each in a random direction (yaw / pitch byte angles from the ranges, func_151423D8 = sin) at
// 0..radius; velocity by `mode`: 0 horizontal along the yaw with a separate vertical speed, 1 along the direction,
// 2 spray->dir, 3 spray->dir times a random speed. Random size (x30 for the model scale), spin and two rotation
// speeds. Each piece gets a shadow / trail (func_15134908 kind 4, size x15, 0.358) whose record is kept at its
// extra +4. Returns 0 (the asm leaves v0 unset; callers ignore it).
void func_151A74B0(void *arg0, s32 mode, u8 arg2, s32 arg3) {
    Spray74B0 *s = arg0;
    struct {
        u8 *pos[3];
        f32 size;
        f32 u9C;
        s16 life;
        u8 uA2;
        u8 uA3;
    } trail;
    f32 size;
    struct {
        f32 gravity;
        u8 *trail;
        u8 u54;
        u8 u55;
        s16 u56;
        s16 u58;
        u8 padE2[2];
    } extra;
    struct {
        f32 scale;
        f32 uEC;
        f32 uF0;
        f32 uF4;
        f32 rot[3];
        f32 scale3[3];
        f32 pos[3];
        f32 vel[3];
        f32 spin[3];
        f32 u134;
        s32 flags;
        s16 model;
        s16 tex;
        u8 u140;
        u8 pad141[3];
        s32 u144;
        u8 u148;
        u8 u149;
        u8 u14A;
        u8 u14B;
        u8 u14C;
        u8 u14D;
        u8 u14E;
        u8 u14F;
        u8 u150;
        u8 pad151;
        u8 u152;
        u8 pad153;
        s32 u154;
        u8 u158;
        u8 pad159;
        s16 u15A;
        s16 u15C;
    } sp;
    s16 n;
    u8 yaw;
    u8 pitch;
    f32 sy, cy, sp_, cp;
    f32 r, h, v;
    u8 *p;
    u8 *t;

    n = s->count;
    sp.scale3[0] = 1.0f;
    sp.scale3[1] = 1.0f;
    sp.scale3[2] = 1.0f;
    sp.flags = 0x21E9;
    sp.u140 = 0;
    sp.tex = 0x1B;
    sp.rot[0] = 0.0f;
    sp.rot[1] = 0.0f;
    sp.rot[2] = 0.0f;
    sp.spin[1] = 0.0f;
    sp.model = s->model;
    sp.uEC = 0.2f;
    extra.gravity = -18.0f;
    extra.u54 = s->u54;
    extra.u55 = s->u55;
    extra.u56 = s->u56;
    sp.u144 = 0;
    sp.u148 = 0xFF;
    sp.u149 = 1;
    sp.u14A = 5;
    sp.u14B = 4;
    sp.u14C = 0;
    sp.u14D = 0;
    sp.u14E = 1;
    sp.u14F = 0;
    sp.u150 = 0;
    sp.u152 = 0;
    sp.u154 = 0;
    sp.u158 = 0;
    sp.u15A = 0x20;
    sp.u15C = 7;
    extra.u58 = s->u58;
    while (n-- != 0) {
        yaw = func_150ADA20() % (u32)(s->yawRange + 1) + s->yawMin;
        pitch = func_150ADA20() % (u32)(s->pitchRange + 1) + s->pitchMin;
        sy = func_151423D8(yaw - 0x40);
        cy = func_151423D8(yaw);
        sp_ = func_151423D8(pitch - 0x40);
        cp = func_151423D8(pitch);
        r = func_150ADA68() * s->radius;
        h = r * cp;
        sp.pos[0] = s->pos[0] + h * sy;
        sp.pos[1] = s->pos[1] - r * sp_;
        sp.pos[2] = s->pos[2] + h * cy;
        switch ((u8)mode) {
        case 0:
            v = func_150ADA68() * s->speedRange + s->speedMin;
            sp.vel[1] = func_150ADA68() * s->upRange + s->upMin;
            sp.vel[0] = v * sy;
            sp.vel[2] = v * cy;
            break;
        case 1:
            v = func_150ADA68() * s->speedRange + s->speedMin;
            h = v * cp;
            sp.vel[0] = h * sy;
            sp.vel[1] = -v * sp_;
            sp.vel[2] = h * cy;
            break;
        case 2:
            ((s32 *)sp.vel)[0] = ((s32 *)s->dir)[0];
            ((s32 *)sp.vel)[1] = ((s32 *)s->dir)[1];
            ((s32 *)sp.vel)[2] = ((s32 *)s->dir)[2];
            break;
        case 3:
            v = func_150ADA68() * s->speedRange + s->speedMin;
            sp.vel[0] = s->dir[0] * v;
            sp.vel[1] = s->dir[1] * v;
            sp.vel[2] = s->dir[2] * v;
            break;
        }
        size = func_150ADA68() * s->sizeRange + s->sizeMin;
        sp.uF4 = size;
        sp.uF0 = size;
        sp.scale = size * 30.0f;
        sp.u134 = func_150ADA68() * s->spinRange + s->spinMin;
        sp.spin[0] = func_150ADA68() * s->rotRange + s->rotMin;
        sp.spin[2] = func_150ADA68() * s->rotRange + s->rotMin;
        p = (u8 *)func_15132FBC(&sp, 0, 0, 0x10, arg2, arg3);
        if (p != NULL) {
            memcpy(p + 0x170, &extra, 0x10);
            trail.pos[0] = p + 0x38;
            trail.pos[1] = p + 0x3C;
            trail.pos[2] = p + 0x40;
            trail.size = 15.0f * sp.uF4;
            trail.life = 300;
            trail.uA2 = 0;
            trail.uA3 = 1;
            trail.u9C = 0.358f;
            *(u8 **)(p + 0x170 + 4) = NULL;
            t = (u8 *)func_15134908((struct_eu_EF410 *)&trail, 4, arg2, arg3);
            *(u8 **)(p + 0x170 + 4) = t;
            if (t != NULL) {
                memcpy(t + 0x40, &size, 4);
            }
        }
    }

}
