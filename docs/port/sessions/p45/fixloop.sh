#!/bin/bash
# usage: fixloop.sh FUNC draft.c -- add the file's later prototype for each 'redeclaration of X' (implicit-decl) error
cd /Users/sorikairo/conker-wt/portb; eval "$(tools/eu_port/wt.sh env portb)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
for k in $(seq 1 12); do
  out=$(tools/port/difftest.sh $1 $2 --trials 4 2>&1 | tail -1)
  n=$(echo "$out" | grep -o "line [0-9]*: redeclaration of '[a-zA-Z0-9_]*'" | head -1)
  [ -z "$n" ] && { echo "$out" | cut -c1-400; exit; }
  ln=$(echo "$n" | sed 's/line \([0-9]*\):.*/\1/'); nm=$(echo "$n" | sed "s/.*'\(.*\)'/\1/")
  decl=$(sed -n ${ln}p conker/build/difftest/$1.c | sed "s/) *{ *$/);/")
  echo "add: $decl"; printf '%s\n' "$decl" | cat - $2 > $2.tmp && mv $2.tmp $2
done
