/* P129: the air meter state at D_800D28E8 + 0x80 (drawn by func_15090AE8 with D_800D28E8's two 0x40 matrices). */
typedef struct {
    /* 0x80 */ s32 dl;          /* first display list of model 0xB9 */
    /* 0x84 */ u8 *vtx[2];      /* the model's 16-byte vertices (buffer 0 = the asset's own, 1 = a copy), per frame */
    /* 0x8C */ u8 *base;        /* 10-byte copies: s16 x, y, z, u8 colour[4] */
    /* 0x90 */ u8 *target;      /* the blend target (asset 2/0x18, same 10-byte layout) */
    /* 0x94 */ f32 blend;       /* 0..1 between base and target positions */
    /* 0x98 */ f32 blend_vel;
    /* 0x9C */ f32 level;       /* air used / 720, at most 1 */
    /* 0xA0 */ f32 drop_y;      /* falls once the air is gone */
    /* 0xA4 */ f32 drop_vel;
    /* 0xA8 */ f32 wobble;      /* -2..2 */
    /* 0xAC */ f32 wobble_vel;
    /* 0xB0 */ u16 img[4];      /* sprite ids by air level */
    /* 0xB8 */ s16 wobble_timer;
    /* 0xBA */ u8 active;
    /* 0xBB */ u8 count;        /* vertex count */
} AirMeter;
extern s32 D_800D28E8;
extern f32 D_8009E0F8;  /* initial blend speed */
extern f32 D_8009E0FC;  /* initial drop speed */
extern f32 D_8009E100;  /* blend range below the level */
extern f32 D_8009E104;  /* blend range above the level */
extern f32 D_8009E108;  /* minimum wobble speed */
extern f32 D_8009E10C;  /* wobble kick */
extern u16 D_8009060A;
extern u16 D_80090612;
extern u16 D_80090616;
extern u16 D_8009061E;
extern u16 D_80090622;
s32 func_15030100(s32 idx, s32 **dls, u8 *count, s32 *data, s32 *out10, s32 *out8, s32 *outC);

// underwater_air_meter_update: animates the HUD air meter while the player is under water (object 0's in_water,
// unkB2 = time under water): loads model 0xB9 once, blends its vertices towards the target shape around the air
// level, tints them, wobbles the meter when air runs low and drops it once the air is gone (unkB2 >= 1440).
void func_1509093C(void) {
    AirMeter *am = (AirMeter *)((u8 *)&D_800D28E8 + 0x80);
    s32 used;
    s32 *dls;
    u8 count;
    s32 data;
    s32 out10, out8, outC;
    f32 frames;
    f32 lo, hi;
    f32 step;
    u8 *vtx;
    u8 *dst;
    u8 *base;
    u8 *target;
    s32 i;
    s32 dark;
    s32 tint_r, tint_g;

    used = D_800CC2D0[0].in_water ? D_800CC2D0[0].unkB2 : 0;
    if (used < 0x5B) {
        am->active = 0;
        return;
    }
    if (am->active == 0) {
        am->active = 0xFF;
        am->blend = 0.0f;
        am->drop_y = 0.0f;
        am->blend_vel = D_8009E0F8;
        am->wobble = 0.0f;
        am->wobble_vel = 0.0f;
        am->drop_vel = D_8009E0FC;
        am->wobble_timer = (func_150ADA20() & 0x3F) + 0x3C;
    }
    am->level = (f32)D_800CC2D0[0].unkB2 / 720.0f;
    if (am->level > 1.0f) {
        am->level = 1.0f;
    }
    if (used < 1441) {
        /* the blend bounces between level - D_8009E100 and level + D_8009E104, clamped to 0..1 */
        am->blend += am->blend_vel * (f32)D_800BE9E4;
        lo = am->level - D_8009E100;
        if (lo < 0.0f) {
            lo = 0.0f;
        }
        if (am->blend <= lo) {
            am->blend_vel = -am->blend_vel;
            am->blend = (lo + lo) - am->blend;
        } else {
            hi = am->level + D_8009E104;
            if (hi > 1.0f) {
                hi = 1.0f;
            }
            if (hi <= am->blend) {
                am->blend_vel = -am->blend_vel;
                am->blend = (hi + hi) - am->blend;
            }
        }
    }
    if (am->dl == 0) {
        func_15030100(0xB9, &dls, &count, &data, &out10, &out8, &outC);
        am->dl = *dls;
        am->count = ((u32)dls - (u32)data) >> 4;
        am->vtx[0] = (u8 *)data;
        am->vtx[1] = (u8 *)allocate_memory(am->count * 16, 1, 2, 0);
        bcopy((void *)data, am->vtx[1], am->count * 16);
        am->base = (u8 *)allocate_memory(am->count * 10, 1, 0, 0);
        for (i = 0; i < am->count; i++) {
            *(s16 *)(am->base + i * 10 + 0) = *(s16 *)(data + i * 16 + 0);
            *(s16 *)(am->base + i * 10 + 2) = *(s16 *)(data + i * 16 + 2);
            *(s16 *)(am->base + i * 10 + 4) = *(s16 *)(data + i * 16 + 4);
            am->base[i * 10 + 6] = *(u8 *)(data + i * 16 + 0xC);
            am->base[i * 10 + 7] = *(u8 *)(data + i * 16 + 0xD);
            am->base[i * 10 + 8] = *(u8 *)(data + i * 16 + 0xE);
            am->base[i * 10 + 9] = *(u8 *)(data + i * 16 + 0xF);
        }
        /* (the asm runs this as a one-pass loop) */
        func_1502B7F0((s32 *)&am->target, 2, 0x18, 0);
    }
    vtx = am->vtx[D_800BE9C0];
    base = am->base;
    target = am->target;
    for (i = 0; i < am->count; i++) {
        dst = vtx + i * 16;
        *(s16 *)(dst + 0) = (s32)(((f32)*(s16 *)(target + i * 10 + 0) - (f32)*(s16 *)(base + i * 10 + 0)) * am->blend +
                                           (f32)*(s16 *)(base + i * 10 + 0));
        *(s16 *)(dst + 2) = (s32)(((f32)*(s16 *)(target + i * 10 + 2) - (f32)*(s16 *)(base + i * 10 + 2)) * am->blend +
                                           (f32)*(s16 *)(base + i * 10 + 2));
        *(s16 *)(dst + 4) = (s32)(((f32)*(s16 *)(target + i * 10 + 4) - (f32)*(s16 *)(base + i * 10 + 4)) * am->blend +
                                           (f32)*(s16 *)(base + i * 10 + 4));
    }
    if (used < 480) {
        am->img[3] = am->img[2] = D_8009061E;
        am->img[1] = am->img[0] = D_8009060A;
    } else if (used < 960) {
        am->img[3] = am->img[2] = D_80090622;
        am->img[1] = am->img[0] = D_8009060A;
    } else if (used < 1200) {
        am->img[3] = am->img[2] = D_80090622;
        am->img[1] = am->img[0] = D_80090616;
    } else {
        am->img[3] = am->img[2] = D_80090622;
        am->img[1] = am->img[0] = D_80090612;
    }
    /* darkening 0..255 over the last 480 units of air (used 720 .. 1200) */
    dark = ((used - 720) * 255) / 480;
    if (dark < 0) {
        dark = 0;
    } else if (dark > 0xFF) {
        dark = 0xFF;
    }
    tint_r = ((dark * -151) >> 8) + 0xFF;
    tint_g = ((dark * -164) >> 8) + 0xFF;
    for (i = 0; i < am->count; i++) {
        dst = vtx + i * 16;
        if (i < 0xD0) {
            dst[0xC] = (s32)(base[i * 10 + 6] * tint_r) >> 8;
            dst[0xD] = (s32)(base[i * 10 + 7] * tint_g) >> 8;
            dst[0xE] = (s32)(base[i * 10 + 8] * 0xFF) >> 8;
        } else if (i < 0xDC) {
            dst[0xC] = ((dark * -97) >> 8) + 0xFF;
            dst[0xD] = ((dark * -94) >> 8) + 0xFF;
            dst[0xE] = ((dark * -91) >> 8) + 0xFF;
        } else {
            dst[0xC] = tint_r;
            dst[0xD] = tint_g;
            dst[0xE] = 0xFF;
        }
    }
    frames = D_800BE9E4;
    if (used >= 1441) {
        am->wobble_vel = 0.0f;
    } else if (used >= 1201) {
        if (fabsf(am->wobble_vel) < D_8009E108) {
            am->wobble_vel = D_8009E108;
        }
    } else if (am->wobble_timer != 0) {
        i = am->wobble_timer - D_800BE9E4;
        if (i <= 0) {
            i = 0;
            am->wobble_vel = D_8009E10C;
            am->wobble = frames * am->wobble_vel;
        }
        am->wobble_timer = i;
    }
    step = am->wobble_vel * frames;
    am->wobble += step;
    if (am->wobble > 2.0f) {
        am->wobble_vel = -am->wobble_vel;
        am->wobble = 4.0f - am->wobble;
    } else if (am->wobble < -2.0f) {
        am->wobble_vel = -am->wobble_vel;
        am->wobble = -4.0f - am->wobble;
    } else if (am->wobble_timer == 0 && used < 1200 && am->wobble >= 0.0f && am->wobble < step) {
        /* a swing passed through 0 with no kick pending: rest until the next random kick */
        am->wobble_timer = (func_150ADA20() & 0x3F) + 0x3C;
        am->wobble = 0.0f;
        am->wobble_vel = 0.0f;
    }
    if (used >= 1440 && am->drop_y > -22.0f) {
        am->drop_vel -= 0.25f * D_800BE9E4;
        am->drop_y += am->drop_vel;
    }
}
