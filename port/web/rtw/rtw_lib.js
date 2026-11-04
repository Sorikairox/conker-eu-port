// P376 retrowser.app build: Emscripten --js-library of conker.wasm's imports (only in the rtw build, port/Makefile rtw).
// env.rtw_* are the host imports of the retrowser v1 standard (~/Code/retrowser spec/retrowser-v1.md §4.10): the host
// hands them to the factory as Module.rtw and they read memory through Module.HEAPU8 (spec §4.2). The port_rtw_*
// functions are this build's own hooks into the worker glue (port/web/rtw/rtw_glue.js, --pre-js, object rtwGlue).
addToLibrary({
  rtw_log__deps: ['$UTF8ToString'],
  rtw_log: (ptr, len) => {
    const host = Module['rtw'];
    if (host && host['rtw_log']) return host['rtw_log'](ptr, len) | 0;
    out(UTF8ToString(ptr, len));
    return 0;
  },
  rtw_build_id: (ptr) => {
    const host = Module['rtw'];
    if (host && host['rtw_build_id']) return host['rtw_build_id'](ptr) | 0;
    HEAPU8.fill(0, ptr, ptr + 32);   // no host: an all-zero id
    return 0;
  },
  rtw_rumble: (port, on) => {
    const host = Module['rtw'];
    return host && host['rtw_rumble'] ? host['rtw_rumble'](port, on) | 0 : 0;
  },
  rtw_export_file: (namePtr, mimePtr, ptr, len) => {
    const host = Module['rtw'];
    return host && host['rtw_export_file'] ? host['rtw_export_file'](namePtr, mimePtr, ptr, len) | 0 : -1;
  },
  rtw_pointer_lock: (on) => {
    const host = Module['rtw'];
    return host && host['rtw_pointer_lock'] ? host['rtw_pointer_lock'](on) | 0 : 0;
  },

  // pc_video.c port_video_init: the WebGL2 context on the host's OffscreenCanvas, with the attributes the page build
  // asks emscripten_webgl_create_context for (WebGL 2, no alpha, no antialias, depth, preserveDrawingBuffer for photos)
  port_rtw_gl_create__deps: ['$GL'],
  port_rtw_gl_create: () => {
    const canvas = Module['canvas'];
    if (!canvas) { err('[video] the host gave no OffscreenCanvas'); return 0; }
    rtwGlue.beforeGl();
    return GL.createContext(canvas, {
      majorVersion: 2, minorVersion: 0, alpha: false, depth: true, stencil: false, antialias: false,
      premultipliedAlpha: true, preserveDrawingBuffer: true, powerPreference: 'default',
      failIfMajorPerformanceCaveat: false, enableExtensionsByDefault: true,
    });
  },
  port_rtw_gl_ready: () => rtwGlue.glReady(),
  port_rtw_glue_start: () => rtwGlue.start(),
  port_rtw_glue_option: (id, value) => rtwGlue.option(id, value),
  port_rtw_glue_resize: (width, height, dpr100) => rtwGlue.resize(width, height, dpr100),
  port_rtw_glue_pause: (on) => rtwGlue.pause(on),
});
