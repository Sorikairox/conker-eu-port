// s125: amCreateAudioMgr (libultra demo / DKR audiomgr.c shape, built -O2)
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
extern AmFxParams D_8002B1A4;
extern u8 D_8003E710[];
extern void *D_8003E720;
#define dmaBuffs ((AMDMABuffer *) &D_800406B8)
#define amUnk18Buffs ((AmUnk18 *) &D_80040AC8)
extern u32 D_80041330;
extern u32 D_80041334;
typedef struct {
    Acmd *ACMDList[2];
    AmAudioInfo *audioInfo[3];
} AmMgr;
#define __am (*(AmMgr *) D_8003E728)
#define AM_LINK(ln, to) \
    (ln)->next = (to)->next; \
    (ln)->prev = (to); \
    if ((to)->next) (to)->next->prev = (ln); \
    (to)->next = (ln);
extern OSMesg D_8003E9C0[];
extern OSMesg D_8003E988[];
extern OSMesg D_80041650[];
extern OSMesgQueue D_80041A90;
extern OSMesg D_80041AA8[];
extern OSThread D_8003E3A0;
extern u8 D_8002AE40;
s32 func_10009FFC(void);

void func_10008F90(AmSynConfig *c, OSPri pri, AmConfig *arg2) {
    u32 i;
    f32 fsize;
    AmFxParams params;

    func_10012588((s32) D_8003E710);
    c->dmaproc = func_10009980;
    c->outputRate = osAiSetFrequency(arg2->frequency);
    c->unk14 = func_10009FFC;
    c->unk18 = func_10009B2C;
    c->unk1C = func_10009B90;
    c->unk20 = func_10009B4C;

    fsize = arg2->unk4 * (f32) c->outputRate / 25.0f;
    D_8004132C = (s32) fsize;
    if (D_8004132C < fsize) {
        D_8004132C++;
    }
    D_8004132C = (D_8004132C / 184) * 184 + 184;
    D_80041328 = D_8004132C - 184;
    D_80041330 = D_8004132C + 84;
    D_80041324 = 0;

    params = D_8002B1A4;
    c->params[0] = params.bus0;
    c->params[1] = params.bus1;
    n_alInit((void *) &D_8003E9E0, (s32) c);
    D_8003E720 = &D_8003E9E0;

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
    D_80041334 = arg2->unk8;

    for (i = 0; i < 3; i++) {
        __am.audioInfo[i] = alHeapAlloc(c->heap, 1, sizeof(AmAudioInfo));
        __am.audioInfo[i]->type = 2;
        __am.audioInfo[i]->info = __am.audioInfo[i];
        __am.audioInfo[i]->data = alHeapAlloc(c->heap, 1, 4 * D_80041330);
    }

    osCreateMesgQueue(&D_8003E9A8, D_8003E9C0, 8);
    osCreateMesgQueue(&D_8003E970, D_8003E988, 8);
    osCreateMesgQueue(&D_80041638, D_80041650, 0x20);
    osCreateMesgQueue(&D_80041A90, D_80041AA8, 0x28);
    osCreateThread(&D_8003E3A0, 4, (void (*)(void *)) func_10009400, 0, (void *) &D_800406A0, pri);
    D_8002AE40 = 1;
    osStartThread(&D_8003E3A0);
}
