/* Placeholder video: a WebGL2 context on #canvas, cleared every frame (proves the main loop).
 * The Fast3D/F3DEX2 interpreter (PLAN 3.3) will draw here. */
#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <math.h>
#include "pc_ultra.h"

static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;

void port_video_init(void) {
    EmscriptenWebGLContextAttributes a;
    emscripten_webgl_init_context_attributes(&a);
    a.majorVersion = 2; a.minorVersion = 0; a.alpha = 0; a.antialias = 0;
    a.preserveDrawingBuffer = 1; /* so screenshots see the last frame */
    ctx = emscripten_webgl_create_context("#canvas", &a);
    if (ctx <= 0) { port_log("[video] no WebGL2 context (%d); running headless\n", (int)ctx); ctx = 0; return; }
    emscripten_webgl_make_context_current(ctx);
    port_log("[video] WebGL2: %s\n", (const char *)glGetString(GL_VERSION));
}

void port_video_frame(void) {
    if (!ctx) return;
    float t = port_frame_count / 60.0f;
    glClearColor(0.10f + 0.08f * sinf(t), 0.12f, 0.20f + 0.10f * sinf(t * 0.7f), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
