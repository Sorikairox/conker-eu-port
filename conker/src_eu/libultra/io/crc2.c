#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// game copy of libultra io/crc.c (pre-J version, -O1); the init copy is init_eu_26370
u8 func_151F27E0(u16 addr) {
    u8 temp = 0;
    u8 temp2;
    int i;

    for (i = 0; i < 16; i++) {
        if (temp & 0x10) {
            temp2 = 0x15;
        } else {
            temp2 = 0;
        }
        temp <<= 1;
        temp |= (u8)((addr & 0x400) ? 1 : 0);
        addr <<= 1;
        temp ^= temp2;
    }
    return temp & 0x1F;
}

u8 func_151F2890(u8 *data) {
    u8 temp = 0;
    u8 temp2;
    int i;
    int j;

    for (i = 0; i <= 32; i++) {
        for (j = 7; j >= 0; j--) {
            if (temp & 0x80) {
                temp2 = 0x85;
            } else {
                temp2 = 0;
            }
            temp <<= 1;
            if (i == 32) {
                temp |= 0;
            } else {
                temp |= ((*data & (1 << j)) ? 1 : 0);
            }
            temp ^= temp2;
        }
        data++;
    }
    return temp;
}
