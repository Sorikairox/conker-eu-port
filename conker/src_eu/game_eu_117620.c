#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 particle_spawn_basic(void *, s32, s32, u8, s32);
s32 mdl_particle_spawn(void *, s32, s32, s32, u8, s32);
void vec3_from_angles_byte(s16, s16, f32, void *);
typedef struct { f32 x, y, z; } V3s96;
/* was func_150E9E10 */
s32 fx_spark_burst_with_light(s32 *arg0, s32 *arg1, f32 arg2, u8 arg3, s32 arg4) {
    struct {
        s32 u34;
        s32 u38;
        s16 u3C;
        s16 u3E;
        s32 u40;
        s32 u44;
        u8 u48;
        u8 u49;
        u8 u4A;
        u8 u4B;
        u8 u4C;
        u8 u4D;
        u8 u4E;
        u8 u4F;
        u8 u50;
        s8 u51;
        s16 u52;
        s16 u54;
        s16 u56;
        f32 u58;
        f32 u5C;
        f32 u60;
        V3s96 u64;
        f32 u70;
        f32 u74;
        f32 u78;
        V3s96 u7C;
        f32 u88;
        s32 u8C;
        u8 pad90[4];
        s8 u94;
        s8 u95;
        s8 u96;
        s8 u97;
        u8 pad98[0xC];
    } sp;
    struct {
        f32 u28[10];
        V3s96 u34;
        s32 u5C;
        u8 pad60[0x8];
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        s32 u78;
        s16 u7C;
        s16 u7E;
        s8 u80;
        u8 pad81[0x3];
        s32 u84;
        u8 u88;
        s8 u89;
        s8 u8A;
        s8 u8B;
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        s8 u90;
        u8 pad91[0x1];
        s8 u92;
        u8 pad93[0x1];
        s32 u94;
        s8 u98;
        u8 pad99[0x1];
        s16 u9A;
        s16 u9C;
        u8 padA0[0x8];
    } sp2;
    Header hdr;
    Header2 h2;
    s32 i;

    sp.u52 = sp.u56 = sp.u3E = (random_int() % 31U) + 0x14;
    sp.u54 = 0xFF / sp.u52;
    sp.u4F = 0xFF;
    sp.u5C = sp.u60 = ((random_float() * 608.0f) + 808.0f) * arg2;
    sp.u58 = ((random_float() * 18.0f) + 1016.0f) * 0.001f;
    sp.u51 = 0x16;
    sp.u3C = 0x2001;
    sp.u34 = 0x200005;
    sp.u38 = 0;
    sp.u40 = 0;
    sp.u44 = 0;
    sp.u4B = 0xFF;
    sp.u50 = 0xFF;
    sp.u8C = 0x800E05;
    sp.u94 = 3;
    sp.u95 = 3;
    sp.u96 = -1;
    sp.u97 = -1;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0.0f;
    if (random_int() & 1) {
        sp.u8C |= 0x40;
    }
    if (random_int() & 1) {
        sp.u8C |= 0x80;
    }
    sp.u4C = 0xFF;
    sp.u4D = 0x8E;
    sp.u4E = 0x13;
    sp.u48 = 0x2F;
    sp.u49 = 0;
    sp.u4A = 0;
    sp.u64 = *(V3s96 *)arg0;
    sp.u7C = *(V3s96 *)arg1;
    sp.u88 = 0.0f;
    particle_spawn_basic(&sp, 0, 0, arg3, arg4);
    i = (random_int() & 7) + 5;
    sp2.u78 = 0x21E8;
    sp2.u7E = 0x1B;
    sp2.u28[0] = 0.0f;
    sp2.u28[4] = 0.0f;
    sp2.u28[5] = 0.0f;
    sp2.u28[6] = 0.0f;
    sp2.u6C = 0.0f;
    sp2.u80 = 0;
    sp2.u84 = 0;
    sp2.u89 = 1;
    sp2.u8A = 0;
    sp2.u8B = 0;
    sp2.u8C = 0;
    sp2.u8D = 0;
    sp2.u8E = 0;
    sp2.u8F = 0;
    sp2.u90 = 0;
    sp2.u92 = 2;
    sp2.u94 = 0;
    sp2.u98 = 0;
    sp2.u9A = 0x14;
    sp2.u9C = 0xC;
    sp2.u28[7] = 1.0f;
    sp2.u28[8] = 1.0f;
    sp2.u28[9] = 1.0f;
    sp2.u28[1] = 0.2f;
    for (; i > 0; i--) {
        sp2.u34 = *(V3s96 *)arg0;
        sp2.u7C = (random_int() % 41U) + 0x1D;
        sp2.u88 = (random_int() % 76U) + 0xB4;
        vec3_from_angles_byte(random_int() & 0xFF, -(random_int() % 65U), ((random_float() * 2031.0f) + 1641.0f) * 0.01f, &sp2.u5C);
        sp2.u28[3] = sp2.u28[2] = ((random_float() * 3047.0f) + 1016.0f) * 0.0001f * arg2;
        sp2.u74 = ((random_float() * 99.0f) + -206.0f) * 0.01f;
        sp2.u68 = (random_float() * 101.0f) + -49.0f;
        sp2.u70 = (random_float() * 101.0f) + -49.0f;
        mdl_particle_spawn(&sp2, 3, 0xFF, 0, arg3, arg4);
    }
    hdr.unk0 = 3;
    hdr.unk1 = -1;
    hdr.unk2 = (random_int() % 13U) + 8;
    hdr.unk4 = 0;
    h2.unk0 = ((f32 *)arg0)[0];
    h2.unk4 = ((f32 *)arg0)[1];
    h2.unk8 = ((f32 *)arg0)[2];
    light_create_with_ctrl(&hdr, &h2, (random_int() % 31U) + 0x46, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg3, arg4);
}

void vec3_from_angles_byte(s16, s16, f32, void *);
s32 fx_spark_burst_with_light(s32 *, s32 *, f32, u8, s32);
void spawn_region_random_point_3d(u8 *arg0, u8 *arg1);

/* was func_150EA3B4 */
void fx_marker_spark_emitter_update(u8 *arg0)
{
  f32 temp_f20;
  s32 sp80[3];
  s32 sp74[3];
  u8 *temp_s0;
  temp_s0 = arg0 + 0x28;
  ;
  *((f32 *) (((u8 *) temp_s0) + 0x14)) = (f32) ((((*((f32 *) (((u8 *) temp_s0) + 4))) + (random_float() * (*((f32 *) (((u8 *) temp_s0) + 8))))) * D_800BE9A4) + (*((f32 *) (((u8 *) temp_s0) + 0x14))));
  if ((*((f32 *) (((u8 *) temp_s0) + 0x14))) > 1.0f)
  {
    do
    {
      temp_f20 = (*((f32 *) (((u8 *) temp_s0) + 0xC))) + ((*((f32 *) (((u8 *) temp_s0) + 0x10))) * random_float());
      spawn_region_random_point_3d(*((s32 *) (((u8 *) temp_s0) + 0)), sp80);
      vec3_from_angles_byte((s16) (random_int() & 0xFF), (s16) (0x40 - (((u32) random_int()) % 129U)), (random_float() * 600.0f) * 0.01f, sp74);
      fx_spark_burst_with_light(sp80, sp74, temp_f20, *((u8 *) (((u8 *) arg0) + 0xC)), (s32) (*((u8 *) (((u8 *) arg0) + 1))));
      *((f32 *) (((u8 *) temp_s0) + 0x14)) = (f32) ((*((f32 *) (((u8 *) temp_s0) + 0x14))) - 1.0f);
    }
    while ((*((f32 *) (((u8 *) temp_s0) + 0x14))) > 1.0f);
  }
}
