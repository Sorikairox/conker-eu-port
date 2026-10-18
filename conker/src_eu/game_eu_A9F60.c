#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1507C7C0(struct127 *, u16 *, u16 *, u16 *);

void func_1507C370(void) {
    s32 i;
    struct127 *p;
    struct126 *t;

    p = D_800CC2D0;
    i = 0;
    if (D_8008FD8C > 0) {
        do {
            t = p->unk31C;
            if (t != NULL) {
                func_1507C7C0(p, &t->unk114, &t->unk116, &t->unk118);
            }
            i++;
            p++;
        } while (i < D_8008FD8C);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_A9F60/func_1507C7C0.s")
