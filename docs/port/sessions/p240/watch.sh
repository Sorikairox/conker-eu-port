#!/bin/bash
# P233 store watch (P161 method): build a copy of port/build/web whose wasm traps on any store touching [LO, HI)
# (default null+0x24..0x28), then run it in node with a frame script.
#   watch.sh inst [LO HI]            -> port_work/p240/sw_web (instrumented copy)
#   watch.sh run MODE SECS LOG       MODE = war|race (PORT_PADF from the env file)
cd /Users/sorikairo/conker-wt/web || exit 1
export PATH=$PATH:/Applications/Docker.app/Contents/Resources/bin
H=docs/port/sessions/p240; W=port_work/p240/sw_web
case $1 in
inst)
  rm -rf $W; mkdir -p $W; cp -R port/build/web/. $W/
  docker run --rm -v "$PWD":/w -w /w conker-emsdk bash -c "
    /emsdk/upstream/bin/wasm-dis $W/conker.wasm -o $W/c.wat &&
    SW_EXCL=$SW_EXCL python3 $H/storewatch_inst.py $W/c.wat $W/c2.wat ${2:-0x24} ${3:-0x28} &&
    /emsdk/upstream/bin/wasm-as -all -g $W/c2.wat -o $W/conker.wasm && rm -f $W/c.wat $W/c2.wat"
  echo "inst rc=$?"; ls -la $W/conker.wasm;;
run)
  M=$2; source $H/$M.env; export PORT_PADF="$PADF"
  docs/port/sessions/p161/nrun.sh p240sw "$PWD/$W" "$3" "$4";;
esac
