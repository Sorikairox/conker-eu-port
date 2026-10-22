#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_15080628(void);
u8 *func_151149AC(u8);
extern u8 D_800C3938[][0x19];
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501CE34.s")

s32 func_1501D064(s32 arg0) {
    s32 sum = 0;
    s32 i;

    for (i = 0; i < D_800C3A5A[arg0]; i++) {
        sum += D_800C39F8[arg0][i];
    }
    return sum;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501D044.s")

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
s32 func_1501E888(s32, s32);
void func_1502457C(s32, s32);
s32 func_1501ECA4(s32);
void func_150228F0(s32);
void func_150227FC(s32);
void func_150225D0(s32);
s32 func_15020F6C(s32);
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DB18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DE84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501DF70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E0C8.s")

s32 func_1000E17C(void);
void func_1501DF70(void);
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
        func_1501DF70();
        D_800C3C88 = 0;
    }
}

#ifdef NON_MATCHING
void func_1501E46C(s32);
s32 func_1501E888(s32, s32);
s32 func_1501ECA4(s32);
s32 func_15020F6C(s32);
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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E5AC.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501E888.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501EA84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501ECA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501F7D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501FD34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1501FF10.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020430.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020920.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15020F6C.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15021E60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150220CC.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_150225D0.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022A8C.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15022C4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_1502330C.s")

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
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_4A070/func_15023684.s")

#ifdef NON_MATCHING
void func_15021834(struct127 *, s32, s32);
s32 func_15022A8C(s32 *);
void func_1504A730(void);
s32 func_15061B4C();
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