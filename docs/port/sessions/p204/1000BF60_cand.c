/* P204 */
// ambient_voice_update_3d: sound-voice handler (D_8002B5xx table, like func_1000C350) for voice channel ch on
// level 0x1D. state: bit 7 = started, bits 0..1 = mode, bits 2..6 = fade counter, bits 8..15 / 16..23 = the last
// pan / volume. First call: plays sound 0x22 (func_1000E40C, 0x5DC0; func_1000DF68 when D_800C35EA is 1). Off level
// 0x1D the voice is stopped (func_10008F24) and the state returned as is. Otherwise three emitter points
// (-351, 0, 407), (-64, 0, 543), (-294, 0, 656) are mixed (func_100114D0): when the first point's volume (0x40 below
// 0x4000, else / 256) or pan differ from the stored ones, the volume of controller 6 / 1 / 0x18 (at least 0x40) and
// the pans of the parts 1..4 (0 centred) are re-sent. When mode differs from D_80041F08: mode 1 fades the counter
// down by D_800BE9E4 / 2 per frame (stopping sound 0x22 at 0, state 0x81) and sets the volume 0xFE0; mode 2 sets the
// state 0xF8, selects music set 4 (func_10011FA0), restarts sound 0x22 and sets the volume 0xFE0. Returns
// the state with the new pan / volume in bits 8..23.
s32 func_1000BF60(s32 state, u8 ch, s32 arg2, s32 arg3) {
    s32 mode = state & 3;
    u32 last = (u32) state >> 8;
    s32 started = FALSE;
    s32 volChanged;
    s32 panChanged;
    u32 pan;
    u32 vol;
    s32 n;

    if (!(state & 0x80)) {
        func_1000E40C(0x22, 0x5DC0);
        if (D_800C35EA == 1) {
            func_1000DF68(0x22, 0x14, 1);
        }
        state = 0x80;
        started = TRUE;
    }
    if (D_800BE9F0 != 0x1D) {
        func_10008F24(ch);
        return state;
    }
    volChanged = FALSE;
    panChanged = FALSE;

    func_100114D0(-0x15F, 0, 0x197, 0x7FFF, 0xBB8, 0x12C, (s32 *) &pan, (s32 *) &vol, NULL);
    if (vol < 0x4000) {
        vol = 0x40;
    } else {
        vol >>= 8;
    }
    if (vol != (last >> 8)) {
        volChanged = TRUE;
        func_1000886C(ch, 6, vol & 0xFF);
    }
    if (pan != (last & 0xFF)) {
        panChanged = TRUE;
        func_10008744(ch, 1, pan & 0x7F);
        func_10008744(ch, 2, pan & 0x7F);
        func_100086FC(ch, 1, (pan >> 7) & 0xFF);
        func_100086FC(ch, 2, (pan >> 7) & 0xFF);
    }
    last = (pan << 8) | (vol << 16);

    func_100114D0(-0x40, 0, 0x21F, 0x7FFF, 0xBB8, 0x12C, (s32 *) &pan, (s32 *) &vol, NULL);
    if (volChanged) {
        if (vol < 0x4000) {
            vol = 0x4000;
        }
        func_1000886C(ch, 1, (vol >> 8) & 0xFF);
    }
    if (panChanged) {
        func_10008744(ch, 0, 0x40);
        func_100086FC(ch, 0, 0);
    }

    func_100114D0(-0x126, 0, 0x290, 0x7FFF, 0xBB8, 0x12C, (s32 *) &pan, (s32 *) &vol, NULL);
    if (volChanged) {
        if (vol < 0x4000) {
            vol = 0x4000;
        }
        func_1000886C(ch, 0x18, (vol >> 8) & 0xFF);
    }
    if (panChanged) {
        func_10008744(ch, 3, pan & 0x7F);
        func_10008744(ch, 4, pan & 0x7F);
        func_100086FC(ch, 3, (pan >> 7) & 0xFF);
        func_100086FC(ch, 4, (pan >> 7) & 0xFF);
    }

    if (mode != D_80041F08) {
        switch (D_80041F08) {
            case 1:
                if (state & 0x7C) {
                    n = (state & 0x7C) - (D_800BE9E4 >> 1) * 4;
                    if (n > 0) {
                        state = n | 0x80;
                    } else {
                        func_1000E704(0x22, 0, 0xFFFF);
                        state = 0x81;
                    }
                }
                func_1000E46C(0x22, 0x64, 0xFE0, 0);
                break;
            case 2:
                state = 0xF8;
                func_10011FA0((s32 *) 4);
                func_1000E704(0x22, 1, 0xFFFF);
                func_1000E46C(0x22, 0, 0xFE0, started);
                break;
        }
    }
    return state | last;
}
