#!/bin/bash
# P200 chain 2: full runs on the float-ARG-fixed harness
cd /Users/sorikairo/conker-wt/port && eval "$(tools/eu_port/wt.sh env port)"; export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
D=docs/port/sessions/p200
for f in 15087204 15086508 15155B1C 15195160; do echo "### $f"; TR=4 $D/full.sh $f; done
echo CHAIN2 DONE
