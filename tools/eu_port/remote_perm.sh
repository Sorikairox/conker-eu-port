#!/bin/bash
# decomp-permuter with the search running on a remote worker Mac (same output format as permute.sh).
#
# usage: remote_perm.sh <func> [draft.c] [seconds=600] [jobs=8]
#        remote_perm.sh -l <list> [seconds=600] [jobs=8]     list lines: "<func> [draft.c]"
#
# Per function: setup (base.c, target.o, compile.sh) runs locally in conkerdev exactly as in
# permute.sh; the job dir is copied to the worker, permuter.py runs in the worker's conkerdev
# (conker-arm image, same IDO -> identical scores), output-* dirs are copied back, and best.c
# is extracted and screened locally with m2c/try (still the authoritative check).
#
# Worker: REMOTE (default sorikairo@192.168.0.71), repo copy at ~/conker there with a running
# container named conkerdev (see HANDOFF "Remote permuter worker"). Run several streams on
# different lists in parallel for more throughput; each job only uses the worker's CPUs.
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
REMOTE=${REMOTE:-sorikairo@192.168.0.71}
RDOCKER=/Applications/Docker.app/Contents/Resources/bin/docker
R=~/conker; P=$R/tools/decomp-permuter; DRAFTS=${DRAFTS:-$P/drafts}
one() {
  f=$1; d=${2:-$DRAFTS/$f.c}; secs=$3; jobs=$4; od=$P/nm/$f
  [ -f "$d" ] || { echo "$f no draft ($d)"; return; }
  rm -rf $od; mkdir -p $od; cp "$d" $od/draft.c
  if ! docker exec conkerdev python3 /conker/tools/eu_port/permute/setup.py $f /conker/tools/decomp-permuter/nm/$f/draft.c /conker/tools/decomp-permuter/nm/$f > $od/setup.txt 2>&1; then
    echo "$f SETUP-FAILED $(tail -3 $od/setup.txt | tr '\n' ' ' | cut -c1-200)"; return; fi
  # ship the job, run it remotely, bring back log + outputs
  (cd $P && tar -cf - nm/$f) | ssh -o BatchMode=yes $REMOTE "cd ~/conker/tools/decomp-permuter && rm -rf nm/$f && tar -xf - && \
    $RDOCKER exec -w /conker/tools/decomp-permuter conkerdev timeout -s INT $secs \
      python3 permuter.py nm/$f -j$jobs --stop-on-zero --better-only --stack-diffs $PERM_ARGS > nm/$f/log.txt 2>&1; \
    tar -cf - nm/$f/log.txt nm/$f/output-* 2>/dev/null; rm -rf nm/$f" | (cd $P && tar -xf - 2>/dev/null)
  base=$(tr '\r' '\n' < $od/log.txt 2>/dev/null | grep -m1 -o 'base score = [0-9]*' | grep -o '[0-9]*$')
  bestdir=$(ls -d $od/output-* 2>/dev/null | sed 's/.*output-\([0-9]*\)-\([0-9]*\)$/\1 \2 &/' | sort -n -k1,1 -k2,2 | head -1 | cut -d' ' -f3)
  if [ -z "$bestdir" ]; then echo "$f base=$base best=none (remote)"; return; fi
  best=$(basename $bestdir | cut -d- -f2)
  docker exec conkerdev python3 /conker/tools/eu_port/permute/setup.py extract $f /conker/tools/decomp-permuter/nm/$f/$(basename $bestdir)/source.c /conker/tools/decomp-permuter/nm/$f/draft.c > $od/best.c 2>/dev/null
  t=$(TRYDIR=perm_$f $R/tools/eu_port/m2c/try $f $od/best.c | head -1)
  out=$od/best.c
  if [ "$t" = OK ]; then cp $od/best.c $od/match.c; out=$od/match.c; fi
  echo "$f base=$base best=$best try=$t $out (remote)"
}
if [ "$1" = -l ]; then
  list=$2; secs=${3:-600}; jobs=${4:-8}
  while read -r f d; do [ -n "$f" ] && one $f "$d" $secs $jobs < /dev/null; done < $list
else
  one $1 "$2" ${3:-600} ${4:-8}
fi
