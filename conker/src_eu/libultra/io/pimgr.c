// #include <os_internal.h>
// #include "piint.h"
//
// s32 osPiRawStartDma(s32 direction, u32 devAddr, void *dramAddr, u32 size);
// s32 osEPiRawStartDma(OSPiHandle *pihandle, s32 direction, u32 devAddr, void *dramAddr, u32 size);
//
// OSDevMgr __osPiDevMgr = {0};
// OSPiHandle *__osPiTable = NULL;
// OSPiHandle *__osCurrentHandle[2] = {&CartRomHandle, &LeoDiskHandle};
// static OSThread piThread;
// static char piThreadStack[OS_PIM_STACKSIZE];
// #ifdef _DEBUG
// static OSThread ramromThread;
// static char ramromThreadStack[OS_RAMROM_STACKSIZE];
// static OSMesgQueue getRamromQ;
// static OSMesg getRamromBuf[1];
// static OSMesgQueue freeRamromQ;
// static OSMesg freeRamromBuf[1];
// #endif
// static OSMesgQueue piEventQueue;
// static OSMesg piEventBuf[1];
// void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt)
// {
// 	u32 savedMask;
// 	OSPri oldPri;
// 	OSPri myPri;
// 	if (!__osPiDevMgr.active)
// 	{
// 		osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
// 		osCreateMesgQueue(&piEventQueue, (OSMesg*)&piEventBuf, 1);
// 		if (!__osPiAccessQueueEnabled)
// 			__osPiCreateAccessQueue();
// 		osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg)0x22222222);
// 		oldPri = -1;
// 		myPri = osGetThreadPri(NULL);
// 		if (myPri < pri)
// 		{
// 			oldPri = myPri;
// 			osSetThreadPri(NULL, pri);
// 		}
// 		savedMask = __osDisableInt();
// 		__osPiDevMgr.active = 1;
// 		__osPiDevMgr.thread = &piThread;
// 		__osPiDevMgr.cmdQueue = cmdQ;
// 		__osPiDevMgr.evtQueue = &piEventQueue;
// 		__osPiDevMgr.acsQueue = &__osPiAccessQueue;
// 		__osPiDevMgr.dma = osPiRawStartDma;
// 		__osPiDevMgr.edma = osEPiRawStartDma;
// 		osCreateThread(&piThread, 0, __osDevMgrMain, &__osPiDevMgr, &piThreadStack[OS_PIM_STACKSIZE], pri);
// 		osStartThread(&piThread);
// 		__osRestoreInt(savedMask);
// 		if (oldPri != -1)
// 		{
// 			osSetThreadPri(NULL, oldPri);
// 		}
// 	}
// }

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u32 active;
    OSThread *thread;
    OSMesgQueue *cmdQueue;
    OSMesgQueue *evtQueue;
    OSMesgQueue *acsQueue;
    s32 (*dma)(s32, u32, void *, u32);
    s32 (*edma)(OSPiHandle *, s32, u32, void *, u32);
} OSDevMgr_s86;

extern OSDevMgr_s86 g_os_pi_dev_mgr; /* __osPiDevMgr; was D_8002AE90 */
extern OSThread g_os_pi_thread;     /* piThread; was D_80035C70 */
extern char g_os_pi_access_queue[];       /* piThreadStack end; was D_80042C88 */
extern OSMesgQueue g_os_pi_event_queue;  /* piEventQueue; was D_80036EA0 */
extern OSMesg g_os_pi_event_buf[1];    /* piEventBuf; was D_80036EB8 */
extern u32 g_os_pi_access_queue_enabled;          /* __osPiAccessQueueEnabled; was D_8002C0B0 */
extern OSMesgQueue g_os_pi_event_queue; /* was D_80036EA0 */
void os_pi_create_access_queue(void);       /* __osPiCreateAccessQueue */
s32 os_epi_raw_start_dma(OSPiHandle *, s32, u32, void *, u32); /* osEPiRawStartDma */
void pi_dev_mgr_main(void *);     /* __osDevMgrMain */
s32 osPiRawStartDma(s32, u32, void *, u32);
u32 __osDisableInt(void);
void __osRestoreInt(u32);

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (!g_os_pi_dev_mgr.active) {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&g_os_pi_event_queue, (OSMesg *)&g_os_pi_event_buf, 1);
        if (!g_os_pi_access_queue_enabled) {
            os_pi_create_access_queue();
        }
        osSetEventMesg(OS_EVENT_PI, &g_os_pi_event_queue, (OSMesg)0x22222222);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        g_os_pi_dev_mgr.active = 1;
        g_os_pi_dev_mgr.thread = &g_os_pi_thread;
        g_os_pi_dev_mgr.cmdQueue = cmdQ;
        g_os_pi_dev_mgr.evtQueue = &g_os_pi_event_queue;
        g_os_pi_dev_mgr.acsQueue = (OSMesgQueue *)g_os_pi_access_queue;
        g_os_pi_dev_mgr.dma = osPiRawStartDma;
        g_os_pi_dev_mgr.edma = os_epi_raw_start_dma;
        osCreateThread(&g_os_pi_thread, 0, pi_dev_mgr_main, &g_os_pi_dev_mgr, &g_os_pi_event_queue, pri);
        osStartThread(&g_os_pi_thread);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}
