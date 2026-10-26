#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 node_spawn_sprite(s32 *, s32, s32, s32, s32, s32);
extern s32 D_8008CDEC;

/* was func_15174690 */
void fx_dust_puff_behind_obj(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8) {
    struct {
        s32 u40;
        s32 u44;
        s32 u48;
        s16 u4C;
        s16 u4E;
        s16 u50;
        s16 u52;
        s16 u54;
        s16 u56;
        s16 u58;
        s16 u5A;
        u8 pad5C[0x3];
        s8 u5F;
        s16 u60;
        s16 u62;
        s16 u64;
        s16 u66;
        s16 u68;
        s8 u6A;
        s8 u6B;
        s8 u6C;
        s8 u6D;
        s8 u6E;
        s8 u6F;
        u8 pad70[0x4];
        s16 u74;
        u8 pad76[0x6];
        s32 u7C;
        u8 pad80[0x4];
        f32 u84;
        u8 pad88[0x4];
        f32 u8C;
    } sp;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f22;
    f32 var_f20;
    f32 var_f22;
    s32 temp_v0_2;
    s32 temp_v0_3;
    struct127 *temp_v0;

    temp_v0 = &g_objects[arg0];
    if ((temp_v0->in_water == 0) && (temp_v0->unk118 == -10000.0f)) {
        temp_f20 = temp_v0->x_position;
        temp_f12 = temp_v0->unk40 * 0.017453292f;
        temp_f22 = temp_v0->z_position;
        sp.u84 = temp_v0->y_position + 5.0f;
        sp.u8C = temp_f12;
        var_f20 = temp_f20 - (10.0f * sinf(temp_f12));
        var_f22 = temp_f22 - (10.0f * cosf(temp_f12));
        if (arg1 != 0) {
            temp_v0_2 = random_int();
            sp.u7C = temp_v0_2;
            var_f20 += (f32) (temp_v0_2 % arg1);
            temp_v0_3 = random_int();
            sp.u7C = temp_v0_3;
            var_f22 += (f32) (temp_v0_3 % arg1);
        }
        if (arg3 != 0) {
            arg2 += random_int() % (u32) arg3;
        }
        sp.u44 = arg2;
        sp.u52 = (s16) (s32) sp.u84;
        sp.u4E = 0x100;
        sp.u40 = D_8008CDEC;
        sp.u48 = arg5;
        sp.u50 = (s16) (s32) var_f20;
        sp.u4C = 0;
        sp.u56 = 0;
        sp.u58 = 0;
        sp.u5A = 0;
        sp.u5F = 5;
        sp.u62 = 0;
        sp.u68 = 0x200;
        sp.u6A = 0;
        sp.u6B = 0;
        sp.u6C = 0xFF;
        sp.u6D = 0xFF;
        sp.u6E = 0xFF;
        sp.u6F = 0xFF;
        sp.u74 = 0;
        sp.u64 = (s16) arg4;
        sp.u66 = (s16) arg4;
        sp.u54 = (s16) (s32) var_f22;
        sp.u60 = (s16) arg6;
        node_spawn_sprite(&sp.u40, 0, 0, -1, (s32) arg7, arg8);
    }
}
/* was func_15174E90 */
void fx_puff_fade_grow_tick(u8 *arg0)
{
  s32 v;
  s32 temp_v1;
  v = arg0[0x3F];
  if (v >= 0xC9)
  {
    v = 0xC8;
  }
  v -= D_800BE9E4 * (*((s32 *) (arg0 + 0x18)));
  if (v < 0)
  {
    *((s16 *) (arg0 + 0x38)) = 0;
    return;
  }
  temp_v1 = *((s32 *) (arg0 + 0x14));
  arg0[0x3F] = v;
  *((s16 *) (arg0 + 0x34)) = (*((s16 *) (arg0 + 0x34))) + temp_v1;
  *((s16 *) (arg0 + 0x36)) = (*((s16 *) (arg0 + 0x36))) + ((temp_v1 * 8) / 7);
}
