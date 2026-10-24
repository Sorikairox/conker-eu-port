#ifdef NON_MATCHING
s32 func_15134070(struct127 *arg0);
void func_1515C7B4(u8 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
void func_1504715C(void *, u8 *);
s32 func_1514672C(f32 *);
s32 func_15046F70(f32 *, s32, f32, f32 *);
void func_1513A24C(f32 *pos, s32 *ids, s32 *scales, s32 n, f32 scale, u8 kind, u8 arg6, u8 *obj, s32 *bounds, u8 arg9, s32 argA);
void func_1513A48C(struct17 *arg0, u8 arg1, s32 arg2);
s32 func_15136698(f32 arg0, f32 arg1, u8 arg2, u8 arg3, s16 arg4, s32 arg5, struct17 *arg6, u8 arg7, u8 arg8, u8 arg9, s32 argA);
typedef struct { f32 x, y, z; } V3; /* as game_eu_1E3DD0 */
s32 func_151B61A0(V3 *arg0, V3 *arg1, f32 arg2, V3 *arg3, V3 *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, u8 argA, u8 argB, u8 argC, s32 argD);
s32 func_151B65C0(V3 *arg0, V3 *arg1, f32 arg2, V3 *arg3, V3 *arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8, f32 arg9, u8 argA, u8 argB, u8 argC, s32 argD);
void func_15145A50(struct127 *arg0);
f32 func_150ADA68(void);
s32 func_150ADA20(void);
extern s32 *D_80089DC0[];       /* per hit kind: debris model ids */
extern s32 D_800A4010[];        /* debris scales (all 1.0) */
extern s32 D_800A42F4[];        /* per hit kind: debris kinds */
extern s32 D_800A4344[];        /* per hit kind: debris spec byte +0x40 */
extern u8 D_800A43B8[][16];     /* per hit kind: +0xE == 2: debris only */

// object_break_effects: the break effects of `obj` (called by game_83300 with (obj, 0xFF, 1)): nothing for hit kind
// 0x63 (func_15134070) or when no floor is found under the effect position + 100 (func_1514672C). The floor
// (func_15046F70 within 500 below, bounds record) sets the drop height; then debris without the first two models
// (func_1513A24C, two kinds fewer) at the effect position (func_1515C7B4). Unless the kind's D_800A43B8 +0xE is 2:
// func_1513A48C at the position and, on a floor with bounds +0x1C bit 0 (water), a splash (func_15136698, random
// sizes / alpha / life) and a ripple model (func_151B61A0 or func_151B65C0 at random, 10 above the floor, random
// rotation, scale 0.6..0.7). Ends with func_15145A50(obj). arg1 / arg2 are passed on to every spawner.
void func_1513783C(struct127 *obj, s32 arg1, s32 arg2) {
    u8 *o = (u8 *)obj;
    s32 bounds[9];
    f32 pos[3];
    f32 sizeX;
    f32 sizeY;
    f32 size;
    struct17 drop;
    V3 at;
    V3 vel;
    V3 rot;
    V3 zero;
    s32 (*ripple)(V3 *, V3 *, f32, V3 *, V3 *, f32, s16, u8, s32, f32, u8, u8, u8, s32);
    s32 kind;
    s32 water;
    f32 r1, r2;
    u32 i1, i2, i3;

    if (obj == NULL) {
        return;
    }
    kind = func_15134070(obj);
    if (kind == 0x63) {
        return;
    }
    size = (*(f32 *)(o + 0x14C) + *(f32 *)(o + 0x150)) * 0.5f;
    func_1515C7B4(o, pos, &sizeX, &sizeY);
    func_1504715C(bounds, o);
    drop.unk0 = pos[0];
    drop.unk4 = pos[1] + 100.0f;
    drop.unk8 = pos[2];
    if (func_1514672C((f32 *)&drop) == 0) {
        return;
    }
    if (func_15046F70((f32 *)&drop, 0, drop.unk4 - 500.0f, (f32 *)bounds) != 0) {
        water = (((u8 *)bounds)[0x1C] & 1) ? 1 : 0;
        drop.unk4 = *(f32 *)&bounds[0];
    } else {
        drop.unk0 = pos[0];
        drop.unk4 = pos[1];
        drop.unk8 = pos[2];
        water = 0;
    }
    func_1513A24C(pos, D_80089DC0[kind] + 2, D_800A4010, D_800A42F4[kind] - 2, size, kind, D_800A4344[kind], o, bounds,
                  arg1, arg2);
    if (D_800A43B8[kind][0xE] != 2) {
        func_1513A48C((struct17 *)pos, arg1, arg2);
        if (water) {
            r1 = func_150ADA68();
            r2 = func_150ADA68();
            i1 = func_150ADA20();
            i2 = func_150ADA20();
            i3 = func_150ADA20();
            func_15136698((r1 * 25.0f + 75.0f) * 0.001f, (r2 * 106.0f + 75.0f) * 1e-05f, i1 % 101 + 0x9B,
                          i2 % 101 + 0x64, i3 % 56 + 0xCB, (s32)&bounds[1], &drop, 1, 1, arg1, arg2);
            ripple = (func_150ADA20() & 1) ? func_151B61A0 : func_151B65C0;
            at.x = drop.unk0;
            at.y = drop.unk4 + 10.0f;
            at.z = drop.unk8;
            vel.x = 0.0f;
            vel.y = 0.0f;
            vel.z = 0.0f;
            rot.x = func_150ADA68() * 360.0f;
            rot.y = func_150ADA68() * 360.0f;
            zero.x = 0.0f;
            zero.y = 0.0f;
            zero.z = 0.0f;
            rot.z = func_150ADA68() * 360.0f;
            ripple(&at, &vel, (func_150ADA68() * 101.0f + 600.0f) * 0.001f, &rot, &zero, 0.0f, 1000, 0xFF, 0xFF, 1.0f,
                   3, 0, arg1, arg2);
        }
    }
    func_15145A50(obj);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_161520/func_1513783C.s")
#endif
