#ifdef NON_MATCHING
/* Timed effect list (entries made by func_15044C54, head D_800CBE00): per frame each entry with no start delay
 * (+0xE) runs its update hook D_80086220[+0xC](entry) and, when that returns non-zero, the hook D_8008622C[+0xD]
 * (called with no argument set: a0 is whatever the first hook left). The delay counts down by D_800BE9E4
 * (clamped at 0). The lifetime (+4, -1 = forever) counts down too; at <= 0 the entry is unlinked and freed
 * (func_100043B4(entry, 2)). The next pointer is read before the hooks run. */
typedef struct TimedFx {
    struct TimedFx *next;
    s16 life;
    s16 pad6[3];
    u8 update;
    u8 done;
    u8 delay;
} TimedFx;
extern s32 (*D_80086220[])(TimedFx *);
extern void (*D_8008622C[])(void);

void func_15044D18(void) {
    TimedFx *e = (TimedFx *) D_800CBE00;
    TimedFx *prev = NULL;
    TimedFx *next;
    s32 t;

    while (e != NULL) {
        next = e->next;
        if (e->delay == 0) {
            if (D_80086220[e->update](e) != 0) {
                D_8008622C[e->done]();
            }
        } else {
            t = e->delay - D_800BE9E4;
            if (t < 0) {
                t = 0;
            }
            e->delay = t;
        }
        if (e->life == -1) {
            prev = e;
        } else {
            t = e->life - D_800BE9E4;
            if (t > 0) {
                e->life = t;
                prev = e;
            } else {
                if (prev == NULL) {
                    D_800CBE00 = (s32) e->next;
                } else {
                    prev->next = e->next;
                }
                func_100043B4((s32 *) e, 2);
            }
        }
        e = next;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_71E70/func_15044D18.s")
#endif
