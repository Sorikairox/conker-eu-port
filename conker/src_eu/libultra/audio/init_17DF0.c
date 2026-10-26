#include <n_libaudio.h>


/* was func_10017DF0 */
void n_csp_set_fx_mix_offset_scale(N_ALCSPlayer *csp, f32 arg1, f32 arg2) {
    N_ALEvent event;

    event.type = 25;
    event.msg.unknown0.unk0 = arg1;
    event.msg.unknown0.unk4 = arg2;

    n_alEvtqPostEvent(&csp->evtq, &event, 0, 2);
}

/* was func_10017E4C */
void n_csp_set_chan_fx_bus(N_ALCSPlayer *csp, u8 chan, u8 arg2) {
    N_ALEvent event;

    event.type = 2; // AL_SEQP_MIDI_EVT ?
    /* likely a custom event */
    event.msg.midi.ticks = 0;
    event.msg.midi.status = chan | 0xB0;
    event.msg.midi.byte1 = 92;
    event.msg.midi.byte2 = arg2;

    n_alEvtqPostEvent(&csp->evtq, &event, 0, 2);
}
