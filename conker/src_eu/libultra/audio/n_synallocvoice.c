#include <os_internal.h>
#include <ultraerror.h>
#include "n_synthInternals.h"


s32 _allocatePVoice(N_PVoice **pvoice, s16 priority);

s32 n_alSynAllocVoice(N_ALVoice *voice, ALVoiceConfig *vc)
{
    N_PVoice *pvoice = 0;
    ALParam  *update;
    s32      stolen;

    voice->priority      = vc->priority;
    voice->unityPitch    = vc->unityPitch;
    voice->table         = 0;
    voice->fxBus         = vc->fxBus;
    voice->state         = AL_STOPPED;
    voice->pvoice        = 0;
    voice->unk14         = (void *)vc->unk8; /* clientPrivate */

    stolen = _allocatePVoice(&pvoice, vc->priority);

    if (pvoice) { /* if we were able to allocate a voice */
        if (stolen) {
            pvoice->offset = 0x228;
            pvoice->vvoice->pvoice = 0; /* zero stolen voice */

            pvoice->vvoice = voice;
            voice->pvoice  = pvoice;

            /*
             * ramp down stolen voice
             */
            update = __n_allocParam();
            if (update) {
                update->delta      = n_syn->paramSamples;
                update->type       = AL_FILTER_SET_VOLUME;
                update->data.i     = 0;
                update->moredata.i = 0x228 - 0xB8;

                n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
            } else {
                /* _DEBUG build: __osError(ERR_ALSYN_NO_UPDATE, 0); */
            }

            /*
             * stop stolen voice
             */
            update = __n_allocParam();
            if (update) {
                update->delta = n_syn->paramSamples + pvoice->offset;
                update->type  = AL_FILTER_STOP_VOICE;
                update->next  = 0;
                n_alEnvmixerParam(voice->pvoice, AL_FILTER_ADD_UPDATE, update);
            } else {
                /* _DEBUG build: __osError(ERR_ALSYN_NO_UPDATE, 0); */
            }
        } else {
            pvoice->offset = 0;
            pvoice->vvoice = voice;
            voice->pvoice  = pvoice;
            /* Rare: move the voice to its aux bus's list */
            N_AL_UNLINK(&pvoice->unk8);
            N_AL_LINK(&pvoice->unk8, &n_syn->auxBus[vc->fxBus].voices);
            pvoice->dc_table = 0;
        }
    }

    return (pvoice != 0);
}

s32 _allocatePVoice(N_PVoice **pvoice, s16 priority)
{
    ALLink   *dl;
    N_PVoice *pv;
    s32      stolen = 0;

    if ((dl = n_syn->pLameList.next) != 0) { /* check the lame list first */
        *pvoice = (N_PVoice *)dl;
        N_AL_UNLINK(dl);
        N_AL_LINK(dl, &n_syn->pAllocList);
    } else if ((dl = n_syn->pFreeList.next) != 0) { /* from the free list */
        *pvoice = (N_PVoice *)dl;
        N_AL_UNLINK(dl);
        N_AL_LINK(dl, &n_syn->pAllocList);
    } else { /* steal one */
        for (dl = n_syn->pAllocList.next; dl != 0; dl = dl->next) {
            pv = (N_PVoice *)dl;
            /*
             * if it is lower priority and not already stolen, keep it
             * as a candidate for stealing
             */
            if ((pv->vvoice->priority <= priority) && (pv->offset == 0)) {
                *pvoice = pv;
                priority = pv->vvoice->priority;
                stolen = 1;
            }
        }
    }
    return stolen;
}
