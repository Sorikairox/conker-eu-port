#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// contains jr
#ifdef NON_MATCHING
/* P7: UNVERIFIED-difftest (infinite loop: UNSURE by construction; no difference over 10 trials with DIFFTEST_OUTPARAMS=1), needs runtime check */
/* scheduler thread (sched.c-style): retrace / SP done / DP done / pre-NMI / controller messages */
typedef struct SchedClient {
    /* 0x00 */ struct SchedClient *next;
    /* 0x04 */ OSMesgQueue *msgQ;
    /* 0x08 */ s32 flags;            /* bit 0: does not want retrace messages */
} SchedClient;
extern OSViMode D_8002AF20;          /* the active VI mode (PAL timing tweak below) */
extern OSTimer D_8003A8E8;           /* gfx task timeout timer */
extern u16 D_8003A928;
void func_10003ACC(s32 arg0, s32 arg1, s32 arg2);
void func_10004DB0(void);

void func_100049E0(s32 arg0) {
    OSMesg msg;
    SchedClient *client;
    OSTime countdown;

    D_8003A581 = 0;
    D_8003A582 = 0;
    D_8003A584 = 1;
    D_8003A583 = 0;
    *(u16 *)&D_8003B240 = 1;         /* retrace message */
    msg = 0;
    D_8003A928 = 4;

    for (;;) {
        osRecvMesg(&D_8003B218, &msg, OS_MESG_BLOCK);
        /* an if chain, not a switch: difftest mis-ran IDO's jump table here; see P7.md */
        if ((u32)msg == 0) { /* retrace */
            if (D_8002AC5C != 0) {
                D_8002AF20.comRegs.hStart = 0x8C02D5;
                D_8002AF20.comRegs.xScale = 0x200;
                D_8002AF20.fldRegs[0].yScale = 0x400;
                D_8002AF20.fldRegs[1].yScale = 0x400;
                D_8002AF20.fldRegs[0].vStart = 0x3D01E8;
                D_8002AF20.fldRegs[1].vStart = 0x3D01E8;
                func_10003ACC(0, 0, 0);
            }
            for (client = (SchedClient *)D_8003B234; client != NULL; client = client->next) {
                if (!(client->flags & 1)) {
                    osSendMesg(client->msgQ, (OSMesg)&D_8003B240, OS_MESG_NOBLOCK);
                }
            }
            if (D_8003B238 != 0xFF) {
                D_8003B238++;
            }
            if (D_8003B23A != 0) {
                D_8003B23A--;
            }
            if (D_8003A581 == 0 && D_8002AC6C == 0 &&
                osRecvMesg(&D_8003B200, (OSMesg *)&D_8002AC54, OS_MESG_NOBLOCK) == 0) {
                countdown = 200000;
                if (D_8003A582 != 0 || (s32)osAiGetStatus() >= 0) {
                    countdown = 20000;
                }
                osSetTimer(&D_8003A8E8, countdown, 0, &D_8003B218, (OSMesg)3);
                D_8002AC6C = 1;
            }
            if (D_8003A581 == 0) {
                func_10004DB0();
            }
        } else if ((u32)msg == 1) {
            D_8003A584 = 1;
            if (D_8003A583 == 0) {
                func_10004FE0();
            }
        } else if ((u32)msg == 2) { /* SP task done */
            if (D_8003A582 == 3) {
                if (osSpTaskYielded(&D_8002AC50->list) == 1) {
                    osSpTaskLoad(&D_8002AC54->list);
                    osSpTaskStartGo(&D_8002AC54->list);
                    D_8003A581 = 1;
                    D_8003A582 = 4;
                } else {
                    D_8003A582 = 1;
                    osSpTaskLoad(&D_8002AC54->list);
                    osSpTaskStartGo(&D_8002AC54->list);
                    D_8003A581 = 1;
                    D_8003A583 = 0;
                }
            } else if (D_8003A581 != 0) {
                osSendMesg(D_8002AC54->msgQ, D_8002AC54->msg, OS_MESG_BLOCK);
                D_8003A581 = 0;
                if (D_8003A582 == 4) {
                    osSpTaskLoad(&D_8002AC50->list);
                    osSpTaskStartGo(&D_8002AC50->list);
                    D_8003A580 = 1;
                    D_8003A582 = 1;
                }
            } else {
                D_8003A583 = 0;
                if (D_8003A584 == 1) {
                    func_10004FE0();
                }
            }
        } else if ((u32)msg == 3) { /* gfx task timeout */
            D_8002AC6C = 0;
            if (D_8003A583 != 0) {
                osSpTaskYield();
                D_8003A582 = 3;
            } else {
                osSpTaskLoad(&D_8002AC54->list);
                osSpTaskStartGo(&D_8002AC54->list);
                D_8003A581 = 1;
            }
        } else if ((u32)msg == 6) { /* controller read */
            if (D_8002AC5C == 0) {
                osContStartReadData(&D_800BE900);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_49E0/func_100049E0.s")
#endif
// void func_100049E0(s32 arg0) {
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
//     D_8003A581 = (u8)0U;
//     D_8003A582 = (u8)0U;
//     D_8003A584 = (u8)1U;
//     D_8003A583 = (u8)0U;
//     D_8003B240 = (u16)1;
//     sp64 = 0;
//     D_8003A5C8 = (u16)4;
// default:
// loop_1:
//     osRecvMesg(&D_8003B218, &sp64, (u16)1);
//     if (sp64 >= 7U) {
//         goto loop_1;
//     }
//     goto **(&jtbl_8002C0A0 + (sp64 * 4));
// case 0:
//     temp_s0 = D_8003B234;
//     phi_s0 = temp_s0;
//     if (temp_s0 != 0) {
// loop_4:
//         if ((phi_s0->unk8 & 1) == 0) {
//             osSendMesg(phi_s0->unk4, D_8003B240, 0);
//         }
//         temp_s0_2 = phi_s0->unk0;
//         phi_s0 = temp_s0_2;
//         if (temp_s0_2 != 0) {
//             goto loop_4;
//         }
//     }
//     temp_v0 = D_8003B238;
//     if ((temp_v0 != 0xFF) && ((s32) temp_v0 < 0xFF)) {
//         D_8003B238 = (s8) (temp_v0 + 1);
//     }
//     temp_v0_2 = D_8003B23A;
//     if (temp_v0_2 != 0) {
//         D_8003B23A = (s8) (temp_v0_2 - 1);
//     }
//     if ((D_8003A581 == 0) && (D_8002AC6C == 0) && (osRecvMesg(&D_8003B200, &D_8002AC54, 0) == 0)) {
//         sp5C = 0x30D40;
//         sp58 = 0;
//         if ((D_8003A582 != 0) || ((osAiGetStatus() << 0) >= 0)) {
//             sp5C = 20000;
//             sp58 = 0;
//         }
//         osSetTimer(&D_8003A588, 0, 0, &D_8003B218, 3);
//         D_8002AC6C = (s8) (u16)1;
//     }
//     if (D_8003A581 != 0) {
//         goto loop_1;
//     }
//     func_10004DB0();
//     goto loop_1;
// case 2:
//     if (D_8003A582 == 3) {
//         if (osSpTaskYielded(D_8002AC50->osTask) == (u8)1U) {
//             osSpTaskLoad(D_8002AC54->list);
//             osSpTaskStartGo(D_8002AC54->list);
//             D_8003A581 = (u8)1U;
//             D_8003A582 = (u8)4U;
//         } else {
//             D_8003A582 = (u8)1U;
//             osSpTaskLoad(D_8002AC54->list);
//             osSpTaskStartGo(D_8002AC54->list);
//             D_8003A581 = (u8)1U;
//             D_8003A583 = (u8)0U;
//         }
//     } else if (D_8003A581 != 0) {
//         temp_v0_3 = D_8002AC54;
//         osSendMesg(temp_v0_3->unk58, temp_v0_3->unk5C, (u16)1);
//         D_8003A581 = (u8)0U;
//         if (D_8003A582 != 4) {
//             goto loop_1;
//         }
//         osSpTaskLoad(D_8002AC50->osTask);
//         osSpTaskStartGo(D_8002AC50->osTask);
//         D_8003A580 = (s8) (u16)1;
//         D_8003A582 = (u8)1U;
//     } else {
//         D_8003A583 = (u8)0U;
//         if ((u16)1 != D_8003A584) {
//             goto loop_1;
//         }
//         func_10004FE0();
//         goto loop_1;
//     case 1:
//         D_8003A584 = (u8)1U;
//         if (D_8003A583 != 0) {
//             goto loop_1;
//         }
//         func_10004FE0();
//         goto loop_1;
//     case 3:
//         D_8002AC6C = (u8)0;
//         if (D_8003A583 != 0) {
//             osSpTaskYield();
//             D_8003A582 = (u8)3U;
//         } else {
//             osSpTaskLoad(D_8002AC54->list);
//             osSpTaskStartGo(D_8002AC54->list);
//             D_8003A581 = (u8)1U;
//             goto loop_1;
//         case 6:
//             if (D_8002AC5C != 0) {
//                 goto loop_1;
//             }
//             osContStartReadData(&D_800BE900);
//         }
//     }
//     goto loop_1;
// }

void *func_10025210();
void func_10004DB0(void) {
    if (D_8003A582 == 0) {
        if (osRecvMesg(&D_8003B1E8, (OSMesg *)&D_8002AC50, 0) == 0) {
            if ((osViGetCurrentFramebuffer() != D_8002AC50->framebuffer) &&
                (func_10025210() != D_8002AC50->framebuffer) &&
                ((D_8003B23A == 0) || (D_8003B238 >= D_8003B239))) {
                if (D_8003B238 != 255) {
                    if ((D_8003B238 >= D_8003B239) || (D_8003B23A == 0)) {
                        D_8003B239 = D_8003B238;
                    }
                }
                func_10004F00();
            } else {
                D_8003A582 = 2;
            }
        }
    } else if (D_8003A582 == 2) {
        if ((D_8003B23A == 0) || (D_8003B238 >= D_8003B239)) {
            func_10004F00();
        }
    } else if (D_8003A582 == 6) {
        func_10004FE0();
    }
}
// NON-MATCHING: branching is not right
// void func_10004DB0(void) {
//     if (D_8003A582 == 0) {
//         if (osRecvMesg(&D_8003B1E8, &D_8002AC50, 0) == 0) {
//             if ((osViGetCurrentFramebuffer() == D_8002AC50->framebuffer) ||
//                 (osViGetNextFramebuffer() == D_8002AC50->framebuffer) ||
//                 ((D_8003B23A != 0) && (D_8003B238 < D_8003B239))) {
//                 D_8003A582 = 2;
//             } else {
//                 if (D_8003B238 != 255) {
//                     if ((D_8003B238 >= D_8003B239) || (D_8003B23A == 0)) {
//                         D_8003B239 = D_8003B238;
//                     }
//                 }
//                 func_10004F00();
//             }
//         }
//     } else if (D_8003A582 == 2) {
//         if ((D_8003B23A == 0) || ( D_8003B238 >= D_8003B239)) {
//             func_10004F00();
//         }
//     } else if (D_8003A582 == 6) {
//         func_10004FE0();
//     }
// }

void func_10004F00(void) {
    if (D_8002AC5C == 0) {
        osSpTaskLoad(&D_8002AC50->list);
        osSpTaskStartGo(&D_8002AC50->list);
        D_8003A580 = 0;
        D_8002AC58 = D_8002AC50;
        D_8003A583 = 1;
        D_8003A584 = 0;
        if ((D_8003B238 == 255) ||
            ((D_8003B238 >= 11) && ((D_8003B238 >= 21) || (D_800C35EA != 1)))) {
            D_8003B238 = 2;
        }
        D_800BE9E4 = D_8003B238;
        D_8003B238 = 0 ;
        D_8003A582 = 1;
        osSendMesg(D_8003B230, &D_8003B240, 0);
    }
}

void func_10004FE0(void) {
    if (D_8003B238 <= 0) {
        D_8003A582 = 6;
    } else {
        func_10005020();
    }
}

extern u8 D_eu_8002AFA8;
extern s8 D_eu_8002AE24;

void func_10005020(void) {
    void *fb;

    D_8003A582 = 0;
    fb = D_8002AC50->framebuffer;
    if ((D_8002AC50->flags & OS_SC_SWAPBUFFER) && (D_8002AC5C == 0)) {
        func_1515FDA0(fb);
        // EU: blank the VI once before the first swap
        if (D_eu_8002AFA8 == 0) {
            osViBlack(FALSE);
            D_eu_8002AFA8 = 1;
        }
        osViSwapBuffer(fb);
        D_eu_8002AE24 = 1;
    }
    osSendMesg(D_8002AC50->msgQ, D_8002AC50->msg, 1);
}
