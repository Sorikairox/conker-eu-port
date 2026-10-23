#!/bin/bash
# P173: for each name in $1, is it defined/wrapped by port-web's port/ (not port/build)? PROV / MISS
W=${W:-$HOME/conker-wt/web/port}
while read n; do
  if grep -rqw --exclude-dir=build "$n" "$W" 2>/dev/null; then echo "PROV $n $(grep -rlw --exclude-dir=build "$n" "$W" | sed "s|$W/||" | head -3 | tr '\n' ' ')"; else echo "MISS $n"; fi
done < "$1"
