#!/bin/bash
# P80: func_150322B8 mutants on s22b8_mut.txt (the quick setups shuffled), 4 parallel groups (MTAG), mutfast.sh
D=/Users/sorikairo/conker-wt/port/docs/port/sessions/p80; F=func_150322B8; B=port_work/p80/22b8.c; S=$D/s22b8_mut.txt
MTAG=_a $D/mutfast.sh $F $B $S \
 's#/\* 0x000 \*/ 0x05, 0x03#/* 0x000 */ 0x05, 0x04#' \
 's/0x83, 0x84, 0x87, 0x88/0x83, 0x84, 0x88, 0x87/' \
 's#/\* 0x104 \*/ 0x04#/* 0x104 */ 0x05#' \
 's/0x07, 0x00, 0x08/0x07, 0x01, 0x08/' \
 's/id < 0x104 + 0x4E/id <= 0x104 + 0x4E/' \
 's/id >= 0x17F \&\&/id > 0x17F \&\&/' \
 's/idx = 0x5F/idx = 0x5E/' \
 's/case 0x27: idx = 3/case 0x27: idx = 2/' \
 's/(att\[1\] == 0x9B) ? 3 : 0/(att[1] == 0x9B) ? 3 : 1/' > $D/mut_22b8_a.log 2>&1 &
MTAG=_b $D/mutfast.sh $F $B $S \
 's/? D_80090684 : D_80090680/? D_80090680 : D_80090684/' \
 's/else if (id == 0x51)/else if (id == 0x52)/' \
 's/> 0.0f) ? 1 : 0/>= 0.0f) ? 1 : 0/' \
 's/case 0x172: idx = 0x00/case 0x172: idx = 0x01/' \
 's/case 0x81: idx = 2; att\[2\] = 0x13/case 0x81: idx = 2; att[2] = 0x12/' \
 's/case 0xB6: idx = 1/case 0xB6: idx = 2/' \
 's/== 0.0f) ? 3 : 0/== 0.0f) ? 2 : 0/' \
 's/case 0x2AA: idx = 6/case 0x2AA: idx = 5/' \
 's/case 0xFA:/case 0xFB:/' > $D/mut_22b8_b.log 2>&1 &
MTAG=_c $D/mutfast.sh $F $B $S \
 's/(id == 5) ? 2 : 0/(id == 6) ? 2 : 0/' \
 's/idx = 7;/idx = 8;/' \
 's/id == 0x13 || id == 0x20/id == 0x13 || id == 0x21/' \
 's/sync = 0;/sync = 1;/' \
 's/\*(s16 \*) (att + 0x1E) = 0;/*(s16 *) (att + 0x1E) = 1;/' \
 's/idx = id - 0x33/idx = id - 0x32/' \
 's/att\[2\] = 0xE;/att[2] = 0xF;/' \
 's/idx = 8;/idx = 9;/' > $D/mut_22b8_c.log 2>&1 &
MTAG=_d $D/mutfast.sh $F $B $S \
 's/idx == cur \&\&/idx != cur \&\&/' \
 's/== 0x3FF/== 0x3FE/' \
 's/anim\[0x215\] == 0/anim[0x215] != 0/' \
 's/- 1.0f;/- 2.0f;/' \
 's/if (last <= /if (last < /' \
 's/\& ~0x8000/\& ~0x4000/' \
 's/0, idx, 0, 0.0f, 1)/0, idx, 1, 0.0f, 1)/' \
 's/\*(s16 \*) (anim + 0x3A) = \*(s16 \*) (src + 0x3A)/*(s16 *) (anim + 0x3A) = *(s16 *) (src + 0x38)/' \
 's/(\*(s8 \*) (anim + 0x39) != 0 ||/(*(s8 *) (anim + 0x39) == 0 ||/' > $D/mut_22b8_d.log 2>&1 &
wait; echo DONE; cat $D/mut_22b8_?.log | grep -c KILLED
