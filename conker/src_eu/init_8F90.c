#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void snd_cache_flush_unused(void);
void heap_free(s32);
extern s32 g_snd_cache_flush_request; /* was D_8003E724 */

typedef struct AMDMABuffer_s {
    ALLink node;
    u32 startAddr;
    u32 lastFrame;
    char *ptr;
} AMDMABuffer;
typedef struct {
    u8 initialized;
    AMDMABuffer *firstUsed;
    AMDMABuffer *firstFree;
} AMDMAState;
#define dmaState (*(AMDMAState *)&g_audio_dma_state)
extern u32 g_audio_frame_count; /* was D_8002B194 */
extern u32 g_audio_dma_count; /* was D_8002B198 */
extern OSMesgQueue g_audio_dma_queue; /* was D_80041638 */
extern OSIoMesg g_audio_dma_io_msgs[]; /* was D_80041338 */
typedef struct { s16 type; s16 pad; void *data; } AmMsg;
extern OSMesgQueue g_audio_frame_queue; /* was D_8003E970 */
extern OSMesgQueue g_audio_reply_queue; /* was D_8003E9A8 */
extern s32 g_audio_al_globals; /* was D_8003E9E0 */
extern void *g_audio_mgr_audio_info[]; /* was D_8003E730 */
extern u32 g_audio_frame_count; /* was D_8002B194 */
s32 audio_do_frame();
struct AudTask {
        void *next;
        u32 state;
        u32 unk8;
        u32 flags;
        void *framebuffer;
        u32 unk14;
        OSTask list;
        OSMesgQueue *msgQ;
        OSMesg msg;
    };
typedef struct {
    s16 *data;
    s16 *unk4;
    s16 frameSamples;
    s16 pad;
    s32 padC;
    struct AudTask task;
    s32 unk70;
} AudioInfo;
extern u8 g_audio_short_frame_hold; /* was D_80041324 */
extern s32 g_audio_frame_samples_short; /* was D_80041328 */
extern s32 g_audio_frame_samples; /* was D_8004132C */
extern u32 g_audio_cmdlist_index; /* was D_8002B19C */
extern Acmd *g_audio_mgr[]; /* was D_8003E728 */
extern OSMesgQueue g_sched_audio_queue; /* was D_8003B560 */
extern u8 g_rspboot_text[]; /* was D_10029400 */
extern u8 g_rspboot_text_end[]; /* was D_100294D0 */
extern u8 g_audio_ucode_data[]; /* was D_8002CCC0 */
void audio_clear_dma(void);
void snd_cache_update_dmas(void);
Acmd *n_alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen);


typedef struct {
    s32 maxVVoices;
    s32 maxPVoices;
    s32 maxUpdates;
    s32 maxFXbusses;
    void *dmaproc;
    void *unk14;
    void *unk18;
    void *unk1C;
    void *unk20;
    s32 unk24;
    ALHeap *heap;
    s32 outputRate;
    u8 fxTypes[4];
    s32 *params[2];
} AmSynConfig;
typedef struct {
    s32 frequency;
    u32 unk4;
    u32 unk8;
} AmConfig;
typedef struct {
    s32 bus0[0x42];
    s32 bus1[0x42];
} AmFxParams;
typedef struct AmUnk18_s {
    ALLink node;
    u32 unk8;
    u32 unkC;
    u32 unk10;
    u32 unk14;
} AmUnk18;
typedef struct {
    s16 *data;
    u8 pad4[0x70 - 0x4];
    s16 type;
    void *info;
    u8 pad78[0x90 - 0x78];
} AmAudioInfo;
extern AmFxParams g_audio_fx_params; /* was D_8002B1A4 */
extern u8 g_audio_heap[]; /* was D_8003E710 */
extern void *g_audio_al_globals_ptr; /* was D_8003E720 */
#define dmaBuffs ((AMDMABuffer *) &g_audio_dma_buffers)
#define amUnk18Buffs ((AmUnk18 *) &g_snd_cache_dma_bufs)
extern u32 g_audio_frame_buf_samples; /* was D_80041330 */
extern u32 g_audio_cmdlist_len; /* was D_80041334 */
typedef struct {
    Acmd *ACMDList[2];
    AmAudioInfo *audioInfo[3];
} AmMgr;
#define __am (*(AmMgr *) g_audio_mgr)
#define AM_LINK(ln, to) \
    (ln)->next = (to)->next; \
    (ln)->prev = (to); \
    if ((to)->next) (to)->next->prev = (ln); \
    (to)->next = (ln);
extern OSMesg g_audio_reply_msgs[]; /* was D_8003E9C0 */
extern OSMesg g_audio_frame_msgs[]; /* was D_8003E988 */
extern OSMesg g_audio_dma_msgs[]; /* was D_80041650 */
extern OSMesgQueue g_snd_cache_dma_queue; /* was D_80041A90 */
extern OSMesg g_snd_cache_dma_msgs[]; /* was D_80041AA8 */
extern OSThread g_audio_thread; /* was D_8003E3A0 */
extern u8 g_audio_thread_started; /* was D_8002AE40 */
s32 snd_cache_dma_new(void);

/* was func_10008F90 */
void audio_mgr_init(AmSynConfig *c, OSPri pri, AmConfig *arg2) {
    u32 i;
    u32 n;
    f32 fsize;
    AmFxParams params;

    mp3_voice_init((s32) g_audio_heap);
    c->dmaproc = audio_dma_new;
    c->outputRate = osAiSetFrequency(arg2->frequency);
    c->unk14 = snd_cache_dma_new;
    c->unk18 = snd_cache_entry_unref;
    c->unk1C = snd_cache_entry_ref;
    c->unk20 = snd_cache_entry_release;

    /* Samples per frame (25 fps), rounded up to a multiple of 184 plus one more block. */
    fsize = arg2->unk4 * (f32) c->outputRate / 25.0f;
    n = (s32) fsize;
    g_audio_frame_samples = n;
    if ((f32) n < fsize) {
        n++;
        g_audio_frame_samples = n;
    }
    n = (n / 184) * 184 + 184;
    g_audio_frame_samples = n;
    g_audio_frame_samples_short = n - 184;
    g_audio_frame_buf_samples = n + 84;
    g_audio_short_frame_hold = 0;

    params = g_audio_fx_params;
    c->params[0] = params.bus0;
    c->params[1] = params.bus1;
    n_alInit((void *) &g_audio_al_globals, (s32) c);
    g_audio_al_globals_ptr = &g_audio_al_globals;

    dmaBuffs[0].node.prev = 0;
    dmaBuffs[0].node.next = 0;

    for (i = 0; i < 51; i++) {
        AM_LINK((ALLink *) &dmaBuffs[i + 1], (ALLink *) &dmaBuffs[i]);
        dmaBuffs[i].ptr = alHeapAlloc(c->heap, 1, 0x800);
    }
    dmaBuffs[i].ptr = alHeapAlloc(c->heap, 1, 0x800);

    bzero(amUnk18Buffs, 1200);
    amUnk18Buffs[0].node.prev = 0;
    amUnk18Buffs[0].node.next = 0;
    for (i = 0; i < 49; i++) {
        {
            ALLink *ln = (ALLink *) &amUnk18Buffs[i + 1];
            ALLink *to = (ALLink *) &amUnk18Buffs[i];
            AM_LINK(ln, to);
        }
        amUnk18Buffs[i].unk10 = 0;
    }
    amUnk18Buffs[i].unk10 = 0;

    for (i = 0; i < 2; i++) {
        __am.ACMDList[i] = alHeapAlloc(c->heap, 1, arg2->unk8 * 8);
    }
    g_audio_cmdlist_len = arg2->unk8;

    for (i = 0; i < 3; i++) {
        __am.audioInfo[i] = alHeapAlloc(c->heap, 1, sizeof(AmAudioInfo));
        __am.audioInfo[i]->type = 2;
        __am.audioInfo[i]->info = __am.audioInfo[i];
        __am.audioInfo[i]->data = alHeapAlloc(c->heap, 1, 4 * g_audio_frame_buf_samples);
    }

    osCreateMesgQueue(&g_audio_reply_queue, g_audio_reply_msgs, 8);
    osCreateMesgQueue(&g_audio_frame_queue, g_audio_frame_msgs, 8);
    osCreateMesgQueue(&g_audio_dma_queue, g_audio_dma_msgs, 0x20);
    osCreateMesgQueue(&g_snd_cache_dma_queue, g_snd_cache_dma_msgs, 0x28);
    osCreateThread(&g_audio_thread, 4, (void (*)(void *)) audio_thread_main, 0, (void *) &g_snd_cache, pri);
    g_audio_thread_started = 1;
    osStartThread(&g_audio_thread);
}
// NON-MATCHING: so much to do
// void audio_mgr_init(struct15 *arg0, OSPri arg1, struct52 *arg2) {
//     // ? sp160;
//     s32 sp58;
//     // ? *temp_t4_2;
//     f32 temp_f0;
//     s32 temp_f8;
//     s32 temp_t4;
//     s32 temp_t7;
//     s32 temp_v0;
//     // u32 temp_a1;
//     // u32 temp_s0_2;
//     // void *temp_a0;
//     // void *temp_s0;
//     // void *temp_s0_3;
//     // void *temp_s1;
//     // void *temp_t0;
//     // void *temp_v0_2;
//     // void *temp_v0_3;
//     // void *temp_v0_4;
//     // void *temp_v1;
//     u32 phi_v1;
//     void *phi_t0;
//     s32 *phi_t4;
//     // void *phi_s0;
//     // void *phi_s1;
//     // void *phi_v0;
//     // s32 phi_v1_2;
//     // u32 phi_a1;
//     // u32 phi_s0_2;
//     // void *phi_s0_3;
//
//     mp3_voice_init(&D_8003E370);
//     arg0->unk10 = audio_dma_new;
//     temp_v0 = osAiSetFrequency(arg2->unk0);
//     arg0->unk2C = temp_v0;
//     arg0->unk14 = snd_cache_dma_new;
//     arg0->unk18 = snd_cache_entry_unref;
//     arg0->unk1C = snd_cache_entry_ref;
//     arg0->unk20 = snd_cache_entry_release;
//     temp_f0 = ((f32) (u32) arg2->unk4 * (f32) temp_v0) / 30.0f;
//     temp_f8 = (s32) temp_f0;
//     D_80040F8C = temp_f8;
//     phi_v1 = temp_f8;
//     if ((f32) (u32) temp_f8 < temp_f0) {
//         temp_t4 = temp_f8 + 1;
//         D_80040F8C = temp_t4;
//         phi_v1 = (u32) temp_t4;
//     }
//     temp_t7 = ((phi_v1 / 184) * 184) + 184;
//     D_80040F8C = temp_t7;
//     D_80040F88 = temp_t7 - 184;
//     D_80040F90 = temp_t7 + 84;
//     D_80040F84 = (u8)0;
//     phi_t0 = g_printf_zeros;
//     phi_t4 = &sp58;
// // loop_3:
// //     temp_t0 = phi_t0 + 0xC;
// //     temp_t4_2 = phi_t4 + 0xC;
// //     temp_t4_2->unk-C = (s32) *phi_t0;
// //     temp_t4_2->unk-8 = (s32) temp_t0->unk-8;
// //     temp_t4_2->unk-4 = (s32) temp_t0->unk-4;
// //     phi_t0 = temp_t0;
// //     phi_t4 = temp_t4_2;
// //     if (temp_t0 != 0x8002B064) {
// //         goto loop_3;
// //     }
// //     arg0->unk34 = &sp58;
// //     arg0->unk38 = &sp160;
// //     n_alInit(0x8003E640, arg0, (void *)0x80040F8C, &sp58);
// //     *(void *)0x8003E380 = 0x8003E640;
// //     g_audio_dma_buffers.unk4 = 0;
// //     g_audio_dma_buffers.unk0 = 0;
// //     phi_s0 = &g_audio_dma_buffers;
// //     phi_s1 = (void *)0x800406CC;
// // loop_5:
// //     temp_v0_2 = phi_s0->unk0;
// //     phi_s0->unk18 = phi_s0;
// //     phi_s0->unk14 = temp_v0_2;
// //     if (temp_v0_2 != 0) {
// //         temp_v0_2->unk4 = phi_s1;
// //     }
// //     phi_s0->unk0 = phi_s1;
// //     temp_s1 = phi_s1 + 0x14;
// //     temp_s0 = phi_s0 + 0x14;
// //     temp_s0->unk-4 = alHeapDBAlloc(0, 0, arg0->unk28, 1, 2048);
// //     phi_s0 = temp_s0;
// //     phi_s1 = temp_s1;
// //     if ((u32) temp_s1 < (u32) &g_snd_cache_dma_bufs) {
// //         goto loop_5;
// //     }
// //     temp_s0->unk10 = alHeapDBAlloc(0, 0, arg0->unk28, 1, 2048);
// //     bzero(&g_snd_cache_dma_bufs, 1200);
// //     g_snd_cache_dma_bufs.unk4 = 0;
// //     g_snd_cache_dma_bufs.unk0 = 0;
// //     phi_v0 = &g_snd_cache_dma_bufs;
// //     phi_v1_2 = 0x80040AE0;
// //     phi_a1 = 0U;
// // loop_9:
// //     temp_a0 = phi_v0->unk0;
// //     phi_v0->unk1C = phi_v0;
// //     phi_v0->unk18 = temp_a0;
// //     if (temp_a0 != 0) {
// //         temp_a0->unk4 = phi_v1_2;
// //     }
// //     phi_v0->unk0 = phi_v1_2;
// //     temp_a1 = phi_a1 + 1;
// //     temp_v0_3 = phi_v0 + 0x18;
// //     temp_v0_3->unk-8 = 0;
// //     phi_v0 = temp_v0_3;
// //     phi_v1_2 = phi_v1_2 + 0x18;
// //     phi_a1 = temp_a1;
// //     if (temp_a1 < 0x31U) {
// //         goto loop_9;
// //     }
// //     temp_v0_3->unk10 = 0;
// //     phi_s0_2 = 0x8003E388U;
// // loop_13:
// //     temp_s0_2 = phi_s0_2 + 4;
// //     temp_s0_2->unk-4 = alHeapDBAlloc(0, 0, arg0->unk28, 1, arg2->unk8 * 8);
// //     phi_s0_2 = temp_s0_2;
// //     if (temp_s0_2 < 0x8003E390U) {
// //         goto loop_13;
// //     }
// //     *(void *)0x80040F94 = (s32) arg2->unk8;
// //     phi_s0_3 = (void *)0x8003E388;
// // loop_15:
// //     temp_v0_4 = alHeapDBAlloc(0, 0, arg0->unk28, 1, 0x90);
// //     phi_s0_3->unk8 = temp_v0_4;
// //     temp_v0_4->unk70 = (u16)2;
// //     temp_v1 = phi_s0_3->unk8;
// //     temp_v1->unk74 = temp_v1;
// //     temp_s0_3 = phi_s0_3 + 4;
// //     phi_s0_3->unk8->unk0 = alHeapDBAlloc(0, 0, arg0->unk28, 1, *(void *)0x80040F90 * 4);
// //     phi_s0_3 = temp_s0_3;
// //     if (temp_s0_3 != 0x8003E394) {
// //         goto loop_15;
// //     }
//
//     osCreateMesgQueue(&D_8003E608, &D_8003E620, 8);
//     osCreateMesgQueue(&D_8003E5D0, &D_8003E5E8, 8);
//     osCreateMesgQueue(&D_80041298, &D_800412B0, 32);
//     osCreateMesgQueue(&D_800416F0, &D_80041708, 40);
//     osCreateThread(&g_audio_thread, 4, (void *) audio_thread_main, 0, &g_snd_cache, arg1);
//     g_audio_thread_started = (u8)1;
//     osStartThread(&g_audio_thread);
// }

/* was func_100093CC */
void audio_thread_stop(void) {
    if (g_audio_thread_started != 0) {
        osStopThread(&g_audio_thread);
    }
}

// audio thread
/* was func_10009400 */
void audio_thread_main(s32 arg0) {
    s32 pad; // fakematch: 4-byte frame slot above msg
    u8 done = 0;
    AmMsg *msg = NULL;
    void *lastInfo = NULL;
    struct { void *next; void *mq; s32 x; } client;
    u32 count = 0;
    s32 first = 1;

    client.x = 0;
    sched_add_client((OSPfs *) &client, &g_audio_frame_queue);
    while (!done) {
        osRecvMesg(&g_audio_frame_queue, (OSMesg *) &msg, OS_MESG_BLOCK);
        if (g_eeprom_writes_disabled) {
            msg->type = 4;
        }
        switch (msg->type) {
            case 1:
                if (count >= 2) {
                    count = 0;
                }
                if (count == 0 && audio_do_frame(g_audio_mgr_audio_info[g_audio_frame_count % 3], lastInfo)) {
                    if (!first) {
                        osRecvMesg(&g_audio_reply_queue, (OSMesg *) &msg, OS_MESG_BLOCK);
                        lastInfo = msg->data;
                    }
                    first = 0;
                }
                count++;
                break;
            case 4:
                done = 1;
                break;
            case 10:
                done = 1;
                break;
        }
    }
    n_alClose((s32) &g_audio_al_globals);
    for (;;) {
        osRecvMesg(&g_audio_frame_queue, (OSMesg *) &msg, OS_MESG_BLOCK);
    }
}

// NON-MATCHING: a long way to go
// void audio_thread_main(s32 arg0) {
//     OSMesg *msg;
//     s32 sp54;
//     OSPfs *sp4C;
//     s16 temp_v0;
//     u32 phi_s0;
//     u32 phi_s0_2;
//     s32 phi_s5;
//     s32 phi_s4;
//     s32 phi_s1;
//
//     msg = NULL;
//     sp54 = 0;
//     phi_s0 = 0;
//     phi_s5 = 0;
//     phi_s4 = 1;
//     phi_s1 = 0;
//     sched_add_client(&sp4C, &D_8003E5D0);
//     do {
//         osRecvMesg(&D_8003E5D0, &msg, 1);
//         if (g_eeprom_writes_disabled != 0) {
//             ((struct53*)msg)->unk0 = (u16)4;
//         }
//         temp_v0 = ((struct53*)msg)->unk0;
//         if (temp_v0 != 1) {
//             if (temp_v0 == (u16)4 || temp_v0 == 16) {
//                     phi_s1 = 1;
//             }
//         } else {
//             phi_s0_2 = phi_s0;
//             if (phi_s0 >= 2U) {
//                 phi_s0_2 = 0U;
//             }
//             if (phi_s0_2 == 0 && (audio_do_frame(D_8003E390[D_8002AE44 % 3U], phi_s5) != 0)) {
//                 if (phi_s4 == 0) {
//                     osRecvMesg(&D_8003E608, &msg, 1);
//                     phi_s5 = ((struct53*)msg)->unk4;
//                 }
//                 phi_s4 = 0;
//             }
//             phi_s0 = phi_s0_2 + 1;
//         }
//     }
//     while (phi_s1 == 0);
//
//     func_10018E0C(&D_8003E640);
//     while (1) {
//         osRecvMesg(&D_8003E5D0, &msg, 1);
//     }
// }

/* was func_100095A0 */
s32 audio_do_frame(AudioInfo *info, AudioInfo *lastInfo) {
    s16 *audioPtr;
    Acmd *cmdp;
    s32 cmdLen;
    s32 samplesLeft;
    struct AudTask *t;
    u32 end;
    u32 ret;

    audioPtr = (s16 *) osVirtualToPhysical(info->data);
    audio_clear_dma();
    snd_cache_update_dmas();
    samplesLeft = IO_READ(AI_LEN_REG) >> 2;
    if (lastInfo) {
        osAiSetNextBuffer(lastInfo->unk4, lastInfo->frameSamples << 2);
    }
    if (samplesLeft >= 0xF9 && g_audio_short_frame_hold == 0) {
        info->frameSamples = g_audio_frame_samples_short;
        g_audio_short_frame_hold = 2;
    } else {
        info->frameSamples = g_audio_frame_samples;
        if (g_audio_short_frame_hold) {
            g_audio_short_frame_hold--;
        }
    }
    end = (u32) audioPtr + (info->frameSamples << 2);
    if ((end & 0x1FFF) == 0) {
        audioPtr += 8;
        info->unk4 = info->data + 8;
    } else {
        info->unk4 = info->data;
    }
    cmdp = n_alAudioFrame(g_audio_mgr[g_audio_cmdlist_index], &cmdLen, audioPtr, info->frameSamples);
    if (cmdLen == 0) {
        return 0;
    }
    t = &info->task;
    t->next = 0;
    t->msgQ = &g_audio_reply_queue;
    t->msg = (OSMesg) &info->unk70;
    t->flags = 2;
    t->framebuffer = 0;
    t->list.t.data_ptr = (u64 *) g_audio_mgr[g_audio_cmdlist_index];
    t->list.t.data_size = (cmdp - g_audio_mgr[g_audio_cmdlist_index]) * sizeof(Acmd);
    t->list.t.type = M_AUDTASK;
    t->list.t.ucode_boot = (u64 *) g_rspboot_text;
    t->list.t.ucode_boot_size = g_rspboot_text_end - g_rspboot_text;
    t->list.t.flags = 0;
    t->list.t.ucode = (u64 *) aspMainTextStart;
    t->list.t.ucode_data = (u64 *) g_audio_ucode_data;
    t->list.t.ucode_data_size = 0x800;
    t->list.t.yield_data_ptr = NULL;
    t->list.t.yield_data_size = 0x400;
    osWritebackDCacheAll();
    osSendMesg(&g_sched_audio_queue, (OSMesg) t, OS_MESG_BLOCK);
    g_audio_cmdlist_index ^= 1;
    return 1;
}

// NON-MATCHING: so far away
// s32 audio_do_frame(struct50 *arg0, struct51 *arg1) {
//     s32 sp3C;
//     s32 sp34;
//     u32 sp30;
//     s32 temp_a2;
//     s32 temp_v1;
//     u32 temp_t7;
//     u8 temp_v0;
//     s32 phi_v1;
//     s32 phi_a2;
//
//     sp3C = osVirtualToPhysical(arg0->unk0);
//     audio_clear_dma();
//     snd_cache_update_dmas();
//     temp_a2 = sp3C;
//     temp_t7 = (u32) AI_A4500004 >> 2;
//     phi_v1 = (s32) temp_t7;
//     if (arg1 != 0) {
//         sp3C = temp_a2;
//         sp30 = temp_t7;
//         func_10002DB0(arg1->unk4, arg1->unk8 * 4, temp_a2);
//         phi_v1 =  sp30;
//     }
//     if ((phi_v1 >= 0xF9) && (D_80040F84 == 0)) {
//         arg0->unk8 = D_80040F88; // *
//         D_80040F84 = 2U;
//     } else {
//         arg0->unk8 = D_80040F8C; // *
//         temp_v0 = D_80040F84;
//         if (temp_v0 != 0) {
//             D_80040F84 = (u8) (temp_v0 - 1);
//         }
//     }
//     if (((temp_a2 + (arg0->unk8 * 4)) & 0x1FFF) == 0) {
//         arg0->unk4 = (s32) (arg0->unk0 + 16);
//         phi_a2 = temp_a2 + 16;
//     } else {
//         arg0->unk4 = (s32) arg0->unk0;
//         phi_a2 = temp_a2;
//     }
//     // temp_v1 = alAudioFrame(D_8003E388[D_8002AE4C], &sp34, phi_a2, arg0->unk8);
//     if (sp34 == 0) {
//         return 0;
//     }
//     arg0->unk10 = 0;
//     arg0->unk68 = 0x8003E608;
//     arg0->unk6C = arg0->unk70;
//     arg0->unk1C = 2;
//     arg0->unk20 = 0;
//     arg0->unk58 = (s32) D_8003E388[D_8002AE4C];
//     arg0->unk5C = (s32) (((s32) D_8003E388[temp_v1 - D_8002AE4C] >> 3) * 8);
//     arg0->unk28 = 2;
//     arg0->unk30 = 0x100290D0;
//     arg0->unk34 = (s32) (D_100291A0 - D_100290D0);
//     arg0->unk2C = 0;
//     arg0->unk38 = 0x100291A0;
//     arg0->unk40 = 0x8002C960;
//     arg0->unk44 = 2048;
//     arg0->unk60 = 0;
//     arg0->unk64 = 1024;
//     // D_8002AE4C, 0x8003E388, 2
//     osWritebackDCacheAll();
//     osSendMesg(&g_sched_audio_queue_alias, &arg0->unk10, 1);
//     D_8002AE4C = D_8002AE4C ^ 1;
//     return 1;
// }

/* was func_100097CC */
s32 audio_dma_callback(u32 addr, s32 len, s32 state) {
    void *foundBuffer;
    s32 delta, addrEnd, buffEnd;
    AMDMABuffer *dmaPtr, *lastDmaPtr;

    lastDmaPtr = NULL;
    dmaPtr = dmaState.firstUsed;
    addrEnd = (s32) addr + len;
    while (dmaPtr) {
        buffEnd = dmaPtr->startAddr + 0x800;
        if (dmaPtr->startAddr > (u32) addr) {
            break;
        } else if (addrEnd <= buffEnd) {
            dmaPtr->lastFrame = g_audio_frame_count;
            foundBuffer = dmaPtr->ptr + addr - dmaPtr->startAddr;
            return osVirtualToPhysical(foundBuffer);
        }
        lastDmaPtr = dmaPtr;
        dmaPtr = (AMDMABuffer *) dmaPtr->node.next;
    }
    dmaPtr = dmaState.firstFree;
    if (!dmaPtr || g_audio_dma_count >= 32) {
        return 0;
    }
    dmaState.firstFree = (AMDMABuffer *) dmaPtr->node.next;
    { ALLink *ln = (ALLink *) dmaPtr; if (ln->next) ln->next->prev = ln->prev; if (ln->prev) ln->prev->next = ln->next; }
    if (lastDmaPtr) {
        ALLink *ln = (ALLink *) dmaPtr; ALLink *to = (ALLink *) lastDmaPtr;
        ln->next = to->next; ln->prev = to;
        if (to->next) to->next->prev = ln;
        to->next = ln;
    } else if (dmaState.firstUsed) {
        lastDmaPtr = dmaState.firstUsed;
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = (ALLink *) lastDmaPtr;
        dmaPtr->node.prev = 0;
        lastDmaPtr->node.prev = (ALLink *) dmaPtr;
    } else {
        dmaState.firstUsed = dmaPtr;
        dmaPtr->node.next = 0;
        dmaPtr->node.prev = 0;
    }
    foundBuffer = dmaPtr->ptr;
    delta = addr & 1;
    addr -= delta;
    dmaPtr->startAddr = addr;
    dmaPtr->lastFrame = g_audio_frame_count;
    osPiStartDma(&g_audio_dma_io_msgs[g_audio_dma_count++], OS_MESG_PRI_HIGH, OS_READ, addr, foundBuffer, 0x800, &g_audio_dma_queue);
    return osVirtualToPhysical(foundBuffer) + delta;
}

// NON-MATCHING: another horrible function
// s32 audio_dma_callback(u32 arg0, s32 arg1, s32 arg2) {
//     s32 sp2C;
//     s32 sp28;
//     s32 temp_a3;
//     s32 temp_t0;
//     s32 temp_t1;
//     s32 temp_t9;
//     u32 temp_v0;
//     u32 temp_v0_6;
//     struct19 *temp_a2;
//     struct19 *temp_v0_2;
//     struct19 *temp_v0_3;
//     struct19 *temp_v0_4;
//     struct19 *temp_v0_5;
//     struct19 *temp_v1;
//     struct19 *temp_v1_2;
//     struct19 *temp_v1_3;
//     struct19 *phi_v1;
//     struct19 *phi_a2;
//
//     temp_v1 = g_audio_dma_state.unk4;
//     phi_v1 = temp_v1;
//     phi_a2 = NULL;
//     phi_a2 = NULL;
//     if (temp_v1 != 0) {
// loop_1:
//         temp_v0 = phi_v1->unk8;
//         if (arg0 >= temp_v0) {
//             temp_a2 = phi_v1;
//             if ((temp_v0 + 0x800) >= (arg0 + arg1)) {
//                 phi_v1->unkC = (s32) D_8002AE44;
//                 return osVirtualToPhysical((phi_v1->unk10 + arg0) - temp_v0); //, temp_a2, arg0);
//             }
//             temp_v1_2 = phi_v1->unk0;
//             phi_v1 = temp_v1_2;
//             phi_a2 = temp_a2;
//             // phi_a2 = temp_a2;
//             if (temp_v1_2 != 0) {
//                 goto loop_1;
//             }
//         }
//     }
//     temp_v1_3 = g_audio_dma_state.unk8;
//     if ((temp_v1_3 == 0) || ((u32) D_8002AE48 >= 0x20U)) {
//         return 0;
//     }
//     g_audio_dma_state.unk8 = (struct19 *) temp_v1_3->unk0;
//     temp_v0_2 = temp_v1_3->unk0;
//     if (temp_v0_2 != 0) {
//         temp_v0_2->unk4 = (struct19 *) temp_v1_3->unk4;
//     }
//     temp_v0_3 = temp_v1_3->unk4;
//     if (temp_v0_3 != 0) {
//         temp_v0_3 = (struct19 *) temp_v1_3->unk0; // ()
//     }
//     if (phi_a2 != 0) {
//         temp_v1_3->unk4 = phi_a2;
//         temp_v1_3->unk0 = (struct19 *) phi_a2; // *
//         temp_v0_4 = phi_a2; // *
//         if (temp_v0_4 != 0) {
//             temp_v0_4->unk4 = temp_v1_3;
//         }
//         phi_a2 = temp_v1_3; // *
//     } else {
//         temp_v0_5 = g_audio_dma_state.unk4;
//         if (temp_v0_5 != 0) {
//             g_audio_dma_state.unk4 = temp_v1_3;
//             temp_v1_3->unk0 = temp_v0_5;
//             temp_v1_3->unk4 = NULL;
//             temp_v0_5->unk4 = temp_v1_3;
//         } else {
//             g_audio_dma_state.unk4 = temp_v1_3;
//             temp_v1_3->unk0 = NULL;
//             temp_v1_3->unk4 = NULL;
//         }
//     }
//     temp_t0 = arg0 & 1;
//     temp_t1 = temp_v1_3->unk10;
//     sp28 = temp_t0;
//     temp_a3 = arg0 - temp_t0;
//     temp_v1_3->unk8 = temp_a3;
//     temp_v1_3->unkC = (s32) D_8002AE44;
//     temp_v0_6 = D_8002AE48;
//     // temp_t9 = temp_v0_6; // * 0x18;
//     D_8002AE48 = (u32) (temp_v0_6 + 1); // next free slot in D_80040F98?
//     sp2C = temp_t1;
//     osPiStartDma(&D_80040F98[temp_v0_6], 1, 0, temp_a3, temp_t1, 0x800, &D_80041298);
//     return osVirtualToPhysical(sp2C) + sp28;
// }

/* was func_10009980 */
s32 audio_dma_new(s32 *arg0) {
    if (g_audio_dma_state.unk0 == 0) {
        g_audio_dma_state.unk4 = (u8) 0;
        g_audio_dma_state.unk8 = &g_audio_dma_buffers;
        g_audio_dma_state.unk0 = 1;
    }
    *arg0 = 0;
    return audio_dma_callback;
}

/* was func_100099BC */
void audio_clear_dma(void) {
    u32 i;
    OSIoMesg *iomsg = 0;
    AMDMABuffer *dmaPtr, *nextPtr;

    for (i = 0; i < g_audio_dma_count; i++) {
        if (osRecvMesg(&g_audio_dma_queue, (OSMesg *) &iomsg, OS_MESG_NOBLOCK) == -1) {
            osRecvMesg(&g_audio_dma_queue, (OSMesg *) &iomsg, OS_MESG_BLOCK);
        }
    }
    dmaPtr = dmaState.firstUsed;
    while (dmaPtr) {
        nextPtr = (AMDMABuffer *) dmaPtr->node.next;
        if (dmaPtr->lastFrame + 1 < g_audio_frame_count) {
            if (dmaState.firstUsed == dmaPtr) {
                dmaState.firstUsed = nextPtr;
            }
            { ALLink *ln = (ALLink *) dmaPtr; if (ln->next) ln->next->prev = ln->prev; if (ln->prev) ln->prev->next = ln->next; }
            if (dmaState.firstFree) {
                ALLink *ln = (ALLink *) dmaPtr; ALLink *to = (ALLink *) dmaState.firstFree;
                ln->next = to->next; ln->prev = to;
                if (to->next) to->next->prev = ln;
                to->next = ln;
            } else {
                dmaState.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
    g_audio_dma_count = 0;
    g_audio_frame_count++;
}


/* was func_10009B2C */
void snd_cache_entry_unref(struct54 *arg0) {
    if (((s32)arg0 & 1) == 0) {
        arg0->unk14--;
    }
}

/* was func_10009B4C */
void snd_cache_entry_release(struct54 *arg0) { // struct147 unk14 is wrong type
    if (((s32)arg0 & 1) == 0) {
        arg0->unk14--;
        if (arg0->unk14 == 0) {
            snd_cache_entry_free(arg0);
        }
    }
}

/* was func_10009B90 */
void snd_cache_entry_ref(struct54 *arg0) {
    if (((s32)arg0 & 1) == 0) {
        if (1 == arg0->unk15) {
            if (1 == arg0->unk16) {
                arg0->unk14 += 1;
            }
            arg0->unk15 = 2;
            return;
        }
        arg0->unk14 += 1;
    }
}

s32 func_150ADC50(struct147 *);

/* was func_10009BE4 */
void snd_cache_entry_free(struct54 *arg0) {
    struct54 *temp_a1;
    struct54 *temp_v0;
    struct54 *temp_v0_2;

    if ((s32) arg0 & 1) {
        g_dbg_crash_marker = 0x0F000004;
        func_150ADC50(&g_snd_cache);
        return;
    }
    *(s32 *)arg0->unkC = (u32) arg0->unk8;
    if ((s32)arg0 == (s32)g_snd_cache.unk4) {
        g_snd_cache_used_head = arg0->unk0;
    }
    temp_v0 = arg0->unk0;
    if (temp_v0 != NULL) {
        temp_v0->unk4 = arg0->unk4;
    }
    temp_v0_2 = arg0->unk4;
    if (temp_v0_2 != NULL) {
        temp_v0_2->unk0 = arg0->unk0;
    }
    if (g_snd_cache.unk10 != NULL) {
        arg0->unk4 = g_snd_cache.unk10;
        arg0->unk0 = g_snd_cache.unk10->unk0;
        temp_a1 = g_snd_cache.unk10->unk0;
        if (temp_a1 != NULL) {
            temp_a1->unk4 = arg0;
        }
        g_snd_cache.unk10->unk0 = arg0;
        return;
    }
    g_snd_cache_free_list = arg0;
    arg0->unk0 = NULL;
    arg0->unk4 = NULL;
}
// void snd_cache_entry_free(struct00 *arg0) {
//     struct00 *temp_a1;
//     struct00 *temp_v0;
//     struct00 *temp_v1;
//
//     if (((s32)arg0 & 1) != 0) {
//         g_dbg_crash_marker = 0x0F000004;
//         func_150AD770(); // 0x80040000
//         return;
//     }
//     arg0->unkC = (s32) arg0->unk8;
//     if ((s32)arg0 == g_snd_cache.unk4) {
//         D_800406A4 = (struct54 *) arg0->unk0;
//     }
//     temp_v0 = arg0->unk0;
//     if (temp_v0 != 0) {
//         temp_v0->unk4 = (struct54 *) arg0->unk4;
//     }
//     temp_v0 = arg0->unk4;
//     if (temp_v0 != 0) {
//         temp_v0 = (struct54 *) arg0->unk0;
//     }
//     temp_v1 = g_snd_cache.unk10;
//     if (temp_v1 != 0) {
//         arg0->unk4 = temp_v1;
//         arg0->unk0 = (struct54 *) &temp_v1;
//         temp_a1 = &temp_v1;
//         if (temp_a1 != 0) {
//             temp_a1->unk4 = arg0;
//         }
//         temp_v1 = arg0;
//         return;
//     }
//     D_800406B0 = arg0;
//     arg0->unk0 = NULL;
//     arg0->unk4 = NULL;
//     // return temp_v0;
// }

// Sound-bank on-demand loader (the n_alSynNew DMA callback set up by snd_cache_dma_new).
// *slot holds either a packed ROM reference (bit 0 set: ROM offset in bits 8.., size byte in bits 0..7)
// or, once loaded, a pointer to its cache entry. A ROM reference is replaced by a fresh cache entry
// (from the free list, else the last idle loaded entry is evicted) and an async PI DMA is started;
// the call returns 0 until the DMA completed. A loaded entry returns its data.
typedef struct SndCacheEntry_s {
    struct SndCacheEntry_s *next;
    struct SndCacheEntry_s *prev;
    u32 romRef;     /* the original *slot value */
    u32 *slot;
    u8 *data;
    s8 users;
    u8 state;       /* 0 = DMA pending, 1 = DMA done, 2 = in use (evictable when users == 0) */
    u8 keep;
} SndCacheEntry;
typedef struct {
    u8 initialized;
    SndCacheEntry *used;
    SndCacheEntry *free;
    SndCacheEntry *loaded;
} SndCache;
#define sndCache (*(SndCache *)&g_snd_cache)
extern s32 g_snd_cache_dma_pending;          /* PI DMA messages in flight this frame; was D_8002B1A0 */
extern OSIoMesg g_snd_cache_io_msgs[]; /* was D_800416D0 */
extern OSMesgQueue g_snd_cache_dma_queue; /* was D_80041A90 */
void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
void os_writeback_dcache(void *addr, s32 size); /* osWritebackDCache */

#define SND_CACHE_UNLINK(e)              \
    {                                    \
        if ((e)->next != NULL) {         \
            (e)->next->prev = (e)->prev; \
        }                                \
        if ((e)->prev != NULL) {         \
            (e)->prev->next = (e)->next; \
        }                                \
    }

/* was func_10009CBC */
s32 snd_cache_load_on_demand(void *arg0, s32 arg1) {
    u32 *slot = arg0;
    u32 ref = *slot;
    SndCacheEntry *e;
    SndCacheEntry *it;
    SndCacheEntry *head;
    u32 size;
    u32 alignedSize;

    if (!(ref & 1)) {
        e = (SndCacheEntry *)ref;
        *slot = ref;
        if (e->state == 0) {
            return 0;
        }
        if (arg1 == 1) {
            if (e->state == 1) {
                e->state = 2;
            } else {
                e->users++;
            }
        }
        return (s32)e->data;
    }

    if (arg1 == 0) {
        size = (ref & 0xFF) + 1;
    } else {
        size = (ref & 0xFE) << 6;
    }

    if (sndCache.free != NULL) {
        e = sndCache.free;
        sndCache.free = e->next;
        SND_CACHE_UNLINK(e);
    } else {
        e = NULL;
        for (it = sndCache.used; it != NULL; it = it->next) {
            if (it->users == 0 && it->keep == 0 && it->state == 2) {
                e = it;
            }
        }
        if (e != NULL) {
            *e->slot = e->romRef;
            heap_set_block_tag((s32 *)e->data, 4);
            e->data = NULL;
            e->slot = NULL;
            if (e == sndCache.used) {
                sndCache.used = e->next;
            }
            SND_CACHE_UNLINK(e);
        }
    }
    if (e == NULL) {
        return 0;
    }

    e->next = NULL;
    e->prev = NULL;
    head = sndCache.loaded;
    if (head != NULL) {
        e->prev = head;
        e->next = head->next;
        if (head->next != NULL) {
            head->next->prev = e;
        }
        head->next = e;
    } else {
        sndCache.loaded = e;
        e->next = NULL;
        e->prev = NULL;
    }
    e->romRef = ref;
    e->users = 0;
    e->keep = arg1;
    e->state = 0;
    e->slot = slot;

    if ((u32)g_snd_cache_dma_pending < 40) {
        alignedSize = (size + 0xF) & ~0xF;
        e->data = allocate_memory(alignedSize, 0xFF, 2, 0);
        bzero(e->data, alignedSize);
    } else {
        e->data = NULL;
    }
    if (e->data != NULL) {
        os_writeback_dcache(e->data, alignedSize);
        osInvalDCache(e->data, alignedSize);
        osPiStartDma(&g_snd_cache_io_msgs[g_snd_cache_dma_pending++], OS_MESG_PRI_HIGH, OS_READ, (ref >> 5) & ~7, e->data, alignedSize,
                     &g_snd_cache_dma_queue);
        *slot = (u32)e;
    }
    return 0;
}
/* was func_10009FFC */
s32 snd_cache_dma_new(void) {
    if (g_snd_cache.unk0 == 0) {
        g_snd_cache.unk4 = NULL;
        g_snd_cache.unk8 = &g_snd_cache_dma_bufs;
        g_snd_cache.unkC = 0;
        g_snd_cache.unk10 = NULL;
        g_snd_cache.unk0 = (u8)1U;
    }
    return snd_cache_load_on_demand;
}

/* Audio bank DMA bookkeeping: for each pending DMA (g_snd_cache_dma_pending), poll g_snd_cache_dma_queue; a finished message (+8 = bank
 * address) moves its node from the loading list (g_snd_cache.unkC) to the loaded list (.unk4), relocating the bank's
 * pointer table once (unk16 == 1). Then nodes of the release list (.unk10) whose instruments are no longer in use
 * (+0xA flags of each entry) are freed (heap_free) and moved to the free list (.unk8). */
/* was func_1000A03C */
void snd_cache_update_dmas(void) {
    u32 pending = g_snd_cache_dma_pending;
    s32 received = 0;
    u32 i, j;
    s32 found;
    u8 *msg = NULL;
    struct54 *s;
    struct54 *next;
    struct54 *h;
    u8 *bank;

    for (i = 0; i < g_snd_cache_dma_pending; i++) {
        if (osRecvMesg(&g_snd_cache_dma_queue, (OSMesg *)&msg, OS_MESG_NOBLOCK) != -1) {
            received++;
            found = 0;
            s = g_snd_cache.unkC;
            while (s != NULL && !found) {
                if (*(s32 *)(msg + 8) == s->unk10) {
                    found = 1;
                    if (s == g_snd_cache.unkC) {
                        g_snd_cache.unkC = s->unk0;
                    }
                    if (s->unk0 != NULL) {
                        s->unk0->unk4 = s->unk4;
                    }
                    if (s->unk4 != NULL) {
                        s->unk4->unk0 = s->unk0;
                    }
                    s->unk0 = NULL;
                    s->unk4 = NULL;
                    if (g_snd_cache.unk4 != 0) {
                        h = (struct54 *)g_snd_cache.unk4;
                        s->unk4 = h;
                        s->unk0 = h->unk0;
                        if (h->unk0 != NULL) {
                            h->unk0->unk4 = s;
                        }
                        h->unk0 = s;
                    } else {
                        g_snd_cache.unk4 = (s32)s;
                        s->unk0 = NULL;
                        s->unk4 = NULL;
                    }
                    if (s->unk16 == 1) {
                        bank = (u8 *)s->unk10;
                        for (j = 0; j < (u32)*(s16 *)(bank + 0xE); j++) {
                            ((s32 *)(bank + 0x10))[j] += s->unk10;
                        }
                    }
                    s->unk15 = 1;
                    s->unk14++;
                } else {
                    s = s->unk0;
                }
            }
        }
    }
    s = g_snd_cache.unk10;
    g_snd_cache_dma_pending = pending - received;
    while (s != NULL) {
        found = 0;
        next = s->unk0;
        if (s->unk16 == 1) {
            bank = (u8 *)s->unk10;
            for (j = 0; j < (u32)*(s16 *)(bank + 0xE); j++) {
                u8 *inst = *(u8 **)(((u8 **)(bank + 0x10))[j] + 8);
                if (inst[0xA] != 0) {
                    inst[0xA] = 0;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            s->unk14 = 0;
            s->unk15 = 0;
            heap_free(s->unk10);
            s->unkC = 0;
            if (s == g_snd_cache.unk10) {
                g_snd_cache.unk10 = next;
            }
            if (s->unk0 != NULL) {
                s->unk0->unk4 = s->unk4;
            }
            if (s->unk4 != NULL) {
                s->unk4->unk0 = s->unk0;
            }
            if (g_snd_cache.unk8 != 0) {
                h = (struct54 *)g_snd_cache.unk8;
                s->unk4 = h;
                s->unk0 = h->unk0;
                if (h->unk0 != NULL) {
                    h->unk0->unk4 = s;
                }
                h->unk0 = s;
            } else {
                g_snd_cache.unk8 = (s32)s;
                s->unk0 = NULL;
                s->unk4 = NULL;
            }
        }
        s = next;
    }
    if (g_snd_cache_flush_request != 0) {
        snd_cache_flush_unused();
        g_snd_cache_flush_request = 0;
    }
}
typedef struct ACBuf_s {
    ALLink node;
    s32 unk8;
    s32 *unkC;
    s32 unk10;
    s8 unk14;
    u8 unk15;
    u8 unk16;
} ACBuf;
typedef struct {
    s32 unk0;
    ACBuf *firstUsed;
    s32 unk8;
    s32 unkC;
    ACBuf *firstFree;
} ACState;
#define acState (*(ACState *)&g_snd_cache)

/* was func_1000A348 */
void snd_cache_flush_unused(void) {
    ACBuf *dmaPtr, *nextPtr;
    s32 *p;

    dmaPtr = acState.firstUsed;
    while (dmaPtr) {
        nextPtr = (ACBuf *) dmaPtr->node.next;
        if (dmaPtr->unk14 == 0 && dmaPtr->unk16 == 0) {
            p = dmaPtr->unkC;
            *p = dmaPtr->unk8;
            dmaPtr->unkC = NULL;
            if (acState.firstUsed == dmaPtr) {
                acState.firstUsed = nextPtr;
            }
            { ALLink *ln = (ALLink *) dmaPtr; if (ln->next) ln->next->prev = ln->prev; if (ln->prev) ln->prev->next = ln->next; }
            if (acState.firstFree) {
                ALLink *ln = (ALLink *) dmaPtr; ALLink *to = (ALLink *) acState.firstFree;
                ln->next = to->next; ln->prev = to;
                if (to->next) to->next->prev = ln;
                to->next = ln;
            } else {
                acState.firstFree = dmaPtr;
                dmaPtr->node.next = 0;
                dmaPtr->node.prev = 0;
            }
        }
        dmaPtr = nextPtr;
    }
}
