#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    u8 c[4];
    s16 v[4];
    u16 a;
    u16 b;
} Info3850;
extern Info3850 g_fog_presets; /* was D_8008D010 */
extern s8 g_fog_level_preset_on; /* was D_800DD710 */
s32 fog_blend_presets(s32, s32, s32, s32, s32);
/* was func_15173850 */
void fog_init_from_level(s32 arg0) {
    if (*(s16 *)((u8 *)g_level_header + 0x40) == *(s16 *)((u8 *)g_level_header + 0x3C) && *(s16 *)((u8 *)g_level_header + 0x3C) == 0) {
        *(s16 *)((u8 *)g_level_header + 0x40) = 100;
    }
    g_fog_presets.c[0] = g_level_header->pad2A[0x18];
    g_fog_presets.c[1] = g_level_header->pad2A[0x19];
    g_fog_presets.c[2] = g_level_header->pad2A[0x1A];
    g_fog_presets.c[3] = g_level_header->pad2A[0x1B];
    g_fog_presets.v[0] = *(s16 *)((u8 *)g_level_header + 0x3A);
    g_fog_presets.v[1] = *(s16 *)((u8 *)g_level_header + 0x3C);
    g_fog_presets.v[2] = *(s16 *)((u8 *)g_level_header + 0x3E);
    g_fog_presets.v[3] = *(s16 *)((u8 *)g_level_header + 0x40);
    g_fog_presets.a = *(u16 *)((u8 *)g_level_header + 2);
    g_fog_presets.b = *(u16 *)((u8 *)g_level_header + 0);
    if ((s8)g_level_header->pad2A[0x1C] != -1) {
        g_fog_level_preset_on = 1;
        fog_blend_presets((s8)g_level_header->pad2A[0x1C], (s8)g_level_header->pad2A[0x1C], arg0, 0, -1);
    } else {
        g_fog_level_preset_on = 0;
        fog_blend_presets(0, 0, arg0, 0, -1);
    }
}

/* was func_15173948 */
s32 fog_identity_stub(s32 arg0, s32 arg1)
{
  return arg0;
  if (arg0)
  {
  }
}

s8 fog_level_preset_get(s32 arg0);
extern s32 g_fog_state;          /* current fog/colour state: c[4] at +0, then halfwords at +4..+0x10; was D_800DD714 */
extern s16 g_fog_near, g_fog_state_v3, g_fog_far, g_fog_state_v1, g_fog_blend_t; /* was D_800DD71A; was D_800DD71E; was D_800DD720; was D_800DD718; was D_800DD71C */
extern u16 g_fog_state_width, g_fog_state_height; /* was D_800DD722; was D_800DD724 */

/* Blend fog/colour preset `from` toward `to` by t/4096 into slot `dest` of g_fog_presets (or, for -1, the current
 * state g_fog_state; note its halfword order differs from a table entry). Presets 0x7C..0x7F are aliases. */
/* was func_15173954 */
s32 fog_blend_presets(s32 from, s32 to, s32 arg2, s32 t, s32 dest) {
    Info3850 *table = &g_fog_presets;
    u8 *out;
    s16 *v0;
    s16 *v1;
    s16 *v2;
    s16 *v3;
    s16 *pa;
    s16 *pb;
    s32 *sel;
    s32 i;
    s32 a;
    s32 b;
    s32 a2;
    s32 b2;

    g_fog_blend_t = t;
    if (dest == -1) {
        out = (u8 *)&g_fog_state;
        v0 = &g_fog_far;
        v1 = &g_fog_state_v1;
        v2 = &g_fog_near;
        v3 = &g_fog_state_v3;
        pa = (s16 *)&g_fog_state_width;
        pb = (s16 *)&g_fog_state_height;
    } else {
        out = (u8 *)&table[dest];
        v0 = (s16 *)(out + 4);
        v1 = (s16 *)(out + 6);
        v2 = (s16 *)(out + 8);
        v3 = (s16 *)(out + 0xA);
        pa = (s16 *)(out + 0xC);
        pb = (s16 *)(out + 0xE);
    }
    for (i = 0; i < 2; i++) {
        sel = (i == 0) ? &from : &to;
        switch (*sel) {
        case 0x7C:
            *sel = 1;
            break;
        case 0x7D:
        case 0x7F:
            *sel = 2;
            break;
        case 0x7E:
            *sel = fog_level_preset_get(arg2);
            break;
        }
    }
    for (i = 0; i < 4; i++) {
        a = table[from].c[i];
        out[i] = a + ((s32)((table[to].c[i] - a) * t) / 4096);
    }
    a = (u16)table[from].v[0];
    *v0 = a + ((s32)(((u16)table[to].v[0] - a) * t) / 4096);
    a = (u16)table[from].v[1];
    *v1 = a + ((s32)(((u16)table[to].v[1] - a) * t) / 4096);
    a = (u16)table[from].v[2];
    *v2 = a + ((s32)(((u16)table[to].v[2] - a) * t) / 4096);
    a = (u16)table[from].v[3];
    *v3 = a + ((s32)(((u16)table[to].v[3] - a) * t) / 4096);

    /* -1 means "the level default" (g_level_header) */
    a = (s16)table[from].a;
    if (a == -1) {
        a = g_level_header->unk2;
    }
    b = (s16)table[to].a;
    if (b == -1) {
        b = g_level_header->unk2;
    }
    *pa = ((s32)((b - a) * t) / 4096) + a;
    a2 = (s16)table[from].b;
    if (a2 == -1) {
        a2 = g_level_header->unk0;
    }
    b2 = (s16)table[to].b;
    if (b2 == -1) {
        b2 = g_level_header->unk0;
    }
    *pb = ((s32)((b2 - a2) * t) / 4096) + a2;
    return a2;
}
s32 fog_blend_presets(s32, s32, s32, s32, s32);
extern s32 g_level_bg_colour; /* was D_800DC2D8 */
extern s32 g_fog_state; /* was D_800DD714 */

/* was func_15173E34 */
void fog_apply_level_default(s32 arg0) {
    if ((s8) g_level_header->pad2A[0x1C] == -1) {
        if (g_player_views->unk5F0 & 1) {
            fog_blend_presets(6, 6, arg0, 0, -1);
            (*(u8 *)((u8 *)(&g_level_bg_colour) + 0)) = (u8) (*(u8 *)((u8 *)(&g_fog_state) + 0));
            (*(u8 *)((u8 *)(&g_level_bg_colour) + 1)) = (u8) (*(u8 *)((u8 *)(&g_fog_state) + 1));
            (*(u8 *)((u8 *)(&g_level_bg_colour) + 2)) = (u8) (*(u8 *)((u8 *)(&g_fog_state) + 2));
            return;
        }
        fog_blend_presets(0, 0, arg0, 0, -1);
        (*(u8 *)((u8 *)(&g_level_bg_colour) + 0)) = (u8) g_level_header->unk5;
        (*(u8 *)((u8 *)(&g_level_bg_colour) + 1)) = (u8) g_level_header->unk6;
        (*(u8 *)((u8 *)(&g_level_bg_colour) + 2)) = (u8) g_level_header->unk7;
    }
}

/* was func_15173F04 */
s8 fog_level_preset_get(s32 arg0) {
    return (s8) g_level_header->pad2A[0x1C];
}
