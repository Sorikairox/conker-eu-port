#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B5E0.s")
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B83C.s")

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

void func_1513BA10(struct132 *arg0) {
    D_80089C44[arg0->unk48]();
}

void func_1513BA44(struct132 *arg0) {
    D_80089C54[arg0->unk48]();
}

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
struct102 *func_1513B5E0(BAE8Params *, s32, s32, s32, s32);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513BBFC.s")
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
