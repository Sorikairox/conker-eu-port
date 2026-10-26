#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void mtxf_look_at(f32 mtx[4][4], f32 posx, f32 posy, f32 posz, f32 lookx, f32 looky, f32 lookz, f32 upx, f32 upy, f32 upz);

/* read from memory: the multiplications by 0 / 1 must not be folded (IDO folds literal operands, which changes the
 * sign of zero results; the asm multiplies by registers) */
static const f32 sAxisY[3] = { 0.0f, 1.0f, 0.0f };

#define OBJ_F32(obj, off) (*(f32 *) ((u8 *) (obj) + (off)))

/* Turns joint `joint` of object `index` towards the D_800DBFF0 position (+0x2F8, a look-at from the joint's own
 * translation, up = d x (d x Y)), then applies the object's scale: x / z columns by +0x14C, y column by +0x150.
 * `turn` swaps the look direction a quarter turn about Y: (dx, dy, dz) -> (dz, dy, -dx). arg0 is unused. */
/* was func_15036600 */
void obj_joint_look_at_camera(s32 arg0, s32 index, s32 joint, s32 turn) {
    struct127 *obj = &g_objects[index];
    f32 (*mtx)[4];
    f32 pos[3];
    f32 d[3];
    f32 a[3];
    f32 up[3];
    f32 t;

    if (obj->unk1D4 == NULL) {
        return;
    }
    mtx = (f32 (*)[4]) ((u8 *) obj->unk1D4 + joint * 64);
    pos[0] = mtx[3][0];
    pos[1] = mtx[3][1];
    pos[2] = mtx[3][2];
    d[0] = OBJ_F32(D_800DBFF0, 0x2F8) - pos[0];
    d[1] = OBJ_F32(D_800DBFF0, 0x2FC) - pos[1];
    d[2] = OBJ_F32(D_800DBFF0, 0x300) - pos[2];
    if (turn) {
        t = d[0];
        d[0] = d[2];
        d[2] = -t;
    }
    /* a = d x Y, up = d x a */
    a[0] = d[1] * sAxisY[2] - sAxisY[1] * d[2];
    a[1] = d[2] * sAxisY[0] - sAxisY[2] * d[0];
    a[2] = d[0] * sAxisY[1] - sAxisY[0] * d[1];
    up[0] = d[1] * a[2] - a[1] * d[2];
    up[1] = d[2] * a[0] - a[2] * d[0];
    up[2] = d[0] * a[1] - a[0] * d[1];
    mtxf_look_at(mtx, pos[0], pos[1], pos[2], pos[0] - d[0], pos[1] - d[1], pos[2] - d[2], up[0], up[1], up[2]);
    if (OBJ_F32(obj, 0x14C) != 1.0f) {
        mtx[0][0] *= OBJ_F32(obj, 0x14C);
        mtx[1][0] *= OBJ_F32(obj, 0x14C);
        mtx[2][0] *= OBJ_F32(obj, 0x14C);
        mtx[0][2] *= OBJ_F32(obj, 0x14C);
        mtx[1][2] *= OBJ_F32(obj, 0x14C);
        mtx[2][2] *= OBJ_F32(obj, 0x14C);
    }
    if (OBJ_F32(obj, 0x150) != 1.0f) {
        mtx[0][1] *= OBJ_F32(obj, 0x150);
        mtx[1][1] *= OBJ_F32(obj, 0x150);
        mtx[2][1] *= OBJ_F32(obj, 0x150);
    }
}
