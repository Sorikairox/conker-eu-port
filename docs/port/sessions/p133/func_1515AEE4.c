struct260 *func_151A8B20(void *, s16, s32, u8, s32);
typedef struct { u8 b[0x2C]; } Blk_AEE4;
typedef struct { f32 x, y; Blk_AEE4 blk; } Tab_AEE4; /* 0x34 bytes */
extern Tab_AEE4 D_800A674C[];

/*
 * object_attach_effect_start: for an object whose byte +0x1F is 0 (<= 0), spawns its attached effect through
 * func_151A8B20 (kind 0xF, owner obj, x / y from D_800A674C[obj[0x1F]], 0x2C bytes of extra data) and copies the
 * table entry's 0x2C-byte block to the new record at +0x80. arg1 (the handler table's second argument) is unused.
 * The asm leaves the spawn block's padding bytes uninitialised; the C zeroes them.
 */
void func_1515AEE4(u8 *obj, s32 arg1) {
    struct {
        u8 kind;
        u8 pad1[3];
        u8 *owner;
        f32 x, y;
        f32 zero[5];
        s8 b24, b25, b26, pad27;
    } spawn;
    Tab_AEE4 *e;
    Blk_AEE4 blk;
    struct260 *p;

    if (obj[0x1F] > 0) {
        return;
    }
    e = &D_800A674C[obj[0x1F]];
    spawn.kind = 0xF;
    spawn.pad1[0] = spawn.pad1[1] = spawn.pad1[2] = 0;
    spawn.owner = obj;
    spawn.x = e->x;
    spawn.y = e->y;
    spawn.zero[0] = spawn.zero[1] = spawn.zero[2] = spawn.zero[3] = spawn.zero[4] = 0.0f;
    spawn.b24 = 0;
    spawn.b25 = -1;
    spawn.b26 = 2;
    spawn.pad27 = 0;
    blk = e->blk;
    p = func_151A8B20(&spawn, -1, 0x2C, 0xFF, 0);
    if (p != NULL) {
        memcpy((u8 *) p + 0x80, &blk, 0x2C);
    }
}
