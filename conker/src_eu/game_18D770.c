#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// rodata_inject: inside 0x24BFDC
// rodata_inject: inside 0x24C014
// rodata_inject: inside 0x24C04C

s32 func_151149AC(u8);

struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);
struct225 *func_1516037C(Header *src, struct226 *arg1, s32 size, u8 arg3, s32 arg4);
void func_151603FC(struct225 *arg0);
s32  func_15160600(struct225 *arg0);
s32  func_1516065C(struct225 *arg0);
s32  func_15160684(struct225 *arg0);
s32  func_151607A4(struct225 *arg0);
void func_15160954(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, struct225 *arg4);
s32  func_15161238(struct127 *arg0, struct127 *arg1);
struct225 *func_1516127C(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_15161334(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_15161408(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_15161494(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_15161540(s32 arg0, u8 arg1, s32 arg2);
struct225 *func_151615F8(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5);
void func_151616D0(u8 arg0, u8 arg1, s32 arg2);
void func_15161714(struct225 *arg0);
void func_15161740(struct225 *arg0);
void func_1516176C(struct225 *arg0);
void func_15161798(struct225 *arg0);
void func_151617C4(struct225 *arg0);
void func_151617E4(struct225 *arg0);
void func_15161804(struct225 *arg0);
void func_15161860(struct225 *arg0);
void func_151618BC(u16 arg0, s16 arg1, u8 arg2, s32 arg3, f32 *arg4, s16 arg5, s16 arg6);
struct225 *func_151619A0(s32 arg0, s16 arg1, u8 arg2, s32 arg3);
s32  func_15161A68(struct225 *arg0);
struct225 *func_15161E24(struct127 *arg0, u8 arg1, u8 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9);
#ifdef NON_MATCHING
s32 func_15161F2C(struct225 *arg0);
#else
void func_15161F2C(struct225 *arg0);
#endif
struct225 *func_15162034(s32 arg0, u8 arg1, s32 arg2);
void func_15162110(s32 arg0);
struct225 *func_15162740(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, u8 arg6, s32 arg7);
struct225 *func_1516284C(Header *header, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, s32 size, u8 arg8, u8 arg9, s32 argA);
void func_15162EF8(struct239 *arg0);
void func_15162F50(struct239 *arg0);
struct225 *func_15162FAC(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, u8 arg6, s32 arg7);
struct225 *func_15163414(Header *header, f32* arg1, f32* arg2, f32* arg3, s8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE);
struct225 *func_15163604(s32 arg0, u8 arg1, u8 arg2, s16 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
s32  func_15163704(struct225 *arg0);
void func_1516381C(s32 arg0, u8 arg1, u8 arg2, s32 arg3);
struct225 *func_1516387C(s32 arg0, u8 arg1, s8 arg2, s16 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
s32  func_151639D0(struct225 *arg0, s32 arg1, u8 arg2);
void func_15163A18(struct225 *arg0, s32 arg1, u8 arg2);
struct225 *func_15163A60(u8 arg0, u8 arg1, s32 arg2);
s32  func_15163B98(struct230 *arg0);
struct225 *func_15163BE8(s32 arg0, u8 arg1, s32 arg2);
s32  func_15163CD0(struct225 *arg0);
void func_15163CF8(struct227 *arg0, struct225 *arg1);
void func_15163DEC(struct225 *arg0, struct228 *arg1);
s32  func_15163F50(struct225 *arg0, struct225 *arg1);
struct225 *func_15164208(s32 arg0, u8 arg1, u8 arg2, s32 arg3);
s32  func_1516429C(struct237 *arg0);
void func_151643A8(struct225 *arg0, s32 arg1, u8 arg2);
s32  func_151643F8(struct225 *arg0);
void func_1516441C(struct225 *arg0, s32 *arg1);
void func_151644F4(struct242 *arg0, struct17 *arg1, s32 arg2, f32 arg3, f32 arg4);
s32  func_151644A8(struct242 *arg0);

struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA) {
    struct225 *ret;
    struct226 *sp30;

    ret = NULL;
    sp30 = func_1515D5F8(header2->unk0, header2->unk4, header2->unk8, arg2, arg3, arg4, arg5, arg6, arg7, 0);
    if (sp30 != 0) {
        ret = func_1516037C(header, sp30, offset, arg9, argA);
        if (ret != 0) {
            ret->unkE |= 2;
        } else {
            func_1515F10C(sp30);
        }
    }
    return ret;
}

struct225 *func_1516037C(Header *header, struct226 *arg1, s32 offset, u8 arg3, s32 arg4) {
    struct225 *ret = func_15167A68(53, arg4, offset + 24, 1, arg3, 1);
    if (ret == 0) {
        return NULL;
    }
    memcpy(&ret->unkE, header, 6);
    ret->unk14 = arg1;
    return ret;
}

#ifdef NON_MATCHING
// light_effect_update: P234 (port fix). Counts the effect's life down (+0x10, flag 1 of +0xE) and runs its handler
// D_8008B0F0[+0xF] with the effect (the asm keeps a0 = the effect at the jalr; the matched C passed nothing, so the
// port handlers got NULL: Total War null+0x24 writes); a 0 result or an expired life frees it (func_1516972C).
void func_151603FC(struct225 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0->unkE & 1) != 0) {
        arg0->unk10 -= D_800BE9E4;
        if (arg0->unk10 < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (arg0->unkF != -1) && (D_8008B0F0[arg0->unkF](arg0) == 0)) {
        ret = 1;
    }
    if (ret) {
        func_1516972C(arg0);
    }
}
#else
void func_151603FC(struct225 *arg0) {
    s32 pad;
    u8 ret = 0;

    if ((arg0->unkE & 1) != 0) {
        arg0->unk10 -= D_800BE9E4;
        if (arg0->unk10 < 0) {
            ret = 1;
        }
    }
    if ((ret == 0) && (arg0->unkF != -1) && (D_8008B0F0[arg0->unkF]() == 0)) {
        ret = 1;
    }
    if (ret) {
        func_1516972C(arg0);
    }
}
#endif

// requires jump table
extern s32 (*D_8008B4F0[])(struct225 *);

void func_151604A0(struct225 *arg0, u8 *arg1, u8 arg2) {
    s32 pad[2]; // fakematch: frame is 8 bytes larger than the locals need
    struct17 tmp;

    switch (arg2) {
    case 0x17:
    case 0x18:
    case 0x1C:
    case 0x1F:
    case 0x22:
        if (arg1[0] == ((u8 *)arg0)[0x12]) { // fakematch: raw byte index loads arg1[0] first
            switch (arg2) {
            case 0: // fakematch: a low case keeps the table 0-based (sltiu 0x23, no -0x17)
                break;
            case 0x17:
                arg0->unk14->unk9 = 0;
                break;
            case 0x18:
                arg0->unk14->unk9 = 1;
                break;
            case 0x1C:
                tmp.unk0 = arg0->unk14->unkE;
                tmp.unk4 = arg0->unk14->unk10;
                tmp.unk8 = arg0->unk14->unk12;
                func_151618BC(16000, 0, 0, 0, &tmp, 500, 1000);
                break;
            case 0x1F:
                arg0->unkF = 0xB;
                arg0->unk14->unk9 = 0;
                break;
            case 0x22:
                func_1516972C((struct102 *)arg0);
                break;
            }
        }
        break;
    default:
        if (D_8008B4F0[arg0->unk12] != NULL) {
            D_8008B4F0[arg0->unk12](arg0);
        }
        break;
    }
}

s32 func_15160600(struct225 *arg0) {
    arg0->unk14->unk2F = func_151422DC(0, &D_800A6690, 0, 0xFF, 0xFF, &D_800A6698, 575);
    return 1;
}

s32 func_1516065C(struct225 *arg0) {
    func_15163CF8(&arg0->unk18, arg0);
    return 1;
}

s32 func_15160684(struct225 *arg0) {
    func_15163DEC(arg0, &arg0->unk18);
    return 1;
}

s32 func_151606A8(struct225 *arg0) {
    struct227 **pp = &arg0->unk18;
    s32 pad[1];
    f32 mtx[4][4];
    f32 z;
    f32 y;
    f32 x;

    func_150A8050(mtx, (*pp)->unk0, (*pp)->unk4, (*pp)->unk8);
    mtx[3][0] = ((s16 *)*pp)[8];
    mtx[3][1] = ((s16 *)*pp)[9];
    mtx[3][2] = ((s16 *)*pp)[10];
    func_150A7E40(mtx, D_800A6A94.unk0, D_800A6A94.unk4, D_800A6A94.unk8, &x, &y, &z);
    arg0->unk14->unkE = x;
    arg0->unk14->unk10 = y;
    arg0->unk14->unk12 = z;
    return 1;
}

s32 func_151607A4(struct225 *arg0) {
    struct227 *temp_a1 = &arg0->unk18;
    if (arg0->unk28 != 0) {
        if (temp_a1->unkC < 0.0f) {
            temp_a1->unk4 = (temp_a1->unk4 + (temp_a1->unk8 * D_800BE9A4));
            if (temp_a1->unk0 < temp_a1->unk4) {
                temp_a1->unk4 = temp_a1->unk0;
                temp_a1->unk10 -= 1;
                if (temp_a1->unk10 != 0) {
                    func_15160954(&temp_a1->unk4, &temp_a1->unk0, &temp_a1->unk8, &temp_a1->unkC, arg0);
                }
            }
        } else {
            temp_a1->unkC -= D_800BE9A4;
        }
    } else if (func_150ADA68() < 0.0050000004f) {
        temp_a1->unk10 = (func_150ADA20() % 5U) + 1;
        func_15160954(&temp_a1->unk4, &temp_a1->unk0, &temp_a1->unk8, &temp_a1->unkC, arg0);
    }
    arg0->unk14->unk2F = arg0->unk1C;
    return 1;
}

void func_15160954(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, struct225 *arg4) {
    s32 pad0;
    struct17 tmp;
    s32 pad1;

    *arg0 = 0.0f;
    *arg2 = *arg1 / ((func_150ADA68() * 12.0f) + 8.0f);
    *arg3 = (func_150ADA68() * 28.0f) + 1.0f;

    tmp.unk0 = arg4->unk14->unkE;
    tmp.unk4 = arg4->unk14->unk10;
    tmp.unk8 = arg4->unk14->unk12;

    if (arg4->unk2A != 0) {
        func_151618BC(25000, 0, 0, 0, &tmp, 500, 1500);
    }
}

struct225 *func_15160A58(struct127 *arg0, u8 arg1, struct17 *arg2, u8 arg3, s16 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s8 argB, s32 argC, u8 argD, u8 argE, s32 argF) {
    struct225 *temp_v0;
    Header header;
    struct {
        struct127 *unk0;
        u8  unk4;
        u8  unk5;
        struct17 unk8;
        s8  unk14;
        u8  unk15;
    } data;
    Header2 header2;

    if (arg0 == NULL) {
        return NULL;
    }
    header.unk0 = arg3;
    header.unk1 = 5;
    header.unk2 = arg4;
    header.unk4 = 0x10;
    data.unk0 = arg0;
    data.unk4 = arg0->unique_id;
    data.unk5 = arg1;
    data.unk8 = *arg2;
    header2.unk0 = 0;
    header2.unk4 = 0;
    header2.unk8 = 0;
    data.unk14 = argB;
    data.unk15 = argD;
    temp_v0 = func_151602C0(&header, &header2, arg5, arg6, arg7, arg8, 0xFF, 0, argC + 0x18, argE, argF);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &data, sizeof(data));
    }
    return temp_v0;
}

// ??
typedef struct {
    struct127 *unk0;
    u8  unk4;
    u8  unk5;
    struct17 unk8;
    s8  unk14;
    u8  unk15;
} struct_eu_15160B74;

extern u8 (*D_8008B598[])(struct225 *);

typedef struct { f32 x, y, z; } V3_60B74;

u8 func_15160B74(struct225 *arg0) {
    u8 ret;
    u8 *obj;
    u8 *s;

    obj = *(u8 **)((u8 *)arg0 + 0x18);
    ret = 1;
    s = (u8 *)arg0 + 0x18;
    if (*(s32 *)obj == 0) {
        return 0;
    }
    if (s[4] != obj[0x3B]) {
        return 0;
    }
    if (*(u8 **)(obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 0xF) {
        V3_60B74 out;

        func_15143134(s + 8, &out, (s[5] << 6) + *(u8 **)(obj + 0x1D4));
        arg0->unk14->unkE = out.x;
        arg0->unk14->unk10 = out.y;
        arg0->unk14->unk12 = out.z;
    } else {
        arg0->unk14->unkE = *(f32 *)(obj + 0x14);
        arg0->unk14->unk10 = *(f32 *)(obj + 0x18);
        arg0->unk14->unk12 = *(f32 *)(obj + 0x1C);
    }
    if ((s8)s[0x14] != -1) {
        ret = D_8008B598[(s8)s[0x14]](arg0);
    }
    return ret;
}

// another struct definition
struct225 *func_15160CDC(struct127 *arg0, u8 arg1, struct17 *arg2, struct17 *arg3, f32 arg4, u8 arg5, s16 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, u8 argC, u8 argD, u8 argE, s32 argF) {
    struct225 *temp_v0;
    Header header;
    struct {
        struct127 *unk0;
        u8  unk4;
        u8  unk5;
        struct17 unk8;
        struct17 unk14;
        f32 unk20;
        u8  unk24;
        u8  unk25;
    } data;
    Header2 header2;
    s32 f1;
    s32 f2;

    if (arg0 == NULL) {
        return NULL;
    }
    header.unk0 = arg5;
    header.unk1 = 6;
    header.unk2 = arg6;
    header.unk4 = 0x11;
    data.unk0 = arg0;
    data.unk4 = arg0->unique_id;
    data.unk5 = arg1;
    data.unk8 = *arg2;
    data.unk14 = *arg3;
    data.unk20 = arg4;
    f1 = argB ? 1 : 0;
    f2 = argD ? 2 : 0;
    data.unk24 = f2 | f1;
    data.unk25 = argC;
    header2.unk0 = 0;
    header2.unk4 = 0;
    header2.unk8 = 0;
    temp_v0 = func_151602C0(&header, &header2, arg7, arg8, arg9, argA, 0xFF, 0, sizeof(data), argE, argF);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &data, sizeof(data));
    }
    return temp_v0;
}

// similar to func_15160B74
#ifdef NON_MATCHING
void func_15145EA4(f32 **, f32 **, void *, s32);
s32 func_15145128(f32 *, f32 *, f32 *, f32 *);
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
typedef struct {
    struct127 *obj; /* first object hit */
    f32 t;          /* hit distance along the ray (fraction of dir) */
    f32 x, y, z;    /* hit point */
    u8 pad14[0x45];
    u8 hit;         /* +0x59: what was hit (0 = nothing, 1 = world, >= 2 = an object) */
    u8 pad5A[2];
} Ray_60E30;
/* data at +0x18 (func_15160CDC): object, its unique id, attach point, offset (+8), ray end (+0x14), scale (+0x20),
 * flags (+0x24: 1 = cast, 2 = poke kind 0x9E). */

/* light_beam_update: P237. D_8008B0F0 handler for the beam lights of func_15160CDC. Ends the light (0) when its
 * object is gone or was reused (unique id). Without attach matrices (+0x1D4), without flag 1, or for a hidden
 * object (+0x74 & 0xF == 0xF), the light sits at the object position (light +0xE / +0x10 / +0x12) with brightness
 * +0x2F = 0 and +9 = 1. Else the offset and end points go through attach matrix `point` (func_15145EA4), and when
 * the direction between them is not degenerate (func_15145128) a ray is cast from the start along it
 * (func_15081A90): no hit = as above; a hit moves the light to the hit point with brightness
 * clamp(scale * t, 0, 255) and +9 = 0, and with flag 2 a hit object of kind 0x9E gets +0x2E4 = 1. Returns 1. */
s32 func_15160E30(struct225 *arg0) {
    u8 *obj = *(u8 **) ((u8 *) arg0 + 0x18);
    u8 *s = (u8 *) arg0 + 0x18;
    f32 *src[2];
    f32 *dst[2];
    f32 start[3];
    f32 dir[3];
    f32 tmp0, tmp1;
    Ray_60E30 ray;
    f32 f;

    if (*(s32 *) obj == 0) {
        return 0;
    }
    if (s[4] != obj[0x3B]) {
        return 0;
    }
    if (*(u8 **) (obj + 0x1D4) != NULL && (s[0x24] & 1) && (obj[0x74] & 0xF) != 0xF) {
        src[0] = (f32 *) (s + 8);
        src[1] = (f32 *) (s + 0x14);
        dst[0] = start;
        dst[1] = dir;
        func_15145EA4(src, dst, *(u8 **) (obj + 0x1D4) + (s[5] << 6), 2);
        dir[0] = dir[0] - start[0];
        dir[1] = dir[1] - start[1];
        dir[2] = dir[2] - start[2];
        if (func_15145128(dir, dir, &tmp0, &tmp1) != 0) {
            func_15081A90((struct127 *) obj, start[0], start[1], start[2], dir[0], dir[1], dir[2], (u8 *) &ray, 0.0f,
                          0, 0, 1, -1, 0, 0);
            if (ray.hit != 0) {
                if ((s[0x24] & 2) && ray.hit >= 2 && ((u8 *) ray.obj)[4] == 0x9E) {
                    *(s32 *) ((u8 *) ray.obj + 0x2E4) = 1;
                }
                arg0->unk14->unkE = ray.x;
                arg0->unk14->unk10 = ray.y;
                arg0->unk14->unk12 = ray.z;
                f = *(f32 *) (s + 0x20) * ray.t;
                if (255.0f < f) {
                    f = 255.0f;
                }
                if (f < 0.0f) {
                    f = 0.0f;
                }
                arg0->unk14->unk2F = (u32) f;
                arg0->unk14->unk9 = 0;
                return 1;
            }
        }
    }
    arg0->unk14->unkE = *(f32 *) (obj + 0x14);
    arg0->unk14->unk10 = *(f32 *) (obj + 0x18);
    arg0->unk14->unk12 = *(f32 *) (obj + 0x1C);
    arg0->unk14->unk2F = 0;
    arg0->unk14->unk9 = 1;
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_15160E30.s")
#endif

s32 func_15161238(struct127 *arg0, struct127 *arg1) {
    if (arg0->interaction_state == 0) {
        return 0;
    }
    if (arg0->id == 0xFF) {
        return 0;
    }
    if (arg0 == arg1) {
        return 0;
    }
    return 1;
}

struct225 *func_1516127C(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 src[4];

    src[0] = 50.0f;
    src[1] = 40.0f;
    src[2] = func_150ADA68() * 6.2831855f;

    header.unk0 = 0;
    header.unk1 = 1;
    header.unk2 = 300;
    header.unk4 = 5;

    src[3] = 0.1021f;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

struct225 *func_15161334(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 tmp1[8];

    tmp1[1] = 1.0f;
    tmp1[3] = 1.0f;

    header.unk0 = 0;
    header.unk1 = 2;
    header.unk2 = 300;
    header.unk4 = 6;

    tmp1[0] = 20.0f;
    tmp1[2] = 50.0f;
    tmp1[4] = 0.0f;
    tmp1[5] = 10.0f;
    tmp1[6] = 0.2489f;
    tmp1[7] = 127.0f;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp1), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp1, sizeof(tmp1));
    }
    return temp_v0;
}

struct225 *func_15161408(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    s32 tmp;

    tmp = func_151149AC(249); // what does this return?

    header.unk0 = 0;
    header.unk1 = 3;
    header.unk2 = 300;
    header.unk4 = 8;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp), arg1, arg2);

    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

struct225 *func_15161494(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 tmp[4];

    header.unk0 = 0;
    header.unk1 = 1;
    header.unk2 = 300;
    header.unk4 = 5;

    tmp[0] = 127.0f;
    tmp[1] = 100.0f;
    tmp[2] = 0.0f;
    tmp[3] = 0.08f;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

struct225 *func_15161540(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 tmp[4];

    tmp[0] = 28.0f;
    tmp[1] = 27.0f;
    tmp[2] = func_150ADA68() * 6.2831855f;
    tmp[3] = 0.0766f;

    header.unk0 = 0;
    header.unk1 = 1;
    header.unk2 = 300;
    header.unk4 = 5;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

struct225 *func_151615F8(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5) {
    struct225 *temp_v0;
    Header header;
    struct232 tmp1;
    f32 tmp;

    if (arg2 < 0) {
        return 0;
    }
    if (arg2 >= 9) {
        return 0;
    }

    tmp = D_800A66C0[arg2];
    tmp1.unk4 = tmp;
    tmp1.unk8 = 0.0f;
    tmp1.unkC = 0.0f;
    tmp1.unk0 = tmp;
    tmp1.unk10 = 0;
    tmp1.unk12 = arg1;

    header.unk0 = 0;
    header.unk1 = 4;
    header.unk2 = 300;
    header.unk4 = arg3;

    temp_v0 = func_1516037C(&header, arg0, sizeof(tmp1), arg4, arg5);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp1, sizeof(tmp1));
    }
    return temp_v0;
}

void func_151616D0(u8 arg0, u8 arg1, s32 arg2) {
    struct234 tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg2;

    func_1516944C(53, &tmp, arg1);
}

void func_15161714(struct225 *arg0) {
    func_1514EDF0(arg0, arg0->unk18);
    func_151617C4(arg0);
}

void func_15161740(struct225 *arg0) {
    func_1514EDF0(arg0, arg0->unk18);
    func_151617E4(arg0);
}

void func_1516176C(struct225 *arg0) {
    func_1514EDF0(arg0, arg0->unk18);
    func_151617C4(arg0);
}

void func_15161798(struct225 *arg0) {
    func_1514EDF0(arg0, arg0->unk18);
    func_151617E4(arg0);
}

void func_151617C4(struct225 *arg0) {
    func_15169804(arg0);
}

void func_151617E4(struct225 *arg0) {
    func_15169824(arg0);
}

void func_15161804(struct225 *arg0) {
    if ((arg0->unkE & 2) != 0) {
        func_1515F10C(arg0->unk14, arg0);
    }
    D_8008B208[arg0->unk12](arg0);
}

void func_15161860(struct225 *arg0) {
    if ((arg0->unkE & 2) != 0) {
        func_1515F10C(arg0->unk14, arg0);
    }
    D_8008B2B0[arg0->unk12](arg0);
}

typedef struct {
    s32 unk0[10];
} struct_eu_151618BC;

extern struct_eu_151618BC D_800A6AC4;

void func_151618BC(u16 arg0, s16 arg1, u8 arg2, s32 arg3, f32 *arg4, s16 arg5, s16 arg6) {
    struct_eu_151618BC tbl = D_800A6AC4;

    func_10010F88(tbl.unk0[(u32)func_150ADA20() % 10], arg0, arg1, arg2, arg3, arg4[0], arg4[1], arg4[2], arg5, arg6);
}

struct225 *func_151619A0(s32 arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct225 *temp_v0;
    Header header;
    s32 tmp;
    Header2 header2;

    tmp = arg0;

    header.unk0 = 3;
    header.unk1 = 9;
    header.unk2 = arg1;
    header.unk4 = 20;

    header2.unk0 = 0;
    header2.unk4 = 0;
    header2.unk8 = 0;

    temp_v0 = func_151602C0(&header, &header2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, sizeof(tmp), arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

s32 func_15161A68(struct225 *arg0) {
    struct233 **tmp = &D_800C3958; // fakematch?

    if (D_800C35EA == 1) {
        f32 phi_f0;
        f32 phi_f2;
        struct233 *temp_v0 = *tmp + (s32) arg0->unk18;

        arg0->unk14->unkE = temp_v0->unk0;
        arg0->unk14->unk10 = temp_v0->unk4;
        arg0->unk14->unk12 = temp_v0->unk8;

        if (temp_v0->unk24 < 0.0f) {
            phi_f0 = 0.0f;
        } else {
            if (temp_v0->unk24 > 255.0f) {
                phi_f2 = 255.0f;
            } else {
                phi_f2 = temp_v0->unk24;
            }
            phi_f0 = phi_f2;
        }
        temp_v0->unk24 = phi_f0;
        arg0->unk14->unk5 = phi_f0;
        if (temp_v0->unk28 < 0.0f) {
            phi_f0 = 0.0f;
        } else {
            if (temp_v0->unk28 > 255.0f) {
                phi_f2 = 255.0f;
            } else {
                phi_f2 = temp_v0->unk28;
            }
            phi_f0 = phi_f2;
        }
        temp_v0->unk28 = phi_f0;
        arg0->unk14->unk6 = phi_f0;
        if (temp_v0->unk2C < 0.0f) {
            phi_f0 = 0.0f;
        } else {
            if (temp_v0->unk2C > 255.0f) {
                phi_f2 = 255.0f;
            } else {
                phi_f2 = temp_v0->unk2C;
            }
            phi_f0 = phi_f2;
        }
        temp_v0->unk2C = phi_f0;
        arg0->unk14->unk7 = phi_f0;

        if (temp_v0->unk18 < 0.0f) {
            phi_f0 = 0.0f;
        } else {
            if (temp_v0->unk18 > 255.0f) {
                phi_f2 = 255.0f;
            } else {
                phi_f2 = temp_v0->unk18;
            }
            phi_f0 = phi_f2;
        }
        temp_v0->unk18 = phi_f0;
        arg0->unk14->unk2F = phi_f0;

    }
    return 1;
}

struct225 *func_15161E24(struct127 *arg0, u8 arg1, u8 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9) {
    struct225 *temp_v0;
    Header header;
    struct244 tmp;
    Header2 header2;

    if (arg0 == NULL) {
        return 0;
    }

    header.unk0 = arg2;
    header.unk1 = 10;
    header.unk2 = arg3;
    header.unk4 = 21;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0->unique_id;
    tmp.unk5 = arg1;

    header2.unk0 = arg0->x_position;
    header2.unk4 = arg0->y_position;
    header2.unk8 = arg0->z_position;

    temp_v0 = func_151602C0(&header, &header2, arg4, arg5, arg6, arg7, 0xFF, 0, sizeof(tmp), arg8, arg9);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &tmp, sizeof(tmp));
    }
    return temp_v0;
}

#ifdef NON_MATCHING
// handler 10 of D_8008B0F0 (P234): the dispatcher func_151603FC tests the result, which is func_15163F50's v0 left in
// place by the matched void C; s32 here, one signature for wasm
s32 func_15161F2C(struct225 *arg0) {
    return func_15163F50(arg0, &arg0->unk18);
}
#else
void func_15161F2C(struct225 *arg0) {
    func_15163F50(arg0, &arg0->unk18);
}
#endif

extern void (*D_8008B6F8[])(u8 *, u8 *, u8);
void func_15161F4C(u8 *arg0, u8 *arg1, u8 arg2)
{
  u8 *v = arg0 + 0x18;
  if (arg2 == 0)
  {
    s32 blk_t; // fakematch: block-local declaration = basic-block boundary (s69)
    if ((*(s32 *)v == *(s32 *)arg1) || (v[4] == arg1[4])) { func_1516972C((struct102 *)arg0); }
  }
  else if (arg2 == 0x2D)
  {
    if (*(s32 *)arg1 == *(s32 *)v) { *(s32 *)v = *(s32 *)(arg1 + 4); v[4] = arg1[9]; }
    else if (*(s32 *)(arg1 + 4) == *(s32 *)v) { *(s32 *)v = *(s32 *)arg1; v[4] = arg1[8]; }
  }
  if (D_8008B6F8[arg0[0x1D]] != NULL) { D_8008B6F8[arg0[0x1D]](arg0, arg1, arg2); }
}

struct225 *func_15162034(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    Header header;
    f32 src[8];

    header.unk0 = 0;
    header.unk1 = 2;
    header.unk2 = 0x12C;
    header.unk4 = 6;

    src[1] = 15.0f;
    src[0] = 22.0f;

    src[2] = 45.0f;
    src[3] = 1.0f;
    src[4] = 0.0f;
    src[5] = 10.0f;
    src[6] = 0.2489f;
    src[7] = 127.0f;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

void func_15162110(s32 arg0) {
    struct236 *temp_v0;
    f32 src[8];

    src[1] = 15.0f;
    src[2] = 0.0f;
    src[4] = 15.0f;
    src[5] = 0.0f;
    src[6] = 0.0f;
    src[0] = 42.5f;
    src[3] = 37.5f;
    src[7] = 0.0761f;

    temp_v0 = func_15149130(300, -1, 30, -1, 0, 0, sizeof(src), 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk28, &src, sizeof(src));
    }
}

void func_151621B8(u8 *volatile arg0) { // fakematch: volatile gives the arg0 home reload (s101 recipe)
    s32 pad; // fakematch: frame slot
    f32 s;
    f32 *p;

    s = sinf(*(f32 *)(arg0 + 0x40));
    p = (f32 *)(arg0 + 0x28);
    func_1515D4D4((u8)(s * p[3] + p[0]), (u8)(s * p[4] + p[1]), (u8)(s * p[5] + p[2]), 0);
    p[6] = p[7] * D_800BE9A4 + p[6];
    p[6] = func_15144B68(p[6]);
}
// NON-MATCHING: not quite right here
// struct235 *func_151621B8(struct236 *arg0) {
//     struct235 *temp_v0;
//     f32 temp_f0;
//     u8 temp_a0;
//     u8 temp_a1;
//     u8 temp_a2;
//
//     temp_v0 = &arg0->unk28;
//     temp_f0 = sinf(temp_v0->unk18);
//
//     temp_a0 = temp_v0->unk0 + (temp_f0 * temp_v0->unkC);
//     temp_a1 = temp_v0->unk4 + (temp_f0 * temp_v0->unk10);
//     temp_a2 = temp_v0->unk8 + (temp_f0 * temp_v0->unk14);
//
//
//     func_1515D4D4(temp_a0, temp_a1, temp_a2, 0);
//     temp_v0->unk18 += temp_v0->unk1C * D_800BE9A4;
//     temp_v0->unk18 = func_15144B68(temp_v0->unk18);
//
//     return temp_v0;
// }

// help.
struct225 *func_151623F4(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s8 arg4, s16 arg5, u8 arg6, s32 arg7) {
    struct {
        struct17 unk0;
        struct17 unkC;
        f32 unk18;
        f32 unk1C;
    } data;
    Header header;
    struct225 *temp_v0;

    if (arg1 >= 3) {
        return NULL;
    }
    data.unk0 = D_eu_800A6AEC[arg1];
    data.unkC = D_eu_800A6B10[arg1];
    data.unk18 = 0.0f;
    data.unk1C = D_800A6B34[arg1];
    header.unk0 = arg3;
    header.unk1 = arg4;
    header.unk2 = arg5;
    header.unk4 = arg2;
    temp_v0 = func_1516037C(&header, arg0, sizeof(data), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &data, sizeof(data));
    }
    return temp_v0;
}
s32 func_15162510(u8 *arg0) {
    f32 s;
    f32 *p;

    p = (f32 *)(arg0 + 0x18);
    s = sinf(p[6]);
    (*(u8 **)(arg0 + 0x14))[5] = s * p[3] + p[0];
    (*(u8 **)(arg0 + 0x14))[6] = s * p[4] + p[1];
    (*(u8 **)(arg0 + 0x14))[7] = s * p[5] + p[2];
    p[6] = p[7] * D_800BE9A4 + p[6];
    p[6] = func_15144B68(p[6]);
    return 1;
}
// s32 func_15162510(struct237 *arg0) {
//     struct235 *temp_v1;
//     f32 temp_f0;
//
//     temp_f0 = sinf(arg0->unk18.unk18);
//     temp_v1 = &arg0->unk18;
//
//     arg0->unk14->unk5 = temp_v1->unk0 + (temp_f0 * arg0->unk0[2]);
//     arg0->unk14->unk6 = temp_v1->unk4 + (temp_f0 * temp_v1->unk10);
//     arg0->unk14->unk7 = temp_v1->unk8 + (temp_f0 * temp_v1->unk14);
//
//     temp_v1->unk18 += temp_v1->unk1C * D_800BE9A4;
//     temp_v1->unk18 = func_15144B68(temp_v1->unk18);
//     return 1;
// }

struct225 *func_15162740(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    f32 src[8];

    if (arg1 >= 24) {
        return 0;
    }

    src[0] = D_800A67C0[arg1];
    src[1] = D_800A6760[arg1];
    src[2] = D_800A6820[arg1];
    src[3] = 1.0f;
    src[4] = 0.0f;
    src[5] = 10.0f;
    src[6] = 0.2489f;
    src[7] = 127.0f;

    header.unk0 = arg3;
    header.unk1 = arg5;
    header.unk2 = arg4;
    header.unk4 = arg2;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

struct225 *func_1516284C(Header *header, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, s32 offset, u8 arg8, u8 arg9, s32 argA) {
    struct225 *temp_v0;
    f32 src[8];

    if (arg8 >= 0x18) {
        return 0;
    }

    src[0] = D_800A67C0[arg8];
    src[1] = D_800A6760[arg8];
    src[2] = D_800A6820[arg8];
    src[3] = 1.0f;
    src[4] = 0.0f;
    src[5] = 10.0f;
    src[6] = 0.2489f;
    src[7] = 127.0f;
    temp_v0 = func_151602C0(header, arg1, 0, arg2, arg3, arg4, arg5, arg6, offset + sizeof(src), arg9, argA);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

#ifdef NON_MATCHING
/* six 5-entry tables (rodata 0x800A6C60..0x800A6CD7), indexed by arg1 & 0xFF < 5 */
static const f32 D_800A6C60[5] = { 0.0f, 50.0f, 50.0f, 50.0f, 50.0f };
static const f32 D_800A6C74[5] = { 0.0f, 15.0f, 15.0f, 15.0f, 15.0f };
static const f32 D_800A6C88[5] = { 0.0f, 0.0f, 15.5f, 31.0f, 46.5f };
static const f32 D_800A6C9C[5] = { 10.0f, 12.0f, 12.0f, 12.0f, 12.0f };
static const f32 D_800A6CB0[5] = { 10.0f, 25.0f, 25.0f, 25.0f, 25.0f };
static const f32 D_800A6CC4[5] = { 10.0f, 0.0f, 0.0f, 0.0f, 0.0f };

struct225 *func_1516295C(struct226 *arg0, s32 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, s8 arg6, s8 arg7, s8 arg8, s8 arg9, s32 argA, u8 argB, s32 argC) {
    struct {
        f32 u30;
        f32 u34;
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        s8 u54;
        s8 u55;
        s8 u56;
        s8 u57;
        s8 u58;
        u8 pad59[0x3];
        u8 u5C;
        s8 u5D;
        s16 u5E;
        u8 u60;
        u8 pad61[0x3];
        struct225 * u64;
    } sp;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f2;
    s32 temp_t6;
    struct225 *temp_v0;
    struct225 *var_v1;

    temp_t6 = arg1 & 0xFF;
    if (temp_t6 >= 5) {
        return NULL;
    }
    temp_f2 = D_800A6C60[temp_t6];
    temp_f12 = D_800A6C74[temp_t6];
    temp_f0 = D_800A6C9C[temp_t6];
    temp_f18 = D_800A6CB0[temp_t6];
    temp_f14 = temp_f18 + temp_f0;
    sp.u38 = temp_f2 - temp_f12;
    sp.u3C = D_800A6C88[temp_t6];
    temp_f16 = D_800A6CC4[temp_t6] + temp_f14;
    sp.u55 = arg6;
    sp.u44 = temp_f14;
    sp.u48 = temp_f16;
    sp.u4C = temp_f18 + temp_f16;
    sp.u30 = temp_f2;
    sp.u34 = temp_f12;
    sp.u40 = temp_f0;
    sp.u56 = arg7;
    sp.u57 = arg8;
    sp.u58 = arg9;
    if (sp.u3C < temp_f0) {
        sp.u54 = 0;
    } else if (sp.u3C < sp.u44) {
        sp.u54 = 1;
    } else if (sp.u3C < sp.u48) {
        sp.u54 = 2;
    } else if (sp.u3C < sp.u4C) {
        sp.u54 = 3;
    } else {
        sp.u54 = 4;
    }
    sp.u5C = arg3;
    sp.u5D = arg5;
    sp.u5E = arg4;
    sp.u60 = arg2;
    sp.u50 = 1.0f / temp_f18;
    temp_v0 = func_1516037C((Header *) &sp.u5C, arg0, argA + 0x30, argB, argC);
    var_v1 = temp_v0;
    if (temp_v0 != NULL) {
        sp.u64 = temp_v0;
        memcpy(&temp_v0->unk18, &sp.u30, 0x30);
        var_v1 = sp.u64;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_1516295C.s")
#endif
// s32 func_1516295C(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, s8 arg6, s8 arg7, s8 arg8, s8 arg9, s32 argA, u8 argB, s32 argC) {
//     struct225 *temp_v0;
//     Header header;
//     struct238 src;
//
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f16;
//     f32 temp_f18;
//     f32 temp_f2;
//     f32 temp_f8;
//
//     if (arg1 >= 5) {
//         return 0;
//     }
//
//     temp_f2 = D_800A6880[arg1];
//     temp_f12 = D_800A6894[arg1];
//     temp_f8 = D_800A68A8[arg1];
//     temp_f0 = D_800A68BC[arg1];
//     temp_f18 = D_800A68D0[arg1];
//     temp_f16 = D_800A68E4[arg1] ;
//
//     src.unk0 = temp_f2; // sp30
//     src.unk4 = temp_f12;
//     src.unk8 = temp_f2 - temp_f12;
//     src.unkC = temp_f8;
//     src.unk10 = temp_f0;
//     src.unk14 = temp_f18 + temp_f0;
//     src.unk18 = temp_f18 + temp_f0 + temp_f16;
//     src.unk1C = temp_f18 + temp_f0 + temp_f16 + temp_f18;
//
//     src.unk25 = arg6;
//     src.unk26 = arg7;
//     src.unk27 = arg8;
//     src.unk28 = arg9;
//
//     if (src.unkC < temp_f0) {
//         src.unk24 = 0;
//     } else if (src.unkC < src.unk14) {
//         src.unk24 = 1;
//     } else if (src.unkC < src.unk18) {
//         src.unk24 = 2;
//     } else if (src.unkC < src.unk1C) {
//         src.unk24 = 3;
//     } else {
//         src.unk24 = 4;
//     }
//
//     header.unk0 = arg3;
//     header.unk1 = arg5;
//     header.unk2 = arg4;
//     header.unk4 = arg2;
//
//     src.unk20 = 1.0f / temp_f18;
//
//     temp_v0 = func_1516037C(&header, arg0, argA + 0x30, argB, argC);
//     if (temp_v0 != NULL) {
//         memcpy(&temp_v0->unk18, &src, 0x30);
//     }
//     return temp_v0;
// }

// a biggun'
#ifdef NON_MATCHING
extern void (*D_8008B704[])(u8 *, s32); // mixed-signature list (P284: see HANDOFF); a1 = the new phase

// envelope_update: drives a byte (+0x14 -> +0x2F, e.g. an alpha) through a looping 4-phase envelope on the timer
// +0x24: before +0x28 the base +0x1C (phase 0); rising to base + range (+0x20) until +0x2C (phase 1, slope +0x38);
// the hold value +0x18 until +0x30 (phase 2); then falling back (phase 3). On a phase change the phase's handler id
// (+0x3D..+0x40, -1 = none) is run from D_8008B704 with (obj, phase). The timer advances by the frame time and wraps at +0x34.
// Returns 1.
s32 func_15162B28(u8 *obj) {
    u8 old;
    f32 t;
    s8 id;

    old = obj[0x3C];
    if (*(f32 *) (obj + 0x24) < *(f32 *) (obj + 0x28)) {
        (*(u8 **) (obj + 0x14))[0x2F] = (u32) *(f32 *) (obj + 0x1C);
        obj[0x3C] = 0;
    } else {
        t = *(f32 *) (obj + 0x24);
        if (t < *(f32 *) (obj + 0x2C)) {
            (*(u8 **) (obj + 0x14))[0x2F] =
                (u32) (*(f32 *) (obj + 0x1C) +
                       *(f32 *) (obj + 0x20) * ((t - *(f32 *) (obj + 0x28)) * *(f32 *) (obj + 0x38)));
            obj[0x3C] = 1;
        } else if (t < *(f32 *) (obj + 0x30)) {
            (*(u8 **) (obj + 0x14))[0x2F] = (u32) *(f32 *) (obj + 0x18);
            obj[0x3C] = 2;
        } else {
            (*(u8 **) (obj + 0x14))[0x2F] =
                (u32) (*(f32 *) (obj + 0x1C) +
                       *(f32 *) (obj + 0x20) * (1.0f - (t - *(f32 *) (obj + 0x30)) * *(f32 *) (obj + 0x38)));
            obj[0x3C] = 3;
        }
    }
    if (obj[0x3C] != old) {
        switch (obj[0x3C]) {
            case 0:
                id = obj[0x3D];
                break;
            case 1:
                id = obj[0x3E];
                break;
            case 2:
                id = obj[0x3F];
                break;
            case 3:
                id = obj[0x40];
                break;
            default:
                id = -1;
                break;
        }
        if (id != -1) {
            D_8008B704[id](obj, obj[0x3C]);
        }
    }
    *(f32 *) (obj + 0x24) += D_800BE9A4;
    while (*(f32 *) (obj + 0x34) < *(f32 *) (obj + 0x24)) {
        *(f32 *) (obj + 0x24) -= *(f32 *) (obj + 0x34);
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_15162B28.s")
#endif

void func_15162EF8(struct239 *arg0) {
    s8 sp1C[9]; // FIXME: what size should this be?
    struct240 *temp_v0;

    temp_v0 = func_151149AC(arg0->unk48);
    if (temp_v0 != NULL) {
        temp_v0->unk7C |= 1;
    }
    sp1C[0] = arg0->unk12 - 21;
    func_151403A8(&sp1C, 36);
}

void func_15162F50(struct239 *arg0) {
    s8 sp1C[9]; // FIXME: what size should this be?
    struct240 *temp_v0;

    temp_v0 = func_151149AC(arg0->unk48);
    if (temp_v0 != NULL) {
        temp_v0->unk7C &= ~1;
    }
    sp1C[0] = arg0->unk12 - 21;
    func_151403A8(&sp1C, 37);
}

struct225 *func_15162FAC(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s16 arg4, s8 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    struct241 src;

    if (arg1 >= 3) {
        return NULL;
    }

    src.unk0 = 0.0f;
    src.unk4 = D_800A68F8[arg1];
    src.unk8 = 0.0f;
    src.unk14 = 0;
    src.unk20 = 0.0f;
    src.unkC = D_800A6904[arg1];
    src.unk10 = D_800A6910[arg1];
    src.unk24 = D_800A6934[arg1];
    src.unk28 = D_800A6940[arg1];
    src.unk2C = D_800A694C[arg1];
    src.unk18 = D_800A691C[arg1];
    src.unk1C = D_800A6928[arg1];
    src.unk30 = D_800A6958[arg1];

    header.unk0 = arg3;
    header.unk1 = arg5;
    header.unk2 = arg4;
    header.unk4 = arg2;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

// big one
#ifdef NON_MATCHING
// lightning_flash_update: weather record handler (table entry at ROM 0x230744; returns 1 = keep). Drives the sky flash
// of the area object +0x14 (skipped when its +0x9 is 1): its +0x2F gets the flash level +0x18, which decays by the
// factor +0x1C once per tick (D_800BE9E4). While a burst is running (+0x2C flashes left) +0x38 counts down by
// D_800BE9A4; at zero a new flash of level rand * +0x48 + +0x44 starts, the next one is due after rand * +0x40 + +0x3C,
// and a flash counter is used up (func_1000E770 is called with two NULL pointers; the asm also computes a thunder
// delay from func_151EFDD0 that EU's two-pointer func_1000E770 never reads). Between bursts +0x20 counts down; at zero
// a burst of rand % (+0x34 + 1) + +0x30 flashes is queued and the next pause is rand * +0x28 + +0x24.
s32 func_1000E770(s32 *arg0, s32 *arg1);
f32 func_150ADA68(void);
int func_151EFDD0(void);

s32 func_151630F4(u8 *rec) {
    u8 *obj = *(u8 **) (rec + 0x14);
    f32 *level = (f32 *) (rec + 0x18);
    u32 n;

    if (obj[9] == 1) {
        return 1;
    }
    obj[0x2F] = (u32) *level;
    for (n = D_800BE9E4; n != 0; n--) {
        *level -= *level * *(f32 *) (rec + 0x1C);
    }
    if (*(s32 *) (rec + 0x2C) > 0) {
        *(f32 *) (rec + 0x38) -= D_800BE9A4;
        if (*(f32 *) (rec + 0x38) < 0.0f) {
            *level = func_150ADA68() * *(f32 *) (rec + 0x48) + *(f32 *) (rec + 0x44);
            *(f32 *) (rec + 0x38) = func_150ADA68() * *(f32 *) (rec + 0x40) + *(f32 *) (rec + 0x3C);
            func_151EFDD0();
            func_1000E770(NULL, NULL);
            *(s32 *) (rec + 0x2C) -= 1;
        }
    } else {
        *(f32 *) (rec + 0x20) -= D_800BE9A4;
        if (*(f32 *) (rec + 0x20) < 0.0f) {
            *(s32 *) (rec + 0x2C) = (u32) func_150ADA20() % (u32) (*(s32 *) (rec + 0x34) + 1) + *(s32 *) (rec + 0x30);
            *(f32 *) (rec + 0x38) = 0.0f;
            *(f32 *) (rec + 0x20) = func_150ADA68() * *(f32 *) (rec + 0x28) + *(f32 *) (rec + 0x24);
        }
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_18D770/func_151630F4.s")
#endif

struct225 *func_15163414(Header *header, f32* arg1, f32* arg2, f32* arg3, s8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    struct225 *temp_v0;
    struct245 data;
    Header2 header2;

    data.unk0 = arg1;
    data.unk4 = arg2;
    data.unk8 = arg3;
    data.unkC = arg4;
    data.unkD = arg5;

    header2.unk0 = *arg1;
    header2.unk4 = *arg2;
    header2.unk8 = *arg3;

    temp_v0 = func_151602C0(header, &header2, arg6, arg7, arg8, arg9, argA, argB, argC + sizeof(data), argD, argE);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &data, sizeof(data));
    }
    return temp_v0;
}

s32 func_15163504(u8 *arg0) {
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0xE) = (s32)**(f32 **)(arg0 + 0x18);
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0x10) = (s32)**(f32 **)(arg0 + 0x1C);
    *(s16 *)(*(u8 **)(arg0 + 0x14) + 0x12) = (s32)**(f32 **)(arg0 + 0x20);
    if (*(s8 *)(arg0 + 0x24) != -1) {
        return D_8008B70C[*(volatile s8 *)(arg0 + 0x24)](); // fakematch: volatile forces the second lb
    }
    return 1;
}
// NON-MATCHING: something is missing..
// s32 func_15163504(struct225 *arg0) {
//     s32 ret = 1;
//     arg0->unk14->unkE = arg0->unk18->unk0;
//     arg0->unk14->unk10 = arg0->unk18->unk4;
//     arg0->unk14->unk12 = arg0->unk18->unk8;
//     if (arg0->unk24 != -1) {
//         ret = D_8008B36C[arg0->unk24]();
//     }
//
//     return ret;
// }

void func_151635A8(u8 *arg0, s32 arg1, u8 arg2)
{
  int new_var;
  new_var = 0x25; // fakematch: constant index in a variable stops the CSE of the table index load
  if (D_8008B710[arg0[new_var]] != 0)
  {
    D_8008B710[arg0[new_var]](arg0, arg1, arg2);
  }
}
// NON-MATCHING: similar issue to func_15163504
// void func_151635A8(struct225 *arg0, s32 arg1, u8 arg2) {
//     s32 (*func)(s32) = D_8008B370[arg0->unk25];
//     if (func != NULL) {
//         func(arg2);
//     }
// }

struct225 *func_15163604(s32 arg0, u8 arg1, u8 arg2, s16 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    f32 src[4];

    if (arg1 < 0) {
        return 0;
    }
    if (arg1 >= 14) {
        return 0;
    }

    src[0] = D_800A6964[arg1];
    src[1] = D_800A699C[arg1];
    src[2] = func_150ADA68() * 6.2831855f;
    src[3] = D_800A69D4[arg1];

    header.unk0 = arg4;
    header.unk1 = 1;
    header.unk2 = arg3;
    header.unk4 = arg2;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

s32 func_15163704(struct225 *arg0) {
    struct227 *temp_v0;
    f32 tmp;
    s32 pad1;

    temp_v0 = &arg0->unk18;
    tmp = sinf(temp_v0->unk8);
    arg0->unk14->unk2F = temp_v0->unk0 + (temp_v0->unk4 * tmp);

    temp_v0->unk8 += temp_v0->unkC * D_800BE9A4;
    temp_v0->unk8 = func_15144B68(temp_v0->unk8);

    if (temp_v0->unk8 > 3.1415927f) {
        return 0;
    }
    return 1;
}

void func_1516381C(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    Header tmp;
    tmp.unk0 = 0;
    tmp.unk1 = -1;
    tmp.unk2 = 300;
    tmp.unk4 = arg1;
    func_1516037C(&tmp, arg0, 0, arg2, arg3);
}

struct225 *func_1516387C(s32 arg0, u8 arg1, s8 arg2, s16 arg3, u8 arg4, s32 offset, u8 arg6, s32 arg7) {
    Header tmp;
    tmp.unk0 = arg1;
    tmp.unk1 = arg2;
    tmp.unk2 = arg3;
    tmp.unk4 = arg4;

    return func_1516037C(&tmp, arg0, offset, arg6, arg7);
}

typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
} struct_eu_151638E0;

s32 func_151638E0(struct225 *arg0) {
    struct_eu_151638E0 *pl = (struct_eu_151638E0 *)&arg0->unk18;
    f32 sp20[3];
    f32 sp1C;

    func_15188530(pl->unk0, sp20);
    func_15188580(pl->unk0, &sp1C);
    arg0->unk14->unk2F = pl->unk4 + (pl->unk8 * sp1C);
    return 1;
}

s32 func_151639D0(struct225 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x27) {
        arg0->unk14->unk9 = 1;
    } else if (arg2 == 0x28) {
        arg0->unk14->unk9 = 0;
    }
}

void func_15163A18(struct225 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x27) {
        arg0->unk14->unk9 = 0;
    } else if (arg2 == 0x28) {
        arg0->unk14->unk9 = 1;
    }
}

struct225 *func_15163A60(u8 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0_2;
    Header header;
    f32 tmp1[4];
    struct226 *temp_v0;
    Header2 header2;

    temp_v0 = func_151149AC(arg0); // maybe different types?
    if (temp_v0 == 0) {
        return 0;
    }
    tmp1[0] = D_800A6964[6]; // D_800A697C
    tmp1[1] = D_800A699C[6]; // D_800A69B4
    tmp1[2] = func_150ADA68() * 6.2831855f;
    tmp1[3] = D_800A69D4[6]; // D_800A69EC;

    header2.unk0 = temp_v0->unk10;
    header2.unk4 = temp_v0->unk12;
    header2.unk8 = temp_v0->unk14;

    header.unk0 = 2;
    header.unk1 = 17;
    header.unk2 = 300;
    header.unk4 = 5;

    temp_v0_2 = func_151602C0(&header, &header2, D_800A6964[6], 0, 0xFF, 0, 0xFF, 0, 20, arg1, arg2);
    if (temp_v0_2 != 0) {
        memcpy(&temp_v0_2->unk18, &tmp1, 16);
        memcpy(&temp_v0_2->unk28, &temp_v0, 4);
    }
    return temp_v0_2;
}

s32 func_15163B98(struct230 *arg0) {
    struct228* tmp;
    if (func_1516065C(arg0) == 0) {
        return 0;
    } else {
        tmp = arg0->unk28;
        if (tmp->unk6E == 1) {
            return 0;
        } else {
            return 1;
        }
    }
}

struct225 *func_15163BE8(s32 arg0, u8 arg1, s32 arg2) {
    struct225 *temp_v0;
    f32 src[4];

    src[0] = D_800A6964[6];
    src[1] = D_800A699C[6];
    src[2] = func_150ADA68() * 6.2831855f;
    src[3] = D_800A69D4[6];

    temp_v0 = func_15160A58(arg0, 1, &D_800A6A0C, 2, 300, 100, 0, 0xFF, 0, 0xFF, 0, 0, sizeof(src), 1, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk30, &src, sizeof(src));
    }
    return temp_v0;
}

s32 func_15163CD0(struct225 *arg0) {
    func_15163CF8(&arg0->unk30, arg0);
    return 1;
}

void func_15163CF8(struct227 *arg0, struct225 *arg1) {
    f32 tmp = sinf(arg0->unk8);
    arg1->unk14->unk2F = arg0->unk0 + (arg0->unk4 * tmp);
    arg0->unk8 = arg0->unk8 + (arg0->unkC * D_800BE9A4);
    arg0->unk8 = func_15144B68(arg0->unk8);
}

void func_15163DEC(struct225 *arg0, struct228 *arg1) {
    arg1->unk10 = arg1->unk10 - D_800BE9A4;
    if (arg1->unk10 < 0.0f) {
        arg1->unk10 = func_150ADA68() * arg1->unk14;
        if ((func_150ADA20() & 3) != 0) {
            arg1->unkC = (func_150ADA68() * (arg1->unk0 - arg1->unk4)) + arg1->unk4;
        } else {
            arg1->unkC = (func_150ADA68() * (arg1->unk8 - arg1->unk0)) + arg1->unk0;
        }
    }
    arg1->unk1C += (arg1->unkC - arg1->unk1C) * arg1->unk18;
    arg0->unk14->unk2F = arg1->unk1C;
}

s32 func_15163F50(struct225 *arg0, struct225 *arg1) {
    struct127 *temp_v1;

    temp_v1 = arg1->unk0;
    if (temp_v1->interaction_state == 0) {
        return 0;
    }
    if (temp_v1->id == 0xFF) {
        return 0;
    }
    if (temp_v1->unique_id != arg1->unk4) {
        return 0;
    }
    arg0->unk14->unkE = temp_v1->x_position;
    arg0->unk14->unk10 = temp_v1->y_position;
    arg0->unk14->unk12 = temp_v1->z_position;
    return 1;
}

// ???
typedef struct {
    s32 unk0;
    u8  unk4;
} struct_eu_18D770_pl;

typedef struct {
    s32 unk0;
    union {
        u8  b;
        s32 w;
    } unk4;
    u8  unk8;
    u8  unk9;
} struct_eu_18D770_msg;

void func_15163FEC(struct225 *arg0, struct_eu_18D770_msg *arg1, u8 arg2) {
    struct_eu_18D770_pl *pl = &arg0->unk18;
    void (*func)(struct225 *, void *, u8);
    s32 id;

    if (arg2 == 0) {
        id = arg1->unk0;
        if (id == pl->unk0 || arg1->unk4.b == pl->unk4) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (pl->unk0 == arg1->unk0) {
            pl->unk0 = arg1->unk4.w;
            pl->unk4 = arg1->unk9;
        } else if (pl->unk0 == arg1->unk4.w) {
            pl->unk0 = arg1->unk0;
            pl->unk4 = arg1->unk8;
        }
        goto dummy_label; dummy_label: ; // fakematch: forces the `b` + target-copied delay slot
    } else {
        func = D_8008B714[arg0->unk2D];
        if (func != NULL) {
            func(arg0, arg1, arg2);
        }
    }
}
// NON-MATCHING: only the tail of the 0x2D case is scheduled differently (target has an extra b)
// void func_15163FEC(struct225 *arg0, struct_eu_18D770_msg *arg1, u8 arg2) {
//     struct_eu_18D770_pl *pl = &arg0->unk18;
//     void (*func)(struct225 *, void *, u8);
//     s32 id;
//     s32 cur;
//
//     if (arg2 == 0) {
//         id = arg1->unk0;
//         if (id == pl->unk0 || arg1->unk4.b == pl->unk4) {
//             func_1516972C(arg0);
//         }
//     } else if (arg2 == 0x2D) {
//         cur = pl->unk0;
//         id = arg1->unk0;
//         if (id == cur) {
//             pl->unk0 = arg1->unk4.w;
//             pl->unk4 = arg1->unk9;
//         } else if (arg1->unk4.w == cur) {
//             pl->unk0 = id;
//             pl->unk4 = arg1->unk8;
//         }
//     } else {
//         func = D_8008B714[arg0->unk2D];
//         if (func != NULL) {
//             func(arg0, arg1, arg2);
//         }
//     }
// }
typedef struct {
    u8 *unk0;
    u8  unk4;
} struct_eu_151640C0;

void func_151640C0(u8 *arg0, u8 *arg1, u8 arg2)
{
  u8 **q = &arg0; // fakematch: shape C home reload
  u8 **r = &arg1; // fakematch: shape C home reload
  u8 *a;
  u8 *v;
  s32 k;
  s32 w;
  u8 b;
  u8 c;
  if (arg2 == 0x29)
  {
    a = *(u8 **)(*r + 4);
    v = *q;
    v = v + 0x18; // fakematch: split add keeps the reload in v0 (permuter)
    k = *(s32 *)a;
    w = *(s32 *)v;
    c = v[4];
    b = a[4];
    if ((w == k) || (c == b) || (b == ((u8 *)w)[0x3B]))
    {
      func_1516972C((struct102 *)*q);
    }
  }
}
// NON-MATCHING: all four values are loaded into a0-a3 before the tests; regalloc
// void func_151640C0(struct225 *arg0, struct_eu_151640C0 **arg1, u8 arg2) {
//     struct_eu_151640C0 *a;
//     u8 *p1;
//     u8 *p0;
//     u8 b1;
//     u8 b0;
//
//     if (arg2 == 0x29) {
//         a = arg1[1];
//         p1 = a->unk0;
//         p0 = ((struct_eu_151640C0 *)&arg0->unk18)->unk0;
//         b1 = a->unk4;
//         b0 = ((struct_eu_151640C0 *)&arg0->unk18)->unk4;
//         if (p0 == p1 || b1 == b0 || b1 == p0[0x3B]) {
//             func_1516972C(arg0);
//         }
//     }
// }

void func_15164134(struct225 *arg0, struct_eu_18D770_msg *arg1, u8 arg2) {
    struct_eu_18D770_pl *pl = &arg0->unk18;
    void (*func)(struct225 *, void *, u8);
    s32 id;

    if (arg2 == 0) {
        id = arg1->unk0;
        if (id == pl->unk0 || arg1->unk4.b == pl->unk4) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (pl->unk0 == arg1->unk0) {
            pl->unk0 = arg1->unk4.w;
            pl->unk4 = arg1->unk9;
        } else if (pl->unk0 == arg1->unk4.w) {
            pl->unk0 = arg1->unk0;
            pl->unk4 = arg1->unk8;
        }
        goto dummy_label; dummy_label: ; // fakematch: forces the `b` + target-copied delay slot
    } else {
        func = D_8008B71C[((u8 *)arg0)[0x3D]];
        if (func != NULL) {
            func(arg0, arg1, arg2);
        }
    }
}

struct225 *func_15164208(s32 arg0, u8 arg1, u8 arg2, s32 arg3) {
    struct225 *temp_v0;
    Header header;
    struct243 src;

    src.unk0 = 0.0f;
    src.unk4 = arg1;

    header.unk0 = 0;
    header.unk1 = 20;
    header.unk2 = 300;
    header.unk4 = 39;

    temp_v0 = func_1516037C(&header, arg0, sizeof(src), arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &src, sizeof(src));
    }
    return temp_v0;
}

s32 func_1516429C(struct237 *arg0) {
    arg0->unk14->unk2F = arg0->unk18.unk0;
    arg0->unk18.unk0 = arg0->unk18.unk0 - (arg0->unk18.unk0 * 0.70000005f);
    return 1;
}

// what structs?
typedef struct {
    f32 unk0;
    u8  unk4;
    u8  unk5;
    u8  unk6;
    u8  unk7;
} struct_eu_1516434C;

void func_1516434C(struct225 *arg0, struct_eu_1516434C *arg1, u8 arg2) {
    struct_eu_1516434C *temp_v0 = (struct_eu_1516434C *)&arg0->unk18;

    if (arg2 == 0x33 && temp_v0->unk4 == arg1->unk4) {
        temp_v0->unk0 = arg1->unk0;
        arg0->unk14->unk5 = arg1->unk5;
        arg0->unk14->unk6 = arg1->unk6;
        arg0->unk14->unk7 = arg1->unk7;
    }
}

void func_151643A8(struct225 *arg0, s32 arg1, u8 arg2) {
    struct227 *tmp;
    tmp = &arg0->unk18;
    if (arg2 == 64) {
        tmp->unk24 |= 1;      // force odd?
    } else if (arg2 == 65) {
        tmp->unk24 &= 0xFFFE; // force even?
    }
}

s32 func_151643F8(struct225 *arg0) {
    func_1516441C(arg0, &arg0->unk18);
    return 1;
}

// ???
void func_1516441C(struct225 *arg0, s32 *arg1) {
    s32 *sp2C;
    f32 *sp28;
    f32 sp1C[3];

    sp2C = arg1;
    sp28 = sp1C;
    func_15145CD0(arg1[3], &sp2C, &sp28, 1);
    arg0->unk14->unkE = sp1C[0];
    arg0->unk14->unk10 = sp1C[1];
    arg0->unk14->unk12 = sp1C[2];
}

s32 func_151644A8(struct242 *arg0) {
    f32 temp_f0;
    struct17 *temp_v0;

    temp_v0 = arg0->unk20;
    temp_f0 = arg0->unk1C;
    func_151644F4(arg0, &arg0->unk24, arg0->unk18, temp_v0->unk0 * temp_f0, temp_v0->unk8 * temp_f0);
    return 1;
}

void func_151644F4(struct242 *arg0, struct17 *arg1, s32 arg2, f32 arg3, f32 arg4) {
    f32 z;
    f32 y;
    f32 x;
    f32 mf[4][4];

    func_150A8050(mf, arg3, 0.0f, arg4);
    mf[3][0] = arg1->unk0;
    mf[3][1] = arg1->unk4;
    mf[3][2] = arg1->unk8;
    func_150A7E40(mf, 0.0f, *(f32 *)&arg2, 0.0f, &x, &y, &z);
    arg0->unk14->unkE = x;
    arg0->unk14->unk10 = y;
    arg0->unk14->unk12 = z;
}
// NON-MATCHING: close...
// void func_151644F4(struct242 *arg0, struct17 *arg1, s32 arg2, f32 arg3, f32 arg4) {
//     f32 tmp1;
//     f32 tmp2;
//     f32 tmp3;
//
//     f32 tmp[16];
//
//     func_150A8050(&tmp, arg3, 0.0f, arg4);
//
//     tmp[13] = arg1->unk0;
//     tmp[14] = arg1->unk4;
//     tmp[15] = arg1->unk8;
//     func_150A7960(&tmp, NULL, arg0, NULL, &tmp1, &tmp2, &tmp3);
//
//     arg0->unk14->unkE =  tmp1;
//     arg0->unk14->unk10 = tmp2;
//     arg0->unk14->unk12 = tmp3;
// }

// loop
extern u8 D_80088A90[];
extern u8 D_80088A94[];
extern u8 D_80088A98[];
void func_15111CAC(s32);
void func_1515F170(s32, s32);

void func_151645C4(u8 arg0) {
    D_800DCDD0 = arg0;
    if (arg0) {
        switch (D_800BE9F0) {
        case 0xB:
            func_15111CAC(4);
            break;
        case 0x6:
            func_1515F170(0xA, 1);
            func_15111CAC(4);
        case 0x39:
            ((u8 *)&D_800DCD20)[0] = D_80088A90[0];
            ((u8 *)&D_800DCD20)[1] = D_80088A90[1];
            ((u8 *)&D_800DCD20)[2] = D_80088A90[2];
            D_800B0DF0->unk5 = D_80088A94[0];
            D_800B0DF0->unk6 = D_80088A94[1];
            D_800B0DF0->unk7 = D_80088A94[2];
            break;
        case 0x7:
        case 0xC:
            break;
        }
    } else {
        switch (D_800BE9F0) {
        case 0x6:
            func_1515F170(0xA, 0);
        case 0x7:
        case 0xC:
        case 0x39:
            func_15111CAC(6);
            ((u8 *)&D_800DCD20)[0] = D_80088A98[0];
            ((u8 *)&D_800DCD20)[1] = D_80088A98[1];
            ((u8 *)&D_800DCD20)[2] = D_80088A98[2];
            D_800B0DF0->unk5 = 0xFF;
            D_800B0DF0->unk6 = 0xFF;
            D_800B0DF0->unk7 = 0xFF;
            break;
        case 0xB:
            func_15111CAC(6);
            break;
        case 0x29:
            func_15111CAC(1);
            break;
        }
    }
}
