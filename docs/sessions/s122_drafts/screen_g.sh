#!/bin/bash
cd /Users/sorikairo/conker-wt/a && eval "$(tools/eu_port/wt.sh env a)"
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
U=/conker/tools/ultralib/include
export OPTS=-g
tools/eu_port/rarescreen.sh dkr tools/dkr all 0.6 -- -I include/libc -I libultra -I libultra/src -D_FINALROM -DNDEBUG -DTARGET_N64 -DF3DDKR_GBI -DVERSION_us_v77 -DBUILD_VERSION=7
tools/eu_port/rarescreen.sh bk tools/banjo-kazooie all 0.6 -- -I include/n_audio/PR -I $U -I $U/PR -I $U/PRinternal -I $U/compiler/ido -I /conker/tools/ultralib/src/audio -D_FINALROM -DF3DEX_GBI -DVERSION=0 -DNDEBUG -DBUILD_VERSION=6 -DBKDIFFS -DN_MICRO -DANTI_TAMPER=1 -DANTI_PIRACY=1
echo SCREEN_DONE
