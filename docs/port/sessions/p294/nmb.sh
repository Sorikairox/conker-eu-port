#!/bin/bash
# P294: NM build only (log nm_build.log), prints rc + first errors / warnings of D5E90.c
cd ~/conker-wt/pe && eval "$(tools/eu_port/wt.sh env pe)" && export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
D=docs/port/sessions/p294
touch conker/src_eu/nm_asm/D5E90.c
docker exec -w /conker $CONKERDEV make -C conker VERSION=eu NON_MATCHING=1 -j4 > $D/nm_build.log 2>&1; rc=$?
echo "nm rc $rc"; grep -iE 'error|D5E90.c.*warn' $D/nm_build.log | head -20
