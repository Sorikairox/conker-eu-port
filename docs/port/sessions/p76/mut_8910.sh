#!/bin/bash
# P76: func_15038910 mutants on s8910.txt (mutfast.sh) with the matrix ARGMEM keys
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p76
export DIFFTEST_ARGMEM="10023E80=0:64,15049FA8=0:64,150A7F28=0:64,150A7F28=1:64"
$D/mutfast.sh func_15038910 port_work/p76/8910.c $D/s8910.txt \
 's/target\[0\] == -99999.0f \&\&/target[0] == -9999.0f \&\&/' \
 's/flag4 = self\[0x2FB\] \& 4;/flag4 = self[0x2FB] \& 2;/' \
 's/lt->fade\[slot\] < 2 \&\& lt->hold/lt->fade[slot] < 3 \&\& lt->hold/' \
 's/(100 - n \* 10) \/ 10.0f/(100 - n * 10) \/ 9.0f/' \
 's/ax = -1.0f;/ax = 1.0f;/' \
 's/ay = -1.0f;/ay = 1.0f;/' \
 's/if (pitch > 180.0f)/if (pitch > 190.0f)/' \
 's/(s32) (yaw \* 0.7111111f)/(s32) (yaw * 0.72f)/' \
 's/(expired \&\& !fixed) ||/(expired) ||/' \
 's/yaw -= yawBias;/yaw += yawBias;/' \
 's/d\[1\] = 20.0f - d\[1\];/d[1] = 10.0f - d[1];/' \
 's/yaw > 100.0f || yaw < -100.0f/yaw > 100.0f/' \
 's/d\[0\] \* 100.0f + J/d[0] * 10.0f + J/' \
 's/stepYaw = stepPitch = 5.0f;/stepYaw = stepPitch = 4.0f;/' \
 's/t = 1.0f - t;/t = 1.0f + t;/' \
 's/kYaw += (1.0f - kYaw) \* t;/kYaw += (1.0f - kYaw) * 0.5f;/' \
 's/if (lt->yaw\[slot\] < -90.0f)/if (lt->yaw[slot] < -80.0f)/' \
 's/lt->yawVel\[slot\] += stepYaw/lt->yawVel[slot] -= stepYaw/' \
 's/pitch = lt->pitchVel\[slot\] + lt->pitch\[slot\];/pitch = lt->pitchVel[slot];/' \
 's/if (!(keepMask \& 2))/if (!(keepMask \& 1))/' \
 's/func_150A8050(rot2, -a, roll, 0.0f);/func_150A8050(rot2, a, roll, 0.0f);/' \
 's/func_150A8050(rot1, 0.0f, 0.0f, b);/func_150A8050(rot1, 0.0f, 0.0f, -b);/' \
 's/rot1\[k\]\[i\] = J\[k\]\[i\] \* inv;/rot1[k][i] = J[i][k] * inv;/' \
 's/    res\[3\]\[1\] = J\[3\]\[1\];//' \
 's/J\[1\]\[i\] \*= scale\[i\];//' \
 's/lt->hold\[slot\] = 40;/lt->hold[slot] = 41;/' \
 's/step = D_800BE9E4 \* 10;/step = D_800BE9E4 * 8;/' \
 's/func_15049F30(q1, q2);/func_15049F30(q2, q1);/' \
 's/func_1504A1CC(q1, q2, t, q);/func_1504A1CC(q1, q2, 1.0f - t, q);/' \
 's/lt->pitchOfs\[slot\] = v - step/lt->pitchOfs[slot] = v + step/' \
 's/lt->flag4\[slot\] = flag4;/lt->flag4[slot] = 0;/' \
 's/noTarget \&\& !fixed \&\& lt->hold\[slot\] == 0/noTarget \&\& lt->hold[slot] == 0/' \
 's/if (postMul) {/if (!postMul) {/' \
 's/rot2\[k\]\[i\] = res\[k\]\[i\] \* inv;/rot2[k][i] = res[k][i];/'
