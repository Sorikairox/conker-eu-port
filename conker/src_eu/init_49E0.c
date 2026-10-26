#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// contains jr
/* P7: UNVERIFIED-difftest (infinite loop: UNSURE by construction; no difference over 10 trials with DIFFTEST_OUTPARAMS=1), needs runtime check */
/* scheduler thread (sched.c-style): retrace / SP done / DP done / pre-NMI / controller messages */
typedef struct SchedClient {
    /* 0x00 */ struct SchedClient *next;
    /* 0x04 */ OSMesgQueue *msgQ;
    /* 0x08 */ s32 flags;            /* bit 0: does not want retrace messages */
} SchedClient;
extern OSViMode g_vi_mode;          /* the active VI mode (PAL timing tweak below); was D_8002AF20 */
extern OSTimer g_sched_audio_timer;           /* gfx task timeout timer; was D_8003A8E8 */
extern u16 g_sched_thread_state; /* was D_8003A928 */
void framebuffer_fill_color(s32 arg0, s32 arg1, s32 arg2);
void sched_try_start_gfx_task(void);

/* was func_100049E0 */
void sched_thread_main(s32 arg0) {
    OSMesg msg;
    SchedClient *client;
    OSTime countdown;

    g_sched_audio_running = 0;
    g_sched_gfx_state = 0;
    g_sched_dp_done = 1;
    g_sched_gfx_running = 0;
    *(u16 *)&g_sched_retrace_msg = 1;         /* retrace message */
    msg = 0;
    g_sched_thread_state = 4;

    for (;;) {
        osRecvMesg(&g_sched_event_queue_alias, &msg, OS_MESG_BLOCK);
        /* an if chain, not a switch: difftest mis-ran IDO's jump table here; see P7.md */
        if ((u32)msg == 0) { /* retrace */
            if (g_eeprom_writes_disabled != 0) {
                g_vi_mode.comRegs.hStart = 0x8C02D5;
                g_vi_mode.comRegs.xScale = 0x200;
                g_vi_mode.fldRegs[0].yScale = 0x400;
                g_vi_mode.fldRegs[1].yScale = 0x400;
                g_vi_mode.fldRegs[0].vStart = 0x3D01E8;
                g_vi_mode.fldRegs[1].vStart = 0x3D01E8;
                framebuffer_fill_color(0, 0, 0);
            }
            for (client = (SchedClient *)g_sched_clients; client != NULL; client = client->next) {
                if (!(client->flags & 1)) {
                    osSendMesg(client->msgQ, (OSMesg)&g_sched_retrace_msg, OS_MESG_NOBLOCK);
                }
            }
            if (g_sched_retrace_count != 0xFF) {
                g_sched_retrace_count++;
            }
            if (g_sched_retrace_hold != 0) {
                g_sched_retrace_hold--;
            }
            if (g_sched_audio_running == 0 && g_sched_audio_timer_armed == 0 &&
                osRecvMesg(&g_sched_audio_queue_alias, (OSMesg *)&g_sched_audio_task, OS_MESG_NOBLOCK) == 0) {
                countdown = 200000;
                if (g_sched_gfx_state != 0 || (s32)osAiGetStatus() >= 0) {
                    countdown = 20000;
                }
                osSetTimer(&g_sched_audio_timer, countdown, 0, &g_sched_event_queue_alias, (OSMesg)3);
                g_sched_audio_timer_armed = 1;
            }
            if (g_sched_audio_running == 0) {
                sched_try_start_gfx_task();
            }
        } else if ((u32)msg == 1) {
            g_sched_dp_done = 1;
            if (g_sched_gfx_running == 0) {
                sched_try_swap_buffer();
            }
        } else if ((u32)msg == 2) { /* SP task done */
            if (g_sched_gfx_state == 3) {
                if (osSpTaskYielded(&g_sched_gfx_task->list) == 1) {
                    osSpTaskLoad(&g_sched_audio_task->list);
                    osSpTaskStartGo(&g_sched_audio_task->list);
                    g_sched_audio_running = 1;
                    g_sched_gfx_state = 4;
                } else {
                    g_sched_gfx_state = 1;
                    osSpTaskLoad(&g_sched_audio_task->list);
                    osSpTaskStartGo(&g_sched_audio_task->list);
                    g_sched_audio_running = 1;
                    g_sched_gfx_running = 0;
                }
            } else if (g_sched_audio_running != 0) {
                osSendMesg(g_sched_audio_task->msgQ, g_sched_audio_task->msg, OS_MESG_BLOCK);
                g_sched_audio_running = 0;
                if (g_sched_gfx_state == 4) {
                    osSpTaskLoad(&g_sched_gfx_task->list);
                    osSpTaskStartGo(&g_sched_gfx_task->list);
                    g_sched_gfx_resumed = 1;
                    g_sched_gfx_state = 1;
                }
            } else {
                g_sched_gfx_running = 0;
                if (g_sched_dp_done == 1) {
                    sched_try_swap_buffer();
                }
            }
        } else if ((u32)msg == 3) { /* gfx task timeout */
            g_sched_audio_timer_armed = 0;
            if (g_sched_gfx_running != 0) {
                osSpTaskYield();
                g_sched_gfx_state = 3;
            } else {
                osSpTaskLoad(&g_sched_audio_task->list);
                osSpTaskStartGo(&g_sched_audio_task->list);
                g_sched_audio_running = 1;
            }
        } else if ((u32)msg == 6) { /* controller read */
            if (g_eeprom_writes_disabled == 0) {
                osContStartReadData(&g_si_mesg_queue);
            }
        }
    }
}
// void sched_thread_main(s32 arg0) {
//     u32 sp64;
//     s32 sp5C;
//     s32 sp58;
//     u8 temp_v0;
//     u8 temp_v0_2;
//     void *temp_s0;
//     void *temp_s0_2;
//     void *temp_v0_3;
//     void *phi_s0;
//
//     g_sched_audio_running = (u8)0U;
//     g_sched_gfx_state = (u8)0U;
//     g_sched_dp_done = (u8)1U;
//     g_sched_gfx_running = (u8)0U;
//     g_sched_retrace_msg = (u16)1;
//     sp64 = 0;
//     D_8003A5C8 = (u16)4;
// default:
// loop_1:
//     osRecvMesg(&g_sched_event_queue_alias, &sp64, (u16)1);
//     if (sp64 >= 7U) {
//         goto loop_1;
//     }
//     goto **(&jtbl_8002C0A0 + (sp64 * 4));
// case 0:
//     temp_s0 = g_sched_clients;
//     phi_s0 = temp_s0;
//     if (temp_s0 != 0) {
// loop_4:
//         if ((phi_s0->unk8 & 1) == 0) {
//             osSendMesg(phi_s0->unk4, g_sched_retrace_msg, 0);
//         }
//         temp_s0_2 = phi_s0->unk0;
//         phi_s0 = temp_s0_2;
//         if (temp_s0_2 != 0) {
//             goto loop_4;
//         }
//     }
//     temp_v0 = g_sched_retrace_count;
//     if ((temp_v0 != 0xFF) && ((s32) temp_v0 < 0xFF)) {
//         g_sched_retrace_count = (s8) (temp_v0 + 1);
//     }
//     temp_v0_2 = g_sched_retrace_hold;
//     if (temp_v0_2 != 0) {
//         g_sched_retrace_hold = (s8) (temp_v0_2 - 1);
//     }
//     if ((g_sched_audio_running == 0) && (g_sched_audio_timer_armed == 0) && (osRecvMesg(&g_sched_audio_queue_alias, &g_sched_audio_task, 0) == 0)) {
//         sp5C = 0x30D40;
//         sp58 = 0;
//         if ((g_sched_gfx_state != 0) || ((osAiGetStatus() << 0) >= 0)) {
//             sp5C = 20000;
//             sp58 = 0;
//         }
//         osSetTimer(&D_8003A588, 0, 0, &g_sched_event_queue_alias, 3);
//         g_sched_audio_timer_armed = (s8) (u16)1;
//     }
//     if (g_sched_audio_running != 0) {
//         goto loop_1;
//     }
//     sched_try_start_gfx_task();
//     goto loop_1;
// case 2:
//     if (g_sched_gfx_state == 3) {
//         if (osSpTaskYielded(g_sched_gfx_task->osTask) == (u8)1U) {
//             osSpTaskLoad(g_sched_audio_task->list);
//             osSpTaskStartGo(g_sched_audio_task->list);
//             g_sched_audio_running = (u8)1U;
//             g_sched_gfx_state = (u8)4U;
//         } else {
//             g_sched_gfx_state = (u8)1U;
//             osSpTaskLoad(g_sched_audio_task->list);
//             osSpTaskStartGo(g_sched_audio_task->list);
//             g_sched_audio_running = (u8)1U;
//             g_sched_gfx_running = (u8)0U;
//         }
//     } else if (g_sched_audio_running != 0) {
//         temp_v0_3 = g_sched_audio_task;
//         osSendMesg(temp_v0_3->unk58, temp_v0_3->unk5C, (u16)1);
//         g_sched_audio_running = (u8)0U;
//         if (g_sched_gfx_state != 4) {
//             goto loop_1;
//         }
//         osSpTaskLoad(g_sched_gfx_task->osTask);
//         osSpTaskStartGo(g_sched_gfx_task->osTask);
//         g_sched_gfx_resumed = (s8) (u16)1;
//         g_sched_gfx_state = (u8)1U;
//     } else {
//         g_sched_gfx_running = (u8)0U;
//         if ((u16)1 != g_sched_dp_done) {
//             goto loop_1;
//         }
//         sched_try_swap_buffer();
//         goto loop_1;
//     case 1:
//         g_sched_dp_done = (u8)1U;
//         if (g_sched_gfx_running != 0) {
//             goto loop_1;
//         }
//         sched_try_swap_buffer();
//         goto loop_1;
//     case 3:
//         g_sched_audio_timer_armed = (u8)0;
//         if (g_sched_gfx_running != 0) {
//             osSpTaskYield();
//             g_sched_gfx_state = (u8)3U;
//         } else {
//             osSpTaskLoad(g_sched_audio_task->list);
//             osSpTaskStartGo(g_sched_audio_task->list);
//             g_sched_audio_running = (u8)1U;
//             goto loop_1;
//         case 6:
//             if (g_eeprom_writes_disabled != 0) {
//                 goto loop_1;
//             }
//             osContStartReadData(&g_si_mesg_queue);
//         }
//     }
//     goto loop_1;
// }

void *os_vi_get_next_framebuffer();
/* was func_10004DB0 */
void sched_try_start_gfx_task(void) {
    if (g_sched_gfx_state == 0) {
        if (osRecvMesg(&g_sched_gfx_queue_alias, (OSMesg *)&g_sched_gfx_task, 0) == 0) {
            if ((osViGetCurrentFramebuffer() != g_sched_gfx_task->framebuffer) &&
                (os_vi_get_next_framebuffer() != g_sched_gfx_task->framebuffer) &&
                ((g_sched_retrace_hold == 0) || (g_sched_retrace_count >= g_sched_frame_retraces))) {
                if (g_sched_retrace_count != 255) {
                    if ((g_sched_retrace_count >= g_sched_frame_retraces) || (g_sched_retrace_hold == 0)) {
                        g_sched_frame_retraces = g_sched_retrace_count;
                    }
                }
                sched_start_gfx_task();
            } else {
                g_sched_gfx_state = 2;
            }
        }
    } else if (g_sched_gfx_state == 2) {
        if ((g_sched_retrace_hold == 0) || (g_sched_retrace_count >= g_sched_frame_retraces)) {
            sched_start_gfx_task();
        }
    } else if (g_sched_gfx_state == 6) {
        sched_try_swap_buffer();
    }
}
// NON-MATCHING: branching is not right
// void sched_try_start_gfx_task(void) {
//     if (g_sched_gfx_state == 0) {
//         if (osRecvMesg(&g_sched_gfx_queue_alias, &g_sched_gfx_task, 0) == 0) {
//             if ((osViGetCurrentFramebuffer() == g_sched_gfx_task->framebuffer) ||
//                 (osViGetNextFramebuffer() == g_sched_gfx_task->framebuffer) ||
//                 ((g_sched_retrace_hold != 0) && (g_sched_retrace_count < g_sched_frame_retraces))) {
//                 g_sched_gfx_state = 2;
//             } else {
//                 if (g_sched_retrace_count != 255) {
//                     if ((g_sched_retrace_count >= g_sched_frame_retraces) || (g_sched_retrace_hold == 0)) {
//                         g_sched_frame_retraces = g_sched_retrace_count;
//                     }
//                 }
//                 sched_start_gfx_task();
//             }
//         }
//     } else if (g_sched_gfx_state == 2) {
//         if ((g_sched_retrace_hold == 0) || ( g_sched_retrace_count >= g_sched_frame_retraces)) {
//             sched_start_gfx_task();
//         }
//     } else if (g_sched_gfx_state == 6) {
//         sched_try_swap_buffer();
//     }
// }

/* was func_10004F00 */
void sched_start_gfx_task(void) {
    if (g_eeprom_writes_disabled == 0) {
        osSpTaskLoad(&g_sched_gfx_task->list);
        osSpTaskStartGo(&g_sched_gfx_task->list);
        g_sched_gfx_resumed = 0;
        g_sched_last_gfx_task = g_sched_gfx_task;
        g_sched_gfx_running = 1;
        g_sched_dp_done = 0;
        if ((g_sched_retrace_count == 255) ||
            ((g_sched_retrace_count >= 11) && ((g_sched_retrace_count >= 21) || (g_cutscene_slot_state != 1)))) {
            g_sched_retrace_count = 2;
        }
        g_frame_ticks = g_sched_retrace_count;
        g_sched_retrace_count = 0 ;
        g_sched_gfx_state = 1;
        osSendMesg(g_sched_client_queue, &g_sched_retrace_msg, 0);
    }
}

/* was func_10004FE0 */
void sched_try_swap_buffer(void) {
    if (g_sched_retrace_count <= 0) {
        g_sched_gfx_state = 6;
    } else {
        sched_swap_framebuffer();
    }
}

extern u8 D_eu_8002AFA8;
// func_1515FDA0 is the US name of EU fb_fx_apply_all (undefined_syms alias); the port has only the EU symbol
void fb_fx_apply_all(u16 *);
#define func_1515FDA0 fb_fx_apply_all
extern s8 D_eu_8002AE24;

/* was func_10005020 */
void sched_swap_framebuffer(void) {
    void *fb;

    g_sched_gfx_state = 0;
    fb = g_sched_gfx_task->framebuffer;
    if ((g_sched_gfx_task->flags & OS_SC_SWAPBUFFER) && (g_eeprom_writes_disabled == 0)) {
        func_1515FDA0(fb);
        // EU: blank the VI once before the first swap
        if (D_eu_8002AFA8 == 0) {
            osViBlack(FALSE);
            D_eu_8002AFA8 = 1;
        }
        osViSwapBuffer(fb);
        D_eu_8002AE24 = 1;
    }
    osSendMesg(g_sched_gfx_task->msgQ, g_sched_gfx_task->msg, 1);
}
