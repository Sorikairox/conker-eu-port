struct102 *func_1513418C(u8 *arg0, s32 arg1, u8 arg2, s32 arg3);
/* effect spec for func_1513418C (0x30 bytes) */
typedef struct {
    /* 0x00 */ s32 u0;
    /* 0x04 */ s32 u4;
    /* 0x08 */ u8 objId;
    /* 0x09 */ u8 pad9[3];
    /* 0x0C */ u8 *obj;
    /* 0x10 */ u8 u10;
    /* 0x11 */ u8 pad11[3];
    /* 0x14 */ f32 offset[3];
    /* 0x20 */ f32 u20;
    /* 0x24 */ f32 u24;
    /* 0x28 */ s16 u28;
    /* 0x2A */ u8 u2A;
    /* 0x2B */ u8 u2B;
    /* 0x2C */ s8 u2C;
    /* 0x2D */ u8 u2D;
    /* 0x2E */ u8 pad2E[2];
} S4B40;
/*
 * obj_attached_effect_start: P190. Starts a func_1513418C effect attached to obj (id obj[0x3B], offset 0, 14.7,
 * 3.0, 100, 10, 1, -1, 0) with arg1 as its byte argument; nothing for a NULL obj.
 */
void func_151A4B40(u8 *obj, u8 arg1) {
    S4B40 s;

    if (obj != NULL) {
        s.u0 = 0;
        s.u4 = 0;
        s.objId = obj[0x3B];
        s.obj = obj;
        s.u10 = 1;
        s.offset[0] = 0.0f;
        s.offset[1] = 0.0f;
        s.offset[2] = 0.0f;
        s.u20 = 14.7f;
        s.u24 = 3.0f;
        s.u28 = 100;
        s.u2A = 10;
        s.u2B = 1;
        s.u2C = -1;
        s.u2D = 0;
        func_1513418C((u8 *)&s, 0, arg1, 0);
    }
}
