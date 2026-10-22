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
