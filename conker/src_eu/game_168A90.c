#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
// mesh_effect_spawn: spawns an animated mesh effect record (P195). The 0x3C-byte spawn block p (copied to rec + 0x10) names
// a model by its +0x30 / +0x34 words (func_1502B6BC, kind 2 lookup); the model header starts with its display list
// pointer, followed at +0x28 by the vertex block (size = dl - header - 0x28). The record (kind 0x54 when arg1 != 0,
// else 0x38; func_15167A68 with group arg4 and priority arg3) gets D_80082FA0 + 1 double-buffered vertex copies at
// +0xF8 (+0x58[i] / +0x68[i] point at the two halves), +0x4C = header, +0x50 = the copies' size, +0x54 = the display
// list, which is registered with func_1510D3E0 (age 0x3E). arg2 extra bytes follow the copies. Returns NULL when the
// pool is full. Callers: func_15010A60 (ambient fires), func_15108850, func_1513BAE8, game_eu_1E7CC0.
s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, ...);
s32 func_1510D3E0(Gfx *dl, s32 skipResolved, s32 addRef, s32 age, s16 **outList);
void *func_15167A68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, u8 arg5);
void *memcpy(void *, const void *, s32);

struct102 *func_1513B5E0(void *p, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 found;
    s32 count;
    u8 *hdr;
    u8 *rec;
    u8 *dst;
    s32 size;
    s32 total;
    s32 i;

    hdr = (u8 *) func_1502B6BC(&found, 0, &count, 2, *(s32 *) ((u8 *) p + 0x30), *(s32 *) ((u8 *) p + 0x34));
    size = *(s32 *) hdr - (s32) hdr - 0x28;
    total = size * 2 * (D_80082FA0 + 1);
    rec = func_15167A68(arg1 ? 0x54 : 0x38, arg4, arg2 + total + 0xF8, 2, arg3, 1);
    if (rec == NULL) {
        return NULL;
    }
    memcpy(rec + 0x10, p, 0x3C);
    *(u8 **) (rec + 0x4C) = hdr;
    dst = rec + 0xF8;
    for (i = 0; i <= D_80082FA0; i++) {
        ((u8 **) (rec + 0x58))[i] = dst;
        ((u8 **) (rec + 0x68))[i] = dst + size;
        memcpy(dst, hdr + 0x28, size);
        memcpy(((u8 **) (rec + 0x68))[i], hdr + 0x28, size);
        dst += size * 2;
    }
    *(s32 *) (rec + 0x54) = *(s32 *) hdr;
    *(s32 *) (rec + 0x50) = total;
    func_1510D3E0(*(Gfx **) hdr, 0, 1, 0x3E, NULL);
    return (struct102 *) rec;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B5E0.s")
#endif
void func_1513B798(u8 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0[0x10] & 1) != 0) {
        *(s16 *)(arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x14) < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (*(s8 *)(arg0 + 0x11) != -1) && (D_80089FB8[*(s8 *)(arg0 + 0x11)](arg0) == 0)) {
        ret = 1;
    }
    if (ret) {
        func_1516972C(arg0);
    }
}
// NON-MATCHING: only the stack slot of done differs (0x1B vs 0x1F)
// void func_1513B798(struct_eu_168A90 *arg0) {
//     u8 done;
//
//     done = FALSE;
//     if (arg0->unk10 & 1) {
//         arg0->unk14 -= D_800BE9E4;
//         if (arg0->unk14 < 0) {
//             done = TRUE;
//         }
//     }
//     if (!done) {
//         if (arg0->unk11 != -1) {
//             if (D_80089FB8[arg0->unk11](arg0) == 0) {
//                 done = TRUE;
//             }
//         }
//     }
//     if (done) {
//         func_1516972C(arg0);
//     }
// }
#ifdef NON_MATCHING
extern s32 D_80089FC8;

u8 *func_1513B83C(u8 *arg0, u8 *arg1, s16 arg2) {
    s16 var_a2;
    s32 temp_v0_2;
    s8 temp_v0;
    u8 *temp_a3;
    u8 *temp_a3_2;

    var_a2 = arg2;
    if (((*(u8 *)((u8 *)arg1 + 0x10)) & 2) && !((*(u8 *)((u8 *)arg1 + 0x49)) & (1 << var_a2))) {
        return arg0;
    }
    temp_v0 = (*(s8 *)((u8 *)arg1 + 0x12));
    if (temp_v0 != -1) {
        arg2 = var_a2;
        // P250: the handlers (func_151096A0, func_151BA634) are s32 (u8 *, s32); a2 / a3 are only leftovers in the asm
        temp_v0_2 = ((s32 (**)(u8 *, s32)) &D_80089FC8)[temp_v0](arg1, var_a2);
        var_a2 = arg2;
        if (temp_v0_2 == 0) {
            return arg0;
        }
    }
    (*(s32 *)((u8 *)arg0 + 0)) = 0xDA380003;
    temp_a3_2 = arg0 + 8;
    (*(u8 **)((u8 *)arg0 + 4)) = (u8 *) (arg1 + (D_800BE9C0 << 6) + 0x78);
    (*(s32 *)((u8 *)temp_a3_2 + 0)) = 0xDB060004;
    temp_a3 = temp_a3_2 + 8;
    (*(s32 *)((u8 *)temp_a3_2 + 4)) = (s32) (*(s32 *)((u8 *)((arg1 + (D_800BE9C0 * 0x10) + (var_a2 * 4))) + 0x58));
    (*(s32 *)((u8 *)temp_a3 + 0)) = 0xDE000000;
    (*(s32 *)((u8 *)temp_a3 + 4)) = (s32) (*(s32 *)((u8 *)arg1 + 0x54));
    return temp_a3 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B83C.s")
#endif
s32 func_1513B968(s32 arg0, s32 arg1) {
    // FIXME: &arg0->unk_120[D_800BE9C0]
    func_150A7B80(arg0 + 120 + (D_800BE9C0 << 6));
    return 1;
}

void func_1513B9A8(struct132 *arg0) {
    func_100043B4(arg0->unk4C, 4);
    func_15169804(arg0);
}

void func_1513B9DC(struct132 *arg0) {
    func_100043B4(arg0->unk4C, 4);
    func_15169824(arg0);
}

#ifdef NON_MATCHING
// object_mode_dispatch_a: runs the D_80089C44 handler picked by the object's +0x48 byte on the object. The asm leaves
// the object in a0 at the jalr; every entry (func_1513B9A8 x4) is void (struct132 *), so no result is passed on.
void func_1513BA10(struct132 *arg0) {
    ((void (*)(struct132 *)) D_80089C44[arg0->unk48])(arg0);
}

// object_mode_dispatch_b: as func_1513BA10 with the table D_80089C54 (func_1513B9DC x4).
void func_1513BA44(struct132 *arg0) {
    ((void (*)(struct132 *)) D_80089C54[arg0->unk48])(arg0);
}
#else
void func_1513BA10(struct132 *arg0) {
    D_80089C44[arg0->unk48]();
}

void func_1513BA44(struct132 *arg0) {
    D_80089C54[arg0->unk48]();
}
#endif

void func_1513BA78(u8 *arg0, s32 arg1, u8 arg2) {
    switch (arg0[0x48]) {
    case 1:
        func_151095E4(arg0, arg1, arg2);
        break;
    case 2:
        func_151BAA18(arg0, arg1, arg2);
        break;
    }
}

s32 func_1513BAD4(s32 arg0, s32 arg1) {
    return 0;
}

typedef struct { u8 pad[0x50]; s32 off; u8 pad54[0xA4]; u8 data[1]; } BAE8Obj;
typedef struct {
    s8 b0; s8 b1; s8 b2; s8 pad3;
    s16 h4; s16 pad6;
    s32 w8; s32 wC; s32 w10; s32 w14; s32 w18; s32 w1C; s32 w20;
    s8 b24; s8 b25; s8 pad26[2];
    s32 w28; s32 w2C;
    s32 w30; s32 w34;
    s8 b38; s8 pad39[3];
} BAE8Params;
#ifndef NON_MATCHING /* NM: defined above as (void *, u8, s32, u8, s32) */
struct102 *func_1513B5E0(BAE8Params *, s32, s32, s32, s32);
#endif
void *memcpy(void *, const void *, s32);
struct102 *func_1513BAE8(void) {
    struct102 *p;
    BAE8Params s;
    f32 f[5];

    s.b1 = 2;
    s.b2 = 5;
    s.h4 = 0x12C;
    s.w30 = 9;
    f[0] = 0.0f;
    f[1] = 0.0f;
    f[3] = 0.0f;
    f[4] = 0.0f;
    f[2] = 0.0f;
    s.b0 = 0;
    s.w34 = 0x1AE;
    s.w8 = 1;
    s.wC = 0x220205;
    s.w10 = 0x40600;
    s.b24 = 0;
    s.b25 = 0;
    s.w14 = 1;
    s.w18 = 0x36;
    s.w1C = 0x80;
    s.w20 = 0x20;
    s.b38 = 3;
    p = func_1513B5E0(&s, 1, 0x14, 0xFF, 1);
    if (p != NULL) {
        if (*(s32 *)((u8 *)p + 0x50) != 0x1180) {
            func_1516972C(p);
        } else {
            memcpy(&((BAE8Obj *)p)->data[((BAE8Obj *)p)->off], f, 0x14);
        }
    }
    return p;
}
#ifdef NON_MATCHING
float sqrtf(float);
extern f32 D_800A4DA0[9][3];    // the nine texture-projection centres
extern s32 D_800A4E0C[9][2];    // their vertex ranges { first, count }
extern f32 D_800A4E54;          // 1.21f
extern f32 D_800A4E58;          // 2.854f
extern f32 D_800A4E5C;          // 1.994f
extern f32 D_800A4E60;          // 8.328f

// water_texcoords_update: object-type handler (table D_80089FC8 + 0x14). Calls func_1513B968 first, then rewrites the
// texture coordinates of the nine vertex groups of the object's current vertex buffer (obj + 0x58 + D_800BE9C0 * 16
// + part * 4) so each group's texture faces the player camera point (func_15144B34(part)) seen from its centre
// D_800A4DA0[k]: s = horizontal offset along the camera direction * (sin(rec + 0xC) * 1.21 + 2.854) - scroll u,
// t = height * (sin(rec + 0x10) * 1.994 + 8.328) - scroll v, where rec = obj + obj[0x50] + 0xF8 holds the scroll
// (+0 / +4, taken mod 1024) and the two wave phases. Returns 1.
s32 func_1513BBFC(s32 obj, s16 part) {
    f32 *rec;
    f32 *cam;
    f32 scaleS;
    f32 scaleT;
    f32 scrollS;
    f32 scrollT;
    f32 dx;
    f32 dz;
    f32 inv;
    f32 dirX;
    f32 dirZ;
    Vtx_t *v;
    s32 k;
    s32 n;

    func_1513B968(obj, part);
    rec = (f32 *) (obj + *(s32 *) (obj + 0x50) + 0xF8);
    scaleS = sinf(rec[3]) * D_800A4E54 + D_800A4E58;
    scaleT = sinf(rec[4]) * D_800A4E5C + D_800A4E60;
    cam = func_15144B34(part);
    scrollS = rec[0] - (f32) (s32) (rec[0] * (1.0f / 1024.0f)) * 1024.0f;
    scrollT = rec[1] - (f32) (s32) (rec[1] * (1.0f / 1024.0f)) * 1024.0f;
    for (k = 0; k < 9; k++) {
        dx = D_800A4DA0[k][0] - cam[0];
        dz = D_800A4DA0[k][2] - cam[2];
        if (dx == 0.0f && dz == 0.0f) {
            dirX = 1.0f;
            dirZ = 0.0f;
        } else {
            inv = 1.0f / sqrtf(dx * dx + dz * dz);
            dirX = dz * inv;
            dirZ = -dx * inv;
        }
        for (n = D_800A4E0C[k][0]; n < D_800A4E0C[k][0] + D_800A4E0C[k][1]; n++) {
            v = (Vtx_t *) (*(u8 **) (obj + 0x58 + D_800BE9C0 * 16 + part * 4) + n * 16);
            v->tc[0] = (s32) ((((f32) v->ob[0] - D_800A4DA0[k][0]) * dirX + ((f32) v->ob[2] - D_800A4DA0[k][2]) * dirZ) *
                                  scaleS - scrollS);
            v->tc[1] = (s32) (((f32) v->ob[1] - D_800A4DA0[k][1]) * scaleT - scrollT);
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BBFC.s")
#endif
extern f32 D_800A4E64; // 0.037f (file does not own .rodata)
extern f32 D_800A4E68; // 1.9f
extern f32 D_800A4E6C; // 77.3f
extern f32 D_800A4E70; // 0.019f
extern f32 D_800A4E74; // 0.01f
typedef struct {
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
} Wave1513BEB0;

s32 func_1513BEB0(u8 *arg0) {
    f32 f;
    Wave1513BEB0 *w = (Wave1513BEB0 *)(arg0 + *(s32 *)(arg0 + 0x50) + (0, 0xF8)); // fakematch: comma keeps addu a0,t6 order

    w->c += D_800A4E64 * D_800BE9A4;
    f = func_15144B68(w->c);
    w->c = f;
    w->a += D_800A4E68 * D_800BE9A4;
    w->b = sinf(f) * D_800A4E6C;
    w->d += D_800A4E70 * D_800BE9A4;
    w->e += D_800A4E74 * D_800BE9A4;
    w->d = func_15144B68(w->d);
    w->e = func_15144B68(w->e);
    while (w->a > 4096.0f) {
        w->a -= 4096.0f;
    }
    while (w->a < 0.0f) {
        w->a += 4096.0f;
    }
    while (w->b > 4096.0f) {
        w->b -= 4096.0f;
    }
    while (w->b < 0.0f) {
        w->b += 4096.0f;
    }
    return 1;
}
