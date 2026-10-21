#!/bin/zsh
# scr.sh : tryall every extracted draft in d/, one line per function
cd /Users/sorikairo/conker-wt/a && eval "$(tools/eu_port/wt.sh env a)" && export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
for f in ${@:-$(ls conker/build_port/s154/d/*.c)}; do
  fn=$(basename $f .c); fn=${fn[1,13]}
  r=$(tools/eu_port/m2c/tryall $fn $f 2>&1 | grep -v '^$' | tail -1)
  echo "$fn $r"
done
