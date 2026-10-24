void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB);
u8 *func_151A7F00(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);
u8 *func_150F0448(u8 *obj, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
struct225 *func_150F0718(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);
extern u8 D_800A5860[];
extern s32 D_800A4AA0;

// fire_effect_start: P181: starts the burning effect on object `arg0` (side `arg1` < 2, else nothing): an effect
// record (func_1513D2F0, handlers D_800A4AA0, 0x44 extra bytes at +0x110 holding obj, its index obj +0x3B, the
// effect object func_15083E90(18), kind 18, `arg1`, two random angles 0..2pi), two flame sprites
// (func_151A7F00 with the 0x50-byte flame definition; their +0x60 blocks get obj / index / effect / sprite number)
// stored at +0x12C / +0x130, a light (func_15149130, its +0x28 gets effect / 0.0) at +0x134, a smoke emitter
// (func_150F0448, colour (255, 217, 160)) at +0x138 and func_150F0718(70, 255, 130, 0) at +0x13C; all owned by
// arg2 / arg3. Returns the effect (NULL when none). Bytes +0x1C..+0x2F of the extra block are not set by the
// asm (uninitialised stack copied).
u8 *func_150EF500(struct127 *arg0, u8 arg1, s32 arg2, s32 arg3) {
    u8 *obj = (u8 *)arg0;
    struct {
        u8 *obj;       /* +0x00 */
        u8 index;      /* +0x04 */
        u8 *effObj;    /* +0x08 */
        u8 kind;       /* +0x0C */
        u8 side;       /* +0x0D */
        f32 angA;      /* +0x10 */
        f32 angB;      /* +0x14 */
        u8 u18;        /* +0x18 */
        u8 u19[0x17];
        s32 color[3];  /* +0x30: D_800A5860 */
        f32 u3C;       /* +0x3C */
        f32 u40;       /* +0x40 */
    } pay;
    struct {
        u8 u00;
        u8 u01;
        s16 flags;     /* +0x02 */
        s16 life;      /* +0x04 */
        s32 u08;
        s32 u0C;
        u8 color[4];   /* +0x10 */
        f32 size;      /* +0x14 */
        f32 u18;
        s32 color1[3]; /* +0x1C: D_800A5860 */
        s32 color2[3]; /* +0x28: D_800A5860 */
        f32 u34[3];
        s32 u40;
        u8 u44[4];
        s32 u48;
        u8 u4C;
        s32 u50;
        s16 u54;
        s16 u56;
    } def;
    struct {
        u8 *obj;
        u8 index;
        u8 *eff;
        u8 i;
    } spay;
    struct {
        s16 u00;
        s16 u02;
        f32 u04;
        f32 u08;
        u8 u0C;
        f32 u10;
        u8 color[4];   /* +0x14 */
        f32 u18;
        u8 u1C;
        s8 u1D;
        f32 u20[10];
        f32 u48;
        u8 u4C;
    } flame;
    struct {
        u8 *eff;
        f32 u4;
    } lpay;
    u8 *e;
    u8 *s;
    u8 **slots;

    if (obj == NULL) {
        return NULL;
    }
    if (arg1 >= 2) {
        return NULL;
    }
    pay.angA = func_150ADA68() * 6.2831855f;
    pay.angB = func_150ADA68() * 6.2831855f;
    pay.obj = obj;
    pay.index = obj[0x3B];
    pay.effObj = (u8 *)func_15083E90(18);
    pay.kind = 18;
    pay.side = arg1;
    pay.color[0] = ((s32 *)D_800A5860)[0];
    pay.color[1] = ((s32 *)D_800A5860)[1];
    pay.color[2] = ((s32 *)D_800A5860)[2];
    pay.u18 = 0;
    def.u00 = 0x94;
    def.u01 = 7;
    def.flags = 0x2203;
    def.life = 300;
    def.u08 = 0;
    def.u0C = 0;
    def.color[0] = 0xFF;
    def.color[1] = 0xFF;
    def.color[2] = 0xFF;
    def.color[3] = 0xFF;
    pay.u40 = 1.0f;
    def.u18 = 1.0f;
    pay.u3C = 0.0f;
    def.u34[0] = 0.0f;
    def.u34[1] = 0.0f;
    def.u34[2] = 0.0f;
    def.size = 100.0f;
    def.color1[0] = ((s32 *)D_800A5860)[0];
    def.color1[1] = ((s32 *)D_800A5860)[1];
    def.color1[2] = ((s32 *)D_800A5860)[2];
    def.color2[0] = ((s32 *)D_800A5860)[0];
    def.color2[1] = ((s32 *)D_800A5860)[1];
    def.color2[2] = ((s32 *)D_800A5860)[2];
    def.u40 = 0x046C0008;
    def.u44[0] = 0xFF;
    def.u44[1] = 0xFF;
    def.u44[2] = 0;
    def.u44[3] = 7;
    def.u48 = 0;
    def.u4C = 0xFF;
    def.u50 = 0;
    def.u54 = 1;
    def.u56 = 0xFF;
    e = func_1513D2F0(&def, (s32)&D_800A4AA0, 29, 0, 0, 28, 0, 0, 0, 0x44, arg2, arg3);
    if (e == NULL) {
        return e;
    }
    memcpy(e + 0x110, &pay, 0x44);
    flame.u00 = 300;
    flame.u02 = 9;
    flame.u04 = 1.0f;
    flame.u08 = 1.0f;
    flame.u0C = 0;
    flame.color[0] = 0xFF;
    flame.color[1] = 0xDC;
    flame.color[2] = 0xA0;
    flame.color[3] = 0xC8;
    flame.u1C = 0;
    flame.u1D = -1;
    flame.u20[0] = 0.0f;
    flame.u20[1] = 0.0f;
    flame.u20[2] = 0.0f;
    flame.u20[3] = 0.0f;
    flame.u20[4] = 0.0f;
    flame.u20[5] = 0.0f;
    flame.u20[6] = 0.0f;
    flame.u20[7] = 0.0f;
    flame.u20[8] = 0.0f;
    flame.u20[9] = 0.0f;
    flame.u48 = 1.0f;
    spay.obj = obj;
    flame.u10 = 0.95f;
    flame.u18 = 40.0f;
    spay.eff = e;
    flame.u4C = 1;
    spay.i = 0;
    spay.index = obj[0x3B];
    slots = (u8 **)(e + 0x110 + 0x1C);
    do {
        slots[spay.i] = func_151A7F00((u8 *)&flame, 16, arg2, arg3);
        s = slots[spay.i];
        if (s != NULL) {
            memcpy(*(u8 **)(s + 0x60), &spay, 16);
        }
        spay.i++;
    } while (spay.i < 2);
    lpay.eff = e;
    lpay.u4 = 0.0f;
    s = (u8 *)func_15149130(300, -1, 34, -1, 0, 32, (struct37 *)8, arg2, arg3);
    *(u8 **)(e + 0x110 + 0x24) = s;
    if (s != NULL) {
        memcpy(s + 0x28, &lpay, 8);
    }
    *(u8 **)(e + 0x110 + 0x28) = func_150F0448(obj, arg1, 255, 217, 160, (s32)e, arg2, arg3);
    *(u8 **)(e + 0x110 + 0x2C) = (u8 *)func_150F0718(70, 255, 130, 0, (s32)e, arg2, arg3);
    return e;
}
