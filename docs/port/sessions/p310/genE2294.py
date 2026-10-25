#!/usr/bin/env python3
# P310: writes sE2294.txt (setups for func_150E2294, beam_effect_update). obj 80410000 (+0x90 life, +0x94 head,
# +0xA0 / +0xA4 pitch / yaw, +0xA8 speed, +0xAC limit, +0xB0 end, +0xC0, +0xD0 mode, +0xD2 / +0xD4 / +0xD6 timer,
# +0xDA slot, +0xDB, +0xDC followed object, +0xE0 serial, +0xE2 matrix, +0xE3 delay, +0xE4 / +0xF0 offsets, +0xFC,
# +0xFD, +0xFE); followed object 80420000 (+0x3B slot, +0x76 heading, +0x84 serial, +0x127 aim, +0x1D1 tilt,
# +0x1D4 matrices 80440000, +0x31C -> 80430000 (+0x12)). Globals (EU): D_800BE9E4 frames 800BEE04, D_800BE616
# 800BEA36, D_800D9D80 aim records (0x1C) 800D9D80, D_800DC26C 800DC26C, D_800DBE4C 800DC27C, D_800DBE5C 800DC28C
# (-> 80450000), D_800CC2D0 800CC6F0. EU jal keys: func_1516972C 15169C9C, func_150A7E40 150A7E40 (OUTW 4 / 5 / 6),
# func_151EFDD0 151EFDD0 (RET rand), func_150ADDE0 150ADDE0 (RETF), func_15049148 15049438 (OUTA 2),
# func_15048F58 15049248 (OUTA 2), func_150E2030 150E2030, func_10010F88 10011278, func_1505A184 1505A504
# (OUTW 3 / 4 / 5), func_150ACEA0 150ACEA0 (RET, OUTW 6 hit record, 8 / 9 / 10 point), func_1510FE4C 1510FE4C (RET),
# func_150484A0 15048790 (RETF), func_150AD78C 150ADC6C / func_150AD780 150ADC60 (RETF), func_150E1AF0 150E1AF0,
# func_150E4AD0 150E4AD0.
import os, struct
def fb(x): return struct.unpack('>I', struct.pack('>f', x))[0]
def setup(name, life=50, frames=2, follow=True, serial=0x1234, fserial=0x1234, mode=1, delay=0, mtx=True, slot=3,
          fslot=3, aim=2, timer=-5, d4=4, d2=40, fd=1, speed=6.0, limit=0.0, db=1, fe=0, fc=0, head=(10.0, 20.0, 30.0),
          end=(110.0, 70.0, -50.0), c0=500.0, heading=0x2000, h31c=0x0100, tilt=-3, rec=(0x1F00, -3, 50), on616=0,
          rnd=(0x12345, 0x0042, 0x6789B, 0x1001), ray=1, rayhit=0x80460018, count=5, tab=True, fe_obj=None,
          cosv=(0.6, -0.8), sinv=(0.8, 0.28), at=(0.75, -1.25), ddot=1.5):
    a = {0: 0x80410000}
    o = 0x80410000
    pk = {0x800BEE04: frames, 0x800BEA34: on616 << 8, 0x800DC26C: 0x80460000, 0x800DC27C: count,
          0x800DC28C: 0x80450000 if tab else 0, o + 0x90: ((life & 0xFFFF) << 16) | 0x1111,
          o + 0xA0: fb(0.4), o + 0xA4: fb(-1.1), o + 0xA8: fb(speed), o + 0xAC: fb(limit), o + 0xC0: fb(c0),
          o + 0xD0: ((mode & 0xFF) << 24) | 0x00 << 16 | (d2 & 0xFFFF), o + 0xD4: ((d4 & 0xFFFF) << 16) | (timer & 0xFFFF),
          o + 0xD8: 0x5555 << 16 | slot << 8 | db, o + 0xDC: (0x80420000 if follow else 0),
          o + 0xE0: ((serial & 0xFFFF) << 16) | 2 << 8 | delay, o + 0xFC: fc << 24 | fd << 16 | fe << 8,
          0x80420038: fslot, 0x80420074: heading & 0xFFFF, 0x80420084: (fserial & 0xFFFF) << 16,
          0x80420124: aim, 0x804201D0: (tilt & 0xFF) << 16, 0x804201D4: 0x80440000 if mtx else 0, 0x8042031C: 0x80430000,
          0x80430010: h31c & 0xFFFF, 0x80450000: 0x80470000, 0x80450004: 0x80471000, 0x80450008: 0x80472000}
    for i, v in enumerate(head): pk[o + 0x94 + 4 * i] = fb(v)
    for i, v in enumerate(end): pk[o + 0xB0 + 4 * i] = fb(v)
    for i, v in enumerate((1.0, 2.0, 3.0, -4.0, 5.0, 6.0)): pk[o + 0xE4 + 4 * i] = fb(v)
    r = 0x800D9D80 + 2 * 0x1C
    pk[r] = ((rec[0] & 0xFFFF) << 16) | (rec[1] & 0xFF) << 8 | rec[2]
    for i, v in enumerate((-200.0, 33.0, 400.0, 0.0, 1.0, 0.0)): pk[r + 4 + 4 * i] = fb(v)
    ret = '151EFDD0=%s,150ACEA0=%X,1510FE4C=80480000' % (';'.join('%X' % x for x in rnd), ray)
    retf = '150ADDE0=%08X,15048790=%s,150ADC6C=%s,150ADC60=%s' % (fb(ddot), ';'.join('%08X' % fb(x) for x in at),
        ';'.join('%08X' % fb(x) for x in cosv), ';'.join('%08X' % fb(x) for x in sinv))
    outa = '15049438=2:%08X;%08X;%08X,15049248=2:%08X;%08X;%08X' % (fb(0.5), fb(2.5), fb(-1.5), fb(7.0), fb(-8.0), fb(9.5))
    outw = ('150A7E40=4:%08X;%08X/5:%08X;%08X/6:%08X;%08X,1505A504=3:%08X/4:%08X/5:%08X,150ACEA0=6:%08X/8:%08X/9:%08X/10:%08X'
            % (fb(12.0), fb(150.0), fb(22.0), fb(66.0), fb(32.0), fb(-44.0), fb(900.0), fb(-700.0), fb(55.0),
               rayhit, fb(80.0), fb(41.0), fb(-20.0)))
    return '%s ! %s ! %s ! %s ! %s ! %s ! %s !' % (name, ','.join('%d=%X' % kv for kv in a.items()),
        ','.join('%08X=%08X' % kv for kv in sorted(pk.items())), ret, retf, outa, outw)
S = []
def add(n, **k): S.append(setup(n, **k))
# early free / keep
add('base'); add('lifeout', life=1); add('life0', life=2); add('nofollow', follow=False); add('ser_m1', serial=-1, fserial=7)
add('sermis', fserial=0x1235); add('sermis0', follow=False, serial=5, life=1)
# mode 0: straight to motion
add('m0', mode=0, timer=5); add('m0t0', mode=0, timer=0); add('m0neg', mode=0, timer=-3); add('mneg', mode=0x80, delay=1)
# delay / attach
add('delay2', delay=2, timer=40); add('att', delay=0, timer=40); add('att_nof', delay=0, timer=40, follow=False, serial=-1)
add('att_nomtx', delay=0, timer=40, mtx=False); add('att_slot', delay=0, timer=40, fslot=4); add('att_ff', delay=0, timer=40, aim=0xFF)
# timer restart
add('teq', timer=-2, d4=4); add('tlt', timer=-3, d4=4); add('t_nof', follow=False, serial=-1); add('t_nomtx', mtx=False)
add('t_slot', fslot=9); add('fd0', fd=0); add('fd2', fd=2); add('fdff', fd=0xFF); add('w0', speed=0.0)
add('w0r', speed=0.0, rnd=(0x7FFFFFF0, 0x3, 0x5, 0x9))
# aim record path
add('aimmis_h', heading=0x2001); add('aimmis_t', tilt=-4); add('aimmis_t2', tilt=100, heading=0x1FFF, h31c=0xFFFF)
add('aim_on', on616=1); add('aim_fail', rnd=(0x32, 0x9, 0x2)); add('aim_eq', rnd=(0x31, 0x9, 0x2)); add('aim_pass', rnd=(0x5, 0x22, 0x7, 0x2))
add('aim_eq2', rnd=(0x96, 0x9, 0x2)); add('aim_passw', speed=0.0, rnd=(0x10, 0x5, 0x23, 0x6, 0x1)); add('aim_fd0', fd=0); add('aim_fd0f', fd=0, rnd=(1, 99, 2, 3))
add('aim_big', end=(40000.0, -50000.0, 70000.0), rec=(0x1F00, -3, 100)); add('aim_negh', heading=0x0050, h31c=0x0150, rec=(-0x100, -3, 50))
add('aimmis_neg', heading=0x0050, h31c=0x0150, tilt=-128)
# aim 0xFF path
add('ff', aim=0xFF); add('ff_ray', aim=0xFF, fd=0); add('ff_ray0', aim=0xFF, fd=0, ray=0); add('ff_rayw', aim=0xFF, fd=0, speed=0.0)
add('ff_idx0', aim=0xFF, fd=0, rayhit=0x80460000); add('ff_idx4', aim=0xFF, fd=0, rayhit=0x80460030)
add('ff_idx5', aim=0xFF, fd=0, rayhit=0x8046003C); add('ff_idxneg', aim=0xFF, fd=0, rayhit=0x8045FFF4)
add('ff_idxodd', aim=0xFF, fd=0, rayhit=0x8046001F); add('ff_notab', aim=0xFF, fd=0, tab=False)
add('ff_fe', aim=0xFF, fd=0, fe=3, fc=0)
# motion
add('mv_lim', mode=0, timer=5, limit=20.0); add('mv_lim_db0', mode=0, timer=5, limit=20.0, db=0); add('mv_db0', mode=0, timer=5, db=0)
add('mv_near', mode=0, timer=5, limit=20.0, end=(14.0, 22.0, 31.0)); add('mv_near_fc', mode=0, timer=5, limit=20.0, end=(14.0, 22.0, 31.0), fc=7)
add('mv_far', mode=0, timer=5, limit=2.0, speed=1.0, end=(14.0, 22.0, 31.0)); add('mv_lim_c0', mode=0, timer=5, limit=2.0, speed=0.5, c0=1.0)
add('mv_step', mode=0, timer=5, limit=2.0, speed=100.0, fc=3); add('mv_fe1', mode=0, timer=5, fe=1)
add('mv_fe1n', mode=0, timer=5, fe=1, follow=False, serial=-1); add('mv_fe1_2', fe=1, limit=5.0)
add('mv_dir', mode=0, timer=5, cosv=(-0.0, 0.5), sinv=(1.0, -0.5)); add('mv_dir2', mode=0, timer=5, cosv=(0.25, 0.9), sinv=(-0.6, 0.3), db=0)
add('mv_frames', mode=0, timer=5, frames=3, limit=50.0); add('full', fe=1, limit=30.0, fc=5, fd=0, db=0)
# P310 second round (survivor killers, mE2294b.txt)
add('w0ray', speed=0.0, fd=0, rnd=(0x47, 0x9, 0x3)); add('w0ff', speed=0.0, fd=0, aim=0xFF, rnd=(0x47, 0x9))
add('aim_hs', heading=0x0050, h31c=0xFF00, rec=(0x150, -3, 50)); add('aim_hu', heading=0x9000, h31c=0x0100, rec=(-0x7100, -3, 50))
add('mv_vz0', mode=0, timer=5, cosv=(1.0, -0.8), sinv=(0.0, -0.5))
add('mv_eq', mode=0, timer=5, head=(0.0, 0.0, 0.0), end=(3.0, 4.0, 0.0), speed=5.0, frames=1, limit=0.5, c0=1.0, cosv=(0.8, 0.5), sinv=(-0.6, 0.0))
add('mv_dlim', mode=0, timer=5, head=(0.0, 0.0, 0.0), end=(3.0, 4.0, 0.0), speed=5.0, frames=1, limit=1.5, c0=1.0, cosv=(0.8, 0.5), sinv=(-0.6, 0.0))
add('mv_away', mode=0, timer=5, head=(0.0, 0.0, 0.0), end=(3.0, 4.0, 0.0), speed=1.0, frames=1, limit=0.5, cosv=(-0.8, 1.0), sinv=(0.6, 0.0))
L = ['# P310 setups for func_150E2294 (beam_effect_update), generated by genE2294.py'] + S
open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'sE2294.txt'), 'w').write('\n'.join(L) + '\n')
