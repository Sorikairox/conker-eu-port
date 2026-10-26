#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 g_os_pi_access_queue_enabled; /* was D_8002C0B0 */
extern u8 *g_os_pi_access_buf; /* was D_80042C80 */
extern OSMesgQueue g_os_pi_access_queue; /* was D_80042C88 */

/* was func_10023B70 */
void os_pi_create_access_queue(void) {
    g_os_pi_access_queue_enabled = 1;
    osCreateMesgQueue(&g_os_pi_access_queue, &g_os_pi_access_buf, 1);
    osSendMesg(&g_os_pi_access_queue, NULL, 0);
}

/* was func_10023BC0 */
void os_pi_get_access(void) {
    OSMesg dummyMesg;

    if (!g_os_pi_access_queue_enabled) {
        os_pi_create_access_queue();
    }
    osRecvMesg(&g_os_pi_access_queue, &dummyMesg, OS_MESG_BLOCK);
}

extern OSMesgQueue g_os_pi_access_queue; /* was D_80042C88 */

/* was func_10023C04 */
void os_pi_rel_access(void) {
    osSendMesg(&g_os_pi_access_queue, NULL, 0);
}

typedef struct {
    OSMesgQueue *messageQueue;
    OSMesg message;
} __OSEventState;
extern __OSEventState g_os_event_state_tab[]; /* was D_80042CA0 */ // __osEventStateTab

void osSetEventMesg(OSEvent event, OSMesgQueue *mq, OSMesg msg) {
    register u32 saveMask = __osDisableInt();
    __OSEventState *es;

    es = &g_os_event_state_tab[event];
    es->messageQueue = mq;
    es->message = msg;
    __osRestoreInt(saveMask);
}
