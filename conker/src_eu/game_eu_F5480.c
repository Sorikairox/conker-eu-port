#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 event_dispatch(s32, s32, ...);
#else
s32 event_dispatch();
#endif

void func_150C7C70(u8 *arg0) {
    if (event_dispatch(3, 0x2000, 0xAC, 0x401B, 0x401C, 0x401D) != 0) {
        event_dispatch_alt(1, 0x2000, 0x3B, 2);
    }
    if (event_dispatch(1, 0x4006, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x400000);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFFBFFFFF);
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x400000);
    if (event_dispatch(1, 0x4030, 6, 0x2000) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x01000000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFEFFFFFF);
}
