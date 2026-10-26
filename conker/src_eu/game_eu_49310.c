#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_8002AE18;
extern u64 D_8002C060;
extern OSMesgQueue D_8003B578;
extern OSTimer D_800BEB00;
/* was func_1501BB20 */
void cont_arm_read_timer(void) {
    if (D_8002AE18 != 0) {
        osSetTimer(&D_800BEB00, (25ULL * D_8002C060) / 1000000ULL, 0, &D_8003B578, (void *)6);
        D_8002AE18 = 0;
    }
}

extern u8 D_8002AE18;
extern OSMesg D_800BEDB0;
extern u8 D_800BEB60;
extern u8 D_800E0FC5;
extern u16 D_800BEB20[4];
extern u16 D_800BEB28[4];
extern u16 D_800BEB30[4];
extern u16 D_800BEB38[4];
extern OSContPad D_800BED38[4];
extern u16 D_800BED50[4];
void demo_input_play_next(void);
void save_process_request(void);

/* Stick dead zone: |v| < 8 -> 0, otherwise move v 7 towards 0. */
#define DEADZONE(v) ((((v) < 0) ? -(v) : (v)) >= 8 ? (v) - (((v) < 0) ? -1 : 1) * 7 : 0)

/* Per-frame controller read: fetch the 4 pads, map them to players, compute the edge masks
 * and apply the stick dead zone. Returns the player input block. */
/* was func_1501BBB8 */
struct14 *cont_read_frame(void) {
    OSContPad pads[4];
    OSContPad *player = (OSContPad *)D_800BE748;
    s32 i;
    s32 nplayers;
    s32 replay;
    u8 idx;

    for (i = 0; i < 4; i++) {
        D_800BEB38[i] = player[i].button;
    }
    osRecvMesg(&D_800BE900, &D_800BEDB0, OS_MESG_BLOCK);
    osContGetReadData(pads);
    save_process_request();
    D_8002AE18 = 1;
    D_800BEB60 = 0;
    for (i = 0; i < 4; i++) {
        if (pads[i].errno != 0) {
            pads[i].button = 0;
            pads[i].stick_x = 0;
            pads[i].stick_y = 0;
        } else {
            D_800BEB60 |= 1 << i;
        }
    }

    nplayers = 4;
    if (D_800BE9F0 != 0x1D) {
        nplayers = D_80090130;
    }
    for (i = 0; i < 4; i++) {
        idx = D_800843F0[i];
        if (idx < 4 && i < nplayers) {
            player[i].stick_x = pads[idx].stick_x;
            player[i].stick_y = pads[idx].stick_y;
            player[i].button = pads[idx].button | D_800BE720[idx];
            D_800BE720[idx] = 0;
        } else {
            player[i].button = 0;
            player[i].stick_x = 0;
            player[i].stick_y = 0;
        }
    }

    for (i = 0; i < 4; i++) {
        D_800BED50[i] = ~D_800BEB28[i] & player[i].button;
        D_800BED38[i].button = player[i].button;
        D_800BEB28[i] = player[i].button;
        D_800BED38[i].stick_x = DEADZONE(player[i].stick_x);
        D_800BED38[i].stick_y = DEADZONE(player[i].stick_y);
    }

    if (D_800E0B94 == 2 || D_800E0FC5 == 2) {
        replay = 1;
        demo_input_play_next();
    } else {
        replay = 0;
    }

    for (i = 0; i < 4; i++) {
        D_800BEB30[i] = ~D_800BEB20[i] & player[i].button;
        D_800BEB20[i] = player[i].button;
        if (replay == 0) {
            player[i].stick_x = DEADZONE(player[i].stick_x);
            player[i].stick_y = DEADZONE(player[i].stick_y);
        }
    }
    return &D_800BE730;
}
#undef DEADZONE
extern f32 D_80096D10;
void rumble_start(u8, f32, f32);
/* was func_1501BFF0 */
void rumble_start_strength(u8 arg0, u8 arg1)
{
  f32 t;
  f32 a;
  f32 b;
  if (arg1 >= 9) {
    arg1 = 8;
  }
  if (arg1 == 8) {
    a = 20.0f;
    b = 0.0f;
  } else if (arg1 == 0) {
    a = 0.0f;
    b = 99.0f;
  } else {
    t = ((f32)(u32)arg1 - 1) * D_80096D10 * 5.0f;
    a = t + 2.0f;
    b = 7.0f - t;
  }
  rumble_start(arg0, a, b);
}

extern u8 D_800BED64[];
extern f32 D_800BED70[];
extern f32 D_800BED80[];
extern f32 D_800BED90[];
extern f32 D_800BEDA0[];
/* was func_1501C0D0 */
void rumble_start(u8 arg0, f32 arg1, f32 arg2) {
    s32 idx;
    idx = D_800843F0[arg0];
    if (idx < 4 && D_800BED64[idx] != 0) {
        D_800BED5C[idx] = 1;
        D_800BED70[idx] = 0.0f;
        D_800BED80[idx] = arg1;
        D_800BED90[idx] = arg2;
        D_800BEDA0[idx] = arg1 + arg2;
    }
}

/* was func_1501C15C */
void rumble_stop(u8 arg0) {
    s32 temp_v0 = D_800843F0[arg0];

    if (temp_v0 < 4) {
        D_800BED5C[temp_v0] = 0;
    }
}

extern s32 D_800BEB80;
extern s32 D_800BED60;
extern s32 D_800BED68;
extern u8 D_800BEEE2;
extern u8 D_800BEEE3;
extern u8 D_eu_800E0E30;

/* was func_1501C1B0 */
void rumble_update(void) {
    f32 *temp_v0_2;
    f32 temp_f2;
    s32 var_s1;
    u8 *temp_s2;
    u8 *temp_s4;
    u8 *temp_s7;
    u8 *var_s3;
    u8 temp_v0;
    u8 var_s0;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;

    var_s3 = D_800BED64;
    var_s1 = 0;
    do {
        if (D_800BE938 != 0) {
            temp_s0 = ((u8 *)&D_800BEB80 + (var_s1 * 0x68));
            if (os_motor_init(&D_800BE900, temp_s0, var_s1) == 0) {
                if (*var_s3 == 0) {
                    *var_s3 = 1;
                    D_800BED5C[var_s1] = 0;
                    ((u8 *)&D_800BED60)[var_s1] = 0;
                    ((u8 *)&D_800BED68)[var_s1] = 0;
                    D_800BED70[var_s1] = 0.0f;
                    D_800BED80[var_s1] = 1.0f;
                    D_800BED90[var_s1] = 1.0f;
                    D_800BEDA0[var_s1] = 2.0f;
                    os_motor_stop(temp_s0);
                }
            } else {
                *var_s3 = 0;
            }
        }
        temp_s4 = &D_800BED5C[var_s1];
        if (*var_s3 != 0) {
            temp_s7 = ((u8 *)&D_800BED60 + var_s1);
            if ((D_800BEEE3 != 0) || (D_eu_800E0E30 != 0)) {
                temp_s0_2 = ((u8 *)&D_800BEB80 + (var_s1 * 0x68));
                os_motor_init(&D_800BE900, temp_s0_2, var_s1);
                os_motor_stop(temp_s0_2);
                ((u8 *)&D_800BED68)[var_s1] = 0;
                *temp_s4 = 0;
            }
            if ((D_800BEAC1 == 0) && (D_800BEAC0 == 0) && (D_800BEEE2 == 0) && (D_800BEEE3 == 0) && (D_eu_800E0E30 == 0)) {
                temp_v0 = *temp_s4;
                switch (temp_v0) {                  /* irregular */
                case 0:
                    if (*temp_s7 == 1) {
                        temp_s0_3 = ((u8 *)&D_800BEB80 + (var_s1 * 0x68));
                        os_motor_init(&D_800BE900, temp_s0_3, var_s1);
                        os_motor_stop(temp_s0_3);
                        ((u8 *)&D_800BED68)[var_s1] = 0;
                    }
                    break;
                case 1:
                    temp_v0_2 = &D_800BED70[var_s1];
                    *temp_v0_2 += D_800BE9A4;
                    temp_f2 = D_800BEDA0[var_s1];
                    temp_s2 = ((u8 *)&D_800BED68 + var_s1);
                    var_s0 = 1;
                    if (temp_f2 < *temp_v0_2) {
                        do {
                            *temp_v0_2 -= temp_f2;
                        } while (temp_f2 < *temp_v0_2);
                    }
                    if (D_800BED80[var_s1] <= *temp_v0_2) {
                        var_s0 = 0;
                    }
                    if (var_s0 != 0) {
                        if (*temp_s2 == 0) {
                            os_motor_start(((u8 *)&D_800BEB80 + (var_s1 * 0x68)));
                        }
                    } else if (*temp_s2 == 1) {
    s32 pad;
                        os_motor_stop(((u8 *)&D_800BEB80 + (var_s1 * 0x68)));
                    }
                    *temp_s2 = var_s0;
                    break;
                }
            }
            *temp_s7 = *temp_s4;
        }
        var_s1 += 1;
        var_s3 += 1;
    } while (var_s1 != 4);
    D_800BE938 = 0;
    D_800BEEE3 = 0;
    D_eu_800E0E30 = 0;
}
/* was func_1501C51C */
void rumble_stop_all(void) {
    u8 i;

    for (i = 0; i < 4; i++) {
        rumble_stop(i);
    }
}

void heap_free(s32);
void save_slot_load(s8);
void save_slot_write(s8);
void save_slot_erase(s8);
void save_config_reset(void);
void save_config_load(void);
void save_config_write(void);
void save_options_load(void);
void save_options_write(void);
s32 eeprom_async_write_step(s32);
s32 game_eeprom_probe(OSMesgQueue *);
extern u8 D_800843F4;
extern s32 D_800BE810;

/* was func_1501C55C */
void save_process_request(void) {
    s8 mode;
    u8 state;

    eeprom_async_write_step(0);
    mode = (s8)D_80082BB4;
    if (mode == 0) {
        return;
    }
    state = D_800843F4;
    if (state != 2) {
        D_800843F4 = game_eeprom_probe(&D_800BE900);
        state = D_800843F4;
        mode = (s8)D_80082BB4;
    }
    if (state != 2) {
        if (mode == 1) {
            save_game_defaults();
        } else if (mode == 4) {
            save_config_reset();
        }
        D_80082BB4 = 0;
        return;
    }
    switch (mode) {
        case 1: save_slot_load((s8)D_800BE3EC); break;
        case 2: save_slot_write((s8)D_800BE3EC); break;
        case 3: save_slot_erase((s8)D_800BE3EC); break;
        case 4: save_config_load(); break;
        case 5: save_config_write(); break;
        case 6: save_options_load(); break;
        case 7: save_options_write(); break;
    }
    D_80082BB4 = 0;
    if (D_800BE810 != 0) {
        heap_free(D_800BE810 - 8);
        D_800BE810 = 0;
    }
}