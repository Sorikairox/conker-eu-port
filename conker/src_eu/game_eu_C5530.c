#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 func_15083E0C(u8);
struct127 *func_15083E90(u8);
s32 func_15082E44(u8 *e, s32 idx, s32 arg2, s32 arg3, s32 reuse);

/* Object id (0x2000 | n) of script entity `entity` (u8): -1 when it has no record (func_15083E0C), the live object's
 * +0x13F when it exists (func_15083E90), else the record's flag +2 is cleared and the entity is spawned
 * (func_15082E44; -1 when that fails) and looked up again. 0 stays 0. */
s32 func_15097D20(s32 entity, s32 unused) {
    s32 idx;
    struct127 *obj;

    idx = func_15083E0C(entity);
    if (idx != -1) {
        obj = func_15083E90(entity);
        if (obj != NULL) {
            idx = ((u8 *)obj)[0x13F];
        } else {
            ((u8 *)D_800D20FC + idx * 0x30)[2] = 0;
            if (func_15082E44((u8 *)D_800D20FC + idx * 0x30, idx, 0, 0, 0) == 0) {
                return -1;
            }
            idx = func_15083E0C(entity);
        }
    }
    if (idx != 0) {
        idx |= 0x2000;
    }
    return idx;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C5530/func_15097D20.s")
#endif

#ifdef NON_MATCHING
s32 func_15053430(struct127 *);
void func_15060F28(struct127 *arg0, s32 arg1);
extern u8 D_800D2520;
extern s32 D_800D3C60;

/* Removes object `id`: sets flag +2 of its entity record (when id < D_800D2520) and kills it with
 * func_15060F28(obj, 0), or with func_15053430 when called with two words and args[1] != 0. Returns 999999,
 * 0 for a missing object. */
s32 func_15097DDC(s32 id, s32 *args) {
    struct127 *obj;

    obj = func_1505EEF4(id);
    if (obj == NULL) {
        return 0;
    }
    if (id < D_800D2520) {
        ((u8 *)D_800D20FC + id * 0x30)[2] = 1;
    }
    if (D_800D3C60 == 2 && args[1] != 0) {
        func_15053430(obj);
    } else {
        func_15060F28(obj, 0);
    }
    return 999999;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C5530/func_15097DDC.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C5530/func_15097E9C.s")

#ifdef NON_MATCHING
/* Object query handler: entry 1 of func_1509BE40's handler table D_80088838 (event ids 0x2xxx), called as
 * handler(id & 0xFFF, cmd, args) with args = D_800D3380 = {id, cmd, x1, x2, ...} (args[2] is the first extra
 * argument; D_800D3C60 = the number of words). `id` names an object (func_1505EEF4). 0xB7 asks func_15083E0C,
 * 0xB0 / 0xB1 test whether the object is missing (0xB1: or of kind 8 / 0x27); every other query returns 0 for a
 * missing object and otherwise a field or a derived value (positions packed as x << 16 | z, distances, angles in
 * degrees, ...). Object ids passed as arguments drop bits 12..15 (& 0xFFFF0FFF). */
s32 func_15083E0C(u8);
s32 func_15084000(s32);
s32 func_15085890(struct127 *);
s32 func_15086218(f32 y);
s32 func_15086508(f32 x, f32 y, f32 z, s32 count, s32 first, u8 *list, void *sel);
void func_150867D4(s32 point, s32 count, s32 first, u8 *list, s8 *sel);
s32 func_1508712C(s32 point, f32 *x, f32 *y, f32 *z);
s32 func_150871B8(s32 id);
f32 func_15087204(f32 x, f32 y, f32 z, f32 dx, f32 dz);
s32 func_150A3674(s32, s32, s32 x, s32 y, s32 z);
u8 *func_15031C4C(struct127 *, s32, s32);
f32 func_15144BC8(f32 angle);
s32 func_150ACEA0(f32, f32, f32, f32, f32, f32, s32, s32, f32 *, f32 *, f32 *, f32 *, s32, s32, f32);
s32 func_151E5DF8(void);
s32 func_151E5E08(void);
extern s32 D_800D3C60;
extern u8 D_800E0FE8[];
extern s8 D_800E0EF0[];
extern u8 D_80087638;
extern u8 D_8008763C;
extern u8 D_800D1CC9;
extern u16 D_800BEB30[];
extern f32 D_8009E80C;

#define A024_U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define A024_S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define A024_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define A024_S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define A024_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define A024_F32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define A024_REC(p) (*(u8 **)((u8 *)(p) + 0x31C))
#define A024_OBJ(arg) func_1505EEF4((arg) & 0xFFFF0FFF)
#define A024_INDEX(p) (((u8 *)(p) - (u8 *)D_800CC2D0) / 0x32C)   /* index in D_800CC2D0 (0x32C each) */
#define A024_POINT(i) (((u8 *)D_800D2778 + (i) * 0x10)[7])
#define A024_DEG (360.0f / 65536.0f)

s32 func_1509A024(s32 id, s32 cmd, s32 *args) {
    struct127 *obj;
    struct127 *other;
    u8 *rec;
    s16 *list;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 d;
    f32 px;
    f32 py;
    f32 pz;
    f32 hit[4];
    s32 r;
    s32 n;
    s32 i;
    s32 best;
    s32 minD;
    s32 maxD;
    s32 ox;
    s32 oz;
    u8 *p;
    u8 found[16];
    s8 count;
    s8 sel;
    u8 none;

    if (cmd == 0xB7) {
        return func_15083E0C(id & 0xFF);
    }
    obj = func_1505EEF4(id);
    if (cmd == 0xB0) {
        return (obj == NULL) ? 1 : 0;
    }
    if (cmd == 0xB1) {
        if (obj == NULL) {
            return 1;
        }
        return (A024_S32(obj, 0) == 8 || A024_S32(obj, 0) == 0x27) ? 1 : 0;
    }
    if (obj == NULL) {
        return 0;
    }

    switch (cmd) {
    case 0x91:
        return A024_U8(obj, 0x232);
    case 0x92:
        return A024_U16(obj, 0x21C);
    case 0x93:
        return obj->health;
    case 0x94:
        return (A024_U8(obj, 0x13D) != 0) ? 1 : 0;
    case 0x95:
        if (A024_U8(obj, 0x13C) == 0) {
            return 0;
        }
        return (A024_U8(obj, 0x13C) == func_15084000(args[2] & 0xFFFF0FFF) + 100) ? 1 : 0;
    case 0x96:
        return (obj->in_water == 1) ? 1 : 0;
    case 0x97:
        return ((s32)obj->x_position << 16) | ((s32)obj->z_position & 0xFFFF);
    case 0x98:
        return (s16)(s32)obj->y_position;
    case 0x99: /* within args[3] of object args[2] (xz) */
        other = A024_OBJ(args[2]);
        dx = obj->x_position - other->x_position;
        dz = obj->z_position - other->z_position;
        return (dx * dx + dz * dz < (f32)(args[3] * args[3])) ? 1 : 0;
    case 0x9A: /* xz distance to object args[2] (32000 when it does not exist) */
        other = A024_OBJ(args[2]);
        if (other == NULL) {
            return 32000;
        }
        dx = obj->x_position - other->x_position;
        dz = obj->z_position - other->z_position;
        return sqrtf(dx * dx + dz * dz);
    case 0x9B: /* xz distance to the point (args[2], args[3]) */
        dz = obj->z_position - (f32)args[3];
        dx = obj->x_position - (f32)args[2];
        return sqrtf(dz * dz + dx * dx);
    case 0x9C: /* heading to object args[2] */
        other = A024_OBJ(args[2]);
        r = func_1505A630(other->x_position - obj->x_position, other->z_position - obj->z_position, 0);
        return (f32)(r + 0x4000) * A024_DEG * 65536.0f;
    case 0x9D: /* heading to the point (args[2], args[3]) */
        r = func_1505A630((f32)args[2] - obj->x_position, (f32)args[3] - obj->z_position, 0);
        return (f32)(u32)((r - 0x4000) & 0xFFFF) * A024_DEG * 65536.0f;
    case 0x9E: /* within args[4] of the point (args[2], args[3]), integer xz */
        ox = (s32)obj->x_position - args[2];
        oz = (s32)obj->z_position - args[3];
        return (ox * ox + oz * oz < args[4] * args[4]) ? 1 : 0;
    case 0x9F:
        return A024_F32(obj, 0x48);
    case 0xA0:
        return A024_U8(obj, 0x223);
    case 0xA1:
        return A024_U8(obj, 0x234);
    case 0xA2:
        return (A024_U8(A024_REC(obj), 0x57) != 0) ? 1 : 0;
    case 0xA3:
        return A024_S32(obj, 0x25C) & 0x40;
    case 0xA4:
        return A024_U16(obj, 0x7A);
    case 0xA5:
        return func_150859AC(id, (s16)args[2]);
    case 0xA6: /* more than 150 below +0x1CC */
        return (150.0f < A024_F32(obj, 0x1CC) - obj->y_position) ? 1 : 0;
    case 0xA7:
        return func_15085890(obj) | 0xD000;
    case 0xA8:
        return (obj->stunned != 0) ? 1 : 0;
    case 0xA9:
        return A024_U8(A024_REC(obj), 0x77);
    case 0xAA:
        return A024_U8(A024_REC(obj), 0x78);
    case 0xAB:
        return A024_U8(A024_REC(obj), 0x79);
    case 0xAC:
        r = func_150A2FCC(A024_INDEX(obj), D_800D3C60 - 2, &args[2]);
        if (r != -1) {
            return r | 0x4000;
        }
        return 0;
    case 0xAD:
        return A024_U8(obj, 0x251);
    case 0xAE:
        return obj->xz_velocity;
    case 0xAF:
        rec = A024_REC(obj);
        if (A024_U8(rec, 0x16) != 0) {
            return 2;
        }
        return (A024_S16(rec, 0x8) != 0) ? 1 : 0;
    case 0xB2:
        return A024_S32(obj, 0x2E4 + args[2] * 4);
    case 0xB3:
        return A024_F32(obj, 0x40) * 65536.0f;
    case 0xB4:
        return A024_U8(obj, 0x10A);
    case 0xB5: /* the object +0x10A refers to (bit 7 set), its +0 */
        n = A024_U8(obj, 0x10A);
        if (n & 0x80) {
            return A024_S32(&D_800CC2D0[n & 0x7F], 0);
        }
        return 0xFFFF;
    case 0xB6: /* read and clear bit 7 of D_800E0FE8[index] */
        p = &D_800E0FE8[A024_INDEX(obj)];
        n = *p;
        *p = n & 0x7F;
        return n;
    case 0xB8:
        return A024_S8(obj, 0x2CA);
    case 0xB9: /* path point args[2] of path +0x13F: x << 16 | z */
        list = (s16 *)D_800D2104[A024_U8(obj, 0x13F)] + args[2] * 4;
        return (list[0] << 16) | (list[2] & 0xFFFF);
    case 0xBA:
        list = (s16 *)D_800D2104[A024_U8(obj, 0x13F)] + args[2] * 4;
        return list[1];
    case 0xBB:
        if (A024_U8(obj, 0x65) == 0) {
            return -1;
        }
        return A024_U8(&D_800CC2D0[A024_U8(obj, 0x65) - 1], 0x13F);
    case 0xBC:
        return A024_U8(obj, 0x13C);
    case 0xBD: /* xz distance to object args[2] */
        other = A024_OBJ(args[2]);
        dx = obj->x_position - other->x_position;
        dz = obj->z_position - other->z_position;
        return sqrtf(dx * dx + dz * dz);
    case 0xBE:
        return A024_F32(obj, 0x20);
    case 0xBF:
        return (f32)(s32)A024_F32(obj, 0x28) * 65536.0f;
    case 0xC0:
        return A024_U8(A024_REC(obj), 0x1B);
    case 0xC1:
        return A024_U8(A024_REC(obj), 0x4E);
    case 0xC2:
        return A024_U8(obj, 0x3B);
    case 0xC3:
        return A024_S32(obj, 0xF4);
    case 0xC4:
        return A024_S32(obj, 0x25C);
    case 0xC5:
        return A024_U8(obj, 0x89);
    case 0xC6: /* func_150859AC(index, 6) for the first D_8008FD8C objects */
        n = A024_INDEX(obj);
        if (n < 0 || n >= D_8008FD8C) {
            return 0;
        }
        return func_150859AC(A024_INDEX(obj), 6);
    case 0xC7:
        if (A024_U8(obj, 0x211) == 0xFF) {
            return 1;
        }
        return A024_S32(obj, 0x25C) & 0x800;
    case 0xC8: /* distance to the point +0x20F (+ +0x216), or to the point +0x211 when that is farther */
        if (A024_U8(obj, 0x20F) == 0xFF || A024_U8(obj, 0x211) == 0xFF) {
            return 0;
        }
        best = -1;
        if (func_1508712C(A024_U8(obj, 0x20F), &px, &py, &pz) != 0) {
            px -= obj->x_position;
            py -= obj->y_position;
            pz -= obj->z_position;
            best = (s32)sqrtf(px * px + py * py + pz * pz) + A024_S16(obj, 0x216);
            if (A024_U8(obj, 0x211) != A024_U8(obj, 0x20F)
                && func_1508712C(A024_U8(obj, 0x211), &px, &py, &pz) != 0) {
                px -= obj->x_position;
                py -= obj->y_position;
                pz -= obj->z_position;
                r = sqrtf(px * px + py * py + pz * pz);
                if (best < r) {
                    return r;
                }
            }
        }
        return best;
    case 0xC9:
        return func_15086218(obj->y_position);
    case 0xCA: /* the point +0x20F, else the nearest one (stored in +0x213) */
        none = 0xFF;
        if (A024_U8(obj, 0x20F) != 0xFF) {
            return A024_POINT(A024_U8(obj, 0x20F));
        }
        D_8008763C = A024_U8(obj, 0x213);
        r = func_15086508(obj->x_position, obj->y_position, obj->z_position, 0, 0, &none, &none);
        A024_U8(obj, 0x213) = r;
        if (r != 0xFF) {
            return A024_POINT(r);
        }
        return 0xFF;
    case 0xCB: /* distance to object args[2] if the ray to it is clear */
        other = A024_OBJ(args[2]);
        if (other == NULL) {
            return 0;
        }
        dx = other->x_position - obj->x_position;
        dy = other->y_position - obj->y_position;
        dz = other->z_position - obj->z_position;
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (func_150ACEA0(obj->x_position, obj->y_position + 100.0f, obj->z_position, dx, dy, dz, 0, 0,
                          &hit[3], &hit[2], &hit[1], &hit[0], 0, 0, 0.0f) == 0) {
            return dist;
        }
        if (dist < hit[0]) {
            if (0.0f < func_15087204(obj->x_position, obj->y_position, obj->z_position, dx, dz)) {
                return 0;
            }
            return dist;
        }
        return 0;
    case 0xCC: /* index of the D_800D34B8 record (0x34 bytes) at the object's position */
        p = (u8 *)func_150A3674(3, 0xB, obj->x_position, obj->y_position, obj->z_position);
        if (p == NULL) {
            return -1;
        }
        return (p - D_800D34B8) / 0x34;
    case 0xCD: /* angle between the heading +0x40 and the direction to object args[2] (args[3] == 1: absolute) */
        other = A024_OBJ(args[2]);
        r = func_1505A630(other->x_position - obj->x_position, other->z_position - obj->z_position, 0);
        dist = A024_F32(obj, 0x40);
        d = func_15144BC8((f32)(r + 0x4000) * A024_DEG);
        d = func_15144BC8(func_15144BC8(dist) - d);
        if (180.0f < d) {
            d += -360.0f;
        }
        if (args[3] == 1 && d < 0.0f) {
            d = -d;
        }
        return d;
    case 0xCE: /* pitch to object args[2] (args[3] == 1: absolute) */
        other = A024_OBJ(args[2]);
        dx = other->x_position - obj->x_position;
        dz = other->z_position - obj->z_position;
        dy = other->y_position - obj->y_position;
        r = func_1505A630(sqrtf(dx * dx + dz * dz), dy, 0);
        d = func_15144BC8((f32)(u32)r * A024_DEG);
        if (180.0f < d) {
            d += -360.0f;
        }
        if (args[3] == 1 && d < 0.0f) {
            d = -d;
        }
        return d;
    case 0xCF: /* nearest of the args[2] points args[3..] */
        sel = 0;
        count = 0;
        for (i = 0; i < args[2]; i++) {
            found[count] = func_150871B8(args[3 + i]);
            if (found[count] != 0xFF) {
                count++;
            }
        }
        best = -1;
        if (count != 0) {
            r = func_15086508(obj->x_position, obj->y_position, obj->z_position, count, sel, found, &sel);
            D_80087638 = 0xFF;
            if ((u8)r != 0xFF) {
                func_150867D4((u8)r, count, sel, found, &sel);
            }
            if (D_80087638 != 0xFF) {
                best = A024_POINT(D_80087638);
            }
        }
        return best;
    case 0xD0: /* xz distance to point args[2] (30000 when there is none) */
        if (func_1508712C(func_150871B8(args[2]), &px, &py, &pz) == 0) {
            return 30000;
        }
        px -= obj->x_position;
        pz -= obj->z_position;
        return sqrtf(px * px + pz * pz);
    case 0xD1: /* read and clear flag 0x100 of +0x22C */
        n = A024_U16(obj, 0x22C);
        A024_U16(obj, 0x22C) = n & ~0x100;
        return n & 0x100;
    case 0xD2:
        n = A024_U16(obj, 0x22C);
        A024_U16(obj, 0x22C) = n & ~0x200;
        return n & 0x200;
    case 0xD3: /* class of the record's kind (+0x75) */
        rec = A024_REC(obj);
        if (rec == NULL) {
            return 0;
        }
        switch (A024_U8(rec, 0x75) & 0x7F) {
        case 0x03:
        case 0x09:
        case 0x15:
            return 2;
        case 0x21:
        case 0x22:
            return 3;
        case 0x14:
        case 0x16:
        case 0x18:
        case 0x23:
        case 0x24:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3F:
        case 0x41:
            return 1;
        }
        return 0;
    case 0xD4:
        rec = A024_REC(obj);
        if (rec == NULL) {
            return 0;
        }
        return A024_U8(rec, 0x78);
    case 0xD5:
        return func_151E5DF8();
    case 0xD6:
        return func_151E5E08();
    case 0xD7:
        return (600.0f < A024_F32(obj, 0x1CC) - obj->y_position && D_8009E80C == A024_F32(obj, 0x118)) ? 1 : 0;
    case 0xD8:
        return obj->in_water;
    case 0xD9:
        return (A024_U8(obj, 0xA9) == 2) ? 1 : 0;
    case 0xDA:
        return A024_F32(obj, 0x180);
    case 0xDB: /* the point +0x20F (args[2] == 1) or +0x211 */
        if (args[2] == 1) {
            if (A024_U8(obj, 0x20F) == 0xFF) {
                return 0xFF;
            }
            return A024_POINT(A024_U8(obj, 0x20F));
        }
        if (A024_U8(obj, 0x211) == 0xFF) {
            return 0xFF;
        }
        return A024_POINT(A024_U8(obj, 0x211));
    case 0xDC:
        if (A024_S8(A024_REC(obj), 0x195) == 0) {
            return 0;
        }
        return A024_S8(A024_REC(obj), 0x196) | 0x80;
    case 0xDD:
        if (A024_REC(obj) == NULL) {
            return 0;
        }
        return A024_S8(A024_REC(obj), 0x23);
    case 0xDE:
        return A024_INDEX(obj);
    case 0xDF:
        if (A024_REC(obj) == NULL) {
            return 0;
        }
        return A024_S8(A024_REC(obj), 0x1AE);
    case 0xE0:
        return A024_F32(obj, 0x150) * 65536.0f;
    case 0xE1:
        return A024_U8(obj, 0x125);
    case 0xE2:
        return A024_U8(A024_REC(obj), 0x7D);
    case 0xE3:
        return D_800D1CC9;
    case 0xE4:
        return D_800D18A8;
    case 0xE5:
        return A024_U8(obj, 0x275);
    case 0xE6: /* read and clear +0x275 (object number + 1): is that object's +4 byte args[2]? */
        n = A024_U8(obj, 0x275);
        if (n == 0) {
            return 0;
        }
        A024_U8(obj, 0x275) = 0;
        return (A024_U8(&D_800CC2D0[n - 1], 4) == args[2]) ? 1 : 0;
    case 0xE7: /* nearest point of path +0x13F to object args[2], squared xz distance in (args[3]^2, args[4]^2) */
        n = A024_U8(obj, 0x13F);
        list = (s16 *)D_800D2104[n];
        i = D_800D2528[n];
        best = -1;
        if (list == NULL || i == 0) {
            return -1;
        }
        other = A024_OBJ(args[2]);
        ox = other->x_position;
        oz = other->z_position;
        maxD = 100000000;
        minD = -1;
        if (D_800D3C60 >= 4) {
            minD = args[3] * args[3];
            if (D_800D3C60 >= 5) {
                maxD = args[4] * args[4];
            }
        }
        for (n = 0; n < i; n++, list += 4) {
            r = (list[2] - oz) * (list[2] - oz) + (list[0] - ox) * (list[0] - ox);
            if (r < maxD && minD < r) {
                best = n;
                maxD = r;
            }
        }
        return best;
    case 0xE8:
        return A024_U16(obj, 0x84);
    case 0xE9:
        return A024_U8(A024_REC(obj), 0x51);
    case 0xEA:
        p = func_15031C4C(obj, args[2], args[3]);
        if (p != NULL) {
            return A024_S32(p, 0x38);
        }
        return 0;
    case 0xEB: /* the object's xz position clamped to the circle (args[2], args[3]) radius args[4] */
        px = (f32)args[2];
        pz = (f32)args[3];
        d = (f32)args[4];
        dx = obj->x_position - px;
        dz = obj->z_position - pz;
        dist = dz * dz + dx * dx;
        if (dist <= d * d) {
            return ((s32)obj->x_position << 16) | ((s32)obj->z_position & 0xFFFF);
        }
        d = d / sqrtf(dist);
        return ((s32)(dx * d + px) << 16) | ((s32)(dz * d + pz) & 0xFFFF);
    case 0xEC:
        return A024_U8(A024_REC(obj), 0x95);
    case 0xED:
        return D_800BEB30[id];
    case 0xEE: /* the point args[2] ahead of the object (heading +0x7A turned 180 degrees): x << 16 | z */
        func_1505A184(A024_U16(obj, 0x7A) + 0x8000, (f32)args[2], 0.0f, &hit[2], &hit[0], &hit[1]);
        return ((s32)((f32)(s16)(s32)obj->x_position + hit[2]) << 16)
             | ((s32)((f32)(s16)(s32)obj->z_position + hit[0]) & 0xFFFF);
    case 0xEF:
        return A024_S32(obj, 0);
    case 0xF0:
        return D_800E0EF0[A024_U8(obj, 0x128)];
    case 0xF1:
        return ((A024_U8(obj, 0x74) & 0xF) == 0xF) ? 1 : 0;
    case 0xF2:
        if (A024_U8(obj, 0x13C) == 0) {
            return 0;
        }
        return A024_U8(&D_800CC2D0[A024_U8(obj, 0x13C)], 0x13F) | 0x2000;
    case 0xF3:
        return (A024_U8(obj, 0xA9) == 2) ? 1 : 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_C5530/func_1509A024.s")
#endif
