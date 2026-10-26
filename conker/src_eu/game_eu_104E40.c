#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
void func_15150258(u8 *, u8, s32);
void func_151C0AA8(u8 *, u8, s32);
void func_151C0B54(void *, u8, s32); /* P253: was s32 (a pointer in both callers) */
void func_151C0BA0(void *, u8, s32);

/* was func_150D7630 */
void impact_burst_effect(u8 *arg0, u8 arg1, s32 arg2) {
    struct {
        s16 u1C;
        s16 u1E;
        s16 u20;
        s16 u22;
        s32 u24;
        s32 u28;
        s32 u2C;
        u8 pad30[0x8];
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        s32 u50;
        s32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        s16 u68;
        s16 u6A;
        s16 u6C;
        s16 u6E;
        s16 u70;
        s16 u72;
        s8 u74;
    } sp;

    func_151C0AA8(arg0, arg1, arg2);
    func_151C0B54(arg0, arg1, arg2);
    func_151C0BA0(arg0, arg1, arg2);
    sp.u1C = 0;
    sp.u1E = 0xFF;
    sp.u20 = -0x40;
    sp.u22 = 0x47;
    sp.u24 = 6;
    sp.u28 = 4;
    (*(s32 *)((u8 *)(&sp.u2C) + 0)) = (s32) (*(s32 *)((u8 *)arg0 + 0));
    (*(s32 *)((u8 *)(&sp.u2C) + 4)) = (s32) (*(s32 *)((u8 *)arg0 + 4));
    (*(s32 *)((u8 *)(&sp.u2C) + 8)) = (s32) (*(s32 *)((u8 *)arg0 + 8));
    sp.u38 = 23.0f;
    sp.u3C = 30.0f;
    sp.u40 = 45.0f;
    sp.u44 = 53.0f;
    sp.u50 = 7;
    sp.u54 = 3;
    sp.u68 = 0x19;
    sp.u6A = 0xF;
    sp.u6C = 0x64;
    sp.u6E = 0x64;
    sp.u70 = 0xC;
    sp.u72 = 0x14;
    sp.u74 = 0;
    sp.u48 = 203.0f;
    sp.u4C = 414.0f;
    sp.u58 = 15.0f;
    sp.u5C = 0.87200004f;
    sp.u60 = -0.39800003f;
    sp.u64 = 0.36400002f;
    func_15150258(&sp.u1C, arg1, arg2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_104E40/impact_burst_effect.s")
#endif
#ifdef NON_MATCHING
void func_151C01F0(f32 *, f32 *);
void func_1515016C(u8 *, u8, s32);
void func_15150108(u8 *, u8, s32);
/* 0x54-byte effect description: func_151C01F0 fills everything except the position (+0x08) */
typedef struct {
    f32 unk0;
    s32 unk4;
    f32 pos[3];
    u8 unk14[0x40];
} ImpactInfo_150D779C;
/* 0x12-byte collision triangle (copied as a whole) */
typedef struct {
    s16 v[9];
} ImpactTri_150D779C;
// bullet_impact_effect: P253. Effect at a hit point: pos = hit position, dir = shot direction, kind (0xFF from both
// callers) and arg4 are passed to every spawner. Always spawns func_151C0AA8 / func_151C0B54 / func_151C0BA0 at pos.
// With a triangle (tri != NULL: the surface that was hit) builds { -dir, the triangle, size, info } and calls
// func_1515016C (a mark on the triangle); without one builds { -dir, size, info } and calls func_15150108. info / size
// come from func_151C01F0; info's position is the hit position.
/* was func_150D779C */
void bullet_impact_effect(ImpactTri_150D779C *tri, f32 *pos, f32 *dir, u8 kind, s32 arg4) {
    func_151C0AA8((u8 *) pos, kind, arg4);
    func_151C0B54(pos, kind, arg4);
    func_151C0BA0(pos, kind, arg4);
    if (tri != NULL) {
        struct {
            f32 normal[3];
            ImpactTri_150D779C tri;
            f32 size;
            ImpactInfo_150D779C info;
        } rec;

        rec.normal[0] = -dir[0];
        rec.normal[1] = -dir[1];
        rec.normal[2] = -dir[2];
        rec.tri = *tri;
        *(s32 *) &rec.info.pos[0] = *(s32 *) &pos[0];   /* copied as words, like the asm */
        *(s32 *) &rec.info.pos[1] = *(s32 *) &pos[1];
        *(s32 *) &rec.info.pos[2] = *(s32 *) &pos[2];
        func_151C01F0((f32 *) &rec.info, &rec.size);
        func_1515016C((u8 *) &rec, kind, arg4);
    } else {
        struct {
            f32 normal[3];
            f32 size;
            ImpactInfo_150D779C info;
        } rec;

        rec.normal[0] = -dir[0];
        rec.normal[1] = -dir[1];
        rec.normal[2] = -dir[2];
        func_151C01F0((f32 *) &rec.info, &rec.size);
        *(s32 *) &rec.info.pos[0] = *(s32 *) &pos[0];
        *(s32 *) &rec.info.pos[1] = *(s32 *) &pos[1];
        *(s32 *) &rec.info.pos[2] = *(s32 *) &pos[2];
        func_15150108((u8 *) &rec, kind, arg4);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_104E40/bullet_impact_effect.s")
#endif
