#ifdef NON_MATCHING
/* func_15147FF0 spawn request (0x18 bytes) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ s16 u0C;
    /* 0x0E */ s16 flags;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 u14;
    /* 0x15 */ u8 u15;
    /* 0x16 */ u8 pad16[2];
} Spawn3870;

/* 0x1C bytes copied to the new object's data (+0x98); func_150D513C releases the sounds and the two emitters */
typedef struct {
    /* 0x00 */ struct127 *obj;
    /* 0x04 */ u8 room;
    /* 0x05 */ u8 u05;
    /* 0x08 */ u8 *handle;
    /* 0x0C */ u8 *emit[2];
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
} Data3870;

/* func_151407D0's particle spec (0x58 bytes; PartSpec layout of game_eu_1E7CC0) */
typedef struct {
    /* 0x00 */ u8 texture;
    /* 0x01 */ u8 u01;
    /* 0x02 */ s16 texSet;
    /* 0x04 */ s16 life;
    /* 0x08 */ s32 u08;
    /* 0x0C */ s32 u0C;
    /* 0x10 */ u8 color[4];
    /* 0x14 */ f32 halfW;
    /* 0x18 */ f32 halfH;
    /* 0x1C */ f32 pos[3];
    /* 0x28 */ f32 dir[3];
    /* 0x34 */ f32 scale[3];
    /* 0x40 */ s32 flags;
    /* 0x44 */ u8 u44;
    /* 0x45 */ u8 u45;
    /* 0x46 */ u8 u46;
    /* 0x47 */ u8 u47;
    /* 0x48 */ s32 u48;
    /* 0x4C */ u8 u4C;
    /* 0x4D */ u8 pad4D[0xB];
} Spec3870;

/* func_151407D0's emitter block (filled up to 0x5A; the calls pass 0x60 / 0x68) */
typedef struct {
    /* 0x00 */ f32 u00;
    /* 0x04 */ f32 u04;
    /* 0x08 */ f32 u08;
    /* 0x0C */ f32 u0C;
    /* 0x10 */ f32 u10;
    /* 0x14 */ f32 u14;
    /* 0x18 */ f32 u18;
    /* 0x1C */ f32 u1C;
    /* 0x20 */ f32 u20;
    /* 0x24 */ s32 u24[8];
    /* 0x44 */ s32 u44;
    /* 0x48 */ f32 u48;
    /* 0x4C */ s16 u4C[4];
    /* 0x54 */ u8 u54[4];
    /* 0x58 */ u8 u58;
    /* 0x59 */ s8 u59;
    /* 0x5A */ u8 pad5A[2];
} Emit3870;

/* 8 bytes copied to the second emitter's +0x170 */
typedef struct {
    /* 0x00 */ s16 u00;
    /* 0x04 */ f32 u04;
} EmitExtra3870;

u8 *func_15031C4C(struct127 *, s32, s32);
s32 func_150D4FF0(u8 *arg0, u8 *arg1, struct127 *arg2, s32 arg3);
u8 *func_151407D0(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9);
s32 memcpy(u8 *, u8 *, s32);
extern s32 func_150D5634;
extern u8 D_800A0D90[]; /* 4 s32 texture ids (0x60..0x63) */
extern f32 D_800A0DB8;
extern f32 D_800A0DBC;
extern f32 D_800A0DC0;
extern f32 D_800A0DC4;
extern f32 D_800A0DC8;
extern f32 D_800A0DCC;
extern f32 D_800A0DD0;

// object_fire_spawn: creates the burning-effect object for `obj` (func_15031D40): takes effect handle 0x79 (0x7A when
// obj->id is 0x48) with func_15031C4C (none: return); the effect position and direction come from func_150D4FF0 (flag 4
// set when it found them; else (0, 0, 0) and (0, 500, 0)); func_15147FF0 (0x20, 0x14) creates the object, whose data
// (+0x98) gets {obj, room, 1, handle, emitters, 20, 20}. Starts the looping sounds 0x5B3 (sound level < 5), 0x5B4 and
// 0x5BC (level < 7 or obj +0x318 set) at the object's position with callback func_150D5634, and two emitters
// (func_151407D0: texture 0x15 set 0x5503, and a random texture of D_800A0D90 set 0x2203 with +0x170 = {0, 1.0}),
// stored in the data. kind (u8) and owner go to every spawn. Returns 0 (the asm leaves a leftover v0; the callers,
// func_15031D40 (asm) and game_eu_5D910's C, do not read it).
s32 func_150D3870(struct127 *obj, u8 kind, s32 owner) {
    EmitExtra3870 extra;
    Spec3870 spec2;
    Emit3870 emit2;
    Spec3870 spec1;
    Emit3870 emit1;
    f32 dir[3];
    Data3870 blk;
    Spawn3870 spawn;
    u8 *handle;
    u8 *newobj;
    Data3870 *data;
    s32 snd;

    spawn.u15 = 25;
    spawn.u0C = 300;
    spawn.flags = 0x12;
    spawn.u10 = 15;
    spawn.u14 = 1;
    blk.u18 = 20.0f;
    blk.u14 = 20.0f;
    blk.u05 = 1;
    blk.emit[0] = NULL;
    blk.emit[1] = NULL;
    blk.obj = obj;
    blk.room = obj->unique_id;
    snd = (obj->id == 0x48) ? 0x7A : 0x79;
    handle = func_15031C4C(obj, snd, 0);
    if (handle == NULL) {
        return 0;
    }
    blk.handle = handle;
    if (func_150D4FF0((u8 *) spawn.pos, (u8 *) dir, obj, (s32) handle) != 0) {
        spawn.flags |= 4;
    } else {
        spawn.pos[0] = 0.0f;
        spawn.pos[1] = 0.0f;
        spawn.pos[2] = 0.0f;
        dir[0] = 0.0f;
        dir[2] = 0.0f;
        dir[1] = 500.0f;
    }
    newobj = func_15147FF0(&spawn, 0x20, 0x14, 0, 13, 13, 0, 0, 0, kind, owner);
    if (newobj == NULL) {
        return 0;
    }
    data = *(Data3870 **) (newobj + 0x98);
    memcpy((u8 *) data, (u8 *) &blk, sizeof(Data3870));
    if (D_8008FD8C < 5) {
        func_1000FA64(0x5B3, data->obj->x_position, data->obj->y_position, data->obj->z_position, 1000, 1000, 200,
                      (s32) &func_150D5634, data, 0x5B3, 12, 0);
    }
    func_1000FA64(0x5B4, data->obj->x_position, data->obj->y_position, data->obj->z_position, 1000, 1000, 200,
                  (s32) &func_150D5634, data, 0x5B4, 12, 0);
    if (D_8008FD8C < 7 || *(s32 *) ((u8 *) obj + 0x318) != 0) {
        func_1000FA64(0x5BC, data->obj->x_position, data->obj->y_position, data->obj->z_position, 1000, 1000, 200,
                      (s32) &func_150D5634, data, 0x5BC, 12, 0);
    }

    emit1.u00 = 200.0f;
    emit1.u04 = 40.0f;
    emit1.u08 = 40.0f;
    emit1.u0C = 40.0f;
    emit1.u10 = D_800A0DB8;
    emit1.u14 = D_800A0DB8;
    emit1.u18 = D_800A0DBC;
    emit1.u1C = D_800A0DC0;
    emit1.u20 = D_800A0DC4;
    emit1.u24[0] = -1;
    emit1.u24[4] = -1;
    emit1.u24[1] = -1;
    emit1.u24[5] = -1;
    emit1.u24[2] = -1;
    emit1.u24[6] = -1;
    emit1.u24[3] = -1;
    emit1.u24[7] = -1;
    emit1.u44 = 0;
    emit1.u48 = 1.0f;
    emit1.u4C[0] = 0;
    emit1.u4C[1] = 0;
    emit1.u4C[2] = 0;
    emit1.u4C[3] = 0;
    emit1.u54[0] = 0;
    emit1.u54[1] = 0;
    emit1.u54[2] = 0;
    emit1.u54[3] = 0;
    emit1.u58 = 0;
    emit1.u59 = -1;
    spec1.texture = 0x15;
    spec1.u01 = 3;
    spec1.texSet = 0x5503;
    spec1.life = 300;
    spec1.u08 = 0;
    spec1.u0C = 0;
    spec1.color[0] = 0xFF;
    spec1.color[1] = 0xFF;
    spec1.color[2] = 0xFF;
    spec1.color[3] = 0xFF;
    spec1.halfW = 100.0f;
    spec1.halfH = 100.0f;
    spec1.pos[0] = spawn.pos[0];
    spec1.pos[1] = spawn.pos[1];
    spec1.pos[2] = spawn.pos[2];
    spec1.dir[0] = dir[0];
    spec1.dir[1] = dir[1];
    spec1.dir[2] = dir[2];
    spec1.scale[0] = 1.0f;
    spec1.scale[1] = 1.0f;
    spec1.scale[2] = 1.0f;
    spec1.flags = 0xCD2006;
    spec1.u44 = 0xFF;
    spec1.u45 = 0xFF;
    spec1.u46 = 0;
    spec1.u47 = 6;
    spec1.u48 = 0;
    spec1.u4C = 0xFF;
    data->emit[0] = func_151407D0(&emit1, 0x60, &spec1, 0, 0, 0, 0, -1, kind, owner);

    extra.u00 = 0;
    extra.u04 = 1.0f;
    emit2.u00 = 45.0f;
    emit2.u04 = 45.0f;
    emit2.u08 = 25.5f;
    emit2.u0C = 25.5f;
    emit2.u10 = D_800A0DC8;
    emit2.u14 = D_800A0DC8;
    emit2.u18 = 1.0f;
    emit2.u1C = D_800A0DCC;
    emit2.u20 = D_800A0DD0;
    emit2.u24[0] = -1;
    emit2.u24[4] = -1;
    emit2.u24[1] = -1;
    emit2.u24[5] = -1;
    emit2.u24[2] = -1;
    emit2.u24[6] = -1;
    emit2.u24[3] = -1;
    emit2.u24[7] = -1;
    emit2.u44 = 0;
    emit2.u48 = 1.0f;
    emit2.u4C[0] = 0;
    emit2.u4C[1] = 0;
    emit2.u4C[2] = 0;
    emit2.u4C[3] = 0;
    emit2.u54[0] = 0;
    emit2.u54[1] = 0;
    emit2.u54[2] = 0;
    emit2.u54[3] = 0;
    emit2.u58 = 0;
    emit2.u59 = -1;
    spec2.texture = ((s32 *) D_800A0D90)[func_150ADA20() & 3];
    spec2.u01 = 3;
    spec2.texSet = 0x2203;
    spec2.life = 300;
    spec2.u08 = 0;
    spec2.u0C = 0;
    spec2.color[0] = 0xFF;
    spec2.color[1] = 0xFF;
    spec2.color[2] = 0xFF;
    spec2.color[3] = 0xFF;
    spec2.halfW = 100.0f;
    spec2.halfH = 100.0f;
    spec2.pos[0] = spawn.pos[0];
    spec2.pos[1] = spawn.pos[1];
    spec2.pos[2] = spawn.pos[2];
    spec2.dir[0] = dir[0];
    spec2.dir[1] = dir[1];
    spec2.dir[2] = dir[2];
    spec2.scale[0] = 1.0f;
    spec2.scale[1] = 1.0f;
    spec2.scale[2] = 1.0f;
    spec2.flags = 0xCD2006;
    spec2.u44 = 0xFF;
    spec2.u45 = 0xFF;
    spec2.u46 = 0;
    spec2.u47 = 7;
    spec2.u48 = 0;
    spec2.u4C = 0xFF;
    data->emit[1] = func_151407D0(&emit2, 0x68, &spec2, 0, 0x27, 0, 0, -1, kind, owner);
    if (data->emit[1] != NULL) {
        memcpy(data->emit[1] + 0x170, (u8 *) &extra, sizeof(EmitExtra3870));
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3870.s")
#endif
