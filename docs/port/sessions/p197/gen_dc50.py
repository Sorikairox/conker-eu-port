# P197: setups for func_1518DC50 character_effect_update (e 0x80410000, owner 0x80420000, matrices 0x80430000,
# scale source 0x80438000, slot objects 0x80450000 + i * 0x200). Real D_8008D980 rows via DIFFTEST_ROMDATA=1.
# Knobs (EU addresses): D_800BE9E4 = 800BEE04 (dt), D_80082FA4 = 80083334 (view), D_800BEDC8 = 800BEDC8.
# jal keys: rng 150ADF00, rand float 150ADF48, sin 15142948, spawn 1513DA94, D_8008D9C8 handlers 1518EBDC / 1518EC44.
import sys, struct
def fb(x): return struct.unpack('>I', struct.pack('>f', x))[0]
E, OWN, MTX, SCL, OBJ = 0x80410000, 0x80420000, 0x80430000, 0x80438000, 0x80450000
# tpl address per (effect, row) for the slot objects' +0x164 (release reads tpl end / life)
TPL = {1: 0x8008ED60, 10: 0x8008F060}
def base():
    return dict(flags=1, owner=OWN, own0=1, id=7, oid=7, time=50, timed=0, onend=-1, effect=10, accum=0.25, live=0,
                mode=4, attach=1, ssrc=0, scale=1.5, pos=(100.0, 0.0, -100.0), vis=0, model=99, variant=0, mtx=MTX,
                view=0, dt=1, slots={}, tpl=0x8008F060, ret='1513DA94=80460000', retf='', opos=(0.0, 0.0, 0.0))
def build(c):
    p = {}
    p[E + 0x10] = c['flags']; p[E + 0x18] = c['owner']
    p[E + 0x1C] = (c['id'] << 24) | (c['time'] & 0xFFFF)
    p[E + 0x20] = (c['timed'] << 24) | ((c['onend'] & 0xFF) << 16) | (c['effect'] << 8)
    p[E + 0x24] = fb(c['accum']); p[E + 0x28] = c['live']
    p[E + 0x2C] = (c['mode'] << 24) | (c['attach'] << 16)
    p[E + 0x30] = SCL if c['ssrc'] else 0; p[E + 0x34] = fb(c['scale'])
    for k in range(3): p[E + 0x38 + 4 * k] = fb(c['pos'][k])
    for i in range(100):
        o = E + 0x48 + i * 0x18
        if i in c['slots']:
            t = c['slots'][i]; ob = OBJ + i * 0x200
            p[o] = ob; p[o + 4] = t & 0xFFFFFFFF
            for k in range(3): p[o + 8 + 4 * k] = fb((1.0, 2.0, -3.0)[k] * (i + 1))
            for k in range(3): p[ob + 0x34 + 4 * k] = fb(c['opos'][k] + i)
            p[ob + 0x58] = 0x100; p[ob + 0x164] = c['tpl']
        else:
            p[o] = 0
    if c['ssrc']: p[SCL + 0x18] = SCL + 0x100; p[SCL + 0x100] = fb(150.0)
    p[OWN] = c['own0']; p[OWN + 0x14] = fb(5.0); p[OWN + 0x18] = fb(60.0); p[OWN + 0x1C] = fb(-7.0)
    p[OWN + 0x38] = c['oid']; p[OWN + 0x74] = c['vis'] << 24; p[OWN + 0x84] = c['model'] << 16
    p[OWN + 0x1C8] = c['variant'] << 24; p[OWN + 0x1D4] = c['mtx']
    p[0x80083334] = c['view']; p[0x800BEE04] = c['dt']; p[0x800BEDC8] = fb(25.0)
    return ','.join('%08X=%08X' % (a, v & 0xFFFFFFFF) for a, v in sorted(p.items()))
R = []
def add(name, **kw):
    c = base(); c.update(kw)
    R.append('%s ! 0=%08X ! %s ! %s ! %s ! ! !' % (name, E, build(c), c['ret'], c['retf']))
SL = {0: 100, 1: 0, 2: -5, 5: 1}
F = '150ADF48=3F000000,15142948=3F3504F3'
# early exits
add('off_live0', flags=0)
add('off_live3', flags=0, live=3, slots=SL)
add('off_live1', flags=0, live=1, slots=SL)
add('own_null', owner=0)
add('own_dead', own0=0)
add('own_id', oid=8)
# timer
add('time_run', timed=1, time=5, dt=1)
add('time_zero', timed=1, time=1, dt=1, slots=SL, live=4)
add('time_end_rm', timed=1, time=0, dt=1, slots=SL, live=4)
add('time_end_h0', timed=1, time=0, dt=1, onend=0, ret='1513DA94=80460000,1518EBDC=0')
add('time_end_h1', timed=1, time=0, dt=1, onend=1, ret='1513DA94=80460000,1518EC44=100', slots=SL, live=4)
add('time_end_h1k', timed=1, time=0, dt=1, onend=1, ret='1513DA94=80460000,1518EC44=1')
# hidden in this view
add('hid_v0', vis=1, slots=SL, live=4)
add('hid_v0_done', vis=1, mode=5)
add('hid_v1', vis=2, view=1, slots=SL, live=4)
add('vis_other', vis=2, view=0, slots=SL, live=4)
# model / hidden rows
for eff, tpl in ((10, 0x8008F060), (1, 0x8008ED60), (4, 0x8008ED60), (2, 0x8008ED60), (7, 0x8008ED60), (0, 0x8008ED60)):
    for model in (99, 15, 2, 50):
        if eff not in (1, 7) and model != 99: continue
        for hid in ('', 'mtx', 'f'):
            kw = dict(effect=eff, model=model, tpl=tpl, slots=SL, live=4, retf=F)
            if hid == 'mtx': kw['mtx'] = 0
            if hid == 'f': kw['vis'] = 0x0F; kw['view'] = 4
            for mode, att in ((8, 0), (4, 1), (4, 2), (2, 2), (2, 1)):
                if (mode, att) not in ((8, 0), (4, 1)) and model not in (99, 50): continue
                add('e%d_m%d%s_md%d_a%d' % (eff, model, hid, mode, att), mode=mode, attach=att, **kw)
# variants, scale source, accumulator / limits
add('var1', effect=1, variant=1, model=2, slots=SL, live=4)
add('var1_hid', effect=1, variant=1, mtx=0, slots=SL, live=4, retf=F)
add('ssrc', ssrc=1, effect=4, slots=SL, live=4, retf=F)
for acc in (0.0, 0.5, -10.0, 60.0):
    for live in (0, 4, 7, 57):
        add('acc%g_l%d' % (acc, live), accum=acc, live=live, slots=SL)
        add('acc%g_l%d_e4' % (acc, live), accum=acc, live=live, slots=SL, effect=4, retf=F)
add('spawn_fail', ret='1513DA94=0', accum=3.0, slots=SL, live=4)
add('spawn_fail_e4', ret='1513DA94=0', accum=3.0, slots=SL, live=4, effect=4)
add('spawn_2nd_fail', ret='1513DA94=80460000;0', accum=3.0, slots=SL, live=4, effect=4, retf=F)
add('full_slots', effect=4, slots={i: 50 for i in range(20)}, live=5, accum=3.0)
add('full_slots_rel', effect=4, slots={i: (50 if i % 2 else -1) for i in range(20)}, live=5, accum=3.0, retf=F)
add('big_dt', dt=30, slots=SL, live=4, effect=4)
add('big_dt_e10', dt=30, slots={i: i for i in range(57)}, live=57, effect=10)
add('opos_far', effect=4, slots=SL, live=4, opos=(-500.0, 900.0, 400.0))
add('opos_near', effect=4, slots=SL, live=4, opos=(99.9, 0.0, -100.1))
add('opos_far_neg', effect=4, slots=SL, live=4, opos=(500.0, 0.0, -900.0))
add('rng0', ret='1513DA94=80460000,150ADF00=0', slots=SL, live=4, effect=1, model=50, accum=2.0)
add('rngff', ret='1513DA94=80460000,150ADF00=FFFFFFFF', slots=SL, live=4, effect=1, model=50, accum=2.0)
add('rng7f', ret='1513DA94=80460000,150ADF00=7F', slots=SL, live=4, effect=4, accum=2.0)
# P201: visibility 0x7 (not 0xF, view bit 3 clear): the matrix rows must be used
add('vis7_e1', vis=7, view=3, effect=1, model=50, slots=SL, live=4, retf=F)
add('vis7_e10', vis=7, view=3, effect=10, slots=SL, live=4, retf=F)
add('vis7_e4', vis=7, view=3, effect=4, slots=SL, live=4, retf=F, mode=8, attach=0)
# P201: model ids >= 0x100 whose low byte is in a list (u16 compare at owner +0x84)
add('e1_m10F', effect=1, model=0x10F, tpl=0x8008ED60, slots=SL, live=4, retf=F)
add('e1_m102', effect=1, model=0x102, tpl=0x8008ED60, slots=SL, live=4, retf=F)
# P201: release velocities just inside the clamps: hidden model (mode 2) -> slot 2 (timer -5) moves to owner
# (5, 60, -7) + (3, 6, -9); prev = opos + 2 -> vel x = 0.42 * 25 = 10.5, vel z = -0.38 * 25 = -9.5
for eff in (10, 4, 1):
    add('vel_edge_e%d' % eff, effect=eff, mtx=0, slots=SL, live=4, retf=F, opos=(5.58, 0.0, -17.62))
    add('vel_edge2_e%d' % eff, effect=eff, mtx=0, slots=SL, live=4, retf=F, opos=(5.62, 0.0, -17.58))
# P201: live slots == max (effect 4 rows: max 7) with the accumulator full; effects 8 / 9 (template 8008F020 is the
# only one with initialiser 1, D_8008D9C0[1])
add('live_eq_max_e4', effect=4, slots={i: 50 for i in range(7)}, live=7, accum=3.0, retf=F)
add('live_eq_max_e4h', effect=4, mtx=0, slots={i: 50 for i in range(7)}, live=7, accum=3.0, retf=F)
add('live_max1_e4', effect=4, slots={i: 50 for i in range(6)}, live=6, accum=3.0, retf=F)
for eff in (8, 9):
    add('e%d_spawn' % eff, effect=eff, tpl=0x8008F020, slots=SL, live=4, accum=3.0, retf=F)
    add('e%d_spawn_h' % eff, effect=eff, tpl=0x8008F020, mtx=0, slots=SL, live=4, accum=3.0, retf=F)
R = R[15:] + R[:15]  # P197: rich setups first (mut.sh stops at the first DIFFER)
open(sys.argv[1], 'w').write('\n'.join(R) + '\n'); print(len(R))
