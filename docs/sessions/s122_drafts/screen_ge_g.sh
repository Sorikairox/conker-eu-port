#!/bin/bash
cd /Users/sorikairo/conker-wt/a && eval "$(tools/eu_port/wt.sh env a)"
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
OPTS=-g tools/eu_port/rarescreen.sh ge tools/goldeneye all 0.6 -- -DVERSION_US -DLANG_US -DREFRESH_NTSC -DBUGFIX_R0 -DBYTEMATCH -DTARGET_N64 -I src/inflate
echo SCREEN_DONE
