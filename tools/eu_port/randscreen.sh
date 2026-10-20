#!/bin/bash
# s108: screen randinline.py variants (+ the original) of each function's gensome draft
# (repair/fresh/<f>.c) with m2c/tryall. usage: randscreen.sh outdir func...  -> "<best> <f> <draft>" per function
# s110: also realproto.py fix (real callee prototypes, padded calls) of the draft -> <f>_r.c and its
# randinline variants <f>_r_*.c; NOPROTO=1 skips them. A CERR best prints the first compile error.
# Run after eval "$(tools/eu_port/wt.sh env <name>)". Writes drafts to outdir (keep it under conker/build_port).
export PATH=/Applications/Docker.app/Contents/Resources/bin:$PATH
R=${CONKER_ROOT:-$HOME/conker}; out=$1; shift; mkdir -p $out
for f in "$@"; do
  d=$R/tools/decomp-permuter/repair/fresh/$f.c
  [ -f $d ] || { echo "NODRAFT $f"; continue; }
  cp $d $out/${f}_o.c
  vs=$(python3 $R/tools/eu_port/randinline.py $d $out/$f)
  if [ -z "$NOPROTO" ]; then
    cf=$(grep -l "/$f\.s\"" $R/conker/src_eu/*.c $R/conker/src_eu/*/*.c 2>/dev/null | head -1)
    python3 $R/tools/eu_port/realproto.py fix $d $out/${f}_r.c $cf 2>>$out/realproto.log
    vs="$vs $out/${f}_r.c $(python3 $R/tools/eu_port/randinline.py $out/${f}_r.c $out/${f}_r)"
  fi
  $R/tools/eu_port/m2c/tryall $f $out/${f}_o.c $vs > $out/$f.res 2>&1
  b=$(awk '{r=$1; s=r; sub(/^DIFF/,"",s); sub(/^SIZE[+-]/,"",s); k=(r=="OK")?-1:(r ~ /^DIFF/)?s:(r ~ /^SIZE/)?1000+s:9999; if (b=="" || k<b) {b=k; best=$0}} END {print best}' $out/$f.res | sed "s|^\([^ ]*\) |\1 $f |")
  case "$b" in CERR*) e=$(cat $R/conker/build/ta/*/errs/$f.txt 2>/dev/null | head -1 | sed 's/.*line [0-9]*: //' | cut -c1-90); echo "$b | $e";; *) echo "$b";; esac
done
