#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F500.s")

void func_1519F678(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    func_15147E64(arg0);
}

void func_1519F6D8(u8 *arg0) {
    u8 **temp_v0 = *(u8 ***)(arg0 + 0x98);
    s32 *temp_a0;

    if (*temp_v0 != NULL) {
        temp_a0 = (s32 *)(*temp_v0 + 0x58);
        if (*(s32 *)(arg0 + 0x20) == 6) {
            temp_a0[0] = 0;
        }
        if (*(s32 *)(arg0 + 0x20) == 7) {
            temp_a0[2] = 0;
        }
    }
    func_15147E98(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F738.s")

s32 func_1519F738(u8 *, u8);
void func_1519F928(u8 *arg0) {
    s32 *p = (s32 *)(arg0 + 0x58);
    p[0] = func_1519F738(arg0, 6);
    p[1] = 0;
    p[2] = func_1519F738(arg0, 7);
    p[3] = 0;
}

void func_151A0E98(u8 *);
void func_1519F9FC(u8 *);

void func_1519F970(u8 *arg0) {
    u8 *v = arg0 + 0x58;

    if (*(s32 *)(arg0 + 0x58) != 0) {
        func_1519F9FC(*(u8 **)(arg0 + 0x58));
    }
    if (*(u8 **)(v + 8) != NULL) {
        func_1519F9FC(*(u8 **)(v + 8));
    }
    if (*(u8 **)(v + 4) != NULL) {
        func_151A0E98(*(u8 **)(v + 4));
        func_1516972C(*(struct102 **)(v + 4));
    }
    if (*(u8 **)(v + 0xC) != NULL) {
        func_151A0E98(*(u8 **)(v + 0xC));
        func_1516972C(*(struct102 **)(v + 0xC));
    }
}

#ifdef NON_MATCHING
void func_1519F9FC(u8 *arg0) {
    s32 temp_v1;
    u8 *temp_a1;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x98));
    temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0));
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 + 0x58;
        if ((*(s32 *)((u8 *)arg0 + 0x20)) == 6) {
            (*(s32 *)((u8 *)temp_a1 + 0)) = 0;
        }
        if ((*(s32 *)((u8 *)arg0 + 0x20)) == 7) {
            (*(s32 *)((u8 *)temp_a1 + 8)) = 0;
        }
        (*(s32 *)((u8 *)temp_v0 + 0)) = 0;
    }
    (*(s8 *)((u8 *)arg0 + 0x30)) = 0;
    (*(u16 *)((u8 *)arg0 + 0x1E)) = (u16) ((*(u16 *)((u8 *)arg0 + 0x1E)) & 0xFFFD);
    (*(u8 *)((u8 *)temp_v0 + 4)) = (u8) ((*(u8 *)((u8 *)temp_v0 + 4)) | 1);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519F9FC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519FA60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_1519FD60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A03DC.s")

#ifdef NON_MATCHING
void func_151A0DBC(u8 *arg0) {
    u8 *sp28;
    u8 sp23;
    u8 *sp18;
    s32 temp_v0_2;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a1;
    u8 *temp_a2;
    u8 *temp_t0;
    u8 *temp_v0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x28));
    var_v1 = 0;
    temp_a2 = arg0 + 0x28;
    temp_a1 = (*(u8 **)((u8 *)temp_v0 + 0x18));
    temp_t0 = temp_v0 + 0x58;
    if ((*(s32 *)((u8 *)temp_a1 + 0)) == 0) {
        var_v1 = 1;
    }
    temp_a0 = (*(u8 **)((u8 *)temp_a2 + 0));
    if ((*(u8 *)((u8 *)temp_a0 + 0x1C)) != (*(u8 *)((u8 *)temp_a1 + 0x3B))) {
        var_v1 = 1;
    }
    if ((var_v1 == 0) && ((*(s32 *)((u8 *)temp_a1 + 0x1D4)) != 0)) {
        sp23 = 1;
        sp28 = temp_t0;
        sp18 = temp_a2;
        temp_v0_2 = func_1519F738(temp_a0, (*(u8 *)((u8 *)temp_a2 + 4)));
        var_v1 = 1;
        if ((*(u8 *)((u8 *)temp_a2 + 4)) == 6) {
            (*(s32 *)((u8 *)temp_t0 + 0)) = temp_v0_2;
        } else {
            (*(s32 *)((u8 *)temp_t0 + 8)) = temp_v0_2;
        }
    }
    if (var_v1 != 0) {
        func_151A0E98(arg0);
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        (*(u8 *)((u8 *)arg0 + 0xD)) = (u8) ((*(u8 *)((u8 *)arg0 + 0xD)) | 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1CCD10/func_151A0DBC.s")
#endif
void func_151A0E98(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x28) + 0x58;
    if (arg0[0x2C] == 6) {
        *(s32 *)(p + 4) = 0;
    } else {
        *(s32 *)(p + 0xC) = 0;
    }
}

void func_151A0EC0(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 temp_t6;
    unsigned int new_var; // fakematch: field temp pins t7/v1 register choice
    unsigned int new_var2; // fakematch: same for the second branch
    u8 **temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_t6 = arg2;
    temp_v1 = *(u8 ***)(arg0 + 0x98);
    if (temp_t6 == 0xA) {
        temp_v0 = *temp_v1;
        if ((temp_v0 != NULL) && (((new_var = *(s32 *)(temp_v0 + 0x18)) == *(s32 *)(arg1 + 0)) || (*(u8 *)(temp_v0 + 0x1C) == *(u8 *)(arg1 + 4)))) {
            func_1519F9FC(arg0);
        }
    } else if (temp_t6 == 0) {
        temp_v0_2 = *temp_v1;
        if ((temp_v0_2 != NULL) && ((new_var2 = *(s32 *)(temp_v0_2 + 0x18)) == *(s32 *)(arg1 + 0))) {
            func_1519F9FC(arg0);
        }
    }
}

void func_151A0F5C(u8 *arg0, u8 *arg1, u8 arg2) {
    u8 *v = *(u8 **)(*(u8 **)(arg0 + 0x28) + 0x18);
    if (arg2 == 0) {
        if (((s32)v == *(s32 *)arg1) || (v[0x3B] == arg1[4])) {
            func_151A0E98(arg0);
            func_1516972C(arg0);
        }
    }
}
