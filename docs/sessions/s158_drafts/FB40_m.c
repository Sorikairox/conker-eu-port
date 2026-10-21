void *func_151D2F00(void *arg0, s32 arg1, u8 arg2, s32 arg3);
void func_151D2AB0(s32);
struct225 *func_1519078C(s32 arg0, u8 *arg1, u8 arg2, s16 arg3, u8 arg4, s32 arg5);
s32 func_1518E808(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

typedef struct {
    s32 w[0x14];
} BlkFB40;

typedef struct {
    f32 unk0;
    BlkFB40 blk;
    s32 padAC;
    s8 unkB0;
    s8 unkB1;
    u8 unkB2;
    s32 unkB4;
} DataFB40;

typedef struct {
    u8 *obj;
    u8 id;
    s16 time;
    u8 flag;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
} HeadFB40;

s32 func_1518FB40(s32 arg0, u8 *arg1, s16 arg2, s8 arg3, s8 arg4, s8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    HeadFB40 head;
    DataFB40 data;
    u8 *temp_v0;
    DataFB40 *d;
    s32 flag;
    u8 flag;

    data.unk0 = 0.0f;
    data.blk = *(BlkFB40 *)arg1;
    data.unkB0 = arg3;
    data.unkB1 = arg4;
    data.unkB2 = arg6;
    head.obj = (u8 *)arg0;
    head.id = ((u8 *)arg0)[0x3B];
    if (arg2 == -1) {
        head.time = 300;
    } else {
        head.time = arg2;
    }
    flag = 1;
    if (arg2 == -1) {
        flag = 0;
    }
    head.flag = flag;
    head.unk9 = 0;
    head.unkA = 0;
    head.unkB = 0;
    head.unkC = 0;
    head.unkD = 1;
    temp_v0 = func_151D2F00(&head, arg7 + 0x60, arg8, arg9);
    if (temp_v0 != NULL) {
        d = (DataFB40 *)(temp_v0 + 0x30);
        memcpy(d, &data, 0x5C);
        if (arg5 != -1) {
            *(struct225 **)((u8 *)d + 0x54) = func_1519078C((s32)temp_v0, (u8 *)arg0, arg5, arg2, arg8, arg9);
        } else {
            *(struct225 **)((u8 *)d + 0x54) = NULL;
        }
        func_151D2AB0(*(s32 *)((u8 *)d + 0x48));
        func_1000FA64(0x4D, *(f32 *)((u8 *)arg0 + 0x14), *(f32 *)((u8 *)arg0 + 0x18), *(f32 *)((u8 *)arg0 + 0x1C), 15000, 2000, 800, (s32)func_1518E808, temp_v0, arg0, 0, 0);
    }
    return (s32)temp_v0;
}
