#include <ultra64.h>

#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15122C5C(struct108 *arg0);
void func_150498A0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_151206C8(struct108 *);
void func_151220D0(struct108 *);
void func_151221F0(struct108 *, s32);
void func_151226E0(struct108 *);
void func_151229B0(struct108 *);
void func_15122EF0(struct108 *);
void func_15129EA4(struct108 *);
void func_1512DEA4(struct108 *);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, void *, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
void func_15049978(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_150ADD90(u8 *, u8 *, u8 *);
f32 func_150ADDE0(f32 *a, f32 *b);
void func_1504917C(struct17 *arg0, struct17 *arg1);
void func_15048F90(struct17 *arg0, struct17 *arg1, struct17 *arg2);
extern u8 D_800BEE2C;
extern f32 D_800DC430;
extern f32 D_80089950;
#endif

extern f32 D_800A34B0[4][2];
extern f32 D_800A34D4;
extern f32 D_800A34D8;
extern f32 D_800A34DC;
extern f32 D_800A34E0;
extern f32 D_800A34E4;
extern f32 D_800A34E8;
extern f32 D_800A34EC;
extern f32 D_800A34F0;
extern f32 D_800A34F4;
extern f32 D_800A34F8;
extern f32 D_800A34FC;
extern f32 D_800A3500;
extern f32 D_800A3504;
extern f32 D_800A3508;
extern f32 D_800A350C;
extern f32 D_800A3510;
extern f32 D_800A3514;
extern f32 D_800A3518;
extern f32 D_800A352C;
extern f32 D_800A3534;
extern f32 D_800A3538;
extern f32 D_800A353C;
extern f32 D_800A3540;
extern f32 D_800A3544;
extern f32 D_800A3548;
extern f32 D_800A354C;
extern f32 D_800A3550;
extern f32 D_800A3554;
extern f32 D_800A3558;
extern f32 D_800A355C;
extern f32 D_800A3560;
extern f32 D_800A3564;
extern f32 D_800A3568;
extern f32 D_800A356C;
extern f32 D_800A3570;
extern f32 D_800A3574;
extern f32 D_800A3578;
extern f32 D_800A357C;
extern f32 D_800A3580;
extern f32 D_800A3584;
extern f32 D_800A3588;
extern f32 D_800A358C;
extern f32 D_800A3590;
extern f32 D_800A3594;
extern f32 D_800A3598;
extern f32 D_800A359C;
extern f32 D_800A35A0;
extern f32 D_800A35A4;
extern f32 D_800A35A8;
#if 0
f32 D_800A34B0[4][2] = {
    { 267.0f, 100.0f },
    { 247.0f, 100.0f },
    { 370.0f, 185.0f },
    { 530.0f, 400.0f }
};

f32 0.02f = 0.01666666753590107f;
f32 D_800A34D4 = 0.10000000149011612f;
f32 D_800A34D8 = 999.0f;
f32 D_800A34DC = 0.01745329238474369f;
f32 D_800A34E0 = 0.01745329238474369f;
f32 D_800A34E4 = 0.01745329238474369f;
f32 D_800A34E8 = 0.01745329238474369f;
f32 D_800A34EC = 530.0f;
f32 D_800A34F0 = 3.1415927410125732f;
f32 D_800A34F4 = 3.1415927410125732f;
f32 D_800A34F8 = 0.3253220021724701f;
f32 D_800A34FC = 1.5707963705062866f;
f32 D_800A3500 = 1.5707963705062866f;
f32 D_800A3504 = 0.6499999761581421f;
f32 D_800A3508 = 0.550000011920929f;
f32 D_800A350C = 0.8999999761581421f;
f32 D_800A3510 = 0.8500000238418579f;
f32 D_800A3514 = -10000.0f;
f32 D_800A3518 = 0.0033333334140479565f;
f32 57.295776f = 57.2957763671875f;
f32 0.017453292f = 0.01745329238474369f;
f32 0.017453292f = 0.01745329238474369f;
f32 0.017453292f = 0.01745329238474369f;
f32 D_800A352C = 0.01745329238474369f;
f32 0.017453292f = 0.01745329238474369f;
f32 D_800A3534 = 6.2831854820251465f;
f32 D_800A3538 = 0.01745329238474369f;
f32 D_800A353C = 0.03999999910593033f;
f32 D_800A3540 = 0.05000000074505806f;
f32 D_800A3544 = 0.07999999821186066f;
f32 D_800A3548 = 0.03999999910593033f;
f32 D_800A354C = 0.05000000074505806f;
f32 D_800A3550 = 0.01745329238474369f;
f32 D_800A3554 = 0.01745329238474369f;
f32 D_800A3558 = 0.019999999552965164f;
f32 D_800A355C = 0.01745329238474369f;
f32 D_800A3560 = 0.6000000238418579f;
f32 D_800A3564 = 10000.0f;
f32 D_800A3568 = 10000.0f;
f32 D_800A356C = -0.01745329238474369f;
f32 D_800A3570 = -0.01745329238474369f;
f32 D_800A3574 = -0.01745329238474369f;
f32 D_800A3578 = -0.01745329238474369f;
f32 D_800A357C = -0.9399999976158142f;
f32 D_800A3580 = -10000.0f;
f32 D_800A3584 = 0.01666666753590107f;
f32 D_800A3588 = 0.01745329238474369f;
f32 D_800A358C = 0.02500000037252903f;
f32 D_800A3590 = -0.01745329238474369f;
f32 D_800A3594 = -0.01745329238474369f;
f32 D_800A3598 = -0.01745329238474369f;
f32 D_800A359C = -0.01745329238474369f;
f32 D_800A35A0 = 999.0f;
f32 D_800A35A4 = 0.01745329238474369f;
f32 D_800A35A8 = 999.0f;
f32 999.0f = 999.0f;
#endif

void func_15122AE0(void) {
    struct108 *temp_s0;
    s16 i;
    f32 temp_f20;

    temp_f20 = D_800BEA08 * 0.02f;

    for (i = 0; i <= D_80082FA0; i++) {
        temp_s0 = &D_800DBFF0[i]; // ???
        if (func_150859AC(i, 0) || (i == 0)) {
            temp_s0->unk7B4 = temp_f20;
            if ((D_800BEAC0 == 0) || (D_800C35EA != 0) || (D_800D2DB4 != 0)) {
                func_151239CC(temp_s0, 5);
                func_15122C5C(temp_s0);
            } else {
                func_15123934(temp_s0, 8192, 0, temp_s0->unk134, 5);
                func_1512C490(temp_s0);
            }
        }
    }
    D_800894B0 += 1;
}

#ifdef NON_MATCHING
void func_1510B6A8(s32 player, f32 fovX, f32 fovY, f32 scale, f32 width);
s32 func_15097BA8(s32);
void func_15125A6C(u8 *);
s32 func_15129220(struct108 *);
s32 func_15125DB4(struct108 *);
void func_15127EB8(struct108 *);
s32 func_15128540(struct108 *);
void func_15123070(u8 *arg0);
s32 func_1512EE50(struct108 *);
void func_151307A0(struct108 *, s32);
void func_15126138(struct108 *);
void func_15125C40(u8 *);
void func_15128680(struct108 *);
s32 func_1512317C(struct108 *);
void func_15125394(struct108 *);
void func_15123568(struct108 *);
void func_1512C770(struct108 *);
void func_15125924(struct108 *);
void func_151283B8(struct108 *);
void func_15125594(struct108 *);
void func_15123508(struct108 *);
s32 func_1512D900(struct108 *);
s32 func_151256BC(struct108 *);
void func_1512DEF0(struct108 *);
void func_1512C5D8(struct108 *);
void func_1512B670(u8 *);
s32 func_1512C77C(struct108 *);
s32 func_1512C080(struct108 *);
s32 func_15128D50(struct108 *, s32, s32);
s32 func_1512C6C0(struct108 *);
void func_151284C4(struct108 *);
extern u16 D_800BEB30[];

#define CAM_W(o) (*(s32 *)(p + (o)))
#define CAM_H(o) (*(s16 *)(p + (o)))
#define CAM_F(o) (*(f32 *)(p + (o)))

/* Per-frame update of one camera controller (front end / cutscene branch of func_15122AE0): keep the previous
 * eye / target (0x2BC.. / 0x2F8..), copy the player's settings, ease the field of view 0x19C/0x1A0 toward
 * 0x1A4/0x1A8 (snap on the first frame, 0x23C), set the projection (func_1510B6A8), then run the controller steps. */
void func_15122C5C(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *eye = p + 0x2BC;
    u8 *at = p + 0x2F8;
    u8 *obj;
    s16 mode;
    u8 pl;
    f32 k;
    f32 w;
    s32 fl;

    if (p[0x23C] != 0) {
        CAM_W(0x2E0) = CAM_W(0x2BC);
        CAM_W(0x2E4) = CAM_W(0x2C0);
        CAM_W(0x2F0) = CAM_W(0x2FC);
        CAM_W(0x2E8) = CAM_W(0x2C4);
        CAM_W(0x2EC) = CAM_W(0x2F8);
        CAM_W(0x2F4) = CAM_W(0x300);
    }
    obj = *(u8 **)(p + 0x3D4);
    if (obj != NULL) {
        mode = CAM_H(0x73C);
        if (mode != 3 && (CAM_W(0x2C) != 0x100 || mode != 0)) {
            p[0x23E] = obj[0x78];
        }
    }
    if (D_800DBFF4[p[0x23D]] != 4) {
        CAM_W(0x5F0) &= ~4;
    }
    if (!(CAM_W(0x2C) & 0x400000)) {
        ((s32 *)eye)[0] = CAM_W(0x2E0);
        ((s32 *)eye)[1] = CAM_W(0x2E4);
        ((s32 *)eye)[2] = CAM_W(0x2E8);
        ((s32 *)at)[0] = CAM_W(0x2EC);
        ((s32 *)at)[1] = CAM_W(0x2F0);
        ((s32 *)at)[2] = CAM_W(0x2F4);
    }
    pl = p[0x23D];
    CAM_W(0x36C) = (*(s32 **)&D_800BE728)[pl];
    CAM_H(0x36A) = D_800BEB30[pl];
    CAM_W(0x304) = ((s32 *)at)[0];
    CAM_W(0x308) = ((s32 *)at)[1];
    CAM_F(0x358) = CAM_F(0x35C);
    CAM_W(0x30C) = ((s32 *)at)[2];
    CAM_W(0x2C8) = ((s32 *)eye)[0];
    CAM_W(0x2CC) = ((s32 *)eye)[1];
    CAM_W(0x2D0) = ((s32 *)eye)[2];
    if (p[0x23C] != 0) {
        CAM_F(0x19C) = CAM_F(0x1A4);
        CAM_F(0x1A0) = CAM_F(0x1A8);
    } else {
        k = 0.1f; /* D_800A38A4 */
        CAM_F(0x19C) = CAM_F(0x19C) + (CAM_F(0x1A4) - CAM_F(0x19C)) * k;
        CAM_F(0x1A0) = CAM_F(0x1A0) + (CAM_F(0x1A8) - CAM_F(0x1A0)) * k;
    }
    if (CAM_W(0x2C) & 0x100) {
        w = 16.0f;
    } else {
        w = 0.0f;
    }
    pl = p[0x23D];
    func_1510B6A8(pl, CAM_F(0x19C), CAM_F(0x1A0), *(f32 *)((u8 *)D_800BE628 + pl * 0x180 + 0x84), w);
    func_15097BA8(p[0x23D]);
    func_15125A6C(p);
    func_15129220(arg0);
    func_15125DB4(arg0);
    obj = *(u8 **)(p + 0x3D4);
    if (obj[0x120] != 0 && obj[0x197] != 0) {
        func_15127EB8(arg0);
    }
    if (func_15128540(arg0) != 0) {
        return;
    }
    fl = CAM_W(0x84);
    if ((fl & 0x08000000) && !(fl & 0x400)) {
        func_1512EE50(arg0);
    }
    func_151307A0(arg0, D_800BE9F0);
    func_15126138(arg0);
    func_15125C40(p);
    func_15128680(arg0);
    func_1512317C(arg0);
    func_15125394(arg0);
    fl = CAM_W(0x84);
    if (!(fl & 0x08000000) && !(fl & 0x400)) {
        func_1512EE50(arg0);
    }
    func_15123568(arg0);
    func_1512C770(arg0);
    func_15125924(arg0);
    func_151283B8(arg0);
    if (p[0x23C] != 0) {
        func_15125594(arg0);
        func_15123070(p);
        func_151283B8(arg0);
        func_151283B8(arg0);
    }
    func_15123508(arg0);
    if ((CAM_W(0x84) & 2) && (*(u8 **)(p + 0x3D4))[0x120] == 0) {
        func_1512D900(arg0);
    }
    func_15125594(arg0);
    func_151256BC(arg0);
    func_1512DEF0(arg0);
    func_1512C5D8(arg0);
    func_1512B670(p);
    func_1512C77C(arg0);
    func_1512C080(arg0);
    if (p[0x23C] != 0) {
        func_1512C5D8(arg0);
        func_1512B670(p);
        func_1512C77C(arg0);
        func_1512C080(arg0);
    }
    func_15125594(arg0);
    func_15123070(p);
    if (*(u16 *)(p + 0x7F4) == 0) {
        func_15128D50(arg0, 0, 0);
    }
    func_1512C6C0(arg0);
    func_151284C4(arg0);
}
#undef CAM_W
#undef CAM_H
#undef CAM_F
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15122C5C.s")
#endif
// NON-MATCHING: 80% there
// void func_15122C5C(struct108 *arg0) {
//     f32 phi_f12;
//     u8 temp_v0_2;
//     struct167 *temp_a1;
//     struct167 *temp_a0;
//
//     if (arg0->unk23C) {
//         arg0->unk2E0 = arg0->unk2BC;
//         arg0->unk2E4 = arg0->unk2C0;
//         arg0->unk2F0 = arg0->unk2FC;
//
//         arg0->unk2EC = arg0->unk2F8;
//         arg0->unk2E8 = arg0->unk2C4;
//         arg0->unk2F4 = arg0->unk300;
//     }
//
//     temp_a0 = &arg0->unk2BC;
//     temp_a1 = &arg0->unk2F8;
//
//     if ((arg0->unk3D4 != NULL) && (arg0->unk73C != 3) && ((arg0->unk2C != 0x100) || (arg0->unk73C != 0))) {
//         arg0->unk23E = arg0->unk3D4->unk78;
//     }
//
//     temp_v0_2 = arg0->unk23D;
//
//     if (D_800DBFF4[temp_v0_2] != 4) {
//         arg0->unk5F0 &= -5;
//     }
//
//     if ((arg0->unk2C << 9) >= 0) {
//         temp_a0->unk0 = arg0->unk2E0;
//         temp_a0->unk4 = arg0->unk2E4;
//         temp_a0->unk8 = arg0->unk2E8;
//         temp_a1->unk0 = arg0->unk2EC;
//         temp_a1->unk4 = arg0->unk2F0;
//         temp_a1->unk8 = arg0->unk2F4;
//     }
//     // temp_v0_2 = arg0->unk23D;
//     arg0->unk36C = D_800BE728[temp_v0_2];
//     arg0->unk36A = D_800BE710[temp_v0_2];
//     arg0->unk304 = temp_a1->unk0;
//     arg0->unk308 = temp_a1->unk4;
//     arg0->unk358 = arg0->unk35C;
//     arg0->unk30C = temp_a1->unk8;
//     arg0->unk2C8 = temp_a0->unk0;
//     arg0->unk2CC = temp_a0->unk4;
//     arg0->unk2D0 = temp_a0->unk8;
//     if (arg0->unk23C != 0) {
//         arg0->unk19C = arg0->unk1A4;
//         arg0->unk1A0 = arg0->unk1A8;
//         // phi_f12 = *(s32*)&arg0; // unk0?
//     } else {
//         arg0->unk19C += (arg0->unk1A4 - arg0->unk19C) * D_800A34D4;
//         arg0->unk1A0 += (arg0->unk1A8 - arg0->unk1A0) * D_800A34D4;
//         phi_f12 = D_800A34D4;
//     }
//
//     func_1510B128(phi_f12, temp_v0_2, arg0->unk19C, arg0->unk1A0, D_800BE628[temp_v0_2].unk84, (arg0->unk2C & 0x100) ? 16.0f : 0.0f);
//     func_15097798(arg0->unk23D);
//     func_15125A6C(arg0);
//     func_15128CB0(arg0);
//     func_15125DB4(arg0);
//     if ((arg0->unk3D4->unk120 != 0) && (arg0->unk3D4->unk197 != 0)) {
//         func_15127EB8(arg0);
//     }
//     if (func_15128540(arg0) == 0) {
//         if (((arg0->unk84 * 0x10) < 0) && ((arg0->unk84 & 0x400) == 0)) {
//             func_1512E8E0(arg0);
//         }
//         func_15130230(arg0, D_800BE9F0);
//         func_15126138(arg0);
//         func_15125C40(arg0);
//         func_15128680(arg0);
//         func_1512317C(arg0);
//         func_15125394(arg0);
//         if (((arg0->unk84 * 16) >= 0) && ((arg0->unk84 & 0x400) == 0)) {
//             func_1512E8E0(arg0);
//         }
//         func_15123568(arg0);
//         func_1512C200(arg0);
//         func_15125924(arg0);
//         func_151283B8(arg0);
//         if (arg0->unk23C != 0) {
//             func_15125594(arg0);
//             func_15123070(arg0);
//             func_151283B8(arg0);
//             func_151283B8(arg0);
//         }
//         func_15123508(arg0);
//         if (((arg0->unk84 & 2) != 0) && (arg0->unk3D4->unk120 == 0)) {
//             func_1512D390(arg0);
//         }
//         func_15125594(arg0);
//         func_151256BC(arg0);
//         func_1512D980(arg0);
//         func_1512C068(arg0);
//         func_1512B100(arg0);
//         func_1512C20C(arg0);
//         func_1512BB10(arg0);
//         if (arg0->unk23C != 0) {
//             func_1512C068(arg0);
//             func_1512B100(arg0);
//             func_1512C20C(arg0);
//             func_1512BB10(arg0);
//         }
//         func_15125594(arg0);
//         func_15123070(arg0);
//         if (arg0->unk7F4 == 0) {
//             func_151287E0(arg0, 0, 0);
//         }
//         func_1512C150(arg0);
//         func_151284C4(arg0);
//     }
// }

void func_15123070(u8 *arg0) {
    f32 a;
    struct17 tmp;

    if (*(s32 *)(arg0 + 0x6C8) != 0 && (*(s32 *)(arg0 + 0x6FC) == 10 || *(s32 *)(arg0 + 0x6FC) == 14)) {
        func_15048F90((struct17 *)(arg0 + 0x618), (struct17 *)(arg0 + 0x2A4), &tmp);
        *(f32 *)(arg0 + 0x390) = *(f32 *)(arg0 + 0x37C) - func_15048FC8(&tmp);
        if (!arg0 && !arg0 && !arg0) { // fakematch: permuter barrier (puts the -360.0f lui in the arm)
        }
    } else {
        a = *(f32 *)(*(u8 **)(arg0 + 0x3D0) + 0x40) - *(f32 *)(arg0 + 0x37C) - 180.0f;
        while (a < 0.0f) {
            a += 360.0f;
        }
        *(f32 *)(arg0 + 0x390) = a;
    }
    while (*(f32 *)(arg0 + 0x390) < -360.0f) {
        *(f32 *)(arg0 + 0x390) += 360.0f;
    }
}
// NON-MATCHING: 1 missing lui
// void func_15123070(struct108 *arg0) {
//     f32 temp_f0;
//     struct17 tmp;
//
//     if ((arg0->unk6C8 != 0) && ((arg0->unk6FC == 10) || (arg0->unk6FC == 14))) {
//         func_15048F90(&arg0->unk618, &arg0->unk2A4, &tmp, arg0);
//         arg0->unk390 = arg0->unk37C - func_15048FC8(&tmp);
//     } else {
//         temp_f0 = arg0->unk3D0->unk40 - arg0->unk37C - 180.0f;
//
//         while (temp_f0 < 0.0f) {
//             temp_f0 += 360.0f;
//         }
//
//         arg0->unk390 = temp_f0;
//     }
//
//     while (arg0->unk390 < -360.0f) {
//         arg0->unk390 += 360.0f;
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_1512317C.s")

void func_15123508(struct108 *arg0) {
    if ((arg0->unk84 & 2) != 0) {
        if (((arg0->unk36A & 2) != 0) && (arg0->unk698 == 0)) {
            arg0->unk6B0 = -1;
        }
        if (((arg0->unk36A & 1) != 0) && (arg0->unk698 == 0)) {
            arg0->unk6B0 = 1;
        }
    }
}

#ifdef NON_MATCHING
void func_15123568(struct108 *arg0) {
    f32 temp_v0;
    s32 temp_t1;

    if ((arg0->unk3D4->unk120 == 4) && (arg0->unk2C != 0x40) && (arg0->pad8EE[0x3E] == 0)) {
        arg0->unk1B4 = 1;
        (*(f32 *)((u8 *)arg0 + 0x7C0)) = 999.0f;
        func_15124B18(arg0);
        arg0->unk198 = 0.0f;
        arg0->unk190 = 0.0f;
        return;
    }
    temp_v0 = arg0->unk7B8;
    if ((*(s32 *)&(temp_v0)) > 0) {
        temp_t1 = (*(s32 *)&(temp_v0)) - D_800BE9E4;
        arg0->unk7B8 = (*(f32 *)&(temp_t1));
        if (temp_t1 < 0) {
            arg0->unk7B8 = 0.0f;
        }
    } else if ((arg0->unk84 & 4) && (arg0->unk36A & 8) && (arg0->unkDC != 4) && ((arg0->unk6C8 == 0) || (arg0->unk6FC == 4)) && ((arg0->unk3D0->in_water != 1) || (arg0->unk1B4 != 1)) && (arg0->unk1B4 != 1)) {
        do {
            arg0->unk1B4 -= 1;
            if (arg0->unk1B4 <= 0) {
                arg0->unk1B4 = 3;
            }
        } while (!((1 << arg0->unk1B4) & arg0->unk1E0));
        func_15124B18(arg0);
        func_15125608(arg0);
        arg0->unk7B8 = 2.8e-44f;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15123568.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_151236D0.s")
s32 func_15123934(struct108 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
#define STK ((struct_eu_108_stack *)arg0)
    if (STK->unk20C[arg4] == 0) {
        STK->unk0[arg4 + 1] = STK->unk0[0];
        STK->unk2C[arg4 + 1] = STK->unk2C[0];
        STK->unk84[arg4 + 1] = STK->unk84[0];
        STK->unkDC[arg4 + 1] = STK->unkDC[0];
        STK->unk134[arg4 + 1] = STK->unk134[0];
        STK->unk1B4[arg4 + 1] = STK->unk1B4[0];
        STK->unk1E0[arg4 + 1] = STK->unk1E0[0];
        STK->unk2C[0] = arg1;
        STK->unkDC[0] = arg2;
        STK->unk134[0] = arg3;
        STK->unk20C[arg4] = 1;
        func_15125394(arg0);
        return 1;
    }
    return 0;
#undef STK
}

s32 func_151239CC(struct108 *arg0, s32 arg1) {
#define STK ((struct_eu_108_stack *)arg0)
    if (STK->unk20C[arg1] != 0) {
        STK->unk0[0] = STK->unk0[arg1 + 1];
        STK->unk2C[0] = STK->unk2C[arg1 + 1];
        STK->unkDC[0] = STK->unkDC[arg1 + 1];
        STK->unk84[0] = STK->unk84[arg1 + 1];
        STK->unk134[0] = STK->unk134[arg1 + 1];
        STK->unk1B4[0] = STK->unk1B4[arg1 + 1];
        STK->unk1E0[0] = STK->unk1E0[arg1 + 1];
        func_15124B18(arg0);
        STK->unk20C[arg1] = 0;
        return 1;
    }
    return 0;
#undef STK
}
#ifdef NON_MATCHING
/* P41: camera eye orbit. eye (0x2F8 / 0x300) = at (0x2BC / 0x2C4) + (sin, cos)(yaw) * distance 0x370, where 0x370
 * eases toward the wanted distance 0x374 (rates 0x3B4 / 0x3B8, chosen from the mode and flags). The yaw 0x37C / 0x39C
 * can be turned toward the record's heading (pad button 4 of 0x36C, the 0x8E4 / 0x8E8 timer; the 0x3D4 object's
 * +0x95 flag), and spun by D_800BEE2C. Two ray casts (func_150ACEA0) from the target toward the eye shorten
 * 0x374 against walls (0x600 / 0x604 = hit and distance). 0x374 is restored to its entry value at the end. */
void func_15123A54(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *rec;
    u16 *pad;
    f32 save;
    f32 yaw;
    f32 d;
    s32 v0;
    s32 v1;
    f32 sp104[3];
    s16 tri[9];
    f32 hitE4;
    f32 hitE8;
    f32 hitEC;
    f32 hitE0;
    s16 triC8[9];
    f32 hit8C;
    f32 hit90;
    f32 hit94;
    f32 hit88;
    f32 bx;
    f32 bz;
    f32 va[3];
    f32 vb[3];
    f32 vc[3];
    f32 e1[3];
    f32 e2[3];
    f32 n[3];
    f32 old;
    f32 dx;
    f32 dz;

    save = *(f32 *)(p + 0x374);
    p[0x600] = 0;
    *(f32 *)(p + 0x604) = save;
    if (D_800C3671 != 0) {
        return;
    }
    d = *(f32 *)(p + 0x6F8);
    if (!(0.0f == d)) {
        *(f32 *)(p + 0x374) = (d < save) ? d : save;
    }
    rec = *(u8 **)(p + 0x3D0);
    if (p[0x23C] != 0) {
        *(f32 *)(p + 0x39C) = *(f32 *)(p + 0x37C) * 0.0174532924f;
    } else {
        if ((*(s32 *)(p + 0x5F0) & 0x10) && (**(u16 **)(p + 0x36C) & 0x10)) {
            *(f32 *)(p + 0x374) = 130.0f;
        }
        if (*(s16 *)(p + 0x73C) == 0 && (*(s32 *)(p + 0x5F0) & 0x40)) {
            *(f32 *)(p + 0x374) = 420.0f;
        }
        if (*(s32 *)(p + 0x2C) & 0x403) {
            if (*(u16 *)(p + 0x36A) & 4) {
                p[0x8E4] = 1;
                *(s32 *)(p + 0x8E8) = 0x96;
                *(f32 *)(p + 0x8E0) = 0.0f;
            } else {
                pad = *(u16 **)(p + 0x36C);
                v1 = *pad & 4;
                if (v1 != 0 || p[0x8E4] != 0) {
                    v0 = p[0x8E4];
                    if (v0 != 0 && v1 != 0) {
                        v1 = (u8)(v0 + D_800BEA08);
                        if (v1 < 0x10) {
                            p[0x8E4] = v1;
                            v0 = v1;
                        } else {
                            p[0x8E4] = 15;
                            v0 = 15;
                        }
                    }
                    rec = *(u8 **)(p + 0x3D0);
                    if (v0 == 15) {
                        p[0x8EC] = 1;
                        *(s32 *)(p + 0x7B8) = 20;
                        *(f32 *)(p + 0x374) = 300.0f;
                        *(f32 *)(p + 0x348) = 150.0f;
                        func_15049978((f32 *)(p + 0x37C), *(f32 *)(rec + 0x40) - 180.0f, (f32 *)(p + 0x8E0), 1.5f, 2.0f,
                                      *(f32 *)(p + 0x7B4));
                        if (!(**(u16 **)(p + 0x36C) & 4)) {
                            p[0x8E4] = 0;
                        }
                    } else {
                        func_15049978((f32 *)(p + 0x37C), *(f32 *)(rec + 0x40) - 180.0f, (f32 *)(p + 0x8E0), 2.0f, 4.0f,
                                      *(f32 *)(p + 0x7B4));
                    }
                    *(f32 *)(p + 0x39C) = *(f32 *)(p + 0x37C) * 0.0174532924f;
                    if (p[0x8E4] < 15 && !(**(u16 **)(p + 0x36C) & 4)) {
                        if (*(s16 *)(p + 0x298) != 0) {
                            p[0x8E4] = 0;
                        } else {
                            *(s32 *)(p + 0x8E8) = *(s32 *)(p + 0x8E8) - D_800BEA08;
                            if (*(s32 *)(p + 0x8E8) <= 0) {
                                p[0x8E4] = 0;
                            } else {
                                rec = *(u8 **)(p + 0x3D0);
                                d = *(f32 *)(p + 0x37C) - (*(f32 *)(rec + 0x40) - 180.0f);
                                if (d < 0.0f) {
                                    d = -d;
                                }
                                if (d <= 2.0f) {
                                    p[0x8E4] = 0;
                                }
                            }
                        }
                    }
                } else if (p[0x8EC] != 0) {
                    func_15124B18(arg0);
                    p[0x8EC] = 0;
                    p[0x8E4] = 0;
                }
            }
        }
    }
    yaw = *(f32 *)(p + 0x39C);
    if (D_800BEE2C != 0) {
        *(f32 *)(p + 0x37C) = *(f32 *)(p + 0x37C) + 1.20000005f * *(f32 *)(p + 0x7E0) * (f32)D_800BEA08;
        yaw = *(f32 *)(p + 0x39C) = *(f32 *)(p + 0x37C) * 0.0174532924f;
    } else {
        *(f32 *)(p + 0x7E0) = (func_150ADA20() & 1) ? -1.0f : 1.0f;
    }
    if ((*(u8 **)(p + 0x3D4))[0x95] != 0 && (*(s32 *)(p + 0x5F0) & 0x40)) {
        rec = *(u8 **)(p + 0x3D0);
        func_15049978((f32 *)(p + 0x37C), *(f32 *)(rec + 0x40) + 180.0f, (f32 *)(p + 0x844), 2.0f, 4.0f, *(f32 *)(p + 0x7B4));
        yaw = *(f32 *)(p + 0x39C) = *(f32 *)(p + 0x37C) * 0.0174532924f;
        *(f32 *)(p + 0x374) = 530.0f;
    }
    if (*(s32 *)(p + 0x2C) == 0x2000) {
        return;
    }
    dx = *(f32 *)(p + 0x2F8) - *(f32 *)(p + 0x2BC);
    dz = *(f32 *)(p + 0x300) - *(f32 *)(p + 0x2C4);
    *(f32 *)(p + 0x370) = sqrtf(dx * dx + dz * dz);
    rec = *(u8 **)(p + 0x3D0);
    if (*(s16 *)(p + 0x73C) != 0 || p[0x23C] != 0 || rec[0x102] != 0 ||
        !((*(s32 *)(p + 0x84) & 0x1000) || p[0x92C] != 0 || (*(s32 *)(p + 0x84) & 0x40000) || (*(s32 *)(p + 0x5F0) & 0x80))) {
        sp104[0] = sinf(*(f32 *)(p + 0x39C));
        sp104[1] = 0.0f;
        sp104[2] = cosf(*(f32 *)(p + 0x39C));
        if (func_150ACEA0(*(f32 *)(p + 0x2A4), *(f32 *)(p + 0x2A8) + 140.0f, *(f32 *)(p + 0x2AC), sp104[0], sp104[1], sp104[2], 0, tri, &hitE4, &hitE8,
                          &hitEC, &hitE0, 0, 0, *(f32 *)(p + 0x374) + 30.0f) != 0 &&
            hitE0 < *(f32 *)(p + 0x374)) {
            bx = sinf(*(f32 *)(p + 0x39C) + 3.14159274f) * *(f32 *)(p + 0x374);
            bz = cosf(*(f32 *)(p + 0x39C) + 3.14159274f) * *(f32 *)(p + 0x374);
            va[0] = tri[0];
            va[1] = tri[1];
            va[2] = tri[2];
            vb[0] = tri[3];
            vb[1] = tri[4];
            vb[2] = tri[5];
            vc[0] = tri[6];
            vc[1] = tri[7];
            vc[2] = tri[8];
            func_15048F90((struct17 *)va, (struct17 *)vb, (struct17 *)e1);
            func_15048F90((struct17 *)va, (struct17 *)vc, (struct17 *)e2);
            func_150ADD90((u8 *)e2, (u8 *)e1, (u8 *)n);
            func_1504917C((struct17 *)n, (struct17 *)n);
            if (0.325322002f < func_150ADDE0(sp104, n) &&
                func_150ACEA0(*(f32 *)(p + 0x2A4) - bx, *(f32 *)(p + 0x2A8) + 140.0f, *(f32 *)(p + 0x2AC) - bz, bx, 0.0f, bz, 0, triC8, &hit8C, &hit90,
                              &hit94, &hit88, 0, 0, *(f32 *)(p + 0x374) + 30.0f) != 0) {
                dx = hit8C - hitE4;
                dz = hit94 - hitEC;
                if (sqrtf(dx * dx + dz * dz) < 1.0f || (*(s32 *)(p + 0x5F0) & 0x10) || p[0x23E] == 0xC || p[0x23E] == 9 ||
                    p[0x23E] == 0x38 || p[0x23E] == 0x39 || p[0x23E] == 0x37 || p[0x23E] == 0x3B ||
                    p[0x23E] == 0x12 || p[0x23E] == 0x15 || p[0x23E] == 0x26 || p[0x23E] == 0x3A ||
                    p[0x23C] != 0) {
                    old = *(f32 *)(p + 0x374);
                    d = hitE0 - ((*(s16 *)(p + 0x73C) != 0) ? 16.0f : 12.0f);
                    hitE0 = (d < 50.0f) ? 50.0f : d;
                    *(f32 *)(p + 0x374) = (hitE0 < *(f32 *)(p + 0x374)) ? hitE0 : *(f32 *)(p + 0x374);
                    if (p[0x23E] == 3) {
                        *(f32 *)(p + 0x348) = *(f32 *)(p + 0x348) * (*(f32 *)(p + 0x374) / old);
                        if (*(s32 *)(p + 0x5F0) & 0x10) {
                            d = *(f32 *)(p + 0x2C0) - *(f32 *)(p + 0x354);
                            *(f32 *)(p + 0x348) = (*(f32 *)(p + 0x348) < d) ? d : *(f32 *)(p + 0x348);
                        }
                    }
                    p[0x600] = 1;
                    *(f32 *)(p + 0x604) = hitE0;
                }
            }
        }
    }
    if (*(u16 *)(p + 0x7F4) != 0) {
        *(f32 *)(p + 0x374) = D_800DC430;
    }
    rec = *(u8 **)(p + 0x3D0);
    if (p[0x23C] != 0) {
        *(f32 *)(p + 0x370) = *(f32 *)(p + 0x374);
        *(f32 *)(p + 0x258) = 0.0f;
        if (*(s32 *)(p + 0x84) & 0x200000) {
            if (*(s32 *)(p + 0x2C) & 0x40) {
                *(f32 *)(p + 0x974) = 1.0f;
                *(f32 *)(p + 0x964) = 1.0f;
                *(f32 *)(p + 0x978) = 2.0f;
                *(f32 *)(p + 0x968) = 2.0f;
            } else {
                *(f32 *)(p + 0x978) = 8.0f;
                *(f32 *)(p + 0x968) = 8.0f;
                *(f32 *)(p + 0x974) = 6.0f;
                *(f32 *)(p + 0x964) = 6.0f;
            }
            *(f32 *)(p + 0x984) = 0.0f;
            *(f32 *)(p + 0x988) = 0.0f;
        }
    } else {
        v0 = *(s32 *)(p + 0x2C);
        if (*(s32 *)(p + 0x7B8) != 0 || (v0 & 0x100) || ((v0 & 0x80) && (**(u16 **)(p + 0x36C) & 0x10))) {
            *(f32 *)(p + 0x3B4) = 6.0f;
            *(f32 *)(p + 0x3B8) = 10.0f;
        } else if (D_800BE616 != 0 || (*(s32 *)(p + 0x84) & 0x200000)) {
            if (v0 & 0x40) {
                *(f32 *)(p + 0x974) = 1.0f;
                *(f32 *)(p + 0x978) = 2.0f;
            } else {
                *(f32 *)(p + 0x974) = 6.0f;
                *(f32 *)(p + 0x978) = 8.0f;
            }
            func_150498A0((f32 *)(p + 0x964), *(f32 *)(p + 0x974), (f32 *)(p + 0x984), 1.0f, 2.0f, *(f32 *)(p + 0x7B4));
            func_150498A0((f32 *)(p + 0x968), *(f32 *)(p + 0x978), (f32 *)(p + 0x988), 1.0f, 2.0f, *(f32 *)(p + 0x7B4));
            *(f32 *)(p + 0x3B4) = *(f32 *)(p + 0x964);
            *(f32 *)(p + 0x3B8) = *(f32 *)(p + 0x968);
        } else if (rec[0x102] != 0 || p[0x8EC] != 0 || (p[0x92C] != 0 && (*(u16 *)(p + 0x920) & 0x40))) {
            *(f32 *)(p + 0x3B4) = 6.0f;
            *(f32 *)(p + 0x3B8) = 8.0f;
        } else if ((*(u16 *)(p + 0x36A) & 3) || (v0 & 0x40)) {
            *(f32 *)(p + 0x3B4) = 1.0f;
            *(f32 *)(p + 0x3B8) = 2.0f;
        } else {
            *(f32 *)(p + 0x3B4) = 2.0f;
            *(f32 *)(p + 0x3B8) = 3.0f;
        }
        if (D_800BEE2C == 0) {
            if (p[0x600] != 0) {
                if (*(s16 *)(p + 0x73C) != 0 || D_800BE616 != 0) {
                    func_150498A0((f32 *)(p + 0x370), *(f32 *)(p + 0x374), (f32 *)(p + 0x258), 8.0f, 10.0f, *(f32 *)(p + 0x7B4));
                } else {
                    func_150498A0((f32 *)(p + 0x370), *(f32 *)(p + 0x374), (f32 *)(p + 0x258), 6.0f, 8.0f, *(f32 *)(p + 0x7B4));
                }
            } else {
                func_150498A0((f32 *)(p + 0x370), *(f32 *)(p + 0x374), (f32 *)(p + 0x258), *(f32 *)(p + 0x3B4), *(f32 *)(p + 0x3B8), *(f32 *)(p + 0x7B4));
            }
        } else if (0.0f == D_80089950 && (p[0x3E8] != 0 || rec[0x102] != 0)) {
            func_150498A0((f32 *)(p + 0x370), 200.0f, (f32 *)(p + 0x258), 4.0f, 8.0f, *(f32 *)(p + 0x7B4));
        } else {
            func_150498A0((f32 *)(p + 0x370), 200.0f, (f32 *)(p + 0x258), 0.5f, 1.0f, *(f32 *)(p + 0x7B4));
        }
    }
    *(f32 *)(p + 0x2F8) = sinf(yaw) * *(f32 *)(p + 0x370) + *(f32 *)(p + 0x2BC);
    *(f32 *)(p + 0x300) = cosf(yaw) * *(f32 *)(p + 0x370) + *(f32 *)(p + 0x2C4);
    dx = *(f32 *)(p + 0x2F8) - *(f32 *)(p + 0x2BC);
    dz = *(f32 *)(p + 0x300) - *(f32 *)(p + 0x2C4);
    *(f32 *)(p + 0x370) = sqrtf(dx * dx + dz * dz);
    if (*(f32 *)(p + 0x374) + *(f32 *)(p + 0x374) < *(f32 *)(p + 0x370)) {
        pad = *(u16 **)(p + 0x36C);
        if ((*pad & 3) && D_800BE616 == 0) {
            *pad = *pad & 0xFFFC;
            *(u16 *)(p + 0x36A) = *(u16 *)(p + 0x36A) & 0xFFFC;
        }
    }
    *(f32 *)(p + 0x374) = save;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15123A54.s")
#endif
void func_15124770(struct108 *arg0, s32 arg1) {
    if (arg1 != 0) {
        arg0->unk244 = arg1;
        arg0->unk248 = &D_800CC2D0[arg1];
    } else {
        arg0->unk244 = 0;
        arg0->unk248 = NULL;
    }
}

#ifdef NON_MATCHING
/* P41: per-frame camera target ("at"). 0x2A4..0x2AC eases (rate 0x670, smoothed by func_150498A0 toward 0x674 = 1,
 * or 0.25 while the target object +0x9C / +0x95 is busy) toward the followed record's position (0x3D0 +0x14..+0x1C;
 * the midpoint with record 0x248 while 0x244 is set; y is not eased). 0x23C (first frame) snaps. Then an offset of
 * length 0x994 (eased toward 0x99C) along yaw 0x39C - pi/2, and at 0x2BC / 0x2C4 = the result (func_15125594). */
void func_151247C0(struct108 *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *o;
    u8 *r;
    u8 *q;
    s32 busy;
    f32 s;
    f32 c;

    if (*(u16 *)(p + 0x7F4) != 0) {
        return;
    }
    o = *(u8 **)(p + 0x3D4);
    busy = 0;
    if (o != NULL) {
        busy = (u8)(*(s32 *)(o + 0x9C) | o[0x95]);
    }
    *(f32 *)(p + 0x674) = busy ? 0.25f : 1.0f;
    if (p[0x23C] != 0) {
        *(f32 *)(p + 0x670) = *(f32 *)(p + 0x674);
        *(f32 *)(p + 0x678) = 0.0f;
    } else {
        func_150498A0((f32 *)(p + 0x670), *(f32 *)(p + 0x674), (f32 *)(p + 0x678), *(f32 *)(p + 0x3B4) * 0.25f, *(f32 *)(p + 0x3B8) * 0.25f, *(f32 *)(p + 0x7B4));
    }
    if (*(s16 *)(p + 0x244) != 0) {
        r = *(u8 **)(p + 0x3D0);
        q = *(u8 **)(p + 0x248);
        if (p[0x23C] != 0) {
            *(f32 *)(p + 0x2A4) = (*(f32 *)(r + 0x14) + *(f32 *)(q + 0x14)) * 0.5f;
            *(f32 *)(p + 0x2A8) = (*(f32 *)(r + 0x18) + *(f32 *)(q + 0x18)) * 0.5f;
            *(f32 *)(p + 0x2AC) = (*(f32 *)(r + 0x1C) + *(f32 *)(q + 0x1C)) * 0.5f;
        } else {
            *(f32 *)(p + 0x2A4) = *(f32 *)(p + 0x2A4) + ((*(f32 *)(r + 0x14) + *(f32 *)(q + 0x14)) * 0.5f - *(f32 *)(p + 0x2A4)) * *(f32 *)(p + 0x670);
            *(f32 *)(p + 0x2A8) = (*(f32 *)(r + 0x18) + *(f32 *)(q + 0x18)) * 0.5f;
            *(f32 *)(p + 0x2AC) = *(f32 *)(p + 0x2AC) + ((*(f32 *)(r + 0x1C) + *(f32 *)(q + 0x1C)) * 0.5f - *(f32 *)(p + 0x2AC)) * *(f32 *)(p + 0x670);
        }
    } else {
        r = *(u8 **)(p + 0x3D0);
        if (p[0x23C] != 0) {
            *(f32 *)(p + 0x2A4) = *(f32 *)(r + 0x14);
            *(f32 *)(p + 0x2AC) = *(f32 *)(r + 0x1C);
        } else {
            *(f32 *)(p + 0x2A4) = *(f32 *)(p + 0x2A4) + (*(f32 *)(r + 0x14) - *(f32 *)(p + 0x2A4)) * *(f32 *)(p + 0x670);
            *(f32 *)(p + 0x2AC) = *(f32 *)(p + 0x2AC) + (*(f32 *)(r + 0x1C) - *(f32 *)(p + 0x2AC)) * *(f32 *)(p + 0x670);
        }
        *(f32 *)(p + 0x2A8) = *(f32 *)(r + 0x18);
    }
    if (!(0.0f == *(f32 *)(p + 0x994)) || !(0.0f == *(f32 *)(p + 0x99C))) {
        if (p[0x23C] != 0) {
            *(f32 *)(p + 0x994) = *(f32 *)(p + 0x99C);
            *(f32 *)(p + 0x998) = 0.0f;
        } else {
            func_150498A0((f32 *)(p + 0x994), *(f32 *)(p + 0x99C), (f32 *)(p + 0x998), 4.0f, 6.0f, *(f32 *)(p + 0x7B4));
        }
        s = sinf(*(f32 *)(p + 0x39C) - 1.5707964f) * *(f32 *)(p + 0x994);
        c = cosf(*(f32 *)(p + 0x39C) - 1.5707964f) * *(f32 *)(p + 0x994);
        *(f32 *)(p + 0x2A4) = *(f32 *)(p + 0x2A4) + s;
        *(f32 *)(p + 0x2AC) = *(f32 *)(p + 0x2AC) + c;
    }
    *(f32 *)(p + 0x2BC) = *(f32 *)(p + 0x2A4);
    *(f32 *)(p + 0x2C4) = *(f32 *)(p + 0x2AC);
    func_15125594(arg0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_151247C0.s")
#endif
void func_15124AB4(struct108 *arg0) {
    arg0->unk668 = -sinf(arg0->unk398);
    arg0->unk66C = cosf(arg0->unk398);
    arg0->unk664 = sinf(arg0->unk39C) * arg0->unk66C;
    arg0->unk66C = cosf(arg0->unk39C) * arg0->unk66C;
}

void func_15124B18(struct108 *arg0) {
    s32 temp_t8;
    f32 *temp_v0;

    if (arg0->unk1B4 == 0) {
        arg0->unk1B4 = 4;
    }
    temp_t8 = arg0->unk2C & 0x80;
    if ((temp_t8 != 0) && ((*arg0->unk36C & 0x10) != 0)) {
        arg0->unk348 = 40.0f;
        arg0->unk34C = 40.0f;
        arg0->unk374 = 150.0f;
    } else if (temp_t8 != 0) {
        arg0->unk348 = (f32) (arg0->unk2FC - arg0->unk354);
    } else if ((temp_t8 != 0) && (arg0->unk3D0->unk102 == 0) && (D_800BE9F0 != 0x17)) {
        arg0->unk348 = 40.0f;
        arg0->unk34C = 40.0f;
        arg0->unk374 = 150.0f;
    } else if (arg0->unk3D0->unk102 != 0) {
        arg0->unk348 = 40.0f;
        arg0->unk34C = 40.0f;
        arg0->unk374 = 194.0f;
    } else {
        temp_v0 = D_800A34B0[arg0->unk1B4];
        arg0->unk374 = temp_v0[0]; //->unk0;
        arg0->unk348 = temp_v0[1]; //->unk4;
        arg0->unk34C = arg0->unk348;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15124C38.s")

void func_1512523C(struct108 *arg0) {
    f32 temp_f12;
    f32 temp_f2;
    f32 phi_f14;

    temp_f2 = arg0->unk2BC - arg0->unk2F8;
    temp_f12 = arg0->unk2C4 - arg0->unk300;
    temp_f12 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
    if (temp_f12 < 0.0f) {
        phi_f14 = -temp_f12;
    } else {
        phi_f14 = temp_f12;
    }
    temp_f2 = func_150484A0(arg0->unk2FC - arg0->unk2C0, phi_f14) * 57.295776f;
    arg0->unk388 = temp_f2;
    if (temp_f2 > 180.0f) {
        arg0->unk388 -= 360.0f;
    }
    arg0->unk388 = -arg0->unk388;
    arg0->unk388 -= arg0->unk3A8;
    arg0->unk388 += arg0->unk38C;
    arg0->unk398 = arg0->unk388 * 0.017453292f;
}

void func_15125330(struct108 *arg0) {
    struct17 tmp;

    tmp.unk0 = arg0->unk2BC - arg0->unk2F8;
    tmp.unk4 = 0.0f;
    tmp.unk8 = arg0->unk2C4 - arg0->unk300;

    arg0->unk37C = func_15048FC8(&tmp);
    arg0->unk39C = arg0->unk37C * 0.017453292f;
}

void func_15125394(struct108 *arg0) {
    s32 i = 0;

    while ((arg0->unk2C & (1 << i)) == 0) {
        i += 1;
    }
    arg0->unk0 = i;
}

s32 func_151253CC(struct108 *arg0) {
    f32 temp_f0;
    f32 temp_f2;

    if (arg0->unk2C & 0x40000) {
        arg0->unk84 &= ~0x4F;
        arg0->unk84 |= 0x2680;
        arg0->unk3A8 = 0.0f;
        arg0->unk5E8 = 0.0f;
        arg0->unk38C = 0.0f;
        func_15125330(arg0);
        func_1512523C(arg0);
        temp_f0 = arg0->unk37C;
        temp_f2 = 0.017453292f;
        arg0->unk380 = arg0->unk37C;
        arg0->unk3A0 = (f32) (temp_f0 * temp_f2);
        arg0->unk398 = (f32) (arg0->unk388 * temp_f2);
        func_15124AB4(arg0);
        if (arg0->unk3D4->unk197 != 0) {
            func_15127EB8(arg0);
        }
        func_1512C490(arg0);
        return 1;
    }
    return 0;
}

// note: no return value when 100 <= dist <= 300 (returns garbage in the original)
s32 func_15125490(struct108 *arg0) {
    struct127 *temp_v0 = arg0->unk3D0;
    s32 dist;

    if (temp_v0->in_water == 1) {
        dist = fabsf(temp_v0->y_position - temp_v0->unk118);
        if (dist < 100) {
            return 0;
        }
        if (dist > 300) {
            return 1;
        }
    } else {
        return 0;
    }
}

void func_151254F4(struct108 *arg0, s32 arg1) {
    arg0->unk3A0 = arg0->unk380 * 0.017453292f;
    arg0->unk398 = arg0->unk388 * 0.017453292f;
    func_15124AB4(arg0);
    func_151239CC(arg0, 1);
    arg0->unk3D4->unk198 = 0;
    arg0->unk73C = 0;
    arg0->unk3D0 = &D_800CC2D0[arg1];
    arg0->unk670 = 0.0f;
}
// NON-MATCHING: only the 0.017453292f load is scheduled after the prologue stores
// void func_151254F4(struct108 *arg0, s32 arg1) {
//     f32 tmp = 0.017453292f;
//
//     arg0->unk3A0 = arg0->unk380 * tmp;
//     arg0->unk398 = arg0->unk388 * tmp;
//     func_15124AB4(arg0);
//     func_151239CC(arg0, 1);
//     arg0->unk3D4->unk198 = 0;
//     arg0->unk73C = 0;
//     arg0->unk3D0 = &D_800CC2D0[arg1];
//     arg0->unk670 = 0.0f;
// }

void func_15125594(struct108 *arg0) {
    f32 temp_f0;
    f32 temp_f2;

    func_1512523C(arg0);
    func_15125330(arg0);

    temp_f0 = arg0->unk37C;
    temp_f2 = arg0->unk5E8;
    arg0->unk380 = temp_f0 - temp_f2;
    if (temp_f0 < temp_f2) {
        arg0->unk380 += 360.0f;
    }
    arg0->unk3A0 = arg0->unk380 * 0.017453292f;
    func_15124AB4(arg0);
}


void func_15125608(struct108 *arg0) {
    arg0->unk24C = 3.0f;
    arg0->unk250 = 2.5f;
}

// ???
void func_15125628(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_800DBFF4[i] != 0) {
            D_800DBFF4[i]--;
        }
    }
}

void func_15125690(struct108 *arg0, s32 arg1) {
    u8 *temp_v0 = &D_800DBFF4[arg0->unk23D];

    if (*temp_v0 < arg1) {
        *temp_v0 = arg1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_151256BC.s")
#ifdef NON_MATCHING
void func_15125924(struct108 *arg0) {
    s32 sp2C;
    s32 sp28;
    f32 temp_f0;
    s32 temp_v0_2;
    s32 var_a1;
    struct127 *temp_v0;
    u8 var_v1;

    temp_v0 = arg0->unk3D4;
    var_a1 = 0;
    var_v1 = 0;
    if (temp_v0 != NULL) {
        var_v1 = (*(u8 *)((u8 *)temp_v0 + 0x4E));
        var_a1 = (s32) temp_v0->z_position;
    }
    if (!(arg0->unk2C & 0x40) && ((arg0->unk84 & 0x4000) || (arg0->unk3D0->unk102 != 0))) {
        sp2C = (s32) var_v1;
        sp28 = var_a1;
        if ((func_15125490(arg0) != 0) && (var_v1 == 0) && (var_a1 == 0)) {
            if ((func_15123934(arg0, 0x80, 1, 1, 0xD) != 0) && (arg0->unk6C8 == 0)) {
                func_15124B18(arg0);
                arg0->unk5F0 |= 0x1000;
            }
        } else {
            if (arg0->unk2C & 0x80) {
                func_151239CC(arg0, 0xD);
                arg0->unk190 = 0.0f;
            }
            temp_v0_2 = arg0->unk5F0;
            if (temp_v0_2 & 0x1000) {
                temp_f0 = arg0->unk2FC - arg0->unk354;
                arg0->unk5F0 = temp_v0_2 & ~0x1000;
                (*(f32 *)((u8 *)arg0 + 0x344)) = temp_f0;
                arg0->unk348 = temp_f0;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15125924.s")
#endif
#ifdef NON_MATCHING
s32 func_1512DAD0(u8 *, s32, s32 *);
extern s32 D_800C3A20;
extern f32 D_800C3A34;
extern f32 D_800C3A38;
extern f32 D_800C3A3C;
extern f32 D_800C3A44;
extern s8 D_800C3A80;

void func_15125A6C(u8 *arg0) {
    f32 sp38;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 temp_f12;
    f32 temp_f12_2;

    if ((*(u8 *)((u8 *)arg0 + 0x23E)) == 0x2A) {
        sp38 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40));
        if ((*(s32 *)((u8 *)arg0 + 0x2C)) != 0x40000) {
            func_1512DAD0(arg0, 5, NULL);
            (*(u8 *)((u8 *)arg0 + 0x7E4)) = 1U;
        }
        *D_800DBFF4 = 3;
        (*(s32 *)((u8 *)(&D_800C3A20) + 0)) = 1;
        (*(s32 *)((u8 *)(&D_800C3A20) + 4)) = 0;
        temp_f12 = sp38 * 0.017453292f;
        sp28 = temp_f12;
        sp2C = sinf(temp_f12);
        temp_f12_2 = (sp38 - 90.0f) * 0.017453292f;
        sp24 = temp_f12_2;
        D_800C3A34 = (sinf(temp_f12_2) * 46.0f) + ((*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x14)) + (138.0f * sp2C));
        D_800C3A38 = (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x18)) + 96.0f;
        sp2C = cosf(temp_f12);
        D_800C3A3C = (cosf(temp_f12_2) * 46.0f) + ((*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x1C)) + (138.0f * sp2C));
        (*(f32 *)((u8 *)(&D_800C3A20) + 0x20)) = 0.0f;
        D_800C3A44 = -180.0f;
        (*(f32 *)((u8 *)(&D_800C3A20) + 8)) = 0.0f;
        (*(f32 *)((u8 *)(&D_800C3A20) + 0x28)) = (f32) (sp38 - 180.0f);
        D_800C3A80 = 0;
        func_1512DAD0(arg0, 7, &D_800C3A20);
        return;
    }
    if ((*(u8 *)((u8 *)arg0 + 0x7E4)) != 0) {
        func_1512DAD0(arg0, 6, NULL);
        (*(u8 *)((u8 *)arg0 + 0x7E4)) = 0U;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15125A6C.s")
#endif
// NON-MATCHING: miles away
// void func_15125A6C(struct108 *arg0) {
//     f32 pad3C;
//     f32 sp38;
//     f32 pad34;
//     f32 pad30;
//     f32 sp2C;
//     f32 sp28;
//     f32 sp24;
//
//     f32 temp_f12;
//     f32 temp_f12_2;
//
//     if (arg0->unk23E == 0x2A) {
//         sp38 = arg0->unk3D0->unk40;
//         if (arg0->unk2C != 0x40000) {
//             func_1512D560(arg0, 5, 0);
//             arg0->unk7E4 = 1U;
//         }
//         D_800DBFF4[0] = 3;
//         D_800C3600->unk0 = 1;
//         D_800C3600->unk4 = 0;
//         temp_f12 = sp38 * D_800A3550;
//         sp28 = temp_f12;
//         sp2C = sinf(temp_f12);
//         temp_f12_2 = (sp38 - 90.0f) * D_800A3554;
//         sp24 = temp_f12_2;
//         D_800C3600->unk14 = (sinf(temp_f12_2) * 46.0f) + (arg0->unk3D0->unk14 + (138.0f * sp2C));
//         D_800C3600->unk18 = arg0->unk3D0->unk18 + 96.0f;
//         sp2C = cosf(temp_f12);
//         D_800C3600->unk1C = (cosf(temp_f12_2) * 46.0f) + (arg0->unk3D0->unk1C + (138.0f * sp2C));
//         D_800C3600->unk20 = 0.0f;
//         D_800C3600->unk24 = -180.0f;
//         D_800C3600->unk8 = 0.0f;
//         D_800C3600->unk28 = sp38 - 180.0f;
//         D_800C3600->unk5C = 0;
//         func_1512D560(arg0, 7, D_800C3600);
//         return;
//     }
//
//     if (arg0->unk7E4 != 0) {
//         func_1512D560(arg0, 6, 0);
//         arg0->unk7E4 = 0U;
//     }
// }

#ifdef NON_MATCHING
void func_15125C40(u8 *arg0) {
    s32 temp_t8;
    s32 var_v0;
    s32 var_v0_2;
    u16 *temp_v0;
    u8 temp_a1;

    temp_a1 = (*(u8 *)((u8 *)arg0 + 0x23E));
    var_v0 = D_800D1940 == 0x42;
    if (var_v0 != 0) {
        var_v0 = temp_a1 == 0x1A;
    }
    var_v0_2 = temp_a1 == 3;
    if (var_v0_2 == 0) {
        var_v0_2 = temp_a1 == 0x1A;
        if (var_v0_2 == 0) {
            var_v0_2 = var_v0 != 0;
        }
    }
    temp_t8 = (*(s32 *)((u8 *)arg0 + 0x7CC)) - 1;
    (*(s32 *)((u8 *)arg0 + 0x7CC)) = temp_t8;
    if (var_v0_2 != 0) {
        if (temp_t8 == 0) {
            if (var_v0 != 0) {
                func_1509BFB0(3, 0x9000, 0x18, (s32) (*(f32 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0x40)), 0, 0xFA);
            } else if (temp_a1 == 0x1A) {
                func_1509BFB0(3, 0x9000, 0x18, 0, 0, 0xFA);
            }
            temp_v0 = (*(u16 **)((u8 *)arg0 + 0x36C));
            (*(s32 *)((u8 *)arg0 + 0x5F0)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x5F0)) | 2);
            *temp_v0 |= 0x10;
            (*(s32 *)((u8 *)arg0 + 0x7CC)) = 1;
            (*(u16 *)((u8 *)arg0 + 0x36A)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x36A)) | 0x10);
        }
    } else {
        if (((*(s32 *)((u8 *)arg0 + 0x5F0)) & 2) && (var_v0_2 == 0)) {
            func_1509BFB0(1, 0x9000, 0x10, 0);
            func_1509BFB0(1, 0x9000, 0xF, 0);
            (*(s32 *)((u8 *)arg0 + 0x5F0)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x5F0)) & ~2);
        }
        (*(s32 *)((u8 *)arg0 + 0x7CC)) = 2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15125C40.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15125DB4.s")

void func_15126138(struct108 *arg0) {
    struct127 *temp_v0_2;
    struct108 *phi_a0;

    func_151247C0(arg0);

    temp_v0_2 = arg0->unk3D0;

    if (((temp_v0_2->x_position != arg0->unk2B0) ||
         (temp_v0_2->y_position != arg0->unk2B4) ||
         (temp_v0_2->z_position != arg0->unk2B8)) && ((arg0->unk2C & ~0x100) != 0)) {
        arg0->unk298 = 1;
        arg0->unk7E6 = 60;
        arg0->unk8ED = 0;
    } else {
        arg0->unk298 = 0;
    }

    if (arg0->unk84 & 0x200000) {
        temp_v0_2 = arg0->unk3D0; // again?!
        if (temp_v0_2->interaction_state != 0x1E) {
            if (temp_v0_2->unk102 == 0) {
                if ((*(arg0->unk36C) & 0xF) != 0) {
                    if ((arg0->unk2C & 0x40) == 0) {
                        func_151220D0(arg0);
                    }
                }
            }
        }
    }
    func_15124C38(arg0, 0);
}


typedef struct { f32 x, y, z; } V3_2623C;

void func_1512623C(u8 *arg0, u8 *arg1, s32 arg2, f32 *arg3, f32 *arg4, f32 *arg5, s32 arg6) {
    s32 ret;
    V3_2623C in;
    V3_2623C out;
    s32 idx;
    u8 *m;

    ret = 1;
    if (*(u8 **)(arg0 + 0x1D4) != NULL) {
        ret = 0;
        if (arg6 != 0) {
            idx = 3;
            in.x = 0.0f;
            in.z = 0.0f;
            in.y = 20.0f;
        } else if (arg2 == 0x1B) {
            idx = 4;
            in.y = 116.0f;
            in.x = 0.0f;
            in.z = 130.0f;
        } else {
            ret = 1;
        }
        if (ret == 0) {
            m = *(u8 **)(arg0 + 0x1D4); m += idx << 6;
            func_15143134(&in, &out, m);
            *arg3 = out.x;
            *arg4 = out.y;
            *arg5 = out.z;
        }
    }
    if (ret != 0) {
        *arg3 = *(f32 *)(arg0 + 0x14);
        *arg4 = *(s16 *)(arg1 + 0x114) * 0.75f + *(f32 *)(arg0 + 0x18);
        *arg5 = *(f32 *)(arg0 + 0x1C);
    }
}
// ooh mama
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15126378.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15127520.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_151277B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_151279A0.s")

#ifdef NON_MATCHING
void func_151CA484(u8 *arg0);
void func_1510B8AC(s32 arg0, f32 arg1, f32 arg2, f32 arg3);

void func_15127EB8(struct108 *arg0) {
    struct127 *temp_v1;
    struct127 *var_v0;
    u8 temp_a0;

    func_151239CC(arg0, 1);
    arg0->unk3D4->unk197 = 0;
    func_151CA484(arg0);
    arg0->unk19C = 0.0f;
    arg0->unk1A0 = 0.0f;
    arg0->unk1A4 = 0.0f;
    arg0->unk1A8 = 0.0f;
    func_1510B8AC(arg0->unk23D, 0.0f, 0.0f, 1.0f);
    (*(f32 *)((u8 *)((D_800BE628 + (arg0->unk23D * 0x180))) + 0x84)) = 1.0f;
    func_150627D4(arg0->unk3D0);
    D_800DBFF4[arg0->unk23D] = 2;
    temp_v1 = arg0->unk3D0;
    temp_a0 = temp_v1->unk65;
    var_v0 = temp_v1;
    if (temp_a0 != 0) {
        var_v0 = &(*(struct127 *)((u8 *)(&D_800CC2D0[temp_a0]) + -0x32C));
    }
    var_v0->unk2FC &= ~(1 << arg0->unk23D);
    var_v0->unk74 &= ~(1 << arg0->unk23D);
    arg0->unk23C = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15127EB8.s")
#endif
// NON-MATCHING: not too far away
// void func_15127EB8(struct108 *arg0) {
//     struct127 *phi_v0;
//
//     func_151239CC(arg0, 1);
//     arg0->unk3D4->unk197 = (u8)0;
//     func_151C9ED4(arg0);
//     arg0->unk19C = 0.0f;
//     arg0->unk1A0 = 0.0f;
//     arg0->unk1A4 = 0.0f;
//     arg0->unk1A8 = 0.0f;
//     func_1510B32C(arg0->unk23D, 0.0f, 0.0f, 1.0f);
//     D_800BE628[arg0->unk23D].unk84 = 1.0f;
//     func_150627D4(arg0->unk3D0);
//     D_800DBFF4[arg0->unk23D] = (u8)2;
//
//     phi_v0 = &arg0->unk3D0;
//     if (phi_v0->unk65 != 0) {
//         phi_v0 = &D_800CC2D0[phi_v0->unk65];
//     }
//
//     phi_v0->unk2FC &= ~(1 << arg0->unk23D);
//     phi_v0->unk74 &= ~(1 << arg0->unk23D);
//     arg0->unk23C = (u8)1;
// }

void func_15127FEC(struct108 *arg0, s32 arg1, s32 arg2) {
    arg0->unk7F4 = 1;
    arg0->unk7F8 = arg0->unk2A4;
    arg0->unk7FC = arg0->unk2A8;
    arg0->unk800 = *(f32*)&arg0->unk2AC;
    func_1512A390();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_15128030.s")
#ifdef NON_MATCHING
/* P41: camera mode dispatcher on controller +0x2C (1 / 0x800: func_15122EF0, the follow camera). */
void func_151283B8(struct108 *arg0) {
    switch (*(s32 *)((u8 *)arg0 + 0x2C)) {
        case 1:
        case 0x800:
            func_15122EF0(arg0);
            break;
        case 2:
            func_151220D0(arg0);
            break;
        case 8:
            func_151221F0(arg0, 0);
            break;
        case 0x40:
            func_15129EA4(arg0);
            break;
        case 0x80:
            func_151229B0(arg0);
            break;
        case 0x100:
            func_151206C8(arg0);
            break;
        case 0x400:
            func_151226E0(arg0);
            break;
        case 0x800000:
            func_1512DEA4(arg0);
            break;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_14FF90/func_151283B8.s")
#endif
void func_151284C4(struct108 *arg0) {
    func_1512C490(arg0);
    arg0->unk2B0 = arg0->unk3D0->x_position;
    arg0->unk2B4 = arg0->unk3D0->y_position;
    arg0->unk2B8 = arg0->unk3D0->z_position;
    if (arg0->unk23C != 0) {
        arg0->unk23C--;
    }
    if ((arg0->unk84 & 8) && ((s16)arg0->unk5FE <= 0)) {
        arg0->unk5FE = 50;
        func_15128774(arg0, arg0->unk3D0);
    }
}
#ifdef NON_MATCHING
void func_15121F40(struct108 *);
#else
s32 func_15121F40(struct108 *);
#endif
s32 func_151236D0(struct108 *);
s32 func_151256BC(struct108 *);
s32 func_15126378(struct108 *);
s32 func_15128030(struct108 *);
s32 func_1512A8D0(struct108 *);
#ifdef NON_MATCHING
void func_1512EA20(struct108 *);
#else
s32 func_1512EA20(struct108 *);
#endif

s32 func_15128540(struct108 *arg0) {
    if (func_151253CC(arg0) != 0) {
        return 1;
    }
    if (func_15128030(arg0) != 0) {
        return 0;
    }
    if (arg0->unk2C & 0x80000) {
        func_1512A8D0(arg0);
        *(vertex *)&arg0->unk2BC = *(vertex *)&arg0->unk2A4;
        func_151256BC(arg0);
        func_151236D0(arg0);
        func_151284C4(arg0);
        return 1;
    }
    if (arg0->unk2C & 0x100000) {
        func_1512EA20(arg0);
        func_151236D0(arg0);
        func_151284C4(arg0);
        return 1;
    }
    if (arg0->unk2C & 0x200000) {
        func_15121F40(arg0);
        func_151236D0(arg0);
        func_151284C4(arg0);
        return 1;
    }
    if (arg0->unk2C & 0x400000) {
        func_1512D380((s32) arg0);
        func_151236D0(arg0);
        func_151284C4(arg0);
        return 1;
    }
    if (func_15126378(arg0) != 0) {
        func_151284C4(arg0);
        return 1;
    }
    return 0;
}

void func_15128680(struct108 *arg0) {
}

void func_1512868C(struct108 *arg0) {
    struct127 *temp_v1_2;
    u8 idx;
    s32 i;

    for (i = 0; i < 21; i++)
    {
        arg0->unk20C[i] = 0;
    }

    arg0->unk2C = 1;
    arg0->unkDC = 0;
    arg0->unk134 = 1;
    arg0->unk84 = 14;
    arg0->unk1B4 = 3;
    func_15124B18(arg0);
    idx = arg0->unk23D;
    arg0->unk3D0 = temp_v1_2 = &D_800CC2D0[idx];
    arg0->unk368 = arg0->unk3CC = idx;
    arg0->unk3D4 = temp_v1_2->unk31C;
    arg0->unk190 = 0.0f;
    arg0->unk198 = 0.0f;
    arg0->unk18C = 0.0f;
    arg0->unk194 = 0.0f;
    arg0->unk674 = 1.0f;
    arg0->unk3D4->unk198 = 0;
    arg0->unk73C = 0;
}

void func_15128774(struct108 *arg0, struct127 *arg1) {
    arg0->unk35C = arg1->unk180;
    arg0->unk304 = arg0->unk2F8 = arg1->x_position;
    arg0->unk308 = arg0->unk2FC = arg1->y_position;
    arg0->unk30C = arg0->unk300 = arg1->z_position;
    arg0->unk37C = arg0->unk3D0->unk40 - 180.0f;
    arg0->unk3D4->unk18C = 999.0f;
    arg0->unk23C = 1;
}
