#!/bin/bash
# ASYNCIFY cost probe: link every game object (no GC) with and without ASYNCIFY and compare wasm sizes.
# Run in the container from port/:  bash tools/size_probe.sh
set -e
OBJS=$(make -s -f Makefile print-objs)
COMMON="-O2 -sALLOW_MEMORY_GROWTH=1 -sINITIAL_MEMORY=128MB -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sERROR_ON_UNDEFINED_SYMBOLS=0 -Wl,--no-gc-sections -Wl,--export-all -Wl,--error-limit=0"
mkdir -p build/probe
emcc $OBJS build/boot.o build/ultra/*.o build/stubs/*.o -o build/probe/async.js $COMMON -sASYNCIFY 2>/dev/null
emcc $OBJS build/boot.o build/ultra/*.o build/stubs/*.o -o build/probe/plain.js $COMMON 2>/dev/null
ls -l build/probe/*.wasm | awk '{print $5, $9}'
