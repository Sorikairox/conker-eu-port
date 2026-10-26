#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ u8 pad0[0xA8];
    /* 0xA8 */ s32 unkA8;
    /* 0xAC */ s32 unkAC;
} struct_eu_15B2E0; // size 0xB0

extern struct_eu_15B2E0 *g_camera_event_queues; /* was D_800DC6E0 */


/* camera_queue_event: appends event (type, data) to camera cam's event queue g_camera_event_queues[cam +0x23D]: 20 slots of
 * { s32 type; void *data; } at +0x00, write index +0xAC (wraps at 20; the read index +0xA8 is camera_dequeue_event's).
 * The camera event pump camera_process_events drains it. Nothing checks for a full queue (as in the asm). */
/* was func_1512DAD0 */
void camera_queue_event(u8 *cam, s32 type, void *data) {
    struct_eu_15B2E0 *q = &g_camera_event_queues[cam[0x23D]];
    s32 *slot = (s32 *) ((u8 *) q + q->unkAC * 8);

    slot[0] = type;
    *(void **) (slot + 1) = data;
    q->unkAC++;
    if (q->unkAC == 20) {
        q->unkAC = 0;
    }
}

/* was func_1512DB74 */
u8 *camera_dequeue_event(u8 *arg0) {
    s32 temp_a1;
    struct_eu_15B2E0 *temp_v0;
    struct_eu_15B2E0 *temp_v0_2;

    temp_v0 = &g_camera_event_queues[(*(u8 *)((u8 *)arg0 + 0x23D))];
    temp_a1 = temp_v0->unkA8;
    temp_v0->unkA8 = temp_a1 + 1;
    temp_v0_2 = &g_camera_event_queues[(*(u8 *)((u8 *)arg0 + 0x23D))];
    if (temp_v0_2->unkA8 == 0x14) {
        temp_v0_2->unkA8 = 0;
    }
    return ((struct_eu_15B2E0 *)((u8 *)temp_v0 + (temp_a1 * 8)));
}
/* was func_1512DBDC */
void camera_event_queue_clear(u8 *arg0) {
    g_camera_event_queues[arg0[0x23D]].unkA8 = 0;
    g_camera_event_queues[arg0[0x23D]].unkAC = 0;
}

/* was func_1512DC20 */
s32 camera_event_queue_empty(u8 *arg0) {
    return g_camera_event_queues[arg0[0x23D]].unkA8 == g_camera_event_queues[arg0[0x23D]].unkAC;
}
