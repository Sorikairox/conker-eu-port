#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15058F24(struct127 *arg0, f32, f32);
u8   func_150599C8(struct127 *arg0, u8 arg1, u16 arg2);
void func_1505A250(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
f32  func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);

u8  func_1505B9C4(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
s32 func_1505C1E4(struct127 *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);

// EU: split from game_83300.c, EU pads to a file boundary before this.

#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15062800.s")

void func_15062AC4(struct127 *arg0) {
    if (arg0->unkE6 && arg0->unkE4) {
        f32 tmp = arg0->unkE4;
        arg0->unkEC = tmp / arg0->unkE6;
        arg0->unkF0 = arg0->unkE6 / tmp;
    } else {
        arg0->unkF0 = arg0->unkEC = 0.0f;
    }
}

void func_15062B1C(struct127 *arg0, f32 arg1) {
    arg0->unkE4 = arg0->xz_scale * arg1;
    func_15062AC4(arg0);
}

void func_15062B50(struct127 *arg0, f32 arg1) {
    arg0->unkE6 = arg0->y_scale * arg1;
    func_15062AC4(arg0);
}

void func_15062B84(struct127 *arg0) {
    if (arg0->unkD4 && arg0->unkD2) {
        f32 tmp = arg0->unkD2;
        arg0->unkDC = tmp / arg0->unkD4;
        arg0->unkE0 = arg0->unkD4 / tmp;
    } else {
        arg0->unkDC = 0.0f;
        arg0->unkE0 = 0.0f;
    }
}

void func_15062BDC(struct127 *arg0, f32 arg1, f32 arg2) {
    struct124 *temp_v0;

    arg0->xz_scale = arg1;
    arg0->y_scale = arg2;
    if (arg0->id != 255) {
        temp_v0 = D_800D1C90[arg0->id];
        arg0->unkD2 = (s32) (temp_v0->unk20 * arg0->xz_scale);
        arg0->unkD4 = (s32) (temp_v0->unk22 * arg0->y_scale);
        arg0->unkD6 = (s32) (temp_v0->unk24 * arg0->y_scale);
        arg0->unkE4 = (s32) (temp_v0->unk1A * arg0->xz_scale);
        arg0->unkE6 = (s32) (temp_v0->unk1C * arg0->y_scale);
        arg0->unkE8 = (s32) (temp_v0->unk1E * arg0->y_scale);
        func_15062AC4(arg0);
        func_15062B84(arg0);
    }
}

#ifdef NON_MATCHING
extern s32 D_800C48A8;

void func_15062D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a3;

    if ((&D_800D19A0)[arg0] != 0) {
        temp_a3 = *(s32 *)(*(s32 *)((u8 *)&D_800C48A8 + (arg0 * 4)) + (arg4 * 4)) + (arg1 * 8);
        temp_a2 = (*(s32 *)((u8 *)temp_a3 + 4));
        temp_v1 = ((temp_a2 >> 0xC) & 0xFFF) + 2;
        temp_a0 = (temp_a2 & 0xFFF) + 2;
        temp_a2_2 = (*(s32 *)((u8 *)temp_a3 + 0));
        if (arg5 != 0) {
            var_v0 = arg2 & 0xFFF;
        } else {
            temp_a1 = ((temp_a2_2 >> 0xC) & 0xFFF) + arg2;
            var_v0 = temp_a1;
            if (temp_v1 < temp_a1) {
                var_v0 = temp_a1 - temp_v1;
            } else if (temp_a1 < 0) {
                var_v0 = temp_a1 + temp_v1;
            }
        }
        if (arg5 != 0) {
            var_v1 = arg3 & 0xFFF;
        } else {
            temp_a1_2 = (temp_a2_2 & 0xFFF) + arg3;
            var_v1 = temp_a1_2;
            if (temp_a0 < temp_a1_2) {
                var_v1 = temp_a1_2 - temp_a0;
            } else if (temp_a1_2 < 0) {
                var_v1 = temp_a1_2 + temp_a0;
            }
        }
        (*(s32 *)((u8 *)temp_a3 + 0)) = (s32) ((temp_a2_2 & 0xFF000000) | (var_v1 & 0xFFF) | ((var_v0 & 0xFFF) << 0xC));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15062D10.s")
#endif
#ifdef NON_MATCHING
extern u8 *D_800C5758[]; /* per object type: 12-byte texture entries, u16 size at +8 / +0xA */
void func_15094EC8(u8 *, s32 *, s32, f32, s32, s32);

// type_texture_scroll_apply: for every live object (+0x0) of `type` (+0x4) with +0x2FA set and a display list
// for the current screen (+0x28C[D_800BE9C0]), calls func_15094EC8 on entry `dl` (16-byte steps) of it with the
// type's texture-command table D_800C6360[type] at `cmd`, `arg2`, the amount `amount`, and the size of texture
// `tex` of D_800C5758[type] (doubled when `twice`).
void func_15062E24(s32 type, s32 dl, s32 arg2, s32 cmd, s32 amount, s32 tex, s32 twice) {
    s32 *table;
    struct127 *o;
    u8 *entry;
    u8 *list;
    s32 w;
    s32 h;
    s32 i;

    if (D_800C6360[type] == 0) {
        return;
    }
    for (i = 0, o = D_800CC2D0; i < 25; i++, o++) {
        if (*(s32 *) o == 0 || type != *((u8 *) o + 4) || o->unk2FA == 0) {
            continue;
        }
        entry = D_800C5758[type] + tex * 12;
        w = *(u16 *) (entry + 8);
        h = *(u16 *) (entry + 0xA);
        if (twice) {
            w *= 2;
            h *= 2;
        }
        list = ((u8 **) &D_800CC2D0[i].unk28C)[D_800BE9C0];
        if (list != NULL) {
            table = (s32 *) D_800C6360[type];
            func_15094EC8(list + dl * 16, &table[cmd], arg2, (f32) amount, h, w);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15062E24.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800C4440;

void func_15062FC0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s16 temp_a1;
    s16 temp_a3;
    s16 temp_t5;
    s16 temp_t9;
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t4;
    s32 temp_t7;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v1;
    u8 *temp_a2;
    u8 *var_t1;
    u8 *var_t1_2;
    u8 *var_t2;
    u8 *var_t2_2;
    u8 *var_v0;

    temp_a2 = arg0 + ((*(u8 *)((u8 *)arg0 + 0x1C8)) * 8);
    var_v0 = (*(u8 **)((u8 *)((temp_a2 + (D_800BE9C0 * 4))) + 0x28C));
    var_v1 = (*(s32 *)((u8 *)((temp_a2 + ((D_800BE9C0 == 0) * 4))) + 0x28C));
    if (var_v0 != NULL) {
        if (arg1 != -1) {
            temp_t7 = *(s32 *)(*(s32 *)(((s32 *)((u8 *)&D_800C4440 + ((*(u8 *)((u8 *)arg0 + 4)) * 4)))) + (arg1 * 4)) * 0x10;
            var_v0 += temp_t7;
            var_v1 += temp_t7;
        }
        var_a0 = arg6;
        if (var_a0 != 0) {
            temp_a1 = (*(s16 *)((u8 *)var_v0 + 8));
            if (arg3 < temp_a1) {
                var_a0 -= arg3;
            } else if (temp_a1 < 0) {
                var_a0 += arg3;
            }
        }
        var_a1 = arg7;
        if (var_a1 != 0) {
            temp_a3 = (*(s16 *)((u8 *)var_v0 + 0xA));
            if (arg4 < temp_a3) {
                var_a1 -= arg4;
            } else if (temp_a3 < 0) {
                var_a1 += arg4;
            }
        }
        var_a2 = 0;
        temp_t4 = arg5 & 3;
        if (arg5 > 0) {
            if (temp_t4 != 0) {
                temp_t0 = 0 * 0x10;
                var_t1 = var_v0 + temp_t0;
                var_t2 = var_v1 + temp_t0;
                do {
                    var_a2 += 1;
                    var_t1 += 0x10;
                    (*(s16 *)((u8 *)var_t1 + -8)) = (s16) ((*(s16 *)((u8 *)var_t2 + 8)) + var_a0);
                    temp_t5 = (*(s16 *)((u8 *)var_t2 + 0xA));
                    var_t2 += 0x10;
                    (*(s16 *)((u8 *)var_t1 + -6)) = (s16) (temp_t5 + var_a1);
                } while (temp_t4 != var_a2);
                if (var_a2 != arg5) {
                    goto block_18;
                }
            } else {
block_18:
                temp_t0_2 = var_a2 * 0x10;
                var_t1_2 = var_v0 + temp_t0_2;
                var_t2_2 = var_v1 + temp_t0_2;
                do {
                    var_a2 += 4;
                    var_t1_2 += 0x40;
                    (*(s16 *)((u8 *)var_t1_2 + -0x38)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + 8)) + var_a0);
                    temp_t9 = (*(s16 *)((u8 *)var_t2_2 + 0xA));
                    var_t2_2 += 0x40;
                    (*(s16 *)((u8 *)var_t1_2 + -0x36)) = (s16) (temp_t9 + var_a1);
                    (*(s16 *)((u8 *)var_t1_2 + -0x28)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -0x28)) + var_a0);
                    (*(s16 *)((u8 *)var_t1_2 + -0x26)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -0x26)) + var_a1);
                    (*(s16 *)((u8 *)var_t1_2 + -0x18)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -0x18)) + var_a0);
                    (*(s16 *)((u8 *)var_t1_2 + -0x16)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -0x16)) + var_a1);
                    (*(s16 *)((u8 *)var_t1_2 + -8)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -8)) + var_a0);
                    (*(s16 *)((u8 *)var_t1_2 + -6)) = (s16) ((*(s16 *)((u8 *)var_t2_2 + -6)) + var_a1);
                } while (var_a2 != arg5);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15062FC0.s")
#endif
void func_15063168(struct127 *arg0) {
    s32 i;

    for (i = 0; i < D_8008FD8C; i++) {
        if ((i != (arg0 - D_800CC2D0)) && ((1 << i) & D_800CC268)) {
            if ((D_800CC2D0[i].unk31C != NULL) && (((u8 *)D_800CC2D0[i].unk31C)[0x1AC] == 0)) {
                func_15195564(arg0, &D_800CC2D0[i], 1);
            }
        }
    }
}
#ifdef NON_MATCHING
void func_15060F28(struct127 *obj, s32 mode);
s32 func_15082E44(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);

// obj_model_swap_keep_pose: sets the object's model record (+0x144: +4 = `a1`, +3 = `a2`, +0x20 / +0x24 = `scale`,
// +2 = 0), resets the object (func_15060F28 mode 0) and reloads model slot +0x13F (func_15082E44, owner = object
// index + 1), then puts back what the reset clears: position (+0x14..+0x1C, copied to +0x2C..+0x34, y also to
// +0x1CC), +0x318 (whose +0x3D4 gets the object's +0x31C), +0xB8, +0x40, +0xC4 and the yaw (+0x76, also +0x7A).
void func_15063254(struct127 *obj, s32 a1, s32 a2, f32 scale) {
    u8 *o = (u8 *) obj;
    u8 slot = o[0x13F];
    u8 *e = *(u8 **) (o + 0x144);
    u8 *link;
    f32 x;
    f32 y;
    f32 z;
    f32 fB8;
    f32 f40;
    f32 fC4;
    u16 yaw;

    e[4] = a1;
    e[3] = a2;
    *(f32 *) (e + 0x20) = scale;
    *(f32 *) (e + 0x24) = scale;
    e[2] = 0;
    link = *(u8 **) (o + 0x318);
    x = *(f32 *) (o + 0x14);
    y = *(f32 *) (o + 0x18);
    z = *(f32 *) (o + 0x1C);
    fB8 = *(f32 *) (o + 0xB8);
    f40 = *(f32 *) (o + 0x40);
    fC4 = *(f32 *) (o + 0xC4);
    yaw = *(u16 *) (o + 0x76);
    func_15060F28(obj, 0);
    func_15082E44(e, slot, 0, 0, (obj - D_800CC2D0) + 1);
    *(f32 *) (o + 0x14) = x;
    *(f32 *) (o + 0x18) = y;
    *(u8 **) (o + 0x318) = link;
    *(f32 *) (o + 0x1C) = z;
    *(f32 *) (o + 0xB8) = fB8;
    *(f32 *) (o + 0x40) = f40;
    *(u16 *) (o + 0x76) = yaw;
    *(u16 *) (o + 0x7A) = yaw;
    *(f32 *) (o + 0x2C) = x;
    *(f32 *) (o + 0x30) = y;
    *(f32 *) (o + 0x1CC) = *(f32 *) (o + 0x18);
    *(f32 *) (o + 0x34) = *(f32 *) (o + 0x1C);
    *(f32 *) (o + 0xC4) = fC4;
    *(s32 *) (link + 0x3D4) = *(s32 *) (o + 0x31C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_8FCB0/func_15063254.s")
#endif
