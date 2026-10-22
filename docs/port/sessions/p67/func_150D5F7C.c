//HOIST void func_150D6898(s32 arg0, u8 arg1, s32 arg2);
//HOIST void func_150D6944(s32 arg0, u8 arg1, s32 arg2);
//HOIST void func_150D6B00(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
//HOIST void func_150D6BB4(u8 arg0, u8 arg1, s32 arg2);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, s16 *, f32 *, f32 *, f32 *, f32 *, s32, s32 *, f32);
s32 func_15132FBC(void *, s32, s32, s32, s32, s32);
s32 func_15134070(struct127 *);
void func_15143874(s16, f32, f32 *, f32 *);
f32 func_15144A74(f32 *, f32 *);
s32 func_15144E80(s16 *, f32 *, f32 *, f32 *);
s32 func_15145128(f32 *, f32 *, s32 *, s32 *);
s32 func_15146078(f32 *, f32 *, f32 *);
void func_151C0910(s16 *, f32 *, s32, s32);
void func_151C0B54(f32 *, s32, s32);
void func_151C0BA0(f32 *, s32, s32);
extern s32 D_800A0E00[3];   /* sprites of the first burst */
extern s32 D_800A42F4[];    /* per type: entry count of the D_80089DC0 list */
extern s32 *D_80089DC0[];   /* per type: sprite list (entries 2.. are used) */

/* P67: particle request passed to func_15132FBC (0x7C bytes). */
typedef struct {
    /* 0x00 */ f32 scale[4];     /* 1, 1, xz_scale, y_scale */
    /* 0x10 */ f32 rot[3];       /* random degrees */
    /* 0x1C */ f32 one[3];
    /* 0x28 */ f32 pos[3];
    /* 0x34 */ f32 vel[3];
    /* 0x40 */ f32 spinX;
    /* 0x44 */ f32 spinY;
    /* 0x48 */ f32 spinZ;
    /* 0x4C */ f32 gravity;
    /* 0x50 */ s32 flags;
    /* 0x54 */ s16 life;
    /* 0x56 */ s16 sprite;
    /* 0x58 */ u8  u58;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8  alpha;
    /* 0x61 */ u8  u61;
    /* 0x62 */ u8  u62[6];
    /* 0x68 */ u8  u68;
    /* 0x69 */ u8  pad69;
    /* 0x6A */ u8  u6A;
    /* 0x6C */ struct127 *owner;
    /* 0x70 */ u8  ownerId;
    /* 0x72 */ s16 u72;
    /* 0x74 */ s16 u74;
    /* 0x78 */ s32 u78;
} DebrisParticle;

/* P67: debris burst of a destroyed object: sounds, two particle bursts thrown out along the surface it hit (ray cast
 * along its last movement) or straight up, then the dust / scorch effects. arg1 / arg2 are passed through. */
void func_150D5F7C(struct127 *arg0, s32 arg1, s32 arg2) {
    DebrisParticle p;
    f32 pos[3];          /* sp1B4: centre, 50 above the object */
    f32 dir[3];          /* sp1A8: last movement (normalised) */
    f32 hit[3];          /* sp19C */
    s16 tri[9];          /* sp188: the hit triangle */
    f32 axisA[3];        /* sp15C */
    f32 axisB[3];        /* sp150 */
    f32 normal[3];       /* sp168 */
    f32 t;
    s32 surface;
    s32 type;
    s32 tmp0, tmp1;
    s32 moved;
    s32 useDefault;
    u8 hitWall = 0;
    u8 id = arg1 & 0xFF;
    s32 *s;
    s32 i;

    pos[0] = arg0->x_position;
    pos[1] = arg0->y_position + 50.0f;
    pos[2] = arg0->z_position;
    dir[0] = arg0->x_position - arg0->old_x_position;
    dir[1] = arg0->y_position - arg0->old_y_position;
    dir[2] = arg0->z_position - arg0->old_z_position;
    type = func_15134070(arg0);
    if (type == 0x63) {
        return;
    }
    if ((arg0->unk184 & 0x1F) == 0xE) {
        func_10010630(0x434, arg0, 0x7D00, 0x2BC, 0x7D0);
    } else {
        func_10010630(0x4C8, arg0, -0x7D00, 0x2BC, 0x7D0);
    }
    func_10010630((func_150ADA20() & 1) + 0x2B6, arg0, 0x7D00, 0x3E8, 0xBB8);
    func_10010630((func_150ADA20() & 3) + 0x2B1, arg0, 0x7D00, 0x2BC, 0x7D0);
    func_151C0B54(pos, id, arg2);
    func_151C0BA0(pos, id, arg2);
    func_15145A50(arg0);
    if (arg0->unk1D4 == NULL || (arg0->unk74 & 0xF) == 0xF) {
        return;
    }

    /* the surface it was moving into: basis (axisA, axisB, normal) of the hit triangle, facing back */
    moved = func_15145128(dir, dir, &tmp0, &tmp1) != 0;
    if (moved && func_150ACEA0(arg0->old_x_position, arg0->old_y_position, arg0->old_z_position, dir[0], dir[1], dir[2],
                               0, tri, &hit[0], &hit[1], &hit[2], &t, 0, &surface, 0.0f) != 0 && t < 397.0f) {
        hitWall = 1;
    }
    useDefault = 1;
    if (hitWall) {
        useDefault = 0;
        if (func_15144E80(tri, axisA, axisB, normal) != 0) {
            s32 a, b;

            func_15145128(axisA, axisA, &a, &b);
            func_15145128(axisB, axisB, &a, &b);
            func_15145128(normal, normal, &a, &b);
            if (func_15144A74(normal, dir) > 0.0f) {
                normal[0] = -normal[0];
                normal[1] = -normal[1];
                normal[2] = -normal[2];
            }
        } else {
            useDefault = 1;
        }
    }
    if (useDefault) {
        if (moved) {
            normal[0] = -dir[0];
            normal[1] = -dir[1];
            normal[2] = -dir[2];
            func_15146078(normal, axisA, axisB);
        } else {
            normal[0] = 0.0f; normal[1] = 1.0f; normal[2] = 0.0f;
            axisA[0] = 1.0f;  axisA[1] = 0.0f;  axisA[2] = 0.0f;
            axisB[0] = 0.0f;  axisB[1] = 0.0f;  axisB[2] = 1.0f;
        }
    }

    p.scale[0] = 1.0f;
    p.scale[1] = 1.0f;
    normal[0] *= 1000.0f;
    normal[1] *= 1000.0f;
    normal[2] *= 1000.0f;
    p.scale[2] = arg0->xz_scale;
    p.one[0] = 1.0f;
    p.one[1] = 1.0f;
    p.one[2] = 1.0f;
    p.scale[3] = arg0->y_scale;
    p.pos[0] = pos[0];
    p.pos[1] = pos[1];
    p.pos[2] = pos[2];
    p.flags = 0x21E8;
    p.u58 = 0;
    p.u5C = 0;
    p.alpha = 0xFF;
    p.u61 = 8;
    p.u62[0] = 0;
    p.u62[1] = 0;
    p.u62[2] = 0;
    p.u62[3] = 0;
    p.u62[4] = 0;
    p.u62[5] = 0;
    p.u68 = 2;
    p.u6A = 1;
    p.owner = arg0;
    p.u78 = 0;
    p.spinY = 0.0f;
    p.ownerId = arg0->unique_id;
    p.u72 = 0xC;
    p.u74 = 0x15;

    /* burst 1: one particle per D_800A0E00 sprite, thrown in a random direction around the normal */
    for (i = 0; i < 3; i++) {
        f32 speed = func_150ADA68() * 0.0132f + 0.0298f;
        s32 ang = func_150ADA20();
        f32 c, d;

        func_15143874(ang & 0xFF, func_150ADA68() * 759.0f, &c, &d);
        p.vel[0] = (axisA[0] * c + axisB[0] * d + normal[0]) * speed;
        p.vel[1] = (axisA[1] * c + axisB[1] * d + normal[1]) * speed;
        p.vel[2] = (axisA[2] * c + axisB[2] * d + normal[2]) * speed;
        p.rot[0] = func_150ADA68() * 360.0f;
        p.rot[1] = func_150ADA68() * 360.0f;
        p.rot[2] = func_150ADA68() * 360.0f;
        p.spinX = func_150ADA68() * 38.444f + -19.222f;
        p.spinZ = func_150ADA68() * 38.444f + -19.222f;
        p.gravity = func_150ADA68() * 0.648f + -1.3970001f;
        p.life = (u32)func_150ADA20() % 21 + 30;
        p.sprite = D_800A0E00[i];
        func_15132FBC(&p, 0, 0, 0, id, arg2);
    }

    /* burst 2: the type's own sprites, entries 2 .. count - 1 */
    p.u72 = 0xC;
    p.u74 = 0x15;
    for (i = 2; i < D_800A42F4[type]; i++) {
        f32 speed = func_150ADA68() * 0.02f + 0.0052f;
        s32 ang = func_150ADA20();
        f32 c, d;

        func_15143874(ang & 0xFF, func_150ADA68() * 723.0f, &c, &d);
        p.vel[0] = (axisA[0] * c + axisB[0] * d + normal[0]) * speed;
        p.vel[1] = (axisA[1] * c + axisB[1] * d + normal[1]) * speed;
        p.vel[2] = (axisA[2] * c + axisB[2] * d + normal[2]) * speed;
        p.rot[0] = func_150ADA68() * 360.0f;
        p.rot[1] = func_150ADA68() * 360.0f;
        p.rot[2] = func_150ADA68() * 360.0f;
        p.spinX = func_150ADA68() * 40.45f + -20.225f;
        p.spinZ = func_150ADA68() * 40.45f + -20.225f;
        p.gravity = func_150ADA68() * 0.62600005f + -1.0890001f;
        p.life = (u32)func_150ADA20() % 41 + 40;
        p.sprite = D_80089DC0[type][i];
        func_15132FBC(&p, 0, 0, 0, id, arg2);
    }

    if (arg0->camera != NULL && D_80082FA0 <= 0) {
        func_150D6BB4(arg0->camera->unk23D, id, arg2);
    }
    if (hitWall && arg0->camera != NULL) {
        if ((surface & 0x1F) == 0xE) {
            func_150D6B00((s32)tri, (s32)hit, id, arg2);
        } else {
            func_151C0910(tri, hit, id, arg2);
        }
    }
    func_150D6944((s32)pos, id, arg2);
    func_150D6898((s32)pos, id, arg2);
}
