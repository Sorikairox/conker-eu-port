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
void prenmi_thread_main(s32 arg0) {
    OSMesg mesg;
    s32 any;
    s32 i;

    mesg = 0;
    if (D_8002C068 == 0) {
        osRecvMesg(&D_8003BD70, &mesg, OS_MESG_BLOCK);
    }
    D_8002AC5C = 1;
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
            osRecvMesg(&D_800BE900, &D_800BEDB0, OS_MESG_BLOCK);
        }
        for (i = 0; i < 4; i++) {
            if (D_800BED64[i] != 0) {
                os_motor_init(&D_800BE900, &D_800BEB80[i], i);
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
