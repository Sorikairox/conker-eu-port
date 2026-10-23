// Apply the pending per-player requests queued in D_800D9F18 (x == -1.0f: none) through func_1510BB78,
// with the player's camera record (D_800BE628, 0x180 bytes each).
extern struct PendingF2 D_800D9F18[];
extern u8 D_800D9F38;
void func_1510BB78(s32 arg0, u16 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);

void func_1510BA9C(void) {
    s32 i;
    u8 *cam;

    for (i = 0; i <= D_80082FA0; i++) {
        if (D_800D9F18[i].x != -1.0f) {
            cam = (u8 *)D_800BE628 + i * 0x180;
            func_1510BB78(i, (u16 *)(cam + 0xB8), *(f32 *)(cam + 0x78), *(f32 *)(cam + 0x74), D_800D9F18[i].x,
                          D_800D9F18[i].y, *(f32 *)(cam + 0x84));
            D_800D9F18[i].x = -1.0f;
        }
    }
    D_800D9F38 = 0;
}
