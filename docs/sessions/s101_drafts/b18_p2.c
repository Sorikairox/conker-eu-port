void func_151DC260(void *arg0, void *arg1, u8 arg2, u8 arg3, s32 arg4);
void func_15152700(void *arg0, void *arg1, void *arg2, s32 arg3, f32 arg4, u8 arg5, u8 arg6, s32 arg7);
extern f32 D_80099F88[3][3];
extern u8 D_80099FAC[];
extern u8 D_80099FC4[];

void func_15071B18(s32 arg0) {
    struct17 pos;
    f32 m[9];
    struct {
        s32 u34;
        s32 u38;
        struct17 u3C;
        s16 u48;
        s16 u4A;
        s16 u4C;
        s16 u4E;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        s16 u60;
        s16 u62;
        f32 u64;
        f32 u68;
        f32 u6C;
    } s;

    if ((D_800D154C->unk1D4 != NULL) && ((D_800D154C->unk74 & 0xF) != 0xF)) {
        func_15143134(D_80099F88[func_150ADA20() % 3U], &pos, (u8 *)D_800D154C->unk1D4 + 0x1C0);
        func_1504715C(m, D_800D154C);
        if (func_150ADA20() & 1) {
            if (func_150ADA20() & 1) {
                func_151DC260(&pos, m, 0, 0xFF, 1);
            } else {
                func_151DC484(&pos, m, 0, 0xFF, 1);
            }
        }
        if (func_150ADA20() & 1) {
            s32 blk; // fakematch: unused block-scoped local (s69 basic-block boundary) schedules the 10.0f stores

            s.u34 = 8;
            s.u38 = 5;
            s.u3C = pos;
            s.u48 = 0;
            s.u4A = 0xFF;
            s.u4C = -0x40;
            s.u4E = 0x3C;
            s.u50 = 10.0f;
            s.u54 = 10.0f;
            s.u60 = 0x19;
            s.u62 = 0x14;
            s.u58 = -0.97800004f;
            s.u5C = 0.263f;
            s.u64 = 0.096f;
            s.u68 = 0.07f;
            s.u6C = 21.892f;
            func_15152700(&s, D_80099FAC, D_80099FC4, 6, 25.0f, 0, 0xFF, 1);
        }
    }
}
