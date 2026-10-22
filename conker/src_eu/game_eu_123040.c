#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_1509BE40(s32, s32, ...);
#else
s32 func_1509BE40(s32, s32, s32, s32);
#endif

void func_150F5830(u8 *arg0) {
    if (func_1509BE40(1, 0x401C, 6, 0x9000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x80000000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0x7FFFFFFF);
}

void func_15182D40(void);

void func_150F5890(s32 arg0) {
    func_15182D40();
}
