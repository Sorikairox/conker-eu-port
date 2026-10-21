#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    s32 h;
    u8 t;
} EntABB0;
typedef struct {
    u8 type;
    u8 n;
    u8 pad[6];
} DescABB0;
extern DescABB0 D_800A7610[];
extern u16 D_800C4730[];
void func_1517ABB0(void) {
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 2; i++) {
        if (((EntABB0 ***)D_800DD460)[i] != NULL) {
            for (j = 0; j < D_800C4730[D_800A7610[i].type]; j++) {
                for (k = 0; k < D_800A7610[i].n; k++) {
                    if (((EntABB0 ***)D_800DD460)[i][j][k].h != 0) {
                        if (((EntABB0 ***)D_800DD460)[i][j][k].t != 0) {
                            ((EntABB0 ***)D_800DD460)[i][j][k].t--;
                        } else {
                            func_10004074(((EntABB0 ***)D_800DD460)[i][j][k].h);
                            ((EntABB0 ***)D_800DD460)[i][j][k].h = 0;
                        }
                    }
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A8930/func_1517B270.s")
