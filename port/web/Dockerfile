# Browser (wasm32) toolchain for the Conker source port.
# Pinned emsdk. On Apple Silicon use the -arm64 tag (default); on x86_64 hosts build with
#   docker build --build-arg EMSDK_TAG=4.0.15 -t conker-emsdk port/web
ARG EMSDK_TAG=4.0.15-arm64
FROM emscripten/emsdk:${EMSDK_TAG}
# emsdk ships clang/wasm-ld/node/python3/cmake/make. Nothing else is needed for the skeleton.
# Warm the system-library cache (libc, libGL, fibers/asyncify support) so builds are fast and offline.
RUN echo 'int main(void){return 0;}' > /tmp/w.c \
 && emcc -O1 /tmp/w.c -o /tmp/w.js -sASYNCIFY -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 \
 && rm -f /tmp/w.*
WORKDIR /src
