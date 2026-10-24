#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
s32 func_1517F18C(u8 *arg0, u32 *arg1);
#endif


u8 *allocate_memory(s32, s32, s32, s32);

u8 *func_1517E080(s32 arg0, s32 arg1) {
    s32 *sp18;
    s32 *var_t0;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_v0;

    var_v1 = D_800DDD64;
    if (var_v1 != 0) {
        var_v0 = (*(s32 *)((u8 *)var_v1 + 0x24));
        if (var_v0 != 0) {
            do {
                var_v1 = var_v0;
                var_v0 = (*(s32 *)((u8 *)var_v0 + 0x24));
            } while (var_v0 != 0);
        }
        var_t0 = var_v1 + 0x24;
    } else {
        var_t0 = &D_800DDD64;
    }
    sp18 = var_t0;
    temp_v0 = allocate_memory(0x34, 1, 0, 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    *var_t0 = (s32) temp_v0;
    (*(s32 *)((u8 *)temp_v0 + 0x24)) = 0;
    (*(s16 *)((u8 *)temp_v0 + 0x28)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2E)) = 0;
    (*(f32 *)((u8 *)temp_v0 + 0x10)) = 0.0f;
    (*(f32 *)((u8 *)temp_v0 + 0xC)) = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 0x2F)) = (s8) arg0;
    (*(s8 *)((u8 *)temp_v0 + 0x30)) = (s8) arg1;
    return temp_v0;
}

#ifdef NON_MATCHING
void func_10004074(void *);

// object_node_remove: unlinks node arg0 (an object's +0x154) from the list D_800DDD64 (next at +0x24, appended
// by func_1517E080) and frees it (func_10004074); a node that is not in the list is left alone (not freed).
// arg1 (the owner) is not read.
void func_1517E6A4(f32 *arg0, structEU_16DC80 *arg1) {
    u8 *node = (u8 *) arg0;
    u8 *prev;

    if (node == (u8 *) D_800DDD64) {
        D_800DDD64 = *(s32 *) (node + 0x24);
    } else {
        prev = (u8 *) D_800DDD64;
        while (prev != NULL && *(u8 **) (prev + 0x24) != node) {
            prev = *(u8 **) (prev + 0x24);
        }
        if (prev == NULL) {
            return;
        }
        *(s32 *) (prev + 0x24) = *(s32 *) (node + 0x24);
    }
    func_10004074(node);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E6A4.s")
#endif

void func_1517E71C(void) {
    f32 temp_f0;
    f32 temp_f2;
    s32 var_v0;

    var_v0 = D_800DDD64;
    if (var_v0 != 0) {
        do {
            temp_f0 = *(f32 *)(var_v0 + 0xC);
            if ((temp_f0 >= 0.0f) && (temp_f0 < (f32) D_800BE620)) {
                temp_f2 = *(f32 *)(var_v0 + 0x10);
                if ((temp_f2 >= 0.0f) && (temp_f2 < (f32) D_800BE624)) {
                    *(u16 *)(var_v0 + 0x2A) = *(u16 *)(*(u8 **)&D_800BEDE4 + ((s32) temp_f0 * 2) + ((u32) (s32) temp_f2 * (u32) D_800BE620 * 2));
                }
            }
            var_v0 = *(s32 *)(var_v0 + 0x24);
        } while (var_v0 != 0);
    }
}

#ifdef NON_MATCHING
s32 func_1517F01C(f32 x, f32 y, f32 z, f32 *outX, f32 *outY);
Gfx *func_1517EA18(Gfx *gdl, u8 *node, s32 r, s32 g, s32 b, s32 alpha, u8 *flag);
extern u8 D_8008D3A4[2];
extern u8 D_8008D3A8[2];
extern u8 D_8008D3AC[2];
extern u8 D_800DE190;

/* Node list D_800DDD64 (0x34-byte nodes, see func_1517E080): +0xC/+0x10 screen x/y, +0x24 next,
 * +0x2A/+0x2C u16, +0x2E flags (1 = world-projected, 2 = clears D_800DD2D0 when hidden), +0x2F colour index,
 * +0x30 enabled. Each visible node is drawn by func_1517EA18. */
#define NM_E7FC_U8(n, o) (*((u8 *)(n) + (o)))
#define NM_E7FC_U16(n, o) (*(u16 *)((u8 *)(n) + (o)))
Gfx *func_1517E7FC(Gfx *gdl, s32 arg1) {
    u8 rr[2], gg[2], bb[2];
    u8 *node;
    u8 *flag;
    f32 *pos;
    u32 t;
    s32 hide;
    s32 alpha = -1; /* the asm starts from a stale stack word; every drawn node sets it first */
    u8 fl;

    rr[0] = D_8008D3A4[0];
    rr[1] = D_8008D3A4[1];
    gg[0] = D_8008D3A8[0];
    gg[1] = D_8008D3A8[1];
    bb[0] = D_8008D3AC[0];
    bb[1] = D_8008D3AC[1];
    D_800DE190 = 0;
    for (node = (u8 *)D_800DDD64; node != NULL; node = *(u8 **)(node + 0x24)) {
        if (NM_E7FC_U8(node, 0x30) == 0) {
            continue;
        }
        hide = 0;
        fl = NM_E7FC_U8(node, 0x2E);
        if (fl & 1) {
            if (D_800DCDD0 == 0) {
                hide = 1;
            } else {
                pos = (f32 *)D_8008CFFC[*((u8 *)D_800B0DF0 + 0x10)];
                if (func_1517F01C(pos[0], pos[1], pos[2], (f32 *)(node + 0xC), (f32 *)(node + 0x10)) != 1) {
                    hide = 1;
                }
                alpha = (NM_E7FC_U16(node, 0x2A) == 0xFFFC) ? 0xFF : -1;
                fl = NM_E7FC_U8(node, 0x2E);
            }
        } else {
            if (func_1517F18C(node, &t) != 1) {
                hide = 1;
            }
            alpha = ((s32)(NM_E7FC_U16(node, 0x2C) - t) < 0x1E) ? 0x100 : -1;
            fl = NM_E7FC_U8(node, 0x2E);
        }
        flag = (fl & 2) ? &D_800DD2D0 : NULL;
        if (!hide) {
            fl = NM_E7FC_U8(node, 0x2F);
            gdl = func_1517EA18(gdl, node, rr[fl], gg[fl], bb[fl], alpha, flag);
        } else if (flag != NULL) {
            *flag = 0;
        }
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517E7FC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517EA18.s")

Gfx *func_1517EFBC(Gfx *arg0) {
    gDPPipeSync(arg0++);
    gDPSetCombine(arg0++, 0xFFB3FF, 0xFF65FEFF);
    gDPSetOtherMode(arg0++, 0x2C0F, 0x504344);
    return arg0;
}

#ifdef NON_MATCHING
void func_151108E0(s32, f32 (*)[4], f32, f32, f32);
void func_150A7EE0(f32 (*)[4], f32, f32, f32, f32 *, f32 *, f32 *, f32 *);

// world_to_screen: projects (x, y, z) with the current player's camera (D_800DBFF0[D_80082FA4]: view matrix from
// func_151108E0 with -pitch +0x388, -yaw +0x380 and +0x5EC) into its viewport (D_800BE628 + player * 0x180: half
// width +0xC, half height +0x10). In front (w > 10): *outX / *outY = viewport centre + projected x / - projected y,
// returns 1; else both 0 and returns 0.
s32 func_1517F01C(f32 x, f32 y, f32 z, f32 *outX, f32 *outY) {
    f32 mtx[4][4];
    u8 *cam;
    u8 *vp;
    f32 hw;
    f32 hh;
    f32 inv;
    f32 sx;
    f32 sy;
    f32 sz;
    f32 w;

    cam = (u8 *) D_800DBFF0 + D_80082FA4 * 0x9A0;
    func_151108E0(D_80082FA4, mtx, -*(f32 *) (cam + 0x388), -*(f32 *) (cam + 0x380), *(f32 *) (cam + 0x5EC));
    vp = (u8 *) D_800BE628 + D_80082FA4 * 0x180;
    hw = *(f32 *) (vp + 0xC);
    hh = *(f32 *) (vp + 0x10);
    func_150A7EE0(mtx, x, y, z, &sx, &sy, &sz, &w);
    if (10.0f < w) {
        inv = 1.0f / w;
        sx = sx * hw * inv;
        sy = sy * hh * inv;
        *outX = hw + sx;
        *outY = hh - sy;
        return 1;
    }
    *outX = 0.0f;
    *outY = 0.0f;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517F01C.s")
#endif

#ifdef NON_MATCHING
s32 func_15095A4C(f32, f32, f32, u8 *, u8 *, f32 *, f32 *, f32);
extern s32 D_800899D0;

s32 func_1517F18C(u8 *arg0, u32 *arg1) {
    struct {
        f32 u28;
        f32 u2C;
    } sp;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    u16 temp_a3;
    u8 *temp_a1;
    u8 *temp_a2;

    if (func_15095A4C((*(f32 *)((u8 *)arg0 + 0)), (*(f32 *)((u8 *)arg0 + 4)), (*(f32 *)((u8 *)arg0 + 8)), arg0 + 0xC, arg0 + 0x10, &sp.u2C, &sp.u28, 4000.0f) == 1) {
        if ((*(u8 *)((u8 *)arg0 + 0x2E)) & 4) {
            temp_f2 = (*(f32 *)((u8 *)arg0 + 0)) - D_800DBFF0->unk2F8;
            temp_f12 = (*(f32 *)((u8 *)arg0 + 4)) - D_800DBFF0->unk2FC;
            temp_f14 = (*(f32 *)((u8 *)arg0 + 8)) - D_800DBFF0->unk300;
            if ((((temp_f2 * (*(f32 *)((u8 *)arg0 + 0x14))) + (temp_f12 * (*(f32 *)((u8 *)arg0 + 0x18))) + (temp_f14 * (*(f32 *)((u8 *)arg0 + 0x1C)))) / sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12) + (temp_f14 * temp_f14))) < (*(f32 *)((u8 *)arg0 + 0x20))) {
                return 1;
            }
        }
        temp_a3 = (*(u16 *)((u8 *)arg0 + 0x2A));
        temp_a1 = ((s32 *)((u8 *)&D_800899D0 + (((s32) temp_a3 >> 0xD) * 8)));
        *arg1 = (u32) ((*(s32 *)((u8 *)temp_a1 + 4)) + ((((s32) temp_a3 >> 2) & 0x7FF) << (*(s32 *)((u8 *)temp_a1 + 0)))) >> 3;
        temp_a2 = D_800BE628 + (D_800BE9C0 * 0x10);
        (*(s16 *)((u8 *)arg0 + 0x2C)) = (s16) (u32) (((f32) (*(s16 *)((u8 *)temp_a2 + 0x4C)) + ((sp.u2C / sp.u28) * (f32) (*(s16 *)((u8 *)temp_a2 + 0x44)))) * 32.0f);
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1ABE00/func_1517F18C.s")
#endif