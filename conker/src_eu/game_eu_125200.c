#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
extern u8 D_800A5860[];
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F79F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F7E34.s")

extern f32 D_800A1FA8;
s32 func_150F83A0(u8 *arg0)
{
  u8 *v = arg0 + 0x110;
  f32 f;
  *((s8 *) (arg0 + 0x5C)) = (s8) ((u32) ((*((f32 *) (arg0 + 0x128))) * D_800A1FA8));
  f = (*((f32 *) (v + 0x24))) + ((*((f32 *) (v + 0x28))) * sinf(*((f32 *) (arg0 + 0x12C))));
  *((f32 *) (arg0 + 0x30)) = f;
  *((f32 *) (arg0 + 0x2C)) = f;
  *((f32 *) (v + 0x1C)) = func_15144B68(((*((f32 *) (v + 0x20))) * D_800BE9A4) + (*((f32 *) (v + 0x1C))));
  *((f32 *) (v + 0x18)) = (*((f32 *) (v + 0x18))) - D_800BE9A4;
  if ((*((f32 *) (v + 0x18))) < 0.0f)
  {
    return 0;
  }
  return 1;
}

void func_150F84D8(u8 *arg0, s16 arg1) {
    func_15140410(arg0, arg0 + 0x110, arg0 + 0x11C, arg1);
}

#ifdef NON_MATCHING
s32 func_15154728(u8 *, f32, f32, f32, f32, u8, s32); /* P95: f32 parameter */
#else
void func_15154728(u8 *, f32, s32, f32, f32, u8, s32);
#endif
void func_151D44C4(u8 *, u8, s32);

void func_150F850C(u8 *arg0, u8 arg1, s32 arg2) {
#ifdef NON_MATCHING
    func_15154728(arg0, 9.0f + func_150ADA68() * 3.0f, 0.511905f, 70.0f + func_150ADA68() * 70.0f, 0.0f, arg1, arg2); /* P95: float literal (asm passes the bits 0x3F030C35) */
#else
    func_15154728(arg0, 9.0f + func_150ADA68() * 3.0f, 0x3F030C35, 70.0f + func_150ADA68() * 70.0f, 0.0f, arg1, arg2);
#endif
    func_151D44C4(arg0, arg1, arg2);
}

#ifdef NON_MATCHING
/* P159 */
s32 func_15132BBC(void *, s32, s32, s32, s32, s32, s32);
extern u8 D_800A5860[];
s32 memcpy(s32, s32 *, s32);
// record_particle_spawn: spawns particle type 0x2F (func_15132BBC) lasting `life` at the record's point rec[0..2]
// with the angles rec[3..5], scale 1 / 0.02 and the colour of D_800A5860; the 0x14 extra bytes at +0x170 keep
// the record pointer, its point and 0.0.
void func_150F85AC(f32 *rec, s16 life, u8 flag, s32 arg3) {
    struct {
        /* spawn block for func_15132BBC (0x7C bytes) */
        f32 scale[4];
        f32 angle[3];
        f32 one[3];
        f32 pos[3];
        f32 vel[3];
        s32 color[3];
        f32 u4C;
        s32 flags50;
        s16 life;
        s16 type;
        u8 u58;
        u8 pad59[3];
        s32 u5C;
        u8 u60;
        u8 u61;
        u8 u62[7];
        u8 u69;
        u8 u6A;
        u8 pad6B;
        s32 u6C;
        u8 u70;
        u8 pad71;
        s16 u72;
        s16 u74;
        u8 pad76[2];
        s32 u78;
        /* extra data copied to particle +0x170 (0x14 bytes) */
        f32 *rec;
        f32 recPos[3];
        f32 u10;
    } sp;
    s32 i;
    s32 p;

    sp.rec = rec;
    sp.recPos[0] = rec[0];
    sp.recPos[1] = rec[1];
    sp.recPos[2] = rec[2];
    sp.u10 = 0.0f;
    sp.scale[0] = 1.0f;
    sp.scale[1] = 1.0f;
    sp.scale[2] = 0.020000001f; /* 0x3CA3D70B */
    sp.scale[3] = 0.020000001f; /* 0x3CA3D70B */
    sp.angle[0] = rec[3];
    sp.angle[1] = rec[4];
    sp.angle[2] = rec[5];
    sp.one[0] = 1.0f;
    sp.one[1] = 1.0f;
    sp.one[2] = 1.0f;
    sp.pos[0] = rec[0];
    sp.pos[1] = rec[1];
    sp.pos[2] = rec[2];
    sp.vel[0] = 0.0f;
    sp.vel[1] = 0.0f;
    sp.vel[2] = 0.0f;
    sp.color[0] = ((s32 *)D_800A5860)[0];
    sp.color[1] = ((s32 *)D_800A5860)[1];
    sp.color[2] = ((s32 *)D_800A5860)[2];
    sp.u4C = 0.0f;
    sp.flags50 = 0x980;
    sp.life = life;
    sp.type = 0x2F;
    sp.u58 = 0;
    sp.u5C = 0;
    sp.u60 = 0xFF;
    sp.u61 = 0x14;
    for (i = 0; i < 7; i++) {
        sp.u62[i] = 0;
    }
    sp.u6A = 0;
    sp.u6C = 0;
    sp.u70 = 0;
    sp.u72 = 1;
    sp.u74 = 0xFF;
    sp.u78 = 0;
    p = func_15132BBC(&sp, 3, 0xFF, 0, 0xB4, flag, arg3);
    if (p != 0) {
        memcpy(p + 0x170, (s32 *)&sp.rec, 0x14);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F85AC.s")
#endif

#ifdef NON_MATCHING
s32 func_15145128(f32 *, f32 *, f32 *, s32 *);
s32 func_15146078(f32 *, s32 *, s32 *);
s32 memcpy(s32, s32 *, s32);

s32 func_150F873C(u8 *arg0) {
    struct {
        s32 u98;
        u8 pad9C[0x8];
        s32 uA4;
        u8 padA8[0x8];
        f32 uB0;
        f32 uB4;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        s8 uC4;
        s8 uC5;
        s16 uC6;
        s16 uC8;
        u8 padCA[0x2];
        s32 uCC;
        s32 uD0;
        s8 uD4;
        s8 uD5;
        s8 uD6;
        s8 uD7;
        f32 uD8;
        f32 uDC;
        s32 uE0;
        u8 padE4[0x8];
        s32 uEC;
        u8 padF0[0x8];
        f32 uF8;
        f32 uFC;
        f32 u100;
        s32 u104;
        s8 u108;
        s8 u109;
        s8 u10A;
        s8 u10B;
        s32 u10C;
        s8 u110;
        u8 pad111[0x3];
        s32 u114;
        u8 pad118[0x8];
        f32 u120;
        f32 u124;
        u8 pad128[0x4];
        f32 u12C;
        f32 u130;
        f32 u134;
        s32 u138;
        f32 u13C;
        f32 u140;
        f32 u144;
        f32 u148;
    } sp;
    f32 sp94;
    f32 var_f20;
    u8 *temp_t4;
    u8 *temp_s0;
    u8 *temp_s5;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x170));
    (*(f32 *)((u8 *)arg0 + 0x38)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0));
    (*(f32 *)((u8 *)arg0 + 0x3C)) = (f32) (*(f32 *)((u8 *)temp_v0 + 4));
    (*(f32 *)((u8 *)arg0 + 0x40)) = (f32) (*(f32 *)((u8 *)temp_v0 + 8));
    (*(f32 *)((u8 *)arg0 + 0x20)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0xC));
    (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x10));
    (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (*(f32 *)((u8 *)temp_v0 + 0x14));
    sp.u140 = (*(f32 *)((u8 *)arg0 + 0x38)) - (*(f32 *)((u8 *)arg0 + 0x174));
    sp.u144 = (*(f32 *)((u8 *)arg0 + 0x3C)) - (*(f32 *)((u8 *)arg0 + 0x178));
    sp.u148 = (*(f32 *)((u8 *)arg0 + 0x40)) - (*(f32 *)((u8 *)arg0 + 0x17C));
    (*(f32 *)((u8 *)arg0 + 0x180)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x180)) + D_800BE9A4);
    if (func_15145128(&sp.u140, &sp.u12C, &sp.u13C, &sp.u138) != 0) {
        temp_s0 = arg0 + 0x170;
        var_f20 = sp.u13C * 0.05f;
        sp.u120 = sp.u130 * 20.0f;
        sp.u124 = sp.u134 * 20.0f;
        if (var_f20 > 1.0f) {
            sp94 = (*(f32 *)((u8 *)temp_s0 + 0x10)) / var_f20;
            func_15146078(&sp.u140, &sp.u98, &sp.uA4);
            temp_t4 = ((u8 *)&D_800A5860);
            sp.uC4 = 0x7A;
            sp.uC5 = 0;
            sp.uC6 = 0x4404;
            sp.uC8 = 0xA;
            sp.uCC = 0;
            sp.uD0 = 0;
            sp.uD4 = 0xFF;
            sp.uD5 = 0xFF;
            sp.uD6 = 0xFF;
            sp.uD7 = 0xFF;
            sp.uB8 = 0.46300003f;
            sp.uBC = 8.241f;
            sp.uDC = 0.0f;
            sp.uD8 = 0.0f;
            sp.uC0 = 3.889f;
            (*(s32 *)((u8 *)(&sp.uEC) + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
            (*(s32 *)((u8 *)(&sp.uEC) + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
            (*(s32 *)((u8 *)(&sp.uEC) + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
            sp.uF8 = 1.0f;
            sp.uFC = 1.0f;
            sp.u100 = 1.0f;
            sp.u104 = 0xCC0008;
            sp.u109 = 0xFF;
            sp.u10A = 0;
            sp.u10B = 6;
            sp.u10C = 0;
            sp.u110 = 0xFF;
            sp.u114 = 0;
            temp_s5 = temp_s0 + 4;
            do {
                sp.uB4 = 4.712389f;
                sp.uB0 = 27.0f - (*(f32 *)((u8 *)temp_s0 + 0x10));
                (*(s32 *)((u8 *)(&sp.uE0) + 0)) = (s32) (*(s32 *)((u8 *)temp_s5 + 0));
                (*(s32 *)((u8 *)(&sp.uE0) + 4)) = (s32) (*(s32 *)((u8 *)temp_s5 + 4));
                (*(s32 *)((u8 *)(&sp.uE0) + 8)) = (s32) (*(s32 *)((u8 *)temp_s5 + 8));
                sp.u108 = (s8) (u32) (sp.uB0 * 6.4814816f);
                temp_v0_2 = func_1513D2F0(&sp.uC4, (s32) ((u8 *)&D_800A4AA0), 0x24U, 0U, 0U, 0x21U, 0U, 0, 0, 0x2C, (u8) (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                if (temp_v0_2 != NULL) {
                    memcpy(temp_v0_2 + 0x110, &sp.u98, 0x2C);
                }
                var_f20 -= 1.0f;
                (*(f32 *)((u8 *)temp_s0 + 4)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 4)) + (sp.u12C * 20.0f));
                (*(f32 *)((u8 *)temp_s0 + 8)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 8)) + sp.u120);
                (*(f32 *)((u8 *)temp_s0 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0xC)) + sp.u124);
                (*(f32 *)((u8 *)temp_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0x10)) - sp94);
            } while (var_f20 > 1.0f);
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_125200/func_150F873C.s")
#endif