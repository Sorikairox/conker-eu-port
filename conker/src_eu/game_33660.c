#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150061B0 */
void controller_init_si_queue(void) {
    osCreateMesgQueue(&g_si_mesg_queue, &g_si_mesg_buf, 8);
    osSetEventMesg(OS_EVENT_SI, &g_si_mesg_queue, g_si_event_mesg);
    g_cont_pad_ptrs.unk0 = &D_800BE748;
    g_cont_pad_ptrs.unk4 = &g_cont_pad1;
    g_cont_pad_ptrs.unk8 = &g_cont_pad2;
    g_cont_pad_ptrs.unkC = &g_cont_pad3;
    controller_init_hook_noop();
}

s32 os_motor_stop(u8 *);
s32 os_motor_init(void *, void *, int);
s32 os_pfs_init(void *, void *, int);
extern s8 D_8002AE14;
extern OSContStatus g_cont_status; /* was D_800BE6E0 */
extern s32 g_cont_count; /* was D_800BEB4C */
extern u8 D_800BEB60;
extern s32 D_800BEB80;
extern s8 D_800BED60;
extern s8 D_800BED64;
extern s8 D_800BED68;
extern f32 D_800BED70;
extern f32 D_800BED80;
extern f32 D_800BED90;
extern f32 D_800BEDA0;

/* was func_15006234 */
void controller_init_all(void) {
    struct {
        u8 u8F;
    } sp;
    f32 *sp6C;
    f32 *sp68;
    u16 *sp60;
    f32 *var_a3;
    f32 *var_fp;
    f32 *var_s7;
    f32 *var_t0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s6;
    s8 *var_s2;
    s8 *var_s4;
    s8 *var_s5;
    u16 *var_t1;
    u8 *var_s3;
    u8 *temp_s1;
    u8 *temp_v0;

    if (osContInit(&g_si_mesg_queue, &sp.u8F, &g_cont_status) != 0) {
        do {

        } while (osContInit(&g_si_mesg_queue, &sp.u8F, &g_cont_status) != 0);
    }
    g_cont_count = 0;
    var_t1 = D_800BE720;
    var_t0 = &D_800BEDA0;
    var_a3 = &D_800BED90;
    var_fp = &D_800BED80;
    var_s7 = &D_800BED70;
    var_s5 = &D_800BED68;
    var_s4 = &D_800BED60;
    var_s3 = D_800BED5C;
    var_s2 = &D_800BED64;
    var_s0 = 0;
    var_s6 = 0;
    do {
        temp_v1 = 1 << var_s0;
        *var_s2 = 0;
        *var_s3 = 0;
        *var_s4 = 0;
        *var_s5 = 0;
        *var_s7 = 0.0f;
        *var_fp = 1.0f;
        *var_a3 = 1.0f;
        *var_t0 = 1.0f + 1.0f;
        *var_t1 = 0;
        if (sp.u8F & temp_v1) {
            temp_v0 = ((OSContStatus *)((u8 *)&g_cont_status + var_s6));
            if (!((*(u8 *)((u8 *)temp_v0 + 3)) & 8)) {
                D_800BEB60 |= temp_v1;
                g_cont_count += 1;
                if (((*(u16 *)((u8 *)temp_v0 + 0)) & 4) && ((*(u8 *)((u8 *)temp_v0 + 2)) & 1) && ((temp_s1 = ((s32 *)((u8 *)&D_800BEB80 + (var_s0 * 0x68))), sp6C = var_a3, sp68 = var_t0, sp60 = var_t1, temp_v0_2 = os_pfs_init(&g_si_mesg_queue, temp_s1, var_s0), (temp_v0_2 == 0xA)) || (temp_v0_2 == 0xB))) {
                    sp6C = var_a3;
                    sp68 = var_t0;
                    sp60 = var_t1;
                    temp_v0_3 = os_motor_init(&g_si_mesg_queue, temp_s1, var_s0);
                    if (temp_v0_3 == 0) {
                        *var_s2 = 1;
                        sp6C = var_a3;
                        sp68 = var_t0;
                        sp60 = var_t1;
                        os_motor_stop(temp_s1);
                    }
                }
            }
        }
        var_s0 += 1;
        var_s2 += 1;
        var_s3 += 1;
        var_s4 += 1;
        var_s5 += 1;
        var_s6 += 4;
        var_s7 = (f32 *)((u8 *)var_s7 + (4));
        var_fp = (f32 *)((u8 *)var_fp + (4));
        var_a3 = (f32 *)((u8 *)var_a3 + (4));
        var_t0 = (f32 *)((u8 *)var_t0 + (4));
        var_t1 = (u16 *)((u8 *)var_t1 + (2));
    } while (var_s0 != 4);
    D_8002AE14 = 1;
}