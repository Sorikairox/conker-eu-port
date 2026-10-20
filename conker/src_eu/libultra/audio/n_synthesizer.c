#define alN_PVoiceNew alN_PVoiceNew_proto
#define n_alSynNew n_alSynNew_proto
#include "n_synthInternals.h"
#undef alN_PVoiceNew
#undef n_alSynNew


extern f32 D_8002C750;

// s125: DK64 n_synthesizer.c n_alSynNew with Conker's layout: 6 extra config words copied to the synth,
// per-bus voice lists (0x14/0x18) instead of DK64's source arrays, alLink inlined, aux bus stride 0x44.
typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[0x2C - 0x4];
    void *unk2C;
    void *unk30;
    u8 pad34[0x38 - 0x34];
} SynNewBusFx;

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
    s32 unk18;
    void *fx;
    u8 pad20[0x40 - 0x20];
    SynNewBusFx *unk40;
} SynNewAuxBus;

typedef struct {
    u8 pad0[4];
    void *handler;
    u8 pad8[0x14 - 0x8];
} SynNewMainBus;

typedef struct SynNewParam {
    struct SynNewParam *next;
    u8 pad4[0x24 - 0x4];
} SynNewParam;

typedef struct {
    ALLink node;
    ALLink unk8;
    void *vvoice;
    u8 pad14[0xD0 - 0x14];
} SynNewPVoice;

typedef struct {
    void *head;
    ALLink pFreeList;
    ALLink pAllocList;
    ALLink pLameList;
    s32 paramSamples;
    s32 curSamples;
    void *dma;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    ALHeap *heap;
    SynNewParam *paramList;
    SynNewMainBus *mainBus;
    SynNewAuxBus *auxBus;
    s32 numPVoices;
    s32 maxAuxBusses;
    s32 outputRate;
    s32 maxOutSamples;
} SynNewSynth;

typedef struct {
    s32 maxVVoices;
    s32 maxPVoices;
    s32 maxUpdates;
    s32 maxFXbusses;
    void *dmaproc;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    ALHeap *heap;
    s32 outputRate;
    u8 fxTypes[4];
} SynNewConfig;

extern SynNewSynth *D_8002BA44;
void *func_1001E4A0(s32, SynNewConfig *, ALHeap *);
void alN_PVoiceNew(SynNewPVoice *, void *, ALHeap *);
Acmd *func_1001E530();

void n_alSynNew(SynNewConfig *c) {
    s32 i;
    s32 j;
    SynNewPVoice *pv;
    SynNewPVoice *pvoices;
    ALHeap *hp = c->heap;
    SynNewParam *params;
    SynNewParam *paramPtr;

    D_8002BA44->head          = NULL;
    D_8002BA44->numPVoices    = c->maxPVoices;
    D_8002BA44->curSamples    = 0;
    D_8002BA44->paramSamples  = 0;
    D_8002BA44->outputRate    = c->outputRate;
    D_8002BA44->maxOutSamples = FIXED_SAMPLE;
    D_8002BA44->dma           = c->dmaproc;
    D_8002BA44->unk28         = c->unk14;
    D_8002BA44->unk2C         = c->unk18;
    D_8002BA44->unk30         = c->unk1C;
    D_8002BA44->unk34         = c->unk20;
    D_8002BA44->unk38         = c->unk24;

    if (c->maxFXbusses > 2) {
        D_8002BA44->maxAuxBusses = 2;
    } else if (c->maxFXbusses < 1) {
        D_8002BA44->maxAuxBusses = 1;
    } else {
        D_8002BA44->maxAuxBusses = c->maxFXbusses;
    }

    D_8002BA44->auxBus = alHeapAlloc(hp, D_8002BA44->maxAuxBusses, sizeof(SynNewAuxBus));

    for (i = 0; i < D_8002BA44->maxAuxBusses; i++) {
        D_8002BA44->auxBus[i].unk14 = 0;
        D_8002BA44->auxBus[i].unk18 = 0;

        if (c->fxTypes[i]) {
            D_8002BA44->auxBus[i].fx = func_1001E4A0(i, c, hp);
        } else {
            D_8002BA44->auxBus[i].fx = NULL;
        }

        D_8002BA44->auxBus[i].unk40 = alHeapAlloc(hp, 1, sizeof(SynNewBusFx));
        D_8002BA44->auxBus[i].unk40->unk2 = 0;
        D_8002BA44->auxBus[i].unk40->unk2C = alHeapAlloc(hp, 1, 8);
        D_8002BA44->auxBus[i].unk40->unk30 = alHeapAlloc(hp, 1, 8);
    }

    D_8002BA44->mainBus = alHeapAlloc(hp, 1, sizeof(SynNewMainBus));
    D_8002BA44->mainBus->handler = func_1001E530;

    D_8002BA44->pFreeList.next = 0;
    D_8002BA44->pFreeList.prev = 0;
    D_8002BA44->pLameList.next = 0;
    D_8002BA44->pLameList.prev = 0;
    D_8002BA44->pAllocList.next = 0;
    D_8002BA44->pAllocList.prev = 0;

    pvoices = alHeapAlloc(hp, c->maxPVoices, sizeof(SynNewPVoice));

    for (i = 0; i < c->maxPVoices; i++) {
        pv = &pvoices[i];
        {
            ALLink *ln = (ALLink *) pv;
            ALLink *to = &D_8002BA44->pFreeList;

            ln->next = to->next;
            ln->prev = to;
            if (to->next) {
                to->next->prev = ln;
            }
            to->next = ln;
        }
        pv->vvoice = 0;
        alN_PVoiceNew(pv, D_8002BA44->dma, hp);
    }

    for (j = 0; j < D_8002BA44->maxAuxBusses; j++) {
        D_8002BA44->auxBus[j].unk14 = 0;
        D_8002BA44->auxBus[j].unk18 = 0;
    }

    params = alHeapAlloc(hp, c->maxUpdates, sizeof(SynNewParam));
    D_8002BA44->paramList = 0;

    for (i = 0; i < c->maxUpdates; i++) {
        paramPtr = &params[i];
        paramPtr->next = D_8002BA44->paramList;

        D_8002BA44->paramList = paramPtr;
    }

    D_8002BA44->heap = hp;
}

static s32 __n_nextSampleTime(ALPlayer **client);
Acmd *func_1001FB40(s32 sampleOffset, Acmd *p); // n_alSavePull?
s32 _n_timeToSamplesNoRound(s32 micros);

Acmd *n_alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen)
{
    ALPlayer *client;
    Acmd     *cmdlEnd = cmdList;
    s32      nOut;
    s16      *lOutBuf = outBuf;

    if (n_syn->head == 0) {
        *cmdLen = 0;
        return cmdList;
    }

    for (n_syn->paramSamples = __n_nextSampleTime(&client);
         (u32)(n_syn->paramSamples - n_syn->curSamples) < (u32)outLen;
         n_syn->paramSamples = __n_nextSampleTime(&client)) {
        n_syn->paramSamples &= ~0xf;
        client->samplesLeft += _n_timeToSamplesNoRound((*client->handler)(client));
    }
    n_syn->paramSamples &= ~0xf;

    while (outLen > 0) {
        nOut = MIN(n_syn->maxOutSamples, outLen);
        cmdlEnd = func_1001FB40(n_syn->curSamples, cmdlEnd);
        {
            Acmd *_a = cmdlEnd++;
            _a->words.w0 = 0x0D000000;
        }
        {
            Acmd *_a = cmdlEnd++;
            _a->words.w0 = 0x062E0000;
            _a->words.w1 = (u32)lOutBuf;
        }
        outLen -= nOut;
        lOutBuf += nOut << 1;
        n_syn->curSamples += nOut;
    }

    *cmdLen = (s32)(cmdlEnd - cmdList);
    _n_collectPVoices();
    return cmdlEnd;
}

ALParam *__n_allocParam(void) {
    ALParam *update = 0;

    if (n_syn->paramList) {
        update = n_syn->paramList;
        n_syn->paramList = n_syn->paramList->next;
        update->next = 0;
    }
    return update;
}


void _n_freeParam(ALParam *param)
{
  param->next = n_syn->paramList;
  n_syn->paramList = param;
}

void _n_collectPVoices(void) {
    ALLink *dl;

    while ((dl = n_syn->pLameList.next) != 0) {
        N_AL_UNLINK(dl);
        N_AL_LINK(dl, &n_syn->pFreeList);
        N_AL_UNLINK(&((N_PVoice *)dl)->unk8);
        ((N_PVoice *)dl)->unk8.next = NULL;
        ((N_PVoice *)dl)->unk8.prev = NULL;
    }
}
void _n_freePVoice(N_PVoice *pvoice) {
    /*
     * move the voice from the allocated list to the lame list
     */
    N_AL_UNLINK(pvoice);
    N_AL_LINK(pvoice, &n_syn->pLameList);
}

s32 _n_timeToSamplesNoRound(s32 micros) {
    f32 tmp = (((f32) micros * (f32) n_syn->outputRate) / D_8002C750) + 0.5f; // 1000000.0f
    return (s32) tmp;
}

s32 _n_timeToSamples( s32 micros)
{
  return _n_timeToSamplesNoRound( micros) & ~0xf;
}

static s32 __n_nextSampleTime(ALPlayer **client) {
    u32 delta = 0x7FFFFFFF; /* max delta for s32 */
    ALPlayer *cl;

    *client = 0;
    for (cl = n_syn->head; cl != 0; cl = cl->next) {
        if ((cl->samplesLeft - n_syn->curSamples) < delta) {
            *client = cl;
            delta = cl->samplesLeft - n_syn->curSamples;
        }
    }
    return (*client)->samplesLeft;
}
