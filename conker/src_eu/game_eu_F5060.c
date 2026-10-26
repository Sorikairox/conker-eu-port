#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 event_dispatch(s32, s32, ...);
#else
s32 event_dispatch(s32, s32, s32, s32, s32, s32);
#endif

void func_150C7850(u8 *arg0) {
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x80004000);
    if (event_dispatch(3, 0x2000, 0xAC, 0x4002, 0x4003, 0x4004) != 0) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x400000);
        return;
    }
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFFBFFFFF);
}
