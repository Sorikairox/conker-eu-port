#include <PR/sched.h>

#include "functions.h"
#include "variables.h"


u64 D_8003B260; // bss

/* was func_100050A0 */
void sched_init(OSMesgQueue *queue) {
    D_8003B260 = 0x00000000FEFEFEFE;
    D_8003B234 = 0;
    D_8003B230 = queue;
    D_8003B238 = (u8)0xFF;
    D_8003B239 = (u8)0;
    D_8003B23A = (u8)0;
    osCreateMesgQueue(&D_8003B1E8, &D_8003B660, 3);
    osCreateMesgQueue(&D_8003B200, &D_8003B670, 1);
    // EU: no third queue and no osViSetEvent here
    video_init_screen();
    osSetEventMesg(OS_EVENT_DP, &D_8003B218, (OSMesg *) 1);
    osSetEventMesg(OS_EVENT_SP, &D_8003B218, (OSMesg *) 2);
    osCreateThread(&D_8003B6A0, 0x14, (void *) sched_thread_main, 0, &D_8003B660, 13);
    osStartThread(&D_8003B6A0);
}

/* was func_100051C8 */
void sched_add_client(OSPfs *pfs, OSMesgQueue *queue) {
    pfs->queue = queue;
    pfs->status = (s32)D_8003B234;
    D_8003B234 = pfs;
}

/* was func_100051E8 */
void sched_send_retrace_msg(void) {
    osSendMesg(D_8003B230, &D_8003B240, 0);
}

/* was func_10005218 */
void prenmi_thread_start(void) {
    osCreateMesgQueue(&D_8003B9D0, &D_8003B9E8, 2);
    osSetEventMesg(OS_EVENT_PRENMI, &D_8003B9D0, (OSMesg *)5);
    osCreateThread(&D_8003B9F0, 0x15, (void *) prenmi_thread_main, 0, &D_8003B9D0, OS_PRIORITY_RMON);
    osStartThread(&D_8003B9F0);
}

/* was func_10005298 */
void prenmi_stub_noop(void) {
}

/* P281: readable C for prenmi_thread_main (compiled C, 195 insns; replaces the US-era `#if 0` draft). */
extern s32 D_8002C068;            /* set: do not wait for the PRE-NMI message */
extern OSMesgQueue D_8003BD70;    /* PRE-NMI queue (osSetEventMesg(OS_EVENT_PRENMI) in prenmi_thread_start) */
extern OSThread D_80035C70;
extern u64 D_8003BFC0;            /* time of the PRE-NMI */
extern u8 D_8002AE14;             /* rumble paks were probed */
extern u8 D_8002AE18;             /* the controller queue is already ours */
extern u8 D_800BED64[4];          /* channel has a rumble pak */
extern u8 D_800BED68[4];          /* channel's rumble is running */
extern OSMesg D_800BEDB0;
extern OSPfs D_800BEB80[4];
extern s8 D_8002AE24;             /* RDP in use */
extern void __osSpSetStatus(u32);
extern s32 __osSpSetPc(u32);
extern void osDpSetStatus(u32);
extern s32 os_motor_init(OSMesgQueue *mq, OSPfs *pfs, int channel);
extern s32 os_motor_stop(OSPfs *pfs);
// prenmi_thread: thread entry started by prenmi_thread_start. Waits for the PRE-NMI message (unless D_8002C068), stops the
// game threads, lowers its priority, stops every running rumble pak (taking the controller queue first when needed),
// waits 0x22ADD7 then 0x7270E0 counter ticks after the PRE-NMI, halts the RSP (and the RDP when it was in use),
// writes back the data cache and spins until the reset.
/* was func_100052A0 */
void prenmi_thread_main(s32 arg0) {
    OSMesg mesg;
    s32 any;
    s32 i;

    mesg = 0;
    if (D_8002C068 == 0) {
        osRecvMesg(&D_8003BD70, &mesg, OS_MESG_BLOCK);
    }
    g_eeprom_writes_disabled = 1;
    osStopThread(&D_80035C70);
    osStopThread(&D_80031AE0);
    audio_thread_stop();
    D_8003BFC0 = osGetTime();
    osSetThreadPri(NULL, 11);
    if (D_8002AE14 != 0) {
        any = 0;
        for (i = 0; i < 4; i++) {
            if (D_800BED64[i] != 0) {
                any = 1;
            }
        }
        if (any == 1 && D_8002AE18 == 0) {
            osRecvMesg(&g_si_mesg_queue, &D_800BEDB0, OS_MESG_BLOCK);
        }
        for (i = 0; i < 4; i++) {
            if (D_800BED64[i] != 0) {
                os_motor_init(&g_si_mesg_queue, &D_800BEB80[i], i);
                os_motor_stop(&D_800BEB80[i]);
                D_800BED68[i] = 0;
            }
        }
    }
    while (osGetTime() < D_8003BFC0 + 0x22ADD7) {
    }
    while (osGetTime() < D_8003BFC0 + 0x7270E0) {
    }
    __osSpSetStatus(0xAAAA82);
    if (D_8002AE24 != 0) {
        osDpSetStatus(0x1D6);
    }
    __osSpSetPc(0);
    osWritebackDCacheAll();
    while (1) {
    }
}
