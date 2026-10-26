/* P66 runtime checks of port-b P64's jump / idle C and of player_stat_modify (link-time wraps; only cross-TU calls).
 *  ?p66jump=N  obj_jump_swim_glide_update (jump / swim / glide handler, called by obj_state_walk): record 0's buttons, anim id
 *              (+0x84), y (+0x18), y_velocity (+0x20), height (+0x28), in_water (+0xAD), hanging (+0x137), target
 *              speed (+0xC0) before -> after. Logged for the first N calls, every 64th, and for every call where the
 *              buttons, the anim id or the sign of y_velocity change or the record is airborne (+0x28 > 0.5) for the
 *              first 400 such calls; plus the idle-chooser state (ctl +0x58..+0x65, P64 IdleState) when it changes.
 *  ?p66lowg=1  DIAGNOSTIC: g_cur_floor_kind = 1 during calls with A pressed on the floor (reaches P64's low-gravity jump
 *              branches: Z long jump +0x81 = 0x81, y_velocity * 1.4); logged as "[p66] lowg".
 *  ?p66hud=N   player_stat_modify (per-player HUD / status records, game_eu_B2980.c; called by func_150447B0 users,
 *              player_lose_life's restart path, ...): arguments of the first N calls (proves it is the C body). */
#include <stdint.h>
#include "../ultra/pc_mem.h"

int port_flag(const char *name);
void port_log(const char *fmt, ...);
extern unsigned port_frame_count;
extern unsigned char g_objects[]; /* was D_800CC2D0 */

#define REC 0x32C
static float F(const unsigned char *r, int o) { return *(const float *)(r + o); }
static int recno(const void *r) { return (int)(((const unsigned char *)r - g_objects) / REC); } /* was D_800CC2D0 */

static int fj = -1, fh = -1, flg = -1;
extern unsigned char D_800CC69C_[] __asm__("g_cur_floor_kind"); /* was D_800CC69C */

static void idle_state(const unsigned char *ctl, unsigned char *out) {
    int i;
    for (i = 0; i < 14; i++) out[i] = vbe_ld8(ctl + 0x58 + i);
}

void __real_obj_jump_swim_glide_update(void *rec, void *pad);
void __wrap_obj_jump_swim_glide_update(void *rec, void *pad) {
    static unsigned n, air, lastb = 0xFFFF, lastid = 0xFFFF;
    static int lastsign = 9;
    static unsigned char lastidle[14];
    const unsigned char *r = rec;
    unsigned b, id0, id1;
    float y0, vy0, h0;
    int sign;
    if (fj < 0) fj = port_flag("p66jump");
    if (!fj || !rec || recno(rec) != 0) { __real_obj_jump_swim_glide_update(rec, pad); return; }
    n++;
    b = pad ? vbe_ld16(pad) : 0;
    id0 = vbe_ld16(r + 0x84); y0 = F(r, 0x18); vy0 = F(r, 0x20); h0 = F(r, 0x28);
    if (flg < 0) flg = port_flag("p66lowg");
    if (flg && (b & 0x8000) && h0 < 0.5f) {   /* DIAGNOSTIC: g_cur_floor_kind = 1 (P64's "low gravity" test) for this call */
        unsigned char old = vbe_ld8(D_800CC69C_);
        vbe_st8(D_800CC69C_, 1);
        __real_obj_jump_swim_glide_update(rec, pad);
        vbe_st8(D_800CC69C_, old);
        port_log("[p66] lowg call frame %u: D_800CC69C forced 1 (was %d): buttons %04X id %04X -> %04X vy %.2f -> %.2f "
                 "+81 %02X\n", port_frame_count, old, b, id0, vbe_ld16(r + 0x84), vy0, F(r, 0x20), vbe_ld8(r + 0x81));
    } else
        __real_obj_jump_swim_glide_update(rec, pad);
    id1 = vbe_ld16(r + 0x84);
    sign = F(r, 0x20) > 0.01f ? 1 : F(r, 0x20) < -0.01f ? -1 : 0;
    if (n <= (unsigned)fj || n % 64 == 0 || b != lastb || id1 != id0 || id1 != lastid || sign != lastsign ||
        (h0 > 0.5f && ++air <= 400))
        port_log("[p66] jump call %u frame %u: buttons %04X | id %04X -> %04X | y %.2f -> %.2f vy %.2f -> %.2f "
                 "+28 %.2f -> %.2f | water %d hang %d tspeed %.2f +81 %d +83 %d\n",
                 n, port_frame_count, b, id0, id1, y0, F(r, 0x18), vy0, F(r, 0x20), h0, F(r, 0x28),
                 vbe_ld8(r + 0xAD), vbe_ld8(r + 0x137), F(r, 0xC0), vbe_ld8(r + 0x81), vbe_ld8(r + 0x83));
    lastb = b; lastid = id1; lastsign = sign;
    {
        const unsigned char *ctl = *(unsigned char *const *)(r + 0x31C);
        unsigned char st[14];
        int i, ch = 0;
        if (ctl) {
            idle_state(ctl, st);
            for (i = 0; i < 14; i++) ch |= st[i] != lastidle[i];
            if (ch) {
                port_log("[p66] idle state frame %u: active %d delay %d timer %d set %d entry %d recent %d %d %d %d %d "
                         "mode %d count %d\n", port_frame_count, st[0], st[1], st[2] << 8 | st[3], st[4], st[5],
                         st[7], st[8], st[9], st[10], st[11], st[12], st[13]);
                for (i = 0; i < 14; i++) lastidle[i] = st[i];
            }
        }
    }
}

void __real_player_stat_modify(short idx, short field, int value);
void __wrap_player_stat_modify(short idx, short field, int value) {
    static unsigned n;
    if (fh < 0) fh = port_flag("p66hud");
    if (fh && ++n <= (unsigned)fh)
        port_log("[p66] player_stat_modify call %u frame %u: idx %d field %d value %d (C body, game_eu_B2980.c)\n",
                 n, port_frame_count, idx, field, value);
    __real_player_stat_modify(idx, field, value);
}
