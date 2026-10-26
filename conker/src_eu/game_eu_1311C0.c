#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 event_dispatch(s32, s32, ...);

/* was func_151039B0 */
void player_update_level_event_flags(u8 *arg0) {
    s32 temp_t6;
    s32 sp24;

    temp_t6 = (*(u8 *)((u8 *)arg0 + 0x23D)) | 0x9000;
    if ((*(u8 *)((u8 *)((*(u8 **)((u8 *)arg0 + 0x3D0))) + 0xAD)) == 1) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x01000000);
    } else {
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xFEFFFFFF);
    }
    if (g_level_id == 0x34) {
        if (event_dispatch(1, 0x406D, 6, temp_t6) != 0) {
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x200);
            return;
        }
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x200);
        return;
    }
    if (g_level_id == 0x30) {
        sp24 = temp_t6;
        if ((event_dispatch(1, 0x403C, 6, temp_t6) != 0) || (event_dispatch(1, 0x403D, 6, temp_t6) != 0)) {
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x200);
            return;
        }
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & ~0x200);
        return;
    }
    if (g_level_id == 0x2D) {
        sp24 = temp_t6;
        if ((event_dispatch(1, 0x4053, 6, temp_t6) != 0) || (sp24 = temp_t6, (event_dispatch(1, 0x4054, 6, temp_t6) != 0)) || (sp24 = temp_t6, (event_dispatch(1, 0x4056, 6, temp_t6) != 0)) || (event_dispatch(1, 0x4057, 6, temp_t6) != 0)) {
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x20000000);
        } else {
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xDFFFFFFF);
        }
        if ((event_dispatch(1, 0x4058, 6, 0x9000) != 0) || (event_dispatch(1, 0x4059, 6, 0x9000) != 0)) {
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x80000000);
            return;
        }
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0x7FFFFFFF);
        return;
    }
    if (g_level_id == 0x34) {
        if (event_dispatch(1, 0x406E, 6, temp_t6) != 0) {
            (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) | 0x20000000);
            return;
        }
        (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x84)) & 0xDFFFFFFF);
    }
}
