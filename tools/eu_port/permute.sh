#!/bin/bash
# decomp-permuter on one or more EU functions (host side; uses the container conkerdev).
#
# usage: permute.sh <func> [draft.c] [seconds=600] [jobs=8]
#        permute.sh -l <list> [seconds=600] [jobs=8]     list lines: "<func> [draft.c]"
#
# The draft is the function's C (plus any declarations it needs above it), default
# $DRAFTS/<func>.c (DRAFTS defaults to tools/decomp-permuter/drafts). For each function:
#   - tools/decomp-permuter/nm/<func>/ is recreated by tools/eu_port/permute/setup.py
#     (base.c = preprocessed TU with the draft, other bodies stripped; target.o from the .s;
#     compile.sh = the file's IDO cc line);
#   - permuter.py runs with --stop-on-zero --better-only for at most <seconds> (log: log.txt);
#   - the best output is extracted to best.c and screened with m2c/try (the authoritative check:
#     permuter score 0 ignores relocation target names). A score-0 result also goes to match.c.
# One summary line per function:  <func> base=<score> best=<score> try=<OK|DIFFn|...> <file>
# Extra permuter flags: PERM_ARGS="...". Run long batches with run_in_background.
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
R=~/conker; P=$R/tools/decomp-permuter; DRAFTS=${DRAFTS:-$P/drafts}
one() {
  f=$1; d=${2:-$DRAFTS/$f.c}; secs=$3; jobs=$4; od=$P/nm/$f
  [ -f "$d" ] || { echo "$f no draft ($d)"; return; }
  rm -rf $od; mkdir -p $od; cp "$d" $od/draft.c
  if ! docker exec conkerdev python3 /conker/tools/eu_port/permute/setup.py $f /conker/tools/decomp-permuter/nm/$f/draft.c /conker/tools/decomp-permuter/nm/$f > $od/setup.txt 2>&1; then
    echo "$f SETUP-FAILED $(tail -3 $od/setup.txt | tr '\n' ' ' | cut -c1-200)"; return; fi
  docker exec -w /conker/tools/decomp-permuter conkerdev timeout -s INT $secs \
    python3 permuter.py nm/$f -j$jobs --stop-on-zero --better-only $PERM_ARGS > $od/log.txt 2>&1
  base=$(tr '\r' '\n' < $od/log.txt | grep -m1 -o 'base score = [0-9]*' | grep -o '[0-9]*$')
  bestdir=$(ls -d $od/output-* 2>/dev/null | sed 's/.*output-\([0-9]*\)-\([0-9]*\)$/\1 \2 &/' | sort -n -k1,1 -k2,2 | head -1 | cut -d' ' -f3)
  if [ -z "$bestdir" ]; then echo "$f base=$base best=none"; return; fi
  best=$(basename $bestdir | cut -d- -f2)
  docker exec conkerdev python3 /conker/tools/eu_port/permute/setup.py extract $f /conker/tools/decomp-permuter/nm/$f/$(basename $bestdir)/source.c /conker/tools/decomp-permuter/nm/$f/draft.c > $od/best.c 2>/dev/null
  t=$(TRYDIR=perm_$f $R/tools/eu_port/m2c/try $f $od/best.c | head -1)
  out=$od/best.c
  if [ "$t" = OK ]; then cp $od/best.c $od/match.c; out=$od/match.c; fi
  echo "$f base=$base best=$best try=$t $out"
}
if [ "$1" = -l ]; then
  list=$2; secs=${3:-600}; jobs=${4:-8}
  while read -r f d; do [ -n "$f" ] && one $f "$d" $secs $jobs < /dev/null; done < $list
else
  one $1 "$2" ${3:-600} ${4:-8}
fi
