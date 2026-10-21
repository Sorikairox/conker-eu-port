#include <ultra64.h>

#include "functions.h"
#include "variables.h"


s32 allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return func_10003C6C(arg0, arg1, arg2, 0, arg3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_3C40/func_10003C6C.s")
#ifdef NON_MATCHING
extern struct54 *D_8003841C;

void func_10004074(s32 arg0) {
    struct54 *sp2C;
    s32 sp20;
    u32 sp1C;
    struct54 *sp18;
    s32 temp_t8;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_a3;
    struct54 *temp_a0;
    struct54 *temp_a0_2;
    struct54 *temp_t3;
    struct54 *temp_t7;
    struct54 *temp_v1;
    struct54 *var_a1;
    struct54 *var_v1;
    u32 temp_v0;
    u32 temp_v0_3;

    temp_v1 = arg0 - 0xC;
    if (arg0 != 0) {
        sp18 = temp_v1;
        sp2C = temp_v1;
        sp20 = 0;
        sp1C = osSetIntMask(1U);
        var_a1 = sp2C;
        temp_a0 = sp18->unk4;
        var_a3 = sp20;
        (*(s8 *)((u8 *)sp18 + 8)) = 0;
        if (temp_a0 != NULL) {
            temp_v0 = temp_a0->unk8;
            if ((temp_v0 >> 0x18) == 0) {
                temp_t7 = sp18->unk0;
                var_a1 = temp_a0;
                var_a3 = 1;
                temp_a0->unk0 = temp_t7;
                temp_a0->unk8 = temp_v0 + sp18->unk8 + 0xC;
                if (temp_t7 != NULL) {
                    temp_t7->unk4 = temp_a0;
                }
            }
        }
        temp_a0_2 = var_a1->unk0;
        if ((temp_a0_2 != NULL) && (((u32) temp_a0_2->unk8 >> 0x18) == 0)) {
            temp_t3 = temp_a0_2->unk0;
            var_a1->unk0 = temp_t3;
            var_a3 = 1;
            var_a1->unk8 = var_a1->unk8 + temp_a0_2->unk8 + 0xC;
            if (temp_t3 != NULL) {
                temp_t3->unk4 = var_a1;
            }
            temp_t8 = temp_a0_2->unkC;
            var_a1->unkC = temp_t8;
            if (temp_t8 != 0) {
                (*(struct54 **)((u8 *)temp_t8 + 0x10)) = var_a1;
            }
            temp_v1_2 = temp_a0_2->unk10;
            if (temp_v1_2 == 0) {
                D_800380B8 = var_a1;
                var_a1->unk10 = 0;
            } else if (temp_v1_2 != (s32)var_a1) {
                var_a1->unk10 = temp_v1_2;
                if (temp_v1_2 != 0) {
                    (*(struct54 **)((u8 *)temp_v1_2 + 0xC)) = var_a1;
                }
            }
        }
        if (var_a3 == 0) {
            var_v1 = D_800380B8;
            if (var_v1 == NULL) {
                var_a1->unkC = 0;
                var_a1->unk10 = 0;
                D_800380B8 = var_a1;
            } else if ((u32) var_a1 < (u32) var_v1) {
                var_a1->unkC = (s32) var_v1;
                var_a1->unk10 = 0;
                var_v1->unk10 = (s32) var_a1;
                D_800380B8 = var_a1;
            } else {
loop_21:
                temp_v0_2 = var_v1->unkC;
                if (temp_v0_2 == 0) {
                    var_a1->unkC = 0;
                    var_a1->unk10 = (s32) var_v1;
                    var_v1->unkC = (s32) var_a1;
                } else if ((u32) var_a1 < (u32) temp_v0_2) {
                    var_a1->unkC = temp_v0_2;
                    var_a1->unk10 = (s32) var_v1;
                    (*(struct54 **)((u8 *)temp_v0_2 + 0x10)) = var_a1;
                    var_v1->unkC = (s32) var_a1;
                } else {
                    var_v1 = (struct54 *) temp_v0_2;
                    goto loop_21;
                }
            }
        }
        if (var_a1->unkC == 0) {
            D_8003841C = var_a1;
        }
        temp_v0_3 = var_a1->unk8;
        if ((u32) D_8002AC30 < temp_v0_3) {
            D_8002AC30 = (s32) temp_v0_3;
            D_800380B0 = var_a1;
        }
        osSetIntMask(sp1C);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_3C40/func_10004074.s")
#endif
void func_10004250(void) {
    s32 temp_v0;
    u32 temp_v1;
    OSIntMask mask;
    struct54 *phi_s0;

    mask = osSetIntMask(1);

    if (phi_s0 = D_800380B4) {
        do {
            temp_v1 = phi_s0->unk8;
            temp_v0 = temp_v1 >> 0x18;
            if (2 == temp_v0) {
                func_10004074(&phi_s0->unkC);
            } else if ((temp_v0 == 3) || (temp_v0 == 4)) {
                phi_s0->unk8 = ((temp_v0 - 1) << 0x18) | (temp_v1 & 0xFFFFFF);
            }
        } while(phi_s0 = phi_s0->unk0);
    }
    osSetIntMask(mask);
}

void func_10004308(void) {
    u32 temp_t6;
    struct54 *phi_s0;
    OSIntMask mask;

    mask = osSetIntMask(1);
    phi_s0 = D_800380B4;
    func_15042D50();

    if (phi_s0) {
        do {
            temp_t6 = phi_s0->unk8 >> 24;
            if (temp_t6 == 1 || temp_t6 == 2 || temp_t6 == 3 || temp_t6 == 4) {
                func_10004074(&phi_s0->unkC);
            }
        }
        while (phi_s0 = phi_s0->unk0);
    }
    osSetIntMask(mask);
}

typedef struct { s32 a; s32 b; u32 c; } Hdr43B4; /* 12-byte header before the block */

void func_100043B4(s32 *arg0, u32 arg1) {
    Hdr43B4 *h = (Hdr43B4 *)arg0 - 1;
    u32 mask = osSetIntMask(1);

    h->c = (h->c & 0xFFFFFF) | (arg1 << 24);
    osSetIntMask(mask);
}
// NON-MATCHING: missing an addiu
// void func_100043B4(s32 *arg0, u32 arg1) {
//     OSIntMask mask = osSetIntMask(1);
//     *(arg0 - 1) = (arg1 << 24) | *(arg0 - 1) & 0xFFFFFF;
//     osSetIntMask(mask);
// }

void func_1000440C(void) {
    struct54 *foo;
    struct54 *last_good_foo;
    s32 tmp0;

    for (foo = D_800380B8, tmp0 = NULL; foo != NULL; foo = (struct54 *)foo->unkC) {
        if (tmp0 < (s32) foo->unk8) {
            tmp0 = foo->unk8;
            last_good_foo = foo;
        }
    }

    D_800380B0 = last_good_foo;
    D_8002AC30 = tmp0;
}
