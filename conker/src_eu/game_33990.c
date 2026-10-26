#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150064E0 */
void save_game_defaults(void) {
    s32 i = 0;
    level_state_clear();

    do {
        g_save_level_bits[i++] = 0;
    } while (i < 69);

    g_save_resume_level = 24;
    g_save_play_time = 0;
    g_save_default_flag_2e45 = 1;
}

s32 asset_load(s32 *arg0, s32 arg1, ...);
void os_writeback_dcache(void *, s32); /* osWritebackDCache */
extern u8 *g_save_field_widths;           /* bit widths of the 69 packed save fields (asset 1/7, +8); was D_800BE810 */
extern s32 g_save_stat9; /* was D_800BE804 */

/* save_slot_unpack: reads EEPROM save slot arg0 (block arg0 * 16 + 4, 0x80 bytes into g_save_slot_buf) and checks the
 * checksum (0xCC + sum of bytes 2..0x7F shifted left by index & 3, 16 bits) against the first u16. Bad block:
 * save_game_defaults (defaults) and, if a slot is loaded (g_save_best_slot_score >= 0) while g_save_slot_refresh is set, the 27-byte state
 * at D_800D2E4C is put back. Good block: byte 2 = slot kind (sp+0x7F), bytes 3..6 = a time stamp (big-endian),
 * 27 bytes of D_800D2E4C, 9 bytes of D_800D2E60, g_save_resume_level, D_800BE800, g_save_stat9 (u16, also passed to
 * player_stat_modify(0, 9, .)), g_save_play_time, then the 69 bit fields of g_save_level_bits (u64 each, widths g_save_field_widths, MSB
 * first). While g_save_slot_refresh is set and the kind is < 3, the slot record g_save_slot_summaries[kind] is refreshed when the stamp
 * is newer (count of set bits in D_800D2E4C, g_save_play_time, g_save_resume_level, stamp, slot, g_save_stat9); g_save_best_slot_score keeps the
 * best count (D_800BE7FE = 1 when D_800D2E68 bit 5 is set), otherwise the old D_800D2E4C state is put back.
 * Block 0x34 (slot 3) clears g_save_slot_refresh at the end. */
/* was func_15006590 */
void save_slot_load(s8 arg0) {
    u8 saved[27];   /* sp+0x5C */
    u8 kind;        /* sp+0x7F */
    s32 stamp;      /* sp+0x78 */
    s32 block;      /* sp+0x48 */
    u64 bit;        /* sp+0xA8 */
    u8 *p;
    u8 *rec;
    s32 i, j;
    s32 sum;
    s32 bits;
    u8 mask;
    u8 cur;
    u8 v;

    for (i = 0; i < 27; i++) {
        saved[i] = ((u8 *) D_800D2E4C)[i];
    }
    if (g_save_field_widths == NULL) {
        g_save_field_widths = (u8 *) asset_load(NULL, 1, 7) + 8;
    }
    os_writeback_dcache(g_save_slot_buf, 0x80);
    osInvalDCache(g_save_slot_buf, 0x80);
    block = arg0 * 16 + 4;
    game_eeprom_long_read(&g_si_mesg_queue, block, g_save_slot_buf, 0x80);
    sum = 0xCC;
    for (i = 2; i < 0x80; i++) {
        sum = (sum + (g_save_slot_buf[i] << (i & 3))) & 0xFFFF;
    }
    if (sum != *(u16 *) g_save_slot_buf) {
        save_game_defaults();
        if (g_save_best_slot_score >= 0 && g_save_slot_refresh != 0) {
            for (i = 0; i < 27; i++) {
                ((u8 *) D_800D2E4C)[i] = saved[i];
            }
        }
        if (block == 0x34) {
            g_save_slot_refresh = 0;
        }
        return;
    }

    p = &g_save_slot_buf[2];
    kind = p[0];
    stamp = (p[1] << 24) | (p[2] << 16) | (p[3] << 8) | p[4];
    p += 5;
    for (i = 0; i < 27; i++) {
        ((u8 *) D_800D2E4C)[i] = *p++;
    }
    for (i = 0; i < 9; i++) {
        D_800D2E60[i] = *p++;
    }
    g_save_resume_level = p[0];
    D_800BE800 = p[1];
    g_save_stat9 = p[2] << 8;
    g_save_stat9 = (p[2] << 8) | p[3];
    p += 4;
    player_stat_modify(0, 9, g_save_stat9);
    g_save_play_time = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
    cur = p[4];
    p += 5;
    mask = 0x80;
    for (i = 0; i < 69; i++) {
        g_save_level_bits[i] = 0;
        bit = 1LL << (g_save_field_widths[i] - 1);
        for (j = 0; j < g_save_field_widths[i]; j++) {
            if (cur & mask) {
                g_save_level_bits[i] |= bit;
            }
            if (mask == 1) {
                cur = *p++;
                mask = 0x80;
            } else {
                mask >>= 1;
            }
            bit >>= 1;
        }
    }

    if (g_save_slot_refresh != 0 && kind < 3) {
        g_save_slot_kinds[arg0] = kind;
        rec = (u8 *) &g_save_slot_summaries[kind];
        if (*(s32 *) (rec + 8) < stamp) {
            bits = 0;
            for (i = 0; i < 27; i++) {
                v = ((u8 *) D_800D2E4C)[i];
                for (j = 0; j < 8; j++) {
                    if (v & 1) {
                        bits++;
                    }
                    v >>= 1;
                }
            }
            rec[0xD] = bits;
            *(s32 *) (rec + 0) = g_save_play_time;
            rec[0xC] = (s8) g_save_resume_level;
            *(s32 *) (rec + 8) = stamp;
            rec[0xE] = arg0;
            *(s32 *) (rec + 4) = g_save_stat9;
            if ((u8) bits >= g_save_best_slot_score) {
                g_save_best_slot_score = (u8) bits;
                if (D_800D2E68 & 0x20) {
                    D_800BE7FE = 1;
                }
            } else {
                for (i = 0; i < 27; i++) {
                    ((u8 *) D_800D2E4C)[i] = saved[i];
                }
            }
        } else {
            for (i = 0; i < 27; i++) {
                ((u8 *) D_800D2E4C)[i] = saved[i];
            }
        }
    }
    if (block == 0x34) {
        g_save_slot_refresh = 0;
    }
}
s32 player_stat_get(s16, s32);

/* save_slot_pack: P232. Writes save slot `slot` (record g_save_slot_summaries[slot]): bumps the slot's time stamp (+8, 31 bits)
 * and moves it to the highest EEPROM slot area (0..3) that no live record (+8 >= 0) uses (+0xE). Unless the EEPROM
 * is disabled (g_eeprom_writes_disabled), the area's last block (area * 16 + 0x13) is first overwritten with 0xFE bytes. The
 * 0x80-byte block g_save_slot_buf is the inverse of save_slot_load's layout: u16 checksum, slot, stamp (big-endian), 27
 * bytes of *D_800D2E4C, 9 bytes of D_800D2E60, g_save_resume_level, D_800BE800, g_save_stat9 = player_stat_get(0, 6) (u16),
 * g_save_play_time (u32), then the 69 values of g_save_level_bits packed MSB first with the widths g_save_field_widths (a last partial
 * byte is not stored; the 0x45 bytes after g_save_play_time are cleared first). Checksum = 0xCC + bytes 2..0x7F shifted
 * left by index & 3 (16 bits). Written with eeprom_async_write_start (osEepromLongWrite) to block area * 16 + 4. */
/* was func_15006BEC */
void save_slot_write(s32 slot) { /* the asm uses the whole a0 (callers pass an s8) */
    u8 *rec = (u8 *) &g_save_slot_summaries[slot];
    s32 stamp;
    s32 used;
    s32 area;
    u8 *e;
    u8 *p;
    s32 i;
    s32 j;
    u64 bit;
    u8 cur;
    u8 mask;
    u16 sum;

    stamp = (*(s32 *) (rec + 8) + 1) & 0x7FFFFFFF;
    used = -1;
    for (e = (u8 *) g_save_slot_summaries; e < (u8 *) &g_save_slot_summaries[3]; e += 0x10) {
        if (*(s32 *) (e + 8) >= 0) {
            used &= ~(1 << (s8) e[0xE]);
        }
    }
    area = 0;
    for (i = 0; i < 4; i++) {
        if ((1 << i) & used) {
            area = i;
        }
    }
    rec[0xE] = area;
    *(s32 *) (rec + 8) = stamp;
    if (g_eeprom_writes_disabled == 0) {
        for (i = 0; i < 8; i++) {
            g_save_slot_buf[i] = 0xFE;
        }
        osWritebackDCacheAll();
        game_eeprom_write(&g_si_mesg_queue, area * 16 + 0x13, g_save_slot_buf);
    }
    if (g_save_field_widths == NULL) {
        g_save_field_widths = (u8 *) asset_load(NULL, 1, 7) + 8;
    }
    p = &g_save_slot_buf[2];
    p[0] = slot;
    p[1] = stamp >> 24;
    p[2] = stamp >> 16;
    p[3] = stamp >> 8;
    p[4] = stamp;
    p += 5;
    for (i = 0; i < 27; i++) {
        *p++ = ((u8 *) D_800D2E4C)[i];
    }
    for (i = 0; i < 9; i++) {   /* the asm copies up to D_800D3289 (EU), 9 bytes */
        *p++ = D_800D2E60[i];
    }
    p[0] = g_save_resume_level;
    p[1] = D_800BE800;
    p += 2;
    g_save_stat9 = player_stat_get(0, 6);
    p[0] = (u32) g_save_stat9 >> 8;
    p[1] = g_save_stat9;
    p[2] = (u32) g_save_play_time >> 24;
    p[3] = (u32) g_save_play_time >> 16;
    p[4] = (u32) g_save_play_time >> 8;
    p[5] = g_save_play_time;
    p += 6;
    for (i = 0; i < 69; i++) {
        p[i] = 0;
    }
    cur = 0;
    mask = 0x80;
    for (i = 0; i < 69; i++) {
        bit = 1LL << (g_save_field_widths[i] - 1);
        for (j = 0; j < g_save_field_widths[i]; j++) {
            if (g_save_level_bits[i] & bit) {
                cur |= mask;
            }
            if (mask == 1) {
                *p++ = cur;
                cur = 0;
                mask = 0x80;
            } else {
                mask >>= 1;
            }
            bit >>= 1;
        }
    }
    sum = 0xCC;
    for (i = 2; i < 0x80; i++) {
        sum += g_save_slot_buf[i] << (i & 3);
    }
    *(u16 *) g_save_slot_buf = sum;
    osWritebackDCacheAll();
    if (g_eeprom_writes_disabled == 0) {
        eeprom_async_write_start(&g_si_mesg_queue, area * 16 + 4, g_save_slot_buf, 0x80);
    }
}
/* was func_1500707C */
void save_slot_erase(s32 arg0) {
    s32 temp_v0;
    s32 var_s0;
    s32 var_s0_2;
    s8 *var_s2;
    u8 *temp_t6;

    var_s0 = 0;
    do {
        temp_t6 = &g_save_slot_buf[var_s0];
        var_s0 += 1;
        *temp_t6 = 0xFF;
    } while (var_s0 < 8);
    osWritebackDCacheAll();
    var_s2 = g_save_slot_kinds;
    var_s0_2 = 0;
    if (g_eeprom_writes_disabled == 0) {
        do {
            temp_v0 = (var_s0_2 * 0x10) + 4;
            if (arg0 == *var_s2) {
                game_eeprom_write(&g_si_mesg_queue, temp_v0 & 0xFF, g_save_slot_buf);
                game_eeprom_write(&g_si_mesg_queue, (temp_v0 + 1) & 0xFF, g_save_slot_buf);
            }
            var_s0_2 += 1;
            var_s2 += 1;
        } while (var_s0_2 != 4);
    }
}
extern u8 *D_80082F4C; /* -> g_save_config_data0: the ten 10-byte records of the save data; was D_800BE712 */

// save_data_reset: clears the save data g_save_config (0x68 bytes) and gives its ten records their defaults: bytes
// +1 / +2 / +3 / +4 = 3 / 10 / 2 / 1, +9 = 0 and per record (asm jump table jtbl_80095DB0) +5 = 3 (records 0, 8,
// 9), 5 (1, 2) or 20 (5, 7), record 5 also +2 = 0; records 3, 4, 6 keep +5 = 0. Takes no arguments (the C caller
// save_config_load used to pass two that the asm never reads).
/* was func_15007168 */
void save_config_reset(void) {
    u8 *p;
    u8 *rec;
    s32 i;

    for (p = (u8 *) &g_save_config; p < (u8 *) &g_save_config + 0x68; p++) {
        *p = 0;
    }
    for (i = 0; i < 10; i++) {
        rec = D_80082F4C + i * 10;
        rec[1] = 3;
        rec[3] = 2;
        rec[4] = 1;
        rec[2] = 10;
        switch (i) {
            case 0:
            case 8:
            case 9:
                rec[5] = 3;
                break;
            case 1:
            case 2:
                rec[5] = 5;
                break;
            case 5:
                rec[5] = 20;
                rec[2] = 0;
                break;
            case 7:
                rec[5] = 20;
                break;
        }
        rec[9] = 0;
    }
}

/* was func_1500727C */
void save_config_load(void) {
    s32 temp_t9;
    s32 var_v0;
    s32 var_v1;
    u8 *var_a0;

    game_eeprom_long_read(&g_si_mesg_queue, 0x44U, &g_save_config, 0x70);
    var_a0 = g_save_config_data_rest;
    var_v0 = ((g_save_config_data0 * 4) + 0xCC + (g_save_config_data1 * 8)) & 0xFFFF;
    var_v1 = 4;
    do {
        temp_t9 = (var_v0 + ((*(u8 *)((u8 *)var_a0 + 0)) << (var_v1 & 3)) + ((*(u8 *)((u8 *)var_a0 + 1)) << ((var_v1 + 1) & 3)) + ((*(u8 *)((u8 *)var_a0 + 2)) << ((var_v1 + 2) & 3)) + ((*(u8 *)((u8 *)var_a0 + 3)) << ((var_v1 + 3) & 3))) & 0xFFFF;
        var_v1 += 4;
        var_v0 = temp_t9;
        var_a0 += 4;
    } while (var_v1 != 0x68);
    if (temp_t9 != g_save_config.checksum) {
        save_config_reset();
    }
}
/* was func_15007360 */
void save_config_write(void) {
    s32 sp18;
    s32 var_v1;
    u16 temp_t9;
    u16 var_v0;
    u8 *var_a0;

    var_a0 = g_save_config_data_rest;
    var_v0 = ((g_save_config_data0 * 4) + 0xCC + (g_save_config_data1 * 8)) & 0xFFFF;
    var_v1 = 4;
    do {
        temp_t9 = (var_v0 + ((*(u8 *)((u8 *)var_a0 + 0)) << (var_v1 & 3)) + ((*(u8 *)((u8 *)var_a0 + 1)) << ((var_v1 + 1) & 3)) + ((*(u8 *)((u8 *)var_a0 + 2)) << ((var_v1 + 2) & 3)) + ((*(u8 *)((u8 *)var_a0 + 3)) << ((var_v1 + 3) & 3))) & 0xFFFF;
        var_v1 += 4;
        var_v0 = temp_t9;
        var_a0 += 4;
    } while (var_v1 != 0x68);
    g_save_config.checksum = temp_t9;
    if (g_eeprom_writes_disabled == 0) {
        sp18 = eeprom_async_write_start(&g_si_mesg_queue, 0x44U, &g_save_config, 0x70);
    }
}
void settings_clamp_to_range(void); /* P85: takes no arguments (the asm reads none) */
void menu_settings_apply_checked(void);
extern u8 g_save_slot_buf_body; /* was D_800BE77A */
extern s32 g_save_options_end; /* was D_800E102C */

/* was func_15007440 */
void save_options_load(void) {
    s32 temp_t7;
    s32 temp_t9;
    s32 var_a0;
    s32 var_v0;
    s8 *var_v0_2;
    s8 *var_v0_3;
    s8 temp_a1;
    u8 *var_v1;
    u8 *var_v1_2;
    u8 temp_t1;
    u8 temp_t2;
    u8 temp_t3;
    u8 temp_t4;

    game_eeprom_long_read(&g_si_mesg_queue, 0U, g_save_slot_buf, 0x20);
    var_v0 = 0xCC;
    var_v1 = &g_save_slot_buf_body;
    var_a0 = 2;
    do {
        temp_t7 = var_a0 & 3;
        var_a0 += 1;
        temp_t9 = (var_v0 + (*var_v1 << temp_t7)) & 0xFFFF;
        var_v0 = temp_t9;
        var_v1 += 1;
    } while (var_a0 < 0x1E);
    temp_a1 = (*(s8 *)((u8 *)D_800E1010 + 0x10));
    if (temp_t9 != *(u16 *)g_save_slot_buf) {   /* P18: the asm reads a halfword (lhu) */
        var_v0_2 = D_800E1010;
        do {
            var_v0_2 += 4;
            (*(s8 *)((u8 *)var_v0_2 + -4)) = -1;
            (*(s8 *)((u8 *)var_v0_2 + -3)) = -1;
            (*(s8 *)((u8 *)var_v0_2 + -2)) = -1;
            (*(s8 *)((u8 *)var_v0_2 + -1)) = -1;
        } while ((s32)var_v0_2 != (s32)&g_save_options_end);
    } else {
        var_v0_3 = D_800E1010;
        var_v1_2 = g_save_slot_buf;
        do {
            temp_t1 = (*(u8 *)((u8 *)var_v1_2 + 2));
            temp_t2 = (*(u8 *)((u8 *)var_v1_2 + 3));
            temp_t3 = (*(u8 *)((u8 *)var_v1_2 + 4));
            temp_t4 = (*(u8 *)((u8 *)var_v1_2 + 5));
            var_v0_3 += 4;
            var_v1_2 += 4;
            (*(u8 *)((u8 *)var_v0_3 + -4)) = temp_t1;
            (*(u8 *)((u8 *)var_v0_3 + -3)) = temp_t2;
            (*(u8 *)((u8 *)var_v0_3 + -2)) = temp_t3;
            (*(u8 *)((u8 *)var_v0_3 + -1)) = temp_t4;
        } while ((s32)var_v0_3 != (s32)&g_save_options_end);
    }
    (*(s8 *)((u8 *)D_800E1010 + 0x10)) = temp_a1;
    settings_clamp_to_range();
    menu_settings_apply_checked();
    D_800901D0 = 1;
}
// save_options_write: copies the 0x1C option bytes D_800E1010..g_save_options_end to g_save_slot_buf + 2, stores their checksum
// (0xCC + sum of byte i << (i & 3) over bytes 2..29, 16 bits) in the first halfword and, unless EEPROM writes are
// off (g_eeprom_writes_disabled), writes the 0x20-byte block to EEPROM block 0 (eeprom_async_write_start = osEepromLongWrite).
/* was func_15007558 */
void save_options_write(void) {
    s8 *src;
    u8 *dst = &g_save_slot_buf[2];
    u16 sum;
    s32 i;

    for (src = D_800E1010; (u8 *)src < (u8 *)&g_save_options_end; src++) {
        *dst++ = *src;
    }
    sum = 0xCC;
    for (i = 2; i < 30; i++) {
        sum += g_save_slot_buf[i] << (i & 3);
    }
    *(u16 *)g_save_slot_buf = sum;
    if (g_eeprom_writes_disabled == 0) {
        eeprom_async_write_start(&g_si_mesg_queue, 0, g_save_slot_buf, 0x20);
    }
}

/* was func_15007644 */
void controller_init_hook_noop(void) {
}

/* was func_1500764C */
void save_request_options_load(void) {
    g_save_request_kind = (u8)6;
    g_save_request_slot = (u8)0;
}

/* was func_15007668 */
void save_request_options_write(void) {
    g_save_request_kind = (u8)7;
    g_save_request_slot = (u8)0;
}

/* was func_15007684 */
void save_request_config_load(void) {
    g_save_request_kind = (u8)4;
    g_save_request_slot = (u8)0;
}

/* was func_150076A0 */
void save_request_config_write(void) {
    g_save_request_kind = (u8)5;
    g_save_request_slot = (u8)0;
}

/* was func_150076BC */
void save_request_slot_load(s32 arg0) {
    if (arg0 < 0) {
        save_game_defaults();
    }
    if ((arg0 >= 0) && (arg0 < 4) && (D_800BE616 == 0)) {
        g_save_request_kind = (u8)1;
        g_save_request_slot = arg0;
    }
}

/* was func_15007718 */
void save_request_slot_write(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 3) && (D_800BE616 == 0)) {
        g_save_request_kind = (u8)2;
        g_save_request_slot = arg0;
    }
}

/* was func_15007750 */
void save_request_slot_erase(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 3)) {
        g_save_request_kind = (u8)3;
        g_save_request_slot = arg0;
    }
}

// save_slots_reset: marks the three save-slot summaries g_save_slot_summaries empty (+8 = -1, +0xE = -1), clears the current slot
// g_save_best_slot_score / D_800BE7FE, sets g_save_slot_refresh, clears the 27 bytes at D_800D2E4C (pointer) and the 9 save bits
// D_800D2E60, and sets the four bytes g_save_slot_kinds[0..3] to -1. Mode 3 (menu) calls it on its first frame.
/* was func_15007778 */
void save_slots_reset(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        g_save_slot_summaries[i].unk8 = -1;
    }
    for (i = 0; i < 3; i++) {
        g_save_slot_summaries[i].unkE = -1;
    }
    g_save_best_slot_score = -1;
    D_800BE7FE = 0;
    g_save_slot_refresh = 1;
    for (i = 0; i < 0x1B; i++) {
        ((u8 *) D_800D2E4C)[i] = 0;
    }
    for (i = 0; i < 9; i++) {
        D_800D2E60[i] = 0;
    }
    g_save_slot_kinds[3] = -1;
    g_save_slot_kinds[2] = -1;
    g_save_slot_kinds[1] = -1;
    g_save_slot_kinds[0] = -1;
}
// NON-MATCHING: should probably start over..
// void save_slots_reset(void) {
//     s32 phi_v0;
//
//     D_800BE3F8->unk8 = -1;
//     D_800BE3F8->unk18 = -1;
//     D_800BE3F8->unk28 = -1;
//     D_800BE3F8->unkE = -1;
//     D_800BE3F8->unk1E = -1;
//     D_800BE3F8->unk2E = -1;
//     D_800BE3DC = -1;
//     D_80082BC0 = 1;
//     D_800BE3DE = 0;
//
//     phi_v0 = 0;
//     do {
//         ((u8*)D_800D2E4C)[phi_v0++] = 0;
//     } while (phi_v0 < 27);
//
//     for (phi_v0 = 0; phi_v0 < 9; phi_v0++) {
//         D_800D2E60[phi_v0] = 0;
//     }
//
//     D_800BE3DB = -1;
//     D_800BE3DA = -1;
//     D_800BE3D9 = -1;
//     D_800BE3D8 = -1;
// }
