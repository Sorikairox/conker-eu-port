#include <ultra64.h>
#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
s32 texture_cache_lookup(s32 id, s32 *outSize, s32 age, s32 addRef);
s32 texture_rom_offset(s32 arg0);


extern u16 g_tint_wobble_phase[]; /* [player * 3 + i]: wobble phase (12 bits, the sine angle is phase >> 4); was D_800DA290 */
extern u8 g_tint_wobble_speed[];  /* [player * 3 + i]: phase speed; was D_800DA2A8 */
extern u8 g_tint_wobble_amp[];  /* [player * 3 + i]: wobble amplitude; was D_800DA2B8 */
extern u8 g_tint_level[];  /* [player * 3 + i]: current level; was D_800DA2C8 */
extern u8 g_tint_default_level[];  /* [i]: default level; was D_800DA2D4 */
extern u8 g_tint_request_level[];  /* [player * 3 + i]: requested level; element 0 != 0 = a request is pending; was D_800DA2D8 */
f32 math_cos_u8(u8);

/* tint_channels_update: per frame for a player whose g_player_views record has +0x5F0 & 1: three colour channels.
 * Each level g_tint_level moves by 2 * step (g_frame_ticks) toward the requested level (g_tint_request_level, when a request is
 * pending, else the default g_tint_default_level); a sine wobble (math_cos_u8(phase >> 4) * amplitude) around it, minus
 * 0x7F, is added to the "up" byte g_tint_prim_rgb when >= 0, else to the "down" byte g_tint_env_rgb (both capped at 0x7F);
 * the phase advances by its speed (mod 0x1000). The request flag is cleared afterwards. */
/* was func_1510D090 */
void tint_channels_update(s32 player) { /* s32: the asm uses a0 as it is (callers pass an s16) */
    s32 step;
    s32 pending;
    s32 i;
    s32 j;
    s32 level;
    s32 target;
    s32 d;
    s32 v;

    if (!(*(s32 *) ((u8 *) g_player_views + player * 0x9A0 + 0x5F0) & 1)) {
        return;
    }
    step = g_frame_ticks * 2;
    pending = g_tint_request_level[player * 3];
    for (i = 0; i < 3; i++) {
        j = player * 3 + i;
        level = g_tint_level[j];
        target = pending ? g_tint_request_level[j] : g_tint_default_level[i];
        d = target - level;
        if (d != 0) {
            if ((d < 0 ? -d : d) < step) {
                level = target;
            } else if (d >= 0) {
                level += step;
            } else {
                level -= step;
            }
            g_tint_level[j] = level;
        }
        v = (s32) (math_cos_u8((g_tint_wobble_phase[j] >> 4) & 0xFF) * g_tint_wobble_amp[j]) + level - 0x7F; /* level not truncated to u8 here (as in the asm) */
        if (v >= 0) {
            g_tint_prim_rgb[j] += v;
        } else {
            g_tint_env_rgb[j] -= v;
        }
        if (g_tint_prim_rgb[j] >= 0x80) {
            g_tint_prim_rgb[j] = 0x7F;
        }
        if (g_tint_env_rgb[j] >= 0x80) {
            g_tint_env_rgb[j] = 0x7F;
        }
        g_tint_wobble_phase[j] = (g_tint_wobble_phase[j] + g_tint_wobble_speed[j]) & 0xFFF;
    }
    g_tint_request_level[player * 3] = 0;
}

/* was func_1510D338 */
Gfx *tint_emit_prim_env_colors(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3) {
    gDPSetPrimColor(gdl++, 0xF2, 0, g_tint_prim_rgb[arg3 * 3], g_tint_prim_rgb[arg3 * 3 + 1], g_tint_prim_rgb[arg3 * 3 + 2], arg1);
    gDPSetEnvColor(gdl++, g_tint_env_rgb[arg3 * 3], g_tint_env_rgb[arg3 * 3 + 1], g_tint_env_rgb[arg3 * 3 + 2], arg2);
    return gdl;
}

s32 allocate_memory(s32, s32, s32, s32);

#define TEXCACHE_MISSING 0x80000000
#define TEXID_COUNT 0x1E54

/* Resolve the texture ids of a model display list (up to G_ENDDL). For each G_SETTIMG (0xFD) whose w1 is
 * a texture id (top byte < 6, segment nibble 0): w1 = id | flags << 22, id = w1 & 0xF03FFFFF. The id is
 * looked up in the texture cache (texture_cache_lookup, with `age` and `addRef`) and w1 becomes the address;
 * flag 1 (0x00400000) points at the 256-colour palette at size - 0x200, flag 2 (0x00800000) at the
 * 16-colour palette at size - 0x20. `skipResolved` leaves w1 alone when its top byte is set.
 * With `outList`, a newly allocated s16 list {n, id_0, ..., id_n-1} of the distinct ids (ascending) is
 * stored there. Returns 1 when every texture was found, 0 if one was missing. */
/* was func_1510D3E0 */
s32 texture_resolve_dl_ids(Gfx *dl, s32 skipResolved, s32 addRef, s32 age, s16 **outList) {
    u8 seen[(TEXID_COUNT + 7) / 8];
    s32 count;
    s32 missing = 0;
    s32 i;
    u32 w1;
    s32 flags;
    s32 id;
    s32 last = 0;
    s32 size;
    s32 bit;
    s32 k;
    s16 *list;

    if (outList != NULL) {
        for (i = 0; i < (s32)sizeof(seen); i++) {
            seen[i] = 0;
        }
        count = 0;
    }
    for (i = 0; (u8)(dl[i].words.w0 >> 24) != 0xDF; i++) {
        if ((u8)(dl[i].words.w0 >> 24) != 0xFD) {
            continue;
        }
        w1 = dl[i].words.w1;
        if (skipResolved && (w1 & 0xFF000000)) {
            continue;
        }
        if ((w1 & 0xFF000000) >= 0x06000000) {
            continue;
        }
        flags = (s32)w1 >> 22;
        id = w1 & 0xF03FFFFF;
        if ((w1 & 0x0F000000) == 0) {
            last = texture_cache_lookup(id, &size, age, addRef);
            dl[i].words.w1 = last;
            /* The original has no bound check here (an id >= TEXID_COUNT, which the cache rejects, would
             * write past the bitmap on the stack). */
            if (outList != NULL && id < TEXID_COUNT && !(seen[id >> 3] & (1 << (id & 7)))) {
                seen[id >> 3] |= 1 << (id & 7);
                count++;
            }
        } else {
            flags = 0;
        }
        if (last == TEXCACHE_MISSING) {
            missing = 1;
        }
        if (flags == 0) {
            continue;
        }
        if (flags & 1) {
            dl[i].words.w1 += size - 0x200;
        } else if (flags & 2) {
            dl[i].words.w1 += size - 0x20;
        }
        dl[i].words.w1 |= (flags & 0x3C) << 22;
    }

    if (outList != NULL) {
        list = (s16 *)allocate_memory((count + 1) * 2, 1, 0, 2);
        *outList = list;
        if (list != NULL) {
            list[0] = count;
            i = 0;
            for (k = 0; i < count; k++) {
                bit = 1 << (k & 7);
                if (seen[k >> 3] & bit) {
                    list[1 + i] = k;
                    i++;
                }
            }
        }
    }
    return missing == 0;
}
#undef TEXCACHE_MISSING
#undef TEXID_COUNT
extern u16 g_texture_rom_sizes[]; /* was D_800920D0 */
extern u16 g_texture_expanded_sizes[]; /* was D_800B8BB8 */
extern s32 g_texture_cache_data[]; /* was D_800B1268 */
extern u8 g_texture_load_cooldown; /* was D_800DC1DC */
s32 heap_alloc_tagged(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 rom_dma_read(s32 devAddr, void *dramAddr, u32 size, s32 arg3);
void heap_free(s16 *);
s32 rzip_inflate(s32, s32 *, u32);

#define TEXCACHE_MISSING 0x80000000

/* Texture cache lookup. Returns the expanded data of texture `id` (g_texture_cache_data[id]), loading it on a miss:
 * DMA the compressed block (ROM offset texture_rom_offset(id), g_texture_rom_sizes[id] bytes) into a temporary buffer,
 * expand it into a g_texture_expanded_sizes[id]-byte buffer. Returns 0x80000000 for a bad id or when out of memory.
 * `*outSize` gets the expanded size; the slot's age is raised to `age`; `addRef` bumps its use count. */
/* was func_1510D66C */
s32 texture_cache_lookup(s32 id, s32 *outSize, s32 age, s32 addRef) {
    s32 *slot;
    u16 len;
    s32 rom;
    s32 skew;
    s32 size;
    s32 tmp;
    s32 dst;
    s32 data;

    if (id < g_texture_cache_dirty_lo) {
        g_texture_cache_dirty_lo = id;
    }
    if (g_texture_cache_dirty_hi < id) {
        g_texture_cache_dirty_hi = id;
    }
    if (id >= 0x1E54 || id < 0) {
        return TEXCACHE_MISSING;
    }
    len = g_texture_rom_sizes[id];
    slot = &g_texture_cache_data[id];
    if (len == 0) {
        *slot = TEXCACHE_MISSING;
    } else if (*slot == -1) {
        g_texture_load_cooldown = 5;
        if (age == 0x3F) {
            age = 0x3E;
        }
        /* DMA needs an even ROM address and a 16-byte multiple length. */
        rom = texture_rom_offset(id);
        if (rom & 1) {
            rom -= 1;
            skew = 1;
        } else {
            skew = 0;
        }
        size = len + skew;
        if (size & 1) {
            size += 1;
        }
        size = (size + 15) & ~15;
        tmp = heap_alloc_tagged(size, 1, 2, 1, 2);
        if (tmp == 0) {
            return TEXCACHE_MISSING;
        }
        rom_dma_read(rom, (void *)tmp, size, 1);
        dst = heap_alloc_tagged(g_texture_expanded_sizes[id], 1, 1, 0, 2);
        if (dst == 0) {
            heap_free((s16 *)tmp);
            return TEXCACHE_MISSING;
        }
        rzip_inflate(tmp + skew, (s32 *)dst, g_mem_scratch_area);
        heap_free((s16 *)tmp);
        *slot = dst;
        g_texture_cache_refs[id] = 0;
    }
    if (outSize != NULL) {
        *outSize = g_texture_expanded_sizes[id];
    }
    data = *slot;
    if (g_texture_cache_ages[id] < age) {
        g_texture_cache_ages[id] = age;
    }
    if (addRef != 0 && g_texture_cache_refs[id] < 0xFF) {
        g_texture_cache_refs[id]++;
    }
    return data;
}
#undef TEXCACHE_MISSING
extern u16 g_texture_rom_sizes[]; /* was D_800920D0 */
extern s32 D_1A3B40;
/* was func_1510D8F4 */
s32 texture_rom_offset(s32 arg0) {
    s32 sum;
    s32 i;

    sum = (s32)&D_1A3B40;
    for (i = 0; i < arg0; i++) {
        sum += g_texture_rom_sizes[i];
    }
    return sum;
}

extern u8 g_texture_load_cooldown; /* was D_800DC1DC */
extern u8 g_texture_cache_age_hold; /* was D_800DA380 */
extern s32 g_texture_cache_freeing_id; /* was D_800DC1E0 */
extern s32 g_texture_cache_data[]; /* was D_800B1268 */
void heap_free(s16 *);
s32 rzip_inflate(s32, s32 *, u32);
void func_150ADC50(void);

/* Texture cache ageing, once per frame. Slots lo..hi (g_texture_cache_dirty_lo..g_texture_cache_dirty_hi) are pending: an age 1..3
 * counts down and frees the slot at 0; flag 0x40 asks for a refresh (re-expand the slot's data in
 * place, free the old buffer). Slots that still need work set the pending range for the next frame. */
/* was func_1510D984 */
void texture_cache_age_tick(void) {
    s32 hi = g_texture_cache_dirty_hi;
    s32 lo;
    s32 i;
    s8 age;
    s32 *slot;
    s32 buf;

    if (hi == -1) {
        return;
    }
    if (g_texture_load_cooldown == 0 && g_texture_cache_age_hold != 0) {
        return;
    }
    if (g_texture_load_cooldown != 0) {
        g_texture_load_cooldown--;
    }
    lo = g_texture_cache_dirty_lo;
    g_texture_cache_dirty_lo = 0xFFFF;
    g_texture_cache_dirty_hi = -1;
    if (lo < 0 || hi >= 0x1E55) {
        g_dbg_crash_marker = 0x0C000046;
        func_150ADC50();
    }
    g_texture_cache_freeing_id = -1;
    for (i = lo; i <= hi; i++) {
        age = g_texture_cache_ages[i];
        if (age == 0) {
            continue;
        }
        if (age < 4) {
            g_texture_cache_ages[i] = age - 1;
            if (g_texture_cache_ages[i] == 0) {
                g_texture_cache_freeing_id = i;
                heap_free((s16 *)g_texture_cache_data[i]);
                g_texture_cache_data[i] = -1;
                continue;
            }
        } else if (age & 0x40) {
            slot = (s32 *)g_texture_cache_data[i];
            buf = slot[0];
            rzip_inflate(buf + slot[1], slot, g_mem_scratch_area);
            heap_free((s16 *)buf);
            g_texture_cache_ages[i] &= ~0x40;
        } else {
            continue;
        }
        if (i < g_texture_cache_dirty_lo) {
            g_texture_cache_dirty_lo = i;
        }
        if (g_texture_cache_dirty_hi < i) {
            g_texture_cache_dirty_hi = i;
        }
    }
    g_texture_cache_freeing_id = -2;
}
/* was func_1510DB88 */
void texture_cache_set_age(s32 arg0, s32 arg1) {
    s8 *p = &g_texture_cache_ages[arg0];
    s8 v = *p;
    if (v != 0) {
        *p = (v & 0x40) | arg1;
    }
}

void texture_unref_age3(s32);
void heap_free(s16 *);
/* was func_1510DBB0 */
void texture_id_list_release(s16 *arg0)
{
  s16 *new_var;
  s16 *q = arg0;
  s16 *p;
  s16 *end;
  s16 n = q[0];
  p = q + 1;
  new_var = p + n; // fakematch: hoists p + n before the guard
  if (n > 0)
  {
    end = new_var;
    do
    {
      texture_unref_age3(*p);
      p++;
    }
    while (end != p);
  }
  heap_free(q);
}

/* was func_1510DC14 */
void texture_unref_age3(s32 arg0) {
    u8 *temp_v0 = &g_texture_cache_refs[arg0];
    if (g_texture_cache_ages[arg0] != 0) {
        if (*temp_v0 != 0) {
            *temp_v0 = *temp_v0 - 1;
            if (*temp_v0 == 0) {
                if (arg0 < g_texture_cache_dirty_lo) {
                    g_texture_cache_dirty_lo = arg0;
                }
                if (g_texture_cache_dirty_hi < arg0) {
                    g_texture_cache_dirty_hi = arg0;
                }
                texture_cache_set_age(arg0, 3);
            }
        }
    }
}

/* was func_1510DCA0 */
void texture_unref_age2(s32 arg0) {
    u8 *temp_v0 = &g_texture_cache_refs[arg0];
    if (g_texture_cache_ages[arg0] != 0) {
        if (*temp_v0 != 0) {
            *temp_v0 = *temp_v0 - 1;
            if (*temp_v0 == 0) {
                if (arg0 < g_texture_cache_dirty_lo) {
                    g_texture_cache_dirty_lo = arg0;
                }
                if (g_texture_cache_dirty_hi < arg0) {
                    g_texture_cache_dirty_hi = arg0;
                }
                texture_cache_set_age(arg0, 2);
            }
        }
    }
}

/* P130 */
extern s32 g_texture_cache_data[];  /* texture cache: expanded data per texture id; was D_800B1268 */
void heap_free(s16 *);  /* free (as the file's other callers) */

// texture_cache_release: drops one reference to texture id (g_texture_cache_refs[id]); when the last one goes and the
// texture is cached (g_texture_cache_ages[id] != 0), frees its data (and first the block its first word points to when
// g_texture_cache_ages[id] & 0x40) and empties the slot (g_texture_cache_data[id] = -1, g_texture_cache_ages[id] = 0).
// s32 with three parameters for game_eu_6AA20.c's prototype (its only caller passes id, id, a u16 and ignores the
// result; the asm reads a0 only and leaves v0 undefined): returns 0. Verified as the void (s32 id) variant.
/* was func_1510DD2C */
s32 texture_cache_release(s32 id, s32 unused1, u16 unused2) {
    s8 state = g_texture_cache_ages[id];

    if (state == 0 || g_texture_cache_refs[id] == 0) {
        return 0;
    }
    if (--g_texture_cache_refs[id] != 0) {
        return 0;
    }
    if (state & 0x40) {
        heap_free(*(s16 **) g_texture_cache_data[id]);
    }
    heap_free((s16 *) g_texture_cache_data[id]);
    g_texture_cache_data[id] = -1;
    g_texture_cache_ages[id] = 0;
    return 0;
}

extern s8 g_segment_override_count; /* was D_800DA2F0 */

/* was func_1510DDE4 */
void segment_override_clear(void) {
    g_segment_override_count = 0;
}

extern u8 g_segment_overrides[]; /* was D_800DA2F8 */

/* was func_1510DDF4 */
void segment_override_add(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p;
    s32 i = (u8)g_segment_override_count;

    if (i < 8) {
        p = g_segment_overrides + i * 16;
        *(s32 *)(p + 0) = arg0;
        *(s32 *)(p + 4) = arg1;
        *(s32 *)(p + 8) = arg2;
        p[0xC] = arg3;
        p[0xD] = arg4;
        g_segment_override_count = i + 1;
    }
}

/* was func_1510DE40 */
u8 *segment_override_emit(u8 *arg0, s32 arg1) {
    s32 var_v0;
    u8 *var_a0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_a2;

    var_a2 = arg0;
    var_a0 = g_segment_overrides;
    var_v0 = 0;
    if ((s32) (u8) g_segment_override_count > 0) {
        do {
            var_v0 += 1;
            if (arg1 == (*(s32 *)((u8 *)var_a0 + 0))) {
                temp_v1 = var_a2;
                var_a2 += 8;
                (*(s32 *)((u8 *)temp_v1 + 0)) = (s32) ((((*(u8 *)((u8 *)var_a0 + 0xC)) * 4) & 0xFFFF) | 0xDB060000);
                (*(s32 *)((u8 *)temp_v1 + 4)) = (s32) (*(s32 *)((u8 *)var_a0 + 4));
                if ((*(s32 *)((u8 *)var_a0 + 8)) != 0) {
                    temp_v1_2 = var_a2;
                    var_a2 += 8;
                    (*(s32 *)((u8 *)temp_v1_2 + 0)) = (s32) ((((*(u8 *)((u8 *)var_a0 + 0xD)) * 4) & 0xFFFF) | 0xDB060000);
                    (*(s32 *)((u8 *)temp_v1_2 + 4)) = (s32) (*(s32 *)((u8 *)var_a0 + 8));
                }
            }
            var_a0 += 0x10;
        } while (var_v0 < (s32) (u8) g_segment_override_count);
    }
    return var_a2;
}