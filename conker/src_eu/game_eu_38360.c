#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_1500ABA0(s32 arg0) {
    bzero(&D_800BE4A0, 60);
    func_1502B8E0(&D_800BE4A0, 60, 3, 12, arg0, 10);
    bzero(&D_800DDA90, 240);
    bzero(&D_800DD478, 1560);
}

#ifdef NON_MATCHING
extern u16 D_800BE898[];  /* per ambient sound: loaded even when it is not id 0x3B */
extern s16 D_800DDFB0[];  /* per ambient sound: 2 x s16 */
extern u8 D_80096090[];   /* per sound id, 10 bytes: +2 u16 length, +8 u8 rate (asm rodata_inject block; ROM) */
u8 *func_1502B020(s32 *arg0, s32 arg1, ...);

// ambient_sounds_load: for each of the 15 ambient sound slots (ids at D_800BE4A0, 4-byte stride; 0xFF = empty)
// clears its voice record (D_800DDA90, 16 bytes) and, when D_800BE898[slot] is set or the id is 0x3B, loads the
// sample (func_1502B020 kind 2) into +0 with the 16-byte rounded size in +4 (+0 = NULL when the size or the id's
// length is 0), and sets D_800DDFB0[slot] = { rate * 32 - 1, (length / rate) * 64 / 5 - 1 } (unsigned divisions;
// rate 0 traps like the asm's divu check).
void func_1500AC14(void) {
    u8 *voice = (u8 *) &D_800DDA90;
    u16 *ids = (u16 *) &D_800BE4A0;
    s16 *timing;
    u8 *info;
    s32 slot;
    u32 id;
    s32 size;
    u8 *data;
    u32 length;
    u32 rate;

    for (slot = 0; slot < 15; slot++, voice += 0x10, ids += 2) {
        id = *ids;
        *(s32 *) (voice + 0) = 0;
        *(s32 *) (voice + 8) = 0;
        *(s32 *) (voice + 4) = 0;
        voice[0xC] = 0;
        if (id == 0xFF) {
            continue;
        }
        if (D_800BE898[slot] == 0 && id != 0x3B) {
            continue;
        }
        timing = &D_800DDFB0[slot * 2];
        data = func_1502B020(&size, 2, 0, id);
        info = &D_80096090[id * 10];
        *(u8 **) (voice + 0) = data;
        *(s32 *) (voice + 4) = (size + 15) & ~15;
        length = *(u16 *) (info + 2);
        if (size == 0 || length == 0) {
            length = 0;
            *(s32 *) (voice + 0) = 0;
        }
        rate = info[8];
        timing[0] = (rate << 5) - 1;
        timing[1] = (((length / rate) << 6) / 5) - 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500AC14.s")
#endif
// GOTO hell
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500AD84.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500AF08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500B1F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500B3B0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500B714.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500B8F4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500BAB8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500BC7C.s")

void func_1500BE40(s32 arg0) {
    D_800DDD10[0] = 0;
    D_800DDD10[1] = 0;
    D_800DDD0C = 110;
}

void func_1500BE68(void) {
    D_800DDD1C = 0;
    D_8008CEB0 = 0;
    D_800DDC04 = D_800DDC00 = D_800DDC08 = 0;
    D_800DDD20 = 0;
    func_1500BE40(0);
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_38360/func_1500BEC0.s")
