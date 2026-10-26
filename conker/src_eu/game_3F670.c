#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void collision_select_area(s32);
void *memcpy(void *, const void *, u32);

/* was func_150121C0 */
void debris_spawn_linked(s32 arg0) {
    u8 *temp_v0;
    s32 i;
    struct {
        f32 u28[13];
        f32 u5C;
        f32 u60;
        f32 u64;
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
        u8 pad9E[0x2];
    } sp;
    s32 sp34;

    sp.u28[0] = 1.0f;
    sp.u28[1] = 1.0f;
    sp.u28[2] = 1.0f;
    sp.u28[3] = 1.0f;
    sp.u28[4] = 0.0f;
    sp.u28[5] = 0.0f;
    sp.u28[6] = 0.0f;
    sp.u28[7] = 1.0f;
    sp.u28[8] = 1.0f;
    sp.u28[9] = 1.0f;
    sp.u28[10] = 0.0f;
    sp.u28[11] = 0.0f;
    sp.u28[12] = 0.0f;
    sp.u5C = 0.0f;
    sp.u60 = 0.0f;
    sp.u64 = 0.0f;
    sp.u68 = 0.0f;
    sp.u6C = 0.0f;
    sp.u70 = 0.0f;
    sp.u74 = 0.0f;
    sp.u78 = 0xC0500;
    sp.u7C = 0x12C;
    sp.u7E = 0x21;
    sp34 = arg0;
    sp.u80 = 0;
    collision_select_area(0);
    sp.u84 = zone_tree_find_leaf((s32) (&g_debris_linked_zone_pos)[0], (s32) (&g_debris_linked_zone_pos)[2]);
    sp.u88 = 0xFF;
    sp.u89 = 0;
    sp.u8A = 6;
    sp.u8B = 0;
    sp.u8C = 0;
    sp.u8D = 0;
    sp.u8E = 0;
    sp.u8F = 0;
    sp.u90 = 3;
    sp.u92 = 0;
    sp.u94 = 0;
    sp.u98 = 0;
    sp.u9A = 1;
    sp.u9C = 0xFF;
    temp_v0 = (u8 *) mdl_particle_spawn(&sp, 0, 0, 4, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy(temp_v0 + 0x170, &sp34, 4);
        for (i = 0; i < 2; i = (u8)(i + 1)) {
            memcpy(temp_v0 + 0x90 + i * 0x40, g_identity_mtx, 0x40);
        }
    }
}
