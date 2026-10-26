#include "n_synthInternals.h"

// s125: DK64 src/global_asm/audio/code_1445A0.c (n_alAuxBusPull, func_global_asm_8073F8A0), built -g.
// Conker walks a per-bus voice list (ALLink at +8 of each pvoice) instead of DK64's array + bus id check.
typedef struct {
    u8 pad0[0x99];
    u8 unk99;
} S210C0_Owner;

typedef struct {
    u8 pad0[8];
    S210C0_Owner *unk8;
} S210C0_Voice;

typedef struct S210C0_PVoice {
    u8 pad0[8];
    struct S210C0_PVoice *next;
    u8 padC[4];
    S210C0_Voice *vvoice;
} S210C0_PVoice;

typedef struct {
    u8 pad0[0x14];
    S210C0_PVoice *voices;
    u8 pad18[0x44 - 0x18];
} S210C0_AuxBus;

typedef struct {
    u8 pad0[0x48];
    S210C0_AuxBus *auxBus;
} S210C0_Synth;

extern S210C0_Synth *g_audio_synth; /* was D_8002BA44 */
Acmd *func_10020000(S210C0_PVoice *, s32, Acmd *);
f32 sqrtf(f32);

/* was func_100210C0 */
Acmd *n_aux_bus_pull(s32 arg0, Acmd *arg1, s32 arg2, s32 *arg3) {
    Acmd *sp3C;
    S210C0_AuxBus *sp38;
    S210C0_PVoice *sp34;
    s32 sp30;
    u32 sp2C;
    u32 sp28;
    Acmd *sp24;
    Acmd *sp20;
    Acmd *sp1C;

    sp3C = arg1;
    sp38 = &g_audio_synth->auxBus[arg2];
    sp30 = 0;
    sp2C = 1;
    *arg3 = 0;
    sp34 = sp38->voices;
    while (sp34 != NULL) {
        sp34 = (S210C0_PVoice *) ((u8 *) sp34 - 8);
        if ((sp34->vvoice != NULL) &&
            (sp34->vvoice->unk8 != NULL) &&
            (sp34->vvoice->unk8->unk99 >= 0x40)) {
            sp3C = func_10020000(sp34, arg0, sp3C);
            *arg3 += 1;
            sp30++;
            if (sp34->vvoice->unk8->unk99 > sp2C) {
                sp2C = sp34->vvoice->unk8->unk99;
            }
        }
        sp34 = sp34->next;
    }
    if (sp30) {
        sp2C -= 0x3E;
        if (sp2C >= 7U) {
            sp28 = 26755.0f / sqrtf(sp2C);
        } else {
            sp28 = 65536.0f / sp2C;
        }
        sp24 = sp3C++;
        sp24->words.w0 = 0x4E0;
        sp24->words.w1 = (s32) (((sp28 & 0xFFFF) << 0x10) | (sp2C & 0xFFFF));
        sp20 = sp3C++;
        sp20->words.w0 = 0x650;
        sp20->words.w1 = (s32) (((sp28 & 0xFFFF) << 0x10) | (sp2C & 0xFFFF));
    }
    sp34 = sp38->voices;
    while (sp34 != NULL) {
        sp34 = (S210C0_PVoice *) ((u8 *) sp34 - 8);
        if (((sp34->vvoice != NULL) &&
             ((sp34->vvoice->unk8 == NULL) || (sp34->vvoice->unk8->unk99 < 0x40))) ||
            ((sp34->vvoice == NULL) && (arg2 == 0))) {
            sp1C = sp3C;
            sp3C = func_10020000(sp34, arg0, sp3C);
            if (sp3C != sp1C) {
                *arg3 += 1;
            }
        }
        sp34 = sp34->next;
    }
    return sp3C;
}
