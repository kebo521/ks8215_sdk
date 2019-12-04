
#ifndef MINUI_DEF_H
#define MINUI_DEF_H
#include "comm_type.h"
#include "sdk/sys_sdk.h"

#include "xui_ui.h"
#include "xui_fb.h"

 typedef struct minui_backend {
    // Initializes the backend and returns a gr_surface to draw into.
    gr_surface (*init)(struct minui_backend*);

    // Causes the current drawing surface (returned by the most recent
    // call to flip() or init()) to be displayed, and returns a new
    // drawing surface.
    gr_surface (*flip)(struct minui_backend*);

    // Blank (or unblank) the screen.
    void (*blank)(struct minui_backend*, int);

    // Device cleanup when drawing is done.
    void (*exit)(struct minui_backend*);
} minui_backend;

#endif /*MINUI_DEF_H*/
