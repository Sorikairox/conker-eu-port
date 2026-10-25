#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
f32 func_15143E64(f32 *);
s32 memcpy(u8 *, s32, s32);

u8 *func_150C5870(s32 arg0, s32 arg1) {
    struct {
        f32 u20;
        f32 u24;
        f32 u28;
        u8 * u2C;
    } sp;
    u8 *temp_v0;

    temp_v0 = func_15167A68(0x46, 0, arg1 + 0xC8, 1, 0xFFU, 1U);
    if (temp_v0 == NULL) {
        return NULL;
    }
    sp.u2C = temp_v0;
    memcpy(temp_v0 + 0x18, arg0, 0x24);
    sp.u20 = (*(f32 *)((u8 *)temp_v0 + 0x18)) - (*(f32 *)((u8 *)temp_v0 + 0x24));
    sp.u24 = (*(f32 *)((u8 *)temp_v0 + 0x1C)) - (*(f32 *)((u8 *)temp_v0 + 0x28));
    sp.u28 = (*(f32 *)((u8 *)temp_v0 + 0x20)) - (*(f32 *)((u8 *)temp_v0 + 0x2C));
    (*(f32 *)((u8 *)sp.u2C + 0xC0)) = func_15143E64(&sp.u20);
    (*(s32 *)((u8 *)sp.u2C + 0x10)) = 1;
    (*(s32 *)((u8 *)sp.u2C + 0x14)) = 0;
    return sp.u2C;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5870.s")
#endif
void func_150C5930(struct102 *arg0) {
    func_15169804(arg0);
}

void func_150C5950(struct102 *arg0) {
    func_15169824(arg0);
}

extern void (*D_80088B58[2])(void);
void func_150C5970(u8 *arg0) {
    s32 idx = *(u8 *)(arg0 + 0x38);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 2) {
        idx = 0;
    }
    D_80088B58[idx]();
}

extern void (*D_80088B60[2])(void);
void func_150C59C0(u8 *arg0) {
    s32 idx = *(u8 *)(arg0 + 0x38);

    if (idx < 0) {
        idx = 0;
    } else if (idx >= 2) {
        idx = 0;
    }
    D_80088B60[idx]();
}

void func_150C5A10(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5930(arg0);
}

void func_150C5A3C(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5950(arg0);
}

#ifdef NON_MATCHING
extern s32 (*D_80088B00[])(u8 *); /* motion handlers (func_150C6088, func_150C60D4) (index obj +0x30, -1 = none); 0 = remove the object */

/* object_motion_step: for an active object (flag word +0x10 bit 0), runs its motion handler D_80088B00[+0x30] (if
 * any); when the handler returns 0 the object is removed (func_1516972C). Otherwise, if the offset position +0x18 -
 * +0x24 (f32[3] each) changed across the handler, its length (func_15143E64) is stored in +0xC0. Table record word
 * 0x8008C680 (update slot), like its neighbours `void (struct102 *)`. */
void func_150C5A68(struct102 *obj) {
    u8 *o = (u8 *) obj;
    f32 dx, dy, dz;
    f32 d[3];
    u8 remove = 0;

    if (!(*(s32 *) (o + 0x10) & 1)) {
        return;
    }
    dx = *(f32 *) (o + 0x18) - *(f32 *) (o + 0x24);
    dy = *(f32 *) (o + 0x1C) - *(f32 *) (o + 0x28);
    dz = *(f32 *) (o + 0x20) - *(f32 *) (o + 0x2C);
    if (*(s8 *) (o + 0x30) != -1) {
        if (D_80088B00[*(s8 *) (o + 0x30)](o) == 0) {
            remove = 1;
        }
    }
    if (!remove) {
        d[0] = *(f32 *) (o + 0x18) - *(f32 *) (o + 0x24);
        d[1] = *(f32 *) (o + 0x1C) - *(f32 *) (o + 0x28);
        d[2] = *(f32 *) (o + 0x20) - *(f32 *) (o + 0x2C);
        if (d[0] != dx || d[1] != dy || d[2] != dz) {
            *(f32 *) (o + 0xC0) = func_15143E64(d);
        }
    }
    if (remove) {
        func_1516972C(obj);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5A68.s")
#endif

#ifdef NON_MATCHING
Gfx *func_15142C10(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5);
s32 func_15142CF0(s32, s32, s32, s16, s32, s32, s32, s8 *);
s32 func_15142E24(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
s32 func_15142B7C(s32, s32, s32);
s32 func_1513F4E4(s32, s32, s8 *);
u8 *func_15142FBC(s32, s32, s32, s8 *);
extern s32 D_80091198[];
float sqrtf(float);
extern s32 D_800D30BC;
extern u8 D_800A4EA8[];

// beam_quad_draw: draws a camera-facing beam quad from +0x18 (start) to +0x24 (end) for player view `view` when
// flag 1 of +0x10 is set. The quad's half-width vector is (end - start) x (end - camera) normalised to 8.4
// (camera = view record +0x2F8 of D_800DBFF0, 0x9A0 bytes per view); the texture runs 0..0x3C0 across and
// 0..+0xC0 * +0x34 * 64 along. Render state: texture D_80091198 (func_15142E24); with flag 1 of the view's
// +0x5F0 the view's colours D_800D9F98 / D_800D9F88 (3 bytes per view) and mode 0x1E, else black and mode 0x13.
// The 4 vertices go to the obj's buffer for D_800BE9C0 (+0x40, 0x40 bytes each) and two triangles are added.
u8 *func_150C5BA4(u8 *gdl, u8 *obj, s16 view) {
    u8 flag;
    f32 *cam;
    s16 *v;
    u32 *g;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 ex;
    f32 ey;
    f32 ez;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 len2;
    f32 inv;
    s32 t;

    if (!(*(s32 *) (obj + 0x10) & 1)) {
        return gdl;
    }
    cam = (f32 *) ((u8 *) D_800DBFF0 + view * 0x9A0 + 0x2F8);
    v = (s16 *) (obj + D_800BE9C0 * 0x40 + 0x40);
    flag = 1;
    gdl = (u8 *) func_15142B7C((s32) gdl, 1, 0x600);
    gdl = (u8 *) func_15142E24(gdl, D_80091198, 0, 0, 0, 0, 0x36, 0, 0, (s8 *) &flag, 3);
    if (*(s32 *) ((u8 *) D_800DBFF0 + view * 0x9A0 + 0x5F0) & 1) {
        gdl = (u8 *) func_15142C10((Gfx *) gdl, D_800D9F98[view * 3], D_800D9F98[view * 3 + 1],
                                   D_800D9F98[view * 3 + 2], 0xFF, &flag);
        gdl = (u8 *) func_15142CF0((s32) gdl, 0xF2, 0, D_800D9F88[view * 3], D_800D9F88[view * 3 + 1],
                                   D_800D9F88[view * 3 + 2], 0xFF, (s8 *) &flag);
        gdl = (u8 *) func_1513F4E4((s32) gdl, 0x1E, (s8 *) &flag);
    } else {
        gdl = (u8 *) func_15142C10((Gfx *) gdl, 0, 0, 0, 0, &flag);
        gdl = (u8 *) func_15142CF0((s32) gdl, 0, 0, 0, 0, 0, 0, (s8 *) &flag);
        gdl = (u8 *) func_1513F4E4((s32) gdl, 0x13, (s8 *) &flag);
    }
    gdl = func_15142FBC((s32) gdl, D_800D30BC | 0x80000 | 0x2CA0,
                        *(s32 *) (D_800A4EA8 + 0xC) | *(s32 *) (D_800A4EA8 + 0x8), (s8 *) &flag);
    dx = *(f32 *) (obj + 0x24) - *(f32 *) (obj + 0x18);
    dy = *(f32 *) (obj + 0x28) - *(f32 *) (obj + 0x1C);
    dz = *(f32 *) (obj + 0x2C) - *(f32 *) (obj + 0x20);
    ex = *(f32 *) (obj + 0x24) - cam[0];
    ey = *(f32 *) (obj + 0x28) - cam[1];
    ez = *(f32 *) (obj + 0x2C) - cam[2];
    nx = dy * ez - ey * dz;
    ny = dz * ex - ez * dx;
    nz = dx * ey - ex * dy;
    len2 = nx * nx + ny * ny + nz * nz;
    if (len2 == 0.0f) {
        nx = 0.0f;
        ny = 0.0f;
        nz = 0.0f;
    } else {
        inv = 8.4f / sqrtf(len2); /* D_800A07D0 = 0x41066666 */
        nx *= inv;
        ny *= inv;
        nz *= inv;
    }
    t = (s32) (*(f32 *) (obj + 0xC0) * *(f32 *) (obj + 0x34) * 64.0f);
    v[0] = (s32) (*(f32 *) (obj + 0x24) + nx);
    v[1] = (s32) (*(f32 *) (obj + 0x28) + ny);
    v[2] = (s32) (*(f32 *) (obj + 0x2C) + nz);
    v[4] = 0;
    v[5] = 0;
    v[8] = (s32) (*(f32 *) (obj + 0x24) - nx);
    v[9] = (s32) (*(f32 *) (obj + 0x28) - ny);
    v[10] = (s32) (*(f32 *) (obj + 0x2C) - nz);
    v[12] = 0x3C0;
    v[13] = 0;
    v[16] = (s32) (*(f32 *) (obj + 0x18) - nx);
    v[17] = (s32) (*(f32 *) (obj + 0x1C) - ny);
    v[18] = (s32) (*(f32 *) (obj + 0x20) - nz);
    v[20] = 0x3C0;
    v[21] = t;
    v[24] = (s32) (*(f32 *) (obj + 0x18) + nx);
    v[25] = (s32) (*(f32 *) (obj + 0x1C) + ny);
    v[26] = (s32) (*(f32 *) (obj + 0x20) + nz);
    v[28] = 0;
    v[29] = t;
    g = (u32 *) gdl;
    g[0] = 0x01004008; /* gSPVertex: 4 vertices */
    g[1] = (u32) v;
    g[2] = 0x05000204; /* gSP1Triangle 0, 1, 2 */
    g[3] = 0;
    g[4] = 0x05000406; /* gSP1Triangle 0, 2, 3 */
    g[5] = 0;
    return gdl + 0x18;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_F3080/func_150C5BA4.s")
#endif

s32 func_150C6088(u8 *arg0) {
    u8 **temp_v1 = (u8 **)(arg0 + 0xC8);

    if (**(s32 **)(arg0 + 0xC8) == 0) {
        return 0;
    }
    *(f32 *)(arg0 + 0x24) = *(f32 *)(*temp_v1 + 0x14);
    *(f32 *)(arg0 + 0x28) = *(f32 *)(*temp_v1 + 0x18);
    *(f32 *)(arg0 + 0x2C) = *(f32 *)(*temp_v1 + 0x1C);
    return 1;
}

s32 func_150C60D4(u8 *arg0)
{
  u8 *temp_t0;
  u8 *temp_v0;
  u8 *temp_v1;
  temp_v0 = arg0;
  temp_v0 = temp_v0 + 0xC8;
  if ((*(*((s32 **) (((u8 *) arg0) + 0xC8)))) == 0)
  {
    return 0;
  }
  temp_v1 = *((u8 **) (((u8 *) temp_v0) + 0));
  if ((*((u8 *) (((u8 *) temp_v0) + 4))) != (*((u8 *) (((u8 *) temp_v1) + 0x3B))))
  {
    return 0;
  }
  ;
  if ((*((u8 **) (((u8 *) temp_v1) + 0x1D4))) == 0)
  {
    *((f32 *) (((u8 *) arg0) + 0x24)) = (f32) (*((f32 *) (((u8 *) temp_v1) + 0x14)));
    *((f32 *) (((u8 *) arg0) + 0x28)) = (f32) (*((f32 *) (((u8 *) (*((u8 **) (((u8 *) temp_v0) + 0)))) + 0x18)));
    *((f32 *) (((u8 *) arg0) + 0x2C)) = (f32) (*((f32 *) (((u8 *) (*((u8 **) (((u8 *) temp_v0) + 0)))) + 0x1C)));
  }
  else
  {
    func_15143134(temp_v0 + 8, arg0 + 0x24, ((*((u8 *) (((u8 *) temp_v0) + 5))) << 6) + (((s32) (*((u8 **) (((u8 *) temp_v1) + 0x1D4)))) ^ 0));
  }
  return 1;
}

void func_150C6174(s32 arg0) {
    func_1514D3B0(arg0, 0x15, 1, 0);
}

void func_150C619C(s32 arg0) {
    func_1514D3B0(arg0, 0x15, 2, 0);
}

void func_150C61C4(u8 *arg0, s32 arg1, u8 arg2) {
    void (*temp_v0)(u8 *, s32, u8) = D_80088B68[arg0[0x38]];

    if (temp_v0 != NULL) {
        temp_v0(arg0, arg1, arg2);
    }
}

void func_150C620C(u8 *arg0, s32 *arg1, u8 arg2) {
    u8 *v = arg0 + 0xC8;
    if (arg2 == 0) {
        if ((*(s32 *)v == arg1[0]) || (v[4] == ((u8 *)arg1)[4])) {
            func_1516972C(arg0);
        }
    } else {
        v = arg0 + 0xC8;
        if (arg2 == 0x2D) {
            if (arg1[0] == *(s32 *)v) {
                *(s32 *)v = arg1[1];
                v[4] = ((u8 *)arg1)[9];
            } else if (arg1[1] == *(s32 *)v) {
                *(s32 *)v = arg1[0];
                v[4] = ((u8 *)arg1)[8];
            }
        }
    }
}
