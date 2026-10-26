#include <PR/sched.h>

#include "functions.h"
#include "variables.h"


u64 g_sched_init_pattern; /* was D_8003B260 */ // bss

/* was func_100050A0 */
void sched_init(OSMesgQueue *queue) {
    g_sched_init_pattern = 0x00000000FEFEFEFE;
    g_sched_clients = 0;
    g_sched_client_queue = queue;
    g_sched_retrace_count = (u8)0xFF;
    g_sched_frame_retraces = (u8)0;
    g_sched_retrace_hold = (u8)0;
    osCreateMesgQueue(&g_sched_gfx_queue_alias, &g_sched_gfx_msgs, 3);
    osCreateMesgQueue(&g_sched_audio_queue_alias, &g_sched_audio_msgs, 1);
    // EU: no third queue and no osViSetEvent here
    video_init_screen();
    osSetEventMesg(OS_EVENT_DP, &g_sched_event_queue_alias, (OSMesg *) 1);
    osSetEventMesg(OS_EVENT_SP, &g_sched_event_queue_alias, (OSMesg *) 2);
    osCreateThread(&g_sched_thread, 0x14, (void *) sched_thread_main, 0, &g_sched_gfx_msgs, 13);
    osStartThread(&g_sched_thread);
}

/* was func_100051C8 */
void sched_add_client(OSPfs *pfs, OSMesgQueue *queue) {
    pfs->queue = queue;
    pfs->status = (s32)g_sched_clients;
    g_sched_clients = pfs;
}

/* was func_100051E8 */
void sched_send_retrace_msg(void) {
    osSendMesg(g_sched_client_queue, &g_sched_retrace_msg, 0);
}

/* was func_10005218 */
void prenmi_thread_start(void) {
    osCreateMesgQueue(&g_prenmi_queue, &g_prenmi_msgs, 2);
    osSetEventMesg(OS_EVENT_PRENMI, &g_prenmi_queue, (OSMesg *)5);
    osCreateThread(&g_prenmi_thread, 0x15, (void *) prenmi_thread_main, 0, &g_prenmi_queue, OS_PRIORITY_RMON);
    osStartThread(&g_prenmi_thread);
}

/* was func_10005298 */
void prenmi_stub_noop(void) {
}

/* P281: readable C for prenmi_thread_main (compiled C, 195 insns; replaces the US-era `#if 0` draft). */
extern s32 g_os_shutdown_alias;            /* set: do not wait for the PRE-NMI message; was D_8002C068 */
extern OSMesgQueue g_prenmi_queue_alias;    /* PRE-NMI queue (osSetEventMesg(OS_EVENT_PRENMI) in prenmi_thread_start); was D_8003BD70 */
extern OSThread g_os_pi_thread; /* was D_80035C70 */
extern u64 g_prenmi_time;            /* time of the PRE-NMI; was D_8003BFC0 */
extern u8 g_rumble_paks_probed;             /* rumble paks were probed; was D_8002AE14 */
extern u8 g_cont_read_done;             /* the controller queue is already ours; was D_8002AE18 */
extern u8 g_rumble_pak_present[4];          /* channel has a rumble pak; was D_800BED64 */
extern u8 g_rumble_motor_on[4];          /* channel's rumble is running; was D_800BED68 */
extern OSMesg g_si_recv_mesg; /* was D_800BEDB0 */
extern OSPfs g_rumble_pfs[4]; /* was D_800BEB80 */
extern s8 g_sched_fb_swapped;             /* RDP in use; was D_8002AE24 */
extern void __osSpSetStatus(u32);
extern s32 __osSpSetPc(u32);
extern void osDpSetStatus(u32);
extern s32 os_motor_init(OSMesgQueue *mq, OSPfs *pfs, int channel);
extern s32 os_motor_stop(OSPfs *pfs);
// prenmi_thread: thread entry started by prenmi_thread_start. Waits for the PRE-NMI message (unless g_os_shutdown_alias), stops the
// game threads, lowers its priority, stops every running rumble pak (taking the controller queue first when needed),
// waits 0x22ADD7 then 0x7270E0 counter ticks after the PRE-NMI, halts the RSP (and the RDP when it was in use),
// writes back the data cache and spins until the reset.
/* was func_100052A0 */
void prenmi_thread_main(s32 arg0) {
    OSMesg mesg;
    s32 any;
    s32 i;

    mesg = 0;
    if (g_os_shutdown_alias == 0) {
        osRecvMesg(&g_prenmi_queue_alias, &mesg, OS_MESG_BLOCK);
    }
    g_eeprom_writes_disabled = 1;
    osStopThread(&g_os_pi_thread);
    osStopThread(&g_game_thread);
    audio_thread_stop();
    g_prenmi_time = osGetTime();
    osSetThreadPri(NULL, 11);
    if (g_rumble_paks_probed != 0) {
        any = 0;
        for (i = 0; i < 4; i++) {
            if (g_rumble_pak_present[i] != 0) {
                any = 1;
            }
        }
        if (any == 1 && g_cont_read_done == 0) {
            osRecvMesg(&g_si_mesg_queue, &g_si_recv_mesg, OS_MESG_BLOCK);
        }
        for (i = 0; i < 4; i++) {
            if (g_rumble_pak_present[i] != 0) {
                os_motor_init(&g_si_mesg_queue, &g_rumble_pfs[i], i);
                os_motor_stop(&g_rumble_pfs[i]);
                g_rumble_motor_on[i] = 0;
            }
        }
    }
    while (osGetTime() < g_prenmi_time + 0x22ADD7) {
    }
    while (osGetTime() < g_prenmi_time + 0x7270E0) {
    }
    __osSpSetStatus(0xAAAA82);
    if (g_sched_fb_swapped != 0) {
        osDpSetStatus(0x1D6);
    }
    __osSpSetPc(0);
    osWritebackDCacheAll();
    while (1) {
    }
}
