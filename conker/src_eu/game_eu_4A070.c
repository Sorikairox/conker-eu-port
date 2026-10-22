#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15080628(void);
u8 *func_151149AC(u8);
extern u8 D_800C3938[][0x19];
void func_15021834(struct127 *, s32, s32);
extern s32 D_eu_800C3A60;
extern s32 D_800C39D0;
extern s32 D_800C3A68;
extern u16 *D_800C39E8[];
extern u16 *D_800C39F0[];
extern s32 D_800C3B98[][30];
extern s32 D_800C3AA8[][30];
s32 func_15022A8C(s32 *);
struct127 *func_15083E90(u8);
#endif
// hoisted forward declaration(s) for func_1501E7A8
s32 func_1507EE9C(struct127 *);


#ifdef NON_MATCHING
/* End of frame (P13, hand C): closes the display list (rolled back to the per-buffer reserve D_800BE9D8 when it
 * overflowed, cut at 0x190 commands before the end otherwise), fills the gfx OSScTask D_800BEEF8[idx] (0x60
 * bytes), sends it to the scheduler's gfx queue and, when arg1 != 0, flips the DL buffer index D_800BE9C0.
 * Names are the asm's (several are US names remapped by undefined_syms.eu.txt). */
extern s32 *D_800BEEF4;           /* the task being filled */
extern u8 D_800BEEF8[];           /* OSScTask[2], 0x60 each */
extern u8 D_10029400[];           /* rspboot */
extern u8 D_100294D0[];
extern u8 D_800BEFC0;
extern u8 D_800BEA37;
extern u8 D_8003A948[];           /* yield buffer */
extern OSMesgQueue D_800BEE30;    /* main-loop queue */
extern u8 D_800BEE88[];           /* done messages, 0x20 each */
extern OSMesgQueue D_8003B548;    /* scheduler gfx queue */
extern s16 D_800BEEC8;
extern s32 D_800BEFD0;            /* ucode text / data pairs */
extern s32 D_800C1480;
extern u8 *D_800BEFBC;
extern u8 *D_800BEEF0;
void func_1501A39C(void);
void func_1501CC1C(void);

void func_eu_1501C860(s32 arg0, s32 arg1) {
    s32 *task;
    s32 cap;
    s32 n;
    s32 base;
    s32 *g;

    task = (s32 *)(D_800BEEF8 + D_800BE9C0 * 0x60);
    D_800BEEF4 = task;
    task[0] = 0;
    cap = ((s32)D_800BEDE8[1] - (s32)D_800BEDE8[0]) >> 3;
    base = (s32)D_800BEDE8[D_800BE9C0];
    n = (D_800BE9D0 - base) >> 3;
    if (n < 0 || cap < n) {
        func_1501A39C();
        D_800BE9D0 = D_800BE9D8[D_800BE9C0];
        g = (s32 *)D_800BE9D0; D_800BE9D0 += 8; g[1] = 0; g[0] = 0xE9000000;
        g = (s32 *)D_800BE9D0; D_800BE9D0 += 8; g[1] = 0; g[0] = 0xDF000000;
        base = (s32)D_800BEDE8[D_800BE9C0];
        n = (D_800BE9D0 - base) >> 3;
    }
    if (n < 0 || cap - 0x190 < n) {
        D_800BE9D0 = base + (cap - 0x190) * 8;
        g = (s32 *)D_800BE9D0; D_800BE9D0 += 8; g[1] = 0; g[0] = 0xE9000000;
        g = (s32 *)D_800BE9D0; D_800BE9D0 += 8; g[1] = 0; g[0] = 0xDF000000;
        base = (s32)D_800BEDE8[D_800BE9C0];
    }
    D_800BEEF4[0x48 / 4] = base;
    D_800BEEF4[0x4C / 4] = ((D_800BE9D0 - (s32)D_800BEDE8[D_800BE9C0]) >> 3) << 3;
    func_1501CC1C();
    D_800BEEF4[0x18 / 4] = 1;                                  /* M_GFXTASK */
    D_800BEEF4[0x1C / 4] = 4;                                  /* OS_TASK_LOADABLE */
    D_800BEEF4[0x20 / 4] = (s32)D_10029400;
    D_800BEEF4[0x24 / 4] = D_100294D0 - D_10029400;
    if (D_800BEFC0 != 0) {
        D_800BEEF4[0x28 / 4] = (s32)&D_800C1480;
        D_800BEEF4[0x30 / 4] = (s32)D_800BEFBC;
    } else {
        D_800BEEF4[0x28 / 4] = (s32)&D_800BEFD0;
        D_800BEEF4[0x30 / 4] = (s32)D_800BEEF0;
    }
    D_800BEEF4[0x34 / 4] = 0x800;
    D_800BEEF4[0x38 / 4] = (s32)&D_800CC230;
    D_800BEEF4[0x3C / 4] = 0x400;
    D_800BEEF4[0x40 / 4] = D_80038090;
    D_800BEEF4[0x44 / 4] = D_80038094;
    D_800BEEF4[0x50 / 4] = (s32)D_8003A948;
    D_800BEEF4[0x54 / 4] = 0xC00;
    D_800BEEF4[0x0C / 4] = 0x23;
    if (arg1 != 0) {
        D_800BEEF4[0x0C / 4] |= 0x40;
    }
    if (D_800BEA37 != 0) {
        D_800BEEF4[0x0C / 4] |= (D_80082FA0 + 1) << 16;
        D_800BEA37 = 0;
    }
    D_800BEEF4[0x58 / 4] = (s32)&D_800BEE30;
    D_800BEEF4[0x5C / 4] = (s32)(D_800BEE88 + D_800BE9C0 * 0x20);
    D_800BEEF4[0x10 / 4] = D_8002AAE8[D_800BE9C0];
    osWritebackDCacheAll();
    osSendMesg(&D_8003B548, (OSMesg)D_800BEEF4, OS_MESG_BLOCK);
    if (arg1 != 0) {
        D_800BE9C0 ^= 1;
    }
    D_800BEEC8++;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_eu_1501C860.s")
#endif
#ifdef NON_MATCHING
extern s32 D_2D810;
extern s8 D_80084400;
extern s8 D_80084404;
extern s32 D_80084408;
extern u8 *D_800BEEF0;
extern s32 D_800BEFB8;
extern u8 *D_800BEFBC;
extern s32 D_800BEFD0;
extern s32 D_800C1480;

void func_1501CC1C(void) {
    s32 sp2C;
    s32 sp28;
    u8 *sp20;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_t1;
    u8 var_t0;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_v0;
    u8 *temp_v0_2;

    var_t1 = 4;
    var_t0 = D_800B0DF0->pad2A[1];
    if ((s32) var_t0 >= 2) {
        var_t0 -= 2;
        var_t1 = 0;
    }
    if (D_800BEFB8 == 1) {
        var_t0 += 2;
    }
    temp_v0 = ((s32 *)((u8 *)&D_80084408 + (var_t0 * 0x10)));
    if ((var_t0 != D_80084400) || (var_t1 != D_80084404)) {
        temp_v1 = (*(s32 *)((u8 *)temp_v0 + 0));
        sp20 = temp_v0;
        sp2C = (s32) var_t0;
        sp28 = var_t1;
        func_10004514((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1))), &D_800C1480, (*(s32 *)((u8 *)temp_v0 + 4)) - temp_v1, 1);
        temp_v1_2 = (*(s32 *)((u8 *)temp_v0 + 8));
        temp_a1 = ((s32 *)((u8 *)&D_800C1480 + ((*(s32 *)((u8 *)temp_v0 + 4)) - (*(s32 *)((u8 *)temp_v0 + 0)))));
        D_800BEFBC = temp_a1;
        func_10004514((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_2))), temp_a1, (*(s32 *)((u8 *)temp_v0 + 0xC)) - temp_v1_2, 1);
        D_80084400 = (s8) var_t0;
        temp_v0_2 = ((s32 *)((u8 *)&D_80084408 + ((var_t0 + var_t1) * 0x10)));
        D_80084404 = (s8) var_t1;
        temp_v1_3 = (*(s32 *)((u8 *)temp_v0_2 + 0));
        sp20 = temp_v0_2;
        func_10004514((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_3))), &D_800BEFD0, (*(s32 *)((u8 *)temp_v0_2 + 4)) - temp_v1_3, 1);
        temp_a1_2 = ((s32 *)((u8 *)&D_800BEFD0 + ((*(s32 *)((u8 *)temp_v0_2 + 4)) - (*(s32 *)((u8 *)temp_v0_2 + 0)))));
        D_800BEEF0 = temp_a1_2;
        temp_v1_4 = (*(s32 *)((u8 *)temp_v0_2 + 8));
        func_10004514((s32) (((s32 *)((u8 *)&D_2D810 + temp_v1_4))), temp_a1_2, (*(s32 *)((u8 *)temp_v0_2 + 0xC)) - temp_v1_4, 1);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CC1C.s")
#endif
#ifdef NON_MATCHING
extern void *D_800C3D80[][30];   /* 16-byte block per actor */

/* Clears (0xFF) the 16-byte block of every actor of sequence slot `slot`. */
void func_1501CDA0(s32 slot) {
    s32 i;
    s32 j;

    for (i = 0; i < D_800C3A5A[slot]; i++) {
        for (j = 0; j < 16; j++) {
            ((u8 *)D_800C3D80[slot][i])[j] = 0xFF;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CDA0.s")
#endif

#ifdef NON_MATCHING
/* Length of cutscene slot `slot` (P84 browser blocker: func_1501E364 waits for it): the end frame of the first
 * camera track when it has one (record +0x12 != -9999 and the slot's first camera word >= 4), else the latest end
 * (+0x0A) of the camera tracks of the active actors, else the last key (frame at -2 of key k, D_800C39F0 count)
 * of their actor tracks. D_800C3A68 = the length in 60 Hz frames, D_eu_800C3A60[slot] = it in 50 Hz frames
 * (EU: * 50 / 60). */
void func_1501CE34(s32 slot) {
    s32 *len = &(&D_eu_800C3A60)[slot];
    u16 *cams;
    u8 n;
    s32 i;
    s32 found;
    s32 end;
    s32 v;
    u16 k;

    *len = 0;
    D_800C3A68 = 0;
    n = D_800C3A5A[slot];
    if (n == 0) {
        return;
    }
    cams = D_800C39F8[slot];
    if (cams[0] >= 4) {
        v = *(s16 *)((u8 *)D_800C3AA8[slot][0] + 0x12);
        if (v != -9999) {
            D_800C3A68 = v;
            *len = v * 50 / 60;
            return;
        }
    }
    found = FALSE;
    for (i = 0; i < n; i++) {
        if (D_800C39E8[slot][i] != 0 && cams[i] != 0) {
            v = *(s16 *)((u8 *)D_800C3AA8[slot][i] + 0xA);
            if (*len < v) {
                *len = v;
                found = TRUE;
            }
        }
    }
    if (found) {
        end = *len;
        D_800C3A68 = end;
        *len = end * 50 / 60;
        return;
    }
    end = *len;
    for (i = 0; i < n; i++) {
        if (D_800C39E8[slot][i] != 0) {
            k = D_800C39F0[slot][i];
            if (k != 0) {
                v = *(s16 *)((u8 *)D_800C3B98[slot][i] + k * 8 - 2);
                if (end < v) {
                    *len = v;
                    end = v;
                }
            }
        }
    }
    D_800C3A68 = end;
    *len = end * 50 / 60;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CE34.s")
#endif

s32 func_1501D064(s32 arg0) {
    s32 sum = 0;
    s32 i;

    for (i = 0; i < D_800C3A5A[arg0]; i++) {
        sum += D_800C39F8[arg0][i];
    }
    return sum;
}

#ifdef NON_MATCHING
/* P87: declarations for func_1501D044 / func_1501DB18 / func_1501E888 */
extern s32 D_800C39D0;
extern s32 D_800C39D8[];
extern u8 D_800C39E0[];
extern u16 D_800C40AE;
extern void *D_800C4170;
extern u8 D_800C3A18;
extern f32 D_800C39C4;
extern f32 D_800C3A6C;
extern f32 D_800C3A70;
extern f32 D_800C3A74;
extern f32 D_800C3A94;
extern f32 D_800C3A98;
extern u8 D_800C3A78;
extern u8 D_800C3A7A;
extern u8 D_800C3A7C;
extern u8 D_800C3A7E;
extern u8 D_800C3A80;
extern u8 D_800C3A82;
extern u8 D_800C3A84;
extern u8 D_800C3A86;
extern u8 D_800C40AC;
extern u8 D_800C40AD;
extern u8 D_800C39E2;            /* queued follow-up scene + 1 */
extern u8 D_800C39E3;            /* its level */
extern u8 D_eu_800C3E78;
extern u8 D_800C40AA;
extern u8 D_800C40AB;
extern s32 D_800C3A9C;
extern u8 D_800C3AA0;
extern u8 D_800C3A92;
extern u8 D_800C40BD;
extern s16 D_800C40BE;
extern s8 D_80090124;
extern u8 D_800C40B9;
extern u8 D_800C39C9;
extern u8 D_800C40BC;
extern u8 D_800C39CA;
extern u8 D_800844A0[][3];       /* RGB rows */
void func_15023464(void);
s32 func_15023C60(u32, s32, s32, u8 **, s32, s32, s32, s32, s32, s32, s32);
void func_1517F3B0(s32, s32, s32, s32, s8, s32);
void func_15169040(s32, u8);
void func_1502348C(void);
void func_15023684(s32);
void func_1501EA84(s32);
void func_1501E5AC(s32);
void func_1510B8AC(s32, f32, f32, f32);
void func_1501E7A8(s32);
void func_1501D348(s32, s32, s32, s32, s32);
#endif
#ifdef NON_MATCHING
/* Resets cutscene slot `slot` and the shared cutscene state (func_1501D348, before a scene is loaded): no
 * script position / script wait (D_800C39D8 = -100), slot not loaded, no actors, camera actor D_800C3A18 =
 * 0xFF (func_15020F6C picks it again), cleared look / fade state, D_800C3A94 / D_800C3A98 = 999, then
 * func_15023464. */
void func_1501D044(s32 slot) {
    D_800C39D8[slot] = -100;
    (&D_800C39D0)[slot] = 0;
    D_800C39E0[slot] = 0;
    D_800C40AE = 0;
    D_800C3A5A[slot] = 0;
    (&D_800C35EA)[slot] = 0;
    D_800C4170 = NULL;
    D_800C3A18 = 0xFF;
    D_800C3A6C = 0.0f;
    D_800C3A70 = 0.0f;
    D_800C3A74 = 0.0f;
    (&D_800C3A78)[slot] = 0;
    (&D_800C3A7A)[slot] = 0;
    (&D_800C3A7C)[slot] = 1;
    (&D_800C3A7E)[slot] = 0;
    (&D_800C3A80)[slot] = 0;
    (&D_800C3A82)[slot] = 0;
    (&D_800C3A84)[slot] = 0;
    D_800C3638 = 0;
    D_800C3A86 = 0;
    D_800C40AC = 0;
    D_800C40AD = 0;
    D_800C39E2 = 0;
    D_eu_800C3E78 = 0;
    D_800C39C4 = 0.0f;
    D_800C40AA = 0xFF;
    D_800C40AB = 0;
    D_800C3A94 = 999.0f;
    D_800C3A98 = 999.0f;
    D_800C3A9C = 0;
    D_800C3AA0 = 0;
    D_800C3A92 = 0;
    D_800C40BD = 100;
    D_800C40BE = -1;
    func_15023464();
    D_80090124 = 0;
    D_800C3670 = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D044.s")
#endif

s32 func_1502B6BC(s32 *, s32, s32 *, s32, s32, s32, s32);
extern s32 D_800C3A88;

s32 func_1501D240(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp34;
    s32 sp30;
    s32 temp_v0;

    temp_v0 = func_1502B6BC(&sp30, 0, &sp34, 3, 6, arg0, arg1);
    if (temp_v0 != 0) {
        (&D_800C3A88)[arg2] = temp_v0;
    } else {
        (&D_800C3A88)[arg2] = 0;
    }
    return temp_v0;
}

void func_1501D2C4(s32 arg0, s32 arg1) {
    if (D_800C3670 == 0) {
        D_800C3A60[arg0] |= 1ULL << arg1;
    }
}

s32 func_1501D330(s32 arg0, s32 arg1) {
    u64 bit;
    if (D_800C3670 != 0) {
        return 1;
    }
    if ((D_800C3A60[arg0] & (1ULL << arg1)) != 0) {
        return 1;
    }
    return 0;
}

#ifdef NON_MATCHING
/* Load scene `scene` (asset group 3, type 6, found by func_1501D240) of level `level` into sequence slot `slot`.
 * Skipped while the slot is already loaded (D_800C35EA[slot] == 1) or a level change is pending (D_800C35C4).
 * For another level than the current one (D_800BE9F0) the level change is requested instead (func_1501C710;
 * D_800C35C4 = scene + 1, D_800C35C5 = "the slot was empty").
 * The asset is a header {u16 nActors, nCameras, nSounds, nWords} followed by 8-byte records {s32 value, u32 bits}
 * (record 0 is the header pointer itself): nActors actor records, one record for D_800C3A10[slot], nActors
 * more (not read here), nCameras, nSounds, then nWords plain words. The per-slot tables (u16 arrays of
 * bits >> 3, the 30-entry value tables, actor state blocks) are allocated and filled, the optional setup
 * callback D_8008448C[callback] runs, and the sequence is started (func_1501CDA0 ... func_1501DB18). */
typedef void (*SceneSetupFunc)(s32 level, s32 scene, s32 slot, s32 arg);
typedef struct {
    s32 value;
    u32 bits;
} SceneRecord;
typedef struct {
    u8 pad0[4];
    void *keys;        /* +0x04: (count of the actor's u16 entry) words */
    u8 pad8[0x30];
    void *state;       /* +0x38: 0x194 bytes */
    u8 pad3C[4];
} SceneActor;          /* 0x40 bytes, D_800C3E70[slot][actor] */

void *allocate_memory(s32, s32, s32, s32);
void func_1501C710(s32, s32, s32, s32, s32);
void func_1501D044(s32);
void func_1501CDA0(s32);
void func_1501CE34(s32);
void func_15022C4C(s32);
void func_15020430(s32, s32);
void func_15023980(void);
void func_150222DC(s32);
void func_150222F0(s32);
void func_1501E888(s32, s32);
void func_1502457C(s32, s32);
void func_1501ECA4(s32);
void func_150228F0(s32);
void func_150227FC(s32);
void func_150225D0(s32);
void func_15020F6C(s32);
void func_1501DB18(s32);
extern u8 D_800C39C8;
extern u8 D_800C40B8;
extern u16 *D_800C39E8[];        /* actors: bits >> 3 */
extern u16 *D_800C39F0[];        /* cameras */
extern s32 *D_800C3A00[];        /* plain words */
extern SceneActor *D_800C3E70[];
extern void *D_800C3D80[][30];   /* 16-byte block per actor */
extern s32 D_eu_800C3C88[][30];  /* actor record values */
extern s32 D_800C3B98[][30];     /* camera record values */
extern s32 D_800C3AA8[][30];     /* sound record values */
extern SceneSetupFunc D_8008448C[];
extern u16 D_800C40BA;
extern void *D_800C4170;
extern s32 D_800C39D0;
extern u8 *D_800C3A10[];        /* the record after the actors */

void func_1501D348(s32 level, s32 scene, s32 slot, s32 callback, s32 callbackArg) {
    u8 *loaded;
    u8 state;
    SceneRecord *rec;
    u16 *hdr;
    s32 size;
    s32 n;
    s32 i;
    s32 k;

    loaded = &D_800C35EA + slot;
    state = *loaded;
    if (state == 1 || D_800C35C4 != 0) {
        return;
    }
    D_800C3C90 = callback;
    D_800C3C94 = callbackArg;
    if (level != D_800BE9F0) {
        D_800C35C4 = scene + 1;
        func_1501C710(1, level, 0, 0, 0);
        if (*loaded != 0) {
            D_800C35C5 = 0;
        } else {
            D_800C35C5 = 1;
        }
        return;
    }

    (&D_800C3A08)[slot] = scene;
    if (state != 2) {
        D_800C39C8 = D_800BE9F0;
        D_800C40B8 = scene;
    }
    func_1501D044(slot);
    if (func_1501D240(level, scene, slot) == 0) {
        return;
    }
    rec = ((SceneRecord **)&D_800C3A88)[slot];
    hdr = (u16 *)rec[0].value;

    /* the per-slot tables */
    D_800C39E8[slot] = allocate_memory(hdr[0] * 2, 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        D_800C39E8[slot][i] = rec[1 + i].bits >> 3;
    }
    size = ((hdr[1] < hdr[0]) ? hdr[0] : hdr[1]) * 2;
    D_800C39F0[slot] = allocate_memory(size, 1, 0, 0);
    bzero(D_800C39F0[slot], size);
    size = ((hdr[2] < hdr[0]) ? hdr[0] : hdr[2]) * 2;
    D_800C39F8[slot] = allocate_memory(size, 1, 0, 0);
    bzero(D_800C39F8[slot], size);
    D_800C3A00[slot] = allocate_memory(hdr[3] * 4, 1, 0, 0);
    D_800C3E70[slot] = allocate_memory(hdr[0] * sizeof(SceneActor), 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        if (D_800C39E8[slot][i] != 0) {
            D_800C3E70[slot][i].keys = allocate_memory(D_800C39E8[slot][i] * 4, 1, 0, 0);
            D_800C3E70[slot][i].state = allocate_memory(0x194, 1, 0, 0);
        }
    }
    (&D_800C3958)[slot] = allocate_memory(hdr[0] * 0x44, 1, 0, 0);
    for (i = 0; i < hdr[0]; i++) {
        D_800C3D80[slot][i] = allocate_memory(0x10, 1, 0, 0);
    }
    for (i = 0; i < hdr[0]; i++) {
        D_800C39F8[slot][i] = 0;
        D_800C39F0[slot][i] = 0;
        D_800C39E8[slot][i] = 0;
    }
    D_800C3A5A[slot] = hdr[0];

    /* the records */
    k = 1;
    for (i = 0; i < hdr[0]; i++, k++) {
        D_800C39E8[slot][i] = rec[k].bits >> 3;
        D_eu_800C3C88[slot][i] = rec[k].value;
    }
    D_800C3A10[slot] = (u8 *)rec[k].value;
    k += hdr[0];
    for (i = 0; i < hdr[1]; i++, k++) {
        D_800C39F0[slot][i] = rec[k].bits >> 3;
        D_800C3B98[slot][i] = rec[k].value;
    }
    for (i = 0; i < hdr[2]; i++, k++) {
        D_800C39F8[slot][i] = rec[k].bits >> 3;
        D_800C3AA8[slot][i] = rec[k].value;
    }
    for (i = 0; i < hdr[3]; i++) {
        D_800C3A00[slot][i] = rec[k + i].value;
    }

    if (callback != 0) {
        D_8008448C[callback](level, scene, slot, callbackArg);
    }
    n = func_1501D064(slot);
    D_800C40BA = n;
    D_800C4170 = allocate_memory((u16)n * 12, 1, 0, 0);
    (&D_800C39D0)[slot] = 0;

    /* start the sequence */
    func_1501CDA0(slot);
    func_1501CE34(slot);
    func_15022C4C(slot);
    for (i = 0; i < D_800C3A5A[slot]; i++) {
        func_15020430(i, slot);
    }
    func_15023980();
    *loaded = 1;
    D_800C3638 = 1;
    func_150222DC(slot);
    func_150222F0(slot);
    if (D_800C3A5A[slot] == 0) {
        func_1501E888(0, slot);
    }
    func_1502457C(1, slot);
    func_1501ECA4(slot);
    func_150228F0(slot);
    func_150227FC(slot);
    func_150225D0(slot);
    func_15020F6C(slot);
    D_800DBFF4[0] = 4;
    func_1501DB18(slot);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D348.s")
#endif

#ifdef NON_MATCHING
/* Start of cutscene slot `slot`: scans the sound / event track (D_800C3AA8[slot][i] + 0x18) of every actor with
 * func_15023C60 (type 5) for the event codes 0x1E, 0x0E, 0x68, 0x44 (flags D_800C40B9, D_800C40BC, D_800C39CA,
 * D_800C39C9), 0x77 (start position D_800C40AE = its frame) and 1 (the earliest one sets the screen colour
 * func_1517F3B0 from the RGB row D_800844A0[key[5]], key +6 == 1: with fade). The script position
 * D_800C39D0[slot] starts at D_800C40AE. */
void func_1501DB18(s32 slot) {
    u8 *found;
    u8 *rec;
    u8 *rgb;
    s32 best;
    s32 v;
    s32 i;

    D_800C40B9 = 0;
    D_800C39C9 = 0;
    D_800C40BC = 0;
    D_800C39CA = 0;
    D_800C40AE = 0;
    best = -1;
    for (i = 0; i < D_800C3A5A[slot]; i++) {
        rec = (u8 *)D_800C3AA8[slot][i];
        if (rec == NULL) {
            continue;
        }
        found = NULL;
        func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0x1E, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C40B9 = 1;
        }
        found = NULL;
        func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0xE, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C40BC = 1;
        }
        found = NULL;
        func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0x68, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C39CA = 1;
        }
        found = NULL;
        func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0x44, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C39C9 = 1;
        }
        found = NULL;
        v = func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 0x77, 0, 0, 0, 0, slot);
        if (found != NULL) {
            D_800C40AE = v;
        }
        found = NULL;
        v = func_15023C60((u32)(rec + 0x18), 5, i, &found, 1, 1, 1, 0, 0, 0, slot);
        if (found != NULL && (best == -1 || v < best)) {
            best = v;
            rgb = D_800844A0[(s8)found[5]];
            if (*(s16 *)(found + 6) == 1) {
                func_1517F3B0(rgb[0], rgb[1], rgb[2], 0, 1, 0);
            } else {
                func_1517F3B0(rgb[0], rgb[1], rgb[2], 0, 0, 0);
            }
        }
    }
    (&D_800C39D0)[slot] = D_800C40AE;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DB18.s")
#endif

#ifdef NON_MATCHING
/* Starts cutscene slot `slot`: script position D_800C39D0[slot] = start D_eu_800C3A60[slot] + D_800BEA08, runs the
 * camera / actor tracks once (func_1501ECA4, func_15020F6C, with func_1502457C around them), then gives every
 * live object that takes part (func_15022A8C, current object index in D_800C3E78) its first actor frame
 * (func_15021834(obj, slot, -1)) and ends with func_1501E888(1, slot). */
void func_1501DE84(s32 slot) {
    struct127 *obj;
    s32 i;

    (&D_800C39D0)[slot] = (&D_eu_800C3A60)[slot] + D_800BEA08;
    func_1502457C(1, 0);
    func_1501ECA4(0);
    func_1502457C(0, 0);
    func_15020F6C(0);
    for (i = 0, obj = D_800CC2D0; i < 25; i++, obj++) {
        if (*(s32 *)obj != 0) {
            D_800C3E78 = i;
            if (func_15022A8C((s32 *)obj) != 0) {
                func_15021834(obj, slot, -1);
            }
        }
    }
    func_1501E888(1, slot);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DE84.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DF70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E0C8.s")

s32 func_1000E17C(void);
void func_1501DF70(s32);
s32 func_1501E0C8(s32, u8 *);
s32 func_151F2CDC(void);
extern s8 D_80090124;
extern s32 D_800C39D0;
extern u8 D_800C40A9;
extern s32 D_eu_800C3A60;

void func_1501E220(s32 arg0) {
    if (D_800C3C88 == 0) {
        if (((&D_800C35EA)[arg0] == 1) && (func_1501E0C8(arg0, &D_800C3C88) != 0)) {
            D_80090124 = 0;
            if (((*(&D_eu_800C3A60 + arg0) - *(&D_800C39D0 + arg0)) >= 0x4C)) {
                D_800C3C88 = 1;
                D_800C40A9 = 0x19;
                func_1517F3B0(0, 0, 0, 0x19, 1, 0);
                func_1000E17C();
                if ((func_151F2CDC() == 1) || (func_151F2CDC() == 2)) {
                    func_151F2D6C(0, 0x2B02);
                }
            }
        }
    } else if (D_800C3C88 == 1) {
        if (D_800BEA08 < (s32) D_800C40A9) {
            D_800C40A9 -= D_800BEA08;
            return;
        }
        D_800C40A9 = 0;
        D_800C3C88 = 2;
        /* P82: the asm leaves arg0 (the slot) in a0; func_1501DF70 reads it (arity scan row, dropped argument) */
        func_1501DF70(arg0);
        D_800C3C88 = 0;
    }
}

#ifdef NON_MATCHING
void func_1501E46C(s32);
void func_1501E888(s32, s32);
void func_1501ECA4(s32);
void func_15020F6C(s32);
void func_1502457C(s32, s32);
extern u8 D_800C40AC;

void func_1501E364(s32 arg0) {
    s32 var_s1;
    u8 *temp_s0;

    var_s1 = arg0;
loop_1:
    temp_s0 = &(&D_800C35EA)[var_s1];
    if ((*temp_s0 == 1) && ((&D_800C39D0)[var_s1] >= (&D_eu_800C3A60)[var_s1])) {
        if (D_800C40AC == 0) {
            func_1501E888(0, var_s1);
            if (*temp_s0 == 1) {
                var_s1 = 0;
                func_1501E46C(0);
                func_1502457C(1, 0);
                func_1501ECA4(0);
                func_1502457C(0, 0);
                func_15020F6C(0);
                goto loop_1;
            }
        } else {
            D_800C40AC = 2;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E364.s")
#endif
#ifdef NON_MATCHING
extern s32 D_800C39D8[];
extern u8 D_800C39E0[];
extern u16 D_800C40AE;
extern u8 D_eu_800C3E78;

/* Per-player counter step (P15, hand C from the asm): remembers the previous value D_800C39D8[i] of
 * D_800C39D0[i], and for an active player (D_800C35EA[i] == 1) advances it by D_800BEA08 (player 0
 * only when D_800BEAC0 == 0), clamped to D_eu_800C3A60[i]. */
void func_1501E46C(s32 i) {
    s32 *cur = &(&D_800C39D0)[i];
    s32 lim;

    if (D_eu_800C3E78 != 0) {
        D_eu_800C3E78--;
    }
    D_800C39D8[i] = *cur;
    if ((&D_800C35EA)[i] != 1) {
        return;
    }
    func_1501E220(i);
    if (i != 0 || D_800BEAC0 == 0) {
        *cur += D_800BEA08;
    }
    if (D_800C39E0[i] == 0 && D_800C40AE == D_800C39D8[i] && D_800C40AE != *cur) {
        D_800C39D8[i] = -1;
    }
    if (func_151F2CDC() == 1) {
        func_15080628();
    }
    lim = (&D_eu_800C3A60)[i];
    if (*cur >= lim) {
        *cur = lim;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E46C.s")
#endif
#ifdef NON_MATCHING
/* P92: declarations for func_1501E5AC */
void func_10004074(s32);   /* free */
#endif

#ifdef NON_MATCHING
/* Frees the tables of cutscene slot `slot` (scene teardown, func_1501E888), when a scene asset is loaded
 * (D_800C3A88[slot], first word = its header {u16 nActors, ...}): every actor's path length table and sample
 * table (SceneActor +4 / +0x38, actors with path keys only), the actor array D_800C3E70, the camera records
 * D_800C3958, the per-actor blocks D_800C3D80, the u16 tables D_800C39E8 / D_800C39F0 / D_800C39F8, the words
 * D_800C3A00, the shared D_800C4170 and the asset itself; all pointers become NULL. */
void func_1501E5AC(s32 slot) {
    u16 *hdr;
    s32 i;

    if ((&D_800C3A88)[slot] == 0) {
        return;
    }
    hdr = *(u16 **)(&D_800C3A88)[slot];
    for (i = 0; i < hdr[0]; i++) {
        if (D_800C39E8[slot][i] != 0) {
            func_10004074((s32)D_800C3E70[slot][i].keys);
            func_10004074((s32)D_800C3E70[slot][i].state);
        }
    }
    func_10004074((s32)D_800C3E70[slot]);
    D_800C3E70[slot] = NULL;
    func_10004074((s32)(&D_800C3958)[slot]);
    (&D_800C3958)[slot] = NULL;
    for (i = 0; i < hdr[0]; i++) {
        func_10004074((s32)D_800C3D80[slot][i]);
        D_800C3D80[slot][i] = NULL;
    }
    func_10004074((s32)D_800C39E8[slot]);
    func_10004074((s32)D_800C39F0[slot]);
    func_10004074((s32)D_800C39F8[slot]);
    func_10004074((s32)D_800C3A00[slot]);
    D_800C39E8[slot] = NULL;
    D_800C39F0[slot] = NULL;
    D_800C39F8[slot] = NULL;
    D_800C3A00[slot] = NULL;
    func_10004074((s32)D_800C4170);
    D_800C4170 = NULL;
    func_10004074((&D_800C3A88)[slot]);
    (&D_800C3A88)[slot] = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E5AC.s")
#endif
extern u8 *D_800C3A10[];

void func_1501E7A8(s32 arg0)
{
  s32 var_s0;
  s32 n;
  struct127 *e;
  u8 *cnt;
  u8 **tbl;
  u8 *p;
  cnt = &D_800C3A5A[arg0];
  n = *cnt;
  if (n > 0)
  {
    tbl = &D_800C3A10[arg0];
    var_s0 = 0;
    do
    {
      p = (*tbl) + var_s0;
      if ((*((u16 *) p)) == 2)
      {
        e = func_15083E90(p[2]);
        if (e == 0)
        {
          s32 blk_t; // fakematch: block-local decl (shape D)
          n = *cnt;
        }
        else
        {
          if ((*((u8 *) (((u8 *) e) + 0x6C))) >= 0xA)
          {
            *((u8 *) (((u8 *) e) + 0x6C)) = 0;
            *((s8 *) (((u8 *) e) + 0x6A)) = 0;
          }
          if ((*((u8 *) (((u8 *) e) + 0x6D))) >= 0xA)
          {
            *((u8 *) (((u8 *) e) + 0x6D)) = 0;
            *((s8 *) (((u8 *) e) + 0x6B)) = 0;
          }
          func_1507EE9C(e);
          n = *cnt;
        }
      }
      if (0) // fakematch: permuter empty if
      {
      }
    }
    while ((var_s0 += 8) < (n * 8));
  }
  tbl++; // fakematch: permuter tbl++/tbl--
  tbl--;
}

#ifdef NON_MATCHING
/* End of cutscene slot `slot` (skipped != 0: cut short, event 0xF, else 0x10 to func_15169040 with the scene
 * number): position back to the start D_800C40AE, scene marked as seen (func_1501D2C4), slot unloaded,
 * per-scene teardown (func_1501E7A8, func_1502348C, func_15023684, func_1501EA84, func_1501E5AC), view reset
 * (func_1510B8AC with the game camera's +0x19C / +0x1A0). A queued follow-up scene (D_800C39E2 = scene + 1,
 * level D_800C39E3, 0x25 = load it into level 0x25 temporarily) is loaded at once (func_1501D348, slot state
 * 2); otherwise the screen fade / pause flags are cleared. */
void func_1501E888(s32 skipped, s32 slot) {
    u8 *loaded;
    struct108 *gameCam;
    u8 scene;
    s32 level;
    s32 savedLevel;

    loaded = &D_800C35EA + slot;
    gameCam = D_800DBFF0;
    if (*loaded == 0) {
        return;
    }
    scene = (&D_800C3A08)[slot];
    func_15169040((s32)&scene, skipped ? 0xF : 0x10);
    D_800C39D8[slot] = -100;
    (&D_800C39D0)[slot] = D_800C40AE;
    func_1501D2C4(D_800BE9F0, (&D_800C3A08)[slot]);
    *loaded = 0;
    D_800C3638 = 0;
    func_1501E7A8(slot);
    func_1502348C();
    D_800C3A86 = 0;
    D_800C3683 = 0;
    func_15023684(slot);
    func_1501EA84(slot);
    func_1501E5AC(slot);
    D_800C3A6C = 0.0f;
    D_800C3A70 = 0.0f;
    D_800C3A74 = 0.0f;
    func_1510B8AC(0, *(f32 *)((u8 *)gameCam + 0x19C), *(f32 *)((u8 *)gameCam + 0x1A0), 1.0f);
    if (D_800C39E2 != 0) {
        *loaded = 2;
        level = D_800C39E3;
        if (level == 0x25) {
            savedLevel = D_800BE9F0;
            D_800BE9F0 = 0x25;
        }
        D_800C3671 = 0;
        func_1501D348(level, D_800C39E2 - 1, slot, D_800C3C90, D_800C3C94);
        if (D_800C39E3 == 0x25) {
            D_800BE9F0 = savedLevel;
        }
    } else {
        if (D_800C40AB != 0) {
            func_1517F3B0(0, 0, 0, 0x19, 0, 0);
        }
        D_80090124 = 0;
        D_800C3670 = 0;
        D_800C3671 = 0;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E888.s")
#endif

#ifdef NON_MATCHING
/* P92: declarations for func_1501EA84 */
void func_1512DAD0(struct108 *, s32, void *);
void func_15022864(s32);
void func_1502298C(s32);
extern s32 D_800C3A20;   /* camera event block */
extern s32 D_800D121C;   /* end of the object table D_800CC2D0 */
extern f32 D_80096D74;   /* unset D_800C3A94 */
extern f32 D_80096D78;   /* unset D_800C3A98 */
#endif

#ifdef NON_MATCHING
/* Scene end, camera and objects of cutscene slot `slot` (called by func_1501E888). The camera event block
 * D_800C3A20 = {1, slot, .., eye = game camera +0x2F8..0x300, 0, +0x388, +0x37C} is sent to the game camera
 * (func_1512DAD0 event 7) unless D_800C3671; then event 8 with D_800C3A94 at +0xC unless it is unset
 * (D_80096D74), and event 10 with D_800C3A98 / D_800C3A9C unless that is unset (D_80096D78). Without a queued
 * follow-up scene (D_800C39E2) and D_800C3671: event 6 (with the slot number as its data), skipped once when
 * D_800C3AA0 is set (it is cleared). Then func_1502298C (unless D_800C3A7E[slot]) and func_15022864; every
 * object of the scene (func_15022A8C) gets byte +0xA4 and the floats +0xB8 / +0xC4 cleared. Without a follow-up
 * scene: D_eu_800C3E78 = 2, D_800C3663 = 0, the start angle / position D_800C39B4 / D_800C39AC come back from
 * D_800C39C0 / D_800C39B8. */
void func_1501EA84(s32 slot) {
    struct108 *cam;
    s32 *ev;
    u8 *obj;

    ev = &D_800C3A20;
    cam = D_800DBFF0;
    ev[0] = 1;
    ev[1] = slot;
    ((f32 *)ev)[5] = *(f32 *)((u8 *)cam + 0x2F8);
    ((f32 *)ev)[6] = *(f32 *)((u8 *)cam + 0x2FC);
    ((f32 *)ev)[7] = *(f32 *)((u8 *)cam + 0x300);
    ((f32 *)ev)[8] = 0.0f;
    ((f32 *)ev)[9] = *(f32 *)((u8 *)cam + 0x388);
    ((f32 *)ev)[10] = *(f32 *)((u8 *)cam + 0x37C);
    if (D_800C3671 == 0) {
        func_1512DAD0(cam, 7, ev);
        if (D_800C3A94 != D_80096D74) {
            ((f32 *)ev)[3] = D_800C3A94;
            func_1512DAD0(cam, 8, ev);
        }
        if (D_800C3A98 != D_80096D78) {
            ((f32 *)ev)[3] = D_800C3A98;
            ev[4] = D_800C3A9C;
            func_1512DAD0(cam, 10, ev);
        }
    }
    if (D_800C39E2 == 0 && D_800C3671 == 0) {
        if (D_800C3AA0 == 0) {
            func_1512DAD0(cam, 6, (void *)slot);
        } else {
            D_800C3AA0 = 0;
        }
    }
    if ((&D_800C3A7E)[slot] == 0) {
        func_1502298C(slot);
    }
    func_15022864(slot);
    for (obj = (u8 *)D_800CC2D0; obj != (u8 *)&D_800D121C; obj += 0x32C) {
        if (*(s32 *)obj != 0 && func_15022A8C((s32 *)obj) != 0) {
            obj[0xA4] = 0;
            *(f32 *)(obj + 0xB8) = 0.0f;
            *(f32 *)(obj + 0xC4) = 0.0f;
        }
    }
    if (D_800C39E2 == 0) {
        D_eu_800C3E78 = 2;
        D_800C3663 = 0;
        D_800C39B4 = D_800C39C0;
        D_800C39AC[0] = D_800C39B8[0];
        D_800C39AC[1] = D_800C39B8[1];
        D_800C39AC[2] = D_800C39B8[2];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501EA84.s")
#endif
#ifdef NON_MATCHING
/* P87: camera / actor track key (8 bytes, D_800C3B98[slot][actor] arrays) */
typedef struct {
    f32 value;
    u8 mode;     /* interpolation into the next key: 0 = spline (func_15049AD0), else linear */
    u8 channel;  /* 0 .. 14 */
    s16 frame;   /* 60 Hz frames */
} TrackKey;
#define TRACK_NONE (-9999)
#define TRACK_NONE_F (-9999.0f)   /* D_80096D7C / D_80096DA0: no value */
extern f32 D_800C39C4;
f32 func_15049AD0(s32 *, s32, f32);
void func_1501FF10(s32, f32, f32 *, s32);
void func_1501FD34(s32, f32, f32 *, f32 *, f32 *, s32);
s32 func_1501F7D4(s32, f32, f32 *, s32, s32 *);
void func_15020090(u8 *, s32, s32, s32);
extern f32 D_80096D84; /* 0.01 */
extern f32 D_80096D80; /* 0.01 */
void func_15020920(s32, s32, s32);
extern f32 D_80096D88; /* 0.01 */
extern f32 D_80096D8C; /* radians to degrees */
#endif
#ifdef NON_MATCHING
/* Camera track pass of cutscene slot `slot` (P72 / P84: the scene loader reads what this writes). Every actor i
 * has a 0x44-byte camera record cam = D_800C3958[slot] + i * 17 floats (position 0..2 from its s16 actor record,
 * then per-type defaults, entry type = u16 at D_800C3A10[slot] + i * 8). Its keys D_800C3B98[slot][i] (count
 * D_800C39F0[slot][i]) are 8-byte TrackKey records on 15 channels; each channel is evaluated at the current
 * frame (script position * 60 / 50, or D_800C3A68 once the slot has ended): before the first key -> no value,
 * at / after the last key -> last value, else spline (mode 0, func_15049AD0 over the 4 surrounding keys) or
 * linear between the two keys around the frame. Channel 10 (roll) goes to func_1501FF10 when the actor has a
 * look step (D_800C3D80 byte 0 != 0xFF), else channel 7 sets cam[4]; the other channels overwrite cam[3..16]
 * where they have a value; func_1501FD34 then places cam[0..2]. D_800C3638 = 0 while running, 1 after. */
void func_1501ECA4(s32 slot) {
    TrackKey *keys;
    TrackKey *key;
    f32 *cam;
    u8 *n;
    s32 frame;
    s32 i;
    s32 ch;
    s32 k;
    s32 seen;
    s32 at;
    s32 want;
    s32 flags;
    s32 ia;
    s32 ib;
    f32 t;
    s16 *pos;
    s32 nextFrame[15];
    s32 prevFrame[15];
    s32 nextIdx[15];
    s32 mode[15];
    s32 count[15];
    f32 first[15];
    f32 last[15];
    f32 out[15];
    f32 pts[4];

    if ((&D_800C35EA)[slot] != 1) {
        return;
    }
    if ((&D_800C39D0)[slot] < (&D_eu_800C3A60)[slot]) {
        frame = (&D_800C39D0)[slot] * 60 / 50;
    } else {
        frame = D_800C3A68;
    }
    D_800C3638 = 0;
    n = &D_800C3A5A[slot];
    ib = 0;
    for (i = 0; i < *n; i++) {
        cam = (f32 *)(&D_800C3958)[slot] + i * 17;
        if (D_800C39E8[slot][i] != 0) {
            pos = (s16 *)D_eu_800C3C88[slot][i];
            cam[0] = pos[0];
            cam[1] = pos[1];
            cam[2] = pos[2];
        } else {
            cam[0] = 0.0f;
            cam[1] = 0.0f;
            cam[2] = 0.0f;
        }
        if (*(u16 *)(D_800C3A10[slot] + i * 8) == 4) {
            cam[3] = 64.0f;
            cam[4] = 0.0f;
            cam[5] = 20.0f;
            cam[6] = 255.0f;
            cam[7] = 62.5f;
            cam[8] = 50.0f;
            cam[9] = 0.0f;
            cam[10] = 0.0f;
            cam[11] = 0.0f;
            cam[13] = 0.0f;
        } else {
            cam[3] = 0.0f;
            cam[4] = D_800C39C4;
            cam[5] = 0.0f;
            cam[6] = TRACK_NONE_F;
            cam[7] = TRACK_NONE_F;
            cam[8] = TRACK_NONE_F;
            cam[9] = 0.0f;
            cam[10] = 0.0f;
            cam[11] = 0.0f;
            cam[15] = TRACK_NONE_F;
            cam[16] = TRACK_NONE_F;
            cam[12] = TRACK_NONE_F;
        }
        cam[14] = 0.0f;
        switch (*(u16 *)(D_800C3A10[slot] + i * 8)) {
            case 1:
                cam[13] = TRACK_NONE_F;
                break;
            case 2:
                cam[13] = 255.0f;
                break;
            case 5:
                cam[6] = 32.0f;
                cam[7] = 32.0f;
                cam[13] = 1.0f;
                break;
            case 3:
                cam[6] = TRACK_NONE_F;
                cam[7] = TRACK_NONE_F;
                cam[8] = TRACK_NONE_F;
                cam[13] = 255.0f;
                break;
        }

        keys = (TrackKey *)D_800C3B98[slot][i];
        if (keys == NULL) {
            continue;
        }
        for (ch = 0; ch < 15; ch++) {
            nextFrame[ch] = TRACK_NONE;
            prevFrame[ch] = TRACK_NONE;
            nextIdx[ch] = TRACK_NONE;
            mode[ch] = 1;
            count[ch] = 0;
            first[ch] = TRACK_NONE_F;
            last[ch] = TRACK_NONE_F;
        }
        /* per channel: the last key before the frame (its mode and frame), the first key at / after it */
        for (k = 0; k < D_800C39F0[slot][i]; k++) {
            key = &keys[k];
            ch = key->channel;
            if (nextIdx[ch] == TRACK_NONE) {
                if (key->frame < frame) {
                    mode[ch] = key->mode;
                    prevFrame[ch] = key->frame;
                } else {
                    nextIdx[ch] = count[ch];
                    nextFrame[ch] = key->frame;
                }
            }
            last[ch] = key->value;
            if (first[ch] == TRACK_NONE_F) {
                first[ch] = key->value;
            }
            count[ch]++;
        }
        for (ch = 0; ch < 15; ch++) {
            out[ch] = TRACK_NONE_F;
            if (prevFrame[ch] == TRACK_NONE) {
                if (nextFrame[ch] != TRACK_NONE) {
                    out[ch] = first[ch];
                }
            } else if (nextFrame[ch] == TRACK_NONE) {
                out[ch] = last[ch];
            } else {
                t = (f32)(frame - prevFrame[ch]) / (f32)(nextFrame[ch] - prevFrame[ch]);
                if (mode[ch] == 0) {
                    /* spline over keys nextIdx-2 .. nextIdx+1 of the channel, ends repeated */
                    if (nextIdx[ch] - 2 >= 0) {
                        flags = 7;
                        seen = nextIdx[ch] - 2;
                        want = 3;
                        at = 0;
                    } else {
                        flags = 6;
                        seen = nextIdx[ch] - 1;
                        want = 2;
                        at = 1;
                    }
                    if (nextIdx[ch] + 1 < count[ch]) {
                        flags |= 8;
                        want++;
                    }
                    /* ia counts the channel's keys; from index `seen` on they are collected */
                    ia = 0;
                    for (k = 0; k < D_800C39F0[slot][i] && want != 0; k++) {
                        if (keys[k].channel == ch) {
                            if (ia == seen) {
                                pts[at++] = keys[k].value;
                                want--;
                            } else {
                                ia++;
                            }
                        }
                    }
                    if (!(flags & 1)) {
                        pts[0] = pts[1];
                    }
                    if (!(flags & 8)) {
                        pts[3] = pts[2];
                    }
                    out[ch] = func_15049AD0((s32 *)pts, 0, t);
                } else {
                    /* linear between the channel's keys nextIdx-1 (ia) and nextIdx (ib) */
                    seen = 0;
                    ia = -1;
                    for (k = 0; k < D_800C39F0[slot][i]; k++) {
                        if (keys[k].channel == ch) {
                            if (ia != -1) {
                                ib = k;
                                break;
                            }
                            if (seen + 1 == nextIdx[ch]) {
                                ia = k;
                            } else {
                                seen++;
                            }
                        }
                    }
                    out[ch] = (keys[ib].value - keys[ia].value) * t + keys[ia].value;
                }
            }
        }
        if (out[10] == TRACK_NONE_F) {
            out[10] = 0.0f;
        }
        if (*(u8 *)D_800C3D80[slot][i] != 0xFF) {
            func_1501FF10(i, out[10], &cam[4], slot);
        } else if (out[7] != TRACK_NONE_F) {
            cam[4] = out[7];
        }
        if (out[8] != TRACK_NONE_F) {
            cam[3] = out[8];
        }
        if (out[6] != TRACK_NONE_F) {
            cam[5] = out[6];
        }
        if (out[5] != TRACK_NONE_F) {
            cam[6] = out[5];
        }
        if (out[4] != TRACK_NONE_F) {
            cam[7] = out[4];
        }
        if (out[3] != TRACK_NONE_F) {
            cam[8] = out[3];
        }
        if (out[1] != TRACK_NONE_F) {
            cam[9] = out[1];
        }
        if (out[2] != TRACK_NONE_F) {
            cam[10] = out[2];
        }
        if (out[0] != TRACK_NONE_F) {
            cam[11] = out[0];
        }
        if (out[14] != TRACK_NONE_F) {
            cam[12] = out[14];
        }
        if (out[9] != TRACK_NONE_F) {
            cam[13] = out[9];
        }
        if (out[11] != TRACK_NONE_F) {
            cam[14] = out[11];
        }
        if (out[13] != TRACK_NONE_F) {
            cam[15] = out[13];
        }
        if (out[12] != TRACK_NONE_F) {
            cam[16] = out[12];
        }
        func_1501FD34(i, out[10], &cam[0], &cam[1], &cam[2], slot);
    }
    D_800C3638 = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501ECA4.s")
#endif

#ifdef NON_MATCHING
/* Path point lookup for actor `actor` of cutscene slot `slot` at distance `dist` along its path: binary search of
 * the segment start lengths (SceneActor +4, D_800C39E8 key count entries) gives `seg` (*segOut); a segment change
 * (SceneActor +0x3C) prepares the segment's cubic (func_15020920: coefficients D / C / B / A at +0x08 / +0x14 /
 * +0x20 / +0x2C, xyz each). Curved segment (key shape +6 == 0): binary search of the 101 sample lengths
 * (SceneActor +0x38) gives the sample k; out[0..2] / out[3..5] = the cubic at u = k * 0.01 and (k + 1) * 0.01;
 * returns k. Straight segment: out[0..2] = out[3..5] = the point between the middle control points (func_15020090)
 * at the distance's fraction of the segment; the asm then returns an uninitialised stack word (callers only read
 * the result of a curved segment): 0 here. A slot without keys leaves `seg` uninitialised in the asm (0 here). */
s32 func_1501F7D4(s32 actor, f32 dist, f32 *out, s32 slot, s32 *segOut) {
    SceneActor *a;
    f32 pts[12];
    f32 *tab;
    f32 *c;
    f32 *o;
    f32 frac;
    f32 u;
    s32 lo;
    s32 hi;
    s32 mid;
    s32 seg;
    s32 k;
    s32 j;
    u16 shape;

    a = &D_800C3E70[slot][actor];
    seg = 0;
    lo = 0;
    hi = D_800C39E8[slot][actor] - 1;
    if (hi >= 0) {
        tab = a->keys;
        do {
            mid = (lo + hi) / 2;
            if (dist < tab[mid]) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
            if (tab[mid] <= dist && dist <= tab[mid + 1]) {
                break;
            }
        } while (lo <= hi);
        seg = mid;
    }
    *segOut = seg;
    if (seg != a->pad3C[0]) {
        func_15020920(actor, seg, slot);
    }
    shape = *(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6);
    func_15020090((u8 *)pts, D_eu_800C3C88[slot][actor], seg, D_800C39E8[slot][actor]);
    if (shape == 0) {
        tab = a->state;
        lo = 0;
        hi = 100;
        do {
            k = (lo + hi) / 2;
            if (dist < tab[k]) {
                hi = k - 1;
            } else {
                lo = k + 1;
            }
            if (tab[k] <= dist && dist <= tab[k + 1]) {
                break;
            }
        } while (lo <= hi);
        c = (f32 *)a->pad8;
        for (j = 0; j < 2; j++) {
            u = (f32)(k + j) * D_80096D80;
            o = out + j * 3;
            o[0] = c[0] + ((c[9] * u + c[6]) * u + c[3]) * u;
            o[1] = c[1] + ((c[10] * u + c[7]) * u + c[4]) * u;
            o[2] = c[2] + ((c[11] * u + c[8]) * u + c[5]) * u;
        }
        return k;
    }
    tab = a->keys;
    if (tab[seg + 1] - tab[seg] == 0.0f) {
        frac = 0.0f;
    } else {
        frac = (dist - tab[seg]) / (tab[seg + 1] - tab[seg]);
    }
    for (j = 0; j < 2; j++) {
        o = out + j * 3;
        o[0] = pts[3] + (pts[6] - pts[3]) * frac;
        o[1] = pts[4] + (pts[7] - pts[4]) * frac;
        o[2] = pts[5] + (pts[8] - pts[5]) * frac;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501F7D4.s")
#endif
#ifdef NON_MATCHING
/* Place actor `actor` of cutscene slot `slot` at `t` percent (clamped to 0..100) of its path length (SceneActor
 * +0, needs >= 2 path keys). func_1501F7D4 finds the segment `seg` holding that distance, two points (ends[0..2],
 * ends[3..5]) and the sample `k` of the actor's length table (SceneActor +0x38). On a curved segment (key shape
 * +6 == 0, func_15020430) the position is interpolated between the two points by the distance's fraction between
 * the lengths of samples k and k + 1; on a straight one it is the first point. */
void func_1501FD34(s32 actor, f32 t, f32 *x, f32 *y, f32 *z, s32 slot) {
    SceneActor *a;
    f32 ends[6];
    f32 dist;
    f32 frac;
    f32 *len;
    s32 seg;
    s32 k;

    if (D_800C39E8[slot][actor] < 2) {
        return;
    }
    if (100.0f < t) {
        t = 100.0f;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }
    a = &D_800C3E70[slot][actor];
    dist = *(f32 *)a->pad0 * t * D_80096D84;
    k = func_1501F7D4(actor, dist, ends, slot, &seg);
    if (*(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6) == 0) {
        len = (f32 *)a->state + k;
        if (len[1] - len[0] == 0.0f) {
            frac = 0.0f;
        } else {
            frac = (dist - len[0]) / (len[1] - len[0]);
        }
        *x = (ends[3] - ends[0]) * frac + ends[0];
        *y = (ends[4] - ends[1]) * frac + ends[1];
        *z = (ends[5] - ends[2]) * frac + ends[2];
    } else {
        *x = ends[0];
        *y = ends[1];
        *z = ends[2];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501FD34.s")
#endif
#ifdef NON_MATCHING
/* Heading of actor `actor` of cutscene slot `slot` at `t` percent (clamped to 0..100) of its path length (needs
 * >= 2 path keys), in degrees (func_150484A0(dx, dz) * D_80096D8C). func_1501F7D4 finds the segment for that
 * distance: on a curved segment (key shape +6 == 0, func_15020430) the direction runs between the two curve
 * points it returns (first - second), on a straight one between the segment's middle control points
 * (func_15020090, third - second). */
void func_1501FF10(s32 actor, f32 t, f32 *out, s32 slot) {
    f32 pts[12];
    f32 ends[6];
    f32 dx;
    f32 dz;
    s32 seg;

    if (D_800C39E8[slot][actor] < 2) {
        return;
    }
    if (100.0f < t) {
        t = 100.0f;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }
    func_1501F7D4(actor, *(f32 *)D_800C3E70[slot][actor].pad0 * t * D_80096D88, ends, slot, &seg);
    if (*(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6) == 0) {
        dx = ends[0] - ends[3];
        dz = ends[2] - ends[5];
    } else {
        func_15020090((u8 *)pts, D_eu_800C3C88[slot][actor], seg, D_800C39E8[slot][actor]);
        dx = pts[6] - pts[3];
        dz = pts[8] - pts[5];
    }
    *out = func_150484A0(dx, dz) * D_80096D8C;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501FF10.s")
#endif
#ifdef NON_MATCHING
void func_15020090(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 *var_t0;
    s16 var_t6;
    s16 var_t6_2;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_t1;
    s32 temp_t9;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_t0;
    u8 *var_a1_2;
    u8 *var_a1_3;
    u8 *var_t0_2;

    temp_v1 = arg2 - 1;
    var_v0 = 6;
    if (temp_v1 >= 0) {
        var_v0 = 7;
        var_a0 = temp_v1;
        var_a1 = 3;
        var_a3 = 0;
    } else {
        var_a0 = arg2;
        var_a1 = 2;
        var_a3 = 1;
    }
    if ((arg2 + 2) < arg3) {
        var_v0 |= 8;
        var_a1 += 1;
    }
    temp_a2 = var_a0 + var_a1;
    var_v1 = var_a0;
    if (var_a0 < temp_a2) {
        temp_t9 = (temp_a2 - var_a0) & 3;
        temp_t1 = temp_t9 + var_a0;
        if (temp_t9 != 0) {
            var_a1_2 = arg0 + (var_a3 * 0xC);
            var_t0 = arg1 + (var_a0 * 8);
            var_v1 += 1;
            var_t6 = *var_t0;
            if (temp_t1 != var_v1) {
                do {
                    var_v1 += 1;
                    var_a3 += 1;
                    var_a1_2 += 0xC;
                    var_t0 = (s16 *)((u8 *)var_t0 + (8));
                    (*(f32 *)((u8 *)var_a1_2 + -0xC)) = (f32) var_t6;
                    (*(f32 *)((u8 *)var_a1_2 + -8)) = (f32) (*(s16 *)((u8 *)var_t0 + -6));
                    (*(f32 *)((u8 *)var_a1_2 + -4)) = (f32) (*(s16 *)((u8 *)var_t0 + -4));
                    var_t6 = (*(s16 *)((u8 *)var_t0 + 0));
                } while (temp_t1 != var_v1);
            }
            var_a3 += 1;
            temp_a1 = var_a1_2 + 0xC;
            temp_t0 = ((s16 *)((u8 *)var_t0 + 8));
            (*(f32 *)((u8 *)temp_a1 + -0xC)) = (f32) var_t6;
            (*(f32 *)((u8 *)temp_a1 + -8)) = (f32) (*(s16 *)((u8 *)temp_t0 + -6));
            (*(f32 *)((u8 *)temp_a1 + -4)) = (f32) (*(s16 *)((u8 *)temp_t0 + -4));
            if (var_v1 != temp_a2) {
                goto block_10;
            }
        } else {
block_10:
            var_a1_3 = arg0 + (var_a3 * 0xC);
            temp_a0 = (temp_a2 * 8) + arg1;
            var_t0_2 = arg1 + (var_v1 * 8) + 0x20;
            var_t6_2 = (*(s16 *)((u8 *)var_t0_2 + -0x20));
            if ((s32)var_t0_2 != (s32)temp_a0) {
                do {
                    var_t0_2 += 0x20;
                    var_a1_3 += 0x30;
                    (*(f32 *)((u8 *)var_a1_3 + -0x30)) = (f32) var_t6_2;
                    (*(f32 *)((u8 *)var_a1_3 + -0x2C)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x3E));
                    (*(f32 *)((u8 *)var_a1_3 + -0x28)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x3C));
                    (*(f32 *)((u8 *)var_a1_3 + -0x24)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x38));
                    (*(f32 *)((u8 *)var_a1_3 + -0x20)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x36));
                    (*(f32 *)((u8 *)var_a1_3 + -0x1C)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x34));
                    (*(f32 *)((u8 *)var_a1_3 + -0x18)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x30));
                    (*(f32 *)((u8 *)var_a1_3 + -0x14)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x2E));
                    (*(f32 *)((u8 *)var_a1_3 + -0x10)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x2C));
                    (*(f32 *)((u8 *)var_a1_3 + -0xC)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x28));
                    (*(f32 *)((u8 *)var_a1_3 + -8)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x26));
                    (*(f32 *)((u8 *)var_a1_3 + -4)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x24));
                    var_t6_2 = (*(s16 *)((u8 *)var_t0_2 + -0x20));
                } while ((s32)var_t0_2 != (s32)temp_a0);
            }
            temp_a1_2 = var_a1_3 + 0x30;
            (*(f32 *)((u8 *)temp_a1_2 + -0x30)) = (f32) var_t6_2;
            (*(f32 *)((u8 *)temp_a1_2 + -0x2C)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x1E));
            (*(f32 *)((u8 *)temp_a1_2 + -0x28)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x1C));
            (*(f32 *)((u8 *)temp_a1_2 + -0x24)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x18));
            (*(f32 *)((u8 *)temp_a1_2 + -0x20)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x16));
            (*(f32 *)((u8 *)temp_a1_2 + -0x1C)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x14));
            (*(f32 *)((u8 *)temp_a1_2 + -0x18)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0x10));
            (*(f32 *)((u8 *)temp_a1_2 + -0x14)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0xE));
            (*(f32 *)((u8 *)temp_a1_2 + -0x10)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -0xC));
            (*(f32 *)((u8 *)temp_a1_2 + -0xC)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -8));
            (*(f32 *)((u8 *)temp_a1_2 + -8)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -6));
            (*(f32 *)((u8 *)temp_a1_2 + -4)) = (f32) (*(s16 *)((u8 *)var_t0_2 + -4));
        }
    }
    if (!(var_v0 & 1)) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) (*(f32 *)((u8 *)arg0 + 0xC));
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (*(f32 *)((u8 *)arg0 + 0x10));
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) (*(f32 *)((u8 *)arg0 + 0x14));
    }
    if (!(var_v0 & 8)) {
        (*(f32 *)((u8 *)arg0 + 0x24)) = (f32) (*(f32 *)((u8 *)arg0 + 0x18));
        (*(f32 *)((u8 *)arg0 + 0x28)) = (f32) (*(f32 *)((u8 *)arg0 + 0x1C));
        (*(f32 *)((u8 *)arg0 + 0x2C)) = (f32) (*(f32 *)((u8 *)arg0 + 0x20));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020090.s")
#endif
#ifdef NON_MATCHING
/* Path length of actor `actor` of cutscene slot `slot` (needs >= 2 path keys, D_800C39E8 count; keys are the
 * 8-byte records D_eu_800C3C88[slot][actor], +6 = segment shape). For every segment the 4 control points come
 * from func_15020090; keys[seg] (D_800C3E70 actor +4) = the length up to the segment's start. A curved segment
 * (shape 0) is measured as a Catmull-Rom curve sampled every 0.01 (chords between successive samples, the
 * previous sample in the other half of `prev`, which carries over between segments), a straight one as the
 * distance between its two middle points. +0 = the total length, keys[count - 1] = it too; +0x3C = 0xFF. */
void func_15020430(s32 actor, s32 slot) {
    SceneActor *act;
    s32 seg;
    s32 c;
    u16 shape;
    u8 cur;
    f32 total;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d;
    f32 pts[4][3];
    f32 A[3];
    f32 B[3];
    f32 C[3];
    f32 D[3];
    f32 prev[2][3];

    if (D_800C39E8[slot][actor] < 2) {
        return;
    }
    D_800C3E70[slot][actor].pad3C[0] = 0xFF;
    total = 0.0f;
    cur = 0;
    for (seg = 0; seg < D_800C39E8[slot][actor] - 1; seg++) {
        shape = *(u16 *)(D_eu_800C3C88[slot][actor] + seg * 8 + 6);
        /* P87: the asm leaves the key count in a3; func_15020090 reads it (dropped argument) */
        func_15020090((u8 *)pts, D_eu_800C3C88[slot][actor], seg, D_800C39E8[slot][actor]);
        ((f32 *)D_800C3E70[slot][actor].keys)[seg] = total;
        if (shape == 0) {
            for (c = 0; c < 3; c++) {
                A[c] = 0.5f * pts[3][c] + ((-0.5f * pts[0][c] + 1.5f * pts[1][c]) + -1.5f * pts[2][c]);
                B[c] = -0.5f * pts[3][c] + ((pts[0][c] + -2.5f * pts[1][c]) + (pts[2][c] + pts[2][c]));
                C[c] = 0.5f * pts[2][c] + -0.5f * pts[0][c];
                D[c] = pts[1][c];
            }
            for (c = 0; c < 3; c++) {
                prev[cur == 0][c] = D[c];
            }
            for (t = 0.01f; t <= 1.0f; t += 0.01f) {
                x = D[0] + ((A[0] * t + B[0]) * t + C[0]) * t;
                prev[cur][0] = x;
                y = D[1] + ((A[1] * t + B[1]) * t + C[1]) * t;
                prev[cur][1] = y;
                z = D[2] + ((A[2] * t + B[2]) * t + C[2]) * t;
                prev[cur][2] = z;
                dx = x - prev[cur == 0][0];
                dy = y - prev[cur == 0][1];
                dz = prev[cur][2] - prev[cur == 0][2];
                d = dx * dx + (dy * dy + dz * dz);
                if (d != 0.0f) {
                    total += sqrtf(d);
                }
                cur ^= 1;
            }
        } else {
            dz = pts[2][2] - pts[1][2];
            dx = pts[2][0] - pts[1][0];
            dy = pts[2][1] - pts[1][1];
            total += sqrtf(dz * dz + (dx * dx + dy * dy));
        }
    }
    ((f32 *)D_800C3E70[slot][actor].keys)[seg] = total;
    *(f32 *)D_800C3E70[slot][actor].pad0 = total;
    D_800C3E70[slot][actor].pad3C[0] = 0xFF;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020430.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020920.s")

#ifdef NON_MATCHING
s32 func_1502330C(s32, s32);
void func_1512DAD0(struct108 *, s32, void *);
s32 func_15129220(struct108 *);
void func_1517DB6C(s16, s16, s16, s32, s32, s32);
extern u8 D_800C3A18;
extern s32 D_800C3A20;   /* camera event block (func_1512DAD0 event 7) */
extern f32 D_800C3A40;   /* D_800C3A20 + 0x20: look target */
extern f32 D_800C3A44;
extern f32 D_800C3A48;
#endif
#ifdef NON_MATCHING
/* Applies the camera records of cutscene slot `slot` (written by func_1501ECA4) to the game. D_800C3A18 = the
 * actor whose record drives the game camera (func_1502330C at the current script position, cached until reset
 * to 0xFF). Two passes over the active actors (D_800C39F0 / D_800C39E8 counts != 0): pass 0 every entry type
 * but 1, pass 1 type 1 (the camera; so the camera sees the objects already placed). Entry = 8 bytes at
 * D_800C3A10[slot] + i * 8: u16 type, u8 a, s8 b, s16 c.
 *   type 1 (camera, only actor D_800C3A18): clamps cam[13] / cam[15] / cam[16] to -20 .. 40, fills the camera
 *     event block D_800C3A20 (eye cam[0..2]; target by a: 1 = actor b's position raised by c (+ cam[14]),
 *     2 = object func_15083E90(b), 3 = entity func_151149AC(b) raised by c, 0 = angle mode) and sends it to the
 *     game camera D_800DBFF0 (func_1512DAD0 event 7; event 5 + func_15129220 first unless flag 0x40000).
 *   type 3: entity func_151149AC(a) gets position / angles / scale (* 0.01) / alpha from the record.
 *   type 2: object func_15083E90(a) takes its actor frame (func_15021834(obj, slot, i)).
 *   type 5: when cam[13] >= 1, func_1517DB6C at the record position with cam[6] / cam[7].
 * D_800C3638 = 0 while running, 1 after. */
void func_15020F6C(s32 slot) {
    f32 *cams;
    f32 *cam;
    f32 *other;
    u8 *ent;
    u8 *ev;
    u8 *e;
    struct108 *gameCam;
    s32 pass;
    s32 i;
    s32 a;
    f32 f;
    f32 v15;
    f32 v16;

    if ((&D_800C35EA)[slot] != 1) {
        return;
    }
    D_800C3638 = 0;
    if (D_800C3A18 == 0xFF) {
        D_800C3A18 = func_1502330C(slot, (&D_800C39D0)[slot]);
    }
    ev = (u8 *)&D_800C3A20;
    for (pass = 0; pass != 2; pass++) {
        for (i = 0; i < D_800C3A5A[slot]; i++) {
            if (D_800C39F0[slot][i] == 0 || D_800C39E8[slot][i] == 0) {
                continue;
            }
            ent = D_800C3A10[slot] + i * 8;
            if (pass == 0) {
                if (*(u16 *)ent == 1) {
                    continue;
                }
            } else if (*(u16 *)ent != 1) {
                continue;
            }
            switch (*(u16 *)ent) {
                case 1:
                    gameCam = D_800DBFF0;
                    if (i != D_800C3A18) {
                        break;
                    }
                    if (!(*(s32 *)((u8 *)gameCam + 0x2C) & 0x40000)) {
                        if (D_800C3671 == 0) {
                            func_1512DAD0(gameCam, 5, (void *)slot);
                        }
                        func_15129220(gameCam);
                    }
                    cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                    f = cam[13];
                    if (f == TRACK_NONE_F) {
                        *(f32 *)(ev + 8) = 0.0f;
                    } else {
                        cam[13] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                        *(f32 *)(ev + 8) = cam[13];
                    }
                    f = cam[15];
                    if (f == TRACK_NONE_F) {
                        v15 = 0.0f;
                    } else {
                        cam[15] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                        v15 = cam[15];
                    }
                    f = cam[16];
                    if (f == TRACK_NONE_F) {
                        v16 = 0.0f;
                    } else {
                        cam[16] = (f < -20.0f) ? -20.0f : (40.0f < f) ? 40.0f : f;
                        cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                        v16 = cam[16];
                    }
                    ent = D_800C3A10[slot] + i * 8;
                    *(s32 *)(ev + 4) = slot;
                    *(f32 *)(ev + 0x14) = cam[0];
                    *(f32 *)(ev + 0x18) = cam[1];
                    *(f32 *)(ev + 0x1C) = cam[2];
                    switch (ent[2]) {
                        case 1:
                            /* look at actor ent[3], raised by the entry's s16 */
                            *(s32 *)ev = 0;
                            cams = (f32 *)(&D_800C3958)[slot];
                            other = cams + (s8)ent[3] * 17;
                            *(f32 *)(ev + 0x20) = other[0];
                            *(f32 *)(ev + 0x24) = cam[14] + (other[1] + (f32)*(s16 *)(ent + 4));
                            *(f32 *)(ev + 0x28) = other[2];
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 2:
                            /* look at object ent[3] */
                            e = (u8 *)func_15083E90(ent[3]);
                            if (e == NULL) {
                                continue;
                            }
                            *(s32 *)ev = 0;
                            D_800C3A40 = *(f32 *)(e + 0x14);
                            ent = D_800C3A10[slot] + i * 8;
                            cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                            D_800C3A44 = cam[14] + (*(f32 *)(e + 0x18) + (f32)*(s16 *)(ent + 4));
                            D_800C3A48 = *(f32 *)(e + 0x1C);
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 3:
                            /* look at entity ent[3] (s16 position) */
                            e = func_151149AC(ent[3]);
                            if (e == NULL) {
                                continue;
                            }
                            *(s32 *)ev = 0;
                            D_800C3A40 = *(s16 *)(e + 0x10);
                            ent = D_800C3A10[slot] + i * 8;
                            cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                            D_800C3A44 = cam[14] + (f32)(*(s16 *)(e + 0x12) + *(s16 *)(ent + 4));
                            D_800C3A48 = *(s16 *)(e + 0x14);
                            *(f32 *)(ev + 0x30) = v15;
                            *(f32 *)(ev + 0x34) = v16;
                            *(f32 *)(ev + 0x2C) = -cam[5];
                            break;
                        case 0:
                            /* angle mode */
                            *(s32 *)ev = 1;
                            *(f32 *)(ev + 0x20) = -cam[5];
                            *(f32 *)(ev + 0x24) = cam[3];
                            *(f32 *)(ev + 0x28) = cam[4];
                            *(f32 *)(ev + 0x2C) = v15;
                            *(f32 *)(ev + 0x30) = v16;
                            *(f32 *)(ev + 0x18) = cam[1] + cam[14];
                            break;
                    }
                    if (D_800C3671 == 0) {
                        func_1512DAD0(gameCam, 7, ev);
                    }
                    break;
                case 3:
                    e = func_151149AC(ent[2]);
                    if (e == NULL) {
                        continue;
                    }
                    e[0x4E] = 0;
                    e[0x6F] &= 0x7F;
                    cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                    *(s16 *)(e + 0x10) = (s32)cam[0];
                    *(s16 *)(e + 0x12) = (s32)(cam[14] + cam[1]);
                    *(s16 *)(e + 0x14) = (s32)cam[2];
                    *(f32 *)(e + 0x0) = cam[3];
                    *(f32 *)(e + 0x4) = cam[4];
                    *(f32 *)(e + 0x8) = cam[5];
                    if (cam[6] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x2C) = cam[6] * 0.01f;
                    }
                    if (cam[7] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x30) = cam[7] * 0.01f;
                    }
                    if (cam[8] != TRACK_NONE_F) {
                        *(f32 *)(e + 0x34) = cam[8] * 0.01f;
                    }
                    a = cam[13];
                    e[0x8A] = (a >= 0x100) ? 0xFF : (a >= 0) ? a : 0;
                    break;
                case 2:
                    func_15021834(func_15083E90(ent[2]), slot, i);
                    break;
                case 5:
                    cam = (f32 *)(&D_800C3958)[slot] + i * 17;
                    if (1.0f <= cam[13]) {
                        func_1517DB6C((s32)cam[0], (s32)cam[1], (s32)cam[2], 0, (s32)cam[6], (s32)cam[7]);
                    }
                    break;
            }
        }
    }
    D_800C3638 = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020F6C.s")
#endif

#ifdef NON_MATCHING
/*
 * P53: place an actor on its spawn / cutscene marker of player slot arg1 (arg2 = one marker, -1 = all) and refresh
 * its floor (func_1510ED24: floor triangle, height, water level). Hand-written (m2c gave no draft: the f32 -> u32
 * angle conversion minus 0x4000 and the 0x44-byte marker records).
 */
void func_1510ED24(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
extern u16 *D_800C39E8[];
extern u8 *D_800C3A10[];
extern u8 D_800D39FC;
extern f32 D_80096DB0; /* "unset" scale marker */
extern f32 D_80096DB4; /* no water level */
extern f32 D_80096DB8; /* scale factor */
extern f32 D_80096DBC; /* degrees to the 16-bit angle */
#define A834_F(o) (*(f32 *)((u8 *)obj + (o)))
#define A834_M(o) (*(f32 *)(mk + (o)))

void func_15021834(struct127 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 end;
    s32 scaled;
    u8 *e;
    u8 *mk;
    struct127 *obj;
    f32 ox, oz, d, a;
    f32 floorY;
    u32 ang;

    if ((&D_800C35EA)[arg1] != 1) {
        return;
    }
    D_800C3638 = 0;
    if (arg2 != -1) {
        i = arg2;
        end = arg2 + 1;
    } else {
        i = 0;
        end = D_800C3A5A[arg1];
    }
    for (; i < end; i++) {
        if (D_800C39E8[arg1][i] == 0) continue;
        e = D_800C3A10[arg1] + i * 8;
        if (*(u16 *)e != 2) continue;
        obj = func_15083E90(e[2]);
        if (obj == NULL || obj != arg0) continue;
        mk = (u8 *)(&D_800C3958)[arg1] + i * 0x44;
        ox = A834_F(0x14);
        oz = A834_F(0x1C);
        A834_F(0x14) = A834_M(0x0);
        A834_F(0x18) = A834_M(0x38) + A834_M(0x4);
        A834_F(0x1CC) = A834_F(0x18);
        A834_F(0x1C) = A834_M(0x8);
        if (D_800C3C88 == 0) {
            d = A834_F(0x1C) - oz;
            a = A834_F(0x14) - ox;
            A834_F(0x3C) = d * d + a * a;
            if (A834_F(0x3C) != 0.0f) {
                A834_F(0x3C) = sqrtf(A834_F(0x3C)) * 2.0f;
            }
        } else {
            A834_F(0x3C) = 0.0f;
        }
        if (*(f32 **)((u8 *)obj + 0x31C) != NULL) {
            **(f32 **)((u8 *)obj + 0x31C) = A834_F(0x3C) * 2.0f;
        }
        A834_F(0x54) = 0.0f;
        *(s16 *)((u8 *)obj + 0xCC) = 0;
        D_800D39FC = (arg0 - D_800CC2D0) + 1;
        func_1510ED24((s32)obj + 0x188, (s32)obj + 0x18C, (s32)&floorY, (s32)obj + 0x118, (s32)obj + 0x184,
                      (s32)obj + 0x1A2, A834_F(0x14), A834_F(0x18), A834_F(0x1C), A834_F(0x18), 0, (s32)obj,
                      D_80096DB4, *(f32 *)((u8 *)arg0 + 0x18));
        D_800D39FC = 0;
        A834_F(0x180) = floorY;
        *((u8 *)obj + 0xD0) = 0;
        A834_F(0x28) = A834_F(0x18) - A834_F(0x180);
        if (*(s32 *)obj == 1) {
            if (D_80096DB4 != A834_F(0x118) && A834_F(0x18) < A834_F(0x118)) {
                *((u8 *)obj + 0xAD) = 1;
            } else {
                *((u8 *)obj + 0xAD) = 0;
                *(s16 *)((u8 *)obj + 0xB2) = 0;
            }
        }
        scaled = 0;
        if (D_80096DB0 != A834_M(0x18)) {
            scaled = 1;
            A834_F(0x14C) = A834_M(0x18) * D_80096DB8;
            A834_F(0x154) = A834_M(0x18) * D_80096DB8;
        }
        if (D_80096DB0 != A834_M(0x1C)) {
            scaled = 1;
            A834_F(0x150) = A834_M(0x1C) * D_80096DB8;
            A834_F(0x158) = A834_M(0x1C) * D_80096DB8;
        }
        if (scaled) {
            func_15062BDC(obj, A834_F(0x14C), A834_F(0x150));
        }
        A834_F(0xB8) = A834_M(0xC);
        a = A834_M(0x10) + 180.0f;
        while (a >= 360.0f) a -= 360.0f;
        while (a < 0.0f) a += 360.0f;
        ang = (u32)(a * D_80096DBC) - 0x4000;
        *(u16 *)((u8 *)obj + 0x78) = ang;
        *(u16 *)((u8 *)obj + 0x7A) = ang;
        *(u16 *)((u8 *)obj + 0x76) = ang;
        A834_F(0x40) = a;
        A834_F(0xC4) = A834_M(0x14);
        if (A834_M(0x34) < 0.0f) {
            A834_M(0x34) = 0.0f;
        } else {
            A834_M(0x34) = (A834_M(0x34) > 255.0f) ? 255.0f : A834_M(0x34);
        }
        func_1506160C(obj, 1, (u32)A834_M(0x34) & 0xFF, 0, 0);
        A834_F(0x2C) = A834_F(0x14);
        A834_F(0x30) = A834_F(0x18);
        A834_F(0x34) = A834_F(0x1C);
    }
    D_800C3638 = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15021834.s")
#endif

#ifdef NON_MATCHING
extern f32 D_80096DC0;
/* Look target of the actor of player `player` in sequence slot `slot` (D_800C35EA[slot] == 1: a cutscene runs):
 * the first live actor (D_800C39E8 id != 0) whose record (D_800C3A10, kind 2) names the player's room.
 * Its look step (D_800C3D80 +2) gives a point next to entity r[5] (D_800C3958 0x44-byte records) raised by r[6]:
 * written to pos, returns 0. Without one, look step +1: entity 0 = fixed angles (record i +0x24 / +0x28 / +0x2C
 * to outB / outA / outC, returns 1), else the camera point (D_800DBFF0 +0x2F8) raised by r[6]. No step: pos =
 * D_80096DC0 x3. */
s32 func_15021E60(f32 *outA, f32 *outB, f32 *outC, f32 *pos, s32 player, s32 slot) {
    u16 *ids;
    u8 *e;
    u8 *step;
    u8 *r;
    f32 *q;
    s32 n;
    s32 i;

    if ((&D_800C35EA)[slot] != 1) {
        return 0;
    }
    n = D_800C3A5A[slot];
    ids = D_800C39E8[slot];
    for (i = 0; i < n; i++, ids++) {
        if (*ids == 0) {
            continue;
        }
        e = D_800C3A10[slot] + i * 8;
        if (*(u16 *)e != 2) {
            continue;
        }
        if (*((u8 *)D_800CC2D0 + player * 0x32C + 0x3B) != e[2]) {
            continue;
        }
        step = (u8 *)D_800C3D80[slot][i];
        if (step[2] != 0xFF) {
            r = (u8 *)D_800C3AA8[slot][i] + step[2] * 8;
            q = (f32 *)(((u8 **)&D_800C3958)[slot] + (s8)r[5] * 0x44);
            pos[0] = q[0];
            pos[1] = q[1] + (f32)*(s16 *)(r + 6);
            pos[2] = q[2];
            return 0;
        }
        if (step[1] != 0xFF) {
            r = (u8 *)D_800C3AA8[slot][i] + step[1] * 8;
            if ((s8)r[5] == 0) {
                q = (f32 *)(((u8 **)&D_800C3958)[slot] + i * 0x44);
                *outA = q[10];
                *outB = q[9];
                *outC = q[11];
                return 1;
            }
            pos[0] = *(f32 *)((u8 *)D_800DBFF0 + 0x2F8);
            pos[1] = *(f32 *)((u8 *)D_800DBFF0 + 0x2FC) + (f32)*(s16 *)(r + 6);
            pos[2] = *(f32 *)((u8 *)D_800DBFF0 + 0x300);
            return 0;
        }
        pos[0] = D_80096DC0;
        pos[1] = D_80096DC0;
        pos[2] = D_80096DC0;
        return 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15021E60.s")
#endif

#ifdef NON_MATCHING
extern f32 D_80096DC4;
/* Look limits of the actor of player `player` in sequence slot `slot` (same search as func_15021E60): both
 * pairs are cleared, then entity record i +0x3C (into b[0], b[1]) and +0x40 (into a[0], a[1]) unless they hold the
 * "unset" value D_80096DC4. Returns 1 when the actor was found. */
s32 func_150220CC(f32 *a, f32 *b, s32 player, s32 slot) {
    u16 *ids;
    u8 *e;
    f32 *q;
    s32 n;
    s32 i;

    if ((&D_800C35EA)[slot] != 1) {
        return 0;
    }
    n = D_800C3A5A[slot];
    ids = D_800C39E8[slot];
    for (i = 0; i < n; i++, ids++) {
        if (*ids == 0) {
            continue;
        }
        e = D_800C3A10[slot] + i * 8;
        if (*(u16 *)e != 2) {
            continue;
        }
        if (*((u8 *)D_800CC2D0 + player * 0x32C + 0x3B) != e[2]) {
            continue;
        }
        a[1] = 0.0f;
        b[1] = 0.0f;
        a[0] = 0.0f;
        b[0] = 0.0f;
        q = (f32 *)(((u8 **)&D_800C3958)[slot] + i * 0x44);
        if (q[15] != D_80096DC4) {
            b[0] = q[15];
            b[1] = b[0];
        }
        if (q[16] != D_80096DC4) {
            a[0] = q[16];
            a[1] = a[0];
        }
        return 1;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150220CC.s")
#endif

void func_15022238(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    D_800C39B4 = arg3;
    D_800C39AC[0] = arg0;
    D_800C39AC[1] = arg1;
    D_800C39AC[2] = arg2;
    D_800C3663 = 1;
}

void func_15022290(s16 arg0, s16 arg1, s16 arg2, f32 arg3) {
    D_800C39C0 = arg3;
    D_800C39B8[0] = arg0;
    D_800C39B8[1] = arg1;
    D_800C39B8[2] = arg2;
}

void func_150222DC(s32 arg0) {
    D_800C3930[arg0] = 0;
}

void func_150222F0(s32 arg0) {
    D_800C396A[arg0] = 0;
}

#ifdef NON_MATCHING
/* P36: add id to the list `list` (D_800C3938[list], 25 bytes, count D_800C3930[list]) unless present. Returns the
 * 1-based position when found, else the old count (the new entry's index). */
s32 func_15022304(s32 id, s32 list) {
    u8 *cnt = (u8 *) &D_800C3930 + list;
    u8 *a = (u8 *) &D_800C3938 + list * 25;
    s32 n = *cnt;
    s32 i = 0;

    if (n > 0) {
        do {
            i++;
            if (id == a[i - 1]) {
                return i;
            }
        } while (i < n);
    }
    a[n] = id;
    *cnt = n + 1;
    return i;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022304.s")
#endif
extern u16 *D_800C39E8[];
extern u8 *D_800C3A10[];
void func_15022388(s32 arg0, s32 arg1) {
    struct127 *obj;
    u8 *e;
    if (D_800C39E8[arg1][arg0] != 0) {
        e = D_800C3A10[arg1] + arg0 * 8;
        if (*(u16 *)e == 2) {
            obj = func_15083E90(e[2]);
            if (obj != NULL) {
                *((u8 *)obj + 0x6C) = 0;
                *((u8 *)obj + 0x6D) = 0;
                *((u8 *)obj + 0x6A) = 0;
                *((u8 *)obj + 0x6B) = 0;
                *(s16 *)((u8 *)obj + 0x282) = 0;
                *(s16 *)((u8 *)obj + 0x27A) = 0;
                *(s16 *)((u8 *)obj + 0x27C) = 0;
                *(s16 *)((u8 *)obj + 0x27E) = 0;
                *(s16 *)((u8 *)obj + 0x280) = 0;
                func_1507E7E4(obj, 0, 3, 0xFFFF, 0xA);
                *((u8 *)obj + 0x71) = 0;
            }
        }
    }
}

#ifdef NON_MATCHING
s32 func_15022304(s32, s32);
s32 func_15082E44(u8 *, s32, s32, s32, s32);
extern u8 D_800D2520;

s32 func_15022440(s32 arg0, s32 arg1) {
    struct127 *sp3C;
    s32 sp38;
    s32 sp34;
    u8 **sp2C;
    s32 var_v0;
    u8 **temp_a2;
    u8 temp_v0;
    u8 *temp_v1;

    var_v0 = arg1;
    temp_a2 = &D_800C3A10[var_v0];
    if (D_800C39E8[var_v0][arg0] != 0) {
        temp_v1 = *temp_a2 + (arg0 * 8);
        if ((*(u16 *)((u8 *)temp_v1 + 0)) == 2) {
            temp_v0 = (*(u8 *)((u8 *)temp_v1 + 2));
            sp2C = temp_a2;
            sp34 = (s32) temp_v0;
            var_v0 = func_15083E0C(temp_v0);
            if (var_v0 != -1) {
                sp38 = var_v0;
                sp2C = temp_a2;
                var_v0 = func_1505EEF4(var_v0);
                if (var_v0 != 0) {
                    if ((*(u8 *)((u8 *)var_v0 + 5)) == 3) {
                        if (temp_a2 != D_800C3A10) {
                            (*(u8 *)((u8 *)var_v0 + 5)) = 4U;
                        } else {
                            (*(u8 *)((u8 *)var_v0 + 5)) = 0U;
                        }
                    }
                    if (sp34 == 1) {
                        (*(s32 *)((u8 *)var_v0 + 0xF4)) = (s32) ((*(s32 *)((u8 *)var_v0 + 0xF4)) & ~0x2A);
                        return var_v0;
                    }
                    /* Duplicate return node #13. Try simplifying control flow for better match */
                    return var_v0;
                }
                if (sp38 < (s32) D_800D2520) {
                    func_15082E44((sp38 * 0x30) + D_800D20FC, sp38, 0, arg1, 0);
                    var_v0 = func_1505EEF4(sp38);
                    if (var_v0 != 0) {
                        sp3C = (struct127 *) var_v0;
                        func_1505E650((struct127 *) var_v0, 0U, 0.0f, 0.0f, 0.0f, 0.0f, 1);
                        var_v0 = func_15022304((s32) (sp3C - D_800CC2D0) / 812, arg1);
                    }
                }
                /* Duplicate return node #13. Try simplifying control flow for better match */
                return var_v0;
            }
        }
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022440.s")
#endif
#ifdef NON_MATCHING
/* Actor pass of cutscene slot `slot`: for each of its D_800C3A5A[slot] actors that has a camera and actor track
 * (D_800C39F0 / D_800C39E8 words != 0) and a record of kind 2 (D_800C3A10[slot] + 8 i), finds the object
 * (func_15083E90(record[2])) and gives it its actor frame (func_15021834(obj, slot, i)). */
void func_150225D0(s32 slot) {
    struct127 *obj;
    u8 *rec;
    s32 i;

    for (i = 0; i < D_800C3A5A[slot]; i++) {
        if (D_800C39F0[slot][i] == 0 || D_800C39E8[slot][i] == 0) {
            continue;
        }
        rec = D_800C3A10[slot] + i * 8;
        if (*(u16 *)rec == 2) {
            obj = func_15083E90(rec[2]);
            if (obj != NULL) {
                func_15021834(obj, slot, i);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150225D0.s")
#endif

#ifdef NON_MATCHING
extern u8 D_800C3970[];

/* Adds `id` to sequence slot `slot`'s id list (D_800C3970, 30 bytes per slot, count D_800C396A[slot]) unless it
 * is already there. Returns i + 1 for an id found at index i, else the old count (the loop counter, as the
 * original). The list is not bounded. */
s32 func_150226E8(u8 id, s32 slot) {
    u8 *list = &D_800C3970[slot * 30];
    s32 count = D_800C396A[slot];
    s32 i = 0;

    while (i < count) {
        i++;
        if (list[i - 1] == id) {
            return i;
        }
    }
    list[count] = id;
    D_800C396A[slot] = count + 1;
    return i;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150226E8.s")
#endif

#ifdef NON_MATCHING
s32 func_150226E8(u8, s32);

s32 func_15022764(s32 arg0, s32 arg1) {
    u8 *sp1C;
    s32 var_v0;
    u8 *temp_v1;

    var_v0 = arg1 * 4;
    if (D_800C39E8[arg1][arg0] != 0) {
        temp_v1 = D_800C3A10[arg1] + (arg0 * 8);
        if ((*(u16 *)((u8 *)temp_v1 + 0)) == 3) {
            var_v0 = func_151149AC((*(u8 *)((u8 *)temp_v1 + 2)));
            if ((var_v0 != 0) && ((*(u8 *)((u8 *)var_v0 + 0x6E)) == 1)) {
                sp1C = (u8 *) var_v0;
                var_v0 = func_150226E8((*(u8 *)((u8 *)var_v0 + 0x72)), arg1);
                (*(s8 *)((u8 *)sp1C + 0x6E)) = 0;
            }
        }
    }
    return var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022764.s")
#endif
s32 func_15022764(s32, s32);

void func_150227FC(s32 arg0) {
    s32 var_s0;
    u8 *temp_s1;

    temp_s1 = &D_800C3A5A[arg0];
    var_s0 = 0;
    if ((s32) *temp_s1 > 0) {
        do {
            func_15022764(var_s0, arg0);
            var_s0 += 1;
        } while (var_s0 < (s32) *temp_s1);
    }
}

u8 *func_151149AC(u8);
extern u8 D_800C3970[];
void func_15022864(s32 arg0)
{
  s32 i;
  u8 *cnt;
  u8 *p;
  cnt = &D_800C396A[arg0];
 do { i = 0; if ((*cnt) > 0) { p = D_800C3970 + (arg0 * 0x1E); do { func_151149AC(*p)[0x6E] = 1; i += 1; p += 1; } while (i < (*cnt)); } } while (0);
}

void func_15022388(s32, s32);
s32 func_15022440(s32, s32);

void func_150228F0(s32 arg0) {
    s32 var_s0;
    u8 *temp_s2;

    if ((&D_800C35EA)[arg0] == 1) {
        D_800C3638 = 0;
        temp_s2 = &D_800C3A5A[arg0];
        var_s0 = 0;
        if ((s32) *temp_s2 > 0) {
            do {
                func_15022440(var_s0, arg0);
                func_15022388(var_s0, arg0);
                var_s0 += 1;
            } while (var_s0 < (s32) *temp_s2);
        }
        D_800C3638 = 1;
    }
}

extern u8 D_800C3938[][0x19];

void func_1502298C(s32 arg0)
{
  s32 i;
  u8 *new_var; // fakematch: permuter temp
  s32 n;
  u8 *cnt = &D_800C3930[arg0];
  u8 *p;
  struct127 *e;
 i = 0; n = *cnt; if (n > 0) { p = D_800C3938[arg0]; do {
      e = &D_800CC2D0[*p];
      if (e->interaction_state)
      {
        new_var = &(*cnt);
        func_15060F28(e, 0);
        n = *new_var;
      }
      i++;
      p++;
    }
    while (i < n);
  }
}

void func_15022A40(s32 *arg0) {
    s32 v = arg0[0];

    if ((v == 27) || (v == 4)) {
        if (D_800863B4[v] != NULL) {
            D_800863B4[v]();
        }
    }
}

#ifdef NON_MATCHING
extern u8 D_800CC3FF;   /* D_800CC2D0[0] + 0x12F: actor id of an object (0x32C-byte objects) */
#endif
#ifdef NON_MATCHING
/* Does object `obj` take part in the loaded cutscene? Slot 1 for object kind 4 (byte +5), else slot 0; its id
 * is the actor id of its owner D_800CC2D0[obj[0x65]] (byte at +0x12F) when it has one, else its own byte +0x3B.
 * Returns 2 (owned) / 1 when an active actor of that slot has entry type 2 (object) with that id (entry byte
 * +2), else 0 (also for no object, a free slot obj[0] == 0, or no scene loaded in slot 0). */
s32 func_15022A8C(s32 *obj) {
    u8 *ent;
    u8 owner;
    u8 id;
    s32 slot;
    s32 n;
    s32 i;

    if (obj == NULL || obj[0] == 0 || D_800C39E8[0] == NULL) {
        return 0;
    }
    slot = (((u8 *)obj)[5] == 4) ? 1 : 0;
    owner = ((u8 *)obj)[0x65];
    if (owner != 0) {
        id = (&D_800CC3FF)[owner * 0x32C];
    } else {
        id = ((u8 *)obj)[0x3B];
    }
    n = D_800C3A5A[slot];
    for (i = 0; i < n; i++) {
        if (D_800C39E8[slot][i] == 0) {
            continue;
        }
        ent = D_800C3A10[slot] + i * 8;
        if (*(u16 *)ent == 2 && ent[2] == id) {
            return (owner != 0) ? 2 : 1;
        }
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022A8C.s")
#endif

#ifdef NON_MATCHING
s32 func_15022BB0(s32 arg0, s32 arg1) {
    s32 var_v0;
    u16 *var_a2;
    u8 temp_v1;

    temp_v1 = D_800C3A5A[arg1];
    var_v0 = 0;
    if ((s32) temp_v1 > 0) {
        var_a2 = D_800C39E8[arg1];
loop_2:
        if ((*var_a2 != 0) && ((*(u8 *)((u8 *)((D_800C3A10[arg1] + (var_v0 * 8))) + 2)) == D_800DBEF4[arg0].pad70[2])) {
            return 1;
        }
        var_v0 += 1;
        var_a2 = (u16 *)((u8 *)var_a2 + (2));
        if (var_v0 >= (s32) temp_v1) {
            /* Duplicate return node #6. Try simplifying control flow for better match */
            return 0;
        }
        goto loop_2;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022BB0.s")
#endif
#ifdef NON_MATCHING
void func_15022238(s16, s16, s16, f32);
f32 sinf(f32);
f32 cosf(f32);
#endif
#ifdef NON_MATCHING
/* Places the scene of cutscene slot `slot` in the level: the first actor whose entry (D_800C3A10[slot] + i * 8)
 * is an anchor moves every actor's path keys (s16 x, y, z at D_eu_800C3C88[slot][j] + k * 8):
 *   type 6: by the offset from the anchor's first key to object func_15083E90(b) (a == 0) or entity
 *     func_151149AC(b) (a == 1); other a: nothing.
 *   type 7: rotated about the anchor's first key by D_800C39B4 - its channel-7 key angle (stored in
 *     D_800C39C4) and moved onto D_800C39AC; the channel-7 keys of the other camera tracks turn by the same
 *     angle unless their sound record +0x20 is 7.
 * func_15022238 gets the anchor (unless D_800C3663). */
void func_15022C4C(s32 slot) {
    TrackKey *keys;
    u8 *ent;
    u8 *o;
    s16 *p;
    s16 *q;
    s32 i;
    s32 j;
    s32 k;
    s32 cnt;
    s32 keep;
    f32 ang;
    f32 rot;
    f32 r;
    f32 tx;
    f32 ty;
    f32 tz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 px;
    f32 py;
    f32 pz;
    f32 c;
    f32 s;
    f32 ox;
    f32 oz;
    f32 nx;
    f32 nz;

    for (i = 0; i < D_800C3A5A[slot]; i++) {
        if (D_800C39E8[slot][i] == 0) {
            continue;
        }
        ent = D_800C3A10[slot] + i * 8;
        if (*(u16 *)ent == 6) {
            if (D_800C3663 == 0) {
                p = (s16 *)D_eu_800C3C88[slot][i];
                func_15022238(p[0], p[1], p[2], 0.0f);
                ent = D_800C3A10[slot] + i * 8;
            }
            if (ent[2] == 0) {
                o = (u8 *)func_15083E90(ent[3]);
                if (o == NULL) {
                    return;
                }
                tx = *(f32 *)(o + 0x14);
                ty = *(f32 *)(o + 0x18);
                tz = *(f32 *)(o + 0x1C);
            } else if (ent[2] == 1) {
                o = func_151149AC(ent[3]);
                if (o == NULL) {
                    return;
                }
                tx = *(s16 *)(o + 0x10);
                ty = *(s16 *)(o + 0x12);
                tz = *(s16 *)(o + 0x14);
            } else {
                return;
            }
            p = (s16 *)D_eu_800C3C88[slot][i];
            dx = tx - (f32)p[0];
            dy = ty - (f32)p[1];
            dz = tz - (f32)p[2];
            for (j = 0; j < D_800C3A5A[slot]; j++) {
                for (k = 0; k < D_800C39E8[slot][j]; k++) {
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[0] = (s32)((f32)q[0] + dx);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[1] = (s32)((f32)q[1] + dy);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[2] = (s32)((f32)q[2] + dz);
                }
            }
            return;
        }
        if (*(u16 *)ent == 7) {
            cnt = D_800C39F0[slot][i];
            ang = 0.0f;
            keys = (TrackKey *)D_800C3B98[slot][i];
            for (k = 0; k < cnt; k++) {
                if (keys[k].channel == 7) {
                    ang = keys[k].value;
                    break;
                }
            }
            if (D_800C3663 == 0) {
                p = (s16 *)D_eu_800C3C88[slot][i];
                func_15022238(p[0], p[1], p[2], ang);
            }
            rot = D_800C39B4 - ang;
            D_800C39C4 = rot;
            p = (s16 *)D_eu_800C3C88[slot][i];
            r = rot * 0.017453292f;
            px = p[0];
            py = p[1];
            pz = p[2];
            c = cosf(r);
            s = sinf(r);
            dy = (f32)D_800C39AC[1] - py;
            for (j = 0; j < D_800C3A5A[slot]; j++) {
                keep = FALSE;
                for (k = 0; k < D_800C39E8[slot][j]; k++) {
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    ox = (f32)q[0] - px;
                    oz = (f32)q[2] - pz;
                    nx = ox * c + oz * s;
                    nz = -ox * s + oz * c;
                    q[0] = (s32)((f32)D_800C39AC[0] + nx);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[1] = (s32)((f32)q[1] + dy);
                    q = (s16 *)D_eu_800C3C88[slot][j] + k * 4;
                    q[2] = (s32)((f32)D_800C39AC[2] + nz);
                }
                if (D_800C39F8[slot][j] != 0 && *(s8 *)((u8 *)D_800C3AA8[slot][j] + 0x20) == 7) {
                    keep = TRUE;
                }
                if (!keep) {
                    for (k = 0; k < D_800C39F0[slot][j]; k++) {
                        keys = (TrackKey *)D_800C3B98[slot][j];
                        if (keys[k].channel == 7) {
                            keys[k].value += rot;
                        }
                    }
                }
            }
            return;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022C4C.s")
#endif

#ifdef NON_MATCHING
/* Camera actor of cutscene slot `slot`: of the slot's sound / event records D_800C3AA8[slot][i] (i < the actor
 * count D_800C3A5A[slot]) asks func_15023C60 (type 3) for the nearest event; the record it reports with the
 * smallest distance gives the actor (s16 at +2). Without one the first actor with entry type 1 (u16 at
 * D_800C3A10[slot] + i * 8), else 0. `pos` (the script position) is not read. */
s32 func_1502330C(s32 slot, s32 pos) {
    u8 *found;
    s32 best;
    s32 dist;
    s32 actor;
    s32 i;

    best = 99999;
    actor = -1;
    for (i = 0; i < D_800C3A5A[slot]; i++) {
        if (D_800C3AA8[slot][i] != 0) {
            found = NULL;
            dist = func_15023C60(D_800C3AA8[slot][i] + 0x18, 3, i, &found, 0, 0, 0, 0, 0, 0, slot);
            if (found != NULL && dist < best) {
                best = dist;
                actor = *(s16 *)(found + 2);
            }
        }
    }
    if (actor == -1) {
        actor = 0;
        for (i = 0; i < D_800C3A5A[slot]; i++) {
            if (*(u16 *)(D_800C3A10[slot] + i * 8) == 1) {
                actor = i;
                break;
            }
        }
    }
    return actor;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502330C.s")
#endif
void func_15023464(void) {
    bzero(D_800C3CA0, 0xA8);
}

void func_1502348C(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if ((s16)D_800C3CA0[i].unk0 != 0) {
            func_1516D850(*(s32 *)((u8 *)&D_800C3CA0[i] + 0x34));
            *(s32 *)((u8 *)&D_800C3CA0[i] + 0x34) = 0;
            D_800C3CA0[i].unk0 = 0;
        }
    }
}

void func_150234E8(s16 *arg0, s32 arg1) {
    if (arg1 != 0) {
        func_1516D850(*(s32 *)((u8 *)arg0 + 0x34));
        *(s32 *)((u8 *)arg0 + 0x34) = 0;
    } else if (*(u8 *)((u8 *)arg0 + 0xC) != 0) {
        func_1516D898(*(s32 *)((u8 *)arg0 + 0x34));
    } else {
        *(s32 *)((u8 *)arg0 + 0x34) = 0;
    }
    *(s16 *)((u8 *)arg0) = 0;
}

#ifdef NON_MATCHING
extern s32 D_800C4168;

s16 *func_1502354C(s32 arg0, s32 arg1) {
    s16 *sp20;                                      /* compiler-managed */
    struct163 *sp1C;
    s16 *sp18;                                      /* compiler-managed */
    s16 temp_v0;
    s32 var_a3;
    struct163 *var_a2;
    struct163 *var_t0;
    struct163 *var_t1;

    var_a3 = arg0 + 1;
    var_t1 = NULL;
    var_t0 = NULL;
    var_a2 = D_800C3CA0;
loop_1:
    temp_v0 = (s16) var_a2->unk0;
    if (var_a3 == temp_v0) {
        if ((arg1 != 0) && (var_a2->unkC != 0)) {
            sp18 = (s16 *) var_a2;
            arg0 = var_a3;
            sp1C = D_800C3CA0;
            sp20 = NULL;
            func_150234E8((s16 *) D_800C3CA0, 1);
            var_a3 = arg0;
            var_t0 = sp1C;
            var_t1 = NULL;
        } else {
            var_t1 = var_a2;
        }
    } else if (temp_v0 == 0) {
        var_t0 = var_a2;
        if ((arg1 != 0) && (var_a2->unkC != 0)) {
            sp18 = var_a2;
            arg0 = var_a3;
            sp1C = var_t0;
            sp20 = NULL;
            func_150234E8((s16 *) var_a2, 1);
            var_a3 = arg0;
            var_t1 = NULL;
        }
    } else {
        var_a2 = (struct163 *)((u8 *)var_a2 + (0x38));
        if ((s32)var_a2 != (s32)&D_800C4168) {
            goto loop_1;
        }
    }
    if ((s32)var_a2 == (s32)&D_800C4168) {
        sp1C = D_800C3CA0;
        arg0 = var_a3;
        sp20 = var_t1;
        func_150234E8((s16 *) D_800C3CA0, 1);
        var_a3 = arg0;
        var_t0 = sp1C;
    }
    if (var_t1 != NULL) {
        return (s16 *) var_t1;
    }
    if (var_t0 != NULL) {
        var_t0->unk0 = (u16) var_a3;
    }
    return (s16 *) var_t0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502354C.s")
#endif
#ifdef NON_MATCHING
/* P92: declarations for func_15023684 */
void func_1508F060(void);
void func_1507F640(void);
extern f32 D_80096DCC;   /* no water level (-10000) */
#endif
#ifdef NON_MATCHING
/* Scene teardown, player (func_1501E888): clears flag 0x200 of object 0 (+0x25C) and, unless D_800C39CA, resets
 * the player object func_15083E90(1) (D_800C3E78 = its index): speeds / timers cleared; in water (water level
 * +0x118 set, D_80096DCC = none, and above the feet +0x18): swimming (+0xAD = 1, func_1508F060 when the water
 * is deeper than 50 above the floor +0x1A6 or the model flag +0x31C->+0x20 bit 0 is set), else standing on the
 * floor +0x180 (+0x20 = -4, +0x24 = 5). Then the height above the floor (+0x28), cleared input / state bytes,
 * D_800D154C = the player and the idle animation (func_1507F640). `slot` is not read. */
void func_15023684(s32 slot) {
    u8 *p;
    f32 water;

    *(u32 *)((u8 *)D_800CC2D0 + 0x25C) &= ~0x200;
    if (D_800C39CA != 0) {
        return;
    }
    p = (u8 *)func_15083E90(1);
    if (p == NULL) {
        return;
    }
    D_800C3E78 = (p - (u8 *)D_800CC2D0) / 0x32C;
    *(f32 *)(p + 0x3C) = 0.0f;
    if (*(f32 **)(p + 0x31C) != NULL) {
        **(f32 **)(p + 0x31C) = 0.0f;
    }
    *(f32 *)(p + 0x54) = 0.0f;
    *(s16 *)(p + 0xCC) = 0;
    p[0xD0] = 0;
    water = *(f32 *)(p + 0x118);
    if (D_80096DCC != water && *(f32 *)(p + 0x18) < water) {
        p[0xAD] = 1;
        *(f32 *)(p + 0x20) = 0.0f;
        *(f32 *)(p + 0x24) = 0.0f;
        if (water - 50.0f < (f32)*(s16 *)(p + 0x1A6) || (*(u8 **)(p + 0x31C))[0x20] & 1) {
            *(s16 *)(p + 0xB2) = 0;
            func_1508F060();
        }
    } else {
        p[0xAD] = 0;
        *(s16 *)(p + 0xB2) = 0;
        *(f32 *)(p + 0x20) = -4.0f;
        *(f32 *)(p + 0x18) = *(f32 *)(p + 0x180);
        *(f32 *)(p + 0x1CC) = *(f32 *)(p + 0x180);
        *(f32 *)(p + 0x24) = 5.0f;
    }
    p[0x81] = 0;
    p[0x83] = 0;
    p[0x89] = 0;
    p[0x8A] = 0;
    p[0x104] = 0;
    *(f32 *)(p + 0x28) = *(f32 *)(p + 0x18) - *(f32 *)(p + 0x180);
    D_800D154C = (struct127 *)p;
    func_1507F640();
    (*(u8 **)(p + 0x31C))[0x23] = 0;
    p[0x276] = 0;
    *(s16 *)(p + 0x282) = 0;
    *(s16 *)(p + 0x278) = 0;
    p[0x284] = p[0x285] = p[0x286] = p[0x287] = 0;
    (*(u8 **)(p + 0x31C))[0x31] = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15023684.s")
#endif
#ifdef NON_MATCHING
void func_15021834(struct127 *, s32, s32);
extern s32 D_eu_800C3A60;
extern s32 D_800C39D0;
s32 func_15022A8C(s32 *);
void func_1504A730(void);
void func_15061B4C(void);
void func_1507EB1C(s32 *);
void func_150802A8(s32 *);
extern u8 D_800C3A78;

void func_1502378C(void) {
    struct127 *var_s0;
    u8 var_s1;

    var_s0 = D_800CC2D0;
    var_s1 = 0;
    if (D_800C3A78 != 0) {
        func_1504A730();
        return;
    }
    do {
        if (var_s0->interaction_state != 0) {
            D_800C3E78 = var_s1;
            func_15022A40(&var_s0->interaction_state);
            func_1507EB1C(&var_s0->interaction_state);
            if (func_15022A8C(&var_s0->interaction_state) != 0) {
                func_15021834(&var_s0->interaction_state, 0, -1);
                func_150627D4(var_s0);
                func_150802A8(&var_s0->interaction_state);
                var_s0->unk2FF = 1;
            }
        }
        var_s1 += 1;
        var_s0 = (struct127 *)((u8 *)var_s0 + (0x32C));
    } while (var_s1 != 0x19);
    func_15061B4C();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502378C.s")
#endif