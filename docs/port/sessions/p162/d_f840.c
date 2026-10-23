void func_15100248(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_151D56F8(u8 *arg0);
void func_151D44C4(u8 *arg0, u8 arg1, s32 arg2);
s32 func_151030B8(u8 *, u8, f32 *, f32 *, f32 *, s32, s32, f32, f32 *, s32, s32, s32, s32, s32);
void func_15100304(f32 *pos, f32 *dir, u8 flag, s32 arg3);
void func_151000EC(u8 *arg0, s32 arg1, struct127 *arg2, s32 arg3);
s32 func_15081A90(struct127 *, f32, f32, f32, f32, f32, f32, u8 *, f32, s32, s32, s32, s32, s32, s32);
void func_15082278(u8 *obj, u8 *hit, s32 arg2);
void func_151001BC(u8 *arg0);
extern s32 D_800A2500;      /* f32[3] spray point (rodata; s32 as in func_1510015C below) */
extern f32 D_800A250C[9];

// gun_fire_effects: muzzle effects of obj's weapon: muzzle point / direction from func_15100248; with a visible
// model a flash, a spark spray (func_151030B8) and the shot effect (func_15100304); if `trail` three trail puffs
// along the direction (0.088 / 0.383 / 0.81); if `ray` a 2000-unit ray cast whose hit record (obj + 0x31C's block
// + 0xB0, or a local one) is applied (func_15082278); finally the shell drop (func_151001BC)
void func_150FF840(u8 *obj, u8 trail, u8 ray, u8 flag, s32 arg4) {
    f32 pos[3];
    f32 dir[3];
    f32 v104[3];
    f32 vF8[3];
    f32 speed[2];
    f32 puff[3][3];
    u8 local_hit[0x48];
    u8 *hit;
    s32 r1;
    s32 r2;
    s32 i;

    func_15100248((s32)obj, (s32)pos, (s32)dir, (s32)v104, (s32)vF8);
    func_151D56F8(obj);
    if (*(void **)(obj + 0x1D4) != NULL && (obj[0x74] & 0xF) != 0xF) {
        func_151D44C4((u8 *)pos, flag, arg4);
        speed[1] = (func_150ADA68() * 3400.0f + 4800.0f) * 0.001f;
        speed[0] = (func_150ADA68() * 220.0f + 320.0f) * 0.1f;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_151030B8(obj, D_80088BB0, (f32 *)&D_800A2500, D_800A250C, speed, (u32)r1 % 3 + 4, (r2 & 0x7F) + 0x80,
                      func_150ADA68() * 450.0f + 780.0f, pos, 0xFF, 0, -1, flag, arg4);
        func_15100304(pos, dir, flag, arg4);
    }
    if (trail) {
        for (i = 0; i < 3; i++) {
            f32 k = (i == 0) ? 0.088000007f : (i == 1) ? 0.383000016f : 0.810000062f;

            puff[i][0] = dir[0] * k + pos[0];
            puff[i][1] = dir[1] * k + pos[1];
            puff[i][2] = dir[2] * k + pos[2];
        }
        func_151000EC((u8 *)puff[0], (s32)pos, (struct127 *)obj, 0x32);
        func_151000EC((u8 *)puff[1], (s32)pos, (struct127 *)obj, 0x30);
        func_151000EC((u8 *)puff[2], (s32)pos, (struct127 *)obj, 0x31);
    }
    if (ray) {
        hit = (*(u8 **)(obj + 0x31C) != NULL) ? *(u8 **)(obj + 0x31C) + 0xB0 : local_hit;
        func_15081A90((struct127 *)obj, pos[0], pos[1], pos[2], dir[0] * 0.001f, dir[1] * 0.001f, dir[2] * 0.001f,
                      hit, 2000.0f, 0, 0, 0, -1, 0, 0);
        func_15082278(obj, hit, 0x10);
    }
    func_151001BC(obj);
}
