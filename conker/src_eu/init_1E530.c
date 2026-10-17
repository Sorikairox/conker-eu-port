#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/init_1E530/func_1001E530.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_1E530/func_1001ED6C.s")
// _n_loadOutputBuffer ?
#pragma GLOBAL_ASM("asm/nonmatchings/init_1E530/func_1001F28C.s")
// _n_loadBuffer ?
#pragma GLOBAL_ASM("asm/nonmatchings/init_1E530/func_1001F5A4.s")
// void *func_1001F5A4(void *arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4, void *arg5) {
//     void *sp34;
//     s32 sp30;
//     s32 sp2C;
//     u32 sp28;
//     u32 sp24;
//     void *sp20;
//     void *sp1C;
//     void *sp18;
//     void *temp_t3;
//     void *temp_t3_2;
//     void *temp_t7;
//
//     sp34 = arg5;
//     sp24 = (arg0 + (arg1 * 4))->unk20 + (*arg0 * 2);
//     if (arg2 < (u32) (arg0 + (arg1 * 4))->unk20) {
//         arg2 = arg2 + (*arg0 * 2);
//     }
//     sp28 = (arg4 * 2) + arg2;
//     if (sp24 < sp28) {
//         sp30 = (s32) (sp28 - sp24) >> 1;
//         sp2C = (s32) (sp24 - arg2) >> 1;
//         temp_t7 = sp34;
//         sp34 = temp_t7 + 8;
//         sp20 = temp_t7;
//         *temp_t7 = (s32) ((((sp2C * 2) & 0xFFF) << 0xC) | 0x4000000 | (arg3 & 0xFFF));
//         sp20->unk4 = osVirtualToPhysical(arg2);
//         temp_t3 = sp34;
//         sp34 = temp_t3 + 8;
//         sp1C = temp_t3;
//         sp1C->unk0 = (s32) ((((sp30 * 2) & 0xFFF) << 0xC) | 0x4000000 | ((arg3 + (sp2C * 2)) & 0xFFF));
//         sp1C->unk4 = osVirtualToPhysical((arg0 + (arg1 * 4))->unk20);
//     } else {
//         temp_t3_2 = sp34;
//         sp34 = temp_t3_2 + 8;
//         sp18 = temp_t3_2;
//         *temp_t3_2 = (s32) ((((arg4 * 2) & 0xFFF) << 0xC) | 0x4000000 | (arg3 & 0xFFF));
//         sp18->unk4 = osVirtualToPhysical(arg2);
//     }
//     return sp34;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/init_1E530/func_1001F79C.s")
// void *func_1001F79C(void *arg0, s32 arg1, u32 arg2, s32 arg3, void *arg4) {
//     void *sp34;
//     s32 sp30;
//     s32 sp2C;
//     u32 sp28;
//     u32 sp24;
//     void *sp20;
//     void *sp1C;
//     void *sp18;
//     void *temp_t0;
//     void *temp_t7;
//     void *temp_t7_2;
//
//     sp34 = arg4;
//     sp24 = (arg0 + (arg1 * 4))->unk20 + (*arg0 * 2);
//     if (arg2 < (u32) (arg0 + (arg1 * 4))->unk20) {
//         arg2 = arg2 + (*arg0 * 2);
//     }
//     sp28 = arg2 + 0x170;
//     if (sp24 < sp28) {
//         sp30 = (s32) (sp28 - sp24) >> 1;
//         sp2C = (s32) (sp24 - arg2) >> 1;
//         temp_t0 = sp34;
//         sp34 = temp_t0 + 8;
//         sp20 = temp_t0;
//         *temp_t0 = (s32) ((((sp2C * 2) & 0xFFF) << 0xC) | 0x6000000 | (arg3 & 0xFFF));
//         sp20->unk4 = osVirtualToPhysical(arg2);
//         temp_t7 = sp34;
//         sp34 = temp_t7 + 8;
//         sp1C = temp_t7;
//         sp1C->unk0 = (s32) ((((sp30 * 2) & 0xFFF) << 0xC) | 0x6000000 | ((arg3 + (sp2C * 2)) & 0xFFF));
//         sp1C->unk4 = osVirtualToPhysical((arg0 + (arg1 * 4))->unk20);
//     } else {
//         temp_t7_2 = sp34;
//         sp34 = temp_t7_2 + 8;
//         sp18 = temp_t7_2;
//         sp18->unk0 = (s32) ((arg3 & 0xFFF) | 0x6170000);
//         sp18->unk4 = osVirtualToPhysical(arg2);
//     }
//     return sp34;
// }

Acmd *func_1001F978(struct55 *arg0, s32 arg1, s32 arg2, Acmd *p) {
    Acmd *ptr = p;
    s16 tmp = arg2 >> 8;

    aLoadADPCM(ptr++, 32, osVirtualToPhysical(&arg0->unk8));
    aPoleFilter(ptr++, arg0->unk28, arg0->unk2, (osVirtualToPhysical(((s32 **)&arg0->unk2C)[arg1]) & 0xFFFFFF) | ((tmp & 0xFF) << 24));
    arg0->unk28 = 0;
    return ptr;
}

f32 func_1001FA78(f32 arg0[4][4], s32 arg1) {
    f32 tmp;

    arg0[1][1] += arg0[1][0] * arg1;
    if (arg0[1][1] > 2.0f) {
        arg0[1][1] -= 4.0f;
    }
    else {
        arg0[1][1] = arg0[1][1]; // ???
    }

    tmp = arg0[1][1];
    tmp = tmp < 0.0f ? -tmp : tmp;
    tmp = tmp - 1.0f;

    return tmp * arg0[1][3];
}
