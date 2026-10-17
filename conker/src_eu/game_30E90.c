#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150039E0.s")

// FIXME: matches but something isnt right
void func_15004574(void) {
    if (D_800DBF88 != 0xFF) {
        D_800DBF8C = D_800DBEF4[D_800DBF88].unk1C;
        D_800DBF90 = D_800DBEF4[D_800DBF88].unk28;
    }
}

void func_150045BC(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_150045C4.s")
void func_150049A4(Gfx *arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; ((struct_eu_cmd8 *)&arg0[i])->cmd != -0x21; i++) {
        switch (((struct_eu_cmd8 *)&arg0[i])->cmd) {
            case 0xDE:
                ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg1;
                break;
            case 1:
                ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg1;
                break;
            case -0x24:
                if (((struct_eu_cmd8 *)&arg0[i])->unk3 == 0xE) {
                    ((struct_eu_cmd8 *)&arg0[i])->unk4 += arg2;
                }
                break;
        }
    }
}
void func_15004A4C(void) {
    s32 i;

    for (i = 0; i < D_800DC320; i++) {
        D_800DC328[i] = 0;
        D_800DC32C[i] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_30E90/func_15004AAC.s")
s32 func_15004BF0(s32 arg0) {
    s32 i;
    s32 id;
    s32 first;

    if (arg0 == 0) {
        id = 1;
        for (i = D_800DBF00; i < D_800DC320; i++) {
            if (id == D_800DBEF4[i].pad70[2]) {
                id++;
                i = D_800DBF00 - 1;
            }
            if (id >= 0x100) {
                id = 0xFF;
                break;
            }
        }
    } else {
        first = 0xFF - D_800DBF00;
        id = first;
        for (i = 0; i < D_800DC320; i++) {
            if (id == D_800DBEF4[i].pad70[2]) {
                id--;
                i = -1;
            }
            if (id <= 0) {
                id = first;
                break;
            }
        }
    }
    return id;
}
void func_15004CE0(Gfx *arg0, s32 arg1) {
    s32 i;
    struct_eu_cmd8 *p;

    for (i = 0; ((struct_eu_cmd8 *)&arg0[i])->cmd != -0x21; i++) {
        p = (struct_eu_cmd8 *)&arg0[i];
        if (p->cmd == -0x24 && p->unk3 == 0xE && p->unk4 < 0x80000000) {
            p->unk4 += arg1;
        }
    }
}
