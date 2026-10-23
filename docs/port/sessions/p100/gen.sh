#!/bin/bash
# gen.sh FUNC...: m2c drafts (gen2.py, JT LAX TYPED) into port_work/p100/gen/v*/FUNC.c as a reading aid only
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"
W=$PWD/port_work/p100; printf '%s\n' "$@" > $W/only.txt; rm -rf $W/gen
RAWDUMP=$W/raw ONLY=$W/only.txt JT=1 LAX=1 TYPED=1 tools/eu_port/m2c/venv/bin/python3 tools/eu_port/m2c/gen2.py $W/gen 1 5000 > $W/gen.log 2>&1
for f in "$@"; do ls $W/gen/*/$f.c 2>/dev/null | head -1 || echo "$f: no draft"; done
