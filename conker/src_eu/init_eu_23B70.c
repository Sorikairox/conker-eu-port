#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_8002C0B0;
extern u8 *D_80042C80;
extern OSMesgQueue D_80042C88;

void func_10023B70(void) {
    D_8002C0B0 = 1;
    osCreateMesgQueue(&D_80042C88, &D_80042C80, 1);
    osSendMesg(&D_80042C88, NULL, 0);
}

void func_10023BC0(void) {
    OSMesg dummyMesg;

    if (!D_8002C0B0) {
        func_10023B70();
    }
    osRecvMesg(&D_80042C88, &dummyMesg, OS_MESG_BLOCK);
}

extern OSMesgQueue D_80042C88;

void func_10023C04(void) {
    osSendMesg(&D_80042C88, NULL, 0);
}

typedef struct {
    OSMesgQueue *messageQueue;
    OSMesg message;
} __OSEventState;
extern __OSEventState D_80042CA0[]; // __osEventStateTab

void osSetEventMesg(OSEvent event, OSMesgQueue *mq, OSMesg msg) {
    register u32 saveMask = __osDisableInt();
    __OSEventState *es;

    es = &D_80042CA0[event];
    es->messageQueue = mq;
    es->message = msg;
    __osRestoreInt(saveMask);
}
