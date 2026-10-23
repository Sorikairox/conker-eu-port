void func_1000DEC4(void);
void func_1000E40C(s32 arg0, s32 arg1);
void func_1000DF68(s32 arg0, s32 arg1, s32 arg2);
s32 func_1000E46C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_10017944(s32 arg0, u32 arg1);
void func_1000E2F4(s32 arg0);
s32 func_1000B548(s32 *arg0);
void func_1000DE1C(s32 arg0, s32 arg1);
void func_1000D96C(s32 arg0, s32 arg1, s32 arg2);
extern s8 D_800422A0;

// Level music block, level header (D_800B0DF0) +0x2C..+0x39.
typedef struct {
    s16 songA;  // +0x0: first song (< 0: none, 0: silence)
    u16 volA;   // +0x2: func_1000E40C
    u16 fadeA;  // +0x4: func_1000E46C
    s16 songB;  // +0x6: second song
    u16 volB;   // +0x8
    u16 fadeB;  // +0xA
    u8  mode;   // +0xC: 0..4, how songs already playing are handled
    u8  unkD;   // +0xD: func_10017944(1, ...)
} LevelMusic;

// Level start: request the level's songs. Songs already playing that the level wants are kept (volume and
// fade set again); the rest are stopped, oldest-slot songs reused for the new ones.
void func_150000B0(void) {
    LevelMusic m;
    s32 playing[3];
    s32 restart;
    s32 count;
    s32 needed;
    s32 excess;
    s32 slot;
    s32 i;
    s32 j;
    s32 *p;

    needed = 0;
    restart = FALSE;
    D_800422A0 = 0;
    if (D_800B0DF0 != NULL) {
        m = *(LevelMusic *) ((u8 *) D_800B0DF0 + 0x2C);
    } else {
        m.mode = 1;
        m.volA = 0;
        m.volB = 0;
        m.unkD = 2;
        m.songA = 0;
        m.songB = 0;
    }
    D_80041F04 = 0;
    D_80041F08 = 0;
    D_80041F0C = 0;

    if (m.songA == 1 && (D_800D2E4C->unk4 & 0x80)) {
        m.fadeA = 0x10;
        m.songA = 0x46;
    }

    switch (m.mode) {
    case 0:
    case 4:
        func_1000DEC4();
        break;
    case 2:
        restart = TRUE;
        func_1000DEC4();
        break;
    case 3:
        restart = TRUE;
        /* fallthrough */
    case 1:
        if (D_800BE9B4 == 2) {
            func_1000DEC4();
        } else if (D_800BE9F8 != 0x22) {
            restart = FALSE;
            m.songA = -1;
            m.songB = -1;
        }
        break;
    }

    count = func_1000B548(playing);
    for (i = count; i < 3; i++) {
        playing[i] = -1;
    }

    // Mode 4: when song B is already playing (and song A is not), it becomes the first song.
    if (m.mode == 4 && m.songB >= 0) {
        for (i = 0; i < 3; i++) {
            if (m.songB == playing[i]) {
                if (m.songA >= 0) {
                    for (j = 0; j < 3; j++) {
                        if (m.songA == playing[j]) {
                            m.songB = 0;
                        }
                    }
                }
                if (m.songB >= 0) {
                    m.songA = m.songB;
                    m.fadeA = m.fadeB;
                    m.volA = m.volB;
                }
            }
        }
        if (m.songB >= 0) {
            m.songB = 0;
        }
    }

    func_1000E2F4(0);

    if (!restart) {
        // Keep the wanted songs that are already playing.
        for (i = 0; i < 3; i++) {
            if (playing[i] == -1) {
                continue;
            }
            if (m.songA == playing[i]) {
                func_1000E46C(m.songA, 0, m.fadeA, 0);
                func_1000E46C(m.songA, 100, m.fadeA ^ 0xFFFF, 0);
                func_1000E40C(m.songA, m.volA);
                func_1000DF68(m.songA, 0x7FFF, 0);
                playing[i] = -1;
                m.songA = -1;
                count--;
            } else if (m.songB == playing[i]) {
                func_1000E46C(m.songB, 0, m.fadeB, 0);
                func_1000E46C(m.songB, 100, m.fadeB ^ 0xFFFF, 0);
                func_1000E40C(m.songB, m.volB);
                func_1000DF68(m.songB, 0x7FFF, 0);
                playing[i] = -1;
                m.songB = -1;
                count--;
            }
        }
    }

    // Stop the songs that are not needed, newest slot first.
    if (m.songA >= 0) {
        needed = 1;
    }
    if (m.songB >= 0) {
        needed++;
    }
    if (count != 0 && needed < count) {
        excess = count - needed;
        if (excess != 0) {
            for (p = &playing[2]; p >= playing && excess != 0; p--) {
                if (*p != -1) {
                    func_1000DE1C(*p, 4);
                    *p = -1;
                    excess--;
                }
            }
        }
    }

    // Start song A in place of the last song still playing (or fresh).
    if (m.songA >= 0) {
        slot = -1;
        for (i = 0; i < 3; i++) {
            if (playing[i] != -1) {
                slot = i;
            }
        }
        if (slot == -1) {
            if (m.songA > 0) {
                func_1000D96C(m.songA, 0, 0);
            }
        } else {
            if (m.songA > 0) {
                func_1000D96C(m.songA, playing[slot], 5);
            } else {
                func_1000DE1C(playing[slot], 4);
            }
            playing[slot] = -1;
        }
        if (m.songA > 0) {
            func_1000E46C(m.songA, 0, m.fadeA, 0);
            func_1000E40C(m.songA, m.volA);
        }
    }

    if (m.songB >= 0) {
        slot = -1;
        for (i = 0; i < 3; i++) {
            if (playing[i] != -1) {
                slot = i;
            }
        }
        if (slot == -1) {
            if (m.songB > 0) {
                func_1000D96C(m.songB, 0, 0);
            }
        } else {
            if (m.songB > 0) {
                func_1000D96C(m.songB, playing[slot], 5);
            } else {
                func_1000DE1C(playing[slot], 4);
            }
            playing[slot] = -1;
        }
        if (m.songB > 0) {
            func_1000E46C(m.songB, 0, m.fadeB, 0);
            func_1000E40C(m.songB, m.volB);
        }
    }

    func_10017944(1, m.unkD);
}
