#ifdef NON_MATCHING
/* func_1515128C smoke spec (0x2D bytes used) */
typedef struct {
    /* 0x00 */ s32 u00;
    /* 0x04 */ s32 u04;
    /* 0x08 */ f32 pos[3];
    /* 0x14 */ s16 u14;
    /* 0x16 */ s16 u16;
    /* 0x18 */ s16 u18;
    /* 0x1A */ s16 u1A;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ s16 u28;
    /* 0x2A */ s16 u2A;
    /* 0x2C */ u8  dark;
} HitSmokeSpec;
void func_1504715C(void *, u8 *);
void func_1515C7B4(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void func_1515128C(u8 *arg0, u8 arg1, s32 arg2);
void func_151C6750(s32 arg0, s32 arg1, u8 arg2, s32 arg3);
void func_1513A24C(f32 *pos, s32 *ids, s32 *scales, s32 n, f32 scale, u8 kind, u8 arg6, u8 *obj, s32 *bounds,
                   u8 arg9, s32 argA);
void func_1513A48C(struct17 *arg0, u8 arg1, s32 arg2);
void func_151A9DE4(f32 *arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);
extern s32 *D_80089DC0[];       /* per hit kind: debris model ids */
extern s32 D_800A4010[];        /* debris scales (all 1.0) */
extern s32 D_800A42F4[];        /* per hit kind: debris kinds */
extern s32 D_800A4344[];        /* per hit kind: debris spec byte +0x40 */
extern u8 D_800A43B8[][16];     /* per hit kind: +0xE == 2: debris only */

// object_hit_effects: the hit / break effects of an object by its hit kind (func_15134070, 0x63: none), at its
// effect position (func_1515C7B4): debris pieces (debris; two kinds fewer with fewer, or for kind 4 unless the
// object type is 0x16), then unless the kind's +0xE is 2: a smoke puff (smoke; dark for kinds 2 / 15 / 18),
// 18..23 floor splats within 300 below (splats), and the finishing effect (finish: func_151C6750 for kinds 2 / 15,
// else func_1513A48C). arg6 / arg7 are passed on to every spawner. The asm's v0 is left over from a callee; every
// caller ignores it (func_151086A0 returns it to its asm caller, which does not read it).
void func_15136C3C(u8 *obj, u8 smoke, u8 splats, u8 debris, u8 finish, u8 fewer, u8 arg6, s32 arg7) {
    HitSmokeSpec spec;
    s32 bounds[9];
    f32 pos[3];
    f32 sizeY;
    f32 sizeX;
    f32 size;
    s32 kind;
    s32 n;
    u8 *info;
    u8 dark;

    if (obj == NULL) {
        return;
    }
    size = (*(f32 *)(obj + 0x14C) + *(f32 *)(obj + 0x150)) * 0.5f;
    func_1515C7B4(obj, pos, &sizeX, &sizeY);
    kind = func_15134070((struct127 *)obj);
    if (kind == 0x63) {
        return;
    }
    func_1504715C(bounds, obj);
    if (debris) {
        if (fewer || (kind == 4 && obj[4] != 0x16)) {
            n = D_800A42F4[kind] - 2;
        } else {
            n = D_800A42F4[kind];
        }
        func_1513A24C(pos, D_80089DC0[kind], D_800A4010, n, size, kind, D_800A4344[kind], obj, bounds, arg6, arg7);
    }
    info = D_800A43B8[kind];
    if (info[0xE] == 2) {
        return;
    }
    if (smoke) {
        spec.u00 = 0xC;
        spec.u04 = 3;
        spec.pos[0] = pos[0];
        spec.pos[1] = pos[1];
        spec.pos[2] = pos[2];
        spec.u14 = 0;
        spec.u16 = 0xFF;
        spec.u18 = -0x40;
        spec.u1A = 0x45;
        spec.u28 = 0x96;
        spec.u2A = 0x64;
        spec.u1C = 998.0f;
        spec.u20 = 25.0f;
        spec.u24 = 10.0f;
        spec.dark = (kind == 2 || kind == 15 || kind == 18) ? 1 : 0;
        func_1515128C((u8 *)&spec, arg6, arg7);
    }
    if (splats) {
        dark = (kind == 2 || kind == 15 || kind == 18) ? 1 : 0;
        func_151A9DE4(pos, pos[1] - 300.0f, 300.0f, bounds, (func_150ADA20() % 6U) + 18, 0, (s32)&dark,
                      arg6, arg7);
    }
    if (finish) {
        if (kind == 2 || kind == 15) {
            func_151C6750((s32)pos, (s32)bounds, arg6, arg7);
            return;
        }
        func_1513A48C((struct17 *)pos, arg6, arg7);
    }
    return;
}
#endif
