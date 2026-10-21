typedef struct {
    u8 flags;
    s8 idx;
} struct_1F34_b;
typedef struct {
    u8 pad0[0x3C];
    f32 u3C;
    f32 x;
    f32 y;
    f32 z;
    u8 pad4C[0x34];
    f32 u80;
} struct_1F34;
extern u8 (*D_80089C14[])(struct_1F34 *, f32 *, f32 *, struct_1F34_b *);
s32 func_1514672C(f32 *);
s32 func_15046F70(f32 *, s32, f32, f32 *);
int func_15131F34(struct_1F34 *arg0, f32 *arg1, struct_1F34_b *arg2) {
    u8 ret;
    f32 pos[3];
    f32 tmp[3];

    ret = 1;
    if ((arg2->flags & 1) && (arg2->idx != -1) && (D_80089C14[arg2->idx] != NULL) && (arg0->y < arg1[1])) {
        pos[0] = arg0->x;
        pos[1] = arg1[1];
        pos[2] = arg0->z;
        if (func_1514672C(pos) == 0) {
            return 0;
        }
        if (func_15046F70(pos, 0, arg0->y - arg0->u3C * 0.06f, &arg0->u80) != 0) {
            tmp[0] = pos[0];
            tmp[2] = pos[2];
            tmp[1] = arg0->u80;
            ret = D_80089C14[arg2->idx](arg0, arg1, tmp, arg2);
        }
    }
    return ret;
}
