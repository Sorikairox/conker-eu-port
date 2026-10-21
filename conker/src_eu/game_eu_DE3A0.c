#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_8009FBE0[];
extern u8 D_8009FBE8[];
#endif


#ifdef NON_MATCHING
void func_1504715C(void *, u8 *);
s32 func_15143E24(struct127 *);
extern s32 D_8009FBE4;
extern s32 D_8009FBEC;

void func_150B0B90(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3) {
    struct {
        s16 u3C;
        s16 u3E;
        s16 u40;
        s16 u42;
        struct17 u44;
        f32 u50;
        f32 u54;
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
        s16 u74;
        s16 u76;
        s8 u78;
        u8 pad79[0x3];
        f32 u7C;
        s16 u80;
        s16 u82;
        s32 u84;
        s32 u88;
        s32 u8C;
        s32 u90;
        u8 pad94[0x8];
        s16 u9C;
        s16 u9E;
        s16 uA0;
        s16 uA2;
        f32 uA4;
        f32 uA8;
        f32 uAC;
        f32 uB0;
        s16 uB4;
        s16 uB6;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s32 uC4;
        s32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        s16 uD8;
        s16 uDA;
        s16 uDC;
        s16 uDE;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        s16 uF0;
        s16 uF2;
        f32 uF4;
        f32 uF8;
        f32 uFC;
        f32 u100;
        f32 u104;
        f32 u108;
        s32 u10C;
        u8 pad110[0x23];
        s8 u133;
        f32 u134;
        f32 u138;
        f32 u13C;
    } sp;
    s32 temp_s1;

    temp_s1 = arg2 & 0xFF;
    sp.u134 = arg0->x_position;
    sp.u138 = arg0->y_position;
    sp.u13C = arg0->z_position;
    sp.u133 = func_15143E24(arg1) + 0x40;
    func_1504715C(&sp.u10C, arg0);
    if (arg0->id == 0xA6) {
        sp.u104 = sp.u138 + 50.0f;
        sp.u100 = sp.u134;
        sp.u108 = sp.u13C;
        func_151C384C(&sp.u100, temp_s1 & 0xFF, arg3);
        sp.uC4 = 0xA;
        sp.uC8 = 0xA;
        (*(f32 *)((u8 *)(&sp.uCC) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u134) + 0));
        (*(f32 *)((u8 *)(&sp.uCC) + 4)) = (f32) (*(f32 *)((u8 *)(&sp.u134) + 4));
        (*(f32 *)((u8 *)(&sp.uCC) + 8)) = (f32) (*(f32 *)((u8 *)(&sp.u134) + 8));
        sp.uE0 = 7.0f;
        sp.uE4 = 17.0f;
        sp.uD8 = sp.u133 - 0x28;
        sp.uDA = 0x50;
        sp.uDC = -0x2D;
        sp.uDE = 0x1A;
        sp.uF0 = 0x19;
        sp.uF2 = 0x19;
        sp.uE8 = -0.8f;
        sp.uEC = 0.344f;
        sp.uF4 = 0.707f;
        sp.uF8 = 0.507f;
        sp.uFC = 26.411001f;
        func_15152700(&sp.uC4, ((u8 *)&D_8009FBE0), &D_8009FBE4, 1, 0.0f, 0U, (u8) temp_s1, arg3);
        return;
    }
    sp.u88 = 0xA;
    sp.u8C = 0xA;
    (*(f32 *)((u8 *)(&sp.u90) + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u134) + 0));
    (*(f32 *)((u8 *)(&sp.u90) + 4)) = (f32) (*(f32 *)((u8 *)(&sp.u134) + 4));
    (*(f32 *)((u8 *)(&sp.u90) + 8)) = (f32) (*(f32 *)((u8 *)(&sp.u134) + 8));
    sp.uA4 = 7.0f;
    sp.uA8 = 17.0f;
    sp.u9C = sp.u133 - 0x28;
    sp.u9E = 0x50;
    sp.uA0 = -0x15;
    sp.uA2 = 0xD;
    sp.uB4 = 0x19;
    sp.uB6 = 0x19;
    sp.uAC = -0.8f;
    sp.uB0 = 0.344f;
    sp.uB8 = 0.049000002f;
    sp.uBC = 0.102000006f;
    sp.uC0 = 26.411001f;
    func_15152700(&sp.u88, ((u8 *)&D_8009FBE8), &D_8009FBEC, 1, 0.0f, 0U, (u8) temp_s1, arg3);
    sp.u44.unk0 = (*(f32 *)((u8 *)(&sp.u134) + 0));
    sp.u44.unk4 = (*(f32 *)((u8 *)(&sp.u134) + 4));
    sp.u44.unk8 = (*(f32 *)((u8 *)(&sp.u134) + 8));
    sp.u50 = 3.05f;
    sp.u68 = 7;
    sp.u6A = 3;
    sp.u3C = sp.u133 - 0x3C;
    sp.u3E = 0x78;
    sp.u40 = -0x1E;
    sp.u42 = 0x10;
    sp.u6C = 3;
    sp.u6E = 2;
    sp.u70 = 0x14;
    sp.u72 = 0x14;
    sp.u74 = 0x9B;
    sp.u76 = 0x64;
    sp.u80 = 0x10;
    sp.u82 = 0xF;
    sp.u84 = 0;
    sp.u78 = 0;
    sp.u54 = 5.0099998f;
    sp.u58 = 0.70000005f;
    sp.u5C = 0.50100005f;
    sp.u60 = 15.1f;
    sp.u64 = 20.800001f;
    sp.u7C = 0.5f;
    func_15154488((struct_eu_15154488 *) &sp.u3C, &sp.u44, (s32) &sp.u10C, temp_s1 & 0xFF, arg3);
    sp.u78 = 1;
    func_15154488((struct_eu_15154488 *) &sp.u3C, &sp.u44, (s32) &sp.u10C, temp_s1 & 0xFF, arg3);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_DE3A0/func_150B0B90.s")
#endif