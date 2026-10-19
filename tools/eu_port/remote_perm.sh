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
# Worker: REMOTE (default sorikairo@192.168.0.71) with Docker and the conker-arm image.
# `remote_perm.sh --setup` (re)creates the worker container `conkerdev` and pipes the permuter
# code + headers into it from this repo. Everything on the worker lives inside the container's
# own filesystem: no host bind mount (Docker Desktop 20.10's file sharing deadlocked under
# permuter load, leaving processes stuck in D state). Each job runs in its own /work/<id> dir,
# so several agents/streams can use the worker at once.
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
REMOTE=${REMOTE:-sorikairo@192.168.0.71}
RDOCKER=/Applications/Docker.app/Contents/Resources/bin/docker
R=${CONKER_ROOT:-$HOME/conker}; P=$R/tools/decomp-permuter; DRAFTS=${DRAFTS:-$P/drafts}
one() {
  f=$1; d=${2:-$DRAFTS/$f.c}; secs=$3; jobs=$4; od=$P/nm/$f
  [ -f "$d" ] || { echo "$f no draft ($d)"; return; }
  rm -rf $od; mkdir -p $od; cp "$d" $od/draft.c
  if ! docker exec ${CONKERDEV:-conkerdev} python3 /conker/tools/eu_port/permute/setup.py $f /conker/tools/decomp-permuter/nm/$f/draft.c /conker/tools/decomp-permuter/nm/$f > $od/setup.txt 2>&1; then
    echo "$f SETUP-FAILED $(tail -3 $od/setup.txt | tr '\n' ' ' | cut -c1-200)"; return; fi
  # ship the job into the worker container, run it, bring back log + outputs
  job=$f-$$-$RANDOM
  (cd $P && tar --no-mac-metadata --no-xattrs -cf - nm/$f) | ssh -o BatchMode=yes $REMOTE "$RDOCKER exec -i conkerdev bash -c '\
    mkdir -p /work/$job && cd /work/$job && tar -xf - && \
    timeout -s INT -k 30 $secs python3 /conker/tools/decomp-permuter/permuter.py nm/$f -j$jobs \
      --stop-on-zero --better-only --stack-diffs $PERM_ARGS > nm/$f/log.txt 2>&1; \
    tar -cf - nm/$f/log.txt nm/$f/output-* 2>/dev/null; cd / && rm -rf /work/$job'" | (cd $P && tar -xf - 2>/dev/null)
  base=$(tr '\r' '\n' < $od/log.txt 2>/dev/null | grep -m1 -o 'base score = [0-9]*' | grep -o '[0-9]*$')
  bestdir=$(ls -d $od/output-* 2>/dev/null | sed 's/.*output-\([0-9]*\)-\([0-9]*\)$/\1 \2 &/' | sort -n -k1,1 -k2,2 | head -1 | cut -d' ' -f3)
  if [ -z "$bestdir" ]; then echo "$f base=$base best=none (remote)"; return; fi
  best=$(basename $bestdir | cut -d- -f2)
  docker exec ${CONKERDEV:-conkerdev} python3 /conker/tools/eu_port/permute/setup.py extract $f /conker/tools/decomp-permuter/nm/$f/$(basename $bestdir)/source.c /conker/tools/decomp-permuter/nm/$f/draft.c > $od/best.c 2>/dev/null
  t=$(TRYDIR=perm_$f $R/tools/eu_port/m2c/try $f $od/best.c | head -1)
  out=$od/best.c
  if [ "$t" = OK ]; then cp $od/best.c $od/match.c; out=$od/match.c; fi
  echo "$f base=$base best=$best try=$t $out (remote)"
}
if [ "$1" = --setup ]; then
  ssh -o BatchMode=yes $REMOTE "$RDOCKER rm -f conkerdev >/dev/null 2>&1; \
    $RDOCKER run -d --restart unless-stopped --name conkerdev --platform linux/arm64 conker-arm sleep infinity >/dev/null"
  (cd $R && tar --no-mac-metadata --no-xattrs -cf - --exclude 'tools/decomp-permuter/nm' --exclude 'tools/decomp-permuter/sweep' \
     --exclude 'tools/decomp-permuter/repair' --exclude 'tools/decomp-permuter/s34' --exclude '__pycache__' \
     tools/decomp-permuter conker/include) | \
    ssh -o BatchMode=yes $REMOTE "$RDOCKER exec -i conkerdev bash -c 'mkdir -p /conker /work && tar -xf - -C /conker && nproc'"
  exit
fi
if [ "$1" = -l ]; then
  list=$2; secs=${3:-600}; jobs=${4:-8}
  while read -r f d; do [ -n "$f" ] && one $f "$d" $secs $jobs < /dev/null; done < $list
else
  one $1 "$2" ${3:-600} ${4:-8}
fi
