#!/bin/zsh
# first compile error per CERR func: cerr.sh list_of_funcs
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
R=$HOME/conker; F=${DIR:-$R/tools/decomp-permuter/repair/fresh}
for f in $(cat $1); do
  out=$($R/tools/eu_port/repair_try.sh $f $F/$f.c 2>&1)
  res=$(echo "$out" | grep -E "^$f " | tail -1)
  err=$(echo "$out" | grep -m2 -E 'Error|error' | sed 's/.*line [0-9]*: //' | tr '\n' '|' | cut -c1-160)
  echo "$res :: $err"
done
