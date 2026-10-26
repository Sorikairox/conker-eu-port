#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// context_action_set: offers the context action `action` to the player obj (live, +0x127 != 0xFF) for slot 0 (B
// button, player +0x31C byte +0x74) or slot != 0 (+0x75, with +0x7A = the g_level_zones hotspot index of target, 0x34-byte
// entries); a slot whose bit 7 is set is locked. Actions 0x2B / 0x2C remember the hotspot in g_hint_hotspot and show as
// 0x2A; other actions known to hint_action_has_hint are recorded in g_hint_action and show as 0x1A until their g_hints_seen bit is
// set (first use). arg4 is not used (P195).
s32 hint_action_has_hint(s32 arg0);
extern u8 *g_hint_hotspot; /* was D_800D1DBC */

/* was func_15080900 */
void context_action_set(struct127 *obj, u8 *target, s32 slot, s32 action, s32 arg4) {
    u8 *ctl;

    if (obj == NULL || *(s32 *) obj == 0 || ((u8 *) obj)[0x127] == 0xFF) {
        return;
    }
    if (action == 0x2B || action == 0x2C) {
        g_hint_action = action;
        g_hint_hotspot = target;
        action = 0x2A;
    } else if (hint_action_has_hint(action) != 0) {
        g_hint_action = action;
        if (!(g_hints_seen[action >> 3] & (1 << (action & 7)))) {
            action = 0x1A;
        }
    }
    ctl = *(u8 **) ((u8 *) obj + 0x31C);
    if (slot == 0) {
        if (!(ctl[0x74] & 0x80)) {
            ctl[0x74] = action;
        }
    } else if (!(ctl[0x75] & 0x80)) {
        ctl[0x75] = action;
        (*(u8 **) ((u8 *) obj + 0x31C))[0x7A] = (target - g_level_zones) / 0x34;
    }
}

/* was func_15080A20 */
void context_action_lock(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg2 != 0) {
        arg2 |= 0x80;
    }
    if (arg1 == 0) {
        (*(u8 **)((u8 *)&g_objects_state + arg0 * 0x32C))[0x74] = arg2;
        return;
    }
    (*(u8 **)((u8 *)&g_objects_state + arg0 * 0x32C))[0x75] = arg2;
}

/* was func_15080AA8 */
void context_action_clear(s32 arg0) {
    struct127 *p;
    u8 b;
    p = &g_objects[arg0];
    if ((p->unk31C->pad6C[8] != 0) && (!(p->unk31C->pad6C[8] & 0x80))) {
        p->unk31C->pad6C[8] = 0;
    }
    b = p->unk31C->unk75;
    if ((b != 0) && (!(b & 0x80))) {
        p->unk31C->unk75 = 0;
    }
}

/* was func_15080B18 */
void flag_bit_position(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg2 = 1 << (arg0 & 7);
    *arg1 = arg0 >> 3;
}

/* was func_15080B38 */
s32 hint_action_has_hint(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    flag_bit_position(arg0, &sp1C, &sp18);
    if (D_eu_800BE9A0[sp1C] & sp18) {
        return 1;
    }
    return 0;
}

/* was func_15080B84 */
void hint_play_next_voice(void) {
    u16 new_var; // fakematch: permuter temp
    u16 *q;
    u16 temp_a0;
    q = (u16 *) g_hint_voice_queue;
    if (q != 0) {
        if (((unsigned short) g_hint_voice_pos) != g_hint_voice_count) {
            temp_a0 = q[g_hint_voice_pos];
            new_var = temp_a0; // fakematch
            if (0 != temp_a0) {
                mp3_voice_play((s32) new_var, 0x7FFF, 0x40);
            }
            g_hint_voice_pos++;
        }
    }
}

/* was func_15080BF4 */
void hint_text_event_cb(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 == 0x20) {
        hint_play_next_voice();
    }
}

s32 allocate_memory(s32, s32, s32, s32);
s32 asset_load_with_subfiles(s32, s32, s32, s32, s32, s32, s32);
s32 text_box_open(s32, s32, s32, void (*)(s32, s32, s32), s32 *, s32);
s32 strlen(u8 *);
extern u8 g_text_bank_lang; /* was D_800BEECB */
extern u8 g_chapter_replay; /* was D_800D3260 */

/* was func_15080C28 */
void hint_box_open(s32 arg0) {
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp30;
    u32 sp2C;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 var_t3;
    u32 temp_t6;

    if (arg0 == 0) {
        if (!(g_hints_seen_b8 & 0x10)) {
            sp40 = 1;
        } else {
            goto block_4;
        }
    } else {
block_4:
        sp40 = 0;
    }
    temp_v0 = asset_load_with_subfiles(0, 0, 0, 3, 0x1A, (s32) g_text_bank_lang, (s32) g_hint_action);
    g_hint_text_asset = temp_v0;
    if (temp_v0 != 0) {
        g_hint_voice_pos = 0;
        g_hint_voice_queue = (*(s32 *)((u8 *)temp_v0 + 8));
        g_hint_voice_count = (u8) ((u32) (*(u32 *)((u8 *)temp_v0 + 0xC)) >> 1);
        if (sp40 != 0) {
            temp_v0_2 = asset_load_with_subfiles(0, 0, 0, 3, 0x1A, (s32) g_text_bank_lang, 0x43);
            g_hint_intro_asset = temp_v0_2;
            if (g_hint_text_asset != 0) {
                sp3C = strlen(*(s32 *)temp_v0_2) + 1;
                temp_v0_3 = strlen((*(u8 **)((u8 *)g_hint_text_asset + 0)));
                sp38 = temp_v0_3 + 1;
                temp_v0_4 = allocate_memory(sp3C + temp_v0_3 + 2, 1, 0, 0);
                g_hint_text_buf = temp_v0_4;
                bcopy((*(u8 **)((u8 *)g_hint_intro_asset + 0)), (u8 *) temp_v0_4, sp3C);
                (*(s8 *)((u8 *)((g_hint_text_buf + sp3C)) + -1)) = 0xBD;
                bcopy((*(u8 **)((u8 *)g_hint_text_asset + 0)), g_hint_text_buf + sp3C, sp38);
                temp_t6 = (u32) (*(u32 *)((u8 *)g_hint_intro_asset + 0xC)) >> 1;
                temp_v1 = g_hint_voice_count + temp_t6;
                sp30 = temp_v1;
                sp2C = temp_t6;
                temp_v0_5 = allocate_memory(temp_v1 * 2, 1, 0, 0);
                g_hint_voice_queue = temp_v0_5;
                bcopy((*(u8 **)((u8 *)g_hint_intro_asset + 8)), (u8 *) temp_v0_5, sp2C * 2);
                bcopy((*(u8 **)((u8 *)g_hint_text_asset + 8)), (temp_t6 * 2) + g_hint_voice_queue, g_hint_voice_count * 2);
                g_hint_voice_count = (u8) sp30;
                goto block_10;
            }
        } else {
            g_hint_intro_asset = 0;
block_10:
            g_hint_box_open = 1;
            if (sp40 != 0) {
                var_t3 = g_hint_text_buf;
            } else {
                var_t3 = (s32) (*(u8 **)((u8 *)g_hint_text_asset + 0));
            }
            (*(s32 *)((u8 *)g_hint_box_params + 0)) = 0x38013;
            if (((sp40 != 0) || (arg0 != 0) || !(g_hints_seen[(s32) g_hint_action >> 3] & (1 << (g_hint_action & 7)))) && (g_chapter_replay == 0)) {
                (*(s32 *)((u8 *)g_hint_box_params + 0)) |= 0x60;
            }
            if ((arg0 != 0) || (g_hint_action == 0x42)) {
                (*(s32 *)((u8 *)g_hint_box_params + 0)) |= 0x80;
            }
            g_hint_box_params[1] = var_t3;
            (*(s16 *)((u8 *)g_hint_box_params + 0x26)) = 0x64;
            (*(s8 *)((u8 *)g_hint_box_params + 8)) = 1;
            (*(s16 *)((u8 *)g_hint_box_params + 0x24)) = 0;
            (*(s8 *)((u8 *)g_hint_box_params + 0x2B)) = 0;
            g_hint_box_params[6] = (s32) &g_hint_box_x;
            g_hint_box_params[7] = (s32) &g_hint_box_y;
            g_hint_box_params[8] = (s32) &g_hint_box_scale;
            (*(s8 *)((u8 *)g_hint_box_params + 0x28)) = 0xFF;
            (*(s8 *)((u8 *)g_hint_box_params + 0x29)) = 0xFF;
            (*(s8 *)((u8 *)g_hint_box_params + 0x2A)) = 0xFF;
            g_hint_box_x = 78.0f;
            g_hint_box_y = 48.0f;
            g_hint_box_scale = 9.0f;
            temp_v0_6 = text_box_open(0, 0, 0, hint_text_event_cb, g_hint_box_params, 0);
            g_hint_text_box = temp_v0_6;
            (*(s8 *)((u8 *)temp_v0_6 + 0x14)) = 0;
        }
    }
}
// the definition is void (asm: v0 is not a result); one signature for wasm
void heap_free(s32);
void text_box_close_now(s32);
void mp3_stream_set_volume(s32, s32);

/* was func_15080FE8 */
void hint_box_close(void) {
    s32 r;
    g_hint_box_open = 0;
    text_box_close_now(g_hint_text_box);
    heap_free(g_hint_text_asset);
    if (g_hint_intro_asset != 0) {
        r = g_hint_intro_asset;
        heap_free(r);
        heap_free(g_hint_text_buf);
        heap_free(g_hint_voice_queue);
        g_hint_intro_asset = 0;
    }
    mp3_stream_set_volume(0, 0x5622);
}

extern u8 *g_hint_hotspot; /* was D_800D1DBC */

/* was func_15081064 */
void hint_box_update(void) {
    if ((g_hint_box_open != 0) && ((*(u8 *)((u8 *)g_hint_text_box + 0x15)) == 0)) {
        hint_box_close();
        if ((g_level_id != 0x29) && (g_level_id != 0x2E)) {
            (*(u8 *)((u8 *)g_hints_seen + 8)) = (u8) ((*(u8 *)((u8 *)g_hints_seen + 8)) | 0x10);
        }
        if (g_hint_hotspot != NULL) {
            (*(s8 *)((u8 *)g_hint_hotspot + 0x14)) = 1;
            g_hint_hotspot = NULL;
        }
    }
}

/* was func_150810F4 */
s32 hint_box_is_closed(void) {
    if (g_hint_box_open == 0) {
        return 1;
    }
    return 0;
}
