#include "n_synthInternals.h"


// s123: DK64 src/global_asm/audio/n_resample2.c (func_global_asm_80740C50), built -g
/* DK64 CustomPVoice (include/structs.h), only the fields used here */
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    void *unk14;
    f32 unk18;
    s32 unk1C;
    f32 unk20;
    s32 unk24;
} CustomResampler;
typedef struct {
    u8 pad0[0x34]; /* Conker: DK64 offsets +8 */
    CustomResampler resampler;
    u8 pad5C[0x99 - 0x5C];
    u8 unk8C; /* Conker 0x99 (DK64 0x8C) */
    u8 pad9A[0xA0 - 0x9A];
    s16 unk90;
    s16 unk92;
    u8 padA4[0xA8 - 0xA4];
    s32 unk98;
    u8 padAC[0xC8 - 0xAC];
    s32 unkB8;
    s32 unkBC;
} CustomPVoice;

#define func_global_asm_80740C50 func_10022040
#define func_global_asm_80741070 func_10022460
#define func_global_asm_8073BE54 func_1001CF38
void *func_global_asm_80741070(CustomPVoice *, s16 *, Acmd *);
void func_global_asm_8073BE54(void *arg0, f32 arg1);
f32 sqrtf(f32);

void *func_global_asm_80740C50(CustomPVoice *arg0, s16 *arg1, s32 arg2, Acmd *arg3) {
    // Unsure of arg2 type, doesn't seem used?
    Acmd *sp2C;
    f32 sp24;
    Acmd *sp20;
    Acmd *sp1C;
    Acmd *sp18;

    sp2C = arg3;
    sp2C = func_global_asm_80741070(arg0, arg1, arg3);
    if ((arg0->unk8C != 0) && (arg0->unk8C < 0x40)) {
        if (arg0->unk8C >= 6) {
            sp24 = 26755.0f / sqrtf(arg0->unk8C + 1.0f);
        } else {
            sp24 = 65536.0f / ((f32) arg0->unk8C + 1.0f);
        }
        if (sp24 < 7723.0f) {
            sp24 = 7723.0f;
        }
        sp20 = sp2C++;
        sp20->words.w0 = (*arg1 & 0xFFFF);
        sp20->words.w1 = ((((u32) sp24 & 0xFFFF) << 0x10) | ((arg0->unk8C + 1) & 0xFFFF));
    }
    if (arg0->unk92 > 0) {
        if (arg0->unkB8 != 0) {
            func_global_asm_8073BE54(&arg0->unk90, 22050.0f);
        }
        sp1C = sp2C++;
        sp1C->words.w0 = 0x0B000020;
        sp1C->words.w1 = osVirtualToPhysical(&arg0->unk98);
        if (arg0->unkB8 == 2) {
            arg0->unkB8 = 0;
        }
        sp18 = sp2C++;
        sp18->words.w0 = ((*arg1 & 0xFFFF) | (((arg0->unkB8 & 0xFF) << 0x10) | 0x0E000000));
        sp18->words.w1 = (osVirtualToPhysical(arg0->unkBC) & 0xFFFFFF & 0xFFFFFF);
        arg0->unkB8 = 0;
    }
    return sp2C;
}

// NON-MATCHING: 80% matching
// struct21 *func_10022040(struct42 *arg0, struct119 *arg1, s32 arg2, struct21 *arg3) {
//     struct21 *sp2C;
//     f32 sp28;
//     struct21 *sp24;
//     struct21 *sp20;
//     struct21 *sp1C;
//
//     sp2C = arg3;
//     sp2C = func_10022460(arg0, arg1, arg3);
//
//     if ((arg0->unk99 != 0) && (arg0->unk99 < 64)) {
//         if (arg0->unk99 >= 6) {
//             sp28 = D_8002C820 / sqrtf(arg0->unk99 + 1.0f);
//         } else {
//             sp28 = 65536.0f / (arg0->unk99 + 1.0f);
//         }
//         if (sp28 < D_8002C834) {
//             sp28 = D_8002C838;
//         }
//         sp24 = sp2C = &sp2C->unk8;
//         sp24->unk0 = ((s32)arg1 & 0xFFFF);
//         sp24->unk4 =  (((u32) sp28 & 0xFFFF) << 16) | (arg0->unk99 + 1);
//     }
//     if ((s16)arg0->unkA2 > 0) {
//         if (arg0->unkC8 != 0) {
//             func_1001CF38(&arg0->unkA0, 22050.0f);
//         }
//         sp20 = sp2C = &sp2C->unk8;
//         sp20->unk0 = 0xB000020;
//         sp20->unk4 = osVirtualToPhysical(&arg0->unkA8);
//         if (arg0->unkC8 == 2) {
//             arg0->unkC8 = 0;
//         }
//         sp1C = sp2C = &sp2C->unk8;
//         sp1C->unk0 = (((s32)arg1 & 0xFFFF) | (((arg0->unkC8 & 0xFF) << 0x10) | 0xE000000));
//         sp1C->unk4 = (osVirtualToPhysical(arg0->unkCC) & 0xFFFFFF & 0xFFFFFF);
//         arg0->unkC8 = 0;
//     }
//     return sp2C;
// }

s32 n_alLoadParam(N_PVoice *filter, s32 paramID, void *param) {
    f32 *sp24 = &param;

    switch (paramID) {
        case 4:
            filter->unkA2 = 0;
            n_adpcm_load_param(filter, 4, param);
            break;
        case 18:
            filter->unkA2 = param;
            filter->unkC8 |= 2;
            break;
        case 19:
            filter->unkA0 = *sp24;
            filter->unkC8 |= 2;
            break;
        case 17:
            filter->unk99 = param;
            break;
        default:
            n_adpcm_load_param(filter, paramID, param);
            break;
    }

    return 0;
}
