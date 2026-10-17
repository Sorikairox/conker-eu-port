#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15012FE0(void) {
    D_800BE570 = 0;
    D_800BE574 = 0;
    D_800BE575 = 0;
}

typedef struct {
    u8 pad0[0x15];
    u8 unk15;
    u8 pad16[0x1E];
} struct_eu_40490_obj; // size 0x34

extern void (*D_800831C0[])();

#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013000.s")
// NON-MATCHING: global stores/loads scheduled differently, regalloc
// void func_15013000(void) {
//     u32 i;
//     void (*func)();
//     struct_eu_40490_obj *obj;
//
//     D_800DCDC4 = 0;
//     D_800DCD90 = 0.0f;
//     for (i = 0; i < D_800D3094; i++) {
//         obj = &((struct_eu_40490_obj *)D_800D34B8)[i];
//         func = D_800831C0[(u8)(obj->unk15 >> 2)];
//         if (func != NULL) {
//             func(obj, func);
//         }
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150130B4.s")

s32 func_1501370C(struct16 *arg0) {
    u8 idx = arg0->unk17;
    void (*func)(void) = D_80082EA0[idx];

    if (func != NULL) {
        func();
    }
    return 1;
}

s32 func_1501374C(struct16 *arg0) {
    arg0->unk16 |= 4;
    func_1515D088(arg0);
    return 1;
}

// fat struct definition:
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013778.s")

s32 func_1501396C(struct16 *arg0) {
    u8 idx = arg0->unk17;
    void (*func)(void) = D_80082ECC[idx];

    if (func != NULL) {
        func();
    }
    return 1;
}

// another struct
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u8 unk34;
    u8 pad35[3];
} Ent150139AC;
extern Ent150139AC D_80096350[];
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    s32 unk18;
} Obj150139AC;
extern f32 D_800969F8;
extern f32 D_800969FC;

s32 func_150139AC(Obj150139AC *arg0) {
    struct {
        Obj150139AC *unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        s16 unk24;
        s16 unk26;
        f32 unk28;
        f32 unk2C;
        f32 unk30;
        f32 unk34;
        f32 unk38;
        f32 unk3C;
        u8 unk40;
        u8 unk41;
        u8 unk42;
        u8 pad43;
        s16 unk44;
        u8 pad46[2];
        f32 unk48;
        u8 pad4C[0x14];
        s32 unk60;
        u8 unk64;
        u8 unk65;
        u8 pad66[2];
        s32 unk68;
        s32 unk6C;
    } tmp;
    Ent150139AC *e;
    s32 idx;

    arg0->unk16 |= 4;
    idx = arg0->unk18;
    tmp.unk0 = arg0;
    tmp.unkC = 0.0f;
    switch (arg0->unk15 & 3) {
    case 2:
        tmp.unk4 = arg0->unk6 * arg0->unkA * 4.0f;
        tmp.unk10 = arg0->unk2 + arg0->unk8;
        break;
    case 0:
    case 1:
        tmp.unk4 = arg0->unk6 * arg0->unk6 * D_800969F8;
        tmp.unk10 = arg0->unk2 + arg0->unk8;
        break;
    default:
        tmp.unk4 = 1.0f;
        tmp.unk10 = 1000.0f;
        break;
    }
    e = &D_80096350[idx];
    tmp.unk14 = e->unk4;
    tmp.unk18 = e->unk8;
    tmp.unk1C = e->unkC;
    tmp.unk20 = e->unk10;
    tmp.unk24 = e->unk14;
    tmp.unk26 = e->unk16;
    tmp.unk28 = e->unk18;
    tmp.unk2C = e->unk1C;
    tmp.unk30 = e->unk20;
    tmp.unk34 = e->unk24;
    tmp.unk38 = e->unk28;
    tmp.unk3C = e->unk2C;
    tmp.unk8 = e->unk0;
    tmp.unk40 = e->unk30;
    tmp.unk41 = e->unk31;
    tmp.unk42 = e->unk32;
    tmp.unk48 = D_800969FC;
    tmp.unk60 = 0;
    tmp.unk64 = 0;
    tmp.unk65 = 0;
    tmp.unk68 = 0;
    if (e->unk34) {
        func_1510F800(0);
        tmp.unk6C = func_1510FD20(arg0->unk0, arg0->unk4);
    } else {
        tmp.unk6C = 0;
    }
    if (e->unk33) {
        tmp.unk44 = func_1000FA64(0x4D, arg0->unk0, arg0->unk2, arg0->unk4, 0x5DC0, 0x3E8, 0x12C, 0, 0, 0, 0, 0);
    } else {
        tmp.unk44 = 0;
    }
    e = (Ent150139AC *)func_151491F4(300, -1, 6, 0, 10, 0x70, 0xFF, 0);
    if (e != NULL) {
        memcpy((u8 *)e + 0x28, &tmp, sizeof(tmp));
    }
    return 1;
}

extern void (*D_800832B8[])(struct134 *, f32);

s32 func_15013C38(struct134 *arg0) {
    s32 idx = arg0->unk18;
    void (*func)(struct134 *, f32);

    arg0->unk16 |= 4;
    if ((((u8 *)D_800D2E4C)[0x11] & 4) && (D_800BE9F0 == 19)) {
        return 1;
    }
    if ((D_800C35EA == 1) && ((D_800C3A08 == 15) || (D_800C3A08 == 16) || (D_800C3A08 == 17))) {
        return 1;
    }
    if (idx >= 6) {
        return 1;
    }
    func = D_800832B8[idx];
    if (func != NULL) {
        f32 val = (u32)arg0->unk1C * D_80096A00;
        func(arg0, val);
    }
    return 1;
}

s32 func_15013D38(struct134 *arg0) {
    f32 pos[3];
    s32 temp_v0;

    arg0->unk16 |= 4;
    pos[0] = arg0->unk0;
    pos[1] = (s16)arg0->unk2;
    pos[2] = arg0->unk4;
    temp_v0 = arg0->unk18;
    func_151BEE00(pos, arg0->unk10, temp_v0 ? temp_v0 : 1, ((u8 *)arg0)[0x1F], 1, 255, 1);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15013DE8.s")

s32 func_15013F9C(s32 arg0) {
    func_151CD2C0(arg0, 0xFF, 1);
    return 1;
}

s32 func_15013FC4(struct133 *arg0) {
    s32 idx = ((u8 *)arg0)[0x1B];
    void (*func)(void) = D_80082F40[idx];

    if (func != NULL) {
        func();
    }
    return 1;
}

s32 func_15014004(struct134 *arg0) {
    s32 temp_v1 = arg0->unk1C;
    if (temp_v1 < 0) {
        return 1;
    }
    if (temp_v1 >= 6) {
        return 1;
    }
    D_800E0900[temp_v1] = arg0;
    return 1;
}

s32 func_15014040(struct134 *arg0) {
    s32 temp_v0 = arg0->unk18;
    arg0->unk16 |= 4;
    if (temp_v0 == 0) {
        D_800D9A20 = arg0;
    } else if (temp_v0 == 1) {
        D_800D9A24 = arg0;
    }
    return 1;
}

s32 func_1501407C(s32 arg0) {
    D_800D987C = (u8)0;
    return 1;
}

s32 func_15014094(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        f32 unk8;
        s32 unkC;
        u8  pad10[0x1C];
        s8  unk2C;
        u8  pad2D[0x7];
    } tmp;
    struct37 *temp_v0;

    arg0->unk16 |= 4;
    tmp.unk0 = arg0;
    tmp.unk4 = func_15144598(arg0);
    tmp.unk8 = 0.0f;
    func_1510F800(0);
    tmp.unkC = func_1510FD20(arg0->unk0, arg0->unk4);
    tmp.unk2C = 0;
    temp_v0 = func_15149130(300, -1, 33, -1, 0, 0, 52, 255, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, sizeof(tmp));
    }
}

s32 func_15014144(struct134 *arg0) {
    s32 flags = arg0->unk18;
    s32 f8 = (flags & 8) ? 8 : 0;
    s32 f4 = (flags & 4) ? 4 : 0;
    s32 f2 = (flags & 2) ? 0 : 2;
    s32 f1 = (flags & 1) ? 1 : 0;
    s32 f10 = (flags & 0x10) ? 0x10 : 0;

    func_151A9940(f10 | f1 | f2 | f4 | f8, ((u8 *)arg0)[0x1F], arg0, 0, D_80096A2C, 100.0f, -1, 255, 1);
    return 1;
}

s32 func_15014220(struct134 *arg0) {
    struct {
        f32 unk0;
        struct134 *unk4;
        s8 unk8;
    } tmp;
    struct37 *temp_v0;

    arg0->unk16 |= 4;
    tmp.unk8 = 1;
    tmp.unk4 = arg0;
    tmp.unk0 = 0.0f;
    temp_v0 = func_15149130(300, -1, 38, -1, 0, 36, 12, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 12);
    }
    return 1;
}
s32 func_150142AC(struct134 *arg0) {
    s32 idx = ((u8 *)arg0)[0x1B];
    arg0->unk16 |= 4;
    if (idx < 0 || idx >= 3) {
        return 1;
    }
    D_800D9AA0[idx] = arg0;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150142EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150144B8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_1501474C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15014B60.s")
s32 func_15014F6C(struct134 *arg0) {
    struct {
        struct134 *unk0;
        u32 unk4;
        u32 unk8;
        u32 unkC;
        u8  unk10[0x30];
        f32 unk40;
        f32 unk44;
        f32 unk48;
        u8  pad4C[0x4];
        s8  unk50;
        s8  unk51;
    } tmp;
    struct37 *temp_v0;
    s8 flag = 0;

    arg0->unk16 |= 4;
    tmp.unk51 = arg0->unk20;
    flag = (arg0->unk1C & 1) ? 1 : 0;
    tmp.unk50 = flag;
    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unk18 & 0xFFFF;
    tmp.unk8 = ((u32)arg0->unk18 >> 16) & 0xFFFF;
    tmp.unkC = (func_150ADA20() % (tmp.unk8 + 1)) + tmp.unk4;
    func_150A8050((void *)tmp.unk10, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0.0f);
    tmp.unk40 = arg0->unk0;
    tmp.unk44 = (s16)arg0->unk2;
    tmp.unk48 = arg0->unk4;
    temp_v0 = func_15149130(300, -1, 49, -1, 0, 42, 84, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, sizeof(tmp));
    }
    return 1;
}

s32 func_150150A4(void) {
    struct17 *temp_v0 = func_1515F1B0();
    if (temp_v0 == NULL) {
        return 1;
    }

    func_1515F25C(&D_800DCDC4, temp_v0);
    D_800DCD90 += temp_v0->unk8;
    return 1;
}

s32 func_15015104(struct134 *arg0) {
    struct {
        struct134 *unk0;
        s8  unk4;
        s32 unk8;
        s8  unkC;
        s32 unk10;
    } tmp;
    struct37 *temp_v0;
    s32 f1;
    s32 f2;

    *(u8 *)&arg0->unk14 = 1;
    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unk1C;
    func_1510F800(0);
    tmp.unk8 = func_1510FD20(arg0->unk0, arg0->unk4);
    f1 = arg0->unk20 ? 1 : 0;
    f2 = arg0->unk20 ? 2 : 0;
    tmp.unkC = f2 | f1;
    tmp.unk10 = 0;
    temp_v0 = func_15149130(300, -1, -1, -1, 0, 44, 20, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, sizeof(tmp));
    }
    return 1;
}
s32 func_150151D4(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        s16 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        u8  pad24[0x14];
        s32 unk38;
        s8  unk3C;
        s8  unk3D;
        s32 unk40;
        s32 unk44;
    } tmp;
    struct37 *temp_v0;

    arg0->unk16 |= 4;
    *(u8 *)&arg0->unk14 = 1;
    tmp.unk0 = arg0;
    tmp.unk8 = -1;
    tmp.unk4 = 0.0f;
    tmp.unkC = arg0->unk0;
    tmp.unk10 = (s16)arg0->unk2;
    tmp.unk14 = arg0->unk4;
    tmp.unk18 = (s16)arg0->unk6;
    tmp.unk1C = (s16)arg0->unk8;
    tmp.unk40 = 0;
    tmp.unk3D = 0;
    tmp.unk3C = 0;
    tmp.unk38 = 0;
    tmp.unk20 = D_80096A64;
    func_1510F800(0);
    tmp.unk44 = func_1510FD20(arg0->unk0, arg0->unk4);
    temp_v0 = func_15149130(300, -1, 60, -1, 0, 45, 72, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, sizeof(tmp));
    }
    return 1;
}

s32 func_15015300(struct134 *arg0) {
    void (*func)(void);
    s32 idx = arg0->unk1C;

    if ((idx < 0) || (idx >= 2)) {
        return 1;
    }

    func = D_80082F70[idx];
    if (func != NULL) {
        func();
    }

    return 1;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_15015354.s")
s32 func_15015644(struct134 *arg0) {
    struct {
        struct134 *unk0;
        f32 unk4;
        s32 unk8;
        s8 unkC;
    } tmp;
    struct37 *temp_v0;

    arg0->unk16 |= 4;
    *(u8 *)&arg0->unk14 = 1;
    tmp.unk0 = arg0;
    tmp.unk4 = func_15144598(arg0);
    func_1510F800(0);
    tmp.unk8 = func_1510FD20(arg0->unk0, arg0->unk4);
    tmp.unkC = 0;
    temp_v0 = func_15149130(300, -1, 68, -1, 0, 47, 16, 255, 0);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &tmp, 16);
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150156F4.s")
