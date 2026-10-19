#!/bin/bash
_top=$(git rev-parse --show-toplevel 2>/dev/null); if [ -n "$_top" ] && [ "$_top" != "${CONKER_ROOT:-$HOME/conker}" ]; then echo "refusing: cwd repo $_top != CONKER_ROOT ${CONKER_ROOT:-$HOME/conker} (run: eval \"\$(tools/eu_port/wt.sh env <name>)\")" >&2; exit 3; fi
# usage: u8run.sh [outdir=build/u]  -- the u8/u16-parameter pipeline (session 7):
# u8params.py -> list, fresh contexts, gen2.py drafts for those functions only, narrow.py
# (forced by the list) into n0..n7, screen.py each set in the container, merge.py -> final.
# Then run apply.py on <outdir>/final yourself.
set -e
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
M=$(cd "$(dirname "$0")" && pwd); O=${1:-build/u}; C=${CONKER_ROOT:-$HOME/conker}/conker
rm -rf $M/ctx $C/$O; mkdir -p $(dirname $C/$O); python3 $M/u8params.py > $C/$O.list; (cd $M && python3 list.py > all.txt)
ONLY=$C/$O.list $M/venv/bin/python $M/gen2.py $C/$O 1 400 | tail -1
cp $M/screen.py $M/merge.py $C/build/ 2>/dev/null || true
sets=""
for v in 0 1 2 3 4 5 6 7; do
  [ -d $C/$O/v$v ] || continue
  python3 $M/narrow.py $C/$O/v$v $C/$O/n$v $C/$O.list >/dev/null
  docker exec -w /conker/conker ${CONKERDEV:-conkerdev} python3 build/screen.py $O/n$v 8 >/dev/null 2>&1 || true
  echo "n$v: $(grep -c '^OK' $C/$O/n$v/screen.txt 2>/dev/null || true) OK"
  sets="$sets $C/$O/n$v"
done
python3 $M/merge.py $C/$O/final $sets | tail -1
