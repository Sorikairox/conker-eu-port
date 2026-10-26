#include <n_libaudio.h>

#include "macros.h"

typedef struct {
  u8 unk0[8][0xEC];
} struct247; // something naudio related? size 0x760

void func_100186DC(void *arg0, void *arg1);

extern N_ALCSPlayer *D_8003C900[];
extern ALCSeq        D_8003CA58[];
extern struct247     D_8003CD48[];

// FIXME: create header file for audio related functions
s32  func_10017A80(N_ALCSPlayer *csp);
void func_10017AF0(N_ALCSPlayer *csp, s32 arg1);
void func_10017B04(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void func_10017B30(N_ALCSPlayer *csp);
void func_10017BB8(N_ALCSPlayer *csp, s32 arg1);
void func_10017C00(N_ALCSPlayer *csp, s32 arg1);
void func_10017C68(N_ALCSPlayer *arg0, s32 arg1, u8 arg2, u8 arg3);
void func_10017CE0(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void func_10017D30(N_ALCSPlayer *arg0, s32 arg1, u8 arg2);
void func_10017D80(N_ALCSPlayer *arg0, u8 arg1, u8 arg2);
void func_10017DF0(N_ALCSPlayer *csp, f32 arg1, f32 arg2);
void func_10017E4C(N_ALCSPlayer *csp, u8 chan, u8 arg2);
void func_10017F10(N_ALCSPlayer *arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4);
void func_10018790(N_ALCSPlayer *arg0, s32 arg1, u32 arg2, u32 arg3);
void func_10018D00(N_ALCSPlayer *arg0, s16 arg1);
void func_10018D50(N_ALCSPlayer *seqp);

typedef struct {
    s32 unk0;
    s32 unk4;
} SeqRom8180;

extern u16 D_8003CDDC[];
extern u8 *D_8003CDE8[];
extern SeqRom8180 *D_8003D0E0;
extern u16 D_8003CCB0[];
void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
void func_10004074(s32 arg0);
s32 func_10004514(s32 devAddr, void *dramAddr, u32 size, s32 arg3);
void func_10018CB0(N_ALCSPlayer *csp, ALCSeq *seq);

// this one is a monster
#ifdef NON_MATCHING
// Audio init: audio heap, synth + audio manager (func_10008F90), the instrument bank, the sequence
// table (sizes rounded up to even into D_8003CCB0), three sequence players and the sound player.
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
    /* 0x00 */ u32 maxStates;
    /* 0x04 */ s32 maxEvents;
    /* 0x08 */ s32 maxSounds;
    /* 0x0C */ ALHeap *heap;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u16 unk14;
} SndpConfig8180;
extern ALHeap D_8003E710;          /* the audio heap */
extern u8 D_80044B20[];            /* its 0x3E000-byte arena */
extern s32 D_8003E708;             /* the first bank of the instrument bank file */
u8 *asset_lookup_rom(s32 *arg0, s32 arg1, ...);
s32 asset_load_into(s32 arg0, s32 arg1, s32 arg2, ...);
s32 asset_get_size(s32 arg0, ...);
void func_10008F90(AmSynConfig *c, s32 pri, AmConfig *arg2);
void func_100046E4(u32 devAddr, u8 *dramAddr, u32 size);
void func_10012934(ALBankFile *file, u8 *table, s32 arg2);
void func_100131FC(ALSeqpConfig *arg0, s32 arg1);
void func_10015550(N_ALCSPlayer *csp, s32 arg1);
s32 func_100155A0(SndpConfig8180 *c);
void func_10017870(u8 arg0);
void func_10017944(s32 arg0, u32 arg1);

void func_10008180(void) {
    AmConfig amc;
    ALSeqpConfig seqc;
    AmSynConfig c;
    SndpConfig8180 sndc;
    ALBankFile *bankFile;
    ALSeqFile *hdr;
    ALSeqFile *seqFile;
    u8 *seqRom;
    u8 *ctlRom;
    u8 *tblRom;
    s32 size;
    s32 len;
    s32 i;

    alHeapInit(&D_8003E710, D_80044B20, 0x3E000);
    c.maxVVoices = 0x2C;
    c.maxPVoices = 0x28;
    c.maxUpdates = 0x40;
    c.maxFXbusses = 2;
    c.dmaproc = NULL;
    c.fxTypes[0] = 6;
    c.fxTypes[1] = 6;
    c.outputRate = 0;
    c.heap = &D_8003E710;
    amc.frequency = 22020;
    amc.unk4 = 1;
    amc.unk8 = 0xBB0;
    c.unk24 = (s32)asset_lookup_rom(NULL, 2, 0x17, 2);
    func_10008F90(&c, 12, &amc);

    size = asset_get_size(2, 0x17, 0);
    bankFile = allocate_memory(size, 0xFF, 2, 0);
    asset_load_into((s32)bankFile, size, 2, 0x17, 0);
    ctlRom = asset_lookup_rom(NULL, 2, 0x17, 1);
    tblRom = asset_lookup_rom(NULL, 2, 0x17, 2);
    func_10012934(bankFile, tblRom, (s32)ctlRom);
    D_8003E708 = (s32)bankFile->bankArray[0];

    seqRom = asset_lookup_rom(NULL, 2, 0x17, 3);
    hdr = allocate_memory(0x10, 1, 2, 0);
    func_100046E4((u32)seqRom, (u8 *)hdr, 0x10);
    size = hdr->seqCount * 8 + 4;
    func_10004074((s32)hdr);
    D_8003D0E0 = allocate_memory(size, 0xFF, 2, 0);
    func_100046E4((u32)seqRom, (u8 *)D_8003D0E0, (size + 0xF) & ~0xF);
    alSeqFileNew((ALSeqFile *)D_8003D0E0, seqRom);
    seqFile = (ALSeqFile *)D_8003D0E0;
    for (i = 0; i < 150; i++) {
        len = seqFile->seqArray[i].len & 0xFFFF;
        D_8003CCB0[i] = len;
        if (len & 1) {
            D_8003CCB0[i] = len + 1;
        }
    }

    seqc.maxVoices = 0x2C;
    seqc.maxEvents = 0x68;
    seqc.debugFlags = 0;
    seqc.maxChannels = 0x10;
    seqc.heap = &D_8003E710;
    func_100131FC(&seqc, 0x58);
    for (i = 0; i < 3; i++) {
        D_8003CDDC[i] = 0xFFFF;
        D_8003CDE8[i] = NULL;
        D_8003C900[i] = alHeapDBAlloc(NULL, 0, &D_8003E710, 1, sizeof(N_ALCSPlayer));
        n_alCSPNew(D_8003C900[i], &seqc);
        func_10015550(D_8003C900[i], (s32)bankFile->bankArray[0]);
    }

    sndc.maxEvents = 0x40;
    sndc.maxStates = 0x40;
    sndc.maxSounds = 0x14;
    sndc.unk14 = 8;
    sndc.heap = &D_8003E710;
    sndc.unk10 = (s32)tblRom;
    func_100155A0(&sndc);
    func_10017870(4);
    func_10017944(0, 2);
    func_10017944(1, 2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/init_8180/func_10008180.s")
#endif
void func_100084D8(u8 idx) {
    if ((n_alCSPGetState(D_8003C900[idx]) == 0) || (n_alCSPGetState(D_8003C900[idx]) == 3)) {
        func_10017AA0(D_8003C900[idx]);
    }
}

s32 func_1000853C(u8 idx) {
    return n_alCSPGetState(D_8003C900[idx]);
}

void func_10008570(u8 idx, s32 arg1) { // arg1 is OSMesgQueue ?
    func_10017AF0(D_8003C900[idx], arg1);
}

void func_100085A4(s32 arg0, s32 arg1, s32 arg2) {
}

void func_100085B8(u8 idx, s32 arg1, u8 arg2) {
    func_10017B04(D_8003C900[idx], arg1, arg2);
}

void func_100085F8(u8 idx, s32 arg1) {
    func_10017BB8(D_8003C900[idx], arg1);
}

void func_1000862C(u8 idx, s32 arg1) {
    func_10017C00(D_8003C900[idx], arg1);
}

void func_10008660(u8 idx, u8 chan, u8 arg2, s32 arg3) {
    if (arg3 > 0) {
        arg3 = (arg3 * 10) / 50;
        if (arg3 == 0) {
            arg3 = 1; // final?
        } else if (arg3 >= 128) {
            arg3 = 127; // more to come?
        }
    } else {
        arg3 = 0; // empty?
    }
    func_10017C68(D_8003C900[idx], chan, arg2, arg3);
}

void func_100086FC(u8 idx, u8 arg1, u8 arg2) {
    func_10017CE0(D_8003C900[idx], arg1, arg2);
}

void func_10008744(u8 idx, u8 arg1, u8 arg2) {
    func_10017D80(D_8003C900[idx], arg1, arg2);
}

void func_10008790(u8 idx, s32 mask, u8 arg2, s32 arg3) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            func_10008660(idx, chan, arg2, arg3);
        }
    }
}

void func_10008824(u8 idx, u8 arg1, u8 arg2) {
    func_10017D30(D_8003C900[idx], arg1, arg2);
}

void func_1000886C(u8 idx, s32 mask, u8 arg2) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            func_10008824(idx, chan, arg2);
        }
    }
}

void func_100088F0(u8 idx, s32 mask, s32 enable) {
    s32 chan;

    for (chan = 0; chan < 16; chan++)
    {
        if ((1 << chan) & mask) {
            if (enable) {
                func_1000862C(idx, chan);
            } else {
                func_100085F8(idx, chan);
            }
        }
    }
}

void func_10008988(u8 idx, s32 mask, s32 enable) {
    s32 chan;

    for(chan = 0; chan < 16; chan++) // 16 channels
    {
        if ((1 << chan) & mask) {
            if (enable != 0) {
                D_8003C900[idx]->chanMask |= mask; // enable
            } else {
                D_8003C900[idx]->chanMask &= (mask ^ 0xFFFF); // disable
            }
        }
    }
}

// is this n_alCSPGetChlVol ?
u8 func_10008A4C(u8 idx, u8 chan) {
    return D_8003C900[idx]->chanState[chan].unkD; // do we assume this is volume?
}

void func_10008A94(u8 idx, s32 mask, s32 arg2) {
    s32 chan;

    for(chan = 0; chan < 16; chan++)
    {
        if (((1 << chan) & mask) != 0) {
            func_10017E4C(D_8003C900[idx], chan, arg2);
        }
    }
}

void func_10008B2C(u8 idx) {
      n_alCSPGetTempo(D_8003C900[idx]);
}

void func_10008B60(u8 idx, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    func_10017F10(D_8003C900[idx], arg1, arg2, arg3, arg4);
}

void func_10008BC0(u8 idx, f32 arg1, f32 arg2) {
    func_10017DF0(D_8003C900[idx], arg1, arg2);
}

void func_10008C04(u8 idx, u8 arg1, s32 arg2) {
    func_10018790(&D_8003CA58[idx], &D_8003CD48[idx], arg1, arg2);
}

void func_10008C6C(u8 idx, u8 arg1) {
    func_100186DC(&D_8003CA58[idx], D_8003CD48[idx].unk0[arg1]);
}

// s129: (re)start sequence player idx with sequence arg1: wait for the player to stop, load the
// sequence (cached in D_8003CDE8[idx], id in D_8003CDDC[idx]) and start it

s32 func_10008CE8(u8 idx, s32 arg1) {
    s32 devAddr;
    u32 i;

    i = 0;
    func_10018C60(D_8003C900[idx]);
    while (n_alCSPGetState(D_8003C900[idx]) != 0 && i < 2000000) {
        i++;
    }
    if (i >= 2000000) {
        func_10018C60(D_8003C900[idx]);
        while (n_alCSPGetState(D_8003C900[idx]) != 0 && i < 4000000) {
            i++;
        }
    }
    if (arg1 != D_8003CDDC[idx]) {
        if (D_8003CDE8[idx] != NULL) {
            func_10004074((s32)D_8003CDE8[idx]); // the int conversion gives the ref v0 load + move
            D_8003CDE8[idx] = NULL;
        }
        devAddr = D_8003D0E0[arg1].unk4;
        D_8003CDE8[idx] = allocate_memory(D_8003CCB0[arg1], 0xFF, 2, 2);
        if (D_8003CDE8[idx] == NULL) {
            return -1;
        }
        func_10004514(devAddr, D_8003CDE8[idx], ALIGN16(D_8003CCB0[arg1]), 1);
        D_8003CDDC[idx] = arg1;
    }
    n_alCSeqNew(&D_8003CA58[idx], D_8003CDE8[idx]);
    func_10018CB0(D_8003C900[idx], &D_8003CA58[idx]);
    func_10017B30(D_8003C900[idx]);
    return 0;
}

void func_10008EE0(u8 idx, s32 arg1) {
    func_10018D00(D_8003C900[idx], arg1);
}

void func_10008F24(u8 idx) {
    // AL_TRACK_END
    func_10018C60(D_8003C900[idx]);
}

void func_10008F58(u8 idx) {
    func_10018D50(D_8003C900[idx]);
}
