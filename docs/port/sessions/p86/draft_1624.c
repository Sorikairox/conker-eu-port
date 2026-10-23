/* SfxEnt.unk10 flags used by the update pass */
#define SFX_PLAYING     0x0001 /* unk24 holds a live voice */
#define SFX_REFRESH     0x0002 /* recompute even while playing */
#define SFX_SMOOTH      0x0004 /* pitch ratio follows the distance change (Doppler-like), smoothed */
#define SFX_KEEP        0x0008 /* keep the entry when the voice ends / goes silent */
#define SFX_CALLBACK    0x0010 /* unk14 may adjust the parameters (non-zero: the entry is freed) */
#define SFX_LISTENER    0x0040 /* position relative to listener D_80042308[0] (func_1000A750) */
#define SFX_FREE        0x0080
#define SFX_FIXED_PAN   0x0100 /* pan 0x40, not computed */
#define SFX_MIRROR      0x0200 /* mirrored pan, flips the 0x80 bit */
#define SFX_FX_MASK     0x0C00 /* voice effect mode: 0 = D_80041FD9, 0x400 = 0, else 1 */
#define SFX_SKIP_ONCE   0x1000

/* Updates the sound entries [first, min(*count, end)): drops ended voices, computes volume / pan / pitch from the
 * position (func_100114D0 or the listener-relative func_1000A750), starts a voice for an entry without one
 * (func_10010BE8) or sends the changed parameters to the playing one (func_1000F85C 8 = volume, 4 = pan,
 * 0x100 = pan high bit | slot, 0x11 = pitch ratio). Entries that fall silent are freed (func_1000FE88) or stopped. */
void func_10011624(struct15 *arg0, s32 *count, s32 first, s32 end) {
    SfxEnt *e;
    SfxListener *lis;
    u32 flags;
    u16 voice;
    s32 pan;            /* sp BC */
    u32 vol;            /* sp B4 */
    u32 dist;           /* sp AC */
    s32 pos;            /* sp B0 (only the callback reads it) */
    s32 pitch;          /* sp A8, cents */
    s32 slot;           /* sp A0 */
    u16 sound;          /* sp A6 */
    s32 *panOut;
    s32 hi;
    s32 fx;
    s32 d;
    f32 k;
    union { f32 f; s32 i; } ratio;
    s32 i;

    for (i = first; i < *count && i < end; i++) {
        e = (SfxEnt *) arg0 + i;
        flags = e->unk10;
        if (flags & SFX_FREE) {
            continue;
        }
        if (flags & SFX_SKIP_ONCE) {
            e->unk10 = flags & ~SFX_SKIP_ONCE;
            continue;
        }
        voice = e->unk24;
        if ((flags & SFX_PLAYING) && voice != 0 && func_1000F3D0(voice) == 0) {
            /* the voice has ended */
            flags &= ~SFX_PLAYING;
            voice = 0;
            if (!(flags & SFX_KEEP)) {
                flags |= SFX_FREE;
                e->unk0 = 0;
            }
            e->unk26 = 0;
            e->unk22 = 0;
            e->unk24 = 0;
            e->unk10 = flags;
            e->unk2C = 1.0f;
        }
        if (!(flags & SFX_REFRESH) && voice != 0) {
            e->unk24 = voice;
            e->unk10 = flags;
            continue;
        }
        if (flags & SFX_FIXED_PAN) {
            pan = 0x40;
            panOut = NULL;
        } else {
            panOut = &pan;
        }
        if (flags & SFX_LISTENER) {
            lis = &D_80042308[0];
            pos = func_1000A750(e->unk4, lis->ex, lis->ey, lis->ez, lis->f, lis->x, lis->y, lis->z, e->unk8, e->unkA,
                                &pan, &vol, &dist);
            vol = (e->unkC * vol) >> 15;
        } else {
            pos = func_100114D0(e->unk2, e->unk4, e->unk6, e->unkC, e->unk8, e->unkA, panOut, (s32 *) &vol,
                                (s32 *) &dist);
        }
        if (D_800BEA35 != 0) {
            vol = 0;
        }
        pitch = e->unk20;
        slot = e->unk23;
        sound = e->unk0;
        if ((flags & SFX_CALLBACK) && e->unk14 != NULL) {
            e->unk10 = flags;
            if (e->unk14((struct15 *) e, &pos, &vol, &pan, &pitch, &slot, &sound) != 0) {
                func_1000FE88(arg0, i, count);
                continue;
            }
            voice = e->unk24;
            flags = e->unk10;
        }
        if (sound == 0) {
            e->unk24 = voice;
            e->unk10 = flags;
            continue;
        }
        if (vol == 0) {
            /* silent */
            if (!(flags & SFX_KEEP)) {
                func_1000FE88(arg0, i, count);
                continue;
            }
            if (voice != 0) {
                func_100111C8(voice);
            }
            flags &= ~SFX_PLAYING;
            e->unk24 = 0;
            e->unk10 = flags;
            continue;
        }
        hi = (pan & 0x80) | slot;
        pan &= 0x7F;
        if (flags & SFX_MIRROR) {
            pan = 0x80 - pan;
            if (pan == 0x80) {
                pan = 0x7F;
            }
            hi ^= 0x80;
        }
        ratio.f = alCents2Ratio(pitch);
        if (voice == 0) {
            switch (flags & SFX_FX_MASK) {
                case 0:
                    fx = D_80041FD9;
                    break;
                case 0x400:
                    fx = 0;
                    break;
                default:
                    fx = 1;
                    break;
            }
            voice = func_10010BE8(0, sound, vol, pan, pitch, hi, fx);
            if (voice != 0) {
                flags |= SFX_PLAYING;
                e->unk0 = sound;
            }
        } else {
            if (vol != e->unk26) {
                func_1000F85C(voice, 8, vol);
            }
            if (pan != (e->unk22 & 0x7F)) {
                func_1000F85C(voice, 4, pan);
            }
            if (hi != (e->unk23 | (e->unk22 & 0x80))) {
                func_1000F85C(voice, 0x100, hi);
            }
            if (flags & SFX_SMOOTH) {
                d = (s32) ((e->unk28 - dist) * D_800BE9E4) / 3;
                if (d >= 367) {
                    k = 2.0f;
                } else {
                    k = 367.0f / (f32) (367 - d);
                    if (2.0f < k) {
                        k = 2.0f;
                    } else if (k < 0.5f) {
                        k = 0.5f;
                    }
                }
                ratio.f *= k;
                ratio.f = e->unk2C + (ratio.f - e->unk2C) * 0.3f;
            }
            if (ratio.f != e->unk2C) {
                func_1000F85C(voice, 0x11, ratio.i);
            }
        }
        e->unk28 = dist;
        e->unk26 = vol;
        e->unk22 = pan | hi;
        e->unk23 = slot;
        e->unk2C = ratio.f;
        e->unk24 = voice;
        e->unk10 = flags;
    }
}
