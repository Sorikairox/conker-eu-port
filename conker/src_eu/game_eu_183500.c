#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1515F10C(s32);
#endif

struct_eu_node *func_15156544(s32 arg0);


s32 func_1518C900(s32);
struct_eu_node *func_15155CF0(s32 arg0, s32 arg1)
{
  struct_eu_node *temp_v0;
  temp_v0 = node_alloc(0x50, 0, 0xA0, 1, (u8) arg1, 1U);
  if (temp_v0 == 0)
  {
    return temp_v0;
  }
  *((s8 *) (((u8 *) temp_v0) + 0x10)) = (s8) arg0;
  *((s8 *) (((u8 *) temp_v0) + 0x11)) = 0;
  *((s32 *) (((u8 *) temp_v0) + 0x14)) = 0;
  *((f32 *) (((u8 *) temp_v0) + 0x98)) = 0.0f;
  func_1518C900(0xA6);
  return temp_v0;
}

struct_eu_node *func_15155CF0(s32, s32);

void func_15155D6C(s32 arg0, s32 arg1, f32 arg2) {
    struct_eu_node *var_v0;

    var_v0 = func_15156544(arg0);
    if (var_v0 == NULL) {
        var_v0 = func_15155CF0(arg0, 0xFF);
    }
    if (var_v0 != NULL) {
        (*(f32 *)((u8 *)var_v0 + 0x98)) = arg2;
        if (*(&D_800CC37D + (arg0 * 0x32C)) != 0) {
            (*(s16 *)((u8 *)var_v0 + 0xE)) = 0;
            (*(s8 *)((u8 *)var_v0 + 0x11)) = 0;
            return;
        }
        (*(s8 *)((u8 *)var_v0 + 0x11)) = 3;
        (*(s16 *)((u8 *)var_v0 + 0xE)) = (s16) arg1;
    }
}

#ifdef NON_MATCHING
u8 *func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_15155E0C(u8 *arg0) {
    struct127 *sp48;
    f32 sp38;
    f32 var_f2;
    s16 temp_v0;
    s16 var_v0_2;
    struct126 *temp_v1_2;
    struct127 *temp_t0;
    u8 temp_a2;
    u8 temp_v1;
    u8 var_v0;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_a1_3;
    u8 *temp_a1_4;
    u8 *var_v0_3;

    temp_a2 = (*(u8 *)((u8 *)arg0 + 0x10));
    temp_v1 = (*(u8 *)((u8 *)arg0 + 0x11));
    temp_t0 = &D_800CC2D0[temp_a2];
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_v1_2 = D_800CC2D0[temp_a2].unk31C;
        var_v0 = 0;
        if (temp_v1_2 != NULL) {
            var_v0 = temp_v1_2->unk75;
        }
        if (!(var_v0 & 0x80) && (var_v0 != 0x2A) && (var_v0 != 0x2B) && ((var_v0 != 0x42) || !(D_800D2E68 & 4)) && (var_v0 != 0x2C) && (temp_v1_2->unk197 == 0) && (var_v0 != 0) && (var_v0 != 0x1F) && (temp_t0->in_water == 0)) {
            (*(u8 *)((u8 *)arg0 + 0x11)) = 1U;
            (*(s16 *)((u8 *)arg0 + 0xE)) = 0x78;
            func_10010F30(0x1EB, 0x7FFFU, 0x40U, 0, 0U);
            return;
        }
        temp_a1 = (*(u8 **)((u8 *)arg0 + 0x14));
        if (temp_a1 != NULL) {
            func_1515F10C((s32) temp_a1);
            (*(u8 **)((u8 *)arg0 + 0x14)) = NULL;
            return;
        }
        return;
    case 1:
        var_v0_2 = (*(s16 *)((u8 *)arg0 + 0xE)) - D_800BE9E4;
        if ((var_v0_2 <= 0) || (D_800CC2D0[temp_a2].unk31C->unk75 == 0)) {
            (*(u8 *)((u8 *)arg0 + 0x11)) = 2U;
            var_v0_2 = 0;
        }
        (*(s16 *)((u8 *)arg0 + 0xE)) = var_v0_2;
        temp_a1_2 = (*(u8 **)((u8 *)arg0 + 0x14));
        (*(u8 *)((u8 *)arg0 + 0x12)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x12)) + (D_800BE9E4 * 2));
        if (temp_a1_2 != NULL) {
            if (D_800CC2D0[temp_a2].unk31C->unk75 == 5) {
                var_f2 = 85.0f;
            } else {
                var_f2 = 0.0f;
            }
            (*(s16 *)((u8 *)temp_a1_2 + 0xE)) = (s16) (s32) temp_t0->x_position;
            sp38 = var_f2;
            sp48 = temp_t0;
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x14))) + 0x10)) = (s16) (s32) ((func_15048A40((*(u8 *)((u8 *)arg0 + 0x12))) * 15.0f) + (temp_t0->y_position + 160.0f + (*(f32 *)((u8 *)arg0 + 0x98)) + var_f2));
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x14))) + 0x12)) = (s16) (s32) temp_t0->z_position;
            return;
        }
        var_v0_3 = func_1515D5F8(0, 0, 0, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
block_38:
        (*(u8 **)((u8 *)arg0 + 0x14)) = var_v0_3;
        break;
    case 2:
        if (D_800CC2D0[temp_a2].unk31C->unk75 == 0) {
            (*(u8 *)((u8 *)arg0 + 0x11)) = 0U;
        }
        temp_a1_3 = (*(u8 **)((u8 *)arg0 + 0x14));
        if (temp_a1_3 != NULL) {
            func_1515F10C((s32) temp_a1_3);
            (*(u8 **)((u8 *)arg0 + 0x14)) = NULL;
            return;
        }
        break;
    case 3:
        temp_v0 = (*(s16 *)((u8 *)arg0 + 0xE)) - D_800BE9E4;
        if (temp_v0 <= 0) {
            (*(u8 *)((u8 *)arg0 + 0x11)) = 2U;
            (*(s16 *)((u8 *)arg0 + 0xE)) = 0;
            return;
        }
        (*(s16 *)((u8 *)arg0 + 0xE)) = temp_v0;
        temp_a1_4 = (*(u8 **)((u8 *)arg0 + 0x14));
        (*(u8 *)((u8 *)arg0 + 0x12)) = (u8) ((*(u8 *)((u8 *)arg0 + 0x12)) + (D_800BE9E4 * 2));
        if (temp_a1_4 != NULL) {
            (*(s16 *)((u8 *)temp_a1_4 + 0xE)) = (s16) (s32) temp_t0->x_position;
            sp48 = temp_t0;
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x14))) + 0x10)) = (s16) (s32) ((func_15048A40((*(u8 *)((u8 *)arg0 + 0x12))) * 15.0f) + (temp_t0->y_position + 160.0f));
            (*(s16 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x14))) + 0x12)) = (s16) (s32) temp_t0->z_position;
            return;
        }
        var_v0_3 = func_1515D5F8(0, 0, 0, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
        goto block_38;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_183500/func_15155E0C.s")
#endif
extern Gfx **D_800E0810;
typedef struct {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ u8 obj;
    /* 0x11 */ u8 mode;
    /* 0x12 */ u8 ang;
    /* 0x13 */ u8 pad13[5];
    /* 0x18 */ Mtx mtx[2];
    /* 0x98 */ f32 yoff;
} Unk1515626C;
Gfx *func_15096D44(Gfx *arg0);

Gfx *func_1515626C(Gfx *gdl, Unk1515626C *arg1, s16 arg2) {
    u8 mode;
    u8 obj;
    struct127 *p;

    mode = arg1->mode;
    obj = arg1->obj;
    if (mode == 1 || mode == 3) {
        f32 rot;
        s32 pad; // fakematch: slot 0x58 between rot and h
        f32 h;

        p = &D_800CC2D0[obj];
        if (p->unk31C->unk75 == 5) {
            h = 85.0f;
        } else {
            h = 0.0f;
        }
        rot = D_800DBFF0[arg2].unk380;
        gdl = func_15096D44(gdl);
        func_15043D90(&arg1->mtx[D_800BE9C0], 0.0f, rot, 0.0f, 2.25f, 2.25f, 2.25f, p->x_position,
                      func_15048A40(arg1->ang) * 15.0f + (p->y_position + 160.0f + h + arg1->yoff), p->z_position);
        gSPMatrix(gdl++, &arg1->mtx[D_800BE9C0], G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPClearGeometryMode(gdl++, G_ZBUFFER);
        gSPDisplayList(gdl++, *D_800E0810);
        gSPSetGeometryMode(gdl++, G_ZBUFFER);
    }
    return gdl;
}

void func_1515F10C(s32);
s32 func_1518CF74(s32);
void func_15156468(struct102 *arg0)
{
  u8 *p = (u8 *) arg0;
  s32 temp_a2;
  temp_a2 = *((s32 *) (p + 0x14));
  if (temp_a2 != 0)
  {
    func_1515F10C(temp_a2);
  }
  if (((!arg0) && (!arg0)) && (!arg0)) // fakematch: dead test from the permuter
  {
  }
  node_retire(p);
  func_1518CF74(0xA6);
}

void func_151564AC(void) {
    u8 *temp_v0 = (u8 *)func_15156544(D_800C3E78);

    if (temp_v0 != NULL) {
        if (temp_v0[0x11] == 2) {
            temp_v0[0x11] = 0;
        } else if (temp_v0[0x11] == 3) {
            temp_v0[0x11] = 2;
        }
    }
}

void func_15156500(void) {
    u8 *temp_v0 = (u8 *)func_15156544(D_800C3E78);

    if ((temp_v0 != NULL) && (temp_v0[0x11] == 3)) {
        temp_v0[0x11] = 1;
    }
}

struct_eu_node *func_15156544(s32 arg0) {
    s32 i;
    struct_eu_node *node;

    for (i = 0; i < 2; i++) {
        for (node = D_800DD280[i][80]; node != NULL; node = node->next) {
            if (arg0 == ((u8 *)node)[0x10]) {
                return node;
            }
        }
    }
    return NULL;
}

void func_15156598(u8 *arg0, struct127 **arg1, u8 arg2) {
    if (arg2 == 0) {
        s32 a;
        a = arg1[0] - D_800CC2D0;
        if ((a >= 0) && (a < 25) && (a == arg0[0x10])) {
            node_destroy((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        s32 a;
        s32 b;
        a = arg1[0] - D_800CC2D0;
        b = arg1[1] - D_800CC2D0;
        if ((a >= 0) && (a < 25) && (b >= 0) && (b < 25)) {
            if (a == arg0[0x10]) { arg0[0x10] = b; }
            else if (b == arg0[0x10]) { arg0[0x10] = a; }
        }
    }
}
