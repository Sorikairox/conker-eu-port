void func_15179B70(s32 arg0, s32 arg1);
int func_1517A028(void);
void func_15179A38(void);
void func_1517A084(s32 count);
u16 func_10010F30(s32 arg0, u16 arg1, u8 arg2, s16 arg3, u8 arg4);
void func_100111C8(u16 arg0);
void func_1000F85C(u16 arg0, s16 arg1, s32 arg2);
s32 allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_150ADA20(void);

/* rain_update: per-frame rain state machine (view index arg0; D_800C35EA[arg0] != 0 pauses the timers).
 * D_800DD862 / D_800DD863: random gust timer and strength (after a strong gust (>= 40) a weak one of 20..50 frames,
 * else a strong one of 60..122). D_800DD876 is the state, D_800DD864 the requested mode (func_1517946C),
 * D_800DD874 (US name D_800DD444, s16) the state timer, D_800DD866 the number of drops in the table D_800DD870
 * (300 pointers), D_800DD860 the rain sound.
 * 0 idle: on a request, after 600 frames (or at once for request 4) allocate the drop table, start the sound
 *   (0x6F) and go to 1.
 * 1 starting: add 4 drops per frame (func_15179B70) up to 300, raising the sound volume with the count; at 300 go
 *   to 2.
 * 2 raining: request 1 -> 4; request 0 or 120 frames -> 3 (request 3 keeps the timer counting).
 * 3 stopping: retire 4 drops per frame (func_1517A028), lowering the volume; with no drops left free the table,
 *   stop the sound and go to 0.
 * 4 stop now: retire every drop, go to 3, clear the request.
 * While there are drops: move the rain centre with the camera (func_15179A38) and spawn count / 30 splashes
 * (func_1517A084). */
void func_15179008(s32 arg0) {
    s32 timer;
    s32 i;
    s16 t;

    timer = D_800DD862 - D_800BE9E4;
    if (timer <= 0) {
        if (D_800DD863 < 40) {
            timer = (u32) func_150ADA20() % 31 + 20;
            D_800DD863 = (func_150ADA20() & 0xF) + 0xAA;
        } else {
            timer = (u32) func_150ADA20() % 63 + 60;
            D_800DD863 = (func_150ADA20() & 0xF) + 0x14;
        }
    }
    D_800DD862 = timer;

    switch (D_800DD876) {
        case 0:
            if (D_800DD864 == 0) {
                break;
            }
            t = D_800DD444;
            if (D_800DD864 == 4 || t >= 600) {
                D_800DD870 = allocate_memory(300 * 4, 1, 0, 0);
                for (i = 0; i < 300; i++) {
                    ((s32 *) D_800DD870)[i] = 0;
                }
                if (D_800DD870 != 0) {
                    D_800DD876 = 1;
                    D_800DD444 = 0;
                    D_800DD860 = func_10010F30(0x6F, 200, 0x40, 0, 0x80);
                }
            } else if ((&D_800C35EA)[arg0] == 0) {
                D_800DD444 = t + D_800BE9E4;
            }
            break;
        case 1:
            if (D_800DD866 == 300) {
                D_800DD876 = 2;
                D_800DD444 = 0;
                break;
            }
            for (i = 0; i < 4; i++) {
                if (D_800DD866 != 300) {
                    func_15179B70(1, 1);
                }
            }
            if ((s16) D_800DD444 >= 11 && D_800DD866 < 300) {
                func_1000F85C(D_800DD860, 8, (D_800DD866 << 14) / 300);
                func_1000F85C(D_800DD860, 0x2000, 0);
            }
            D_800DD444 = (s16) D_800DD444 + D_800BE9E4;
            break;
        case 2:
            if (D_800DD864 == 1) {
                D_800DD876 = 4;
                D_800DD444 = D_800DD866;
            } else if (D_800DD864 == 0 || (s16) D_800DD444 >= 120) {
                D_800DD876 = 3;
                D_800DD444 = D_800DD866;
            } else if (D_800DD864 == 3 && (&D_800C35EA)[arg0] == 0) {
                D_800DD444 = (s16) D_800DD444 + D_800BE9E4;
            }
            break;
        case 3:
            if (D_800DD866 == 0) {
                D_800DD876 = 0;
                D_800DD444 = 0;
                func_100111C8(D_800DD860);
                func_10004074((s32 *) D_800DD870);
                D_800DD870 = 0;
                break;
            }
            for (i = 0; i < 4; i++) {
                func_1517A028();
            }
            if ((s16) D_800DD444 != 0) {
                func_1000F85C(D_800DD860, 8, (D_800DD866 << 13) / (s16) D_800DD444);
            }
            break;
        case 4:
            for (i = 0; i < D_800DD866; i++) {
                func_1517A028();
            }
            D_800DD876 = 3;
            D_800DD864 = 0;
            break;
    }
    if (D_800DD866 != 0) {
        func_15179A38();
        func_1517A084(D_800DD866 / 30);
    }
}
