#!/bin/zsh
# ljall.sh func:draft ... -> linejoin variants of each draft through tryall; OK lines + best per func
cd /Users/sorikairo/conker-wt/a && eval "$(tools/eu_port/wt.sh env a)" && export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
for fd in "$@"; do
  fn=${fd%%:*}; dr=${fd#*:}; o=conker/build_port/s154/lj/$fn; rm -rf $o; mkdir -p $o
  n=$(python3 tools/eu_port/linejoin.py $dr $o 128 $fn)
  tools/eu_port/m2c/tryall $fn $o/lj_*.c 2>&1 | grep -v '^$' > $o/res.txt
  echo "$fn n=$n $(grep -c '^OK' $o/res.txt) OK; best: $(cut -d' ' -f1 $o/res.txt | sort | uniq -c | sort -k2 | head -3 | tr '\n' ' ')"
  grep '^OK' $o/res.txt | head -2
done
