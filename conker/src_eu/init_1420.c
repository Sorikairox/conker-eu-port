#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/init_1420/func_10001420.s")
// NOT MATCHING: JUSTREG: uses v0 registers not a1 registers
// void func_10001420(void) {
//     s32 *tmp = &D_80043B40;
//     s32 cnt = 4064;
//
//     do {
//         *tmp++ = 0;
//     }
//     while ((s32)tmp < (u32)&D_80043B40 + cnt);
// }

void func_10001444(void) {
    u32 saveMask = __osDisableInt();
    func_100061F8(2, 31);
    func_10001420();
    func_10005BE0();
    osInvalICache(&D_1002AAD0, 0x80400000 - (u32)&D_1002AAD0);
    __osRestoreInt(saveMask);
}

void func_100014A0(void) {
    osStopThread(&D_80031AE0);
}

void func_100014C4(s32 arg0) {
    u32 saveMask = __osDisableInt();
    func_100061F8(2, 31);

    if (0) {};

    if (D_8003BE74) {
        func_10004074(D_8003BE74 | 0x80000000);
    }
    if (D_8003BE70) {
        func_10004074(D_8003BE70 | 0x80000000);
    }
    func_10005B04(arg0);
    func_10001420();
    func_10005BE0();
    __osRestoreInt(saveMask);
}

// this is a loopy mutha. contains delay slot so insert nop after .L1000183C
#pragma GLOBAL_ASM("asm/nonmatchings/init_1420/func_10001550.s")

s16 func_100019F0(s16 *arg0, struct05 *arg1) {
    s16 temp_v1 = (arg1->unk0 & 0x7FF0) >> 4;

    if (temp_v1 == 0x7FF) {
        s32 ret;
        *arg0 = 0;
        if ((arg1->unk0 & 0xF) || (arg1->unk2) || (arg1->unk4) || (arg1->unk6)) {
            ret = 2;
        }
        else {
            ret = 1;
        }
        return ret;
    }

    if (temp_v1 > 0) {
        arg1->unk0 = (arg1->unk0 & 0x800F) | 0x3FF0;
        *arg0 = temp_v1 - 0x3FE; // 1022
        return -1;
    }

    if (temp_v1 < 0) {
      return 2;
    }

    *arg0 = 0;
    return 0;
}

typedef struct {
    union {
        long long ll;
        long double ld;
    } v;
    unsigned char *s;
    int n0;
    int nz0;
    int n1;
    int nz1;
    int n2;
    int nz2;
    int prec;
    int width;
    size_t nchar;
    unsigned int flags;
    unsigned char qual;
} _Pft;
#define FLAGS_ZERO 16
#define FLAGS_MINUS 4
#define FLAGS_HASH 8
extern u8 D_8002C2C0[]; // "0"
void *memcpy(void *, const void *, size_t);

// libultra libc xldtob.c _Genld (same source as debugger func_16002DE4)
void func_10001AA8(_Pft *px, u8 code, u8 *p, s16 nsig, s16 xexp) {
    const u8 point = '.';

    if (nsig <= 0) {
        p = D_8002C2C0;
        nsig = 1;
    }
    if (code == 'f' || ((code == 'g' || code == 'G') && (-4 <= xexp) && (xexp < px->prec))) {
        xexp++;
        if (code != 'f') {
            if (((px->flags & FLAGS_HASH) == 0) && (nsig < px->prec)) {
                px->prec = nsig;
            }
            if ((px->prec -= xexp) < 0) {
                px->prec = 0;
            }
        }
        if (xexp <= 0) {
            px->s[px->n1++] = '0';
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = point;
            }
            if (px->prec < -xexp) {
                xexp = -px->prec;
            }
            px->nz1 = -xexp;
            px->prec += xexp;
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            memcpy(&px->s[px->n1], p, px->n2 = nsig);
            px->nz2 = px->prec - nsig;
        } else if (nsig < xexp) {
            memcpy(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = xexp - nsig;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1] = point;
                ++px->n2;
            }
            px->nz2 = px->prec;
        } else {
            memcpy(&px->s[px->n1], p, xexp);
            px->n1 += xexp;
            nsig -= xexp;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = point;
            }
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            memcpy(&px->s[px->n1], p + xexp, nsig);
            px->n1 += nsig;
            px->nz1 = px->prec - nsig;
        }
    } else {
        if (code == 'g' || code == 'G') {
            if (nsig < px->prec) {
                px->prec = nsig;
            }
            if (--px->prec < 0) {
                px->prec = 0;
            }
            code = (code == 'g') ? 'e' : 'E';
        }
        px->s[px->n1++] = *p++;
        if (0 < px->prec || px->flags & FLAGS_HASH) {
            px->s[px->n1++] = point;
        }
        if (0 < px->prec) {
            if (px->prec < --nsig) {
                nsig = px->prec;
            }
            memcpy(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = px->prec - nsig;
        }
        p = (u8 *)&px->s[px->n1];
        *p++ = code;
        if (0 <= xexp) {
            *p++ = '+';
        } else {
            *p++ = '-';
            xexp = -xexp;
        }
        if (100 <= xexp) {
            if (1000 <= xexp) {
                *p++ = (xexp / 1000) + '0', xexp %= 1000;
            }
            *p++ = (xexp / 100) + '0', xexp %= 100;
        }
        *p++ = (xexp / 10) + '0', xexp %= 10;
        *p++ = xexp + '0';
        px->n2 = (u32)p - ((u32)px->s + px->n1);
    }
    if ((px->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        s32 n = px->n0 + px->n1 + px->nz1 + px->n2 + px->nz2;

        if (n < px->width) {
            px->nz0 = px->width - n;
        }
    }
}
// some kind of memory allocation?
// NON-MATCHING: 50% of the way there...
// void func_10001AA8(struct246 *arg0, u8 arg1, u8 *arg2, s16 arg3, s16 arg4) {
//     s32 temp_v0_3;
//     s32 temp_v1_2;
//     s32 phi_v0;
//     u8 *phi_s1;
//     s32 phi_v1;
//     s32 required;
//     u8 *mem_array;
//
//     if (arg3 <= 0) {
//         arg2 = &D_8002BF70;
//         arg3 = 1;
//     }
//
//     if (arg1 != 0x66) {
//         if ((arg1 == 0x67) || (arg1 == 0x47)) {
//             if ((arg4 >= -4) && (arg4 < arg0->unk24)) {
// block_7:
//                 arg4 = arg4 + 1;
//                 if (arg1 != 0x66) {
//                     phi_v0 = arg0->unk24;
//                     if (((arg0->unk30 & 8) == 0) && (arg3 < arg0->unk24) ){
//                         arg0->unk24 = arg3;
//                         phi_v0 = arg3;
//                     }
//                     arg0->unk24 = phi_v0 - arg4;
//                     if (arg0->unk24 < 0) {
//                         arg0->unk24 = 0;
//                     }
//                 }
//                 if (arg4 <= 0) {
//                     *(arg0->unk8 + arg0->unk14) = 0x30;
//                     arg0->unk14 += 1;
//                     if ((arg0->unk24 > 0) || ((arg0->unk30 & 8) != 0)) {
//                         *(arg0->unk8 + arg0->unk14) = 0x2E;
//                         arg0->unk14 += 1;
//                     }
//                     phi_v1 = -arg4;
//                     if (arg0->unk24 < phi_v1) {
//                         phi_v1 = arg0->unk24;
//                         arg4 = -arg0->unk24;
//                     }
//                     arg0->unk18 = phi_v1;
//                     arg0->unk24 += arg4;
//                     if (arg0->unk24 < arg3) {
//                         arg3 = (s16)arg0->unk24;
//                     }
//                     arg0->unk1C = arg3;
//                     memcpy(arg0->unk8 + arg0->unk14, arg2, arg3);
//                     arg0->unk20 = arg0->unk24 - arg3;
//                 } else if (arg3 < (s32) arg4) {
//                     memcpy(arg0->unk8 + arg0->unk14, arg2, arg3);
//                     arg0->unk14 = (s32) (arg0->unk14 + arg3);
//                     arg0->unk18 = (s32) (arg4 - arg3);
//                     if ((arg0->unk24 > 0) || ((arg0->unk30 & 8) != 0)) {
//                         *(arg0->unk8 + arg0->unk14) = (u8)0x2E;
//                         arg0->unk1C = (s32) (arg0->unk1C + 1);
//                     }
//                     arg0->unk20 = arg0->unk24;
//                 } else {
//                     memcpy(arg0->unk8 + arg0->unk14, arg2, arg4);
//                     arg0->unk14 = (s32) (arg0->unk14 + arg4);
//                     if ((arg0->unk24 > 0) || ((arg0->unk30 & 8) != 0)) {
//                         *(arg0->unk8 + arg0->unk14) = (u8)0x2E;
//                         arg0->unk14 = (s32) (arg0->unk14 + 1);
//                     }
//                     arg3 = (s16) arg3 - arg4;
//                     if (arg0->unk24 < (s32) arg3) {
//                         arg3 = (s16) arg0->unk24;
//                     }
//                     memcpy(arg0->unk8 + arg0->unk14, arg4 + arg2, arg3);
//                     arg0->unk14 = (s32) (arg0->unk14 + arg3);
//                     arg0->unk18 = (s32) (arg0->unk24 - arg3);
//                 }
//             } else {
// block_33:
//                 if ((arg1 == 0x67) || (arg1 == 0x47)) {
//                     phi_v0 = arg0->unk24;
//                     if (arg3 < phi_v0) {
//                         arg0->unk24 = arg3;
//                         phi_v0 = arg3;
//                     }
//                     arg0->unk24 = phi_v0 - 1;
//                     if (arg0->unk24 < 0) {
//                         arg0->unk24 = 0;
//                     }
//                     if (arg1 == 0x67) {
//                         arg1 = 0x65U;
//                     } else {
//                         arg1 = 0x45U;
//                     }
//                 }
//                 *(arg0->unk8 + arg0->unk14) = *arg2;
//                 arg0->unk14 += 1;
//                 if ((arg0->unk24 > 0) || ((arg0->unk30 & 8) != 0)) {
//                     *(arg0->unk8 + arg0->unk14) = 0x2E;
//                     arg0->unk14 += 1;
//                 }
//                 if (arg0->unk24 > 0) {
//                     arg3 = arg3 - 1;
//                     if (arg0->unk24 < arg3) {
//                         arg3 = (s16) arg0->unk24; // (s16)
//                     }
//                     memcpy(arg0->unk8 + arg0->unk14, arg2 + 1, arg3);
//                     arg0->unk14 += arg3;
//                     arg0->unk18 = (arg0->unk24 - arg3);
//                 }
//                 mem_array = arg0->unk8 + arg0->unk14;
//                 *(mem_array) = arg1;
//                 mem_array += 1;
//                 if (arg4 >= 0) {
//                     mem_array[0] = 43;
//                     required = arg4;
//                     mem_array += 1;
//                 } else {
//                     mem_array[0] = 45;
//                     required = -arg4;
//                     mem_array += 1;
//                 }
//                 if (required >= 100) {
//                     if (required >= 1000) {
//                         *mem_array = (s8) ((required / 1000) + 48);
//                         required = required % 1000;
//                         mem_array += 1;
//                     }
//                     *mem_array = (s8) ((required / 100) + 48);
//                     required = (required % 100);
//                     mem_array += 1;
//                 }
//                 *(mem_array + 0) = (required / 10) + 48;
//                 *(mem_array + 1) = (required % 10) + 48;
//                 arg0->unk1C = (((mem_array + 2) - arg0->unk8) - arg0->unk14);
//             }
//         } else {
//             goto block_33;
//         }
//     } else {
//         goto block_7;
//     }
//
//     if ((arg0->unk30 & 0x14) == 0x10) {
//         temp_v1_2 = arg0->unk28;
//         temp_v0_3 = arg0->unkC + arg0->unk14 + arg0->unk18 + arg0->unk1C + arg0->unk20;
//         if (temp_v0_3 < temp_v1_2) {
//             arg0->unk10 = temp_v1_2 - temp_v0_3;
//         }
//     }
// }
