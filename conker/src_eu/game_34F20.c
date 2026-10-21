#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15007A70(s16 arg0, s16 arg1, s16 arg2) {

    D_800BE9B4 = 2;
    func_1503FB08();
    D_800BE9F0 = D_800BE9F4 = arg2;

    func_15172C50(D_800DD2C0);
    func_15008230();
    func_15005270();
    func_15017300(arg0, arg1);

    func_15015F40(D_80087280[D_800D2138], arg2);
    func_150175E0();
    func_150177F8();
    func_15089BB0();
    func_15000090();
    D_800BE938 = 1;
    D_800D18A8 = 0;
    D_800BE9ED = 0;
}

// requires jump table
#ifdef NON_MATCHING
// Level loader (hand C from the asm, P13). Runs once per level change: picks the music/ambience id for the
// level (func_100014C4), resets the per-level systems, allocates the two DL buffers (func_15015E30), arms the
// controller-read timer (func_1501BB20), initialises every player (func_15125690), every live object
// (func_150A16A4) and commits the level id (D_800BE9F4 = D_800BE9F0).
extern s32 D_8003E724;
extern u8 D_800BEA39;
extern u8 D_800BEA3A;
extern u8 D_800BEE2C;
extern s32 D_800BEE08;
extern s32 D_800BE804;
extern u8 D_800E0FC9;
extern u8 D_800E1001;
extern s8 D_eu_800E0E30;
void func_100014C4(s32 arg0);
void func_10004308(void);
void func_1000F248(s32 arg0);
void func_10011FEC(void);
void func_100125CC(s32 arg0);
void func_15000AC0(void);
void func_15002F40(s32 arg0);
void func_15002FB4(s32 arg0);
void func_150038A0(void);
void func_150039B0(s32 arg0);
void func_15004E00(void);
void func_15004E80(void);
void func_15004F00(void);
void func_15004F10(void);
void func_150081E4(void);
void func_15008248(s32 arg0);
void func_150082CC(void);
void func_15008840(void);
void func_15008DD0(void);
void func_15009150(s32 arg0);
void func_1500BE68(void);
void func_15012780(void);
void func_15016370(void);
void func_15016500(void);
void func_1501748C(s16 arg0);
void func_15085710(s16, s16, s32);
void func_15125690(struct108 *arg0, s32 arg1);
void func_10003ACC(s32 arg0, s32 arg1, s32 arg2);
void func_150000B0(void);
s32 func_150006E0(s32);
void func_15000AD0(s32 arg0);
void func_150031EC(s32 arg0);
void func_15003668(s32 arg0);
void func_150039E0(s32 arg0, s32 arg1);
void func_15004574(void);
void func_150045C4(s32 arg0);
void func_15004D50(void);
void func_15005290(s32 arg0, s32 arg1);
void func_15008870(s32 arg0);
void func_15008930(s32 arg0);
void func_15008A60(void);
void func_150091D0(void);
void func_150092DC(void);
void func_1500C1E0(void);
void func_1500C2A0(void);
void func_1500E470(s32 arg0);
void func_1500E70C(s32 arg0);
void func_1500E738(void);
void func_15012F40(void);
void func_15013000(void);
void func_150158C0(void);
void func_15015E30(void);
void func_150162B0(void);
void func_15016380(s32 arg0);
void func_15016670(void);
void func_15016690(s32 arg0);
void func_15016950(s32 arg0);
void func_15017578(s32 arg0);
void func_15017640(void);
void func_15017868(void);
void func_15017930(s32 arg0);
void func_1501A220(s32 arg0, s32 arg1);
void func_1501B640(void);
void func_1501BB20(void);
void func_1501C51C(void);
void func_1501CC1C(void);
void func_1502AAF0(void);
void func_1502AAF8(s32 arg0);
void func_15044660(void);
void func_1507DFE4(s32 arg0, s32 arg1);
s32 func_1507E114(s32 arg0);
void func_15080600(void);
void func_15085FE0(s32 arg0);
void func_1509BBA0(s32 arg0);
s32 func_1509C2A4(void);
void func_1509C3A0(void);
void func_150A16A4(struct127 *arg0);
void func_1510B5F0(s32 arg0);
void func_1511FEF0(void);
void func_15173850(s32 arg0);
void func_15182388(s32 arg0);
void func_15188500(void);
void func_151BF8F0(s32 arg0, s32 arg1);
void func_151D9398(void);
void func_151E5DD8(void);
s8 func_151E6758(void);
void func_151E8998(void);

void func_15007B3C(void) {
    s32 sp30;   /* in/out for func_1507E114: the save slot / profile byte */
    s32 sp2C;
    s32 level;
    s32 snd;
    s32 i;
    s32 n;
    u8 *obj;

    if (D_800BE9B4 == 0) {
        D_800BE9B4 = 1;
    }
    func_10004308();
    func_15002FB4((s32)D_800BE9F4);

    level = (s32)D_800BE9F4;
    switch (level) {
    case 0x1A: case 0x24: case 0x2B: case 0x2D: case 0x30: case 0x33: case 0x34: case 0x3F:
        snd = (level == 0x24) ? 0xF3 : 0x103;
        if (level == 0x33) snd -= 8;
        if (level == 0x3F) snd -= 8;
        if (level == 0x34) snd += 8;
        break;
    case 0x13:
        snd = 0xEB;
        if (!(((u8 *)D_800D2E4C)[0x11] & 4)) {
            snd = ((s8 *)D_800B0DF0)[0x11] + 0xEB;
        }
        break;
    default:
        snd = ((s8 *)D_800B0DF0)[0x11] + 0xEB;
        break;
    }
    func_100014C4(snd);

    D_eu_800E0E30 = 0;
    func_1500E738();
    func_1500C2A0();
    D_800DCE20 = 0;
    D_800E0D50 = 0;
    func_15008840();
    D_8003E724 = 1;
    sp30 = D_800DD2C0;
    sp2C = func_1507E114((s32)&sp30);
    if (D_800E0B94 == 2) {
        sp30 = D_800E1001;
    }
    D_800BE9F8 = D_800BE9F0;
    D_800BE9F0 = (s32)D_800BE9F4;
    func_150091D0();
    func_15188500();
    D_800BEA39 = 0;
    D_800BEA3A = 0;
    D_800BEE2C = 0;
    func_150081E4();
    if (D_800BE9ED != 0) {
        func_10003ACC(0xFF, 0xFF, 0xFF);
        D_800BE9ED = 0;
    } else {
        func_10003ACC(0, 0, 0);
    }
    if (D_800BE616 == 0 && !(((u8 *)D_800D2E4C)[0x18] & 1)) {
        D_800D2456 = 3;
        D_800D2457 = 3;
        func_15085710(0, 5, 3);
    }
    func_15002F40(D_800BE9F0);
    func_1501C51C();
    func_15015E30();
    func_150162B0();
    func_15017930(D_800BE9F0);
    func_15016500();
    func_1501A220(D_800BEE08, 1);
    func_15012F40();
    func_15008A60();
    func_15000AC0();
    func_15012780();
    func_1500BE68();
    func_15044660();
    func_15016670();
    func_15004F00();
    func_15004E80();
    func_15017868();
    func_15173850(D_800BE9F0);
    func_1502AAF0();
    func_1502AAF8(D_800BE9F0);
    func_150031EC(D_800BE9F0);
    func_150039E0(D_800BE9F0, 1);
    func_15004574();
    func_1511FEF0();
    func_15003668(D_800BE9F0);
    func_150038A0();
    func_150039B0(D_800BE9F0);
    func_15017578(D_800BE9F0);
    func_150045C4(D_800BE9F0);
    func_15008248(D_800BE9F0);
    func_150000B0();
    func_1000F248(D_800BE9F0);
    func_100125CC(D_800BE9F0);
    func_10011FEC();
    func_1501BB20();
    func_15008870(1);
    func_15008930(1);
    func_15016690(D_800BE9F0);
    func_15016950(D_800BE9F0);
    func_15005290(D_800BE9F0, sp30);
    func_15016370();
    func_150006E0(D_800BE9F0);
    func_1510B5F0(0);
    for (i = 0; i <= D_80082FA0; i++) {
        func_15125690((struct108 *)((u8 *)D_800DBFF0 + i * 0x9A0), 1);
    }
    func_1500E70C(D_800BE9F0);
    func_15016380(D_800BE9F0);
    func_150092DC();
    func_15000AD0(D_800BE9F0);
    if (D_800BE9F0 == 0x1D) {
        func_151E8998();
    }
    func_1500E470(D_800BE9F0);
    func_15009150(D_800BE9F0);
    func_15085FE0(D_800BE9F0);
    func_15008DD0();
    func_1501B640();
    func_15080600();
    D_800BE9E4 = 2;
    func_150158C0();
    func_15004F10();
    func_1501748C(D_800D2340);
    func_1500C1E0();
    func_15004E00();
    func_15004D50();
    func_150082CC();
    if (D_800BE616 == 0) {
        func_15085710(0, 9, D_800BE804);
    }
    if (func_1509C2A4() != 0) {
        D_800BE800 = sp30;
    }
    D_800D2E43 = 1;
    func_1509BBA0(4);
    func_1509BBA0(1);
    func_15013000();
    if (sp2C != 0) {
        func_1507DFE4(sp30, sp2C - 1);
    }
    func_151E5DD8();
    if (D_800E0FC9 != 0 || D_800DDE38 == 2) {
        if (D_800C35EA != 1 && D_800DDE38 != 1) {
            n = func_151E6758();
            for (i = 0; i < n; i++) {
                func_15182388(i);
            }
        }
        D_800E0FC9 = 0;
    }
    func_15017640();
    func_1501CC1C();
    obj = (u8 *)D_800CC2D0;
    do {
        if (*(s32 *)obj != 0 && obj[0x127] != 0xFF) {
            func_150A16A4((struct127 *)obj);
        }
        obj += 0x32C;
    } while (obj != (u8 *)&D_800D121C);
    if (D_800D18A8 != 0 && D_800BE9F0 != 0x22) {
        D_800D18A8 = 0;
        func_151BF8F0(0xFF, 1);
    }
    func_1509C3A0();
    D_800BE9F4 = (u16 *)D_800BE9F0;
    func_151D9398();
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_34F20/func_15007B3C.s")
#endif
void func_150081E4(void) {
    s32 i;

    D_800D3668 = 0;
    D_800CBE00 = 0;
    D_800DDD64 = 0;

    for (i = 0; i < 2; i++)
    {
        D_800DF7C8[i] = 0;
    }

    D_800D245C = 0;
    D_800D2548 = 0;
}


void func_15008230(void) {
    D_800C35C4 = (u8)0;
    D_800C3C88 = (u8)0;
}

void func_15008248(s32 arg0) {
    s32 i;

    D_800C3638 = 0;
    D_800C3671 = 0;
    D_800C3670 = 0;
    func_1501D044(0);
    func_1501D044(1);
    D_800C3663 = 0;

    for (i = 0; i < 3; i++)
    {
        D_800C3CA0[i].unk0 = 0;
        D_800C3CA0[i].unkC = 0;
    }

    D_800C3681 = 0;
    D_800C3682 = 0;
    D_800C3683 = 0;
}

void func_150082CC(void) {
    s32 tmp = D_800C35C4 - 1;

    if (D_800C35C4 != 0) {
        if (D_800C35C5 == 0) {
            D_800C35EA = 2;
        }
        D_800C35C4 = 0;
        func_1501D348(D_800BE9F0, tmp, 0, D_800C3C90, D_800C3C94);
    }
}
