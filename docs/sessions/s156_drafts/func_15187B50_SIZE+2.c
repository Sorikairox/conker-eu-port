typedef struct {
    u8 pad0[0x80];
    f32 x;
    f32 y;
    f32 z;
    f32 w8C;
    f32 w90;
    s16 h94;
    s16 h96;
    s8 b98;
    u8 pad99[7];
} Rec7B50;
typedef struct {
    u8 pad0[0x90];
    f32 f90;
    f32 f94;
    f32 f98;
    f32 f9C;
    f32 fA0;
    Rec7B50 *recs;
    s16 hA8;
    s16 hAA;
} Obj7B50;
void func_15187B50(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7) {
    Obj7B50 *p;
    s32 i;
    s32 a;

    p = func_15167A68(6, 0, 0xB0, 1, 0xFF, 1);
    if (p != NULL) {
        p->recs = allocate_memory(0x780, 1, 2, 1);
        if (p->recs == NULL) {
            func_1516972C((struct102 *)p);
            return;
        }
        p->f90 = arg0;
        p->f94 = arg1;
        p->hA8 = 0;
        p->hAA = arg4;
        p->f98 = arg2;
        p->f9C = arg6;
        p->fA0 = arg7;
        for (i = 0, a = 0; a != 0x438; a += 0x5A, i++) {
            if (a < 0x168) {
                p->recs[i].x = (u32)(7 - (func_150ADA20() & 0xF));
                p->recs[i].y = 0.0f;
                p->recs[i].z = (u32)((func_150ADA20() & 0x3F) + (a - 0x1E));
                p->recs[i].b98 = 0;
            } else if (a < 0x2D0) {
                p->recs[i].x = 0.0f;
                p->recs[i].y = (u32)((func_150ADA20() & 0x3F) + (a - 0x23A));
                p->recs[i].z = (u32)(7 - (func_150ADA20() & 0xF));
                p->recs[i].b98 = 0;
            } else {
                p->recs[i].x = (u32)((func_150ADA20() & 0x3F) + (a - 0x1E));
                p->recs[i].y = (u32)(0x61 - (func_150ADA20() & 0xF));
                p->recs[i].z = 0.0f;
                p->recs[i].b98 = 1;
            }
            if (arg3 >= 4) {
                p->recs[i].w8C = (u32)(func_150ADA20() % (u32)(arg3 >> 2) + arg3);
            } else {
                p->recs[i].w8C = arg3;
            }
            p->recs[i].w90 = (u32)(func_150ADA20() & 0xF);
            p->recs[i].h94 = 0;
            p->recs[i].h96 = arg4 - (func_150ADA20() & arg5);
        }
    }
}
