/* PC (browser) replacement for libultra: internal interface shared by the port/ultra sources. */
#ifndef PC_ULTRA_H
#define PC_ULTRA_H

#include <stddef.h>
#define _SIZE_T /* keep the libc size_t (same width on wasm32) */
#include <PR/ultratypes.h>
#include <PR/os_thread.h>
#include <PR/os_message.h>

/* console logging (goes to the page's console panel via stdout) */
void port_log(const char *fmt, ...);
/* called by every generated stub; logs the first PORT_STUB_LOG_MAX distinct hits */
void port_stub_hit(const char *name, const char *what);
extern int port_stub_hits;

/* scheduler (pc_sched.c) */
typedef void (*port_boot_fn)(void);
void port_run(port_boot_fn boot);  /* init fibers, call boot() on the main context, start the main loop */
void port_sched_run(void);        /* run threads until all are blocked / idle */
OSThread *port_current_thread(void);
void port_dump_threads(void);     /* log every thread and its state */
void port_post_event(int event);  /* osSetEventMesg delivery (OS_EVENT_*) */
extern unsigned port_frame_count;
extern void (*port_frame_hook)(void); /* optional per-frame callback (after VI, before threads) */

/* VI (pc_vi.c) */
void port_vi_retrace(void);

/* video (pc_video.c): WebGL2 context on #canvas, cleared every frame */
void port_video_init(void);
void port_video_frame(void);

/* ROM bytes supplied by the page (big-endian .z64 order) */
extern unsigned char *port_rom;
extern unsigned port_rom_size;

#endif
