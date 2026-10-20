#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u64 D_8002C060;
extern OSTimer D_80042DE8;
extern OSMesgQueue D_80042E08;
extern s32 D_80042E20;
extern OSMesgQueue *D_800E0E50;
extern u8 D_800E0E54;
extern void *D_800E0E58;
extern s32 D_800E0E5C;
s32 func_151DD4A0(OSMesgQueue *mq, u8 address, void *buffer, s32 nbytes) {
    s32 temp_v0;
    temp_v0 = func_151DD588(1);
    if (temp_v0 != 0) {
        do {
        } while (func_151DD588(1) != 0);
    }
    D_800E0E50 = mq;
    D_800E0E54 = address;
    D_800E0E58 = buffer;
    D_800E0E5C = nbytes;
    return osSetTimer(&D_80042DE8, (12000ULL * D_8002C060) / 1000000ULL, 0, &D_80042E08, &D_80042E20);
}

int func_151DD588(s32 flag) {
    if (D_800E0E50 == NULL) {
        return 0;
    }
    if (osRecvMesg(&D_80042E08, NULL, flag) != -1) {
        if (D_800E0E5C <= 0) {
            D_800E0E50 = NULL;
            D_800E0E5C = 0;
            return 0;
        }
        if (func_151DDA90(D_800E0E50, D_800E0E54, D_800E0E58) != 0) {
            D_800E0E50 = NULL;
            D_800E0E5C = 0;
            return 0;
        }
        D_800E0E5C -= 8;
        D_800E0E54 += 1;
        D_800E0E58 = (u8 *)D_800E0E58 + 8;
        osSetTimer(&D_80042DE8, (12000ULL * D_8002C060) / 1000000ULL, 0, &D_80042E08, &D_80042E20);
        return 1;
    }
    return 0;
}
