#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_150D513C(u8 *arg0);
extern u8 D_800A4EA8[];
#endif


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

/* particle_emitter_spawn's particle spec (0x58 bytes; PartSpec layout of game_eu_1E7CC0) */
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

/* particle_emitter_spawn's emitter block (filled up to 0x5A; the calls pass 0x60 / 0x68) */
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
u8 *particle_emitter_spawn(void *emit, s32 emitSize, void *spawn, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9);
s32 memcpy(u8 *, u8 *, s32);
s32 func_150D5634(u8 *e, s32 *pos, u32 *vol, s32 *pan, s32 *pitch, s32 *slot, u16 *sound);
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
// (particle_emitter_spawn: texture 0x15 set 0x5503, and a random texture of D_800A0D90 set 0x2203 with +0x170 = {0, 1.0}),
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
    data->emit[0] = particle_emitter_spawn(&emit1, 0x60, &spec1, 0, 0, 0, 0, -1, kind, owner);

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
    data->emit[1] = particle_emitter_spawn(&emit2, 0x68, &spec2, 0, 0x27, 0, 0, -1, kind, owner);
    if (data->emit[1] != NULL) {
        memcpy(data->emit[1] + 0x170, (u8 *) &extra, sizeof(EmitExtra3870));
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3870.s")
#endif

#ifdef NON_MATCHING
f32 func_15143E64(s32);
s32 func_1515C668(s32, s32 *, u8 *);
void func_150D5268(f32 *pos, f32 *vel, f32 scale, u8 room, s32 owner);

/* rodata copies (NM link drops the asm rodata) */
static const f32 D_800A0DD4_c[1] = { 2.1f };  /* 0x40066666 */
static const f32 D_800A0DD8_c[1] = { 0.2f };  /* 0x3E4CCCCD */
static const f32 D_800A0DDC_c[1] = { 0.35000002f }; /* 0x3EB33334 */

/* +0x94 ring of recorded points (0x14 bytes each) */
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 dist;
    /* 0x10 */ f32 u10;
} Point3F78;

// track_follow_record: entry 13 of D_8008A5DC (`s32 (*)(u8 *)`, 0 = drop). State = +0x98 {target, byte 4 = the
// target's +0x3B, byte 5 = speed class, word 8, links +0xC / +0x10, f32 +0x14 eased towards +0x18}. Returns 0 when
// the target has gone (no word 0) or changed (+0x3B). With D_800BE9E4 > 0: moves the position (+0x10) with
// func_150D4FF0 (result 0: clears link flag 2 and own flag 4, returns 1; 1: on first contact (flag 4) restarts the
// step from here, copies the position and func_150D4FF0's direction to both links (+0x34 / +0x40) and sets their flag
// 2, clears 4; 2: first contact as 1, links lose flag 2), records position + step length + 100 in the +0x94 ring
// (write index +0x2E, count +0x2C, read index +0x2D, size +0x25), then picks the speed class from the target's
// +0x31C (record byte 0x84: target speed +0x44 > 6 / > 3; else the player slot's lean (*D_800BE728)[i] byte 3 > 20 /
// < -20) and sets the goal +0x18 (50 / 10 / 20) and link +0x10's +0x174 (2.1 / 0.2 / 1); class 0 newly reached
// spawns func_150D5268 dust (surface from func_1515C668 or D_800A5860). Always eases +0x14 by 0.35.
s32 func_150D3F78(u8 *obj) {
    Point3F78 *ring = *(Point3F78 **) (obj + 0x94);
    u8 *st = *(u8 **) (obj + 0x98);
    u8 *tgt = *(u8 **) st;
    u8 *rec;
    f32 *pos;
    f32 *glow;
    f32 old[3];
    f32 dir[3];
    f32 step[3];
    f32 spd;
    f32 *surface;
    u8 prev;
    u8 slot;
    s8 lean;
    s32 r;

    if (*(s32 *) tgt == 0 || st[4] != tgt[0x3B]) {
        return 0;
    }
    if (D_800BE9E4 > 0) {
        pos = (f32 *) (obj + 0x10);
        old[0] = pos[0];
        old[1] = pos[1];
        old[2] = pos[2];
        r = func_150D4FF0((u8 *) pos, (u8 *) dir, (struct127 *) tgt, *(s32 *) (st + 8));
        if (r == 0) {
            if (*(u8 **) (st + 0xC) != NULL) {
                *(s32 *) (*(u8 **) (st + 0xC) + 0x58) &= ~2;
            }
            if (*(u8 **) (st + 0x10) != NULL) {
                *(s32 *) (*(u8 **) (st + 0x10) + 0x58) &= ~2;
            }
            *(u16 *) (obj + 0x1E) &= ~4;
            return 1;
        }
        if (r == 1) {
            if (!(*(u16 *) (obj + 0x1E) & 4)) {
                old[0] = pos[0];
                old[1] = pos[1];
                old[2] = pos[2];
            }
            *(u16 *) (obj + 0x1E) |= 4;
            if (*(u8 **) (st + 0xC) != NULL) {
                *(f32 *) (*(u8 **) (st + 0xC) + 0x34) = pos[0];
                *(f32 *) (*(u8 **) (st + 0xC) + 0x38) = pos[1];
                *(f32 *) (*(u8 **) (st + 0xC) + 0x3C) = pos[2];
                *(f32 *) (*(u8 **) (st + 0xC) + 0x40) = dir[0];
                *(f32 *) (*(u8 **) (st + 0xC) + 0x44) = dir[1];
                *(f32 *) (*(u8 **) (st + 0xC) + 0x48) = dir[2];
                *(s32 *) (*(u8 **) (st + 0xC) + 0x58) &= ~4;
                *(s32 *) (*(u8 **) (st + 0xC) + 0x58) |= 2;
            }
            if (*(u8 **) (st + 0x10) != NULL) {
                *(f32 *) (*(u8 **) (st + 0x10) + 0x34) = pos[0];
                *(f32 *) (*(u8 **) (st + 0x10) + 0x38) = pos[1];
                *(f32 *) (*(u8 **) (st + 0x10) + 0x3C) = pos[2];
                *(f32 *) (*(u8 **) (st + 0x10) + 0x40) = dir[0];
                *(f32 *) (*(u8 **) (st + 0x10) + 0x44) = dir[1];
                *(f32 *) (*(u8 **) (st + 0x10) + 0x48) = dir[2];
                *(s32 *) (*(u8 **) (st + 0x10) + 0x58) &= ~4;
                *(s32 *) (*(u8 **) (st + 0x10) + 0x58) |= 2;
            }
        } else if (r == 2) {
            if (!(*(u16 *) (obj + 0x1E) & 4)) {
                old[0] = pos[0];
                old[1] = pos[1];
                old[2] = pos[2];
            }
            *(u16 *) (obj + 0x1E) |= 4;
            if (*(u8 **) (st + 0xC) != NULL) {
                *(s32 *) (*(u8 **) (st + 0xC) + 0x58) &= ~2;
            }
            if (*(u8 **) (st + 0x10) != NULL) {
                *(s32 *) (*(u8 **) (st + 0x10) + 0x58) &= ~2;
            }
        }
        step[0] = pos[0] - old[0];
        step[1] = pos[1] - old[1];
        step[2] = pos[2] - old[2];
        spd = func_15143E64((s32) step);
        ring[(s8) obj[0x2E]].pos[0] = pos[0];
        ring[(s8) obj[0x2E]].pos[1] = pos[1];
        ring[(s8) obj[0x2E]].pos[2] = pos[2];
        ring[(s8) obj[0x2E]].dist = spd;
        ring[(s8) obj[0x2E]].u10 = 100.0f;
        obj[0x2E]++;
        if (obj[0x25] == (s8) obj[0x2E]) {
            obj[0x2E] = 0;
        }
        obj[0x2C]++;
        if ((s8) obj[0x2D] == (s8) obj[0x2E]) {
            obj[0x2D]++;
            if (obj[0x25] == (s8) obj[0x2D]) {
                obj[0x2D] = 0;
            }
            obj[0x2C]--;
        }
        rec = *(u8 **) (tgt + 0x31C);
        if (rec != NULL) {
            glow = NULL;
            if (*(u8 **) (st + 0x10) != NULL) {
                glow = (f32 *) (*(u8 **) (st + 0x10) + 0x170);
            }
            prev = st[5];
            if (rec[0x84] != 0) {
                if (6.0f < *(f32 *) (tgt + 0x44)) {
                    st[5] = 0;
                } else if (3.0f < *(f32 *) (tgt + 0x44)) {
                    st[5] = 1;
                } else {
                    st[5] = 2;
                }
            } else {
                slot = (tgt - (u8 *) D_800CC2D0) / 0x32C;
                if (slot >= 4) {
                    st[5] = 1;
                } else {
                    lean = *(s8 *) (((u8 **) D_800BE728[0])[slot] + 3);
                    if (lean > 20) {
                        st[5] = 0;
                    } else if (lean < -20) {
                        st[5] = 2;
                    } else {
                        st[5] = 1;
                    }
                }
            }
            if (st[5] == 0) {
                if (glow != NULL) {
                    glow[1] = D_800A0DD4_c[0];
                }
                *(f32 *) (st + 0x18) = 50.0f;
                if (st[5] != prev) {
                    if (func_1515C668((s32) tgt, (s32 *) &surface, tgt) == 0) {
                        surface = (f32 *) D_800A5860;
                    }
                    func_150D5268(pos, surface, *(f32 *) (tgt + 0x40), obj[0xC], obj[1]);
                }
            } else if (st[5] == 2) {
                if (glow != NULL) {
                    glow[1] = D_800A0DD8_c[0];
                }
                *(f32 *) (st + 0x18) = 10.0f;
            } else {
                *(f32 *) (st + 0x18) = 20.0f;
                if (glow != NULL) {
                    glow[1] = 1.0f;
                }
            }
        }
    }
    *(f32 *) (st + 0x14) += (*(f32 *) (st + 0x18) - *(f32 *) (st + 0x14)) * D_800A0DDC_c[0];
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3F78.s")
#endif

#ifdef NON_MATCHING
f32 func_15143E64(s32);
s32 func_1515C668(s32, s32 *, u8 *);

s32 func_150D44E4(u8 *arg0) {
    struct {
        s32 u7C;
        f32 u80;
        f32 u84;
        s32 u88;
        s32 * u8C;
    } sp;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f12;
    f32 var_f24;
    f32 var_f26;
    f32 var_f2;
    s32 *temp_t6;
    s32 temp_a1;
    s32 var_a0;
    s32 var_t0;
    s8 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_t6 = (*(s32 **)((u8 *)arg0 + 0x98));
    sp.u8C = temp_t6;
    var_t0 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (D_800C35EA != 1) {
        sp.u88 = var_t0;
        var_t0 = sp.u88;
        if (func_1515C668(*temp_t6, &sp.u7C, arg0) != 0) {
            var_f2 = func_15143E64(sp.u7C);
        } else {
            var_f2 = 0.0f;
        }
    } else if (D_800DBFF0->unk5F0 & 4) {
        var_f2 = 0.0f;
    } else {
        var_f2 = 128.0f;
    }
    if (var_f2 < 10.0f) {
        var_f26 = 0.0f;
    } else if (var_f2 > 70.0f) {
        var_f26 = 600.0f;
    } else {
        var_f26 = (var_f2 - 10.0f) * 0.016666668f * 600.0f;
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_f24 = 0.0f;
        var_a0 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
        if (var_a0 < 0) {
            var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
        if (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
            do {
                temp_a1 = var_a0;
                var_a0 -= 1;
                if (var_a0 < 0) {
                    var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                temp_v1 = (temp_a1 * 0x14) + var_t0;
                temp_f16 = (*(f32 *)((u8 *)temp_v1 + 0xC));
                var_f24 += temp_f16;
                if (var_f26 < var_f24) {
                    if (temp_f16 != 0.0f) {
                        temp_f14 = (var_f24 - var_f26) / temp_f16;
                        temp_v0 = (var_a0 * 0x14) + var_t0;
                        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0));
                        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 4));
                        temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
                        (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) (temp_f0 - ((temp_f0 - (*(f32 *)((u8 *)temp_v1 + 0))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) (temp_f2 - ((temp_f2 - (*(f32 *)((u8 *)temp_v1 + 4))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) (temp_f12 - ((temp_f12 - (*(f32 *)((u8 *)temp_v1 + 8))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0xC)) * (1.0f - temp_f14));
                    }
                    var_f24 = var_f26;
                    if (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        do {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                                (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                            }
                            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                        } while (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                    }
                }
            } while (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
        if (var_f24 != 0.0f) {
            var_f12 = 1.0f / var_f24;
        } else {
            var_f12 = 0.0f;
        }
        sp.u80 = var_f12;
        sp.u84 = var_f24;
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_v0 = (*(s8 *)((u8 *)arg0 + 0x2E));
        var_f0 = sp.u84;
        do {
            var_v0 -= 1;
            if (var_v0 < 0) {
                var_v0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v1_2 = (var_v0 * 0x14) + var_t0;
            (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) (var_f0 * ((*(f32 *)((u8 *)sp.u8C + 0x14)) * sp.u80));
            var_f0 -= (*(f32 *)((u8 *)temp_v1_2 + 0xC));
        } while (var_v0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D44E4.s")
#endif
#ifdef NON_MATCHING
s32 gfx_set_combine_mode(s32, s32, s8 *);
s32 func_15142B7C(s32, s32, s32);
s32 func_15142C10(s32, s32, s32, s32, s32, s8 *);
s32 func_15142E24(u8 *, s32 *, s32, s32, s32, s32, s32, s32, s32, s8 *, s32);
u8 *func_15142FBC(s32, s32, s32, s8 *);
void func_151D6310(s32 *, s16, s32, s32 *, u8 *);
extern s32 D_800914B0;
extern s32 D_800D30BC;

u8 *func_150D4810(u8 *arg0, u8 *arg1, s16 arg2) {
    struct {
        u8 uD7;
        s16 * uD8;
        u8 padDC[0x4];
        f32 uE0;
        f32 uE4;
        u8 padE8[0x3];
        s8 uEB;
        f32 uEC;
        u8 padF0[0x28];
        f32 * u118;
        u8 pad11C[0x8];
        f32 u124;
        f32 u128;
        f32 u12C;
        f32 u130;
        f32 u134;
        f32 u138;
    } sp;
    f32 sp88;
    s32 *temp_v1_2;
    f32 *temp_v0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f24;
    f32 temp_f24_2;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f28;
    f32 temp_f28_2;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f30;
    f32 temp_f30_2;
    f32 temp_f6;
    f32 temp_f8_3;
    f32 var_f14;
    f32 var_f14_2;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f18;
    f32 var_f18_2;
    s16 *temp_t6;
    s16 *temp_t7;
    s16 *temp_t7_2;
    s16 *temp_t7_3;
    s32 temp_a0;
    s32 temp_f10;
    s32 temp_f10_2;
    s32 temp_f10_3;
    s32 temp_f4;
    s32 temp_f4_2;
    s32 temp_f4_3;
    s32 temp_f6_2;
    s32 temp_f6_3;
    s32 temp_f6_4;
    s32 temp_f8;
    s32 temp_f8_2;
    s32 temp_f8_4;
    s32 temp_s2;
    s32 var_a0;
    s32 var_t1;
    s32 var_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_t8;
    u8 *temp_v0_2;
    u8 *temp_v1;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *var_s0;
    u8 *var_v0;

    var_s0 = arg1;
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) < 2) {

    } else {
        temp_s2 = (*(s32 *)((u8 *)arg0 + 0x94));
        temp_v1 = *(*(u8 ***)((u8 *)arg0 + 0x98));
        if (((*(s32 *)((u8 *)temp_v1 + 0x1D4)) == 0) || (((*(u8 *)((u8 *)temp_v1 + 0x74)) & 0xF) == 0xF)) {

        } else {
            func_151D6310(arg0 + 0x84, arg2, ((*(u8 *)((u8 *)arg0 + 0x25)) * 0x30) + 0xF0, &sp.uD8, &sp.uD7);
            if (sp.uD7 != 0) {
                var_v0 = (*(u8 **)((u8 *)((arg0 + (arg2 * 4))) + 0x84));
                var_v1 = 0;
                if ((((*(u8 *)((u8 *)arg0 + 0x25)) * 2) + 0xA) > 0) {
                    do {
                        (*(s16 *)((u8 *)var_v0 + 8)) = 5;
                        (*(s16 *)((u8 *)var_v0 + 0xA)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 6)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 0x18)) = 0xFFA;
                        (*(s16 *)((u8 *)var_v0 + 0x1A)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 0x16)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 0x28)) = 0x1FA4;
                        (*(s16 *)((u8 *)var_v0 + 0x2A)) = 0;
                        (*(s16 *)((u8 *)var_v0 + 0x26)) = 0;
                        var_v1 += 1;
                        var_v0 += 0x30;
                    } while (var_v1 < (((*(u8 *)((u8 *)arg0 + 0x25)) * 2) + 0xA));
                }
            }
            temp_v0 = func_15144B34((s32) arg2);
            sp.uEB = 1;
            sp.u118 = temp_v0;
            temp_v1_2 = ((u8 *)&D_800A4EA8);
            var_s0 = func_15142FBC(gfx_set_combine_mode(func_15142B7C(func_15142C10(func_15142E24(var_s0, &D_800914B0, 0, 0, 0, 0, 0x78, 0, 0, &sp.uEB, 0x3E), 0xFF, 0xFF, 0xFF, 0xFF, &sp.uEB), 0x200005, 0x1F0600), 0x55, &sp.uEB), D_800D30BC | 0x80000 | 0x2CA0, (*(s32 *)((u8 *)temp_v1_2 + 0x1C)) | (*(s32 *)((u8 *)temp_v1_2 + 0x18)), &sp.uEB);
            var_a0 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
            if (var_a0 < 0) {
                var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            var_t1 = var_a0 - 1;
            if (var_t1 < 0) {
                var_t1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v0_2 = temp_s2 + (var_a0 * 0x14);
            (*(f32 *)((u8 *)(&sp.u124) + 0)) = (*(f32 *)((u8 *)temp_v0_2 + 0));
            (*(s32 *)((u8 *)(&sp.u124) + 4)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 4));
            (*(s32 *)((u8 *)(&sp.u124) + 8)) = (s32) (*(s32 *)((u8 *)temp_v0_2 + 8));
            temp_v1_3 = temp_s2 + (var_t1 * 0x14);
            sp.uE0 = (*(f32 *)((u8 *)temp_v0_2 + 0x10));
            (*(f32 *)((u8 *)(&sp.u130) + 0)) = (*(f32 *)((u8 *)temp_v1_3 + 0));
            (*(s32 *)((u8 *)(&sp.u130) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1_3 + 4));
            (*(s32 *)((u8 *)(&sp.u130) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1_3 + 8));
            sp.uE4 = (*(f32 *)((u8 *)temp_v1_3 + 0x10));
            temp_f26 = sp.u124 - (*(f32 *)((u8 *)sp.u118 + 0));
            temp_f28 = sp.u128 - (*(f32 *)((u8 *)sp.u118 + 4));
            temp_f30 = sp.u12C - (*(f32 *)((u8 *)sp.u118 + 8));
            temp_f22 = sp.u128 - sp.u134;
            temp_f24 = sp.u12C - sp.u138;
            temp_f20 = sp.u124 - sp.u130;
            temp_f14 = (temp_f22 * temp_f30) - (temp_f28 * temp_f24);
            temp_f16 = (temp_f24 * temp_f26) - (temp_f30 * temp_f20);
            temp_f12 = (temp_f20 * temp_f28) - (temp_f26 * temp_f22);
            temp_f6 = (temp_f14 * temp_f14) + (temp_f16 * temp_f16) + (temp_f12 * temp_f12);
            sp88 = temp_f6;
            sp.uEC = temp_f6;
            temp_f10 = (s32) sp.u124;
            if (temp_f6 != 0.0f) {
                temp_f2 = sp.uE0 / sqrtf(temp_f6);
                var_f14 = temp_f14 * temp_f2;
                var_f16 = temp_f16 * temp_f2;
                var_f18 = temp_f12 * temp_f2;
            } else {
                var_f18 = 0.0f;
                var_f14 = 0.0f;
                var_f16 = 0.0f;
            }
            temp_f8 = (s32) sp.u128;
            temp_f6_2 = (s32) var_f14;
            temp_f8_2 = (s32) var_f16;
            temp_f10_2 = (s32) sp.u12C;
            temp_f4 = (s32) var_f18;
            (*(s16 *)((u8 *)sp.uD8 + 0)) = temp_f10 + temp_f6_2;
            (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) (temp_f8 + temp_f8_2);
            (*(s16 *)((u8 *)sp.uD8 + 4)) = (s16) (temp_f10_2 + temp_f4);
            temp_t7 = (s16 *) ((u8 *) sp.uD8 + 0x10);  /* P270: byte offset (was s16 stride) */
            sp.uD8 = temp_t7;
            *temp_t7 = (s16) temp_f10;
            (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) temp_f8;
            (*(s16 *)((u8 *)sp.uD8 + 4)) = (s16) temp_f10_2;
            temp_t7_2 = (s16 *) ((u8 *) sp.uD8 + 0x10);  /* P270: byte offset (was s16 stride) */
            sp.uD8 = temp_t7_2;
            (*(s16 *)((u8 *)temp_t7_2 + 0)) = temp_f10 - temp_f6_2;
            (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) (temp_f8 - temp_f8_2);
            (*(s16 *)((u8 *)temp_t7_2 + 4)) = (s16) (temp_f10_2 - temp_f4);
            sp.uD8 = (s16 *) ((u8 *) sp.uD8 + 0x10);  /* P270: byte offset (was s16 stride) */
            do {
                temp_f26_2 = sp.u130 - (*(f32 *)((u8 *)sp.u118 + 0));
                temp_f28_2 = sp.u134 - (*(f32 *)((u8 *)sp.u118 + 4));
                temp_f30_2 = sp.u138 - (*(f32 *)((u8 *)sp.u118 + 8));
                temp_f22_2 = sp.u128 - sp.u134;
                temp_f24_2 = sp.u12C - sp.u138;
                temp_f20_2 = sp.u124 - sp.u130;
                temp_f14_2 = (temp_f22_2 * temp_f30_2) - (temp_f28_2 * temp_f24_2);
                temp_f16_2 = (temp_f24_2 * temp_f26_2) - (temp_f30_2 * temp_f20_2);
                temp_f12_2 = (temp_f20_2 * temp_f28_2) - (temp_f26_2 * temp_f22_2);
                temp_f8_3 = (temp_f14_2 * temp_f14_2) + (temp_f16_2 * temp_f16_2) + (temp_f12_2 * temp_f12_2);
                sp88 = temp_f8_3;
                sp.uEC = temp_f8_3;
                temp_f4_2 = (s32) sp.u130;
                if (temp_f8_3 != 0.0f) {
                    temp_f2_2 = sp.uE4 / sqrtf(temp_f8_3);
                    var_f14_2 = temp_f14_2 * temp_f2_2;
                    var_f16_2 = temp_f16_2 * temp_f2_2;
                    var_f18_2 = temp_f12_2 * temp_f2_2;
                } else {
                    var_f18_2 = 0.0f;
                    var_f14_2 = 0.0f;
                    var_f16_2 = 0.0f;
                }
                temp_f6_3 = (s32) sp.u134;
                temp_f8_4 = (s32) var_f14_2;
                temp_f6_4 = (s32) var_f16_2;
                temp_f4_3 = (s32) sp.u138;
                temp_f10_3 = (s32) var_f18_2;
                (*(s16 *)((u8 *)sp.uD8 + 0)) = temp_f4_2 + temp_f8_4;
                (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) (temp_f6_3 + temp_f6_4);
                (*(s16 *)((u8 *)sp.uD8 + 4)) = (s16) (temp_f4_3 + temp_f10_3);
                temp_t7_3 = (s16 *) ((u8 *) sp.uD8 + 0x10);  /* P270: byte offset (was s16 stride) */
                sp.uD8 = temp_t7_3;
                temp_t6 = (s16 *) ((u8 *) temp_t7_3 + 0x10);  /* P270: byte offset (was s16 stride) */
                (*(s16 *)((u8 *)temp_t7_3 + 0)) = (s16) temp_f4_2;
                (*(s16 *)((u8 *)temp_t7_3 + 2)) = (s16) temp_f6_3;
                (*(s16 *)((u8 *)temp_t7_3 + 4)) = (s16) temp_f4_3;
                sp.uD8 = temp_t6;
                (*(s16 *)((u8 *)temp_t6 + 0)) = temp_f4_2 - temp_f8_4;
                (*(s16 *)((u8 *)sp.uD8 + 2)) = (s16) (temp_f6_3 - temp_f6_4);
                (*(s16 *)((u8 *)temp_t6 + 4)) = (s16) (temp_f4_3 - temp_f10_3);
                sp.uD8 = (s16 *) ((u8 *) sp.uD8 + 0x10);  /* P270: byte offset (was s16 stride) */
                (*(s32 *)((u8 *)var_s0 + 0)) = 0x0100600C;
                temp_s0 = var_s0 + 8;
                (*(s16 **)((u8 *)var_s0 + 4)) = (s16 *) ((s16 *) ((u8 *) sp.uD8 - 0x60));  /* P270: byte offset (was s16 stride) */
                temp_s0_2 = temp_s0 + 8;
                (*(s32 *)((u8 *)temp_s0 + 0)) = 0x06000206;
                (*(s32 *)((u8 *)temp_s0 + 4)) = 0x20806;
                (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0x0604020A;
                (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0x2080A;
                var_s0 = temp_s0_2 + 8;
                temp_a0 = var_t1;
                var_t1 -= 1;
                if (var_t1 < 0) {
                    var_t1 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                if (temp_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                    temp_t8 = temp_s2 + (temp_a0 * 0x14);
                    (*(f32 *)((u8 *)(&sp.u124) + 0)) = (*(f32 *)((u8 *)temp_t8 + 0));
                    (*(s32 *)((u8 *)(&sp.u124) + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
                    temp_v1_4 = temp_s2 + (var_t1 * 0x14);
                    (*(s32 *)((u8 *)(&sp.u124) + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
                    (*(f32 *)((u8 *)(&sp.u130) + 0)) = (*(f32 *)((u8 *)temp_v1_4 + 0));
                    (*(s32 *)((u8 *)(&sp.u130) + 4)) = (s32) (*(s32 *)((u8 *)temp_v1_4 + 4));
                    (*(s32 *)((u8 *)(&sp.u130) + 8)) = (s32) (*(s32 *)((u8 *)temp_v1_4 + 8));
                    sp.uE4 = (*(f32 *)((u8 *)temp_v1_4 + 0x10));
                }
            } while (temp_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
    }
    return var_s0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4810.s")
#endif
#ifdef NON_MATCHING
u8 *func_15031C4C(struct127 *, s32, s32);

// object_fire_message: message handler of the func_150D3870 effect object (D_8008A760 handler table). data = +0x98
// ({owner object, its room byte, effect handle, ...}). Messages 0, 0x2E and 3: when the message names the owner
// (msg +0 == owner, or msg +4 byte == room) the effect object removes itself (node_destroy). Message 0x2D (object
// replaced, msg = {old, new, ..., room of old (+8), room of new (+9)}): when the owner is msg +0, it moves to msg +4
// (room +9), when it is msg +4 it moves to msg +0 (room +8); either way it takes a new effect handle for the new
// owner (func_15031C4C 0x79, 0x7A when the owner's id is 0x48).
void func_150D4ED0(u8 *obj, u8 *msg, u8 event) {
    u8 *data = *(u8 **) (obj + 0x98);
    struct127 *owner;

    if (event == 0 || event == 0x2E || event == 3) {
        if (*(struct127 **) msg == *(struct127 **) data || data[4] == msg[4]) {
            node_destroy((struct102 *) obj);
        }
    } else if (event == 0x2D) {
        if (*(struct127 **) msg == *(struct127 **) data) {
            owner = *(struct127 **) (msg + 4);
            *(struct127 **) data = owner;
            data[4] = msg[9];
        } else if (*(struct127 **) (msg + 4) == *(struct127 **) data) {
            owner = *(struct127 **) msg;
            *(struct127 **) data = owner;
            data[4] = msg[8];
        } else {
            return;
        }
        *(u8 **) (data + 8) = func_15031C4C(owner, (owner->id == 0x48) ? 0x7A : 0x79, 0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4ED0.s")
#endif

#ifdef NON_MATCHING
s32 func_1514654C(struct127 *, s32, s32, void **, void **, s32);
extern s32 D_800A0DA0;
extern s32 D_800A0DAC;

// object_get_beam_ends: the two end points of the object's beam: with a model (arg2->unk1D4) the positions of the
// two named joints D_800A0DA0 / D_800A0DAC (func_1514654C, 2 lookups, result 1 on success, else 0); without one,
// the object position + 100 and + 600 in y (result 2). P124: the joint name / output lists are 2-element arrays
// (m2c had 4 separate locals and passed the address of the first of each pair).
s32 func_150D4FF0(u8 *arg0, u8 *arg1, struct127 *arg2, s32 arg3) {
    void *names[2];
    void *outs[2];

    if (arg2->unk1D4 != NULL) {
        names[0] = &D_800A0DA0;
        names[1] = &D_800A0DAC;
        outs[0] = arg0;
        outs[1] = arg1;
        if (func_1514654C(arg2, arg3, 0, names, outs, 2) != 0) {
            return 1;
        }
        return 0;
    }
    *(f32 *)(arg0 + 0) = arg2->x_position;
    *(f32 *)(arg0 + 4) = arg2->y_position + 100.0f;
    *(f32 *)(arg0 + 8) = arg2->z_position;
    *(f32 *)(arg1 + 0) = arg2->x_position;
    *(f32 *)(arg1 + 4) = arg2->y_position + 100.0f + 500.0f;
    *(f32 *)(arg1 + 8) = arg2->z_position;
    return 2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4FF0.s")
#endif
void func_150D50E4(s32 arg0) {
    func_150D513C(arg0);
    func_15147E64(arg0);
}

void func_150D5110(s32 arg0) {
    func_150D513C(arg0);
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
void func_1000FD38(s32, s32, s32);
s32 func_150D5634(u8 *e, s32 *pos, u32 *vol, s32 *pan, s32 *pitch, s32 *slot, u16 *sound);

void func_150D513C(u8 *arg0) {
    s32 *sp20;
    struct102 *temp_a0;
    struct102 *temp_a0_2;
    u8 *temp_s0;

    temp_s0 = (*(u8 **)((u8 *)arg0 + 0x98));
    if (D_8008FD8C < 5) {
        func_1000FD38((s32) &func_150D5634, (s32) temp_s0, 0x5B3);
    }
    sp20 = (s32 *) &func_150D5634;
    func_1000FD38((s32) &func_150D5634, (s32) temp_s0, 0x5B4);
    func_1000FD38((s32) &func_150D5634, (s32) temp_s0, 0x5BC);
    temp_a0 = (*(struct102 **)((u8 *)temp_s0 + 0xC));
    if (temp_a0 != NULL) {
        node_destroy(temp_a0);
    }
    temp_a0_2 = (*(struct102 **)((u8 *)temp_s0 + 0x10));
    if (temp_a0_2 != NULL) {
        node_destroy(temp_a0_2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D513C.s")
#endif
extern f32 D_800A0DE4;
extern u8 D_800A0D90[];
s32 func_150D51D4(u8 *arg0)
{
  u8 *temp_v1;
  *(s16 *)(arg0 + 0x170) -= D_800BE9E4;
  temp_v1 = arg0 + 0x110;
  if (*(s16 *)(arg0 + 0x170) < 0) {
    arg0[0x18] = *(s32 *)&D_800A0D90[(func_150ADA20() & 3) * 4];
    *(s16 *)(arg0 + 0x170) = (func_150ADA20() & 7) + 3;
  }
  *(f32 *)(temp_v1 + 0x48) += (*(f32 *)(arg0 + 0x174) - *(f32 *)(temp_v1 + 0x48)) * D_800A0DE4;
  return 1;
}

#ifdef NON_MATCHING
s32 func_151307F0(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void func_15143794(s16, s16, f32, void *);
extern f32 D_800A0DE8;
extern f32 D_800A0DEC;
extern f32 D_800A0DF0;
extern f32 D_800A0DF4;
extern f32 D_800A0DF8;

/* func_151307F0's sprite particle template (the func_15153BA4 layout; +0x68.. is not filled here) */
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u16 flags;
    /* 0x0A */ s16 life;
    /* 0x0C */ s32 uC;
    /* 0x10 */ s32 u10;
    /* 0x14 */ u8 colour[8]; /* 7 bytes, alpha */
    /* 0x1C */ u8 u1C;
    /* 0x1D */ u8 sprite;
    /* 0x1E */ s16 u1E;
    /* 0x20 */ s16 u20;
    /* 0x22 */ s16 u22;
    /* 0x24 */ f32 u24;
    /* 0x28 */ f32 size[2];
    /* 0x30 */ f32 pos[3];
    /* 0x3C */ f32 u3C[3];
    /* 0x48 */ f32 vel[3];
    /* 0x54 */ f32 u54;
    /* 0x58 */ s32 mode;
    /* 0x5C */ s32 u5C;
    /* 0x60 */ u8 u60[7];
    /* 0x67 */ u8 pad67;
    /* 0x68 */ s16 u68;
    /* 0x6A */ u8 pad6A[2];
    /* 0x6C */ f32 u6C;
} SprTmpl5268;

// smoke_puff_burst: spawns 10..20 smoke sprites (func_151307F0, room / owner from arg3 / arg4) at pos. Each gets a
// random sprite of D_800A0D90, life 27..44, alpha 100..255, size 199..432 and a velocity from func_15143794 (yaw
// around the scaled heading byte (s16) (scale * D_800A0DE8) >> 8 + 0x40 plus 0..129, pitch -64..16, speed 5..15)
// minus the source's horizontal velocity (vel x / z) times a random drag; random flip flags 0x40 / 0x80.
void func_150D5268(f32 *pos, f32 *vel, f32 scale, u8 room, s32 owner) {
    SprTmpl5268 t;
    s32 n;
    s16 yaw;
    f32 drag;
    u32 r1;
    u32 r2;
    s32 bit80;
    s32 bit40;

    n = (u32) func_150ADA20() % 11 + 10;
    t.u0 = 0x200005;
    t.u4 = 0;
    t.flags = 0x2203;
    t.uC = 0;
    t.u10 = 0;
    t.colour[0] = 0xFF;
    t.colour[1] = 0xFF;
    t.colour[2] = 0xFF;
    t.colour[3] = 0xFF;
    t.colour[4] = 0xFF;
    t.colour[5] = 0xFF;
    t.colour[6] = 0xFF;
    t.u1C = 0xFF;
    t.pos[0] = pos[0];
    t.pos[1] = pos[1];
    t.pos[2] = pos[2];
    t.u3C[0] = ((f32 *) D_800A5860)[0];
    t.u3C[1] = ((f32 *) D_800A5860)[1];
    t.u3C[2] = ((f32 *) D_800A5860)[2];
    t.u1E = 10;
    t.u20 = 0x19;
    t.u60[1] = 7;
    t.u60[2] = 0xFF;
    t.u22 = 1;
    t.mode = 0x4C207;
    t.u60[0] = 0;
    t.u60[3] = 0xFF;
    t.u60[4] = 0xFF;
    t.u60[5] = 0;
    t.u5C = 0;
    t.u60[6] = 0xFF;
    t.u24 = 1.0f;
    yaw = ((s16) (s32) (scale * D_800A0DE8) >> 8) + 0x40;
    do {
        drag = func_150ADA68() * D_800A0DF0 + D_800A0DEC;
        t.sprite = ((s32 *) D_800A0D90)[func_150ADA20() & 3];
        t.life = (u32) func_150ADA20() % 18 + 27;
        t.colour[7] = (u32) func_150ADA20() % 156 + 100;
        t.size[0] = t.size[1] = func_150ADA68() * 233.0f + 199.0f;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_15143794(r1 % 130 + yaw, r2 % 81 - 0x40, func_150ADA68() * 10.0f + 5.0f, t.vel);
        t.vel[0] -= vel[0] * drag;
        t.vel[2] -= vel[2] * drag;
        t.u54 = func_150ADA68() * D_800A0DF4 + D_800A0DF8;
        t.mode &= ~0xC0;
        bit80 = (func_150ADA20() & 1) ? 0x80 : 0;
        bit40 = (func_150ADA20() & 1) ? 0x40 : 0;
        t.mode |= bit40 | bit80;
        func_151307F0((s32) &t, 1, 0, 0, room, owner);
        n--;
    } while (n > 0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5268.s")
#endif
#ifdef NON_MATCHING
// rocket_sound_update: per-frame callback (func_1000FA64, same type as object_sound_follow_cam) of the three sounds
// func_150D3870 starts for its object (voice +0x18 = the object's Data3870, voice +0x1C = sound id). Target volume
// and pitch per id: 0x5B3 follows the speed of data->obj (f32 +0x28): volume speed*25 (0 below 500, capped at 5000),
// pitch speed*5 (capped at 1000); state (data +5) 1 or 2 adds 7000 to the volume (1 also sets pitch 400); another
// state sets pitch 400 and jumps the volume to its target. 0x5BC: state 0 -> 24000 at once, else 400. 0x5B4: state
// 0 -> 16000 at once with pitch 400; 1 (or D_8008FD8C >= 5) -> 12000; else 0 with pitch 400. Volume (+0xC) and pitch
// (*pitch) move towards their targets by D_800BE9E4 * 256 a frame (pitch down by * 8). Below 500 the volume is 0;
// otherwise a voice without a sound restarts its id (+0 and *sound). Follows data->obj's position (+2/+4/+6), halves
// the volume (and *vol) in mode D_800C35EA == 1, stores the pitch (+0x20). When *vol is 0 it stops the playing sound
// (+0x24) and clears *sound. Returns 0.
s32 func_150D5634(u8 *e, s32 *pos, u32 *vol, s32 *pan, s32 *pitch, s32 *slot, u16 *sound) {
    Data3870 *data = *(Data3870 **) (e + 0x18);
    s32 id = *(s32 *) (e + 0x1C);
    s32 cur = *(s32 *) (e + 0xC);
    s32 curPitch = *pitch;
    s32 target = 0;
    s32 targetPitch = 0;
    u8 *obj;
    f32 speed;

    if (id == 0x5B3) {
        obj = (u8 *) data->obj;
        if (obj != NULL) {
            speed = *(f32 *) (obj + 0x28);
            target = (s32) (speed * 25.0f);
            if (target > 5000) {
                target = 5000;
            } else if (target < 500) {
                target = 0;
            }
            targetPitch = (s32) (0.0f + speed * 5.0f);
            if (targetPitch > 1000) {
                targetPitch = 1000;
            }
        }
        if (data->u05 == 2) {
            target += 7000;
        } else if (data->u05 == 1) {
            targetPitch = 400;
            target += 7000;
        } else {
            targetPitch = 400;
            if (target != 0) {
                cur = target;
            }
        }
    } else if (id == 0x5BC) {
        if (data->u05 == 0) {
            target = 24000;
            cur = 24000;
        } else {
            target = 400;
        }
    } else if (id == 0x5B4) {
        if (data->u05 == 0) {
            target = 16000;
            targetPitch = 400;
            cur = 16000;
        } else if (data->u05 == 1 || D_8008FD8C >= 5) {
            target = 12000;
        } else {
            targetPitch = 400;
        }
    }

    if (cur != target) {
        if (cur < target) {
            cur += D_800BE9E4 << 8;
            if (cur > target) {
                cur = target;
            }
        } else {
            cur -= D_800BE9E4 << 8;
            if (cur < target) {
                cur = target;
            }
        }
    }
    if (curPitch != targetPitch) {
        if (curPitch < targetPitch) {
            curPitch += D_800BE9E4 << 8;
            if (curPitch > targetPitch) {
                curPitch = targetPitch;
            }
        } else {
            curPitch -= D_800BE9E4 << 3;
            if (curPitch < targetPitch) {
                curPitch = targetPitch;
            }
        }
    }

    if (cur < 500) {
        cur = 0;
    } else if (*sound == 0) {
        *(s16 *) (e + 0) = id;
        *sound = id;
    }
    *(s16 *) (e + 2) = (s32) *(f32 *) ((u8 *) data->obj + 0x14);
    *(s16 *) (e + 4) = (s32) *(f32 *) ((u8 *) data->obj + 0x18);
    *(s16 *) (e + 6) = (s32) *(f32 *) ((u8 *) data->obj + 0x1C);
    if (D_800C35EA == 1) {
        *(s32 *) (e + 0xC) = cur >> 1;
        *vol >>= 1;
    } else {
        *(s32 *) (e + 0xC) = cur;
    }
    *(s16 *) (e + 0x20) = curPitch;
    *pitch = (s16) curPitch;
    if (*vol == 0) {
        if (*(u16 *) (e + 0x24) != 0) {
            func_100111C8(*(u16 *) (e + 0x24));
            *(u16 *) (e + 0x24) = 0;
        }
        *sound = 0;
    }
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5634.s")
#endif
