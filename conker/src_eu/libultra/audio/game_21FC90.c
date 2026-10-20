#include <n_libaudio.h>

extern s32  D_800E0E00;
extern s32  D_800E0E04;
extern s32  D_800E0E10;
extern s16  D_800E0E14;
extern s16  D_800E0E16;
extern u8   D_800E0E18;
extern u8   D_800E0E2C;
extern s32  D_800E0E20;
extern s32  D_800E0E24;
extern s32  D_800E0E28;
extern s32  *D_800E0E30; // 0x8000
extern s32  D_800E0D80; // libaudio struct?
extern s16  D_800E0DB0;
extern s16  D_800E0DB2;
extern s32  D_800E0DD8;
extern s32  D_800E0DE0;
extern s32  D_800E0DE4;
extern s32  D_800E0DFC;
extern s32  D_800E1238;
extern void *D_8002BA44;


void func_151F2960(s32 arg0, s32 arg1) {
    if (D_800E0DFC == 0) {
        return;
    }
    D_800E0E04 = 4;
    if (D_800E0E2C == 0) {
      D_800E0E2C = 1;
        D_800E0E30 = allocate_memory(0x8000, 0xFF, 2, 1);
        if (D_800E0E30 == 0) {
            D_800E0E2C = 0;
            return;
        }
        D_800E0E20 = func_1502B5C8(0, 2, 0x17, 4);
        if (D_800E0E20 != 0) {
            func_100043B4(D_800E0E20, 0xFF);
        }
        D_800E0E24 = func_1502B5C8(0, 2, 0x17, 5);
        if (D_800E0E24 != 0) {
            func_100043B4(D_800E0E24, 0xFF);
        }
        D_800E0E28 = func_1502B5C8(0, 2, 0x17, 6);
        if (D_800E0E28 != 0) {
            func_100043B4(D_800E0E28, 0xFF);
        }
        if ((D_800E0E20 == 0) || (D_800E0E24 == 0) || (D_800E0E28 == 0)) {
            if (D_800E0E20 != 0) {
                func_10004074(D_800E0E20);
            }
            if (D_800E0E24 != 0) {
                func_10004074(D_800E0E24);
            }
            if (D_800E0E28 != 0) {
                func_10004074(D_800E0E28);
            }
            func_10004074(D_800E0E30);
            D_800E0E30 = 0;
            D_800E0E2C = 0;
            return;
        }
        func_151F3DE0();
    }
    D_800E0D80 = arg0;
    D_800E0DE0 = arg1;
    D_800E0DE4 = 0;
    D_800E0E10 = 0;
    D_800E0E18 = 5;
    D_800E0E04 = 5;
}

void func_151F2BA8(void) {
    u32 mask = osSetIntMask(1);
    D_800E0E04 = 3;
    osSetIntMask(mask);
}

void func_151F2BE8(void) {
    u32 mask = osSetIntMask(1);
    if (D_800E0E04 == 5) {
        D_800E0E04 = 6;
    } else {
        D_800E0E04 = 2;
    }
    osSetIntMask(mask);
}

void func_151F2C4C(void) {
    u32 mask = osSetIntMask(1);
    if (D_800E0E04 == 2) {
        D_800E0E18 = 5;
        D_800E0E04 = 7;
    } else if (D_800E0E04 == 6) {
        D_800E0E18 = 5;
        D_800E0E04 = 5;
    }
    osSetIntMask(mask);
}

s32 func_151F2CDC(void) {
    s32 ret = 0;
    u32 mask = osSetIntMask(1);
    if ((D_800E0E04 == 1) || (D_800E0E04 == 5) || (D_800E0E04 == 6) || (D_800E0E04 == 7) || (D_800E0E04 == 2)) {
        ret = D_800E0E04;
    }
    osSetIntMask(mask);
    return ret;
}

void func_151F2D6C(s32 arg0, s32 arg1) {
    u32 mask = osSetIntMask(1);
    if (arg0 < 0) {
        D_800E1238 = 0;
    } else if (arg0 >= 0x8000) {
        D_800E1238 = 0x7FFF;
    } else {
        D_800E1238 = arg0;
    }
    D_800E0E10 = arg1;
    osSetIntMask(mask);
}

void func_151F2DFC(s32 arg0, s32 arg1) {
    if (arg0 >= 0x80) {
        arg0 = (u16)0x7F;
    } else {
        if (arg0 < 0) {
            arg0 = (u16)0;
        }
    }
    D_800E0E16 = arg0;
    if (arg1 != 0) {
        D_800E0E14 = (s16) D_800E0E16;
    }
}

void func_151F2E4C(s32 arg0, s32 arg1) {
    D_800E0DB2 = arg0;
    D_800E0DB0 = arg1;
    if (D_800E0DD8 == 0) {
        D_800E0DD8 = 2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/audio/game_21FC90/func_151F2E88.s")

typedef struct {
    /* 0x00 */ u8  pad0[0xC];
    /* 0x0C */ s16 pan;
    /* 0x0E */ s16 volume;
    /* 0x10 */ s16 cvolL;
    /* 0x12 */ s16 cvolR;
    /* 0x14 */ u8  pad14[0x4];
    /* 0x18 */ u16 lratl;
    /* 0x1A */ s16 lratm;
    /* 0x1C */ s16 ltgt;
    /* 0x1E */ u16 rratl;
    /* 0x20 */ s16 rratm;
    /* 0x22 */ s16 rtgt;
    /* 0x24 */ u8  unk24;
    /* 0x28 */ s32 delta;
    /* 0x2C */ s32 segEnd;
    /* 0x30 */ u8  pad30[0x58];
    /* 0x88 */ s32 unk88; // target volume
    /* 0x8C */ u8  pad8C[0x4];
    /* 0x90 */ u32 unk90; // ramp time
    /* 0x94 */ s16 unk94; // target pan
} struct_151F39E4;

extern s16 D_8002BF60[]; // eqpower
extern u8 D_800428C1;
extern u8 D_800428C2;
s16 _getVol(s16 ivol, s32 samples, s16 ratem, u16 ratel);
void func_151F2BA8(void);

void func_151F39E4(struct_151F39E4 *arg0) {
    if ((arg0->volume != arg0->unk88) || (arg0->pan != arg0->unk94)) {
        if (arg0->delta >= arg0->segEnd) {
            arg0->ltgt = (D_8002BF60[arg0->pan] * arg0->volume) >> 15;
            arg0->rtgt = (D_8002BF60[127 - arg0->pan] * arg0->volume) >> 15;
            arg0->delta = arg0->segEnd;
            arg0->cvolL = arg0->ltgt;
            arg0->cvolR = arg0->rtgt;
        } else {
            arg0->cvolL = _getVol(arg0->cvolL, arg0->delta, arg0->lratm, arg0->lratl);
            arg0->cvolR = _getVol(arg0->cvolR, arg0->delta, arg0->rratm, arg0->rratl);
        }
        if (arg0->cvolL == 0) {
            arg0->cvolL = 1;
        }
        if (arg0->cvolR == 0) {
            arg0->cvolR = 1;
        }
        arg0->volume = arg0->unk88;
        if ((arg0->volume == 0) && (arg0->unk90 != 0)) {
            func_151F2BA8();
        }
        if (arg0->pan != arg0->unk94) {
            if (D_800428C2 != 0) {
                arg0->pan = (arg0->unk94 >> 1) + 0x20;
            } else if (D_800428C1 != 0) {
                arg0->pan = 0x40;
            } else {
                arg0->pan = arg0->unk94;
            }
        }
        arg0->delta = 0;
        arg0->segEnd = ((arg0->unk90 + 183) / 184) * 184;
        arg0->unk24 = 1;
    }
}

void func_151F3C1C(s32 arg0) {
    D_800E0E00 = arg0;
}

void func_151F3C34(s32 arg0) {
    D_800E0DFC = arg0;
}

s32 func_151F3C4C(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 sp1C;
    s32 (*dma)(s32, s32, s32);

    if (arg3 != -1) {
        D_800E0DE4 = arg3;
    }
    if ((D_800E0DE4 + arg2) > D_800E0DE0) {
        arg2 = D_800E0DE0 - D_800E0DE4;
    }
    dma = ((ALDMAproc (*)(void *))(((void **)D_8002BA44)[9]))(&sp1C);
    sp1C = dma(D_800E0D80 + D_800E0DE4, arg2, 0);
    if (sp1C == 0) {
        return 0;
    }
    sp1C += 0x80000000;
    osInvalDCache((void *)sp1C, arg2);
    bcopy((void *)sp1C, arg1, arg2);
    D_800E0DE4 += arg2;
    return arg2;
}

void func_151F3D78(void) {
    s32 sp1C;
    void (*dma)(s32, s32, s32);

    dma = ((ALDMAproc (*)(void *))(((void **)D_8002BA44)[9]))(&sp1C);
    dma(D_800E0D80 + D_800E0DE4, 0x810, 0);
}
