#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


extern s32 g_os_cont_initialized;          /* __osContinitialized; was D_8002C160 */
extern u64 g_os_clock_rate;          /* osClockRate; was D_8002C060 */
extern u8 g_os_cont_last_cmd;           /* __osContLastCmd; was D_80042DE0 */
extern u8 g_os_max_controllers;           /* __osMaxControllers; was D_80042DE1 */
extern OSPifRam g_os_cont_pif_ram;     /* __osContPifRam; was D_80042DA0 */
extern OSMesgQueue g_eep_timer_queue;  /* __osEepromTimerQ; was D_80042E08 */
extern OSMesg g_eep_timer_msg;       /* __osEepromTimerMsg; was D_80042E20 */
s32 os_si_raw_start_dma(s32, void *); /* __osSiRawStartDma */
void __osPackRequestData(u8);
void __osContGetInitData(u8 *, OSContStatus *);
void __osSiCreateAccessQueue(void);

/* was func_151EF850 */
s32 game_os_cont_init(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *data) {
    OSMesg dummy;
    s32 ret = 0;
    OSTime t;
    OSTimer mytimer;
    OSMesgQueue timerMesgQueue;

    if (g_os_cont_initialized) {
        return 0;
    }
    g_os_cont_initialized = TRUE;
    t = osGetTime();
    if (t < (500000ULL * g_os_clock_rate) / 1000000ULL) {
        osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
        osSetTimer(&mytimer, (500000ULL * g_os_clock_rate) / 1000000ULL - t, 0, &timerMesgQueue, &dummy);
        osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
    }
    g_os_max_controllers = 4;
    __osPackRequestData(0);
    ret = os_si_raw_start_dma(OS_WRITE, &g_os_cont_pif_ram);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    ret = os_si_raw_start_dma(OS_READ, &g_os_cont_pif_ram);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    __osContGetInitData(bitpattern, data);
    g_os_cont_last_cmd = 0;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&g_eep_timer_queue, &g_eep_timer_msg, 1);
    return ret;
}

extern u8 g_os_max_controllers; /* was D_80042DE1 */
extern OSPifRam g_os_cont_pif_ram; /* was D_80042DA0 */
/* was func_151EFA48 */
void game_os_cont_get_init_data(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits;

    bits = 0;
    ptr = (u8 *)g_os_cont_pif_ram.ramarray;
    for (i = 0; i < g_os_max_controllers; i++, ptr += sizeof(requestformat), data++) {
        requestformat = *(__OSContRequesFormat *)ptr;
        data->errno = CHNL_ERR(requestformat);
        if (data->errno == 0) {
            data->type = (requestformat.typel << 8) | requestformat.typeh;
            data->status = requestformat.status;
            bits |= 1 << i;
        }
    }
    *pattern = bits;
}

extern OSPifRam __osContPifRam;
extern u8 _osContNumControllers;
/* was func_151EFB18 */
void game_os_pack_request_data(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;

    for (i = 0; i < 16; i++) {
        __osContPifRam.ramarray[i] = 0;
    }
    __osContPifRam.pifstatus = CONT_CMD_EXE;
    ptr = (u8 *)__osContPifRam.ramarray;
    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;
    for (i = 0; i < _osContNumControllers; i++) {
        *(__OSContRequesFormat *)ptr = requestformat;
        ptr += sizeof(requestformat);
    }
    *ptr = CONT_CMD_END;
}
