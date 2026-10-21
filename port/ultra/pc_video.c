/* Video: the WebGL2 context on #canvas. Game frames are drawn by the F3DEX2 interpreter
 * (port/gfx) when the scheduler submits gfx tasks (pc_os.c osSpTaskStartGo); until a frame has
 * been drawn the canvas is cleared to an animated colour (proves the main loop). ?gfxdemo= shows
 * the ROM asset viewer instead. */
#include <emscripten.h>
#include <emscripten/html5.h>
#include <GLES3/gl3.h>
#include <math.h>
#include "pc_ultra.h"
#include "../gfx/gfx.h"

unsigned port_gfx_frame_tasks; /* gfx tasks drawn since the last VI frame (pc_os.c) */
static int demo; /* ?gfxdemo=...: ROM asset viewer (port/gfx/gfx_demo.c) */

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
    gfx_init();
    demo = emscripten_run_script_int("(typeof location !== 'undefined' && /[?&]gfxdemo=/.test(location.search)) ? 1 : 0");
}

void port_video_frame(void) {
    if (!ctx) return;
    if (demo == 1) {
        char *spec = emscripten_run_script_string("new URLSearchParams(location.search).get('gfxdemo') || '1'");
        demo = gfx_demo_init(spec) == 0 ? 2 : 0;
    }
    if (demo == 2) { gfx_demo_frame(); return; }
    if (port_gfx_frame_tasks) { port_gfx_frame_tasks = 0; return; } /* the game drew this frame */
    float t = port_frame_count / 60.0f;
    glClearColor(0.10f + 0.08f * sinf(t), 0.12f, 0.20f + 0.10f * sinf(t * 0.7f), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
