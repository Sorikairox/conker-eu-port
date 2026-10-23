// event_object_effect_spawn: spawns a type-0x1A effect for an object (obj NULL: none) through func_15149130:
// lifetime `span` (negative: 300, untimed), sub-list arg5 + 0x14, arg6 / arg7 passed on. Its data (+0x28, 20 bytes):
// the object, the object's byte +0x3B, 0.0f, arg4, arg2, arg3 (bytes +0x12 / +0x13 uninitialised, as in the asm).
// Returns the effect (NULL if none). Event command 0x65 cases 1 / 2 (game_eu_51190); sibling of func_1510A454.
struct260 *func_15109990(u8 *obj, s16 span, s8 arg2, s8 arg3, f32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct260 *fx;
    struct {
        u8 *obj;
        u8 objByte3B;
        u8 pad5[3];
        f32 unk8;
        f32 unkC;
        s8 unk10;
        s8 unk11;
        u8 pad12[2];
    } tmp;
    s16 n;
    u8 timed;

    if (obj == NULL) {
        return NULL;
    }
    timed = 0;
    if (span < 0) {
        n = 300;
    } else {
        timed = 1;
        n = span;
    }
    tmp.unk8 = 0.0f;
    tmp.unkC = arg4;
    tmp.unk10 = arg2;
    tmp.unk11 = arg3;
    tmp.obj = obj;
    tmp.objByte3B = obj[0x3B];
    fx = func_15149130(n, -1, 0x1A, -1, timed, 0x1A, (struct37 *) (arg5 + 0x14), arg6, arg7);
    if (fx != NULL) {
        memcpy((u8 *) fx + 0x28, &tmp, 0x14);
    }
    return fx;
}
