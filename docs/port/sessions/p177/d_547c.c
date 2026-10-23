u8 *func_15165B98(u8 *arg0, s32 arg1, s8 arg2, s32 arg3, u8 arg4, s32 arg5);

// screen_effect_preset: starts preset `kind` (0..7) of the func_15165B98 effect (record kind 0x39 via func_15164CF0)
/* for view `view`: a block of 15 floats (3 periods, 9 coefficients, 3 more), with (-1, 0) for presets 0..3 and 7,
 * (0, 0) for 4 and (1, 0x18) for 5 / 6; presets 5 and 6 also copy 0x18 bytes of `data` to the new record's +0x108.
 * Returns the record (NULL when none was made; the asm returns a stale v0 for kind >= 8, NULL here). */
u8 *func_1516547C(u8 kind, u8 view, u8 *data, u8 arg3, s32 arg4) {
    f32 p[15];
    u8 *rec;

    switch (kind) {
    case 0:
        p[0] = 10.0f;
        p[1] = 4.0f;
        p[2] = 7.0f;
        p[3] = 0.78059995f;
        p[4] = 0.28689998f;
        p[5] = 0.88879997f;
        p[6] = 0.666f;
        p[7] = 1.194f;
        p[8] = 1.01f;
        p[9] = 0.4353f;
        p[10] = 0.58669996f;
        p[11] = 0.7097f;
        p[12] = 6.0f;
        p[13] = 17.0f;
        p[14] = 48.0f;
        return func_15165B98((u8 *)p, view, -1, 0, arg3, arg4);
    case 1:
        p[0] = 20.0f;
        p[1] = 19.0f;
        p[2] = 53.0f;
        p[3] = 0.0f;
        p[4] = 0.0f;
        p[5] = 1.4778f;
        p[6] = 0.60200006f;
        p[7] = 1.021f;
        p[8] = 1.1910001f;
        p[9] = 0.0f;
        p[10] = 0.0f;
        p[11] = 2.905f;
        p[12] = 3.0f;
        p[13] = 5.0f;
        p[14] = 30.0f;
        return func_15165B98((u8 *)p, view, -1, 0, arg3, arg4);
    case 2:
        p[0] = 10.0f;
        p[1] = 7.0f;
        p[2] = 6.0f;
        p[3] = 1.0029f;
        p[4] = 0.49769998f;
        p[5] = 1.4305999f;
        p[6] = 0.65400004f;
        p[7] = 1.062f;
        p[8] = 0.321f;
        p[9] = 0.5169f;
        p[10] = 0.77279997f;
        p[11] = 0.17559999f;
        p[12] = 2.0f;
        p[13] = 27.0f;
        p[14] = 15.0f;
        return func_15165B98((u8 *)p, view, -1, 0, arg3, arg4);
    case 3:
        p[0] = 7.0f;
        p[1] = 11.0f;
        p[2] = 5.0f;
        p[3] = 0.4321f;
        p[4] = 0.6329f;
        p[5] = 0.8082f;
        p[6] = 0.27600002f;
        p[7] = 0.53900003f;
        p[8] = 0.439f;
        p[9] = 1.6726999f;
        p[10] = 0.49469998f;
        p[11] = 0.98939997f;
        p[12] = 5.0f;
        p[13] = 15.0f;
        p[14] = 12.0f;
        return func_15165B98((u8 *)p, view, -1, 0, arg3, arg4);
    case 4:
        p[0] = 8.0f;
        p[1] = 17.0f;
        p[2] = 4.0f;
        p[3] = 0.7614f;
        p[4] = 1.5706999f;
        p[5] = 1.2667999f;
        p[6] = 0.587f;
        p[7] = 0.906f;
        p[8] = 0.40300003f;
        p[9] = 1.1592f;
        p[10] = 0.69729996f;
        p[11] = 1.3464f;
        p[12] = 5.0f;
        p[13] = 3.0f;
        p[14] = 45.0f;
        return func_15165B98((u8 *)p, view, 0, 0, arg3, arg4);
    case 5:
        p[0] = 15.0f;
        p[1] = 10.0f;
        p[2] = 19.0f;
        p[3] = 0.5397f;
        p[4] = 0.7679f;
        p[5] = 0.9881f;
        p[6] = 1.0450001f;
        p[7] = 0.63600004f;
        p[8] = 1.404f;
        p[9] = 0.4526f;
        p[10] = 0.48499998f;
        p[11] = 0.6843f;
        p[12] = 5.0f;
        p[13] = 5.0f;
        p[14] = 25.0f;
        rec = func_15165B98((u8 *)p, view, 1, 0x18, arg3, arg4);
        if (rec != NULL) {
            memcpy(rec + 0x108, data, 0x18);
        }
        return rec;
    case 6:
        p[0] = 15.0f;
        p[1] = 10.0f;
        p[2] = 19.0f;
        p[3] = 0.5397f;
        p[4] = 0.7679f;
        p[5] = 0.9881f;
        p[6] = 1.0450001f;
        p[7] = 0.63600004f;
        p[8] = 1.404f;
        p[9] = 0.4526f;
        p[10] = 0.48499998f;
        p[11] = 0.6843f;
        p[12] = 5.0f;
        p[13] = 5.0f;
        p[14] = 25.0f;
        rec = func_15165B98((u8 *)p, view, 1, 0x18, arg3, arg4);
        if (rec != NULL) {
            memcpy(rec + 0x108, data, 0x18);
        }
        return rec;
    case 7:
        p[0] = 8.0f;
        p[1] = 12.0f;
        p[2] = 9.0f;
        p[3] = 0.5f;
        p[4] = 0.19999999f;
        p[5] = 0.29999998f;
        p[6] = 1.156f;
        p[7] = 0.96400005f;
        p[8] = 0.45800003f;
        p[9] = 2.2786f;
        p[10] = 1.9194f;
        p[11] = 1.525f;
        p[12] = 4.0f;
        p[13] = 10.0f;
        p[14] = 16.0f;
        return func_15165B98((u8 *)p, view, -1, 0, arg3, arg4);
    }
    return NULL;
}
