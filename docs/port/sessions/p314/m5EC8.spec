# old ||| new ||| setups [||| occurrence]
static const f32 sFlyerCircleX[1] = { -3478.0f }; ||| static const f32 sFlyerCircleX[1] = { -3477.0f }; ||| ev8go ev8circ
static const f32 sFlyerCircleZ[1] = { 3858.0f }; ||| static const f32 sFlyerCircleZ[1] = { 3857.0f }; ||| ev8go ev8circ
{ 1.57079637f } ||| { 1.57079648f } ||| ev9go ev8go
{ 0.0115f } ||| { 0.0116f } ||| ev9go ev8go
{ 0.200000003f } ||| { 0.300000003f } ||| turnmin turn21 rollz rollp
{ 0.149999991f } ||| { 0.150000006f } ||| ev8sink
{ 0.00518999994f } ||| { 0.00519000040f } ||| ev8circ ev8sink
{ 3.20000005f } ||| { 3.25f } ||| ev8circ ev8sink circok
{ -3100.0f } ||| { -3200.0f } ||| ev8sink
{ 0.0174532924f } ||| { 0.0174532942f } ||| base plo
(u8 *)D_800DDE80 + f->type * 0x14); ||| (u8 *)D_800DDE80 + f->type * 0x10); ||| off ev8go mup mdn ||| 1
row->enabled == 0 ||| row->enabled != 0 ||| off base
D_800DDF78[f->type] == 0 ||| D_800DDF78[f->type + 1] == 0 ||| off78 base
alpha = f->alpha; ||| alpha = f->fading; ||| fadein fadeout
(f->type == 8 || f->type == 9) ||| (f->type == 8 || f->type == 10) ||| ev9go ev7
(f->type == 8 || f->type == 9) ||| (f->type == 7 || f->type == 9) ||| ev8go ev7 ev8wait
D_800BE9F0 == 6 ||| D_800BE9F0 >= 5 ||| ev8lvl5
D_800C35EA != 0 && D_800C3A08 == 0xF) { ||| D_800C35EA != 0 && D_800C3A08 >= 0xE) { ||| ev8evE
D_800C35EA != 0 && D_800C3A08 == 0xF) { ||| D_800C3A08 == 0xF) { ||| ev8ev35
f->flags &= 0xFFF7; ||| f->flags &= 0xFFFF; ||| ev8wait
if (D_800C39D0 >= 60 && ||| if (D_800C39D0 >= 61 && ||| ev9go
!(f->flags & 0x200)) { ||| !(f->flags & 0x400)) { ||| ev8circ ||| 1
(f->flags & 0xFFB3) | 0x200; ||| (f->flags & 0xFFB7) | 0x200; ||| ev9go ev8go
dx = f->x - sFlyerCircleX[0]; ||| dx = f->z - sFlyerCircleX[0]; ||| ev8go
dz = f->z - sFlyerCircleZ[0]; ||| dz = f->x - sFlyerCircleZ[0]; ||| ev8go
sFlyerHalfPi[0] - func_150484A0(dx, dz); ||| sFlyerHalfPi[0] - func_150484A0(dz, dx); ||| ev8go
sFlyerHalfPi[0] - func_150484A0(dx, dz); ||| sFlyerHalfPi[0] + func_150484A0(dx, dz); ||| ev8go ev9go
f->rollVel = sqrtf(dx * dx + dz * dz); ||| f->rollVel = sqrtf(dx * dx + dx * dz); ||| ev8go
if (f->fading == 0) { ||| if (f->fading != 1) { ||| fadeout fadein
(f->flags & 8) && D_800DDF5C[f->slot] == 0 ||| (f->flags & 8) || D_800DDF5C[f->slot] == 0 ||| fade8on base
f->fading = 1; ||| f->fading = 2; ||| fade8
alpha != 0xFF ||| alpha != 0xFE ||| fadeFF fadeFE fadeFFn
alpha += D_800BE9E4 * 4; ||| alpha += D_800BE9E4 * 3; ||| base fade8on
if (alpha > 0xFF) { ||| if (alpha > 0x100) { ||| fadein fadeFC
alpha = 0xFF; ||| alpha = 0xFE; ||| fadein
if (alpha == 0) { ||| if (alpha <= 1) { ||| fadeclp fade0 fade1
alpha -= D_800BE9E4 * 4; ||| alpha -= D_800BE9E4 * 2; ||| fadeout
if (alpha < 0) { ||| if (alpha < -1) { ||| fadeclp fade7
D_800DDF68[f->type] = 1; ||| D_800DDF68[f->slot] = 1; ||| base
(u8 *)&D_8008D450 + f->type * 0x38 ||| (u8 *)&D_8008D450 + f->type * 0x34 ||| base plo spdhi
if (func_1000F3D0(f->sound) != 0) { ||| if (func_1000F3D0(f->sound) == 0) { ||| sndon sndoff
0x7D00, 0, 0, 0, (s32)f->x, (s32)f->y, (s32)f->z, 1000, 4000 ||| 0x7D00, 0, 0, 0, (s32)f->x, (s32)f->y, (s32)f->z, 1000, 4001 ||| sndon
0x7D00, 0, 0, 0, (s32)f->x, (s32)f->y, (s32)f->z, 1000, 4000 ||| 0x7D00, 0, 0, 0, (s32)f->x, (s32)f->z, (s32)f->z, 1000, 4000 ||| sndon
f->sound = 0; ||| f->sound = 1; ||| sndoff
if (f->flags & 4) { ||| if (f->flags & 6) { ||| cull0 base
dist = func_150ADE40((s32)f->x, (s32)f->z, f->homeX, f->homeZ); ||| dist = func_150ADE40((s32)f->x, (s32)f->z, f->homeX, f->homeY); ||| tfar
(f->flags & 0x10) && dist < f->rangeMin ||| (f->flags & 0x10) && dist <= f->rangeMin ||| tedge
(f->flags & 0x10) && dist < f->rangeMin ||| (f->flags & 0x14) && dist < f->rangeMin ||| tnearno
if (dist > f->rangeMax || near) { ||| if (dist >= f->rangeMax || near) { ||| tedge
dir.unk0 = (f32)f->homeX - f->x; ||| dir.unk0 = f->x - (f32)f->homeX; ||| tfar tfarwrap
dir.unk8 = f->z - (f32)f->homeZ; ||| dir.unk8 = (f32)f->homeZ - f->z; ||| tfar tfarwrap
ang += 0x80; ||| ang += 0x40; ||| tnear tnear2
if (ang >= 0x100) { ||| if (ang > 0x100) { ||| tnear tnear3
ang -= 0x100; ||| ang -= 0x80; ||| tnear
f->targetHeading = (f32)ang * 1.40625f; ||| f->targetHeading = (f32)ang * 1.4f; ||| tfar
f->timer = t->homeTime; ||| f->timer = t->wanderTime; ||| tfar ||| 1
if (f->state == 3) { ||| if (f->state != 3) { ||| st3pos st2pos
step = D_800BE9E4 * 0.5f; ||| step = D_800BE9E4 * 0.25f; ||| st3pos
if (f->targetHeading < f->heading) { ||| if (f->targetHeading <= f->heading) { ||| st3eq
fabsf(f->targetHeading - f->heading) >= 180.0f ||| fabsf(f->targetHeading - f->heading) > 180.0f ||| st3d180
fabsf(f->targetHeading - f->heading) >= 180.0f ||| (f->targetHeading - f->heading) >= 180.0f ||| st3wrap
(step > 0.0f && f->turnVel < 0.0f) ||| (step > 0.0f && f->turnVel < 1.0f) ||| st3pos
(step < 0.0f && f->turnVel > 0.0f) ||| (step < 0.0f && f->turnVel > -1.0f) ||| st3neg
f->state = 2; ||| f->state = 4; ||| st3opp st3opp2
f->turnVel += step; ||| f->turnVel -= step; ||| st3pos st3neg
if (f->state == 2) { ||| if (f->state == 3) { ||| st2pos st3opp
if (f->turnVel != 0.0f) { ||| if (f->turnVel > 1.0f) { ||| st2neg st2posz
if (f->turnVel > 0.0f) { ||| if (f->turnVel > 1.0f) { ||| st2posz st2posd1 ||| 1
f->turnVel -= D_800BE9E4 * 0.5f; ||| f->turnVel -= D_800BE9E4 * 0.75f; ||| st2pos
if (f->turnVel < 0.0f) { ||| if (f->turnVel < -0.5f) { ||| st2posz ||| 1
f->turnVel += D_800BE9E4 * 0.5f; ||| f->turnVel += D_800BE9E4 * 0.75f; ||| st2neg
if (f->turnVel > 0.0f) { ||| if (f->turnVel > 0.5f) { ||| st2negz ||| 2
f->timer -= D_800BE9E4; ||| f->timer -= 1; ||| st2pos st2tmr
if (f->timer <= 0) { ||| if (f->timer < 0) { ||| st2tmr st2zero
(f32)((u32)func_150ADA20() ||| (f32)((s32)func_150ADA20() ||| st2tmr st2tmr1 st2tmrn ||| 1
360); ||| 359); ||| st2tmr1 st2zero
f->timer = t->wanderTime; ||| f->timer = t->homeTime; ||| st2tmr st2zero st2tmr1
if (fabsf(f->turnVel) > t->turnMax) { ||| if (fabsf(f->turnVel) > t->turnMax + 1.0f) { ||| tmaxeq tmax35
if (fabsf(f->turnVel) > t->turnMax) { ||| if (f->turnVel > t->turnMax) { ||| tmaxn
f->turnVel = -t->turnMax; ||| f->turnVel = t->turnMax; ||| tmaxn
if (f->flags & 0x80) { ||| if (f->flags & 0x800) { ||| floor0 floor1
f->floorY = (f32)func_1510FE58((s32)f->x, (s32)f->y, (s32)f->z, &tri); ||| f->floorY = (f32)func_1510FE58((s32)f->x, (s32)f->z, (s32)f->y, &tri); ||| floor0
v = ((s32 *)D_800DBE5C)[(tri - D_800DC26C) / 12]; ||| v = ((s32 *)D_800DBE5C)[(tri - D_800DC26C) / 9]; ||| floor1
if (tri != 0) { ||| if (tri == 0) { ||| floor0 floor1
f->surface = v; ||| f->surface = v + 1; ||| floor0 floor1
if (f->climbTimer >= 0) { ||| if (f->climbTimer > 0) { ||| bobexp bobup
f->climbTimer -= D_800BE9E4; ||| f->climbTimer -= 1; ||| bobexp bobup
if (f->climbTimer <= 0) { ||| if (f->climbTimer < 0) { ||| bobexp
f->climbTimer = -1; ||| f->climbTimer = -2; ||| bobexp
f->yRange) + (f32)f->homeY; ||| (u16)f->yRange) + (f32)f->homeY; ||| bobexp2
f->yRange) + (f32)f->homeY; ||| f->yRange) + (f32)f->homeX; ||| bobexp bobexp3
if (f->y < f->targetY) { ||| if (f->y <= f->targetY) { ||| bobexp3
} else if (f->pitch > 0.0f) { ||| } else if (f->pitch >= 0.0f) { ||| bob0
} else if (f->pitch < 0.0f) { ||| } else if (f->pitch <= 0.0f) { ||| bob0
(f->pitchVel > 0.0f && f->y < f->targetY) ||| (f->pitchVel > 0.0f && f->y > f->targetY) ||| bobm1 bobm2
(f->pitchVel < 0.0f && f->targetY < f->y) ||| (f->pitchVel < 0.0f && f->targetY > f->y) ||| bobm3 bobm4
f->climbTimer = 120; ||| f->climbTimer = 121; ||| bobm1
f->pitchVel = -f->pitchVel; ||| f->pitchVel = f->pitchVel; ||| bobm1 bobm3
f->pitch += f->pitchVel; ||| f->pitch -= f->pitchVel; ||| base
if (f->pitch < -lim) { ||| if (f->pitch < lim) { ||| pmid base ||| 1
f->pitch = -lim; ||| f->pitch = lim; ||| plo
f->pitch = (f->pitch > lim) ? lim : f->pitch; ||| f->pitch = (f->pitch > lim) ? -lim : f->pitch; ||| phi
if (fabsf(f->turnVel) > sFlyerTurnMin[0]) { ||| if (fabsf(f->turnVel) >= sFlyerTurnMin[0]) { ||| turnmin
if (fabsf(f->turnVel) > sFlyerTurnMin[0]) { ||| if (f->turnVel > sFlyerTurnMin[0]) { ||| rcllo hwrapn
f->heading += f->turnVel; ||| f->heading -= f->turnVel; ||| base
if (f->heading < 0.0f) { ||| if (f->heading < 1.0f) { ||| hwrap0 hwrapn base
f->heading += 360.0f; ||| f->heading += 359.0f; ||| hwrapn
} else if (f->heading >= 360.0f) { ||| } else if (f->heading > 360.0f) { ||| hwrap0
f->heading -= 360.0f; ||| f->heading -= 361.0f; ||| hwrapp
if (!(f->flags & 0x20)) { ||| if (!(f->flags & 0x40)) { ||| flag20
f->rollVel = -f->turnVel; ||| f->rollVel = f->turnVel; ||| base
f->roll += f->rollVel; ||| f->roll -= f->rollVel; ||| base ||| 1
lim = t->rollMax; ||| lim = t->pitchMax; ||| rclhi rcllo
f->roll = -lim; ||| f->roll = lim; ||| rcllo
f->roll = (f->roll > lim) ? lim : f->roll; ||| f->roll = (f->roll > lim + 1.0f) ? lim : f->roll; ||| rclmid rclhi
f->roll = (f->roll > lim) ? lim : f->roll; ||| f->roll = (f->roll > lim) ? -lim : f->roll; ||| rclhi
if (f->roll > 0.0f) { ||| if (f->roll >= 0.0f) { ||| roll0
f->rollVel = -1.0f; ||| f->rollVel = -2.0f; ||| rollp
} else if (f->roll < 0.0f) { ||| } else if (f->roll <= 0.0f) { ||| roll0
f->rollVel = 1.0f; ||| f->rollVel = 2.0f; ||| rolln
f->roll += f->rollVel; ||| f->roll += f->turnVel; ||| rollbig rollp ||| 2
if (fabsf(f->roll) < sFlyerTurnMin[0]) { ||| if (f->roll < sFlyerTurnMin[0]) { ||| rollbign
if (fabsf(f->roll) < sFlyerTurnMin[0]) { ||| if (fabsf(f->roll) < sFlyerCircleTurnMax[0]) { ||| rollz rollz2
f->roll = 0.0f; ||| f->roll = 0.1f; ||| rollp
f->speed += f->accel; ||| f->speed -= f->accel; ||| base
if (f->speed < t->speedMin) { ||| if (f->speed < t->speedMax) { ||| spdeq base
f->speed = t->speedMin; ||| f->speed = t->speedMax; ||| spdlo
if (sp > t->speedMax) { ||| if (sp > t->speedMin) { ||| spdmid base
sp = t->speedMax; ||| sp = t->speedMin; ||| spdhi
if (!(f->flags & 1)) { ||| if (!(f->flags & 3)) { ||| mup cull0
if (f->pitch >= 0.0f) { ||| if (f->pitch > 0.0f) { ||| mup0
row->modelUp == f->model && t->flapA < t->flapB && -t->flapB < t->flapA ||| row->modelDown == f->model && t->flapA < t->flapB && -t->flapB < t->flapA ||| mup mupx ||| 1
row->modelUp == f->model && t->flapA < t->flapB && -t->flapB < t->flapA ||| row->modelUp == f->model && t->flapA <= t->flapB && -t->flapB < t->flapA ||| mfa ||| 1
f->model = row->modelDown; ||| f->model = row->modelUp; ||| mup
row->modelDown == f->model && t->flapA < t->flapB && -t->flapB < t->flapA ||| row->modelDown == f->model && t->flapA < t->flapB && -t->flapB <= t->flapA ||| mfb ||| 1
row->modelDown == f->model && t->flapA < t->flapB && -t->flapB < t->flapA ||| row->modelDown == f->model && t->flapA < t->flapB && t->flapB < t->flapA ||| mfb2 ||| 1
f->model = row->modelUp; ||| f->model = row->modelDown; ||| mdn
if (f->flags & 0x200) { ||| if (f->flags & 0x300) { ||| base ||| 1
d = D_800BE9E4; ||| d = D_800BE9E4 + 1; ||| ev8circ
f->pitchVel += f->turnVel * d; ||| f->pitchVel += f->turnVel; ||| ev8circ
f->turnVel += sFlyerCircleTurnAcc[0]; ||| f->turnVel -= sFlyerCircleTurnAcc[0]; ||| ev8circ
if (f->turnVel > sFlyerCircleTurnMax[0]) { ||| if (f->turnVel > sFlyerTurnMin[0]) { ||| ev8sink
f->turnVel = sFlyerCircleTurnMax[0]; ||| f->turnVel = sFlyerCircleTurnAcc[0]; ||| ev8sink
f->rollVel -= sFlyerCircleShrink[0] * d; ||| f->rollVel -= sFlyerCircleShrink[0]; ||| ev8circ
if (f->rollVel < 60.0f) { ||| if (f->rollVel < 59.0f) { ||| ev8sink circok ev8r59
f->rollVel = 60.0f; ||| f->rollVel = 61.0f; ||| ev8sink circok
s = func_150AD78C(f->pitchVel); ||| s = func_150AD78C(f->turnVel); ||| ev8circ
c = func_150AD780(f->pitchVel); ||| c = func_150AD780(f->rollVel); ||| ev8circ
f->x = f->rollVel * c + sFlyerCircleX[0]; ||| f->x = f->rollVel * s + sFlyerCircleX[0]; ||| ev8circ
f->z = f->rollVel * s + sFlyerCircleZ[0]; ||| f->z = f->rollVel * c + sFlyerCircleZ[0]; ||| ev8circ
f->y -= 100.0f / ((f->rollVel - 60.0f) + 4.0f); ||| f->y -= 100.0f / ((f->rollVel - 60.0f) + 2.0f); ||| ev8circ
f->y < sFlyerCircleFloor[0] || D_800C35EA == 0 ||| f->y < sFlyerCircleFloor[0] && D_800C35EA == 0 ||| ev8sink circ35
|| D_800C3A08 != 0xF) { ||| || D_800C3A08 != 0xE) { ||| circend ||| 2
a = f->pitch * sFlyerDegToRad[0]; ||| a = f->roll * sFlyerDegToRad[0]; ||| base
h = f->heading * sFlyerDegToRad[0]; ||| h = f->pitch * sFlyerDegToRad[0]; ||| base
sh = func_150AD78C(h); ||| sh = func_150AD78C(a); ||| base
ch = func_150AD780(h); ||| ch = func_150AD780(a); ||| base
dir.unk0 = ca * sh; ||| dir.unk0 = sa * sh; ||| base
dir.unk4 = -sa; ||| dir.unk4 = sa; ||| base
dir.unk8 = ca * ch; ||| dir.unk8 = ca * sh; ||| base
d = f->speed * D_800BE9E4; ||| d = f->speed; ||| base
f->x += dir.unk0 * d; ||| f->x += dir.unk8 * d; ||| base
f->z += dir.unk8 * d; ||| f->z -= dir.unk8 * d; ||| base
f->kind == 0x13 && D_800DDF60[f->slot] == 0 ||| f->kind >= 0x13 && D_800DDF60[f->slot] == 0 ||| chirpk chirp
f->kind == 0x13 && D_800DDF60[f->slot] == 0 ||| f->kind == 0x13 && D_800DDF60[f->slot] != 1 ||| chirpno chirp chirpf2
func_10010F88(0x10, 0x7FFF, func_150ADA20() & 0x7F, 0, 0 ||| func_10010F88(0x10, 0x7FFF, func_150ADA20() & 0xFF, 0, 0 ||| chirp
(s32)f->z, 500, 4000); ||| (s32)f->z, 400, 4000); ||| chirp
D_800DDF60[f->slot] = (func_150ADA20() & 0x3F) + 30; ||| D_800DDF60[f->slot] = (func_150ADA20() & 0x7F) + 30; ||| chirp
D_800DDF60[f->slot] = (func_150ADA20() & 0x3F) + 30; ||| D_800DDF60[f->slot] = (func_150ADA20() & 0x3F) + 31; ||| chirp
if ((f->flags & 2) ||| if ((f->flags & 1) ||| cull1
func_1510B460(D_800DA030, f->x, f->y, f->z, D_800D9F40, D_800D9F3C, D_800D3A00, D_800D3A04, 0, 0) != 0 ||| func_1510B460(D_800DA030, f->x, f->y, f->z, D_800D9F40, D_800D9F3C, D_800D3A00, D_800D3A00, 0, 0) != 0 ||| cull1
func_1510B460(D_800DA030, f->x, f->y, f->z, D_800D9F40, D_800D9F3C, D_800D3A00, D_800D3A04, 0, 0) != 0 ||| func_1510B460(D_800DA030, f->x, f->y, f->z, D_800D9F3C, D_800D9F40, D_800D3A00, D_800D3A04, 0, 0) != 0 ||| cull1
func_1510B460(D_800DA030, f->x, f->y, f->z, D_800D9F40, D_800D9F3C, D_800D3A00, D_800D3A04, 0, 0) != 0 ||| func_1510B460(D_800DA030, f->x, f->y, f->z, D_800D9F40, D_800D9F3C, D_800D3A00, D_800D3A04, 0, 0) == 0 ||| cull0 cull1
(D_800D2138 != 1 ||| (D_800D2138 != 2 ||| cull2a cull2c
|| func_1510B460(D_800DA070, f->x, f->y, f->z ||| || func_1510B460(D_800DA030, f->x, f->y, f->z ||| cull2b
