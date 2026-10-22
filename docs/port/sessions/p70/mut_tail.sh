#!/bin/bash
# P70: mutants of func_1503BCAC (one per branch) and func_1503CE88, on reduced setup files.
cd /Users/sorikairo/conker-wt/port
M=docs/port/sessions/p70/mut.sh; S=docs/port/sessions/p70
bash $M func_1503BCAC port_work/p70/bcac.c $S/sbcac_m.txt \
  's/(rec->phase + 180.0f)/(rec->phase + 90.0f)/' \
  's/speed \*= 0.5f;/speed *= 0.25f;/' \
  '0,/b = 23.0f;/s//b = 22.0f;/' \
  's/rec->timer = 60;/rec->timer = 61;/' \
  's/> -17.0f)/> -21.0f)/' \
  's/D_800C4428\[0\] = rec->p\[0\]\[0\] + s;/D_800C4428[0] = rec->p[0][0] - s;/' \
  's/lift = 60.0f - (speed + speed);/lift = 60.0f - speed;/' \
  's/lift_tbl = D_80098B18;/lift_tbl = D_80098AF0;/' \
  's/lift = 60.0f;/lift = 50.0f;/' \
  's/rec->timer = 0;/rec->timer = 1;/' \
  's/\* 5.0f;/* 4.0f;/' \
  's/fabsf(f) > 15.0f/fabsf(f) > 25.0f/' \
  's/rec->timer = 200;/rec->timer = 199;/' \
  's/(30 - rec->fade)/(29 - rec->fade)/' \
  's/f \*= D_80098AD0\[i\];/f *= D_80098AC0[i];/' \
  's/f = 1.0f;$/f = 0.5f;/' \
  's/p1\[1\] = len\[i\] \* dir\[1\] \* obj->y_scale/p1[1] = len[i] * dir[1] * obj->xz_scale/' \
  's/rec->swayAmp = 100.0f;/rec->swayAmp = 90.0f;/' \
  's/JOINT_POS(obj, 24 + i)\[1\];/JOINT_POS(obj, 23 + i)[1];/' \
  's/rec->fade -= D_800BE9E4;/rec->fade -= 1;/'
bash $M func_1503CE88 port_work/p70/ce88_t.c $S/sce88_m.txt \
  's/ax += 1.0f;/ax += 2.0f;/' \
  's/anim\[4\]\[1\] = anim\[3\]\[1\] + /anim[4][1] = anim[2][1] + /' \
  's/by += (anim\[i + 1\]\[1\] - by) \* fade;/by += (anim[i][1] - by) * fade;/' \
  's/rec\[0x4E\] = 30;/rec[0x4E] = 31;/' \
  's/up\[1\] = prev\[1\]\[1\];/up[1] = prev[1][0];/' \
  's/obj->y_scale, obj->xz_scale, ax/obj->xz_scale, obj->xz_scale, ax/'
