#include "header.h"

int main(void)
{
    /* mandelbrot_print(); */
    GConf gconf = {
        .window_width = 300,
        .window_height = 300
    };
    GState *gstate = graphics_init(&gconf);
    graphics_run(gstate);
    graphics_quit(gstate);
    return 0;
}
