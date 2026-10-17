#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_1509BE40(s32, s32, s32, s32);

void func_150BBBE0(u8 *arg0) {
    if (func_1509BE40(1, 0x4047, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x1000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x1000);
}
