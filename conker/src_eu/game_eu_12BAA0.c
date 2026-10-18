#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_150FE290(s32 arg0) {
    struct127 *p;

    func_15103828();
    if (D_800C35EA == 1) {
        p = D_800CC2D0;
        do {
            if (p->id == 0x28) {
                func_150EDBB8(p, 0x14, 0x14);
            }
            p++;
        } while (p != (struct127 *)&D_800D121C);
    }
}
